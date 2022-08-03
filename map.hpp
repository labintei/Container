/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 18:44:36 by labintei          #+#    #+#             */
/*   Updated: 2022/08/01 14:07:49 by labintei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP


#include "three_iterator.hpp"

namespace ft
{
	template<class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<std::pair<const Key, T> > >
	class map
	{

		public:

		typedef Key										key_type;
		typedef T										mapped_type;
		typedef typename ft::pair<const Key, T>							value_type;
		typedef typename size_t									size_type;
		typedef typename std::ptrdiff_t								difference_type;
		typedef typename Compare								key_compare;
		typedef Allocator									allocator_type;
		typedef value_type&									reference;
		typedef const value_type&								const_reference;
		typedef typename std::allocator_traits<Allocator>::pointer				pointer;
		typedef typename std::allocator_traits<Allocator>::const_pointer			const_pointer;
		typedef typename ft::three_iterator<value_type, key_compare, allocator_type>		iterator;
		typedef typename ft::three_iterator<const value_type, key_compare, allocator_type>	const_iterator;
		typedef typename ft::reverse_iterator<iterator>						reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator>					const_reverse_iterator;
		typedef typename Node<value_type>							node_type;

		// cplusplus reeference

		class	value_compare{
			friend class map;
			protected:
				Compare		comp;
				value_compare	(Compare c): comp(c){} // constructeur
			public:
				typedef bool		result_type;
				typedef value_type	_arg1;
				typedef value_type	_arg2;
				bool	operator() (const value_type& x, const value_type&y) const
				{ return comp(x.first, y.first);}
		}

		// FAIRE LES PROTOS POUR SOUS CLASSE
	
		// Si l allocator n est pas specifiee dans la librairie ce qui est le cas de ft::pair
		//template <class U> struct Node rebind {typedef allocator<value_type> other;};// ?? 

		private:

			three		_tree;// aura root dedans et le template donne par default key et alloc
			key_compare	_comp;
			allocator_type	_alloc;
			value_compare	_value_comp;

			// value_compare ??? Utiliser pour comaparer deux values 
		public:

			explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()){}
			template <class InputIterator>
			map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()){}
			map(const map& x){}
			~map(){}

			map& operator=(const map& x){}

			iterator begin()
			const_iterator begin()const{}
			iterator end()
			const_iterator end()const{}

			reverse_iterator rbegin(){}
			const_reverse_iterator rbegin()const{}

			reverse_iterator rend(){}
			const_reverse_iterator rend()const{}

			bool		empty(){}
			size_type	size(){}
			size_type	max_size(){}

			mapped_type&	operator[](const key_type& k){}

			pair<iterator,bool>	insert(const value_type& val){}
			
			iterator		insert(iterator pos, const value_type& val){}
			
			template <class InputIterator>
			void	insert(InputIterator first, InputIterator last){}

			void		erase(iterator pos){}
			size_type	erase(const key_type& k){}
			void		erase(iterator first, iterator last){}
			
			void		swap(map& x){}

			void		clear(){}

			key_compare	key_comp()const{return _key;}

			iterator	find(const key_type& k){}
			const_iterator	find(const key_type& k)const{}

			size_type	count(const key_type &k)const{}

			iterator	lower_bound(const key_type& k){}
			const_iterator	lower_bound(const key_type& k)const()

			iterator	upper_bound(const key_type& k){}	
			const_iterator	upper_bound(const key_type& k)const{}

			pair<const_iterator,const_iterator>	equal_range(const key_type& k)const{}
			pair<iterator,iterator>			equal_range(const key_type& k){}

			allocator_type				get_allocator()const{return _alloc;}

		
	

	}
	// NON-MEMBER function overload

	template<class Key, class Compare, class Alloc>
	bool	operator>(const map& x, const map& y)
	{
		// j ai inverse car trompe de signe c est moche
		return !(lexicographical_compare(x.begin(),x.end(),y.begin(), y.end()));
	}
	template<class Key, class Compare, class Alloc>
	bool	operator==(const map& x,const map& y)
	{
		if(x.size() 1= y.size())
			return false;
		return equal(x.begin(), x.end(), y.begin());
	}
	template<class Key, class Compare, class Alloc>
	bool	operator!=(const map&x, const map& y)
	{return !(x == y);}

	template<class Key, class Compare, class Alloc>
	bool	operator>=(const map& x, const map& y)
	{return (x == y || x > y);}

	template<class Key, class Compare, class Alloc>
	bool	operator<(const map&x, const map& y)
	{return !(x > y && x == y);}

	template<class Key, class Compare, class Alloc>
	bool	operator<=(const map& x,const map& y)
	{return (x < y || x == y);}	

}

#endif
