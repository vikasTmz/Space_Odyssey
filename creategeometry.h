#ifndef _CREATEGEOMETRY_H
#define _CREATEGEOMETRY_H

#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H
#include <FTGL/ftgl.h>

#include "SOIL.h"


extern float xcord,zcord,ycord;
extern int number_blocks;

void createcube(float ,float ,float ,float ,float,float ,int ,GLuint );
void createplayercube(float ,float ,float ,float );
void drawaxis();
void createpyramid ();
void createsky(GLuint );
void createRectangle (GLuint );
void createpoints(float ,float , float );

#endif