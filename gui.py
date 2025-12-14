import numpy as np
import pandas as pd
import streamlit as st
from derivatives_pricer import Strangle, BlackScholesParams, Derivative, EUCall
import matplotlib.pyplot as plt

from app.core.curves import payoff_curve, price_curve
from app.core.plots import plot_diff_maturities_price_payoff

plt.style.use('dark_background')

st.write("""
# Derivatives Pricer
""")

ui_products_list = ["Call (Vanilla)", "Put (Vanilla)", "Straddle", "Strangle", "CFD"]
ui_product = st.radio("Pick a derivative", ui_products_list)

print(ui_product)

product = None
if ui_product == "Call (Vanilla)":
    product = EUCall(100, 150, 1, 1, "SP");

fig = plot_diff_maturities_price_payoff(product,
                                        1.2, 0.05, BlackScholesParams())
st.pyplot(fig)

data = payoff_curve(product)
# data = pd.DataFrame(data[1].T, index=data[0])
data = pd.DataFrame(data.T, columns=["Spot price", "Payoff"])
# data.rename(columns={0: "Payoff"}, inplace=True)
# data.rename(index={0: "Spot"}, inplace=True)
print(data)
st.line_chart(data, x="Spot price", y="Payoff")


def plot_diff_maturities_price_payoff_SL(product, vol, r, pricingParams):
    x, y = payoff_curve(product)
    data = pd.DataFrame({"Spot": x, "Payoff": y})

    T0 = product.timeToMaturity
    for T in [1.0, 0.5, 0.1]:
        product.timeToMaturity = T
        x, y = price_curve(product, pricingParams, vol, r)
        data[f"Price (T={T})"] = y
    product.timeToMaturity = T0

    st.line_chart(data, x="Spot")


plot_diff_maturities_price_payoff_SL(product, 1.2, 0.05, BlackScholesParams())
