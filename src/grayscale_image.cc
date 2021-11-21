#include "grayscale_image.hpp"

GrayscaleImage::GrayscaleImage(const ElevationDataset& dataset) {
  width_ = dataset.width();
  height_ = dataset.height();
  // std::vector<std::vector<Color>> image_;
  std::vector<std::vector<int>> elev_data = dataset.get_data();
  for (int row = 0; row < (int)elev_data.size(); ++row) {
    std::vector<Color> row_colors;
    for (int col = 0; col < (int)elev_data.at(row).size(); ++col) {
      double elevation_point = (double)elev_data.at(row).at(col);
      int shade_of_gray = 0;
      if (dataset.max_ele() != dataset.min_ele()) {
        shade_of_gray =
            std::round((elevation_point - dataset.min_ele()) /
                       (dataset.max_ele() - dataset.min_ele()) * 255);
      }
      Color elev_color(shade_of_gray, shade_of_gray, shade_of_gray);
      row_colors.push_back(elev_color);
    }
    image_.push_back(row_colors);
  }
};
GrayscaleImage::GrayscaleImage(const std::string& filename,
                               size_t width,
                               size_t height) {
  ElevationDataset file_dataset(filename, width, height);
  width_ = file_dataset.width();
  height_ = file_dataset.height();

  std::vector<std::vector<int>> elev_data = file_dataset.get_data();
  for (int row = 0; row < (int)elev_data.size(); ++row) {
    std::vector<Color> row_colors;
    for (int col = 0; col < (int)elev_data.at(row).size(); ++col) {
      double elevation_point = (double)elev_data.at(row).at(col);
      int shade_of_gray = 0;
      if (file_dataset.max_ele() != file_dataset.min_ele()) {
        shade_of_gray =
            std::round((elevation_point - file_dataset.min_ele()) /
                       (file_dataset.max_ele() - file_dataset.min_ele()) * 255);
      }
      Color elev_color(shade_of_gray, shade_of_gray, shade_of_gray);
      row_colors.push_back(elev_color);
    }
    image_.push_back(row_colors);
  }
};
size_t GrayscaleImage::width() const { return width_; }
size_t GrayscaleImage::height() const { return height_; }
unsigned int GrayscaleImage::max_color_value() const {
  return max_color_value_;
}
const Color& GrayscaleImage::color_at(int row, int col) const {
  // Color color_1 = Color(1, 2, 3);
  const Color& color_ref = image_.at(row).at(col);
  return color_ref;
}
const std::vector<std::vector<Color>>& GrayscaleImage::get_image() const {
  const std::vector<std::vector<Color>>& image_reference = image_;
  return image_reference;
}
void GrayscaleImage::to_ppm(const std::string& name) const {
  std::ofstream ofs{name};
  ofs << "P3" << std::endl;
  ofs << width() << ' ' << height() << std::endl;
  ofs << max_color_value() << std::endl;
  for (auto row : image_) {
    for (Color color : row) {
      ofs << color.red() << ' ' << color.green() << ' ' << color.blue() << ' ';
    }
    ofs << std::endl;
  }
}