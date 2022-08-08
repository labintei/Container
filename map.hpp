/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 18:44:36 by labintei          #+#    #+#             */
/*   Updated: 2022/08/08 15:31:52 by labintei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

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
			value_compare(){}
			value_compare(value_compare const & src){(void)src;}
			~value_compare(){}
			value_compare &operator=(const value_compare &){return *this;}
			bool operator()(const value_type &a, const value_type &b)const{return (key_comapre()(a.first,b.first);)}
		};
		// quand je creer le tree je vait modifier ca
		//typedef typename ft::three<value_type, value_compare>					three;
		// ok a deux compare
		typedef typename ft::three<const value_type,const value_compare>			three;// par default fournit alloc
		typedef typename three::iterator							iterator;
		typedef typename three::const_iterator							const_iterator;
		typedef typename three::reverse_iterator						reverse_iterator;
		typedef typename three::const_reverse_iterator						const_reverse_iterator;
		typedef typename three::node								node_type;
		
		typedef typename allocator_type::template rebind<Node>::other				node_allocator;// ?? 41gt

		private:

			three		_tree;// aura root dedans et le template donne par default key et alloc
			key_compare	_comp;
			allocator_type	_alloc;
			value_compare	_value_comp;

		public:

			explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()){}
			template <class InputIterator>
			map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()){}
			map(const map& x){}
			~map(){}

			map& operator=(const map& x){}

			iterator begin(){return _tree.begin();}// DONE
			const_iterator begin()const{return _tree.begin();}//DONE
			iterator end(){return _three.end();}//DONE
			const_iterator end()const{return _tree.end();}//DONE

			reverse_iterator rbegin(){return _tree.rbegin();}//DONE
			const_reverse_iterator rbegin()const{return _tree.rbegin();}//DONE

			reverse_iterator rend(){return tree.rend();}// DONE
			const_reverse_iterator rend()const{return tree.rend();}//DONE

			bool		empty(){return _tree.empty();}// DONE
			size_type	size(){return _tree.size();}// DONE
			size_type	max_size(){return _tree.max_size();}// DONE

			mapped_type&	operator[](const key_type& k)
			{
				value_type search = ft::make_pair(k, mapped_type());
				value_type find = tree.find(search);
				if(find)
					return find->second;
				else
				{
					_tree.insert(search);
					return (tree.find(search)->second);
				}
			}//DONE


			iterator	upper_bound(const key_type &k)
			{// envoit un iterateur pointant sur le premier element dans le container ou la clee est considere comme allant apres k
				for(iterator tmp = begin(); tmp != end(); tmp++)
					if((key_comp()(k, tmp->first))// k est devenu < tmp->first ??
						return tmp;
				return end();
			}

			pair<iterator,bool>	insert(const value_type& val){}
			{

			}	
			iterator		insert(iterator pos, const value_type& val){}
			{

			}
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

		
		// probleme je devrais mettre pleins de void	

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
