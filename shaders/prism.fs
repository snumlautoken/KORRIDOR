#version 440 core

in vec2 TexCoords;
in vec3 SurfaceNorm;

out vec4 outColor;

uniform sampler2D tex;
uniform vec3 lightDir;

void main() {
    float diff = max(dot(normalize(SurfaceNorm), normalize(-lightDir)), 0.0);
    outColor = (0.5+diff/2)*texture(tex, TexCoords);
}
