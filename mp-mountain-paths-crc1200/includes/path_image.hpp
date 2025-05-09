#ifndef PATH_IMAGE_H
#define PATH_IMAGE_H

#include <cstdlib>  // for size_t
#include <vector>
#include <string>

#include "color.hpp"
#include "path.hpp"
#include "grayscale_image.hpp"
#include "elevation_dataset.hpp"

class PathImage {
public:
  PathImage(const GrayscaleImage &image, const ElevationDataset &dataset);
  size_t Width() const;
  size_t Height() const;
  unsigned int MaxColorValue() const;
  const std::vector<Path>& Paths() const;
  const std::vector<std::vector<Color> >& GetPathImage() const;
  void ToPpm(const std::string& name) const;
  void ChangeBottom(Path &path, size_t &col, size_t &i_row,  const ElevationDataset &dataset);
  void ChangeRegular(Path &new_path, size_t &col, size_t &i_row,  const ElevationDataset &dataset);
  void ChangeTop(Path &path, size_t &col, size_t &i_row,  const ElevationDataset &dataset);



private:
  std::vector<Path> paths_;
  size_t width_;
  size_t height_;
  std::vector<std::vector<Color>> path_image_;
  static const int kMaxColorValue = 255;
};

#endif