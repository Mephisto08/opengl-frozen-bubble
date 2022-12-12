#include "Camera.h"

Camera::Camera(float width, float height, float v_opening, float near_clipping, float far_clipping, Transform* target) {
    this->width = width;
    this->height = height;
    this->v_opening = v_opening;
    this->near_clipping = near_clipping;
    this->far_clipping = far_clipping;
    
}

glm::mat4 Camera::getViewMatrix() {
    glm::vec3 position = getPosition();
    /*if(m_target != nullptr) {
        if (this->getParent() != nullptr) {
            position = position + this->getParent()->getPosition();
        }
        glm::vec3 targetPos = m_target->getPosition();
        return glm::lookAt(glm::vec3(position.x, position.y, position.z), targetPos, getYAxis());
    } else {*/
        return glm::inverse(getMatrix());
    //}
}

glm::mat4 Camera::getProjectionMatrix() {
    auto aspect_ratio = this->width / this->height;
    return glm::perspective(glm::radians(this->v_opening), aspect_ratio, this->near_clipping, this->far_clipping);
}

void Camera::bind(GLint shaderID) {
    std::cout<< "Before if" << std::endl;
    std::cout<< "Shader ID:" << shaderID << std::endl;
    if (shaderID != 0) {
        std::cout<< "Get Location view" << std::endl;
        GLint viewMatrixLocation = glGetUniformLocation(shaderID, "view_m");
        std::cout<< "Get Location proj" << std::endl;
        GLint projectionMatrixLocation = glGetUniformLocation(shaderID, "projection_m");
        //GLint cameraPositionLoction = glGetUniformLocation(shaderID, "camPos");

        glm::mat4 viewMatrix = this->getViewMatrix();
        std::cout<< "View Matrix" << std::endl;
        glm::mat4 projectionMatrix = this->getProjectionMatrix();
        std::cout<< "Projection Matrix" << std::endl;
        //glm::vec3 cameraPosition = this->getPosition();

        glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
        glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]);
        //glUniform3fv(cameraPositionLoction, 1, &cameraPosition[0]);
    }
}