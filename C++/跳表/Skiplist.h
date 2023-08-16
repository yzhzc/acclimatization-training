#pragma once
#include <iostream>
#include <vector>


using namespace std;


struct SkiplistNode
{
    int _val;
    vector<SkiplistNode*> _nextV;

    SkiplistNode(int val, int level)
        :_val(val)
        , _nextV(level)
    {}
};

class Skiplist {
    typedef SkiplistNode Node;
public:
    Skiplist()
    {
        //头节点初始层数为1
        _head = new SkiplistNode(-1, 1);
    }

    bool search(int target)
    {
        Node* cur = _head;
        int level = _head->_nextV.size() - 1;
        while (level >= 0)
        {
            if (cur->_nextV[level] && target > cur->_nextV[level]->_val) //比当前层大,向右跳跃
                cur = cur->_nextV[level];
            else if (cur->_nextV[level] == nullptr || target < cur->_nextV[level]->_val)    //右边为空或者比当前层小,向下走
                --level;
            else
                return true;
        }

        return false;
    }

    void add(int num)
    {
        vector<Node*> prevV = FindPrevNode(num);    //获取前节点列表
        int n = Randomlevel();  //随机层数
        Node* newnode = new Node(num, n);

        //更新最大层数
        if (n > _head->_nextV.size())
        {
            prevV.resize(n, _head);
            _head->_nextV.resize(n);
        }

        //链接前后节点
        for (size_t i = 0; i < n; ++i)
        {
            newnode->_nextV[i] = prevV[i]->_nextV[i];
            prevV[i]->_nextV[i] = newnode;
        }
    }

    bool erase(int num)
    {
        vector<Node*> prevV = FindPrevNode(num);    //获取前节点列表
        if (prevV[0]->_nextV[0] == nullptr || prevV[0]->_nextV[0]->_val != num)
        {
            return false;
        }
        else
        {
            Node* del = prevV[0]->_nextV[0];    //定位到当前被删除的节点
            for (size_t i = 0; i < del->_nextV.size(); ++i)
            {
                prevV[i]->_nextV[i] = del->_nextV[i];
            }
            delete del;

            //重置头结点高度
            int i = _head->_nextV.size() - 1;
            while (i >= 0)
            {
                if (_head->_nextV[i] == nullptr)
                    --i;
                else
                    break;
            }
            _head->_nextV.resize(i + 1);

            return true;
        }

        return false;
    }

    vector<Node*> FindPrevNode(int num)
    {
        Node* cur = _head;
        int level = _head->_nextV.size() - 1;
        vector<Node*> prevV(level + 1, _head);  //存放在插入节点前面每一层的节点

        while (level >= 0)
        {
            if (cur->_nextV[level] && num > cur->_nextV[level]->_val) //比当前层大,向右跳跃
            {
                cur = cur->_nextV[level];
            }
            else if (cur->_nextV[level] == nullptr || num <= cur->_nextV[level]->_val)
            {
                //右边为空或<=当前层,记录当前节点并向下走
                prevV[level] = cur;
                --level;
            }
        }

        return prevV;
    }

    //获取一个随机层数
    int Randomlevel()
    {
        size_t level = 1;
        while (rand() < RAND_MAX * _p && level < _maxLevel)
        {
            ++level;
        }

        return level;
    }

private:
    Node* _head;
    size_t _maxLevel = 32;
    double _p = 0.25;
};