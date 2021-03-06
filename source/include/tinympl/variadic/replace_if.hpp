/*
//@HEADER
// ************************************************************************
//
//                              replace_if.hpp                             
//                         darma_mockup
//              Copyright (C) 2015 Sandia Corporation
// This file was adapted from its original form in the tinympl library.
// The original file bore the following copyright:
//   Copyright (C) 2013, Ennio Barbaro.
// See LEGAL.md for more information.
//
// Under the terms of Contract DE-NA-0003525 with NTESS, LLC,
// the U.S. Government retains certain rights in this software.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
// 1. Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
//
// 3. Neither the name of the Corporation nor the names of the
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY SANDIA CORPORATION "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL SANDIA CORPORATION OR THE
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Questions? Contact darma@sandia.gov
//
// ************************************************************************
//@HEADER
*/


#ifndef TINYMPL_VARIADIC_REPLACE_IF_HPP
#define TINYMPL_VARIADIC_REPLACE_IF_HPP

#include <type_traits>

namespace tinympl {
namespace variadic {

/**
 * \ingroup VarModAlgs
 * \class replace_if
 * \brief Replace all the elements in the input sequence which satisfy a given
predicate with a given type T
 * \param F The predicate, `F<T>::type::value` must be convertible to bool
 * \param T The type used to replace the types
 * \param Out The type of the output sequence, defaults to the same kind of the
input sequence
 * \param Args... The input sequence
 * \return `replace_if<...>::type` is a type templated from `Out`
 * \sa tinympl::replace_if
 */
template<template<class ... T> class F,
        class T,
        template<class ...> class Out,
        class ... Args> struct replace_if;

template<template<class ... T> class F,
        class T,
        template<class ...> class Out,
        class Head,
        class ... Tail>
struct replace_if<F, T, Out, Head, Tail...> {
private:
    template<class ... CopiedElements>
    struct impl {
        typedef typename replace_if<F, T, Out, Tail...>::template
            impl <CopiedElements...,
                typename std::conditional <
                    F<Head>::type::value,
                    T,
                    Head >::type
                >::type type;
    };

    template<
        template<class ...> class,
        typename,
        template<class...> class,
        class ...> friend struct replace_if;

public:
    typedef typename impl<>::type type;
};

template<template<class ... T> class F, class T, template<class ...> class Out>
struct replace_if<F, T, Out> {
private:
    template<class ... CopiedElements>
    struct impl {
        typedef Out<CopiedElements...> type;
    };

    template<template<class ...> class,
            typename,
            template<class...> class,
            class ...> friend struct replace_if;

public:
    typedef typename impl<>::type type;
};

} // namespace variadic
} // namespace tinympl

#endif // TINYMPL_VARIADIC_REPLACE_IF_HPP