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

#include "noriter/ObjectManager.h"

#include <cassert>
#include <iostream>

#include "noriter/Property.h"

namespace nrt {

bool                        ObjectManager::mIsInitialized   = false;
ObjectManager::CallbackMap* ObjectManager::mObjects         = nullptr;
PropertyMaps*               ObjectManager::mPropertyMaps    = nullptr;

//==============================================================================
void ObjectManager::startup()
{
  if (mIsInitialized == true)
    return;

  mIsInitialized = true;

  std::cout
      << "[ENGINE] ----------------------------------------------------------\n"
      << "[ENGINE] ObjectManager is starting up...\n"
      << "[ENGINE] ----------------------------------------------------------\n";

  std::cout
      << "[ENGINE] ----------------------------------------------------------\n";

}

//=============================================================================
void ObjectManager::cleanup()
{
}

//==============================================================================
bool ObjectManager::isInitialized()
{
  return mIsInitialized;
}

//==============================================================================
ObjectManager::CallbackMap* ObjectManager::getObjectMap()
{
  if (mObjects == nullptr)
    mObjects = new ObjectManager::CallbackMap();

  return mObjects;
}

//==============================================================================
void ObjectManager::registerObject(const std::string& type,
                                   std::function<void*()> _registerFunction)
{
  // mObjects[type] = _registerFunction;

  // If ret.second is true, then name is new key and ret.first is the iterator
  // pointing the new key. If ret.second is false, then reg already has name
  // and ret.first is the iterator point the first key of reg.
  std::pair<CallbackMap::iterator, bool> ret =
      ObjectManager::getObjectMap()->insert(
        CallbackMap::value_type(type, _registerFunction));

  if (ret.second == false)
  {
    // This means there already is a component registered to
    // this name. You should handle this error as you see fit.
    throw;
  }
}

//==============================================================================
void ObjectManager::unregisterObject(const std::string& type)
{
  ObjectManager::getObjectMap()->erase(type);
}

//==============================================================================
void* ObjectManager::createObject(const std::string& type)
{
  ObjectManager::CallbackMap* map = ObjectManager::getObjectMap();
  CallbackMap::iterator it = map->find(type);
  if (it != map->end())
    return (it->second());

  // TODO: throw
  throw;
  return nullptr;
}

//==============================================================================
PropertyMaps* ObjectManager::getPropertyMaps()
{
  if (mPropertyMaps == nullptr)
    mPropertyMaps = new PropertyMaps();

  return mPropertyMaps;
}

}  // namespace nrt

