/*
 * ============================================================================
 *
 *  SourceMod Project Base
 *
 *  File:          Weapons.inc
 *  Type:          Module
 *  Description:   Allow/Deny Class weapons for player
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
#if defined CLASS_SYS
#define CLASS_WEAPONS

stock Module:g_moduleClass_Weapons;

public Class_Weapons_OnPluginStart(){
	new moduledata[ModuleData];
	
	moduledata[ModuleData_Disabled] = false;
	moduledata[ModuleData_Hidden] = false;
	strcopy(moduledata[ModuleData_FullName], MM_DATA_FULLNAME, "[Cmod] Class Weapons");
	strcopy(moduledata[ModuleData_ShortName], MM_DATA_SHORTNAME, "Class_Weapons");
	strcopy(moduledata[ModuleData_Description], MM_DATA_DESCRIPTION, "Allow/Deny Class weapons for player");
	moduledata[ModuleData_Dependencies][0] = g_moduleClassSys;
	moduledata[ModuleData_Dependencies][1] = INVALID_MODULE;
	
	g_moduleClass_Weapons = ModuleMgr_Register(moduledata);
	
	EventMgr_RegisterEvent(g_moduleClass_Weapons, "Event_OnEventsRegister", "Class_Weapons_OnEventsRegister");
	
	g_hCmodAllowsWeapons = CreateArray(32);
	
	for(new i; i <= MAXPLAYERS; i++){
		g_hCmodPlayerAllowsWeapons[i] = CreateArray(32);
		g_hCmodPlayerBonusWeapons[i] = CreateArray(32);
	}
		
	#if defined PROJECT_GAME_CSGO
		PushArrayString(g_hCmodAllowsWeapons, "weapon_c4");
		PushArrayString(g_hCmodAllowsWeapons, "item_defuser");
		PushArrayString(g_hCmodAllowsWeapons, "weapon_knife");
		
		PushArrayString(g_hCmodClassWeapons[0], "weapon_glock");
		PushArrayString(g_hCmodClassWeapons[0], "weapon_hkp2000");
	#endif

}

public Class_Weapons_OnEventsRegister(){
	#if defined EVENT_MANAGER	
		EventMgr_RegisterEvent(g_moduleClass_Weapons, "Event_OnClassChangeSuccess", "Class_Weapons_OnClassChangeSuccess");
		#if defined PROJECT_GAME_CSGO
			EventMgr_RegisterEvent(g_moduleClass_Weapons, "Event_OnClientPutInServer", "Class_Weapons_EventOnClientPutInServer");
			EventMgr_RegisterEvent(g_moduleClass_Weapons, "Event_OnClientDisconnect", "Class_Weapons_EventOnClientDisconnect");
			
			EventMgr_RegisterEvent(g_moduleClass_Weapons, "Event_ItemEquip", "Class_Weapons_EventItemEquip");
			EventMgr_RegisterEvent(g_moduleClass_Weapons, "Event_PlayerSpawn", "Class_Weapons_EventPlayerSpawn");
		#endif	

	#endif
}

public Class_Weapons_OnClassChangeSuccess(client){
	Class_Weapons_RemoveAllWeapons(client);
	Class_Weapons_GiveWeapons(client);
}

#if defined PROJECT_GAME_CSGO

public Action:Class_Weapons_EventOnClientPutInServer(client){
	SDKHook(client, SDKHook_WeaponEquip, Class_Weapons_EventItemPickup); 
}

public Action:Class_Weapons_EventOnClientDisconnect(client){
	SDKUnhook(client, SDKHook_WeaponEquip, Class_Weapons_EventItemPickup); 
}


public Action:Class_Weapons_EventItemPickup(client, weapon){
	decl String:_buffer[64];
	GetEdictClassname(weapon, _buffer, sizeof(_buffer));
	
	if(Class_Weapons_CheckPlayerWeapon(client, _buffer)){
		AcceptEntityInput(weapon, "Kill");
		return Plugin_Handled;
	}
	
	return Plugin_Continue;
}

public Class_Weapons_EventItemEquip(client){
	decl String:_buffer[64];
	new _entClientWeapon = GetEntPropEnt(client, Prop_Send, "m_hActiveWeapon");
	
	GetClientWeapon(client, _buffer, sizeof(_buffer));
	
	if(Class_Weapons_CheckPlayerWeapon(client, _buffer)){
		CS_DropWeapon(client, _entClientWeapon, false);
	}	
}

public Class_Weapons_EventPlayerSpawn(client){
	CreateTimer(0.1, Class_Weapons_Timer, client, TIMER_FLAG_NO_MAPCHANGE);	
	//Class_Weapons_GiveWeapons(client);
}

public Action:Class_Weapons_Timer(Handle:timer, any:client){	
	Class_Weapons_GiveWeapons(client);
}
#endif



stock Class_Weapons_CheckPlayerWeapon(client, String:_buffer[]){
	if(client >= 1 && client <= MaxClients && IsClientConnected(client) && IsClientInGame(client) && !IsFakeClient(client) && IsPlayerAlive(client)){
		
		decl	String:_weapon[32],
				_tmpCount,
				_tmpClass;

		_tmpClass = g_iCmodPlayerClass[client];
		_tmpCount = GetArraySize(g_hCmodClassWeapons[_tmpClass]);
		for(new i; i < _tmpCount; i++){
			GetArrayString(g_hCmodClassWeapons[_tmpClass], i, _weapon, sizeof(_weapon));
			if(StrEqual(_weapon, _buffer))
				return 0;
		}
			
		_tmpCount = GetArraySize(g_hCmodPlayerBonusWeapons[client]);
		for(new i; i < _tmpCount; i++){
			GetArrayString(g_hCmodPlayerBonusWeapons[client], i, _weapon, sizeof(_weapon));
			if(StrEqual(_weapon, _buffer))
				return 0;
		}
		
		_tmpCount = GetArraySize(g_hCmodPlayerAllowsWeapons[client]);
		for(new i; i < _tmpCount; i++){
			GetArrayString(g_hCmodPlayerAllowsWeapons[client], i, _weapon, sizeof(_weapon));
			if(StrEqual(_weapon, _buffer))
				return 0;
		}
		
		_tmpCount = GetArraySize(g_hCmodAllowsWeapons);
		for(new i; i < _tmpCount; i++){
			GetArrayString(g_hCmodAllowsWeapons, i, _weapon, sizeof(_weapon));
			if(StrEqual(_weapon, _buffer))
				return 0;
		}
		
		return 1;
	}
	return 0;
}

stock Class_Weapons_RemoveAllWeapons(client){
		if(client >= 1 && client <= MaxClients && IsClientConnected(client) && IsClientInGame(client) && !IsFakeClient(client) && IsPlayerAlive(client)){
			new slot = -1;
			
			slot = GetPlayerWeaponSlot(client, CS_SLOT_PRIMARY);
			if(slot != -1)
				RemovePlayerItem(client, slot);
				
			slot = GetPlayerWeaponSlot(client, CS_SLOT_SECONDARY);	
			if(slot != -1)	
				RemovePlayerItem(client, slot);
				
			slot = GetPlayerWeaponSlot(client, CS_SLOT_GRENADE);	
			if(slot != -1)	
				RemovePlayerItem(client, slot);
	}
}

stock Class_Weapons_GiveWeapons(client){
	if(client >= 1 && client <= MaxClients && IsClientConnected(client) && IsClientInGame(client) && IsPlayerAlive(client)){
		decl String:_buffer[32];
		
		
		for(new i; i < GetArraySize(g_hCmodClassWeapons[g_iCmodPlayerClass[client]]); i++){
			GetArrayString(g_hCmodClassWeapons[g_iCmodPlayerClass[client]], i, _buffer, sizeof(_buffer));
			GivePlayerItem(client, _buffer);	
		}
		
		
		for(new i; i < GetArraySize(g_hCmodPlayerBonusWeapons[client]); i++){
			GetArrayString(g_hCmodPlayerBonusWeapons[client], i, _buffer, sizeof(_buffer));
			GivePlayerItem(client, _buffer);	
		}
		
	}
}

#endif
