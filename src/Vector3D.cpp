#include "Vector3D.h"
double Vector3D::mag()
{
	return ( sqrt( (*this) * (*this)));
}

Vector3D Vector3D::operator +(Vector3D aux)
{
	return (Vector3D( _x + aux._x , _y + aux._y, _z + aux._z ));
}

Vector3D Vector3D::operator -(Vector3D aux)
{
	return (Vector3D( _x - aux._x , _y - aux._y, _z - aux._z ));
}

void Vector3D::operator =(Vector3D aux)
{
	_x = aux._x;
	_y = aux._y;
	_z = aux._z;
}

Vector3D Vector3D:: operator ^(Vector3D aux)
{
	return (Vector3D( (_y*aux._z - _z * aux._y), (_z*aux._x - _x * aux._z), (_x*aux._y - _y * aux._z) ));
}

double Vector3D:: operator *(Vector3D aux)
{
	return (_x*aux._x + _y*aux._y + _z*aux._z);
}

Vector3D Vector3D:: operator *(double aux)
{
	return (Vector3D(_x*aux, _y*aux, _z*aux));
}

void Vector3D::normalize()
{
	_x/=mag();
	_y/=mag();
	_z/=mag();
}