/* Edit from http://www.swiftless.com/tutorials/glsl/4_lighting.html */

#include <GL\glew.h>
#include <GL\glut.h>

class Shader
{
public:
	Shader();
	~Shader();
	void init(const char *vsFile, const char *fsFile);
	void bind();
	void unbind();
private:
	GLuint shader_vp;
	GLuint shader_fp;
	GLuint shader_id;
};

static char* textFileRead(const char *fileName);
static void validateShader(GLuint shader, const char* file = 0);
static void validateProgram(GLuint program);