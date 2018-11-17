#include "imwarp.h"
#include "homography.h"
#include "timer.h"

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>

int main()
{
  cv::Mat I = cv::imread("D:/bitplanes-master/data/zm/00000.png", cv::IMREAD_GRAYSCALE);
  cv::Rect roi(55, 100, 200, 100);

  bp::Matrix33f T;
  T <<
      1.0, 0.0, 30.0,
      0.0, 1.0, 10.0,
      0.0, 0.0, 1.0;

  cv::Mat Iw, xmap, ymap;
  bp::imwarp<bp::Homography>(I, Iw, T, roi, xmap, ymap);

  /*auto t_ms = bp::TimeCode(1000, [&]() { bp::imwarp<bp::Homography>(I,Iw,T,roi,xmap,ymap); });
  printf("remap time %0.2f ms\n", t_ms);*/

  std::cout << roi.size() << std::endl;
  std::cout << Iw.size() << std::endl;

  cv::Mat Iw2;
  bp::imwarp<bp::Homography>(I, Iw2, T, roi);

  //t_ms = bp::TimeCode(1000, [&]() { bp::imwarp<bp::Homography>(I,Iw2,T,roi); });
  //printf("warpPerspective time %0.2f ms\n", t_ms);

  cv::imshow("I", I(roi));
  cv::imshow("Iw", Iw);
  cv::imshow("Iw2", Iw2);
  cv::waitKey();

  return 0;
}
