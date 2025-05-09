#include "elevation_dataset.hpp"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>


size_t ElevationDataset::Width() const {
    return width_;
}
size_t ElevationDataset::Height() const {
    return height_;
}
int ElevationDataset::MaxEle() const {
    return max_ele_;
}
int ElevationDataset::MinEle() const {
    return min_ele_;
}
int ElevationDataset::DatumAt(size_t row, size_t col) const {
    return data_.at(row).at(col);
}
const std::vector<std::vector<int>>& ElevationDataset::GetData() const {
    return data_;
}

ElevationDataset::ElevationDataset(const std::string& filename, size_t width, size_t height): width_(width), height_(height) {
    max_ele_ = INT32_MIN;
    min_ele_ = INT32_MAX;
    int count2 = 0;
    int value = 0;
    data_ = std::vector<std::vector<int>>(height, std::vector<int>(width));
    std::ifstream ifs(filename);
    std::ifstream ifs2(filename);
    if (ifs2.is_open()) {
            while (ifs2.good()) {
                ifs2 >> value;
                count2 += 1;
            }
    }
    if (count2 > int(height * width + 1) || count2 < int(height * width)) {
        throw std::runtime_error("Hey man");
    }
    if (ifs.is_open()) {
        size_t row = 0;
        size_t col = 0;
        while (row < height) {
            if (ifs.fail()) {
                throw std::runtime_error ("Formatted-read Failure");
            }
            while (ifs.good() && col < width) {
                ifs >> value;
                if (value > max_ele_) {
                    max_ele_ = value;
                }
                if (value < min_ele_) {
                    min_ele_ = value;
                }
                data_.at(row).at(col) = value;
                col += 1;            
            }
            col = 0;
            row += 1;
        }
    }
    
}

    



