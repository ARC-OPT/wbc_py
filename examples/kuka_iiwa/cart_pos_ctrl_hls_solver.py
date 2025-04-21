from wbc.core import *
from wbc.robot_models.robot_model_pinocchio import RobotModelPinocchio
from wbc.scenes.velocity_scene_qp import VelocitySceneQP
from wbc.solvers.qpoases_solver import QPOASESSolver
from wbc.controllers import CartesianPosPDController
from wbc.tasks import SpatialVelocityTask
import time
import numpy as np

# Configure robot model
robot_model=RobotModelPinocchio()
r=RobotModelConfig()
r.file_or_string="../../models/kuka/urdf/kuka_iiwa.urdf"
if robot_model.configure(r) == False:
    print("Failed to configure robot model  ")
    exit(0)
    
# Initial joint state
position = np.array([0.0]*7)
velocity = np.array([0.0]*7)
acceleration = np.array([0.0]*7)
floating_base_state = RigidBodyState()
robot_model.update(position, velocity, acceleration, 
                   floating_base_state.pose, floating_base_state.twist, floating_base_state.acceleration) 
                   
# Create solver
solver = QPOASESSolver()

# Set up Tasks: Only a single, Cartesian positioning task
cfg = TaskConfig()
cfg.name = "tcp_pose"
cfg.priority = 0
cfg.activation = 1
cfg.weights = [1]*6


# Configure WBC Scene
task = SpatialVelocityTask(cfg, robot_model, "kuka_lbr_l_tcp", "kuka_lbr_l_link_0")
scene=VelocitySceneQP(robot_model, solver, 0.001)
scene.addSpatialVelocityTask(task)
if scene.configure() == False:
    print("Failed to configure scene")
    exit(0)

# Configure Cartesian position controller
ctrl = CartesianPosPDController()
ctrl.setPGain([3]*6)

# Target Pose
setpoint_pose = Pose()
setpoint_twist = Twist()
setpoint_pose.position  = [0.0,0.0,0.95]
setpoint_pose.orientation = [0,0,0,1]
setpoint_twist.linear = [0,0,0]
setpoint_twist.angular = [0,0,0]

# Actual pose
feedback = Pose()
feedback.position = [0,0,0]
feedback.orientation = [0,0,0,1]
control_output = Twist()

start = time.time()
# Control Loop
sample_time = 0.01
while np.linalg.norm(setpoint_pose.position-feedback.position) > 1e-4:
    
    robot_model.update(position, velocity, acceleration,
                       floating_base_state.pose, floating_base_state.twist, floating_base_state.acceleration)
    control_output = ctrl.updateVel(setpoint_pose, setpoint_twist, feedback)
    feedback = robot_model.pose("kuka_lbr_l_tcp")

    task.setReference(control_output)
    qp = scene.update()
    solver_output = scene.solve(qp)
        
    for i in range(robot_model.nj()):
        position[i] = position[i] + solver_output.velocity[i] * sample_time
        
    print(solver_output.velocity)
    print("Time: [" + str(time.time()-start) + " sec]")
    print("Ref. Pos:  %.4f %.4f %.4f"  % (setpoint_pose.position[0],setpoint_pose.position[1],setpoint_pose.position[2]))
    print("Act. Pos:  %.4f %.4f %.4f"  % (feedback.position[0],feedback.position[1],feedback.position[2]))
    print("Ctrl. Out: %.4f %.4f %.4f"  % (control_output.linear[0],control_output.linear[1],control_output.linear[2]))
    print("-------------------------------------------")
    time.sleep(sample_time)
