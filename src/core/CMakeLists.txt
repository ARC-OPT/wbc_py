PYTHON_ADD_MODULE(core core.cpp)

pkg_search_module(wbc-core REQUIRED IMPORTED_TARGET wbc-core)

list(APPEND PKGCONFIG_REQUIRES wbc-core)
string (REPLACE ";" " " PKGCONFIG_REQUIRES "${PKGCONFIG_REQUIRES}")

# Set up the libraries and header search paths for this target
target_link_libraries(core PUBLIC
	${PYTHON_LIBRARIES}
	Boost::python
	Boost::numpy
        PkgConfig::wbc-core)

target_include_directories(core PUBLIC
	${PYTHON_INCLUDE_DIRS})

install(TARGETS core
        DESTINATION ${PYTHON_INSTALL_PATH}/wbc)
