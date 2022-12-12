#ifndef SHADERENTWICKLUNG_CAMERA_H
#define SHADERENTWICKLUNG_CAMERA_H

#include "Transform.h"
#include <iostream>

class Camera: public Transform{
public:
    Camera(float width, float height, float v_opening, float near_clipping, float far_clipping, Transform* target);
    ~Camera() = default;

    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();

    void bind(GLint shaderID);

private:
    float width;
    float height;
    float v_opening;
    float near_clipping;
    float far_clipping;
    Transform* m_target;
    glm::mat4 view_matrix{};
    glm::mat4 proj_matrix{};
};


#endif //SHADERENTWICKLUNG_CAMERA_H
