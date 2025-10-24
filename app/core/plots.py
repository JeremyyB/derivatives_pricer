from matplotlib import pyplot as plt

from app.core.curves import payoffCurve, priceCurve


def plotDifferentMaturitiesPricePayoff(product, vol, r, pricingParams):
    x, y = payoffCurve(product)

    fig = plt.figure(figsize=(8, 8))

    plt.plot(x, y, label="Payoff", linewidth=3)

    T0 = product.timeToMaturity
    for T in [1.0, 0.5, 0.1]:
        product.timeToMaturity = T
        x, y = priceCurve(product, pricingParams, vol, r)
        plt.plot(x, y, label=f"Price $(T={T})$")

    product.timeToMaturity = T0

    plt.axvline(x=product.strike, color='r', linestyle='--', label="Strike $K$")

    plt.legend()

    plt.xlabel("Spot Price $S$")
    plt.ylabel("Value")
    plt.tight_layout()

    return fig
