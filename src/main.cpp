/*
	Created by Diego Perez and Fernando Crema
*/

#pragma comment (lib, "lib/glut32.lib")
#pragma comment (lib, "lib/glew32.lib")

#include "GL/glew.h"
#include "GL/glut.h"
#include "OBJmodel3D.h"
#include <windows.h>	
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

GLuint tex_paredes,tex_bar, tex_piso, tex_techo, tex_mesa, tex_lampara,tex_silla,tex_vaso, tex_ball1, tex_ball2,escena,tex_sobremesa;
OBJmodel3D * BAR = new OBJmodel3D();
OBJmodel3D * MESA = new OBJmodel3D();
OBJmodel3D * LAMPARA = new OBJmodel3D();
OBJmodel3D * SILLA1 = new OBJmodel3D();
OBJmodel3D * SILLA2 = new OBJmodel3D();
OBJmodel3D * VASO1 = new OBJmodel3D();
OBJmodel3D * VASO2 = new OBJmodel3D();
OBJmodel3D * BALL1 = new OBJmodel3D();
OBJmodel3D * BALL2 = new OBJmodel3D();
Camera2 C = Camera2();
static char s[25];
float angle = 0.0;
float lx,ly;
int w,h,frame=0,timebase=0;
float tAct,fps;
GLfloat specReflection[] = { 0.8f, 0.8f, 0.8f, 1.0f };
GLfloat LightAmbient[]=		{ 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat LightDiffuse[]=		{ 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightPosition[]=	{ 0.0f, 0.0f, 2.0f, 1.0f };

GLfloat light_ambient[] = {0.0f,0.0f,0.0f,0.0f};
GLfloat light_diffuse[] = {0.0f,1.0f,0.0f,0.0f};
GLfloat light_specular[] = {1.0f,1.0f,1.0f,0.0f};
GLfloat light_position[] = {0.0f, 0.0f, 2.0f,0.0f};

GLfloat light_ambient2[] = {0.0f,0.0f,0.0f,0.0f};
GLfloat light_diffuse2[] = {0.0f,1.0f,0.0f,0.0f};
GLfloat light_specular2[] = {1.0f,1.0f,1.0f,0.0f};
GLfloat light_position2[] = {0.0f, 0.0f, 3.0f,0.0f};

GLfloat light_ambient3[] = {1.0f,0.0f,0.0f,0.0f};
GLfloat light_diffuse3[] = {1.0f,1.0f,0.0f,0.0f};
GLfloat light_specular3[] = {1.0f,0.0f,1.0f,0.0f};
GLfloat light_position3[] = {-1.4482, 7.037451, -0.181357,0.0f};

GLfloat light_ambient4[] = {0.0f,1.0f,0.0f,0.0f};
GLfloat light_diffuse4[] = {0.0f,1.0f,1.0f,0.0f};
GLfloat light_specular4[] = {0.0f,1.0f,1.0f,0.0f};
GLfloat light_position4[] = {-1.00246, -2.160, 2.098257,0.0f};


float pos[]={-2.0f, 0.0f, 0.0f};
float pos2[]={-2.0f, 0.3f, 0.0f};
float x_pos =0.0, x_pos2 =0.0;

GLuint LoadTexture( const char * filename, int width, int height ){

	GLuint texture;
	unsigned char *data;
	FILE *file;

	file = fopen( filename, "rb" );
    if ( file == NULL )  return 0;
	data = (unsigned char *)malloc( width * height * 3 );
    fread( data, width * height * 3, 1, file );
    fclose( file );
	//lei el archivo

	glGenTextures( 1, &texture );
	glBindTexture( GL_TEXTURE_2D, texture );
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data );
	free( data );
	return texture;

}

void FreeTexture( GLuint texture )
{
  glDeleteTextures( 1, &texture ); 
}


void cube(){

}

void init()
{

	glLightfv(GL_LIGHT0,GL_AMBIENT,light_ambient);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,light_diffuse);
	glLightfv(GL_LIGHT0,GL_SPECULAR,light_specular);
	glLightfv(GL_LIGHT0,GL_POSITION,light_position);

	glLightfv(GL_LIGHT1,GL_AMBIENT,light_ambient2);
	glLightfv(GL_LIGHT1,GL_DIFFUSE,light_diffuse2);
	glLightfv(GL_LIGHT1,GL_SPECULAR,light_specular2);
	glLightfv(GL_LIGHT1,GL_POSITION,light_position2);

	glLightfv(GL_LIGHT2, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, LightDiffuse);	
	glLightfv(GL_LIGHT2, GL_POSITION,LightPosition);

	glLightfv(GL_LIGHT3,GL_AMBIENT,light_ambient3);
	glLightfv(GL_LIGHT3,GL_DIFFUSE,light_diffuse3);
	glLightfv(GL_LIGHT3,GL_SPECULAR,light_specular3);
	glLightfv(GL_LIGHT3,GL_POSITION,light_position3);

	glLightfv(GL_LIGHT4,GL_AMBIENT,light_ambient4);
	glLightfv(GL_LIGHT4,GL_DIFFUSE,light_diffuse4);
	glLightfv(GL_LIGHT4,GL_SPECULAR,light_specular4);
	glLightfv(GL_LIGHT4,GL_POSITION,light_position4);

	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);
	glEnable(GL_LIGHT4);


	glMaterialfv(GL_FRONT, GL_SPECULAR, specReflection);
	glMateriali(GL_FRONT, GL_SHININESS, 10.0f);

	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);

	glColor4f(1.0f, 1.0f, 1.0f, 0.5);					// Full Brightness.  50% Alpha
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);

	escena = glGenLists(1);
	glNewList (escena, GL_COMPILE);

		tex_piso = LoadTexture( "Textures/piso.raw", 512, 256 );
		glBindTexture( GL_TEXTURE_2D, tex_piso );
		glBegin (GL_QUADS);//piso :D
		glTexCoord2d(0.0,0.0); glVertex3f(4.310728, -3.476887, -6.153112);
		glTexCoord2d(1.0,0.0); glVertex3f(-7.300507, -3.476887, -6.153114);
		glTexCoord2d(1.0,1.0); glVertex3f(-7.300510, -3.476887, 5.458124);
		glTexCoord2d(0.0,1.0); glVertex3f(4.310728, -3.476887, 5.458126);
		glEnd();
		tex_techo = LoadTexture( "Textures/techo.raw", 512, 256 );
		glBindTexture( GL_TEXTURE_2D, tex_techo );
		glBegin (GL_QUADS);//techo :D
		glTexCoord2d(0.0,0.0); glVertex3f(4.410730, 8.134349, -6.153110);
		glTexCoord2d(1.0,0.0); glVertex3f(4.410724, 8.134350, 5.458128);
		glTexCoord2d(1.0,1.0); glVertex3f(-7.500512, 8.134350, 5.458123);
		glTexCoord2d(0.0,1.0); glVertex3f(-7.500509, 8.134349, -6.153112);
		glEnd();

		tex_paredes = LoadTexture( "Textures/paredes.raw", 512, 256 );
		glBindTexture( GL_TEXTURE_2D, tex_paredes );

		glBegin (GL_QUADS);//latreral derecho :D
		glTexCoord2d(0.0,0.0); glVertex3f(4.310728, -3.476887, -6.153112);
		glTexCoord2d(1.0,0.0); glVertex3f(4.310728, -3.476887, 5.458126);
		glTexCoord2d(1.0,1.0); glVertex3f(4.310724, 8.134350, 5.458128);
		glTexCoord2d(0.0,1.0); glVertex3f(4.310730, 8.134349, -6.153110);
		glEnd();

		glBegin (GL_QUADS);//adelante
		glTexCoord2d(0.0,0.0); glVertex3f(4.310728, -3.476887, 5.458126);
		glTexCoord2d(1.0,0.0); glVertex3f(-7.300510, -3.476887, 5.458124);
		glTexCoord2d(1.0,1.0); glVertex3f(-7.300512, 8.134350, 5.458123);
		glTexCoord2d(0.0,1.0); glVertex3f(4.310724, 8.134350, 5.458128);
		glEnd();

		glBegin (GL_QUADS);//lateral izq
		glTexCoord2d(0.0,0.0); glVertex3f(-7.300510, -3.476887, 5.458124);
		glTexCoord2d(1.0,0.0); glVertex3f(-7.300507, -3.476887, -6.153114);
		glTexCoord2d(1.0,1.0); glVertex3f(-7.300509, 8.134349, -6.153112);
		glTexCoord2d(0.0,1.0); glVertex3f(-7.300512, 8.134350, 5.458123);
		glEnd();

		glBegin (GL_QUADS);//atraz
		glTexCoord2d(0.0,0.0); glVertex3f(-7.300507, -3.476887, -6.153114);
		glTexCoord2d(1.0,0.0); glVertex3f(4.310728, -3.476887, -6.153112);
		glTexCoord2d(1.0,1.0); glVertex3f(4.310730, 8.134349, -6.153110);
		glTexCoord2d(0.0,1.0); glVertex3f(-7.300509, 8.134349, -6.153112);
		glEnd();

		tex_bar = LoadTexture( "Textures/mesa.raw", 512,256 );
		glBindTexture( GL_TEXTURE_2D, tex_bar );
		BAR->DrawModel();


		//glEnable(GL_TEXTURE_GEN_S);
		//glEnable(GL_TEXTURE_GEN_T);
		tex_mesa = LoadTexture( "Textures/mesa.raw", 512,512 );
		glBindTexture( GL_TEXTURE_2D, tex_mesa );
		MESA->DrawModel();

		
		tex_sobremesa = LoadTexture( "Textures/sobremesa.raw", 512,512 );
		glBindTexture( GL_TEXTURE_2D, tex_sobremesa );
		glBegin (GL_QUADS);
		glNormal3f(-0.000000, -1.000000, 0.000000);
		glTexCoord2d(0.0,0.0); glVertex3f(3.320246, -1.160, 0.098257);
		glTexCoord2d(0.0,1.0); glVertex3f(-5.858867, -1.160, 0.098256);
		glTexCoord2d(1.0,1.0); glVertex3f(-5.858870, -1.160, 3.765110);
		glTexCoord2d(1.0,0.0); glVertex3f(3.320246, -1.160, 3.765111);
		glEnd();

		glEnable(GL_BLEND);	
		glDisable(GL_CULL_FACE);
		tex_lampara = LoadTexture( "Textures/lampara.raw", 512,512 );
		glBindTexture( GL_TEXTURE_2D, tex_lampara );
		LAMPARA->DrawModel();
		glDisable(GL_BLEND);
		glEnable(GL_CULL_FACE);

		tex_silla = LoadTexture( "Textures/silla2.raw", 256,256 );
		glBindTexture( GL_TEXTURE_2D, tex_silla );
		SILLA1->DrawModel();
		SILLA2->DrawModel();

		tex_vaso = LoadTexture( "Textures/vaso.raw", 256,256 );
		glBindTexture( GL_TEXTURE_2D, tex_vaso );
		glDisable(GL_CULL_FACE);
		VASO1->DrawModel();
		VASO2->DrawModel();
		glEnable(GL_CULL_FACE);

		tex_ball1 = LoadTexture( "Textures/ball1.raw", 256,256 );
		glBindTexture( GL_TEXTURE_2D, tex_ball1 );
		BALL1->DrawModel();
		tex_ball2 = LoadTexture( "Textures/ball8.raw", 256,256 );
		glBindTexture( GL_TEXTURE_2D, tex_ball2 );
		BALL2->DrawModel();
		//glDisable(GL_TEXTURE_GEN_S);
		//glDisable(GL_TEXTURE_GEN_T);
	glEndList();
	//glEnable(GL_DEPTH_TEST);

}
void click (int boton, int estado, int x, int y)
{
}
void processSpecialKeys(int key, int x, int y) {
	
}

void pasivo (int x, int y)
{
	C.RotateX((GLfloat)(y-ly)*-0.1);
	C.RotateY((GLfloat)(x-lx)*-0.1);
	lx=x;
	ly=y;
	if(x>w/2+10 || y>h/2+10 || x<w/2-10 || y<h/2-10){
		glutWarpPointer(w/2, h/2);
		lx=w/2;
		ly=h/2;
	}
	
}
void teclado (unsigned char key, int x, int y)
{
	if(key == 'w')
	{
		C.MoveForwards( -0.1 ) ;
		glutPostRedisplay();
	}
	if(key == 's')
	{
		C.MoveForwards( 0.1 ) ;
		glutPostRedisplay();
	}
	if(key == 'a')
	{
		C.StrafeRight(-0.1);
		glutPostRedisplay();
	}

	if(key == 'd')
	{
		C.StrafeRight(0.1);
		glutPostRedisplay();
	}
	if(key == 27)
	{
		exit(0);
	}
	if(key == 49)
	{
		glEnable(GL_LIGHT0);
	}
	if(key == 50)
	{
		glDisable(GL_LIGHT0);
	}
	if(key == 51)
	{
		glEnable(GL_LIGHT1);
	}
	if(key == 52)
	{
		glDisable(GL_LIGHT1);
	}
	if(key == 53)
	{
		glEnable(GL_LIGHT3);
	}
	if(key == 54)
	{
		glDisable(GL_LIGHT3);
	}
	if(key == 55)
	{
		glEnable(GL_LIGHT4);
	}
	if(key == 56)
	{
		glDisable(GL_LIGHT4);
	}
	if(key == 57)
	{
		glEnable(GL_LIGHT2);
	}
	if(key == 48)
	{
		glDisable(GL_LIGHT2);
	}

	if(key == 102)
	{
		glShadeModel(GL_FLAT);
	}
	if(key == 103)
	{
		glShadeModel(GL_SMOOTH);
	}
}
void movimiento (int x, int y)
{

}
void Idle(){

	tAct = glutGet(GLUT_ELAPSED_TIME);

	x_pos+=0.05;
	x_pos2-=0.05;
	light_position2[0]=sin(x_pos)*3;
	light_position2[0]=cos(x_pos)*3;
	glLightfv(GL_LIGHT1,GL_POSITION,light_position2);
	pos[0]=sin(x_pos)*3;
	pos[2]=cos(x_pos)*3;

	pos2[0]=sin(x_pos2)*4;
	pos2[2]=cos(x_pos2)*4;

	light_position[0]=sin(x_pos2)*4;
	light_position[0]=cos(x_pos2)*4;
	glLightfv(GL_LIGHT0,GL_POSITION,light_position);

	glutPostRedisplay();

	frame++;
	if (tAct - timebase > 1000) {
		
		fps = frame*(tAct-timebase)/1000.0;
		timebase = tAct;		
		frame = 0;
		glutPostRedisplay();
		memset(s,0,25);
		sprintf(s,"Tarea 4- fps: %f",fps);
		glutSetWindowTitle(s);
	}
}

void render (){

	glClearColor (1.0,1.0,1.0,1.0);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity(); 
	//gluLookAt (0.0, 0.0, 20.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	//cuad();
	C.Render();
	glEnable( GL_TEXTURE_2D );
	//glEnable(GL_TEXTURE_GEN_S);
	//glEnable(GL_TEXTURE_GEN_T);
	glCallList(escena);
	glPushMatrix();
	glTranslatef(pos[0],pos[1],pos[2]);
	glColor3f(0.0f,0.0f,0.0f);
	glutSolidSphere(0.1,100,100);
	glColor3f(1.0f,1.0f,1.0f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(pos2[0],pos2[1],pos2[2]);
	glColor3f(0.0f,0.0f,0.0f);
	glutSolidSphere(0.1,100,100);
	glColor3f(1.0f,1.0f,1.0f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.4482, 7.037451, -0.181357);
	glColor3f(0.0f,0.0f,0.0f);
	glutSolidSphere(0.1,100,100);
	glColor3f(1.0f,1.0f,1.0f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.00246, -2.160, 2.098257);
	glColor3f(0.0f,0.0f,0.0f);
	glutSolidSphere(0.1,100,100);
	glColor3f(1.0f,1.0f,1.0f);
	glPopMatrix();
	//FreeTexture(texture);


    glutSwapBuffers();

}

void reshape (int W, int H){

	glViewport (0, 0, (GLsizei)W, (GLsizei)H);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective (45, (GLfloat)W / (GLfloat)H, 1.0, 100.0);
    glMatrixMode (GL_MODELVIEW);
	w=W;
	h=H;
}

int main (int argc, char *argv[]){

	BAR->MakeModel2("Archivos_OBJ/bar.obj");
	MESA->MakeModel2("Archivos_OBJ/mesa2.obj");
	LAMPARA->MakeModel2("Archivos_OBJ/lampara.obj");
	SILLA1->MakeModel2("Archivos_OBJ/silla1.obj");
	SILLA2->MakeModel2("Archivos_OBJ/silla2.obj");
	VASO1->MakeModel2("Archivos_OBJ/vaso1.obj");
	VASO2->MakeModel2("Archivos_OBJ/vaso2.obj");
	BALL1->MakeModel2("Archivos_OBJ/ball1.obj");
	BALL2->MakeModel2("Archivos_OBJ/ball2.obj");
	glutInit(&argc, argv);
	w=800;
	h=600;
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition (0, 0);
	glutInitWindowSize (800, 600);
	glutCreateWindow("Tarea 4");
	init();
	glutDisplayFunc(render);
	glutIdleFunc(Idle);
	glutWarpPointer(w/2,h/2);
	glutSetCursor(GLUT_CURSOR_NONE);

	glutMotionFunc(movimiento);
	glutMouseFunc(click);
	glutKeyboardFunc(teclado);
	glutSpecialFunc(processSpecialKeys); 
	glutPassiveMotionFunc(pasivo);
	glutReshapeFunc (reshape);

	glutMainLoop();
	return 0;

}