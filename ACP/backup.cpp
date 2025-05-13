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


namespace fs = std::filesystem;


namespace backup
{

    void Back::show(std::unordered_set<std::string> s) {
        std::unordered_set<std::string>::iterator it;
        for (it = s.begin(); it != s.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }

    void Back::avtor(std::string Ver)
    {
        std::cout << "�����������: ������� ������ ��������\n";
        std::cout << "������: ";
        std::cout << Ver;
        std::cout << "\n\n\n";
    }

    void Back::patchAll(fs::path path)
    {
        for (const auto& entry : fs::directory_iterator(path))
        {

            std::cout << "\t" << entry.path().stem() << std::endl;

        }
        std::cout << "____________________________\n\n";
    }

    void Back::patchConcrect(fs::path path)
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

    void Back::input(int inp, fs::path path, std::string folder_name)
    {
        std::cout << "\n\n�������� �����: " << path << "\n";
        std::cout << "�������� ����� �����: " << folder_name;
        std::cout << "\n============================= \n";
        std::cout << "1 - ����������� ��� ����� � ������� ����\n";
        std::cout << "2 - ����������� ��� �����, ������� ������������ �������\n";
        std::cout << "3 - ������� �����\n";
        std::cout << "\n�����: ";
        std::cin >> inp;
        std::cin.ignore();

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
     
        // �������� ���������� ��� ����������

        // �����

        std::string folder_name1 = origname;
        fs::path sourcefolder = destination.string() + "/" + folder_name1;
        // ����
        fs::path dir_path = destination / folder_name1;
        fs::create_directory(dir_path);

        //std::cout << "\t����� �: " << sourcefolder.string() << " � ������ " << folder_name ;
        //std::cout << "\n\t������ " << source << " --- " << destination << " \n ";

        fs::copy(source, sourcefolder, fs::copy_options::recursive | fs::copy_options::overwrite_existing);
        std::cout << "\t\t����� �����������: " << source << " -> " << sourcefolder << "\n\n";
        

    }

    void Back::createFolder(const fs::path& path, std::string folder_name)
    {
        // �����
        std::string folder_name1 = folder_name + time();
        // ����
        fs::path dir_path = path / folder_name1;
        fs::create_directory(dir_path);
        std::cout << "\n>> ����� �������! " << dir_path;
        std::cout << "\n��������... \n";
        std::string filepathEnd = path.string() + "/" + folder_name1;
        for (const auto& entry : fs::recursive_directory_iterator(path))
        {
            std::string filename = entry.path().filename().string();
            std::string filepath = entry.path().string();

            if (allowedNames.count(filename) > 0)
            {
                //std::cout << "\n\t������ " << filepath << " === " << filepathEnd << " \n ";
                copyDirectory(filepath, filepathEnd, filename);
                //std::cout << "\t����� � ����� " << filepath << " ����������� � " << filepathEnd << " C ������ " << filename << "\n";
            }
        }
    }
  
}
