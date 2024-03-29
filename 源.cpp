#define TEST
#include<ctime>
#include<string>
#include<iostream>
#include<algorithm>
using namespace std;
string dp(string a, string b)
{
	string res;
	int n1 = a.size(), n2 = b.size();
	int** map = new int*[n1];
	int** ch = new int* [n1];
	for (int i = 0; i < n1; ++i)map[i] = new int[n2], ch[i] = new int[n2];
	for (int i = 0; i < n1; ++i)
		for (int j = 0; j < n2; ++j)
			if (a[i] == b[j])
			{
				if (!i || !j)map[i][j] = 1;
				else map[i][j] = map[i - 1][j - 1] + 1;
				ch[i][j] = 1;
			}
			else
			{
				if (!i && !j)map[i][j] = 0, ch[i][j] = 2;
				if (!i)map[i][j] = map[i][j - 1], ch[i][j] = 3;
				else if (!j)map[i][j] = map[i - 1][j], ch[i][j] = 2;
				else if (map[i - 1][j] >= map[i][j - 1])
				{
					map[i][j] = map[i - 1][j];
					ch[i][j] = 2;
				}
				else
				{
					map[i][j] = map[i][j - 1];
					ch[i][j] = 3;
				}
			}
	int i = n1 - 1, j = n2 - 1;
	while (i >= 0 && j >= 0)
	{
		if (ch[i][j] == 1)
		{
			res = a[i] + res;
			--i, --j;
		}
		else if (ch[i][j] == 2)--i;
		else --j;
	}
	int maxi = 0;
	for (int i = 0; i < n1; ++i)
		for (int j = 0; j < n2; ++j)maxi = max(maxi, map[i][j]);
	cout <<"Length of LCS is:"<< maxi << endl;
	if (n1 <= 10 && n2 <= 10)
	{
		cout << "The direction matrix is:(1 for up and left, 2 for up and 3 for up)\n";
		for (int i = 0; i < n1; ++i) { for (int j = 0; j < n2; ++j)cout << ch[i][j] << ' '; cout << endl; }
	}
	return res;
}
int main()
{
	string a, b;
#ifdef TEST
	cout << "PLS input the lengths of the two strings: \n";
	int n1, n2;
	cin >> n1 >> n2;
	srand(time(0));
	for (int i = 0; i < n1; ++i)a += rand() % 26 + 'a';
	for (int j = 0; j < n2; ++j)b += rand() % 26 + 'a';
	cout << a << endl << b << endl;
#else
	cout << "PLS input the two strings: \n";
	cin >> a >> b;
#endif // TEST

	cout << "LCS is " << dp(a, b);
	return 0;
}