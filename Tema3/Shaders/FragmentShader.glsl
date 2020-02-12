#version 330
 

 
in vec2 texcoord;

layout(location = 0) out vec4 out_color;

uniform sampler2D tex1;
uniform sampler2D tex2;

uniform int two_text;
uniform int is_globe;
uniform float Time;

void main()
{
	// TODO : calculate the out_color using the texture2D() function
	
	if(two_text == 1){
		vec4 color1 = texture2D(tex1, texcoord); 
			if(color1.a < 0.5f){
			discard;
		}
		vec4 color2 = texture2D(tex2, texcoord);
			if(color2.a < 0.5f){
			discard;
		}
		vec3 color = mix(color1.xyz, color2.xyz, 0.5f);

		out_color = vec4(color,1);

	} else{
		vec4 colorr; 
		if(is_globe == 1){
			colorr = texture2D(tex1, vec2(texcoord.x + Time, texcoord.y));
		} else{
			colorr = texture2D(tex1, texcoord);
		}
			if(colorr.a < 0.5f){
			discard;
		}
		out_color = colorr;
	}
}