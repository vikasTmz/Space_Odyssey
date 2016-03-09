# Space_Odyssey
An Opengl 3.3 3-D Game

#3-D platform game - **by Vikas**

## Libraries used

1) SOIL.h 
2) Freetype/ftgl3
3) GLFW
4) GLM

## Features (Version 1.0)

1) Customizable map ( Created a 3-D map by specifing order and height in "Map_templates.txt"). Thus any kind of map can be generated , given the right template.
2) First person, Third person , Top view and tower view has been implemented.
3) In first and third person , the player (a block temperarily ) can turn around and achieve a 360 view. 
4) Images have been rendered.

## Manual / Instructions

1) W,A,S,D - move player.
2) Arrow keys to look around (turn left,right and look up,down).
3) #1 - First person
   #3 - Third person
   #8 - Tower view
   #9 - Top viewFont Library - FTGL3

////////////////////////////////////////--Default Readme--///////////////////////////////////////////////////////////////////////////

--------------------
* Download and Install freetype2 library from
  http://download.savannah.gnu.org/releases/freetype/freetype-2.6.2.tar.gz
* Download and install ftgl3 library from 
  https://github.com/lukexi/ftgl3


Simple OpenGL Image Library - SOIL (Textures)
---------------------------------------------
* Download and Install SOIL library from
  http://www.lonesock.net/soil.html


Sample Code - Changes (Fonts)
-----------------------------
* initGL and draw functions have been modified to include font rendering
* Additional camera defined for fonts in draw() which stays fixed while
  the original camera keeps rotating.
* Vertex shader code for rendering font is a bit different from the 
  vertex shader code for rendering other geometry.
* FTExtrude style font rendering is used in example. Other styles can be
  found at:
  http://ftgl.sourceforge.net/docs/html/ftgl-tutorial.html
* Font can be animated and colors changed every frame.


Sample Code - Changes (Textures)
--------------------------------
* initGL and draw functions have been modified to include loading textures
  and corresponding texture shaders
* create3DTexturedObject and draw3DTexturedObject use texture buffers 
  instead of color buffer.
* Vertex and fragment shaders for textured rendering are very different 
  from the shaders of normal rendering.
* NOTE width and height of images used for textures should be power of 2 on
  some graphic cards. (beach2.png - power of two image)
