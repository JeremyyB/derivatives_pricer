import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import datetime as _dt
from typing import Optional, Union

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import yfinance as yf


def download_ticker_data(
        ticker: str,
        interval: str,
        past: Union[str, _dt.date, _dt.datetime, int],
        *,
        auto_adjust: bool = False,
        prepost: bool = False,
        tz: str = "UTC",
) -> pd.DataFrame:
    """
    Download time series for `ticker`


    :param ticker:
        Symbol to download (e.g. "AAPL", "EURUSD=X", "^GSPC").
    :param interval:
        Bar size accepted by yfinance, e.g. "1m","2m","5m","15m","30m","60m","90m",
        "1h","1d","5d","1wk","1mo","3mo".
    :param past:
        Defines how far back to download:
        - int: number of days to look back from now (UTC)
        - str/date/datetime: interpreted as the start date/time (inclusive)
          (strings should be parseable by pandas, e.g. "2024-01-01").
    :parama uto_adjust:
        If True, adjusts OHLC for splits/dividends (yfinance parameter).
    :param prepost:
        If True, includes pre/post market data where available (yfinance parameter).
    :param tz:
        Timezone to convert the returned index to (default "UTC").

    :return pd.DataFrame
        DataFrame with columns like: Open, High, Low, Close, Adj Close (optional), Volume.
        Index is a DatetimeIndex.
    """
    if not isinstance(ticker, str) or not ticker.strip():
        raise ValueError("ticker must be a non-empty string")

    interval = str(interval).strip()
    if not interval:
        raise ValueError("interval must be a non-empty string (e.g. '1d', '1h', '5m')")

    now_utc = pd.Timestamp.now(tz="UTC")

    if isinstance(past, int):
        if past <= 0:
            raise ValueError("past (int) must be a positive number of days")
        start = now_utc - pd.Timedelta(days=past)
    else:
        start = pd.to_datetime(past, utc=True, errors="raise")

    df = yf.download(
        tickers=ticker,
        start=start.to_pydatetime(),
        interval=interval,
        auto_adjust=auto_adjust,
        prepost=prepost,
        progress=False,
        group_by="column",
        threads=True,
    )

    if df is None or df.empty:
        raise ValueError(
            f"No data returned for ticker={ticker!r} (interval={interval!r}, start={start.isoformat()})."
        )

    # If yfinance returns a MultiIndex (can happen when multiple tickers are passed),
    # keep only the requested ticker.
    if isinstance(df.columns, pd.MultiIndex):
        if ticker in df.columns.get_level_values(0):
            df = df[ticker]
        else:
            # Fallback: take the first symbol
            df = df.xs(df.columns.get_level_values(0)[0], axis=1)

    # Normalize index to timezone-aware and convert
    if not isinstance(df.index, pd.DatetimeIndex):
        df.index = pd.to_datetime(df.index, utc=True)
    elif df.index.tz is None:
        df.index = df.index.tz_localize("UTC")

    if tz:
        df.index = df.index.tz_convert(tz)

    df = df.sort_index()
    return df


def get_current_spot(ticker: str) -> float:
    if not isinstance(ticker, str) or not ticker.strip():
        raise ValueError("ticker must be a non-empty string")

    t = yf.Ticker(ticker)

    # Try to get the info asap
    last = None
    try:
        fi = getattr(t, "fast_info", None)
        if fi:
            last = fi.get("last_price", None)
    except Exception:
        last = None

    if last is not None and np.isfinite(last):
        return float(last)

    # Fallback: recent intraday close
    hist = t.history(period="1d", interval="1m", prepost=False)
    if hist is None or hist.empty or "Close" not in hist.columns:
        raise ValueError(f"Could not fetch current spot for ticker={ticker!r}")

    spot = hist["Close"].dropna().iloc[-1]
    return float(spot)
