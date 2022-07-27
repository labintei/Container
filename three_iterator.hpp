/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   three_iterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 16:55:25 by labintei          #+#    #+#             */
/*   Updated: 2022/07/27 20:21:57 by labintei         ###   ########.fr       */
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

#include <cstdeff>



// trouver un autre moyen de l implementer
// BLACK 0
// RED 1

namespace ft
{


//	toutes ces valeur doivent etre visible et accessible par les precedent
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
		// struct on pas besoin de ~Node() ??
	};

//	cplusplus bidirectional_iterator_tag

//	Je ne sais pas si il y a moyen de mettre les const emsemble

//	rchallie prend en compte la class Compare qui est pas la meme sous map ou set


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

		// en protected plus diificile d acceder a ce qu il y a dedans

		node_p		_current;
		// root ne sert a rien
		node_p		_root;
		// NIL correspond par default a pointeur sur un Node NUll
		node_p		_NIL;
		
		// par default fera n importe que des NULL
		three_iterator():_current(), _root(), _NIL();
		// copy(0)
		three_iterator(const three_iterator &s): _current(s._current), _root(s._root), _NIL(s._NIL){};
		// copy(1)
		three_iterator(const node_p &c, const node_p &r, const node_p &N): _current(c), _root(r), _NIL(N){};
		// si ne marche pas
		// three_iterator(node_p c, node_p r, node_p N)
		// je ne sais pas trop pour ca
		~three_iterator(){};


		three_iterator operator=(const three_iterator &s)
		{
			_current = s._current;
			_root = s._root;
			_NIL = s._NIL;
			return *this;
		};

		

		// 
		friend bool operator==(const three_iterator &s, const three_iterator &r){return (s._current == r._current);}
		friend bool operator!=(const three_iterator &s, const three_iterator &r){return (s._current != r._current);}


		node_p	_max(node_p n)
		{
			while(node->right)
				node = node->_right;
			return node;
		}
		node_p	_min(node_p c)
		{
			while(node->left)
				node = node->left;
			return node;
		}

		reference		operator*(){return _current->val;}
		// renvoit une reference sous const ???
		const_reference		operator*()const{return _current->val;}	
		const_pointer		operator->()const{return &(operator*());}
		pointer			operator->(){return &(operator*());}

		// normalement toutes les decrementation ok
		three_iterator operator++()
		{
			if(_current->right)
				_current = _current->right;	
		};
		three_iterator &operator++(int){three_iterator tmp = *this; _current++; return tmp};
		three_iterator operator--(){current--; return *this;};
		three_iterator &operator--(int){three_iterator tmp = *this; _current--; return tmp;};
		
		
		// reprendre leur logique ???

		void increase()
		{
			if(_current->right)
			{
				_current = _current->right;// on est d accord
				// ??
				while(_node->left)
					_nide = node->left;// ??
			}
			else
			{

			}
		}

	};



	template <class T, class Compare, class Alloc = std::allocator<Node<T>>>
	class three
	{
		public:

		typedef Compare					comp;
		typedef T					value_type;
		typedef T*					pointer;
		typedef T&					reference;
		typedef Alloc					allocator_type;
		typedef typename ft::Node<value_type>		node;
		typedef node*					pointer_node;
		typedef	size_t					size_type;

		//  a rechecker

		typedef	ft::three_iterator<value_type>		iterator;
		// peut etre a changer vu le build
		typedef const ft::three_iterator<value_type>		const_iterator;
		typedef typename reverse_iterator<iterator>		reverse_iterator;
		typedef typename reverse_iterator<const_iterator>	const_reverse_iterator;
		typedef std::ptrdiff				difference_type;

		protected:

		pointer_node	_root;
		comp		_comp;
		allocator_type	_alloc;
		size_type	_size;

		public:






	};

};

#endif
