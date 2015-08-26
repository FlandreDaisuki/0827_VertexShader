#version 110

uniform mat4 modelviewMat; // for Custumize 1
uniform mat4 projMat; // for Custumize 1

varying vec4 specialColor;

void main() {

	///////////
	// Color //
	///////////

	//different effect between GL_SMOOTH and GL_FLAT;
	if(gl_Vertex.x > 0.0) {
		gl_FrontColor = vec4(0.9, 0.1, 0.9, 1.0);
	} else {
		gl_FrontColor = vec4(0.1, 0.9, 0.9, 1.0);
	}

	specialColor = vec4(0.5, 0.5, 0.5, 1.0); //gray

	////////////////////////
	// Position Transform //
	////////////////////////

	/* No change 1 */
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

	/* No change 2 */
	//gl_Position = ftransform();

	/* Custumize 1 */
	//gl_Position = projMat * modelviewMat * gl_Vertex;

	/* Custumize 2 */
	//vec4 new_pos = gl_Vertex + vec4(1.0, 0.0, 0.0, 0.0);
	//gl_Position = gl_ModelViewProjectionMatrix * new_pos;
}