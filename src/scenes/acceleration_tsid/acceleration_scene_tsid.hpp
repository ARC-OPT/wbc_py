#ifndef WBC_PY_ACCELERATION_SCENE_TSID_HPP
#define WBC_PY_ACCELERATION_SCENE_TSID_HPP

#include <wbc/scenes/acceleration_tsid/AccelerationSceneTSID.hpp>
#include "../../solvers/qpoases/QPOasesSolver.hpp"
#include <wbc/robot_models/pinocchio/RobotModelPinocchio.hpp>
#include <wbc/tasks/SpatialAccelerationTask.hpp>

namespace wbc_py {

class AccelerationSceneTSID : public wbc::AccelerationSceneTSID{
    std::vector<wbc::TaskPtr> new_tasks;
public:
    AccelerationSceneTSID(std::shared_ptr<wbc::RobotModelPinocchio> robot_model, std::shared_ptr<wbc_py::QPOASESSolver> solver, const double dt);
    void addSpatialAccelerationTask(wbc::SpatialAccelerationTaskPtr task){
        new_tasks.push_back(task);
    }
    bool configure(){
        return wbc::AccelerationSceneTSID::configure(new_tasks); 
    }
};

}

#endif
