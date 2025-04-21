from wbc.core import *
from wbc.robot_models.robot_model_pinocchio import *
import numpy as np
import nose

def run(robot_model):
    joint_names = ["LLHip1", "LLHip2", "LLHip3", "LLKnee", "LLAnkleRoll", "LLAnklePitch"]
    root_link = "RH5_Root_Link"
    tip_link = "LLAnkle_FT"
    nj = len(joint_names)
    gravity_vector = [0,0,-9.81]
    a = Contact()
    a.mu = 0.6
    a.active = 1

    r=RobotModelConfig()
    r.file_or_string="../models/rh5/urdf/rh5_single_leg.urdf"
    r.floating_base = False
    assert robot_model.configure(r) == True

    qp = QuadraticProgram()
    qp.g = []
    floating_base_state = RigidBodyState()
    joint_state = JointState()
    print(joint_state.position)
    joint_state.position = np.array([0.1]*6)
    joint_state.velocity = np.array([0.1]*6)
    joint_state.acceleration = np.array([0.1]*6)
    robot_model.update(joint_state.position, joint_state.velocity, joint_state.acceleration,
                       floating_base_state.pose, floating_base_state.twist, floating_base_state.acceleration)

    robot_model.jointState() == joint_state
    pose = robot_model.pose(tip_link)
    twist = robot_model.twist(tip_link)
    acceleration = robot_model.acceleration(tip_link)
    space_jacobian = robot_model.spaceJacobian(tip_link)
    body_jacobian  = robot_model.bodyJacobian(tip_link)

    twist_new = np.array(space_jacobian).dot(joint_state.velocity)
    assert np.all(np.isclose(twist_new[0:3] - twist.linear, np.array([0]*3)))
    assert np.all(np.isclose(twist_new[3:6] - twist.angular, np.array([0]*3)))

    bias_acc = robot_model.spatialAccelerationBias(tip_link)
    accel = np.append(bias_acc.linear,bias_acc.angular) + space_jacobian.dot(joint_state.acceleration)
    assert np.all(np.isclose(accel[0:3] - acceleration.linear, np.array([0]*3)))
    assert np.all(np.isclose(accel[3:6] - acceleration.angular, np.array([0]*3)))

    inertia_mat = robot_model.jointSpaceInertiaMatrix()
    assert inertia_mat.shape[0] == nj
    assert inertia_mat.shape[1] == nj

    eff_bias = robot_model.biasForces()
    assert len(eff_bias) == nj

    assert robot_model.jointNames() == joint_names
    assert robot_model.actuatedJointNames() == joint_names
    assert robot_model.independentJointNames() == joint_names
    assert robot_model.jointIndex("LLHip2") == 1
    assert robot_model.baseFrame() == "RH5_Root_Link"

    joint_limits = robot_model.jointLimits()
    joint_limits.names = joint_names

    sel_mat = robot_model.selectionMatrix()
    assert np.all(sel_mat == np.eye(nj))

    assert robot_model.hasLink("LLAnkle_FT") == True
    assert robot_model.hasLink("LLAnkle_F") == False
    assert robot_model.hasJoint("LLAnkle_F") == False
    assert robot_model.hasJoint("LLKnee") == True
    assert robot_model.hasActuatedJoint("LLKnee") == True
    assert robot_model.hasActuatedJoint("LLKnee_F") == False

    cog = robot_model.centerOfMass()
    
    a = Contact()
    a.mu = 0.6
    a.active = 1
    a.frame_id = "contact_1"
    b = Contact()
    b.mu = 0.6
    b.active = 0
    b.frame_id = "contact_2"
    contacts = [a,b]

    robot_model.setContacts(contacts)
    robot_model.getContacts() == contacts

    assert robot_model.nj() == nj
    assert robot_model.na() == nj
    assert robot_model.nc() == 2
    assert robot_model.nac() == 1


def test_robot_model_pinocchio():
    run(RobotModelPinocchio())

if __name__ == '__main__':
    nose.run()
