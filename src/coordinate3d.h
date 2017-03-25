#ifndef COORDINATE3D_H
#define COORDINATE3D_H

#include <cstdint>

class Coordinate3D
{
public:

	//-------------------------------------------------------------- constructor
	// Brief Description
	//  Constructor for a 3D Coordinate
	//
	// Method:    Coordinate3D
	// FullName:  Coordinate3D::Coordinate3D
	// Access:    public 
	// Returns:   None
	// Parameter: const int64_t& x
	// Parameter: const int64_t& x
	// Parameter: const int64_t& z
	//--------------------------------------------------------------------------
	Coordinate3D(
		const int64_t& x,
		const int64_t& y,
		const int64_t& z);

	//-------------------------------------------------------------------- viewX
	// Brief Description
	//  Accessor for the X coordinate integer value
	//
	// Method:    viewX
	// FullName:  Coordinate3D::viewX
	// Access:    public 
	// Returns:   const int64_t&
	//--------------------------------------------------------------------------
	const int64_t& viewX() const;

	//-------------------------------------------------------------------- viewY
	// Brief Description
	//  Accessor for the Y coordinate integer value
	//
	// Method:    viewY
	// FullName:  Coordinate3D::viewY
	// Access:    public 
	// Returns:   const int64_t&
	//--------------------------------------------------------------------------
	const int64_t& viewY() const;

	//-------------------------------------------------------------------- viewZ
	// Brief Description
	//  Accessor for the Z coordinate integer value
	//
	// Method:    viewZ
	// FullName:  Coordinate3D::viewZ
	// Access:    public 
	// Returns:   const int64_t&
	//--------------------------------------------------------------------------
	const int64_t& viewZ() const;

private:
	int64_t m_x;
	int64_t m_y;
	int64_t m_z;
};

#endif