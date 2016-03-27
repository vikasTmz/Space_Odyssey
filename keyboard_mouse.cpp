#ifndef _KEYBOARDMOUSE_CPP
#define _KEYBOARDMOUSE_CPP

#include "keyboard_mouse.h"
#include "initialize.h"
#define GLFW_MOD_SHIFT   0x0001

using namespace std;

float triangle_rot_dir = 1;
float rectangle_rot_dir = -1;
bool triangle_rot_status = true;
bool rectangle_rot_status = true;
float eyex=15,eyey=7,eyez=24,player_speed=0.015;
float targetx=0,targety=0,targetz=0;
float yview=0,zview=0,xview=0,camerax=10,cameraz=20,cameray=10,canglex=0,canglez=0,cameravz=0,cameravx=0;
float dotproductwx=0,dotproductwz=0,dotproductlx=0,dotproductlz=0,dotproductcz=0,dotproductcx=0;
GLfloat fov = 45.0f;
extern Blocks player;
int three_flag =1, one_flag=0,tower_flag=0,top_flag=0,Play_flag=0,Jump_flag=0,helicopter_flag=0;
extern GLMatrices Matrices;

void quit(GLFWwindow *window)
{
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

void keyboard (GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_RELEASE) {
		switch (key) {
			case GLFW_KEY_G:
			player_speed=0.015;
			break;
			case GLFW_KEY_A:
			player.vz = 0;
			player.vx = 0;
			break;
			case GLFW_KEY_W:
			player.vz = 0;
			player.vx = 0;
			break;
			case GLFW_KEY_S:
			player.vz = 0;
			player.vx = 0;
			break;
			case GLFW_KEY_D:
			player.vz = 0;
			player.vx = 0;
			break;
			case GLFW_KEY_UP:
			if(helicopter_flag==1)
			{
				cameravz = 0;
				cameravx = 0;
			}
			break;
			case GLFW_KEY_DOWN:
			if(helicopter_flag==1)
			{
				cameravz = 0;
				cameravx = 0;
			}
			break;
			default:
			break;
		}
	}
	else if(action == GLFW_REPEAT){
		switch (key) {
			case GLFW_KEY_UP:
			if(helicopter_flag==0){
				yview += 0.02;
				if(yview > 4)
					yview=4;}
			else if(helicopter_flag==1)
			{
				cameravz = player_speed*dotproductcz;
				cameravx = player_speed*dotproductcx;
			}
			break;
			case GLFW_KEY_DOWN:
			if(helicopter_flag==0){
				yview -= 0.02;
				if(yview < -1)
					yview=-1;}
			else if(helicopter_flag==1)
			{
				cameravz = -1*player_speed*dotproductcz;
				cameravx = -1*player_speed*dotproductcx;
			}
			break;
			case GLFW_KEY_RIGHT:
			if(one_flag==1)
			{
				xview += 1;
				zview += 1;
			}
			if(three_flag==1)
			{
				xview -= 1;
				zview -= 1;
			}
			if(helicopter_flag==1)
			{
				canglex += 1;
				canglez += 1;
			}
			break;
			case GLFW_KEY_LEFT:
			if(one_flag==1)
			{
				xview -= 1;
				zview -= 1;
			}
			if(three_flag==1)
			{
				xview += 1;
				zview += 1;
			}
			if(helicopter_flag==1)
			{
				canglez -= 1;
				canglex -= 1;
			}
			break;
			case GLFW_KEY_A:
			player.vz = player_speed*dotproductlz;
			player.vx = player_speed*dotproductlx;
			break;
			case GLFW_KEY_W:
			player.vz = player_speed*dotproductwz;
			player.vx = player_speed*dotproductwx;
			break;
			case GLFW_KEY_S:
			player.vz = -1*player_speed*dotproductwz;
			player.vx = -1*player_speed*dotproductwx;
			break;
			case GLFW_KEY_D:
			player.vz = -1*player_speed*dotproductlz;
			player.vx = -1*player_speed*dotproductlx;
			break;
			default:
			case GLFW_KEY_Z:
			cameray += 0.03;
			break;
			case GLFW_KEY_X:
			cameray -= 0.03;
			break;
			break;
		}
	}
	else if (action == GLFW_PRESS) {
		switch (key) {
			case GLFW_KEY_ESCAPE:
			quit(window);
			break;
			case GLFW_KEY_G:
			player_speed=0.03;
			break;
			case GLFW_KEY_A:
			player.vz = player_speed*dotproductlz;
			player.vx = player_speed*dotproductlx;
			break;
			case GLFW_KEY_W:
			player.vz = player_speed*dotproductwz;
			player.vx = player_speed*dotproductwx;
			break;
			case GLFW_KEY_S:
			player.vz = -1*player_speed*dotproductwz;
			player.vx = -1*player_speed*dotproductwx;
			break;
			case GLFW_KEY_D:
			player.vz = -1*player_speed*dotproductlz;
			player.vx = -1*player_speed*dotproductlx;
			break;
			case GLFW_KEY_SPACE:
			if(Jump_flag==0)	
				player.vy = 0.15;
			Jump_flag=1;
			break;
			case GLFW_KEY_P:
			Play_flag=1;
			break;
			case GLFW_KEY_UP:
			yview += 0.02;
			if(yview > 4)
				yview=4;
			if(helicopter_flag==1)
			{
				cameravz = player_speed*dotproductcz;
				cameravx = player_speed*dotproductcx;
			}
			break;
			case GLFW_KEY_DOWN:
			yview -= 0.02;
			if(yview < -1)
				yview=-1;
			if(helicopter_flag==1)
			{
				cameravz = -1*player_speed*dotproductcz;
				cameravx = -1*player_speed*dotproductcx;
			}
			break;
			case GLFW_KEY_RIGHT:
			if(one_flag==1)
			{
				xview += 1;
				zview += 1;
			}
			if(three_flag==1)
			{
				xview -= 1;
				zview -= 1;
			}
			if(helicopter_flag==1)
			{
				canglez += 1;
				canglex += 1;
			}
			break;
			case GLFW_KEY_LEFT:
			if(one_flag==1)
			{
				xview -= 1;
				zview -= 1;
			}
			if(three_flag==1)
			{
				xview += 1;
				zview += 1;
			}
			if(helicopter_flag==1)
			{
				canglez -= 1;
				canglex -= 1;
			}
			break;
			case GLFW_KEY_3:
			three_flag=1;
			one_flag=0;
			tower_flag=0;
			top_flag=0;
			helicopter_flag=0;
			break;
			case GLFW_KEY_1:
			three_flag=0;
			one_flag=1;
			tower_flag=0;
			top_flag=0;
			helicopter_flag=0;
			break;
			case GLFW_KEY_8:
			three_flag=0;
			one_flag=0;
			tower_flag=1;
			top_flag=0;
			helicopter_flag=0;
			break;
			case GLFW_KEY_9:
			three_flag=0;
			one_flag=0;
			tower_flag=0;
			top_flag=1;
			helicopter_flag=0;
			break;
			case GLFW_KEY_4:
			three_flag=0;
			one_flag=0;
			tower_flag=0;
			top_flag=0;
			helicopter_flag=1;
			break;
			case GLFW_KEY_Z:
			cameray += 0.03;
			break;
			case GLFW_KEY_X:
			cameray -= 0.03;
			break;
			default:
			break;
		}
	}
}

/* Executed for character input (like in text boxes) */
void keyboardChar (GLFWwindow* window, unsigned int key)
{
	switch (key) {
		case 'Q':
		case 'q':
		quit(window);
		break;
		default:
		break;
	}
}

/* Executed when a mouse button is pressed/released */
void mouseButton (GLFWwindow* window, int button, int action, int mods)
{
	switch (button) {
		case GLFW_MOUSE_BUTTON_LEFT:
		if (action == GLFW_RELEASE)
			triangle_rot_dir *= -1;
		break;
		case GLFW_MOUSE_BUTTON_RIGHT:
		if (action == GLFW_RELEASE) {
			rectangle_rot_dir *= -1;
		}
		break;
		default:
		break;
	}
}

void cursor_pos_callback(GLFWwindow *window,double xpos, double ypos)   
{

	if(xpos > 700)
	{
		if(one_flag==1)
		{
			xview += 1;
			zview += 1;
		}
		if(three_flag==1)
		{
			xview -= 1;
			zview -= 1;
		}
		if(helicopter_flag==1)
		{
			canglex +=1;
			canglez +=1;
		}
	}
	if(xpos < 700)
	{
		if(three_flag==1)
		{
			xview += 1;
			zview += 1;

		}
		if(one_flag==1)
		{
			xview -= 1;
			zview -= 1;
		}
		if(helicopter_flag==1)
		{
			canglex -=1;
			canglez-=1;
		}
	}
	if(ypos < 400)
	{
		yview += 0.02;
		if(yview > 4)
			yview=4;
	}
	if(ypos > 400)
	{
		yview -= 0.02;
		if(yview < -1)
			yview=-1;
	}
	glfwSetCursorPos (window, 700, 400);
}

void mouseScroll(GLFWwindow *window, double xoffset, double yoffset)
{
	int fbwidth=1400/300, fbheight=800/5;
	glfwGetFramebufferSize(window, &fbwidth, &fbheight);
	if(yoffset==-1)	{
		if(fov < 45.6f)
			fov += 0.1f;
		Matrices.projection = glm::perspective (fov, (GLfloat) fbwidth / (GLfloat) fbheight, 0.1f, 500.0f);
	}
	if(yoffset==1){
		if(fov > 44.4f)
			fov -= 0.1f;
		Matrices.projection = glm::perspective (fov, (GLfloat) fbwidth / (GLfloat) fbheight, 0.1f, 500.0f);
	}
}


#endif