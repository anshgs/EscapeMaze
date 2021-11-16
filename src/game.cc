#include "game.hpp"
#include "utils.hpp"


void Game::Init(){
    // initialize random seed and start time
    srand((unsigned int)time(NULL));

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "Failed to initialize GLAD" << endl;
        exit(EXIT_FAILURE);
    }

    InitializeWindow();
    programs_ = BuildShaders(kVertexShaderSource, kFragmentSources, kNames);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void Game::InitializeWindow(){
    // glfw: initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    // glfw window creation
    GLFWwindow* window = glfwCreateWindow(kScreenWidth, kScreenHeight, "EscapeMaze", NULL, NULL);
    if (window == NULL)
    {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback);
    game_window_ = window;
}

void Game::GenerateNextLevel(){
    if(cur_level_ >= levels_.size()){
        //TODO: Endgame handling
        cout << "End of Game" << endl;
        exit(EXIT_SUCCESS);
    }   
    Level next_level = levels_.at(cur_level_++);
    Maze maze(next_level.maze_width_, next_level.maze_height_);
    start_time_ = chrono::system_clock::now();
    Play(next_level, maze);
}

void Game::Play(Level level, Maze maze){
    maze.GenerateMaze(maze.GetWidth(), maze.GetHeight());


    glGenBuffers(kNumObjects, element_buffer_objects_);
    glGenVertexArrays(kNumObjects, vertex_array_objects_);
    glGenBuffers(kNumObjects, vertex_buffer_objects_);
    
    map<string, vector<pair<int, const void*>>> name_to_size_data;
    for (string name : kNames) {
        name_to_size_data_[name] = vector<pair<int, const void*>>();
    }
    name_to_size_data_["player"] = {{sizeof(player_.GetHitbox()), player_.GetHitbox()}, {sizeof(player_ind), player_ind}, {6, (void*) 0}};
    name_to_size_data_["win_tile"] = {{sizeof(GetHitbox(level.win_coord_)), GetHitbox(level.win_coord_)}, {sizeof(win_ind), win_ind}, {6, (void*) 0}};
    name_to_size_data_["walls"] = maze.GetSizeData();
    for (string name : kNames) {
        BindElement(name);
    }
    
    while(!glfwWindowShouldClose(game_window_)){
        ProcessInputAndRegenerate(level, maze);
    }
    glDeleteVertexArrays(kNumObjects, vertex_array_objects_);
    glDeleteBuffers(kNumObjects, vertex_buffer_objects_);
    glDeleteBuffers(kNumObjects, element_buffer_objects_);
    for(const auto& name_program_pair : programs_){    
        glDeleteProgram(name_program_pair.second);
    }

    glfwTerminate();
}

void Game::Draw(string object_name){
    glUseProgram(programs_.at(object_name));
    glBindVertexArray(vertex_array_objects_[kIndexMap.at(object_name)]); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glDrawElements(GL_TRIANGLES, name_to_size_data_[object_name][2].first, GL_UNSIGNED_INT, 0);
}

void Game::ProcessInput(Level level, Maze maze){
    float inc = player_.GetSpeed();

    float* player_hitbox = player_.GetHitbox();
    std::vector<float> player_current_coords;
    player_current_coords.push_back(player_hitbox[0]);
    player_current_coords.push_back(player_hitbox[3]);
    player_current_coords.push_back(player_hitbox[1]);
    player_current_coords.push_back(player_hitbox[10]);

    std::set<std::vector<float>> walls;
    walls = maze.GetWallCoor();
    float* win_tile_hitbox = GetHitbox(level.win_coord_);
    std::vector<float> win_tile_coords;
    win_tile_coords.push_back(win_tile_hitbox[0]);
    win_tile_coords.push_back(win_tile_hitbox[3]);
    win_tile_coords.push_back(win_tile_hitbox[1]);
    win_tile_coords.push_back(win_tile_hitbox[10]);

    if(CollideOnMove(player_current_coords, win_tile_coords, 0, 0)){
        float c1 = (rand()%10)/10.0f;
        float c2 = (rand()%10)/10.0f;
        float c3 = (rand()%10)/10.0f;
        glClearColor(c1, c2, c3, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        level_over = true;
    }

    if (glfwGetKey(game_window_, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(game_window_, true);
    }

    if(!level_over){
        if (glfwGetKey(game_window_, GLFW_KEY_RIGHT) == GLFW_PRESS){
            if(player_current_coords[3]+inc <= 1 && !CollideWalls(player_current_coords, walls, inc, 0)){
                player_.MoveRight();
            }
        }
        if (glfwGetKey(game_window_, GLFW_KEY_LEFT) == GLFW_PRESS){
            if(player_current_coords[0]-inc>=-1 && !CollideWalls(player_current_coords, walls, -inc, 0)){
                player_.MoveLeft();
            }
        }
        if (glfwGetKey(game_window_, GLFW_KEY_DOWN) == GLFW_PRESS){
            if(player_current_coords[1]-inc >= -1 && !CollideWalls(player_current_coords, walls, 0, -inc)){
                player_.MoveDown();
            }
        }
        if (glfwGetKey(game_window_, GLFW_KEY_UP) == GLFW_PRESS){
            if(player_current_coords[7]+inc <= 1 && !CollideWalls(player_current_coords, walls, 0, inc)){
                player_.MoveUp();
            }
        }
    }
}

void Game::ProcessInputAndRegenerate(Level level, Maze maze){
    ProcessInput(level, maze);
    // render
    // ------
    glClear(GL_COLOR_BUFFER_BIT);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    int regen_counter = 0;
    //Redo map
    if(level_over){
        start_time_ = std::chrono::system_clock::now();
        regen_counter = 0;
    }
    else{
        auto curTime = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed = curTime - start_time_;
        if(elapsed.count() > regen_counter*10){
            maze.GenerateMaze(maze.GetWidth(), maze.GetHeight());
            regen_counter++;
            name_to_size_data_["walls"] = maze.GetSizeData();
            BindElement("walls");
        }
        BindElement("player");
        
        for(string name : kNames){
            Draw(name);
        }
    }
    glfwSwapBuffers(game_window_);
    glfwPollEvents();
}

map<string, unsigned int> Game::BuildShaders(const char* vertex_source, vector<const char*> fragment_sources, vector<string> fragment_names){
    // build and compile our shader program
    map<string, unsigned int> shader_programs;
    unsigned int vertex_shader = CreateVertexShader(vertex_source);
    for(unsigned int i = 0; i < fragment_sources.size(); i++){
        unsigned int fragment = CreateFragmentShader(fragment_sources[i]);
        unsigned int shader = LinkShader(vertex_shader, fragment);
        glDeleteShader(fragment);
        shader_programs[fragment_names[i]] = shader;
    }
    return shader_programs;
}

unsigned int Game::CreateVertexShader(const char* source){
    unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &source, NULL);
    glCompileShader(vertex_shader);

    CheckShaderCompile(vertex_shader);
    return vertex_shader;
}

unsigned int Game::CreateFragmentShader(const char* source){
    unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &source, NULL);
    glCompileShader(fragment_shader);

    CheckShaderCompile(fragment_shader);
    return fragment_shader;
}

unsigned int Game::LinkShader(unsigned int &vertex_shader, unsigned int& fragment_shader){
    unsigned int shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    CheckLinkStatus(shader_program);
    return shader_program;
}

// check for shader compile errors
void Game::CheckShaderCompile(unsigned int &shader){
    int success;
    char info_log[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, info_log);
        cout << "ERROR::SHADER::COMPILATION_FAILED\n" << info_log << endl;
        exit(EXIT_FAILURE);
    }
}

// check for linking errors
void Game::CheckLinkStatus(unsigned int &program){
    int success;
    char info_log[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, info_log);
        cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << info_log << endl;
    }
}

void Game::BindElement(string object_name){
    int index = kIndexMap.at(object_name);
    glBindVertexArray(vertex_array_objects_[index]);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_objects_[index]);
    glBufferData(GL_ARRAY_BUFFER, name_to_size_data_[object_name][0].first, name_to_size_data_[object_name][0].second, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_objects_[index]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, name_to_size_data_[object_name][1].first, name_to_size_data_[object_name][1].second, GL_STATIC_DRAW); 

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}