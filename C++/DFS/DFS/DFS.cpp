#include<iostream>
#include<vector>



using namespace std;


void DFS(vector<int>& box, vector<int>& used, int idx, int n)
{
	if (idx == n + 1) 
	{
		for (int i : box)
		{
			cout << i << " ";
		}
		cout << endl;
		return;
	}
	for (int i = 1; i <= n; ++i)
	{
		if (used[i] == 0)
		{
			box[idx] = i;
			used[i] = 1;
			DFS(box, used, idx + 1, n);
			used[i] = 0;
		}
	}
}

int main()
{
	int n = 0;
	cin >> n;
	vector<int> box(n + 1, 0);
	vector<int> used(n + 1, 0);
	DFS(box, used, 1, n);

	return 0;
}