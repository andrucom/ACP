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




namespace fs = std::filesystem;


namespace backup
{

    void Back::show(const std::unordered_set<std::string> s) {
        std::unordered_set<std::string>::iterator it;
        for (it = s.begin(); it != s.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }

    void Back::avtor(const std::string Ver)
    {
        std::cout << "Разработчик: Чупиков Андрей Петрович\n";
        std::cout << "Версия: " << Ver;
        std::cout << "\n\n\n";
    }

    void Back::patchAll(const fs::path path)
    {
        for (const auto& entry : fs::directory_iterator(path))
        {

            std::cout << "\t" << entry.path().stem() << std::endl;

        }
        std::cout << "____________________________\n\n";
    }

    void Back::patchConcrect(const fs::path path, const std::unordered_set<std::string> allowedNames)
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

    void Back::input(const fs::path path, const std::string folder_name)
    {
        std::cout << "\n\nОсновная папка: " << path << "\n";
        std::cout << "Название новой папки: " << folder_name;
        std::cout << "\n============================= \n";
        std::cout << "1 - Просмотреть все папки в главной папк\n";
        std::cout << "2 - Просмотреть все папки, которые соответсвуют фильтру\n";
        std::cout << "3 - Сделать бекап\n";
        std::cout << "4 - Изменить основную папку\n";
        std::cout << "5 - Изменить имя создаваеой папки\n";
        std::cout << "\n>>";

    }

    void Back::zip(const std::string& folderPath) {
        std::string command;

        #ifdef _WIN32
        command = "powershell Compress-Archive -Path " + folderPath + " -DestinationPath " + folderPath + ".zip";
        #else
        command = "zip -r " + folderPath + ".zip " + folderPath;
        #endif

        system(command.c_str());
    }

    void Back::copyDirectory(const fs::path& source, const fs::path& destination, const std::string origname) {
     
        // Копируем рекурсивно все содержимое

        // Папка
        try {
            std::string folder_name1 = origname;
            fs::path sourcefolder = destination.string() + "/" + folder_name1;
            // Путь
            fs::path dir_path = destination / folder_name1;
            fs::create_directory(dir_path);

            //std::cout << "\tПапка в: " << sourcefolder.string() << " С именем " << folder_name ;
            //std::cout << "\n\tСоздаю " << source << " --- " << destination << " \n ";

            fs::copy(source, sourcefolder, fs::copy_options::recursive | fs::copy_options::overwrite_existing);
            std::cout << "\t\tПапка скопирована: " << source << " -> " << sourcefolder << "\n\n";
        }
        catch (const fs::filesystem_error& e) {
           // std::cerr << "Ошибка копирования: " << e.what() << std::endl;

        }

    }

    void Back::createFolder(const fs::path& path, std::string folder_name, std::unordered_set<std::string> allowedNames)
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
   
    void Back::OpenMainDir(const std::string path)
    {

        std::string fullpath = "explorer " + path;
        std::replace(fullpath.begin(), fullpath.end(), '/', '\\');
        system(fullpath.c_str());
        std::cout << fullpath;

    }
}
