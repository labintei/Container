/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   three_iterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 16:55:25 by labintei          #+#    #+#             */
/*   Updated: 2022/08/12 14:09:44 by labintei         ###   ########.fr       */
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
#include <iostream>

#include "print_tree_iterator.hpp"
#include "tree.hpp"


// trouver un autre moyen de l implementer
#define BLACK 0
#define RED 1

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
		bool		color;
		Node*		parent;
		Node*		left;
		Node*		right;

		Node(value_type &s): val(s), color(RED), parent(NULL), left(NULL), right(NULL){};
	};

	

	template<class N>
//	template<class T>
	class three_iterator// voir si on peut pas simplifier en mettant directement le Node dans l iterateur
	{
		public:

		
		typedef N					node_type;
		typedef node_type*				node_p;	

		typedef typename node_type::value_type		value_type;
		
//		typedef T					value_type;
//		typedef Node<value_type>			node_type;
//		typedef node_type*				node_p;
		typedef value_type*				pointer;
		typedef value_type&				reference;
		typedef typename std::ptrdiff_t			difference_type;
		typedef std::bidirectional_iterator_tag		iterator_category;

		public:

		node_p		_current;

		public:	
		three_iterator():_current(NULL){};
		three_iterator(const three_iterator &s): _current(s._current){};
		// Important de le faire au niveau d une node
		three_iterator(const node_p &c): _current(c){};
		
		// peut deja faire un find dans mes iterateurs
//		three_iterator(const value_type &val){_current = find(val);};

		~three_iterator(){};

		three_iterator operator=(const three_iterator &s)
		{
			_current = s._current;
			return *this;
		};

		friend bool operator==(const three_iterator &s, const three_iterator &r){return (s._current == r._current);}
		friend bool operator!=(const three_iterator &s, const three_iterator &r){return (s._current != r._current);}
/*
		three_iterator	find(const value_type val)
		{
			three_iterator	f(_root);
			// je nai pas la root
			while(f != NULL)
			{
				if((*f) == val)
					return f;
			}
			return f;// devrait renvoyer NULL
		}*/

		node_p	max(node_p n)
		{
			while(n->right != NULL)
				n = n->right;
			return n;
		}
		node_p	min(node_p n)
		{
			while(n->left != NULL)//doit corresondre a un NILL
				n = n->left;
			return n;
		}

		reference		operator*()const{return _current->val;}	
		pointer			operator->()const{return &(operator*());}

		three_iterator &operator++(){if(_current != NULL)increase();return *this;};
		three_iterator operator++(int){three_iterator tmp(*this); ++(*this); return tmp;};
		three_iterator &operator--(){if(_current != NULL)decrease(); return *this;};
		three_iterator operator--(int){three_iterator tmp(*this); --(*this); return tmp;};

		void increase()
		{
			if(_current->right != NULL)
				_current = min(_current->right);
			else
			{
				node_p		tmp = _current;
				
				_current = _current->parent;
				while(_current != NULL && _current->left != tmp)
				{
					tmp = _current;
					_current = _current->parent;
				}
			}
		}
		void decrease()
		{
			if(_current->left != NULL)
				_current = max(_current->left);
			else
			{
				node_p	tmp = _current;
				_current = _current->parent;
				while(_current != NULL && _current->right != tmp)
				{
					tmp = _current;
					_current = _current->parent;
				}
			}

		};

	};

	template <typename I1, typename I2>
	bool	operator==(const three_iterator<I1> &x, const three_iterator<I2> &y)
	{return x._current == y._current;}
	template <typename I1, typename I2>
	bool	operator!=(const three_iterator<I1> &x, const three_iterator<I2> &y)
	{return x._current != y._current;};


};

#endif
