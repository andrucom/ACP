#pragma once
#include <fstream>
#include <string>
#include <unordered_set>
#include <algorithm>
#include "json.hpp"

using json = nlohmann::json;
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
			std::string mainDir = "C:/Test";
			std::string FolderName = "BackUp_";
		};

		std::string daw() // >>
		{
			std::string placeholder;
			std::cout << u8"\n\n\n>> ";
			return placeholder;
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
		void init(const fs::path path);
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
		void ChangeMainDir(const fs::path& config_path, Back::Settings& s);
		void ChangeFolderName(const fs::path& config_path, Back::Settings& s);

		// Сохранение настроек в файл
		static void save_settings(const Settings& settings, const fs::path& path);

		// Загрузка настроек из файла
		static Settings load_settings(const fs::path& path);




	};
	void to_json(json& j, const Back::Settings& s);

	// Десериализация JSON в Settings
	void from_json(const json& j, Back::Settings& s);

}
