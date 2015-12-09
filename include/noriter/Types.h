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

#ifndef NORITER_TYPES_H
#define NORITER_TYPES_H

namespace nrt {

enum class ObjectType : unsigned int
{
  Link,
  Joint,
  Skeleton
};

enum class PropertyCategory
{
  PropertyCategory1,
  PropertyCategory2,
  PropertyCategory3,
  MISC
};

enum class PropertyType : unsigned int
{
  Normal = 0x00000000,

  GeneralTypeMask = 0x000000FF,
  BehaviorMask    = 0xFF000000,

  ReadOnly        = 0x01000000,
  NotSerializable = 0x02000000,
  DynamicDefVal   = 0x04000000,
  NoSave          = 0x08000000,
  UI_Hidden       = 0x10000000,
  UI_Disabled     = 0x20000000,

  Char            = 0x00000010,
  Byte            = 0x00000011,
  Int32           = 0x00000012,
  UInt32          = 0x00000013,
  Float           = 0x00000014,
  Double          = 0x00000015,
  String          = 0x00000016,

  Vector3d        = 0x00000050,
  Vector6d        = 0x00000051,
  Matrix3d        = 0x00000052,
  Isometry3d      = 0x00000053,
};

enum class PropertyName : unsigned int
{
  Invalid = 0x00000000,


};


}  // namespace nrt

#endif  // NORITER_TYPES_H
