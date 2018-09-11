#include "image.h"

// for file I/O
#include "lodepng.h"

Image<Pixel> readFromFile(std::string fname) {

  std::vector<unsigned char> raw;
  unsigned w, h;

  // decode the png
  unsigned error = lodepng::decode(raw, w, h, fname.c_str());

  if (error)
    throw std::runtime_error(lodepng_error_text(error));

  Image<Pixel> im(w, h);
  std::size_t idx = 0;
  for (std::size_t i = 0; i < im.width(); ++i)
    for (std::size_t j = 0; j < im.height(); ++j) {
      im(i, j).red = raw[idx++];
      im(i, j).green = raw[idx++];
      im(i, j).blue = raw[idx++];
      im(i, j).alpha = raw[idx++];
    }

  return im;
}

void writeToFile(const Image<Pixel> &im, std::string fname) {

  std::vector<unsigned char> raw(4 * im.width() * im.height());

  std::size_t idx = 0;
  for (std::size_t i = 0; i < im.width(); ++i)
    for (std::size_t j = 0; j < im.height(); ++j) {
      raw[idx++] = im(i, j).red;
      raw[idx++] = im(i, j).green;
      raw[idx++] = im(i, j).blue;
      raw[idx++] = im(i, j).alpha;
    }

  // encode the image
  unsigned error = lodepng::encode(fname.c_str(), raw, im.width(), im.height());

  if (error)
    throw std::runtime_error(lodepng_error_text(error));
}

bool operator==(const Pixel &a, const Pixel &b) {
  return (a.red == b.red) && (a.green == b.green) && (a.blue == b.blue) &&
         (a.alpha == b.alpha);
}

bool operator!=(const Pixel &a, const Pixel &b) { return !(a == b); }
