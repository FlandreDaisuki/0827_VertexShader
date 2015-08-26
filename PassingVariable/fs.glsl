#version 110

varying vec4 specialColor;

void main() {
	if(gl_Color.g > 0.7) {
		gl_FragColor = specialColor;
	} else {
		gl_FragColor = gl_Color;
	}
}