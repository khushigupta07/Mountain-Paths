#include "color.hpp"

Color::Color() : red_(0), green_(0), blue_(0) {}

Color::Color(int r, int g, int b) : red_(r), green_(g), blue_(b) {
  // need to ensure valid color has been constructed...
}

// do not modify: auto-grader relies on this definition of equality.
bool operator==(const Color& rhs, const Color& lhs) {
  return (rhs.red() == lhs.red() && rhs.green() == lhs.green() &&
          rhs.blue() == lhs.blue());
}