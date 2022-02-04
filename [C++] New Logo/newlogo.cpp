#include<iostream>
using namespace std;

int main(){
    int n=0, k=0;
    cin>>k>>n;
    int diameter=2*n+1;
    char board[diameter][diameter];

    // Fill board with space
    for (int i=0; i<diameter; i++){
        for (int j=0; j<diameter; j++){
            board[i][j]=' ';
        }
    }

    // Draw shape on board
    int golden=diameter/2+2;
    for (int i=0; i<=diameter/2; i++){
        for (int j=0; j<=diameter/2; j++){
            if (i+j+2>=golden && i+j+2<golden+k){
                board[i][j]='*';
            }
        }
    }
    
    // Flip 1
    for (int i=0; i<=diameter/2; i++){
        for (int j=0; j<=diameter/2; j++){
            if (board[i][diameter/2-j]=='*'){
                board[i][diameter/2+j]='*';
            }
        }
    }

    // Flip 2
    for (int i=0; i<=diameter/2; i++){
        for (int j=0; j<diameter; j++){
            if (board[diameter/2-i][j]=='*'){
                board[diameter/2+i][j]='*';
            }
        }
    }



    // Print board
    for (int i=0; i<diameter; i++){
        for (int j=0; j<diameter; j++){
            cout<<board[i][j];
        }
        cout<<"\n";
    }
}