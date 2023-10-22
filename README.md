# Fall Hack 2023 Turning Over a New Leaf

## Project description
We made a big 3D rotating leaf in C++ Command Line Interface with ASCII characters  

## Technical detail

## Screenshot


## File structure
TOaNL  
  ├── CMakeLists.txt  
  ├── LICENSE   -- MIT License  
  ├── README.md -- README.md  
  ├── build     -- executable files  
  ├── debug  
  ├── etc  
  ├── include   -- header files  
  ├── src       -- source code  
  └── test      -- test files  

## Setup and run
### Pre-requisite
1. Linux OS
2. g++ compiler 11.4.0

### Install make tool and libraries
```bash
sudo apt-get -y install cmake
sudo apt-get install libncurses-dev
```
### Build files with CMake
```bash
cmake -S . -B build; cmake --build build
```
### Run the file
```bash
./build/bin/main
```

### Usage
```bash
Left click: rotate the leaf for 180 degree
Ctrl+C: Exit the program
```

## Participant names and contact information
### name: id: email:
### name: id: email:
### name: id: email:


## Libraries and resource
1. ncurses 6.4

## Github repository and video tutorial
Github repository: https://github.com/dousbao/TOaNL
Video tutorial: tbd
