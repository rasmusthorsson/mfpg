#include "CSVNoteMapper.h"
#include <fstream>
#include "NoteEnums.h"
#include "ExValException.h"
#include "NoteMapperException.h"

extern int TUPLESIZE;
extern std::string ATTRIBUTE_TYPES;
extern std::vector<std::string> ATTRIBUTES;

CSVNoteMapper::CSVNoteMapper(std::string fp, const std::vector<IString>& list) {
	//File reading
	std::ifstream csv_file;
	csv_file.open(fp);
	std::string linebuffer;

	//Expected CSV columns
	std::vector<std::string> used_columns = ATTRIBUTES;
	used_columns.push_back("Note");
	
	//ordered found columns, ordered according to order of appearance.
	std::vector<std::pair<std::string, std::string>> csv_columns_ordered;

	//indices of used columns in relation to all columns in the CSV file
	std::vector<int> column_indices;
	
	std::string word = "";
	int count = 0;
	
	//First line should correspond to the column names
	if (csv_file) {
		getline(csv_file, linebuffer);
		linebuffer.push_back(','); //Hack for iterating the last word
		
		//Iterates through the characters in the line.
		while (linebuffer.size() > 0) {
			int _break = linebuffer.find_first_of(',');
			word = linebuffer.substr(0, _break);
			linebuffer.erase(0, _break + 1);

			//Iterate through the expected csv_columns
			for (auto attr_itr = used_columns.begin(); attr_itr != used_columns.end(); 
											attr_itr++) {
				if (word == *attr_itr) {
					std::erase(used_columns, word);
					column_indices.push_back(count);
					//if its not the first word (which is always "Note").
					if (count != 0) {
						std::string type = "";
						type += ATTRIBUTE_TYPES[count-1];
						csv_columns_ordered.push_back(std::make_pair(type, word));
					}
					count++;
					break;
				}
			}
		}
		if (used_columns.size() > 0) {
			throw (NoteMapperException("Not every Attibute declared is named in the CSV note mapper file."));
		}
	} else {
		throw (NoteMapperException("Could not open CSV File"));
	}

	//For the rest of the lines.
	noteenums::Note note;
	bool used_column = false;
	while (csv_file) {
		getline(csv_file, linebuffer);
		//If the line is empty it should not be processed.
		if (linebuffer.size() != 0) {
			linebuffer.push_back(','); 
			std::vector<std::pair<const std::string, ExValContainer>> line = {};
			count = 0;

			while (linebuffer.size() > 0) {

				//Find next word
				int _break = linebuffer.find_first_of(',');
				word = linebuffer.substr(0, _break);
				linebuffer.erase(0, _break + 1);

				//Check whether the current CSV column corresponds to one of the columns
				//selected by the ATTRIBUTES
				for (int i : column_indices) {
					if (count == i) {
						used_column = true;
						break;
					}
				}

				//First CSV entry column is the note.
				if (count == 0) {
					note = noteenums::from_string(word);
				//If we are using this column, process it.
				} else if (used_column) {
					//Subsequent CSV entry columns are values of the attribute
					//specified in the ordered CSV columns.
					std::string attr = csv_columns_ordered[count-1].second;

					//Each attribute must be converted to a string using the
					//correct conversion function, since attributes can only be
					//integers, doubles, or booleans this is enough.
					if (csv_columns_ordered[count-1].first == "i") {
						int i = std::stoi(word);
						line.push_back(std::make_pair(attr, ExValContainer(i)));
					} else if (csv_columns_ordered[count-1].first == "d") {
						double d = std::stod(word);
						line.push_back(std::make_pair(attr, ExValContainer(d)));
					} else if (csv_columns_ordered[count-1].first == "b") {
						bool b = std::stoi(word);
						line.push_back(std::make_pair(attr, ExValContainer(b)));
					} else {
						throw (NoteMapperException("Could not find type of attribute: " + attr));
					}
				}
				count++;
				used_column = false;
			}
			try {
				//Add value to the full_map, which represents all lines found in the CSV
				//file.
				PhysAttrMap p_map(line);
				auto v_range = full_map.equal_range(note);
				bool duplicate = false;
				for (auto itr_s = v_range.first; itr_s != v_range.second; ++itr_s) {
					if (itr_s->second == p_map) {
						duplicate = true;
						break;
					}
				}
				if (!duplicate) {
					full_map.insert({note, p_map});
				}
			} catch (ExValException e) {
				throw e;
			}
		}
	}
	//Add REST note to mapped_notes, then select all lines found in full_map that are notes on the
	//strings.
	auto rest_range = full_map.equal_range(noteenums::Note::REST);
		for (auto rest = rest_range.first; rest != rest_range.second; ++rest) {
			mapped_notes.insert(std::make_pair(rest->first, rest->second));
		}
	for (auto &str : list) {
		mapString(str);
	}
}


CSVNoteMapper::~CSVNoteMapper() {}

//Only add notes to the actual map if that note is specified on the strings and part of the CSV.
void CSVNoteMapper::mapString(const IString& s) {

	//If there is a string attribute
	std::vector<std::string> strs{"STRING", "String", "string", "str"};
	bool string_exists = false;
	std::string string_attr;
	for (auto a : ATTRIBUTES) {
		for (auto s : strs) {
			if (a == s) {
				string_exists = true;
				string_attr = s;
				break;
			}
		}
	}
	//For each note on the string we check through all notes specified in the CSV file and add the
	//ones that are in both the string playable notes and the CSV file.
	for (auto note : s.getPlayable()) {
		auto range = full_map.equal_range(note);
		for (auto i = range.first; i != range.second; ++i) {
			if (string_exists) {
				if (i->second.getVal(string_attr) == s.getPosition()) {
					mapped_notes.insert(std::make_pair(i->first, i->second));
				}
			} else {
				mapped_notes.insert(std::make_pair(i->first, i->second));
			}
		}
	}
}
