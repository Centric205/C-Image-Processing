/*
 * Created by Theo Madikgetla
 * Date: 25/03/2022
 *
 * */

#ifndef	_CONNECTEDCOMPONENT_
#define _CONNECTEDCOMPONENT_
#include <iostream>
#include <vectory>
#include <memory>


namespace MDKTHE015
{
	class ConnectedComponent
	{
		int numberOfPixels;
		int _identifier;
		std::vector<std::pair<int, int>> pixelsCoordinates;

	    public:

		std::vector<std::pair<int, int>>& getCoords();
		void addToVector(int row, int col);
		std::vector<int> pixels;

		void removePixel(int& size);
		void setPixels(int size);
		int getNumberofPixels(void);
		int getID(void);
		ConnectedComponent();
		ConnectedComponent(const ConnectedComponent& object);
		ConnectedComponent(ConnectedComponent&& movObject);
		ConnectedComponent(int compID, int nPixels, std::vector<std::pair<int, int>> &pixComp);
		~ConnectedComponent();

		// Overloaded operators
		friend std::ostream & operator << (std::ostream& out, const ConnectedComponent& rhs);
		
	};

}

#endif
