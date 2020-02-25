#include <iostream>
#include <ctime>
#include <math.h>
#include <string.h>
#include <vector>

using namespace std;

#define max(A,B) A>B ? (A) : (B)


int computeLCS(string& string1, string& string2, string& lcs)
{
	int n = string1.length();
	int m = string2.length();
	vector<vector<int>> lookUp = vector<vector<int>>(n+1, vector<int>(m+1,0));
	for (int i = 1; i <= n; i++) 
	{
		for (int j = 1; j <= m; j++) 
		{
			if (string1[i - 1] == string2[j - 1])
				lookUp[i][j] = lookUp[i - 1][j - 1] + 1;
			else
				lookUp[i][j] = max(lookUp[i - 1][j], lookUp[i][j - 1]);
		}
	}	
	lcs.resize(lookUp[n][m]);	
	int i = n, j = m;
	while (i > 0 && j > 0)
	{
		if (string1[i - 1] == string2[j - 1])
		{
			lcs[lookUp[i][j] - 1] = string1[i - 1];
			i--;
			j--;			
		}
		else if (lookUp[i - 1][j] > lookUp[i][j - 1])
			i--;
		else
			j--;
	}	
	return lookUp[n][m];
}



int main()
{
	string x = "BDCABA";
	string y = "ABCBDAB";
	string lcs = "";
	cout << "Lenght of LCS : " << computeLCS(x,y, lcs) << endl;	
	cout << "LCS: " << lcs << " of size "<<lcs.length()<< endl;
	return 1;
}