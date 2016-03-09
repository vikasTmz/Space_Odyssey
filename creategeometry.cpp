#ifndef _CREATEGEOMETRY_CPP
#define _CREATEGEOMETRY_CPP

#include "creategeometry.h"
#include "initialize.h"

using namespace std;


#ifndef PI
#define PI 3.141592653589
#endif

#ifndef DEG2RAD
#define DEG2RAD(deg) (deg * PI / 180)
#endif

extern Blocks Cubes[1000];
extern Blocks player;
extern Blocks ammo;

extern GLuint programID, fontProgramID, textureProgramID;
float xcord=0,zcord=0,ycord = 0;
int number_blocks=0;
extern VAO *screen_axis, * triangle ,*rectangle , *sky;



void createRectangle (GLuint textureID)
{

  static const GLfloat vertex_buffer_data [] = {
    -1.2,-1,0, 
    1.2,-1,0, 
    1.2, 1,0, 

    1.2, 1,0, 
    -1.2, 1,0, 
    -1.2,-1,0  
  };


  static const GLfloat texture_buffer_data [] = {
    0,1, 
    1,1, 
    1,0, 

    1,0, 
    0,0, 
    0,1  
  };


  rectangle = create3DTexturedObject(GL_TRIANGLES, 6, vertex_buffer_data, texture_buffer_data, textureID, GL_FILL);
}


void createcube(float length,float width,float height,float x,float z,float y,int number_blocks,GLuint textureID)
{
	Cubes[number_blocks].width = width*2;
  Cubes[number_blocks].height = height*2;
  Cubes[number_blocks].length = length*2;
  Cubes[number_blocks].x = x;
  Cubes[number_blocks].z = z;
  Cubes[number_blocks].y = y;

  static const GLfloat vertex_buffer_data [] = {

    -length,height,width, // vertex 1
    -length,-height,width, // vertex 2
    -length,-height,-width, // vertex 3

    -length,height,width, // vertex 1
    -length,-height,-width, // vertex 3
    -length,height,-width, //vertex 4

    //front face
    -length,height,width, // vertex 1
    length,height,width, // vertex 5
    -length,-height,width, // vertex 2

    length,height,width, // vertex 5
    -length,-height,width, // vertex 2
    length,-height,width, //vertex 6
    
    //top face
    -length,height,width, // vertex 1
    length,height,width, // vertex 5
    -length,height,-width, //vertex 4
    
    length,height,width, // vertex 5
    -length,height,-width, //vertex 4
    length,height,-width, // vertex 7

    //right face
    length,height,width, // vertex 5
    length,-height,width, //vertex 6
    length,height,-width, // vertex 7

    length,-height,width, //vertex 6
    length,height,-width, // vertex 7
    length,-height,-width, //vertex 8

    //Back face
    -length,-height,-width, // vertex 3
    -length,height,-width, //vertex 4
    length,height,-width, // vertex 7

    -length,-height,-width, // vertex 3
    length,-height,-width, //vertex 8
    length,height,-width, // vertex 7

    //Bottom face
    -length,-height,-width, // vertex 3
    length,-height,-width, //vertex 8
    length,-height,width, //vertex 6

    -length,-height,-width, // vertex 3
    -length,-height,width, // vertex 2
    length,-height,width //vertex 6
  };

  static const GLfloat texture_buffer_data [] = {
   0,1, 
   1,1, 
   1,0, 

   0,1,  
   1,0, 
   0,0, 
   
   1,1, 
   0,1, 
   1,0, 

   0,1,  
   1,0, 
   0,0, 

   1,1, 
   0,1, 
   1,0, 

   0,1,  
   1,0, 
   0,0, 

   1,1, 
   0,1, 
   1,0, 

   0,1,  
   1,0, 
   0,0, 

   0,1, 
   1,1,
   1,0, 

   0,1,  
   0,0, 
   1,0, 
   
   0,1, 
   1,1, 
   1,0, 

   0,1,  
   0,0, 
   1,0, 

 };

 Cubes[number_blocks].cube = create3DTexturedObject(GL_TRIANGLES, 36, vertex_buffer_data, texture_buffer_data, textureID, GL_FILL);
    // Cubes[number_blocks].cube = create3DObject(GL_TRIANGLE_FAN, 36, vertex_buffer_data, color_buffer_data, GL_FILL);
}


void drawaxis()
{
 static const GLfloat vertex_buffer_data [] = {
  0,0,0,
  20,0,0,

  0,0,0,
  -20,0,0,

  0,0,0,
  0,20,0,

  0,0,0,
  0,-20,0,

  0,0,0,
  0,0,20,

  0,0,0,
  0,0,-20,

};

static const GLfloat color_buffer_data [] = {
  1,1,1,
  1,1,1,

  1,1,1,
  1,1,1,

  1,1,1,
  1,1,1,

  1,1,1,
  1,1,1,

  1,1,1,
  1,1,1,

  1,1,1,
  1,1,1,

};
screen_axis = create3DObject(GL_LINES, 12, vertex_buffer_data, color_buffer_data, GL_LINE); 
}

void createpyramid ()
{

	static const GLfloat vertex_buffer_data [] = {
		0.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,

  // Right
		0.0f, 1.0f, 0.0f,
		1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, -1.0f,

  // Back
		0.0f, 1.0f, 0.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,

  // Left
		0.0f, 1.0f, 0.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f, 1.0f,
	};

	static const GLfloat color_buffer_data [] = {
	      1.0f, 0.0f, 0.0f,     // Red
  0.0f, 1.0f, 0.0f,     // Green
  0.0f, 0.0f, 1.0f,     // Blue
  1.0f, 0.0f, 0.0f,     // Red
  0.0f, 0.0f, 1.0f,     // Blue
  0.0f, 1.0f, 0.0f,     // Green
  1.0f, 0.0f, 0.0f,     // Red
  0.0f, 1.0f, 0.0f,     // Green
  0.0f, 0.0f, 1.0f,     // Blue
  1.0f,0.0f,0.0f,       // Red
  0.0f,0.0f,1.0f,       // Blue
  0.0f,1.0f,0.0f,       // Green
};



triangle = create3DObject(GL_TRIANGLES, 12, vertex_buffer_data, color_buffer_data, GL_LINE);
}


void createplayercube(float dime,float x,float z,float y)
{
  int i,k=0,j;
  GLfloat vertex_buffer_data[204410]={};
  GLfloat color_buffer_data[204410]={};
  player.width = player.height = player.length = dime*2;
  player.x = x;
  player.z = z;
  player.y = y;
  player.vy = player.vx = player.vz = 0;
  for (j = -90; j < 91; ++j)
  {
    for (i = -180; i < 181; ++i)
    {
      vertex_buffer_data[k] = dime*cos(DEG2RAD(i))*cos(DEG2RAD(j));
      color_buffer_data[k] = rand()%2-0.5;
      k++;
      vertex_buffer_data[k] = dime*sin(DEG2RAD(i))*cos(DEG2RAD(j));
      color_buffer_data[k] = rand()%2-0.5;
      k++;
      vertex_buffer_data[k] = dime*sin(DEG2RAD(j));
      color_buffer_data[k] = rand()%2-0.5;
      k++;
    }
  }
  player.cube = create3DObject(GL_LINES, 64800, vertex_buffer_data, color_buffer_data, GL_FILL);
}

void createpoints(float x ,float y , float z)
{
  ammo.x = x;
  ammo.z = z;
  ammo.y = y;

  static const GLfloat vertex_buffer_data [] = {
    0,0,0,
  };

  static const GLfloat color_buffer_data [] = {
    1,1,1,
  };
  ammo.cube = create3DObject(GL_POINTS, 1, vertex_buffer_data, color_buffer_data, GL_FILL); 
}



void createsky(GLuint textureID)
{
  float length= 200;
  float height= 200;
  float width = 200;
  static const GLfloat vertex_buffer_data [] = {

    -length,height,width, // vertex 1
    -length,-height,width, // vertex 2
    -length,-height,-width, // vertex 3

    -length,height,width, // vertex 1
    -length,-height,-width, // vertex 3
    -length,height,-width, //vertex 4

    //front face
    -length,height,width, // vertex 1
    length,height,width, // vertex 5
    -length,-height,width, // vertex 2

    length,height,width, // vertex 5
    -length,-height,width, // vertex 2
    length,-height,width, //vertex 6
    
    //top face
    -length,height,width, // vertex 1
    length,height,width, // vertex 5
    -length,height,-width, //vertex 4
    
    length,height,width, // vertex 5
    -length,height,-width, //vertex 4
    length,height,-width, // vertex 7

    //right face
    length,height,width, // vertex 5
    length,-height,width, //vertex 6
    length,height,-width, // vertex 7

    length,-height,width, //vertex 6
    length,height,-width, // vertex 7
    length,-height,-width, //vertex 8

    //Back face
    -length,-height,-width, // vertex 3
    -length,height,-width, //vertex 4
    length,height,-width, // vertex 7

    -length,-height,-width, // vertex 3
    length,-height,-width, //vertex 8
    length,height,-width, // vertex 7

    //Bottom face
    -length,-height,-width, // vertex 3
    length,-height,-width, //vertex 8
    length,-height,width, //vertex 6

    -length,-height,-width, // vertex 3
    -length,-height,width, // vertex 2
    length,-height,width //vertex 6
  };

  static const GLfloat texture_buffer_data [] = {
   0,1, 
   1,1, 
   1,0, 

   0,1,  
   1,0, 
   0,0, 
   
   1,1, 
   0,1, 
   1,0, 

   0,1,  
   1,0, 
   0,0, 

   1,1, 
   0,1, 
   1,0, 

   0,1,  
   1,0, 
   0,0, 

   1,1, 
   0,1, 
   1,0, 

   0,1,  
   1,0, 
   0,0, 

   0,1, 
   1,1,
   1,0, 

   0,1,  
   0,0, 
   1,0, 
   
   0,1, 
   1,1, 
   1,0, 

   0,1,  
   0,0, 
   1,0, 

 };

 sky = create3DTexturedObject(GL_TRIANGLES, 36, vertex_buffer_data, texture_buffer_data, textureID, GL_FILL);
    // Cubes[number_blocks].cube = create3DObject(GL_TRIANGLE_FAN, 36, vertex_buffer_data, color_buffer_data, GL_FILL);
}

#endif