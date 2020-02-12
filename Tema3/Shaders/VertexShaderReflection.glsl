#version 330

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;
layout(location = 3) in vec3 v_color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform vec3 eye_position;

out vec2 texcoord;
out vec3 normal;
out vec4 world_pos;
void main()
{
	world_pos = Model * vec4(v_position, 1.0);
	texcoord = v_texture_coord;
	normal = normalize(v_normal);


	gl_Position = Projection * View * world_pos;
}
