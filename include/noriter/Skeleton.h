#ifndef NORITER_SKELETON_H
#define NORITER_SKELETON_H

#include "noriter/Property.h"

namespace nrt {

class Object
{
public:
  Object() = default;

  virtual void* createPropertyMap() {}
};

class Skeleton : public Object
{
public:

  NORITER_DECLARE_PROPERTY_MAP(Skeleton)

  Skeleton() : Object()
  {
  }

};

}  // namespace nrt

#endif  // NORITER_SKELETON_H
