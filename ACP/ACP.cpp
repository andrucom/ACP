#define _CRT_SECURE_NO_WARNINGS
#define WINVER 0x0601  // Минимум Windows 7
#define _WIN32_WINNT 0x0601
#define NTDDI_VERSION 0x06010000
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
// Выбор вывода папки


backup::Back bk;
std::unordered_set<std::string> allowedNames = { "dahalove","dahalove_nether","dahalove_the_end", "test1"};

int inp;
int inp2;
//std::string settings.FolderName = "BackUp_";
//std::string settings.mainDir = "C:/Test"; //D: / ServerMine
const std::string VER = "0.2.1 (BETA_CА)";
backup::Back::Settings settings;


std::string get_setlocale()
{
#ifdef _WIN32
    std::string placeholder;
    std::cout << "\t\twin32\n";
    setlocale(LC_ALL, "ru_RU.UTF-8");
    return placeholder;
#else
    std::string placeholder;
    std::cout << "\t\tnot !! win32\n";
    setlocale(LC_ALL, "Russian");
    return placeholder;
#endif
}

fs::path get_appdata_path()
{
#ifdef _WIN32
    return fs::path(std::getenv("LOCALAPPDATA"));


#else
    return fs::path(std::getenv("LOCALAPPDATA"));


#endif

}

fs::path config_path = get_appdata_path().string() + "/ACP/ACP_settings.json";

int main()
{
    get_setlocale();

    //setlocale(LC_ALL, "RUS.UTF8");
    //setlocale(LC_ALL, "ru_RU.UTF-8");

    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    //std::locale::global(std::locale("ru_RU.UTF-8"));
    //std::cin.imbue(std::locale());
    //std::cout.imbue(std::locale());


    bk.init(get_appdata_path());
    settings = bk.load_settings(config_path);
    bk.save_settings(settings, config_path);

    bk.avtor(VER);
    bk.input(settings.mainDir, settings.FolderName);



    do
    {

        std::cin >> inp;

        switch (inp)
        {
            // Работа с папками
            case 1:
            {
                system("CLS");
                do
                {
                    std::cout << "_____________________\n";
                    std::cout << "1 - Вывод всех папок\n";
                    std::cout << "2 - Вывод всех с фильтром\n";
                    std::cout << "\n0 - Меню\n";
                    bk.daw();

                    std::cin >> inp2;

                    switch (inp2)
                    {
                        case 1:
                        {
                            system("CLS");
                            bk.patchAll(settings.mainDir);
                            break;
                        }
                        case 2:
                        {
                            system("CLS");
                            std::cout << "\n";
                            bk.patchConcrect(settings.mainDir, allowedNames);
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
                bk.avtor(VER);
                bk.input(settings.mainDir, settings.FolderName);
                break;
            }

            // Настройки папок
            case 2:
            {
                system("CLS");

                do
                {

                    std::cout << "_____________________\n";
                    std::cout << "1 - Поменять основную папку\n";
                    std::cout << "2 - Поменять создаваемую папку\n ";
                    std::cout << "\n0 - Меню\n";
                    bk.daw();


                    std::cin >> inp2;

               
                    switch (inp2)
                    {
                        case 1:
                        {
                            system("CLS");
                            std::cin.ignore();
                            bk.ChangeMainDir(config_path, settings);
                            break;
                        }
                        case 2:
                        {
                            system("CLS");
                            std::cin.ignore();
                            bk.ChangeFolderName(config_path,settings);
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
                bk.avtor(VER);
                bk.input(settings.mainDir, settings.FolderName);
                break;
            }

            // Бекап
            case 3:
            {
                system("CLS");

                do
                {
                    std::cout << "_____________________\n";
                    std::cout << "1 - Сделать бэкап\n";
                    std::cout << "2 - Сделать бэкап (без фильтра)\n ";
                    std::cout << "\n0 - Меню\n";
                    bk.daw();

                    std::cin >> inp2;

                    switch (inp2)
                    {
                    case 1:
                        system("CLS");
                        bk.createFolder(settings.mainDir, settings.FolderName, allowedNames, settings);
                        if (settings.OpenDir == true)
                        {
                            bk.OpenMainDir(settings.mainDir);
                        }

                        break;

                    case 2:
                        system("CLS");
                        bk.createFolderWF(settings.mainDir, settings.FolderName, allowedNames, settings);
                        if (settings.OpenDir == true)
                        {
                            bk.OpenMainDir(settings.mainDir);
                        }

                        break;

                    default:
                        system("cls");
                        break;
                    }
                } while (inp2 != 0);


                system("CLS");
                bk.avtor(VER);
                bk.input(settings.mainDir, settings.FolderName);
                break;
            }

            case 4:
            {
                system("CLS");

                do
                {
                std::cout << "0 - Выкл | 1 - Вкл\n";
                std::cout << "_____________________\n";
                std::cout << "1 - Режим архивирования\t\t\t\t" << "Состояние: " << settings.Zip << "\n";
                std::cout << "2 - Удалить создаваемую папку после .zip\t" << "Состояние: " << settings.DelFolder << "\n";
                std::cout << "3 - Открыть основную папку после бэкапа\t\t" << "Состояние: " << settings.OpenDir << "\n";
                std::cout << "\n0 - Меню\n";
                bk.daw();

                std::cin >> inp2;


                switch (inp2)
                {
                    case 1:
                        system("cls");
                        settings.Zip = !settings.Zip;
                        bk.save_settings(settings, config_path);
                        break;
                    case 2:
                        system("cls");
                        settings.DelFolder = !settings.DelFolder;
                        bk.save_settings(settings, config_path);
                        break;
                    case 3:
                        system("cls");
                        settings.OpenDir = !settings.OpenDir;
                        bk.save_settings(settings, config_path);
                        break;
                    default:
                        system("cls");
                        break;
                }

                } while (inp2 != 0);

                system("CLS");
                bk.avtor(VER);
                bk.input(settings.mainDir, settings.FolderName);
                break;
            }

            default:
            {
                system("CLS");
                bk.avtor(VER);
                bk.input(settings.mainDir, settings.FolderName);
                break;
            }
        }
        
    } while (inp != 0);

    

    system("pause");
}

