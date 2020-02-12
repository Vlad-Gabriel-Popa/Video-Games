#version 330

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;
layout(location = 3) in vec3 v_color;

uniform sampler2D heightMap;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform vec2 mapSize;

out vec2 texcoord;
out vec3 world_position;
out vec3 world_normal;

void main()
{
	// TODO : pass v_texture_coord as output to Fragment Shader

	texcoord = v_texture_coord;
	float height = texture2D(heightMap, texcoord).r;

	vec3 pos = v_position;
	pos.y =  height * 0.2f;
	
	vec2 texelSize = vec2(1.0/mapSize.x, 1.0/mapSize.y);
	float heightRight = texture2D(heightMap, vec2(texcoord.x + texelSize.x, texcoord.y)).r;
	float heightUp = texture2D(heightMap, vec2(texcoord.x, texelSize.y + texcoord.y)).r;
	float Hx = height - heightRight;
	float Hz = height - heightUp;

	world_normal = normalize(vec3(Hx, 1, Hz));
	world_position = (Model * vec4(pos, 1.0)).xyz;

	gl_Position = Projection * View * Model * vec4(pos, 1.0);

}
