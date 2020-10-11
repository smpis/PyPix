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
  <img alt="Camera matrix" src="https://github.com/smpis/PyPix/blob/master/images/aloe_gray.PNG">
</p>
