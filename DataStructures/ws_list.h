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
	/// ���Ԫ�ص�������λ
	/// </summary>
	/// <param name="value">Ԫ��ֵ</param>
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
	/// ���Ԫ�ص���������
	/// </summary>
	/// <param name="value">Ԫ��ֵ</param>
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
	/// �Ƴ�������λ��Ԫ��
	/// </summary>
	void pop_front()
	{
		erase(0);
	}

	/// <summary>
	/// �Ƴ���������Ԫ��
	/// </summary>
	void pop_back()
	{
		erase(_count - 1);
	}

	/// <summary>
	/// ��ȡ������λ��Ԫ��
	/// </summary>
	/// <returns>������λ��Ԫ��</returns>
	ValueT& front()
	{
		return _pHead->next->data;
	}

	/// <summary>
	/// ��ȡ��������Ԫ��
	/// </summary>
	/// <returns>��������Ԫ��</returns>
	ValueT& back()
	{
		return _pHead->prev->data;
	}

	/// <summary>
	/// ������нڵ�
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
	/// �������Ƿ����ָ��ֵ
	/// </summary>
	/// <param name="value">��Ҫ����ֵ</param>
	/// <returns>����������Ϊtrue����֮��Ϊfalse</returns>
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
	/// �жϼ����Ƿ�Ϊ��
	/// </summary>
	/// <returns>��Ϊ�գ���Ϊtrue����֮��Ϊfalse</returns>
	bool empty()
	{
		return _count == 0;
	}

	/// <summary>
	/// ָ��λ�ò���ڵ�
	/// </summary>
	/// <param name="pos">λ��</param>
	/// <param name="value">ֵ</param>
	void insert(size_t pos, ValueT& value)
	{
		DNode<ValueT>* pOldNode = _GetNode(pos);
		DNode<ValueT>* pNewNode = new DEBUG_CHECK_MEMORY_LEAKS DNode<ValueT>(value, pOldNode, pOldNode->next);
		pOldNode->next->prev = pNewNode;
		pOldNode->next = pNewNode;
	}

	/// <summary>
	/// ɾ��ָ��λ�õĽڵ�
	/// </summary>
	/// <param name="pos">ָ��λ��</param>
	void erase(size_t pos)
	{
		_DelNode(pos);
	}

	/// <summary>
	/// ��������������
	/// </summary>
	/// <param name="other">��һ��������</param>
	void swap(ws_list& other)
	{
		ws_list<ValueT> tmp = *this;
		*this = other;
		other = tmp;
	}

	/// <summary>
	/// ��ȡ��ǰ�ڵ�����
	/// </summary>
	/// <returns>�ڵ�����</returns>
	size_t size()
	{
		return _count;
	}

	/// <summary>
	/// ���ظ�ֵ�����
	/// </summary>
	/// <param name="other">�ṩ��ֵ���ݵ���������</param>
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
	/// ��ȡ�ڵ���Ϣ
	/// </summary>
	/// <param name="index">�ڵ����</param>
	/// <returns>��Ŷ�Ӧ�ڵ�</returns>
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
	/// ɾ���ڵ�
	/// </summary>
	/// <param name="index">�ڵ����</param>
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