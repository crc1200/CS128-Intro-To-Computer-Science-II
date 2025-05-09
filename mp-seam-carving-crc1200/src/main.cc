#include <fstream>
#include <iostream>

#include "image_ppm.hpp"
#include "seam_carver.hpp"



void PrintUsage(const std::string& command) {
  std::cout << "Usage: " << command << " INPUT_FILE [options] -o OUTPUT_FILE\n"
            << "Options:\n"
            << "\t-h times\tcarve times horizontal seams\n"
            << "\t-v times\tcarve times vertical seams\n";
}

int main(int argc, char* argv[]) {
  std::string out_option = "-o";
  if (argc < 4 || out_option != argv[argc - 2]) {
    PrintUsage(argv[0]);
    return 1;
  }

  std::ifstream infile(argv[1]);
  if (!infile.good()) {
    std::cout << "file '" << argv[1] << "' not found" << std::endl;
    return 1;
  }

  /* UNCOMMENT COMMENTED CODE BELOW AS YOU IMPLEMENT */

  ImagePPM image;
  infile >> image;
  infile.close();

  SeamCarver carver( image );
  for ( int i = 2; i < argc - 2; i += 2 ) {
    std::string times_string = argv[i + 1];
    int times = 0;
    try {
      times = std::stoi( times_string );
    } catch ( const std::exception& e ) {
      std::cout << "Malformed option" << std::endl;
      PrintUsage( argv[0] );
      return 1;
    }

    std::string option = argv[i];
    if ( option == "-h" ) {
      for ( int t = 0; t < times; t++ ) {
        carver.RemoveHorizontalSeam();
      }
    } else if ( option == "-v" ) {
      for ( int t = 0; t < times; t++ ) {
        carver.RemoveVerticalSeam();
      }
    } else {
      std::cout << argv[i] << " not an option" << std::endl;
      PrintUsage( argv[0] );
      return 1;
    }
  }

  std::ofstream outfile( argv[argc - 1] );
  outfile << carver.GetImage();
  outfile.close();

}

// int main() {
//   ImagePPM test = ImagePPM("./images/ocean.ppm");
//   SeamCarver test2 = SeamCarver(test);
//   for (int i = 0; i < test.GetHeight(); i++) {
//     for (int j = 0; j < test.GetWidth(); j++) {
//       std::cout << "(" << test.GetPixel(i,j).GetRed() << "," << test.GetPixel(i,j).GetGreen() << "," << test.GetPixel(i,j).GetBlue() << ") ";
//     }
//     std::cout << std::endl;
//   }
//   for (int i = 0; i < test.GetHeight(); i++) {
//     for (int j = 0; j < test.GetWidth(); j++) {
//       std::cout << test2.GetEnergy(i,j) << " ";
//     }
//     std::cout << std::endl;
//   }

//   int* test3 = test2.CreateHorizontalTable();
//   for (int i = 0; i < test2.GetHeight(); i++) {
//     for (int j = 0; j < test2.GetWidth(); j++) {
//       std::cout <<test3[(i * test2.GetWidth()) + j] << " ";
//     }
//     std::cout << std::endl;
//   }
//   return 0;
// }

  

//   int* vert = test2.GetHorizontalSeam();
//   for (int i = 0; i < test2.GetWidth(); i++) {
//     std::cout << vert[i] << std::endl;
//   }

//   std::cout << "HEYNYEHYEUEHYEKHKJHKJEHKJEHKEJHEKJHHEY JLKJLKJLKJLK J: " << std::endl;
//   test2.RemoveHorizontalSeam();
//     std::cout << "no errors with removing" << std::endl;
//   for (int i = 0; i < test2.GetImage().GetHeight(); i++) {
//     for (int j = 0; j < test2.GetImage().GetWidth(); j++) {
//       std::cout << "(" << test2.GetImage().GetPixel(i,j).GetRed() << "," << test2.GetImage().GetPixel(i,j).GetGreen() << "," << test2.GetImage().GetPixel(i,j).GetBlue() << ") ";
//     }
//     std::cout << std::endl;
//   }
//   std::cout << "HEYNYEHYEUEHYEKHKJHKJEHKJEHKEJHEKJHHEY JLKJLKJLKJLK J: " << std::endl;



//   return 0;
// }
