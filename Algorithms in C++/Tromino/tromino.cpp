#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>

using namespace std;

int label = 1;

void trominoTile (int bsize, int startx, int starty,int board[],int boardsize); //Implements the Tromino Tiling algorithm
void PrintResult(int board[],int boardsize); //Prints the Result Matrix
void InitializeMatrix(int board[],int boardsize,int x,int y); // Initialize the Matrix

int main (int argc, char *argv[]) {

    if (argc != 4) { //checks for invalid number of arguments
        cout << "Enter only 3 arguments !!" << endl;
        return 0;
    }

    cout << endl << "You have entered " << argc-1 << " arguments:" << endl;
    cout << endl << "K = " << argv[1] << endl;
    cout << "Position of the hole -- [" << argv[2] << ", " << argv[3] << "]" << endl;

    int k, x, y;
    k = atoi(argv[1]);
    x = atoi(argv[2]);
    y = atoi(argv[3]);

    if (k < 2) {
        cout << "Size of this board is out of scope !" << endl;
        return 0;
    }

    int boardsize = pow(2, k);
    int board[boardsize][boardsize];
    cout << "Board size = " << boardsize << endl;

    if (x > boardsize || y > boardsize) {
        cout << "Hole does not exist in the board !";
        return 0;
    }

    InitializeMatrix((int *)board,boardsize,x,y);
    board[x][y] = -1;

    cout<<"Initial Board ---"<<endl;
    PrintResult((int *)board,boardsize);

    trominoTile (boardsize, 0, 0,(int *)board,boardsize);

    cout << endl << "Tiling Done!" << endl;
    PrintResult((int *)board,boardsize);

    return 0;
}


void trominoTile (int bsize, int startx, int starty,int board[],int boardsize) {
    int x, y;

    if (bsize > 2) {
        for(int i = startx; i < startx + bsize; i++) {
            for(int j = starty; j < starty + bsize; j++) {
                if (board[i*(boardsize)+j] != 0) { //hole found, get the co-ordinates
                    x = i;
                    //cout << endl <<  "x = " << x;
                    y = j;
                    //cout << endl <<  "y = " << y;
                    break;
                }
            }
        }

        //search the first quadrant for hole
        if(x < bsize/2 + startx && y >= bsize/2 + starty) {
            trominoTile(bsize/2, startx, bsize/2 + starty,board,boardsize); //divide further
            board[(bsize/2 + startx) * (boardsize) + (bsize/2 + starty)] = label; //label the tile
            board[(bsize/2 + startx) * (boardsize) + (bsize/2 + starty - 1)] = label;
            board[(bsize/2 + startx - 1) * (boardsize) + (bsize/2 + starty - 1)] = label;
            label = label + 1;
            trominoTile(bsize/2, startx, starty,board,boardsize); //get adjacent tiles
            trominoTile(bsize/2, bsize/2 + startx, starty,board,boardsize);
            trominoTile(bsize/2, bsize/2 + startx, bsize/2 + starty,board,boardsize);
        }

        //search the second quadrant for hole
        else if(x < bsize/2 + startx && y < bsize/2 + starty) {
            trominoTile(bsize/2, startx, starty,board,boardsize); //divide further
            board[(bsize/2 + startx) * (boardsize) + (bsize/2 + starty)] = label; //label the tile
            board[(bsize/2 + startx) * (boardsize) + (bsize/2 + starty - 1)] = label;
            board[(bsize/2 + startx - 1) * (boardsize) + (bsize/2 + starty)] = label;
            label = label + 1;
            trominoTile(bsize/2, startx, bsize/2 + starty,board,boardsize); //get adjacent tiles
            trominoTile(bsize/2, bsize/2 + startx, starty,board,boardsize);
            trominoTile(bsize/2, bsize/2 + startx, bsize/2 + starty,board,boardsize);
        }

        //search the third quadrant for hole
        else if(x >= bsize/2 + startx && y < bsize/2 + starty) {
            trominoTile(bsize/2, bsize/2 + startx, starty,board,boardsize);// divide further
            board[(bsize/2 + startx) * (boardsize) + (bsize/2 + starty)] = label; //label the tile
            board[(bsize/2 + startx - 1) * (boardsize) + (bsize/2 + starty)] = label;
            board[(bsize/2 + startx - 1) * (boardsize) + (bsize/2 + starty - 1)] = label;
            label = label + 1;
            trominoTile(bsize/2, startx, starty,board,boardsize); //get adjacent tiles
            trominoTile(bsize/2, startx, bsize/2 + starty,board,boardsize);
            trominoTile(bsize/2, bsize/2 + startx, bsize/2 + starty,board,boardsize);

        }

        //search the fourth quadrant for hole
        else {
            trominoTile(bsize/2, bsize/2 + startx, bsize/2 + starty,board,boardsize); //divide further
            board[(bsize/2 + startx) * (boardsize) + (bsize/2 + starty - 1)] = label; //label  the tile
            board[(bsize/2 + startx - 1) * (boardsize) + (bsize/2 + starty)] = label;
            board[(bsize/2 + startx - 1) * (boardsize) + (bsize/2 + starty - 1)] = label;
            label = label + 1;
            trominoTile(bsize/2, startx, starty,board,boardsize); //get adjacent tiles
            trominoTile(bsize/2, bsize/2 + startx, starty,board,boardsize);
            trominoTile(bsize/2, startx, bsize/2 + starty,board,boardsize);
        }
    }
       else { //base condition (found a smallet set to tiles to label
        for(int i = 0; i < bsize; i++) {
            for(int j = 0; j < bsize; j++) {
                if(board[(startx + i) * (boardsize) + (starty + j)] == 0) { //do not label the 'X'
                    board[(startx + i)* (boardsize) + (starty + j)] = label;
                }
            }
        }
        label = label + 1;
    }
}
void PrintResult(int board[],int boardsize)
{
    for(int i = 0; i < boardsize; i++) {
        for(int j = 0; j < boardsize; j++) {
            if(board[i*(boardsize)+j] == -1) {
                cout << "X\t";
            }
            else
                cout << board[i*(boardsize)+j] << "\t";
        }
        cout << endl;
    }
}
void InitializeMatrix(int board[],int boardsize,int x,int y)
{
    for(int i = 0; i < boardsize; i++) {
        for(int j = 0; j < boardsize; j++) {
            board[i* (boardsize) + j] = 0;
        }
    }
}
