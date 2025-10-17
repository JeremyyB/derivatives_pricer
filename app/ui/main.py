import datetime

#import derivatives_pricer as dp
from derivatives_pricer import EUCall, PricingMethod


print('Hello world')
#print(dp.cfd_payoff(4., -2., 3.))

a = EUCall(3, 90, 4, 10, "Hey")
print(a.payoff(4))

print(a.price(1.9, 0.5, PricingMethod.BLACK_SCHOLES))
