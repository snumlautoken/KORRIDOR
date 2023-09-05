#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <deque>
#include <vector>
#include <iostream>

class Entity {
public:
    glm::vec3 getScale() {return scale;};
    GLuint getTex() {return tex;};
    float getRot() {return rot;};
    glm::vec3 getPos() {return pos;};
    glm::vec3 getAxis() {return axis;};

    static bool checkCollision(Entity& e1, Entity& e2) {
        glm::vec3 axis = e1.getPos() - e2.getPos();
        if (glm::length(axis) != 0) {return true;}
        glm::vec3 a = e1.support(axis) - e2.support(-axis);
        std::vector<glm::vec3> simplex {a};
        axis = -a;

        while(glm::length(axis) != 0) {
            a = e1.support(axis) - e2.support(-axis);
            if (glm::dot(a, axis) < 0) { return false; }
            simplex.push_back(a);
            auto res = nearestSimplex(simplex);
            if (res.first) { break; }
            axis = res.second;
        }
        return true;
    }

    bool checkCollision(Entity& e) {
        return checkCollision(*this, e);
    }

    void setScale(glm::vec3 s) {scale = s;};
    void setTex(GLuint t) {tex = t;};
    void setRot(float r) {rot = r;};
    void setPos(glm::vec3 p) {pos = p;};
    void setAxis(glm::vec3 a) {axis = a;};


protected:
    virtual glm::vec3 support(glm::vec3 dir) = 0;
    glm::vec3 scale;
    GLuint tex;
    float rot;
    glm::vec3 pos;
    glm::vec3 axis;

private:
    static void printVec(glm::vec3& v) {
        std::cout << "(" << v.x << ", " << v.y << ", " << v.z << ")" << std::endl; 
    }

    static std::pair<bool,glm::vec3> nearestSimplex(std::vector<glm::vec3>& s) {
        if (s.size() == 2) { //Line case
            glm::vec3 ab = s.at(0) - s.at(1);
            glm::vec3 ao = -s.at(1);
            glm::vec3 dir;
            if (glm::dot(ab,ao) >= 0) { dir = glm::cross(glm::cross(ab, ao), ab); } 
            else { 
                dir = ao;
                s = {s.at(1)};
            }
            return std::make_pair(false, dir);
        } else if (s.size() == 3) { //Triangle case
            glm::vec3 a = s.at(2);
            glm::vec3 b = s.at(1);
            glm::vec3 c = s.at(0);

            glm::vec3 ab = b - a;
            glm::vec3 ac = c - a;
            glm::vec3 ao = -a;
            glm::vec3 abc = glm::cross(ab, ac);
            glm::vec3 dir;

            if (glm::dot(glm::cross(abc, ac), ao) > 0) {
                if (glm::dot(ac, ao) > 0) { 
                    dir = glm::cross(glm::cross(ac, ao), ac);
                    s = {c, a};
                } else {
                    if (glm::dot(ab,ao) > 0) {
                        dir = glm::cross(glm::cross(ab, ao), ab);
                        s = {b,a};
                    } else {
                        dir = ao;
                        s = {a};
                    }
                }
            } else {
                if (glm::dot(glm::cross(ab, abc), ao) > 0) {
                    if (glm::dot(ab,ao) > 0) {
                        dir = glm::cross(glm::cross(ab, ao), ab);
                        s = {b,a};
                    } else {
                        dir = ao;
                        s = {a};
                    }
                } else {
                    if (glm::dot(abc, ao) > 0) {
                        dir = abc;
                        s = {b,c,a};
                    } else {
                        dir = -abc;
                    }
                }
            }

            return std::make_pair(false, dir);
        } else { //Tetrahedron case
            glm::vec3 a = s.at(3);
            glm::vec3 b = s.at(2);
            glm::vec3 c = s.at(1);
            glm::vec3 d = s.at(0);

            glm::vec3 ab = b - a;
            glm::vec3 ac = c - a;
            glm::vec3 ad = d - a;
            glm::vec3 ao = -a;
            glm::vec3 abc = glm::cross(ab, ac);
            glm::vec3 adb = glm::cross(ad, ab);
            glm::vec3 acd = glm::cross(ac, ad);
            glm::vec3 dir;

            std::vector<glm::vec3> outTriangles;
            std::vector<glm::vec3> ver;

            if (glm::dot(abc, ao) < 0) {
                outTriangles.push_back(abc);
                ver.insert(ver.end(), {b,c});
            }
            if (glm::dot(adb, ao) < 0) {
                outTriangles.push_back(adb);
                ver.insert(ver.end(), {d,b});
            }
            if (glm::dot(acd, ao) < 0) {
                outTriangles.push_back(acd);
                ver.insert(ver.end(), {c,d});
            }

            switch (outTriangles.size())
            {
            case 0:
                return std::make_pair(true, ao);
                break;
            case 1:
                dir = -outTriangles[0];
                s = {ver[1],ver[0],a};
                break;
            case 2:
                dir = glm::vec3(-0.5)*(outTriangles[0]+outTriangles[1]);
                if (ver[1]==ver[2]) {
                    s = {c,a};
                } else {
                    s = {ver[0],a};
                }
                break;
            default:
                dir = ao;
                s = {a};
                break;
            }

            return std::make_pair(false, dir);
        }
    }
};
