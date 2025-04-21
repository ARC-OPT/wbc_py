#include "../../eigen_conversion.h"
#include "../../std_vector_conversion.h"
#include <wbc/solvers/qpoases/QPOasesSolver.hpp>
#include "QPOasesSolver.hpp"
#include <wbc/core/QuadraticProgram.hpp>

BOOST_PYTHON_MODULE(qpoases_solver){

    np::initialize();
    py::class_<wbc_py::QPOASESSolver>("QPOASESSolver")
            .def("solve", &wbc_py::QPOASESSolver::solve)
            .def("setMaxNoWSR", &wbc::QPOASESSolver::setMaxNoWSR)
            .def("getMaxNoWSR", &wbc::QPOASESSolver::getMaxNoWSR)
            .def("getReturnValue", &wbc::QPOASESSolver::getReturnValue)
            .def("getNoWSR", &wbc::QPOASESSolver::getNoWSR)
            .def("getOptions", &wbc::QPOASESSolver::getOptions)
            .def("setOptions", &wbc::QPOASESSolver::setOptions);
}


