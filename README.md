# PyPix
3D scene reconstruction based on stereo vision

In this project we aim to take a step towards real time generation of 3D vision data.
This has huge application in domains such drone mapping, real time photogrammetry, AR/VR etc. 
Real time processing of video requires significant computation and mobile applications like Drones require low power portable units. 
The PYNQ platform provides the right tools to implement a complete pipeline for 3D reconstruction based on these constraints. 
We initially generate the 3D point cloud on an intel processor. Next we visualize the 3D points using Mesh Lab.
As Mesh lab is  not suitable for real time 3D visualization. We create our own 3D to 2D visualisation algorithm.
This is fast enough to run for video input and we demonstrate that by moving the output model around.
Next we recreate this pipeline on the PYNQ board. We demonstrate the concept on stereo images and time the performance. 
A custom overlay will be designed in the future for video input to accelerate both Disparity map and 3D point cloud generation.
For our custom 3D to 2D projection we create an overlay and test it on the PYNQ board. 

![design_flow](https://github.com/smpis/PyPix/blob/master/images/design_flow.PNG)
