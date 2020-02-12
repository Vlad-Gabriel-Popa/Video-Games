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
out vec3 reflected_vector;
out vec3 refracted_vector;

void main()
{
	vec4 world_pos = Model * vec4(v_position, 1.0);
	texcoord = v_texture_coord;
	normal = v_normal;

	vec3 V = normalize(world_pos.xyz - eye_position);
	vec3 N = normalize(v_normal);
	reflected_vector = reflect(V, N);
	refracted_vector = refract(V, N, 1.0/1.33);

	gl_Position = Projection * View * world_pos;
}
