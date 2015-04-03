/*
 * ============================================================================
 *
 *  SourceMod Project Base
 *
 *  File:          itemlib.inc
 *  Type:          Libary
 *  Description:   
 *
 *  Copyright (C) 2015 PLX
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * ============================================================================
 */

#if defined _itemlib
 #endinput
#endif
#define _itemlib

stock Item_Set(client, ItemID){
	new Function:_func;
	new _iValue;
	
	_func = GetFunctionByName(g_hCmodItemPlugin[g_iCmodPlayerItem[client]], "Cmod_OnItemDisabled");
	if(_func !=  INVALID_FUNCTION){
		Call_StartFunction(g_hCmodItemPlugin[g_iCmodPlayerItem[client]], _func);
		Call_PushCell(client);
		Call_PushCell(g_iCmodPlayerItem[client]);
		Call_Finish();
	}
	
	_iValue = GetRandomInt(g_iCmodItemMinValue[ItemID], g_iCmodItemMaxValue[ItemID]);
	
	_func = GetFunctionByName(g_hCmodItemPlugin[ItemID], "Cmod_OnItemEnabled");
	if(_func !=  INVALID_FUNCTION){
		Call_StartFunction(g_hCmodItemPlugin[ItemID], _func);
		Call_PushCell(client);
		Call_PushCell(ItemID);
		Call_PushCell(_iValue);
		Call_Finish();
	}
	
	g_iCmodPlayerItem[client] = ItemID;
	g_iCmodPlayerItemValue[client] = _iValue;
}

