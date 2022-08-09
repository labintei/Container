/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tree_iterator.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 16:55:25 by labintei          #+#    #+#             */
/*   Updated: 2022/08/09 14:24:01 by labintei         ###   ########.fr       */
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

#include "three_iterator.hpp"

// trouver un autre moyen de l implementer

namespace ft
{

	template <class T, class Compare, class Alloc = std::allocator<Node<T> > >
	class three
	{

		public:

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
