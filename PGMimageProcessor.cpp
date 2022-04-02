//
// Created by theoc on 2022/04/02.
//
#include "PGMimageProcessor.h"
#include <sstream>

namespace MDKTHE015
{
    // Constructor with no parameters
    PGMimageProcessor::PGMimageProcessor()
    {
        // Row directions
        row_direction[0] = -1;
        row_direction[1] =  1;
        row_direction[2] =  0;
        row_direction[3] =  0;

        // Column directions
        col_direction[0] =  0;
        col_direction[1] =  0;
        col_direction[2] =  1;
        col_direction[3] = -1;

        height = 0;
        width = 0;
        graylevel = 0;

    }

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

    /*
     * Visits the N/S/E/W neighbours of the current
     * pixel coordinates.
     *
     * */

    void PGMimageProcessor::neighbours(int row, int col)
    {
        int nRow, nCol;
        for (int i = 0; i < (sizeof(row_direction)/sizeof(row_direction[0])); ++i) {
            nRow = row + row_direction[i];
            nCol = col + col_direction[i];

            // Fixes the out of bounce exception, meaning our array is no longer BOUNCY, LOL. (>.<)
            // "Out of bounds" (-.-)
            if (nRow < 0 || nCol < 0 || nRow >= height || nCol >= width)
                continue;

            // If visited, skip. Exercising is good.
            if (visits2D[nRow][nCol])
                continue;

            // If background(= 0) skip for the 3rd time. 3 skips are better than none \(^.^)/
            if (threshImage[nRow][nCol] = 0)
                continue;

            else
            {
                rowQ.push(nRow);
                colQ.push(nCol);
                visits2D[nRow][nCol] = true;
            }
        }
    }

    /*
     * Updates the visited pixels on the visits array.
     * */

    void PGMimageProcessor::updateVisits(int row, int col)
    {
        visits2D[row][col] = true;
    }



}