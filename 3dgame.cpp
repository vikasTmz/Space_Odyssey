#include "3dgame.h"

using namespace irrklang;
ISoundEngine *SoundEngine = createIrrKlangDevice();
  
GLuint programID, fontProgramID, textureProgramID;
float camera_rotation_angle = 90, rectangle_rotation = 0,enemy_rotation=0, triangle_rotation = 0,cube_dime=0.5;
float player_dime=0.25,max_height_flag=-1000,max_height,gravity=0.004,lastupdatetime,currenttime,Leveltemp=0;
int max_index=0,isfalling = 0,isjumping=0,number_platforms=3,number_enemy=1;
char Map[1000][1000];
// FTGLFont GL3Font;
GLMatrices Matrices;
Blocks Cubes[1000];
Blocks player;
Blocks ammo;

Games Game;
VAO *triangle, *rectangle, *screen_axis,*sky;

void reshapeWindow (GLFWwindow* window, int width, int height)
{
	int fbwidth=width/300, fbheight=height/5;
// cout << fbwidth << "  " << fbheight << endl;
	glfwGetFramebufferSize(window, &fbwidth, &fbheight);
	glPointSize(10.0f);
// glviewport (0, 0, (GLsizei) fbwidth, (GLsizei) fbheight);/* glMatrixMode (GL_PROJECTION);glLoadIdentity ();gluPerspective (fov, (GLfloat) fbwidth / (GLfloat) fbheight, 0.1, 500.0); */// Matrices.projection = glm::ortho(-4.0f, 10.0f, -4.0f, 10.0f, 0.1f, 500.0f);
// if(Play_flag==1)

	Matrices.projection = glm::perspective (fov, (GLfloat) fbwidth / (GLfloat) fbheight, 0.1f, 500.0f);

// else if(Play_flag==0)
// {
// 	// glViewport (0, 0, (GLsizei) fbwidth, (GLsizei) fbheight);
// 	Matrices.projection = glm::ortho(0.0f, 30.0f, 0.0f, 30.0f, 0.1f, 500.0f);
// }

}

void GameReset()
{
	player.x=Game.startx,player.y = Game.starty+ player_dime+Cubes[max_index].width/2,player.z = Game.startz;
	Game.Level++;
	Game.Score += 10*Game.Level;
	cout << "Level:  "  << Game.Level << endl;
	cout << "Health:  " << Game.Health << endl;
	cout << "Score:  " << Game.Score << endl << endl;
}

void checkdeath()
{
	if(player.y < -10)
	{
		player.x=Game.startx,player.y = Game.starty+ player_dime+Cubes[max_index].width/2,player.z = Game.startz;
		player.vx=player.vy=player.vz=0;
		Game.Health--;
	}
	if(Game.Health==0)
	{

		// SoundEngine->play2D("explosion.wav", GL_TRUE);
		Game.Level=0;
		Leveltemp=0;	
		Game.Health=3;
		player.vx=player.vy=player.vz=0;
	}
}

void LoadLevel()
{
	int i=0,k=0;
	char filename[] = "Map0.txt" ;
	filename[3] = 48 + Game.Level;
	FILE *file = fopen ( filename, "r" );
	if ( file != NULL )
	{
		char line [ 128 ]; 
		while ( fgets ( line, sizeof line, file ) != NULL )
		{
			i=0;
			while(line[i] != '\0')
			{
				Map[k][i] = line[i];
				i++;
			}
			k++;
	// fputs ( line, stdout ); 
		}
		fclose ( file );
	}
	else
	{
		perror ( filename ); 
	}
	char starttiles[] = "start0.png";
	starttiles[5] = 48 + Game.Level; 
if(Game.Level==0)Game.endblock = 249,Game.Health = 3;//249
if(Game.Level==1)Game.endblock = 238;//238
if(Game.Level==2){Game.endblock = 242,number_platforms=3,number_enemy=0;}//242
if(Game.Level==3){Game.endblock = 300,number_platforms=1,number_enemy=1;}//242

GLuint textureID[10] = {};
textureID[0] = createTexture("gradient1.jpg");
textureID[1] = createTexture("gradient3.jpg");
textureID[2] = createTexture("face.jpg");

textureID[3] = createTexture(starttiles);
textureID[4] = createTexture("finish.png");

int text_flag = 0;
number_blocks=0;
for (int m = 0; m < k; ++m)
{
	for (int j = 0; j < i; ++j)
	{
		xcord = xcord + cube_dime*2;
		if( Map[m][j] >= 49 || Map[m][j] <=47)	
		{
		// cout << Map[m][j] << " " << number_blocks << endl;		
			if(Map[m][j]  >= 49)
			{
				ycord = cube_dime*2*(Map[m][j] -49);
				text_flag=0;
			}
			if(Map[m][j]  >= 52)
			{
				text_flag=1;
			}
			if(Map[m][j] <=47)
			{
				ycord = cube_dime*2*(Map[m][j] - 48);
			}
			if(Map[m][j]  >= max_height_flag)
			{
				max_height_flag = Map[m][j], max_index = number_blocks, max_height = ycord;
			}

			if(number_blocks == Game.endblock)text_flag=3;
			if(number_blocks==10 && Game.Level < 3)text_flag=3;
			if(number_blocks==1 && Game.Level == 3)text_flag=3;				

			createcube(cube_dime,cube_dime,cube_dime,xcord,zcord,ycord,number_blocks,textureID[text_flag]);

			if(number_blocks==10 && Game.Level < 3)
				Game.startx = Cubes[number_blocks].x,Game.starty = Cubes[number_blocks].y,Game.startz = Cubes[number_blocks].z;

			if(Game.Level==3 && number_blocks==1)
				Game.startx = Cubes[number_blocks].x,Game.starty = Cubes[number_blocks].y,Game.startz = Cubes[number_blocks].z;

			number_blocks++;
		}
		text_flag=0;
		Map[m][j] =48;
	}	
	zcord = zcord +cube_dime *2;	
	xcord=0;
}
if(Game.Level==2)
	for (i = 0; i < number_platforms; ++i)
	{
		if(i==0)createcube(cube_dime,cube_dime,cube_dime,Cubes[170].x,Cubes[170].z,Cubes[170].y,number_blocks,textureID[text_flag]);
	if(i==1)createcube(cube_dime,cube_dime,cube_dime,Cubes[224].x,Cubes[224].z,Cubes[224].y,number_blocks,textureID[text_flag]);		//224 225	
	if(i==2)createcube(cube_dime,cube_dime,cube_dime,Cubes[226].x,Cubes[226].z,Cubes[226].y,number_blocks,textureID[text_flag]);		//224 225	
	number_blocks++;
}
if(Game.Level==3)
{
	for (i = 0; i < number_platforms; ++i)
	{
		if(i==0)createcube(cube_dime,cube_dime,cube_dime,Cubes[68].x,Cubes[68].z,Cubes[68].y,number_blocks,textureID[text_flag]);
	// if(i==1)createcube(cube_dime,cube_dime,cube_dime,Cubes[224].x,Cubes[224].z,Cubes[224].y,number_blocks,textureID[text_flag]);		//224 225	
	// if(i==2)createcube(cube_dime,cube_dime,cube_dime,Cubes[226].x,Cubes[226].z,Cubes[226].y,number_blocks,textureID[text_flag]);		//224 225	
		number_blocks++;
	}

	createcube(cube_dime,cube_dime,cube_dime,Cubes[226].x,Cubes[226].z,Cubes[226].y + 2*Cubes[max_index].width/2,number_blocks,textureID[2]);
	number_blocks++;
//226 , 161
}
createpoints(Cubes[226].x,Cubes[226].y,Cubes[226].z);
createplayercube(player_dime,Game.startx,Game.startz,Game.starty + player_dime+Cubes[max_index].width/2);
xcord=0,ycord=0,zcord=0;
}

void moveplatforms()
{
	int index1,index2;

	if(Game.Level==2){
		for (int i = 0; i < number_platforms; ++i)
		{
			if(i==0) {index1=169,index2=170;}
			if(i==1) {index1=224,index2=225;}
			if(i==2) {index1=226;index2=227;}

			if(Cubes[number_blocks- number_platforms+i].x <= Cubes[index1].x)	
			{
				Cubes[number_blocks- number_platforms+i].vx = 0.01;				
				if(i==2)
					Cubes[number_blocks- number_platforms+i].vy = 0.01;
			}	
			else if(Cubes[number_blocks- number_platforms+i].x >= Cubes[index2].x)	
			{
				Cubes[number_blocks- number_platforms+i].vx = -0.01;
				if(i==2)
					Cubes[number_blocks- number_platforms+i].vy = -0.01;
			}
	// cout << Cubes[number_blocks- number_platforms+i].vx << endl;
			Cubes[number_blocks- number_platforms+i].x += Cubes[number_blocks- number_platforms+i].vx;
			if(i==2)
				Cubes[number_blocks- number_platforms+i].y += Cubes[number_blocks- number_platforms+i].vy;
		}}

		if(Game.Level==3){
			for (int i = 0; i < number_platforms; ++i)
			{
				if(i==0) {index1=67,index2=68;}
	// if(i==1) {index1=224,index2=225;}
	// if(i==2) {index1=226;index2=227;}
				if(Cubes[number_blocks- number_platforms -number_enemy +i].x <= Cubes[index1].x)	
				{
					Cubes[number_blocks- number_platforms -number_enemy+i].vx = 0.01;				
					if(i==0)
						Cubes[number_blocks- number_platforms -number_enemy+i].vy = -0.01;
				}	
				else if(Cubes[number_blocks- number_platforms -number_enemy+i].x >= Cubes[index2].x)	
				{
					Cubes[number_blocks- number_platforms -number_enemy+i].vx = -0.01;
					if(i==0)
						Cubes[number_blocks- number_platforms -number_enemy+i].vy = 0.01;
				}
				Cubes[number_blocks- number_platforms -number_enemy+i].x += Cubes[number_blocks- number_platforms -number_enemy+i].vx;
				if(i==0)
					Cubes[number_blocks- number_platforms -number_enemy+i].y += Cubes[number_blocks- number_platforms -number_enemy+i].vy;
			}}

		}

		void Shootammo(int b)
		{
			glm::vec3 xaxis(1,0,0);
			glm::vec3 zaxis(0,0,1);
			glm::vec3 playerpos(player.x,player.y,player.z);	
			glm::vec3 enemypos(Cubes[b].x,Cubes[b].y,Cubes[b].z);	
			glm::vec3 ammopos(ammo.x,ammo.y,ammo.z);	
			glm::vec3 difference = playerpos - enemypos;
			glm::vec3 distance = enemypos - ammopos;
			float dotproductex = glm::dot(difference,xaxis);
			float dotproductez = glm::dot(difference,zaxis);

			if(glm::length(difference) < 8)
			{
				ammo.vz = 0.008*dotproductez;
				ammo.vx = 0.008*dotproductex;
			}

			if(glm::length(distance) > 11)
			{
				ammo.x = Cubes[b].x,ammo.z = Cubes[b].z,ammo.vz=0,ammo.vx=0;
			}
			if((ammo.x > player.x - player.width/2 && ammo.x < player.x + player.width/2))
				if((ammo.z > player.z - player.width/2 && ammo.z < player.z + player.width/2))
				{
					ammo.x = Cubes[b].x,ammo.z = Cubes[b].z,ammo.vz=0,ammo.vx=0;
					Game.Health -= 0.5; 
				}
				ammo.z += ammo.vz;
				ammo.x += ammo.vx;
			}

			void CheckCollision(int m)
			{
// isfalling=0;
				for (int i = 0; i < number_blocks; ++i)
				{
					glm::vec3 center(player.x,player.y,player.z);
					glm::vec3 objs_half_extents(Cubes[i].width/2, Cubes[i].height/2,Cubes[i].length/2);
					glm::vec3 objs_center(Cubes[i].x,Cubes[i].y,Cubes[i].z);
					glm::vec3 difference = center - objs_center;
					glm::vec3 clamped = glm::clamp(difference, -objs_half_extents, objs_half_extents);
					glm::vec3 closest = objs_center + clamped;
					difference = closest - center;
					glm::vec3 dotvector = center - closest;
					glm::vec3 xaxis(1,0,0);
					glm::vec3 zaxis(0,0,1);
					glm::vec3 yaxis(0,1,0);
					float dotproductx = glm::dot(dotvector,xaxis);
					float dotproducty = glm::dot(dotvector,yaxis);
					float dotproductz = glm::dot(dotvector,zaxis);

					if( glm::length(difference) < player.width/2)
					{
						if(dotproductx > 0.0 && m==1)
						{  
		// cout << dotproductx << endl;
							player.x = closest.x + player.width/2;
						}
						else if(dotproductx < 0.0 && m==1)
						{  
							player.x = closest.x - player.width/2;

						}

						if(dotproducty > 0.0 && m==0)
						{  
							lastupdatetime = glfwGetTime();
							player.y = closest.y + player.width/2;
							isfalling = 0, player.vy=0,Jump_flag=0;
							if(i >= number_blocks- number_platforms -number_enemy && Game.Level >=2)
							{
								player.x += Cubes[i].vx;
								player.y += Cubes[i].vy;
							}
							if(i==Game.endblock)
								GameReset();
						}
						else if(dotproducty < 0.0 && m==0)
						{  
							player.y = closest.y - player.width/2;
							isfalling = 0, player.vy=0,Jump_flag=0;
							if(i >= number_blocks- number_platforms  -number_enemy && Game.Level >=2)
							{
								player.x += Cubes[i].vx;					
								player.y += Cubes[i].vy;
							}
							if(i==Game.endblock)
								GameReset();
						}

						if(dotproductz > 0.0 && m==1)
						{  
		// cout << "posz" << endl;
							player.z = closest.z + player.width/2;
						}
						else if(dotproductz < 0.0 && m==1)
						{  
							player.z = closest.z - player.width/2;
						}
					}

				}

				if((currenttime - lastupdatetime) > 0.1 && m==0)
				{
					isfalling=1;
					player.vy = player.vy - (gravity);
					player.y += player.vy;
				}
			}

			void PlayerJump()
			{
				if(isfalling==0)
				{
// cout << "jumping1" << endl;
					player.vy = player.vy - (gravity);
					player.y += player.vy;		
				}
			}
			void moveplayer()
			{
				player.x += player.vx,player.z += player.vz;
				camerax += cameravx,cameraz += cameravz;
			}

			void draw()
			{	
				if(Game.Level==Leveltemp)
				{
					LoadLevel();
					Leveltemp++;		
				}

				glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				glUseProgram (programID);
				glm::vec3 eye (5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
				glm::vec3 target (0,0,0);
				glm::vec3 up (0,1,0);
				glm::vec3 xaxis(1,0,0);
				glm::vec3 zaxis(0,0,1);
				glm::vec3 yaxis(0,1,0);

				if(three_flag==1)	
				{
					Matrices.view = glm::lookAt(glm::vec3(player.x+player_dime*7*sin(xview*M_PI/180.0f),player.y + player_dime*9,player.z + player_dime*7*cos(zview*M_PI/180.0f)), glm::vec3(player.x,player.y+yview+player_dime*4,player.z), glm::vec3(0,1,0));		
					glm::vec3 cameralookat(player.x+player_dime*7*sin(xview*M_PI/180.0f), player.y + player_dime*9, player.z + player_dime*7*cos(zview*M_PI/180.0f));
					glm::vec3 camerapos(player.x,player.y+yview+player_dime*4,player.z);	
					glm::vec3 differencew = camerapos - cameralookat;
					glm::vec3 differencel = glm::cross(yaxis,differencew);
					dotproductlx = glm::dot(differencel,xaxis);
					dotproductlz = glm::dot(differencel,zaxis);

					dotproductwx = glm::dot(differencew,xaxis);
					dotproductwz = glm::dot(differencew,zaxis);
// cout << dotproductlx << " :x:  :z: " << dotproductlz << endl;
				}

				if(one_flag==1)
				{
					Matrices.view = glm::lookAt(glm::vec3(player.x,player.y + player_dime*3,player.z), glm::vec3(player.x+player_dime*10*sin(xview*M_PI/180.0f),player.y+yview,player.z - player_dime*10*cos(zview*M_PI/180.0f)), glm::vec3(0,1,0));		
					glm::vec3 cameralookat(player.x,player.y + player_dime*3,player.z + player_dime*4);
					glm::vec3 camerapos(player.x+player_dime*8*sin(xview*M_PI/180.0f),player.y+yview,player.z - player_dime*8*cos(zview*M_PI/180.0f));	
					glm::vec3 differencew = camerapos - cameralookat;
					glm::vec3 differencel = glm::cross(yaxis,differencew);
					dotproductlx = glm::dot(differencel,xaxis);
					dotproductlz = glm::dot(differencel,zaxis);

					dotproductwx = glm::dot(differencew,xaxis);
					dotproductwz = glm::dot(differencew,zaxis);
				}
				if(helicopter_flag==1)
				{
					Matrices.view = glm::lookAt(glm::vec3(camerax,cameray,cameraz), glm::vec3(camerax+player_dime*10*sin(canglex*M_PI/180.0f),cameray+yview,cameraz - player_dime*10*cos(canglez*M_PI/180.0f)), glm::vec3(0,1,0));		
					glm::vec3 cameralookat(camerax,cameray,cameraz);
					glm::vec3 camerapos(camerax+player_dime*10*sin(canglex*M_PI/180.0f),cameray+yview,cameraz - player_dime*10*cos(canglez*M_PI/180.0f));	
					glm::vec3 difference = camerapos - cameralookat;
					dotproductcx = glm::dot(difference,xaxis);
					dotproductcz = glm::dot(difference,zaxis);
				}

				if(tower_flag==1)
					Matrices.view = glm::lookAt(glm::vec3(player_dime*37,player_dime*38,player_dime*25), glm::vec3(player.x,player.y,player.z), glm::vec3(0,1,0));
				if(top_flag==1)
					Matrices.view = glm::lookAt(glm::vec3(player.x,player_dime*50,player.z+0.5), glm::vec3(player.x,player.y,player.z), glm::vec3(0,1,0));

				glm::mat4 VP = Matrices.projection * Matrices.view;
				glm::mat4 MVP;


				glUseProgram(textureProgramID);

				Matrices.model = glm::mat4(1.0f);
glm::mat4 translateRectangle = glm::translate (glm::vec3(0,0,0));        // glTranslatef
glm::mat4 rotateRectangle = glm::rotate((float)(0*M_PI/180.0f), glm::vec3(0,0,1)); // rotate about vector (-1,1,1)
Matrices.model *= (translateRectangle * rotateRectangle);
MVP = VP * Matrices.model;
glUniformMatrix4fv(Matrices.TexMatrixID, 1, GL_FALSE, &MVP[0][0]);
glUniform1i(glGetUniformLocation(textureProgramID, "texSampler"), 0);
draw3DTexturedObject(sky);

if(Game.Level >=2)
	moveplatforms();

checkdeath();
moveplayer();
CheckCollision(1);

if(Jump_flag==1)
	PlayerJump();

currenttime = glfwGetTime();
if(isfalling == 0 && Jump_flag==0)
	player.y -= 0.01;

CheckCollision(0);

glUseProgram(programID);
Matrices.model = glm::mat4(1.0f);
glm::mat4 translateplayer = glm::translate (glm::vec3(player.x,player.y,player.z)); 
glm::mat4 rotateplayer ;
if(three_flag==1)	
	rotateplayer = glm::rotate((float)(xview*M_PI/180.0f), glm::vec3(0,1,0));  
if(one_flag==1)
	rotateplayer = glm::rotate((float)(-xview*M_PI/180.0f), glm::vec3(0,1,0));  
glm::mat4 playerTransform = translateplayer * rotateplayer ;
Matrices.model *= playerTransform; 
MVP = VP * Matrices.model; 
glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
draw3DObject(player.cube);


float increments = 1;
glUseProgram(programID);

Matrices.model = glm::mat4(1.0f);
glm::mat4 translateaxis = glm::translate (glm::vec3(0,0,0)); 
glm::mat4 rotateaxis = glm::rotate((float)(0*M_PI/180.0f), glm::vec3(0,0,1));  
glm::mat4 axisTransform = translateaxis * rotateaxis ;
Matrices.model *= axisTransform; 
MVP = VP * Matrices.model; 
glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
draw3DObject(screen_axis);


glUseProgram(textureProgramID);


for (int b = 0; b < number_blocks; ++b)
{
	Matrices.model = glm::mat4(1.0f);
	glm::mat4 translatecube = glm::translate (glm::vec3(Cubes[b].x,Cubes[b].y,Cubes[b].z)); 
	glm::mat4 rotatecube;

	if(b==number_blocks-1 && Game.Level==3)
	{
		glm::vec3 playerpos(player.x,player.y,player.z);	
		glm::vec3 enemypos(Cubes[b].x,Cubes[b].y,Cubes[b].z);	
		glm::vec3 difference = playerpos - enemypos;
		float dotproductpex = glm::dot(difference,xaxis);
		if(glm::length(difference) < 10)
			rotatecube = glm::rotate((float)(dotproductpex*-20*M_PI/180.0f), glm::vec3(0,1,0));  
		else
			rotatecube = glm::rotate((float)(0*M_PI/180.0f), glm::vec3(0,1,0));  
		Shootammo(b);
	}
	else
		rotatecube = glm::rotate((float)(0*M_PI/180.0f), glm::vec3(0,1,0));  

	glm::mat4 cubeTransform = translatecube * rotatecube ;
	Matrices.model *= cubeTransform; 
	MVP = VP * Matrices.model; 
	glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
	glUniform1i(glGetUniformLocation(textureProgramID, "texSampler"), 0);
	draw3DTexturedObject(Cubes[b].cube);
}

glUseProgram (programID);
if(Game.Level==3){
	Matrices.model = glm::mat4(1.0f);
	glm::mat4 translategrass = glm::translate (glm::vec3(ammo.x,ammo.y+1,ammo.z)); 
	glm::mat4 grassTransform = translategrass;
	Matrices.model *= grassTransform; 
	MVP = VP * Matrices.model; 
	glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
	draw3DObject(ammo.cube);
}


// 	static int fontScale = 0;
// 	float fontScaleValue = 0.75 + 0.25*sinf(fontScale*M_PI/180.0f);
// 	glm::vec3 fontColor = getRGBfromHue (fontScale);



// 	// Use font Shaders for next part of code
// 	glUseProgram(fontProgramID);
// 	Matrices.view = glm::lookAt(glm::vec3(0,0,3), glm::vec3(0,0,0), glm::vec3(0,1,0)); // Fixed camera for 2D (ortho) in XY plane

// 	// Transform the text
// 	Matrices.model = glm::mat4(1.0f);
// 	glm::mat4 translateText = glm::translate(glm::vec3(-3,2,0));
// 	// glm::mat4 scaleText = glm::scale(glm::vec3(fontScaleValue,fontScaleValue,fontScaleValue));
// 	Matrices.model *= (translateText );//* scaleText);
// MVP = Matrices.projection * Matrices.view * Matrices.model;
// 	// send font's MVP and font color to fond shaders
// glUniformMatrix4fv(GL3Font.fontMatrixID, 1, GL_FALSE, &MVP[0][0]);
// glUniform3fv(GL3Font.fontColorID, 1, &fontColor[0]);

// 	// Render font
// GL3Font.font->Render("Round n Round we go !!");

// triangle_rotation = triangle_rotation + increments*triangle_rot_dir*triangle_rot_status;
rectangle_rotation = rectangle_rotation + increments*rectangle_rot_dir*rectangle_rot_status;

// font size and color changes
// fontScale = (fontScale + 1) % 360;
}

void introframe()
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram (programID);
	glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
	glm::vec3 target (0,0,0);
	glm::vec3 up (0,1,0);
	Matrices.view = glm::lookAt(glm::vec3(player.x,player_dime*30,player.z+0.5), glm::vec3(player.x,player.y,player.z), glm::vec3(0,1,0));
	glm::mat4 VP = Matrices.projection * Matrices.view;
	glm::mat4 MVP;

}

GLFWwindow* initGLFW (int width, int height)
{
	GLFWwindow* window; 

	glfwSetErrorCallback(error_callback);
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, "Sample OpenGL 3.3 Application", NULL, NULL);

	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
	glfwSwapInterval( 1 );

	glfwSetFramebufferSizeCallback(window, reshapeWindow),glfwSetWindowSizeCallback(window, reshapeWindow),glfwSetWindowCloseCallback(window, quit),glfwSetKeyCallback(window, keyboard),glfwSetCharCallback(window, keyboardChar),glfwSetMouseButtonCallback(window, mouseButton);
	glfwSetCursorPosCallback(window, cursor_pos_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glfwSetCursorPos(window, 700, 400);
	glfwSetScrollCallback(window, mouseScroll);
	return window;
}

void initGL (GLFWwindow* window, int width, int height)
{
	glActiveTexture(GL_TEXTURE0);
	Game.Level=0;
	GLuint textureID;
	textureID = createTexture("back.jpg");
// if(textureID[0] == 0 )
// 	cout << "SOIL loading error: '" << SOIL_last_result() << "'" << endl;

// if(textureID[1] == 0 )
// 	cout << "SOIL loading error: '" << SOIL_last_result() << "'" << endl;

	textureProgramID = LoadShaders( "TextureRender.vert", "TextureRender.frag" );

	Matrices.TexMatrixID = glGetUniformLocation(textureProgramID, "MVP");


	drawaxis();
	createsky(textureID);

	programID = LoadShaders( "Sample_GL3.vert", "Sample_GL3.frag" );

	Matrices.MatrixID = glGetUniformLocation(programID, "MVP");
	reshapeWindow (window, width, height);
	glClearColor (0.3f, 0.3f, 0.3f, 0.0f); 
	glClearDepth (1.0f);
	glEnable (GL_DEPTH_TEST);
	glDepthFunc (GL_LEQUAL);
// glEnable(GL_LIGHT0);
// glEnable(GL_NORMALIZE);
// glEnable(GL_COLOR_MATERIAL);
// glEnable(GL_LIGHTING); 
// glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);

// const char* fontfile = "arial.ttf";
// GL3Font.font = new FTExtrudeFont(fontfile); 

// if(GL3Font.font->Error())
// {
// 	cout << "Error: Could not load font `" << fontfile << "'" << endl;
// 	glfwTerminate();
// 	exit(EXIT_FAILURE);
// }

// fontProgramID = LoadShaders( "fontrender.vert", "fontrender.frag" );
// GLint fontVertexCoordAttrib, fontVertexNormalAttrib, fontVertexOffsetUniform;
// fontVertexCoordAttrib = glGetAttribLocation(fontProgramID, "vertexPosition");
// fontVertexNormalAttrib = glGetAttribLocation(fontProgramID, "vertexNormal");
// fontVertexOffsetUniform = glGetUniformLocation(fontProgramID, "pen");
// GL3Font.fontMatrixID = glGetUniformLocation(fontProgramID, "MVP");
// GL3Font.fontColorID = glGetUniformLocation(fontProgramID, "fontColor");

// GL3Font.font->ShaderLocations(fontVertexCoordAttrib, fontVertexNormalAttrib, fontVertexOffsetUniform);
// GL3Font.font->FaceSize(1);
// GL3Font.font->Depth(0);
// GL3Font.font->Outset(0, 0);
// GL3Font.font->CharMap(ft_encoding_unicode);

// cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
// cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
// cout << "VERSION: " << glGetString(GL_VERSION) << endl;
// cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;

}

int main (int argc, char** argv)
{
	int width = 1400,height = 800;
	GLFWwindow* window = initGLFW(width, height);


	initGL (window, width, height);
	double last_update_time = glfwGetTime(), current_time;
	SoundEngine->play2D("background.wav", GL_TRUE);
	while (!glfwWindowShouldClose(window)) {

		// if(Play_flag==1)	
			draw();
		// else if(Play_flag==0)
			// introframe();
		glfwSwapBuffers(window);
		glfwPollEvents();		
		current_time = glfwGetTime(); 
		if ((current_time - last_update_time) >= 0.5) { 

			last_update_time = current_time;
		}
	}
	glfwTerminate();
	exit(EXIT_SUCCESS);
}