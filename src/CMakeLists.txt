find_package(Eigen3 3.3 REQUIRED NO_MODULE)

add_executable(ik "ik.cc")
target_link_libraries(ik PUBLIC Eigen3::Eigen)
