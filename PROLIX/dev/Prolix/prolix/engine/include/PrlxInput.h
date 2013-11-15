//====================================================================================
// @Title:      PROLIX INPUT
//------------------------------------------------------------------------------------
// @Location:   /prolix/engine/include/PrlxInput.h
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//------------------------------------------------------------------------------------
// @Description:
//
//  Poll and handles keyboard and mouse events. Reports results to parent PROLIX 
//  engine and is handled by downstream components as required.
//
//====================================================================================
#ifndef __PROLIX_ENGINE_INPUT_H__
#define __PROLIX_ENGINE_INPUT_H__

#include <string>
#include <map>
#include "../../interface/include/cCursor.h"
#include "../../common/include/cTimer.h"

//====================================================================================
//                                                                          PrlxInput
//====================================================================================
class PrlxInput 
{    
  public:

    Uint8 *KeyState;		// registers state of keys
	Uint8 MouseState;       // registers state of mouse buttons
	
    // returns 1 if specified mouse button is pressed
	int IsMouseButtonPressed(Uint8 mouse_button);

	// cMouse
	struct cMouse 
    {
		Point pos;          // current x,y-coord of mouse
		Point prev_pos;     // previous x,y-coord of mouse
		cCursor *Cursor;	// Cursor instance

		// returns true if Cursor is hovering over specified rectangle
		bool IsHover(PRLX_Rect rect);
		
		// returns current mouse position as string
		std::string Format();
		
		// poll mouse position
		void Update();	

		//Constructor
		cMouse();
	};

    // Mouse instance
	cMouse *Mouse;

    // polls keyboard input
	void GetInput();

	// Constructor
	PrlxInput();

    // Destructor
    ~PrlxInput();
};

//====================================================================================
//                                                                            cCommand
//====================================================================================
struct cCommand 
{
	cTimer Timer;    // delay timer
	int delay;       // reaction delay
	SDLKey key;      // the key associated with the command
	bool allow_hold; // the key must be released before it can be validated for polling again
	bool pressed;    // flag indicating the previously polled accepted state of key

	// returns true if the delay on the timer has expired
	bool Pollable();

	// Constructor
	cCommand(SDLKey key, int delay, bool allow_hold = true);
};
//====================================================================================
//                                                                       cCommandGroup
//====================================================================================
struct cCommandGroup 
{
	std::map<std::string, cCommand *> CommandGroup;

	cCommand *GetCommand(std::string command_id);				// returns an command given an command identifier
	void AddCommand(std::string command_id, cCommand *command);	// adds an command to the command group
	bool ExistsCommand(std::string command_id);				    // checks if command exists in the group (by id)
	void RemoveCommand(std::string command_id);				    // removes an command from the command group

    // Constructors
	cCommandGroup();
	cCommandGroup(std::map<std::string, cCommand *> CommandGroup);
};

//====================================================================================
//                                                                          UserInput
//====================================================================================
struct UserInput 
{
	// inputted string
	std::string input;

	// vector of symbols
	std::vector<Uint8> lowerCase;
	std::vector<Uint8> numbers;

	// delay between keyboard inputs
	cTimer delay;

	void Update();

	// Constructor
	UserInput();

	// Destructor
	~UserInput();
};

#endif