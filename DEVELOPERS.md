

## STRUCTURE

```
derivatives_pricer/
├── CMakeLists.txt
├── setup.py
├── app/
│   ├── db/
│   ├── ui/
│   └── api/
└── src/
    ├── bindings/
    │   └── bind.cpp
    └── engine/
        ├── methods/
        ├── models/
        ├── utils/
        └── products/
```


### How do I price a product ?
`EUCall(double s0, double strike, double time_to_maturity, double position, const std::string &underlying_id)`
Here's a direct example : 
1. Create the product object
```python
b = EUCall(100,     <-- Premium S0 
           150,     <-- Strike
           1,       <-- Time to maturity (1 for 1 year)
           1,       <-- Position (1 for long, -1 for short)
           "DAX")   <-- Underlying Identifier (for database storage purposes)
```

2. Price it :
```python
b.price(1.2,                           <-- Volatility
        0.05,                          <-- Risk-free rate
        BinomialParams(100, 1.5, 0.5)) <-- A PricingParams object
```
where the PricingParams object contains the necessary parameters for the pricing engine.

For example, 
- the Black-Scholes model requires no more parameters,
- the Binomial model requires the number of time steps and the coefficients $up$ and $down$.

That way, you can price any product with any pricing engine.

Remark that stochastic volatility/risk-free rate pricing models require additional parameters that can override the default pricing parameters.


## Future work

- [ ] Logger in C++
- [ ] Logger in Python
- [ ] Return directly the vanilla priceS as a couple = less computation
- [ ] GUI
- [ ] DB storages
- [ ] API exchanges
- [ ] yfinance data download to price get historical, implied-vol of a Ticker
