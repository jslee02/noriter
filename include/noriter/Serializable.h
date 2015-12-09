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

#ifndef NORITER_SERIALIZABLE_H
#define NORITER_SERIALIZABLE_H

#include <cassert>
#include <string>
#include <mutex>

#include "noriter/Property.h"
#include "noriter/Types.h"

#define NORITER_CREATE_PROPERTY_MAP_ONCE(class_name, object_instance)                      \
  class_name class_name##_temp = class_name();                                        \
  std::call_once(mOnceFlag, std::bind(&class_name::createPropertyMap, &class_name##_temp));


namespace nrt {

class PropertyBase;
class PropertyMap;

class Serializable
{
public:

  Serializable();


  virtual void* createPropertyMap();

  const PropertyMap* findPropertyMap() const;

  const PropertyBase* findProperty(const std::string& propertyName) const;

  virtual Serializable* findPropertyTarget(const PropertyBase* property);
//  virtual std::string getPropertyCore(const PropertyBase* property) const;

  virtual std::string getProperty(const std::string& propertyName) = 0;

  virtual std::string getProperty(const PropertyBase* property) = 0;


  ObjectType mObjectType;

protected:

  static Serializable* create(Serializable* derived, std::once_flag& flag);

protected:

  static bool mIsInitialized;

};

template <typename Derived>
class TSerializable : public Serializable
{
public:
  std::string getProperty(const std::string& propertyName) override final
  {

  }

  std::string getProperty(const PropertyBase* property) override final
  {
    // Double check
    //assert(mObjectType == property->getOwnerType());

    if (nullptr == property)
      return std::string();
    // TODO: throw invalid property name exception

    // General implementations
    TPropertyGetterFunction<Derived> getter;
    getter = *static_cast<TPropertyGetterFunction<Derived>*>(property->getPropGetPfn());
    assert(getter.func);

  //  PropertyTraits<ObjectType_::OT_Link>::type a;

    getter.func();

  }
protected:

private:
};

}  // namespace nrt

#endif  // NORITER_SERIALIZABLE_H
