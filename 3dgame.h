// #ifndef _3DGAME_H
// #define _3DGAME_H

#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <vector>
#include <irrKlang.h>

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
#include "keyboard_mouse.h"
#include "initialize.h"
#include "creategeometry.h"

using namespace std;


#ifndef PI
#define PI 3.141592653589
#endif

#ifndef DEG2RAD
#define DEG2RAD(deg) (deg * PI / 180)
#endif
