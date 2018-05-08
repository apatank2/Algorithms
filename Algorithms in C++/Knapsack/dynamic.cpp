#include <iostream>
#include<cstring>
#include<string>
#include <fstream>
#include<cstdlib>
#include <iomanip>
#include <sstream>
using namespace std;
int B[10][100];
int C[10][100];
int merge(int a, int b) {
   int times = 1;
   while (times <= b)
      times *= 10;
   return a*times + b;
}
int main()
{
    int Size;
    int knapsack_Capacity;
    int temp1;
    int temp2;
    int weights[20];
    int profits[20];
    //cout << "Hello world!" << endl;
    int Line_Count = 0;
    char *file1 = argv[1];
    ifstream file(file1);
    string line;
    int i = 1;
    try
    {
    while(!file.eof())
        {
	        getline(file,line);
            //cout<<line<<endl;
            int n = line.length();
            char split[n+1];
            strcpy(split,line.c_str());
            char * pch;
            pch = strtok (split,",");
            int j = 1;
            if (Line_Count == 0)
            {
                Size = atoi(pch);

            }
            if (Line_Count == 1)
            {
               knapsack_Capacity = atoi(pch);

            }
            if (Line_Count == 2 || Line_Count == 3)
            {
                int temp_size = 1;
            while (pch != NULL)
            {

               if (Line_Count == 2)
               {
                   profits[temp_size] = atoi(pch);

                   temp_size = temp_size + 1;
               }
               if (Line_Count == 3)
               {
                   weights[temp_size] = atoi(pch);
                   temp_size = temp_size + 1;
               }


                pch = strtok (NULL, ",");
            }

            } Line_Count++;
        }

     file.close();
     int i;
     //cout<<Size<<endl;
     //cout<<knapsack_Capacity<<endl;
     /*for (i = 0; i <Size ; i++)
     {
         cout<<weights[i]<<endl;
          cout<<profits[i]<<endl;
     }*/

     for (int w = 0; w<knapsack_Capacity; w++) {
        B[0][w] = 0;

    }
    for (int k = 1; k<=Size; k++) {
       B[k][0] = 0;
        for (int w = 1; w<=knapsack_Capacity; w++) {
                 //cout<<" "<<weights[k-1]<<" < "<<w<<" "<<B[k-1][w-weights[k-1]]+profits[k-1]<<" > "<<B[k-1][w]<<endl;
           if ((weights[k]<=w) && (B[k-1][w-weights[k]]+profits[k] > B[k-1][w])){
           B[k][w] = B[k-1][w-weights[k]] + profits[k];
           if (B[k-1][w-weights[k]]== 0)
            C[k][w] = k;
           else
           {
          // C[k][w] = (C[k-1][w-weights[k]] * 10) + k-1;
           C[k][w] = merge(C[k-1][w-weights[k]] , k);
           /*if (C[k-1][w-weights[k-1]] == 0)
           {
               flag = 0;
           }*/
           }

           }
           else {B[k][w] = B[k-1][w];
            C[k][w] = C[k-1][w];
           };

           temp1 = k;
           temp2 = w;
           //cout<<k<<" "<<w<<" "<<B[k][w]<<endl;
       }
    }

     cout<<B[temp1][temp2]<<endl;

     //cout<<C[temp1][temp2]<<endl;
     int n = C[temp1][temp2];
     int loop_cnt = 0;
     int store[20];
     int digit;
     int length = 0;
     int w = 0;
     while(n) {

      digit = n % 10;
      //cout<<digit<<endl;
      if (digit == 0)
      {
         store[length] = 10;
          n /= 10;

          w = w + weights[ store[length]];
          length++;
      }
      else
      {
          store[length] = digit;


          w = w + weights[ store[length]];
          length++;
      }
       n /= 10;
      }
      cout<<w<<endl;
      length--;
      cout<<"Items Selected :"<<endl;
      for (; length >=0; length--)
      {

        cout<<"Profit : "<<profits[ store[length]];
        cout<<"\tWeight : "<<weights[ store[length]]<<endl;
        //cout<<length<<endl;
      }


     }

     catch(int e)
	 {
	    cout<<"File Not Found"<<endl;
	    exit(0);
	 }
}
