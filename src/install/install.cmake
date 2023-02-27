install(TARGETS SHShare
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

include(InstallRequiredSystemLibraries)
if(WIN32)
    find_program(WINDEPLOYQT windeployqt HINTS "${_qt_bin_dir}")
    set(CPACK_PRE_BUILD_SCRIPTS ${CMAKE_CURRENT_SOURCE_DIR}/install/win/dependencies.cmake)
endif()

set(CPACK_GENERATOR "IFW")
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "1")
set(CPACK_PACKAGE_DIRECTORY "${CMAKE_INSTALL_PREFIX}/pack")

include(CPACK)
include(CPackIFW)
