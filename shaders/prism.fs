#version 440 core

in vec2 TexCoords;
in vec3 SurfaceNorm;

out vec4 outColor;

uniform sampler2D tex;
uniform sampler2D texNorm;
uniform vec3 lightDir;

void main() {
    vec3 lightLoc = vec3(1,1,1);
    vec3 normal = texture(texNorm, TexCoords).rgb;
    //normal = normalize(normal * 2.0 - 1.0);
    float diff = max(dot(normalize(SurfaceNorm), normalize(-lightDir)), 0.0);
    vec3 color = texture(tex, TexCoords).rgb;
    outColor = vec4((0.5+diff/2)*color,1);
}
