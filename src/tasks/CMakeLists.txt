PYTHON_ADD_MODULE(tasks tasks.cpp)

pkg_search_module(wbc-tasks REQUIRED IMPORTED_TARGET wbc-tasks)
pkg_search_module(wbc-robot_models-pinocchio REQUIRED IMPORTED_TARGET wbc-robot_models-pinocchio)

list(APPEND PKGCONFIG_REQUIRES wbc-tasks)
string (REPLACE ";" " " PKGCONFIG_REQUIRES "${PKGCONFIG_REQUIRES}")

# Set up the libraries and header search paths for this target
target_link_libraries(tasks PUBLIC
	${PYTHON_LIBRARIES}
	Boost::python
	Boost::numpy
    PkgConfig::wbc-tasks
    PkgConfig::wbc-robot_models-pinocchio)

target_include_directories(tasks PUBLIC
	${PYTHON_INCLUDE_DIRS})

install(TARGETS tasks
        DESTINATION ${PYTHON_INSTALL_PATH}/wbc)
