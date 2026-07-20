cmake_minimum_required(VERSION 3.19)
project(Client LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_resources(RESOURCES
    resources.qrc
)

qt_add_executable(Client
    WIN32
    MACOSX_BUNDLE

    login.cpp
    login.h

    main.cpp

    ${RESOURCES}
    login.ui
    home.cpp
    home.h
    mainwindow.h
    mainwindow.cpp
    register.h
    register.cpp

    ../Common/models/Book.h
    ../Common/models/Book.cpp

    ../Common/models/Review.h
    ../Common/models/Review.cpp
    bookdetailwindow.h
    bookdetailwindow.cpp
    
    ../Common/models/Cart.cpp
    ../Common/models/Cart.h

    cartwidget.h
    cartwidget.cpp
    
    ../Common/users/User.h
    ../Common/users/User.cpp
      ../Common/users/Member.h
    ../Common/users/Member.cpp
    usermanager.h
    usermanager.cpp



      ../Common/models/Shelf.h
    ../Common/models/Shelf.cpp
    ../Common/models/Notification.h
    ../Common/models/Notification.cpp
    genreselectionwidget.h
    genreselectionwidget.cpp
    forgotpasswordwidget.h
    forgotpasswordwidget.cpp
    profilewidget.h
    profilewidget.cpp
    personallibrarywidget.h
    personallibrarywidget.cpp
    publishermanager.h
    publishermanager.cpp



)
target_link_libraries(Client
    PRIVATE
        Qt::Core
        Qt::Widgets
)
target_include_directories(Client PRIVATE
    ../Common/models
    ../Common/users
)

install(TARGETS Client
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET Client
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)

install(SCRIPT ${deploy_script})