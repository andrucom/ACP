#pragma once
#include <fstream>
#include <string>
#include <unordered_set>




namespace fs = std::filesystem;

namespace backup
{
	class Back
	{
	public:
		std::string ChangeMainDir()
		{
			std::string newpath;
			std::cout << "Введите путь папки: ";
			std::cin >> newpath;
			std::cout << "Готово! ";
			std::cout << "\n\n";
			return newpath;
			
		}
		std::string time()
		{
			auto now = std::chrono::system_clock::now();
			auto in_time_t = std::chrono::system_clock::to_time_t(now);

			// Форматируем дату
			std::stringstream ss;
			ss << std::put_time(std::localtime(&in_time_t), "%d.%m.%Y_%H.%M");
			std::string date_str = ss.str();
			return date_str;
		}
		void show(const std::unordered_set<std::string> s);
		void avtor(const std::string Ver);
		void patchAll(const fs::path path);
		void patchConcrect(const fs::path path, const std::unordered_set<std::string> allowedNames);
		void input(const int inp, const fs::path path, const std::string folder_name);
		void zip(const std::string& folderPath);
		void copyDirectory(const fs::path& source, const fs::path& destination, const std::string origname);
		void createFolder(const fs::path& path, std::string folder_name, std::unordered_set<std::string> allowedNames);

	};
}