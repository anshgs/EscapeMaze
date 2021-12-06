#include "ai.hpp"
#include<queue>
#include<cmath>
#include<iostream>
Ai::Ai(){
    
}

void Ai::SetAttributes(pair<float, float> coords, float speed, float size){
    coord_x_ = coords.first;
    coord_y_ = coords.second;
    speed_ = speed;
    raw_speed_ = speed;
    size_x_ = 1.2*size;
    size_y_ = 1.2*size;
}

void Ai::UpdateSpeed(float refresh_rate_){
    if(refresh_rate_!=0){
        speed_ = 1.0F/refresh_rate_ * raw_speed_;
    }
}

void Ai::MoveUp() {
    coord_y_ += speed_;
}

void Ai::MoveDown() {
    coord_y_ -= speed_;
}
    
void Ai::MoveLeft() {
    coord_x_ -= speed_;
}
    
void Ai::MoveRight() {
    coord_x_ += speed_;
}

float Ai::GetSizeX(){
    return size_x_;
}
float Ai::GetSizeY(){
    return size_y_;
}

float Ai::GetSpeed(){
    return speed_;
}

/*void Ai::ScanMaze(Maze& maze){
    maze_ = &maze;
    cout << maze_->GetHeight();
}*/

pair<float, float> Ai::GetCenter(){
    return {coord_x_, coord_y_};
}

void Ai::Seek(pair<float, float> player_coords, int height, Maze& maze){
    pair<int, int> player_loc = CastCoorFloatToGrid(player_coords.first, player_coords.second, height);
    pair<int, int> cur_loc = CastCoorFloatToGrid(coord_x_, coord_y_, height);
    pair<float, float> target = {-1.0F, -1.0F};
    if(cur_loc == player_loc){
        target = player_coords;
    }
    else{
        queue<vector<int>> bfs;

        vector<vector<bool>> vis(height, vector<bool>(height, false));

        vis[cur_loc.second][cur_loc.first] = true;
        Locinfo cur_loc_info = maze.GetLocinfo(cur_loc.second, cur_loc.first);
        //{0:left, 1:up, 2:right, 3:down}
        if(cur_loc_info.left){
            bfs.push({cur_loc.first-1, cur_loc.second, 0});
            vis[cur_loc.second][cur_loc.first-1] = true;
        }
        if(cur_loc_info.up){
            bfs.push({cur_loc.first, cur_loc.second-1, 1});
            vis[cur_loc.second-1][cur_loc.first] = true;
        }
        if(cur_loc_info.right){
            bfs.push({cur_loc.first+1, cur_loc.second, 2});
            vis[cur_loc.second][cur_loc.first+1] = true;
        }
        if(cur_loc_info.down){
            bfs.push({cur_loc.first, cur_loc.second+1, 3});
            vis[cur_loc.second+1][cur_loc.first] = true;
        }
        
        while(!bfs.empty()){
            vector<int> polled = bfs.front();
            if(polled[0] == player_loc.first && polled[1] == player_loc.second){
                if(polled[2] == 0){
                    target = CastCoorGridToFloat(cur_loc.first-1, cur_loc.second, height);
                }
                else if(polled[2] == 1){
                    target = CastCoorGridToFloat(cur_loc.first, cur_loc.second-1, height);
                }
                else if(polled[2] == 2){
                    target = CastCoorGridToFloat(cur_loc.first+1, cur_loc.second, height);
                }
                else if(polled[2] == 3){
                    target = CastCoorGridToFloat(cur_loc.first, cur_loc.second+1, height);
                }
            }
            bfs.pop();
            Locinfo polledloc = maze.GetLocinfo(polled[1], polled[0]);
            if(polledloc.left && !vis[polled[1]][polled[0]-1]){
                vis[polled[1]][polled[0]-1] = true;
                bfs.push({polled[0]-1, polled[1], polled[2]});
            }
            if(polledloc.up && !vis[polled[1]-1][polled[0]]){
                vis[polled[1]-1][polled[0]] = true;
                bfs.push({polled[0], polled[1]-1, polled[2]});
            }
            if(polledloc.right && !vis[polled[1]][polled[0]+1]){
                vis[polled[1]][polled[0]+1] = true;
                bfs.push({polled[0]+1, polled[1], polled[2]});
            }
            if(polledloc.down && !vis[polled[1]+1][polled[0]]){
                vis[polled[1]+1][polled[0]] = true;
                bfs.push({polled[0], polled[1]+1, polled[2]});
            }
        }
    }
    pair<int, int> temp_grid = CastCoorFloatToGrid(target.first, target.second, height);
    if(target.first == -1.0F){
        return;
    }
    float x_diff = target.first - coord_x_;
    float y_diff = target.second - coord_y_;
    if(x_diff > 0)
        coord_x_ += sqrt(x_diff*x_diff/(x_diff*x_diff + y_diff*y_diff)) * speed_;
    else
        coord_x_ -= sqrt(x_diff*x_diff/(x_diff*x_diff + y_diff*y_diff)) * speed_;
        
    if(y_diff > 0)
        coord_y_ += sqrt(y_diff*y_diff/(x_diff*x_diff + y_diff*y_diff)) * speed_;
    else
        coord_y_ -= sqrt(y_diff*y_diff/(x_diff*x_diff + y_diff*y_diff)) * speed_;
}

float Ai::Getcoordx() {
    return coord_x_;
}
        
float Ai::Getcoordy() {
    return coord_y_;
}

float * Ai::GetHitbox(){
    float x1 = coord_x_ - size_x_/2.0F;
    float x2 = coord_x_ + size_x_/2.0F;
    float y1 = coord_y_ - size_y_/2.0F;
    float y2 = coord_y_ + size_y_/2.0F;
    float * hitbox = new float[12];
    hitbox[0] = x1;
    hitbox[1] = y1;
    hitbox[2] = 0.0F;
    hitbox[3] = x2;
    hitbox[4] = y1;
    hitbox[5] = 0.0F;
    hitbox[6] = x2;
    hitbox[7] = y2;
    hitbox[8] = 0.0F;
    hitbox[9] = x1;
    hitbox[10] = y2;
    hitbox[11] = 0.0F;
    return hitbox;

    
}

vector<float> Ai::GetCorners(){
    float x1 = coord_x_ - size_x_/2.0F;
    float x2 = coord_x_ + size_x_/2.0F;
    float y1 = coord_y_ - size_y_/2.0F;
    float y2 = coord_y_ + size_y_/2.0F;
    vector<float> hitbox;
    hitbox.push_back(x1);
    hitbox.push_back(x2);
    hitbox.push_back(y1);
    hitbox.push_back(y2);
    return hitbox;
}