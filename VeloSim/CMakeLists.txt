# CMakeList.txt : CMake project for VeloSim, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (VeloSim "VeloSim.cpp" "VeloSim.h" "utils/utils.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET VeloSim PROPERTY CXX_STANDARD 20)
endif()

#todo var pour path
add_subdirectory(C:\\Users\\blanc\\SimpleBLE-main\\simpleble ${CMAKE_BINARY_DIR}/simpleble)
target_link_libraries(VeloSim simpleble::simpleble)