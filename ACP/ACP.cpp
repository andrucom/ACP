﻿#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <unordered_set>
#include <filesystem>
#include <chrono>
#include <sstream>
#include <cstdlib>


int inp;
std::string folder_name = "zdahalove_";

const char* path = "C:/Test";
const char* Ver = "0.0.1";

namespace fs = std::filesystem;

std::unordered_set<std::string> allowedNames = { "test1","test2","testttt"};
std::ofstream fout;
std::ifstream fin;

void show(std::unordered_set<std::string> s) {
    std::unordered_set<std::string>::iterator it;
    for (it = s.begin(); it != s.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void avtor()
{
    std::cout << "Разработчик: Чупиков Андрей Петрович\n";
    std::cout << "Версия: ";
    std::cout << Ver;
    std::cout << "\n\n\n";
}

void patchAll()
{
    for (const auto& entry : fs::directory_iterator(path))
    {

        std::cout << "\t" << entry.path().stem() << std::endl;

    }
    std::cout << "____________________________\n\n";
}

void patchConcrect()
{
    for (const auto& entry : fs::directory_iterator(path))
    {
        std::string filename = entry.path().filename().string();

        if (allowedNames.count(filename) > 0)
        {
            std::cout << "\t" << entry.path().stem() << std::endl;
        }
        
    }
    std::cout << "____________________________\n\n";
}

void input()
{
    std::cout << "\n\nОсновная папка: " << path << "\n";
    std::cout << "Название новой папки: " << folder_name;
    std::cout << "\n============================= \n";
    std::cout << "1 - Просмотреть все папки в главной папк\n";
    std::cout << "2 - Просмотреть все папки, которые соответсвуют фильтру\n";
    std::cout << "3 - Сделать бекап\n";
    std::cout << "\nВыбор: ";
    std::cin >> inp;
}

void zip(const std::string& folderPath) {
    std::string command;

#ifdef _WIN32
    command = "powershell Compress-Archive -Path " + folderPath + " -DestinationPath " + folderPath + ".zip";
#else
    command = "zip -r " + folderPath + ".zip " + folderPath;
#endif

    system(command.c_str());
}

std::string time()
{
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    // Форматируем дату
    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%m.%d.%Y_%H.%M");
    std::string date_str = ss.str();
    return date_str;
}

void copyDirectory(const fs::path& source, const fs::path& destination, const std::string origname) {
    try {
        // Копируем рекурсивно все содержимое

        // Папка
      
        std::string folder_name = origname;
        fs::path sourcefolder = destination.string() + "/" + folder_name;
        // Путь
        fs::path dir_path = destination / folder_name;
        fs::create_directory(dir_path);

        //std::cout << "\tПапка в: " << sourcefolder.string() << " С именем " << folder_name ;
        //std::cout << "\n\tСоздаю " << source << " --- " << destination << " \n ";

        fs::copy(source, sourcefolder, fs::copy_options::recursive | fs::copy_options::overwrite_existing );
        std::cout << "\t\tПапка скопирована: " << source << " -> " << sourcefolder << "\n\n";
    }
    catch (const fs::filesystem_error& e) {
        //std::cerr << "Ошибка копирования: " << e.what() << std::endl;
        
    }
}

void createFolder(const fs::path& path)
{
    // Папка
    std::string folder_name1 = folder_name + time();
    // Путь
    fs::path dir_path = path / folder_name1;
    fs::create_directory(dir_path);
    std::cout << "\n>> Папка создана! " << dir_path;
    std::cout << "\nКопируем... \n";
    std::string filepathEnd = path.string() + "/" + folder_name1;
    for (const auto& entry : fs::recursive_directory_iterator(path))
    {
        std::string filename = entry.path().filename().string();
        std::string filepath = entry.path().string();

        if (allowedNames.count(filename) > 0)
        {
            //std::cout << "\n\tСоздаю " << filepath << " === " << filepathEnd << " \n ";
            copyDirectory(filepath, filepathEnd, filename);
            //std::cout << "\tПапка с путем " << filepath << " Скопирована в " << filepathEnd << " C именем " << filename << "\n";
        }
    }
}



int main()
{
    setlocale(LC_ALL, "Russian");
    avtor();
    input();

    do
    {
        switch (inp)
        {
            case 1:
            {
                system("CLS");
                std::cout << "Вывод всех папок: \n";
                patchAll();
                input();
                break;
            }
            case 2:
            {
                system("CLS");
                std::cout << "Вывод некоторых папок:        " << "Фильтр: ";
                show(allowedNames);
                std::cout << "\n";
                patchConcrect();
                input();
                break;
            }
            case 3:
            {
                system("CLS");
                std::cout;
                createFolder(path);
                input();
                break;
            }
            default:
            {
                system("CLS");
                avtor();
                input();
                break;
            }
        }
    } while (inp != 0);

    

    system("pause");
}

