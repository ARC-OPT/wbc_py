PYTHON_ADD_MODULE(hls_solver HierarchicalLSSolver.cpp)

find_package (Eigen3 3.3 REQUIRED NO_MODULE)

pkg_search_module(wbc-solvers-hls REQUIRED IMPORTED_TARGET wbc-solvers-hls)
pkg_search_module(eigen3 REQUIRED IMPORTED_TARGET eigen3)

list(APPEND PKGCONFIG_REQUIRES wbc-solvers-hls)
list(APPEND PKGCONFIG_REQUIRES eigen3)
string (REPLACE ";" " " PKGCONFIG_REQUIRES "${PKGCONFIG_REQUIRES}")

# Set up the libraries and header search paths for this target
target_link_libraries(hls_solver PUBLIC
	${PYTHON_LIBRARIES}
	Boost::python
	Boost::numpy
        PkgConfig::wbc-solvers-hls
        Eigen3::Eigen)

target_include_directories(hls_solver PUBLIC
	${PYTHON_INCLUDE_DIRS})

install(TARGETS hls_solver
        DESTINATION ${PYTHON_INSTALL_PATH}/wbc/solvers)
