//
// Copyright (c) 2015, Jeongseok Lee <jslee02@gmail.com>
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
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
//

#ifndef NORITER_ENUMERATORHELPERS_H
#define NORITER_ENUMERATORHELPERS_H

#include <string>
#include "noriter/SfinaeTest.h"

#define XENUM_BEGIN_NAMESPACE      namespace nrt {
#define XENUM_END_NAMESPACE        }
#define XENUM_USING_NAMESPACE      using namespace enum_detail;

XENUM_BEGIN_NAMESPACE
enum TraitString
{
  traitDef  = 0x0001,
  traitAux  = 0x0002,
  traitRes  = 0x0004,
  traitAuto  = 0x0008,

  traitAuxNonUnique = 0x0020,
  traitResNonUnique = 0x0040,
  traitAllUnique    = 0x0080,
};
XENUM_END_NAMESPACE

//==============================================================================
// For value only enumerations, no traits support
//==============================================================================
#define XENUM_DEFINE(enum_name)\
  XENUM_BEGIN_VAL(enum_name)\
    XENUM_##enum_name(XENUM_VAL)\
  XENUM_END_VAL(enum_name)

//==============================================================================
// For value only enumerations, no traits support
//==============================================================================
#define XENUM_DEF   // Default string only(Name + Integer value)
#define XENUM_AUX   // Default string and auxiliary string(XENUM_DEF + XML String)
#define XENUM_RES   // Default string and resource string(XENUM_DEF + Resource String)
#define XENUM_ALL   // All three strings

#define XENUM_AUX_NON_UNIQUE (traitAuxNonUnique)
#define XENUM_RES_NON_UNIQUE (traitResNonUnique)
#define XENUM_ALL_UNIQUE     (traitAllUnique)
#define XENUM_RES_NOT_DEFINED()
#define XENUM_DEFAULT        (0xFFFFFFFF)

#define XENUM_DEFINE_TRAITS(enum_name, supported_strings, options)\
  XENUM_BEGIN_VAL(enum_name)\
    XENUM_##enum_name(supported_strings##_V)\
  XENUM_END_VAL(enum_name)\
  XENUM_BEGIN_T_##supported_strings(enum_name, options)\
    XENUM_##enum_name(supported_strings##_T)\
  XENUM_END_T_##supported_strings(enum_name)

//==============================================================================
// Enumeration macros for value
//==============================================================================
#define _XENUM_BEGIN_VAL(name)            \
  XENUM_BEGIN_NAMESPACE                   \
  namespace tag##name {                   \
    enum Enum {

#define _XENUM_VAL(element, value)        \
      element = (value),

#define _XENUM_END_VAL(name)              \
    };                                    \
  };                                      \
  namespace _StringPools { class name; }; \
  namespace _MaskPools { class name; };   \
  using name = tag##name::Enum;           \
  using ARG##name = name;                 \
  XENUM_END_NAMESPACE

#define XENUM_BEGIN_VAL(name)                   _XENUM_BEGIN_VAL(name)

#define XENUM_VAL(element, value)               _XENUM_VAL(element, value)
#define XENUM_DEF_V(element, value)             _XENUM_VAL(element, value)
#define XENUM_AUX_V(element, value, aux)        _XENUM_VAL(element, value)
#define XENUM_RES_V(element, value, resid)      _XENUM_VAL(element, value)
#define XENUM_ALL_V(element, value, aux, resid) _XENUM_VAL(element, value)

#define XENUM_END_VAL(name)                     _XENUM_END_VAL(name)

//==============================================================================
// Enumeration macros for string-value pairs
//==============================================================================
#define _XENUM_BEGIN_TRAITS(name, flags)                          \
  XENUM_BEGIN_NAMESPACE                                           \
  class name##Traits :                                            \
    public XEnumTraitsBase<name##Traits, tag##name::Enum,         \
      _StringPools::name, _MaskPools::name>                       \
  {                                                               \
  };                                                              \
  class _StringPools::name :                                      \
    public XEnumStringPoolT<tag##name::Enum, _StringPools::name>  \
  {                                                               \
  public:                                                         \
    static CHUNK& GetChunk() {                                    \
      DWORD dwFlags = flags;                                      \
      static PAIR* pairs[] = {

#define _XENUM_END_TRAITS(name)                      \
        NULL                          \
      };                              \
      static CHUNK chunk(_T(#name), pairs, dwFlags);        \
      return chunk;                        \
    }                                \
  };                                  \
  XENUM_END_NAMESPACE


#define XENUM_BEGIN_T_XENUM_DEF(name, options)    _XENUM_BEGIN_TRAITS(name, traitDef|(options))
#define XENUM_BEGIN_T_XENUM_AUX(name, options)    _XENUM_BEGIN_TRAITS(name, traitDef|traitAux|(options))
#define XENUM_BEGIN_T_XENUM_RES(name, options)    _XENUM_BEGIN_TRAITS(name, traitDef|traitRes|(options))
#define XENUM_BEGIN_T_XENUM_ALL(name, options)    _XENUM_BEGIN_TRAITS(name, traitDef|traitAux|traitRes|(options))

#define XENUM_DEF_T(element, value)          new PAIR(_T(#element), value),
#define XENUM_AUX_T(element, value, aux)      new PAIR_AUX(_T(#element), value, (PCTSTR)(UINT_PTR)aux),
#define XENUM_RES_T(element, value, resid)      new PAIR_AUX_RES(_T(#element), value, (PCTSTR)NULL, resid),
#define XENUM_ALL_T(element, value, aux, resid)    new PAIR_AUX_RES(_T(#element), value, (PCTSTR)(UINT_PTR)aux, resid),

#define XENUM_END_T_XENUM_DEF(name)          _XENUM_END_TRAITS(name)
#define XENUM_END_T_XENUM_AUX(name)          _XENUM_END_TRAITS(name)
#define XENUM_END_T_XENUM_RES(name)          _XENUM_END_TRAITS(name)
#define XENUM_END_T_XENUM_ALL(name)          _XENUM_END_TRAITS(name)

//==============================================================================
// XEnumTraitsBase Interface
//   SP: String Pool, MP: Mask Pool
//==============================================================================

#define __if_exists(expression)\
  if (true)

#define __if_not_exists(expression)\
  if (true)

XENUM_BEGIN_NAMESPACE
template< typename TBase, typename E, typename SP, typename MP >
class XEnumTraitsBase
{
public:
  static std::string ToString(E val, TraitString type = traitDef) throw()
  {
    try
    {
      __if_exists(MP::ToString)
      {
        return MP::ToString(val, type);
      }
      __if_not_exists(MP::ToString)
      {
        return SP::ToString(val, type);
      }
    }
    catch (std::exception* e)
    {
      throw e;
    }
  }

  static std::string ToResourceString(E val) throw(){
    try{
      __if_exists(MP::ToString){
        return MP::ToString(val, traitRes);
      }
      __if_not_exists(MP::ToString){
        return SP::ToString(val, traitRes);
      }
    }catch (std::exception* e){
      throw e;
    }
  }

  static std::string ToAuxString(E val) throw()
  {
    try
    {
      __if_exists(MP::ToString){
        return MP::ToString(val, traitAux);
      }
      __if_not_exists(MP::ToString){
        return SP::ToString(val, traitAux);
      }
    }
    catch
    (std::exception* e)
    {
      throw e;
    }
  }


  static E FromString(const std::string& str, TraitString type = traitDef) throw(){
    try{
      __if_not_exists(MP::FromString)
      {
        return static_cast<E>(MP::FromString(str, type));
      }
      __if_not_exists(MP::FromString)
      {
        return static_cast<E>(SP::FromString(str, type));
      }
    }catch (std::exception* e){
      throw e;
    }
  }


  static bool ValidateString(const std::string& str, TraitString type = traitDef)
  {
    __if_exists(MP::FromString){
      return MP::IsElement(str, type);
    }
    __if_not_exists(MP::FromString){
      return SP::IsElement(str, type);
    }
  }

  static bool ValidateValue(E val){
    __if_exists(MP::IsElement){
      return MP::IsElement(val);
    }
    __if_not_exists(MP::FromString){
      return SP::IsElement(val);
    }
  }



  // For string enumeration
public:
  static int GetCardinality()
  {
    return SP::GetChunk().m_nCount;
  }

  static const std::string& GetElementString(int nIndex, TraitString type = traitDef)
  {
    assert(nIndex >= 0 && nIndex < GetCardinality());
    return (SP::GetChunk().m_ppPairs)[nIndex]->GetString(type);
  }

  static int GetElementValue(int nIndex)
  {
    assert(nIndex >= 0 && nIndex < GetCardinality());
    return (SP::GetChunk().m_ppPairs)[nIndex]->val;
  }



  // Interface support
//protected:
//  class IXEnumTraitsImpl : public IXEnumTraits
//  {
//  public:
//    virtual String ToString(int val, TraitString type = traitDef) throw(...){
//      return XEnumTraitsBase<TBase, E, SP, MP>::ToString((E)val, type);
//    }

//    virtual int FromString(ARGString str, TraitString type = traitDef) throw(...){
//      return (int)XEnumTraitsBase<TBase, E, SP, MP>::FromString(str, type);
//    }
//  };


//public:
//  static IXEnumTraits* GetInterface(){
//    static IXEnumTraitsImpl impl;
//    return &impl;
//  }
};
XENUM_END_NAMESPACE


namespace nrt {

template <typename E>
constexpr typename std::underlying_type<E>::type to_underlying(E e)
{
  return static_cast<typename std::underlying_type<E>::type>(e);
}

} // namespace nrt

#endif  // NORITER_ENUMERATORHELPERS_H

