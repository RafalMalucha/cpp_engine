#version 330 core

// Inputs from vertex buffer (VBO)
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

// Outputs to fragment shader
out vec3 FragPos;
out vec3 Normal;

// Uniforms (passed from C++)
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    // Calculate world-space position of vertex
    FragPos = vec3(model * vec4(aPos, 1.0));

    // Transform the normal correctly (using inverse transpose of model matrix)
    Normal = mat3(transpose(inverse(model))) * aNormal;

    // Final screen-space position
    gl_Position = projection * view * vec4(FragPos, 1.0);
}
