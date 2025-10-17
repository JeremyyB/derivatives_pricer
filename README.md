# Derivatives Pricer

This project aims to build a production-grade derivatives pricer.

The idea is to price every derivative I have met from now.

We price using C++ (as it is done in the industry) for execution speed,
and we then use Python to endow the pricer with a graphical user interface, an API and a database storage (to boost
efficiency)

Future tasks involve graphical representation and API exchanges

## Install :

Of course, we recommend you to be in a virtual env. :

`pip install pybind11`

`pip install ./derivatives_pricer`

## Update work flow

1. Build in C++, (`src`)
2. Update the module with pip
3. Use it in Python (`app`)