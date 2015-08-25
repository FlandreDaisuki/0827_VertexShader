#version 110
attribute vec3 offset;

uniform float angle; // 0 ~ 360

void main() {
	const float PI = 3.1415926;
	float rad = PI * (angle / 180.0); // 0 ~ 2*PI

	gl_FrontColor = vec4(1.0, 0.0, 0.0, 1.0) + abs(sin(rad)) * vec4(0.0, 0.5, 0.5, 0.0);
	vec4 new_pos = gl_Vertex + abs(sin(rad)) * vec4(offset, 0.0);

	gl_Position = gl_ModelViewProjectionMatrix * new_pos;
}