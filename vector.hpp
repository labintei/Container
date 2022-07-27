/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 16:41:19 by labintei          #+#    #+#             */
/*   Updated: 2022/07/20 18:40:40 by labintei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef	VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include "vector_iterator.hpp"
#include "reverse_iterator.hpp"
#include <memory>
#include <string>


namespace ft
{
	
	template<typename T, typename Allocator = std::allocator<T> >
	class vector
	{
		public:

			typedef T						value_type;
			typedef T*						pointer_type;
			typedef T&						reference_type;
			typedef Allocator					allocator_type;
			typedef typename allocator_type::pointer		pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef typename allocator_type::reference		reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef vector_iterator<value_type>			iterator;
			typedef vector_iterator<const value_type>		const_iterator;
			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;
			typedef typename allocator_type::size_type		size_type;
			typedef typename allocator_type::difference_type	difference_type;
		protected:
			allocator_type	_alloc_type;
			pointer		_array;
			size_type	_size;
			size_type	_capacity;
		public:
			vector(const allocator_type& a = allocator_type()): _alloc_type(a), _array(NULL), _size(0), _capacity(0){};
			vector(size_type n, const value_type& _val = value_type(), const allocator_type &a = allocator_type()): _alloc_type(a), _array(NULL), _size(n), _capacity(n)
			{
				_array = _alloc_type.allocate(_size);
				for(size_type i = 0; i < _size ; i++)
					_alloc_type.construct(&_array[i], _val);
			};
			template<class InputIterator>
			vector(InputIterator first, InputIterator last, const allocator_type &a = allocator_type(), 
			typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type* = NULL): _alloc_type(a), _array(NULL), _size(0), _capacity(0){assign(first, last);};
			vector(const vector &x): _alloc_type(x._alloc_type), _array(NULL), _size(x._size), _capacity(x._capacity)
			{
				if(x._array)
				{
					_array = _alloc_type.allocate(_capacity);
					for(size_type i = 0; i < _size; i++)
						_alloc_type.construct(&_array[i], x._array[i]);
				}
			};
			~vector()
			{
				clear();
				if(_array)
					_alloc_type.deallocate(_array, _capacity);
			};

			vector& operator=(const vector &a)
			{
				if(this == &a)
					return *this;
				clear();
				if(_array)
					_alloc_type.deallocate(_array, _capacity);
				_capacity = a._capacity;
				_size = a._size;	
				if(a._array)
					_array = _alloc_type.allocate(a._capacity);
				else
					_array = NULL;
				for(size_type i = 0; i < _size; i++)
					_alloc_type.construct(&_array[i], a._array[i]);
				return *this;	
			};
			bool	empty()const{return (_size == 0);};
			void	resize(size_type n, value_type val = value_type())
			{
				if(n > _capacity)
					reserve(n);
				if(n > _size)
				{
					for(size_type i = _size; i < n; i++)
						_alloc_type.construct(&_array[i], val);
				}
				else
				{
					for(size_type i = n; i < _size; i++)
						_alloc_type.destroy(&_array[i]);
				}
				_size = n;
			};
			void reserve(size_type n)
			{
				if(n > max_size())
					return;
				if(n > _capacity)
				{
					value_type*	_tmparray = _alloc_type.allocate(n);
					for(size_type i = 0; i < _size; i++)
					{
						_alloc_type.construct(&_tmparray[i], _array[i]);
						_alloc_type.destroy(&_array[i]);
					}
					if(_array)
						_alloc_type.deallocate(_array, _capacity);
					_capacity = n;
					_array = _tmparray;
				}
			};	
			size_type 	capacity()const{return	_capacity;};
			size_type 	size()const{	return	_size;};
			size_type	max_size()const{return _alloc_type.max_size();}; // pour avoir la _size d une len
			template<class InputIterator>
			void	assign(InputIterator first, InputIterator last, typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type* = NULL)
			{
				size_type	i(0);
				InputIterator	a(first);

				while(a++ != last)
					i++;
				if(i > _capacity)
					reserve(i);
				clear();
				for(size_type u = 0; u < i; u++)
					_alloc_type.construct(&_array[u], (*first++));
				_size = i;
			};
			void	assign(size_type n, const value_type &u)
			{
				if(n > _capacity)
					reserve(n);
				clear();
				for(size_type i = 0; i < n; i++)
					_alloc_type.construct(&_array[i], u);
				_size = n;
			};
			iterator		begin(){return iterator(_array);};
			const_iterator		begin()const{return const_iterator(_array);};
			iterator		end(){return iterator(_array + _size);};
			const_iterator		end()const{return const_iterator(_array + _size);};
			reverse_iterator	rbegin(){return reverse_iterator(_array + _size);};
			const_reverse_iterator	rbegin()const{return const_reverse_iterator(_array + _size);};
			reverse_iterator	rend(){return reverse_iterator(_array);};
			const_reverse_iterator	rend()const{return const_reverse_iterator(_array);};
			reference	operator[](size_type n){return _array[n];};
			const_reference operator[](size_type n)const{return _array[n];};
			reference	front(){return _array[0];};
			const_reference	front()const{return _array[0];};
			reference	back(){return _array[_size - 1];};
			const_reference	back()const{return _array[_size - 1];}; // probleme si _size == 0
			const_reference at(size_type pos) const// a une protection contrairement a []
			{
				if(pos >= _size)
					throw(std::out_of_range("out of range"));
				return _array[pos];
			};
			reference	at(size_type pos)
			{
				if(pos >= _size)
					throw(std::out_of_range("out of range"));
				return _array[pos];
			};
			void		push_back(const value_type& x)
			{
				if(_capacity == _size)
				{  
					if(_capacity == 0)
						reserve(1);
					else
						reserve(_capacity * 2);
				}
				_alloc_type.construct(&_array[_size], x);
				_size++;	
			};
			void		pop_back()
			{
				if(_size > 0)
				{
					_alloc_type.destroy(&_array[_size - 1]);
					_size--;
				}
			};
			iterator	insert(iterator pos, const T& value)
			{
				size_type	a = &*pos - &*begin();
				insert(pos, 1, value);
				return(begin() + a);
			};
			void		insert(iterator pos, size_type n, const T& value)
			{
				size_type	s = &*pos - &*begin();
				size_type	e = &*end() - &*pos;

				if(_size + n > _capacity)
					reserve(_size + n);
				_size += n;
				for(size_type i = 0; i < e; i++)
					_alloc_type.construct(&_array[_size -1 -i], _array[_size -n -1 - i]);
				for(size_type i = 0; i < n; i++)
					_array[s + i] = value;
			};
			template<class InputIterator>
			void insert(iterator pos, InputIterator first, InputIterator last, typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type* = NULL)
			{
				size_type	s = &*pos - &*begin(); // va calculer l index de pos
				size_type	e = &*end() - &*pos; // va calculer la difference entre index de fin et pos
				InputIterator	current = first;
				size_type	def_size(0);

				while(current++ != last)
				{
					def_size++;
				}
				if(_capacity < def_size + _size)
					reserve(def_size + _size);
				InputIterator	f = first;
				
				for(size_type i = 0; i < e ; i++)
				{
					_alloc_type.construct(&_array[_size -1 + def_size - i], _array[_size -1 - i]);
				}
				while(first != last)
					*((begin() + s++)) = *(first++);
				_size += def_size;
			};
			iterator	erase(iterator	pos){return erase(pos, pos + 1);};
			iterator	erase(iterator first, iterator last) // est un test
			{
				iterator	current(first);
				
				size_type i = &*last - &*first;
				while(last != end())
				{
					*first = *last;
					first++;
					last++;
				}
				while(i > 0)
				{
					pop_back();
					i--;
				}
				return current;	
			};
			void	swap(vector &x)
			{
				size_type	_c(_capacity);
				size_type	_s(_size);
				pointer		_a(_array);
		
				_capacity = x._capacity;
				_size = x._size;
				_array = x._array;
				x._capacity = _c;
				x._size = _s;
				x._array = _a;
			};
			void	clear(){
				while(_size > 0)
					pop_back();
			};
			allocator_type	get_allocator()const {return _alloc_type;};


	};

	template<typename T, class Alloc>
	bool operator==(const vector<T, Alloc> &x, const vector<T, Alloc> &y)
	{
		if(x.size() != y.size())
			return false;
		return(equal(x.begin(), x.end(), y.begin())); // ne prends que troiis arguments comme meme taille ou segfault
	};
	template<typename T, class Alloc>
	bool operator!=(const vector<T,Alloc> &x, const vector<T,Alloc> &y){return (!(x == y));};
	template<typename T, class Alloc>
	bool operator<(const vector<T, Alloc> &x, const vector<T, Alloc> &y)
	{	return(lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()));};
	template<typename T, class Alloc>
	bool operator>(const vector<T, Alloc> &x, const vector<T,Alloc> &y){return !(x < y || x == y);};
	template<typename T, class Alloc>
	bool operator<=(const vector<T, Alloc> &x, const vector<T, Alloc> &y){return (x < y || x == y);};
	template<typename T, class Alloc>
	bool operator>=(const vector<T, Alloc> &x, const vector<T,Alloc> &y){return (x > y || x == y);};
	template<typename T, class Alloc>
	void swap(const vector<T, Alloc> &x, const vector<T, Alloc> &y)
	{
		x.swap(y);
	};

}

#endif
