/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 18:43:26 by labintei          #+#    #+#             */
/*   Updated: 2022/07/26 19:23:08 by labintei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft
{
	template<typename T, typename S = ft::vector<T> >
	class stack
	{
		public:

			typedef typename S::value_type		value_type;
			typedef typename S::reference		reference;
			typedef typename S::const_reference	const_reference;
			typedef typename S::size_type		size_type;
			typedef S				container_type;

		protected:
			container_type			c;
			
		public:

		explicit stack(const container_type& s = container_type()):c(s){}
		~stack(){}
		// pas oblige top
		bool empty()const{return c.empty();}
		size_type size()const{return c.size();}
		reference top(){return c.back();}
		const_reference top()const{return c.back();}
		void push(const value_type &x){c.push_back(x);}
		void pop(){c.pop_back();}


		friend bool operator==(const stack<T, S> &x , const stack<T, S> &y){return x.c == y.c;}
		friend bool operator<(const stack<T, S> &x, const stack<T, S> &y){return x.c < y.c;}
		friend bool operator!=(const stack<T, S> &x, const stack<T, S> &y){return x.c != y.c;};
		friend bool operator>(const stack<T, S> &x, const stack<T,S> &y){return x.c > y.c;}
		friend bool operator<=(const stack<T, S> &x, const stack<T,S> &y){return x.c <= y.c;}
		friend bool operator>=(const stack<T, S> &x, const stack<T, S> &y){return x.c >= y.c;}
	};
};


#endif
