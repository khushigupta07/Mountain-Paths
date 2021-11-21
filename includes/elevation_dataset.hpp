#ifndef ELEVATION_DATASET_H
#define ELEVATION_DATASET_H

#include <cstdlib>  // for size_t
#include <fstream>
#include <string>
#include <vector>

class ElevationDataset {
public:
  ElevationDataset(const std::string& filename, size_t width, size_t height);
  size_t width() const;
  size_t height() const;
  int max_ele() const;
  int min_ele() const;
  int datum_at(size_t row, size_t col) const;
  const std::vector<std::vector<int>>& get_data() const;

private:
  size_t width_;
  size_t height_;
  std::vector<std::vector<int>> data_;
  int max_ele_;
  int min_ele_;
};

#endif