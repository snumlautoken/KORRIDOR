#pragma once
#include <string>
#include <GL/glew.h>
#include <GL/gl.h>

class Texture {
public:
    Texture() {
        tex = loadTex();
        normal = loadTex();
    };
    Texture(std::string file);
    Texture(std::string file, std::string normalFile);

    void bind();
private:
    GLuint tex;
    GLuint normal;
    GLuint loadTex(std::string file);
    GLuint loadTex();
};
