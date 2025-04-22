#include <wbc/robot_models/pinocchio/RobotModelPinocchio.hpp>
#include "../../eigen_conversion.h"
#include "../../std_vector_conversion.h"
#include "../../wbc_types_conversions.h"

BOOST_PYTHON_MODULE(robot_model_pinocchio){

    np::initialize();

    py::class_<wbc::RobotModelPinocchio>("RobotModelPinocchio")
            .def("configure",               &wbc::RobotModelPinocchio::configure)
            .def("update",                  &wbc::RobotModelPinocchio::update)
            .def("jointState",              &wbc::RobotModelPinocchio::jointState, py::return_value_policy<py::copy_const_reference>())
            .def("pose",                    &wbc::RobotModelPinocchio::pose, py::return_value_policy<py::copy_const_reference>())
            .def("twist",                   &wbc::RobotModelPinocchio::twist, py::return_value_policy<py::copy_const_reference>())
            .def("acceleration",            &wbc::RobotModelPinocchio::acceleration, py::return_value_policy<py::copy_const_reference>())
            .def("spaceJacobian",           &wbc::RobotModelPinocchio::spaceJacobian, py::return_value_policy<py::copy_const_reference>())
            .def("bodyJacobian",            &wbc::RobotModelPinocchio::bodyJacobian, py::return_value_policy<py::copy_const_reference>())
            .def("comJacobian",             &wbc::RobotModelPinocchio::comJacobian, py::return_value_policy<py::copy_const_reference>())
            .def("spatialAccelerationBias", &wbc::RobotModelPinocchio::spatialAccelerationBias, py::return_value_policy<py::copy_const_reference>())
            .def("jointSpaceInertiaMatrix", &wbc::RobotModelPinocchio::jointSpaceInertiaMatrix, py::return_value_policy<py::copy_const_reference>())
            .def("biasForces",              &wbc::RobotModelPinocchio::biasForces, py::return_value_policy<py::copy_const_reference>())
            .def("jointNames",              &wbc::RobotModelPinocchio::jointNames, py::return_value_policy<py::copy_const_reference>())
            .def("actuatedJointNames",      &wbc::RobotModelPinocchio::actuatedJointNames, py::return_value_policy<py::copy_const_reference>())
            .def("independentJointNames",   &wbc::RobotModelPinocchio::independentJointNames, py::return_value_policy<py::copy_const_reference>())
            .def("jointIndex",              &wbc::RobotModelPinocchio::jointIndex)
            .def("baseFrame",               &wbc::RobotModelPinocchio::baseFrame, py::return_value_policy<py::copy_const_reference>())
            .def("jointLimits",             &wbc::RobotModelPinocchio::jointLimits)
            .def("selectionMatrix",         &wbc::RobotModelPinocchio::selectionMatrix, py::return_value_policy<py::copy_const_reference>())
            .def("hasLink",                 &wbc::RobotModelPinocchio::hasLink)
            .def("hasJoint",                &wbc::RobotModelPinocchio::hasJoint)
            .def("hasActuatedJoint",        &wbc::RobotModelPinocchio::hasActuatedJoint)
            .def("centerOfMass",            &wbc::RobotModelPinocchio::centerOfMass, py::return_value_policy<py::copy_const_reference>())
            .def("setContacts",             &wbc::RobotModelPinocchio::setContacts)
            .def("getContacts",             &wbc::RobotModelPinocchio::getContacts, py::return_value_policy<py::copy_const_reference>())
            .def("nj",                      &wbc::RobotModelPinocchio::nj)
            .def("na",                      &wbc::RobotModelPinocchio::na)
            .def("nfb",                     &wbc::RobotModelPinocchio::nfb)
            .def("nc",                      &wbc::RobotModelPinocchio::nc)
            .def("nac",                     &wbc::RobotModelPinocchio::nac)
            .def("setJointWeights",         &wbc::RobotModelPinocchio::setJointWeights)
            .def("getJointWeights",         &wbc::RobotModelPinocchio::getJointWeights, py::return_value_policy<py::copy_const_reference>())
            .def("floatingBaseState",       &wbc::RobotModelPinocchio::floatingBaseState, py::return_value_policy<py::copy_const_reference>());
}


