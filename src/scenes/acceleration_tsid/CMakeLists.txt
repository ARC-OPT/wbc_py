PYTHON_ADD_MODULE(acceleration_scene_tsid acceleration_scene_tsid.cpp)

pkg_search_module(wbc-scenes-acceleration_tsid REQUIRED IMPORTED_TARGET wbc-scenes-acceleration_tsid)
pkg_search_module(wbc-robot_models-rbdl REQUIRED IMPORTED_TARGET wbc-robot_models-rbdl)
pkg_search_module(wbc-solvers-qpoases REQUIRED IMPORTED_TARGET wbc-solvers-qpoases)

# Set up the libraries and header search paths for this target
target_link_libraries(acceleration_scene_tsid PUBLIC
                      PkgConfig::wbc-scenes-acceleration_tsid
                      PkgConfig::wbc-robot_models-rbdl
                      PkgConfig::wbc-solvers-qpoases
                      Boost::python
                      Boost::numpy)

target_include_directories(acceleration_scene_tsid PUBLIC
	${PYTHON_INCLUDE_DIRS})

install(TARGETS acceleration_scene_tsid
        DESTINATION ${PYTHON_INSTALL_PATH}/wbc/scenes)
