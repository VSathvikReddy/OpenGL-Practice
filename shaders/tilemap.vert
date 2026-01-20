#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec2 texOff;
layout (location = 4) in mat4 instanceModel;

out vec2 TexCoord;

uniform vec2 textureDimensions;
uniform mat4 view;
uniform mat4 projection;

void main(){
    gl_Position =  projection * view * instanceModel * vec4(aPos, 1.0);
    TexCoord = vec2(((aTexCoord.x + 0.5f)/textureDimensions.x) + texOff.x, ((aTexCoord.y + 0.5f)/textureDimensions.y) + texOff.y);
} 