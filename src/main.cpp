#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "init.h"
#include "shader.h"
#include "image.h"
#include "linal.h"

#include <iostream>
#include <math.h>

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


void processInput(GLFWwindow *window);

// camera
glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

int main(){
    GLFWwindow* window = make_window();
    Shader lightCubeShader(DEFAULT_VERTEX_SHADER,LIGHT_FRAGMENT_SHADER);
    Shader lightingShader(DEFAULT_VERTEX_SHADER,DEFAULT_FRAGMENT_SHADER);
    
    
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
float vertices[] = {
    // positions          // normals
    // Front face (+Z)
    -0.5f,-0.5f, 0.5f,     0.0f, 0.0f, 1.0f,
     0.5f,-0.5f, 0.5f,     0.0f, 0.0f, 1.0f,
     0.5f, 0.5f, 0.5f,     0.0f, 0.0f, 1.0f,
    -0.5f, 0.5f, 0.5f,     0.0f, 0.0f, 1.0f,

    // Back face (-Z)
     0.5f,-0.5f,-0.5f,     0.0f, 0.0f,-1.0f,
    -0.5f,-0.5f,-0.5f,     0.0f, 0.0f,-1.0f,
    -0.5f, 0.5f,-0.5f,     0.0f, 0.0f,-1.0f,
     0.5f, 0.5f,-0.5f,     0.0f, 0.0f,-1.0f,

    // Left face (-X)
    -0.5f,-0.5f,-0.5f,    -1.0f, 0.0f, 0.0f,
    -0.5f,-0.5f, 0.5f,    -1.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.5f,    -1.0f, 0.0f, 0.0f,
    -0.5f, 0.5f,-0.5f,    -1.0f, 0.0f, 0.0f,

    // Right face (+X)
     0.5f,-0.5f, 0.5f,     1.0f, 0.0f, 0.0f,
     0.5f,-0.5f,-0.5f,     1.0f, 0.0f, 0.0f,
     0.5f, 0.5f,-0.5f,     1.0f, 0.0f, 0.0f,
     0.5f, 0.5f, 0.5f,     1.0f, 0.0f, 0.0f,

    // Bottom face (-Y)
    -0.5f,-0.5f,-0.5f,     0.0f,-1.0f, 0.0f,
     0.5f,-0.5f,-0.5f,     0.0f,-1.0f, 0.0f,
     0.5f,-0.5f, 0.5f,     0.0f,-1.0f, 0.0f,
    -0.5f,-0.5f, 0.5f,     0.0f,-1.0f, 0.0f,

    // Top face (+Y)
    -0.5f, 0.5f, 0.5f,     0.0f, 1.0f, 0.0f,
     0.5f, 0.5f, 0.5f,     0.0f, 1.0f, 0.0f,
     0.5f, 0.5f,-0.5f,     0.0f, 1.0f, 0.0f,
    -0.5f, 0.5f,-0.5f,     0.0f, 1.0f, 0.0f,
};
    unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3,

        4, 5, 6,
        4, 6, 7,

        8, 9, 10,
        8, 10, 11,

        12, 13, 14,
        12, 14, 15,

        16, 17, 18,
        16, 18, 19,

        20, 21, 22,
        20, 22, 23
    };


    unsigned int VBO, cubeVAO, EBO;
    make_buffer(&VBO, &cubeVAO, &EBO, vertices, sizeof(vertices), indices, sizeof(indices));

    unsigned int lightCubeVAO;
    make_buffer(&VBO, &lightCubeVAO, &EBO, vertices, sizeof(vertices), indices, sizeof(indices));




    // glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);  
    //glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    // glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
    // glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f); 
    // glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
    // glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);
    //Matrix mul for view 

    // glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);

    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
    while(!glfwWindowShouldClose(window)){
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // be sure to activate shader when setting uniforms/drawing objects

        lightingShader.use();
        lightingShader.setVec3("lightPos", lightPos.x,lightPos.y,lightPos.z);  
        lightingShader.setVec3("viewPos", cameraPos.x,cameraPos.y,cameraPos.z); 
        lightingShader.setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
        lightingShader.setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
        lightingShader.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
        lightingShader.setFloat("material.shininess", 32.0f);
        
        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view;                                      //CameraUp
        view = glm::lookAt(cameraPos, cameraFront+cameraPos, glm::vec3(0.0, 1.0, 0.0));
        lightingShader.setMat4("projection", &projection[0][0]);
        lightingShader.setMat4("view", &view[0][0]);

        // world transformation
        glm::mat4 model = glm::mat4(1.0f);
        float angle = (float)glfwGetTime() * glm::radians(50.0f);
        auto axis =  glm::vec3(0.0f, 1.0f, sin((float)glfwGetTime()));
        model = glm::rotate(model, angle, glm::normalize(axis));

        lightingShader.setMat4("model", &model[0][0]);

        // render the cube
        glBindVertexArray(cubeVAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        // also draw the lamp object
        lightCubeShader.use();
        lightCubeShader.setMat4("projection", &projection[0][0]);
        lightCubeShader.setMat4("view", &view[0][0]);
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
        lightCubeShader.setMat4("model", &model[0][0]);

        glBindVertexArray(lightCubeVAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();

    }
    glfwDestroyWindow(window);
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    //glDeleteProgram(shaderProgram);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}
// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
        
    const float cameraSpeed = 0.05f; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        cameraPos += cameraUp*cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        cameraPos -= cameraUp*cameraSpeed;

}