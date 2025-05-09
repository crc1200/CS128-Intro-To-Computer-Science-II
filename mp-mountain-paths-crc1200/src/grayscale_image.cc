#include "grayscale_image.hpp"
#include <vector>
#include <string>
#include "color.hpp"
#include <iostream>
#include <fstream>
#include <cmath>

GrayscaleImage::GrayscaleImage(const ElevationDataset& dataset) {
    int count = 0;
    image_ = std::vector<std::vector<Color>>(dataset.Height(), std::vector<Color>(dataset.Width()));

    for (unsigned int row = 0; row < dataset.Height(); row++) {
        for (unsigned int col = 0; col < dataset.Width(); col++) {
            count++;
            if (dataset.MaxEle() == dataset.MinEle()) {
                image_.at(row).at(col) = Color(0,0,0);
            } else {
                int color = int(std::round((double(dataset.DatumAt(row, col) - dataset.MinEle())) / (dataset.MaxEle() - dataset.MinEle()) * kMaxColorValue));
                if (color < 0 || color > kMaxColorValue) {
                throw "Whoopsy boi" + std::to_string(dataset.MaxEle() - dataset.MinEle());
            }
                image_.at(row).at(col) = Color(color, color, color);
            } 
        }
    }
    if (count != int(dataset.Height() * dataset.Width())) {
        throw std::runtime_error("Shoot");
    }
    height_ = dataset.Height();
    width_ = dataset.Width();
}
GrayscaleImage::GrayscaleImage(const std::string& filename, size_t width, size_t height) {
    image_ = std::vector<std::vector<Color>>(height, std::vector<Color>(width));
    int count = 0;
    ElevationDataset data = ElevationDataset(filename, width, height);\
    for (unsigned int row = 0; row < data.Height(); row++) {
        for (unsigned int col = 0; col < data.Width(); col++) {
            count += 1;
            if (data.MaxEle() == data.MinEle()) {
                image_.at(row).at(col) = Color(0,0,0);
            } else {
                int color = int(std::round((double(data.DatumAt(row, col) - data.MinEle())) / (data.MaxEle() - data.MinEle()) * kMaxColorValue));
                if (color < 0 || color > kMaxColorValue) {
                    throw "Whoopsy daisy";
                }
            image_.at(row).at(col) = Color(color, color, color);
        }
            }
            
    }
    if (count != int(data.Height() * data.Width())) {
        throw std::runtime_error("Whoops");
    }
    height_ = data.Height();
    width_ = data.Width();
}
size_t   GrayscaleImage::Width() const{
    return width_;
}
size_t   GrayscaleImage::Height() const{
    return height_;
}
unsigned int   GrayscaleImage::MaxColorValue() const{
    return kMaxColorValue;
}
const Color&   GrayscaleImage::ColorAt(int row, int col) const{
    return image_[row][col];
}
const std::vector<std::vector<Color> >& GrayscaleImage::GetImage() const{
    return image_;
}
void GrayscaleImage::ToPpm(const std::string& name ) const {
    std::ofstream ofs {name};
    if (!ofs.is_open()) {
        throw "What did you do???";
    }
    ofs << "P3" << std::endl;
    ofs << width_ << " " << height_ << std::endl;
    ofs << kMaxColorValue << std::endl;
    for (size_t row = 0; row < height_; row++) {
        for (size_t col = 0; col < width_; col++) {
            ofs << ColorAt(row, col).Red() << " " << ColorAt(row, col).Green() << " " <<ColorAt(row, col).Blue() << " ";
        }
        ofs << std::endl;
    }
}

