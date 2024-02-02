PYTHON_ADD_MODULE(acceleration_scene acceleration_scene.cpp)

pkg_search_module(wbc-scenes-acceleration REQUIRED IMPORTED_TARGET wbc-scenes-acceleration)
pkg_search_module(wbc-robot_models-rbdl REQUIRED IMPORTED_TARGET wbc-robot_models-rbdl)
pkg_search_module(wbc-solvers-qpoases REQUIRED IMPORTED_TARGET wbc-solvers-qpoases)

list(APPEND PKGCONFIG_REQUIRES wbc-scenes-acceleration)
list(APPEND PKGCONFIG_REQUIRES wbc-robot_models-rbdl)
list(APPEND PKGCONFIG_REQUIRES wbc-solvers-qpoases)
string (REPLACE ";" " " PKGCONFIG_REQUIRES "${PKGCONFIG_REQUIRES}")

# Set up the libraries and header search paths for this target
target_link_libraries(acceleration_scene PUBLIC
                      PkgConfig::wbc-robot_models-rbdl
                      PkgConfig::wbc-solvers-qpoases
                      Boost::python
                      Boost::numpy
                      PkgConfig::wbc-scenes-acceleration)

target_include_directories(acceleration_scene PUBLIC
	${PYTHON_INCLUDE_DIRS})

install(TARGETS acceleration_scene
        DESTINATION ${PYTHON_INSTALL_PATH}/wbc/scenes)
