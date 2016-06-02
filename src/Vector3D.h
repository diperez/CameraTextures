#include <math.h>

class Vector3D
{
	public:
		double _x, _y, _z;
		Vector3D(double x, double y, double z): _x(x), _y(y), _z(z){}
		Vector3D() : _x(0.0), _y(0.0), _z(0.0){}
		double mag();
		Vector3D operator +(Vector3D aux);
		Vector3D operator -(Vector3D aux);
		void operator =(Vector3D aux);
		Vector3D operator ^(Vector3D aux); // Producto vectorial o cruz
		double operator *(Vector3D aux); // Producto punto
		Vector3D operator *(double aux); // Producto escalar
		void normalize();

};