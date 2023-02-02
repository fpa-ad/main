#include <pybind11/pybind11.h>
#include "myutils.h"

PYBIND11_MODULE(example, m) {
    m.doc() = "pybind11 example plugin"; // optional module docstring

    m.def("current_time", &current_time, "A function that returns the current time");
}