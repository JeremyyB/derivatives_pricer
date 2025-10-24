import numpy as np
import streamlit as st
from derivatives_pricer import Strangle, BlackScholesParams, Derivative, EUCall
import matplotlib.pyplot as plt
from app.core.plots import plotDifferentMaturitiesPricePayoff

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

fig = plotDifferentMaturitiesPricePayoff(product,
    1.2, 0.05, BlackScholesParams())
st.pyplot(fig)