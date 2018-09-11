
INCLUDE_DIRECTORIES(${PS4_SOURCE_DIR}/lib)

LINK_DIRECTORIES(${PS4_BINARY_DIR}/lib)

ADD_LIBRARY(image image.h image.cpp lodepng.h lodepng.cpp)
set_property(TARGET image PROPERTY CXX_STANDARD 11)

