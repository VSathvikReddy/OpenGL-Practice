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
std::vector<float> vertices = {
// Front (+Z)
-0.5f, -0.5f,  0.5f,   0.0f,   0.0f,
0.5f, -0.5f,  0.5f, 1.0f,   0.0f,
0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
-0.5f,  0.5f,  0.5f,   0.0f, 1.0f,

// Back (-Z)
 0.5f, -0.5f, -0.5f,   0.0f,   0.0f,
-0.5f, -0.5f, -0.5f, 1.0f,   0.0f,
-0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
 0.5f,  0.5f, -0.5f,   0.0f, 1.0f,

// Left (-X)
-0.5f, -0.5f, -0.5f,   0.0f,   0.0f,
-0.5f, -0.5f,  0.5f, 1.0f,   0.0f,
-0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
-0.5f,  0.5f, -0.5f,   0.0f, 1.0f,

// Right (+X)
 0.5f, -0.5f,  0.5f,   0.0f,   0.0f,
 0.5f, -0.5f, -0.5f, 1.0f,   0.0f,
 0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
 0.5f,  0.5f,  0.5f,   0.0f, 1.0f,

// Bottom (-Y)
-0.5f, -0.5f, -0.5f,   0.0f,   0.0f,
 0.5f, -0.5f, -0.5f, 1.0f,   0.0f,
 0.5f, -0.5f,  0.5f, 1.0f, 1.0f,
-0.5f, -0.5f,  0.5f,   0.0f, 1.0f,


// Top (+Y)
-0.5f,  0.5f,  0.5f,   0.0f,   0.0f,
 0.5f,  0.5f,  0.5f, 1.0f,   0.0f,
 0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
-0.5f,  0.5f, -0.5f,   0.0f, 1.0f,

};
std::vector<unsigned int> indices = {
    0, 1, 2,  0, 2, 3,
    4, 5, 6,  4, 6, 7,
    8, 9,10,  8,10,11,
   12,13,14, 12,14,15,
   16,17,18, 16,18,19,
   20,21,22, 20,22,23
};

std::vector<float> textoff;
std::vector<glm::mat4> make_radom_cubes(std::vector<glm::mat4>& disp, std::vector<float>& textoff){
    disp.reserve(10);
    textoff.reserve(10*2);


    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<float> posDist(-5.0f, 5.0f);
    std::uniform_real_distribution<float> angleDist(0.0f, glm::two_pi<float>());
    std::uniform_real_distribution<float> axisDist(-1.0f, 1.0f);
    std::uniform_int_distribution<int> texDist(0, 3);

    for (int i = 0; i < 10; i++){
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


        textoff.push_back(0.0f);
        textoff.push_back(texDist(gen)*0.25f);
    }
    return disp;
}

void adjust_vertices(float width, float height){
    for(int i=0;i<24;i++){
        if(vertices[5*i + 3]==1.0f){
            vertices[5*i + 3]==width;
        }if(vertices[5*i + 4]==1.0f){
            vertices[5*i + 4]==height;
        }

    }
}



int main(){
    GLFWwindow* window = make_window();
    Shader shader(TILEMAP_VERTEX_SHADER,DEFAULT_FRAGMENT_SHADER);

    std::vector<glm::mat4> disp; std::vector<float> texoff;
    make_radom_cubes(disp,texoff);
    adjust_vertices(8.0f,8.0f);

    TileMap map(vertices,indices,texoff,"test_text.ppm");
    // map.sendStaticData(vertices,indices,texoff,"test_text.ppm");


    shader.use();
    shader.setInt("ourTexture", 0);
    shader.setVec2("textureDimensions",(float)map.texture.getWidth(),(float)map.texture.getHeight());
    //shader.setVec2("tempMove",0.0f,0.5f);


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