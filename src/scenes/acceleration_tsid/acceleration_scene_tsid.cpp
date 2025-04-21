#include "../../eigen_conversion.h"
#include "../../std_vector_conversion.h"
#include "acceleration_scene_tsid.hpp"

namespace wbc_py{
    AccelerationSceneTSID::AccelerationSceneTSID(std::shared_ptr<wbc::RobotModelPinocchio> robot_model, std::shared_ptr<wbc::QPOASESSolver> solver, const double dt) : 
        wbc::AccelerationSceneTSID(robot_model, solver, dt){
    }
}

BOOST_PYTHON_MODULE(acceleration_scene_tsid){

    np::initialize();

    py::class_<wbc_py::AccelerationSceneTSID>("AccelerationSceneTSID", py::init<std::shared_ptr<wbc::RobotModelPinocchio>,std::shared_ptr<wbc::QPOASESSolver>,const double>())
            .def("configure",                  &wbc_py::AccelerationSceneTSID::configure)
            .def("addSpatialAccelerationTask", &wbc_py::AccelerationSceneTSID::addSpatialAccelerationTask)
            .def("update",                     &wbc::AccelerationSceneTSID::update, py::return_value_policy<py::copy_const_reference>())
            .def("solve",                      &wbc::AccelerationSceneTSID::solve, py::return_value_policy<py::copy_const_reference>());
}
