#version 330

// TODO: get vertex attributes from each location
layout(location = 0) in vec3 v_position;
layout(location = 3) in vec3 v_norm;
layout(location = 2) in vec2 v_texcord;
layout(location = 1) in vec3 v_color;



// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform vec3 object_color;

uniform float material_kd;
// TODO: output values to fragment shader
out vec3 frag_color;
out vec3 frag_norm;
out vec3 frag_position;
out vec2 frag_texcord;



void main()
{
	// TODO: send output to fragment shader

	frag_color = object_color;
	frag_norm = v_norm;
	frag_position = v_position;
	frag_texcord = v_texcord;

	// TODO: compute gl_Position

	gl_Position = Projection * View * Model *  vec4(v_position, 1);

}
