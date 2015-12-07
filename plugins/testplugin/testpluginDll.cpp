#include "testplugin.h"

#include <iostream>

#include "dart5/engine/Engine.h"

dart::Plugin* plugin;

//-----------------------------------------------------------------------
//#ifndef OGRE_STATIC_LIB
extern "C" void dllStartPlugin(void)
{
  //
  plugin = new dart::TestPlugin();

  //
  dart::Engine::getSingleton().installPlugin(plugin);

  std::cout << "TestPlugin: dllStartPlugin" << std::endl;
}

extern "C" void dllStopPlugin(void)
{
  dart::Engine::getSingleton().uninstallPlugin(plugin);

  std::cout << "TestPlugin: dllStopPlugin" << std::endl;
}
//#endif
