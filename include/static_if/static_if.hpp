
// Copyright (c) 2014, Maxim Yanchenko, Evgeny Panasyuk, niXman
// All rights reserved.
//
// This file is part of static_if(https://github.com/niXman/static_if) project.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
//   Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.
//
//   Redistributions in binary form must reproduce the above copyright notice, this
//   list of conditions and the following disclaimer in the documentation and/or
//   other materials provided with the distribution.
//
//   Neither the name of the {organization} nor the names of its
//   contributors may be used to endorse or promote products derived from
//   this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
// ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
// ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// Emulation of "static if" feature from D language within function body, alpha version
// Original idea by Maxim Yanchenko (refer http://rsdn.ru/forum/cpp/5816278.flat.1)
// Some improvements by Evgeny Panasyuk
// Some improvements by niXman

#ifndef _static_if_hpp__included_
#define _static_if_hpp__included_

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/variadic/to_seq.hpp>
#include <boost/preprocessor/control/if.hpp>

#include <type_traits>
#include <utility>

/***************************************************************************/

#define _STATIC_IF_GET_PROC_NAME_is_void(...) std::is_void
#define _STATIC_IF_GET_PROC_ARGS_is_void(...) __VA_ARGS__
#define _STATIC_IF_GET_PROC_NAME_is_null_pointer(...) std::is_null_pointer
#define _STATIC_IF_GET_PROC_ARGS_is_null_pointer(...) __VA_ARGS__
#define _STATIC_IF_GET_PROC_NAME_is_integral(...) std::is_integral
#define _STATIC_IF_GET_PROC_ARGS_is_integral(...) __VA_ARGS__
#define _STATIC_IF_GET_PROC_NAME_is_floating_point(...) std::is_floating_point
#define _STATIC_IF_GET_PROC_ARGS_is_floating_point(...) __VA_ARGS__
#define _STATIC_IF_GET_PROC_NAME_is_array(...) std::is_array
#define _STATIC_IF_GET_PROC_ARGS_is_array(...) __VA_ARGS__
#define _STATIC_IF_GET_PROC_NAME_is_enum(...) std::is_enum
#define _STATIC_IF_GET_PROC_ARGS_is_enum(...) __VA_ARGS__
#define _STATIC_IF_GET_PROC_NAME_is_union(...) std::is_union
#define _STATIC_IF_GET_PROC_ARGS_is_union(...) __VA_ARGS__
#define _STATIC_IF_GET_PROC_NAME_is_class(...) std::is_class
#define _STATIC_IF_GET_PROC_ARGS_is_class(...) __VA_ARGS__
#define _STATIC_IF_GET_PROC_NAME_is_function(...) std::is_function
#define _STATIC_IF_GET_PROC_ARGS_is_function(...) __VA_ARGS__
#define _STATIC_IF_GET_PROC_NAME_is_pointer(...) std::is_pointer
#define _STATIC_IF_GET_PROC_ARGS_is_pointer(...) __VA_ARGS__
#define _STATIC_IF_GET_PROC_NAME_is_lvalue_reference(...) std::is_lvalue_reference
#define _STATIC_IF_GET_PROC_ARGS_is_lvalue_reference(...) __VA_ARGS__
#define _STATIC_IF_GET_PROC_NAME_is_rvalue_reference(...) std::is_rvalue_reference
#define _STATIC_IF_GET_PROC_ARGS_is_rvalue_reference(...) __VA_ARGS__
#define _STATIC_IF_GET_PROC_NAME_is_member_object_pointer(...) std::is_member_object_pointer
#define _STATIC_IF_GET_PROC_ARGS_is_member_object_pointer(...) __VA_ARGS__
#define _STATIC_IF_GET_PROC_NAME_is_member_function_pointer(...) std::is_member_function_pointer
#define _STATIC_IF_GET_PROC_ARGS_is_member_function_pointer(...) __VA_ARGS__

#define _STATIC_IF_GET_PROC_NAME_is_fundamental(...) std::is_fundamental
#define _STATIC_IF_GET_PROC_ARGS_is_fundamental(...) __VA_ARGS__
#define _STATIC_IF_GET_PROC_NAME_is_arithmetic(...) std::is_arithmetic
#define _STATIC_IF_GET_PROC_ARGS_is_arithmetic(...) __VA_ARGS__
#define _STATIC_IF_GET_PROC_NAME_is_scalar(...) std::is_scalar
#define _STATIC_IF_GET_PROC_ARGS_is_scalar(...) __VA_ARGS__
#define _STATIC_IF_GET_PROC_NAME_is_object(...) std::is_object
#define _STATIC_IF_GET_PROC_ARGS_is_object(...) __VA_ARGS__
#define _STATIC_IF_GET_PROC_NAME_is_compound(...) std::is_compound
#define _STATIC_IF_GET_PROC_ARGS_is_compound(...) __VA_ARGS__
#define _STATIC_IF_GET_PROC_NAME_is_reference(...) std::is_reference
#define _STATIC_IF_GET_PROC_ARGS_is_reference(...) __VA_ARGS__
#define _STATIC_IF_GET_PROC_NAME_is_member_pointer(...) std::is_member_pointer
#define _STATIC_IF_GET_PROC_ARGS_is_member_pointer(...) __VA_ARGS__

#define _STATIC_IF_GET_PROC_NAME_is_const(...) std::is_const
#define _STATIC_IF_GET_PROC_ARGS_is_const(...) __VA_ARGS__
#define _STATIC_IF_GET_PROC_NAME_is_volatile(...) std::is_volatile
#define _STATIC_IF_GET_PROC_ARGS_is_volatile(...) __VA_ARGS__
#define _STATIC_IF_GET_PROC_NAME_is_trivial(...) std::is_trivial
#define _STATIC_IF_GET_PROC_ARGS_is_trivial(...) __VA_ARGS__
#define _STATIC_IF_GET_PROC_NAME_is_trivially_copyable(...) std::is_trivially_copyable
#define _STATIC_IF_GET_PROC_ARGS_is_trivially_copyable(...) __VA_ARGS__
#define _STATIC_IF_GET_PROC_NAME_is_standard_layout(...) std::is_standard_layout
#define _STATIC_IF_GET_PROC_ARGS_is_standard_layout(...) __VA_ARGS__
#define _STATIC_IF_GET_PROC_NAME_is_pod(...) std::is_pod
#define _STATIC_IF_GET_PROC_ARGS_is_pod(...) __VA_ARGS__
#define _STATIC_IF_GET_PROC_NAME_is_literal_type(...) std::is_literal_type
#define _STATIC_IF_GET_PROC_ARGS_is_literal_type(...) __VA_ARGS__
#define _STATIC_IF_GET_PROC_NAME_is_empty(...) std::is_empty
#define _STATIC_IF_GET_PROC_ARGS_is_empty(...) __VA_ARGS__
#define _STATIC_IF_GET_PROC_NAME_is_polymorphic(...) std::is_polymorphic
#define _STATIC_IF_GET_PROC_ARGS_is_polymorphic(...) __VA_ARGS__
#define _STATIC_IF_GET_PROC_NAME_is_final(...) std::is_final
#define _STATIC_IF_GET_PROC_ARGS_is_final(...) __VA_ARGS__
#define _STATIC_IF_GET_PROC_NAME_is_abstract(...) std::is_abstract
#define _STATIC_IF_GET_PROC_ARGS_is_abstract(...) __VA_ARGS__
#define _STATIC_IF_GET_PROC_NAME_is_signed(...) std::is_signed
#define _STATIC_IF_GET_PROC_ARGS_is_signed(...) __VA_ARGS__
#define _STATIC_IF_GET_PROC_NAME_is_unsigned(...) std::is_unsigned
#define _STATIC_IF_GET_PROC_ARGS_is_unsigned(...) __VA_ARGS__

#define _STATIC_IF_GET_PROC_NAME_is_constructible(...) std::is_constructible
#define _STATIC_IF_GET_PROC_ARGS_is_constructible(...) __VA_ARGS__
#define _STATIC_IF_GET_PROC_NAME_is_default_constructible(...) std::is_default_constructible
#define _STATIC_IF_GET_PROC_ARGS_is_default_constructible(...) __VA_ARGS__
#define _STATIC_IF_GET_PROC_NAME_is_copy_constructible(...) std::is_copy_constructible
#define _STATIC_IF_GET_PROC_ARGS_is_copy_constructible(...) __VA_ARGS__
#define _STATIC_IF_GET_PROC_NAME_is_move_constructible(...) std::is_move_constructible
#define _STATIC_IF_GET_PROC_ARGS_is_move_constructible(...) __VA_ARGS__
#define _STATIC_IF_GET_PROC_NAME_is_assignable(...) std::is_assignable
#define _STATIC_IF_GET_PROC_ARGS_is_assignable(...) __VA_ARGS__
#define _STATIC_IF_GET_PROC_NAME_is_copy_assignable(...) std::is_copy_assignable
#define _STATIC_IF_GET_PROC_ARGS_is_copy_assignable(...) __VA_ARGS__
#define _STATIC_IF_GET_PROC_NAME_is_move_assignable(...) std::is_move_assignable
#define _STATIC_IF_GET_PROC_ARGS_is_move_assignable(...) __VA_ARGS__
#define _STATIC_IF_GET_PROC_NAME_is_destructible(...) std::is_destructible
#define _STATIC_IF_GET_PROC_ARGS_is_destructible(...) __VA_ARGS__
#define _STATIC_IF_GET_PROC_NAME_is_trivially_constructible(...) std::is_trivially_constructible
#define _STATIC_IF_GET_PROC_ARGS_is_trivially_constructible(...) __VA_ARGS__
#define _STATIC_IF_GET_PROC_NAME_is_trivially_default_constructible(...) std::is_trivially_default_constructible
#define _STATIC_IF_GET_PROC_ARGS_is_trivially_default_constructible(...) __VA_ARGS__
#define _STATIC_IF_GET_PROC_NAME_is_trivially_copy_constructible(...) std::is_trivially_copy_constructible
#define _STATIC_IF_GET_PROC_ARGS_is_trivially_copy_constructible(...) __VA_ARGS__
#define _STATIC_IF_GET_PROC_NAME_is_trivially_move_constructible(...) std::is_trivially_move_constructible
#define _STATIC_IF_GET_PROC_ARGS_is_trivially_move_constructible(...) __VA_ARGS__
#define _STATIC_IF_GET_PROC_NAME_is_trivially_assignable(...) std::is_trivially_assignable
#define _STATIC_IF_GET_PROC_ARGS_is_trivially_assignable(...) __VA_ARGS__
#define _STATIC_IF_GET_PROC_NAME_is_trivially_copy_assignable(...) std::is_trivially_copy_assignable
#define _STATIC_IF_GET_PROC_ARGS_is_trivially_copy_assignable(...) __VA_ARGS__
#define _STATIC_IF_GET_PROC_NAME_is_trivially_move_assignable(...) std::is_trivially_move_assignable
#define _STATIC_IF_GET_PROC_ARGS_is_trivially_move_assignable(...) __VA_ARGS__
#define _STATIC_IF_GET_PROC_NAME_is_trivially_destructible(...) std::is_trivially_destructible
#define _STATIC_IF_GET_PROC_ARGS_is_trivially_destructible(...) __VA_ARGS__
#define _STATIC_IF_GET_PROC_NAME_is_nothrow_constructible(...) std::is_nothrow_constructible
#define _STATIC_IF_GET_PROC_ARGS_is_nothrow_constructible(...) __VA_ARGS__
#define _STATIC_IF_GET_PROC_NAME_is_nothrow_default_constructible(...) std::is_nothrow_default_constructible
#define _STATIC_IF_GET_PROC_ARGS_is_nothrow_default_constructible(...) __VA_ARGS__
#define _STATIC_IF_GET_PROC_NAME_is_nothrow_copy_constructible(...) std::is_nothrow_copy_constructible
#define _STATIC_IF_GET_PROC_ARGS_is_nothrow_copy_constructible(...) __VA_ARGS__
#define _STATIC_IF_GET_PROC_NAME_is_nothrow_move_constructible(...) std::is_nothrow_move_constructible
#define _STATIC_IF_GET_PROC_ARGS_is_nothrow_move_constructible(...) __VA_ARGS__
#define _STATIC_IF_GET_PROC_NAME_is_nothrow_assignable(...) std::is_nothrow_assignable
#define _STATIC_IF_GET_PROC_ARGS_is_nothrow_assignable(...) __VA_ARGS__
#define _STATIC_IF_GET_PROC_NAME_is_nothrow_copy_assignable(...) std::is_nothrow_copy_assignable
#define _STATIC_IF_GET_PROC_ARGS_is_nothrow_copy_assignable(...) __VA_ARGS__
#define _STATIC_IF_GET_PROC_NAME_is_nothrow_move_assignable(...) std::is_nothrow_move_assignable
#define _STATIC_IF_GET_PROC_ARGS_is_nothrow_move_assignable(...) __VA_ARGS__
#define _STATIC_IF_GET_PROC_NAME_is_nothrow_destructible(...) std::is_nothrow_destructible
#define _STATIC_IF_GET_PROC_ARGS_is_nothrow_destructible(...) __VA_ARGS__
#define _STATIC_IF_GET_PROC_NAME_has_virtual_destructor(...) std::has_virtual_destructor
#define _STATIC_IF_GET_PROC_ARGS_has_virtual_destructor(...) __VA_ARGS__

#define _STATIC_IF_GET_PROC_NAME_is_same(...) std::is_same
#define _STATIC_IF_GET_PROC_ARGS_is_same(...) __VA_ARGS__
#define _STATIC_IF_GET_PROC_NAME_is_base_of(...) std::is_base_of
#define _STATIC_IF_GET_PROC_ARGS_is_base_of(...) __VA_ARGS__
#define _STATIC_IF_GET_PROC_NAME_is_convertible(...) std::is_convertible
#define _STATIC_IF_GET_PROC_ARGS_is_convertible(...) __VA_ARGS__

// static_if extensions
#define _STATIC_IF_GET_PROC_NAME_userpred(...) ::static_if::detail::userpred
#define _STATIC_IF_GET_PROC_ARGS_userpred(...) __VA_ARGS__

/***************************************************************************/

namespace static_if {
namespace detail {

struct void_type {};

template<typename T>
struct result {
	T value;

	template<class F>
	result &&operator*(const F&) && {
		return std::move(*this);
	}
};

template<typename F, bool enable>
using enable_on_void_return = std::enable_if_t<enable == std::is_same<decltype(std::declval<F>()()), void>::value>;

template<typename F>
auto make_result(F &&calc, enable_on_void_return<F, false>* = 0) {
	return result<std::decay_t<decltype(calc())>>{calc()};
}

template<typename F>
auto make_result(F &&calc, enable_on_void_return<F, true>* = 0) {
	calc();
	return result<void_type>{};
}

template<typename Context>
struct trampoline {
	Context context;

	template<class F>
	auto operator*(F &&f) const {
		return make_result([&]{ return context(f); });
	}
};

struct yes {
	template<class Context>
	auto operator*(Context &&context) const {
		return trampoline<std::decay_t<Context>>{std::forward<Context>(context)};
	}
};

struct no {
	auto operator*(yes) const {
		return yes{};
	}

	template<class F>
	auto operator*(const F&) const {
		return no{};
	}
};

struct extract_result {
	template<typename T>
	auto operator+(result<T> &&x) const {
		return std::move(x.value);
	}

	void operator+(result<void_type> &&) const {}
	void operator+(const no &) const {}
};

auto static_if(std::true_type) {
	return yes{};
}

auto static_if(std::false_type) {
	return no{};
}

} // ns detail
} // ns static_if

/***************************************************************************/
// based on the: http://gustedt.wordpress.com/2010/06/08/detect-empty-macro-arguments

#define _STATIC_IF_ARG16(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, ...) _15
#define _STATIC_IF_HAS_COMMA(...) _STATIC_IF_ARG16(__VA_ARGS__, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0)
#define _STATIC_IF__TRIGGER_PARENTHESIS_(...) ,

#define _STATIC_IF_TUPLE_IS_EMPTY(...) \
	_STATIC_IF__ISEMPTY( \
		/* test if there is just one argument, eventually an empty one */ \
		_STATIC_IF_HAS_COMMA(__VA_ARGS__), \
		/* test if _TRIGGER_PARENTHESIS_ together with the argument adds a comma */ \
		_STATIC_IF_HAS_COMMA(_STATIC_IF__TRIGGER_PARENTHESIS_ __VA_ARGS__), \
		/* test if the argument together with a parenthesis adds a comma */ \
		_STATIC_IF_HAS_COMMA(__VA_ARGS__ (/*empty*/)), \
		/* test if placing it between _TRIGGER_PARENTHESIS_ and the parenthesis adds a comma */ \
		_STATIC_IF_HAS_COMMA(_STATIC_IF__TRIGGER_PARENTHESIS_ __VA_ARGS__ (/*empty*/)) \
	)

#define _STATIC_IF_PASTE5(_0, _1, _2, _3, _4) \
	_0 ## _1 ## _2 ## _3 ## _4

#define _STATIC_IF__ISEMPTY(_0, _1, _2, _3) \
	_STATIC_IF_HAS_COMMA(_STATIC_IF_PASTE5(_STATIC_IF__IS_EMPTY_CASE_, _0, _1, _2, _3))

#define _STATIC_IF__IS_EMPTY_CASE_0001 \
	,

/***************************************************************************/

#define _STATIC_IF_CAPTURE_PASS(r, data, i, elem) \
	BOOST_PP_COMMA_IF(i) elem
#define _STATIC_IF_CAPTURE_PARAMS(r, data, i, elem) \
	BOOST_PP_COMMA_IF(i) auto &elem

#define _STATIC_IF_VARIADIC_FOR_EACH_I_AUX(macro, elems) \
	BOOST_PP_SEQ_FOR_EACH_I(macro, _, elems)

#define _STATIC_IF_VARIADIC_FOR_EACH_I_FOR_EMPTY(macro, ...)

#define _STATIC_IF_VARIADIC_FOR_EACH_I(macro, ...) \
	_STATIC_IF_VARIADIC_FOR_EACH_I_AUX(macro, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__)) \

#define _STATIC_IF_LAMBDA_PREFACE(...) \
	[&](auto &static_if_lambda_preface_long_aux_name) { \
		return static_if_lambda_preface_long_aux_name( \
			BOOST_PP_IF( \
				 _STATIC_IF_TUPLE_IS_EMPTY(__VA_ARGS__) \
				,_STATIC_IF_VARIADIC_FOR_EACH_I_FOR_EMPTY \
				,_STATIC_IF_VARIADIC_FOR_EACH_I \
			)(_STATIC_IF_CAPTURE_PASS, __VA_ARGS__) \
		); \
	} \
	* \
	[]( \
		BOOST_PP_IF( \
			 _STATIC_IF_TUPLE_IS_EMPTY(__VA_ARGS__) \
			,_STATIC_IF_VARIADIC_FOR_EACH_I_FOR_EMPTY \
			,_STATIC_IF_VARIADIC_FOR_EACH_I \
		)(_STATIC_IF_CAPTURE_PARAMS, __VA_ARGS__) \
	)

#define _STATIC_IF_AUX(pred_name, pred_args, ...) \
	::static_if::detail::static_if(pred_name<pred_args>{}) \
		* _STATIC_IF_LAMBDA_PREFACE(__VA_ARGS__)

/***************************************************************************/

#define STATIC_IF(pred, ...) \
	::static_if::detail::extract_result{} + \
	_STATIC_IF_AUX( \
		 BOOST_PP_CAT(_STATIC_IF_GET_PROC_NAME_, pred) \
		,BOOST_PP_CAT(_STATIC_IF_GET_PROC_ARGS_, pred) \
		,__VA_ARGS__ \
	)

#define STATIC_ELSE_IF(pred, ...) \
	* _STATIC_IF_AUX( \
		 BOOST_PP_CAT(_STATIC_IF_GET_PROC_NAME_, pred) \
		,BOOST_PP_CAT(_STATIC_IF_GET_PROC_ARGS_, pred) \
		,__VA_ARGS__ \
	)

#define STATIC_ELSE(...) \
	* ::static_if::detail::yes{} * _STATIC_IF_LAMBDA_PREFACE(__VA_ARGS__)

/***************************************************************************/

#endif // _static_if_hpp__included_
