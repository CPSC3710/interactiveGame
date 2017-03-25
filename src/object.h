#ifndef OBJECT_H
#define OBJECT_H

#include <cstdint>

class Object
{
public:

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

protected:
	int64_t m_xCoordinate;
	int64_t m_yCoordinate;
	int64_t m_zCoordinate;

private:

};

#endif