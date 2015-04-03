/*
 * ============================================================================
 *
 *  SourceMod Project Base
 *
 *  File:          xp.inc
 *  Type:          Module
 *  Description:   Basic Xp and level system
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

#define XP_SYS

stock Module:g_moduleXpSys;
 
public XpSys_OnPluginStart()
{

	new moduledata[ModuleData];
	
	moduledata[ModuleData_Disabled] = false;
	moduledata[ModuleData_Hidden] = true;
	strcopy(moduledata[ModuleData_FullName], MM_DATA_FULLNAME, "[Cmod:core] xp system");
	strcopy(moduledata[ModuleData_ShortName], MM_DATA_SHORTNAME, "XpSys");
	strcopy(moduledata[ModuleData_Description], MM_DATA_DESCRIPTION, "Basic Xp and Lvl system");
	moduledata[ModuleData_Dependencies][0] = INVALID_MODULE;
	
	g_moduleXpSys = ModuleMgr_Register(moduledata);
	
	EventMgr_RegisterEvent(g_moduleXpSys, "Event_OnEventsRegister", "XpSys_OnEventsRegister");
	
	//ConfigMgr_Register(g_moduleXpSys, "XpSys_OnConfigReload", "configs/cmod/xpsys_config.txt");
	
	g_hCmodExpKill = CreateConVar("cmod_expkill", "10", "Kill exp");
	g_hCmodBotExpKill = CreateConVar("cmod_botexpkill", "1", "Kill bot exp");
	g_hCmodMaxLvl = CreateConVar("cmod_maxlvl", "200", "Max lvl");
	g_hCmodLvlRatio = CreateConVar("cmod_lvlratio", "35", "exp for 1st lvl");
	
	AutoExecConfig(true, "cmod");
}

public XpSys_OnEventsRegister()
{

	#if defined EVENT_MANAGER	

		#if defined PROJECT_GAME_CSGO
			EventMgr_RegisterEvent(g_moduleXpSys, "Event_OnClientPutInServer", "XpSys_OnClientPutInServer");
			EventMgr_RegisterEvent(g_moduleXpSys, "Event_PlayerDeath", "XpSys_PlayerDeath");
		#endif	

	#endif
}
public XpSys_OnClientPutInServer(client)
{
	g_iCmodLvl[client] = 1;
	g_iCmodExp[client] = 0;
}

#if defined PROJECT_GAME_CSGO
public XpSys_PlayerDeath(victim, attacker, String:weapon[], headshoot){
	if(!IsFakeClient(attacker) && (attacker != victim)){
		new _iExp = GetConVarInt(g_hCmodExpKill) + g_iCmodBonusExp[attacker];
		if(!IsFakeClient(victim)){
			if(g_iCmodLvl[victim] > g_iCmodLvl[attacker])
				_iExp += (g_iCmodLvl[victim] - g_iCmodLvl[attacker])*(GetConVarInt(g_hCmodExpKill)/10);
			
		}else{
			_iExp = GetConVarInt(g_hCmodBotExpKill);
		}
		XpSys_GiveExp(attacker, _iExp);
		PrintToChat(attacker, "\x01\x0B\x01 \x07%s \x06Otrzymujesz \x03+%dxp \x06za zabójstwo", MOD_TAG, _iExp);
	}
}
#endif

XpSys_GiveExp(client, const value){
	if(!(client >= 1 && client <= MaxClients && IsClientConnected(client) && IsClientInGame(client)))
		return 0;
	
	g_iCmodExp[client] += value;
	XpSys_CheckLvl(client);
	
	return 1;
}

XpSys_CheckLvl(client){
	new bool:_bLvlUp = false;
	new bool:_bLvlDown = false;
	
	if(!IsClientConnected(client))
		return;
	
	while(g_iCmodExp[client] >= XpSys_GetXpForLvl(g_iCmodLvl[client]) && g_iCmodLvl[client] < GetConVarInt(g_hCmodMaxLvl)){
		g_iCmodLvl[client]++;
		
		#if defined STATS_SYS
			//g_iStatsSysPoints[client] = (g_iXpSysLvl[client]-1)*2-g_iStatsSysINT[client]-g_iStatsSysCON[client]-g_iStatsSysSTR[client]-g_iStatsSysDEX[client];
		#endif
		
		_bLvlUp = true;
	} 
	while(g_iCmodExp[client] < XpSys_GetXpForLvl(g_iCmodLvl[client]-1)){
		g_iCmodLvl[client]--;
		_bLvlDown = true;
	}
		
	if(g_iCmodLvl[client] > GetConVarInt(g_hCmodMaxLvl)){
		g_iCmodLvl[client] = GetConVarInt(g_hCmodMaxLvl);
		
		#if defined STATS_RESET
			Stats_Reset_Start(client);
		#endif
		
	}
	
	if(_bLvlDown){
		#if defined STATS_RESET
			Stats_Reset_Start(client);
		#endif
		PrintToChat(client, "\x01\x0B\x01 \x07%s \x06Spadłeś na \x03%d \x06poziom!", MOD_TAG, g_iCmodLvl[client]);
	}else if(_bLvlUp){
		
		#if defined STATS_MENU
			g_iCmodPlayerPoint[client] = (g_iCmodLvl[client]-1)*2-g_iCmodPlayerINT[client]-g_iCmodPlayerCON[client]-g_iCmodPlayerSTR[client]-g_iCmodPlayerDEX[client];		
			Stats_Menu_Show(client);
		#endif 
		
		PrintToChat(client, "\x01\x0B\x01 \x07%s \x06Awansowałeś na \x03%d \x06poziom!", MOD_TAG, g_iCmodLvl[client]);
	}
}

stock XpSys_GetXpForLvl(lvl){
	return lvl*lvl*GetConVarInt(g_hCmodLvlRatio);
}
