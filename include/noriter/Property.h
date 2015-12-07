/*
 * Copyright (c) 2011-2015, Georgia Tech Research Corporation
 * All rights reserved.
 *
 * Author(s): Sehoon Ha <sehoon.ha@gmail.com>
 *
 * Georgia Tech Graphics Lab and Humanoid Robotics Lab
 *
 * Directed by Prof. C. Karen Liu and Prof. Mike Stilman
 * <karenliu@cc.gatech.edu> <mstilman@cc.gatech.edu>
 *
 * This file is provided under the following "BSD-style" License:
 *   Redistribution and use in source and binary forms, with or
 *   without modification, are permitted provided that the following
 *   conditions are met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 *   CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 *   INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 *   MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 *   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 *   USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 *   AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *   LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *   ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *   POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef NORITER_PROPERTY_H
#define NORITER_PROPERTY_H

#include <string>

#define NORITER_DECLARE_PROPERTY_MAP(class_name)                               \
  protected:                                                                   \
    virtual void* createPropertyMap();                                         \
    using ThisClass = class_name;

#define NORITER_BEGIN_PROPERTY_MAP(super_class, class_name)                          \
  void* class_name::createPropertyMap()                                        \
  {                                                                            \
    void* propMap = super_class::createPropertyMap();                      \
    if (nullptr == propMap)                                                \
      return nullptr;

#define NORITER_END_PROPERTY_MAP() \
    return propMap; \
  };


namespace nrt {

enum class PropertyCategory
{
  PropertyCategory1,
  PropertyCategory2,
  PropertyCategory3,
  MISC
};

class Property
{
  // static Getter/Setter
  // static Category
  // static Description
  // static DefaultValue
public:
  Property(PropertyCategory category)
  {

  }


};

}  // namespace nrt

#endif  // NORITER_PROPERTY_H
