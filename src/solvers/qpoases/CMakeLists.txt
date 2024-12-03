PYTHON_ADD_MODULE(qpoases_solver QPOasesSolver.cpp)

pkg_search_module(wbc-solvers-qpoases REQUIRED IMPORTED_TARGET wbc-solvers-qpoases)

# Set up the libraries and header search paths for this target
target_link_libraries(qpoases_solver PUBLIC
	${PYTHON_LIBRARIES}
	Boost::python
        Boost::numpy
        PkgConfig::wbc-solvers-qpoases)

target_include_directories(qpoases_solver PUBLIC
	${PYTHON_INCLUDE_DIRS})

install(TARGETS qpoases_solver
        DESTINATION ${PYTHON_INSTALL_PATH}/wbc/solvers)
