#version 460

layout(location = 0) in vec2 a_position;
layout(location = 1) in vec4 a_color;
layout(location = 2) in vec3 a_texCoords;


layout(location = 0) out vec4 o_color;
layout(location = 1) out vec3 o_texCoords;

uniform mat4 u_cameraMatrix;

void main(){
    gl_Position = u_cameraMatrix * vec4(a_position, 0.0, 1.0);
    o_texCoords = a_texCoords;
    o_color = a_color;

}
