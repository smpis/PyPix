# PyPix
## 3D Scene Reconstruction Based on Stereo Vision

## Introduction

<p align="left">
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

The associated video of this project can be found in the following link: https://www.youtube.com/watch?v=YeAkoiZharE

</p>

<p align="center">
  <img alt="PyPix design flow" src="https://github.com/smpis/PyPix/blob/master/images/PyPix_design_flow.png">
</p>

## Methodology

<p align="left">
The individual tasks and processes of this project are provided in this section.
</p>

### 1. Camera Calibration

<p align="left">
OpenCV open-source code written in Python has been used for calibrating the camera used in this project. The goal of this process is to find the intrinsic parameters of the camera, also known as the camera matrix. The input pattern image used for this initial task is a black and white chessboard pattern that consists of 9 inner corners and 6 inner corners, in the horizontal and vertical directions, respectively. Multiple images of this pattern have been captured from different angles, fed to the camera calibration algorithm. An example of such a pattern image is illustrated in the figure below.
</p>

<p align="center">
  <img alt="Chessboard pattern" src="https://github.com/smpis/PyPix/blob/master/images/chessboard_pattern.png">
</p>

<p align="left">
The output of the camera matrix i.e. the focal lengths pair (fx, fy) and the principal points pair (cx, cy), is provided below.
</p>

<p align="center">
  <img alt="Camera matrix" src="https://github.com/smpis/PyPix/blob/master/images/camera_matrix.PNG">
</p>

### 2. Disparity Map

<p align="left">
After camera calibration, disparity map generation is the next step in the design flow. The disparity map was created and timed both in the PYNQ board and a CPU for validation. The initial aim was to generate stereo vision from two cameras. Due to lack of direct access to stereo cameras a work around was tried to generate pseudo stereo video. The input video is split into two parts to virtually create stereo vision and generate the disparity map. Though the generated map would not be very accurate, the purpose here was to evaluate how 3D construction algorithms work on real time stereo input. OpenCV inbuilt functions  that generate disparity maps were used to accelerate the pipeline
In future work, a method to compress the input frame or existing 3D cloud generating algorithms (VisualSFM, OpenMVS) etc will be used. There are a lot of such tools available but they are computationally intensive and only run post recording, not in real time, validating the need for FPGAs. To test the quality of stereo images, the aloe vera stereo image dataset was used. The process was timed on the PYNQ board and it took 12.531396 seconds so this is not feasible for real-time video. A custom overlay will be designed in the future to resolve this. However, the disparity map was generated both on the PYNQ board and the PC to validate the accuracy and as can been seen in the figure below.
</p>

<p align="center">
  <img alt="Disparity map" src="https://github.com/smpis/PyPix/blob/master/images/disparity_map.PNG">
</p>

### 3. 3D point cloud

<p align="left">
The 3D point cloud was generated using the associated built-in OpenCV function. For comparison with the custom method implemented in the next section, Mesh Lab was used to visualize the 3D point cloud. As can be seen from the figure below, the rendering was accurate. The 3D point cloud generation using the PYNQ board took 42.973997 seconds. This proved that disparity map and point cloud generation are bottlenecks that if accelerated would make real-time 3D model generation possible. Creating an overlay for these two OpenCV functions would be also part of the future work of this project.
</p>

<p align="center">
  <img alt="3D point cloud" src="https://github.com/smpis/PyPix/blob/master/images/3d_recon_aloe.PNG">
</p>

### 4. 3D to 2D projection

<p align="left">
The method of creating the projected 2D image first starts with the generated 3D dense point cloud. A 3D point cloud can be treated as all of the required information about the model. It holds the positional information; X, Y, Z coordinates, as well as the colour information; Red, Green, Blue intensity. To properly test the function, a simple cube was first generated with 8 points representing each of the corners on the object. This structure was then used for the rotation and translation functions. The cube was rotating in all 3 axes independently with the ability to output all points to the screen in the desired position and colour. The previously generated 3D dense point cloud provides the X, Y, Z coordinates and the RGB colours for each point so the rotation and translation matrices can be directly applied to this. For the current implementation, it was decided that a single input frame would be used and would be rotated to view the projection in a series of output frames. This could be changed to be a stream of input images i.e. video with the view either constant or even rotating around it. With the transforms completed, the final output frames were saved to a variable. It is entirely possible to directly view the output frames as they are being generated, though on a laptop this results in approximately a new frame very 3-5 seconds.
</p>

<p align="left">
laptop this results in approximately a new frame very 3-5 seconds.
The aloe vera example image holds over 230000 individual points to be calculated. Using a laptop with an Intel i5 processor, a rotation in 1 axis followed by a projection takes approximately 102.5 seconds to produce 10 output frames. When running on the PYNQ processor, the speed was markedly slower and so the problem had to be significantly rescaled. For this, the problem size would be reduced to 2300 points for the input. This gave an acceptable timeframe for the process to run and required 14.7 seconds for a single output frame. An output example of the rotated and projected model on the 2D plane is illustrated below.
</p>

<p align="left">
There are a couple of reasons for this low performance. Firstly, there is no data handling procedure written for this code. This means that the data is fetched linearly for the board rather than making use of parallel buffers. This could explain why the board processor was faster than making use of the DSP blocks. The communication i.e. the data transferred between the CPU and the FPGA on the board takes longer than the actual hardware acceleration. Secondly, the overlay was only computing in parallel the 3x3 matrix multiplication for a single operation as opposed to, for example, operations on complete frames. This means that the 27 blocks used were all in use at the same time, but to complete a single rotation and projection they would need to be reused for each calculation, individually. There was also only processing performed for each point individually, no points were calculated in parallel.
</p>

<p align="center">
  <img alt="3D to 2D projection" src="https://github.com/smpis/PyPix/blob/master/images/output_2D_plane.PNG">
</p>

## Conclusion

<p align="left">
Real-time 3D modelling on a PYNQ board was the primary motivation behind this project. It was realised that a lot of optimisation is possible in the whole 3D modeling pipeline  but full optimising was outside the scope of this project. Nevertheless, different sections of the pipeline were improved with different approaches. 
</p>

<p align="left">
The stereo video input was simulated by splitting the mono camera. Then to generate more accurate maps Aloe vera image dataset was used. A custom 3D to 2D projection algorithm  was employed to visualize as existing tools like mesh lab would be very intense for real time application. To prove that PYNQ board can be used for acceleration, a custom overlay was created for this projection. The overlay was successfully able to replicate the original algorithm but can be accelerated much further. In future work all the bottlenecks mentioned throughout the project would be accelerated by creating custom overlay.
This work proves that both the portable and parallel computation capacity of PYNQ board makes them the ideal candidate for real time 3D modeling. The authors hope that this would inspire more developers to work on practical applications such as drone mapping or GoPro for on the go photogrammetry. The python platform makes it very easy to prototype such applications and the future is full of interesting possibilities with PYNQ.
</p>

<p align="left">
Some of the next steps for this project would be to begin looking at data handling on the board to make full use of the accelerated hardware multiplications. This would also allow for further parallelisation of the rotation and projection calculations either by performing multiple operations at a time or processing multiple points at a time. Another step would be to create a complete pipeline for this process from video acquisition through to output projection of 3D space. Other steps that can be taken are to implement accelerators for the calculation of the point cloud or the disparity.depth map. All of these steps would push this project closer to a complete real time 3D render and visualisation of an object or environment.
</p>
