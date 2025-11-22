#include "PluginWrapper.hpp"
#include <sstream>
#include <stdexcept>
#include <windows.h>

using namespace sp;

PluginWrapper::PluginWrapper(const std::string &path) {
  _plugin = LoadLibraryA(path.c_str());
  if (!_plugin) {
    std::ostringstream oss;
    oss << "plugin could not be opened, error " << GetLastError();
    throw std::runtime_error(oss.str());
  }
}

PluginWrapper::~PluginWrapper() { cleanup(); }

PluginWrapper::PluginWrapper(PluginWrapper &&other) { move(std::move(other)); }

PluginWrapper &PluginWrapper::operator=(PluginWrapper &&other) {
  if (&other != this) {
    cleanup();
    move(std::move(other));
  }
  return *this;
}

void PluginWrapper::cleanup() {
  if (_plugin) {
    FreeLibrary(_plugin);
  }
}

void PluginWrapper::move(PluginWrapper &&other) {
  _plugin = other._plugin;
  other._plugin = nullptr;
}

FARPROC PluginWrapper::lookup(const std::string &symbol) const {
  FARPROC result = GetProcAddress(_plugin, symbol.c_str());
  if (!result) {
    std::ostringstream oss;
    oss << "symbol '" << symbol << "' could not be found, error "
        << GetLastError();
    throw std::runtime_error(oss.str());
  }
  return result;
}
