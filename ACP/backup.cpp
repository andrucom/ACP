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
std::string prefix = "zZCP";
std::string suffix_limited = "L_";
std::string suffix_full = "F_";

namespace backup
{

    void Back::init(const fs::path path)
    {
        fs::path dir_path = path / "ACP";
        if (fs::exists(dir_path))
        {

        }
        else
        {
            fs::create_directory(dir_path);
        }
    }

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
        if (fs::exists(path))
        {
            std::cout << "Все находящиеся в " << path << "\n";
            std::cout << "---------------------- \n";
            for (const auto& entry : fs::directory_iterator(path))
            {

                std::cout << "\t" << entry.path().stem() << std::endl;

            }
            std::cout << "____________________________\n\n";
        }
        else 
        {

            std::cerr << "\t\tОшибка: " << path << " не существует\n";
        }
        
    }

    void Back::patchConcrect(const fs::path path, const std::unordered_set<std::string> allowedNames)
    {
        std::cout << "Все находящиеся в " << path << "    С фильтром: ";
        show(allowedNames);
        std::cout << "---------------------- \n";

        if (fs::exists(path))
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
        else
        {
            std::cerr << "\t\tОшибка: " << path << " не существует\n";
        }
    }

    void Back::input(const fs::path path, const std::string folder_name)
    {
        std::cout << "\n\nОсновная папка: " << path << "\n";
        std::cout << "Название новой папки: " << folder_name;
        std::cout << "\n============================= \n";
        std::cout << "1 - Работа с папками\n";
        std::cout << "2 - Настройки папок\n";
        std::cout << "3 - Бэкап\n";
        std::cout << "4 - Настройки";
        daw();

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

    void Back::copyDirectory(fs::path& source, const fs::path& destination, std::string origname) {
     

        // Папка
        if (fs::exists(source))
        { 
            try {
                std::string folder_name1 = origname;
                fs::path sourcefolder = destination.string() + "/" + folder_name1;
                // Путь
                fs::path dir_path = destination / folder_name1;
                if (fs::is_directory(source))
                {
                    fs::create_directory(dir_path);
                }
                else
                {

                }


                //std::cout << "\tПапка в: " << sourcefolder.string() << " С именем " << folder_name ;
                //std::cout << "\n\tСоздаю " << source << " --- " << destination << " \n ";

                fs::copy(source, sourcefolder, fs::copy_options::recursive | fs::copy_options::overwrite_existing);
                std::cout << "\tПапка скопирована: " << source << " -> " << sourcefolder << "\n\n";


            }
            catch (const fs::filesystem_error& e) {
               std::cerr << "\t-->> Ошибка копирования: " << e.what() << "\n\n";
               
               system("pause");
            }
        }
        else
        {
            std::cerr << "\t\t-->> Ошибка: " << source << " не существует\n";
        }

    }

    void Back::createFolder(const fs::path& path, std::string folder_name, std::unordered_set<std::string> allowedNames, Settings settings)
    {
        // Папка
        if (fs::exists(path))
        {
            std::string folder_name1 = prefix + suffix_limited + folder_name + time();
            // Путь
            fs::path dir_path = path / folder_name1;
            fs::create_directory(dir_path);
            std::cout << "\n>> Папка создана! " << dir_path;
            std::cout << "\nКопируем... \n";
            std::string filepathEnd = path.string() + "/" + folder_name1;

            for (const auto& entry : fs::directory_iterator(path))
            {
                std::string filename = entry.path().filename().string();
                fs::path filepath = entry.path();

                if (allowedNames.count(filename) > 0)
                {

                    //std::cout << "\n\tСоздаю " << filepath << " === " << filepathEnd << " \n ";
                    copyDirectory(filepath, filepathEnd, filename);
                    //std::cout << "\tПапка с путем " << filepath << " Скопирована в " << filepathEnd << " C именем " << filename << "\n";
                    
                }
            }
            
            if (settings.Zip == true)
            {
                zip(filepathEnd);
                if (settings.DelFolder == true)
                {
                    std::cout << "\nУдаление\n";
                    remove_all(path / folder_name1);
                    std::cout << "Папка удалена!\n";
                }
            }
       

        }
        else
        {
            std::cerr << "\t\t-->> Ошибка: " << path << " не существует\n";
        }
    }

    // Без фильтра
    void Back::createFolderWF(const fs::path& path, std::string folder_name, std::unordered_set<std::string> allowedNames, Settings settings)
    {
        // Папка
        if (fs::exists(path))
        {
            std::string folder_name1 = prefix + suffix_full + folder_name + time();
            fs::path dir_path = path / folder_name1;
            fs::create_directory(dir_path);
            std::cout << "\n>> Папка создана! " << dir_path;
            std::cout << "\nКопируем... \n";
            std::string filepathEnd = path.string() + "/" + folder_name1;


            for (const auto& entry : fs::directory_iterator(path))
            {
                fs::path filepath = entry.path();
                if (entry.path().string().find(prefix) == std::string::npos) //entry.path() != filepathEnd
                {
                    std::string filename = entry.path().filename().string();


                    //std::cout << "\n------ " << filepath << " " << filepathEnd;

                    copyDirectory(filepath, filepathEnd, filename);
                }
                else
                {
                    std::cout << "\n>-xxx-- ИГНОР  " << filepath << "\n";
                }
            }
           
            if (settings.Zip == true)
            {
                zip(filepathEnd);
                std::cout << "\nСоздан\n";
                if (settings.DelFolder == true)
                {
                    std::cout << "\nУдаление\n";
                    remove_all(path / folder_name1);
                    std::cout << "Папка удалена!\n";
                }
            }

        }
        else
        {
            std::cerr << "\t\t-->> Ошибка: " << path << " не существует\n";
        }
    }

    void Back::OpenMainDir(const std::string path)
    {

        std::string fullpath = "explorer " + path;
        std::replace(fullpath.begin(), fullpath.end(), '/', '\\');
        system(fullpath.c_str());


    }

    void Back::save_settings(const Settings& settings, const fs::path& path) {
        json j = settings; // Автоматически вызывает to_json
        std::ofstream file(path);
        if (file) {
            file << j.dump(4);
        }
        else {
            throw std::runtime_error("Failed to save settings");
        }
    }

    Back::Settings Back::load_settings(const fs::path& path) {
        if (!fs::exists(path)) {
            return Settings{}; // Возвращаем настройки по умолчанию
        }

        std::ifstream file(path);
        json j;
        file >> j;
        return j.get<Settings>(); // Автоматически вызывает from_json
    }

    void Back::ChangeMainDir(const fs::path& config_path, Back::Settings& s)
    {
        std::cout << "Введите путь папки: ";
        std::cin >> s.mainDir;
        backup::Back::save_settings(s, config_path);
        std::cout << "Готово! ";
        std::cout << "\n\n";

    }

    void Back::ChangeFolderName(const fs::path& config_path, Back::Settings& s)
    {
        std::cout << "Задайте имя создаваемой папки: ";
        std::cin >> s.FolderName;
        backup::Back::save_settings(s, config_path);
        std::cout << "Готово! ";
        std::cout << "\n\n";


    }

    // Реализация to_json
    void to_json(json& j, const Back::Settings& s) {
        j = json{
            {"Zip", s.Zip},
            {"DelFolder", s.DelFolder},
            {"OpenDir", s.OpenDir},
            {"mainDir", s.mainDir },
            {"FolderName", s.FolderName }
        };
    }

    // Реализация from_json
    void from_json(const json& j, Back::Settings& s) {
        j.at("Zip").get_to(s.Zip);
        j.at("DelFolder").get_to(s.DelFolder);
        j.at("OpenDir").get_to(s.OpenDir);
        j.at("mainDir").get_to(s.mainDir);
        j.at("FolderName").get_to(s.FolderName);

    }

}
