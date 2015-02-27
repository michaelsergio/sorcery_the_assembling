#include <iostream>
#include <opencv2/opencv.hpp>

//#define CARD argv[1]
#define CARD "card_table.png"

int main(int argc, const char *argv[])
{
  std::cout << "Hello World!\n";
  cv::Mat image;
  image = cv::imread(CARD, 1 );

  if ( !image.data )
  {
    printf("No image data \n");
    return -1;
  }

  cv::namedWindow("Display Image", CV_WINDOW_AUTOSIZE );
  imshow("Display Image", image);

  cv::waitKey(0);


  
  return 0;
}
