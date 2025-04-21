#ifndef WBC_PY_QPOASES_SOLVER_HPP
#define WBC_PY_QPOASES_SOLVER_HPP

#include <wbc/solvers/qpoases/QPOasesSolver.hpp>
#include <wbc/core/QuadraticProgram.hpp>

namespace wbc_py {
class QPOASESSolver : public wbc::QPOASESSolver{
public:
    QPOASESSolver() : wbc::QPOASESSolver(){
    }
    Eigen::VectorXd solve(wbc::HierarchicalQP hqp){
        Eigen::VectorXd solver_output;
        wbc::QPOASESSolver::solve(hqp, solver_output);
        return solver_output;
    }
};
}

#endif
