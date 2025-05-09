#include "elevation_dataset.hpp"
#include <vector>
#include <string>
#include <fstream>
#include "grayscale_image.hpp"
#include "path_image.hpp"
#include <iostream>


int main() {
    ElevationDataset check = ElevationDataset("example-data/ex_input_data/map-input-w51-h55.dat", 51, 55);
    GrayscaleImage gray = GrayscaleImage(check);
    PathImage path = PathImage(gray, check);

    gray.ToPpm("file.ppm");
    path.ToPpm("new_file.ppm");

}