#ifndef _INITIALIZE_H
#define _INITIALIZE_H


struct VAO {
	GLuint VertexArrayID;
	GLuint VertexBuffer;
	GLuint ColorBuffer;
	GLuint TextureBuffer;
	GLuint TextureID;

	GLenum PrimitiveMode; // GL_POINTS, GL_LINE_STRIP, GL_LINE_LOOP, GL_LINES, GL_LINE_STRIP_ADJACENCY, GL_LINES_ADJACENCY, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, GL_TRIANGLES, GL_TRIANGLE_STRIP_ADJACENCY and GL_TRIANGLES_ADJACENCY
	GLenum FillMode; // GL_FILL, GL_LINE
	int NumVertices;
};

typedef struct VAO VAO;

struct GLMatrices {
	glm::mat4 projection;
	glm::mat4 model;
	glm::mat4 view;
	GLuint MatrixID; // For use with normal shader
	GLuint TexMatrixID; // For use with texture shader
};

// struct FTGLFont {
// 	FTFont* font;
// 	GLuint fontMatrixID;
// 	GLuint fontColorID;
// };


struct Blocks {
  float x;
  float y;
  float z;
  float vx;
  float vy;
  float vz;
  float length;
  float width;
  float height;
  int targetcollide;
  float mass;
  float rotate;
  VAO *cube;
  float color[3];
};

struct  Games
{
  float Score;
  float Health;
  int Level;
  float startx;
  float starty;
  float startz;
  int endblock;
};

GLuint LoadShaders(const char * ,const char * ) ;
void error_callback(int , const char* );
struct VAO* create3DObject (GLenum , int , const GLfloat* , const GLfloat* , GLenum );
struct VAO* create3DTexturedObject (GLenum , int , const GLfloat* , const GLfloat* , GLuint , GLenum );
struct VAO* create3DObject (GLenum , int , const GLfloat* , const GLfloat , const GLfloat , const GLfloat , GLenum );
GLuint createTexture (const char* );
void draw3DObject (struct VAO* );
void draw3DTexturedObject (struct VAO* );
glm::vec3 getRGBfromHue (int );

#endif

