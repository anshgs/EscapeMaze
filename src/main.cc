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
#include <chrono>
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

float playerCoords[] = {
        -0.675f, 0.65f, 0.0f, // left  
        -0.65f, 0.65f, 0.0f, // right 
        -0.65f, 0.675f, 0.0f, // right  
        -0.675f,  0.675f, 0.0f, // top  
};

float* vertices;
// = {
//         0.1f, 0.1f, 0.0f,
//         0.3f, 0.1f, 0.0f,
//         0.3f, 0.3f, 0.0f,
//         0.1f, 0.3f, 0.0f,
//         0.4f, -0.2f, 0.0f,
//         0.5f, -0.2f, 0.0f,
//         0.5f, 0.0f, 0.0f,
//         0.4f, 0.0f, 0.0f,
//     };

unsigned int *indices;

//  = {  // note that we start from 0!
//     0, 1, 3,   // first triangle
//     1, 2, 3,    // second triangle
//     4, 5, 7,
//     5, 6, 7,
// };

float winV[] = {
    0.65f, -0.65f, 0.0f, // left  
    0.675f, -0.65f, 0.0f, // right 
    0.675f, -0.675f, 0.0f, // right  
    0.65f,  -0.675f, 0.0f, // top  
};

unsigned int playerInd[] = {
    0, 1, 3,
    1, 2, 3,
};

unsigned int winIn[] = {
    0, 1, 3,
    1, 2, 3,
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

       Maze maze(20, 20);

int main()
{
    srand((unsigned int)time(NULL));
    auto start = std::chrono::system_clock::now();
    maze.GenerateMaze(maze.GetWidth(), maze.GetHeight());
    //maze.MazeOut();
    vertices = maze.WallCoorArray(maze.GetWallCoor());
    indices = maze.WallCoorIndex(maze.GetWallCoor().size());
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
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "EscapeMaze", NULL, NULL);
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
        
    unsigned int EBO[3];
    glGenBuffers(3, EBO);
    unsigned int VBO[3], VAO[3];


    glGenVertexArrays(3, VAO);
    glGenBuffers(3, VBO);

    //maze walls
    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, maze.GetWallCoor().size()*48, vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, maze.GetWallCoor().size()*24, indices, GL_STATIC_DRAW); 

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    //winning tile
    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(winV), winV, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(winIn), winIn, GL_STATIC_DRAW); 

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    int counter = 0;
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
        
        //Redo map
        auto curTime = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed = curTime - start;
        if(elapsed.count() > counter*10){
            maze.GenerateMaze(maze.GetWidth(), maze.GetHeight());
            //maze.MazeOut();
            vertices = maze.WallCoorArray(maze.GetWallCoor());
            indices = maze.WallCoorIndex(maze.GetWallCoor().size());
            counter++;
            glBindVertexArray(VAO[0]);
            glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
            glBufferData(GL_ARRAY_BUFFER, maze.GetWallCoor().size()*48, vertices, GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, maze.GetWallCoor().size()*24, indices, GL_STATIC_DRAW); 

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
        }

    //player 
    glBindVertexArray(VAO[2]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(playerCoords), playerCoords, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[2]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(playerInd), playerInd, GL_STATIC_DRAW); 

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); 


        glUseProgram(shaderProgram2);
        glBindVertexArray(VAO[0]); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawElements(GL_TRIANGLES, maze.GetWallCoor().size()*6, GL_UNSIGNED_INT, 0);
        
        glUseProgram(shaderProgram2);
        glBindVertexArray(VAO[1]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO[2]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // glBindVertexArray(0); // no need to unbind it every time 
 
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(3, VAO);
    glDeleteBuffers(3, VBO);
    glDeleteProgram(shaderProgram);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}


bool collide(std::vector<float> obj1, std::set<std::vector<float>> walls, float dx, float dy){ //x1 x2 y1 y2
    obj1[0]+=dx;
    obj1[1]+=dx;
    obj1[2]+=dy;
    obj1[3]+=dy;
    bool xl = false;
    bool yl = false;
    bool overlap = false;
    for(const auto& obj2 : walls){
        xl = ((obj1[0] < obj2[0] && obj1[1] > obj2[0]) || (obj1[0] < obj2[1] && obj1[1] > obj2[1]) || (obj1[0] < obj2[0] && obj1[1] > obj2[1]) || (obj1[0] > obj2[0] && obj1[1] < obj2[1]));
        yl = ((obj1[2] < obj2[2] && obj1[3] > obj2[2]) || (obj1[2] < obj2[3] && obj1[3] > obj2[3]) || (obj1[2] < obj2[2] && obj1[3] > obj2[3]) || (obj1[2] > obj2[2] && obj1[3] < obj2[3]));
        overlap = overlap || (xl && yl);
    }
    obj1[0]-=dx;
    obj1[1]-=dx;
    obj1[2]-=dy;
    obj1[3]-=dy;
    return overlap;
}
// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    float inc = 0.01f;
    std::vector<float> curCord;
    curCord.push_back(playerCoords[0]);
    curCord.push_back(playerCoords[3]);
    curCord.push_back(playerCoords[1]);
    curCord.push_back(playerCoords[10]);
    std::set<std::vector<float>> walls;
    // std::vector<float> mazeCord;
    // mazeCord.push_back(vertices[0]);
    // mazeCord.push_back(vertices[3]);
    // mazeCord.push_back(vertices[1]);
    // mazeCord.push_back(vertices[10]);
    // std::vector<float> mazeCord2;
    // mazeCord2.push_back(vertices[12]);
    // mazeCord2.push_back(vertices[15]);
    // mazeCord2.push_back(vertices[13]);
    // mazeCord2.push_back(vertices[22]);
    // walls.insert(mazeCord);
    // walls.insert(mazeCord2);
    walls = maze.GetWallCoor();
    std::vector<float> winCoord;
    winCoord.push_back(winV[0]);
    winCoord.push_back(winV[3]);
    winCoord.push_back(winV[1]);
    winCoord.push_back(winV[10]);
    std::set<std::vector<float>> wins;
    wins.insert(winCoord);
    if(collide(curCord, wins, 0, 0)){
        float c1 = (rand()%10)/10.0f;
        float c2 = (rand()%10)/10.0f;
        float c3 = (rand()%10)/10.0f;
        glClearColor(c1, c2, c3, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
        if(playerCoords[3]+inc <= 1 && !collide(curCord, walls, inc, 0)){
            playerCoords[0]+=inc;
            playerCoords[3]+=inc;
            playerCoords[6]+=inc;
            playerCoords[9]+=inc;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
        if(playerCoords[0]-inc>=-1 && !collide(curCord, walls, -inc, 0)){
            playerCoords[0]-=inc;
            playerCoords[3]-=inc;
            playerCoords[6]-=inc;
            playerCoords[9]-=inc;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
        if(playerCoords[1]-inc >= -1 && !collide(curCord, walls, 0, -inc)){
            playerCoords[1]-=inc;
            playerCoords[4]-=inc;
            playerCoords[7]-=inc;
            playerCoords[10]-=inc;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
        if(playerCoords[7]+inc <= 1 && !collide(curCord, walls, 0, inc)){
            playerCoords[1]+=inc;
            playerCoords[4]+=inc;
            playerCoords[7]+=inc;
            playerCoords[10]+=inc;
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