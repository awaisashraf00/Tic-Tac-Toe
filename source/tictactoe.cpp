#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include "raylib.h"

using namespace std;

// Board ka boxes ka size colors and or us ka data;
unordered_map<int,pair<char,int>> board;
vector<Color> box_colors = {BLACK,RED,BLUE};
int cell_size {100};

// Sary main functions jo game ka andar use karny hain
void Display_board(int current_pos);
bool check_winner(char player);
bool complete_game(char player);
void game_input(char &player);


int current_pos = 5;

bool game_ended = false;
int main() {
    
    for (int i = 1; i <= 9; i++){
        board[i].first = '.';
        board[i].second = 0;
    }
    
    char p = 'X';

    //game start
    SetTargetFPS(60);
    InitWindow(300,400,"Mini_maX");

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        
        if(!game_ended && !complete_game(p) && !check_winner(p)){
            char prev_player = p;
            game_input(p);
            Display_board(current_pos);
            
            string cell_str(1,p);
            string player_text = "Current Player: " + cell_str;
            DrawText(player_text.c_str(), (100/2)+20 , 340, 20 , BLACK);

            if(check_winner(prev_player) || complete_game(p)){
                game_ended = true;
            }
        }
        if(game_ended){ 
            Display_board(current_pos);
            char winner = (p == 'X') ? 'O' : 'X';
            if(check_winner(winner)){
                string winner_text = string(1, winner) + " IS the winner";
                DrawText(winner_text.c_str(),(100/2)+20 , 340, 20 ,BLACK);
            }else{
                DrawText("GAME_OVER" , (100/2)+20 , 340, 20 , BLACK);
            }
        }
        EndDrawing();
        
    }
    CloseWindow();
    
}

void game_input( char &player) {

    if(IsKeyPressed(KEY_UP)){
        current_pos -= 3;
        if(current_pos < 1) current_pos = 1;
    }
    if(IsKeyPressed(KEY_DOWN)){
        current_pos += 3;
        if(current_pos > 9) current_pos = 9;
    }
    if(IsKeyPressed(KEY_LEFT)){
        current_pos -= 1;
        if(current_pos < 1) current_pos = 1;
    }
    if(IsKeyPressed(KEY_RIGHT)){
        current_pos += 1;
        if(current_pos > 9) current_pos = 9;
    }
    if(IsKeyPressed(KEY_ENTER)){
        if(current_pos >= 1 && current_pos <= 9 && board[current_pos].first == '.') {
            board[current_pos].first = player;
            board[current_pos].second = (player == 'X') ? 1:2;
            player = (player == 'X') ? 'O' : 'X';
        }
    }
}


bool check_winner(char p) {
    int win[8][3] = {
        {1,2,3},{4,5,6},{7,8,9},
        {1,5,9},{3,5,7},
        {1,4,7},{2,5,8},{3,6,9}
    };

    for (auto &w : win)
        if (board[w[0]].first == p && board[w[1]].first == p && board[w[2]].first == p)
            return true;

    return false;
}

bool complete_game(char p){
    for (int i{1};i<=9;i++){
        if (board[i].first=='.'){
            return false;
        }
    }
    return true;
}

void Display_board(int current_pos){
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            int cell_index = row * 3 + col + 1;
            DrawRectangle((col * cell_size)+1 , (row * cell_size )+1, cell_size-2, cell_size-2,
                          box_colors[board[cell_index].second]);
            
            // Highlight current position with yellow border
            if (cell_index == current_pos) {
                DrawRectangleLines((col * cell_size)+1, (row * cell_size )+1, cell_size-2, cell_size-2, YELLOW);
                DrawRectangleLines((col * cell_size)+2, (row * cell_size )+2, cell_size-4, cell_size-4, YELLOW);
            }
            
            char cell_char = board[cell_index].first;

            if (cell_char != '.') {
                string cell_str(1, cell_char);
                int fontSize = 40;
                int textWidth = MeasureText(cell_str.c_str(), fontSize);
                int textX = col * cell_size + (cell_size - textWidth) / 2;
                int textY = row * cell_size + (cell_size - fontSize) / 2;
                DrawText(cell_str.c_str(), textX, textY, fontSize, WHITE);
            }
        }
    }
}