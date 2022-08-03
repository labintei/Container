/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   three_iterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 16:55:25 by labintei          #+#    #+#             */
/*   Updated: 2022/08/03 22:13:52 by labintei         ###   ########.fr       */
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
		three_iterator():_current(), _root(), _NIL();
		three_iterator(const three_iterator &s): _current(s._current), _root(s._root), _NIL(s._NIL){};
		three_iterator(const node_p &c/*, const node_p &r, const node_p &N*/): _current(c)/*, _root(r), _NIL(N)*/{};
		~three_iterator(){};


		three_iterator operator=(const three_iterator &s)
		{
			_current = s._current;
			_root = s._root;
			_NIL = s._NIL;
			return *this;
		};

		friend bool operator==(const three_iterator &s, const three_iterator &r){return (s._current == r._current);}
		friend bool operator!=(const three_iterator &s, const three_iterator &r){return (s._current != r._current);}


		node_p	_max(node_p n)
		{
			while(node->right)
				node = node->_right;
			return node;
		}`
		node_p	_min(node_p c)
		{
			while(node->left)
				node = node->left;
			return node;
		}

		reference		operator*(){return _current->val;}
		const_reference		operator*()const{return _current->val;}	
		const_pointer		operator->()const{return &(operator*());}
		pointer			operator->(){return &(operator*());}

		three_iterator operator++(){increase();return *this};
		three_iterator &operator++(int){three_iterator tmp = *this; ++_current; return tmp};
		three_iterator operator--(){decrease(); return *this;};
		three_iterator &operator--(int){three_iterator tmp = *this; --_current; return tmp;};



		/*
		// compliquer				
		*/
		void increase()
		{
			if(_current->right)
			{
				_current = min(_current->right);
			}
			else
			{
				node_pointer	tmp = _current;
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
			{
				_current = max(_current->left);
			}
			else
			{
				node_pointer	tmp = _current;
				_current = _current->parent;
				while(_current->right != tmp)
				{
					temp = _current;
					_current = _current->parent;
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

		typedef	ft::three_iterator<value_type>		iterator;
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

		bool		empty(){return size == 0;}


		iterator	min()
		{
			iterator	i(root);
			while(i->left)};
				i = i->left;
			return i;
		}
		iterator	max()
		{
			iterator	i(root)
			while(i->right)
				i = i->right;
			return i;
		}
		iterator	find(const value &val)
		{
			iterator i(root);
			
			while(i)
			{
				if(val < i->val || val > i->val)
				{
					if(val < i->val && i->left)
						i = i->left;
					else if(val > i->val && i->right)
						i = i->right;
					else
						return iterator();// renverra un NULL par default
				}
				else if(i->val == val)
					return i;
			}
		}
		

		// PEUT PEUT ETRE SIMPLIFIER CA AVEC DES ++ ET --
		// BREF FAIRE UNE DEUXIEME VERSION



		void	insert(node_pointer parent, node_pointer neww)// mieux
		{
			// Dans tout les cas
			neww->parent = parent;
			if(neww->val == parent->val)
				return ;// je sais pas quoi faire dans ce cas
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
					tmp->parent = neww;// dans tout les cas le parent devient NEWW
			}
			++_size;// important
			// trouver un moyen de simplifier ca
		}
		// est ce que je fait une right insertion et une left insertion
		// faire un cas ou le prochain est NULL OU tout le temps garder un previous ??
		void	insert_good_place(node_pointer neww)
		{
			iterator	i(root);
			node_pointer	i = _alloc_type.allocate(1);
			_alloc_type.construct(&i, node_type(val));
			while(i)
			{
				if(neww->val > i->_current->val)
				{
					if(i->_current->right && neww->val > i->_current->right->val)// je crois qu il y a deux cas
						i = iterator(i->current->right);// SE DEPLACE QUAND IL DOIT SE DEPLACER
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
		//	faire a partir d un pointeur
/*		void	insert_good_place(node_pointer neww)
		{
			iterator	i(root);
			while(i)
			{
				if(i->_current->val > neww->val)
				{
					if(i->_current->right)
						i = iterator(i->_current->right);
					else// c est la que ce fait l insertion
					{
						node_pointeur tmp = i->_current->right;// stock le pointeur right
						i->current->right = neww;
						tmp->parent
					}
					
						
				{
				else if(i->_current->val < neww->val)
				{
					if(i->_current->left)
						i = iterator(i->current->left);
				}
				else
				{
					std::cout << "Je ne sais pas ce que l on fait quand cest ==" << std::endl;
					return ;
				}
			}
			return(i);
		}
*/
//		Pas obligatoire c est juste pour voir ce que je fait
		// ou iterator

		/*
				
					ROOT
			LEFT				RIGHT
		LEFT		RIGHT		LEFT		RIGHT

		PLUS SIMPLE
		//

		TOUJOURS LEFT_PRINT AVANT DE RIGHT PRINT
		REMONTER D UN RANG

		SI RIGHT && (all->parent are RIGHT) ->donc est max_range(n)
		i++;
		ALLER AU LEFT && all->parent are LEFT du rang souhaiter ->min_range(n)

		//n REFAIRE LA MEME CHOSE

		// FAIRE UNE FONCTION QUI CALCULE LE MAX RANGE		

		*/


		// FONCTION ET VALEUR A UTILISER
	

		// CALCUL LE NOMBRE MAXIMAL DE RANG


		size_type	max_range(node_pointer	p, size_type i)
		{
			size_type	sizeleft = i;
			size_type	sizeright = i;

			if(p)
			{
				if(p->right || j->left)
				{
					if(j->right)
					{
						sizeright++;
						sizeright = max_range(j->right, sizeright);
					}
					if(->left)
					{
						sizeleft++;
						sizeleft = max_range(j->left, sizeleft);
					}
					if(sizeleft > sizeright)
						i = sizeleft;
					else
						i = sizeright;
				}
				else// CORESPOND A DES NILL
					return i;
			}
			
		}

		// pourra faire la meme chose avec Min
		// max_range_pointer
		// au debut 
//		max_range(root, 0, range_souhaiter)
		node_pointer	max_range_pointer(node_pointer r, size_type range, size_type actualrange)
		{
			node_pointer	left;
			node_pointer	right; // aller de preference vers le right

			if(range != actualrange)
			{
				// ON est pas au bon rang // Dans tous les cas on avance de 1
				if(r->left)
					left = max_range_pointer(r->left, range + 1, actualrange);
				if(r->right)
					right = max_range_pointer(r->right, range + 1, actualrange);

			}
			else if(actualrange == range)
				return	r;
			if(right)// prioritee a droite
				return right;
			if(left)// apres gauche
				return left;
		}

		node_pointer	min_range_pointer(node_pointer r, size_type range, size_type actualrange)
		{
			node_pointer	left;
			node_pointer	right;

			if(range != actualrange)
			{
				if(r->right)
					right = min_range_pointer(r->right, range + 1, actualrange);
				if(r->left)
					left = min_range_pointer(r->left, range + 1, actualrange);
			}
			else if(actualrange == range)
				return r;
			if(left)// priorite a gauche
				return left;
			if(right)
				return right;
		}
		

		/* PARTIR AUSSI DU PRINCIPE QUE QUAND JE REMONTE JUSQU A ROOT JE VAIS SUR LA PARTIE DROITE DE L ARBRE ET JE VAIS ALLER A DROITE puis 
		-> <-
		*/
		node_pointer	range_implementation(node_pointer actual, size_type range, size_type actualrange)
		{
			if(actual->parent && actual->parent->left == actual && actual->parent->right)// sera techniquement sur le meme rang
				return	actual->parent->right;// EST L ELEMENT DE GAUCHE ET DONC VA SUR L ELEMENT DU MEME RANG DE DROITE SI IL EXISTE
			if(actual->parent && actual->parent->right == actual)
			{
				// EST DEJA SUR L ELEMENT DE DROITE DOIT REMONTER ET CHECHER UN NODE AU MEME RANG
				if(range == actual range)
				{

				}
			}
			else
			{
				node_pointeur	tmp;
				size_type
				if(p->actual->parent)
				node_pointer	p = actual->parent;
				 ,range - 2)
				
			}
		}

		// faire quelque chose de legerement diffrent pour inclure le rang 1

		void		print_n(node_pointer p)// PROBLEME NE PEUT PAS METTRE DE NULL
		{
			if(!p)
			{
				std::cout << "\tNULL ";
				return;
			}	
			else if(p == root)
				std::cout << "\tROOT = ";
			else if(p->parent->left == p)
				std::cout << "\tLEFT = ";
			else if(p->parent->right == p)
				std::cout << "\tRIGHT = ";
			std::cout << p->val;
		}

		void		print_node(node_pointer	p)
		{
			if(p == _root)
			{
				if(_root)
					std::cout << "\tROOT = " << p->val << "\t";
				else
					std::cout << "\tEmpty\t";
			}
			else if(p != _root)// AURA FORCEMENT UN PARENT
			{
				if(p->_parent && p->parent->left == p)
				{
					std::cout << "\tLEFT = " << p->val << "\t";
					if(p->parent->right)
						std::cout << "\tRIGHT = " << p->parent->right->_val << "\t"
					else// element RIGHT NULL
						std::cout << "\tRIGHT = NULL" << "\t"; 
				}
				if(p->parent && p->parent->right == p)
				{
					// par default LEFT SERA TOUJOURS NULL
					std:cout << "\tLEFT = NULL" << "\t";
					std::cout << "\tRIGHT = " << p->val << "\t"; 
				}

			}
		}


		node_pointer	pointer_max_range(int range)
		{
			iterator	i(root);

			for(size_type)
			{

			}

		}






/*
0					R
1			B			C
2		C		D	C		D

*/

		void		print_range(size_type range)// PETIT PROBLEME VA REVENIR AU DEBUT A CHAQUE FOIS // MAIS EN MEME TEMPS C EST CE QU ON FAIT
		{
			if(range == 0 || range == 1)
			{
				if(range == 0)
					return print_node(_root);
				if(range == 1 && _root->left)
					return print(_root->left);
				else if(_root->right)
					return print(root->right);
			}
			else
			{
				// va mettre l element le plus a gauche // pourrait marche pour range 1
				node_pointer	i = min_range_pointer(root, range, 0);

			}
		}

		void		print()
		{
			std::cout << ""
			size_type		i = 0;

			i = max_range(root, i);// va compter le nombre maximale de rang
			for(size_type j = 0; j <= i; j++)// SAUT DE LIGNE
			{
				std::cout << "\t\tRANGE = " << j << std::endl;
				std::cout << "_____________________________________________________________________________________________________________"<< std::endl;// UNE SEPARATION
				print_range(j);
				std::cout << std::endl;
			}

		}

/*
		void		print_node(node_pointer n, size_type range, size_type wish_print)
		{
			if(range == 0 && wish_print == 0)
			{
				std::cout "ROOT " << n->val;
				range++;
				wish_print++;
				std::cout << std::endl;
				if(n->left)
					print_node(n->left);
				else
					print_node(n->right);//cas ou la patie de gauche est vide
				return;
			}// CAS DE ROOT
			else
			{
				// PERMET DE TYPER LA VALEUR EN RIGHT OU EN LEFT
				if(i != 0 && n->parent && n == n->parent->right && range == wish_print)
					std::cout << "RIGHT " << n->val << " ";
				if(i != 0 && n->parent && n == n->parent->left && range == wish_print)
					std::cout << "LEFT " << n->val << " ";
				// GO LEFT
				// IMPRIME LEFT
				// REMONTE
				// GO RIGHT
				// IMPRIME RIGHT
				// ON REMONTE TOUJOURS JUSQU A 0 // PRINCIPE DE BASE
				// 
				while(range != )
				print_node

		
				// IL FAUT UNE FIN
				
			}
				

		}*/
/*
		node_pointeur		max_range(size_type range)
		{
			node_pointer	n = root;
			node_pointer	tmp;

			for(size_type t = 0; t != range)
			{}
		}*/
		void		print()
		{
			std::cout << "PRINT ARBRE DE RECHERCHE" << std::endl;
			size_type	i = 0;
			size_type	j = 0;
			// indiquera le nombre derang que je peut remonter pour print // 
			if(!_root)
				return;
			print_node(_root, i, j);
		}

	};

};

#endif
