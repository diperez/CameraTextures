#define DEG2RAD 3.141592654f / 180.0
#pragma comment (lib, "lib/glut32.lib")
#include "Vector3D.h"
#include "glut.h"
class Camera2
{
	public:
		Vector3D Position;
		Vector3D ViewDir;
		bool changed;
		float RotX, RotY, RotZ;	
		Camera2();
		void Render ( void );	//executes some glRotates and a glTranslate command
								//Note: You should call glLoadIdentity before using Render
		void GetViewDir ( void );
		void Move ( Vector3D Direction );
		void RotateX ( float Angle );
		void RotateY ( float Angle );
		void RotateZ ( float Angle );
		void RotateXYZ ( Vector3D Angles );
		void MoveForwards ( float Distance );
		void StrafeRight ( float Distance );
};