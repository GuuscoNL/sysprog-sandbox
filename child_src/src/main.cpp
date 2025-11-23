#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "IPlugin.hpp"
#include "PluginWrapper.hpp"

std::vector<std::string> SplitString(const std::string &str,
                                     const std::string &sep) {
  std::vector<std::string> result;
  size_t start{0};
  size_t end{str.find(sep)};

  while (end != std::string::npos) {
    result.push_back(str.substr(start, end - start));
    start = end + sep.length();
    end = str.find(sep, start);
  }

  result.push_back(str.substr(start));
  return result;
}

const std::string PLUGIN_DIR = "C:/Users/Gebruiker/OneDrive/Documenten/GitHub/"
                               "sysprog-sandbox/build/child_src/plugins/";

int main(int argc, char *argv[]) {
  std::cout << "Hello from child process!" << std::endl;

  std::cout << "Arguments received:" << std::endl;

  if (argc < 3) {
    std::cerr << "Not enough arguments provided! [text_file_path plugin_path]"
              << std::endl;
    return 1;
  }

  std::string text_file_path = argv[1];
  std::cout << "    Text File Path: " << text_file_path << std::endl;

  std::string pluginString = argv[2];
  std::cout << "    Plugin Path: " << pluginString << std::endl;

  try {

    // Instantiate plugin
    sp::PluginWrapper wrapper(PLUGIN_DIR + pluginString);

    using factory = sp::IPlugin *(*)();
    factory func = reinterpret_cast<factory>(wrapper.lookup("create_instance"));
    std::unique_ptr<sp::IPlugin> plugin(func());

    // Call methods
    std::cout << "Loaded plugin";
    std::cout << plugin->name() << ": " << plugin->description() << '\n';

    // Open text file
    std::ifstream text_file(text_file_path);
    if (!text_file.is_open()) {
      std::cerr << "Failed to open the file: " << text_file_path << std::endl;
      return 1;
    }

    // Read file content
    std::string file_content;
    {
      std::ostringstream ss;
      ss << text_file.rdbuf();
      file_content = ss.str();
    }

    // run selected plugins
    std::string result = file_content;

    result = plugin->transform(result);
    std::cout << "Plugin " << plugin->name() << " applied.\n";

    std::cout << "\nFinal result:\n" << result << std::endl;
  } catch (const std::exception &ex) {
    std::cerr << ex.what() << std::endl;
    return 1;
  }
  return 0;
}