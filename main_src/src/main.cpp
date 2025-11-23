#include <cstring>
#include <iostream>
#include <vector>
#include <windows.h>

int main(int argc, char *argv[]) {
  STARTUPINFO si;
  PROCESS_INFORMATION pi;

  ZeroMemory(&si, sizeof(si));
  si.cb = sizeof(si);
  ZeroMemory(&pi, sizeof(pi));

  // Command line arg for CreateProcess *must* be writable
  std::vector<char> path(1024);

  // Get plugin to run. Hardcoded for simplicity.
  int plugin_number;
  std::cout << "Enter plugin number to run. Be aware that plugin 4 will crash "
               "(1-4): ";
  std::cin >> plugin_number;
  if (plugin_number < 1 || plugin_number > 4) {
    std::cerr << "Invalid plugin number!" << std::endl;
    return 1;
  }

  std::string plugin_filename =
      "plugin" + std::to_string(plugin_number) + ".plug";

  std::string command_line =
      "../child_src/child.exe "
      "C:/Users/Gebruiker/OneDrive/Documenten/GitHub/"
      "sysprog-sandbox/text.txt " + // path to text hardcoded for simplicity
      plugin_filename;

  std::strcpy(path.data(), command_line.c_str());

  // Start the child process.
  if (!CreateProcess(nullptr,     // No module name (use command line)
                     path.data(), // Command line
                     nullptr,     // Process handle not inheritable
                     nullptr,     // Thread handle not inheritable
                     false,       // Set handle inheritance to FALSE
                     0,           // No creation flags
                     nullptr,     // Use parent's environment block
                     nullptr,     // Use parent's starting directory
                     &si,         // Pointer to STARTUPINFO structure
                     &pi)         // Pointer to PROCESS_INFORMATION structure
  ) {
    std::cerr << "CreateProcess failed (" << GetLastError() << ")\n";
    return 1;
  }

  // Wait until child process exits.
  WaitForSingleObject(pi.hProcess, INFINITE);
  DWORD status;
  if (GetExitCodeProcess(pi.hProcess, &status) && status == 0) {
    std::cerr << "\nchild process exited normally. We can trust the plugin!\n";
  } else {
    std::cerr << "\nchild process failed, error " << GetLastError()
              << std::endl;
    std::cerr << "We can't trust this plugin!\n";
  }

  // Close process and thread handles.
  CloseHandle(pi.hProcess);
  CloseHandle(pi.hThread);
}
