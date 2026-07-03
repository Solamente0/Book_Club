add_library(common STATIC
    member.h
    member.cpp
    User.h
    User.cpp
    Book.h
    Book.cpp
    Review.h
    Review.cpp
    cart.h
    cart.cpp
)

target_include_directories(common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(common PUBLIC Qt6::Core)
