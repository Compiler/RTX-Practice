#version 460
layout(location = 0) in vec2 o_texCoords;
layout(location = 0) out vec4 outColor;

void main(){
    outColor = texture(0, o_texCoords.xy);
    //outColor = vec4(1, 1, 1, 1);
}
