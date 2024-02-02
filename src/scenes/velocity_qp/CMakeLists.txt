PYTHON_ADD_MODULE(velocity_scene_qp velocity_scene_qp.cpp)

pkg_search_module(wbc-scenes-velocity_qp REQUIRED IMPORTED_TARGET wbc-scenes-velocity_qp)
pkg_search_module(wbc-robot_models-rbdl REQUIRED IMPORTED_TARGET wbc-robot_models-rbdl)
pkg_search_module(wbc-solvers-qpoases REQUIRED IMPORTED_TARGET wbc-solvers-qpoases)

# Set up the libraries and header search paths for this target
target_link_libraries(velocity_scene_qp PUBLIC
                      PkgConfig::wbc-scenes-velocity_qp
                      PkgConfig::wbc-robot_models-rbdl
                      PkgConfig::wbc-solvers-qpoases
                      Boost::python
                      Boost::numpy)

target_include_directories(velocity_scene_qp PUBLIC
	${PYTHON_INCLUDE_DIRS})

install(TARGETS velocity_scene_qp
        DESTINATION ${PYTHON_INSTALL_PATH}/wbc/scenes)
