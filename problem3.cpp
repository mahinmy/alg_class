#include<iostream>
using namespace std;
int head[20] ;
int N;
inline int min2(int a, int b)
{
	return a < b ? a : b;
}
void printList(int count)
{
	cout << head[0];
	for (int i = 1; i<count; i++)
		cout << '+' << head[i];
	cout << '\n';

}
void R(int n, int value)
{
	
	int maxId;
	if (value == 0)
		printList(n);
	maxId = min2(value, head[n - 1]);
	for ( ; maxId>0; maxId--)
	{
		head[n] = maxId ;
		R(n + 1, value - head[n]);
	}
}
int main()
{
	cin >> N;
	for (int i = N; i>0; i--)
	{
		head[0] = i;		
		R(1, N - i);
	}
	return 0;
}
