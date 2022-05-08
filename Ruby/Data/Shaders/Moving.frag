 #version 120
uniform sampler2D u_TextureSampler;

varying vec4 v_Color;
varying vec2 v_UVCoord;

void main()
{
	vec4 color = texture2D(u_TextureSampler, v_UVCoord);
    
	gl_FragColor = color;
}
