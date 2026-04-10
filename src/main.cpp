#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "init.h"
#include "Shader/shader.hpp"
#include "System/system.hpp"
#include "VertexBuffer/vertex_array.hpp"

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

#include "VertexBuffer/vertex.hpp"
int main(){
    Window abwindow({100,1000 , "Dragon"});
    GLFWwindow* window = abwindow.GetNativeWindow();
    Shader lightCubeShader(DEFAULT_VERTEX_SHADER,LIGHT_FRAGMENT_SHADER);
    Shader lightingShader(DEFAULT_VERTEX_SHADER,DEFAULT_FRAGMENT_SHADER);
    
    VertexArray cube("Dragon 2.5_stl.stl");
    VertexArray lightcube("cube.stl");




    // glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);  
    //glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    // glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
    // glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f); 
    // glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
    // glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);
    //Matrix mul for view 

    // glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);

    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
glfwMakeContextCurrent(window);
// ...
//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    while(!glfwWindowShouldClose(window)){
        // input
        // -----
        processInput(window);
int mode = glfwGetInputMode(window, GLFW_CURSOR);
if (mode == GLFW_CURSOR_DISABLED) {
    printf("Cursor successfully disabled in code.\n");
} else {
    printf("Cursor is NOT disabled. Current mode: %d\n", mode);
}
double x, y;
glfwGetCursorPos(window, &x, &y);
printf("Pos: %.2f, %.2f\n", x, y);
        // render
        // ------
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // be sure to activate shader when setting uniforms/drawing objects

        lightingShader.use();
        lightingShader.setUniform("lightPos", Vec3f(lightPos.x,lightPos.y,lightPos.z));  
        lightingShader.setUniform("viewPos", Vec3f(cameraPos.x,cameraPos.y,cameraPos.z)); 
        float clr = (((int)glfwGetTime()*100) % 1000)/1000.0f;

        lightingShader.setUniforms(
            "material.ambient",Vec3f(1.0f, clr, 1-clr),
            "material.diffuse", Vec3f(1.0f, clr, 1-clr),
            "material.specular", Vec3f(0.5f, 0.5f, 0.5f),
            "material.shininess", 32.0f
        );
        
        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(45.0f),(float) abwindow.getProperties().width / abwindow.getProperties().height, 0.1f, 100.0f);
        glm::mat4 view;                                      //CameraUp
        view = glm::lookAt(cameraPos, cameraFront+cameraPos, glm::vec3(0.0, 1.0, 0.0));
        lightingShader.setUniform("projection", projection);
        lightingShader.setUniform("view", view);

        // world transformation
        glm::mat4 model = glm::mat4(1.0f);
        float angle = (float)glfwGetTime() * glm::radians(50.0f);
        auto axis =  glm::vec3(0.0f, 1.0f,0.0f);
        model = glm::rotate(model, angle, glm::normalize(axis));
        model = glm::rotate(model, glm::radians(-90.0f),glm::vec3(1.0f, 0.0f,0.0f));

        lightingShader.setUniform("model", model);

        // render the cube
        cube.draw();

        // also draw the lamp object
        lightCubeShader.use();
        lightCubeShader.setUniform("projection", projection);
        lightCubeShader.setUniform("view", view);
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
        lightCubeShader.setUniform("model", model);

        lightcube.draw();

        glfwSwapBuffers(window);
        glfwPollEvents();

    }


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