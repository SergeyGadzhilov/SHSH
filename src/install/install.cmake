install(TARGETS SHShare
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT "SHShare")

if(WIN32)
    set(INSTALL_SCRIPTS ${CMAKE_CURRENT_SOURCE_DIR}/install/win)
    find_program(WINDEPLOYQT windeployqt HINTS "${_qt_bin_dir}")
    configure_file("${INSTALL_SCRIPTS}/dependencies.cmake.in" "${INSTALL_SCRIPTS}/dependencies.cmake" @ONLY)
    set(CPACK_PRE_BUILD_SCRIPTS ${INSTALL_SCRIPTS}/dependencies.cmake)
endif()

set(CPACK_GENERATOR "IFW")
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "1")
set(CPACK_IFW_PACKAGE_NAME "SHShare")
set(CPACK_IFW_PACKAGE_TITLE "SHSHare")
set(CPACK_IFW_PACKAGE_WIZARD_STYLE "Modern")
set(CPACK_IFW_PACKAGE_WIZARD_SHOW_PAGE_LIST OFF)
set(CPACK_IFW_TARGET_DIRECTORY "@ApplicationsDir@/SHShare")
set(CPACK_IFW_PACKAGE_CONTROL_SCRIPT ${INSTALL_SCRIPTS}/controller.js)
set(CPACK_PACKAGE_DIRECTORY "${CMAKE_INSTALL_PREFIX}/pack")

include(CPACK)
include(CPackIFW)

cpack_add_component(SHShare REQUIRED)
cpack_ifw_configure_component(SHShare FORCED_INSTALLATION)
cpack_ifw_configure_component(SHShare SCRIPT ${INSTALL_SCRIPTS}/component.js)
