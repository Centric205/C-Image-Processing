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

    PGMimageProcessor::PGMimageProcessor(std::string filename)
    {
        pgmInFile.open(filename, std::ios::in |std::ios::binary);
        std::cout << filename << " in" << std::endl;

        if (!pgmInFile)
        {
            std::cout << "FILEEXCEPTION: Could not open file." << std::endl;
            std::cout << "Correct file name or check directory" << std::endl;
            exit(1);
        }

        std::string str;
        std::getline(pgmInFile, header);

        while (pgmInFile.eof())
        {
            std::getline(pgmInFile, str);
            if (str[0] == '#')
                fileComments.push_back(str);
            else
                break;
        }

        std::getline(pgmInFile, str);
        std::stringstream iss (str);
        iss >> width >> height;
        std::getline(pgmInFile, str);
        std::stringstream  is (str);
        is >> graylevel;
        //pgmInFile >> std::ws;    // empty line

        // Creating 2d dynamic allocated array
        image2D = new unsigned char *[height];
        for (int i = 0; i < height; ++i) {
            image2D[i] = new unsigned char [width];
        }

        //  Setting dimensions of visited array
        setVisits(height, width);

        // Array of pixels
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                pgmInFile >> image2D[i][j];
            }
        }
        pgmInFile.close();
    }

    /* process the input image to extract all the connected components,
       based on the supplied threshold (0...255) and excluding any components
       of less than the minValidSize. The final number of components that
       you store in your container (after discarding undersized one)
       must be returned.
    */

    int PGMimageProcessor::extractComponents(unsigned char threshold, int minValidSize)
    {
       // generateThreshImage(threshold, minValidSize);
        int compID = 0;

        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                if (image2D[i][j] >= threshold)
                {

                    std::queue<std::pair<int, int>> pix_queue;
                    std::shared_ptr<ConnectedComponent> component (new ConnectedComponent(compID));
                    pix_queue.push(std::make_pair(i, j));

                    while (!pix_queue.empty())
                    {
                        std::pair<int, int> pixel_position (pix_queue.front());
                        pix_queue.pop();

                        if (image2D[pixel_position.first][pixel_position.second] >= threshold)
                        {
                            component->addToVector(pixel_position.first,pixel_position.second);
                            image2D[pixel_position.first][pixel_position.second] = 0;

                            if (pixel_position.second < width - 1)
                                pix_queue.push(std::make_pair(pixel_position.first, pixel_position.second + 1));

                            if (pixel_position.first > 0)
                                pix_queue.push(std::make_pair(pixel_position.first - 1, pixel_position.second));

                            if (pixel_position.second > 0)
                                pix_queue.push(std::make_pair(pixel_position.first, pixel_position.second - 1));

                            if (pixel_position.first < height - 1)
                                pix_queue.push(std::make_pair(pixel_position.first + 1, pixel_position.second));

                        }
                    }
                    compID++;

                    if (component->getNumberofPixels() >= minValidSize)
                        extractedComponents.push_back(std::move(component));
                }
            }
        }


       /* for (int row = 0; row < height; ++row) {
            for (int column = 0; column < width; ++column) {
                // Puts current coordinates inside a queue and updates the visited array
                rowQ.push(row);
                colQ.push(column);
                updateVisits(row, column);


                while (colQ.size() > 0)
                {
                    // dequeues visited coordinates off the queue
                    int currentRow = rowQ.front();
                    rowQ.pop();
                    int currentCol = colQ.front();
                    colQ.pop();
                    unsigned char val = 255;

                    if (image2D[currentRow][currentCol] >= val)
                    {
                        entry.addToVector(currentRow, currentCol);

                        neighbours(currentRow, currentCol);
                        threshImage[currentRow][currentCol] = 0;    // value I chose to show that it has been visited.


                    }
                }
                int size = entry.getCoords().size();
                // CHECK: why didn't it work when you used new?
                // ANS: Worked when I included a pointer
                extractedComponents.push_back(
                        static_cast<std::shared_ptr<ConnectedComponent>>(new ConnectedComponent((compID),
                                                                                                size,
                                                                                                entry.getCoords())));



                compID++;
            }
        } */
       // std::cout << "Whats good" << std::endl;
        return extractedComponents.size();
    }

    /* iterate - with an iterator - though your container of connected
       components and filter out (remove) all the components which do not
       obey the size criteria pass as arguments. The number remaining
       after this operation should be returned.
    */

    int PGMimageProcessor::filterComponentsBySize(int minSize, int maxSize)
    {
        std::vector<std::shared_ptr<ConnectedComponent>>::iterator it;

        for (it = extractedComponents.begin(); it != extractedComponents.end(); it++)
        {
            if ((*it)->getNumberofPixels() >= minSize && (*it)->getNumberofPixels() <= maxSize)
            {
                extractedComponents.erase(it);
            }
        }

      return extractedComponents.size();
    }

    /*
     * Updates the image2D with 255 for coordinates
     * contained within each component
     *
     * */

    void PGMimageProcessor::floodImage()
    {
        std::vector<std::shared_ptr<ConnectedComponent>>::iterator it;

        // Floods it with foreground (= 255)
        for (it = extractedComponents.begin(); it != extractedComponents.end(); it++)
        {
            for (int i = 0; i < (*it)->getNumberofPixels(); ++i) {
                image2D[(*it)->getCoords()[i].first][(*it)->getCoords()[i].second] = 255;
            }
        }

        // Floods it with background (= 0)
        for (int row = 0; row < height; ++row) {
            for (int col = 0; col < width; ++col) {
                if (image2D[row][col] != 255)
                    image2D[row][col] = 0;
            }
        }
    }

    /*
     * Writes the filtered components to a file to allow
     * a user to see the changes
     * */
    bool PGMimageProcessor::writeComponents(const std::string &outFileName)
    {
        floodImage();
        pgmOutFile.open(outFileName, std::ios::binary);
        if (!pgmOutFile)
        {
            std::cout << "FILEEXCEPTION: Could not open file." << std::endl;
            std::cout << "Correct file name, or check directory" << std::endl;
        }

        pgmOutFile << header << std::endl;
        pgmOutFile << width << ' ' << height << std::endl;
        pgmOutFile << graylevel << std::endl;

        for (int row = 0; row < height; ++row) {
            for (int col = 0; col < width; ++col) {
                pgmOutFile << image2D[row][col] ;

//                // Creates ws between pixels
//                if (col != width)
//                    pgmOutFile << ' ';
//
//                // Adds '\n' at the end of the last pixel
//                else
//                    pgmOutFile << std::endl;
            }
           // pgmOutFile << std::endl;
        }


        pgmOutFile.close();

        return pgmOutFile.good();
    }

    /*
     * Getter method for the private instance 'extractedComponents'
     * returns number of components
     * */
    int PGMimageProcessor::getComponentCount() const
    {
        return extractedComponents.size();
    }

    // returns number of pixels in smallest component
    int PGMimageProcessor::getSmallestSize() const
    {
        std::vector<std::shared_ptr<ConnectedComponent>>::iterator it;

        int temp = extractedComponents[0]->getNumberofPixels();
        for (int i = 0; i < extractedComponents.size(); ++i) {
            if (temp > extractedComponents[i]->getNumberofPixels())
                temp = extractedComponents[i]->getNumberofPixels();

            if (temp < extractedComponents[i]->getNumberofPixels())
                continue;

            if (temp = extractedComponents[i]->getNumberofPixels())
                continue;

        }
    return temp;
    }

    // returns number of pixels in the largest component
    int PGMimageProcessor::getLargestSize() const
    {
        std::vector<std::unique_ptr<ConnectedComponent>>::iterator it;

        int temp = extractedComponents[0]->getNumberofPixels();
        for (int i = 0; i < extractedComponents.size(); ++i) {
            if (temp > extractedComponents[i]->getNumberofPixels())
                continue;

            else if (temp < extractedComponents[i]->getNumberofPixels())
                temp = extractedComponents[i]->getNumberofPixels();

            else if (temp = extractedComponents[i]->getNumberofPixels())
                continue;
        }
        return temp;
    }

    /* print the data for a component to std::cout
       see ConnectedComponent class;
       print out to std::cout: component ID, number of pixels
    */

    void PGMimageProcessor::printComponentData(const MDKTHE015::ConnectedComponent &theComponent) const
    {
        // Edit this method to print the data of the component if you have not yet overloaded it.
        std::cout << theComponent;
    }

    /*
     * Performs the same thing as the method above. Coded for test purposes.
     * */
    void PGMimageProcessor::printData() const
    {
        std::vector<std::shared_ptr<ConnectedComponent>>::iterator it;
        for (int i = 0; i < extractedComponents.size(); ++i) {
            //std::cout << extractedComponents[i]->getID() << " " << extractedComponents[i]->getNumberofPixels() << std::endl;
            printComponentData(*extractedComponents[i]);
         }
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
        unsigned char fore = 255;
        unsigned char back = 0;
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                if (image2D[i][j] <= thresh && image2D[i][j] > minVal)
                    threshImage[i][j] = fore;

                else
                    threshImage[i][j] = back;
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


    // Copy Constructor
    PGMimageProcessor::PGMimageProcessor(const PGMimageProcessor &p) :
        height(p.height), width(p.width), graylevel(p.graylevel),
        extractedComponents(p.extractedComponents), image2D(p.image2D),
        threshImage(p.threshImage), visits2D(p.visits2D)
    {}

    // Copy assignment operator
    PGMimageProcessor& PGMimageProcessor::operator = (const PGMimageProcessor& rhs)
    {
        if (this != &rhs)
        {
            height = rhs.height;
            width = rhs.width;
            graylevel = rhs.graylevel;
            extractedComponents = rhs.extractedComponents;
            image2D = rhs.image2D;
            threshImage = rhs.threshImage;
            visits2D = rhs.visits2D;
        }

        return *this;
    }

    // Move assignment operator
    PGMimageProcessor &PGMimageProcessor::operator=(const PGMimageProcessor &&rhs)
    {
        height = std::move(rhs.height);
        width = std::move(rhs.width);
        graylevel = std::move(rhs.graylevel);
        extractedComponents = std::move(rhs.extractedComponents);
        image2D = std::move(rhs.image2D);
        threshImage = std::move(rhs.threshImage);
        visits2D = std::move(rhs.visits2D);

        return *this;
    }



    // Move constructor
    PGMimageProcessor::PGMimageProcessor(const PGMimageProcessor &&p) :
        height(std::move(p.height)), width(std::move(p.width)),
        graylevel(std::move(p.graylevel)), extractedComponents(std::move(p.extractedComponents)),
        image2D(std::move(p.image2D)), threshImage(std::move(p.threshImage)),
        visits2D(std::move(p.visits2D))
    {}



    // Destructor
    PGMimageProcessor::~PGMimageProcessor()
    {
        for (int i = 0; i < height; ++i) {
            delete [] threshImage[i];
        }
        delete [] threshImage;

        // Frees visited bool of arrays
        for (int i = 0; i < height; ++i) {
            delete [] visits2D[i];
        }
        delete [] visits2D;

        // Releases memory from image2D
        for (int i = 0; i < height; ++i) {
            delete [] image2D[i];
        }
        delete [] image2D;
    }



}