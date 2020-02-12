#version 330

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;
layout(location = 3) in vec3 data;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

// Uniforms for light properties
uniform vec3 light_position;
uniform vec3 eye_position;
uniform float material_kd;
uniform float material_ks;
uniform uint material_shininess;
uniform float Time;

uniform vec3 object_color;

// Output value to fragment shader
out vec3 color;

void main()
{
	// TODO: compute world space vectors
	vec3 pos = vec3(1);
	
	if(data.z == 0){
	pos = vec3(v_position.x + cos(1.5 * 0.5 * data.x *Time + data.x)*cos(data.y)/28.f, v_position.y + cos(1.5* 0.5 * data.x* Time + data.x)*sin(data.y)/28.f, v_position.z);
	} else if(data.z == 1){
	pos = vec3(v_position.x - cos(1.5*0.5 * data.x * Time + data.x + 3.14f)*cos(data.y)/28.f, v_position.y - cos(1.5*0.5 * data.x*Time + data.x + 3.14f)*sin(data.y)/28.f, v_position.z);
	}else{
		pos = v_position;
	}
	vec3 world_pos = (Model * vec4(v_position,1)).xyz;
	vec3 N = normalize( mat3(Model) * v_normal );
	vec3 L = normalize( light_position - world_pos );
	vec3 V = normalize( eye_position - world_pos );
	vec3 H = normalize( L + V );

	// TODO: define ambient light component
	float ambient_light = material_kd * 0.3;
	
	// TODO: compute diffuse light component
	float diffuse_light = material_kd * max(dot(N, L), 0);

	// TODO: compute specular light component
	float specular_light = 0;

	if (diffuse_light > 0)
	{
		specular_light = material_ks * pow(max(dot(N, H), 0), material_shininess)/100.0;
	}

	float d = distance (world_pos, light_position);
	// TODO: compute light
	float light = ambient_light + (diffuse_light + specular_light) /(0.00001 + 0.00001*d + 0.0000075*d*d);
	// TODO: send color light output to fragment shader

	float r = sqrt(pos.x * pos.x + pos.y * pos.y) - 1;
	vec3 coloor = vec3(0,1,0);
	if(data.z == 1){
		coloor = vec3(1,0,0);
	}
	vec3 v_color = object_color + vec3(r*3,r*3,r*3);
	if(r < 0){
	v_color = object_color + 2*vec3(r*3,r*3,r*3);
	}
	color = light * v_color;

	gl_Position = Projection * View * Model * vec4(pos, 1.0);
}
