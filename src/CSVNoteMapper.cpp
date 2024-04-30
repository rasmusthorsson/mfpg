#include "CSVNoteMapper.h"
#include <fstream>
#include "NoteEnums.h"
#include "ExValException.h"
#include "NoteMapperException.h"

extern int TUPLESIZE;
extern std::string ATTRIBUTE_TYPES;
extern std::vector<std::string> ATTRIBUTES;

CSVNoteMapper::CSVNoteMapper(std::string fp, const std::vector<IString>& list) {
	std::ifstream csv_file;
	csv_file.open(fp);
	std::string linebuffer;

	//Expected CSV columns
	std::vector<std::string> csv_columns = ATTRIBUTES;
	csv_columns.push_back("Note");
	
	//ordered found columns, ordered according to order of appearance.
	std::vector<std::pair<std::string, std::string>> csv_columns_ordered;
	
	std::string word = "";
	int count = 0;
	
	//First line should correspond to the column names
	if (csv_file) {
		getline(csv_file, linebuffer);
		linebuffer.push_back(','); //Hack for iterating the last word

		//Iterates through the characters in the line.
		for (int i = 0; i < linebuffer.size(); i++) {
			if (linebuffer[i] == ',') {
				//Iterate through the expected csv_columns
				for (auto attr_itr = csv_columns.begin(); attr_itr != csv_columns.end(); attr_itr++) {
					if (word == *attr_itr) {
						std::erase(csv_columns, word);
						//if its not the first word (which is always "Note").
						if (count != 0) {
							std::string type = "";
							type += ATTRIBUTE_TYPES[count-1];
							csv_columns_ordered.push_back(std::make_pair(type, word));
						}
						break;
					}
				}
				count++;
				word.clear();
			} else {
				word += linebuffer[i];
			}
		}
		if (TUPLESIZE != count - 1 ) {
			throw (NoteMapperException("There are more CSV column names in the note mapper CSV file than there are declared Attributes."));
		} 
		if (csv_columns.size() > 0) {
			throw (NoteMapperException("Not every Attibute declared is named in the CSV note mapper file."));
		}
	} else {
		throw (NoteMapperException("Could not open CSV File"));
	}
	noteenums::Note note;
	//For the rest of the lines.
	while (csv_file) {
		std::vector<std::pair<const std::string, ExValContainer>> line = {};
		word.clear();
		count = 0;
		getline(csv_file, linebuffer);
		//If it's not the last line.
		if (linebuffer.size() != 0) {
			linebuffer.push_back(','); //This causes issues if its the last line
			for (int i = 0; i < linebuffer.size(); i++) {
				if (linebuffer[i] == ',') {
					if (count == 0) {
						//First CSV entry column is the note.
						note = noteenums::from_string(word);
					} else {
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
						}
					}
					word.clear();
					count++;
				} else {
					//If no ',' is encountered, add character to the word.
					word += linebuffer[i];
				}
			}
			if (TUPLESIZE != count - 1) {
				throw (NoteMapperException("Not enough columns specified for CSV row"));
			}
			try {
				//Add value to the full_map, which represents all lines found in the CSV
				//file.
				PhysAttrMap p_map(line);
				full_map.insert({note, p_map});
			} catch (ExValException e) {
				std::cout << e.what() << "\n";
			}
		}
	}
	//Add REST note to mapped_notes, then select all lines found in full_map that are notes on the
	//strings.
	mapped_notes.insert(std::make_pair(noteenums::Note::REST, PhysAttrMap({0, 0, 0})));
	for (auto &str : list) {
		mapString(str);
	}
}


CSVNoteMapper::~CSVNoteMapper() {}

//Only add notes to the actual map if that note is specified on the strings and part of the CSV.
void CSVNoteMapper::mapString(const IString& s) {

	//If there is a string attribute
	bool string_exists = false;
	for (auto a : ATTRIBUTES) {
		if ("STRING" == a) {
			string_exists = true;
		}
	}
	//For each note on the string we check through all notes specified in the CSV file and add the
	//ones that are in both the string playable notes and the CSV file.
	for (auto note : s.getPlayable()) {
		auto range = full_map.equal_range(note);
		for (auto i = range.first; i != range.second; ++i) {
			if (string_exists) {
				if (i->second.getVal("STRING") == s.getPosition()) {
					mapped_notes.insert(std::make_pair(i->first, i->second));
				}
			} else {
				mapped_notes.insert(std::make_pair(i->first, i->second));
			}
		}
	}
}
