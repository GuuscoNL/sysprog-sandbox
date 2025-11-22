#include "MyPlugin.hpp"

std::string sp::MyPlugin::name() const { return "UpperCasePlugin"; }

std::string sp::MyPlugin::description() const {
  return "Transform to upper case";
}

std::string sp::MyPlugin::transform(const std::string &input) const {
  std::string output = input;
  for (char &c : output) {
    c = std::toupper(c);
  }
  return output;
}

sp::IPlugin *create_instance() { return new sp::MyPlugin; }
