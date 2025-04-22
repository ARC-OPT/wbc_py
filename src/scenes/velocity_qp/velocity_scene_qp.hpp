#ifndef WBC_PY_VELOCITY_SCENE_QP_HPP
#define WBC_PY_VELOCITY_SCENE_QP_HPP

#include <wbc/robot_models/pinocchio/RobotModelPinocchio.hpp>
#include <wbc/scenes/velocity_qp/VelocitySceneQP.hpp>
#include "../../solvers/qpoases/QPOasesSolver.hpp"
#include <wbc/tasks/SpatialVelocityTask.hpp>

namespace wbc_py {

class VelocitySceneQP : public wbc::VelocitySceneQP{
    std::vector<wbc::TaskPtr> new_tasks;
public:
    VelocitySceneQP(std::shared_ptr<wbc::RobotModelPinocchio> robot_model, std::shared_ptr<wbc_py::QPOASESSolver> solver, const double dt);
    void addSpatialVelocityTask(wbc::SpatialVelocityTaskPtr task){
        new_tasks.push_back(task);
    }
    bool configure(){
        return wbc::VelocitySceneQP::configure(new_tasks); 
    }
};

}

#endif
