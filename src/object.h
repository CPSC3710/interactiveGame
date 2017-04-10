#ifndef OBJECT_H
#define OBJECT_H

#include "coordinate3d.h"

class Object
{
public:

	//-------------------------------------------------------------- constructor
	// Brief Description
	//  Constructor for an Object
	//
	// Method:    Object
	// FullName:  Object::Object
	// Access:    public 
	// Returns:   None
	// Parameter: const Coordinate3D& coordinate
	//--------------------------------------------------------------------------
	Object(
	   const Coordinate3D& coordinate);

   virtual ~Object() { }
   

	//--------------------------------------------------------------------- draw
	// Brief Description
	//  Pure virtual draw function
	//
	// Method:    draw
	// FullName:  Object::draw
	// Access:    public 
	// Returns:   void
	//--------------------------------------------------------------------------
	virtual void draw() = 0;

	//-------------------------------------------------------------------- print
	// Brief Description
	//  Prints a letter representing the subclass to the console, intended to
	//  be used only for debugging purposes.
	//
	// Method:    print
	// FullName:  Object::print
	// Access:    public 
	// Returns:   void
	//--------------------------------------------------------------------------
	virtual void print() = 0;

	//--------------------------------------------------------- viewCoordinate3D
	// Brief Description
	//  Returns a const reference to the Coordinate3D of the Object
	//
	// Method:    viewCoordinate3D
	// FullName:  Robot::viewCoordinate3D
	// Access:    public 
	// Returns:   const Coordinate3D&
	//--------------------------------------------------------------------------
   virtual const Coordinate3D& viewCoordinate3D() const = 0;

   virtual bool isDestroyable() const;

protected:
	Coordinate3D m_coordinate3D;

private:

};

#endif
