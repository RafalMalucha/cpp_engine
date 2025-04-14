#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 FragColor;

uniform vec3 lightDir;
uniform vec3 lightColor;
uniform vec3 baseColor;
uniform sampler2D baseColorTexture;
uniform bool hasBaseColorTexture;

void main() {
    vec3 norm = normalize(Normal);
    vec3 lightDirNorm = normalize(lightDir);

    // Basic diffuse lighting
    float diff = max(dot(norm, lightDirNorm), 0.0);
    vec3 diffuse = diff * lightColor;

    // Ambient light
    vec3 ambient = 0.1 * lightColor;

    // Surface color from texture or baseColor
    vec3 surfaceColor = hasBaseColorTexture
        ? texture(baseColorTexture, TexCoords).rgb
        : baseColor;

    // Combine
    vec3 result = (ambient + diffuse) * surfaceColor;
    result = clamp(result, 0.0, 1.0);

    FragColor = vec4(result, 1.0);
}
