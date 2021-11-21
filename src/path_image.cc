#include "path_image.hpp"

PathImage::PathImage(const GrayscaleImage& image,
                     const ElevationDataset& dataset) {
  width_ = image.width();
  height_ = image.height();
  path_image_ = image.get_image();

  // std::vector<Path> paths_;
  // std::vector<std::vector<Color>> path_image_;

  for (int row = 0; row < (int)dataset.height(); ++row) {
    Path row_path(width_, row);  // path created for row
    row_path.set_loc(0, row);
    for (int col = 0; col < (int)dataset.width() - 1; ++col) {
      int current_point = dataset.datum_at(row, col);

      int next_path_row = row;
      int same_path_row_diff =
          abs(dataset.datum_at(row, col + 1) - current_point);

      if (row <
          (int)(dataset.height() - 1)) {  // checking the forward bottom row
        int bottom_path_row_diff =
            abs(dataset.datum_at(row + 1, col + 1) - current_point);
        if (bottom_path_row_diff < same_path_row_diff) {
          next_path_row = row + 1;
        }
      }
      if (row > 0) {  // checking the forward top row
        int top_path_row_diff =
            abs(dataset.datum_at(row - 1, col + 1) - current_point);
        if (top_path_row_diff < same_path_row_diff) {
          if (row < (int)(dataset.height() - 1)) {
            int bottom_path_row_diff =
                abs(dataset.datum_at(row + 1, col + 1) - current_point);
            if (top_path_row_diff < bottom_path_row_diff) {
              next_path_row = row - 1;
            }
          } else {
            next_path_row = row - 1;
          }
        }
      }
      if (next_path_row == (row + 1)) {
        row_path.inc_ele_change(
            abs(dataset.datum_at(row + 1, col + 1) - current_point));
      } else if (next_path_row == (row - 1)) {
        row_path.inc_ele_change(
            abs(dataset.datum_at(row - 1, col + 1) - current_point));
      } else {
        row_path.inc_ele_change(
            abs(dataset.datum_at(row, col + 1) - current_point));
      }
      row_path.set_loc(col + 1, next_path_row);
    }
    paths_.push_back(row_path);
  }

  int lowest_elev = 2147483647;
  int best_path_ind = 0;
  for (int paths_pos = 0; paths_pos < (int)paths_.size(); ++paths_pos) {
    if ((int)paths_.at(paths_pos).ele_change() < lowest_elev) {
      lowest_elev = paths_.at(paths_pos).ele_change();
      best_path_ind = paths_pos;
    }
  }
  Path best_path = paths_.at(best_path_ind);

  // making all of path_image_ red
  // for (int row = 0; row < (int)path_image_.size(); ++row) {
  //   std::vector<Color> row_colors;
  //   for (int col = 0; col < (int)path_image_.at(row).size(); ++col) {
  //     Color red_color(252, 25, 63);
  //     row_colors.push_back(red_color);
  //   }
  //   path_image_.push_back(row_colors);
  // }

  // // adding the best path to the path_image in green
  // for (int col = 0; col < (int)best_path.length(); ++col) {
  //   int row = best_path.path().at(0);
  //   Color green_color(31, 253, 13);
  //   path_image_.at(row).at(col) = green_color;
  // }
};
size_t PathImage::width() const { return width_; }
size_t PathImage::height() const { return height_; }
unsigned int PathImage::max_color_value() const { return max_color_value_; }
const std::vector<Path>& PathImage::paths() const {
  const std::vector<Path>& path_ref = paths_;
  return path_ref;
}
const std::vector<std::vector<Color>>& PathImage::path_image() const {
  const std::vector<std::vector<Color>>& pathim_ref = path_image_;
  return pathim_ref;
}
void PathImage::to_ppm(const std::string& name) const {
  bool hello = true;
  if (name.at(0) == 'a') {
    hello = false;
  }
}