#version 460

layout(location = 0) in vec2 o_texCoords;

layout(location = 0) out vec4 outColor;


uniform sampler2D textureVal;

void main(){
    outColor = texture(textureVal, o_texCoords.xy);
    outColor.r = 1;
    //outColor = vec4(1,0,0,1);
}
