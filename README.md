# PyPix
## 3D Scene Reconstruction Based on Stereo Vision

## Introduction

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

<p align="center">
  <img alt="PyPix design flow" src="https://github.com/smpis/PyPix/blob/master/images/PyPix_design_flow.png">
</p>

## Methodology

The individual tasks and processes of this project are provided in this section.

### 1. Camera Calibration

OpenCV open-source code written in Python has been used for calibrating the camera used in this project. The goal of this process is to find the intrinsic parameters of the camera, also known as the camera matrix. The input pattern image used for this initial task is a black and white chessboard pattern that consists of 9 inner corners and 6 inner corners, in the horizontal and vertical directions, respectively. Multiple images of this pattern have been captured from different angles and used by the camera calibration algorithm. An example of such a pattern image is illustrated in the figure below.

<p align="center">
  <img alt="Chessboard pattern" src="https://github.com/smpis/PyPix/blob/master/images/chessboard_pattern.png">
</p>

The output of the camera matrix i.e. the focal lengths pair (fx, fy) and the principal points pair (cx, cy), is provided below.

<p align="center">
  <img alt="Camera matrix" src="https://github.com/smpis/PyPix/blob/master/images/camera_matrix.PNG">
</p>
