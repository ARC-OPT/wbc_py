PYTHON_ADD_MODULE(robot_model_rbdl robot_model_rbdl.cpp)

pkg_search_module(wbc-robot_models-rbdl REQUIRED IMPORTED_TARGET wbc-robot_models-rbdl)
pkg_search_module(wbc-core REQUIRED IMPORTED_TARGET wbc-core)

list(APPEND PKGCONFIG_REQUIRES wbc-robot_models-rbdl)
list(APPEND PKGCONFIG_REQUIRES wbc-core)
string (REPLACE ";" " " PKGCONFIG_REQUIRES "${PKGCONFIG_REQUIRES}")

# Set up the libraries and header search paths for this target
target_link_libraries(robot_model_rbdl PUBLIC
	${PYTHON_LIBRARIES}
	Boost::python
	Boost::numpy
        PkgConfig::wbc-robot_models-rbdl
        PkgConfig::wbc-core)

target_include_directories(robot_model_rbdl PUBLIC
	${PYTHON_INCLUDE_DIRS})

install(TARGETS robot_model_rbdl
        DESTINATION ${PYTHON_INSTALL_PATH}/wbc/robot_models)
