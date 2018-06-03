//this file is part of notepad++
//Copyright (C)2003 Don HO <donho@altern.org>
//
//This program is free software; you can redistribute it and/or
//modify it under the terms of the GNU General Public License
//as published by the Free Software Foundation; either
//version 2 of the License, or (at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

#ifndef BINHEX_H
#define BINHEX_H

//
// All difinitions of plugin interface
//
#include "PluginInterface.h"
#include "resource1.h"

//-------------------------------------//
//-- STEP 1. DEFINE YOUR PLUGIN NAME --//
//-------------------------------------//
// Here define your plugin name
//
const TCHAR NPP_PLUGIN_NAME[] = TEXT("BinHex");

//-----------------------------------------------//
//-- STEP 2. DEFINE YOUR PLUGIN COMMAND NUMBER --//
//-----------------------------------------------//
//
// Here define the number of your plugin commands
//
const int nbFunc = 21;


//
// Initialization of your plugin data
// It will be called while plugin loading
//
void pluginInit(HANDLE hModule);

//
// Cleaning of your plugin
// It will be called while plugin unloading
//
void pluginCleanUp();

//
//Initialization of your plugin commands
//
void commandMenuInit();

//
//Clean up your plugin commands allocation (if any)
//
void commandMenuCleanUp();

//
// Function which sets your command 
//
//bool setCommand(size_t index, TCHAR *cmdName, PFUNCPLUGINCMD pFunc, ShortcutKey *sk = NULL, bool check0nInit = false);
bool setCommand(size_t index, TCHAR *cmdName, PFUNCPLUGINCMD pFunc, unsigned char key, bool isctrl, bool isshift, bool isalt, bool check0nInit = false);


//
// Your plugin command functions
//

void h2b(char* bb,char* hh,unsigned int len);
void b2h(char* hh,char* bb,unsigned int len);
void dat_grouping(unsigned int num);
unsigned int remove_separator(char* aa,unsigned int len,bool remove_pre);
void shifting(bool dir, bool mode);

void helpDlg();

void hex2bin();
void bin2hex();

void shiftl();
void shiftr();


void rotl();
void rotr();

void bin_invert();
void hex_invert();

void grouping_2();
void grouping_4();
void grouping_8();
void grouping_16();

void ungroup();

void reverse();

// toolbar cmd
void inc_search();
void move_view();


//////////////////////
HWND get_cur_scint();






#endif //BINHEX_H
