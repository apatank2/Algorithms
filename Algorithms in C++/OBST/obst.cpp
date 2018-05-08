// Name of program obst.cpp
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;

float mat[100][100];
int index2[100][100];

int v[100];
int count = 0;
int t,tmax = -1;
//creates an array of obst tree values
int printObst(int i, int j, int k){
    //cout << endl << "i-j-k" << i <<"," << j << "," << k;
  if (i > j)
    return 0;
  else {
    v[k] = index2[i][j];
    t = (2 * k) + 1;
    printObst (i, index2[i][j] - 1, t);
    t = (2 * k) + 2;
    printObst (index2[i][j] + 1, j, t);
  }
}

int main (int nkey, char** prob) {

    int level = 0;
    float ans1 = 0.0, result=0.0;
    if(nkey==1) {
      cout << "Enter more parameters" << endl;
      return 0;
    }

    cout << endl << "You have entered " << nkey-1 << " arguments:" << "\n";

    int key = atoi(prob[1]);
    if (nkey-2 > key || nkey-2 < key) {
      cout << "Incorrect number of probabilities !" << endl;
      return 0;
    }
    if(key==1) {
      cout << "Enter more than 1 probability" << endl;
      return 0;
    }
    char* p[key];
    cout << endl << "Keys--" << key;
    
    for(int i = 2; i <= nkey-1; i++) {
      p[i-2] = (char*)prob[i];
      }

    float val[key+1];
    val[0] = -1;
    for(int i = 0; i < key; i++) {
      val[i+1]=(atof(p[i]));
    }

    cout << "\nProbabilities--" << endl;
    for(int i = 1; i <= key; i++)
      cout << val[i] << "\n"; 
      
    for(int i = 0; i <= key; i++) {
      mat[0][i] = 0.0;
      index2[0][i] = 0.0;
      mat[i][0] = 0.0;
      index2[i][0] = 0.0;
      mat[key+1][i] = 0.0;
      index2[key+1][i] = 0.0;
    }

        for(int i = 0; i <= key+1; i++) { //rows
          for(int j = 0; j <= key; j++) { //columns
            index2[i][j] = 0.0;
          }
        }

    for(int i = 1; i <= key+1; i++) {
      for(int j = 1; j <= key; j++) {
        if(i==j) {
          mat[i][j] = val[i];
          index2[i][j] = i;
        }
        else
        mat[i][j] = 0;
      }
    }

      int j;
  //create cost matrix and corresponding index matrix
        for (level = 1; level < key; level++) {
          for(int i = 1; i <= (key - level); i++) {
            j = i + level;
            for(int k = i; k <= j; k++) {
              ans1 = ans1 + val[k];
            }
            float min = 999.99;
            for(int k = i; k <= j; k++) {
              if (min > (mat[i][k-1] + mat[k+1][j] + ans1)) {
                min = mat[i][k-1] + mat[k+1][j] + ans1;
                mat[i][j] = min;
                index2[i][j] = k;
              }
            }
            ans1 = 0.0;
            //cout << "ans1 = " << ans1 << endl;
          }
      }

    cout << "\nFinal Matrix--" << endl;
    for(int i = 0; i <= key+1; i++) {
      for (int j = 0; j <= key; j++) {
        cout << mat[i][j] <<"\t\t";
        }
        cout << endl;
    }

    cout << "\nFinal index--" << endl;
    for(int i = 0; i <= key+1; i++) {
      for (int j = 0; j <= key; j++) {
        cout << index2[i][j] <<"\t\t";
        }
        cout << endl;
    }
    //for printing the tree depth-wise
    int c = 1;
    printObst (1, key, 0);
    cout << endl << "Tree --";
      cout << endl << "depth 0 : " << index2[1][key];
      int vLen=1, depLen = 1;
      for(int i=0;i<100;i++) {
        if(v[i] > 0) {
          vLen++;
        }
      }
      vLen--;
    int depth = 1;
    while(vLen>depLen) {
      int k=1;
      cout << endl << "depth " << depth << " : ";
      while(k <= pow(2,depth)) {
          cout << v[c] << "\t";
        if(v[c] > 0) {
          depLen++;
        }
        c++;
        k++;
      }
      if(vLen==depLen) {
        break;
      }
      depth++;
    }
    cout << endl;
      return 0;
}
