#pragma once
#ifndef __CLIST__
#define __CLIST__

#include <stdlib.h>
template <typename ListData>
class CList
{
public:
	CList() 
	{
		_head._Next = &_tail;
		_tail._Prev = &_head;
	}
	~CList() {}

	struct Node
	{
		ListData _data;
		Node* _Prev;
		Node* _Next;
	};

	class iterator
	{
	private:
		Node* _node;
		friend iterator CList::erase(iterator itor);
	public:

		iterator(Node* node = nullptr)
		{
			_node = node;
		}

		iterator operator ++(int)
		{
			iterator tmp;
			tmp->_node = this->_node;
			_node = _node->_Next;
			return tmp;
		}

		iterator& operator ++()
		{
			_node = _node->_Next;
			return *this;
		}

		iterator operator --(int)
		{
			iterator tmp;
			tmp->_node = this->_node;
			_node = _node->_Prev;
			return tmp;
		}

		iterator& operator --()
		{
			_node = _node->_Prev;
			return *this;
		}

		ListData& operator *()
		{
			return _node->_data;
			
		}
		bool operator ==(const iterator& other)
		{
			return this->_node->_data == other._node->_data;
		}
		bool operator !=(const iterator& other)
		{
			return this->_node->_data != other._node->_data;
		}
	};

	iterator begin()
	{
		return iterator(_head._Next);
	}
	iterator end()
	{
		return iterator(&_tail);
	}
	void push_front(ListData data)
	{
		Node* tmp = (Node*)malloc(sizeof(Node));
		tmp->_data = data;
		tmp->_Next = _head._Next;
		_head._Next->_Prev = tmp;
		_head._Next = tmp;
		tmp->_Prev = &_head;
		_size++;
	}
	void push_back(ListData data)
	{
		Node* tmp = (Node*)malloc(sizeof(Node));
		tmp->_data = data;

		tmp->_Prev = _tail._Prev;
		_tail._Prev->_Next = tmp;
		_tail._Prev = tmp;
		tmp->_Next = &_tail;
		_size++;
	}
	ListData pop_front()
	{
		return _head._Next->_data;
	}
	ListData pop_back()
	{
		return 	_tail._Prev->_data;
	}
	void clear()
	{
		CList<ListData>::iterator iter;
		for (iter = begin(); iter != end(); )
		{
			iter = erase(iter);
		}
	}

	iterator erase(iterator itor)
	{

		Node* tmp = itor._node;
		itor._node->_Prev->_Next = itor._node->_Next;
		itor._node->_Next->_Prev = itor._node->_Prev;

		itor._node = itor._node->_Next;
		free(tmp);
		_size--;
		return itor;
	}
	void remove(ListData Data)
	{
		CList<ListData>::iterator iter;
		for (iter = begin(); iter != end(); ++iter)
		{
			if (*iter == Data)
			{
				erase(iter);
				break;
			}
		}
	}
	int size() { return _size; };
	bool empty() { return _size == 0; };
private:
	int _size = 0;
	Node _head;
	Node _tail;
};


#endif