# # Install minimal prerequisites (Ubuntu 18.04 as reference)
# sudo apt update && sudo apt install -y cmake g++ wget unzip
# # Download and unpack sources
# wget -O opencv.zip https://github.com/opencv/opencv/archive/4.6.0.zip
unzip opencv.zip
# Create build directory
mkdir -p build && cd build
# Renaming
# mv opencv-4.6.0/ opencv/
# Configure
cmake  ../opencv-4.6.0
# Build
cmake --build .
