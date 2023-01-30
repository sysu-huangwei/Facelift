attribute vec2 a_position;
attribute vec2 a_position_std;
varying vec2 texcoordOut;

void main()
{
   texcoordOut = a_position_std;
    float x = a_position.x * 2.0 - 1.0;
    float y = 1.0 - a_position.y * 2.0;
   gl_Position = vec4(x, y, 0.0, 1.0);
}
