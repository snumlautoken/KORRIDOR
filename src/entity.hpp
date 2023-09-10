#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <deque>
#include <vector>
#include <iostream>
#include "texture.hpp"

struct collisionRes {
    bool collision;
    glm::vec3 penVec;
};

class Entity {
public:
    glm::vec3 getScale() {return scale;};
    GLuint getTex() {return tex;};
    float getRot() {return rot;};
    glm::vec3 getPos() {return pos;};
    glm::vec3 getAxis() {return axis;};

    void setScale(glm::vec3 s) {scale = s;};
    void setTex(GLuint t) {tex = t;};
    void setRot(float r) {rot = r;};
    void setPos(glm::vec3 p) {pos = p;};
    void setAxis(glm::vec3 a) {axis = a;};

    static collisionRes checkCollision(Entity& e1, Entity& e2) {
        glm::vec3 axis(1);
        glm::vec3 a = e1.support(axis) - e2.support(-axis);
        std::vector<glm::vec3> simplex {a};
        axis = -a;
        while (true) {
            a = e1.support(axis) - e2.support(-axis);
            if (glm::dot(a, axis) < 0) { return collisionRes(false,glm::vec3(0)); }
            simplex.push_back(a);
            auto res = nearestSimplex(simplex);
            if (res.collision) { break; }
            axis = res.penVec;
        }
        if (simplex[0] == simplex[1] || simplex[2] == simplex[3] || simplex[1] == simplex[3] || simplex[0] == simplex[3]) {
            return collisionRes(true,glm::vec3(0.001));
        }
        return collisionRes(true,expandingPolytope(simplex,e1,e2));
    }

    collisionRes checkCollision(Entity& e) {
        return checkCollision(*this, e);
    }

protected:
    virtual glm::vec3 support(glm::vec3 dir) = 0;
    glm::vec3 scale;
    GLuint tex;
    float rot;
    glm::vec3 pos;
    glm::vec3 axis;

private:
    static void printVec(glm::vec3 v) {
        std::cout << "(" << v.x << ", " << v.y << ", " << v.z << ")" << std::endl; 
    }

    static collisionRes nearestSimplex(std::vector<glm::vec3>& s) {
        if (s.size() == 2) { //Line case
            glm::vec3 ab = s.at(0) - s.at(1);
            glm::vec3 ao = -s.at(1);
            glm::vec3 dir;
            if (glm::dot(ab,ao) >= 0) { 
                dir = glm::cross(glm::cross(ab, ao), ab);
            } 
            else { 
                dir = ao;
                s = {s.at(1)};
            }
            return collisionRes(false, dir);
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

            return collisionRes(false, dir);
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
                return collisionRes(true, ao);
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

            return collisionRes(false, dir);
        }
    }

    struct Face {
        double distance;
        glm::vec3 normal;
        int index;
    };

    struct Edge {
        unsigned int a,b;
        const bool operator==(const Edge& rhs) {
            return (a == rhs.a && b == rhs.b) || (a == rhs.b && b == rhs.a);
        }
    };

    static glm::vec3 expandingPolytope(std::vector<glm::vec3> simplex, Entity& e1, Entity& e2) {
        std::vector<unsigned int> faces = {
            1,2,3,
            2,0,3,
            0,1,3,
            0,1,2
        };
        while (true) {
            Face e = closestFace(simplex, faces);
            glm::vec3 a = e1.support(e.normal) - e2.support(-e.normal);
            double d = glm::dot(e.normal,a);
            printVec(e.normal);
            std::cout << e.distance << std::endl;
            std::cout << d << std::endl;

            if (fabs(d - e.distance) < 0.4) {
                return e.normal*glm::vec3(e.distance);
            } else {
                std::vector<Edge> uniqueEdges;
                for (int i = 0; i < faces.size()/3; i++) {
                    if (glm::dot(getFace(simplex,faces,i).normal, a) > 0) {
                        addUnique(uniqueEdges, Edge(faces[i*3  ], faces[i*3+1]));
                        addUnique(uniqueEdges, Edge(faces[i*3+1], faces[i*3+2]));
                        addUnique(uniqueEdges, Edge(faces[i*3+2], faces[i*3  ]));

                        faces.erase(std::next(faces.begin(),i*3),std::next(faces.begin(),i*3+2));

                        i--;
                    }
                }

                std::vector<unsigned int> newFaces;
                for (Edge e : uniqueEdges) {
                    newFaces.push_back(e.a);
                    newFaces.push_back(e.b);
                    newFaces.push_back(simplex.size());
                }
                simplex.push_back(a);    
                faces.insert(faces.end(), newFaces.begin(), newFaces.end());
            }
        }
    }

    static Face closestFace(const std::vector<glm::vec3>& simplex,const std::vector<unsigned int>& faces) {
        Face res;
        int minTriangle = 0;
        float  minDistance = FLT_MAX;

        for (int i = 0; i < faces.size()/3; i++) {
            Face curr = getFace(simplex,faces,i);
            if (curr.distance < minDistance) {
                res = curr;
                res.index = i;
                minDistance = curr.distance;
            }
        }
        return res;
    }

    static Face getFace(const std::vector<glm::vec3>& simplex,const std::vector<unsigned int>& faces, unsigned int i) {
        glm::vec3 a = simplex[faces[i*3+2]];
        glm::vec3 b = simplex[faces[i*3+1]];
        glm::vec3 c = simplex[faces[i*3]];

        glm::vec3 normal = glm::normalize(glm::cross(b - a, c - a));
        float distance = glm::dot(normal, a);

        if (distance < 0) {
            normal = -normal;
            distance = -distance;
        }

        return Face(distance,normal);
    }

    static void addUnique(std::vector<Edge>& edges, Edge e) {
        for (auto it = edges.begin(); it != edges.end(); it++) {
            if ((e.a == it->a && e.b == it->b) || (e.a == it->b && e.b == it->a)) {
                edges.erase(it);
                return;
            }
        }
        edges.push_back(e);
    }

};
