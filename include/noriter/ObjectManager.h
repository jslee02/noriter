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

#ifndef NORITER_OBJECTMANAGER_H
#define NORITER_OBJECTMANAGER_H

#include <functional>
#include <map>

namespace nrt {

class PropertyMap;
class PropertyMaps;

class ObjectManager
{
public:

  static void startup();

  static void cleanup();

  static bool isInitialized();

  using CallbackMap= std::map<std::string, std::function<void*()>>;

  static CallbackMap* getObjectMap();

  static void registerObject(const std::string& type,
                             std::function<void*()> _registerFunction);

  static void unregisterObject(const std::string& type);

  static void* createObject(const std::string& type);

  static PropertyMaps* getPropertyMaps();

private:

  static bool mIsInitialized;

  static PropertyMaps* mPropertyMaps;

  static CallbackMap* mObjects;

private:

  /// Constructor
  ObjectManager() {}

  /// Destructor
  virtual ~ObjectManager() {}

};

}  // namespace nrt

#endif
