#ifndef WBC_PY_CONTROLLERS_HPP
#define WBC_PY_CONTROLLERS_HPP

#include "../eigen_conversion.h"
#include "../std_vector_conversion.h"
#include <wbc/controllers/CartesianPosPDController.hpp>
#include <wbc/controllers/JointPosPDController.hpp>

namespace wbc_py {

class CartesianPosPDController : public wbc::CartesianPosPDController{
public:
    wbc::types::Twist updateVel(wbc::types::Pose ref_pose,
                                wbc::types::Twist ref_twist,
                                wbc::types::Pose pose){
        return wbc::CartesianPosPDController::update(ref_pose, ref_twist, pose);
    }
    wbc::types::SpatialAcceleration updateAcc(wbc::types::Pose ref_pose,
                                              wbc::types::Twist ref_twist,
                                              wbc::types::SpatialAcceleration ref_acc,
                                              wbc::types::Pose pose,
                                              wbc::types::Twist twist){
        return wbc::CartesianPosPDController::update(ref_pose, ref_twist, ref_acc, pose, twist);
    }
};

class JointPosPDController : public wbc::JointPosPDController{
public:
    JointPosPDController(uint dim) : wbc::JointPosPDController(dim){
        
    }
    Eigen::VectorXd updateVel(const Eigen::VectorXd& ref_pos,
                              const Eigen::VectorXd& ref_vel,
                              const Eigen::VectorXd& pos){
        return wbc::JointPosPDController::update(ref_pos, ref_vel, pos);
    }
    Eigen::VectorXd updateAcc(const Eigen::VectorXd& ref_pos,
                              const Eigen::VectorXd& ref_vel,
                              const Eigen::VectorXd& ref_acc,
                              const Eigen::VectorXd& pos,
                              const Eigen::VectorXd& vel){
        return wbc::JointPosPDController::update(ref_pos, ref_vel, ref_acc, pos, vel);
    }
};

}

#endif
