cmake_minimum_required(VERSION 3.13)

project(add C)

#create unit list
set(UNIT "INT8" "INT16" "INT32" "INT64" "UINT8" "UINT16" "UINT32" "UINT64" "FLOAT" "DOUBLE")

#add option
# option(NODE_IN "Node input unit" "INT8")
# set(NODE_IN "INT8" CACHE STRING "Node input unit.")
# option(NODE_OUT "Node output unit" "INT8")
# set(NODE_OUT "INT8" CACHE STRING "Node output unit.")
# option(INPUT_COUNT "Input pipe count." "2")
# set(INPUT_COUNT "2" CACHE STRING "Input pipe count.")

#check input unit
list(FIND UNIT "${NODE_IN}" index)
if(index LESS 0 AND NODE_IN)
    message(FATAL_ERROR "NODE_IN is invalid.\nPlease select next list\n${UNIT}")
elseif(NOT NODE_IN)
    set(NODE_IN "INT8")
endif()

#check output unit
list(FIND UNIT "${NODE_OUT}" index)
if(index LESS 0 AND NODE_OUT)
    message(FATAL_ERROR "NODE_OUT is invalid.\nPlease select next list\n${UNIT}")
elseif(NOT NODE_OUT)
set(NODE_OUT "INT8")
endif()

message("${INPUT_COUNT}")

#check NODE
if(NOT "${INPUT_COUNT}" MATCHES [[(^[0-9]+$)]] AND INPUT_COUNT)
    message(FATAL_ERROR "INPUT_COUNT is invalid.\nPlease enter positive number")
elseif(NOT INPUT_COUNT)
    set(INPUT_COUNT "2")
endif()

#build message
message("build project begin")
message("Node input unit : ${NODE_IN}")
message("Node output unit : ${NODE_OUT}")
message("Node input pipes count : ${INPUT_COUNT}")

add_definitions(-DNODE_IN_INT8)
add_definitions(-DNODE_OUT_INT8)
add_definitions(-DINPUT_COUNT=2)

add_library(nodeSystem STATIC ../nodeSystem/nodeSystem.c)

add_executable(out src/main.c)

target_link_libraries(out nodeSystem)
target_include_directories(out PRIVATE ../nodeSystem)