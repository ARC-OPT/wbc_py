#include "controllers.hpp"

namespace wbc_py{

}

BOOST_PYTHON_MODULE(controllers){

    np::initialize();

    py::class_<wbc_py::CartesianPosPDController>("CartesianPosPDController")
            .def("updateVel", &wbc_py::CartesianPosPDController::updateVel)
            .def("updateAcc", &wbc_py::CartesianPosPDController::updateAcc)
            .def("setPGain", &wbc_py::CartesianPosPDController::setPGain)
            .def("setDGain", &wbc_py::CartesianPosPDController::setDGain)
            .def("setMaxCtrlOutput", &wbc_py::CartesianPosPDController::setMaxCtrlOutput)
            .def("pGain", &wbc_py::CartesianPosPDController::pGain, py::return_value_policy<py::copy_const_reference>())
            .def("dGain", &wbc_py::CartesianPosPDController::dGain, py::return_value_policy<py::copy_const_reference>())
            .def("maxCtrlOutput", &wbc_py::CartesianPosPDController::maxCtrlOutput, py::return_value_policy<py::copy_const_reference>());

    py::class_<wbc_py::JointPosPDController>("JointPosPDController", py::init<uint>())
            .def("updateVel", &wbc_py::JointPosPDController::updateVel)
            .def("updateAcc", &wbc_py::JointPosPDController::updateAcc)
            .def("setPGain", &wbc_py::JointPosPDController::setPGain)
            .def("setDGain", &wbc_py::JointPosPDController::setDGain)
            .def("setMaxCtrlOutput", &wbc_py::JointPosPDController::setMaxCtrlOutput)
            .def("pGain", &wbc_py::JointPosPDController::pGain, py::return_value_policy<py::copy_const_reference>())
            .def("dGain", &wbc_py::JointPosPDController::dGain, py::return_value_policy<py::copy_const_reference>())
            .def("maxCtrlOutput", &wbc_py::JointPosPDController::maxCtrlOutput, py::return_value_policy<py::copy_const_reference>());
}
