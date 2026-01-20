#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "init.h"
#include "shader.h"
#include "image.h"
#include "texture.h"
#include "tilemap.h"

#include <iostream>
#include <math.h>
#include <random>


// settings
unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;


void processInput(GLFWwindow *window);

// camera
glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
// glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);  
//glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
// glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
// glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f); 
// glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
// glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);
//Matrix mul for view 

// glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);

std::vector<glm::mat4> make_radom_cubes(){
    std::vector<glm::mat4> disp;
    disp.reserve(10);


    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<float> posDist(-5.0f, 5.0f);
    std::uniform_real_distribution<float> angleDist(0.0f, glm::two_pi<float>());
    std::uniform_real_distribution<float> axisDist(-1.0f, 1.0f);

    for (int i = 0; i < 10; i++)
    {
        glm::vec3 position(
            posDist(gen),
            posDist(gen),
            posDist(gen)
        );

        glm::vec3 axis(
            axisDist(gen),
            axisDist(gen),
            axisDist(gen)
        );
        axis = glm::normalize(axis);

        float angle = angleDist(gen);

        glm::mat4 model(1.0f);
        model = glm::translate(model, position);
        model = glm::rotate(model, angle, axis);

        disp.push_back(model);
    }
    return disp;
}


int main(){
    GLFWwindow* window = make_window();
    Shader shader(TILEMAP_VERTEX_SHADER,DEFAULT_FRAGMENT_SHADER);

    TileMap map;

    shader.use();
    shader.setInt("ourTexture", 0);


    std::vector<glm::mat4> disp = make_radom_cubes();
    while(!glfwWindowShouldClose(window)){
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // texture.use();
        shader.use();

        glm::mat4 view;                                      //CameraUp
        view = glm::lookAt(cameraPos, cameraFront+cameraPos, glm::vec3(0.0, 1.0, 0.0));
        shader.setMat4("view",&view[0][0]);

        int width,height;
        glfwGetFramebufferSize(window,&width,&height);
        glm::mat4 projection    = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
        shader.setMat4("projection", glm::value_ptr(projection));
        
        std::vector<glm::mat4> aft;aft.reserve(disp.size());
        for(int i=0;i<disp.size();i++){ aft.push_back(glm::rotate(disp[i],(float)glfwGetTime(),glm::vec3(1.0f,0.0f,0.0f)));}
        map.sendInstanceData(aft.size()*sizeof(glm::mat4),&aft[0][0]);
        map.draw();

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();

    }
    glfwDestroyWindow(window);
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