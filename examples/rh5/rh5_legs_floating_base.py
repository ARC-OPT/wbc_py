from wbc.core import *
from wbc.robot_models.robot_model_pinocchio import RobotModelPinocchio
from wbc.scenes.acceleration_scene_tsid import AccelerationSceneTSID
from wbc.solvers.qpoases_solver import QPOASESSolver
from wbc.controllers import CartesianPosPDController
from wbc.tasks import SpatialAccelerationTask
import time
import numpy as np

# Configure robot model
floating_base_state = RigidBodyState()
floating_base_state.pose.position       = [-0.03, 0.0, 0.9]
floating_base_state.pose.orientation    = [0,0,0,1]
floating_base_state.twist.linear        = floating_base_state.twist.angular        = [0,0,0]
floating_base_state.acceleration.linear = floating_base_state.acceleration.angular = [0,0,0]

robot_model=RobotModelPinocchio()
r=RobotModelConfig()
r.file_or_string="../../models/rh5/urdf/rh5_legs.urdf"
r.floating_base = True
a = Contact()
a.mu = 0.6
a.active = 1
a.frame_id = "FL_SupportCenter"
b = Contact()
b.mu = 0.6
b.active = 1
b.frame_id = "FR_SupportCenter"
r.contact_points = [a,b]
if robot_model.configure(r) == False:
    print("Failed to configure robot model")
    exit(0)

# Create solver
solver = QPOASESSolver()
solver.setMaxNoWSR(100)

# Set up Tasks: Only a single, Cartesian positioning task
cfg = TaskConfig()
cfg.name = "zero_com_acceleration"
cfg.priority = 0
cfg.activation = 1
cfg.weights = [1]*6

# Configure WBC Scene
task = SpatialAccelerationTask(cfg, robot_model, "RH5_Root_Link", "world")
scene=AccelerationSceneTSID(robot_model, solver, 0.001)
scene.addSpatialAccelerationTask(task)
if scene.configure() == False:
    print("Failed to configure scene")
    exit(0)

# Configure Cartesian position controller
ctrl = CartesianPosPDController()
ctrl.setPGain([3]*6)
ctrl.setDGain([3]*6)

# Target Pose
setpoint = RigidBodyState()
setpoint.pose.position  = [-0.03, 0.0, 0.9]
setpoint.pose.orientation = [0,0,0,1]
setpoint.twist.linear = [0,0,0]
setpoint.twist.angular = [0,0,0]
setpoint.acceleration.linear = [0,0,0]
setpoint.acceleration.angular = [0,0,0]

# Actual pose
feedback = RigidBodyState()
feedback.pose.position  = [-0.0, 0.0, 0.0]
feedback.pose.orientation = [0,0,0,1]
feedback.twist.linear  = [0.0, 0.0, 0.0]
feedback.twist.angular = [0,0,0]

control_output = RigidBodyState()

# Initial joint state
joint_state = JointState()
joint_state.position  = [0,0,-0.2,0.4,0,-0.2,
                         0,0,-0.2,0.4,0,-0.2]
joint_state.velocity = [0]*12                          
joint_state.acceleration = [0]*12
robot_model.update(joint_state.position, joint_state.velocity, joint_state.acceleration,
                   floating_base_state.pose, floating_base_state.twist, floating_base_state.acceleration)

feedback.pose = robot_model.pose(task.tipFrame())
feedback.twist = robot_model.twist(task.tipFrame())
control_output = ctrl.updateAcc(setpoint.pose, setpoint.twist, setpoint.acceleration, 
                                feedback.pose, feedback.twist)

task.setReference(control_output)
qp = scene.update()
solver_output   = scene.solve(qp)
#wrenches_output = scene.getContactWrenches()

print("----- Solver output -----")
print("Names: " + str(robot_model.actuatedJointNames()))
print("Acc:   " + str([e for e in solver_output.acceleration]))
print("Tau:   " + str([e for e in solver_output.effort]))
# print("Contact Wrenches")
# for name,elem in zip(wrenches_output.names, wrenches_output.elements):
#     print(name + ": Force " + str(elem.force.transpose()) + ", Torque " + str(elem.torque.transpose()))
