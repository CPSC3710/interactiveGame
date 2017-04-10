#include "object.h"

Object::Object(
	const Coordinate3D& coordinate) :
	m_coordinate3D(coordinate)
{

}

bool Object::isDestroyable() const
{
	return false;
}
