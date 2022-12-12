#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertexData, std::vector<VertexAttribute> vertexAttributes, std::vector<Index> indexData) {
    this->vertexData = vertexData;
    this->vertexAttributes = vertexAttributes;
    this->indexData = indexData;

    setupMesh();
}

Mesh::Mesh(std::vector<Vertex> vertexData, std::vector<VertexAttribute> vertexAttributes, std::vector<Index> indexData, glm::vec3 matDiffuse, glm::vec3 matSpecular, float shininess) {
    this->vertexData = vertexData;
    this->vertexAttributes = vertexAttributes;
    this->indexData = indexData;
    this->matDiffuse = matDiffuse;
    this->matSpecular = matSpecular;
    this->shininess = shininess;

    setupMesh();
}

/*Mesh::Mesh(std::vector<Vertex> vertexData, std::vector<VertexAttribute> vertexAttributes, std::vector<Index> indexData) { //, TextureMaterial& texture
    this->vertexData = vertexData;
    this->vertexAttributes = vertexAttributes;
    this->indexData = indexData;
    //this->textureMaterial = texture;

    setupMesh();
} */

/*void Mesh::setTextureMaterial(TextureMaterial texture){
    this->textureMaterial = texture;
} */


void Mesh::render() {
    // activate VAO //
    glBindVertexArray(vaoID);
    // render call //
    glDrawElements(GL_TRIANGLES, indexData.size(), GL_UNSIGNED_INT, nullptr);

    // good programmers should reset //
    glBindVertexArray(0);
}

void Mesh::render(GLint id){
    if (id != 0) {
        GLint matDiffuseLocation = glGetUniformLocation(id, "material.diffuse");
        GLint matSpecularLocation = glGetUniformLocation(id, "material.specular");
        GLint fShinyLocation = glGetUniformLocation(id, "material.shininess");

        glUniform3fv(matDiffuseLocation, 1, &this->matDiffuse[0]);
        glUniform3fv(matSpecularLocation, 1, &this->matSpecular[0]);
        glUniform1f(fShinyLocation, this->shininess);
    }

    // activate VAO //
    //glBindVertexArray(vaoID);
    // render call //
    glDrawElements(GL_TRIANGLES, indexData.size(), GL_UNSIGNED_INT, nullptr);

    //glActiveTexture(currentTU);

    // good programmers should reset //
    //glBindVertexArray(0);
}

/*void Mesh::render(GLint id, GLuint currentTU){
    if (id != 0) {
        GLint texDiffuseLocation = glGetUniformLocation(id, "material.diffuse");
        GLint texSpecularLocation = glGetUniformLocation(id, "material.specular");
        GLint texEmissiveLocation = glGetUniformLocation(id, "material.emissive");
        GLint fShininessLocation = glGetUniformLocation(id, "material.shininess");
        GLint texMultiLocation = glGetUniformLocation(id, "material.texMulti");

        this->textureMaterial.getTextureDiffuse().bind(id, texDiffuseLocation, currentTU + 1);
        this->textureMaterial.getTextureSpecular().bind(id, texSpecularLocation, currentTU + 2);
        this->textureMaterial.getTextureEmissive().bind(id, texEmissiveLocation, currentTU + 3);

        glUniform1f(fShininessLocation, this->textureMaterial.getShininess());
        glUniform1f(texMultiLocation, this->textureMaterial.getTexMulti());
    }

    // activate VAO //
    glBindVertexArray(vaoID);
    // render call //
    glDrawElements(GL_TRIANGLES, indexData.size(), GL_UNSIGNED_INT, nullptr);

    //glActiveTexture(currentTU);

    // good programmers should reset //
    glBindVertexArray(0);
} */

void Mesh::setupMesh() {

    // setup VAO //
    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);
    // setup VBO //
    glGenBuffers(1, &vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(Vertex), &vertexData[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, vertexAttributes.at(0).n, GL_FLOAT, false, vertexAttributes.at(0).stride, (void*)vertexAttributes.at(0).offset);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, vertexAttributes.at(1).n, GL_FLOAT, false, vertexAttributes.at(1).stride, (void*)vertexAttributes.at(1).offset);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, vertexAttributes.at(2).n, GL_FLOAT, false, vertexAttributes.at(2).stride, (void*)vertexAttributes.at(2).offset);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(3, vertexAttributes.at(3).n, GL_FLOAT, false, vertexAttributes.at(3).stride, (void*)vertexAttributes.at(3).offset);
    glEnableVertexAttribArray(3);
    
    // setup IBO //
    GLuint iboID;
    glGenBuffers(1, &iboID); //only works after glGenVertexArrays();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexData.size() * sizeof(Index), indexData.data(), GL_STATIC_DRAW);

    //initial opengl state
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}
