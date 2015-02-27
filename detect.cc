#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <boost/program_options.hpp>

//#define CARD argv[1]
//#define CARD "card.png"
#define CARD "card_table.png"

#define OUTPUT_DIR "output/"

bool g_display_all = true;


// Display or writes file depending on global :(
void display(const char *name, cv::Mat image) {
  if (g_display_all) {
    cv::namedWindow("Display Image", CV_WINDOW_AUTOSIZE );
    imshow("Display Image", image);
    cv::waitKey(0); 
  }
  else {
    cv::imwrite(name, image);
  }
}

int main(int argc, const char *argv[])
{
  namespace po = boost::program_options;
  po::options_description desc("Allowed Options");
  desc.add_options()
    ("help", "produce help message")
    ("display", po::value<bool>(), "display or write images (false)")
    ("image", po::value<std::string>(), "the image path");

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);    

  if (vm.count("help")) {
    std::cout << desc << "\n";
    return 1;
  }

  if (vm.count("display")) {
    g_display_all = vm["display"].as<bool>();
  }

  const char *filename;
  if (vm.count("image")) {
    filename = vm["image"].as<std::string>().c_str();
  }
  else {
    filename = CARD;
  }

  cv::Mat image, dst, cdst;
  image = cv::imread(filename, 1 );

  if (!image.data) {
    printf("No image data \n");
    return -1;
  }

  cv::Canny(image, cdst, 50, 200, 3);
  cv::cvtColor(cdst, dst, cv::COLOR_GRAY2BGR);

  // display(cdst);

  // Hough Line finder.
  // gets vector of lines (p, theta) (line-normal form)
  std::vector<cv::Vec4i> lines;
  double rho = 1;
  double theta = CV_PI/180;
  int threshold = 25;
  //int threshold = 250;
  cv::HoughLinesP(cdst, lines, rho, theta, threshold);

  // Draw lines on image
  for (size_t i = 0; i < lines.size(); i++) {
    cv::Vec4i l = lines[i];
    int line_aa = 16;
    cv::line(dst,
             cv::Point(l[0], l[1]),
             cv::Point(l[2], l[3]),
             cv::Scalar(0,0,255),
             3, CV_AA);
  }

  display(OUTPUT_DIR "val.png", dst);

  // TODO:
  // Pull out the outer layer and classify as card.
  // Using that as the dimensions for the new space. 
  // Find the inner square and
  // calculate the phash of the image.

  return 0;
}
