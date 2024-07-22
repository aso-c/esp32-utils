/*!
 * @file: revers-adapt.h
 * @brief reverse adapters for stdlib, own implementation
 * Template definition file
 *
 * @license This code is in the Public Domain (or CC0 licensed, at your option.)
 *
 * Unless required by applicable law or agreed to in writing, this
 *  software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 *  CONDITIONS OF ANY KIND, either express or implied.
 *
 * @author  aso (Solomatov A.A.)
 * @date Created 19.07.2024
 *
 * @version 0.1
 */



#ifndef __REVERSE_ADAPTERS__
#define __REVERSE_ADAPTERS__

#if !defined(__cplusplus)
#error File __FILE__ is not intended to use with a pure C
#endif	// __cplusplus



namespace aso
{
    namespace adaptors
    {

	template <typename T>
	class reverse
	{
	public:
	    reverse(T&& iterable, size_t f_offs = 0, size_t end_offs = 0) : refiterable(std::forward<T>(iterable)),
		front_offset(f_offs), tail_offset(end_offs) {};
	    typename T::reverse_iterator begin() { return refiterable.rbegin() + front_offset; }
	    typename T::reverse_iterator end() { return refiterable.rend() - tail_offset; }

	private:
	    T&& refiterable;
	    const size_t front_offset;
	    const size_t tail_offset;
	}; /* reverse */

	/// Const reverse adaptors
	template <typename T>
	class const_reverse
	{
	public:
	    const_reverse(const T& iterable, int f_offs = 0, int end_offs = 0) : refiterable(iterable),
		front_offset(f_offs), tail_offset(end_offs) {};
	    typename T::const_reverse_iterator begin() { return refiterable.crbegin() + front_offset; }
	    typename T::const_reverse_iterator end() { return refiterable.crend() - tail_offset; }

	private:
	    const T& refiterable;
	    const int front_offset;
	    const int tail_offset;
	}; /* const_reverse_adapter */

    }; /* adaptors */

}; /* namespace aso */

#endif /* __REVERSE_ADAPTERS__ */
