cmake_minimum_required (VERSION 2.8)
add_compile_options(-Wall -g -lstdc++ )
if(CMAKE_COMPILER_IS_GNUCXX)
	add_compile_options(-std=c++11)
endif(CMAKE_COMPILER_IS_GNUCXX)
project(libcell)
include_directories(${PROJECT_SOURCE_DIR}/include  D:/Eigen/Eigen)
link_directories(${PROJECT_SOURCE_DIR}/lib )
#target_link_directories(libcell )
link_libraries(m glfw3 opengl32)

aux_source_directory(${PROJECT_SOURCE_DIR}/src DIR_SRCS)
add_executable(libcell ${DIR_SRCS})
#target_link_libraries(libcell,${EXTRA_LIB})
