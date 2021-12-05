#ifndef GAME_HPP
#define GAME_HPP

#include "utils.hpp"
#include "maze.hpp"
#include "player.hpp"
#include "item.hpp"

#include <iostream>
#include <chrono>
#include <utility>
#include <map>
using namespace std;
struct Level{
    const float player_speed_; //speed of the player
    const float player_width_; //player's width
    const float player_height_; //player's height
    const int num_ai_; //number of AI
    const float ai_speed_; //speed of the AI
    const int maze_height_; //height of the maze
    const int maze_width_; //width of the maze
    const pair<float, float> start_coord_; //starting coordinate
    const pair<float, float> win_coord_; //winning coordinate
    const float regen_time_interval; //time interval of the game
    const int num_items_; //number of items in the game
};
class Game { //Game class
    private:
        size_t cur_level_ = 0; //sets the current level to 0 by default
        int num_items_ = 0; //sets number of items to 0 by default
        vector<Level> levels_; //vector of Level objects
        Player* player_; //pointer to player object
        GLFWwindow* game_window_; //game window
        bool invincible = false; //sets the invincible state to false by default
        bool spedUp = false; //sets the spedUp state to false by default
        bool jchanged; //declaration of the jchanged state
        unsigned int * element_buffer_objects_; //buffer objects of the elements in the game
        unsigned int * vertex_array_objects_; //vertex array of objects 
        unsigned int * vertex_buffer_objects_; //vertex of the buffer objects
        map<string, vector<pair<int, const void*>>> name_to_size_data_;
        chrono::system_clock::time_point start_time_; //starting time of the timer
        map<string, unsigned int> programs_; //map of the programs where the key is the string and the objects are unsinged int
        void Config(); //initialize the game
        void InitializeWindow(); //initialize the game window for the maze window
        void ProcessInput(Level &level, Maze &maze); //this is where the player is displayed in the game window. Levels will also change with respect to the player's movement i.e collition in walls
        //changing the position of the player is also implemented in this function.
        map<string, unsigned int> BuildShaders(const char* vertex_source, vector<const char*> fragment_sources, vector<string> fragment_names); //implements the shader program
        unsigned int CreateVertexShader(const char* source); //this is the function for shading the vertex in the game
        unsigned int CreateFragmentShader(const char* source); //shades in the fragment 
        void CheckShaderCompile(unsigned int &shader); //checks if the shader compiles correctly
        void CheckLinkStatus(unsigned int &shader); //checks if the linking function compiles correctly
        unsigned int LinkShader(unsigned int &vertex_shader, unsigned int& fragment_shader); //checks the link shading function compiles correctly and then shades the link
        void Draw(string object_name); //draw the elements 
        void BindElement(string object_name); //binds shaders and buffers to the elements 
        void Play(Level &level, Maze &maze); //play the game
        void ProcessInputAndRegenerate(Level &level, Maze &maze); //First bind the vertex array objects, and then bind and set vertex buffers, and then configure vertex attributes. This is sort of a regenerating the level and the maze
        void ProcessItems(Level &level, Maze &maze, chrono::system_clock::time_point &invincible_start_time_, chrono::system_clock::time_point &speed_start_time_); //process the items 

    public:
        void Init(); //initialize random seed and the start time is also randomized
        void GenerateNextLevel(); //function to generate the next level
        void AddLevel(Level level); //add the level onto each other
        float refresh_rate_; //the rate of the refreshing the game
        std::vector<Item> items_; //vector of Item objects

};

#endif