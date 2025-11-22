#ifndef IPLUGIN_H_
#define IPLUGIN_H_

#include <string>

namespace sp {
class IPlugin {
public:
  virtual ~IPlugin() = default;
  virtual std::string name() const = 0;
  virtual std::string description() const = 0;
  virtual std::string transform(const std::string &input) const = 0;
};
} // namespace sp

#endif // IPLUGIN_H_
