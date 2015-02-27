#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

//#define CARD argv[1]
#define CARD "card_table.png"


void display(cv::Mat image) {
  cv::namedWindow("Display Image", CV_WINDOW_AUTOSIZE );
  imshow("Display Image", image);
  cv::waitKey(0);
}

int main(int argc, const char *argv[])
{
  //std::cout << "Hello World!\n";
  cv::Mat image, dst, cdst;
  image = cv::imread(CARD, 1 );

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
  int threshold = 250;
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

  display(dst);

  return 0;
}
