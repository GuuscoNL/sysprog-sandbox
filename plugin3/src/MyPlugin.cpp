#include "MyPlugin.hpp"

std::string sp::MyPlugin::name() const { return "RemoveVowelsPlugin"; }

std::string sp::MyPlugin::description() const {
  return "Remove vowels from text";
}

std::string sp::MyPlugin::transform(const std::string &input) const {
  std::string output;
  for (char c : input) {
    if (c != 'a' && c != 'e' && c != 'i' && c != 'o' && c != 'u' && c != 'A' &&
        c != 'E' && c != 'I' && c != 'O' && c != 'U') {
      output += c;
    }
  }
  return output;
}

sp::IPlugin *create_instance() { return new sp::MyPlugin; }
