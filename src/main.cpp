#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "init.h"
#include "shader.h"
#include "image.h"
#include "texture.h"
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
    Shader shader(DEFAULT_VERTEX_SHADER,DEFAULT_FRAGMENT_SHADER);
    
    
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        // ===== Front face (+Z) =====
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // 0
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // 1
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // 2
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // 3

        // ===== Back face (-Z) =====
        0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // 4
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // 5
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // 6
        0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // 7

        // ===== Left face (-X) =====
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // 8
        -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // 9
        -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // 10
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // 11

        // ===== Right face (+X) =====
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // 12
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // 13
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // 14
        0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // 15

        // ===== Bottom face (-Y) =====
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // 16
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // 17
        0.5f, -0.5f,  0.5f,  1.0f, 1.0f, // 18
        -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, // 19

        // ===== Top face (+Y) =====
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, // 20
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // 21
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // 22
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f  // 23
    };
    unsigned int indices[] = {
        // Front
        0, 1, 2,
        0, 2, 3,

        // Back
        4, 5, 6,
        4, 6, 7,

        // Left
        8, 9, 10,
        8, 10, 11,

        // Right
        12, 13, 14,
        12, 14, 15,

        // Bottom
        16, 17, 18,
        16, 18, 19,

        // Top
        20, 21, 22,
        20, 22, 23
    };

float disp[] = {
    -2.0f, 0.0f, 0.0f,
     0.0f, 0.0f, 0.0f,
     2.0f, 0.0f, 0.0f
};


    unsigned int VBO, VAO, EBO,instacesVBO;
    make_buffer(&VBO, &VAO, &EBO,&instacesVBO, vertices, sizeof(vertices), indices, sizeof(indices), disp, sizeof(disp));


    //glGenBuffers(1, &instacesVBO);
    //glBindBuffer(GL_ARRAY_BUFFER, instacesVBO);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(disp), disp, GL_STATIC_DRAW);
    // glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));
    // glEnableVertexAttribArray(3);   
    // glVertexAttribDivisor(3,1);

    Image test;test.loadImageFromFile("test.ppm");
    Texture texture(test);

    shader.use();
    shader.setInt("ourTexture", 0);
    
    glm::mat4 projection    = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    shader.setMat4("projection", glm::value_ptr(projection));

    // glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);  
    //glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    // glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
    // glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f); 
    // glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
    // glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);
    //Matrix mul for view 

    // glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);

    while(!glfwWindowShouldClose(window)){
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        texture.use();
        shader.use();
        
        glm::mat4 model         = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f)); 

        glm::mat4 view;                                      //CameraUp
        view = glm::lookAt(cameraPos, cameraFront+cameraPos, glm::vec3(0.0, 1.0, 0.0));
        shader.setMat4("view",&view[0][0]);

        // render container
        glBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

        shader.setMat4("model", &model[0][0]);

        glDrawElementsInstanced(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0, 3);
        //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        //glDrawArrays(GL_TRIANGLES, 0, 36);

 
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();

    }
    glfwDestroyWindow(window);
    glDeleteVertexArrays(1, &VAO);
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
}