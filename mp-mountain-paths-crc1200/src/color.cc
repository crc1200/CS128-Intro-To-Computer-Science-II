#include "color.hpp"
#include <stdexcept>
#include <iostream>


const int kBigBoi = 255;

Color::Color(int r, int g, int b): red_(r), green_(g), blue_(b) {
  if (red_ > kBigBoi || red_ < 0 || green_ > kBigBoi || green_ < 0 || blue_ > kBigBoi || blue_ < 0) {
    
    throw std::invalid_argument("Invalid argument" + std::to_string(red_));
  }
}


// do not modify
bool operator==(const Color& rhs, const Color& lhs) {
  return (rhs.Red() == lhs.Red() && rhs.Green() == lhs.Green() &&
          rhs.Blue() == lhs.Blue());
}
