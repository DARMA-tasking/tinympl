/*
//@HEADER
// ************************************************************************
//
//                          filter.hpp
//                         darma_new
//              Copyright (C) 2017 NTESS, LLC
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

#ifndef SRC_META_TINYMPL_VARIADIC_FILTER_HPP_
#define SRC_META_TINYMPL_VARIADIC_FILTER_HPP_

#include "../join.hpp"

namespace tinympl {
namespace variadic {

template <
  template <class...> class UnaryPredicate,
  template <class...> class Out,
  typename... Types
>
struct filter { };


template <
  template <class...> class UnaryPredicate,
  template <class...> class Out,
  typename Type1, typename... Types
>
struct filter<
  UnaryPredicate, Out, Type1, Types...
> {
  private:
    typedef typename filter<
      UnaryPredicate, Out, Types...
    >::type _filtered_tail;
  public:
    typedef typename std::conditional<
      UnaryPredicate<Type1>::type::value,
      join<Out<Type1>, _filtered_tail>,
      identity<_filtered_tail>
    >::type::type type;
};

template <
  template <class...> class UnaryPredicate,
  template <class...> class Out

>
struct filter<
  UnaryPredicate, Out
> {
  typedef Out<> type;
};

}} // end namespace tinympl::variadic


#endif /* SRC_META_TINYMPL_VARIADIC_FILTER_HPP_ */
