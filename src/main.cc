#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include "ai.hpp"
#include "item.hpp"
#include "functions.hpp"
#include "game.hpp"
#include "maze.hpp"
#include "user.hpp"
#include "locinfo.hpp"
#include "time.h"
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
float vertices[] = {
        0.5f, 0.5f, 0.0f, // left  
         0.6f, 0.5f, 0.0f, // right 
        0.6f, 0.6f, 0.0f, // right  
         0.5f,  0.6f, 0.0f, // top  
         0.1f, 0.1f, 0.0f,
        0.3f, 0.1f, 0.0f,
        0.3f, 0.3f, 0.0f,
        0.1f, 0.3f, 0.0f,
    }; 

float winV[] = {
    -0.1f, -0.1f, 0.0f,
    0.0f, -0.1f, 0.0f,
    0.0f, 0.0f, 0.0f, 
    -0.1f, 0.0f, 0.0f,
};

unsigned int winIn[] = {
    0, 1, 3,
    1, 2, 3,
};

unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3,    // second triangle
    4, 5, 7,
    5, 6, 7,
};

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

    const char *fragmentShaderSource2 = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(0.2f, 0.6f, 0.6f, 1.0f);\n"
    "}\n\0";

int main()
{
    srand((unsigned int)time(NULL));
    Maze maze(10, 10);
    maze.GenerateMaze(10, 10);
    maze.MazeOut();
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);


    unsigned int fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);
    glCompileShader(fragmentShader2);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    unsigned int shaderProgram2 = glCreateProgram();
    glAttachShader(shaderProgram2, vertexShader);
    glAttachShader(shaderProgram2, fragmentShader2);
    glLinkProgram(shaderProgram2);
    
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------

    // uncomment this call to draw in wireframe polygons.
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        
    unsigned int EBO[2];
    glGenBuffers(2, EBO);
    unsigned int VBO[2], VAO[2];


    glGenVertexArrays(2, VAO);
    glGenBuffers(2, VBO);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
    glClear(GL_COLOR_BUFFER_BIT);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); 

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);



    glBindVertexArray(VAO[1]);




    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(winV), winV, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(winIn), winIn, GL_STATIC_DRAW); 

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); 


        // draw our first triangle
        glUseProgram(shaderProgram2);
        glBindVertexArray(VAO[0]); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
        glUseProgram(shaderProgram);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glUseProgram(shaderProgram2);
        glBindVertexArray(VAO[1]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // glBindVertexArray(0); // no need to unbind it every time 
 
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(2, VAO);
    glDeleteBuffers(2, VBO);
    glDeleteProgram(shaderProgram);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}


bool collide(float obj1[], float obj2[], float dx, float dy){ //x1 x2 y1 y2
    obj1[0]+=dx;
    obj1[1]+=dx;
    obj1[2]+=dy;
    obj1[3]+=dy;
    bool xl = (obj1[0] < obj2[0] && obj1[1] > obj2[0]) || (obj1[0] < obj2[1] && obj1[1] > obj2[1]) || (obj1[0] < obj2[0] && obj1[1] > obj2[1]) || (obj1[0] > obj2[0] && obj1[1] < obj2[1]);
    bool yl = (obj1[2] < obj2[2] && obj1[3] > obj2[2]) || (obj1[2] < obj2[3] && obj1[3] > obj2[3]) || (obj1[2] < obj2[2] && obj1[3] > obj2[3]) || (obj1[2] > obj2[2] && obj1[3] < obj2[3]);
    obj1[0]-=dx;
    obj1[1]-=dx;
    obj1[2]-=dy;
    obj1[3]-=dy;
    return xl&&yl;
}
// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    float inc = 0.001f;
    float curCord[] = {vertices[0], vertices[3], vertices[1], vertices[10]};
    float mazeCord[] = {vertices[12], vertices[15], vertices[13], vertices[22]};
    float winCoord[] = {-0.1f, 0.0f, -0.1f, 0.0f};

    if(collide(curCord, winCoord, 0, 0)){
        float c1 = (rand()%10)/10.0f;
        float c2 = (rand()%10)/10.0f;
        float c3 = (rand()%10)/10.0f;
        glClearColor(c1, c2, c3, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
        if(vertices[3]+inc <= 1 && !collide(curCord, mazeCord, inc, 0)){
            vertices[0]+=inc;
            vertices[3]+=inc;
            vertices[6]+=inc;
            vertices[9]+=inc;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
        if(vertices[0]-inc>=-1 && !collide(curCord, mazeCord, -inc, 0)){
            vertices[0]-=inc;
            vertices[3]-=inc;
            vertices[6]-=inc;
            vertices[9]-=inc;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
        if(vertices[1]-inc >= -1 && !collide(curCord, mazeCord, 0, -inc)){
            vertices[1]-=inc;
            vertices[4]-=inc;
            vertices[7]-=inc;
            vertices[10]-=inc;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
        if(vertices[7]+inc <= 1 && !collide(curCord, mazeCord, 0, inc)){
            vertices[1]+=inc;
            vertices[4]+=inc;
            vertices[7]+=inc;
            vertices[10]+=inc;
        }
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}