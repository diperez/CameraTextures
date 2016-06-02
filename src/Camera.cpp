#include "Camera.h"
#include <stdio.h>
Camera::Camera()
{
	Reset();
}
Camera::~Camera() 
{

}
void Camera::Reset()
{
	printf("cree la camara\n");
	Position = Vector3D(0.0, 0.0, 0.0);
	Along = Vector3D(1.0, 0.0, 0.0);
	Up = Vector3D(0.0, 1.0, 0.0);
	Forward = Vector3D(0.0, 0.0, -1.0);
	Update();

}
Vector3D Camera::GetPosition()
{
	return Position;
}
void Camera::Update() 
{
	double x = Along * Position;
	double y = Up * Position;
	double z = Forward * Position;
	float ViewMatrix[4][4];
	ViewMatrix[0][0] = Along._x;
	ViewMatrix[0][1] = Up._x;
	ViewMatrix[0][2] = -Forward._x;
	ViewMatrix[0][3] = 0.0;

	ViewMatrix[1][0] = Along._y;
	ViewMatrix[1][1] = Up._y;
	ViewMatrix[1][2] = -Forward._y;
	ViewMatrix[1][3] = 0.0;

	ViewMatrix[2][0] = Along._z;
	ViewMatrix[2][1] = Up._z;
	ViewMatrix[2][2] = -Forward._z;
	ViewMatrix[2][3] = 0.0;

	ViewMatrix[3][0] = -x;
	ViewMatrix[3][1] = -y;
	ViewMatrix[3][2] = z;
	ViewMatrix[3][3] = 1.0;

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf((GLfloat *)&ViewMatrix);

}

void Camera::Yaw(float theta) 
{
	Along = Along * cos(theta * DEG2RAD)+ Forward * sin(theta * DEG2RAD);
	Along.normalize();
	Forward = Along^Up * -1.0;
	Update();
}

void Camera::Pitch(GLfloat theta) {
	Forward = Forward * cos(theta * DEG2RAD) + Up * sin(theta * DEG2RAD);
	Forward.normalize();
	Up = Forward^Along * -1.0;
	Update();
}

void Camera::Walk(float delta, bool Wall[4]) {
	printf("caminando\n");
	printf("posicion anterior %f, %f, %f\n", Position._x,Position._y,Position._z);
    Position =  Position - Vector3D(Forward._x *!(Wall[0] && Forward._x * delta > 0.0 ||
                Wall[1] && Forward._x * delta < 0.0),
                0.0, Forward._z *
                !(Wall[2] && Forward._z * delta > 0.0 ||
                Wall[3] && Forward._z * delta < 0.0))
                * delta;
	printf("posicion despues %f, %f, %f\n", Position._x,Position._y,Position._z);
	Update();
}

void Camera::Strafe(GLfloat delta, bool Wall[4]) 
{
	Position = Position - Vector3D(Along._x *
				!(Wall[0] && Along._x * delta > 0.0 ||
				Wall[1] && Along._x * delta < 0.0),
				0.0, Along._z *
				!(Wall[2] && Along._z * delta > 0.0 ||
				Wall[3] && Along._z * delta < 0.0))
			  * delta;
	Update();
}





