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

#include "binhex.h"
#include "menuCmdID.h"

#include <stdlib.h> 
#include <string.h>
#include <stdio.h> 
//#include <wchar.h>


// Global variable
bool is_pre = false;


//
// The plugin data that Notepad++ needs
//
FuncItem funcItem[nbFunc];

//
// The data of Notepad++ that you can use in your plugin commands
//
NppData nppData;

HANDLE g_hModule;
toolbarIcons  tbIncSearch;
toolbarIcons  tbMoveView;

//
// Initialize your plugin data here
// It will be called while plugin loading   
void pluginInit(HANDLE /*hModule*/)
{
}

//
// Here you can do the clean up, save the parameters (if any) for the next session
//
void pluginCleanUp()
{
}

//
// Initialization of your plugin commands
// You should fill your plugins commands here
void commandMenuInit()
{

    //--------------------------------------------//
    //-- STEP 3. CUSTOMIZE YOUR PLUGIN COMMANDS --//
    //--------------------------------------------//
    // with function :
    // setCommand(int index,                      // zero based number to indicate the order of command
    //            TCHAR *commandName,             // the command name that you want to see in plugin menu
    //            PFUNCPLUGINCMD functionPointer, // the symbol of function (function pointer) associated with this command. The body should be defined below. See Step 4.
    //            ShortcutKey *shortcut,          // optional. Define a shortcut to trigger this command
    //            bool check0nInit                // optional. Make this menu item be checked visually
    //            );
   
	//setCommand(0, TEXT("Hello (with dialog)"), helloDlg, NULL, false);
	/*
	setCommand(0, TEXT("bin2hex"), bin2hex, 'H', true, true, false, false);
	setCommand(1, TEXT("hex2bin"), hex2bin, 'B', true, true, false, false);
	setCommand(2, TEXT("bin_invert"), bin_invert, 'B', true, false, true, false);
	setCommand(3, TEXT("hex_invert"), hex_invert, 'H', true, false, true, false);
	setCommand(4, TEXT("reverse"), reverse, 'R', true, false, false, false);

	setCommand(5, TEXT("---"), NULL, NULL, false, false, false, false);
	setCommand(6, TEXT("hex_shift >>"), shiftr, 39, true, true, false, false);
	setCommand(7, TEXT("hex_shift <<"), shiftl, 37, true, true, false, false);
	setCommand(8, TEXT("hex_rotate >>"), rotr, 39, true, false, true, false);
	setCommand(9, TEXT("hex_rotate <<"), rotl, 37, true, false, true, false);
	setCommand(10, TEXT("---"), NULL, NULL, false, false, false, false);
	*/

	setCommand(0, TEXT("bin2hex"), bin2hex, NULL, false, false, false, false);
	setCommand(1, TEXT("hex2bin"), hex2bin, NULL, false, false, false, false);
	setCommand(2, TEXT("bin_invert"), bin_invert, NULL, false, false, false, false);
	setCommand(3, TEXT("hex_invert"), hex_invert, NULL, false, false, false, false);
	setCommand(4, TEXT("reverse"), reverse, NULL, false, false, false, false);

	setCommand(5, TEXT("---"), NULL, NULL, false, false, false, false);
	setCommand(6, TEXT("hex_shift >>"), shiftr, NULL, false, false, false, false);
	setCommand(7, TEXT("hex_shift <<"), shiftl, NULL, false, false, false, false);
	setCommand(8, TEXT("hex_rotate >>"), rotr, NULL, false, false, false, false);
	setCommand(9, TEXT("hex_rotate <<"), rotl, NULL, false, false, false, false);
	setCommand(10, TEXT("---"), NULL, NULL, false, false, false, false);

	setCommand(11, TEXT("grouping_2"), grouping_2, '2', true, false, true, false);
	setCommand(12, TEXT("grouping_4"), grouping_4, '4', true, false, true, false);
	setCommand(13, TEXT("grouping_8"), grouping_8, '8', true, false, true, false);
	setCommand(14, TEXT("grouping_16"), grouping_16, '6', true, false, true, false);
	setCommand(15, TEXT("ungroup"), ungroup, '1', true, false, true, false);

	// Here you insert a separator
	setCommand(16, TEXT("---"), NULL, NULL, false, false, false, false);

	setCommand(17, TEXT("incremental search"), inc_search, NULL, false, false, false, false);
	setCommand(18, TEXT("move to other view"), move_view, NULL, false, false, false, false);

	// Here you insert a separator
	setCommand(19, TEXT("---"), NULL, NULL, false, false, false, false);
	setCommand(20, TEXT("help"), helpDlg, NULL, false, false, false, false);
}

//
// Here you can do the clean up (especially for the shortcut)
//
void commandMenuCleanUp()
{
	if (tbIncSearch.hToolbarBmp)  ::DeleteObject(tbIncSearch.hToolbarBmp);
    if (tbMoveView.hToolbarBmp)  ::DeleteObject(tbMoveView.hToolbarBmp);

	// Don't forget to deallocate your shortcut here
	delete funcItem[0]._pShKey;
	delete funcItem[1]._pShKey;
	delete funcItem[2]._pShKey;
	delete funcItem[3]._pShKey;
	delete funcItem[4]._pShKey;
	delete funcItem[6]._pShKey;
	delete funcItem[7]._pShKey;
	delete funcItem[8]._pShKey;
	delete funcItem[9]._pShKey;
	delete funcItem[11]._pShKey;
	delete funcItem[12]._pShKey;
	delete funcItem[13]._pShKey;
	delete funcItem[14]._pShKey;
	delete funcItem[15]._pShKey;
	delete funcItem[16]._pShKey;
	delete funcItem[17]._pShKey;
	delete funcItem[18]._pShKey;
	delete funcItem[19]._pShKey;
	delete funcItem[20]._pShKey;
}


//
// This function help you to initialize your plugin commands
//
//bool setCommand(size_t index, TCHAR *cmdName, PFUNCPLUGINCMD pFunc, ShortcutKey *sk, bool check0nInit) 
bool setCommand(size_t index, TCHAR *cmdName, PFUNCPLUGINCMD pFunc, unsigned char key, bool isctrl, bool isshift, bool isalt, bool check0nInit) 
{
    if (index >= nbFunc)
        return false;

    if (!pFunc)
        return false;

    lstrcpy(funcItem[index]._itemName, cmdName);
    funcItem[index]._pFunc = pFunc;
    funcItem[index]._init2Check = check0nInit;
	if(key == NULL){
	    funcItem[index]._pShKey = NULL;
	}else{
		funcItem[index]._pShKey = new ShortcutKey;
		funcItem[index]._pShKey->_isAlt		= isalt;
		funcItem[index]._pShKey->_isCtrl	= isctrl;
		funcItem[index]._pShKey->_isShift	= isshift;
		funcItem[index]._pShKey->_key		= key;
	}
    return true;
}

//----------------------------------------------//
//-- STEP 4. DEFINE YOUR ASSOCIATED FUNCTIONS --//
//----------------------------------------------//


void helpDlg()
{
	::MessageBox(NULL, TEXT("Contains bin/hex string manipulating functions : \n\
can support very long string manipulation \n\n\
FORMAT : MSB --> LSB \n\
accepts prefix 0x/0b \n\
----------------- \n\
bin2hex/hex2bin  \t- conversion between hex and binary text \n\
bin_invert/hex_invert - bit inversion for bin/hex text  (0b1010 -> 0b0101)\n\
reverse	 \t- text reverse (abcd -> dcba)\n\
hex_shift   \t- shift left/right for hex string, lose the shift out bit\n\
          \t\t (0x8421 -> 0x4210)\n\
hex_rotate  \t- rotate left/right for hex string, lsb --> msb and vice\n\
          \t\t  versa (0x8421 -> 0xc210)\n\
grouping_2/4/8/16 - grouping hex/bin string to 2/4/8/16 char \n\n\
\n\
added incremental search and move to other view toolbar icon \n\
\n\
Version 2.0.0.1 \n\
By : skycc86  @__@ \n\
https://github.com/skycc86"), TEXT("BinHex Plugin Help"), MB_OK);
}





/*
// debug msgbox
int slen=strlen(wordA);

char haha[50];
sprintf(haha,"%lu-%lu=%u,len=%u",sel_end,sel_start,sel_len,slen);

LPTSTR wordU;
wordU=new TCHAR[buf_len+50];
mbstowcs(wordU,haha,buf_len+50);

::MessageBox(NULL, wordU, TEXT("hex2bin"), MB_OK);
*/


void reverse()
{
	HWND curScint = get_cur_scint();

	unsigned long sel_start=(unsigned long)::SendMessage(curScint, SCI_GETSELECTIONSTART, NULL, NULL);
	unsigned long sel_end=(unsigned long)::SendMessage(curScint, SCI_GETSELECTIONEND, NULL, NULL);
	unsigned int sel_len=(unsigned int) (sel_end-sel_start);
	unsigned int buf_len=sel_len+2;

	if(sel_len==0){
		return;
	}

	char* wordA;
	wordA=new char[buf_len];

	::SendMessage(curScint, SCI_GETSELTEXT, 0, (LPARAM)wordA);

	char* wordA2;
	wordA2=new char[sel_len+2];
	
	unsigned int i=0;

	for(i=0;i<sel_len;i++){
		wordA2[i]=wordA[sel_len-1-i];
	}
	wordA2[sel_len]='\0';

	::SendMessage(curScint, SCI_REPLACESEL, 0, (LPARAM)wordA2);	
	::SendMessage(curScint, SCI_SETSELECTIONSTART, sel_start, NULL);
	::SendMessage(curScint, SCI_SETSELECTIONEND, sel_start+sel_len, NULL);

delete []wordA;
delete []wordA2;

}

void hex2bin()
{
	is_pre = false;
	HWND curScint = get_cur_scint();

	unsigned long sel_start=(unsigned long)::SendMessage(curScint, SCI_GETSELECTIONSTART, NULL, NULL);
	unsigned long sel_end=(unsigned long)::SendMessage(curScint, SCI_GETSELECTIONEND, NULL, NULL);
	unsigned int sel_len=(unsigned int) (sel_end-sel_start);
	unsigned int buf_len=sel_len+2;

	if(sel_len==0){
		return;
	}

	char* wordA;
	wordA=new char[buf_len];

	::SendMessage(curScint, SCI_GETSELTEXT, 0, (LPARAM)wordA);

	//while(wordA[sel_len-1]==' '){ sel_len--; }
	unsigned int newlen=remove_separator(wordA, sel_len, true);

	char* wordA2;
	wordA2=new char[(newlen*4)+2];
	char* wordA3;
	wordA3=new char[(newlen*4)+2];

	h2b(wordA2,wordA,newlen);
	if(is_pre==true){
		strcpy(wordA3, "0b");
		strcat(wordA3, wordA2);
	}else{
		strcpy(wordA3, wordA2);
	}
	newlen = (unsigned int) strlen(wordA3);

	::SendMessage(curScint, SCI_REPLACESEL, 0, (LPARAM)wordA3);	
	::SendMessage(curScint, SCI_SETSELECTIONSTART, sel_start, NULL);
	::SendMessage(curScint, SCI_SETSELECTIONEND, sel_start+newlen, NULL);

delete []wordA;
delete []wordA2;
delete []wordA3;
}

void bin2hex()
{
	is_pre = false;
	HWND curScint = get_cur_scint();

	unsigned long sel_start=(unsigned long)::SendMessage(curScint, SCI_GETSELECTIONSTART, NULL, NULL);
	unsigned long sel_end=(unsigned long)::SendMessage(curScint, SCI_GETSELECTIONEND, NULL, NULL);
	unsigned int sel_len=(unsigned int) (sel_end-sel_start);
	unsigned int buf_len=sel_len+2;

	if(sel_len==0){
		return;
	}

	char* wordA;
	wordA=new char[buf_len];

	::SendMessage(curScint, SCI_GETSELTEXT, 0, (LPARAM)wordA);

	//while(wordA[sel_len-1]==' '){ sel_len--; }
	unsigned int newlen=remove_separator(wordA, sel_len, true);
	
	//unsigned int hmax=newlen/4;
	//unsigned int rem=newlen%4;
	//if(rem>0)hmax++;

	char* wordA2;
	wordA2=new char[(newlen/4)+2];

	b2h(wordA2,wordA,newlen);
	if(is_pre==true){
		strcpy(wordA, "0x");
		strcat(wordA, wordA2);
	}else{
		//wordA = wordA2;
		strcpy(wordA, wordA2);
	}
	newlen = (unsigned int) strlen(wordA);

	::SendMessage(curScint, SCI_REPLACESEL, 0, (LPARAM)wordA);
	::SendMessage(curScint, SCI_SETSELECTIONSTART, sel_start, NULL);
	::SendMessage(curScint, SCI_SETSELECTIONEND, sel_start+newlen, NULL);

delete []wordA;
delete []wordA2;
}


void h2b(char* bb,char* hh,unsigned int len)
{
	char* binbuf;
	char tmp;
	binbuf="0000";

	for(unsigned int i=0;i<len;i++){
		tmp=hh[i];

		switch(tmp){
			case '0': binbuf="0000"; break;
			case '1': binbuf="0001"; break;
			case '2': binbuf="0010"; break;
			case '3': binbuf="0011"; break;
			case '4': binbuf="0100"; break;
			case '5': binbuf="0101"; break;
			case '6': binbuf="0110"; break;
			case '7': binbuf="0111"; break;
			case '8': binbuf="1000"; break;
			case '9': binbuf="1001"; break;
			case 'A':
			case 'a': binbuf="1010"; break;
			case 'B':
			case 'b': binbuf="1011"; break;
			case 'C':
			case 'c': binbuf="1100"; break;
			case 'D':
			case 'd': binbuf="1101"; break;
			case 'E':
			case 'e': binbuf="1110"; break;
			case 'F':
			case 'f': binbuf="1111"; break;
			default:  binbuf="xxxx";
		}
		//for(int j=0;j<4;j++){
		//	bb[(i*4)+j]=binbuf[j];
		//}
		strncpy(bb+(i*4),binbuf,4);
	}
	bb[len*4]='\0';
}

void b2h(char* hh,char* bb,unsigned int len)
{
	char hexbuf;
	char tmp[5];
	int dec;

	int hmax=len/4;
	int rem=len%4;
	if(rem>0)hmax++;

	int len_cp;
	len_cp = (rem>0)?rem:4;

	for(int i=0;i<hmax;i++){
		if(i==0){
			strncpy(tmp,bb,len_cp);
		}else{
			strncpy(tmp,bb+((i-1)*4)+len_cp,4);
		}

		dec=strtol(tmp,NULL,2);
		switch(dec){
			case 0: hexbuf='0'; break;
			case 1: hexbuf='1'; break;
			case 2: hexbuf='2'; break;
			case 3: hexbuf='3'; break;
			case 4: hexbuf='4'; break;
			case 5: hexbuf='5'; break;
			case 6: hexbuf='6'; break;
			case 7: hexbuf='7'; break;
			case 8: hexbuf='8'; break;
			case 9: hexbuf='9'; break;
			case 10: hexbuf='a'; break;
			case 11: hexbuf='b'; break;
			case 12: hexbuf='c'; break;
			case 13: hexbuf='d'; break;
			case 14: hexbuf='e'; break;
			case 15: hexbuf='f'; break;
			default:  hexbuf='x';
		}
			hh[i]=hexbuf;
	}
	hh[hmax]='\0';
}


void rotl()
{
	shifting(0,1);
}

void rotr()
{
	shifting(1,1);
}

void shiftl()
{
	shifting(0,0);
}

void shiftr()
{
	shifting(1,0);
}


// dir  - 1 shift right, 0 shift left
// mode - 1 rotate, 0 shift
void shifting(bool dir, bool mode)
{
	is_pre = false;
	HWND curScint = get_cur_scint();

	unsigned long sel_start=(unsigned long)::SendMessage(curScint, SCI_GETSELECTIONSTART, NULL, NULL);
	unsigned long sel_end=(unsigned long)::SendMessage(curScint, SCI_GETSELECTIONEND, NULL, NULL);
	unsigned int sel_len=(unsigned int) (sel_end-sel_start);
	unsigned int buf_len=sel_len+2;		

	if(sel_len==0){
		return;
	}

	char* wordA;
	wordA=new char[buf_len];
	::SendMessage(curScint, SCI_GETSELTEXT, 0, (LPARAM)wordA);

	unsigned int newlen=remove_separator(wordA, sel_len, true);

	unsigned int new_len=(unsigned int) (newlen*4);
	char* wordB;
	wordB=new char[new_len+2];
	char* wordC;
	wordC=new char[new_len+2];

	h2b(wordB,wordA,newlen);
	
	if(dir){
		// right
		wordC[0]=(mode)?wordB[new_len-1]:'0';
		strncpy(wordC+1,wordB,new_len-1);
	}else{
		//  left
		strncpy(wordC,wordB+1,new_len-1);
		//strncpy(wordC+new_len-1,wordB,1);
		wordC[new_len-1]=(mode)?wordB[0]:'0';
	}
	wordC[new_len]='\0';

	char* wordD;
	wordD=new char[buf_len];
	b2h(wordD,wordC,new_len);

	if(is_pre==true){
		strcpy(wordC, "0x");
		strcat(wordC, wordD);
	}else{
		//wordC = wordD;
		strcpy(wordC, wordD);
	}
	newlen = (unsigned int) strlen(wordC);

	::SendMessage(curScint, SCI_REPLACESEL, 0, (LPARAM)wordC);
	::SendMessage(curScint, SCI_SETSELECTIONSTART, sel_start, NULL);
	::SendMessage(curScint, SCI_SETSELECTIONEND, sel_start+newlen, NULL);

delete []wordA;
delete []wordB;
delete []wordC;
delete []wordD;

}




void bin_invert()
{
	is_pre = false;
	HWND curScint = get_cur_scint();

	unsigned long sel_start=(unsigned long)::SendMessage(curScint, SCI_GETSELECTIONSTART, NULL, NULL);
	unsigned long sel_end=(unsigned long)::SendMessage(curScint, SCI_GETSELECTIONEND, NULL, NULL);
	unsigned int sel_len=(unsigned int) (sel_end-sel_start);
	unsigned int buf_len=sel_len+2;		

	if(sel_len==0){
		return;
	}

	char* wordA;
	wordA=new char[buf_len];
	::SendMessage(curScint, SCI_GETSELTEXT, 0, (LPARAM)wordA);

	unsigned int newlen=remove_separator(wordA, sel_len, true);
	
	char* wordI;
	char* wordI2;
	wordI=new char[buf_len];
	wordI2=new char[buf_len+2];
	char tmp,buf;
	
	for(unsigned int i=0;i<=newlen;i++){
		tmp=wordA[i];
		switch(tmp){
			case '0': buf='1'; break;
			case '1': buf='0'; break;
			default:  buf=tmp;
		}
		wordI[i]=buf;
	}
	wordI[newlen]='\0';

	if(is_pre==true){
		strcpy(wordI2, "0b");
		strcat(wordI2, wordI);
	}else{
		//wordI2 = wordI;
		strcpy(wordI2, wordI);
	}
	newlen = (unsigned int) strlen(wordI2);

	::SendMessage(curScint, SCI_REPLACESEL, 0, (LPARAM)wordI2);
	::SendMessage(curScint, SCI_SETSELECTIONSTART, sel_start, NULL);
	::SendMessage(curScint, SCI_SETSELECTIONEND, sel_start+newlen, NULL);

delete []wordA;
delete []wordI;
delete []wordI2;
}

void hex_invert()
{
	is_pre = false;
	HWND curScint = get_cur_scint();

	unsigned long sel_start=(unsigned long)::SendMessage(curScint, SCI_GETSELECTIONSTART, NULL, NULL);
	unsigned long sel_end=(unsigned long)::SendMessage(curScint, SCI_GETSELECTIONEND, NULL, NULL);
	unsigned int sel_len=(unsigned int) (sel_end-sel_start);
	unsigned int buf_len=sel_len+2;		

	if(sel_len==0){
		return;
	}

	char* wordA;
	wordA=new char[buf_len];
	::SendMessage(curScint, SCI_GETSELTEXT, 0, (LPARAM)wordA);

	unsigned int newlen=remove_separator(wordA, sel_len, true);

	char* wordI;
	char* wordI2;
	wordI=new char[buf_len];
	wordI2=new char[buf_len+2];
	char tmp,buf;
	
	for(unsigned int i=0;i<=newlen;i++){
		tmp=wordA[i];
		switch(tmp){
			case '0': buf='f'; break;
			case '1': buf='e'; break;
			case '2': buf='d'; break;
			case '3': buf='c'; break;
			case '4': buf='b'; break;
			case '5': buf='a'; break;
			case '6': buf='9'; break;
			case '7': buf='8'; break;
			case '8': buf='7'; break;
			case '9': buf='6'; break;
			case 'A':
			case 'a': buf='5'; break;
			case 'B':
			case 'b': buf='4'; break;
			case 'C':
			case 'c': buf='3'; break;
			case 'D':
			case 'd': buf='2'; break;
			case 'E':
			case 'e': buf='1'; break;
			case 'F':
			case 'f': buf='0'; break;
			default:  buf=tmp;
		}
		wordI[i]=buf;
	}
	wordI[newlen]='\0';

	if(is_pre==true){
		strcpy(wordI2, "0x");
		strcat(wordI2, wordI);
	}else{
		//wordI2 = wordI;
		strcpy(wordI2, wordI);
	}
	newlen = (unsigned int) strlen(wordI2);

	::SendMessage(curScint, SCI_REPLACESEL, 0, (LPARAM)wordI2);
	::SendMessage(curScint, SCI_SETSELECTIONSTART, sel_start, NULL);
	::SendMessage(curScint, SCI_SETSELECTIONEND, sel_start+newlen, NULL);

delete []wordA;
delete []wordI;
delete []wordI2;
}


void grouping_2()
{
	dat_grouping(2);
}


void grouping_4()
{
	dat_grouping(4);
}

void grouping_8()
{
	dat_grouping(8);
}

void grouping_16()
{
	dat_grouping(16);
}



void dat_grouping(unsigned int num)
{
	HWND curScint = get_cur_scint();

	unsigned long sel_start=(unsigned long)::SendMessage(curScint, SCI_GETSELECTIONSTART, NULL, NULL);
	unsigned long sel_end=(unsigned long)::SendMessage(curScint, SCI_GETSELECTIONEND, NULL, NULL);
	unsigned int sel_len=(unsigned int) (sel_end-sel_start);
	unsigned int buf_len=sel_len+2;		

	if(sel_len==0){
		return;
	}

	char* wordA;
	wordA=new char[buf_len];
	::SendMessage(curScint, SCI_GETSELTEXT, 0, (LPARAM)wordA);
	
	unsigned int newlen=remove_separator(wordA, sel_len, false);

	int ext=newlen/num;
	unsigned int rem=newlen%num;
	if(rem>0)ext++;

	char* wordB;
	wordB=new char[buf_len+ext];

	int len_cp;
	len_cp = (rem>0)?rem:num;

	for(int i=0;i<ext;i++){
		if(i==0){
			strncpy(wordB,wordA,len_cp);
			wordB[len_cp]='_';
		}else{
			strncpy(wordB+len_cp+((i-1)*num)+i,wordA+((i-1)*num)+len_cp,num);
			wordB[len_cp+(i*(num+1))]='_';
		}
	}

	wordB[newlen+ext-1]='\0';

	::SendMessage(curScint, SCI_REPLACESEL, 0, (LPARAM)wordB);
	::SendMessage(curScint, SCI_SETSELECTIONSTART, sel_start, NULL);
	::SendMessage(curScint, SCI_SETSELECTIONEND, sel_start+newlen+ext-1, NULL);
	
delete []wordA;
delete []wordB;
}

void ungroup()
{
	HWND curScint = get_cur_scint();

	unsigned long sel_start=(unsigned long)::SendMessage(curScint, SCI_GETSELECTIONSTART, NULL, NULL);
	unsigned long sel_end=(unsigned long)::SendMessage(curScint, SCI_GETSELECTIONEND, NULL, NULL);
	unsigned int sel_len=(unsigned int) (sel_end-sel_start);
	unsigned int buf_len=sel_len+2;		

	if(sel_len==0){
		return;
	}

	char* wordA;
	wordA=new char[buf_len];
	::SendMessage(curScint, SCI_GETSELTEXT, 0, (LPARAM)wordA);

	unsigned int newlen=remove_separator(wordA, sel_len, false);

	::SendMessage(curScint, SCI_REPLACESEL, 0, (LPARAM)wordA);
	::SendMessage(curScint, SCI_SETSELECTIONSTART, sel_start, NULL);
	::SendMessage(curScint, SCI_SETSELECTIONEND, sel_start+newlen, NULL);
	
delete []wordA;
}


unsigned int remove_separator(char* aa,unsigned int len,bool remove_pre)
{
	char* wordB;
	wordB=new char[len+2];
	
	unsigned int i=0;
	unsigned int i_start=0;
	unsigned int newlen=0;

	for(i=0;i<len;i++){
		if(aa[i] != '_' && aa[i] != ' '){
			wordB[newlen++]=aa[i];
		}
	}
	wordB[newlen]='\0';

	if(remove_pre==1){
		if(wordB[0] == '0' && (wordB[1] == 'x' || wordB[1] == 'X' || wordB[1] == 'b' || wordB[1] == 'B')){
			i_start += 2;
			newlen -= 2;
			is_pre = true;
		}
	}

	strncpy(aa, wordB+i_start, newlen);
	aa[newlen]='\0';

delete []wordB;
return newlen;
}


// toolbar cmd
void inc_search()
{
	::SendMessage(nppData._nppHandle, NPPM_MENUCOMMAND, 0, (LPARAM)IDM_SEARCH_FINDINCREMENT);
}

void move_view()
{
	::SendMessage(nppData._nppHandle, NPPM_MENUCOMMAND, 0, (LPARAM)IDM_VIEW_GOTO_ANOTHER_VIEW);
}


//////////////////////////////////////
HWND get_cur_scint()
{
	int currentEdit;
	::SendMessage(nppData._nppHandle, NPPM_GETCURRENTSCINTILLA, 0, (LPARAM)&currentEdit);
	HWND curScint = (currentEdit == 0)?nppData._scintillaMainHandle:nppData._scintillaSecondHandle;
	return curScint;
}
