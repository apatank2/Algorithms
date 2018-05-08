#include <iostream>
#include<cstring>
#include<string>
#include <fstream>
#include<cstdlib>
#include <iomanip>
#include <sstream>
#include <math.h>
using namespace std;
int B[10][100];
int items;
int allitems;
 int merge(int a, int b) {
   int times = 1;
   while (times <= b)
      times *= 10;
   return a*times + b;
}
int main()
{
    int Size;
    int comp_profit,comp_weights,power;
    int MaxProfit = 0;
    int MaxWeight = 0;
    int knapsack_Capacity;
    int temp1;
    int temp2;
    int weights[20];
    int profits[20];
    cout << "BruteForce" << endl;
    int Line_Count = 0;
    char *file1 = argv[1];
    ifstream file(file1);
    string line;
    int i = 1;
    try
    {
    while(!file.eof()) //parse input file
        {
	        getline(file,line);
            //cout<<line<<endl;

            int n = line.length();
            char split[n+1];
            strcpy(split,line.c_str());
            char * pch;
            pch = strtok (split,",");
            int j = 1;
            if (Line_Count == 0) //store number of items
            {
                Size = atoi(pch);

            }
            if (Line_Count == 1) //store knapsack capacity
            {
               knapsack_Capacity = atoi(pch);

            }
            if (Line_Count == 2 || Line_Count == 3) //store their weights and corresponding profit
            {
                int temp_size = 0;
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


    int cnt = 0;
    int flag = 999;
    for(int x=0;x < pow(2,Size);x++) //calculate all subsets who have weight witihn the capacity, mark all subsets as either valid or invalid
    {

        for(int i=0;i<Size;i++)
        {
            if (cnt == 0)
            {
                 power = x;
                 cnt = cnt + 1;
            }

            if(power%2==1){
                comp_weights = comp_weights + weights[i];
                comp_profit  = comp_profit + profits[i];
                if (flag != 999)
                {
                 items = merge(items,i+1); //merge if valid to occupy capacity

                }
                else
                    {items = i+1; //ignore invalid ones
                    flag = 0;}
            }

            power = power/2;
        }
//select the best out of valid ones
        cnt = 0;
        if(comp_weights<=knapsack_Capacity && comp_profit>MaxProfit){
                MaxProfit=comp_profit;
                MaxWeight=comp_weights;
                flag = 999;
                allitems = items;
        }
        flag = 999;
        comp_weights = 0;
        comp_profit = 0;
    }


    cout<<MaxProfit<<endl;
     cout<<MaxWeight<<endl;
     //cout<<allitems<<endl;
     int n = allitems;
     int loop_cnt = 0;
     int store[20];
     int digit;
     int length = 0;
// find the items selected
     while(n) {

      digit = n % 10;
      //cout<<digit<<endl;
      if (digit == 0)
      {
         store[length] = 9;
          n /= 10;


          length++;
      }
      else
      {
          store[length] = digit - 1;
          length++;
      }
       n /= 10;
      }

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
