#include "../../eigen_conversion.h"
#include "../../std_vector_conversion.h"
#include "acceleration_scene_reduced_tsid.hpp"

namespace wbc_py{
    AccelerationSceneReducedTSID::AccelerationSceneReducedTSID(std::shared_ptr<wbc::RobotModelPinocchio> robot_model, std::shared_ptr<wbc_py::QPOASESSolver> solver, const double dt) : 
        wbc::AccelerationSceneReducedTSID(robot_model, solver, dt){
    }
}

BOOST_PYTHON_MODULE(acceleration_scene_reduced_tsid){

    np::initialize();

    py::class_<wbc_py::AccelerationSceneReducedTSID>("AccelerationSceneReducedTSID", py::init<std::shared_ptr<wbc::RobotModelPinocchio>,std::shared_ptr<wbc_py::QPOASESSolver>,const double>())
            .def("configure",                  &wbc_py::AccelerationSceneReducedTSID::configure)
            .def("addSpatialAccelerationTask", &wbc_py::AccelerationSceneReducedTSID::addSpatialAccelerationTask)
            .def("update",                     &wbc_py::AccelerationSceneReducedTSID::update, py::return_value_policy<py::copy_const_reference>())
            .def("solve",                      &wbc_py::AccelerationSceneReducedTSID::solve, py::return_value_policy<py::copy_const_reference>());
}
