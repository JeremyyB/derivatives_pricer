import pandas as pd
import matplotlib.pyplot as plt
from derivatives_pricer import *
import numpy as np


def payoffCurve(product, x_lim=70):
    ST_vals = np.array([max(product.strike + i, 0) for i in range(-x_lim, x_lim)])
    y1 = np.array([product.payoff(ST) for ST in ST_vals])
    return ST_vals, y1


def priceCurve(product, pricingParams, vol, r, x_lim=70):
    S0 = product.S0
    spot_vals = np.array([max(product.strike + i, 0) for i in range(-x_lim, x_lim)])
    prices = []
    for spot in spot_vals:
        product.S0 = spot
        prices.append(product.price(vol, r, pricingParams))
    product.S0 = S0
    return spot_vals, np.array(prices)
