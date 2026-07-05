add_library(common STATIC
    Member.h
    Member.cpp
    User.h
    User.cpp
    Publisher.h
    Publisher.cpp
    Admin.h
    Admin.cpp
    Book.h
    Book.cpp
    Review.h
    Review.cpp
    Cart.h
    Cart.cpp
    Shelf.h
    Shelf.cpp
    Notification.h
    Notification.cpp
)

target_include_directories(common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(common PUBLIC Qt6::Core)
