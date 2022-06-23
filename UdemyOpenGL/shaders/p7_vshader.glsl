#version 330

layout (location = 0) in vec3 pos;
uniform float offsetX;

void main()
{
    gl_Position = vec4(0.5 * pos.x + offsetX, 0.5 * pos.y, pos.z, 1.0);
}