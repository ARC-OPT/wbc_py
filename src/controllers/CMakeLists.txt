PYTHON_ADD_MODULE(controllers controllers.cpp)

pkg_search_module(wbc-core REQUIRED IMPORTED_TARGET wbc-core)
pkg_search_module(wbc-controllers REQUIRED IMPORTED_TARGET wbc-controllers)

list(APPEND PKGCONFIG_REQUIRES wbc-core)
list(APPEND PKGCONFIG_REQUIRES wbc-controllers)
string (REPLACE ";" " " PKGCONFIG_REQUIRES "${PKGCONFIG_REQUIRES}")

# Set up the libraries and header search paths for this target
target_link_libraries(controllers PUBLIC
	${PYTHON_LIBRARIES}
	Boost::python
	Boost::numpy
        PkgConfig::wbc-core
        PkgConfig::wbc-controllers)

target_include_directories(controllers PUBLIC
	${PYTHON_INCLUDE_DIRS})

install(TARGETS controllers
        DESTINATION ${PYTHON_INSTALL_PATH}/wbc)
