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

			//The following definition of Hand Positions is different from conventional violin 
			//hand position definitions. Here we define a hand position capable of playing 2 
			//notes per finger, and incrementing the position itself by 2 notes each increase. 
			//This is a much simpler way to define hand positions and provides an easier base for
			//understanding and experimenting with the program itself. For a more accurate 
			//representation, see the build_file_full function below this one.

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

//Builder for the currently default supported attributes, more accurate than the basicnotemapper
std::string Builder::build_file_full() {
	using namespace noteenums;
	using namespace std;
	
	//First we must specify the attribute names as the column names of the CSV file. These columns 
	//MUST correspond to the attribute names exactly as specified in the DSL.
	string ret = "STRING,FINGER,HAND_POS,EXTENSION,STROKE_DIRECTION\n";

	//Here we define what a REST note means.
	ret += build_row(Note::REST, {to_string(0), to_string(0), to_string(0), to_string(0), to_string(0)});
	
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

		//First note is always played on the empty string
		ret += build_row(static_cast<Note>(playable_notes[0]), 
				{to_string(string_position), 
				to_string(0), 
				to_string(0),
				to_string(0),
				to_string(-1)});
		ret += build_row(static_cast<Note>(playable_notes[0]), 
				{to_string(string_position), 
				to_string(0), 
				to_string(0),
				to_string(0),
				to_string(1)});

		//Note that this implementation differs from the one in the basic notemapper, and the one
		//in the function above since those ones are not accurate to how positions actually work. 
		//They are instead meant as simple examples of how to construct a notemapper, while this
		//one is more complex but meant to be more accurate.
		
		//TODO: I am not sure the definitions of positions below is 100% accurate.

		//Position -> Finger -> Note -> Extension(Low = -1, Normal = 0, High = 1) and Relative Note.
		std::vector<std::vector<std::vector<std::tuple<int, int>>>> positions({
				//First
				{{{-1, 1}, {0, 2}}, 
				{{-1, 3}, {0, 4}}, 
				{{0, 5}, {1, 6}}, 
				{{0, 7}}},
				//Second
				{{{-1, 3}, {0, 4}},
				{{-1, 5}, {1, 6}},
				{{0, 7}, {1, 8}},
				{{0, 9}}},
				//Third
				{{{0, 5}},
				{{-1, 6}, {1, 7}},
				{{0, 8}, {1, 9}},
				{{0, 10}, {1, 11}}},
				//Fourth
				{{{0, 7}},
				{{-1, 8}, {1, 9}},
				{{0, 10}, {1, 11}},
				{{0, 12}}},
				//Fifth
				{{{0, 9}},
				{{-1, 10}, {1, 11}},
				{{0, 12}, {1, 13}},
				{{0, 14}, {1, 15}}},
				//Sixth
				{{{-1, 10}, {0, 11}},
				{{-1, 12}, {1, 13}},
				{{0, 14}, {1, 15}},
				{{0, 16}}},
				//Seventh
				{{{0, 12}},
				{{-1, 13}, {1, 14}},
				{{0, 15}, {1, 16}},
				{{-1, 17}, {0, 18}}}});

		for (int pos = 0; pos < positions.size(); pos++) {
			for (int finger = 0; finger < 4; finger++) {
				for (auto f_note : positions[pos][finger]) {
					ret += build_row(static_cast<Note>(
								playable_notes[std::get<1>(f_note)]),
							{to_string(string_position),
							to_string(finger + 1),
							to_string(pos + 1),
							to_string(std::get<0>(f_note)),
							to_string(-1)});
					ret += build_row(static_cast<Note>(
								playable_notes[std::get<1>(f_note)]),
							{to_string(string_position),
							to_string(finger + 1),
							to_string(pos + 1),
							to_string(std::get<0>(f_note)),
							to_string(1)});
				}
			}
		}
	}
	return ret;
}

