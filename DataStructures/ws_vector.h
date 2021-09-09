#ifndef INCLUDE_WS_VECTOR_HPP
#define INCLUDE_WS_VECTOR_HPP

#pragma once
#include "ws_utilities.h"

#pragma warning(push)
#pragma warning(disable:6385)
#pragma warning(disable:6386)
template<typename ValueT>
class ws_vector
{
public:
	ws_vector()
	{
		init();
	}

	ws_vector(size_t cap)
	{
		if (cap > 0) _cap = cap;
		init();
	}

	ws_vector(const ValueT& value, size_t size)
	{
		while (size--)
		{
			push_back(value);
		}
	}

	ws_vector(ws_vector& v) noexcept
	{
		*this = v;
	}

	void init()
	{
		_value = new DEBUG_CHECK_MEMORY_LEAKS ValueT[_cap];
	}

	/// <summary>
	/// �������������һ������
	/// </summary>
	/// <param name="value">��Ҫ��ӵ�ֵ</param>
	void push_back(ValueT value)
	{
		if (_size == _cap)
		{
			_expand_cap(_cap << 1);
		}
		_value[_size++] = value;
	}

	/// <summary>
	/// ȥ���������һ��Ԫ��
	/// </summary>
	void pop_back()
	{
		--_size;
	}

	/// <summary>
	/// ����������С
	/// </summary>
	/// <param name="size">������С</param>
	void resize(size_t size)
	{
		if (size < 0)
		{
			return;
		}

		if (size < _cap)
		{
			_size = size;
			return;
		}

		if (size >= _cap)
		{
			_expand_cap(size << 1);
			return;
		}
	}

	/// <summary>
	/// ����������ָ��λ�õ�Ԫ��
	/// </summary>
	/// <param name="index"></param>
	void erase(size_t index)
	{
		if (index >= _size) return;
		for (size_t i = index; i < _size; ++i)
		{
			_value[i] = _value[i + 1];
		}
	}

	/// <summary>
	/// �������� other �Ľ���
	/// </summary>
	/// <param name="other"></param>
	void swap(ws_vector& other)
	{
		ws_vector<ValueT> tmp = *this;
		*this = other;
		other = tmp;
	}

	/// <summary>
	/// ��������������Ԫ�ء��˵��ú� size() ������
	/// </summary>
	void clear()
	{
		if (_value)
		{
			delete[] _value;
		}
		_size = 0;
		_cap = 0;
	}

	/// <summary>
	/// Ԥ���伯������
	/// </summary>
	/// <param name="cap">������С</param>
	void reserve(size_t cap)
	{
		if (cap <= _cap || cap > max_size())
		{
			return;
		}
		_expand_cap(cap);
	}

	/// <summary>
	/// �������Ƿ����ָ��ֵ
	/// </summary>
	/// <param name="value">��Ҫ����ֵ</param>
	/// <returns>����������Ϊtrue����֮��Ϊfalse</returns>
	bool contains(ValueT value)
	{
		auto index = _size;
		while (index--)
		{
			if (value == _value[index])
			{
				return true;
			}
		}
		return false;
	}

	/// <summary>
	/// �жϼ����Ƿ�Ϊ��
	/// </summary>
	/// <returns>��Ϊ�գ���Ϊtrue����֮��Ϊfalse</returns>
	bool empty()
	{
		return _size == 0;
	}

	/// <summary>
	/// ��ȡ������Ԫ�ظ���
	/// </summary>
	/// <returns>Ԫ�ظ���</returns>
	size_t size()
	{
		return _size;
	}

	/// <summary>
	/// ��ȡ���ϵ����洢����
	/// </summary>
	/// <returns>���ϵ����洢����</returns>
	size_t max_size()
	{
		return std::numeric_limits<size_t>::max();
	}

	/// <summary>
	/// �����ѷ���ռ�Ĵ�С
	/// </summary>
	/// <returns>��ǰ����洢������</returns>
	size_t capacity()
	{
		return _cap;
	}

	/// <summary>
	/// ����λ��ָ��λ�� index ��Ԫ�ص����ã��б߽���
	/// </summary>
	/// <param name="index"></param>
	/// <returns>index��Ԫ�ص�����</returns>
	ValueT& at(size_t index)
	{
		if (index < 0 || index >= _size) throw(std::out_of_range("Parameter access out of range."));
		return _value[index];
	}

	/// <summary>
	/// ����λ��ָ��λ�� index ��Ԫ�ص����ã��ޱ߽���
	/// </summary>
	/// <param name="index"></param>
	/// <returns>index��Ԫ�ص�����</returns>
	ValueT& operator[](size_t index)
	{
		return _value[index];
	}

	/// <summary>
	/// ��ȡ������Ԫ�ص�����
	/// </summary>
	/// <returns>������Ԫ�ص�����</returns>
	ValueT& front()
	{
		return _value[0];
	}

	/// <summary>
	/// ��ȡ�������һ��Ԫ�ص�����
	/// </summary>
	/// <returns>�������һ��Ԫ�ص�����</returns>
	ValueT& back()
	{
		return _value[_size - 1];
	}

	/// <summary>
	/// ��ȡָ����ΪԪ�ش洢�����ĵײ������ָ��
	/// </summary>
	/// <returns>Ԫ�ش洢�����ĵײ������ָ��</returns>
	ValueT* data()
	{
		return _value;
	}

	/// <summary>
	/// ���ظ�ֵ�����
	/// </summary>
	/// <param name="other">�ṩ��ֵ���ݵ���������</param>
	/// <returns></returns>
	ws_vector& operator=(ws_vector& other)
	{
		if (this == &other) return *this;

		delete[] _value;
		_size = other._size;
		_cap = other._cap;
		_value = new DEBUG_CHECK_MEMORY_LEAKS ValueT[_cap];

		for (size_t i = 0; i < _size; ++i)
		{
			_value[i] = other._value[i];
		}

		return *this;
	}

	~ws_vector()
	{
		clear();
	}

private:
	void _expand_cap(size_t cap)
	{
		ValueT* newValue = new DEBUG_CHECK_MEMORY_LEAKS ValueT[cap];
		for (size_t i = 0; i < _size; ++i)
		{
			newValue[i] = _value[i];
		}
		delete[] _value;
		_cap = cap;
		_value = newValue;
	}

private:
	ValueT* _value;
	size_t _size{ 0 };
	size_t _cap{ 2 };
};

#pragma warning(pop)  
#endif // INCLUDE_WS_VECTOR_HPP