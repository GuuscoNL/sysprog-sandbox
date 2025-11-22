#include "MyPlugin.hpp"

std::string sp::MyPlugin::name() const { return "AddOnePlugin"; }

std::string sp::MyPlugin::description() const {
  return "Add 1 to every character's ASCII value";
}

std::string sp::MyPlugin::transform(const std::string &input) const {
  std::string output;
  for (char c : input) {
    output += c + 1;
  }
  return output;
}

sp::IPlugin *create_instance() { return new sp::MyPlugin; }
