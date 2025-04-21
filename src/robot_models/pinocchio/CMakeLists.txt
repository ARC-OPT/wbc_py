PYTHON_ADD_MODULE(robot_model_pinocchio robot_model_pinocchio.cpp)

pkg_search_module(wbc-robot_models-pinocchio REQUIRED IMPORTED_TARGET wbc-robot_models-pinocchio)
pkg_search_module(wbc-core REQUIRED IMPORTED_TARGET wbc-core)

list(APPEND PKGCONFIG_REQUIRES wbc-robot_models-pinocchio)
list(APPEND PKGCONFIG_REQUIRES wbc-core)
string (REPLACE ";" " " PKGCONFIG_REQUIRES "${PKGCONFIG_REQUIRES}")

# Set up the libraries and header search paths for this target
target_link_libraries(robot_model_pinocchio PUBLIC
	${PYTHON_LIBRARIES}
	Boost::python
	Boost::numpy
        PkgConfig::wbc-robot_models-pinocchio
        PkgConfig::wbc-core)

target_include_directories(robot_model_pinocchio PUBLIC
	${PYTHON_INCLUDE_DIRS})

install(TARGETS robot_model_pinocchio
        DESTINATION ${PYTHON_INSTALL_PATH}/wbc/robot_models)
