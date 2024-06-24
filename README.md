# tRAYcer

This is a project for Seasons of Code 2024 that implements a ray tracer in C++. The goal is to implement a ray tracer that can render a scene with spheres, planes, and triangles with diffuse, specular, and reflective materials.

## Requirements

Any C++ compiler. GNU make is used to compile the project. A PPM viewer is needed to view the rendered images.

## Building

Run `make imagex` to build the xth image. For example, `make image1` will build the first image. The images are stored in the `images/` directory.
Run `make` to build all images.
Note: Some images have the same main file as the previous image. Other include file changes were made between such images, and building them with this completed project will result in identical images. The images already present in the repository are the actually intended images.
