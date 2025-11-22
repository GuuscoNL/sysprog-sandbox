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
  // std::strcpy(path.data(), "plugins/plugin1.plug");
  std::strcpy(
      path.data(),
      "../child_src/child.exe "
      "C:/Users/Gebruiker/OneDrive/Documenten/GitHub/sysprog-sandbox/text.txt "
      "plugin1.plug");

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
    std::cerr << "child process exited normally\n";
  } else {
    std::cerr << "child process failed, error " << GetLastError() << std::endl;
  }

  // Close process and thread handles.
  CloseHandle(pi.hProcess);
  CloseHandle(pi.hThread);
}
