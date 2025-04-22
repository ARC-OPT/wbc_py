#include <wbc/robot_models/pinocchio/RobotModelPinocchio.hpp>
#include <wbc/tasks/SpatialVelocityTask.hpp>
#include <wbc/tasks/SpatialAccelerationTask.hpp>
#include <boost/python/module.hpp>
#include <boost/python/numpy.hpp>
#include <wbc/core/TaskConfig.hpp>

namespace py = boost::python;
namespace np = boost::python::numpy;

BOOST_PYTHON_MODULE(tasks){

    np::initialize();

    py::class_<wbc::SpatialVelocityTask>("SpatialVelocityTask", py::init<wbc::TaskConfig, std::shared_ptr<wbc::RobotModelPinocchio>, std::string, std::string>())
        .def("update",        &wbc::SpatialVelocityTask::update)
        .def("setReference",  &wbc::SpatialVelocityTask::setReference)
        .def("setWeights",    &wbc::SpatialVelocityTask::setWeights)
        .def("setActivation", &wbc::SpatialVelocityTask::setActivation)
        .def("tipFrame",      &wbc::SpatialVelocityTask::tipFrame, py::return_value_policy<py::copy_const_reference>())
        .def("refFrame",      &wbc::SpatialVelocityTask::refFrame, py::return_value_policy<py::copy_const_reference>());

    py::class_<wbc::SpatialAccelerationTask>("SpatialAccelerationTask", py::init<wbc::TaskConfig, std::shared_ptr<wbc::RobotModelPinocchio>, std::string, std::string>())
        .def("update",        &wbc::SpatialAccelerationTask::update)
        .def("setReference",  &wbc::SpatialAccelerationTask::setReference)
        .def("setWeights",    &wbc::SpatialAccelerationTask::setWeights)
        .def("setActivation", &wbc::SpatialAccelerationTask::setActivation)
        .def("tipFrame",      &wbc::SpatialAccelerationTask::tipFrame, py::return_value_policy<py::copy_const_reference>())
        .def("refFrame",      &wbc::SpatialAccelerationTask::refFrame, py::return_value_policy<py::copy_const_reference>());
}
