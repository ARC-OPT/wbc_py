#ifndef WBC_PY_ACCELERATION_SCENE_REDUCED_TSID_HPP
#define WBC_PY_ACCELERATION_SCENE_REDUCED_TSID_HPP

#include <wbc/scenes/acceleration_reduced_tsid/AccelerationSceneReducedTSID.hpp>
#include "../../solvers/qpoases/QPOasesSolver.hpp"
#include "../../robot_models/pinocchio/robot_model_pinocchio.hpp"

namespace wbc_py {

class AccelerationSceneReducedTSID : public wbc::AccelerationSceneReducedTSID{
public:
    AccelerationSceneReducedTSID(std::shared_ptr<wbc::RobotModelPinocchio> robot_model, std::shared_ptr<wbc::QPOASESSolver> solver, const double dt);
};

}

#endif
