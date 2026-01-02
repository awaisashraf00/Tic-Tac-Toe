#include <iostream>
#include <unordered_map>
using namespace std;

unordered_map<int,char> board;

void print_board();
bool check_winner(char player);
bool complete_game();

int game(char player);

int main() {
    for (int i = 1; i <= 9; i++)
        board[i] = '.';

    game('X');
}

int game(char player) {

    print_board();

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

void print_board(){
    cout << "\n";
    cout << board[1] << " | " << board[2] << " | " << board[3] << endl;
    cout << "--+---+--\n";
    cout << board[4] << " | " << board[5] << " | " << board[6] << endl;
    cout << "--+---+--\n";
    cout << board[7] << " | " << board[8] << " | " << board[9] << endl;
    cout << "\n";
}