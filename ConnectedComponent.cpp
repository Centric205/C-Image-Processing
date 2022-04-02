/*
 *   Created by: Theo Madikgetla
 *   Date: 26 March 2022
 *
 * */

#include "ConnectedComponent.h"
#include <algorithm>

namespace MDKTHE015
{
    /*
     * @ConnectedComponent(@params)
     * This constructor takes in arguments and helps create
     * objects of connected components
     * */
	ConnectedComponent::ConnectedComponent(int compID, int nPixels, std::vector<std::pair<int, int>> &pixComp)
    {
        _identifier = compID;
        numberOfPixels = nPixels;
        pixelsCoordinates = pixComp;
    }

    /*
     * @ConnectedComponent()
     * Will allow an instance of the Connected Component class
     * in the drivers program
     * */
    ConnectedComponent::ConnectedComponent() {}

    /*
     * @ConnectedComponent(const ConnectedComponent& object)
     * This is the copy constructor of the connected componet
     * class.
     * */
    ConnectedComponent::ConnectedComponent(const ConnectedComponent &object) :
        _identifier(object._identifier), numberOfPixels(object.numberOfPixels), pixelsCoordinates(object.pixelsCoordinates)
    {}

    /*
     * @ConnectedComponent(const ConnectedComponent&& moveObject)
     * This is the move constructor of the connected component class
     * */
    ConnectedComponent::ConnectedComponent(ConnectedComponent &&movObject) :
        _identifier(std::move(movObject._identifier)), numberOfPixels(std::move(movObject.numberOfPixels)),
        pixelsCoordinates(std::move(movObject.pixelsCoordinates))
    {
        movObject._identifier = 0;
        movObject.numberOfPixels = 0;
    }

    /*
     * @getCoord()
     * This methods obtains coordinates of a connected
     * component.
     * */
    std::vector<std::pair<int, int>> & ConnectedComponent::getCoords()
    {
        return pixelsCoordinates;
    }

    /*
     * @addToVector(int row, int col)
     * Adds coordinates of a connectedcomponent when
     * it found
     * */
    void ConnectedComponent::addToVector(int row, int col)
    {
        pixelsCoordinates.push_back(std::make_pair(row, col));
    }

    /*
     * @getNumberofPixels()
     * A getter method for the private instance
     * 'numberOfPixels'
     * */
    int ConnectedComponent::getNumberofPixels()
    {
        return numberOfPixels;
    }

    int ConnectedComponent::getID()
    {
        return _identifier;
    }

    ConnectedComponent::~ConnectedComponent()
    {
        if (!pixelsCoordinates.empty())
            pixelsCoordinates.clear();
    }
}
