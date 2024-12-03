#include "controllers.hpp"

namespace wbc_py {
JointPosPDController::JointPosPDController(const std::vector<std::string> &joint_names) :
    wbc::JointPosPDController(joint_names){
}
base::NamedVector<base::JointState> JointPosPDController::update(const base::NamedVector<base::JointState> &setpoint,
                                                                 const base::NamedVector<base::JointState> &feedback){
    return toNamedVector(wbc::JointPosPDController::update(tobaseSamplesJoints(setpoint), tobaseSamplesJoints(feedback)));
}
}

BOOST_PYTHON_MODULE(controllers){

    np::initialize();

    py::class_<wbc::CartesianPosPDController>("CartesianPosPDController")
            .def("update", &wbc::CartesianPosPDController::update, py::return_value_policy<py::copy_const_reference>())
            .def("setPGain", &wbc::CartesianPosPDController::setPGain)
            .def("setDGain", &wbc::CartesianPosPDController::setDGain)
            .def("setFFGain", &wbc::CartesianPosPDController::setFFGain)
            .def("setMaxCtrlOutput", &wbc::CartesianPosPDController::setMaxCtrlOutput)
            .def("setDeadZone", &wbc::CartesianPosPDController::setDeadZone)
            .def("pGain", &wbc::CartesianPosPDController::pGain, py::return_value_policy<py::copy_const_reference>())
            .def("dGain", &wbc::CartesianPosPDController::dGain, py::return_value_policy<py::copy_const_reference>())
            .def("ffGain", &wbc::CartesianPosPDController::ffGain, py::return_value_policy<py::copy_const_reference>())
            .def("maxCtrlOutput", &wbc::CartesianPosPDController::maxCtrlOutput, py::return_value_policy<py::copy_const_reference>())
            .def("deadZone", &wbc::CartesianPosPDController::deadZone, py::return_value_policy<py::copy_const_reference>())
            .def("getControlError", &wbc::CartesianPosPDController::getControlError);

    py::class_<wbc_py::JointPosPDController>("JointPosPDController", py::init<std::vector<std::string>>())
            .def("update", &wbc_py::JointPosPDController::update)
            .def("setPGain", &wbc_py::JointPosPDController::setPGain)
            .def("setDGain", &wbc_py::JointPosPDController::setDGain)
            .def("setFFGain", &wbc_py::JointPosPDController::setFFGain)
            .def("setMaxCtrlOutput", &wbc_py::JointPosPDController::setMaxCtrlOutput)
            .def("setDeadZone", &wbc_py::JointPosPDController::setDeadZone)
            .def("pGain", &wbc_py::JointPosPDController::pGain, py::return_value_policy<py::copy_const_reference>())
            .def("dGain", &wbc_py::JointPosPDController::dGain, py::return_value_policy<py::copy_const_reference>())
            .def("ffGain", &wbc_py::JointPosPDController::ffGain, py::return_value_policy<py::copy_const_reference>())
            .def("maxCtrlOutput", &wbc_py::JointPosPDController::maxCtrlOutput, py::return_value_policy<py::copy_const_reference>())
            .def("deadZone", &wbc_py::JointPosPDController::deadZone, py::return_value_policy<py::copy_const_reference>())
            .def("getControlError", &wbc_py::JointPosPDController::getControlError);
}
