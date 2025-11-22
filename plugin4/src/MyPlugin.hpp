#ifndef MYPLUGIN_H_
#define MYPLUGIN_H_

#include "IPlugin.hpp"

extern "C" {
__declspec(dllexport) sp::IPlugin *create_instance();
}

namespace sp {
class MyPlugin : public IPlugin {
public:
  std::string name() const override;
  std::string description() const override;
  std::string transform(const std::string &input) const override;
};
} // namespace sp

#endif // MYPLUGIN_H_
