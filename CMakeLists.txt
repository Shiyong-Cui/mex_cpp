cmake_minimum_required(VERSION 3.5)
project(matlab_tutorial)

find_package(Matlab REQUIRED)

if(MATLAB_FOUND)
    message(STATUS "matlab is found")
    message(STATUS "Matlab_VERSION = ${Matlab_VERSION}")
    message(STATUS "Matlab_ROOT_DIR = ${Matlab_ROOT_DIR}")
    message(STATUS "Matlab_MAIN_PROGRAM = ${Matlab_MAIN_PROGRAM}")
    message(STATUS "Matlab_INCLUDE_DIRS = ${Matlab_INCLUDE_DIRS}")
    message(STATUS "Matlab_MEX_LIBRARY = ${Matlab_MEX_LIBRARY}")
    message(STATUS "Matlab_MX_LIBRARY = ${Matlab_MX_LIBRARY}")
    message(STATUS "Matlab_ENG_LIBRARY = ${Matlab_ENG_LIBRARY}")
    message(STATUS "Matlab_MAT_LIBRARY = ${Matlab_MAT_LIBRARY}")
    message(STATUS "Matlab_ENGINE_LIBRARY = ${Matlab_ENGINE_LIBRARY}")
    message(STATUS "Matlab_DATAARRAY_LIBRARY = ${Matlab_DATAARRAY_LIBRARY}")
    message(STATUS "Matlab_LIBRARIES = ${Matlab_LIBRARIES}")
    message(STATUS "Matlab_MEX_COMPILER = ${Matlab_MEX_COMPILER}")
    message(STATUS "Matlab_MCC_COMPILER = ${Matlab_MCC_COMPILER}")
else(MATLAB_FOUND)
    message(STATUS "matlab is NOT found")
endif(MATLAB_FOUND)

matlab_add_mex(NAME mex_test SHARED
SRC
    src/mex_test.cpp
    src/Matlabdef.def
LINK_TO
    ${Matlab_LIBRARIES}
)
target_include_directories(mex_test PRIVATE include)

# copy the mex function to a specific folder
install(TARGETS mex_test DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/test)
