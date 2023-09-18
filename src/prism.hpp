#include "entity.hpp"
#include "renderable.hpp"

class Prism : public Entity, public Renderable {
public:
    Prism(glm::vec3 pos, float rot, glm::vec3 axis, glm::vec3 dim, Texture texture);
    glm::mat4 getModel();

    void setScale(glm::vec3 s) {scale = s; recalcModel();};
    void setTex(GLuint t) {tex = t; recalcModel();};
    void setRot(float r) {rot = r; recalcModel();};
    void setPos(glm::vec3 p) {pos = p; recalcModel();};
    void setAxis(glm::vec3 a) {axis = a; recalcModel();};

    void render() override;
    Shader getProgram() override {return program;}

    static void createRenderer(Shader sp) {
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(normals), nullptr, GL_STATIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(normals), normals);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*3, nullptr);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float)*3, (void*)(sizeof(vertices)));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        program = sp;
        program.use();
        program.loadUniform("tex", 0);
        program.loadUniform("projection", glm::perspective(glm::radians(45.0f), (float)1000 / (float)1000, 0.01f, 1000.0f));
        program.loadUniform("lightDir", glm::vec3(1,-1,1));
    };

    bool scaleTex = true;

private:
    glm::vec3 support(glm::vec3 dir) override;
    void recalcModel();
    void recalcVertices();
    glm::mat4 model;
    std::pair<glm::mat4,glm::mat4> vert;

    static Shader program;
    static GLuint vao;
    static GLuint vbo;

    static const float vertices[3*36];
    static const float normals[3*36];
};
