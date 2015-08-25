#include <cstdio>
#include <GL\glew.h>
#include <GL\glut.h>

// Function Declaration
static char* textFileRead(const char *fileName);
static void validateShader(GLuint shader, const char* file);
static void validateProgram(GLuint program);

// Shader Variable
GLuint shader_vp;
GLuint shader_fp;
GLuint shader_program_id;

// For Passing
GLfloat mv_mat[16];
GLfloat proj_mat[16];

float angle = 0.0;

void init(void)
{
	
	puts((char*)glGetString(GL_VERSION));
	puts((char*)glGetString(GL_SHADING_LANGUAGE_VERSION));

	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

	glewInit(); //if no this line , Segmentation fault in glCreateShader occur.

	shader_program_id = glCreateProgram();

	shader_vp = glCreateShader(GL_VERTEX_SHADER);
	shader_fp = glCreateShader(GL_FRAGMENT_SHADER);

	const char* vsText = textFileRead("vs.glsl");
	const char* fsText = textFileRead("fs.glsl");

	if (vsText == nullptr || fsText == nullptr) {
		puts("Either vertex shader or fragment shader file not found.");
	}

	glShaderSource(shader_vp, 1, &vsText, 0);
	glShaderSource(shader_fp, 1, &fsText, 0);

	glCompileShader(shader_vp);
	validateShader(shader_vp, "vs.glsl");
	glCompileShader(shader_fp);
	validateShader(shader_fp, "fs.glsl");

	//if compile successfully
	glAttachShader(shader_program_id, shader_fp);
	glAttachShader(shader_program_id, shader_vp);

	glLinkProgram(shader_program_id);
	validateProgram(shader_program_id);
}

void display(void)
{
	glClearColor(0.2, 0.2, 0.2, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glUseProgram(shader_program_id);

	glRotatef(angle, 1.0, 1.0, 1.0);

	GLuint modelviewMat_loc = glGetUniformLocation(shader_program_id, "modelviewMat");
	GLuint projMat_loc = glGetUniformLocation(shader_program_id, "projMat");

	glGetFloatv(GL_MODELVIEW_MATRIX, mv_mat);
	glGetFloatv(GL_PROJECTION_MATRIX, proj_mat);

	glUniformMatrix4fv(modelviewMat_loc, 1, GL_FALSE, mv_mat);
	glUniformMatrix4fv(projMat_loc, 1, GL_FALSE, proj_mat);

	glutSolidCube(2.0);

	glUseProgram(0);

	glutSwapBuffers();
	angle += 1.0f;
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLfloat)w / (GLfloat)h, 1.0, 100.0);

	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("GLSL Passing Variable Example");

	init();

	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(reshape);

	glutMainLoop();
	return 0;
}

static char* textFileRead(const char *fileName) {
	char* text = nullptr;
	errno_t err;
	FILE *file;
	if (fileName != NULL) {
		err = fopen_s(&file, fileName, "rt");

		if (file != NULL && err == 0) {
			fseek(file, 0, SEEK_END);
			int count = ftell(file);
			rewind(file);

			if (count > 0) {
				text = (char*)malloc(sizeof(char) * (count + 1));
				count = fread(text, sizeof(char), count, file);
				text[count] = '\0';
			}
			fclose(file);
		}
	}
	return text;
}

static void validateShader(GLuint shader, const char* file) {
	const unsigned int BUFFER_SIZE = 512;
	char buffer[BUFFER_SIZE];
	memset(buffer, 0, BUFFER_SIZE);
	GLsizei length = 0;

	glGetShaderInfoLog(shader, BUFFER_SIZE, &length, buffer);
	if (length > 0) {
		printf_s("Shader %u (%s) compile error: %s\n", (UINT32)shader, (file ? file : ""), buffer);
	}
}

static void validateProgram(GLuint program) {
	const unsigned int BUFFER_SIZE = 512;
	char buffer[BUFFER_SIZE];
	memset(buffer, 0, BUFFER_SIZE);
	GLsizei length = 0;

	memset(buffer, 0, BUFFER_SIZE);
	glGetProgramInfoLog(program, BUFFER_SIZE, &length, buffer);
	if (length > 0)
		printf_s("Program %u link error: %s\n", (UINT32)program, buffer);

	glValidateProgram(program);
	GLint status;
	glGetProgramiv(program, GL_VALIDATE_STATUS, &status);
	if (status == GL_FALSE)
		printf_s("Error validating shader %u\n", (UINT32)program);
}