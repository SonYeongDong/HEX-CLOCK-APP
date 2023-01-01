# hex_clock_app

## Build System 요구사항
- **os : ubuntu 18.04**
- **gcc version : 7.5.0 (x86x64 gcc만 사용 가능)**
- **opencv : 3.4.0**

## Build 필수 Install Package
-- hex_clock_app Build시 아래의 Packge Install이 필수로 필요합니다
#### 1. opencv 3.4.0 Install
- **"package"** 폴더내 **opencv-3.4.0.zip**, **opencv_contrib-3.4.0.zip**을 아래에 방법에 따라 Install 합니다
	- Linux 최신 상태 Update
		~~~bash
			# Optional. Ubuntu 18.04에서 libjasper-dev 패키지를 설치하기 위해서 저장소를 추가야함
			
			$ sudo add-apt-repository "deb http://security.ubuntu.com/ubuntu xenial-security main"
			$ sudo apt update
			$ sudo apt upgrade
			
			# Optional. Ubuntu 18.04 설치 후 추가적으로 필요한 코덱, 미디어 라이브러리를 설치함
			$ sudo apt install ubuntu-restricted-extras
		~~~	
	- 필요 packet 설치
		~~~bash
			# Build tools & required
			$ sudo apt install build-essential cmake git pkg-config
			
			# For still images
			$ sudo apt install libjpeg-dev libtiff5-dev libjasper-dev libpng-dev
			
			# For videos
			$ sudo apt install libavcodec-dev libavformat-dev libswscale-dev
			$ sudo apt install libdc1394-22-dev libxvidcore-dev libx264-dev x264
			$ sudo apt install libxine2-dev libv4l-dev v4l-utils
			$ sudo apt install libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev
			
			# GUI
			$ sudo apt install libgtk-3-dev
			
			# Optimization, Python3, etc.
			$ sudo apt install libatlas-base-dev libeigen3-dev gfortran
			$ sudo apt install python3-dev python3-numpy libtbb2 libtbb-dev
		~~~	
	- opencv 3.4.0.zip, opencv_contrib-3.4.0.zip copy
		~~~bash
			# Create a working directory named opencv & copy opencv file
			$ mkdir ~/opencv
			$ cp package/opencv 3.4.0.zip ~/opencv
            $ cp package/opencv_contrib-3.4.0.zip ~/opencv
			$ cd ~/opencv
            
			# Unpack
			$ unzip opencv-3.4.0.zip
			$ unzip opencv_contrib-3.4.0.zip
		~~~
	- CMake를 이용하여 Makefile 생성
		~~~bash
			# Create a build directory
			$ mkdir build && cd build
			
			# Run CMake
			$ cmake \
			-D CMAKE_BUILD_TYPE=Release \
			-D CMAKE_INSTALL_PREFIX=/usr/local \
			-D BUILD_WITH_DEBUG_INFO=OFF \
			-D BUILD_EXAMPLES=ON \
			-D BUILD_opencv_python2=OFF \
			-D BUILD_opencv_python3=ON \
			-D INSTALL_PYTHON_EXAMPLES=ON \
			-D OPENCV_EXTRA_MODULES_PATH=../opencv_contrib-3.4.0/modules \
			-D WITH_TBB=ON \
			-D WITH_V4L=ON \
			../opencv-3.4.0/ 2>&1 | tee cmake_messages.txt
		~~~
	- 컴파일 및 설치
		~~~bash
			# find out the number of CPU cores in your machine
			$ nproc
			
			# substitute 2 after -j by the output of nproc
			$ make -j2 2>&1 | tee build_messages.txt
			$ sudo make install
			$ sudo ldconfig
		~~~
	- 설치 확인
		~~~bash
			# If the output of next command is '3.4.0' then it's ok!
			$ pkg-config --modversion opencv
		~~~

## Build 방법
-- 아래와 같이 hex_clock_app Build 합니다
~~~bash
	- $ mkdir build
	- $ cd build;
	- $ cmake ..
	- $ make
~~~
