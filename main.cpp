#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <Windows.h>
#include <iterator>
#include <chrono>
#include <ctime>
#include <thread>
#include <filesystem>
#include <fstream>
#include <map>
#include <iomanip>

#define MAX_BUFFER_SIZE 1024
bool isUpdateTimeRunning = false;
bool isUpdateDateRunning = false;
PROCESS_INFORMATION Processs[100];
STARTUPINFO SUInfo[100];
LPSTR cString[100];
HANDLE hHandless[100];
int status[100];
int numberProcess = 0;
std::string currentDirectory = "";
void help()
{
	std::cout <<"_______________________________________________________________________________________________"<<std::endl<<std::endl;
	std::cout << std::left << std::setw(35) << "The following tutorial will help you understand our shell better";
    std::cout << std::left << std::setw(35) << std::endl;
    std::cout << std::left << std::setw(35) << "0.  exit" << "Exit Shell" << std::endl;
    std::cout << std::left << std::setw(35) << "1.  help" << "Provide Help information for Windows commands" << std::endl;
    std::cout << std::left << std::setw(35) << "2.  date" << "Display date" << std::endl;
    std::cout << std::left << std::setw(35) << "3.  time" << "Display time" << std::endl;
    std::cout << std::left << std::setw(35) << "4.  dir" << "Display list of files in current Directory" << std::endl;
    std::cout << std::left << std::setw(35) << "5.  path" << "Display Environment Variable" << std::endl;
    std::cout << std::left << std::setw(35) << "6.  addpath [new_path] [variable]" << "Add new path to Enviroment Variable" << std::endl;
    std::cout << std::left << std::setw(35) << "7.  list" << "Display list of process " << std::endl;
    std::cout << std::left << std::setw(35) << "8.  kill [process_id]" << "Kill process with id equal to [process_id] " << std::endl;
    std::cout << std::left << std::setw(35) << "9.  killall" << "kill all process " << std::endl;
    std::cout << std::left << std::setw(35) << "10. stop [process_id]" << "Stop process with id equal to [process_id] " << std::endl;
    std::cout << std::left << std::setw(35) << "11. resume [process_id]" << "Resume process with id equal to [process_id] " << std::endl;
    std::cout << std::left << std::setw(35) << "12. hello fore" << "Open file 'hello.exe' in foreground mode " << std::endl;
    std::cout << std::left << std::setw(35) << "13. hello back" << "Open file 'hello.exe' in background mode " << std::endl;
    std::cout << std::left << std::setw(35) << "14. [your_batch_file_name].bat" << "Excute [your_batch_file_name] " << std::endl;
    std::cout << std::left << std::setw(35) << "15. calendar" << "You can determine which day of the week is today, tomorrow, or yesterday " << std::endl;
    std::cout<<"_______________________________________________________________________________________________"<<std::endl;
}

void updateTimeThread() {
    isUpdateTimeRunning = false;
    while (!isUpdateTimeRunning) {
        std::chrono::system_clock::time_point currentTime = std::chrono::system_clock::now();

        std::time_t currentTimeT = std::chrono::system_clock::to_time_t(currentTime);
        char timeString[100];
        std::strftime(timeString, sizeof(timeString), "%H:%M:%S", std::localtime(&currentTimeT));

        std::cout << "\rCurrent time is: " << timeString << " | Type to stop: ";

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void updateDateThread() {
    isUpdateDateRunning = false;
    while (!isUpdateDateRunning) {
        std::chrono::system_clock::time_point currentTime = std::chrono::system_clock::now();

        std::time_t currentTimeT = std::chrono::system_clock::to_time_t(currentTime);
        char timeString[100];
        std::strftime(timeString, sizeof(timeString), "%Y-%m-%d", std::localtime(&currentTimeT));

        std::cout << "\rCurrent date is: " << timeString << " | Type to stop: ";

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void dir2()
{
    std::filesystem::path currentPath = std::filesystem::current_path();
    for (const auto& entry : std::filesystem::directory_iterator(currentPath)) {
        if (entry.is_regular_file()) {
            std::cout << entry.path().filename() << std::endl;
        }
    }
}

// void killp(std::string process)
// {
//     int id = std::atoi(process.c_str());
//     bool flag = true;
//     for (int i = 1; i <= numberProcess; i++)
//     {
//         if (Processs[i].dwProcessId == id)
//         {
//             TerminateProcess(Processs[i].hProcess, 0);
//             CloseHandle(Processs[i].hThread);
//             CloseHandle(Processs[i].hProcess);

//             std::cout<<"Process "<<cString[i]<< " is killed"<<std::endl;
//             for (int j = i; j < numberProcess; j++)
//             {
//                 status[j] = status[j+1];
//                 Processs[j] = Processs[j+1];
//                 SUInfo[j] = SUInfo[j+1];
//                 cString[j] = cString[j+1];
//             }
//             numberProcess = numberProcess - 1;
//             flag = false;
//         }
//     }
//     if (flag)
//     {
//         std::cout<<std::endl<<"Cannot find this process with id = "<<id;
//     }
// }

void kill(int id) {
    HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, id);

    if (TerminateProcess(hProcess, 0)) 
    {
        std::cout<<"Process with id = "<<id<<" has been killed";
    } else 
    {
        std::cout<<std::endl<<"Cannot find this process with id = "<<id;
    }

    CloseHandle(hProcess);
}

void ProcessinBackgroundMode(const std::string &process)
{
    void killp(std::string process);
    numberProcess = numberProcess + 1;
    status[numberProcess] = 1;
    SUInfo[numberProcess] = {sizeof(STARTUPINFO)};
    Processs[numberProcess];
    ZeroMemory(&SUInfo[numberProcess], sizeof(SUInfo[numberProcess]));
    SUInfo[numberProcess].cb = sizeof(SUInfo[numberProcess]);
    cString[numberProcess] = strdup(process.c_str());
    if (!CreateProcessA(cString[numberProcess], NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &SUInfo[numberProcess], &Processs[numberProcess]))
    {
        TerminateProcess(Processs[numberProcess].hProcess, 0);
        CloseHandle(Processs[numberProcess].hThread);
        CloseHandle(Processs[numberProcess].hProcess);
        numberProcess = numberProcess - 1;
        std::cout<<std::endl<<"Cannot open this file.";
        return;
    }
}

void addPath(std::string new_value, std::string variable) { 
	HKEY hkey;
    long regOpenResult;
    const char key_name[] = "Environment";

    const char *path=new_value.c_str();//new_value path need to update 

    regOpenResult = RegOpenKeyEx(HKEY_CURRENT_USER,key_name, 0, KEY_ALL_ACCESS, &hkey);

    LPCSTR stuff = variable.c_str();                                                   //Variable Name 
    RegSetValueEx(hkey,stuff,0,REG_SZ,(BYTE*) path, strlen(path));
    RegCloseKey(hkey);

}
//C:\Users\ADMIN\.matplotlib
void ProcessinForegroundMode(const std::string &process)
{
    // PROCESS_INFORMATION process1;
    // STARTUPINFO SUinfo1 = {sizeof(STARTUPINFO)};
    // LPSTR cStr1 = strdup(process.c_str());
    // // STARTUPINFOA 
    // SUInfo[numberProcess];
    // ZeroMemory(&SUInfo[numberProcess], sizeof(SUInfo[numberProcess]));
    // SUInfo[numberProcess].cb = sizeof(SUInfo[numberProcess]);
    // if (!CreateProcessA(cStr1, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, SUInfo, Processs))
    // {
    //     std::cout<<std::endl<<"Cannot open this file.";
    //     return;
    // }
//test
    void killp(std::string process);
    numberProcess = numberProcess + 1;
    status[numberProcess] = 1;
    SUInfo[numberProcess] = {sizeof(STARTUPINFO)};
    Processs[numberProcess];
    ZeroMemory(&SUInfo[numberProcess], sizeof(SUInfo[numberProcess]));
    SUInfo[numberProcess].cb = sizeof(SUInfo[numberProcess]);
    cString[numberProcess] = strdup(process.c_str());
    if (!CreateProcessA(cString[numberProcess], NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &SUInfo[numberProcess], &Processs[numberProcess]))
    {
        TerminateProcess(Processs[numberProcess].hProcess, 0);
        CloseHandle(Processs[numberProcess].hThread);
        CloseHandle(Processs[numberProcess].hProcess);
        numberProcess = numberProcess - 1;
        std::cout<<std::endl<<"Cannot open this file.";
        return;
    }
    WaitForSingleObject(Processs[numberProcess].hProcess, INFINITE);
    // CloseHandle(process.hThread);
    // CloseHandle(process.hProcess);
//test end
    // WaitForSingleObject(process1.hProcess, INFINITE);
    // CloseHandle(process1.hThread);
    // CloseHandle(process1.hProcess);
}

void ProcessBackgroundOrForeground(const std::string &command, const std::string &process)
{
    std::stringstream cou (command);
    std::string cou1, cou2;
    cou >> cou1;
    cou >> cou2;
    if (cou2.compare("back") == 0)
    {
        ProcessinBackgroundMode(process);
    }
    else if (cou2.compare("fore") == 0)
    {
        ProcessinForegroundMode(process);
    }
    else
    {
        std::cout<<std::endl<<"Bug!!";
    }

}

void killAll()
{
    for (int i = 1; i <= numberProcess; ++i)
    {
        DWORD dwe;
        GetExitCodeProcess(Processs[i].hProcess, &dwe);
        if (dwe != 259)
        {
            TerminateProcess(Processs[i].hProcess, 0);
            CloseHandle(Processs[i].hThread);
            CloseHandle(Processs[i].hProcess);
            for (int j = i; j < numberProcess; j++)
            {
                status[j] = status[j+1];
                Processs[j] = Processs[j+1];
                SUInfo[j] = SUInfo[j+1];
                cString[j] = cString[j+1];
            }
            numberProcess = numberProcess - 1;
            i = i - 1;
        }
        else
        {
            int x = static_cast<int>(Processs[i].dwProcessId);
            kill(x);
        }
    }
    std::cout << std::endl << "All process have been killed." << std::endl;
}

void showList()
{
    std::cout<<std::endl;
    std::cout<<"| Number | ProcessId | hProcess | Status | Cmd Name |";
    std::cout<<std::endl;
    for (int i = 1; i <= numberProcess; ++i)
    {
        DWORD dwe;
        GetExitCodeProcess(Processs[i].hProcess, &dwe);
        if (dwe != 259)
        {
            TerminateProcess(Processs[i].hProcess, 0);
            CloseHandle(Processs[i].hThread);
            CloseHandle(Processs[i].hProcess);
            for (int j = i; j < numberProcess; j++)
            {
                status[j] = status[j+1];
                Processs[j] = Processs[j+1];
                SUInfo[j] = SUInfo[j+1];
                cString[j] = cString[j+1];
            }
            numberProcess = numberProcess - 1;
            i = i - 1;
        }
        else
        {
            const char *temp = (status[i] == 0) ? "stopping" : "Running ";
            std::cout<<i<<" | "<<Processs[i].dwProcessId<<" | "<< Processs[i].hProcess<<" | "<<temp<<" | "<<cString[i]<<std::endl;
        }
    }
    std::cout<<std::endl;
}

void stop(std::string process)
{
    int id = atoi(process.c_str());
    bool flag = true;
    for (int i = 1; i <= numberProcess; ++i)
    {
        if (Processs[i].dwProcessId == id)
        {
            flag = false;
            if (status[i] == 1)
            {
                status[i] = 0;
                std::cout <<"Stop " << cString[i]<<std::endl;
                SuspendThread(Processs[i].hThread);
                break;
            }
            else
            {
                std::cout<< "Process " << cString[i] << " is stopping" << std::endl;
                break;
            }
        }
    }
    if (flag)
    {
        std::cout<<std::endl<<"Cannot find this process with id = "<<id;
    }
}

void resume(std::string process)
{
    int id = atoi(process.c_str());
    bool flag = true;
    for (int i = 1; i <= numberProcess; ++i)
    {
        if (Processs[i].dwProcessId == id)
        {
            flag = false;
            if (status[i] == 0)
            {
                status[i] = 1;
                std::cout << "Process " << cString[i] << " run now"<<std::endl;
                ResumeThread(Processs[i].hThread);
                break;
            }
            else
            {
                std::cout << "Process " << cString[i] << " run now" << std::endl;
                break;
            }
        }
    }
    if (flag)
    {
        std::cout<<"Cannot find this process with id = "<< id;
    }
}

void calendar(std::string command)
{
    std::map<int, std::string> week;
    week[1] = "Monday";
    week[2] = "Tuesday";
    week[3] = "Wednesday";
    week[4] = "Thursday";
    week[5] = "Friday";
    week[6] = "Saturday";
    week[0] = "Sunday";
    std::time_t now = std::time(nullptr);
    std::tm* timeInfo = std::localtime(&now);

    int dayOfWeek = timeInfo->tm_wday;

    if (command == "today")
    {
        std::cout<<"Today is: "<<week[dayOfWeek]<<std::endl;
    }
    else if (command == "tomorrow")
    {
        if (dayOfWeek == 6)
        {
            dayOfWeek = 0;
        }else{ dayOfWeek = dayOfWeek + 1; }
        std::cout<<"Tomorrow is: "<<week[dayOfWeek]<<std::endl;
    }
    else if (command == "yesterday")
    {
        if (dayOfWeek == 0)
        {
            dayOfWeek = 6;
        }else{ dayOfWeek = dayOfWeek - 1; }
        std::cout<<"Yesterday is: "<<week[dayOfWeek]<<std::endl;
    }
    else
    {
        std::cout<<std::endl<<"Your command is Invalid, Please use: 'tomorrow', 'yesterday' or 'today' ";
    }
}

void processCommand(const std::string& command) {
    std::istringstream iss(command);
    std::vector<std::string> tokens(std::istream_iterator<std::string>{iss},
                                    std::istream_iterator<std::string>());

    if (tokens.empty()) {
        return;
    }
    if (tokens[0] == "exit") {
        std::cout << std::endl << "Exit succesful!";
        exit(0);
    }
    else if (tokens[0] == "help") {
        help();
    }
    else if (tokens[0] == "date") {
        std::thread updateDate(updateDateThread);

        std::string exitString;
        std::getline(std::cin, exitString);
        updateDate.detach();
        isUpdateDateRunning = true;
        
    }
    else if (tokens[0] == "time") 
    {
        std::thread updateTime(updateTimeThread);

        std::string exitString;
        std::getline(std::cin, exitString);
        updateTime.detach();
        isUpdateTimeRunning = true;
        
    }
    else if (tokens[0] == "dir") 
    {
        dir2();
    }
    else if (tokens[0] == "path") {
        const char* path = getenv("PATH");
        if (path != nullptr) {
            std::cout << "PATH: " << path << std::endl;
        }
    }
    else if (tokens[0] == "addpath") {
        if (tokens.size() >= 3) {
            addPath(tokens[1], tokens[2]);
        }
        else {
            std::cerr << "Usage: addpath <new_path> <variabele>" << std::endl;
        }
    }
    else if (tokens[0] == "list") {
        showList();
    }
    else if (tokens[0] == "kill") 
    {
        int id;
        id = std::stoi(tokens[1]);
        kill(id);

    }
    else if (tokens[0] == "killall")
    {
        killAll();
    }
    else if (tokens[0] == "stop") {
        if (tokens.size() >= 2) {
            std::string process = "";
            for (int i = 0; i < tokens[1].size(); i++)
            {
                process = process + tokens[1][i];
            }
            stop(process);
        }
        else {
            std::cerr << "Usage: stop <Process_id>" << std::endl;
        }
    }
    else if (tokens[0] == "resume") {
        if (tokens.size() >= 2) {
            std::string process = "";
            for (int i = 0; i < tokens[1].size(); i++)
            {
                process = process + tokens[1][i];
            }
            resume(process);
        }
        else {
            std::cerr << "Usage: resume <Process_id>" << std::endl;
        }
    }
    else if (tokens[0].find(".bat") != std::string::npos)
    {
        std::ifstream file(tokens[0]);
        if (!file) {
            std::cerr << "Failed to open file." << std::endl;
            return;
        }
        std::string line;
        while (std::getline(file, line)) {
            processCommand(line);
        }
        file.close();
    }
    
    else if ((tokens[0].compare("note") == 0) and (tokens[1].compare("fore") == 0 || tokens[1].compare("back") == 0))
    {
            std::string s = "C:\\Windows\\System32\\notepad.exe";
            ProcessBackgroundOrForeground(command, s);
    }
//test
    else if (tokens[0].compare("hello.exe") == 0)
    {
        if (tokens.size() == 1)
        {
            std::string command = tokens[0] + " back";
            ProcessBackgroundOrForeground(command, tokens[0]);
        }
        else if (tokens[1].compare("fore") == 0 || tokens[1].compare("back") == 0)
        {
            std::string s = "hello.exe";
            ProcessBackgroundOrForeground(command, s);
        }
        else
        {
            std::cout<<"Wrong";
        }
    }
//test end    
    else if (tokens[0] == "calendar")
    {
        std::cout<<"|   Welcome to Calendar   |";
        std::cout<<std::endl<<"//You want to know today or tomorrow or yesterday";
        std::cout<<std::endl<<"//If you want to exit calendar, type 'out'";
        while (true)
        {
            std::string cmt;
            std::getline(std::cin, cmt);
            if (cmt == "out"){
                break;
            }
            calendar(cmt);
        }
    }
    else {
        std::cout<<"Your command is Invalid"<<std::endl;
        return;
    }
}

int main() {
    std::string command;
    std::string text1 = "Welcome to our Tiny Shell";
    std::string text2 = "LE DINH TRI TUE | DO DUC MANH | NGO DINH LUYEN";
    int totalWidth = 120; 
    int spaces2 = (totalWidth - text2.length()) / 2;
    int spaces1 = (totalWidth - text1.length()) / 2;
    std::cout << std::setw(spaces1) << "" << text1 << std::setw(spaces1) << std::endl;
    std::cout << std::setw(spaces2) << "" << text2 << std::setw(spaces2) << std::endl;
    std::cout<<std::endl<<"Type 'help' to know how this shell work !!";
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, command);

        processCommand(command);
    }
    killAll();
    return 0;
}