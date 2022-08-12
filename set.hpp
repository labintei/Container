/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 14:08:41 by labintei          #+#    #+#             */
/*   Updated: 2022/08/12 14:14:16 by labintei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	SET_HPP
#define SET_HPP

#include "tree.hpp"
#include "three_iterator.hpp"

namespace	ft
{
	template<class T, class Compare = ft::less<T>, class Alloc = std::allocator<T> >
	class set
	{
		public:
	
		typedef	T										Key;
		typedef T										value_type;
		typedef Compare										key_compare;
		typedef Compare										value_compare;
		typedef Alloc										allocator_type;

		protected:		
		typedef typename ft::three<const value_type, const value_compare>			three;
		typedef typename three::node								node;

		public:
		typedef value_type&									reference;
		typedef const value_type&								const_reference;
		typedef value_type*									pointer;
		typedef const value_type*								const_pointer;
		typedef	typename three::iterator							iterator;
		typedef typename three::const_iterator							const_iterator;
		typedef typename three::reverse_iterator						reverse_iterator;
		typedef	typename three::const_reverse_iterator						const_reverse_iterator;
		typedef std::ptrdiff_t									difference_type;
		typedef size_t										size_type;

		protected:
				three			_tree;
				key_compare		_comp;
				allocator_type		_alloc;
				value_compare		_value_comp;

		public:

		explicit	set(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()): _tree(), _comp(comp), _alloc(alloc), _value_comp(comp){}

		template<class InputIterator>
		set(InputIterator first, InputIterator last , const key_compare& k = key_compare(), const allocator_type& a = allocator_type())
		: _tree(), _comp(k), _alloc(a), _value_comp(k)
		{insert(first, last);}

		set(const set& x){*this = x;}// vu qu il y a operateur

		/*A faire*/~set(){}

		set&	operator=(const set& x)
		{
			if(this == &x)
				return *this;
			_tree = x._tree;
			_comp = x._comp;
			_alloc = x._alloc;
			_value_comp = x._value_comp;
		}

		iterator	begin(){return _tree.begin();}
		const_iterator	begin()const{return _tree.begin();}

		iterator	end(){return _tree.end();}
		const_iterator	end()const{return _tree.end();}

		reverse_iterator	rbegin(){return _tree.rbegin();}
		const_reverse_iterator	rbegin()const{return _tree.rbegin();}

		reverse_iterator	rend(){return _tree.rend();}
		const_reverse_iterator	rend()const{return _tree._rend();}

		bool			empty()const{return _tree.empty();}

		size_type		size()const{return _tree.size();}
		size_type		max_size()const{return _tree.max_size();}

		pair<iterator,bool>	insert(const value_type& val){return _tree.insert(val);}
		iterator		insert(iterator pos,const value_type& val){(void)pos;_tree.insert(val);return (find(val));}
		// Si marche pas
		/*iterator		insert(iterator pos, const value_type& val){(void)pos;return (_tree.insert(val))->first;}*/

		template<class InputIterator>
		void insert(InputIterator first, InputIterator last){_tree.insert(first,last);}


		// LES ERASE NE SONT PAS LES MEME
		size_type	erase(const Key& val){_tree.erase(val);};

		key_compare	key_comp(){return _tree.key_comp();}
		value_compare	value_comp(){return _value_comp;}

		size_type	count(const Key& val)const{return _tree.count(val);}

		iterator	lower_bound(const Key& val){return _tree.lower_bound(val);}
		const_iterator	lower_bound(const Key& val)const{return _tree.lower_bound(val);}
		iterator	upper_bound(const Key& val){return _tree.upper_bound(val);}
		const_iterator	upper_bound(const Key& val)const{return _tree.upper_bound(val);}

		// range of equal element

		pair<iterator,iterator>			equal_range(const Key& val){return _tree.equal_range(val);}
		pair<const_iterator,const_iterator>	equal_range(const Key& val)const{return _tree.equal_range(val);}

		allocator_type	get_allocator(){return _alloc;}
		
		iterator		find(const Key& val){return _tree.find(val);}
		const_iterator		find(const Key& val)const{return _tree.find(val);}

	};

	template<class Key,class Compare, class Alloc>
	bool	operator<(const set<Key, Compare, Alloc>& x,const set<Key, Compare, Alloc>& y)
	{return lexicographical_compare(x.begin(),x.end(),y.begin(),y.end());}
	template<class Key, class Compare,class Alloc>
	bool	operator==(const set<Key, Compare, Alloc>& x,const set<Key, Compare, Alloc>& y)
	{
		// bizarre george fait une consversion en const iterator et utilise pas equal ??
		if(x.size() != y.size())
			return false;
		return equal(x.begin(),x.end(),y.begin());
	}
	template<class Key, class Compare, class Alloc>
	bool	operator!=(const set<Key, Compare, Alloc>& x, const set<Key, Compare, Alloc>& y)
	{return !(x == y);}
	template<class Key, class Compare, class Alloc>
	bool	operator>(const set<Key, Compare, Alloc>& x,const set<Key, Compare, Alloc>& y)
	{return !(x < y || x == y);}
	template<class Key,class Compare,class Alloc>
	bool	operator<=(const set<Key, Compare, Alloc>& x, const set<Key, Compare, Alloc>& y)
	{return (x < y || x == y);}
	template<class Key, class Compare, class Alloc>
	bool	operator>=(const set<Key,Compare, Alloc>& x,const set<Key, Compare, Alloc>& y)
	{return (x > y || x == y);}

	// techniquement ok
}


#endif
