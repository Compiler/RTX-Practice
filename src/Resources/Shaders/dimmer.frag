#version 460


layout(location = 0) in vec4 o_color;
layout(location = 1) in vec3 o_texCoords;

layout(location = 0) out vec4 outColor;

uniform sampler2D u_textures[32];
uniform float u_dimmer;

void main(){
    int index = int(o_texCoords.z + 0.5);
    outColor = texture(u_textures[index], o_texCoords.xy);
    outColor *= u_dimmer;
}
