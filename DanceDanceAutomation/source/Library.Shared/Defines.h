#pragma once

#include <map>
#include <string>

namespace DanceDanceAutomation
{
	//Common
	static const std::float_t PatternMultiplier = 1.0f;


	//Beginner
	static const std::map<const std::string, std::map<const std::string, std::size_t>> BeginnerTransitionProbabilities
	{
		{
			"Common",
			{
				{ "1000->1000", 4948 },
				{ "0100->0010", 1667 },
				{ "0010->0100", 1636 },
				{ "1000->0001", 1118 },
				{ "0001->1000", 1112 },
				{ "1000->0100", 1002 }
			}
		},

		{
			"Medium",
			{
				{ "1000->0010", 981 },
				{ "0100->0001", 966 },
				{ "0001->0100", 963 },
				{ "0010->0001", 953 },
				{ "0010->1000", 940 },
				{ "0001->0010", 933 },
				{ "0100->1000", 924 },
				{ "0010->0010", 498 },
				{ "0001->0001", 481 },
				{ "0100->0100", 476 }
			}
		},

		{
			"Rare",
			{
				{ "1001->1000", 107 },
				{ "0001->1001", 103 },
				{ "1001->0001", 83 },
				{ "1000->1001", 77 },
				{ "0010->0110", 28 },
				{ "0100->0110", 25 },
				{ "0100->1001", 24 },
				{ "0010->1001", 23 },
				{ "0110->0100", 18 },
				{ "0110->0010", 14 },
				{ "0110->1000", 8 },
				{ "1001->0110", 7 },
				{ "0110->1001", 6 },
				{ "1001->0010", 5 },
				{ "0110->0001", 5 },
				{ "1000->0110", 4 },
				{ "0001->0110", 4 },
				{ "1001->0100", 3 },
				{ "1100->0001", 2 },
				{ "0110->0110", 1 },
				{ "0100->1100", 1 },
				{ "0011->1000", 1 },
				{ "0010->1100", 1 }
			}
		}
	};

	static const std::size_t Beginner_AverageNumberOfPatternsPerMeasure = (std::size_t)(4 * PatternMultiplier);
	static const std::float_t Beginner_StandardDeviationDivider = 1.0f;


	//Easy
	static const std::map<const std::string, std::map<const std::string, std::size_t>> EasyTransitionProbabilities
	{
		{
			"Common",
			{
				{ "0100->0010", 12710 },
				{ "0010->0100", 12565 },
				{ "1000->0001", 11584 },
				{ "0001->1000", 11476 },
				{ "0001->0100", 7596 },
				{ "1000->0010", 7461 },
				{ "0010->1000", 7421 },
				{ "0100->0001", 7411 },
				{ "1000->0100", 7345 },
				{ "0001->0010", 7322 },
				{ "0010->0001", 7291 },
				{ "0100->1000", 7187 }
			}
		},

		{
			"Medium",
			{
				{ "1000->1000", 1259 },
				{ "0100->0100", 1256 },
				{ "0001->0001", 1206 },
				{ "0010->0010", 1171 },
				{ "0100->0110", 613 },
				{ "0010->0110", 597 },
				{ "1000->1001", 498 },
				{ "1001->1000", 482 },
				{ "1001->0001", 478 },
				{ "0001->1001", 466 },
				{ "0110->0100", 405 },
				{ "0110->0010", 402 },
				{ "0001->0101", 301 },
				{ "1000->1010", 297 },
				{ "0110->1000", 285 },
				{ "1000->1100", 281 },
				{ "0001->0011", 275 },
				{ "0010->1010", 275 },
				{ "0101->0001", 261 },
				{ "0010->0011", 259 },
				{ "0100->0101", 258 },
				{ "0110->0001", 253 },
				{ "0100->1100", 247 },
				{ "1010->1000", 247 },
				{ "0011->0001", 227 },
				{ "1100->1000", 217 },
				{ "1001->0100", 187 },
				{ "1100->0100", 171 },
				{ "1001->0010", 170 },
				{ "1010->0010", 168 },
				{ "0011->0010", 167 },
				{ "0101->0100", 165 },
				{ "1010->0100", 158 },
				{ "0101->0010", 149 },
				{ "1001->1001", 146 },
				{ "1100->0010", 142 },
				{ "0011->0100", 137 },
				{ "0010->1001", 129 },
				{ "0011->1000", 129 },
				{ "0101->1000", 121 },
				{ "1010->0001", 121 },
				{ "0100->1001", 118 },
				{ "0110->0101", 118 },
				{ "1010->0110", 117 },
				{ "0011->0110", 108 },
				{ "0110->0011", 108 },
				{ "1100->0001", 108 },
				{ "1100->0110", 106 },
				{ "0110->1010", 100 }
			}
		},

		{
			"Rare",
			{
				{ "0101->0110", 95 },
				{ "0110->1100", 95 },
				{ "0001->0110", 92 },
				{ "0011->1001", 91 },
				{ "0101->1001", 90 },
				{ "1100->1001", 83 },
				{ "0110->0110", 82 },
				{ "1001->1010", 80 },
				{ "1010->1001", 79 },
				{ "0010->0101", 76 },
				{ "0100->0011", 75 },
				{ "0100->1010", 73 },
				{ "1001->0101", 71 },
				{ "0010->1100", 69 },
				{ "0001->1100", 67 },
				{ "1000->0011", 67 },
				{ "1000->0110", 67 },
				{ "0001->1010", 65 },
				{ "1000->0101", 65 },
				{ "1001->1100", 64 },
				{ "1001->0011", 60 },
				{ "1010->1100", 50 },
				{ "0101->0011", 49 },
				{ "0110->1001", 44 },
				{ "0101->0101", 43 },
				{ "0011->0011", 39 },
				{ "1100->1100", 39 },
				{ "0011->0101", 38 },
				{ "1010->1010", 34 },
				{ "1100->1010", 34 },
				{ "1001->0110", 23 },
				{ "0101->1010", 12 },
				{ "0011->1010", 9 },
				{ "1100->0101", 9 },
				{ "0011->1100", 8 },
				{ "1010->0101", 8 },
				{ "1100->0011", 8 },
				{ "1111->1000", 5 },
				{ "0110->1111", 4 },
				{ "1010->0011", 4 },
				{ "1111->0001", 4 },
				{ "0101->1100", 2 },
				{ "0101->1111", 2 },
				{ "0001->1101", 1 },
				{ "0001->1110", 1 },
				{ "0010->1111", 1 },
				{ "0011->1111", 1 },
				{ "1000->1110", 1 },
				{ "1001->1111", 1 },
				{ "1010->1111", 1 },
				{ "1100->1111", 1 },
				{ "1101->0010", 1 },
				{ "1101->1101", 1 },
				{ "1110->0011", 1 },
				{ "1110->1101", 1 },
				{ "1111->1111", 1 }
			}
		}
	};

	static const std::size_t Easy_AverageNumberOfPatternsPerMeasure = (std::size_t)(9 * PatternMultiplier);
	static const std::float_t Easy_StandardDeviationDivider = 1.25f;


	//Medium
	static const std::map<const std::string, std::map<const std::string, std::size_t>> MediumTransitionProbabilities
	{
		{
			"Common",
			{
				{ "0100->0010", 15272 },
				{ "0010->0100", 15147 },
				{ "1000->0001", 14274 },
				{ "0001->1000", 14174 },
				{ "0001->0100", 9221 },
				{ "0010->1000", 9097 },
				{ "1000->0010", 9084 },
				{ "0100->0001", 9042 },
				{ "1000->0100", 8985 },
				{ "0001->0010", 8964 },
				{ "0010->0001", 8906 },
				{ "0100->1000", 8853 }
			}
		},

		{
			"Medium",
			{
				{ "0100->0100", 1336 },
				{ "0010->0010", 1269 },
				{ "1000->1000", 1179 },
				{ "0001->0001", 1149 },
				{ "0100->0110", 658 },
				{ "0010->0110", 637 },
				{ "1000->1001", 500 },
				{ "1001->0001", 486 },
				{ "1001->1000", 477 },
				{ "0001->1001", 475 },
				{ "0110->0010", 403 },
				{ "0110->0100", 403 },
				{ "0001->0101", 340 },
				{ "1000->1010", 330 },
				{ "1000->1100", 324 },
				{ "0001->0011", 297 },
				{ "0110->0001", 293 },
				{ "0010->1010", 288 },
				{ "0110->1000", 283 },
				{ "0100->0101", 272 },
				{ "0010->0011", 265 },
				{ "0100->1100", 262 },
				{ "1010->1000", 247 },
				{ "0101->0001", 242 },
				{ "0011->0001", 228 },
				{ "1100->1000", 218 },
				{ "0101->0100", 204 },
				{ "1010->0010", 204 },
				{ "1100->0100", 200 },
				{ "0011->0010", 181 },
				{ "1001->0100", 172 },
				{ "0101->0010", 167 },
				{ "1001->0010", 163 },
				{ "1010->0100", 158 },
				{ "0011->0100", 155 },
				{ "1100->0010", 155 },
				{ "0011->1000", 138 },
				{ "1001->1001", 136 },
				{ "1010->0110", 134 },
				{ "0110->0101", 127 },
				{ "0101->1000", 123 },
				{ "1010->0001", 122 },
				{ "0010->1001", 121 },
				{ "0100->1001", 112 },
				{ "1100->0001", 111 },
				{ "1100->0110", 104 },
				{ "0110->1100", 102 },
				{ "0110->0011", 100 }
			}
		},

		{
			"Rare",
			{
				{ "0011->0110", 96 },
				{ "0011->1001", 90 },
				{ "0101->0110", 90 },
				{ "1001->1010", 90 },
				{ "1100->1001", 90 },
				{ "0110->0110", 89 },
				{ "0101->1001", 87 },
				{ "0110->1010", 86 },
				{ "1001->0101", 81 },
				{ "1001->0011", 75 },
				{ "1010->1001", 73 },
				{ "0100->1010", 70 },
				{ "1001->1100", 69 },
				{ "0001->0110", 68 },
				{ "0100->0011", 68 },
				{ "0010->0101", 65 },
				{ "0010->1100", 57 },
				{ "0101->0011", 56 },
				{ "0101->0101", 54 },
				{ "0110->1001", 52 },
				{ "0001->1100", 50 },
				{ "1000->0110", 50 },
				{ "1000->0101", 49 },
				{ "1010->1100", 49 },
				{ "0011->0011", 46 },
				{ "0001->1010", 45 },
				{ "1000->0011", 45 },
				{ "1100->1010", 45 },
				{ "1010->1010", 42 },
				{ "0011->0101", 41 },
				{ "1100->1100", 40 },
				{ "0101->1010", 21 },
				{ "1001->0110", 18 },
				{ "1100->0011", 17 },
				{ "0011->1100", 13 },
				{ "1010->0101", 10 },
				{ "1010->0011", 9 },
				{ "0101->1100", 6 },
				{ "1100->0101", 6 },
				{ "0011->1010", 5 },
				{ "1111->1111", 2 },
				{ "0010->1111", 1 },
				{ "0101->1111", 1 },
				{ "1001->1111", 1 },
				{ "1111->1000", 1 }
			}
		}
	};

	static const std::size_t Medium_AverageNumberOfPatternsPerMeasure = (std::size_t)(10 * PatternMultiplier);
	static const std::float_t Medium_StandardDeviationDivider = 1.5f;


	//Hard
	static const std::map<const std::string, std::map<const std::string, std::size_t>> HardTransitionProbabilities
	{
		{
			"Common",
			{
				{ "0100->0010", 21614 },
				{ "0010->0100", 21455 },
				{ "0001->1000", 19496 },
				{ "1000->0001", 19433 },
				{ "0001->0100", 13306 },
				{ "0100->0001", 13144 },
				{ "1000->0010", 13093 },
				{ "1000->0100", 13009 },
				{ "0001->0010", 12970 },
				{ "0010->0001", 12962 },
				{ "0010->1000", 12941 },
				{ "0100->1000", 12715 }
			}
		},

		{
			"Medium",
			{
				{ "0100->0100", 1713 },
				{ "0010->0010", 1677 },
				{ "1000->1000", 1547 },
				{ "0001->0001", 1531 },
				{ "0010->0110", 714 },
				{ "0100->0110", 695 },
				{ "1000->1001", 569 },
				{ "0001->1001", 548 },
				{ "1001->1000", 510 },
				{ "1001->0001", 507 },
				{ "0110->1000", 425 },
				{ "0110->0001", 407 },
				{ "0110->0100", 402 },
				{ "0110->0010", 401 },
				{ "1000->1010", 392 },
				{ "0001->0011", 387 },
				{ "0001->0101", 367 },
				{ "0010->1010", 367 },
				{ "0100->1100", 363 },
				{ "0100->0101", 347 },
				{ "1000->1100", 347 },
				{ "0010->0011", 313 },
				{ "1010->1000", 274 },
				{ "1001->0010", 269 },
				{ "0101->0001", 261 },
				{ "1100->1000", 258 },
				{ "1010->0100", 249 },
				{ "0011->0001", 240 },
				{ "1001->0100", 240 },
				{ "1001->1001", 240 },
				{ "0011->0100", 227 },
				{ "0101->0010", 226 },
				{ "1100->0010", 225 },
				{ "0011->1000", 212 },
				{ "0101->1000", 212 },
				{ "1100->0001", 212 },
				{ "0101->0100", 211 },
				{ "0011->0010", 203 },
				{ "1010->0001", 200 },
				{ "1010->0010", 191 },
				{ "1010->0110", 181 },
				{ "1100->0100", 173 },
				{ "0110->0101", 166 },
				{ "1100->0110", 165 },
				{ "0011->0110", 162 },
				{ "0110->1100", 150 },
				{ "0110->0110", 148 },
				{ "0110->1010", 146 },
				{ "0101->0110", 142 },
				{ "0110->0011", 140 },
				{ "0100->1001", 139 },
				{ "0010->1001", 137 },
				{ "1100->1001", 136 },
				{ "0101->1001", 129 },
				{ "1001->0101", 124 },
				{ "1010->1001", 124 },
				{ "0011->1001", 115 },
				{ "0101->0101", 109 },
				{ "1001->0011", 108 },
				{ "1001->1010", 106 },
				{ "0010->0101", 101 }
			}
		},

		{
			"Rare",
			{
				{ "0010->1100", 98 },
				{ "1010->1010", 98 },
				{ "1100->1100", 98 },
				{ "0001->0110", 94 },
				{ "0100->1010", 93 },
				{ "0100->0011", 92 },
				{ "0101->0011", 92 },
				{ "0011->0011", 90 },
				{ "1010->1100", 89 },
				{ "1001->1100", 88 },
				{ "0001->1100", 82 },
				{ "1100->1010", 82 },
				{ "1000->0011", 78 },
				{ "0001->1010", 75 },
				{ "0011->0101", 70 },
				{ "1000->0101", 67 },
				{ "1000->0110", 67 },
				{ "0101->1010", 57 },
				{ "0011->1100", 53 },
				{ "0110->1001", 53 },
				{ "1010->0101", 44 },
				{ "1100->0011", 44 },
				{ "1010->0011", 38 },
				{ "1100->0101", 38 },
				{ "0011->1010", 36 },
				{ "0101->1100", 36 },
				{ "1001->0110", 33 },
				{ "1011->0001", 5 },
				{ "0001->1110", 4 },
				{ "0010->1111", 4 },
				{ "1101->0001", 4 },
				{ "1110->0001", 4 },
				{ "0010->1011", 3 },
				{ "0100->1101", 3 },
				{ "0100->1111", 3 },
				{ "0111->0001", 3 },
				{ "1000->1011", 3 },
				{ "1000->1111", 3 },
				{ "1101->1000", 3 },
				{ "1111->1000", 3 },
				{ "0010->0111", 2 },
				{ "0010->1110", 2 },
				{ "0011->1011", 2 },
				{ "0111->0111", 2 },
				{ "0111->1000", 2 },
				{ "1000->0111", 2 },
				{ "1000->1101", 2 },
				{ "1000->1110", 2 },
				{ "1001->1011", 2 },
				{ "1001->1110", 2 },
				{ "1011->1000", 2 },
				{ "1011->1011", 2 },
				{ "1110->1110", 2 },
				{ "1111->0001", 2 },
				{ "1111->0010", 2 },
				{ "1111->0100", 2 },
				{ "1111->1111", 2 },
				{ "0001->1101", 1 },
				{ "0001->1111", 1 },
				{ "0011->1101", 1 },
				{ "0011->1110", 1 },
				{ "0100->0111", 1 },
				{ "0100->1110", 1 },
				{ "0101->1011", 1 },
				{ "0101->1111", 1 },
				{ "0110->0111", 1 },
				{ "0111->0010", 1 },
				{ "0111->1100", 1 },
				{ "1001->0111", 1 },
				{ "1001->1101", 1 },
				{ "1001->1111", 1 },
				{ "1010->0111", 1 },
				{ "1010->1111", 1 },
				{ "1011->0010", 1 },
				{ "1011->0100", 1 },
				{ "1011->1100", 1 },
				{ "1101->1001", 1 },
				{ "1101->1101", 1 },
				{ "1110->0100", 1 },
				{ "1110->0101", 1 }
			}
		}
	};

	static const std::size_t Hard_AverageNumberOfPatternsPerMeasure = (std::size_t)(13 * PatternMultiplier);
	static const std::float_t Hard_StandardDeviationDivider = 1.75f;


	//Challenge
	static const std::map<const std::string, std::map<const std::string, std::size_t>> ChallengeTransitionProbabilities
	{
		{
			"Common",
			{
				{ "0100->0010", 39008 },
				{ "0010->0100", 38811 },
				{ "1000->0001", 36778 },
				{ "0001->1000", 36639 },
				{ "0001->0100", 25325 },
				{ "0100->0001", 24992 },
				{ "0001->0010", 24272 },
				{ "0010->0001", 24165 },
				{ "1000->0100", 23534 },
				{ "1000->0010", 23523 },
				{ "0010->1000", 23365 },
				{ "0100->1000", 23132 }
			}
		},

		{
			"Medium",
			{
				{ "0100->0100", 3085 },
				{ "0010->0010", 2981 },
				{ "1000->1000", 2103 },
				{ "0001->0001", 2094 },
				{ "0010->0110", 1036 },
				{ "0100->0110", 1009 },
				{ "0001->1001", 745 },
				{ "1000->1001", 734 },
				{ "1001->1000", 732 },
				{ "1001->0001", 699 },
				{ "1000->1010", 691 },
				{ "0110->0001", 678 },
				{ "0001->0101", 665 },
				{ "0110->1000", 656 },
				{ "1000->1100", 631 },
				{ "0001->0011", 630 },
				{ "0110->0010", 570 },
				{ "0110->0100", 570 },
				{ "0100->0101", 567 },
				{ "0010->1010", 565 },
				{ "0100->1100", 533 },
				{ "0010->0011", 509 },
				{ "0011->1000", 480 },
				{ "0101->0010", 479 },
				{ "1100->0001", 458 },
				{ "1010->1000", 451 },
				{ "0101->1000", 450 },
				{ "1010->0100", 447 },
				{ "1010->0001", 436 },
				{ "1100->1000", 430 },
				{ "1001->0100", 422 },
				{ "1001->0010", 420 },
				{ "0011->0001", 418 },
				{ "0101->0001", 416 },
				{ "1100->0010", 412 },
				{ "0011->0100", 404 },
				{ "1001->1001", 378 },
				{ "1010->0010", 376 },
				{ "0101->0100", 363 },
				{ "1100->0100", 339 },
				{ "0011->0010", 308 },
				{ "0100->1001", 288 },
				{ "0100->0011", 284 },
				{ "0100->1010", 284 },
				{ "0010->1001", 274 },
				{ "0010->1100", 271 },
				{ "0010->0101", 268 },
				{ "1010->0110", 266 },
				{ "0101->0110", 252 },
				{ "0110->0110", 250 },
				{ "1100->0110", 247 },
				{ "0110->1100", 246 },
				{ "0001->1100", 241 },
				{ "0110->0101", 240 },
				{ "1100->1100", 240 },
				{ "0011->0110", 227 },
				{ "1000->0101", 223 },
				{ "1100->1001", 221 },
				{ "0011->0011", 217 },
				{ "0110->0011", 216 },
				{ "0110->1010", 216 },
				{ "1000->0011", 213 },
				{ "0011->1001", 210 },
				{ "0001->1010", 209 },
				{ "0101->1001", 194 },
				{ "0101->0101", 192 },
				{ "0001->0110", 190 },
				{ "1001->0101", 182 },
				{ "1001->1010", 179 },
				{ "1010->1010", 172 },
				{ "1010->1001", 160 },
				{ "1000->0110", 159 },
				{ "1001->0011", 159 },
				{ "1010->1100", 150 },
				{ "1001->1100", 141 },
				{ "0101->0011", 127 },
				{ "1100->1010", 119 },
				{ "0011->0101", 118 },
				{ "0011->1100", 108 },
				{ "0101->1010", 105 },
				{ "1100->0011", 103 }
			}
		},

		{
			"Rare",
			{
				{ "0110->1001", 95 },
				{ "1010->0101", 78 },
				{ "1100->0101", 64 },
				{ "0011->1010", 64 },
				{ "1010->0011", 63 },
				{ "0101->1100", 58 },
				{ "1001->0110", 13 },
				{ "0001->1110", 13 },
				{ "1110->0001", 12 },
				{ "0010->1101", 12 },
				{ "0111->1000", 10 },
				{ "1000->0111", 10 },
				{ "1100->0111", 10 },
				{ "1101->1000", 9 },
				{ "0100->1011", 9 },
				{ "0111->0011", 9 },
				{ "1111->0001", 9 },
				{ "1111->1000", 8 },
				{ "1101->0001", 7 },
				{ "0111->0001", 7 },
				{ "1000->1110", 7 },
				{ "1001->0111", 7 },
				{ "1011->0001", 7 },
				{ "1011->0100", 7 },
				{ "1011->1011", 7 },
				{ "1110->1010", 6 },
				{ "0011->1101", 6 },
				{ "0011->1110", 6 },
				{ "0101->1011", 6 },
				{ "0111->0101", 6 },
				{ "1000->1011", 6 },
				{ "1000->1111", 6 },
				{ "1010->0111", 6 },
				{ "1100->1011", 6 },
				{ "1110->1000", 5 },
				{ "0101->1110", 5 },
				{ "1010->1011", 5 },
				{ "1010->1101", 5 },
				{ "1011->1010", 5 },
				{ "1101->0101", 5 },
				{ "1110->1100", 5 },
				{ "1111->0100", 4 },
				{ "0010->0111", 4 },
				{ "0010->1111", 4 },
				{ "0011->1011", 4 },
				{ "0100->1101", 4 },
				{ "0100->1110", 4 },
				{ "0100->1111", 4 },
				{ "0101->1101", 4 },
				{ "0110->1110", 4 },
				{ "1001->1011", 4 },
				{ "1011->0010", 4 },
				{ "1011->0011", 4 },
				{ "1011->0101", 4 },
				{ "1011->1000", 4 },
				{ "1011->1001", 4 },
				{ "1101->0010", 4 },
				{ "1101->1001", 3 },
				{ "0001->0111", 3 },
				{ "0001->1111", 3 },
				{ "0010->1110", 3 },
				{ "0100->0111", 3 },
				{ "0110->0111", 3 },
				{ "0111->1010", 3 },
				{ "1000->1101", 3 },
				{ "1001->1101", 3 },
				{ "1011->1100", 3 },
				{ "1100->1110", 3 },
				{ "1101->0100", 3 },
				{ "1101->1010", 3 },
				{ "1101->1100", 3 },
				{ "1110->0100", 3 },
				{ "1110->1110", 3 },
				{ "1111->1111", 2 },
				{ "0010->1011", 2 },
				{ "0011->1111", 2 },
				{ "0101->0111", 2 },
				{ "0101->1111", 2 },
				{ "0110->1011", 2 },
				{ "0111->0100", 2 },
				{ "0111->0110", 2 },
				{ "0111->0111", 2 },
				{ "0111->1100", 2 },
				{ "0111->1101", 2 },
				{ "1010->1110", 2 },
				{ "1011->1101", 2 },
				{ "1100->1101", 2 },
				{ "1101->1011", 2 },
				{ "1101->1101", 2 },
				{ "1110->0011", 2 },
				{ "1110->0101", 2 },
				{ "1110->0110", 2 },
				{ "0001->1011", 1 },
				{ "0001->1101", 1 },
				{ "0011->0111", 1 },
				{ "0110->1111", 1 },
				{ "0111->0010", 1 },
				{ "0111->1001", 1 },
				{ "0111->1011", 1 },
				{ "0111->1110", 1 },
				{ "1001->1110", 1 },
				{ "1001->1111", 1 },
				{ "1010->1111", 1 },
				{ "1011->0110", 1 },
				{ "1100->1111", 1 },
				{ "1101->0110", 1 },
				{ "1101->0111", 1 },
				{ "1101->1110", 1 },
				{ "1110->0111", 1 },
				{ "1110->1101", 1 },
				{ "1111->0010", 1 },
				{ "1111->0011", 1 },
				{ "1111->1010", 1 }
			}
		}
	};

	static const std::size_t Challenge_AverageNumberOfPatternsPerMeasure = (std::size_t)(17 * PatternMultiplier);
	static const std::float_t Challenge_StandardDeviationDivider = 2.0f;

}