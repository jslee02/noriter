#ifndef _DART5_TESTPLUGIN_TESTPLUGIN_H_
#define _DART5_TESTPLUGIN_TESTPLUGIN_H_

#include <dart5/common/Plugin.h>

namespace dart {

class TestPlugin : public Plugin
{
public:
  ///
  TestPlugin();

  ///
  virtual ~TestPlugin();

  ///
  virtual const std::string& getName() const;

  ///
  virtual void install();

  ///
  virtual void startup();

  ///
  virtual void shutdown();

  ///
  virtual void uninstall();

protected:

private:
  ///
  std::string mName;
};

}  // namespace dart

#endif  // _DART5_TESTPLUGIN_TESTPLUGIN_H_

