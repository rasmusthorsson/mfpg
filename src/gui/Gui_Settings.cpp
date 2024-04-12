#include "Gui_Settings.h"

std::string _S(enum Settings s) {
	if (s >= SettingsCount || s < 0) {
		return "None";
	}
	return std::string(Settings_str[s]);
}
