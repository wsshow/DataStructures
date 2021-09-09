#ifndef INCLUDE_WS_LIST_HPP
#define INCLUDE_WS_LIST_HPP

#pragma once
#include "ws_utilities.h"

template<typename ValueT>
struct DNode
{
	ValueT data;
	DNode<ValueT>* prev;
	DNode<ValueT>* next;

	DNode(){}

	DNode(ValueT data, DNode<ValueT>* prev, DNode<ValueT>* next)
	{
		this->data = data;
		this->prev = prev;
		this->next = next;
	}
};

template<typename ValueT>
class ws_list
{
public:
	ws_list()
	{
		_pHead = new DEBUG_CHECK_MEMORY_LEAKS DNode<ValueT>();
		_count = 0;
	}

	~ws_list()
	{
		clear();
	}

	/// <summary>
	/// 添加元素到链表首位
	/// </summary>
	/// <param name="value">元素值</param>
	void push_front(ValueT value)
	{
		DNode<ValueT>* pNode = new DEBUG_CHECK_MEMORY_LEAKS DNode<ValueT>(value, _pHead, _pHead->next);
		if (_pHead->next)
		{
			_pHead->next->prev = pNode;
		}
		else
		{
			_pHead->prev = pNode;
			_pHead->next = pNode;
		}
		++_count;
	}

	/// <summary>
	/// 添加元素到链表的最后
	/// </summary>
	/// <param name="value">元素值</param>
	void push_back(ValueT value)
	{
		if (_count == 0)
		{
			push_front(value);
			return;
		}
		DNode<ValueT>* pNode = new DEBUG_CHECK_MEMORY_LEAKS DNode<ValueT>(value, _pHead->prev, _pHead);
		_pHead->prev->next = pNode;
		_pHead->prev = pNode;
		++_count;
	}

	/// <summary>
	/// 移除链表首位的元素
	/// </summary>
	void pop_front()
	{
		erase(0);
	}

	/// <summary>
	/// 移除链表最后的元素
	/// </summary>
	void pop_back()
	{
		erase(_count - 1);
	}

	/// <summary>
	/// 获取链表首位的元素
	/// </summary>
	/// <returns>链表首位的元素</returns>
	ValueT& front()
	{
		return _pHead->next->data;
	}

	/// <summary>
	/// 获取链表最后的元素
	/// </summary>
	/// <returns>链表最后的元素</returns>
	ValueT& back()
	{
		return _pHead->prev->data;
	}

	/// <summary>
	/// 清除所有节点
	/// </summary>
	void clear()
	{
		DNode<ValueT>* pNodeTmp;
		DNode<ValueT>* pNode = _pHead->next;
		while (pNode != _pHead)
		{
			pNodeTmp = pNode;
			pNode = pNode->next;
			delete pNodeTmp;
		}
		delete _pHead;
		_pHead = NULL;
		_count = 0;
	}

	/// <summary>
	/// 链表中是否包含指定值
	/// </summary>
	/// <param name="value">需要检测的值</param>
	/// <returns>若包含，则为true；反之，为false</returns>
	bool contain(ValueT& value)
	{
		DNode<ValueT>* pNode = _pHead->next;
		while (pNode != _pHead)
		{
			if (pNode->data == value)
			{
				return true;
			}
			pNode = pNode->next;
		}
		return false;
	}

	/// <summary>
	/// 判断集合是否为空
	/// </summary>
	/// <returns>若为空，则为true；反之，为false</returns>
	bool empty()
	{
		return _count == 0;
	}

	/// <summary>
	/// 指定位置插入节点
	/// </summary>
	/// <param name="pos">位置</param>
	/// <param name="value">值</param>
	void insert(size_t pos, ValueT& value)
	{
		DNode<ValueT>* pOldNode = _GetNode(pos);
		DNode<ValueT>* pNewNode = new DEBUG_CHECK_MEMORY_LEAKS DNode<ValueT>(value, pOldNode, pOldNode->next);
		pOldNode->next->prev = pNewNode;
		pOldNode->next = pNewNode;
	}

	/// <summary>
	/// 删除指定位置的节点
	/// </summary>
	/// <param name="pos">指定位置</param>
	void erase(size_t pos)
	{
		_DelNode(pos);
	}

	/// <summary>
	/// 交换两容器对象
	/// </summary>
	/// <param name="other">另一容器对象</param>
	void swap(ws_list& other)
	{
		ws_list<ValueT> tmp = *this;
		*this = other;
		other = tmp;
	}

	/// <summary>
	/// 获取当前节点数量
	/// </summary>
	/// <returns>节点数量</returns>
	size_t size()
	{
		return _count;
	}

	/// <summary>
	/// 重载赋值运算符
	/// </summary>
	/// <param name="other">提供赋值数据的容器对象</param>
	/// <returns></returns>
	ws_list& operator=(ws_list& other)
	{
		if (this == &other) return *this;
		clear();
		_pHead = new DEBUG_CHECK_MEMORY_LEAKS DNode<ValueT>();
		_pHead = other._pHead;
		_count = other._count;
		return *this;
	}

private:
	/// <summary>
	/// 获取节点信息
	/// </summary>
	/// <param name="index">节点序号</param>
	/// <returns>序号对应节点</returns>
	DNode<ValueT>* _GetNode(size_t index)
	{
		assert(index >= 0 && index < _count);

		size_t pos;
		if (index <= (_count >> 1))
		{
			DNode<ValueT>* pNode = _pHead->next;
			while (pos++ < index)
			{
				pNode = pNode->next;
			}
			return pNode;
		}

		size_t rIndex = _count - index - 1;
		DNode<ValueT>* pNode = _pHead->prev;
		while (pos++ < rIndex)
		{
			pNode = pNode->prev;
		}
		return pNode;
	}

	/// <summary>
	/// 删除节点
	/// </summary>
	/// <param name="index">节点序号</param>
	void _DelNode(size_t index)
	{
		DNode<ValueT>* pNode = _GetNode(index);
		pNode->next->prev = pNode->prev;
		pNode->prev->next = pNode->next;
		delete pNode;
		--_count;
	}

private:
	DNode<ValueT>* _pHead;
	size_t _count;
};

#endif