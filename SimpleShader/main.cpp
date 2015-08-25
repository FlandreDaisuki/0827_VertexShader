#include "shader.h"

Shader my_shader;

GLfloat angle = 0.0; //set the angle of rotation

//diffuse light color variables
GLfloat dlr = 1.0;
GLfloat dlg = 1.0;
GLfloat dlb = 1.0;

//ambient light color variables
GLfloat alr = 1.0;
GLfloat alg = 1.0;
GLfloat alb = 1.0;

//light position variables
GLfloat lx = 1.0;
GLfloat ly = 1.0;
GLfloat lz = 1.0;
GLfloat lw = 0.0;


void init(void)
{
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);

	glewInit(); //if no this line , Segmentation fault in glCreateShader occur.

	my_shader.init("shader.vert", "shader.frag");
}

void setLighting(void) {
	GLfloat DiffuseLight[] = { dlr, dlg, dlb }; //set DiffuseLight[] to the specified values
	GLfloat AmbientLight[] = { alr, alg, alb }; //set AmbientLight[] to the specified values

	glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight); //change the light accordingly
	glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight); //change the light accordingly

	GLfloat LightPosition[] = { lx, ly, lz, lw }; //set the LightPosition to the specified values

	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition); //change the light accordingly
}

void display(void)
{
	glClearColor(0.2, 0.2, 0.2, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	setLighting();

	my_shader.bind();

	glRotatef(angle, 1.0, 0.0, 0.0); //rotate on the x axis
	glRotatef(angle, 0.0, 1.0, 0.0); //rotate on the y axis
	glRotatef(angle, 0.0, 0.0, 1.0); //rotate on the z axis
	glColor4f(1.0, 0.0, 0.0, 1.0);
	glutSolidSphere(2.0, 8, 8);

	my_shader.unbind();

	glutSwapBuffers();
	angle += (angle < 360.0f) ? (1.0f) : (-360.0f);
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
	glutCreateWindow("GLSL Simple Shader");

	init();

	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(reshape);

	glutMainLoop();
	return 0;
}