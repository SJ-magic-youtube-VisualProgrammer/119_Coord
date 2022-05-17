#version 120
#extension GL_ARB_texture_rectangle : enable
#extension GL_EXT_gpu_shader4 : enable

uniform sampler2DRect texture0;

/********************
0:FragCoord
1:TexCoord
2:mouse
********************/
uniform int check_id;

uniform vec2 u_resolution;
uniform vec2 u_mouse;

void main(){
/*
	vec2 st = gl_TexCoord[0].xy;
	vec4 color = texture2DRect(texture0, st);
	gl_FragColor = color;
	return;
*/

	vec2 st;
	
	if(check_id == 0)		st = gl_FragCoord.xy/u_resolution;
	else if(check_id == 1)	st = gl_TexCoord[0].xy/u_resolution;
	else					st = u_mouse/u_resolution;
	
	vec4 color = vec4(st.x, st.y, 0.0, 1.0);
	gl_FragColor = color * gl_Color;
}
