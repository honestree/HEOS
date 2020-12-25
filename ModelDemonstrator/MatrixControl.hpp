#pragma once
// Include GLFW
#include <GLFW/glfw3.h>
// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;


class MatrixControl{

    public:
        void ComputeMatricesFromInputs( GLFWwindow *);
        glm::mat4 GetProjMat();
        glm::mat4 GetViewMat();
    private:
        // Initial horizontal angle : toward -Z
        float horizontalAngle = 3.14f;
        // Initial vertical angle : none
        float verticalAngle = 0.0f;
        // Initial Field of View
        float initialFoV = 45.0f;

        float speed = 20.0f; // 3 units / second
        float mouseSpeed = 0.05f;
        // use spherical coordinate system
        float radius = 40;
        float theta = 0.78;
        float phi = 0.78;

        glm::mat4 ViewMatrix;
        glm::mat4 ProjectionMatrix;

};

