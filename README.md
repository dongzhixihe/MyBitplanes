# MyBitPlanes
This libarary is  the modified Windows version of the Bitplanes algorithm based on the Linux version provided by the original authors. This is compiled with vs2015.


[bitplanes]: http://www.cs.cmu.edu/~halismai/bitplanes/
See [here][bitplanes] for additional details and data.


### Dependecies
- Eigen 3.0+
- OpenCV 3.0+

## Using the library

Look into the directory test/ for examples of running the code.

First, initialize the tracker with AlgorithmParameters (see
core/algorithm_parameters.h for docs)

The default values should ok, but might need tweaking.

```cpp
  using namespace bp;

  AlgorithmParameters params;
  params.max_iterations = 50;
  params.verbose = true;
  params.function_tolerance = 1e-5;
  params.parameter_tolerance = 1e-4;

  // Create the tracker

  BitplanesTracker<Homography> tracker(params);

 // Initialize the template

   /* The image must be grayscale
    * ROI indicate the template location within the image
    */
  tracker.setTemplate(image, roi);


// Track new frames

  for(auto I : images)
    auto result = tracker.track(I);
```

see `core/types.h` for the Result structure, which contains the estimated
Homography along with other useful information.


[bpvo]: https://github.com/halismai/bpvo
For version optimized for Visual Odometry see [bpvo][bpvo]

