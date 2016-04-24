#ifndef TEXT_H
#define TEXT_H

#include <string>

#include "enum.h"

using namespace std;

struct Text {

	const string
		txt = ".txt",
		title = "Trains Timetable Project",
		task = 
		"\n This program shows some data about specific railway route:\t       \n"
		" All desired trains, travel time and the schedule of the fastest train \n\n",
		bnf = " Backus-Naur forms of representing information \n\n",
		extendedN = "\t\t\t\t\t\t\t\t\t       \n",
		bnfInput = " [Input]\t\t\t\t\t\t\t\t       \n",
		inputBnf[BNF_INPUT_SIZE] = {
		" <Header>", "::=", " <FileInfo>", "';'","(","<StationName>","'-'",")","+","<StationName>","';'\t\t       \n",
		" <Record>", "::=", " <TrainNumber>", "';'","<StationName>","';'","<DepartureTime>","';'","<ArrivalTime>","';'\n",
		" <Footer>", "::=", " <TotalTrainNumber>","';'","<TotalRecordsNumber>","';'\t\t       \n" },
		bnfHint = " You can use white symbols anywhere \n",
		bnfOutput = " [Output]\t\t\t\t\t\t\t\t       \n",
		outputBnf[BNF_OUTPUT_SIZE] = { 
		" <Record>","::="," <TrainNumber>","<DepartureTime>","'-'","<ArrivalTime>\t\t       \n","\t     <RouteTime>","'['","<StartStationIsRouteStart>","']'\t\t       \n",
		" <Route>"," ::=", " <StationName>","<DepartureTime>","'-'","<ArrivalTime>\t\t       \n\n" },
		inputFileName = "\n Please, input file name (e.g.: data, d a t a . t x t): \n",
		openSuccess = "\n\n You successfully opened: ",
		openError = "\n\n Unfortunately, selected file can't be opened ", 
		separators[3] = { ";", ":", "-" },
		errors[15] = { 
		"at line ", " formatting error ", " Separators", " Train number", " Time", " Unrecognized station name " ,
		" Total trains", " Total records", " number in footer is incorrect, ", " Station name", " field is empty ",
	    " Time doesn't match 24-hour format ", " Unpredictable characters after end of record ",
		" Logic error in route timing for train ", " No trains coursing this route" },
		zero = "0",
		brackets = "()",
		plus = " START",
		sound = "\a",
		terminal = " $",
		menu = " Please, choose two stations: \n",
		menuHint = "\n Use <W>/<S> to select station and <ENTER> to confirm \n\n",
		finder[4] = { "\n All trains that are coursing between ", " and ", "\n The fastest ", " route is for train " },
		saveDialog = "\n Input file name where you want to save result or <ENTER> to print in console  \n",
		saved = "\n\n Your file was successfully saved \n";

	const char
		backslash = '\\',
		whiteSpaces[WHITE_SPACES_SIZE] = { BELL, BACKSPACE, TAB, NEW_LINE, ENTER, SPACE };

	const int
		inputBnfTextColors[BNF_INPUT_SIZE] = { 
		LIGHT_MAGENTA, DARK_GREY, BLUE, LIGHT_RED, DARK_GREY, BLUE, LIGHT_RED, DARK_GREY, DARK_GREY, BLUE, LIGHT_RED,
		LIGHT_MAGENTA, DARK_GREY, BLUE, LIGHT_RED, BLUE, LIGHT_RED, BLUE, LIGHT_RED, BLUE, LIGHT_RED,
		LIGHT_MAGENTA, DARK_GREY, BLUE, LIGHT_RED, BLUE, LIGHT_RED },
		outputBnfTextColors[BNF_OUTPUT_SIZE] = {
		LIGHT_MAGENTA, DARK_GREY, BLUE, BLUE, LIGHT_RED, BLUE, BLUE, LIGHT_RED, BLUE, LIGHT_RED,
		LIGHT_MAGENTA, DARK_GREY, BLUE, BLUE, LIGHT_RED, BLUE },
		allowedKeys[3] = { S, W, ENTER };

};

extern Text text;

#endif