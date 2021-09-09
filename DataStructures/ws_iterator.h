#ifndef INCLUDE_ITERATOR_HPP
#define INCLUDE_ITERATOR_HPP

#define NULL 0

struct _Node_base
{
	typedef _Node_base* _Base_ptr;
	typedef _Node_base const* _Base_const_ptr;

	_Base_ptr _M_parent;
	_Base_ptr _M_left;
	_Base_ptr _M_right;

	_Node_base(_Base_ptr const __PARENT = NULL,
		_Base_ptr const __LEFT = NULL,
		_Base_ptr const __RIGHT = NULL)
		: _M_parent(__PARENT), _M_left(__LEFT), _M_right(__RIGHT) {}

	static _Base_ptr _S_minimum(_Base_ptr __x)
	{
		while (__x->_M_left) __x = __x->_M_left;
		return __x;
	}

	static _Base_ptr _S_maximum(_Base_ptr __x)
	{
		while (__x->_M_right) __x = __x->_M_right;
		return __x;
	}
};

template <typename _Val>
struct _Node : public _Node_base
{
	using _Node_base::_Base_ptr;
	typedef _Node* _Link_type;

	_Val _M_value;

	_Node(_Val const& __VALUE = _Val(),
		_Base_ptr const __PARENT = NULL,
		_Base_ptr const __LEFT = NULL,
		_Base_ptr const __RIGHT = NULL)
		: _Node_base(__PARENT, __LEFT, __RIGHT), _M_value(__VALUE) {}
};

template <typename _Val, typename _Ref, typename _Ptr>
class _Iterator;

template<typename _Val, typename _Ref, typename _Ptr>
inline bool operator==(_Iterator<_Val, _Ref, _Ptr> const&, _Iterator<_Val, _Ref, _Ptr> const&);

template<typename _Val>
inline bool operator==(_Iterator<_Val, const _Val&, const _Val*> const&, _Iterator<_Val, _Val&, _Val*> const&);

template<typename _Val>
inline bool operator==(_Iterator<_Val, _Val&, _Val*> const&, _Iterator<_Val, const _Val&, const _Val*> const&);

template<typename _Val, typename _Ref, typename _Ptr>
inline bool operator!=(_Iterator<_Val, _Ref, _Ptr> const&, _Iterator<_Val, _Ref, _Ptr> const&);

template<typename _Val>
inline bool operator!=(_Iterator<_Val, const _Val&, const _Val*> const&, _Iterator<_Val, _Val&, _Val*> const&);

template<typename _Val>
inline bool operator!=(_Iterator<_Val, _Val&, _Val*> const&, _Iterator<_Val, const _Val&, const _Val*> const&);

class _Base_iterator
{
protected:
	typedef _Node_base::_Base_const_ptr _Base_const_ptr;
	_Base_const_ptr _M_node;

	inline _Base_iterator(_Base_const_ptr const __N = nullptr) : _M_node(__N) {}
	inline _Base_iterator(_Base_iterator const& __THAT) : _M_node(__THAT._M_node) {}

	inline void _M_increment()
	{
		if (_M_node->_M_right)
		{
			_M_node = _M_node->_M_right;
			while (_M_node->_M_left) _M_node = _M_node->_M_left;
		}
		else
		{
			_Base_const_ptr __p = _M_node->_M_parent;
			while (__p && _M_node == __p->_M_right)
			{
				_M_node = __p;
				__p = _M_node->_M_parent;
			}
			if (__p) _M_node = __p;
		}
	}

	inline void _M_decrement()
	{
		if (!_M_node->_M_parent)
		{
			_M_node = _M_node->_M_right;
		}
		else if (_M_node->_M_left)
		{
			_Base_const_ptr x = _M_node->_M_left;
			while (x->_M_right) x = x->_M_right;
			_M_node = x;
		}
		else
		{
			_Base_const_ptr __p = _M_node->_M_parent;
			while (__p && _M_node == __p->_M_left)
			{
				_M_node = __p;
				__p = _M_node->_M_parent;
			}
			if (__p) _M_node = __p;
		}
	}
};

template <typename _Val, typename _Ref, typename _Ptr>
class _Iterator : protected _Base_iterator
{
public:
	typedef _Val value_type;
	typedef _Ref reference;
	typedef _Ptr pointer;
	typedef _Iterator<_Val, _Val&, _Val*> iterator;
	typedef _Iterator<_Val, _Val const&, _Val const*> const_iterator;
	typedef _Iterator<_Val, _Ref, _Ptr> _Self;
	typedef _Node<_Val> const* _Link_const_type;
	typedef std::bidirectional_iterator_tag iterator_category;
	typedef ptrdiff_t difference_type;

	inline _Iterator() : _Base_iterator() {}
	inline _Iterator(_Link_const_type const __N) : _Base_iterator(__N) {}
	inline _Iterator(iterator const& __THAT) : _Base_iterator(__THAT) {}

	_Link_const_type get_raw_node() const
	{
		return _Link_const_type(_M_node);
	}

	reference operator*() const
	{
		return _Link_const_type(_M_node)->_M_value;
	}

	pointer operator->() const
	{
		return &(operator*());
	}

	_Self operator++()
	{
		_M_increment();
		return *this;
	}

	_Self operator++(int)
	{
		_Self ret = *this;
		_M_increment();
		return ret;
	}

	_Self& operator--()
	{
		_M_decrement();
		return *this;
	}

	_Self operator--(int)
	{
		_Self ret = *this;
		_M_decrement();
		return ret;
	}

	friend bool operator== <>(_Iterator<_Val, _Ref, _Ptr> const&, _Iterator<_Val, _Ref, _Ptr> const&);

	friend bool operator== <>(_Iterator<_Val, const _Val&, const _Val*> const&, _Iterator<_Val, _Val&, _Val*> const&);

	friend bool operator== <>(_Iterator<_Val, _Val&, _Val*> const&, _Iterator<_Val, const _Val&, const _Val*> const&);

	friend bool operator!= <>(_Iterator<_Val, _Ref, _Ptr> const&, _Iterator<_Val, _Ref, _Ptr> const&);

	friend bool operator!= <>(_Iterator<_Val, const _Val&, const _Val*> const&, _Iterator<_Val, _Val&, _Val*> const&);

	friend bool operator!= <>(_Iterator<_Val, _Val&, _Val*> const&, _Iterator<_Val, const _Val&, const _Val*> const&);
};

template<typename _Val, typename _Ref, typename _Ptr>
bool operator==(_Iterator<_Val, _Ref, _Ptr> const& __X, _Iterator<_Val, _Ref, _Ptr> const& __Y)
{
	return __X._M_node == __Y._M_node;
}

template<typename _Val>
bool operator==(_Iterator<_Val, const _Val&, const _Val*> const& __X, _Iterator<_Val, _Val&, _Val*> const& __Y)
{
	return __X._M_node == __Y._M_node;
}

template<typename _Val>
bool operator==(_Iterator<_Val, _Val&, _Val*> const& __X, _Iterator<_Val, const _Val&, const _Val*> const& __Y)
{
	return __X._M_node == __Y._M_node;
}

template<typename _Val, typename _Ref, typename _Ptr>
bool operator!=(_Iterator<_Val, _Ref, _Ptr> const& __X, _Iterator<_Val, _Ref, _Ptr> const& __Y)
{
	return __X._M_node != __Y._M_node;
}

template<typename _Val>
bool operator!=(_Iterator<_Val, const _Val&, const _Val*> const& __X, _Iterator<_Val, _Val&, _Val*> const& __Y)
{
	return __X._M_node != __Y._M_node;
}

template<typename _Val>
bool operator!=(_Iterator<_Val, _Val&, _Val*> const& __X, _Iterator<_Val, const _Val&, const _Val*> const& __Y)
{
	return __X._M_node != __Y._M_node;
}


#endif // include guard