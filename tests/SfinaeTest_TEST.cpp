#include <gtest/gtest.h>
#include <string>
#include <iostream>

#include "noriter/noriter.h"

using namespace nrt;

//==============================================================================
class TestClass
{
public:
  void create() {}
  TestClass* serialize() {}
  void mutipleArgs(int, double, float) {}
};

//==============================================================================
TEST(SfinaeTest, Basic)
{
  EXPECT_TRUE( (has_method<TestClass, void(void)>::method_name<&TestClass::create>::value) );
  EXPECT_TRUE( NORITER_HAS_METHOD_VALUE(TestClass, create, void, void) );
  EXPECT_TRUE( NORITER_HAS_METHOD_VALUE(TestClass, create, void) );
  EXPECT_TRUE( NORITER_HAS_METHOD_VALUE(TestClass, create, void, void) );
  EXPECT_TRUE( NORITER_HAS_METHOD_VALUE(TestClass, mutipleArgs, void, int, double, float) );
}

//==============================================================================
int main(int argc, char* argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
