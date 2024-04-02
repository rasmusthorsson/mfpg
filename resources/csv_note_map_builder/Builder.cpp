#include <fstream>
#include <initializer_list>
#include <string>
#include <vector>

#include "Builder.h"

#include "../../src/NoteEnums.h"


std::string Builder::build_file_CUSTOM() {
	//Make your own notemapper here.
	return "";
}


//This function can be used to create individual rows of CSV values.
std::string Builder::build_row(noteenums::Note n, std::initializer_list<std::string> list) {
	std::string ret = "";
	ret += noteenums::to_string(n);
	for (auto e : list) {
		ret += ",";
		ret += e;
	}
	ret += "\n";
	return ret;
}

Builder::Builder(noteenums::Note f, noteenums::Note l) {
	for (int i = static_cast<int>(f); i <= static_cast<int>(l); i++) {
		notes.push_back(static_cast<noteenums::Note>(i));
	}
}

Builder::~Builder() {}


//Example CSV build file which is equivalent to the "BasicNoteMapper" class.
std::string Builder::build_file() {
	using namespace noteenums;
	using namespace std;
	
	//First we must specify the attribute names as the column names of the CSV file. These columns 
	//MUST correspond to the attribute names exactly as specified in the DSL.
	string ret = "STRING,FINGER,HAND_POS\n";

	//Here we define what a REST note means.
	ret += build_row(Note::REST, {to_string(0), to_string(0), to_string(0)});	
	
	//Ranges are the notes to be considered for each string.
	std::vector<std::pair<int, int>> ranges({{43, 68}, {50, 75}, {57, 82}, {64, 89}});
	for (int i = 0; i < ranges.size(); i++) {

		//String position is implicitly declared in the ranges index.
		int string_position = i + 1;
		
		//The playable notes for this string is dictated by the notes vector using the ranges
		//as the offsets.
		vector<Note> playable_notes;
		for (int j = ranges[i].first; j <= ranges[i].second; j++) {
			playable_notes.push_back(notes[j]);
		}

		//The amount of notes is equivalent to the amount of playable notes, -2 because the first
		//note is dealt with below, then the size is off by one so -2 accounts for both of those
		//cases.
		int note_amount = playable_notes.size() - 2;

		//First note is always played on the empty string
		ret += build_row(static_cast<Note>(playable_notes[0]), 
				{to_string(string_position), 
				to_string(0), 
				to_string(0)});

		//For all other notes
		for (int note = 0; note <= note_amount; note = note + 2) {

			//Lowest Hand Position that a note can be played in is either 1 (which is the lowest
			//possible hand position), or position of the note - 3. The position of the note
			//is caluclated like this because each hand position can play two notes, so we
			//calculate the position by dividing by 2 and then adding 1 to account for uneven
			//note positions. -3 is because the lowest hand position can play the note using 
			//the highest finger, the highest finger can reach an extra 3 positions.
			int lowest_hand_position = max(1, ((note / 2) + 1) - 3);

			//Similarly, the Highest Hand Position either the position of the highest note (and
			//then -3 because of the finger reach limiting how high a hand position can be in 
			//this case), or the position of the note itself.
			int highest_hand_position = min((note / 2) + 1, ((note_amount / 2) + 1) - 3);

			//There are 4 possible fingers, but for lower hand positions only a subset of those
			//fingers can be used, therefore we calculate fingers relative to the lowest hand
			//position.
			int fingers = (note / 2) + 1 - lowest_hand_position + 1;

			//We then iterate through all possible hand positions for this note, and decrease
			//fingers by 1 for each iteration while we increase hand position by 1.
			for (int hand_position = lowest_hand_position; 
				 hand_position <= highest_hand_position; 
				 hand_position++) {
					//Add the calculated permutation for that note.
					ret += build_row(static_cast<Note>(playable_notes[note + 1]),
							{to_string(string_position), 
							to_string(fingers), 
							to_string(hand_position)});
				if (note != note_amount) { 
					ret += build_row(static_cast<Note>(playable_notes[note + 2]),
							{to_string(string_position), 
							to_string(fingers), 
							to_string(hand_position)});
				}
				fingers--;
			}
		}
	}
	return ret;
}
