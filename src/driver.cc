#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "color.hpp"
#include "elevation_dataset.hpp"
#include "grayscale_image.hpp"
#include "path.hpp"
#include "path_image.hpp"

int main() {
  Path new_path = Path(1, 2);
  std::cout << "hello" << std::endl;
  ElevationDataset test_elvdataset(
      "/home/vagrant/src/mp-mountain-paths-khushigupta07/example-data/"
      "ex_input_data/prompt_5w_2h.dat",
      5,
      2);

  for (int row = 0; row < (int)test_elvdataset.get_data().size(); ++row) {
    for (int col = 0; col < (int)test_elvdataset.get_data().at(row).size();
         ++col) {
      std::cout << test_elvdataset.get_data().at(row).at(col) << " ";
    }
    std::cout << "endrow" << std::endl;
  }
  std::cout << "max: " << test_elvdataset.max_ele() << std::endl;
  std::cout << "min: " << test_elvdataset.min_ele() << std::endl;

  GrayscaleImage test_gsi(test_elvdataset);
  std::cout << "gsi constructor 1 test: "
            << test_gsi.get_image().at(1).at(3).blue() << std::endl;

  GrayscaleImage test_gsi2(
      "/home/vagrant/src/mp-mountain-paths-khushigupta07/example-data/"
      "ex_input_data/prompt_5w_2h.dat",
      5,
      2);
  std::cout << "gsi constructor 2 test: "
            << test_gsi2.get_image().at(0).at(1).blue() << std::endl;
  std::cout << "gsi color_at: " << test_gsi2.color_at(0, 1).blue() << std::endl;

  PathImage test_pi(test_gsi, test_elvdataset);
  std::vector<Path> test_paths_vect = test_pi.paths();
  std::vector<size_t> test_path = test_paths_vect.at(0).path();
  std::cout << "path test: " << test_path.at(2) << std::endl;

  ElevationDataset test_elvdataset2(
      "/home/vagrant/src/mp-mountain-paths-khushigupta07/example-data/"
      "ex_input_data/map-input-w51-h55.dat",
      51,
      55);
  GrayscaleImage test_gsi3(test_elvdataset2);
  PathImage test_pi2(test_gsi3, test_elvdataset2);
  std::vector<Path> test_paths_vect2 = test_pi2.paths();
  std::vector<size_t> test_path2 = test_paths_vect2.at(17).path();
  std::cout << "path test 2: " << test_path2.at(1) << std::endl;
}