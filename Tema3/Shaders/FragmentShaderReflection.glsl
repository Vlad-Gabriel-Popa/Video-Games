#version 330
 
in vec2 texcoord;
in vec3 normal;
in vec4 world_pos;

layout(location = 0) out vec4 out_color;

uniform sampler2D tex1;
uniform samplerCube env_map;
uniform float reflection_factor;
uniform vec3 eye_position;

void main()
{
	vec3 V = normalize(world_pos.xyz - eye_position);

	vec3 reflected_vector = reflect(V, normalize(normal));

	vec4 color = texture2D(tex1, texcoord);

	vec4 reflected_color = texture(env_map, reflected_vector);
	
	vec3 colorr = mix(color.xyz, reflected_color.xyz, reflection_factor);
	
    out_color = vec4(colorr,1);
	
}