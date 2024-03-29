/*
 * Copyright (c) 1997    -zorjen122
 * Silicon Graphics Computer Systems, Inc.
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Silicon Graphics makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 */


#pragma once

#define TYPE_TRAITS_INTEGRAL_H 
#ifdef TYPE_TRAITS_INTEGRAL_H 

#include "integral.h"
#include <cstddef>


namespace zampl {

    namespace Tvcheck {
        template<class T>
        struct add_lvalue_reference { using type = T&; };
        template<class T> struct add_lvalue_reference<T&> { using type = T&; };

        template<> struct add_lvalue_reference<void> { using type = void; };
        template<> struct add_lvalue_reference<const void> { using type = const void; };
        template<> struct add_lvalue_reference<volatile void> { using type = volatile void; };
        template<> struct add_lvalue_reference<const volatile void> { using type = const volatile void; };

        template<class _Ty>struct add_value_reference : public add_lvalue_reference<_Ty> {
            using Lvalue = _Ty;     using Rvalue = _Ty;
        };
        template<class _Ty>struct add_value_reference<_Ty&> {
            using Lvalue = _Ty&;     using Rvalue = _Ty&&;
        };

        template<class _Ty>
        using add_rvalue_reference_t = typename add_value_reference<_Ty>::Rvalue;
        template<class _Ty>
        using add_lvalue_reference_t = typename add_value_reference<_Ty>::Lvalue;


        template<class _Ty>    struct dereference {};
        template<class _Ty>    struct dereference<_Ty*> { using type = _Ty; };
        template<class _Ty>    using dereference_t = typename dereference<_Ty>::type;


        template<typename _Tp>
        struct remove_cv { using type = _Tp; };
        template<typename _Tp>
        struct remove_cv<const _Tp> { using type = _Tp; };
        template<typename _Tp>
        struct remove_cv<volatile _Tp> { using type = _Tp; };
        template<typename _Tp>
        struct remove_cv<const volatile _Tp> { using type = _Tp; };


        template<class _Ty>   struct remove_reference { using type = _Ty; };
        template<class _Ty>   struct remove_reference<_Ty&> { using type = _Ty; };
        template<class _Ty>   struct remove_reference<_Ty&&> { using type = _Ty; };

        template<class _Ty>
        using remove_reference_t = typename remove_reference<_Ty>::type;


    // reference
        template<class _Tp> struct is_lvalue_reference
            : public false_type { };

        template<class _Tp>
        struct is_lvalue_reference<_Tp&>
            : public true_type { };

        template<class _Ty>
        struct is_reference
            : public false_type {};

        template<class _Ty>
        struct is_reference<_Ty&>
            : public true_type {};


    // pointer
        template<class _Ty>
        struct is_pointer
            : public false_type {};

        template<class _Ty>
        struct is_pointer<_Ty*>
            : public true_type {};


    // void
        template<class _Ty>
        struct is_void
            : public false_type {};

        template<>
        struct is_void<void>
            : public true_type {};


    // volatile
        template<class _Ty>
        struct is_volatile
            : public false_type {};

        template<class _Ty>
        struct is_volatile<_Ty volatile>

            : public true_type {};


        # ifdef __cpp_char8_t
        #  define _GLIBCXX_USE_CHAR8_T 1
        # endif

    // integral type
        template<typename>
        struct __is_integral_helper
            : public false_type { };

        template<>
        struct __is_integral_helper<bool>
            : public true_type { };

        template<>
        struct __is_integral_helper<char>
            : public true_type { };

        template<>
        struct __is_integral_helper<signed char>
            : public true_type { };

        template<>
        struct __is_integral_helper<unsigned char>
            : public true_type { };


        // We want is_integral<wchar_t> to be true (and make_signed/unsigned to work)
            // even when libc doesn't provide working <wchar.h> and related functions,
            // so don't check _GLIBCXX_USE_WCHAR_T here.

        template<>
        struct __is_integral_helper<wchar_t>
            : public true_type { };

        #ifdef _GLIBCXX_USE_CHAR8_T
        template<>
        struct __is_integral_helper<char8_t>
            : public true_type { };
        #endif

        template<>
        struct __is_integral_helper<char16_t>
            : public true_type { };

        template<>
        struct __is_integral_helper<char32_t>
            : public true_type { };


      // number type
        template<>
        struct __is_integral_helper<short>
            : public true_type { };

        template<>
        struct __is_integral_helper<unsigned short>
            : public true_type { };

        template<>
        struct __is_integral_helper<int>
            : public true_type { };

        template<>
        struct __is_integral_helper<unsigned int>
            : public true_type { };

        template<>
        struct __is_integral_helper<long>
            : public true_type { };

        template<>
        struct __is_integral_helper<unsigned long>
            : public true_type { };

        template<>
        struct __is_integral_helper<long long>
            : public true_type { };

        template<>
        struct __is_integral_helper<unsigned long long>
            : public true_type { };


    // float type
        template<class>
        struct is_floating_point_cv
            : public false_type { };

        template<>
        struct is_floating_point_cv<float>
            : public true_type { };

        template<>
        struct is_floating_point_cv<double>
            : public true_type { };

        template<>
        struct is_floating_point_cv<long double>
            : public true_type { };

        template<class _Ty>
        struct is_floating_point
            : is_floating_point_cv<typename remove_cv<_Ty>::type> {};


    // null
        template<class> struct __is_null_pointer_helper : public false_type {};

        template<>
        struct __is_null_pointer_helper<::std::nullptr_t>
            : public true_type {};

        template<class _Ty>
        struct is_null_pointer
            : public __is_null_pointer_helper<typename remove_cv<_Ty>::type>::type
        { };


    // member
        template<class>
        struct is_member_pointer :public false_type {};

        template<class _Ty, class _Cy>
        struct is_member_pointer<_Ty _Cy::*> :true_type {};


    // array
        template<class _Ty>
        struct is_array :public false_type {};

        template<class _Ty>
        struct is_array<_Ty[]>
            :public true_type {};

        template<class _Ty, size_t _sz>
        struct is_array<_Ty[_sz]>
            :public true_type {};



        template<class _Ty>
        struct is_integral : public __is_integral_helper<_Ty> {};


        template<class _Ty>
        using is_intergral_pointer = is_integral<dereference_t<_Ty>>;

        template<class _Ty>
        using is_integral_t = typename is_integral<_Ty>::type;


        template<class _Ty>
        constexpr bool is_integral_v = is_integral_t<_Ty>::value;

        template<class _Ty>
        constexpr bool is_reference_v = is_pointer<_Ty>::value;

        template<class _Ty>
        constexpr bool is_pointer_v = is_pointer<_Ty>::value;


        template<class _Ty>
        struct is_arithmetic
            : public calc::or_<is_integral<_Ty>, is_floating_point<_Ty>>::type
        { };

        template<class _Ty>
        struct is_scalar
            : public calc::or_<is_arithmetic<_Ty>, /* non-define is_enum<_Ty> ,*/is_pointer<_Ty>,
            is_member_pointer<_Ty>, is_null_pointer<_Ty>>::type
        { };


        //  Always_false tells here that instantiation of the object is prohibited, 
        //  and only the object can be accessed, because the (meta-function) of the function at compile time.
        template<class> constexpr bool __always_false = false;
        template<class _Ty> add_rvalue_reference_t<_Ty> declval() noexcept {
            static_assert(__always_false<_Ty>, "Calling declval is ill-formed, see N4892 [declval]/2.");
        }

    };


};              //*     namesapce mpls

#endif          //*     TYPE_TRAITS_INTEGRAL_H 