#include "testplugin.h"

#include <iostream>
#include <string>

namespace dart {

//==============================================================================
TestPlugin::TestPlugin()
{
  mName = "testPlugin";
  std::cout << "TestPlugin::TestPlugin()" << std::endl;
}

//==============================================================================
TestPlugin::~TestPlugin()
{
  std::cout << "TestPlugin::~TestPlugin()" << std::endl;
}

//==============================================================================
const std::string& TestPlugin::getName() const
{
  return mName;
}

//==============================================================================
void TestPlugin::install()
{
  std::cout << "TestPlugin::install()" << std::endl;
}

//==============================================================================
void TestPlugin::startup()
{
  std::cout << "TestPlugin::startup()" << std::endl;
}

//==============================================================================
void TestPlugin::shutdown()
{
  std::cout << "TestPlugin::shutdown()" << std::endl;
}

//==============================================================================
void TestPlugin::uninstall()
{
  std::cout << "TestPlugin::uninstall()" << std::endl;
}

}  // namespace dart

