/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   three_iterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 16:55:25 by labintei          #+#    #+#             */
/*   Updated: 2022/08/05 20:50:49 by labintei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREE_ITERATOR_HPP
#define THREE_ITERATOR_HPP


// toujours des erreurs dans ce dernier
#include "reverse_iterator.hpp"
#include <iostream>
#include <memory>
#include "utils.hpp"
#include "pair.hpp"

#include <cstddef>



// trouver un autre moyen de l implementer
// BLACK 0
// RED 1

namespace ft
{
	template<class T>
	struct Node
	{
		public:

		typedef T	value_type;
		typedef T&	reference;
		typedef T*	pointeur;
		
		value_type	val;
		Node*		parent;
		Node*		left;
		Node*		right;

		Node(value_type &s): val(s){};
	};

	template<class N>
	class three_iterator
	{
		public:

		typedef N					node_type;
		typedef node_type*				node_p;	
		typedef typename node_type::value_type		value_type;
		typedef value_type*				pointer;
		typedef value_type&				reference;
		typedef typename std::ptrdiff_t			difference_type;
		typedef std::bidirectional_iterator_tag		iterator_category;

		protected:

		node_p		_current;

		public:
	
		// modifier	
		three_iterator():_current(value_type()){};
		three_iterator(const three_iterator &s): _current(s._current){};
		three_iterator(const node_p &c): _current(c){};
		~three_iterator(){};


		three_iterator operator=(const three_iterator &s)
		{
			_current = s._current;
			return *this;
		};

		friend bool operator==(const three_iterator &s, const three_iterator &r){return (s._current == r._current);}
		friend bool operator!=(const three_iterator &s, const three_iterator &r){return (s._current != r._current);}


		node_p	_max(node_p n)
		{
			while(n->right)
				n = n->_right;
			return n;
		}
		node_p	_min(node_p n)
		{
			while(n->left)
				n = n->left;
			return n;
		}

		//reference		operator*(){return _current->val;}
		reference		operator*()const{return _current->val;}	
		pointer			operator->()const{return &(operator*());}
		//pointer			operator->(){return &(operator*());}

		three_iterator operator++(){increase();return *this;};
		three_iterator &operator++(int){three_iterator tmp = *this; ++_current; return tmp;};
		three_iterator operator--(){decrease(); return *this;};
		three_iterator &operator--(int){three_iterator tmp = *this; --_current; return tmp;};



		/*
		// compliquer				
		*/
		void increase()
		{
			if(_current->right)
				_current = min(_current->right);
			else
			{
				node_p		tmp = _current;
				
				_current = _current->parent;
				while(_current->left != tmp)
				{
					tmp = _current;
					_current = _current->parent;
				}
			}
		}
		void decrease()
		{
			if(_current->left)
				_current = max(_current->left);
			else
			{
				node_p	tmp = _current;
				_current = _current->parent;
				while(_current->right != tmp)
				{
					tmp = _current;
					_current = _current->parent;
				}
			}

		};

	};

	template <class T, class Compare, class Alloc = std::allocator<Node<T> > >
	class three
	{
		public:

		typedef Compare						comp;
		typedef T						value_type;
		typedef T*						pointer;
		typedef T&						reference;
		typedef Alloc						allocator_type;
		typedef typename ft::Node<value_type>			node;
		typedef node*						node_pointer;
		typedef	size_t						size_type;

		typedef	ft::three_iterator<value_type>			iterator;
		typedef const ft::three_iterator<value_type>		const_iterator;
		typedef typename ft::reverse_iterator<iterator>		reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;
		typedef std::ptrdiff_t					difference_type;

		protected:

		node_pointer	_root;
		comp		_comp;
		allocator_type	_alloc;
		size_type	_size;

		public:

//		FONCTION PRESENTE DANS MAP ET SET
		bool		empty(){return _size == 0;}
		size_type	size(){return _size;}
		size_type	max_size()const{return _alloc.max_size();}
		
		//reference	operator[]()


		iterator		begin(){return min();}
		const_iterator		begin()const{return min();}

		iterator		end(){return max();}
		const_iterator		end()const{return max();}

		reverse_iterator	rbegin(){return reverse_iterator(end())}
		const_reverse_iterator	rbegin()const{return const_reverse_iterator(end());}
		
		reverse_iterator	rend(){return reverse_iterator(begin());}
		const_reverse_iterator	rend(){return const_reverse_iterator(begin());}

		// faire clear ici
		void			clear(){}

		iterator	min()
		{
			iterator	i(_root);
			while(i->_current->left)
				i = iterator(i->_current->left);
			return i;
		}
		iterator	max()
		{
			iterator	i(_root);
			while(i->_current->right)
				i = iterator(i->_current->right);
			return i;
		}

		value_type	find_val(const value_type &val)
		{
			return (find_iterator(val)->_current->val;);// JUSTE POUR CHANGER LE TYPAGE
		}

		iterator	find_iterator(const value_type &val)
		{
			iterator i(_root);
			
			while(i)
			{
				if(val < i->val || val > i->val)
				{
					if(val < i->val && i->left)
						i = i->left;
					else if(val > i->val && i->right)
						i = i->right;
					else
						return iterator();
				}
				else if(i->val == val)
					return i;
			}// ne marche pas simplifier avec ++ et --
		}

		iterator	find_iterator(const value_type &val)
		{
			iterator	i(_root);

			while(i)
			{
				if(val == i->_current->val)
					return i;
				if(val > i->_current->val)
					i++;
				if(val < i->_current->val)
					i--;
			}
			return i;// SI NE TROUVE PAS RENVOIT NULL
		}


		void	insert(node_pointer parent, node_pointer neww)// mieux
		{
			neww->parent = parent;
			if(neww->val == parent->val)
				return ;
			node_pointer	tmp(NULL);
			
			if(neww->val > parent->val)
			{
				tmp = parent->right;
				parent->right = neww;
			}
			else
			{
				tmp = parent->left;
				parent->left = neww;
			}
			if(tmp)
			{
					if(neww->val > tmp->val)
						neww->left = tmp;
					else if(neww->val < tmp->val)
						neww->right = tmp;
					tmp->parent = neww;
			}
			++_size;
		}

		void	insert_good_place(/*node_pointer neww*/ const value_type &val)
		{
			iterator	i(_root);
			node_pointer	neww = _alloc.allocate(1);
			_alloc.construct(&neww, node_type(val));
			neww->right = NULL;
			neww->left = NULL;
			neww->parent = NULL;
			while(i)
			{
				if(neww->val > i->_current->val)
				{
					if(i->_current->right && neww->val > i->_current->right->val)
						i = iterator(i->current->right);
					else
						return	insert(neww);
				}
				if(neww->val < i->_current->val)
				{
					if(i->_current->left && neww->val < i->current->left->val)
						i = iterator(i->current->left);
					else
						return	insert(neww);
				}
				if(neww->val == i->current->val)
				{
					std::cout << "Je ne sais pas quoi faire " << std::endl;
					return;
				}
			}
			

		}	

		size_type	max_range(node_pointer	p, size_type i)
		{
			size_type	sizeleft = i;
			size_type	sizeright = i;

			if(p)
			{
				if(p->right || p->left)
				{
					if(p->right)
					{
						sizeright++;
						sizeright = max_range(p->right, sizeright);
					}
					if(p->left)
					{
						sizeleft++;
						sizeleft = max_range(p->left, sizeleft);
					}
					if(sizeleft > sizeright)
						i = sizeleft;
					else
						i = sizeright;
				}
			}
			return i;
		}
// POUR AVOIR LE MAXIMUM SUR LE RANG N
		node_pointer	max_range_pointer(node_pointer r, size_type range, size_type actualrange)
		{
			node_pointer	left;
			node_pointer	right; // aller de preference vers le right

			if(range != actualrange)
			{
				// ON est pas au bon rang // Dans tous les cas on avance de 1
				if(r->left)
					left = max_range_pointer(r->left, range, actualrange + 1);
				if(r->right)
					right = max_range_pointer(r->right, range , actualrange + 1);

			}
			else if(actualrange == range)
				return	r;
			if(right)// prioritee a droite
				return right;
			if(left)// apres gauche
				return left;
		}
// POUR AVOIR LE MINIMUM SUR LE RANG N
		node_pointer	min_range_pointer(node_pointer r, size_type range, size_type actualrange)
		{
			node_pointer	left;
			node_pointer	right;

			if(range != actualrange)
			{
				if(r->right)
					right = min_range_pointer(r->right, range, actualrange + 1);
				if(r->left)
					left = min_range_pointer(r->left, range, actualrange + 1);
			}
			else if(actualrange == range)
				return r;
			if(left)// priorite a gauche
				return left;
			if(right)
				return right;
		}
		
// FONCTION IMPLEMENTATION
		node_pointer	range_implementation(node_pointer actual, size_type range, size_type actualrange)
		{
			if(range == actualrange && actual->parent->left == actual && actual->parent->right)
				return actual->parent->right;
			node_pointer	l;
			while(actual)
			{
				if(actual == _root)
					return min_range_pointer(_root->right, range, 1);
				l = actual;
				actual = l->parent;// remonte;
				actualrange--;
				if(l == actual->left && actual->right)// si il y un element et que on est au bon range
					return actual->right;
				else if(l == actual->right && actual->parent)
				{
					l->actual;
					actual = l->parent;
					actualrange--;
					node_pointer	s = min_range_pointer(actual->right, range, actualrange);
					if(s)
						return s;
				}
			}
		}

// FONCTION PRINT_NODE
		void		print_n(node_pointer p)// PROBLEME NE PEUT PAS METTRE DE NULL
		{
			if(!p)
			{
				std::cout << "\tNULL ";
				return;
			}	
			else if(p == _root)
				std::cout << "\tROOT = ";
			else if(p->parent->left == p)
				std::cout << "\tLEFT = ";
			else if(p->parent->right == p)
				std::cout << "\tRIGHT = ";
			std::cout << p->val;
		}

// FONCTION 2
		void		print_range(size_type range)
		{
			if(range == 0 || range == 1)
			{
				if(range == 0)
					return print_n(_root);
				if(range == 1 && _root->left)
					print_n(_root->left);
				if(range == 1 && _root->right)
					return print_node(_root->right);
			}
			else
			{
				node_pointer	i = min_range_pointer(_root,range, 0);// On va prendre l elemnet le plus a gauche
				node_pointer	max = max_range_pointer(_root, range, 0);
				node_pointer	tmp;
				while(i != max && i)
				{
					print_node(i);
					tmp = i;
					i = range_implementation(tmp);
				}
				if(i == max)
					print_node(i);
			}
		}
// FONCTION 1
		void		print()
		{
			std::cout << "ARBRE DE RECHERCHE" << std::endl;
		//	size_type		i = 0;

			size_type i = this->max_range(_root, 0);// va compter le nombre maximale de rang
			for(size_type j = 0; j <= i ; j++)// SAUT DE LIGNE
			{
				std::cout << "\t\tRANGE = " << j << std::endl;
				std::cout << "_____________________________________________________________________________________________________________"<< std::endl;// UNE SEPARATION
				print_range(j);
				std::cout << std::endl;
			}

		}

	};

};

#endif
