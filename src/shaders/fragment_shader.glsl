#version 330 core

in vec3 FragPos;   // From vertex shader
in vec3 Normal;    // From vertex shader

out vec4 FragColor;

// Uniforms
uniform vec3 lightDir;     // Direction of the light (e.g. sun)
uniform vec3 lightColor;   // Color/intensity of the light
uniform vec3 objectColor;  // Base color of the object

void main() {
    // Normalize inputs
    vec3 norm = normalize(Normal);
    vec3 lightDirNorm = normalize(lightDir);

    // Diffuse lighting (Lambert's cosine law)
    float diff = max(dot(norm, lightDirNorm), 0.0);
    vec3 diffuse = diff * lightColor;

    // Final color
    vec3 result = diffuse * objectColor;
    FragColor = vec4(result, 1.0);
}
