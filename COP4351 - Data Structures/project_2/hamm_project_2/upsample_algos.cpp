/*
Kaedon Hamm
kah16h

Nearest Neighbor and Bilinear Interpolation to upsample image arrays.
L1 Metric to measure effectiveness of algorithm.
*/
#include <cstdlib>
#include <math.h>


int* nearestNeighbor(int, int, int*);
int* bilinear(int, int, int, int, int*);
int l1_metric(int*, int*, int);

int* nearestNeighbor(int array_size, int new_size, int* pixels){
    
    // New empty array of upsampled size
    int* temp = new int[new_size * new_size];
    
    // Generate ratios to calculate offset of new pixels
    double ratio = array_size/(double)new_size;
    double floor_x, floor_y;

    for(int i = 0; i < new_size; i++){              // Rotates through the col
        for(int j = 0; j < new_size; j++){              // Rotates through the row
            floor_x = floor(j * ratio);
            floor_y = floor(i * ratio);
            temp[(i * new_size) + j] = pixels[(int)((floor_y * array_size) + floor_x)];
        }
    }
    return temp;
}

int* bilinear(int sizeh, int sizew, int upsizeh, int upsizew, int* pixels){
    int* temp = new int[upsizeh * upsizew];                         // New Upsampled array
    int p1, p2, p3, p4, x, y, pnt, avg_num;                         // Grid of 1:4 pixels 
    double x_pad, y_pad;                                      // Decides what pixel to reference
    double ratio = ((double(sizew - 1)) / upsizew);
    int offset = 0;

    for(int i = 0; i < upsizeh; i++){
        for(int j = 0; j < upsizew; j++){
            x = (int)(ratio * j);
            y = (int)(ratio * i);
            pnt = y * sizew + x;                // Finds old array reference pnt

            // Store surrounding pixel info
            p1 = pixels[pnt];
            p2 = pixels[pnt + 1];
            p3 = pixels[pnt + sizew];
            p4 = pixels[pnt + sizew + 1];

            x_pad = (ratio * j) - x;            // Padding in relation to col
            y_pad = (ratio * i) - y;            // Padding in relation to row

            // Average based on surrounding points
            avg_num = (int)((p1 * (1 - x_pad) * (1 - y_pad))
                            + (p2 * (x_pad) * (1 - y_pad))
                            + (p3 * (y_pad) * (1 - x_pad))
                            + (p4 * (x_pad * y_pad)));

            temp[offset++] = avg_num;
        }
    }
    return temp;
}

int l1_metric(int* uppix, int* orig, int size){
    signed long int l1 = 0;
    for(int i = 0; i < size; i++){
        l1 += abs(orig[i] - uppix[i]);
    }
    return l1;
}
