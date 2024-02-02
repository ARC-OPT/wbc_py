#ifndef WBC_PY_ACCELERATION_SCENE_REDUCED_TSID_HPP
#define WBC_PY_ACCELERATION_SCENE_REDUCED_TSID_HPP

#include <wbc/scenes/acceleration_reduced_tsid/AccelerationSceneReducedTSID.hpp>
#include "../../solvers/qpoases/QPOasesSolver.hpp"
#include "../../robot_models/rbdl/robot_model_rbdl.hpp"

namespace wbc_py {

wbc::JointWeights toJointWeights(const base::NamedVector<double> &weights);

class AccelerationSceneReducedTSID : public wbc::AccelerationSceneReducedTSID{
public:
    AccelerationSceneReducedTSID(std::shared_ptr<RobotModelRBDL> robot_model, std::shared_ptr<QPOASESSolver> solver, const double dt);
    void setJointReference(const std::string& task_name, const base::NamedVector<base::JointState>& ref);
    void setCartReference(const std::string& task_name, const base::samples::RigidBodyStateSE3& ref);
    void setJointWeights(const base::NamedVector<double> &weights);
    base::NamedVector<double> getJointWeights2();
    base::NamedVector<double> getActuatedJointWeights2();
    base::NamedVector<base::JointState> solve2(const wbc::HierarchicalQP &hqp);
    base::NamedVector<wbc::TaskStatus> updateTasksStatus2();
};

}

#endif
