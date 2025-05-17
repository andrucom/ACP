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
std::string suffix = "zZCP";
std::string suffix_limited = "L_";
std::string suffix_full = "F_";

namespace backup
{
    //backup::Back::Settings settings;

    void Back::show(const std::unordered_set<std::string> s) {
        std::unordered_set<std::string>::iterator it;
        for (it = s.begin(); it != s.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }

    void Back::avtor(const std::string Ver)
    {
        std::cout << "�����������: ������� ������ ��������\n";
        std::cout << "������: " << Ver;
        std::cout << "\n\n\n";
    }

    void Back::patchAll(const fs::path path)
    {
        if (fs::exists(path))
        {
            std::cout << "��� ����������� � " << path << "\n";
            std::cout << "---------------------- \n";
            for (const auto& entry : fs::directory_iterator(path))
            {

                std::cout << "\t" << entry.path().stem() << std::endl;

            }
            std::cout << "____________________________\n\n";
        }
        else 
        {

            std::cerr << "\t\t������: " << path << " �� ����������\n";
        }
        
    }

    void Back::patchConcrect(const fs::path path, const std::unordered_set<std::string> allowedNames)
    {
        std::cout << "��� ����������� � " << path << "    � ��������: ";
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
            std::cerr << "\t\t������: " << path << " �� ����������\n";
        }
    }

    void Back::input(const fs::path path, const std::string folder_name)
    {
        std::cout << "\n\n�������� �����: " << path << "\n";
        std::cout << "�������� ����� �����: " << folder_name;
        std::cout << "\n============================= \n";
        std::cout << "1 - ������ � �������\n";
        std::cout << "2 - ��������� �����\n";
        std::cout << "3 - �����\n";
        std::cout << "4 - ���������";
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
     

        // �����
        if (fs::exists(source))
        { 
            try {
                std::string folder_name1 = origname;
                fs::path sourcefolder = destination.string() + "/" + folder_name1;
                // ����
                fs::path dir_path = destination / folder_name1;
                if (fs::is_directory(source))
                {
                    fs::create_directory(dir_path);
                }
                else
                {

                }


                //std::cout << "\t����� �: " << sourcefolder.string() << " � ������ " << folder_name ;
                //std::cout << "\n\t������ " << source << " --- " << destination << " \n ";

                fs::copy(source, sourcefolder, fs::copy_options::recursive | fs::copy_options::overwrite_existing);
                std::cout << "\t����� �����������: " << source << " -> " << sourcefolder << "\n\n";


            }
            catch (const fs::filesystem_error& e) {
               std::cerr << "\t-->> ������ �����������: " << e.what() << std::endl;

            }
        }
        else
        {
            std::cerr << "\t\t-->> ������: " << source << " �� ����������\n";
        }

    }

    void Back::createFolder(const fs::path& path, std::string folder_name, std::unordered_set<std::string> allowedNames, Settings settings)
    {
        // �����
        if (fs::exists(path))
        {
            std::string folder_name1 = suffix + suffix_limited + folder_name + time();
            // ����
            fs::path dir_path = path / folder_name1;
            fs::create_directory(dir_path);
            std::cout << "\n>> ����� �������! " << dir_path;
            std::cout << "\n��������... \n";
            std::string filepathEnd = path.string() + "/" + folder_name1;

            for (const auto& entry : fs::directory_iterator(path))
            {
                std::string filename = entry.path().filename().string();
                fs::path filepath = entry.path();

                if (allowedNames.count(filename) > 0)
                {

                    //std::cout << "\n\t������ " << filepath << " === " << filepathEnd << " \n ";
                    copyDirectory(filepath, filepathEnd, filename);
                    //std::cout << "\t����� � ����� " << filepath << " ����������� � " << filepathEnd << " C ������ " << filename << "\n";
                    
                }
            }
            
            if (settings.Zip == true)
            {
                zip(filepathEnd);
            }
       

        }
        else
        {
            std::cerr << "\t\t-->> ������: " << path << " �� ����������\n";
        }
    }

    // ��� �������
    void Back::createFolderWF(const fs::path& path, std::string folder_name, std::unordered_set<std::string> allowedNames, Settings settings)
    {
        // �����
        if (fs::exists(path))
        {
            std::string folder_name1 = suffix + suffix_full + folder_name + time();
            fs::path dir_path = path / folder_name1;
            fs::create_directory(dir_path);
            std::cout << "\n>> ����� �������! " << dir_path;
            std::cout << "\n��������... \n";
            std::string filepathEnd = path.string() + "/" + folder_name1;


            for (const auto& entry : fs::directory_iterator(path))
            {
                fs::path filepath = entry.path();
                if (entry.path().string().find(suffix) == std::string::npos) //entry.path() != filepathEnd
                {
                    std::string filename = entry.path().filename().string();


                    //std::cout << "\n------ " << filepath << " " << filepathEnd;

                    copyDirectory(filepath, filepathEnd, filename);
                }
                else
                {
                    std::cout << "\n>-xxx-- �����  " << filepath << "\n";
                }
            }
           
            if (settings.Zip == true)
            {
                zip(filepathEnd);
            }

        }
        else
        {
            std::cerr << "\t\t-->> ������: " << path << " �� ����������\n";
        }
    }

    void Back::OpenMainDir(const std::string path)
    {

        std::string fullpath = "explorer " + path;
        std::replace(fullpath.begin(), fullpath.end(), '/', '\\');
        system(fullpath.c_str());


    }


}
