#include <windows.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "json.hpp"
using namespace std;

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

        j["path"] = { "C:\\test\\ye.txt" };
        j["destination"] = "C:\\test\\files\\";

        //  Write to cfg
        std::ofstream o("config.json");
        o << std::setw(4) << j << std::endl;
        system("pause");
        return 1;
    }

    for (int i = 0; i < j["path"].size(); i++)
    {
        string tmpdest = j["destination"];
        string src = j["path"].at(i);
        std::size_t found = src.find_last_of("/\\");
        string dest = tmpdest + src.substr(found+1);

        printf("Src: %s - Dest: %s - ", src.c_str(),dest.c_str());
        if (CopyFile(src.c_str(), dest.c_str(), false)) {
            printf("Done!\n");
        }
        else
        {
            printf("Failed!\n");
        }
    }
    return 1;
}