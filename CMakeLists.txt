cmake_minimum_required(VERSION 3.5)
project(P4 CXX)

# require a C++11 compiler for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# build the image library
ADD_SUBDIRECTORY(lib)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/lib)

# build the compare program
ADD_EXECUTABLE(compare compare.cpp)
TARGET_LINK_LIBRARIES(compare image)

set(DEQUE_SOURCE
  deque.hpp deque.tpp)

set(TEST_SOURCE
  test_deque.cpp)

set(PATHFINDER_SOURCE pathfinder.cpp)

set(SOURCE ${DEQUE_SOURCE} ${TEST_SOURCE} ${PATHFINDER_SOURCE})

# create unittests
add_executable(student-tests catch.hpp abstract_deque.hpp ${DEQUE_SOURCE} ${TEST_SOURCE})
TARGET_LINK_LIBRARIES(student-tests)

# build executable
add_executable(pathfinder abstract_deque.hpp ${DEQUE_SOURCE} ${PATHFINDER_SOURCE})
TARGET_LINK_LIBRARIES(pathfinder image)

# some simple tests
enable_testing()
add_test(student-tests student-tests)
add_test(test00 pathfinder ${CMAKE_SOURCE_DIR}/tests/maze00.png output00.png)
add_test(test00-compare compare ${CMAKE_SOURCE_DIR}/tests/output00.png output00.png)
add_test(test01 pathfinder ${CMAKE_SOURCE_DIR}/tests/maze01.png output01.png)
add_test(test01-compare compare ${CMAKE_SOURCE_DIR}/tests/output01.png output01.png)
add_test(test02 pathfinder ${CMAKE_SOURCE_DIR}/tests/maze02.png output02.png)
add_test(test02-compare compare ${CMAKE_SOURCE_DIR}/tests/output02.png output02.png)

add_custom_target(submission COMMAND
  ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/submission.zip" --format=zip
  ${SOURCE}
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
