from wbc.robot_models.robot_model_pinocchio import *
from wbc.scenes.velocity_scene_qp import *
from wbc.scenes.acceleration_scene_tsid import *
from wbc.scenes.acceleration_scene_reduced_tsid import *
from wbc.core import *
from wbc.solvers.qpoases_solver import *
from wbc.tasks import *
import numpy as np
import nose
#from IPython import embed

def configure_wbc(scene):
    
    assert scene.configure(constraint_config) == True

def run_velocity_wbc(scene, robot_model):
    cfg = TaskConfig()
    cfg.name = "tcp_pose"
    cfg.priority = 0
    cfg.activation = 1
    cfg.weights = [1]*6
    constraint_config = [cfg]
    
    task = SpatialVelocityTask(cfg, robot_model, "kuka_lbr_l_tcp", "kuka_lbr_l_link_0")
    scene.addSpatialVelocityTask(task)
    scene.configure() == True

    ref = Twist()
    ref.linear  = [0.0,0.0,0.1]
    ref.angular = [0.0,0.0,0.0]
    task.setReference(ref)
    hqp = scene.update()
    solver_output = scene.solve(hqp)
    
    # Verify solver output
    J = robot_model.spaceJacobian("kuka_lbr_l_tcp")
    y_solution = J.dot(solver_output.velocity)
    xd = J.dot(solver_output.velocity)
    assert np.all(np.isclose(xd[0:3] - ref.linear,np.zeros(3),atol=1e-6))
    assert np.all(np.isclose(xd[3:6] - ref.angular,np.zeros(3),atol=1e-6))

    # Test Joint Weights
    robot_model.setJointWeights([1,1,1,0,1,1,1])
    hqp = scene.update()
    solver_output = scene.solve(hqp)
    assert np.all(solver_output.velocity[3] == 0)
    assert np.all(hqp.Wq[3] == 0)

    # Test Task Weights
    task.setWeights([1,1,0,1,1,1])
    hqp = scene.update()
    solver_output = scene.solve(hqp)
    xd = J.dot(solver_output.velocity)
    assert np.isclose(xd[2],0)

def run_acceleration_wbc(scene, robot_model):

    cfg = TaskConfig()
    cfg.name = "tcp_pose"
    cfg.priority = 0
    cfg.activation = 1
    cfg.weights = [1]*6
    constraint_config = [cfg]
    
    task = SpatialAccelerationTask(cfg, robot_model, "kuka_lbr_l_tcp", "kuka_lbr_l_link_0")
    scene.addSpatialAccelerationTask(task)
    scene.configure() == True
    
    ref = SpatialAcceleration()
    ref.linear  = [0.0,0.0,0.0]
    ref.angular = [0.0,-0.3,0.0]
    task.setReference(ref)
    hqp = scene.update()
    solver_output = scene.solve(hqp)
    
    qd  = solver_output.velocity
    qdd  = solver_output.acceleration
    J = robot_model.spaceJacobian("kuka_lbr_l_tcp")
    acc_bias = np.array([0]*6)
    acc_bias[0:3] = robot_model.spatialAccelerationBias("kuka_lbr_l_tcp").linear
    acc_bias[3:6] = robot_model.spatialAccelerationBias("kuka_lbr_l_tcp").angular
    xdd = J.dot(qdd) + acc_bias
    assert np.all(np.isclose(xdd[0:3] - ref.linear,np.zeros(3),atol=1e-1))
    assert np.all(np.isclose(xdd[3:6] - ref.angular,np.zeros(3),atol=1e-1))

    # Test Joint Weights
    robot_model.setJointWeights([1,1,1,0,1,1,1])
    hqp = scene.update()
    solver_output = scene.solve(hqp)
    assert np.all(np.isclose(solver_output.acceleration[3],0))
    assert np.all(hqp.Wq[3] == 0)

    # Test Task Weights
    task.setWeights([1,1,0,1,1,1])
    hqp = scene.update()
    solver_output = scene.solve(hqp)

    qd  = solver_output.velocity
    qdd = solver_output.acceleration
    xdd = J.dot(qdd) + acc_bias
    assert np.isclose(xdd[2],0,atol=1e-1)

def test_configure():
    robot_model=RobotModelPinocchio()
    r=RobotModelConfig()
    r.file_or_string="../models/kuka/urdf/kuka_iiwa.urdf"
    r.actuated_joint_names = ["kuka_lbr_l_joint_1", "kuka_lbr_l_joint_2", "kuka_lbr_l_joint_3", "kuka_lbr_l_joint_4", "kuka_lbr_l_joint_5", "kuka_lbr_l_joint_6", "kuka_lbr_l_joint_7"]
    r.joint_names = r.actuated_joint_names
    assert robot_model.configure(r) == True

    qp_solver = QPOASESSolver()

    joint_state = JointState()
    joint_state.position = [0.1]*robot_model.nj()
    joint_state.velocity = [0.0]*robot_model.nj()
    joint_state.acceleration = [0.0]*robot_model.nj()
    robot_model.update(joint_state.position, joint_state.velocity, joint_state.acceleration,
                       Pose(), Twist(), SpatialAcceleration())

    cfg = TaskConfig()
    cfg.name = "tcp_pose"
    cfg.priority = 0
    cfg.activation = 1
    cfg.weights = [1]*6
    constraint_config = [cfg]
    
    task = SpatialVelocityTask(cfg, robot_model, "kuka_lbr_l_tcp", "kuka_lbr_l_link_0")
    scene = VelocitySceneQP(robot_model, qp_solver, 0.001)
    scene.addSpatialVelocityTask(task)
    assert scene.configure() == True

    task = SpatialAccelerationTask(cfg, robot_model, "kuka_lbr_l_tcp", "kuka_lbr_l_link_0")
    scene = AccelerationSceneTSID(robot_model, qp_solver, 0.001)
    scene.addSpatialAccelerationTask(task)
    assert scene.configure() == True

    task = SpatialAccelerationTask(cfg, robot_model, "kuka_lbr_l_tcp", "kuka_lbr_l_link_0")
    scene = AccelerationSceneReducedTSID(robot_model, qp_solver, 0.001)
    scene.addSpatialAccelerationTask(task)
    assert scene.configure() == True

def test_solver_output():
    robot_model=RobotModelPinocchio()
    r=RobotModelConfig()
    r.file_or_string="../models/kuka/urdf/kuka_iiwa.urdf"
    r.actuated_joint_names = ["kuka_lbr_l_joint_1", "kuka_lbr_l_joint_2", "kuka_lbr_l_joint_3", "kuka_lbr_l_joint_4", "kuka_lbr_l_joint_5", "kuka_lbr_l_joint_6", "kuka_lbr_l_joint_7"]
    r.joint_names = r.actuated_joint_names
    assert robot_model.configure(r) == True

    qp_solver = QPOASESSolver()

    joint_state = JointState()
    joint_state.position = [1.0]*robot_model.nj() 
    joint_state.velocity = [0.0]*robot_model.nj() 
    joint_state.acceleration = [0.0]*robot_model.nj()
    robot_model.update(joint_state.position, joint_state.velocity, joint_state.acceleration,
                       Pose(), Twist(), SpatialAcceleration())

    run_velocity_wbc(VelocitySceneQP(robot_model, qp_solver, 0.001), robot_model)
    run_acceleration_wbc(AccelerationSceneReducedTSID(robot_model, qp_solver, 0.001), robot_model)
    run_acceleration_wbc(AccelerationSceneReducedTSID(robot_model, qp_solver, 0.001), robot_model)


if __name__ == '__main__':
    nose.run()
