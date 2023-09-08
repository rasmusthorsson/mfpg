#pragma once

namespace noteenums {

	enum class Note {
		A = 5, 
		B = 6, 
		C = 0, 
		D = 1, 
		E = 2, 
		F = 3, 
		G = 4
	};

	enum Accidental {
		Sharp, 
		Flat, 
		Natural, 
		None
	};

	enum Duration {
		Double, 
		Whole, 
		Half, 
		Quarter, 
		Eighth, 
		Sixteenth, 
		ThirtySecond, 
		SixtyFourth
	};

}
