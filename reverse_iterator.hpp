/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 19:11:42 by labintei          #+#    #+#             */
/*   Updated: 2022/07/26 16:41:19 by labintei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include <memory>
#include <iostream>
#include <string>
#include "utils.hpp"
#include "vector_iterator.hpp"

// les iterator permet de faire des typedef et des typename de pointer_type, reference_type value_type iterateur categiry tag

namespace ft
{
	// ?? pourquoi pas typename je vais regarder le code source // le code source emploit les iterator_traits
	template<typename I>
	class reverse_iterator
	{
		public:
			// va surement rien changer
			//typedef	I							iterator_type;
			typedef typename iterator_traits<I>::iterator_category		iterator_category;
			typedef typename iterator_traits<I>::value_type			value_type;
			typedef typename iterator_traits<I>::difference_type		difference_type;
			typedef typename iterator_traits<I>::pointer			pointer_type;
			typedef typename iterator_traits<I>::reference			reference_type;
			typedef I							iterator_type;
		protected:
			iterator_type	_current;
		public:

		reverse_iterator(): _current(NULL){};
		explicit reverse_iterator(iterator_type c): _current(c){};
		// des que je met sous silence j ai un probleme
	//	reverse_iterator(const iterator_type &s): _current(s){};
		template<typename It>
		reverse_iterator(const reverse_iterator<It> & x): _current(x.base()){};
		reverse_iterator& operator=(reverse_iterator const &s){_current = s._current;return *this;};
		virtual ~reverse_iterator(){};
		iterator_type	base()const{return _current;};
	
		operator reverse_iterator<vector_iterator<value_type const> >() const {return reverse_iterator<vector_iterator<value_type const > >(_current);};
		operator reverse_iterator<vector_iterator<value_type> >() {return reverse_iterator<vector_iterator<value_type> >(_current);}

		reference_type operator*()const{iterator_type _tmp = _current;return (*(--_tmp));};
		pointer_type operator->()const{return &(operator*());}; // ??
		reference_type operator[](int index){return *(_current - index -1);};
		/* On pourrait traduire ca par

			pointer_type operator->()const{return &(*this);};
		*/
		
		bool	operator==(const reverse_iterator &s)const{return (_current == s._current);};
		bool	operator!=(const reverse_iterator &s)const{return (_current != s._current);};
		bool	operator>=(const reverse_iterator &s)const{return (_current >= s._current);};
		bool	operator<=(const reverse_iterator &s)const{return (_current <= s._current);};
		bool	operator>(const reverse_iterator &s)const{return (_current > s._current);};
		bool	operator<(const reverse_iterator &s)const{return (_current < s._current);};

		friend reverse_iterator operator+(difference_type n, const reverse_iterator &s)
		{
			reverse_iterator tmp = s;
			tmp += n;
			return tmp;
			//	return s._current - n;
		};
		
		difference_type operator-(const reverse_iterator& s)const{return s._current - _current;};


		reverse_iterator& operator++(){_current--;return *this;};
		reverse_iterator& operator--(){_current++;return *this;};
		reverse_iterator operator++(int){reverse_iterator tmp = *this;_current--;return tmp;};
		reverse_iterator operator--(int){reverse_iterator tmp = *this;_current++;return tmp;};
		reverse_iterator &operator+=(difference_type n){_current -= n;return *this;};
		reverse_iterator operator-(difference_type n){reverse_iterator tmp = *this; tmp -= n; return tmp;};
		reverse_iterator &operator-=(difference_type n){_current += n; return *this;};
		reverse_iterator operator+(difference_type n)const{reverse_iterator tmp = *this; tmp += n; return tmp;};

		
		friend	std::ostream & operator<<(std::ostream &o , reverse_iterator<I> &s){o << *(s._current); return o;};
	};
//ok
	template<typename T>
	reverse_iterator<T> & operator+(typename reverse_iterator<T>::difference_type n, const reverse_iterator<T> &x){return (x + n);};
	template<typename T>
	reverse_iterator<T> & operator-(typename reverse_iterator<T>::difference_type n, const reverse_iterator<T> &x){return (x - n);};
//ok
	// Au final ca va simplifier et si same typename Template<T, T> ...
	template<typename I, typename I2>
	bool operator==(const reverse_iterator<I> &x, const reverse_iterator<I2> &y){return x.base() == y .base();};
	template<typename I, typename I2>
	bool operator<(const reverse_iterator<I> &x, const reverse_iterator<I2> &y){return x.base() < y.base();};
	template<typename I, typename I2>
	bool operator!=(const reverse_iterator<I> &x,const reverse_iterator<I2> &y){return x.base() != y.base();};
	template<typename I, typename I2>
	bool operator>(const reverse_iterator<I> &x, const reverse_iterator<I2> &y){return x.base() > y.base();};
	template<typename I, typename I2>
	bool operator>=(const reverse_iterator<I> &x, const reverse_iterator<I2> &y){return x.base() >= y.base();};
	template<typename I, typename I2>
	bool operator<=(const reverse_iterator<I> &x, const reverse_iterator<I2> &y){return x.base() <= y.base();};

}



#endif
