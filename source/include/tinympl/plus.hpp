
/*
//@HEADER
// ************************************************************************
//
//                                 plus.hpp                                
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


#ifndef TINYMPL_PLUS_HPP
#define TINYMPL_PLUS_HPP

#include <type_traits>

namespace tinympl {

/**
 * \ingroup Arithmetic
 * \class plus
 * \brief Sums its arguments
 * \return `plus<Args...>::type` is a `std::integral_constant<T,v>` where `T` is the common type between the `Args::type...` and `v` is the sum of `Args::value ... `
 */
template<class ... Args> struct plus;
template<class Head,class ... Tail>
struct plus<Head,Tail...>
  : public plus<Head, typename plus<Tail...>::type> {};

template<class A, class B>
struct plus<A, B>
  : public std::integral_constant<
      typename std::common_type<
        typename A::value_type,
        typename B::value_type
      >::type,
      A::value + B::value
    >
{};

template<class Head> struct plus<Head> : std::integral_constant<typename Head::value_type,Head::value> {};

template <typename... Args>
using plus_t = typename plus<Args...>::type;

} // namespace tinympl

#endif // TINYMPL_PLUS_HPP
