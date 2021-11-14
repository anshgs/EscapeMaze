#include maze.hpp
#include utility
#include stack
#include iostream
MazeMaze(int width, int height) {
    width_ = width;
    height_ = height;
}

int MazeGetWidth() {
    return width_;
}

int MazeGetHeight() {
    return height_;
}

Locinfo MazeGetLocinfo(int y, int x){
    return mazedata_[y][x];
}

stdstring MazeRandomNeighbor(int y, int x) {
     check bound 
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
    stdvectorstdstring choices;
    if (left == false)  {
        num = num + 1;
        choices.push_back(left);
    }
    if (right == false)  {
        num = num + 1;
        choices.push_back(right);
    }
    if (up == false)  {
        num = num + 1;
        choices.push_back(up);
    }
    if (down == false)  {
        num = num + 1;
        choices.push_back(down);
    }
    if(num == 0) {
        return no;
    } else {
        int c = rand()%num;
        return choices[c];
    }
}

void MazeGenerateMaze(int width, int height){
    Locinfo l = {false,false,false,false, false};
    stdvectorLocinfo currow(width,l);
    mazedata_.assign(height_, currow);
     TODO now the start point is set at the top left corner. May modify later
    stdstackstdpairint,int trace;
     Choose the initial cell, mark it as visited and push it to the stack
    stdpair int,int startpoint (0,0);  
    mazedata_[0][0].visited = true;
    trace.push(startpoint);
    stdpairint,int cur;
     While the stack is not empty
    while(!trace.empty()) {
         Pop a cell from the stack and make it a current cell
        cur = trace.top();
        trace.pop();
         mark the current cell as visited
        mazedata_[cur.first][cur.second].visited = true;
         If the current cell has any neighbours which have not been visited
        Locinfo curinfo = &mazedata_[cur.first][cur.second];
        stdstring nei = RandomNeighbor(cur.first, cur.second);
        if(nei == no) {
            continue;
        }
         Push the current cell to the stack
        trace.push(cur);
        stdpairint,int chosen_loc;
        Locinfo chosen_n;
         Choose one of the unvisited neighbours  Remove the wall between the current cell and the chosen cell
        if(nei == left) {
            curinfo-left = true;
            chosen_n = &mazedata_[cur.first][cur.second-1];
            chosen_n-right = true;
            chosen_loc = stdmake_pair(cur.first,cur.second-1);
        }
        if(nei == right) {
            curinfo-right = true;
            chosen_n = &mazedata_[cur.first][cur.second+1];
            chosen_n-left = true;
            chosen_loc = stdmake_pair(cur.first,cur.second+1);
        }
        if(nei == up) {
            curinfo-up = true;
            chosen_n = &mazedata_[cur.first-1][cur.second];
            chosen_n-down = true;
            chosen_loc = stdmake_pair(cur.first-1,cur.second);
        }
        if(nei == down) {
            curinfo-down = true;
            chosen_n = &mazedata_[cur.first+1][cur.second];
            chosen_n-up = true;
            chosen_loc = stdmake_pair(cur.first+1,cur.second);
        }
          Mark the chosen cell as visited and push it to the stack
        chosen_n.visited = true;
        trace.push(chosen_loc);
    }
}

void MazeMazeOut() {
    for(int i = 0; i  width_; ++i){
        stdcout   _;
    }
    stdcout  stdendl;
    for (int i = 0; i  width_; ++i){
        for (int j = 0; j  width_; ++j){
            Locinfo c = mazedata_[i][j];
            if (c.left)
                stdcout   ;
            else stdcout  ;
            stdcout  (c.down     _);
            
        }
        stdcout  ;
        stdcout  stdendl;
    }
}


stdsetstdvectorfloat MazeGetWallCoor() {
    stdsetstdvectorfloat toreturn;
     -0.7 to 0.7
    float range = 1.4f;
     the height of every brick
    float b_height = 1.4fheight_;
    float b_width = 0.05f;
    for(int i = 0; i  height_; i++) {
        for (int j = 0; j  width_; j++) {
            stdvectorfloat leftcoor;
            if(mazedata_[i][j].left == false) {
                push the four points of the left wall into coor in format of x1,x2,y1,y2
                 x1
                leftcoor.push_back(-0.7f + (b_height-b_width)  j);
                 x2
                leftcoor.push_back(-0.7f +(b_height-b_width)  j + b_width);
                 y1
                leftcoor.push_back(-0.7f +(b_height-b_width)  i);
                 y2
                leftcoor.push_back(-0.7f +(b_height-b_width)  i + b_height);
                toreturn.insert(leftcoor);
            }
            stdvectorfloat topcoor;
            if(mazedata_[i][j].up == false) {
                 push top wall into coor
                 x1
                topcoor.push_back(-0.7f +(b_height-b_width)  j);
                 x2
                topcoor.push_back(-0.7f +(b_height-b_width)  j + b_height);
                 y1
                topcoor.push_back(-0.7f +(b_height-b_width)  i);
                 y2
                topcoor.push_back(-0.7f +(b_height-b_width)  i + b_width);
                toreturn.insert(topcoor);
            }
        }
    }
     add the rightmost wall 
    float x1 = -0.7f + (b_height - b_width)  width_;
    float x2 = -0.7f + x1 + b_width;
    for(int i = 0; i  height_; i++) {
        stdvectorfloat temp;
         x1
        temp.push_back(x1);
         x2
        temp.push_back(x2);
         y1
        temp.push_back(-0.7f +(b_height-b_width)  i);
        y2
        temp.push_back (-0.7f +(b_height-b_width)  i + b_height);
        toreturn.insert(temp);
    }
    add down wall 
    float y1 = -0.7f +(b_height - b_width)  height_;
    float y2 = -0.7f +y1 + b_height;
    for(int i = 0; i  width_; i++) {
        stdvectorfloat temp;
         x1
        temp.push_back(-0.7f +(b_height-b_width)  i);
         x2
        temp.push_back(-0.7f +(b_height-b_width)  i + b_height);
         y1
        temp.push_back(y1);
         y2
        temp.push_back(y2);
        toreturn.insert(temp);
    }
    return toreturn;
} 

//  float MazeWallCoorArray(stdsetstdvectorfloat coor) {
//      float output = new float[coor.size()  4  3];
//      stdsetstdvectorfloatiterator wIt = coor.begin();
//      while(wIt != coor.end()) {
//          output
//      }
//  }