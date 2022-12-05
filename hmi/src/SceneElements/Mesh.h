#ifndef SHADERENTWICKLUNG_MESH_H
#define SHADERENTWICKLUNG_MESH_H

#include "../../framework/CommonTypes.h"
#include "vector"
#include <memory>
#include <iostream>
//#include "TextureMaterial.h"

class Mesh {
public:
    Mesh(std::vector<Vertex> vertexData, std::vector<VertexAttribute> vertexAttributes, std::vector<Index> indexData);
    Mesh(std::vector<Vertex> vertexData, std::vector<VertexAttribute> vertexAttributes, std::vector<Index> indexData, glm::vec3 matDiffuse, glm::vec3 matSpecular, float shininess);
    //Mesh(std::vector<Vertex> vertexData, std::vector<VertexAttribute> vertexAttributes, std::vector<Index> indexData); //, TextureMaterial& texture)

    //void setTextureMaterial(TextureMaterial texture);

    // mesh data
    std::vector<Vertex> vertexData;
    std::vector<VertexAttribute> vertexAttributes;
    std::vector<Index> indexData;
    glm::vec3 matDiffuse = glm::vec3(0.0f);
    glm::vec3 matSpecular = glm::vec3(0.0f);
    float shininess = 0.0f;

    void render();
    void render(GLint id);
    void render(GLint id, GLuint currentTU);

private:
    void setupMesh();

    //TextureMaterial textureMaterial;
    GLuint vaoID{}, vboID{};
};


#endif //SHADERENTWICKLUNG_MESH_H
