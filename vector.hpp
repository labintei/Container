/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 16:41:19 by labintei          #+#    #+#             */
/*   Updated: 2022/06/30 17:48:39 by labintei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef	VECTOR_HPP
#define VECTOR_HPP

#include "vector_iterator.hpp"
#include "reverse_iterator.hpp"
#include <memory>
#include <string>


namespace ft
{
	template<typename T, typename Allocator = std::allocator<T> >
	class vector
	{
		public:

			/*
				Si marche pas :
				typedef typename allocator_type::const_reference		const_reference;..
			*/
			typedef T						value_type;
			typedef Allocator					allocator_type;
			typedef typename value_type*				pointer;
			typedef typename const pointer				const_pointer;
			typedef typename value_type&				reference;
			typedef typename const reference			const_reference;
			typedef vector_iterator<value_type>			iterator;
			typedef vector_iterator<const value_type>		const_iterator;
			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;
			typedef typename allocator_type::size_type		size_type;
			typedef typename allocator_type::difference_type	difference_type;
		protected:
			allocator_type	_alloc_type;
			pointer_type	_array;
			size_type	_size;
			size_type	_capacity;
			// le contenu d une base ne contient pas d iterator en soit , juste un outil pour se deplacer dans un vecteur ...
		public:
			vector(const Allocator &a): _alloc_type(a){};			
			vector(size_type n, const Allocator &a): _alloc_type(a){_a}
	};

}

#endif
