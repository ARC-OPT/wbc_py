#ifndef WBC_PY_HLS_SOLVER_HPP
#define WBC_PY_HLS_SOLVER_HPP

#include <wbc/solvers/hls/HierarchicalLSSolver.hpp>

namespace wbc_py {

class HierarchicalLSSolver : public wbc::HierarchicalLSSolver{
public:
    base::VectorXd solve(const wbc::HierarchicalQP &hqp);
};

}

#endif
