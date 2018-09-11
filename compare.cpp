// program to compare two images pixel by pixel
// returns EXIT_SUCCESS if they are identical
// returns EXIT_FAILURE if not
#include <iostream>

#include "image.h"

int main(int argc, char *argv[]) {

  if (argc != 3) {
    std::cout << "Usage: compare"
              << "<first_input_filename> <second_output_filename>\n"
              << std::endl;
    return EXIT_FAILURE;
  }

  try {
    Image<Pixel> input1 = readFromFile(argv[1]);
    Image<Pixel> input2 = readFromFile(argv[2]);

    // check size are the same
    if( (input1.width() != input2.width()) ||
	(input1.height() != input2.height()) ){
      std::cout << "Images differ\n";
      return EXIT_FAILURE;
    }
    
    // compare each pixel, stop on first difference
    bool ok = true;
    for (intmax_t i = 0; i < input1.width(); ++i)
      for (intmax_t j = 0; j < input1.height(); ++j) {
	if( input1(i,j) != input2(i,j) ){
	  ok = false;
	  break;
	}
      }

    if(!ok){
      std::cout << "Images differ.\n";
      return EXIT_FAILURE;
    }
  } catch (std::exception &ex) {
    std::cerr << ex.what() << std::endl;
    return EXIT_FAILURE;
  }

  std::cout << "Images identical.\n";
  return EXIT_SUCCESS;
}
