#version 440 core
layout(location = 0) in vec3 position;
layout (location = 1) in vec3 norm;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 scale;

mat3x2 pos2tex(vec3 normal) {
    mat2x3 ret = mat2x3(1);
    if (abs(normal.x) == 1) {
        ret[0] = vec3(0,normal.x,0);
        ret[1] = vec3(0,0,normal.x);
        return transpose(ret);
    } else if (abs(normal.y) == 1) {
        ret[0] = vec3(normal.y,0,0);
        ret[1] = vec3(0,0,normal.y);
        return transpose(ret);
    }
    return transpose(ret);
}

void main() {
    gl_Position = projection * view * model * vec4(position, 1.0);
    TexCoords = pos2tex(norm) * (scale * position);
}
