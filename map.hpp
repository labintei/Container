/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 18:44:36 by labintei          #+#    #+#             */
/*   Updated: 2022/08/11 16:34:01 by labintei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP


#include "utils.hpp"
#include "tree.hpp"
#include "three_iterator.hpp"

namespace ft
{

	// A METTRE EN DEHORS EN FRIEND


	template<class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<std::pair<const Key, T> > >
	class map
	{

		public:

		// Inserer key_comp dans vector mais ne pas gerer les value_type ?? essayer

		typedef Key										key_type;
		typedef T										mapped_type;
		typedef typename ft::pair<const Key, T>							value_type;
		typedef size_t										size_type;
		typedef typename std::ptrdiff_t								difference_type;
		typedef Compare										key_compare;
		typedef Allocator									allocator_type;
		typedef value_type&									reference;
		typedef const value_type&								const_reference;
		typedef value_type*									pointer;
		typedef const value_type*								const_pointer;
		
		class	value_compare
		{
			public:
			value_compare(){}
			value_compare(value_compare const & src){(void)src;}
			~value_compare(){}
			value_compare &operator=(const value_compare &){return *this;}
			bool operator()(const value_type &a, const value_type &b)const{return (key_compare()(a.first,b.first));}
		};
		typedef typename ft::three<const value_type,const value_compare>			three;// par default fournit alloc

		typedef typename three::iterator							iterator;
		typedef typename three::const_iterator							const_iterator;
		typedef typename three::reverse_iterator						reverse_iterator;
		typedef typename three::const_reverse_iterator						const_reverse_iterator;


		typedef typename three::node								node_type;
		
		typedef typename allocator_type::template rebind<node_type>::other				node_allocator;// ?? 41gt

		private:

			three		_tree;// aura root dedans et le template donne par default key et alloc
			key_compare	_comp;
			allocator_type	_alloc;
			value_compare	_value_comp;

		public:

			explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()): _tree(), _comp(comp), _alloc(alloc), _value_comp(value_compare()){}//ok
			template <class InputIterator>
			map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()):_tree(), _comp(comp), _alloc(alloc), _value_comp(value_compare()){insert(first, last);}//ok
			map(const map& x): _tree(x.tree), _comp(x.comp), _alloc(x._alloc), _value_comp(value_compare()){}//ok
			/*a faire*/~map(){}

			map& operator=(const map& x){_tree = x._tree;_comp = x._comp;_alloc = x._alloc; _value_comp = x._value_comp;return *this;}//ok

			iterator begin(){return _tree.begin();}// DONE
			const_iterator begin()const{return _tree.begin();}//DONE
			iterator end(){return _tree.end();}//DONE
			const_iterator end()const{return _tree.end();}//DONE

			reverse_iterator rbegin(){return _tree.rbegin();}//DONE
			const_reverse_iterator rbegin()const{return _tree.rbegin();}//DONE

			reverse_iterator rend(){return _tree.rend();}// DONE
			const_reverse_iterator rend()const{return _tree.rend();}//DONE

			bool		empty(){return _tree.empty();}// DONE
			size_type	size(){return _tree.size();}// DONE
			size_type	max_size(){return _tree.max_size();}// DONE

			mapped_type&	operator[](const key_type& k)
			{
				value_type search = ft::make_pair(k, mapped_type());
				value_type find = _tree.find(search);
				if(find)
					return find->second;
				else
				{
					_tree.insert(search);
					return (_tree.find(search)->second);
				}
			}//DONE


			// PEUT DONNER LE NILL em parametre d Iter ?? obligatoire
			iterator	upper_bound(const key_type &k)
			{
				return iterator(_tree.upper_bound(ft::make_pair(k, mapped_type())), _tree._NIL);
			}

			const_iterator	upper_bound(const key_type &k)const
			{
				return const_iterator(_tree.upper_bound(ft::make_pair(k,mapped_type())), _tree._NIL);
			}

			iterator	lower_bound(const key_type& k)
			{
				return iterator(_tree.upper_bound(ft::make_pair(k, mapped_type())), _tree._NIL);
			}

			const_iterator	lower_bound(const key_type& k)const
			{
				return const_iterator(_tree.upper_bound(ft::make_pair(k, mapped_type())), _tree._NIL);
			}	

			pair<iterator,bool>	insert(const value_type& val){_tree.insert(val);}
	
			iterator		insert(iterator pos, const value_type& val){(void)pos;_tree.insert(val);}

			template <class InputIterator>
			void	insert(InputIterator first, InputIterator last){_tree.insert(first,last);}


			size_type	erase(const key_type& k){_tree.erase(ft::make_pair(k,mapped_type()));}



			//void		clear(){}

			key_compare	key_comp()const{return _tree.key_comp();}

			iterator	find(const key_type& k){return _tree.find(make_pair(k, mapped_type()));}
			const_iterator	find(const key_type& k)const{return _tree.find(k, mapped_type());}

			size_type	count(const key_type &k)const{return _tree.count(ft::make_pair(k, mapped_type()));}

			pair<const_iterator,const_iterator>	equal_range(const key_type& k)const{return ft::make_pair(lower_bound(k), upper_bound(k));}
			pair<iterator,iterator>			equal_range(const key_type& k){return ft::make_pair(lower_bound(k), upper_bound(k));}

			allocator_type				get_allocator()const{return _tree.get_allocator();}
		
		// probleme je devrais mettre pleins de void	

	};
	// NON-MEMBER function overload

	template<class T,class Key, class Alloc, class Compare>
	bool	operator>(const map<Key, T, Compare, Alloc>&x, const map<Key, T, Compare, Alloc> &y)
	{
		// j ai inverse car trompe de signe c est moche
		return !(lexicographical_compare(x.begin(),x.end(),y.begin(), y.end()));
	}
	template<class T, class Key, class Alloc, class Compare>
	bool	operator==(const map<Key, T, Compare, Alloc>& x,const map<Key, T, Compare, Alloc>& y)
	{
		if(x.size() != y.size())
			return false;
		return equal(x.begin(), x.end(), y.begin());
	}	
	template<class T, class Key, class Alloc, class Compare>
	bool	operator!=(const map<Key, T, Compare, Alloc>&x, const map<Key,T, Compare, Alloc>& y)
	{return !(x == y);}

	template<class T, class Key, class Alloc, class Compare>
	bool	operator>=(const map<Key, T, Compare, Alloc>& x, const map<Key, T, Compare, Alloc>& y)
	{return (x == y || x > y);}

	template<class T, class Key, class Alloc, class Compare>
	bool	operator<(const map<Key, T, Compare, Alloc> &x, const map<Key, T, Compare, Alloc>& y)
	{return !(x > y && x == y);}

	template<class T,class Key, class Alloc, class Compare>
	bool	operator<=(const map<Key, T, Compare, Alloc>& x,const map<Key,T,Compare, Alloc>& y)
	{return (x < y || x == y);}	

}

#endif
