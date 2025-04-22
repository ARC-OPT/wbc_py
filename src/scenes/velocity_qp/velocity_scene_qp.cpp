#include "velocity_scene_qp.hpp"
#include "../../eigen_conversion.h"
#include "../../std_vector_conversion.h"

namespace wbc_py{
    VelocitySceneQP::VelocitySceneQP(std::shared_ptr<wbc::RobotModelPinocchio> robot_model, std::shared_ptr<wbc_py::QPOASESSolver> solver, const double dt) : 
        wbc::VelocitySceneQP(robot_model, solver, dt){
    }
}

BOOST_PYTHON_MODULE(velocity_scene_qp){

    np::initialize();

    py::class_<wbc_py::VelocitySceneQP>("VelocitySceneQP", py::init<std::shared_ptr<wbc::RobotModelPinocchio>, std::shared_ptr<wbc_py::QPOASESSolver>, const double>())
            .def("configure",              &wbc_py::VelocitySceneQP::configure)
            .def("addSpatialVelocityTask", &wbc_py::VelocitySceneQP::addSpatialVelocityTask)
            .def("update",                 &wbc::VelocitySceneQP::update, py::return_value_policy<py::copy_const_reference>())
            .def("solve",                  &wbc::VelocitySceneQP::solve, py::return_value_policy<py::copy_const_reference>());
}
