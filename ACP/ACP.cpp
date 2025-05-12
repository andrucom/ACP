
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


int inp;

const char* path = "C:/Test";
const char* Ver = "0.0.1";

namespace fs = std::filesystem;

std::unordered_set<std::string> allowedNames = { "test1","test2" };
std::ofstream fout;
std::ifstream fin;

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

        std::cout << entry.path().stem() << std::endl;

    }
}

void patchConcrect()
{
    for (const auto& entry : fs::directory_iterator(path))
    {
        std::string filename = entry.path().filename().string();

        if (allowedNames.count(filename) > 0)
        {
            std::cout << entry.path().stem() << std::endl;
        }

    }
}

void input()
{
    std::cout << "\n\nВыбор: ";
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

void copyDirectory(const fs::path& source, const fs::path& destination) {
    try {
        // Копируем рекурсивно все содержимое

        std::cout << "\n\tСоздаю ";
        std::cout << source;
        std::cout << " --- ";
        std::cout << destination;
        std::cout << " \n ";

        fs::copy(source, destination, fs::copy_options::recursive | fs::copy_options::overwrite_existing );
        std::cout << "Папка скопирована: " << source << " -> " << destination << std::endl;
    }
    catch (const fs::filesystem_error& e) {
        std::cerr << "Ошибка копирования: " << e.what() << std::endl;
    }
}

void createFolder(const fs::path& path)
{
    // Получаем текущую дату
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    // Форматируем дату
    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%m.%d.%Y");
    std::string date_str = ss.str();
    // Папка
    std::string folder_name = "zdahalove_" + date_str;
    // Путь
    fs::path dir_path = path / folder_name;
    fs::create_directory(dir_path);
    std::cout << "\nПапка создана! " ;
    std::cout << dir_path;

    std::cout << "\nКопируем... \n";
    std::string filepathEnd = path.string() + "/" + folder_name;
    for (const auto& entry : fs::recursive_directory_iterator(path))
    {
        std::string filename = entry.path().filename().string();
        std::string filepath = entry.path().string();

        if (allowedNames.count(filename) > 0)
        {   
            std::cout << "\n\tСоздаю ";
            std::cout << filepath;
            std::cout << " === ";
            std::cout << filepathEnd;
            std::cout << " \n ";
            copyDirectory(filepath, filepathEnd);
        }
    }
    std::cout << "\nСжимаем...\n";
    zip(filepathEnd);

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
                std::cout << "Вывод некоторых папок: \n";
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
        }
    } while (inp != 0);

    

    system("pause");
}

