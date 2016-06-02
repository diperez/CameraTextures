#include "Camera2.h"

Camera2 :: Camera2()
{
	Position = Vector3D(0.0, 2.0,4.0);
	ViewDir = Vector3D(0.0, 0.0, -1.0);
	changed = false;
	RotX=RotY=RotZ=0.0;
}
void Camera2::GetViewDir()
{
	Vector3D aux, aux2;
	aux._x = cos( (RotY + 90.0) * DEG2RAD);
	aux._z = -sin( (RotY + 90.0) * DEG2RAD);
	double cosX = cos (RotX * DEG2RAD);
	aux2._x = aux._x * cosX;
	aux2._z = aux._z * cosX;
	aux2._y = sin(RotX * DEG2RAD);
	ViewDir = aux2;
}
void Camera2::Move(Vector3D Direction)
{
	Position = Position + Direction;
}
void Camera2::RotateX(float Angle)
{
	RotX += Angle;
	if(RotX>90.0){ RotX=90.0;Angle=0.0;}
	if(RotX<-90.0){RotX=-90.0;Angle=0.0;}
	changed = true;
}
void Camera2::RotateY(float Angle)
{
	RotY += Angle;
	changed = true;
}

void Camera2::MoveForwards( float Distance )
{
	if (changed) 
		GetViewDir();
	Vector3D MoveVector;
	MoveVector._x = ViewDir._x * -Distance;
	MoveVector._y = ViewDir._y * -Distance;
	MoveVector._z = ViewDir._z * -Distance;
	Position = Position + MoveVector;

	if(Position._z > 4.3)
		Position._z =4.3;
	if(Position._z < -4.8)
		Position._z =-4.8;
	if(Position._x > 3.2)
		Position._x =3.2;
	if(Position._x < -6.2)
		Position._x =-6.2;
	if(Position._y > 7.0)
		Position._y =7.0;
	if(Position._y < -2.4)
		Position._y =-2.4;

}

void Camera2::StrafeRight ( float Distance )
{
	if (changed)
		GetViewDir();
	Vector3D MoveVector;
	MoveVector._z = -ViewDir._x * -Distance;
	MoveVector._y = 0.0;
	MoveVector._x = ViewDir._z * -Distance;
	Position = Position + MoveVector;

	if(Position._z > 4.3)
		Position._z =4.3;
	if(Position._z < -4.8)
		Position._z =-4.8;
	if(Position._x > 3.2)
		Position._x =3.2;
	if(Position._x < -6.2)
		Position._x =-6.2;
	if(Position._y > 7.0)
		Position._y =7.0;
	if(Position._y < -2.4)
		Position._y =-2.4;
}
void Camera2::Render()
{
	glRotatef(-RotX , 1.0, 0.0, 0.0);
	glRotatef(-RotY , 0.0, 1.0, 0.0);
	glRotatef(-RotZ , 0.0, 0.0, 1.0);
	glTranslatef( -Position._x, -Position._y, -Position._z );
}