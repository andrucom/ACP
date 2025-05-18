#pragma once
#include <fstream>
#include <string>
#include <unordered_set>
#include <algorithm>


namespace fs = std::filesystem;

namespace backup
{
	class Back
	{
	public:
		struct Settings
		{
			bool Zip = false;
			bool DelFolder = false;
			bool OpenDir = true;
		};
		std::string daw() // >>
		{
			std::string placeholder;
			std::cout << "\n\n\n>> ";
			return placeholder;
		}
		std::string ChangeFolderName()
		{
			std::string newfoldername;
			std::cout << "������� ��� ����������� �����: ";
			std::cin >> newfoldername;
			std::cout << "������! ";
			std::cout << "\n\n";
			return newfoldername;

		}
		std::string ChangeMainDir()
		{
			std::string newpath;
			std::cout << "������� ���� �����: ";
			std::cin >> newpath;
			std::cout << "������! ";
			std::cout << "\n\n";
			return newpath;
			
		}
		std::string time()
		{
			auto now = std::chrono::system_clock::now();
			auto in_time_t = std::chrono::system_clock::to_time_t(now);

			// ����������� ����
			std::stringstream ss;
			ss << std::put_time(std::localtime(&in_time_t), "%d.%m.%Y_%H.%M");
			std::string date_str = ss.str();
			return date_str;
		}
		void init();
		void show(const std::unordered_set<std::string> s);
		void avtor(const std::string Ver);
		void patchAll(const fs::path path);
		void patchConcrect(const fs::path path, const std::unordered_set<std::string> allowedNames);
		void input(const fs::path path, const std::string folder_name);
		void zip(const std::string& folderPath);
		void copyDirectory(fs::path& source, const fs::path& destination, std::string origname);
		void createFolder(const fs::path& path, std::string folder_name, std::unordered_set<std::string> allowedNames, Settings settings);
		void createFolderWF(const fs::path& path, std::string folder_name, std::unordered_set<std::string> allowedNames, Settings settings);
		void OpenMainDir(const std::string path);

	};
}