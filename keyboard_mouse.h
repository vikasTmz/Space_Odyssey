#ifndef _KEYBOARDMOUSE_H
#define _KEYBOARDMOUSE_H

#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>

#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>


extern float triangle_rot_dir;
extern float rectangle_rot_dir ;
extern bool triangle_rot_status ;
extern bool rectangle_rot_status ;
extern float eyex,eyey,eyez;
extern float targetx,targety,targetz;
extern float yview,xview,zview,camerax,cameray,cameraz,camerayview,canglez,canglex,cameravz,cameravx;
extern int three_flag,one_flag,tower_flag,top_flag,Play_flag,Jump_flag,helicopter_flag;
extern float dotproductwx,dotproductwz,dotproductlx,dotproductlz,dotproductcx,dotproductcz;
extern GLfloat fov;

void quit(GLFWwindow *);
void keyboard (GLFWwindow* , int , int , int , int );
void mouseButton (GLFWwindow* , int , int , int );
void keyboardChar (GLFWwindow* , unsigned int );
void cursor_pos_callback(GLFWwindow *,double , double ); 
void mouseScroll(GLFWwindow *, double , double );

#endif