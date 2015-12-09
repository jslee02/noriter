#include <gtest/gtest.h>
#include <string>
#include <iostream>

#include "noriter/noriter.h"

using namespace nrt;

class SerializableFactory : public Factory<ObjectType, Serializable>
{
public:

  static SerializableFactory& getInstance()
  {
    static SerializableFactory instance;

    return instance;
  }

private:
  SerializableFactory()
  {
    NORITER_REGISTER_OBJECT_TO_FACTORY_IN_FUNCTION(ObjectType, ObjectType::Link, Serializable, Link);
    NORITER_REGISTER_OBJECT_TO_FACTORY_IN_FUNCTION(ObjectType, ObjectType::Skeleton, Serializable, Skeleton);
  }

protected:

private:
};

//==============================================================================
TEST(Property, Basic)
{
//  auto link1 = SerializableFactory::getInstance().create(ObjectType::Link);

//  std::string mass = link1->getProperty("Mass");

//  std::cout << "mass: " << mass << std::endl;
}

//==============================================================================
int main(int argc, char* argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
