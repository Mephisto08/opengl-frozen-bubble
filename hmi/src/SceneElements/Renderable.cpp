#include "Renderable.h"

Renderable::Renderable(const std::vector<OBJMesh>& objMeshes) { //, Material material
    for (auto & objMesh : objMeshes) {
        this->meshes.emplace_back(
                objMesh.vertices, objMesh.atts, objMesh.indices
                ); //material.matDiffuse, material.matSpecular, material.shininess
    }
}

/*Renderable::Renderable(const std::vector<OBJMesh>& objMeshes, TextureMaterial& textureMaterial) {
    for (auto & objMeshe : objMeshes) {
        this->meshes.emplace_back(
                objMeshe.vertices, objMeshe.atts, objMeshe.indices, textureMaterial);
    }
}

Renderable::Renderable(std::vector<OBJMesh> objMeshes, std::vector<TextureMaterial> textureMaterials) {
    for (int i = 0; i < objMeshes.size(); i++) {
        this->meshes.emplace_back(
                objMeshes.at(i).vertices,
                objMeshes.at(i).atts,
                objMeshes.at(i).indices,
                textureMaterials.at(i));
    }
} */

void Renderable::render() {
    for (auto & mesh : meshes) {
        mesh.render();
    }
}


void Renderable::render(GLint id) {
    if (id != 0) {
        GLint locationModel = glGetUniformLocation(id, "model_m");

        glm::mat4 modelMatrix = this->getTransformMatrix();
        glUniformMatrix4fv(locationModel,1,GL_FALSE, &modelMatrix[0][0]);
    }

    for (auto & mesh : meshes) {
        mesh.render(id);
    }
}

/*void Renderable::render(ShaderProgram* shader, GLint id) {
    if (id != 0) {
        GLint locationModel = glGetUniformLocation(id, "model_m");

        glm::mat4 modelMatrix = this->getTransformMatrix();
        glUniformMatrix4fv(locationModel,1,GL_FALSE, &modelMatrix[0][0]);
    }

    for (auto & meshe : meshes) {
        GLuint currentTU = shader->getCurrentTU();
        meshe.render(id, currentTU);
        //shader->resetTU(0);
    }
} */

void Renderable::addMesh(std::vector<Vertex> vertices, std::vector<VertexAttribute> vertexAttributes, std::vector<Index> indices) {
    meshes.emplace_back(vertices, vertexAttributes, indices);
}
