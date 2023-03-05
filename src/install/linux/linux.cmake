install(FILES install/linux/SHShare.desktop DESTINATION share/applications)
install(FILES install/linux/shshare.svg DESTINATION share/icons/hicolor/scalable/apps)

set(CPACK_GENERATOR "DEB")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "SHShare")

set(CPACK_DEBIAN_PACKAGE_DESCRIPTION "SHShare")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "gadzhilov.sergey@gmail.com")
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

include(CPack)
