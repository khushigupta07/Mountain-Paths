#include "elevation_dataset.hpp"

ElevationDataset::ElevationDataset(const std::string& filename,
                                   size_t width,
                                   size_t height) {
  width_ = width;
  height_ = height;
  min_ele_ = 2147483647;
  max_ele_ = -2147483647;

  std::ifstream ifs{filename};
  // std::vector<std::vector<int>> data_;

  int data_point = 0;
  int total_size = width_ * height_;
  std::vector<int> all_data_points;
  while (ifs.good()) {
    ifs >> data_point;
    if (ifs.fail()) {
      ifs.clear();
      ifs.ignore(1, '\n');
    } else {
      all_data_points.push_back(data_point);
      if (data_point < min_ele_) {
        min_ele_ = data_point;
      }
      if (data_point > max_ele_) {
        max_ele_ = data_point;
      }
    }
  }
  if ((int)all_data_points.size() != total_size) {
    throw std::runtime_error("File data does not match width and height.");
  }
  std::vector<int> row_data;
  int total_count = 1;
  for (int row_pos = 0; row_pos < (int)height_; row_pos++) {
    for (int col_pos = 0; col_pos < (int)width_; col_pos++) {
      row_data.push_back(all_data_points.at(total_count - 1));
      if (total_count % width_ == 0) {
        data_.push_back(row_data);
        row_data = {};
      }
      ++total_count;
    }
  }
};
size_t ElevationDataset::width() const { return width_; }
size_t ElevationDataset::height() const { return height_; }
int ElevationDataset::max_ele() const { return max_ele_; }
int ElevationDataset::min_ele() const { return min_ele_; }
int ElevationDataset::datum_at(size_t row, size_t col) const {
  return data_.at(row).at(col);
}
const std::vector<std::vector<int>>& ElevationDataset::get_data() const {
  const std::vector<std::vector<int>>& data_reference = data_;
  return data_reference;
}