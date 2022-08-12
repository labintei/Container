/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 16:55:25 by labintei          #+#    #+#             */
/*   Updated: 2022/08/12 15:05:36 by labintei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_HPP
#define TREE_HPP


// toujours des erreurs dans ce dernier
#include "reverse_iterator.hpp"
#include <iostream>
#include <memory>
#include "utils.hpp"
#include "pair.hpp"

#include <cstddef>


//#include "three_common_fct.hpp"
#include "three_iterator.hpp"
#include "print_tree_iterator.hpp"

// trouver un autre moyen de l implementer
#define BLACK 0
#define RED 1


// n a pas de NIL au niveau de son RED BALCK TREE
namespace ft
{

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
		// Dans ce que fait Georges peut etre change iterator
		typedef	ft::three_iterator<node>			iterator;
		typedef ft::three_iterator<const node>			const_iterator;
		typedef ft::reverse_iterator<iterator>			reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;
		typedef std::ptrdiff_t					difference_type;

		protected:

		node_pointer	_root;
		comp		_comp;
		allocator_type	_alloc;
		size_type	_size;

		public:

		//CONSTRUCTEUR
		three(const allocator_type &alloc = allocator_type()):_root(), _comp(comp()), _alloc(alloc), _size(0){_root = NULL;}
		three(const three &t):_root(), _comp(t.comp), _alloc(t._alloc), _size(t._size){*this = t;}
		//DESTRUCTEUR
		~three(){}
		//OPERATOR=
		three	operator=(const three &t)
		{
			clear();
			insert(t.begin(), t.end());
		}
		
		bool		empty()const{return _size == 0;}
		
		size_type	size()const{return _size;}
		
		size_type	max_size()const{return _alloc.max_size();}
		
		iterator		begin(){return min();}
		const_iterator		begin()const{return min();}

		iterator		end(){return max();}
		const_iterator		end()const{return max();}

		reverse_iterator	rbegin(){return reverse_iterator(end());}
		const_reverse_iterator	rbegin()const{return const_reverse_iterator(end());}
		
		reverse_iterator	rend(){return reverse_iterator(begin());}
		const_reverse_iterator	rend()const{return const_reverse_iterator(begin());}

		void	clear(){}// est reutiliser dans d autre fonctions


		// na pas de insert qui retourne un iterator
/*
		iterator	insert(const value_type &val)
		{
			return (iterator(find_insert(val)));
		}*/

		ft::pair<iterator,bool>	insert(const value_type &val)
		{
			size_type	n = size();
			node_pointer	res = find_insert(val);
			if(res == NULL)
				return ft::make_pair(value_type(), (n != size()));
			return ft::make_pair(res->val, (n != size()));
		}

		template<class InputIterator>
		void	insert(InputIterator first, InputIterator last)
		{
			for(InputIterator a = first; a != last; a++)
				insert(*a);
		}

		// delete_node bool renvoit 0 si pas d erase , renvoit 1 si erase
		size_type	erase(const value_type& key)// prend un key_type voir ci problemet
		{
			// terminer l algo de delete
			iterator 	find = find(key);
			if(find != NULL)
			{
				// METTRE L ALGO POUR DELETE
				return 1;
			}
			return 0;
		}

		size_type count(const value_type& key)const
		{// renvoit 1 si trouve key sinon renvoit 0
			return(find(key) != end());
		}

		// D abord faire find
		iterator	find(const value_type & key)
		{
			iterator	i(min());
			while(i != NULL && *i != key)
				i++;
			return i;
		}

		const_iterator	find(const value_type& key)const
		{
			iterator	i(min());
			while(i != NULL && *i != key)
				i++;
			return i;
		}

		iterator	lower_bound(const value_type &val)
		{
			iterator	p(min());
			for( ; p != end(); p++)
			{
				if(!_comp(*p,val))
					return p;
			}
			return p;
		}

		const_iterator	lower_bound(const value_type &val)const
		{
			const_iterator	p(min());
			for(; p != end(); p++)
			{
				if(!_comp(*p, val))
					return const_iterator(p);
			}
			return p;
		}

		iterator	upper_bound(const value_type &val)
		{
			iterator	p(min());
			for(; p != end(); p++)
			{
				// ok ne s agit peut etre pas de value_compare
				if(comp()(*p, val))
					return p;
			}
			return p;
		}

		const_iterator	upper_bound(const value_type &val)const
		{
			const_iterator	p(min());
			for(; p != end(); p++)
			{
				if(comp()(*p, val))
					return const_iterator(p);
			}
			return p;
		}

		// si equal range ici

		pair<iterator,iterator>			equal_range(const value_type &val)
		{
			return ft::make_pair(lower_bound(val), upper_bound(val));
		}

		pair<const_iterator,const_iterator>	equal_range(const value_type &val)const
		{
			return ft::make_pair(lower_bound(val), upper_bound(val));
		}

		comp		key_comp()const{return _comp;}


//	PARTIE COMMUNE
		void	clear_branch(node_pointer	x)
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

		/*void	branch_copy(node_pointer src, node_pointer tocopy)
		{
			if(t->parent == Node())
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
		}*/
	
		const_iterator	min()const
		{
			const_iterator	i(_root);	
			while(i._current->left != NULL)
				i = const_iterator(i._current->left);
			return i;
		}

		const_iterator max()const
		{
			const_iterator i(_root);
			while(i._current->right != NULL)
				i = const_iterator(i._current->right);
			return i;
		}
	
		iterator	min()
		{
			iterator	i(_root);
			while(i._current->left != NULL)
				i = iterator(i._current->left);
			return i;
		}
		iterator	max()
		{
			iterator	i(_root);
			while(i._current->right != NULL)
				i = iterator(i._current->right);
			return i;
		}

		value_type	find_val(const value_type &val)
		{
			return (find_iterator(val)._current->val);// JUSTE POUR CHANGER LE TYPAGE
		}

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



		node_pointer	insert(char d, node_pointer root,node_pointer neww)
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
				return root;
			}
			_size++;
			return neww;
		}


		node_pointer		new_node(const value_type &val)
		{
			node_pointer	i = _alloc.allocate(1);
			i->left = NULL;i->right = NULL;i->parent = NULL;

			_alloc.construct(i,node(val));

			return i;
		}

		// find_insert une de mes fonctions principale
		node_pointer		find_insert(const value_type &val)
		{

			iterator	i(_root);
			iterator	s;
			while(i != NULL)
			{
				s = i;
				if(val < (*i))
				{
					if(i == min() || val > (*(--s)))// devrait faire des seg
						return(insert('L', i._current, new_node(val)));
					i--;
				}
				if(val > (*i))
				{
					if(i == max() || val < (*(++s)))// devrait faire des seg
						return(insert('R', i._current, new_node(val)));
					i++;
				}
				if(val == (*i))
					return(insert('e',i._current, NULL));
			}
			return i._current;

		}

// FAIT UN DELETE AVEC DES CLEES ?
// modifier ca

// commence a y = z


		void	 	find_node_del(const value_type &val)
		{
			node_pointer	i = find_insert(val);
			if(i)
				std::cout << "DEL" << std::endl;
			else
				std::cout << "NOT DEL" << std::endl;
		}

		void	delete_n(node_pointer d)// A refaire
		{
	//		bool		color = d->color;
		
			if(d->left == NULL)
			{
					node_pointer	e = d->left;
					d->right = e;
					// transplant
					if(d->parent->left == d)
						d->parent->left = e;
					else
						d->parent->right = e;
					//delete_node(node_pointer); ??
			}
			else if(d->right == NULL)
			{
				node_pointer e;// ??? 
				if(d->parent->left == d)
					d->parent->left = e;
				else
					d->parent->right = e;
			}
			else
			{
				node_pointer	e = min();
				//color = d->
			}
		}


		void	insert_red_black_three(const value_type &val)
		{
			if(!(_root))//
				insert('r', _root, new_node(val));
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
			while(i != _root && i->color == BLACK)
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
						i = _root;
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
						s->color = i->parent->color;
						i->parent->color = BLACK;
						s->left->color = BLACK;
						Right_rotate(i->parent);
						i = _root;
					}

				}
			}
			i->color = BLACK;	
		}




		// CORRESPOND A INSERT FIX DONE
		void		color_change(node_pointer i)// PAR DU PRINCIPE QUE L ON NE DEPLACE PAS LES POINTER QUAND =
		{
			node_pointer	u;// PAS UTILE DE FAIRE UN POINTER DE PLUS
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
					if(i->parent->parent->right->color == RED)
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
				if(i == _root)
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
