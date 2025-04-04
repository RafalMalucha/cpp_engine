#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 FragColor;

// Uniforms
uniform vec3 lightDir;
uniform vec3 lightColor;
uniform vec3 baseColor;            
uniform sampler2D baseColorTexture;
uniform bool hasBaseColorTexture; 

void main() {
    vec3 norm = normalize(Normal);
    vec3 lightDirNorm = normalize(lightDir);

    float diff = max(dot(norm, lightDirNorm), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 surfaceColor = hasBaseColorTexture
        ? texture(baseColorTexture, TexCoords).rgb
        : baseColor;

    vec3 result = diffuse * surfaceColor;

    FragColor = texture(baseColorTexture, TexCoords);
}
