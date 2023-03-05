install(TARGETS SHShare
    BUNDLE DESTINATION . COMPONENT "SHShare"
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT "SHShare")

if(WIN32)
    include(install/win/win.cmake)
endif()

if(APPLE)
    include(install/mac/mac.cmake)
endif()

if(UNIX AND NOT APPLE)
   include(install/linux/linux.cmake)
endif()
