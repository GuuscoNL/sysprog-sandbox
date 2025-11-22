#ifndef PLUGINWRAPPER_H_
#define PLUGINWRAPPER_H_

#include <string>
#include <windows.h>

namespace sp {
class PluginWrapper {
public:
  PluginWrapper(const std::string &path);
  ~PluginWrapper();

  PluginWrapper(const PluginWrapper &) = delete;
  PluginWrapper &operator=(const PluginWrapper &) = delete;

  PluginWrapper(PluginWrapper &&other);
  PluginWrapper &operator=(PluginWrapper &&other);

  HMODULE plugin() const { return _plugin; }
  FARPROC lookup(const std::string &symbol) const;

private:
  HMODULE _plugin{nullptr};

  void cleanup();
  void move(PluginWrapper &&other);
};
} // namespace sp

#endif // PLUGINWRAPPER_H_
