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

    ConnectedComponent::ConnectedComponent(int compID ) : _identifier(compID) , numberOfPixels(0){}
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

    // Copy Assignment operator
    ConnectedComponent &ConnectedComponent::operator=(const ConnectedComponent &rhs)
    {
        if (this != &rhs)
        {
             numberOfPixels = rhs.numberOfPixels;
             _identifier = rhs._identifier;
             pixelsCoordinates = rhs.pixelsCoordinates;
        }

        return *this;
    }

    // Move assignment operator
    ConnectedComponent &ConnectedComponent::operator=(const ConnectedComponent &&rhs)
    {
        numberOfPixels = std::move(rhs.numberOfPixels);
        _identifier = std::move(rhs._identifier);
        pixelsCoordinates = std::move(rhs.pixelsCoordinates);

        return *this;
    }

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
        numberOfPixels++;
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

    /*
     * @getID()
     * A getter method for the private instance
     * '_identifier'
     * */
    int ConnectedComponent::getID()
    {
        return _identifier;
    }

    /*
     * This performs operator overloading
     * on the '<<' operator
     * */
    std::ostream & operator << (std::ostream& out, const ConnectedComponent& rhs)
    {

        out << "| "<< rhs._identifier <<"\t" << "| " << rhs.numberOfPixels << std::endl;
        return out;
    }

    /*
     * @~ConnectedComponent
     * Destructor for the connected component class
     * */
    ConnectedComponent::~ConnectedComponent()
    {
        if (!pixelsCoordinates.empty())
            pixelsCoordinates.clear();
    }
}
