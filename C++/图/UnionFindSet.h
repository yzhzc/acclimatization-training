#pragma once
#include<iostream>
#include<vector>

using namespace std;

class UnionFindSet
{
public:
	UnionFindSet(size_t n)
		:_ufs(n, -1)
	{}

	//找根的下标
	int FindRoot(int x)
	{
		int root = x;
		while (_ufs[root] >= 0)
		{
			root = _ufs[root];
		}

		// 路径压缩
		while (_ufs[x] >= 0)
		{
			int parent = _ufs[x];
			_ufs[x] = root;

			x = parent;
		}

		return root;
	}

	//合并
	bool Union(int x1, int x2)
	{
		int root1 = FindRoot(x1);
		int root2 = FindRoot(x2);

		if (root1 == root2)
			return false;

		//数据量小的往数据量大的合并
		if (_ufs[root1] > _ufs[root2])
			swap(root1, root2);

		_ufs[root1] += _ufs[root2];
		_ufs[root2] = root1;

		return true;
	}

	bool InSet(int x1, int x2)
	{
		return FindRoot(x1) == FindRoot(x2);
	}

	//团体的数量
	size_t SetSize()
	{
		size_t size = 0;
		for (size_t i = 0; i < _ufs.size(); ++i)
		{
			if (_ufs[i] < 0)
				++size;
		}

		return size;
	}

private:
	vector<int> _ufs;
};
