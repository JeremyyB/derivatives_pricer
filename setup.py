from setuptools import setup
from pybind11.setup_helpers import Pybind11Extension, build_ext

ext_modules = [
    Pybind11Extension(
        "derivatives_pricer",
        [
            "src/bindings/bind.cpp",

            "src/engine/products/eu_call.cpp",
            "src/engine/products/eu_put.cpp",
            "src/engine/products/cfd.cpp",
            "src/engine/products/Derivative.cpp",
            "src/engine/products/strangle.cpp",

            "src/engine/models/Model.cpp",
            "src/engine/models/BlackScholes.cpp",
            "src/engine/models/MonteCarlo.cpp",

            "src/engine/utils/Params.cpp",
        ],
        # All C++ source files
        include_dirs=[
            "src",
            "src/bindings",
            "src/engine",
            "src/engine/products",
            "src/engine/methods",
            "src/engine/utils",
        ],
        # Header include path
        cxx_std=17,  # (Compile with C++17 support)
    ),
]

setup(
    name="derivatives_pricer",
    version="0.1.1",
    author="Jeremy B.",
    description="Derivatives pricer with C++ efficiency",
    ext_modules=ext_modules,
    cmdclass={"build_ext": build_ext},
    zip_safe=False,
)
