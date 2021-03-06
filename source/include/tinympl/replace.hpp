
/*
//@HEADER
// ************************************************************************
//
//                               replace.hpp                               
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


#ifndef TINYMPL_REPLACE_HPP
#define TINYMPL_REPLACE_HPP

#include "variadic/replace.hpp"
#include "as_sequence.hpp"
#include "sequence.hpp"

namespace tinympl {

/**
 * \ingroup SeqModAlgs
 * \class replace
 * \brief Replace all the elements in the input sequence equal to *Old* with
*New*
 * \param SequenceIn The input sequence
 * \param Old The type to be replaced
 * \param New The new type
 * \param Out The type of the output sequence, defaults to the same kind of the
input sequence
 * \return `replace<...>::type` is a type templated from `Out`
 * \note The comparison is done with \ref tinympl::equal_to - it can be
specialized
 * \sa variadic::replace
 */
template<class SequenceIn,
        class Old,
        class New,
        template<class ...> class Out =
            as_sequence<SequenceIn>::template rebind>
struct replace : replace<as_sequence_t<SequenceIn>, Old, New, Out> {};

template<class Old, class New, template<class ...> class Out, class ... Args>
struct replace<sequence<Args...>, Old, New, Out> :
    variadic::replace<Old, New, Out, Args...> {};

} // namespace tinympl

#endif // TINYMPL_REPLACE_HPP