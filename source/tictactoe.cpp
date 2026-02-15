#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include <raylib.h>

using namespace std;

// Board ka boxes ka size colors and or us ka data;
unordered_map<int,pair<char,int>> board;
vector<Color> box_colors = {BLACK,RED,BLUE};
int cell_size {100};

// Sary main functions jo game ka andar use karny hain
void Display_board(int current_pos);
void game_input(char &player);
void Insert_input(int pos, char player);
void computer_move();
int mini_max(bool maxi);
bool check_winner(char player);
bool complete_game();


int current_pos = 5;
bool p_put = true;


char p = 'X';
char computer = 'O';

int main() {
    
    for (int i = 1; i <= 9; i++){
        board[i].first = '.';
        board[i].second = 0;
    }

    //game start
    SetTargetFPS(60);
    InitWindow(300,300,"Mini_maX");

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        
        if(!complete_game() && !check_winner(p) && !check_winner(computer)){
            
            game_input(p);
            Display_board(current_pos);
            
            if(!p_put){
                
                computer_move();
                Display_board(current_pos);
                
            }
        }else{
            ClearBackground(RED);
            if(complete_game()){
                DrawText("DRAW",100,125,50,BLACK);
            }else{
                DrawText(check_winner(p)?"HUMAN WINS ":"COMPUTER WINS",100,150,20,BLACK);
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
        Insert_input(current_pos,player);
        p_put = false;
    }
}

void Insert_input(int pos ,char player){
    if(board[pos].first == '.'){ 
        board[pos].first = player;
        board[pos].second = (player == 'X') ? 1:2;
    }

}
int  i = 0;
void computer_move(){
    i++;
    double best = 100;
    int best_move = 0;
    for(int i{1};i<=9;i++){
        if(board[i].first == '.'){
            
            board[i].first = computer;
            board[i].second = 2;
            
            int current_score = mini_max(true);

            board[i].first = '.';
            board[i].second = 0;

            if(current_score < best){
                best = current_score;
                best_move = i;
            }
        }
    }
    Insert_input(best_move,computer);
    p_put = true;
}

// [o,x, ]
// [ ,x,o]
// [ ,o,x]

int mini_max(bool maxi){
    // if(i==3){
    //     BeginDrawing();
    //     Display_board(current_pos);
    //     EndDrawing();
    // }
    if( check_winner(p)) return 1;
    else if (check_winner(computer)) return -1;
    else if  (complete_game()) return 0;

    if (maxi){
        
        double best = -100;
        for(int i{1};i<=9;i++){
            if(board[i].first == '.'){

                board[i].first = p;
                board[i].second = 1;
                
                int current_score = mini_max(false);
                
                board[i].first = '.';
                board[i].second = 0;

                if(current_score > best){
                    best = current_score;
                }
            }
        }
        return best; 
    }
    else{

        double best = 100;
        for(int i{1};i<=9;i++){
            if(board[i].first == '.'){

                board[i].first = computer;
                board[i].second = 2;
                
                int current_score = mini_max(true);
                
                board[i].first = '.';
                board[i].second = 0;

                if(current_score < best){
                    best = current_score;
                }
            }
        }
        return best;
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

bool complete_game(){
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