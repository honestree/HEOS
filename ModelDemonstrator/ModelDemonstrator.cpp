//Include std
#include <stdio.h>
#include <stdlib.h>

//Include GLEW - Always include it before gl.h and glfw3.h, since it's a bit magic.
#include <GL/glew.h>
// Include GLFW
#include <GLFW/glfw3.h>
// Include GLM
#include <glm/glm.hpp>
//transform
#include <glm/gtc/matrix_transform.hpp>

#include "loadShader.hpp"
#include "MatrixControl.hpp"
#include "ModelDemonstrator.hpp"
#include "ModelLoader.hpp"

#define GLFW_DLL
#define OBJFILE "model.ply"

using namespace glm;

int ModelDemonstrator(){

    MatrixControl matrixController;

    // Initialise GLFW
    glewExperimental = true; // Needed for core profile
    if( !glfwInit() ){
        fprintf( stderr, "Failed to initialize GLFW\n" );
        return -1;
    }


	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL

	// Open a window and create its OpenGL context
	GLFWwindow* window; // (In the accompanying source code, this variable is global for simplicity)
	window = glfwCreateWindow( 1024, 768, "HEOS", NULL, NULL);
	if( window == NULL ){
    	fprintf( stderr, "Failed to open GLFW window.\n" );
	    glfwTerminate();
	    return -1;
	}
	glfwMakeContextCurrent(window); // Initialize GLEW
	glewExperimental=true; // Needed in core profile
	if (glewInit() != GLEW_OK) {
    	fprintf(stderr, "Failed to initialize GLEW\n");
	    return -1;
	}
	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // mouse movement
    glfwPollEvents();
    glfwSetCursorPos(window, 1024/2, 768/2);


    //create a Vertex Array Object
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    glEnable( GL_DEPTH_TEST );
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);

    std::vector<GLfloat> g_vertex_buffer_data;
    std::vector<GLfloat> g_color_buffer_data;

    ModelLoader( OBJFILE, g_vertex_buffer_data, g_color_buffer_data );
    
    // This will identify our vertex buffer
    GLuint vertexbuffer;
    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &vertexbuffer);
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, g_vertex_buffer_data.size() * sizeof( GLfloat ), g_vertex_buffer_data.data(), GL_STATIC_DRAW);

    GLuint colorbuffer;
    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, g_color_buffer_data.size() * sizeof( GLfloat ), g_color_buffer_data.data(), GL_STATIC_DRAW);

    GLuint programID = LoadShaders( "ModelDemonstrator/vertexshader", "ModelDemonstrator/fragmentshader" );

	do{
    	// Clear the screen. It's not mentioned before Tutorial 02, but it can cause flickering, so it's there nonetheless.
    	glClear( GL_COLOR_BUFFER_BIT );

	    // Get a handle for our "MVP" uniform
    	// Only during the initialisation
	    GLuint MatrixID = glGetUniformLocation(programID, "MVP");

        matrixController.ComputeMatricesFromInputs( window );

        glm::mat4 ProjectionMatrix = matrixController.GetProjMat();
        glm::mat4 ViewMatrix = matrixController.GetViewMat();
        glm::mat4 ModelMatrix = glm::mat4(1.0);
        glm::mat4 mvp = ProjectionMatrix * ViewMatrix * ModelMatrix;

    	// Send our transformation to the currently bound shader, in the "MVP" uniform
    	// This is done in the main loop since each model will have a different MVP matrix (At least for the M part)
    	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);

        // 1st attribute buffer : vertices
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
                0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                3,                  // size
                GL_FLOAT,           // type
                GL_FALSE,           // normalized?
                0,                  // stride
                (void*)0            // array buffer offset
                );


        // 2nd attribute buffer : colors
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
        glVertexAttribPointer(
                1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
                3,                                // size
                GL_FLOAT,                         // type
                GL_FALSE,                         // normalized?
                0,                                // stride
                (void*)0                          // array buffer offset
                );

        // Draw the triangle !
        glDrawArrays(GL_TRIANGLES, 0, g_color_buffer_data.size() *3); // Starting from vertex 0; 3 vertices total -> 1 triangle
        glDisableVertexAttribArray(0);

	    // Swap buffers
	    glfwSwapBuffers(window);
	    glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(programID);

    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(window) == 0 );
};

