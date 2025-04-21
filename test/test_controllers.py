from wbc.controllers import *
from wbc.core import *
import numpy as np
import nose

def test_cartesian_pos_pd_controller():
    ctrl = CartesianPosPDController()
    p_gain = [1]*6
    d_gain = [0.1]*6
    max_ctrl_out = [10]*6

    ctrl.setPGain(p_gain)
    ctrl.setDGain(d_gain)
    ctrl.setMaxCtrlOutput(max_ctrl_out)
    assert np.all(ctrl.pGain() == p_gain)
    assert np.all(ctrl.dGain() == d_gain)
    assert np.all(ctrl.maxCtrlOutput() == max_ctrl_out)

    ref_pose = Pose()
    ref_twist = Twist()
    ref_pose.position = [1,2,3]
    ref_pose.orientation = [0,0,0,1]
    ref_twist.linear = [0.1,0.1,0.1]
    ref_twist.angular = [0.1,0.1,0.1]

    act_pose = Pose()
    act_pose.position = [0,0,0]
    act_pose.orientation = [0,0,0,1]

    control_output = ctrl.updateVel(ref_pose, ref_twist, act_pose)
    assert np.all(control_output.linear == [1.1, 2.1, 3.1])
    assert np.all(control_output.angular == [0.1, 0.1, 0.1])

def test_joint_pos_pd_controller():
    joint_names = ["joint_1","joint_2","joint_3"]
    nj = len(joint_names)
    ctrl = JointPosPDController(len(joint_names))
    p_gain = [1]*nj
    d_gain = [0.1]*nj
    max_ctrl_out = [10]*nj

    ctrl.setPGain(p_gain)
    ctrl.setDGain(d_gain)
    ctrl.setMaxCtrlOutput(max_ctrl_out)
    assert np.all(ctrl.pGain() == p_gain)
    assert np.all(ctrl.dGain() == d_gain)
    assert np.all(ctrl.maxCtrlOutput() == max_ctrl_out)

    ref_pos = [1,1,1]
    ref_vel = [1,1,1]

    act_pos = [0,0,0]

    control_output = ctrl.updateVel(ref_pos, ref_vel, act_pos)

if __name__ == '__main__':
    nose.run()
