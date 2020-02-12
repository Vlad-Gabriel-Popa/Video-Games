#version 330

in vec2 texcoord;
in vec3 world_position;
in vec3 world_normal;

uniform vec3 light_direction;
uniform vec3 light_position1;
uniform vec3 light_position2;
uniform vec3 light_position3;
uniform vec3 eye_position;

uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;
uniform float angle;

uniform sampler2D heightMap;
uniform sampler2D tex1;
uniform sampler2D tex2;

layout(location = 0) out vec4 out_color;

void main()
{
	float height = texture2D(heightMap, texcoord).r;
	
	// TODO: write pixel out color
	vec4 color1 = texture2D(tex1, 30*texcoord);
	vec4 color2 = texture2D(tex2, 30*texcoord);

	vec4 color;
	float left = 0.1f;
	float right = 0.2f;

	if(height < left){
		color = color1;
	} else if(height < right){
		color = mix(color1, color2, (height - left)/(right-left));	
	} else{
	    color = color2;
	}
	
	vec3 N = normalize(world_normal);	
	vec3 V = normalize( eye_position - world_position );
	vec3 L1 = normalize( light_position1 - world_position );
	vec3 H1 = normalize( L1 + V );
	vec3 L2 = normalize( light_position2 - world_position );
	vec3 H2 = normalize( L2 + V );
	vec3 L3 = normalize( light_position3 - world_position );
	vec3 H3 = normalize( L3 + V );

	float cut_off = radians(angle);
	vec3 direction = normalize(light_direction);
	float spot_light1 = dot(-L2, direction);
	float spot_light2 = dot(-L3, direction);
	float spot_light_limit = cos(cut_off);
 
	// Quadratic attenuation
	float linear_att1 = (spot_light1 - spot_light_limit) / (1 - spot_light_limit);
	float linear_att2 = (spot_light2 - spot_light_limit) / (1 - spot_light_limit);
	float light_att_factor1 = pow(linear_att1, 2);
	float light_att_factor2 = pow(linear_att2, 2);

	float ambient_light = 0;
	float diffuse_light1 = 0;
	float specular_light1 = 0;
	float diffuse_light2 = 0;
	float specular_light2 = 0;
	float d1 = distance (world_position, light_position1);
	float d2 = distance (world_position, light_position2);
	float d3 = distance (world_position, light_position3);

	float light = 0;
	ambient_light =  material_kd * 0.2;

	if(spot_light1 > cos(cut_off)){

			diffuse_light1 =  light_att_factor1 * material_kd * max(dot(N, L2), 0);

			specular_light1 = 0;

			if (diffuse_light1 > 0)
			{
				specular_light1 = light_att_factor1* material_ks * pow(max(dot(N, H2), 0), material_shininess);
			}

		}
	
	if(spot_light2 > cos(cut_off)){

			diffuse_light2 =  light_att_factor2 * material_kd * max(dot(N, L3), 0);

			specular_light2 = 0;

			if (diffuse_light2 > 0)
			{
				specular_light2 = light_att_factor2* material_ks * pow(max(dot(N, H3), 0), material_shininess);
			}

		}

	light = ambient_light + (diffuse_light1 + specular_light1) /(0.016 + 0.03*d2 + 0.05*d2*d2) + (diffuse_light2 + specular_light2) /(0.016 + 0.03*d3 + 0.05*d3*d3) + (material_kd) * max(dot(N, L1), 0)/(0.7 + 0.001*d1 + 0.001*d1*d1);

	out_color = vec4(light * color.xyz,1);
}