/*
Kaedon Hamm
kah16h 

Main program, used to change input file and output file.
Incoming and Outgoing pixel count are hardcoded.

Current input:
    [X] sample1_input_image @ 256x256
    [ ] sample2_input_image @ 256x256

Current output:
    out.txt @ 512x512
    
Current algorithm being used:
    [X] Nearest Neighbor
    [ ] Bilinear Interpolation
*/
#include <iostream>
#include <fstream>
#include <string>
#include "upsample_algos.cpp"

using namespace std;

int main(){
    int pixels[65536];
    char comma;
    fstream infile, outfile;

    infile.open("input/sample1_input_image.txt");
    outfile.open("output/out.txt");
    for(int i = 0; i < 65536; i++){
        infile >> pixels[i];
        if(infile.peek() == ',')
            infile >> comma;
    }
    infile.close();

    int* upsample_pix;
    upsample_pix = nearestNeighbor(256, 512, pixels);
    //upsample_pix = bilinear(256, 256, 512, 512, pixels);

    for(int i = 0; i < 512*512; i++){
        outfile << upsample_pix[i] << ",";
        if(i % 512 == 0 && i !=0)
            outfile << endl;
    }

    int original[262144];
    infile.open("input/sample1_original_image.txt");
    for(int i = 0; i < 262144; i++){
        infile >> original[i];
        if(infile.peek() == ',')
            infile >> comma;
    }
    infile.close();
    outfile.close();

    // Print L1 Metric to file
    outfile.open("output/l1_metric.txt");
    outfile << "L1 Metric: " << l1_metric(upsample_pix, original, 262144) << endl;
    outfile.close();

    cout << "Upsampled array -> output/out.txt\nL1 Metric -> output/l1_metric.txt" << endl;
    return 0;
}
