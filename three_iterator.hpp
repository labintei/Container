/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   three_iterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 16:55:25 by labintei          #+#    #+#             */
/*   Updated: 2022/08/11 16:42:28 by labintei         ###   ########.fr       */
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

		Node():val() , color(BLACK),parent(NULL),left(NULL),right(NULL){};// creer un NILL evitera les segfaults 
		Node(value_type &s): val(s), color(RED), parent(Node()), left(Node()), right(Node()){};
	};

	

	template<class N>
	class three_iterator// voir si on peut pas simplifier en mettant directement le Node dans l iterateur
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
		node_p		_NIL;

		public:	
		three_iterator():_current(node_type()), _NIL(_current){};
		three_iterator(const three_iterator &s): _current(s._current), _NIL(s._NIL){};
		// Important de le faire au niveau d une node
		three_iterator(const node_p &c): _current(c), _NIL(){};
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
			while(n->right->NIL)
				n = n->_right;
			return n;
		}
		node_p	_min(node_p n)
		{
			while(n->left->NIL)//doit corresondre a un NILL
				n = n->left;
			return n;
		}

		reference		operator*()const{return _current->val;}	
		pointer			operator->()const{return &(operator*());}

		three_iterator operator++(){increase();return *this;};
		three_iterator &operator++(int){three_iterator tmp = *this; ++_current; return tmp;};
		three_iterator operator--(){decrease(); return *this;};
		three_iterator &operator--(int){three_iterator tmp = *this; --_current; return tmp;};

		void increase()
		{
			if(_current->right->NIL)
				_current = min(_current->right);
			else
			{
				node_p		tmp = _current;
				
				_current = _current->parent;
				while(_current != _NIL && _current->left != tmp)
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
				while(_current != _NIL && _current->right != tmp)
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
