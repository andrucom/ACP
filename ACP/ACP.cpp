#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <unordered_set>
#include <filesystem>
#include <chrono>
#include <sstream>
#include <cstdlib>
#include "backup.h"




auto bk = backup::Back();
std::unordered_set<std::string> allowedNames = { "test1","test2","testttt" };

int inp;
std::string folder_name = "zdahalove_";
char path[] = "C:/Test";
char Ver[] = "0.0.1";


int main()
{
    setlocale(LC_ALL, "Russian");
    bk.avtor(Ver);
    bk.input(inp, path, folder_name);

    do
    {
        switch (inp)
        {
            case 1:
            {
                system("CLS");
                std::cout << "Вывод всех папок: \n";
                bk.patchAll(path);
                bk.input(inp, path, folder_name);
                break;
            }
            case 2:
            {
                system("CLS");
                std::cout << "Вывод некоторых папок:        " << "Фильтр: ";
                bk.show(allowedNames);
                std::cout << "\n";
                bk.patchConcrect(path);
                bk.input(inp,path,folder_name);
                break;
            }
            case 3:
            {
                system("CLS");
                bk.createFolder(path, folder_name);
                bk.input(inp, path, folder_name);
                break;
            }
            default:
            {
                system("CLS");
                bk.avtor(Ver);
                bk.input(inp, path, folder_name);
                break;
            }
        }
    } while (inp != 0);

    

    system("pause");
}

