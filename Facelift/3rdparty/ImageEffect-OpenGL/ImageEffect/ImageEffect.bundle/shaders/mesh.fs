precision highp float;

uniform sampler2D u_texture;
varying highp vec2 texcoordOut;
void main()
{
    vec4 srcColor = texture2D(u_texture, texcoordOut);
    gl_FragColor = srcColor;
}
