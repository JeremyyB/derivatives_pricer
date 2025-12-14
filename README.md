# Derivatives Pricer

This project is **not** a simple prototype notebook.

This project aims to build a production-grade derivatives pricer.

We price using C++ (as it is done in the industry) for execution speed,
and we then use Python to endow the pricer with a graphical user interface, an API and a database storage (to boost
efficiency).


Future tasks :
- [ ] Logger in C++
- [ ] Logger in Python
- [ ] Return directly the vanilla priceS as a couple = less computation
- [ ] GUI
- [ ] DB storages
- [ ] API exchanges
- [ ] yfinance data download to price get historical, implied-vol of a Ticker

## Install :

```zsh
pip install pybind11 # Installing it with conda is better way to build the C++ engine 
pip install ./derivatives_pricer
```

## Update work flow

1. Build in C++, (`src`) : 
```zsh
cd ./derivatives_pricer
mkdir build
cd build
cmake ..
make .. -I .venv/.Python # Or any path directing to your Python installation
```
2. Update the module with pip, as in the first install
3. Use it in Python (`app`), for now :

## Run the GUI app

`streamlit run ./derivatives_pricer/gui.py`

## Comments

The idea is to price every derivative I have met from now.