#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "image.h"

template class Image<int>;

typedef Image<int> ImageType;

TEST_CASE( "Image of ints test", "[Image]" ) {

  ImageType im(100,200);
    
  REQUIRE( im.width() == 100 );
  REQUIRE( im.height() == 200 );

  for(int i = 0; i < 100; ++i)
    for(int j = 0; j < 200; ++j){
      im(i,j) = 0;
    }
  
}

TEST_CASE( "Image of RGBA pixels test", "[Image]" ) {

  Image<Pixel> im(100,200);
    
  REQUIRE( im.width() == 100 );
  REQUIRE( im.height() == 200 );

  for(int i = 0; i < 100; ++i)
    for(int j = 0; j < 200; ++j){
      im(i,j).red = 0;
      im(i,j).green = 0;
      im(i,j).blue = 0;
      im(i,j).alpha = 255;
    }

  writeToFile(im, "temp.png");

  Image<Pixel> imcopy = readFromFile("temp.png");

  for(int i = 0; i < 100; ++i)
    for(int j = 0; j < 200; ++j){
      REQUIRE(imcopy(i,j).red == 0);
      REQUIRE(imcopy(i,j).green == 0);
      REQUIRE(imcopy(i,j).blue == 0);
      REQUIRE(imcopy(i,j).alpha == 255);
    }
  
}
