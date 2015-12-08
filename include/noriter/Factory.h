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

#ifndef NORITER_FACTORY_H
#define NORITER_FACTORY_H

#include <map>
#include <string>
#include <functional>

namespace nrt {

template <typename KeyType, typename Base>
class Factory
{
public:

  using ObjectMap = std::map<KeyType, std::function<Base*()>>;

  static typename ObjectMap::iterator registerObject(
      const KeyType& key, const std::function<Base*()>& func)
  {
    return getMap().insert(std::make_pair(key, func)).first;
  }

  static void unregisterObject(const KeyType& key)
  {
    getMap().erase(key);
  }

  static Base* create(const KeyType& key)
  {
    const auto it = getMap().find(key);

    const bool found = (it != getMap().end());
    if (!found)
      return nullptr;

    return it->second();
  }

protected:

  Factory() = default;
  ~Factory() = default;

  static ObjectMap& getMap()
  {
    static ObjectMap map;
    return map;
  }

};

template <typename KeyType, typename Base, typename Derived>
class FactoryRegister final
{
public:

  static FactoryRegister<KeyType, Base, Derived>& getInstance(const KeyType& key)
  {
    static FactoryRegister<KeyType, Base, Derived> instance(key);

    return instance;
  }

private:

  FactoryRegister(const KeyType& key)
  {
    Factory<KeyType, Base>::registerObject(
          key, [](void) -> Base* { return new Derived(); });
  }

  FactoryRegister(const FactoryRegister<KeyType, Base, Derived>&) = delete;
  FactoryRegister& operator=(const FactoryRegister<KeyType, Base, Derived>&) = delete;

};

template <typename Enum, typename Base, typename Derived>
class FactoryUnregister final
{
public:

  FactoryUnregister(const Enum& key)
  {
    Factory<Enum, Base>::unregisterObject(key);
  }

private:

  FactoryUnregister(const FactoryRegister<Enum, Base, Derived>&) = delete;
  FactoryUnregister& operator=(const FactoryRegister<Enum, Base, Derived>&) = delete;

};

template <typename Enum, typename Base, typename Derived>
class FactoryScopedRegister final
{
public:

  FactoryScopedRegister(const Enum& key)
  {
    mPosition = Factory<Enum, Base>::registerObject(
          key, [](void) -> Base* { return new Derived(); });
  }

  ~FactoryScopedRegister()
  {
    Factory<Enum, Base>::getMap().erase(mPosition);
  }

private:

  FactoryScopedRegister(const FactoryRegister<Enum, Base, Derived>&) = delete;
  FactoryScopedRegister& operator=(const FactoryRegister<Enum, Base, Derived>&) = delete;

  typename Factory<Enum, Base>::ObjectMap::iterator mPosition;

};

} // namespace nrt

#define NORITER_REGISTER_OBJECT_TO_FACTORY(key_type, key, base, derived) \
  namespace {                                                            \
  const FactoryRegister<key_type, base, derived>&                        \
  factory_register_##__LINE__                                            \
    = FactoryRegister<key_type, base, derived>::getInstance(key);        \
  }

#define NORITER_UNREGISTER_OBJECT_TO_FACTORY(key_type, key)              \
  namespace {                                                            \
  const FactoryUnregister<key_type, base, derived>&                      \
  factory_unregister_##__LINE__                                          \
    = FactoryUnregister<key_type, base, derived>::getInstance(key);      \
  }

#endif  // _DART5_FACTORY_H_
