/*
//@HEADER
// ************************************************************************
//
//                              left_fold.hpp                              
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


#ifndef TINYMPL_VARIADIC_LEFT_FOLD_HPP
#define TINYMPL_VARIADIC_LEFT_FOLD_HPP

namespace tinympl {
namespace variadic {

/**
 * \ingroup VarFold
 * \class left_fold
 * \brief Collapses a sequence starting from left using a functor.
 * \param F The functor; `F<T,U>` must be a valid expression
 * \param Args... The input sequence
 * \return A type which is the result of `F( ... F(F(A1,A2),A3) .. )`
 * \sa tinympl::left_fold
 */
template<template<class ...> class Op, class ... Args> struct left_fold;

template<template<class ...> class Op, class Head, class Next, class ... Tail>
struct left_fold<Op, Head, Next, Tail...> {
    typedef typename left_fold <
        Op,
        typename Op<Head, Next>::type,
        Tail... >::type type;
};

template<template<class ...> class Op, typename T>
struct left_fold<Op, T> {
    typedef T type;
};

} // namespace variadic
} // namespace tinympl

#endif // TINYMPL_VARIADIC_LEFT_FOLD_HPP