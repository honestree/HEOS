#include "MatrixControl.hpp"
#define GLFW_DLL

void MatrixControl::ComputeMatricesFromInputs( GLFWwindow * thiswin ){
    double xpos, ypos;
    int winwid, winhei;
    glfwGetCursorPos( thiswin, &xpos, &ypos );
    glfwGetWindowSize( thiswin, &winwid, &winhei );
    glfwSetCursorPos( thiswin ,((float)winwid) /2,((float)winhei)/2 );
    static double lastTime = glfwGetTime();
    static vec3 right = glm::vec3( 0 , 1 , 0 );

    // compute fps
    double currentTime = glfwGetTime();
    float deltaTime = float(currentTime - lastTime);

    // Compute new orientation
    if( fmod( theta ,  2 * M_PI ) < M_PI ){
        phi -= mouseSpeed * deltaTime * float( (float)winwid/2 - xpos );
    }
    else{
        phi += mouseSpeed * deltaTime * float( (float)winwid/2 - xpos );
    }
    theta   -= mouseSpeed * deltaTime * float( (float)winhei/2 - ypos );

    // Right vector
    right = glm::vec3( -1 * sin(phi), cos(phi), 0 );

    // Move outward
    if (glfwGetKey( thiswin , GLFW_KEY_UP ) == GLFW_PRESS){
        radius *= ( 1 + speed );
    }
    // Move inward
    if (glfwGetKey( thiswin, GLFW_KEY_DOWN ) == GLFW_PRESS){
        radius *= (1 - speed);
    }

    glm::vec3 position = vec3(
                radius * sin( theta ) * cos( phi ),
                radius * sin( theta ) * sin( phi ),
                radius * cos( theta )
            );

    // Up vector : perpendicular to both direction and right
    glm::vec3 up = glm::cross( right, position );

    float FoV = initialFoV;
    // Projection matrix : 45&deg; Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    ProjectionMatrix = glm::perspective(glm::radians(FoV), (float)winwid / (float)winhei, 0.1f, 900.0f);
    // Camera matrix
    ViewMatrix = glm::lookAt(
                position,           // Camera is here
                vec3(0,0,0),        // and looks here : at the same position, plus "direction"
                up                  // Head is up (set to 0,-1,0 to look upside-down)
            );

    lastTime = currentTime;
}

glm::mat4 MatrixControl::GetProjMat(){ return ProjectionMatrix; };

glm::mat4 MatrixControl::GetViewMat(){ return ViewMatrix; };
