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
		void show(std::unordered_set<std::string> s);
		void avtor(std::string ver);
		void patchAll(fs::path path);
		void patchConcrect(fs::path path);
		void input(int inp, fs::path path, std::string folder_name);
		void zip(const std::string& folderPath);
		void copyDirectory(const fs::path& source, const fs::path& destination, const std::string origname);
		void createFolder(const fs::path& path, std::string folder_name);

	};
}