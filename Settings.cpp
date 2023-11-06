#include "Settings.h"
#include "SettingsParser.h"
#include <string_view>
#include <sstream>
#include <fstream>
#include <iostream>
#include <ctype.h>
#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>

#define APP_NAME "airwindows-compressors-ui"


Settings settings;


void Settings::read_settings_files()
{
	// $XDG_CONFIG_HOME/$app_name/settings is actually the only settings file we
	// read.

	std::string config_dir;
	const char* env_dir = getenv("XDG_CONFIG_HOME");
	if (env_dir)
		config_dir = env_dir;
	else {
		// Default to ~/.config.
		std::string home_dir = home_path();
		if (!home_dir.empty())
			config_dir = home_dir + "/.config";
		}
	if (!config_dir.empty())
		read_settings_file(config_dir + "/" APP_NAME "/settings");
}


static void set_setting(std::string_view setting_name, std::string_view value_token, SettingsParser* parser)
{
	bool ok = true;
	//***
	if (setting_name == "TBD") {
		//*** Do something...
		}
	else
		parser->errors << "Unknown setting: " << setting_name << "." << std::endl;

	if (!ok)
		parser->errors << "Settings: bad value for \"" << setting_name << "\"";
}

void Settings::read_settings_file(std::string path)
{
	std::fstream file(path);
	if (!file.is_open()) {
		// All settings files are optional, so don't complain if it doesn't
		// exist.
		return;
		}
	std::string contents(
		(std::istreambuf_iterator<char>(file)),
		std::istreambuf_iterator<char>());
	SettingsParser parser(contents.data(), contents.size());
	parser.parse(
		[&](std::string_view setting_name, std::string_view value_token) {
			set_setting(setting_name, value_token, &parser);
			});

	settings.errors += parser.errors.str();
}


std::string Settings::home_path()
{
	const char* home_dir = getenv("HOME");
	if (home_dir == nullptr) {
		const struct passwd* user_info = getpwuid(getuid());
		if (user_info && user_info->pw_dir[0])
			home_dir = user_info->pw_dir;
		}
	if (home_dir == nullptr)
		return "";
	return home_dir;
}



