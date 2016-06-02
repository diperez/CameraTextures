#define DEG2RAD 3.141592654f / 180.0
#pragma comment (lib, "lib/glut32.lib")
#include "Vector3D.h"
#include "glut.h"
class Camera
{
	public:
		Vector3D Position;
		Vector3D Along;
		Vector3D Up;
		Vector3D Forward;
		Camera();
		~Camera();
		Vector3D GetPosition();
		void Reset();
		void Update();
		void Pitch(float theta);
		void Yaw(float theta);
		//void Roll(float theta);
		void Walk(float delta, bool Wall[4]);
		void Strafe(float delta, bool Wall[4]);
		void Fly(float delta);

};