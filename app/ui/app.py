import streamlit as st

st.write("""
# Derivatives Pricer
""")

product = st.radio("Pick a derivative", ["Call (Vanilla)", "Put (Vanilla)", "Straddle", "Strangle", "CFD"])

print(product)
