#include "seam_carver.hpp"
#include <iostream>

// implement the rest of SeamCarver's functions here

// given functions below, DO NOT MODIFY

SeamCarver::SeamCarver(const ImagePPM& image): image_(image) {
  height_ = image.GetHeight();
  width_ = image.GetWidth();
}

void SeamCarver::SetImage(const ImagePPM& image) {
  image_ = image;
  width_ = image.GetWidth();
  height_ = image.GetHeight();
}

int Squared (int val) {
  return int(val * val);
}

const ImagePPM& SeamCarver::GetImage() const {
  return image_;
}

void SeamCarver::VerticalElse(int* &cols, int* &update_energy, int &row, int &change_col, int &middle) const {
  int left = update_energy[(row * width_) + (change_col - 1)];
  int right = update_energy[(row * width_) + (change_col + 1)];
  if (middle <= left && middle <= right) {
    cols[row] = change_col;
  } else if (left <= right) {
    change_col -= 1;
    cols[row] = change_col;
  } else {
    change_col += 1;
    cols[row] = change_col;
  }
}

void SeamCarver::HorizontalElse(int* &rows, int* &update_energy, int &change_row, int &col, int &middle) const {
  int top = update_energy[((change_row - 1) * width_) + col];
  int bottom = update_energy[((change_row + 1) * width_) + col];
  if (middle <= top && middle <= bottom) {
    rows[col] = change_row;
  } else if (top <= bottom) {
    change_row -= 1;
    rows[col] = change_row;
  } else {
    change_row += 1;
    rows[col] = change_row;
    }
}

void SeamCarver::EnergyElse(int &row, int &col, Pixel &right, Pixel &left, Pixel &top, Pixel &bottom) const {
  left = image_.GetPixel(row, col - 1);
  right = image_.GetPixel(row, col + 1);
  top = image_.GetPixel(row - 1, col);
  bottom = image_.GetPixel(row + 1, col);
}

void SeamCarver::EnergyZero(int &row, int &col, Pixel &right, Pixel &left, Pixel &top, Pixel &bottom) const {
  if (col == 0) {
      left = image_.GetPixel(row, width_ - 1);
      right = image_.GetPixel(row, col + 1);
    } else if (col == width_ - 1) {
      right = image_.GetPixel(row, 0);
      left = image_.GetPixel(row, col - 1);
    } else {
      left = image_.GetPixel(row, col - 1);
      right = image_.GetPixel(row, col + 1);
    }
    bottom = image_.GetPixel(row + 1, col);
    top = image_.GetPixel(height_ - 1, col);
}

int SeamCarver::GetHeight() const {
  return height_;
}

int SeamCarver::GetWidth() const {
  return width_;
}

int SeamCarver::GetEnergy(int row, int col) const {
  Pixel right = Pixel();
  Pixel left = Pixel();
  Pixel top = Pixel();
  Pixel bottom = Pixel();
  if (row == 0) {
    EnergyZero(row, col, right, left, top, bottom);
  } else if (row == height_ - 1) {
    if (col == 0) {
      left = image_.GetPixel(row, width_ - 1);
      right = image_.GetPixel(row, col + 1);
    } else if (col == width_ - 1) {
      right = image_.GetPixel(row, 0);
      left = image_.GetPixel(row, col - 1);
    } else {
      left = image_.GetPixel(row, col - 1);
      right = image_.GetPixel(row, col + 1);
    }
    top = image_.GetPixel(row - 1, col);
    bottom = image_.GetPixel(0, col);
  } else if (col == 0) {
    left = image_.GetPixel(row, width_ - 1);
    right = image_.GetPixel(row, col + 1);
    top = image_.GetPixel(row - 1, col);
    bottom = image_.GetPixel(row + 1, col);
  } else if (col == width_ - 1) {
    right = image_.GetPixel(row, 0);
    left = image_.GetPixel(row, col - 1);
    top = image_.GetPixel(row - 1, col);
    bottom = image_.GetPixel(row + 1, col);
  } else {
    EnergyElse(row, col, right, left, top, bottom);
  }
  int energy =  ((left.GetBlue() - right.GetBlue()) * (left.GetBlue() - right.GetBlue())) + ((left.GetGreen() - right.GetGreen()) * (left.GetGreen() - right.GetGreen())) + ((left.GetRed() - right.GetRed()) * (left.GetRed() - right.GetRed())) + ((top.GetBlue() - bottom.GetBlue()) * (top.GetBlue() - bottom.GetBlue())) + ((top.GetRed() - bottom.GetRed()) * (top.GetRed() - bottom.GetRed())) + ((top.GetGreen() - bottom.GetGreen()) * (top.GetGreen() - bottom.GetGreen()));
  return energy;
}


int* SeamCarver::EnergyTable() const{
  int* energies = new int[height_ * width_];
  for (int row = height_ - 1; row >= 0; row--) {
    for (int col = 0; col < width_; col ++) {
      energies[(row * width_) + col] = GetEnergy(row, col);
    }
  }
  return energies;
}

int* SeamCarver::CreateVerticalTable() const {
  int* energy = EnergyTable();
  int* result = new int[height_ * width_];
  for (int row = height_ - 1; row >= 0; row--) {
    for (int col = 0; col < width_; col ++) {
      result[(row * width_) + col] = energy[(row * width_) + col];
    }
  }

  for (int row = height_ - 2; row >= 0; row--) {
    for (int col = 0; col < width_; col++) {
      int middle = result[((row + 1) * width_) + col];
      if (col == 0) {
        int right = result[((row + 1) * width_) + (col + 1)];
        if (middle <= right) {
          result[(row * width_) + col] = energy[(row * width_) + col] + middle;
        } else {
          result[(row * width_) + col] = energy[(row * width_) + col] + right;
        }
      } else if (col == width_ - 1) {
        int left = result[((row + 1) * width_) + (col - 1)];
        if (middle <= left) {
          result[(row * width_) + col] = energy[(row * width_) + col] + middle;
        } else {
          result[(row * width_) + col] = energy[(row * width_) + col] + left;
        }
      } else {
        int left = result[((row + 1) * width_) + (col - 1)];
        int right =  result[((row + 1) * width_) + (col + 1)];
        if (middle <= left && middle <= right) {
          result[(row * width_) + col] = energy[(row * width_) + col] + middle;
        } else if (left <= right) {
          result[(row * width_) + col] = energy[(row * width_) + col] + left;
        } else {
          result[(row * width_) + col] = energy[(row * width_) + col] + right;
        }
      }
    }
  }
  delete[] energy;
  return result;
}

int* SeamCarver::CreateHorizontalTable() const {
  int* energy = EnergyTable();
  int* result = new int[height_ * width_];
  for (int row = 0; row < height_; row++) {
    for (int col = 0; col < width_; col ++) {
      result[(row * width_) + col] = energy[(row * width_) + col];
    }
  }
  for (int col = width_ - 2; col >= 0; col--) {
    for (int row = 0; row < height_; row++) {
      int middle = result[(row * width_) + (col + 1)];
      if (row == 0) {
        int bottom = result[((row + 1) * width_) + (col + 1)];
        if (middle <= bottom) {
          result[(row * width_) + col] = energy[(row * width_) + col] + middle;
        } else {
          result[(row * width_) + col] = energy[(row * width_) + col] + bottom;
        }
      } else if (row == height_ - 1) {
        int top = result[((row - 1) * width_) + col + 1];
        if (middle <= top) {
          result[(row * width_) + col] = energy[(row * width_) + col] + middle;
        } else {
          result[(row * width_) + col] = energy[(row * width_) + col] + top;
        }
      } else {
        int top = result[((row - 1) * width_) + col + 1];
        int bottom = result[((row + 1) * width_) + col + 1];
        if (middle <= top && middle <= bottom) {
          result[(row * width_) + col] = energy[(row * width_) + col] + middle;
        } else if (top <= bottom && top <= middle) {
          result[(row * width_) + col] = energy[(row * width_) + col] + top;
        } else {
          result[(row * width_) + col] = energy[(row * width_) + col] + bottom;
        }
      }
    }
  }
  delete[] energy;
  return result;
}

int* SeamCarver::GetHorizontalSeam() const {
  int* rows = new int[width_];
  int* update_energy = CreateHorizontalTable();
  int begin = 0;
  for (int row = 0; row < height_; row++) {
    if (GetEnergy(row, 0) < GetEnergy(begin, 0)) {
      begin = row;
    }
  }
    int col = 1;
    rows[0] = begin;
    int change_row = begin;
    while (col < width_) {
      int middle = update_energy[(change_row * width_) + col];
      if (change_row == 0) {  //top
        int bottom = update_energy[((change_row + 1) * width_) + col];
        if (middle <= bottom) {
          rows[col] = change_row;
        } else {
          change_row += 1;
          rows[col] = change_row;
        }
      } else if (change_row == height_ - 1) { // bottom
        int top = update_energy[((change_row - 1) * width_) + col];
        if (middle <= top) {
          rows[col] = change_row;
        } else {
          change_row -= 1;
          rows[col] = change_row;
        }
      } else {
        HorizontalElse(rows, update_energy, change_row, col, middle); 
          }
        col += 1;
    }
  delete[] update_energy;
  return rows;
}

int* SeamCarver::GetVerticalSeam() const {
  int* cols = new int[height_];
  int* update_energy = CreateVerticalTable();
  int begin = 0;
  for (int col = 0; col < width_; col++) {
    if (GetEnergy(0, col) < GetEnergy(0, begin)) {
      begin = col;
    }
  }
    int row = 1;
    cols[0] = begin;
    int change_col = begin;
    while (row < height_) {
      int middle = update_energy[(row * width_) + change_col];
      if (change_col == 0) {  //left end
        int right = update_energy[(row * width_) + (change_col + 1)];
        if (middle <= right) {
          cols[row] = change_col;
        } else {
          change_col += 1;
          cols[row] = change_col;
        }
      } else if (change_col == width_ - 1) { // right end
        int left = update_energy[(row * width_) + (change_col - 1)];
        if (middle <= left) {
          cols[row] = change_col;
        } else {
          change_col -= 1;
          cols[row] = change_col;
        }
      } else {
        VerticalElse(cols, update_energy, row, change_col, middle); 
      }
      row += 1;
    }
  delete[] update_energy;
  return cols;
}

void SeamCarver::RemoveHorizontalSeam() {
  int* horizontals_to_remove = GetHorizontalSeam();
  image_.RemoveHorizontal(horizontals_to_remove);
  delete[] horizontals_to_remove;
  height_ -= 1;
}

void SeamCarver::RemoveVerticalSeam() {
  int* vertical_to_remove = GetVerticalSeam();
  image_.RemoveVertical(vertical_to_remove);
  delete[] vertical_to_remove;
  width_ -= 1;
}

  /**
   * Add any helper methods you may need
   */

