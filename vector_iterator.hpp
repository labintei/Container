/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 18:08:21 by labintei          #+#    #+#             */
/*   Updated: 2022/06/30 14:08:56 by labintei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP


#include <iostream>
#include <memory>
#include <string>


namespace ft
{
	template<typename T>
	class	vector_iterator
	{
		public:
		typedef T				value_type;
		typedef value_type*			pointer;
		typedef value_type&			reference;
		typedef std::ptrdiff_t			difference_type;
		typedef std::random_access_iterator_tag	iterator_category;
		protected:
			pointer		_p;
		public:
		
		vector_iterator():_p(NULL){};
		vector_iterator(value_type* a):_p(a){};
		vector_iterator(vector_iterator const & src):_p(src._p){};
		vector_iterator& operator=(vector_iterator const & s){_p = s._p; return *this;};
		~vector_iterator(){};		
		// conflit avec base a eclaircir
		pointer base() const {return _p;};
		pointer get_ptr() const {return _p;};	
		operator vector_iterator<value_type const>() const{return vector_iterator<value_type const>(_p);};
		
		bool operator<(const vector_iterator& s)const{return (_p < s._p);};
		bool operator<=(const vector_iterator& s)const{return (_p <= s._p);};
		bool operator>(const vector_iterator& s)const{return (_p > s._p);};
		bool operator>=(const vector_iterator& s)const{return (_p >= s._p);};
		bool operator!=(const vector_iterator& s)const{return (_p != s._p);};
		bool operator==(const vector_iterator& s)const{return (_p == s._p);};
		
		vector_iterator<T> operator+(difference_type n) const {return _p + n;};
		vector_iterator<T> operator-(difference_type n) const {return _p - n;};
		vector_iterator<T>& operator+=(difference_type n){_p += n;return *this;};
		vector_iterator<T>& operator-=(difference_type n){_p -= n;return *this;};
		
		friend vector_iterator<T> operator+(difference_type n, const vector_iterator& c){return n + c._p;};
		difference_type operator-(const vector_iterator& s) const {return _p - s._p;};
		
		vector_iterator& operator++(){_p++; return *this;};
		vector_iterator& operator--(){_p--; return *this;};
		vector_iterator operator++(int){vector_iterator i = *this;++(*this);return i;};
		vector_iterator operator--(int){vector_iterator i = *this;--(*this);return i;};
		
		reference operator*(){return *_p;};
		reference operator[](int n){return *(_p + n);};// pas const
		pointer operator->(){return _p;};
		
		friend	std::ostream & operator<<(std::ostream & o, vector_iterator<T> & rhs){o << *rhs._p; return o;};
	};
		
		template <typename I1, typename I2>
		bool operator==(const vector_iterator<I1>& r, const vector_iterator<I2>& l){return(r.get_ptr() == l.get_ptr());};
		template <typename I1, typename I2>
                bool operator!=(const vector_iterator<I1>& r, const vector_iterator<I2>& l){return(r.get_ptr() != l.get_ptr());};
		template <typename I1, typename I2>
		bool operator<(const vector_iterator<I1>& r, const vector_iterator<I2>& l){return(r.get_ptr() < l.get_ptr());};
		template <typename I1, typename I2>
		bool operator>(const vector_iterator<I1>& r, const vector_iterator<I2>& l){return(r.get_ptr() > l.get_ptr());};
		template <typename I1, typename I2>
		bool operator>=(const vector_iterator<I1>& r, const vector_iterator<I2>& l){return(r.get_ptr() >= l.get_ptr());};
		template <typename I1, typename I2>
		bool operator<=(const vector_iterator<I1>& r, const vector_iterator<I2>& l){return(r.get_ptr() <= l.get_ptr());};

}

#endif
