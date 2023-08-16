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
        //ͷ�ڵ��ʼ����Ϊ1
        _head = new SkiplistNode(-1, 1);
    }

    bool search(int target)
    {
        Node* cur = _head;
        int level = _head->_nextV.size() - 1;
        while (level >= 0)
        {
            if (cur->_nextV[level] && target > cur->_nextV[level]->_val) //�ȵ�ǰ���,������Ծ
                cur = cur->_nextV[level];
            else if (cur->_nextV[level] == nullptr || target < cur->_nextV[level]->_val)    //�ұ�Ϊ�ջ��߱ȵ�ǰ��С,������
                --level;
            else
                return true;
        }

        return false;
    }

    void add(int num)
    {
        vector<Node*> prevV = FindPrevNode(num);    //��ȡǰ�ڵ��б�
        int n = Randomlevel();  //�������
        Node* newnode = new Node(num, n);

        //����������
        if (n > _head->_nextV.size())
        {
            prevV.resize(n, _head);
            _head->_nextV.resize(n);
        }

        //����ǰ��ڵ�
        for (size_t i = 0; i < n; ++i)
        {
            newnode->_nextV[i] = prevV[i]->_nextV[i];
            prevV[i]->_nextV[i] = newnode;
        }
    }

    bool erase(int num)
    {
        vector<Node*> prevV = FindPrevNode(num);    //��ȡǰ�ڵ��б�
        if (prevV[0]->_nextV[0] == nullptr || prevV[0]->_nextV[0]->_val != num)
        {
            return false;
        }
        else
        {
            Node* del = prevV[0]->_nextV[0];    //��λ����ǰ��ɾ���Ľڵ�
            for (size_t i = 0; i < del->_nextV.size(); ++i)
            {
                prevV[i]->_nextV[i] = del->_nextV[i];
            }
            delete del;

            //����ͷ���߶�
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
        vector<Node*> prevV(level + 1, _head);  //����ڲ���ڵ�ǰ��ÿһ��Ľڵ�

        while (level >= 0)
        {
            if (cur->_nextV[level] && num > cur->_nextV[level]->_val) //�ȵ�ǰ���,������Ծ
            {
                cur = cur->_nextV[level];
            }
            else if (cur->_nextV[level] == nullptr || num <= cur->_nextV[level]->_val)
            {
                //�ұ�Ϊ�ջ�<=��ǰ��,��¼��ǰ�ڵ㲢������
                prevV[level] = cur;
                --level;
            }
        }

        return prevV;
    }

    //��ȡһ���������
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