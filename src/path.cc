#include "path.hpp"

Path::Path(size_t length, size_t starting_row) {
  length_ = length;
  starting_row_ = starting_row;
  std::vector<size_t> new_path(length);
  path_ = new_path;
};
size_t Path::length() const { return length_; }
size_t Path::starting_row() const { return starting_row_; }
unsigned int Path::ele_change() const { return ele_change_; }
void Path::inc_ele_change(unsigned int value) {
  ele_change_ += value;
  if (value < 0) {
    throw std::runtime_error("Elevation added cannot be negative.");
  }
}
const std::vector<size_t>& Path::path() const {
  const std::vector<size_t>& path_ref = path_;
  return path_ref;
}
void Path::set_loc(size_t col, size_t row) { path_.at(col) = row; }