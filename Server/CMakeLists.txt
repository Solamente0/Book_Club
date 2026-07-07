add_executable(BookClubServer
    Database.h
    Database.cpp
    main.cpp
)

target_link_libraries(BookClubServer PRIVATE
    common
    Qt6::Core
    Qt6::Network
    Qt6::Sql
)