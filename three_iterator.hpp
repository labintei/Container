/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   three_iterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 16:55:25 by labintei          #+#    #+#             */
/*   Updated: 2022/08/09 18:37:37 by labintei         ###   ########.fr       */
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
		bool		NIL;
		bool		color;
		Node*		parent;
		Node*		left;
		Node*		right;

		Node():val(NULL) , NIL(true),color(BLACK),parent(NULL),left(NULL),right(NULL){};// creer un NILL evitera les segfaults 
		Node(value_type &s): val(s) , NIL(false), color(RED), parent(Node()), left(Node()), right(Node()){};
		
		Node operator=(const Node &ref)
		{
			val = ref.val;
			parent = ref.parent;
			left = ref.left;
			right = ref.right;
		}
		// S OCCUPER DES NILS
		friend	bool	operator==(const Node& first, const Node &second)
		{
			if(first.NIL != second.NIL)
				return false;
		}
		// Peut etre faire des operateur pour les node
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
		three_iterator():_current(Node()){};
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
				while(!_current->NIL && _current->left != tmp)
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
				while(!_current->NIL && _current->right != tmp)
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
		// les iterateur peuvent renvoyer des NIL
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

		three(const allocator alloc = allocator_type()):_root(), _comp(comp), _alloc(allocator_type), _size(0)
		{
			_root = _alloc.allocate(1);
			_alloc.construct(&_root), Node();
		}
		three(const &three t):_root(), _comp(t.comp), _alloc(t._alloc), _size(t._size){*this = t;}

		~three(){}

		void	clear_branch(node_ptr	x)
		{
			if(x == NULL)
				x = _root;
			if(x->NIL == false)
			{
				clear_branch(x->left);// va ua bout de la branche
				clear_branch(x->right);
				_alloc.destroy(x);
				_alloc.deallocate(x, 1);
			}
		}

		void	clear()
		{
			
			_root = Node();
			_size = 0;
		}
		three	operator=(const &t)
		{
			clear();
			insert(begin(), end());
		}
		
		void	branch_copy(node_pointer src, node_pointer tocopy)// ON part du principe que les RED black tree sont toujours equilibree
		{
			// tu peut faire des insert a la suite parce qu il y aura a chaque fois une nouvelle allocation
			if(t->parent == Node())// est au niveau de la racine
			{

			}
			else
			{
				src = alloc.allocate(1);
				if(to->copy->left != Node())
					branch_copy(src->left, to->copy->left);
				if(to_copy->right != Node())
					branch_copy(src->right, to->copy->right);
			}
		}

		bool		empty(){return _size == 0;}
		size_type	size(){return _size;}
		size_type	max_size()const{return _alloc.max_size();}
		
		iterator		begin(){return min();}
		const_iterator		begin()const{return min();}

		iterator		end(){return max();}
		const_iterator		end()const{return max();}

		reverse_iterator	rbegin(){return reverse_iterator(end())}
		const_reverse_iterator	rbegin()const{return const_reverse_iterator(end());}
		
		reverse_iterator	rend(){return reverse_iterator(begin());}
		const_reverse_iterator	rend(){return const_reverse_iterator(begin());}

		// faire clear ici
		//void			clear(){}pas obligee d utiliser clear C++11

		// meme entre map et set
		ft::pair<iterator,bool>	insert(const value_type &val)
		{

		}
		// meme entre map et set
		template<class InputIterator>
		void	insert(InputIterator first, InputIterator last)
		{

		}

		
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

		// TOUT CA NE SEMBLE PAS MARCHER
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
			}
		}
		// SAME
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




		// programmiz red black tree

		/*

			1) every_nodes is color, /rouge ou noi

			2) root is black

			3) Chaque NIL is black

			4) Pas de rouges a la suite

			5) Pour chaque chemin a le meme nombre de noeud noir

			Node: color, key, left right parent

			Limitation : aucun chemin a partir de la est plus grand de deux fois que aucun autre chemin
				lenght < 2 * other lenght
		*/

		// Operation Left_rotate
		/*
			Correspond a une rotation B parent left de A
			Prerequis B est le right de A

			R		R
			|		|
			A		B
		       / \	->     / \
		      E   B	      A   D
			 / \	     / \
			C   D	    E   C
		*/

		void		Left_rotate(node_pointer A/*, node_pointer B*/)
		{
			node_pointer	B = A->right;
			if(B->left)//2)
			{
				B->left->parent = A;
				A->right = B->left;// EST DEVENU PARENT
			}
			if(!(A->parent))//3)
				_root = B;
			else if(A == A->parent->right)//4)
				A->parent->right = B;
			else//5)
				A->parent->left = B;
			B->left = A;//6)
			A->parent = B;
		}

		// Operation Right_rotate
		/*
			Correspond a une rotation B parent right de A
			Prerequis B est le left de A
			R			R
			|			|
			A			B
		       / \		       / \
		      B	  E		      C   A
		     / \			 / \
		    C   D			D   E
		*/

		void		Right_rotate(node_pointer A/*, node_pointer B*/)
		{
			node_pointer	B = A->left;
			if(B->right)//1)
			{
				B->right->parent = A;
				A->left = B->right;
			}
			if(!A->parent)//2)
				_root = B;
			else if(A->parent->right == A)//3)
				A->parent->right = B;
			else//4)
				A->parent->left = B;
			B->right = A;//6)
			A->parent = B;
		}

		// LEFT_RIGHT Rotation
		/*
			/\		/
		       /	->     /
				      /
		*/
		void		Left_Right_rotate(node_pointer A)
		{
			Left_rotate(A, A->right);
		}

		// RIGHT_LEFT Rotation
		/*

		*/
		void		Right_Left_rotate(node_pointer A)
		{
			Right_rotate(A, A->left);
		}

		/*
			Insert new element in Red Black Tree

			1)Le node est inserer en tant que rouge
			2) Si le noeud n est pas dans les propritees
				1)Recolor
				2)Rotation
			
		*/



		node_pointer	insert(node_pointer root,node_pointer neww, char d)
		{
			node_pointer	tmp;

			if(d == 'r')
			{
				neww->color = BLACK;
				_root = neww;
			}
			else if(d == 'R' || d == 'L')
			{
				if(d == 'R')
				{
					tmp = root->right;
					root->right = neww;
					neww->right = tmp;
				}
				else
				{
					tmp = root->left;
					root->left = neww;
					neww->left = tmp;
				}
				neww->parent = root;
			}
			else if(d == 'e')
			{
				std::cout << "SAME" << std::endl;
				return NULL;
			}
			_size++;
			return neww;
		}


		node_p	new_node(const value_type &val)
		{
			node_pointer	i = _alloc.allocate(1);
			i->left = NULL;i->right = NULL;i->parent = NULL;
			_alloc.construct(&i,node_type(val));
			return i;
		}

		node_p	find_insert(const value_type &val)
		{

			iterator	i(_root);
			iterator	s();
			while(i)
			{
				s = i;
				if(val < i->_current->val)
				{
					if(i == min() || val > (s--)->_current->val)
						return(insert('L',i->_current, new_node(val)));
					i--;
				}
				if(val > i->_current->val)
				{
					if(i == max() || val > (s++)->current->val)
						return(insert('R',i->_current, new_node(val)));
					i++;
				}
				if(val == i->_current->val)
					return(insert('e',i->_current, node_type(NULL)));
			}
			return i;

		}


// FAIT UN DELETE AVEC DES CLEES ?
// modifier ca

// commence a y = z


		void	 	find_node_del(const value_type &val)
		{
			iterator(root);// seulement si egal egal
		}

		void	delete_node(node_pointer d)
		{
			bool		color = d->color;
		
			if(d->left == Node())
			{
					node_pointer	e = d->left;
					d->right = e;
					// transplant
					if(d->parent->left == d)
						d->parent->left = e;
					else
						d->parent->right = e;
					delete_p(node_pointer);
			}
			else if(d->right == Node())
			{
				d->left 
				if(d->parent->left == d)
					d->parent->left = e;
				else
					d->parent->right = e;
			}
			else
			{
				node_pointer	e = min()
				color = d->
			}
		}


		void	insert_red_black_three(const value_type &val)
		{
			if(!(_root))//
				insert('r', node_type(NULL), new_node(val))
			else
			{
				node_pointer	i = find_insert(val);
				if(i)
				{
					color_change(i);
				}
			}
		}

		//ALGOROTHM TO DELETE A NODE
		// DONE MAIS ERREUR SUR LE PREMIER
		void		delete_algo(node_pointer i)
		{
			// a lancer avant le delete va permettre de recolorer avant deletion
			// sera quand meme plus simple avec un node_pointer

			node_pointer	s;
			while(i != root && i->color == BLACK)
			{
				if(i == i->parent->left)
				{
					s = i->parent->right;
					if(s->color == RED)
					{
						i->parent->right->color = BLACK;
						i->parent->color = RED;
						Left_rotate(i->parent);
						s = i->parent->right;// Assignation apres LEFT_ROTATE
					}
					if(s->left->color == BLACK && s->right->color == BLACK)
					{
						s->color = RED;
						i = i->parent;
					}
					else
					{
						if(s->right->color == BLACK)
						{
							s->left->color = BLACK;
							s->color = RED;
							Right_rotate(s);
							s = i->parent->right;
						}
						s->color = i->parent->color;
						i->parent->color = BLACK;
						s->parent->color = BLACK;
						Left_rotate(i->parent);
						i = root;
					} 
				}
				else
				{
					s = i->parent->left;
					if(s->color == RED)
					{
						s->color = BLACK;
						i->parent->color = RED;
						Left_rotate(s);
						s = i->parent->left;
					}
					else
					{
						if(s->left->color == BLACK)
						{
							s->right->color = BLACK;
							s->color = RED;
							Left_rotate(s);
							s = i->parent->left;
						}
						s->color = x->parent->color;
						i->parent->color = BLACK;
						s->left->color = BLACK;
						Right_rotate(x->parent);
						x = _root;
					}

				}
			}
			x->color = BLACK;	
		}




		// CORRESPOND A INSERT FIX DONE
		void		color_change(node_pointer i)// PAR DU PRINCIPE QUE L ON NE DEPLACE PAS LES POINTER QUAND =
		{
			node_pointer	j;// PAS UTILE DE FAIRE UN POINTER DE PLUS
			while(i->parent->color == RED)
			{
				if(i->parent == i->parent->parent->right)
				{
					u = i->parent->parent->left;
					if(u->color == RED)
					{
						u->color = BLACK;// PAS PARTICULIEREMENT UTILE DANCE CE CAS
						i->parent->color = BLACK;
						i->parent->parent->color = RED;
						i = i->parent->parent;
					}
					else
					{
						if(i == i->parent->left)
						{
							i = i->parent;
							Right_rotate(i);
						}
						i->parent->color = BLACK;
						i->parent->parent->color = RED;
						Left_rotate(i->parent->parent);
					}
				}
				else
				{
					if(i->parent->parent->right->color = RED)
					{
						i->parent->parent->right->color = BLACK;
						i->parent->color = BLACK;
						i->parent->parent->color = RED;
						i = i->parent->parent;
					}
					else
					{
						if(i == i->parent->right)
						{
							i = i->parent;
							Left_rotate(i);
						}
						i->parent->color = BLACK;
						i->parent->parent->color = RED;
						Right_rotate(i->parent->parent);
						
					}
					
				}
				if(i == root)
					break;
			}
			_root->color = BLACK;
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

	};

};

#endif
