add_library(common STATIC
    member.h
    member.cpp
    Book.h
    Book.cpp
<<<<<<< HEAD
add_library(common STATIC
    member.h,member.cpp,Review.h,Review.cpp,Cart.h,Cart.cpp
=======
    Review.h
    Review.cpp
>>>>>>> 2831752f64c1d7032d45996a72bdbd38f051b522
)

target_include_directories(common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(common PUBLIC Qt6::Core)
