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
// Изменение с фильтром: Добавление, изменение, удаление 
// Сохранение измененных параметров 


backup::Back bk;
std::unordered_set<std::string> allowedNames = { "dahalove","dahalove_nether","dahalove_the_end"};

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
                do
                {
                    std::cout << "_____________________\n";
                    std::cout << "1 - Вывод всех папок\n";
                    std::cout << "2 - Вывод всех с фильтром\n\n";
                    std::cout << "0 - Меню\n";
                    std::cout << ">> ";

                    std::cin >> inp2;

                    switch (inp2)
                    {
                        case 1:
                        {
                            system("CLS");
                            bk.patchAll(mainDir);
                            break;
                        }
                        case 2:
                        {
                            system("CLS");
                            std::cout << "\n";
                            bk.patchConcrect(mainDir, allowedNames);
                            break;
                        }
                        default:
                        {
                            system("CLS");
                            break;
                        }
                    }


                } while (inp2 != 0);

                system("CLS");
                bk.avtor(ver);
                bk.input(mainDir, forderName);
                break;
            }

            case 2:
            {
                system("CLS");

                do
                {

                    std::cout << "_____________________\n";
                    std::cout << "1 - Поменять основную папку\n";
                    std::cout << "2 - Поменять создаваемую папку\n\n ";
                    std::cout << "0 - Меню\n";
                    std::cout << ">> ";

                    std::cin >> inp2;

               
                    switch (inp2)
                    {
                        case 1:
                        {
                            system("CLS");
                            mainDir = bk.ChangeMainDir();
                            break;
                        }
                        case 2:
                        {
                            system("CLS");
                            forderName = bk.ChangeFolderName();
                            break;
                        }
                        default:
                        {
                            system("CLS");
                            break;
                        }
                    }
                } while (inp2 != 0);

                system("CLS");
                bk.avtor(ver);
                bk.input(mainDir, forderName);
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

