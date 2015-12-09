#include <gtest/gtest.h>
#include <string>
#include <iostream>

#include "noriter/noriter.h"

using namespace nrt;

class TestClass
{
public:
  void create() {}
  TestClass* serialize() {}
};

//==============================================================================
TEST(SfinaeTest, Basic)
{
  std::cout << has_method<TestClass, void(void)>::method_name<&TestClass::create>::value << std::endl;
  std::cout << NORITER_HAS_METHOD(TestClass, create, void, void) << std::endl;
}

//==============================================================================
int main(int argc, char* argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
