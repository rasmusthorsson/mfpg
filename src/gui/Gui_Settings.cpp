#include "Gui_Settings.h"

std::string _S(enum Settings s) {
	if (s >= SettingsCount || s < 0) {
		return "None";
	}
	return std::string(Settings_str[s]);
}

Settings S_(const std::string s) {
	for (int i = 0; i < sizeof(Settings_str); i++) {
		if (s == Settings_str[i]) {
			return Settings_enums[i];
		}
	}
	return Settings::UNDEFINED;
}
