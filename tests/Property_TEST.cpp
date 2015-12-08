#include <gtest/gtest.h>

#include "noriter/noriter.h"

using namespace nrt;

//==============================================================================
TEST(Property, Basic)
{
  Skeleton* skel1 = Skeleton::create();
  Skeleton* skel2 = Skeleton::create();
  Skeleton* skel3 = Skeleton::create();
  Skeleton* skel4 = Skeleton::create();
  Skeleton* skel5 = Skeleton::create();

  Link* link = Link::create();
//  skel->createPropertyMap();

//  std::cout << link->getProperty("Mass") << std::endl;
}

//==============================================================================
int main(int argc, char* argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
