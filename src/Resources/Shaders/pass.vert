#version 460

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_color;
layout(location = 2) in vec2 a_texCoords;


layout(location = 0) out vec2 o_texCoords;

uniform mat4 u_cameraMatrix;

void main(){
    gl_Position = u_cameraMatrix * vec4(a_position, 1.0);
    o_texCoords = a_texCoords;

}
