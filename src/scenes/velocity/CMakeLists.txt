PYTHON_ADD_MODULE(velocity_scene velocity_scene.cpp)

pkg_search_module(wbc-scenes-velocity REQUIRED IMPORTED_TARGET wbc-scenes-velocity)
pkg_search_module(wbc-robot_models-rbdl REQUIRED IMPORTED_TARGET wbc-robot_models-rbdl)
pkg_search_module(wbc-solvers-hls REQUIRED IMPORTED_TARGET wbc-solvers-hls)

# Set up the libraries and header search paths for this target
target_link_libraries(velocity_scene PUBLIC
                      PkgConfig::wbc-scenes-velocity
                      PkgConfig::wbc-robot_models-rbdl
                      PkgConfig::wbc-solvers-hls
                      Boost::python
                      Boost::numpy)

target_include_directories(velocity_scene PUBLIC
	${PYTHON_INCLUDE_DIRS})

install(TARGETS velocity_scene
        DESTINATION ${PYTHON_INSTALL_PATH}/wbc/scenes)
