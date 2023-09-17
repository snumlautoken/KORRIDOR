#version 440 core
layout(location = 0) in vec3 position;
layout (location = 1) in vec3 norm;

out vec2 TexCoords;
out vec3 SurfaceNorm;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 scale;
uniform mat3 invModel;

mat3x2 pos2tex(vec3 normal) {
    mat2x3 ret = mat2x3(1);
    if (abs(normal.x) == 1) {
        ret[0] = vec3(0,1,0);
        ret[1] = vec3(0,0,1);
        return transpose(ret);
    } else if (abs(normal.y) == 1) {
        ret[0] = vec3(1,0,0);
        ret[1] = vec3(0,0,1);
        return transpose(ret);
    }
    return transpose(ret);
}

void main() {
    gl_Position = projection * view * model * vec4(position, 1.0);
    mat4x3 transfer = mat4x3(1);
    transfer[3] = vec3(0.5,0.5,0.5);
    TexCoords = pos2tex(norm) * scale * transfer * vec4(position, 1.0);
    SurfaceNorm = invModel * norm;
}
