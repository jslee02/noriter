#include <gtest/gtest.h>

#include "noriter/noriter.h"

using namespace nrt;

XENUM_BEGIN_VAL(TestEnum)
  XENUM_VAL(NotDefined,     0x00000000)
  XENUM_VAL(Success,        0x00000001)
XENUM_END_VAL(TestEnum)

//==============================================================================
TEST(Enumerator, Basic)
{
  std::cout << TestEnum::NotDefined << std::endl;
  std::cout << TestEnum::Success << std::endl;
}

//==============================================================================
int main(int argc, char* argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
