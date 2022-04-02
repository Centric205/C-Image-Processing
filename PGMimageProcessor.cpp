//
// Created by theoc on 2022/04/02.
//
#include "PGMimageProcessor.h"
#include <sstream>

namespace MDKTHE015
{
    /*
     * Sets all the elements of the array, then feeds it
     * "false" elements.
     * */
    void PGMimageProcessor::setVisits(int row, int col)
    {
        // Creates a dynamic array after setting dimensions
        visits2D = new bool *[row];
        for (int i = 0; i < row; ++i) {
            visits2D[i] = new bool [col];
        }

        // Creates dynamic array for threshImage
        threshImage = new unsigned char *[row];
        for (int i = 0; i < row; ++i) {
            threshImage[i] = new unsigned char [col];
        }

        // Sets all elements to false - What a pessimistic array, LOL.
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                visits2D[i][j] = false;
            }
        }
    }

    /*
     *  Generates a new image based on the
     *  threshold and 0
     * */
    void PGMimageProcessor::generateThreshImage(unsigned char thresh, int minVal)
    {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                if (image2D[i][j] <= thresh && image2D[i][j] > minVal)
                    threshImage[i][j] = 255;

                else
                    threshImage[i][j] = 0;
            }
        }
        std::cout << "Hell yeah." << std::endl;
    }


}