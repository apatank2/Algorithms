#include <iostream>
#include<cstring>
#include<string>
#include <fstream>
#include<cstdlib>
#include <iomanip>
using namespace std;
int size;

void PrintResult(int ptr_arr[]) //Method use to Print the Matrix
{
	int i,j;
	for (i = 1; i <= size; i++)
	{
		for ( j = 1; j <= size; j++)
			{
				cout<<ptr_arr[i*(size+1)+j]<<"\t";
			}
			cout<<"\n"<<endl;
	}

}
void CalculateShortestDistance(int distance_matrix[]) //Method use to Calculate Distance Matrix
{
    int k,i,j;
	for ( k = 1; k <= size; k++)
		{
			for ( i = 1; i <= size; i++)
			{
				for (j = 1; j <= size; j++)
				{
					if(distance_matrix[i*(size+1)+j]>(distance_matrix[i*(size+1)+k]+distance_matrix[k*(size+1)+j])){
						distance_matrix[i*(size+1)+j]=distance_matrix[i*(size+1)+k]+distance_matrix[k*(size+1)+j];
					}
				}
			}
		}
}
int getsize(char* filename) //Get the Size of the Matrix
{
string line;
    try
    {
      ifstream file(filename);

        string line;
        int size = 0;
        while(!file.eof()) // To get you all the lines.
        {
            size++;
            getline(file,line);
        }
        file.close();
        return size;


        }
	catch(int e)
	{
	    cout<<"File Not Found"<<endl;
	    exit(0);
	}
}
int main(int argc, char *argv[])
{
    char *file1 = argv[1];
    size = getsize(file1);
    int distance_matrix[size+1][size+1];
    ifstream file(file1);
    string line;
    int i = 1;
    try
    {
    while(!file.eof()) // To get you all the lines.
        {
	        getline(file,line);
            int n = line.length();
            char split[n+1];
            strcpy(split,line.c_str());
            char * pch;
            pch = strtok (split,",");
            int j = 1;
            while (pch != NULL)
            {
               distance_matrix[i][j] = atoi(pch);
               if (j == size)
                i++;
                j++;
                pch = strtok (NULL, ",");
            }
        }

     file.close();
     }
     catch(int e)
	 {
	    cout<<"File Not Found"<<endl;
	    exit(0);
	 }
    cout<<"Original Matrix :"<<endl;
    PrintResult((int *)distance_matrix);
    CalculateShortestDistance((int *)distance_matrix);
    cout<<"Distance Matrix :"<<endl;
    PrintResult((int *)distance_matrix);
    return 0;
}
