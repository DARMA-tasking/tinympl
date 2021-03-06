
/*
//@HEADER
// ************************************************************************
//
//                              transpose.hpp                              
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


#ifndef TINYMPL_TRANSPOSE_HPP
#define TINYMPL_TRANSPOSE_HPP

#include "variadic/all_of.hpp"
#include "variadic/at.hpp"
#include "as_sequence.hpp"
#include "is_sequence.hpp"
#include "sequence.hpp"
#include "variadic/all_of.hpp"
#include "size.hpp"
#include "bind.hpp"
#include "equal_to.hpp"
#include "int.hpp"
#include "at.hpp"

namespace tinympl {

/**
 * \ingroup SeqModAlgs
 * \class transpose
 * \brief Transpose a sequence of sequences
 * \param SequenceOfSequences The sequence of sequences which shall be
transposed
 * \param OutOuter The type of the outer output sequence
 * \param OutInner The type of the inner output sequence
 */
template < class SequenceOfSequences,
  template<class ...> class OutOuter =
    as_sequence<SequenceOfSequences>::template rebind,
  template<class ...> class OutInner =
    as_sequence<typename at<0,SequenceOfSequences>::type>::template rebind
>
struct transpose :
  transpose< as_sequence_t<SequenceOfSequences>, OutOuter, OutInner > {};

template< class ... Sequences,
          template<class ...> class OutOuter,
          template<class ...> class OutInner>
class transpose< sequence<Sequences...>, OutOuter, OutInner> {
    static_assert( variadic::all_of<is_sequence, Sequences...>::value,
        "transpose: not all the elements of the main sequence are sequences" );

    static_assert( sizeof...( Sequences ) > 0,
        "transpose is undefined on empty sequences" );

    enum {size = tinympl::size<
            typename variadic::at<0,Sequences...>::type>::value};

    static_assert( variadic::all_of <
                   bind < equal_to, int_<size>,
                   bind<tinympl::size, arg1> >::
                       template eval_value, Sequences...>::value,
                   "transpose: all the sequences must have the same size" );

    template<std::size_t i, class ... Bound>
    struct impl {
        typedef OutInner< typename at<i-1, Sequences>::type ... > cur_t;
        typedef typename impl < i - 1, cur_t, Bound...>::type type;
    };

    template<class ... Bound>
    struct impl<0, Bound...> {
        typedef OutOuter<Bound...> type;
    };

public:
    typedef typename impl<size>::type type;
};

} // namespace tinympl

#endif // TINYMPL_TRANSPOSE_HPP