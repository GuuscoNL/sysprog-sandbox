#include <iostream>

int main(int argc, char *argv[]) {
  std::cout << "Hello from child process!" << std::endl;

  std::cout << "Arguments received:" << std::endl;
  for (int i = 0; i < argc; ++i) {
    std::cout << "  argv[" << i << "]: " << argv[i] << std::endl;
  }

  // Return 0 to indicate success
  return 0;
}