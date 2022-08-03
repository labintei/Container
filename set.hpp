/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 14:08:41 by labintei          #+#    #+#             */
/*   Updated: 2022/08/01 15:22:59 by labintei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	SET_HPP
#define SET_HPP

#include "thrr_iterator.hpp"

namespace	ft
{
	template<class T, class Compare = less<T>, class Alloc = allocator<T>>
	class set
	{
		public:
	
		typedef	T										key_type;
		typedef T										value_type:// pourquoi same
		typedef Compare										key_compare;
		typedef Compare										value_compare;
		typedef Alloc										allocator_type;
		typedef typename allocator_type::reference						reference;
		typedef typename allocator_type::const_reference					const_reference;
		typedef typename allocator_type::pointer						pointer;
		typedef typename allocator_type::const_pointer						const_pointer;
		typedef	typename ft::three_iterator<value_type,key_compare, allocator_type>		iterator;
		typedef typename ft::three_iterator<const value_type,key_compare,allocator_type>	const_iterator;
		typedef typename ft::reverse_iterator<iterator>						reverse_iterator;
		typedef	typename ft::reverse_iterator<const_iterator>					const_reverse_iterator;
		typedef typename std::ptrdiff_t								difference_type;
		typedef typename size_t									size_type;

		protected:

		public:

		explicit	set(const key_compare& comp = key_compare(), const allocator_type& x = allocator_type()){}
		template<class InputIterator>.
		set(InputIterator first, InputIterator last , const key_compare& k = key_compare(), const allocator_type& a = allocator_type()){}
		set(const set& x){}

		~set(){}

		set&	operator=(const set& x){}

		iterator	begin(){}
		const_iterator	begin()const{}

		iterator	end(){}
		const_iterator	end()const{}

		reverse_iterator	rbegin(){}
		const_reverse_iterator	rbegin()const{}

		reverse_iterator	rend(){}
		const_reverse_iterator	rend()const{}

		bool			empty(){}
		size_type		size(){}
		size_type		max_size(){}

		pair<iterator,bool>	insert(const value_type& val){}
		iterator		insert(iterator pos,const value_type& val){}
		template<class InputIterator>
		void insert(InputIterator first, InputIterator last)
		{}

		void		erase(iterator position){}
		size_type	erase(const value_type& val){}
		void		erase(iterator first, iterator last);

		void		swap(set& x){}
		void		clear(){}

		// techniquement la meme chose mais bon
		key_compare	key_comp(){return _key;}
		// correspondra a un less ...
		value_compare	value_comp(){return _value_comp;}

		iterator	find(const value_type& val)const{}
		size_type	count(const value_type& val)const{}
		iterator	lower_bound(const value_type& val)const{}
		iterator	upper_bound(const value_type& val)const{}
		// range of equal element

		iterator	equal_range(){}

		allocator_type	get_allocator(){return _alloc;}

		protected:

		value_compare		_value_comp;
		key_compare		_key;
		allocator_type		_alloc;
		three			_tree;

	}

	template<class Key,class Compare, class Alloc>
	bool	operator<(const set& x,const set& y)
	{return lexicographical_compare(x.begin(),x.end(),y.begin(),y.end());}
	template<class Key, class Compare,class Alloc>
	bool	operator==(const set& x,const set& y)
	{
		// bizarre george fait une consversion en const iterator et utilise pas equal ??
		if(x.size() != y.size())
			return false;
		return equal(x.begin(),x.end(),y.begin());
	}
	template<class Key, class Compare, class Alloc>
	bool	operator!=(const set& x, const set& y)
	{return !(x == y);}
	template<class Key, class Compare, class Alloc>
	bool	operator>(const set& x,const set& y)
	{return !(x < y || x == y);}
	template<class Key,class Compare,class Alloc>
	bool	operator<=(const set& x, const set& y)
	{return (x < y || x == y);}
	bool	operator>=(const set& x,const set& y)
	{return (x > y || x == y);}

	// techniquement ok
}


#endif
