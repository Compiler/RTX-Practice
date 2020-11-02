#version 460

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec2 a_texCoords;


layout(location = 0) out vec2 o_texCoords;
void main(){
    gl_Position = vec4(a_position, 1.0);
    o_texCoords = a_texCoords;

}
