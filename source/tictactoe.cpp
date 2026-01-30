#include <iostream>
#include <unordered_map>
#include "raylib.h"

using namespace std;
unordered_map<int,char> board;

int cell_size {100};

void Display_board();
bool check_winner(char player);
bool complete_game();

int game(char player);

int main() {

    for (int i = 1; i <= 9; i++){
        board[i] = '.';
    }
    SetTargetFPS(60);
    InitWindow(300,300,"Mini_maX");

    ClearBackground({255,255,255});
    
    while (!WindowShouldClose())
    {
        BeginDrawing();
        if(!complete_game()){
            Display_board();
        }
        EndDrawing();
        
    }
    CloseWindow();
    
}

int game(char player) {



    if (check_winner(player == 'X' ? '0' : 'X')) {
        cout << "Player " << (player == 'X' ? '0' : 'X') << " wins!\n";
        return 0;
    }

    if (complete_game()) {
        cout << "DRAW!\n";
        return 0;
    }

    int pos;
    cout << "Player " << player << ", enter position (1-9): ";
    cin >> pos;

    if (pos < 1 || pos > 9 || board[pos] != '.') {
        cout << "Invalid move. Try again.\n";
        return game(player);
    }

    board[pos] = player;

    return game(player == 'X' ? '0' : 'X');
}


bool check_winner(char p) {
    int win[8][3] = {
        {1,2,3},{4,5,6},{7,8,9},
        {1,5,9},{3,5,7},
        {1,4,7},{2,5,8},{3,6,9}
    };

    for (auto &w : win)
        if (board[w[0]] == p && board[w[1]] == p && board[w[2]] == p)
            return true;

    return false;
}

bool complete_game(){
    for (int i{1};i<=9;i++){
        if (board[i]=='.'){
            return false;
        }
    }
    return true;
}

void Display_board(){
    for(int i{0};i<3;i++){
        for(int j{0};j<0;j++){   
            DrawRectangle(cell_size * i,cell_size * j,cell_size - 1,cell_size - 1,{128,128,128});
        }
    }
}