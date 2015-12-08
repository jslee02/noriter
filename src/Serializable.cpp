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

#include "noriter/Serializable.h"

#include <cassert>
#include <iostream>
#include <mutex>

#include "noriter/Property.h"
#include "noriter/ObjectManager.h"

namespace nrt {

bool Serializable::mIsInitialized = false;

//==============================================================================
Serializable* Serializable::create(Serializable* derived, std::once_flag& flag)
{
//  if (!mIsInitialized)
//  {
//    derived->createPropertyMap();
//    mIsInitialized = true;

//  std::call_once(flag, std::bind(&Serializable::createPropertyMap, derived));

//    std::cout << "[Serializable::create] created.\n";
//  }
}

//==============================================================================
void* Serializable::createPropertyMap()
{
  std::cout << "[Serializable::createPropertyMap]\n";
}

//==============================================================================
const PropertyMap* Serializable::findPropertyMap() const
{
  ObjectManager::getPropertyMaps()->find(mObjectType);
}

//==============================================================================
Serializable* Serializable::findPropertyTarget(const PropertyBase* /*property*/)
{
  return this;
}

//==============================================================================
std::string Serializable::getPropertyCore(const PropertyBase* property) const
{
  // Double check
  //assert(mObjectType == property->getOwnerType());

  // General implementations
  PropertyGetterFunction getter;
  getter = property->getPropGetPfn();
  assert(getter);

  getter();
}

//==============================================================================
std::string Serializable::getProperty(const std::string& propertyName)
{

}

//==============================================================================
std::string Serializable::getProperty(const PropertyBase* property)
{
  if (property)
    return findPropertyTarget(property)->getPropertyCore(property);
  else
    return std::string();
    // TODO: throw invalid property name exception
}


}  // namespace nrt

