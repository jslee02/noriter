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

#ifndef NORITER_PROPERTY_H
#define NORITER_PROPERTY_H

#include <string>
#include <functional>
#include <vector>
#include <map>
#include <type_traits>
#include <utility>

#include "noriter/Types.h"

#define NORITER_DECLARE_PROPERTY_MAP(class_name)                               \
  protected:                                                                   \
  virtual void* createPropertyMap();                                         \
  using ThisClass = class_name;                                              \
  static std::once_flag mOnceFlag;                                          \
  static std::once_flag mOnceFlagFactoryRegister;

#define NORITER_BEGIN_PROPERTY_MAP(super_class, class_name)                    \
  std::once_flag class_name::mOnceFlag;                                        \
  void* class_name::createPropertyMap()                                        \
{                                                                            \
  void* propMap = super_class::createPropertyMap();                          \
  if (nullptr == propMap)                                                    \
  return nullptr;

#define NORITER_PROPERTY(name, type, defval, opt_types)                                       \
  __if_exists(g_debugCurProp)                                                               \
{                                                                                         \
  g_debugCurProp = _T(#name);                                                             \
  }                                                                                         \
  pCompProp->InsertProperty(new XProperty(cate, PropertyName::name,                         \
  PropertyType::type | (opt_types),                                                         \
  (PFN_XPROPGET)(static_cast< ARG##type (XObject::*)( void ) > (&ThisClass::get_##name)),   \
  \
  __if_exists(ThisClass::set_##name)                                                        \
{                                                                                         \
  (PFN_XPROPSET)(static_cast< void (XObject::*)( ARG##type ) > (&ThisClass::set_##name)), \
  }                                                                                         \
  __if_not_exists(ThisClass::set_##name)                                                    \
{                                                                                         \
  nullptr,                                                                                \
  }                                                                                         \
  type##Traits::ToString(defval), m_eObjectType));

#define NORITER_END_PROPERTY_MAP() \
  return propMap; \
  };

namespace nrt {




//#define NORITER_ENUM_TO_TYPE(enum_name)\
//  using enum_name =

//template <ObjectEnumType I>
//struct Int2Type
//{
//  static const int value = I;
//};

//template <DataEnumType I>
//struct Data2Type
//{
//  static const std::underlying_type<DataEnumType>::type value = I;
//};

//using IntEnumType = Int2Type<ObjectEnumType::Link>;

//using Vector2dEnumType = Data2Type<DataEnumType::Vector2d>;

template<unsigned int T>
struct type_temp {};

template<ObjectType T>
struct PropertyTraits {};

class Link;

template<>
struct PropertyTraits<ObjectType::Link>
{
  using type = Link;
};

using ObjectTypes = std::vector<ObjectType>;

struct PropertyGetterFunction {};
struct PropertySetterFunction {};

template <typename ArgType>
struct TPropertyGetterFunction : PropertyGetterFunction
{
  using func_type = std::function<const ArgType&(void)>;

  func_type func;
};

template <typename ArgType>
struct TPropertySetterFunction : PropertySetterFunction
{
  using func_type = std::function<void(const ArgType&)>;

  func_type func;
};

class PropertyBase
{
  // static Getter/Setter
  // static Category
  // static Description
  // static DefaultValue
public:
  PropertyBase(PropertyCategory category)
  {

  }

  PropertyGetterFunction* getPropGetPfn() const { return mGetFnc; }

  //protected:
public:
  PropertyGetterFunction* mGetFnc;
  PropertySetterFunction* mSetFnc;
  PropertyCategory mCategroy;
  PropertyName mName;
  std::string mDefaultString;

};



template<typename T>
class Property : public PropertyBase
{
public:
  TPropertyGetterFunction<T>* mTGetFnc;
  TPropertySetterFunction<T>* mTSetFnc;
};

class Properties : public std::vector<const PropertyBase*>
{
public:
};

class PropertyMap : public std::map<PropertyName, PropertyBase*>
{
public:

  PropertyBase* findProperty(const PropertyName& propertyName) const;

protected:

};

class PropertyMaps
{
public:
  const PropertyMap* find(const ObjectType& objectType) const;

private:
  std::map<ObjectType,  const PropertyMap*> mMap1;
  std::map<ObjectTypes, const PropertyMap*> mMap2;

};


}  // namespace nrt

#endif  // NORITER_PROPERTY_H
