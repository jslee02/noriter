#include <gtest/gtest.h>

#include "noriter/noriter.h"

using namespace nrt;

enum ObjectEnumType
{
  OET_Link,
  OET_Skeleton
};

enum class ObjectEnumClassType
{
  Link,
  Skeleton
};

NORITER_REGISTER_OBJECT_TO_FACTORY(std::string, "Link", Serializable, Link)
NORITER_REGISTER_OBJECT_TO_FACTORY(ObjectEnumClassType, ObjectEnumClassType::Link, Serializable, Link)
NORITER_REGISTER_OBJECT_TO_FACTORY(unsigned int, OET_Link, Serializable, Link)

//==============================================================================
TEST(Factory, Basic)
{
  Serializable* link1 = Factory<std::string, Serializable>::create("Link");
  Serializable* link2 = Factory<ObjectEnumClassType, Serializable>::create(ObjectEnumClassType::Link);
  Serializable* link3 = Factory<unsigned int, Serializable>::create(OET_Link);

  EXPECT_NE(link1, nullptr);
  EXPECT_NE(link2, nullptr);
  EXPECT_NE(link3, nullptr);
}

//==============================================================================
int main(int argc, char* argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
