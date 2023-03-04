find_program(DEPLOYQT macdeployqt HINTS "${_qt_bin_dir}")
set(INSTALL_SCRIPTS ${CMAKE_CURRENT_SOURCE_DIR}/install/mac)
set(CPACK_GENERATOR "DragNDrop")

configure_file("${INSTALL_SCRIPTS}/dependencies.cmake.in" "${INSTALL_SCRIPTS}/dependencies.cmake" @ONLY)
set(CPACK_PRE_BUILD_SCRIPTS ${INSTALL_SCRIPTS}/dependencies.cmake)
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "1")
set(CPACK_PACKAGE_DIRECTORY "${CMAKE_INSTALL_PREFIX}/pack")

include(CPACK)
