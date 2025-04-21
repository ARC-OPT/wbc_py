#include "../eigen_conversion.h"
#include "../std_vector_conversion.h"
#include "../wbc_types_conversions.h"
#include <wbc/core/RobotModelConfig.hpp>
#include <wbc/core/TaskConfig.hpp>
#include <wbc/core/QuadraticProgram.hpp>
#include <wbc/types/JointLimits.hpp>
#include <boost/python/enum.hpp>
#include <wbc/types/Contact.hpp>
#include <wbc/types/RigidBodyState.hpp>
#include <wbc/types/Wrench.hpp>
#include <wbc/types/JointState.hpp>
#include <wbc/types/JointCommand.hpp>

BOOST_PYTHON_MODULE(core){

    np::initialize();

    pygen::convertMatrix<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::AutoAlign, -1 , -1>>();    
    pygen::convertVector<Eigen::Matrix<double, Eigen::Dynamic, 1, Eigen::AutoAlign, -1, 1>>();
    pygen::convertStdVector<std::vector<std::string>>();
    pygen::convertStdVector<std::vector<double>>();
    pygen::convertStdVector<std::vector<int>>();
    pygen::convertStdVector<std::vector<wbc::QuadraticProgram>>();
    pygen::convertStdVector<std::vector<wbc::TaskConfig>>();
    pygen::convertStdVector<std::vector<wbc::types::Contact>>();
    pygen::convertVector<Eigen::Matrix<double, 3, 1, Eigen::AutoAlign>>();
    pygen::convertVector<Eigen::Matrix<double, 6, 1, Eigen::AutoAlign>>();
    pygen::convertQuaternion<Eigen::Quaternion<double, Eigen::AutoAlign>>();

    py::class_<wbc::types::Pose>("Pose")
            .add_property("position",
                py::make_getter(&wbc::types::Pose::position, py::return_value_policy<py::copy_non_const_reference>()),
                py::make_setter(&wbc::types::Pose::position))
            .add_property("orientation",
                py::make_getter(&wbc::types::Pose::orientation, py::return_value_policy<py::copy_non_const_reference>()),
                py::make_setter(&wbc::types::Pose::orientation));

    py::class_<wbc::types::Twist>("Twist")
            .add_property("linear",
                py::make_getter(&wbc::types::Twist::linear,py::return_value_policy<py::copy_non_const_reference>()),
                py::make_setter(&wbc::types::Twist::linear))
            .add_property("angular",
                py::make_getter(&wbc::types::Twist::angular, py::return_value_policy<py::copy_non_const_reference>()),
                py::make_setter(&wbc::types::Twist::angular));

    py::class_<wbc::types::SpatialAcceleration>("SpatialAcceleration")
            .add_property("linear",
                py::make_getter(&wbc::types::SpatialAcceleration::linear,py::return_value_policy<py::copy_non_const_reference>()),
                py::make_setter(&wbc::types::SpatialAcceleration::linear))
            .add_property("angular",
                py::make_getter(&wbc::types::SpatialAcceleration::angular, py::return_value_policy<py::copy_non_const_reference>()),
                py::make_setter(&wbc::types::SpatialAcceleration::angular));

    py::class_<wbc::types::Wrench>("Wrench")
            .add_property("force",
                py::make_getter(&wbc::types::Wrench::force,py::return_value_policy<py::copy_non_const_reference>()),
                py::make_setter(&wbc::types::Wrench::force))
            .add_property("torque",
                py::make_getter(&wbc::types::Wrench::torque, py::return_value_policy<py::copy_non_const_reference>()),
                py::make_setter(&wbc::types::Wrench::torque));

    py::class_<wbc::types::RigidBodyState>("RigidBodyState")
            .add_property("pose",
                py::make_getter(&wbc::types::RigidBodyState::pose, py::return_value_policy<py::copy_non_const_reference>()),
                py::make_setter(&wbc::types::RigidBodyState::pose))
            .add_property("twist",
                py::make_getter(&wbc::types::RigidBodyState::twist, py::return_value_policy<py::copy_non_const_reference>()),
                py::make_setter(&wbc::types::RigidBodyState::twist))
            .add_property("acceleration",
                py::make_getter(&wbc::types::RigidBodyState::acceleration, py::return_value_policy<py::copy_non_const_reference>()),
                py::make_setter(&wbc::types::RigidBodyState::acceleration));

   py::class_<wbc::types::JointState>("JointState")
            .add_property("position",
                py::make_getter(&wbc::types::JointState::position, py::return_value_policy<py::copy_non_const_reference>()),
                py::make_setter(&wbc::types::JointState::position))
            .add_property("velocity",
                py::make_getter(&wbc::types::JointState::velocity, py::return_value_policy<py::copy_non_const_reference>()),
                py::make_setter(&wbc::types::JointState::velocity))
            .add_property("acceleration",
                py::make_getter(&wbc::types::JointState::acceleration, py::return_value_policy<py::copy_non_const_reference>()),
                py::make_setter(&wbc::types::JointState::acceleration));

   py::class_<wbc::types::JointCommand>("JointCommand")
            .add_property("position",
                py::make_getter(&wbc::types::JointCommand::position, py::return_value_policy<py::copy_non_const_reference>()),
                py::make_setter(&wbc::types::JointCommand::position))
            .add_property("velocity",
                py::make_getter(&wbc::types::JointCommand::velocity, py::return_value_policy<py::copy_non_const_reference>()),
                py::make_setter(&wbc::types::JointCommand::velocity))
            .add_property("acceleration",
                py::make_getter(&wbc::types::JointCommand::acceleration, py::return_value_policy<py::copy_non_const_reference>()),
                py::make_setter(&wbc::types::JointCommand::acceleration))
            .add_property("effort",
                py::make_getter(&wbc::types::JointCommand::effort, py::return_value_policy<py::copy_non_const_reference>()),
                py::make_setter(&wbc::types::JointCommand::effort));

   py::class_<wbc::types::Limits>("Limits")
            .add_property("position",
                py::make_getter(&wbc::types::Limits::position, py::return_value_policy<py::copy_non_const_reference>()),
                py::make_setter(&wbc::types::Limits::position))
            .add_property("velocity",
                py::make_getter(&wbc::types::Limits::velocity, py::return_value_policy<py::copy_non_const_reference>()),
                py::make_setter(&wbc::types::Limits::velocity))
            .add_property("acceleration",
                py::make_getter(&wbc::types::Limits::acceleration, py::return_value_policy<py::copy_non_const_reference>()),
                py::make_setter(&wbc::types::Limits::acceleration))
            .add_property("effort",
                py::make_getter(&wbc::types::Limits::effort, py::return_value_policy<py::copy_non_const_reference>()),
                py::make_setter(&wbc::types::Limits::effort));


   py::class_<wbc::types::JointLimits>("JointLimits")
            .add_property("max",
                py::make_getter(&wbc::types::JointLimits::max, py::return_value_policy<py::copy_non_const_reference>()),
                py::make_setter(&wbc::types::JointLimits::max))
            .add_property("min",
                py::make_getter(&wbc::types::JointLimits::min, py::return_value_policy<py::copy_non_const_reference>()),
                py::make_setter(&wbc::types::JointLimits::min));

   py::class_<wbc::types::Contact>("Contact")
            .def_readwrite("frame_id",  &wbc::types::Contact::frame_id)
            .def_readwrite("active",  &wbc::types::Contact::active)
            .def_readwrite("mu",  &wbc::types::Contact::mu)
            .def_readwrite("wx",  &wbc::types::Contact::wx)
            .def_readwrite("wy",  &wbc::types::Contact::wy);

   py::class_<wbc::RobotModelConfig>("RobotModelConfig")
            .def_readwrite("file_or_string",       &wbc::RobotModelConfig::file_or_string)
            .def_readwrite("submechanism_file",    &wbc::RobotModelConfig::submechanism_file)
            .def_readwrite("floating_base",        &wbc::RobotModelConfig::floating_base)
            .add_property("contact_points",
                py::make_getter(&wbc::RobotModelConfig::contact_points, py::return_value_policy<py::copy_non_const_reference>()),
                py::make_setter(&wbc::RobotModelConfig::contact_points));

   py::class_<wbc::TaskConfig>("TaskConfig")
            .def_readwrite("name",       &wbc::TaskConfig::name)
            .def_readwrite("priority",   &wbc::TaskConfig::priority)
            .add_property("weights",
                py::make_getter(&wbc::TaskConfig::weights, py::return_value_policy<py::copy_non_const_reference>()),
                py::make_setter(&wbc::TaskConfig::weights))
            .def_readwrite("activation", &wbc::TaskConfig::activation);

   py::class_<wbc::QuadraticProgram>("QuadraticProgram")
           .add_property("A",
               py::make_getter(&wbc::QuadraticProgram::A, py::return_value_policy<py::copy_non_const_reference>()),
               py::make_setter(&wbc::QuadraticProgram::A))
           .add_property("g",
               py::make_getter(&wbc::QuadraticProgram::g, py::return_value_policy<py::copy_non_const_reference>()),
               py::make_setter(&wbc::QuadraticProgram::g))
           .add_property("b",
               py::make_getter(&wbc::QuadraticProgram::b, py::return_value_policy<py::copy_non_const_reference>()),
               py::make_setter(&wbc::QuadraticProgram::b))
           .add_property("C",
               py::make_getter(&wbc::QuadraticProgram::C, py::return_value_policy<py::copy_non_const_reference>()),
               py::make_setter(&wbc::QuadraticProgram::C))
           .add_property("lower_x",
               py::make_getter(&wbc::QuadraticProgram::lower_x, py::return_value_policy<py::copy_non_const_reference>()),
               py::make_setter(&wbc::QuadraticProgram::lower_x))
           .add_property("upper_x",
               py::make_getter(&wbc::QuadraticProgram::upper_x, py::return_value_policy<py::copy_non_const_reference>()),
               py::make_setter(&wbc::QuadraticProgram::upper_x))
           .add_property("lower_y",
               py::make_getter(&wbc::QuadraticProgram::lower_y, py::return_value_policy<py::copy_non_const_reference>()),
               py::make_setter(&wbc::QuadraticProgram::lower_y))
           .add_property("upper_y",
               py::make_getter(&wbc::QuadraticProgram::upper_y, py::return_value_policy<py::copy_non_const_reference>()),
               py::make_setter(&wbc::QuadraticProgram::upper_y))
           .add_property("H",
               py::make_getter(&wbc::QuadraticProgram::H, py::return_value_policy<py::copy_non_const_reference>()),
               py::make_setter(&wbc::QuadraticProgram::H))
           .add_property("Wy",
               py::make_getter(&wbc::QuadraticProgram::Wy, py::return_value_policy<py::copy_non_const_reference>()),
               py::make_setter(&wbc::QuadraticProgram::Wy))
           .def_readwrite("neq",  &wbc::QuadraticProgram::neq)
           .def_readwrite("nin",  &wbc::QuadraticProgram::nin)
           .def_readwrite("nq",  &wbc::QuadraticProgram::nq)
           .def_readwrite("bounded",  &wbc::QuadraticProgram::bounded)
           .def("resize",  &wbc::QuadraticProgram::resize);

   py::class_<wbc::HierarchicalQP>("HierarchicalQP")
       .add_property("prios",
           py::make_getter(&wbc::HierarchicalQP::prios, py::return_value_policy<py::copy_non_const_reference>()),
           py::make_setter(&wbc::HierarchicalQP::prios))
       .add_property("Wq",
           py::make_getter(&wbc::HierarchicalQP::Wq, py::return_value_policy<py::copy_non_const_reference>()),
           py::make_setter(&wbc::HierarchicalQP::Wq))
       .def("resize",  &wbc::HierarchicalQP::resize);
}
