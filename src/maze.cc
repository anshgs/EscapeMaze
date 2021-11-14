#include "maze.hpp"
#include <utility>
#include <stack>
#include <iostream>
Maze::Maze(int width, int height) {
    width_ = width;
    height_ = height;
}

int Maze::GetWidth() {
    return width_;
}

int Maze::GetHeight() {
    return height_;
}

Locinfo Maze::GetLocinfo(int y, int x){
    return mazedata_[y][x];
}

std::string Maze::RandomNeighbor(int y, int x) {
    // check bound 
    bool up = false;
    bool down = false;
    bool right = false;
    bool left = false;
    if(y == 0) {
        up = true;
    } else {
        up = mazedata_[y-1][x].visited;
    }
    if(y == height_-1) {
        down = true;
    } else {
        down = mazedata_[y+1][x].visited;
    }
    if(x == 0) {
        left = true;
    } else {
        left = mazedata_[y][x-1].visited;
    }
    if(x == width_-1) {
        right = true;
    } else {
        right = mazedata_[y][x+1].visited;
    }
    int num = 0;
    std::vector<std::string> choices;
    if (left == false)  {
        num = num + 1;
        choices.push_back("left");
    }
    if (right == false)  {
        num = num + 1;
        choices.push_back("right");
    }
    if (up == false)  {
        num = num + 1;
        choices.push_back("up");
    }
    if (down == false)  {
        num = num + 1;
        choices.push_back("down");
    }
    if(num == 0) {
        return "no";
    } else {
        int c = rand()%num;
        return choices[c];
    }
}

void Maze::GenerateMaze(int width, int height){
    Locinfo l = {false,false,false,false, false};
    std::vector<Locinfo> currow(width,l);
    mazedata_.assign(height_, currow);
    // TODO: now the start point is set at the top left corner. May modify later
    std::stack<std::pair<int,int>> trace;
    // Choose the initial cell, mark it as visited and push it to the stack
    std::pair <int,int> startpoint (0,0);  
    mazedata_[0][0].visited = true;
    trace.push(startpoint);
    std::pair<int,int> cur;
    // While the stack is not empty
    while(!trace.empty()) {
        // Pop a cell from the stack and make it a current cell
        cur = trace.top();
        trace.pop();
        // mark the current cell as visited
        mazedata_[cur.first][cur.second].visited = true;
        // If the current cell has any neighbours which have not been visited
        Locinfo* curinfo = &mazedata_[cur.first][cur.second];
        std::string nei = RandomNeighbor(cur.first, cur.second);
        if(nei == "no") {
            continue;
        }
        // Push the current cell to the stack
        trace.push(cur);
        std::pair<int,int> chosen_loc;
        Locinfo* chosen_n;
        // Choose one of the unvisited neighbours  Remove the wall between the current cell and the chosen cell
        if(nei == "left") {
            curinfo->left = true;
            chosen_n = &mazedata_[cur.first][cur.second-1];
            chosen_n->right = true;
            chosen_loc = std::make_pair(cur.first,cur.second-1);
        }
        if(nei == "right") {
            curinfo->right = true;
            chosen_n = &mazedata_[cur.first][cur.second+1];
            chosen_n->left = true;
            chosen_loc = std::make_pair(cur.first,cur.second+1);
        }
        if(nei == "up") {
            curinfo->up = true;
            chosen_n = &mazedata_[cur.first-1][cur.second];
            chosen_n->down = true;
            chosen_loc = std::make_pair(cur.first-1,cur.second);
        }
        if(nei == "down") {
            curinfo->down = true;
            chosen_n = &mazedata_[cur.first+1][cur.second];
            chosen_n->up = true;
            chosen_loc = std::make_pair(cur.first+1,cur.second);
        }
         // Mark the chosen cell as visited and push it to the stack
        //chosen_n.visited = true;
        trace.push(chosen_loc);
    }
}

