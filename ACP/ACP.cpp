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

// TODO
// Сделать проверку на наличие папки
// Изменение с фильтром: Добавление, изменение, удаление 



backup::Back bk;
std::unordered_set<std::string> allowedNames = { "dahalove","dahalove_nether","dahalove_the_end" };

int inp;
int inp2;
std::string forderName = "zdahalove_";
std::string mainDir = "D:/ServerMine";
std::string ver = "0.1.0 (DEV)";


int main()
{
    setlocale(LC_ALL, "Russian");
    bk.avtor(ver);
    bk.input(mainDir, forderName);



    do
    {
        std::cin >> inp;
        switch (inp)
        {
            case 1:
            {
                system("CLS");
                std::cout << "Вывод всех папок: \n";
                bk.patchAll(mainDir);
                bk.input(mainDir, forderName);
                
                break;
            }
            case 2:
            {
                system("CLS");
                std::cout << "Вывод некоторых папок:        " << "Фильтр: ";
                bk.show(allowedNames);
                std::cout << "\n";
                bk.patchConcrect(mainDir, allowedNames);
                bk.input(mainDir,forderName);
                break;
            }
            case 3:
            {
                system("CLS");
                bk.createFolder(mainDir, forderName, allowedNames);
                bk.input(mainDir, forderName);
                bk.OpenMainDir(mainDir);
                break;
            }
            case 4:
            {
                system("CLS");
                mainDir = bk.ChangeMainDir();
                bk.input(mainDir, forderName);
                break;
            }
            case 5: 
            {
                
                system("CLS");
                forderName = bk.ChangeFolderName();
                bk.input(mainDir, forderName);
                break;
                
            }
            default:
            {
                system("CLS");
                bk.avtor(ver);
                bk.input(mainDir, forderName);
                break;
            }
        }
    } while (inp != 0);

    

    system("pause");
}

