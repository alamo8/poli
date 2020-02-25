#include <iostream>
#include <vector>
using namespace std;
#define min(A,B) A<B ? A : B
#define CANC 1
#define INS 1
#define REP 1
#define COPY 0

static void printChanges(string& s1, string& s2, vector<vector<int>>& lookUp)
{
	int i = s1.length();
	int j = s2.length();	
	while (i != 0 && j != 0)
	{		
		if (s1[i - 1] == s2[j - 1])// Copy
		{
			cout << "Copy " << s1[i - 1] << endl;
			i--;
			j--;
		}		
		else if (lookUp[i][j] == lookUp[i - 1][j - 1] + REP)// Replace 
		{
			cout << "Replace " << s1[i - 1] << " with " << s2[j - 1]<<endl;
			i--;
			j--;
		}		
		else if (lookUp[i][j] == lookUp[i - 1][j] + CANC)// Delete 
		{
			cout << "Delete " << s1[i - 1]<<endl;
			i--;
		}		
		else if (lookUp[i][j] == lookUp[i][j - 1] + INS)// Add  
		{
			cout << "Add " << s2[j - 1]<<endl;
			j--;
		}
	}
}

int computeEditDistance(string& x, string& y, vector<vector<int>>& lookUp)
{
	int edge_number = x.length();
	int node_number = y.length();
	lookUp = vector<vector<int>>(edge_number + 1, vector<int>(node_number + 1, 0));
	for (int i = 1; i <= edge_number; i++)
		lookUp[i][0] = lookUp[i - 1][0] + CANC;
	for (int j = 1; j <= node_number; j++)
		lookUp[0][j] = lookUp[0][j - 1] + INS;
	for (int i = 1; i <= edge_number; i++)
		for (int j = 1; j <= node_number; j++)
		{
			if (x[i - 1] == y[j - 1])
				lookUp[i][j] = lookUp[i - 1][j - 1] + COPY;
			else
			{
				int tmp = min(lookUp[i - 1][j] + CANC, lookUp[i][j - 1] + INS);
				lookUp[i][j] = min(tmp, lookUp[i - 1][j - 1] + REP);    
			}
		}
	return lookUp[edge_number][node_number];
}


int main()
{
	string s1 = "hello";
	string s2 = "hail";
	vector<vector<int>> table;
	cout << "The edit distance is " << computeEditDistance(s1, s2, table)<<endl;
	cout << "The operations performed are:" << endl;
    printChanges(s1, s2, table);
	return 1;
}