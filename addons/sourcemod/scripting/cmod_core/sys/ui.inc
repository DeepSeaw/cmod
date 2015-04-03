/*
 * ============================================================================
 *
 *  SourceMod Project Base
 *
 *  File:			ui.inc
 *  Type:			Module
 *  Description:	Display information
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

#define UI_SYS

stock Module:g_moduleUISys;

public UISys_OnPluginStart(){
	new moduledata[ModuleData];
	
	moduledata[ModuleData_Disabled] = false;
	moduledata[ModuleData_Hidden] = true;
	strcopy(moduledata[ModuleData_FullName], MM_DATA_FULLNAME, "[Cmod] UI system");
	strcopy(moduledata[ModuleData_ShortName], MM_DATA_SHORTNAME, "UISys");
	strcopy(moduledata[ModuleData_Description], MM_DATA_DESCRIPTION, "Display information");
	moduledata[ModuleData_Dependencies][0] = INVALID_MODULE;
	
	g_moduleUISys = ModuleMgr_Register(moduledata);
	 
	CreateTimer(1.0, UISys_Show, _, TIMER_REPEAT);
}

public Action:UISys_Show(Handle:timer){ 
	
			
	for(new client = 1; client <= MaxClients; client++){
		if(IsClientConnected(client) && IsClientInGame(client) && IsPlayerAlive(client) && !IsFakeClient(client)){
			new	String:_tmp[64],
				String:_buffer[256];
			#if defined CLASS_SYS
				Format(_tmp, sizeof(_tmp), "[Klasa: %s]\n", g_sCmodClassName[g_iCmodPlayerClass[client]]);
				StrCat(_buffer, sizeof(_buffer), _tmp);
			#endif
			
			#if defined XP_SYS
				Format(_tmp, sizeof(_tmp), "[LVL: %d][XP %d/%d]\n", g_iCmodLvl[client], g_iCmodExp[client], XpSys_GetXpForLvl(g_iCmodLvl[client]));
				StrCat(_buffer, sizeof(_buffer), _tmp);
			#endif
			
			#if defined ITEM_SYS
				Format(_tmp, sizeof(_tmp), "[Item: %s]\n", g_sCmodItemName[g_iCmodPlayerItem[client]]);
				StrCat(_buffer, sizeof(_buffer), _tmp);
			#endif
			PrintHintText(client, "%s", _buffer); 
		}	
	}
	return Plugin_Continue;
} 
