#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
// layout (location = 2) in uint aColorUint;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 FragPos;
out vec3 Normal;
//out vec4 vColor;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = normalize(mat3(transpose(inverse(model))) * aNormal);

    // Unpack RGBA from uint (assuming 0xRRGGBBAA format)
    // float r = float((aColorUint >> 24u) & 0xFFu) / 255.0;
    // float g = float((aColorUint >> 16u) & 0xFFu) / 255.0;
    // float b = float((aColorUint >> 8u) & 0xFFu) / 255.0;
    // float a = float(aColorUint & 0xFFu) / 255.0;

    // vColor = vec4(r, g, b, a);
} 