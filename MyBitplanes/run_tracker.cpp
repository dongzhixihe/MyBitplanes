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
#include <io.h>
#include <string.h>
#include <Eigen/LU>
#include "file_name.h"
#if BITPLANES_WITH_PROFILER
#include <gperftools/profiler.h>
#endif

using namespace bp;
using namespace std;





int main()
{

	const char* ref_name = "D:\\MATLAB\\ESM\\dataset\\bitplanes_data\\v7";

	File file(ref_name);
	std::string first_frame = file.firstFrame(200);
	cv::Mat I = cv::imread(first_frame, cv::IMREAD_GRAYSCALE);
	cv::resize(I, I, cv::Size(480, 320));
	cv::Rect roi(180, 150, 50, 50);
	uint8_t End = 200;
	AlgorithmParameters alg_params;
	alg_params.verbose = false;
	alg_params.parameter_tolerance = 5e-4;
	alg_params.function_tolerance = 5e-4;
	alg_params.max_iterations = 100;
	alg_params.sigma = 1.2;
	alg_params.subsampling = 4;

	BitplanesTracker<Homography> tracker(alg_params);

	tracker.setTemplate(I, roi);
	


	for (size_t count = 1; count < End;count++)
	{
		std::string target_name = file.nextFrame();
		std::cout << "frame: "<< target_name << std::endl;
		cv::Mat I1 = cv::imread(target_name, cv::IMREAD_GRAYSCALE);

		cv::resize(I1, I1, cv::Size(480, 320));
		cv::imshow("target", I1);
		cv::waitKey(100);
		cv::waitKey(1);
		auto ret = tracker.track(I1);
		cv::Mat dimg;
		bp::DrawTrackingResult(dimg, I1, roi, ret.T.data());
		cv::imshow("bitplanes", dimg);
		cv::waitKey(100);
	}


	cv::waitKey(100000);
	return 0;
}

