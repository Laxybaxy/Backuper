#include <windows.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <direct.h>
#include "json.hpp"
using namespace std;

std::string ExePath() {
    char buffer[MAX_PATH];
    GetModuleFileName(NULL, buffer, MAX_PATH);
    string::size_type pos = string(buffer).find_last_of("\\/");
    return string(buffer).substr(0, pos);
}

int main(int argc, char* argv[])
{
    nlohmann::json j;

    //  Read from cfg
    std::ifstream i("config.json");
    if (i) {
        i >> j;
    }
    else { //if no cfg makes default
        printf("creating config.json\n");

        j["dbg"] = true;
        j["src"] = { "C:/test/ye.txt","C:/test/ya.txt" };

        //  Write to cfg
        std::ofstream o("config.json");
        o << std::setw(4) << j << std::endl;
        system("pause");
        return 1;
    }

    string dir = ExePath()+"/files";
    mkdir(dir.c_str());
    

    for (int i = 0; i < j["src"].size(); i++)
    {
        string src = j["src"].at(i);
        std::size_t found = src.find_last_of("/\\");
        string dest = ExePath() + "\\files\\" + src.substr(found+1);

        if (j["dbg"] == true) {
            printf("Src: %s - Dest: %s - ", src.c_str(), dest.c_str());
            if (CopyFile(src.c_str(), dest.c_str(), false)) {
                printf("Done!\n");
            }
            else
            {
                printf("Failed!\n");
            }
        }
    }
    if(j["dbg"]==true)
        system("pause");
    return 1;
}