#define GLEW_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include "public.h"
#include "simpleGeometry.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>

using namespace std;

#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 1200
#define NEAR 0.1f
#define FAR 100.0f

void framebuffer_size_callback(GLFWwindow*, int, int);
void processInput(GLFWwindow*);
void mouse_callback(GLFWwindow*, double, double);
void scroll_callback(GLFWwindow*, double, double);

// presettings
float ratio = (float)WINDOW_WIDTH / WINDOW_HEIGHT;
// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;
// Camera system
Camera myCamera;

int main(void)
{
    /* Initialize GLFW */
    if (!glfwInit())
        return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello World", NULL, NULL);
    if (!window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -2;
    }

    glfwMakeContextCurrent(window);
    
    /* Initialize glew */
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        std::cout << glewGetErrorString(err) << std::endl;
        return -3;
    }

    /* Operations on the window */
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    /* configure opengl */
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    /*glEnable(GL_STENCIL_TEST);  
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);*/
    
    /* other configurations  */
    //Mycamera.setNoFlyMode();
    //stbi_set_flip_vertically_on_load(true);

    /* vertex attributes and meterials */
    //Model myModel("E:\\Resource\\backpack\\backpack.obj");
    vector<float> cubeVertices = {
        // back face
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // bottom-left
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f, // top-right
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, // bottom-right
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f, // top-right
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // bottom-left
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, // top-left
        // front face
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, // bottom-left
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, // bottom-right
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f, // top-right
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f, // top-right
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, // top-left
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, // bottom-left
        // left face
        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f, // top-right
        -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, // top-left
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // bottom-left
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // bottom-left
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, // bottom-right
        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f, // top-right
        // right face
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, // top-left
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // bottom-right
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f, // top-right
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // bottom-right
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, // top-left
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f, // bottom-left
        // bottom face
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // top-right
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f, // top-left
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, // bottom-left
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, // bottom-left
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, // bottom-right
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // top-right
        // top face
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, // top-left
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, // bottom-right
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f, // top-right
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, // bottom-right
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, // top-left
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f // bottom-left
    };

    vector<float> planeVertices = {
        // positions          // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
         5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
        -5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
        -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

         5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
        -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
         5.0f, -0.5f, -5.0f,  2.0f, 2.0f
    };

    simpleGeometry geo1(cubeVertices, "E:\\Resource\\textures_opengl\\container.png", HAVE_TEXCOORD);
    simpleGeometry geo2(planeVertices, "E:\\Resource\\textures_opengl\\DeepOceanWater.png", HAVE_TEXCOORD);
    
    // shader
    Shader objectShader("../GLSL_01/src/vertexShader.txt", "../GLSL_01/src/fragShader.txt");
    Shader singleColor("../GLSL_01/src/vertexShader_light.txt", "../GLSL_01/src/fragShader_light.txt");
    //Shader lightShader("../GLSL_01/src/vertexShader_light.txt", "../GLSL_01/src/fragShader_light.txt"); 
       
    //light source
    //glm::mat4 lightPos = glm::mat4(1.0f);
    //lightPos = glm::translate(lightPos, glm::vec3(7.0f, 2.0f, 10.0f));

    // set uniform variables 
    objectShader.setVec3("ambient", 0.1f, 0.1f, 0.1f);
    objectShader.setFloat("material.shininess", 12);
    objectShader.setFloat("near", NEAR);
    objectShader.setFloat("far", FAR);
    /*objectShader.setVec3("dirLight.direction", 6.1f, 1.1f, 7.9f);
    objectShader.setVec3("dirLight.color", 0.8f, 0.8f, 0.8f);*/

    objectShader.setVec3("spotLight.color", 0.9f, 0.9f, 0.9f);
    objectShader.setFloat("spotLight.cutoff", glm::cos(glm::radians(12.5f)));
    objectShader.setFloat("spotLight.outCutoff", glm::cos(glm::radians(15.0f)));
    objectShader.setFloat("spotLight.constant", 1.0f);
    objectShader.setFloat("spotLight.linear", 0.09f);
    objectShader.setFloat("spotLight.quadratic", 0.032f);


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* per-frame time logic */
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        /* Input */
        processInput(window);

        /* Render here */
        glClearColor(0.1f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT/* | GL_STENCIL_BUFFER_BIT*/);
                
        // view,projection transformations matrix
        glm::mat4 projectionMatrix = glm::perspective(glm::radians(myCamera.fov), ratio, NEAR, FAR);
        glm::mat4 viewMatrix = myCamera.getViewMatrix();
         
        // set uniform vatiable
        objectShader.use();
        objectShader.setMat4("projection", projectionMatrix);
        objectShader.setMat4("view", viewMatrix);  
        objectShader.setVec3("viewPos", myCamera.cameraPos);

        objectShader.setVec3("spotLight.position", myCamera.cameraPos);
        objectShader.setVec3("spotLight.direction", myCamera.cameraFront);

        singleColor.use();
        singleColor.setMat4("projection", projectionMatrix);
        singleColor.setMat4("view", viewMatrix);
        //render geo2         
        glDisable(GL_CULL_FACE);
        
        objectShader.use();
        glm::mat4 modelMatrix = glm::mat4(1.0f);
        objectShader.setMat4("model", modelMatrix);
        geo2.Draw(objectShader);
        
        //render geo1
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        
        modelMatrix = glm::mat4(1.0f);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-1.0f, 0.0f, -1.0f));
        objectShader.setMat4("model", modelMatrix);
        geo1.Draw(objectShader);
        
        modelMatrix = glm::mat4(1.0f);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(2.0f, 0.0f, 0.0f));
        objectShader.setMat4("model", modelMatrix);
        geo1.Draw(objectShader);
        
        // render edges
        //glStencilFunc(GL_NOTEQUAL, 1, 0xff);
        /*singleColor.use();
        modelMatrix = glm::mat4(1.0f);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-1.0f, 0.0f, -1.0f));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(1.1f, 1.1f, 1.1f));
        singleColor.setMat4("model", modelMatrix);
        geo1.Draw(singleColor);

        modelMatrix = glm::mat4(1.0f);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(2.0f, 0.0f, 0.0f));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(1.1f, 1.1f, 1.1f));
        singleColor.setMat4("model", modelMatrix);
        geo1.Draw(singleColor);*/
 
        //glStencilFunc(GL_ALWAYS, 1, 0xff);
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
        
    }

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    //Camera
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        myCamera.Move(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        myCamera.Move(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        myCamera.Move(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        myCamera.Move(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        myCamera.Move(DOWN, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        myCamera.Move(UP, deltaTime);
}

void mouse_callback(GLFWwindow* window, double xPos, double yPos)
{
    myCamera.Towards((float)xPos, (float)yPos);
}

void scroll_callback(GLFWwindow* window, double offsetX, double offsetY)
{
    myCamera.Zoom((float)offsetY);
}


