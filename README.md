# Lilyphys Vooronderzoek

This is a simple C++ & Raylib project to experiment with creating a custom physics engine.

## How to build

Make sure Git is installed.

Clone this repository with `git clone --resursive https://github.com/EludeQ/phys_demo.git`. 
(Or `git clone --resursive git@github.com:EludeQ/sos_test.git` if you're using SSH.)

CMake version `3.19` or newer must be installed.
(Install it with `sudo apt install cmake` on Debian/Ubuntu.)

I believe it should 'just work' on Windows, but on Linux additional libraries will be needed:

### For Linux

Install the required libraries:

Debian/Ubuntu:
```
sudo apt install libasound2-dev mesa-common-dev libx11-dev libxrandr-dev libxi-dev xorg-dev libgl1-mesa-dev libglu1-mesa-dev
```
Arch Linux:
```
sudo pacman -S alsa-lib mesa libx11 libxrandr libxi libxcursor libxinerama
```
(These are required to compile Raylib.)