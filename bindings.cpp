#include <pybind11/pybind11.h> //pybind is a library that exposes C++ types in python and vice versa
#include "BSModel.h"

namespace py = pybind11;


PYBIND11_MODULE(quant_engine, m) {
    
    //in case anyone wants to see the documentation. (idk how to document it)
    m.doc() = "High-performance Monte Carlo Option Pricer built with C++17";

    // -----------------------------------------------------------------------
    // 1. Bind the 'OptionType' Enum
    // -----------------------------------------------------------------------
    // This allows Python to use: quant_engine.OptionType.Call
    py::enum_<OptionType>(m, "OptionType")
        .value("Call", OptionType::Call)
        .value("Put", OptionType::Put)
        .export_values(); // Allows accessing Call/Put directly from the enum

    // -----------------------------------------------------------------------
    // 2. Bind the 'BSModel' Class
    // -----------------------------------------------------------------------
    py::class_<BSModel>(m, "BSModel")
        // Bind the Constructor
        // We specify the argument types <double, double...> so pybind knows which C++ constructor to call
        .def(py::init<double, double, double, double, double>(),
             "Constructor: BSModel(S0, K, r, sigma, T)",
             // These 'py::arg' calls allow you to use named arguments in Python!
             // e.g., model = BSModel(S0=100, K=105, ...)
             py::arg("S0"), py::arg("K"), py::arg("r"), py::arg("sigma"), py::arg("T"))
        
        // Bind the 'priceOption' method
        // Note: We rename it to 'price_option' to follow Python's snake_case style
        .def("price_option", &BSModel::priceOption,
             "Calculates the fair value of the option using Monte Carlo simulation",
             py::arg("num_simulations"), py::arg("type"));
}