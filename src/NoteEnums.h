#ifndef NOTE_ENUMS_H_MFPG
#define NOTE_ENUMS_H_MFPG

#include <string>
#include <iostream>
#include <vector>

#define HIGHEST_NOTE 107

//Simple way to define notes as we do not need functionality offered by the more 
//complex mx representation.
namespace noteenums {
	enum class Note {
		REST = -1,
		C_0 = 0, Cs_0 = 1, D_0 = 2, Ds_0 = 3, E_0 = 4, F_0 = 5,
	        Fs_0 = 6, G_0 = 7, Gs_0 = 8, A_0 = 9, As_0 = 10, B_0 = 11,	
		C_1 = 12, Cs_1 = 13, D_1 = 14, Ds_1 = 15, E_1 = 16, F_1 = 17,
	        Fs_1 = 18, G_1 = 19, Gs_1 = 20, A_1 = 21, As_1 = 22, B_1 = 23,	
		C_2 = 24, Cs_2 = 25, D_2 = 26, Ds_2 = 27, E_2 = 28, F_2 = 29,
	        Fs_2 =30, G_2 = 31, Gs_2 = 32, A_2 = 33, As_2 = 34, B_2 = 35,	
		C_3 = 36, Cs_3 = 37, D_3 = 38, Ds_3 = 39, E_3 = 40, F_3 = 41,
	        Fs_3 = 42, G_3 = 43, Gs_3 = 44, A_3 = 45, As_3 = 46, B_3 = 47,	
		C_4 = 48, Cs_4 = 49, D_4 = 50, Ds_4 = 51, E_4 = 52, F_4 = 53,
	        Fs_4 = 54, G_4 = 55, Gs_4 = 56, A_4 = 57, As_4 = 58, B_4 = 59,	
		C_5 = 60, Cs_5 = 61, D_5 = 62, Ds_5 = 63, E_5 = 64, F_5 = 65,
	        Fs_5 = 66, G_5 = 67, Gs_5 = 68, A_5 = 69, As_5 = 70, B_5 = 71,	
		C_6 = 72, Cs_6 = 73, D_6 = 74, Ds_6 = 75, E_6 = 76, F_6 = 77,
	        Fs_6 = 78, G_6 = 79, Gs_6 = 80, A_6 = 81, As_6 = 82, B_6 = 83,	
		C_7 = 84, Cs_7 = 85, D_7 = 86, Ds_7 = 87, E_7 = 88, F_7 = 89,
	        Fs_7 = 90, G_7 = 91, Gs_7 = 92, A_7 = 93, As_7 = 94, B_7 = 95,	
		C_8 = 96, Cs_8 = 97, D_8 = 98, Ds_8 = 99, E_8 = 100, F_8 = 101,
	        Fs_8 = 102, G_8 = 103, Gs_8 = 104, A_8 = 105, As_8 = 106, B_8 = 107
	};

	enum class Duration {
		DoubleDur = 8, 
		Whole = 7, 
		Half = 6, 
		Quarter = 5, 
		Eighth = 4, 
		Sixteenth = 3, 
		ThirtySecond = 2, 
		SixtyFourth = 1
	};
	inline std::string to_string(const Duration& d) {
		const std::vector<std::string> durations = {"SixtyFourth", "ThirtySecond", "Sixteenth",
			"Eighth", "Quarter", "Half", "Whole", "Double"};
		return durations[static_cast<int>(d)];
	}
	inline std::string to_string(const Note& n) {
		if (n == noteenums::Note::REST) {
			return std::string("REST");
		} 
		const std::vector<std::string> bases = {"C", "Cs", "D", "Ds", "E", "F", 
							"Fs", "G", "Gs", "A", "As", "B"};
		const std::string base = bases[static_cast<int>(n) % 12];
		const std::string octave = std::to_string(static_cast<int>(n)/12);
		return (base + "_" + octave);
	}
	inline Note from_string(std::string s) {
		const std::vector<std::string> bases = {"C", "Cs", "D", "Ds", "E", "F", 
							"Fs", "G", "Gs", "A", "As", "B"};
		const std::vector<std::string> octaves {"0", "1", "2", "3", "4", "5", "6", "7", "8"};
		if (s == "REST") {
			return Note::REST;
		}
		std::string base;
		std::string temp;
		for (int i = 0; i < s.size(); i++) {
			if (s[i] == '_') {
				base = temp;
				temp = "";
			} else {
				temp.push_back(s[i]);		
			}
		}
		int ret = -1;
		for (int i = 0; i < bases.size(); i++) {
			if (bases[i] == base) {
				ret = i;	
				break;
			}
		}
		if (ret == -1) {
			//TODO Exception? Other solution?
			return Note::REST;
		}
		int oct = -1;
		for (int i = 0; i < octaves.size(); i++) {
			if (octaves[i] == temp) {
				oct = i;
			}
		}
		if (oct == -1) {
			//TODO Exception? Other solution?
			return Note::REST;
		}
		ret += 12 * oct;
		return static_cast<Note>(ret);
	}
}


//Outputting note to output stream.
inline std::ostream& operator << (std::ostream& out, const noteenums::Note& n) {
	out << to_string(n);
	return out;	
}
//Outputting duration to output stream.
inline std::ostream& operator << (std::ostream& out, const noteenums::Duration& d) {
	out << to_string(d);
	return out;	
}
#endif
