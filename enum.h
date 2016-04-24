#ifndef ENUM_H
#define ENUM_H

enum ascii { BELL = 7, BACKSPACE, TAB, NEW_LINE, ENTER = 13, SPACE = 32, ZERO = 48, S = 115, W = 119 };
enum colors {
	BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN,
	LIGHT_GREY, DARK_GREY, LIGHT_BLUE, LIGHT_GREEN, LIGHT_CYAN, LIGHT_RED, LIGHT_MAGENTA,
	YELLOW, WHITE
};
enum sizes { WHITE_SPACES_SIZE = 6, BNF_OUTPUT_SIZE = 16, BNF_INPUT_SIZE = 27};
enum errors { SEPARATOR_ERROR = 2, TRAIN_NUMBER_ERROR, TIME_ERROR, UNKNOWN_STATION_ERROR, INCORRECT_TRAINS_NUMBER_ERROR, INCORRECT_RECORDS_NUMBER_ERROR,
			  EMPTY_STATION_NAME_ERROR = 9, INCORRECT_TIME_FORMAT_ERROR = 11, EXTRA_CHARACTERS_ERROR, EMPTY_TRAIN_NUMBER_ERROR, EMPTY_TIME_ERROR,
			  EMPTY_TRAINS_NUMBER_ERROR = 16, EMPTY_RECORDS_NUMBER_ERROR };

#endif