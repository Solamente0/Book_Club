cmake_minimum_required(VERSION 3.16)
project(Book_Club)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Network Sql)

add_subdirectory(Common)
add_subdirectory(Server)
add_subdirectory(Client)

# ─────────────────────────────────────────────────────────────────────
# Packaging (CPack)
#
# `cpack` (or `cmake --build . --target package`) bundles Client and
# BookClubServer together with their Qt runtime dependencies into a single
# installer. On Windows this produces an NSIS-based Setup.exe with Start
# Menu shortcuts for both programs; each shortcut's working directory
# defaults to the installed executable's own folder, which is required
# since the server stores its SQLite database and uploaded files under a
# "data/" directory relative to its working directory.
# ─────────────────────────────────────────────────────────────────────
set(CPACK_PACKAGE_NAME "BookClub")
set(CPACK_PACKAGE_VENDOR "BookClub")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "BookClub reading platform (client + server)")
set(CPACK_PACKAGE_VERSION_MAJOR 1)
set(CPACK_PACKAGE_VERSION_MINOR 0)
set(CPACK_PACKAGE_VERSION_PATCH 0)
set(CPACK_PACKAGE_INSTALL_DIRECTORY "BookClub")

set(CPACK_PACKAGE_EXECUTABLES
    "Client"          "BookClub"
    "BookClubServer"  "BookClub Server"
)
set(CPACK_CREATE_DESKTOP_LINKS "Client")

if(WIN32)
    set(CPACK_GENERATOR "NSIS")
    set(CPACK_NSIS_PACKAGE_NAME "BookClub")
    set(CPACK_NSIS_DISPLAY_NAME "BookClub")
    set(CPACK_NSIS_MODIFY_PATH OFF)
    set(CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL ON)
elseif(APPLE)
    set(CPACK_GENERATOR "DragNDrop")
else()
    set(CPACK_GENERATOR "TGZ")
endif()

include(CPack)