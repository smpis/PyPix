# PyPix
3D Scene Reconstruction Based on Stereo Vision

The associated video of this project can be found in the following link: https://www.youtube.com/watch?v=YeAkoiZharE

In this project we aim to take a step towards real-time generation of 3D vision data.
This has many applications in domains such as drone-mapping, real-time photogrammetry, AR/VR etc. 
Real-time processing of video requires significant computations, and mobile applications like drones require low-power portable units. 
The PYNQ platform provides the right tools to implement a complete pipeline for 3D reconstruction based on these constraints. 
Initially, we generate the 3D point cloud on an Intel CPU and next, we visualize it using Mesh Lab.
As Mesh Lab is  not suitable for real-time 3D visualization, we create our own 3D to 2D visualization algorithm.
This is fast enough to run for video input and we demonstrate that by moving the output model around.
Next, we recreate this pipeline on the PYNQ-Z2 board. We demonstrate the concept on stereo images and then we time the performance. 
For our custom 3D to 2D projection algorithm, we design an overlay to accelerate the multiply-accumulate (MAC) operations and then test it on the PYNQ board via Jupyter Notebook.
Custom overlays will be designed in the future for video input to accelerate both the disparity map and the 3D point cloud generation, which are the most compute-intensive tasks in this project.

![PyPix_design_flow](https://github.com/smpis/PyPix/blob/master/images/PyPix_design_flow.png)
