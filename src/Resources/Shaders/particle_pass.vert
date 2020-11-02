#version 460 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aOffset;

layout(location = 0)  out vec4 oColor;

uniform mat4 u_cameraMatrix;

void main()
{   
    vec4 position = vec4(aPos + aOffset, 0.0, 1.0);
    gl_Position = u_cameraMatrix * position;
    //gl_Position = vec4(aPos + aOffset, 0.0, 1.0);
    oColor = aColor;
} 