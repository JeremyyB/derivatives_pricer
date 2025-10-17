import datetime
import numpy as np
import matplotlib.pyplot as plt

#import derivatives_pricer as dp
from derivatives_pricer import EUCall, EUPut, PricingMethod


print('Hello world')
#print(dp.cfd_payoff(4., -2., 3.))

a = EUPut(3, 90, 4, 10, "Hey")
print(a.payoff(4))

print(a.price(1.9, 0.5, PricingMethod.BLACK_SCHOLES))
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

b = EUCall(100, 150, 1, 1, "SP500")
r_list = np.array([(i+1)/10 for i in range(40)])
y = np.array([b.price(0.5, r, PricingMethod.BLACK_SCHOLES) for r in r_list])
plt.plot(r_list, y)
plt.show()

