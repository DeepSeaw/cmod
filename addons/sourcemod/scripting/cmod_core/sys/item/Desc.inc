/*
 * ============================================================================
 *
 *  SourceMod Project Base
 *
 *  File:          Desc.inc
 *  Type:          Module
 *  Description:   Describe item
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
#if defined ITEM_SYS;
#define ITEM_DESC;

stock Module:g_moduleItem_Desc;

public Item_Desc_OnPluginStart(){
	new moduledata[ModuleData];
	
	moduledata[ModuleData_Disabled] = false;
	moduledata[ModuleData_Hidden] = false;
	strcopy(moduledata[ModuleData_FullName], MM_DATA_FULLNAME, "[Cmod] Item: Describe");
	strcopy(moduledata[ModuleData_ShortName], MM_DATA_SHORTNAME, "Item_Desc");
	strcopy(moduledata[ModuleData_Description], MM_DATA_DESCRIPTION, "Show player item desc");
	moduledata[ModuleData_Dependencies][0] = g_moduleItemSys;
	moduledata[ModuleData_Dependencies][1] = INVALID_MODULE;
	
	RegConsoleCmd("sm_item", Item_Desc_Cmd);
	RegConsoleCmd("sm_perk", Item_Desc_Cmd);
	
	g_moduleItem_Desc = ModuleMgr_Register(moduledata);
	
}

public Action:Item_Desc_Cmd(client, args){
	if(g_iCmodPlayerItem[client]){
		decl	String:_buffer[MAX_DESC_LONG+1];
		decl	String:_buffer2[4];
		
		_buffer = g_sCmodItemDesc[g_iCmodPlayerItem[client]];
				
		IntToString(g_iCmodPlayerItemValue[client], _buffer2, sizeof(_buffer2));
		ReplaceString(_buffer, sizeof(_buffer), "#", _buffer2, false);
		
		PrintToChat(client, "\x01\x0B\x01 \x06perk:\x03%s \x06opis: \x03%s", g_sCmodItemName[g_iCmodPlayerItem[client]], _buffer);
	}else{
		PrintToChat(client, "\x01\x0B\x01 \x07%s \x06Nie posiadasz żadnego \x03itemu\x06, aby zdobyć item musisz kogoś zabić!", MOD_TAG); 
	}
	return Plugin_Handled; 
}


#endif
