#include "../../eigen_conversion.h"
#include "../../std_vector_conversion.h"
#include <wbc/core/QuadraticProgram.hpp>
#include "QPOasesSolver.hpp"

BOOST_PYTHON_MODULE(qpoases_solver){

    np::initialize();
    py::class_<wbc_py::QPOASESSolver>("QPOASESSolver")
            .def("solve", &wbc_py::QPOASESSolver::solve)
            .def("setMaxNoWSR", &wbc_py::QPOASESSolver::setMaxNoWSR)
            .def("getMaxNoWSR", &wbc_py::QPOASESSolver::getMaxNoWSR)
            .def("getReturnValue", &wbc_py::QPOASESSolver::getReturnValue)
            .def("getNoWSR", &wbc_py::QPOASESSolver::getNoWSR)
            .def("getOptions", &wbc_py::QPOASESSolver::getOptions)
            .def("setOptions", &wbc_py::QPOASESSolver::setOptions);
}


