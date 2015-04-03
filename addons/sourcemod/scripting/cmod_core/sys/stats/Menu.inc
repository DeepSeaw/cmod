/*
 * ============================================================================
 *
 *  SourceMod Project Base
 *
 *  File:          Menu.inc
 *  Type:          Module
 *  Description:   Stats menu
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
#if defined STATS_SYS
#define STATS_MENU;

stock Module:g_moduleStats_Menu;

public Stats_Menu_OnPluginStart(){
	new moduledata[ModuleData];
	
	moduledata[ModuleData_Disabled] = false;
	moduledata[ModuleData_Hidden] = false;
	strcopy(moduledata[ModuleData_FullName], MM_DATA_FULLNAME, "[Cmod] Stats menu");
	strcopy(moduledata[ModuleData_ShortName], MM_DATA_SHORTNAME, "Stats_Menu");
	strcopy(moduledata[ModuleData_Description], MM_DATA_DESCRIPTION, "Stats menu");
	moduledata[ModuleData_Dependencies][0] = g_moduleStatsSys;
	moduledata[ModuleData_Dependencies][1] = INVALID_MODULE;
	
	g_moduleStats_Menu = ModuleMgr_Register(moduledata);
	
	EventMgr_RegisterEvent(g_moduleStats_Menu, "Event_OnEventsRegister", "Stats_Menu_OnEventsRegister");
	
	RegConsoleCmd("sm_statystyki", Stats_Menu_Cmd);
	RegConsoleCmd("sm_staty", Stats_Menu_Cmd);
	RegConsoleCmd("sm_stats", Stats_Menu_Cmd);
}

public Stats_Menu_OnEventsRegister(){

	#if defined EVENT_MANAGER
		//EventMgr_RegisterEvent(g_moduleStats_Menu, "Event_OnClassChangeFail", "Stats_Menu_EventOnClassChangeFail");
		#if defined PROJECT_GAME_CSGO
			EventMgr_RegisterEvent(g_moduleStats_Menu, "Event_PlayerSpawn", "Stats_Menu_EventPlayerSpawn");
		#endif
	#endif
}

public Stats_Menu_EventPlayerSpawn(client){	
	if(g_iCmodPlayerPoint[client])
		Stats_Menu_Show(client);
}

public Action:Stats_Menu_Cmd(client, args)
{
	Stats_Menu_Show(client);
	return Plugin_Handled;
}

public Stats_Menu_Show(client)
{
	new Handle:_Menu = CreateMenu(Stats_Menu_HandlerShow);
	
	decl	String:_DescInt[MAX_STATS_DESCRIPTION_LONG+1],
			String:_DescCon[MAX_STATS_DESCRIPTION_LONG+1],
			String:_DescStr[MAX_STATS_DESCRIPTION_LONG+1],
			String:_DescDex[MAX_STATS_DESCRIPTION_LONG+1],
			String:_Title[25];
	
	Format(_Title, sizeof(_Title), "Przydziel Punkty(%d):\n \n", g_iCmodPlayerPoint[client]);
	Format(_DescInt, sizeof(_DescInt), "Inteligencja(INT): %d \nZwieksza sile perkow i umiejetnosci klasy", Stats_GetINT(client));
	Format(_DescCon, sizeof(_DescCon), "Zdrowie(CON): %d \nZwieksza ilość HP", Stats_GetCON(client));
	Format(_DescStr, sizeof(_DescStr), "Siła(STR): %i \nZmniejsza otrzymywane obrażenia od skilli i itemów ", Stats_GetSTR(client));
	Format(_DescDex, sizeof(_DescDex), "Kondycja(DEX): %i \nZwieksza tempo chodu", Stats_GetDEX(client));	
	
	SetMenuTitle(_Menu, _Title);
	AddMenuItem(_Menu, "int", _DescInt);
	AddMenuItem(_Menu, "con", _DescCon);
	AddMenuItem(_Menu, "str", _DescStr);
	AddMenuItem(_Menu, "dex", _DescDex);
	DisplayMenu(_Menu, client, MENU_TIME_FOREVER);

}

public Stats_Menu_HandlerShow(Handle:menu, MenuAction:action, param1, param2)
{
	if (action == MenuAction_Select){
		
		if(!g_iCmodPlayerPoint[param1])
			return;
			
		switch(param2){
			case 0:{					
				g_iCmodPlayerINT[param1]++;
				g_iCmodPlayerPoint[param1]--;				
			}
			case 1:{				
				g_iCmodPlayerCON[param1]++;
				g_iCmodPlayerPoint[param1]--;			
			}
			case 2:{				
				g_iCmodPlayerSTR[param1]++;
				g_iCmodPlayerPoint[param1]--;			
			}
			case 3:{				
				g_iCmodPlayerDEX[param1]++;
				g_iCmodPlayerPoint[param1]--;		
			}									
		}
		
		if(g_iCmodPlayerPoint[param1] > 0)
			Stats_Menu_Show(param1);
		
	}else if (action == MenuAction_End){
		CloseHandle(menu);
	}
}

#endif
