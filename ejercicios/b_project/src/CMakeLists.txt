add_library(atom atom.cpp)

add_executable(main.x main.cpp)

target_link_libraries(main.x atom)
