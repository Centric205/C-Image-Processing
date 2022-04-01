/*
 * Created by: Theo Madikgetla 
 * Date: 25 March 2022
 *
 * */

#ifndef _PGMIMAGEPROCESSOR_
#define _PGMIMAGEPROCESSOR_
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <memory>
#include "ConnectedComponent.h"

namespace MDKTHE015
{
	class PGMimageProcessor
	{
		int row_direction[4];
		int col_direction[4];
		std::string header;
		int height, width, graylevel;
		std::ifstream pgmInFile;
		std::ofstream pgmOutFile;
		std::vector<std::string> fileComments;
		unsigned char ** image2D;
		unsigned char ** threshImage;
		bool ** visits2D;
		std::queue<int> rowQ;
		std::queue<int> colQ;
		std::vector<std::unique_ptr<MDKTH015::ConnectedComponent>> extractedComponents;
		MDKTHE015::ConnectedComponent entry;

	    public:
		PGMimageProcessor();
		PGMimageProcessor(std::string filename);
		PGMimageProcessor(const PGMimageProcessor& p);
		PGMimageProcessor(const PGMimageProcessor&& p);
		~PGMimageProcessor();

		// Assignment Operator overloading
		PGMimageProcessor& operator = (const PGMimageProcessor& rhs);
		PGMimageProcessor& operator = (const PGMimageProcessor&& rhs);

		// Helper methods
		void setVisits(int row, int col);
		void addToStack(int row, int col);
		void deleteFromStack(int row, int col);
		void updateVisits(int row, int col);
		void generateThreshImage(unsigned char thresh, int minVal);
		void neighbours(int row, int col);
		void floodImage(void);


		 /* process the input image to extract all the connected components,
           	    based on the supplied threshold (0...255) and excluding any components
                    of less than the minValidSize. The final number of components that
           	    you store in your container (after discarding undersized one)
                    must be returned.
       		 */
      	        int extractComponents(unsigned char threshold, int minValidSize = 128);

        	/* iterate - with an iterator - though your container of connected
            	   components and filter out (remove) all the components which do not
            	   obey the size criteria pass as arguments. The number remaining
           	   after this operation should be returned.
        	*/
        	int filterComponentsBySize(int minSize, int maxSize);

        	/* create a new PGM file which contains all current components
           	   (255=component pixel, 0 otherwise) and write this to outFileName as a
           	   valid PGM. the return value indicates success of operation
       		 */
        	bool writeComponents(const std::string & outFileName);

        	// return number of components
        	int getComponentCount(void) const;

        	// return number of pixels in largest component
        	int getLargestSize(void) const;

        	// return number of pixels in smallest component
        	int getSmallestSize(void) const;

        	/* print the data for a component to std::cout
        	see ConnectedComponent class;
        	print out to std::cout: component ID, number of pixels
        	*/
        	void printComponentData(const MDKTHE015::ConnectedComponent & theComponent) const;
	        void printData(void);
	}
}

#endif
