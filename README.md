
# xc2064 - SystemC modeling and simulation 
XC2064 was the first FPGA introduced by Xilinx in 1984. Aim of this project is to make SystemC model of this FPGA and provide simulation environment for experimenting with different configurations.

It was inspired by Ken Shirriff's blog [post](https://www.righto.com/2020/09/reverse-engineering-first-fpga-chip.html#fnref:mux) where he explained process of reverse engineering XC2064 and provided all needed information needed for building one by yourself. Besides great work he did on analyzing XC2064 He also built a web application which shows internal configuration of every FPGA internal element. It can be found [here](https://righto.com/xc2064/).Also [datasheet](https://media.digikey.com/pdf/Data%20Sheets/Xilinx%20PDFs/XC2000%20Families.pdf) needed to be consuted for small amount of details He left out.

## XC2064 internals
![CLB - Configurable Logic Block](https://static.righto.com/images/xc2064/CLB.jpg)

This CLB makes core functional block of XC2064. Grid of CLBs is then connected via routing logic. Internal structure is shown on following image.

![Internal routing](https://semiwiki.com/wp-content/uploads/2020/09/chip-map-zoom-w600.jpg)

Green box represent switching matrix which is implemented in /src/switching_matrix.hpp. Empty square is non directional PIP ( Programmable Interconnect Point), and full squares are normal pips used to route inputs and outputs of CLBs.

## Project structure

- /bitstream - python script that parses bitstream config file and puts it in neat format for loading into simulation
- /src - all C++ source files used in project. Every module is in it's own .hpp file 
- Makefile - build script

## Usage
Build program by running ```make``` and run it with ```./main```
To get waveform output run ```make wave``` (in progress)