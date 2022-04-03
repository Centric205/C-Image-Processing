//
// Created by theoc on 2022/04/02.
//
#include <iostream>
#include "PGMimageProcessor.h"

int main (int argc, char *argv[])
{
    int min, max, thresh;
    std::string printt, name;

    MDKTHE015::PGMimageProcessor pgm(argv[argc - 1]);

    std::cout << "Round_1" << std::endl;
    std::cout << "Results: " << pgm.extractComponents(atoi(argv[5]));
    pgm.filterComponentsBySize(atoi(argv[2]), atoi(argv[3]));
    pgm.writeComponents(argv[argc - 2]);
    std::cout << "Component Count: " << pgm.getComponentCount() << std::endl;
    std::cout << "Largest size: " << pgm.getLargestSize() << std::endl;
    std::cout << "Smallest size: " << pgm.getSmallestSize() << std::endl;


    std::cout << "Custom made" << std::endl;
    pgm.printData();

    //std::cout << "Non-Custome" << std::endl;
    //pgm.printComponentData();
}