#include<iostream>
#include<stdio.h>
#include <unistd.h>
using namespace std;

void printBoard(char board[3][3], int score_x, int score_o, int ties);
void fillBoardWithSpace(char board[3][3]);
void readMove(char board[3][3], char player);
char analyzeBoard(char board[3][3], int *score_x, int *score_o);
char selectChamp(int score_x, int score_o);
void help();
void play();

int main(){
    cout<<"================================\n";
    cout<<"[*] Welcome to Tic Tac Toe Game!\n";
    while (true){
        cout<<"================================\n";
        cout<<" [1] Play   [2] Help   [3] Exit\n";
        cout<<" [>] Enter your choice: ";
        int choice;
        cin>>choice;
        switch (choice)
        {
        case 1:
            play();
            break;
        case 2:
            help();
            break;
        case 3:
            cout<<"[!] Have a nice day, Goodbye!";
            return 0;
        default:
            break;
        }
    }
}

void help(){
    cout<<"[#] Press 1 in menu to play the game. Then, choose game length (rounds). The game will be started after this.\n";
    cout<<"[#] You should select your playing character (X or O, no need to enter it in computer)\n";
    cout<<"[#] When you see your character, it means that it's your turn to play\n";
    cout<<"[#] Choose your square number (9 to 1, 9 is the top-left square and 1 is right-bottom square\n";
    cout<<"[#] Then press enter to submit your selection\n";
    cout<<"[#] Have a good game!\n\n";
}

void play(){
    int score_x = 0, score_o = 0, ties = 0, move = 0;
    int gameLength = 0;
    char board[3][3];
    char result, player = 'X';

    cout<<"[>] Enter game length (example: 3): ";
    cin>>gameLength;

    for (int round=1; round<=gameLength; round++){
        fillBoardWithSpace(board);
        result = 'M';
        move = 0;
        while (true){
            if (move>=9){
                cout<<"[=] Round Tie! \n";
                ties+=1;
                break;
            }
            printBoard(board, score_x, score_o, ties);
            readMove(board, player);
            move++;
            result = analyzeBoard(board, &score_x, &score_o);
            if (result=='M' && move<=9){
                switch (player){ case 'X': player='O'; break; case 'O': player='X'; break;}
                continue;
            }
            else if (result=='M' && move>9){
                cout<<"[=] Round Tie! \n";
                ties+=1;
                break;
            }
            else {
                cout<<"[+] "<<result<<" won this round (round: "<<round<<")\n";
                sleep(2);
                break;
            }
        }
    }

    char champ = selectChamp(score_x, score_o);
    printBoard(board, score_x, score_o, ties);
    printf("[+] X: %d - Ties: %d - O: %d\n[+] Champ: %c\n\n", 
        score_x, ties, score_o, champ);
}

void printBoard(char board[3][3], int score_x, int score_o, int ties){
    system("cls");
    printf("X: %d - Ties: %d - O: %d\n\n", 
        score_x, ties, score_o);
    cout<<" =======\n";
    cout<<" ="<<board[0][0]<<"="<<board[0][1]<<"="<<board[0][2]<<"=\n";
    cout<<" =======\n";
    cout<<" ="<<board[1][0]<<"="<<board[1][1]<<"="<<board[1][2]<<"=\n";
    cout<<" =======\n";
    cout<<" ="<<board[2][0]<<"="<<board[2][1]<<"="<<board[2][2]<<"=\n";
    cout<<" =======\n\n";
}

void readMove(char board[3][3], char player){
    while (true){
        cout<<"["<<player<<"] Choose your square: ";

        int square=0;
        cin>>square;
        if (square<1 || square>9){
            cout<<"[!] Square number must be between 1 and 9!\n";
            continue;
        }
        square--;

        int row = 2 - square/3;
        int col = square % 3;

        if (board[row][col]==' ')
        {
            board[row][col] = player;
            return;
        }
        else {
            cout<<"[!] Square "<<square+1<<" is already filled!\n";
        }
    }
}

void fillBoardWithSpace(char board[3][3]){
    for (int i=0; i<3; i++){
        for (int j=0; j<3; j++){
            board[i][j]=' ';
        }
    }
}

void addScore(char player, int *score_x, int *score_o){
    if (player=='X' || player=='x'){
        *score_x += 1;
    }
    else if (player=='O' || player=='o'){
        *score_o += 1;
    }
}

char analyzeBoard(char board[3][3], int *score_x, int *score_o){
    // Horizontal & Vertical
    for (int i=0; i<3; i++){
        // Horizontal
        if (board[i][0]==board[i][1]&&board[i][1]==board[i][2]  && board[i][2]!=' '){
            addScore(board[i][0], score_x, score_o);
            return board[i][0];
        }
        // Vertical
        if (board[0][i]==board[1][i]&&board[1][i]==board[2][i] && board[2][i]!=' '){
            addScore(board[0][i], score_x, score_o);
            return board[0][i];
        }
    }
    // Diameter 
    if (board[0][0]==board[1][1]&&board[1][1]==board[2][2] && board[2][2]!=' '){
        addScore(board[0][0], score_x, score_o);
            return board[0][0];
    }
    if (board[0][2]==board[1][1]&&board[1][1]==board[2][0] && board[2][0]!=' ')
    {
        addScore(board[0][2], score_x, score_o);
        return board[0][2];
    }
    return 'M';
}

char selectChamp(int score_x, int score_o){
    if (score_x>score_o){
        return 'X';
    }
    else if (score_x<score_o){
        return 'O';
    }
    return 'N';
}
