#include <iostream>
#include <vector>
#include <string>
using namespace std;


void printIterativeParentheses(vector<vector<int>>& input)
{
	if (input.size() <= 1)
	{
		cout << "Error" << endl;
		return;
	}
	vector<int> stack;
	string acc ("");
	
	stack.push_back(0);
	stack.push_back(input.size() - 1);	
	while (!stack.empty())
	{		
		int i = stack.back();
		stack.pop_back();
		switch (i)
		{
		 case -1: acc='('+acc;  break;
		 case -2: acc=')'+acc;  break;
		 case -3: acc='x'+acc; break;
		 default:		
			int j = stack.back();
			stack.pop_back();
			if (i == j)
			{				
				acc=to_string(i)+acc;
			}
			else
			{
				stack.push_back(-1);
				stack.push_back(j);
				stack.push_back(input[i][j]);
				stack.push_back(-3);
				stack.push_back(input[i][j] + 1);
				stack.push_back(i);
				stack.push_back(-2);
			}
			break;			
		}
		
	}
	cout << acc<<endl;
	
}


void printRecursiveParentheses(vector<vector<int>>& input, int i, int j)
{
	if (i == j)
		cout << i;
	else
	{
		cout << "(";
		printRecursiveParentheses(input, input[i][j], j);
		cout << "x";
		printRecursiveParentheses(input, i, input[i][j] + 1);
		cout << ")";
	}
}

void printRecursiveParentheses(vector<vector<int>>& input)
{	
	if(input.size()>1)
	 printRecursiveParentheses(input, input.size() - 1, 0);
}

int matrixChainMultiplyLookUp(vector<int>chain, vector<vector<int>> &lookUpTable)
{
	if (chain.size() < 2)
		return -1;
	int chain_length = chain.size() - 1;
	lookUpTable = vector< vector<int> >(chain_length, vector<int>(chain_length, 0));
	for (int chainLeng = 1; chainLeng < chain_length; chainLeng++)
	{
		for (int i = 0; i < chain_length - chainLeng; i++)
		{
			int j = i + chainLeng;			
			for (int k = i; k < j; k++)
			{
				int q = lookUpTable[i][k] + lookUpTable[k + 1][j] + chain[i] * chain[k + 1] * chain[j + 1];				
				if (lookUpTable[i][j] == 0 || q < lookUpTable[i][j])
				{
					lookUpTable[i][j] = q;
					lookUpTable[j][i] = k;
				}
			}
		}
	}		
	return lookUpTable[0][chain_length - 1];   
}


int main()
{	
  vector <int> chain = vector<int>{ 5, 1, 3, 12 , 5,  50, 6 };
  vector<vector<int>> lookUpTable;	
  int operations= matrixChainMultiplyLookUp(chain, lookUpTable);	
  cout << "Number of operations:" << operations << endl;	
  cout << "LookUp Cost Table:" << endl;
  for (int i = 0; i < lookUpTable.size(); i++)
	{
		for (int j = 0; j < lookUpTable.at(i).size(); j++)
			cout << lookUpTable.at(i).at(j) << " ";
		cout << endl;
	}		
	printRecursiveParentheses(lookUpTable);
	cout << endl;
	printIterativeParentheses(lookUpTable);	
}








