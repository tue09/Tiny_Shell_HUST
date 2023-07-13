#include <iostream>
#include <windows.h>
#include <Shlwapi.h>

std::string GetVSCodePath()
{
    const char* appDataPath = std::getenv("APPDATA");
    std::string vscodePath = appDataPath + std::string("\\Code\\bin\\code.cmd");

    if (PathFileExistsA(vscodePath.c_str()))
    {
        return vscodePath;
    }

    return "";
}

int main()
{
    std::string vscodePath = GetVSCodePath();

    if (!vscodePath.empty())
    {
        std::cout << "Visual Studio Code path: " << vscodePath << std::endl;

        // Truy cập vào Visual Studio Code bằng cách chạy lệnh "code" với tham số
        std::string command = "\"" + vscodePath + "\"";
        std::system(command.c_str());
    }
    else
    {
        std::cout << "Visual Studio Code not found." << std::endl;
    }

    return 0;
}
