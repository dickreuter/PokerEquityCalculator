#include <C:\Users\dickr\AppData\Local\Continuum\anaconda3\include\pybind11\pybind11.h>
#include "Scoring.h"

namespace py = pybind11;
using namespace pybind11::literals;

PYBIND11_PLUGIN(code) {
	pybind11::module m("code", "auto-compiled c++ extension");
	m.def("montecarlo", py::montecarlo(square));
	return m.ptr();
}