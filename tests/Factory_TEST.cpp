#include <gtest/gtest.h>

#include "noriter/noriter.h"

using namespace nrt;

enum class MyEnum
{
  Link,
  Skeleton
};

NORITER_REGISTER_OBJECT_TO_FACTORY(std::string, "Link", Serializable, Link)

//==============================================================================
TEST(Factory, Basic)
{
  Serializable* link_ = Factory<std::string, Serializable>::create("Link");
  std::cout << link_ << std::endl;
}

//==============================================================================
int main(int argc, char* argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
