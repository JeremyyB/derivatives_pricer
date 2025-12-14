import numpy as np
import pandas as pd
import streamlit as st
import plotly.express as px
from derivatives_pricer import Strangle, BlackScholesParams, Derivative, EUCall

from app.core.curves import payoff_curve, price_curve
from app.core.datadl import get_current_spot

st.write("""
# Derivatives Pricer
""")


MAX_MATURITY_DAYS = 150

strike = st.sidebar.slider("Strike Price (% to the Spot)", min_value=50, max_value=150, value=100, step=1)
time_to_maturity = st.sidebar.slider("Maturity (in days)", min_value=1, max_value=MAX_MATURITY_DAYS, value=7, step=1)
position = st.sidebar.slider("Position (negative for short)", min_value=-10, max_value=10, value=1, step=1)
underlying_ticker = st.sidebar.text_input("Underlying Ticker:", "AAPL")

ui_products_list = ["Call (Vanilla)", "Put (Vanilla)", "Straddle", "Strangle", "CFD"]
ui_product = st.radio("Pick a derivative", ui_products_list)

product = None
if ui_product == "Call (Vanilla)":
    spot = get_current_spot(underlying_ticker)
    product = EUCall(spot, spot*strike/100, time_to_maturity/MAX_MATURITY_DAYS, position, underlying_ticker)

if product:
    spot_payoff = payoff_curve(product)
    spot_price = price_curve(product, BlackScholesParams(), 1.2, 0.05)

    df = pd.DataFrame({
        'Spot': spot_payoff[0],
        'Payoff': spot_payoff[1],
        'Price': spot_price[1]
    })

    fig = px.line(df, x='Spot', y=['Payoff', 'Price'],
                  title=f'Price and Payoff Curves (Strike={strike})')
    fig.update_layout(
        xaxis_title="Spot Price",
        yaxis_title="Value",
        showlegend=True
    )
    st.plotly_chart(fig)
