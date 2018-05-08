#include <iostream>
#include<cstring>
#include<string>
#include <fstream>
#include<cstdlib>
#include <iomanip>
using namespace std;
struct knapsack_item
{
int weight;
int profit;
int flag;
}knapsack_item;
char include[20];
int MaxWeight;
int MaxProfit;
int bestset[20];
struct knapsack_item sorted_knapsack[20];
struct knapsack_item elements[20];
int knapsack_Capacity;
int KWF4(int i, int Weight, int Profit,int n)
{
    int bound = Profit;

		while((Weight<knapsack_Capacity) && (i<=n)){

			if( ( sorted_knapsack[i].weight + Weight ) <=knapsack_Capacity){
				Weight = Weight + sorted_knapsack[i].weight;
				bound = bound + sorted_knapsack[i].profit;
			}else{
				int CalcWeight = (knapsack_Capacity - Weight/sorted_knapsack[i].weight);
				bound = bound + ( (sorted_knapsack[i].profit) * CalcWeight);
			}
			i++;
		}
		return bound;
}

bool promising(int i, int Weight, int Profit,int n){

	int bound;
	if( Weight>=knapsack_Capacity )
    {
		return false;
	}
    bound = KWF4(i,Weight,Profit,n);
        if(bound>Profit)
        return true;
	    else
	    return false;
}


void knapsack(int j, int Profit, int Weight,int n){

	if((Weight<=knapsack_Capacity) && (Profit > MaxProfit)) {

		MaxProfit = Profit;
        MaxWeight = Weight;
		int i;
		for ( i = 0; i <= n; ++i)
		{
			if(include[i]=='Y')
				bestset[i]= sorted_knapsack[i].flag;
			else
                bestset[i] = 999;
		}

	}

     if(promising(j, Weight, Profit,n)){
	    include[j+1]='Y';
		knapsack(j+1, Profit + sorted_knapsack[j+1].profit, Weight+sorted_knapsack[j+1].weight,n);
		include[j+1]='N';
		knapsack(j+1,Profit,Weight,n);
	}



}
void knapsack(int n)
{
    int j;
     /*for (j=0;j<n;j++)
     {
        cout<<"Weight of " <<j; cout<< " element is "<<elements[j].weight<<endl;
        cout<<"Profit of " <<j; cout<< " element is "<<elements[j].profit<<endl;
     }*/
    int sort_index = -1;
    int profit = 0;
    int k;
    int calc_profit =0;
    for(k=0;k<n;k++)
    {
    for (j=0;j<n;j++)
    {
    if (elements[j].flag   >= 0 )
    {
      calc_profit = elements[j].profit / elements[j].weight;


    if (profit <= calc_profit)
    {
         sort_index = j;
         profit = calc_profit;
         //elements[j].profit = -1;
    }
    }
    }

    if (sort_index >= 0)
    {
    sorted_knapsack[k+1] = elements[sort_index];
    sorted_knapsack[k+1].flag = sort_index;
    include[k+1] = 'N';
    bestset[k+1] = 999;
    }
    elements[sort_index].flag = -1;
    sort_index = -1;
    profit = 0;
    calc_profit =0;
    }
    //cout <<"------------------------------------------------"<<endl;
   /* for (j=1;j<=n;j++)
     {
        cout<<"Weight of " <<j; cout<< " element is "<<sorted_knapsack[j].weight<<endl;
        cout<<"Profit of " <<j; cout<< " element is "<<sorted_knapsack[j].profit<<endl;
     }*/
    n = n + 1;
    MaxWeight = 0;
    MaxProfit = 0;
    knapsack(0,0,0,n);

     cout<<"Maximum Weight : "<<endl;
     cout<<MaxWeight<<endl;
     cout<<"Maximum Profit : "<<endl;
     cout<<MaxProfit<<endl;
    int i;
    cout<<"Items Selected : "<<endl;
	for (i = 1; i <= n; i++)
	{
		if(bestset[i]!=999){
			//cout<< elements[bestset[i]].;
			cout<<"Profit : "<<elements[bestset[i]].profit;
        cout<<"\tWeight : "<<elements[bestset[i]].weight<<endl;
		}

	}
}
int main()
{

    int Size;
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
                int temp_size = 0;
            while (pch != NULL)
            {

               if (Line_Count == 2)
               {
                   elements[temp_size].profit = atoi(pch);
                   elements[temp_size].flag = 1;
                   temp_size = temp_size + 1;
               }
               if (Line_Count == 3)
               {
                   elements[temp_size].weight = atoi(pch);
                   temp_size = temp_size + 1;
               }


                pch = strtok (NULL, ",");
            }

            } Line_Count++;
        }

     file.close();
     }
     catch(int e)
	 {
	    cout<<"File Not Found"<<endl;
	    exit(0);
	 }
    knapsack(Size);
    return 0;
}
