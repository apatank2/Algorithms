#include <iostream>
#include<cstring>
#include<string>
#include <fstream>
#include<cstdlib>
#include <iomanip>
#include <sstream>
#include<vector>

using namespace std;

//Struct for basic node structure our huffman tree will have
struct Node
{
 Node * left;
 Node * right;
 int frequency;
 string content;
 string  TraversalCode;
};

Node ParsingNode[50];
vector<Node> AllNodes;

//sort function to sort the array of frequencies in the ascending order
void sort()
{
    for (int i = 1; i < AllNodes.size(); ++i){
        for (int j = 0; j < AllNodes.size() - 1; ++j){
            if (AllNodes[j].frequency > AllNodes[j+1].frequency) swap(AllNodes[j], AllNodes[j+1]);
        }
    }


}

//print function - to print the code associated with each character
void printCodes(Node * root, string str)
{

   if(root->left == NULL && root->right == NULL)
   {
    cout<<root->content<<" : "<<root->TraversalCode<<endl;
   }
   else
   {
   string temp;
   temp = str;
   root->left->TraversalCode = str.append("0");
   str = temp;
   root->right->TraversalCode = str.append("1");
   str = temp;

   printCodes(root->left,str.append("0"));
   str = temp;
   printCodes(root->right,str.append("1"));
   str = temp;
   }
}

int main(int argc, char *argv[])
{
   int Size = -1;
   int Line_Count = 1;
    char* file1 = argv[1];
    ifstream file(file1);
    string line;
    try
    {
      while(!file.eof()) //parsing file
        {
	        getline(file,line);
            //cout<<line<<endl;
            int n = line.length();
            char split[n+1];
            strcpy(split,line.c_str());
            char * pch;
            pch = strtok (split," , ");

            int temp_size = 0;

           while (pch != NULL)
            {
               if (Line_Count == 1)
               {

                    ParsingNode[temp_size].content = pch; // store characters
                    ParsingNode[temp_size].left= NULL;
                    ParsingNode[temp_size].right = NULL;
                    temp_size = temp_size + 1;
                    Size = Size + 1;
               }
               if (Line_Count == 2)
               {
                   ParsingNode[temp_size].frequency = atoi(pch); //store their corresponding frequencies
                    AllNodes.push_back(ParsingNode[temp_size]);
                    temp_size = temp_size + 1;

               }
                pch = strtok (NULL, ",");
            }
           Line_Count++;

        }

     file.close();
     //cout<<Size<<endl;
 sort();
  /*vector<Node>::iterator i;
  for (i = AllNodes.begin();i != AllNodes.end();i++)
  {
      cout<<(*i).frequency<<" "<<(*i).content<<endl;
  }

  cout<<"---------------------"<<endl;*/
  while(!AllNodes.empty())
 {
    int temp = 999;
    vector<Node>::iterator minelement;

      minelement = AllNodes.begin(); // the the two characters with minimum frequency
      Node * MinimumNode1 = new Node;
    *MinimumNode1 = (*minelement);
    //AllNodes.pop_back();
    AllNodes.erase(AllNodes.begin());

   Node * MinimumNode2 = new Node;
   minelement = AllNodes.begin();
    *MinimumNode2 = (*minelement);
   //AllNodes.pop_back();
    AllNodes.erase(AllNodes.begin());
   Node * NewNode = new Node;
   NewNode->left= MinimumNode1;

   NewNode->right = MinimumNode2;

   NewNode->frequency = MinimumNode1->frequency+MinimumNode2->frequency; //create a new node with the frequency equals addtition of the two nodes
   AllNodes.push_back(*NewNode); //add the new node to the list of characters
   sort();
  /* vector<Node>::iterator i;
  for (i = AllNodes.begin();i != AllNodes.end();i++)
  {
      cout<<(*i).frequency<<" "<<(*i).content<<endl;
  }
  cout<<"---------------------"<<endl;*/
   if(AllNodes.size() == 1) // continue doing this till only one node is left
   {
    break;
   }
 }


//print compressed codes
    printCodes(&AllNodes[0],"");
     }
     catch(int e)
	 {
	    cout<<"File Not Found"<<endl;
	    exit(0);
	 }

	 return 0;
}
