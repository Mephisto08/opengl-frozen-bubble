#ifndef SHADERENTWICKLUNG_RENDERABLE_H
#define SHADERENTWICKLUNG_RENDERABLE_H

#include "Mesh.h"
#include "vector"
#include "Transform.h"
#include "iostream"
#include "../../framework/OBJLoader.h"

struct Material{
    glm::vec3 matDiffuse;
    glm::vec3 matSpecular;
    float shininess;
};

class Renderable: public Transform {

public:
    Renderable(const std::vector<OBJMesh>& objMeshes); //, Material material
    //Renderable(const std::vector<OBJMesh>& objMeshes, TextureMaterial& textureMaterial);
    //Renderable(std::vector<OBJMesh> objMeshes, std::vector<TextureMaterial> textureMaterials);

    void render();
    void render(GLint id);
    //void render(ShaderProgram* shader, GLint id);
    void addMesh(std::vector<Vertex> vertices, std::vector<VertexAttribute> vertexAttributes, std::vector<Index> indices);

private:
    std::vector<Mesh> meshes;
};


#endif //SHADERENTWICKLUNG_RENDERABLE_H
