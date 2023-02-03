#include <pybind11/pybind11.h>
#include "interface.h"

namespace py = pybind11;

/*PYBIND11_MODULE(libFCpython, m) {
    m.doc() = "pybind11 example plugin"; // optional module docstring

    m.def("current_time", &current_time, "A function that returns the current time");
}*/

PYBIND11_MODULE(libFCpython, m) {
    py::class_<interface>(m, "interface")
        .def(py::init<>())
        .def("create_simulation", &interface::create_simulation)
        .def("run_simulation", &interface::run_simulation)
        .def("end_simulation", &interface::end_simulation);
}