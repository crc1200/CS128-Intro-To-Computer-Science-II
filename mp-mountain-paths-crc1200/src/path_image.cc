#include "path_image.hpp"
#include <vector>
#include <string>
#include "elevation_dataset.hpp"
#include "grayscale_image.hpp"
#include <iostream>
#include <fstream>

Color const kRed = Color(252,25,63);
Color const kGreen = Color(31,253,13);

void PathImage::ChangeBottom(Path &path, size_t &col, size_t &i_row,  const ElevationDataset &dataset) {
    int mid_path = std::abs(dataset.DatumAt(i_row, col + 1) - dataset.DatumAt(i_row, col));
    int top_path = std::abs(dataset.DatumAt(i_row, col) - dataset.DatumAt(i_row - 1, col + 1));
        if (mid_path <= top_path) {
            path.SetLoc(col + 1, i_row);
            path.IncEleChange(mid_path);
            path_image_.at(i_row).at(col + 1) = kRed;
        } else {
            path.SetLoc(col + 1, i_row - 1);
            path.IncEleChange(top_path);
            path_image_.at(i_row - 1).at(col + 1) = kRed;
        i_row -= 1;
    } 
}


void PathImage::ChangeTop(Path &new_path, size_t &col, size_t &i_row,  const ElevationDataset &dataset) {
    int bottom_path = std::abs(dataset.DatumAt(i_row, col) - dataset.DatumAt(i_row + 1, col + 1));
    int mid_path = std::abs(dataset.DatumAt(i_row, col + 1) - dataset.DatumAt(i_row, col));
    if (mid_path <= bottom_path) {
        new_path.SetLoc(col + 1, i_row);
        new_path.IncEleChange(mid_path);
        path_image_.at(i_row).at(col + 1) = kRed;
    } else {
        new_path.SetLoc(col + 1, i_row + 1);
        new_path.IncEleChange(bottom_path);
        path_image_.at(i_row + 1).at(col + 1) = kRed;
        i_row += 1;
    }
}


void PathImage::ChangeRegular(Path &new_path, size_t &col, size_t &i_row,  const ElevationDataset &dataset) {
    int top_path = std::abs(dataset.DatumAt(i_row, col) - dataset.DatumAt(i_row - 1, col + 1));
    int mid_path = std::abs(dataset.DatumAt(i_row, col + 1) - dataset.DatumAt(i_row, col));
    int bottom_path = std::abs(dataset.DatumAt(i_row, col) - dataset.DatumAt(i_row + 1, col + 1));
    if (mid_path <= top_path && mid_path <= bottom_path) {
        new_path.SetLoc(col + 1, i_row);
        new_path.IncEleChange(mid_path);
        path_image_.at(i_row).at(col + 1) = kRed;
    } else if (bottom_path <= top_path) {
        new_path.SetLoc(col + 1, i_row + 1);
        new_path.IncEleChange(bottom_path);
        path_image_.at(i_row + 1).at(col + 1) = kRed;
        i_row += 1;
}   else {
        new_path.SetLoc(col + 1, i_row - 1);
        new_path.IncEleChange(top_path);
        path_image_.at(i_row - 1).at(col + 1) = kRed;
        i_row -= 1;
    }
}


PathImage::PathImage(const GrayscaleImage &image, const ElevationDataset &dataset): width_(dataset.Width()), height_(dataset.Height()), path_image_(std::vector<std::vector<Color>>(dataset.Height(), std::vector<Color>(dataset.Width()))) {
    size_t best_path_row = 0;
    for (size_t row2 = 0; row2 < dataset.Height(); row2++) {
        for (size_t col = 0; col < dataset.Width(); col++) {
            path_image_.at(row2).at(col) = image.ColorAt(row2, col);
            path_image_.at(row2).at(0) = kRed;

        }
    }
    for (size_t row = 0; row < dataset.Height(); row++) {
        Path new_path = Path(dataset.Width(), row);
        new_path.SetLoc(0, row);
        size_t i_row = row;
        size_t col = 0;
        while (col < dataset.Width() - 1) {
            if (i_row == 0) {
                ChangeTop(new_path, col, i_row, dataset);
            } else if (i_row == dataset.Height() - 1) {
                ChangeBottom(new_path, col, i_row, dataset);
            } else {
                ChangeRegular(new_path, col, i_row, dataset);
            }
            col += 1;
        }
        paths_.push_back(new_path); 
        if (new_path.EleChange() <= paths_.at(best_path_row).EleChange()) {
            best_path_row = new_path.StartingRow();
        }
    }
    for (size_t i = 0; i < width_; i++) {
        if (image.GetImage().empty()) {
        for (size_t i = 0; i < width_; i++) {
            path_image_.at(0).at(i) = kGreen;
        }
    } else {
        path_image_.at(paths_.at(best_path_row).GetPath().at(i)).at(i) = kGreen;
    }
    }   
}

size_t PathImage::Width() const{
    return width_;
}
size_t PathImage::Height() const{
    return height_;
}
unsigned int PathImage::MaxColorValue() const{
    return kMaxColorValue;
}
const std::vector<Path>& PathImage::Paths() const{
    return paths_;
}
const std::vector<std::vector<Color> >& PathImage::GetPathImage() const{
    return path_image_;
}
void PathImage::ToPpm(const std::string& name) const{
    std::ofstream ofs {name};
    if (!ofs.is_open()) {
        throw "What did you do???";
    }
    ofs << "P3" << std::endl;
    ofs << width_ << " " << height_ << std::endl;
    ofs << kMaxColorValue << std::endl;
    for (size_t row = 0; row < height_; row++) {
        for (size_t col = 0; col < width_; col++) {
            ofs << path_image_.at(row).at(col).Red() << " " << path_image_.at(row).at(col).Green() << " " << path_image_.at(row).at(col).Blue() << " ";
        }
        ofs << std::endl;
    }
}




