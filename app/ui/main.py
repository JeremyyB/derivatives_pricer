import datetime
import numpy as np
import matplotlib.pyplot as plt

# import derivatives_pricer as dp
from derivatives_pricer import EUCall, EUPut, CFD, PricingMethod, Strangle, Straddle, MonteCarlo, BlackScholes, \
    MonteCarloParams, BlackScholesParams

print('Hello world')
# print(dp.cfd_payoff(4., -2., 3.))

"""
a = EUPut(3, 90, 4, 10, "Hey")
print(a.payoff(4))

print(a.price(1.9, 0.5, PricingMethod.BLACK_SCHOLES))
"""

"""
Derivative(double s0, double strike, double time_to_maturity, double position,
const std::string &underlying_id)
"""

"""
b = EUCall(100, 150, 1, 1, "SP500")
vol = np.array([(i+1)/10 for i in range(20)])
y = np.array([b.price(vol, 0.05, PricingMethod.BLACK_SCHOLES) for vol in vol])
plt.plot(vol, y)
plt.show()
"""

"""
b = EUCall(100, 150, 1, 1, "SP500")
r_list = np.array([(i+1)/10 for i in range(40)])
y = np.array([b.price(0.5, r, PricingMethod.BLACK_SCHOLES) for r in r_list])
plt.plot(r_list, y)
plt.show()
"""

"""
c = CFD(100, 150, 1, -4, "BTCUSDT")
print(c.payoff(200))
"""

"""
# d = EUCall(100, 150, 1, 3, "SP500")
d = Strangle(100, 1, 3, "SP500", 90, 110)
ST_vals = np.array([i for i in range(200)])
y1 = np.array([d.payoff(ST) for ST in ST_vals])
y2 = np.array([Strangle(ST, 1, 3, "SP500", 90, 110).price(0.5, 0.05, PricingMethod.BLACK_SCHOLES) for ST in ST_vals])
plt.plot(ST_vals, y1)

"double price(double vol, double riskfree_rate, PricingMethod method) override;"


plt.plot(ST_vals, y2)
"""

"""
d = Straddle(100, 110, 1, 3, "SP500")
ST_vals = np.array([i for i in range(200)])
y1 = np.array([d.payoff(ST) for ST in ST_vals])
y2 = np.array([Straddle(ST, 110, 1, 3, "SP500").price(0.5, 0.05, PricingMethod.BLACK_SCHOLES) for ST in ST_vals])
plt.plot(ST_vals, y1)

"double price(double vol, double riskfree_rate, PricingMethod method) override;"


plt.plot(ST_vals, y2)
plt.show() 
"""

"""
c = CFD(100, 1, 2, "BTCUSDT")
ST_vals = np.array([i for i in range(300)])
y1 = np.array([c.payoff(ST) for ST in ST_vals])
plt.plot(ST_vals, y1)
plt.show()
"""

"""
m = MonteCarlo(200, 10)
paths = m.simulatePaths(100, .05, .5)
print(paths.shape)
print(paths)
for i in range(paths.shape[0]):
    plt.plot(paths[i])
plt.show()
"""

# plt.plot(MonteCarlo(200, 10).simulatePaths(100, 0.05, 0.5))
# plt.plot(MonteCarlo(200, 10, 3).simulatePaths(100, 0.05, 0.5))
# plt.plot(MonteCarlo(200, 10, -3).simulatePaths(100, 0.05, 0.5))
# plt.show()

"""
bs = BlackScholes()
print(bs.priceEUCall(100, 150, 1, 0.5, 0.05))
print(bs.simulatePaths(100, .05, .5) )
"""


b = EUCall(100, 150, 1, 1, "SP500")
# ST_vals = np.array([i for i in range(200)])
# y1 = np.array([b.payoff(ST) for ST in ST_vals])
# y2 = np.array([EUCall(ST, 150, 1, 1, "SP500").price(0.5, 0.05, PricingMethod.BLACK_SCHOLES) for ST in ST_vals])
# plt.plot(ST_vals, y1)
print("*" * 50)
print(b.price(0.5, 0.05, MonteCarloParams(2000, 93283, 500)))
#b = EUCall(100, 150, 1, 1, "SP500", BlackScholesParams())
print(b.price(0.5, 0.05, BlackScholesParams()))



"""
# updated :
d = Straddle(100, 110, 1, 3, "SP500")
ST_vals = np.array([i for i in range(200)])
y1 = np.array([d.payoff(ST) for ST in ST_vals])
y2 = np.array([Straddle(ST, 110, 1, 3, "SP500").price(0.5, 0.05, BlackScholesParams()) for ST in ST_vals])
plt.plot(ST_vals, y1)

"double price(double vol, double riskfree_rate, PricingMethod method) override;"


plt.plot(ST_vals, y2)
plt.show()
"""