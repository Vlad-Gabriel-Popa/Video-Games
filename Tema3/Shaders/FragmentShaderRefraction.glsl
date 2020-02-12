#version 330
 
in vec2 texcoord;
in vec3 normal;
in vec3 reflected_vector;
in vec3 refracted_vector;


layout(location = 0) out vec4 out_color;

uniform sampler2D tex1;
uniform samplerCube env_map;
uniform float refraction_factor;

void main()
{
	
	vec4 color = texture2D(tex1, texcoord);

	vec4 reflected_color = texture(env_map, reflected_vector);
	vec4 refracted_color = texture(env_map, refracted_vector);
	vec4 env_color = mix(reflected_color, refracted_color, refraction_factor);
	
    out_color = env_color;
	
}