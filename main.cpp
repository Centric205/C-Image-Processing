//
// Created by theoc on 2022/04/02.
//
#include <iostream>
#include <cstring>
#include "PGMimageProcessor.h"

int main (int argc, char *argv[])
{
    int min, max, thresh;
    bool write  = false;
    bool print = false;
   // std::string printt, name;

//    MDKTHE015::PGMimageProcessor pgm(argv[argc - 1]);


    for (int i = 1; i < argc; ++i) {
        if (std::strcmp(argv[i], "-p") == 0)
        {
            print = true;
            //pgm.printData();
        }

        else if (std::strcmp(argv[i], "-s") == 0)
        {
            min = std::stoi(argv[++i]);
            max = std::stoi(argv[++i]);
        }

        else if (std::strcmp(argv[i], "-t") == 0)
        {
            thresh = std::stoi(argv[++i]);
        }

        else if (std::strcmp(argv[i], "-w") == 0)
        {
            write = true;
         //   std::cout << "Now generating " << argv[argc - 2] << ".......\n";
        //    pgm.writeComponents(argv[argc - 2]);
        }
    }

    std::cout << "**************** WELCOME ****************" << std::endl;
    std::cout << std::endl;
    std::cout << "TASK 1:" << std::endl;
    std::cout << "Now reading file: " << argv[argc - 1] << std::endl;
    MDKTHE015::PGMimageProcessor pgm(argv[argc - 1]);

    //std::cout << "Number of extrated components: " << pgm.extractComponents(atoi(argv[5]));
    std::cout << "Now extracting components........" << std::endl;
    std::cout << "Number of components: " << pgm.extractComponents(thresh) << std::endl;

    std::cout << "Now filtering........" << std::endl;
  //  std::cout << "Number of components: " << pgm.filterComponentsBySize(atoi(argv[2]), atoi(argv[3]));
    std::cout << "Number of components: " << pgm.filterComponentsBySize(min, max) << std::endl;

    if (write)
    {
        std::cout << "Now generating " << argv[argc - 2] << ".......\n";
        pgm.writeComponents(argv[argc - 2]);
    }

    std::cout << "============= RESULTS =============" << std::endl;

    std::cout << "Component Count: " << pgm.getComponentCount() << std::endl;
    std::cout << "Largest size: " << pgm.getLargestSize() << std::endl;
    std::cout << "Smallest size: " << pgm.getSmallestSize() << std::endl;

    if (print)
    {
        std::cout << "| ID\t" << "| Number of pixels" << std::endl;
        pgm.printData();
    }



    //std::cout << "Custom made" << std::endl;
    //pgm.printData();

    //std::cout << "Non-Custome" << std::endl;
    //pgm.printComponentData();
}