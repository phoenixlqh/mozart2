// Copyright © 2011, Université catholique de Louvain
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// *  Redistributions of source code must retain the above copyright notice,
//    this list of conditions and the following disclaimer.
// *  Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#ifndef __ARRAY_DECL_H
#define __ARRAY_DECL_H

#include "mozartcore-decl.hh"

#include "datatypeshelpers-decl.hh"

namespace mozart {

///////////
// Array //
///////////

#ifndef MOZART_GENERATOR
#include "Array-implem-decl.hh"
#endif

/**
 * Array
 */
class Array: public DataType<Array>, public WithHome,
  public IntegerDottableHelper<Array>,
  StoredWithArrayOf<UnstableNode> {
public:
  typedef SelfType<Array>::Self Self;
public:
  static atom_t getTypeAtom(VM vm) {
    return vm->getAtom(MOZART_STR("array"));
  }

  inline
  Array(VM vm, size_t width, StaticArray<UnstableNode> _elements,
        nativeint low, RichNode initValue);

  inline
  Array(VM vm, size_t width, StaticArray<UnstableNode> _elements,
        GR gr, Self from);

public:
  size_t getArraySize() {
    return _width;
  }

  size_t getWidth() {
    return _width;
  }

  nativeint getLow() {
    return _low;
  }

  nativeint getHigh() {
    return _low + _width - 1;
  }

protected:
  friend class IntegerDottableHelper<Array>;

  bool isValidFeature(Self self, VM vm, nativeint feature) {
    return isIndexInRange(feature);
  }

  inline
  UnstableNode getValueAt(Self self, VM vm, nativeint feature);

public:
  // DotAssignable interface

  void dotAssign(Self self, VM vm, RichNode feature, RichNode newValue) {
    return arrayPut(self, vm, feature, newValue);
  }

  UnstableNode dotExchange(Self self, VM vm, RichNode feature,
                           RichNode newValue) {
    return arrayExchange(self, vm, feature, newValue);
  }

public:
  // ArrayLike interface

  bool isArray(Self self, VM vm) {
    return true;
  }

  inline
  UnstableNode arrayLow(Self self, VM vm);

  inline
  UnstableNode arrayHigh(Self self, VM vm);

  inline
  UnstableNode arrayGet(Self self, VM vm, RichNode index);

  inline
  void arrayPut(Self self, VM vm, RichNode index, RichNode value);

  inline
  UnstableNode arrayExchange(Self self, VM vm, RichNode index,
                             RichNode newValue);

private:
  inline
  size_t getOffset(Self self, VM vm, RichNode index);

  bool isIndexInRange(nativeint index) {
    return (index >= getLow()) && (index <= getHigh());
  }

  size_t indexToOffset(nativeint index) {
    assert(isIndexInRange(index));
    return (size_t) (index - _low);
  }

public:
  inline
  void printReprToStream(Self self, VM vm, std::ostream& out, int depth);

private:
  size_t _width;
  nativeint _low;
};

#ifndef MOZART_GENERATOR
#include "Array-implem-decl-after.hh"
#endif

}

#endif // __ARRAY_DECL_H
