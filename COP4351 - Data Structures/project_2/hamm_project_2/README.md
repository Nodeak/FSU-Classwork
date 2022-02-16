This README is formatted for Markdown. Best viewed on the GitLab.

v   v   v   v   v   v   v   v   v   v   v   
https://gitlab.com/nodeak/cop4531_project_2
^   ^   ^   ^   ^   ^   ^   ^   ^   ^   ^

**Kaedon Hamm (kah16h)**

**COP 4531 - Analysis of Data Structures and Algorithms**

# Project 2 - Algorithm to Image Upsampling #
## Current Setup ##
- Algorithm being used: _Nearest Neighbor_
- Input being used:     _sample1_input_image.txt_
- L1 Metric comparison: _sample1_original_image.txt_

## How to run ##
This program uses a Makefile.

`make` Compiles the program into an executable called **main** and generates empty output files required in _./output/_

`make test` Compiles the program into an executable called **test** using GoogleTest flags and runs it against the unittests

`make coverage` Compiles the program using Gcovr flags, runs the generated executables, and then runs gcovr on them to show the code coverage of the program and its test cases

`make clean` Removes all files created by the other make options as well as the output files

## Algorithms Used ##
**Nearest Neighbor** - Uses the closest number to fill in the missing spaces in the array (rounded down)

|  |  |
| ------ | ------ |
| 1 | 2 |
| 3 | 4 |
        

would turn into 


|  |  |  |  |
| ------ | ------ | ----- | -----|
| 1 | 1 | 2 | 2 |
| 1 | 1 | 2 | 2 |
| 3 | 3 | 4 | 4 |
| 3 | 3 | 4 | 4 |


**Bilinear Interpolation** - Takes the weight of difference between points near it and calculates the average of them all in reference to each other.


|  |  |
| ------ | ------ |
| 10 | 20 |
| 30 | 40 |
        

would turn into 


|  |  |  |  |
| ------ | ------ | ----- | -----|
| 10 | 12 | 17 | 20 |
| 15 | 17 | 22 | 25 |
| 25 | 27 | 32 | 35 |
| 30 | 32 | 37 | 40 |


## File Structure ##

`input` Contains all input files (_sample1_input_image_, _sample1_original_image_, _etc_)

`output` Location of program output. Empty files of out.txt containing the upsampled array and l1_metric.txt containing the L1 Metric are created during make of program.

`unittest` Holds unittest of program.

`googletest` git clone of Google's GoogleTest repository. Empty when cloned for some reason.

`upsample.cpp` Driver file that controls input/output and which algorithm is called

`upsample_aglos.cpp` Algorithms used to calculate the upsampling of inputted arrays. Contains Bilinear and Nearest Neighbor currently.