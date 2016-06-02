#include "OBJmodel3D.h"
#include <stdio.h>
#include <stdlib.h>
OBJmodel3D::OBJmodel3D()
{}
float OBJmodel3D::Max(float A, float B)
{
	if(A>B)
		return A;
	return B;
}
float OBJmodel3D::Abs(float A)
{
	if(A>0)
		return A;
	return -A;
}
void OBJmodel3D::Normalize()
{
	/*float distanceX = Abs(bb.max.x - bb.min.x);
	float distanceY = Abs(bb.max.y - bb.min.z);
	float distanceZ = Abs(bb.max.z - bb.min.z);
	float distanceMax = Max(Max(distanceX, distanceY),distanceZ);*/

	/*bb.min.x = bb.min.x/distanceMax;
	bb.min.y = bb.min.y/distanceMax;
	bb.min.z = bb.min.z/distanceMax;

	bb.max.x = bb.max.x/distanceMax;
	bb.max.y = bb.max.y/distanceMax;
	bb.max.z = bb.max.z/distanceMax;*/
	
	bb.centro.x = (bb.max.x + bb.min.x)/2;
	bb.centro.y = (bb.max.y + bb.min.y)/2;
	bb.centro.z = (bb.max.z + bb.min.z)/2;

	for(unsigned int i=0;i<this->Points.size();i++)
	{
		this->Points[i].x= (this->Points[i].x /*/distanceMax*/) - bb.centro.x;
		this->Points[i].y= (this->Points[i].y /*/distanceMax*/) - bb.centro.y;
		this->Points[i].z= (this->Points[i].z /*/distanceMax*/) - bb.centro.z;
	}
}
void OBJmodel3D::MakeBB(point P)
{
	if(P.x < bb.min.x)
		bb.min.x=P.x;
	if(P.y < bb.min.y)
		bb.min.y=P.y;
	if(P.z < bb.min.z)
		bb.min.z=P.z;
	if(P.x > bb.max.x)
		bb.max.x=P.x;
	if(P.y > bb.max.y)
		bb.max.y=P.y;
	if(P.z > bb.max.z)
		bb.max.z=P.z;
}
void OBJmodel3D::MakeModel(char * name)
{
	char c;
	char aux [1000];
	string line;
	bb.max.x=bb.max.y=bb.max.z=-10000000;
	bb.min.x=bb.min.y=bb.min.z=10000000;
	ifstream IN(name);
	c = IN.get();
	// recorriendo el archivo hasta la primera coordenada de vertice
	while(c != 'v')
	{
		IN.getline(aux,1000);
		c = IN.get();
	}
	// llenando los vertices X, Y, Z
	while(c == 'v' || c == '#')
	{
		if(c!='#')
		{
			point P;
			IN >> P.x >> P.y >> P.z;
			MakeBB(P);
			this->Points.push_back(P);

			
		}
		IN.getline(aux,1000);
		c = IN.get();
	}
	while(c!='v' && c!='f')
	{
		IN.getline(aux,1000);
		c = IN.get();
	}
	cout <<"pase"<< endl;
	if(c=='v')//si pasa por aca son X, Y, Z de textura
	{
		while(c == 'v' || c == '#')
		{
			if(c!='#')
			{
				c = IN.get();
				point P;
				IN >> P.x >> P.y >> P.z;
				this->Texture.push_back(P);
				
			}
			IN.getline(aux,1000);
			c = IN.get();
		}
		while(c!='v' && c!='f')
		{
			IN.getline(aux,1000);
			c = IN.get();
		}
		if(c=='v')//cooredenadas de las normales
		{
			while(c == 'v' || c == '#')
			{
				if(c!='#')
				{
					c = IN.get();
					point P;
					IN >> P.x >> P.y >> P.z;
					this->Normal.push_back(P);
					
				}
					IN.getline(aux,1000);
					c = IN.get();
			}
		}else
		{
				while(c == 'f' || c == '#')
				{
					if(c!='#')
					{
						face f;
						while(c !='\n')
						{
							int F;
							IN >> F;
							f.VV.push_back(F);
							c = IN.get();
							c = IN.get();
							if(c=='/')// normal
							{
								IN >> F;
								f.VN.push_back(F);
								//printf("%d__ ", F);
							}else
							{
								IN.unget();
								IN >> F;//textura
								f.VT.push_back(F);
								c = IN.get();
								//printf("%d__", F);
								IN >> F;//normal
								f.VN.push_back(F);
								//printf("%d__ ", F);
							}
							c=IN.get();
							if(c=='\n')
								cout << endl;
						}
						this->Faces.push_back(f);
					}
					c = IN.get();
				}
		}
	}else
	{
		while(c == 'f' || c == '#')
		{
			if(c!='#')
			{
				while(c !='\n')
				{
					int F;
					IN >> F;
					//this->Texture.push_back(P);
					//printf("%d__", F);
					c = IN.get();
					c = IN.get();
					if(c=='/')// normal
					{
						IN >> F;
						//printf("%d__ ", F);
					}else
					{
						IN.unget();
						IN >> F;
						c = IN.get();
						//printf("%d__", F);
						IN >> F;
						//printf("%d__ ", F);
					}
					c=IN.get();
					if(c=='\n')
						cout << endl;
				}				
			}
			//IN.getline(aux,1000);
			c = IN.get();
		}
	}
}
void OBJmodel3D::MakeModel2(char * name)
{
	int i=0;
	char c,c2;
	char aux [1000];
	string line;
	bb.max.x=bb.max.y=bb.max.z=-10000000;
	bb.min.x=bb.min.y=bb.min.z=10000000;
	ifstream IN(name);
	c = IN.get();
	while(!IN.eof())
	{
		//printf("antes del switch\n");
		if(c=='v')
		{
			c2=IN.get();
			if(c2==' ')// vertices
			{
				point P;
				IN >> P.x >> P.y >> P.z;
				MakeBB(P);
				this->Points.push_back(P);
			}
			if(c2=='t')// texturas
			{
				point P;
				IN >> P.x >> P.y;
				this->Texture.push_back(P);
				i++;
				//system("pause");
			}
			if(c2=='n')// normales
			{
				point P;
				IN >> P.x >> P.y >> P.z;
				this->Normal.push_back(P);
			}
		}
		if(c=='f')
		{
			//system("pause");
			face f;
			while(c !='\n')
			{
				int F;
				IN >> F;
				f.VV.push_back(F);
				c = IN.get();
				c = IN.get();
				if(c=='/')// normal
				{
					IN >> F;
					f.VN.push_back(F);
				}else
				{
					IN.unget();
					IN >> F;// textura 
					c = IN.get();
					f.VT.push_back(F);
					IN >> F;// normal
					f.VN.push_back(F);
				}
				c=IN.get();
				if(c=='\n')
					cout << endl;
			}
			this->Faces.push_back(f);
			IN.unget();
		}
		IN.getline(aux,1000);
		c = IN.get();
	}
}
void OBJmodel3D:: DrawModel()
{
	for(unsigned int i =0;i< this->Faces.size();i++)
	{
		glBegin(GL_POLYGON);
		//glColor3f(1.0,0.5,0.5);
		for(unsigned int j=0;j<this->Faces[i].VV.size();j++)
		{
			glTexCoord2d(this->Texture[Faces[i].VT[j]-1].x,this->Texture[Faces[i].VT[j]-1].y);
			glNormal3f(this->Normal[Faces[i].VN[j]-1].x,this->Normal[Faces[i].VN[j]-1].y,this->Normal[Faces[i].VN[j]-1].z);
			glVertex3f(this->Points[Faces[i].VV[j]-1].x,this->Points[Faces[i].VV[j]-1].y,this->Points[Faces[i].VV[j]-1].z);
		}
		glEnd();
	}
}