//#include "bitplanes/core/config.h"
#include "homography.h"
#include "bitplanes_tracker.h"
#include "census.h"
#include "imwarp.h"
#include "bitplanes_tracker_pyramid.h"
#include "viz.h"
#include "timer.h"
#include "demo.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>
#include <string.h>
#include <Eigen/LU>
#include "file_name.h"
#if BITPLANES_WITH_PROFILER
#include <gperftools/profiler.h>
#endif

using namespace bp;

std::vector<std::string> split(const  std::string& s, const std::string& delim)
{
	std::vector<std::string> elems;
	size_t pos = 0;
	size_t len = s.length();
	size_t delim_len = delim.length();
	if (delim_len == 0) return elems;
	while (pos < len)
	{
		int find_pos = s.find(delim, pos);
		if (find_pos < 0)
		{
			elems.push_back(s.substr(pos, len - pos));
			break;
		}
		elems.push_back(s.substr(pos, find_pos - pos));
		pos = find_pos + delim_len;
	}
	return elems;
}




int main()
{
  std::string ref_name = "D:/bitplanes-master/data/zm/00000.png";
  File file(ref_name);
  
  cv::Mat I = cv::imread(ref_name, cv::IMREAD_GRAYSCALE);
  cv::Rect roi(80, 50, 100, 100);

  AlgorithmParameters alg_params;
  alg_params.verbose = true;
  alg_params.parameter_tolerance = 5e-6;
  alg_params.function_tolerance  = 5e-6;
  alg_params.max_iterations = 1000;
  alg_params.sigma = 1.2;
  alg_params.subsampling = 4;
  BitplanesTracker<Homography> tracker(alg_params);

  Matrix33f T_true;
  T_true <<
      1.01, 0.00, 1.0,
      0.0, 1.01, 0.0,
      0.0, 0.0, 1.0;
  T_true = T_true.inverse().eval();

  cv::Mat I1, xmap, ymap;
  imwarp<Homography>(I, I1, T_true, cv::Rect(0,0,I.cols,I.rows));

  tracker.setTemplate(I, roi);

  auto ret = tracker.track(I1);
 
cv::Mat dimg;
bp::DrawTrackingResult(dimg, I1, roi, ret.T.data());
cv::imshow("bitplanes", dimg);
cv::waitKey(1000);


  if(!alg_params.verbose)
    printf("track time %0.2f ms\n", TimeCode(100, [&]() {tracker.track(I);}));

//  return 0;


  std::cout << ret << std::endl;

  Matrix33f T_err = (ret.T.inverse() * T_true) - Matrix33f::Identity();
  std::cout << "\n" << T_err << std::endl;
  std::cout << "\nParameter error: " << T_err.norm() << std::endl;


  std::cout << "\nGOT:\n" << ret.T << std::endl;
  T_true = T_true.inverse().eval();
  std::cout << "\nture:\n" << T_true << std::endl;
  cv::waitKey(100000);
  return 0;
}

