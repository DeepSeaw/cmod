/*
 * ============================================================================
 *
 *  SourceMod Project Base
 *
 *  File:          sql.inc
 *  Type:          Module
 *  Description:   Basic save system
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

#define SQL_SYS

stock Module:g_moduleSQLSys;

public SQLSys_OnPluginStart(){
	new moduledata[ModuleData];
	
	moduledata[ModuleData_Disabled] = false;
	moduledata[ModuleData_Hidden] = true;
	strcopy(moduledata[ModuleData_FullName], MM_DATA_FULLNAME, "[Cmod:core] Save data system");
	strcopy(moduledata[ModuleData_ShortName], MM_DATA_SHORTNAME, "SQLSys");
	strcopy(moduledata[ModuleData_Description], MM_DATA_DESCRIPTION, "Basic save system");
	moduledata[ModuleData_Dependencies][0] = INVALID_MODULE;
	
	g_moduleSQLSys = ModuleMgr_Register(moduledata);
	
	EventMgr_RegisterEvent(g_moduleSQLSys, "Event_OnEventsRegister", "SQLSys_OnEventsRegister");
	
	g_hCmodSQL = SQLite_UseDatabase("codmod_lvl", g_sCmodSQLError, sizeof(g_sCmodSQLError));
	if(g_hCmodSQL == INVALID_HANDLE)
		PrintToServer("Could not connect: %s", g_sCmodSQLError);
	
	SQL_FastQuery(g_hCmodSQL, "CREATE VIRTUAL TABLE IF NOT EXISTS codmod_info USING fts4(steamid, class);");
		
	SQL_FastQuery(g_hCmodSQL, "CREATE TABLE IF NOT EXISTS codmod (id INTEGER primary key autoincrement, steamid TEXT references codmod_info(steamid), class TEXT references codmod_info(class), lvl INTEGER, exp INTEGER, sPoints INTEGER, sInt INTEGER, sCon INTEGER, sStr INTEGER, sDex INTEGER, UNIQUE(steamid, class) ON CONFLICT REPLACE);");	
	
}

public SQLSys_OnEventsRegister(){
	#if defined EVENT_MANAGER	
		EventMgr_RegisterEvent(g_moduleSQLSys, "Event_OnClientPutInServer", "SQLSys_OnClientPutInServer");
		EventMgr_RegisterEvent(g_moduleSQLSys, "Event_OnClientDisconnect", "SQLSys_OnClientDisconnect");
	#endif
}

public SQLSys_OnClientPutInServer(client){
	g_iCmodPlayerClass[client] = 0;
	SQLSys_Load(client, 0);
}

public SQLSys_OnClientDisconnect(client){
	SQLSys_Save(client);
}

public SQLSys_Save(id)
{
	decl String:_tmp[1025];
	decl String:_authid[64];
	
	if(IsFakeClient(id))
		return;
		
	if(!GetClientAuthId(id, AuthId_Steam2, _authid, 63))
		return;
	
	//LogError("_auth = %s", _authid);
	
	Format(_tmp, sizeof(_tmp), "INSERT INTO codmod (steamid, class, lvl, exp, sPoints, sInt, sCon, sStr, sDex) VALUES ('%s', '%s', %d, %d, %d, %d, %d, %d, %d);", _authid, g_sCmodClassName[g_iCmodPlayerClass[id]], g_iCmodLvl[id], g_iCmodExp[id], g_iCmodPlayerPoint[id], g_iCmodPlayerINT[id], g_iCmodPlayerCON[id], g_iCmodPlayerSTR[id], g_iCmodPlayerDEX[id]);
	SQL_TQuery(g_hCmodSQL, SQLSys_SaveHandle, _tmp);
}

public SQLSys_SaveHandle(Handle:owner, Handle:hndl, const String:error[], any:data){
	if (hndl == INVALID_HANDLE){
		LogError("[Cmod:SQL:Save]Query failed! %s", error);
	}
}

public SQLSys_Load(id, classN)
{
	new String:_tmp[513];
	decl String:_authid[64];
	if(!GetClientAuthId(id, AuthId_Steam2, _authid, 63))
		return -1;
		
	Format(_tmp, sizeof(_tmp), "SELECT lvl, exp, sPoints, sInt, sCon, sStr, sDex FROM codmod WHERE steamID = '%s' AND class = '%s';", _authid, g_sCmodClassName[classN]);
	new Handle:_query = SQL_Query(g_hCmodSQL, _tmp);
	
	if(_query == INVALID_HANDLE){
		SQL_GetError(g_hCmodSQL, g_sCmodSQLError, sizeof(g_sCmodSQLError));
		PrintToServer("Failed to readClassFromDB query (error: %s)", g_sCmodSQLError);
		return 0;
	}
	
	if(SQL_GetRowCount(_query)){
		g_iCmodLvl[id] = SQL_FetchInt(_query, 0);
		g_iCmodExp[id] = SQL_FetchInt(_query, 1);
		g_iCmodPlayerPoint[id] = SQL_FetchInt(_query, 2);
		g_iCmodPlayerINT[id] = SQL_FetchInt(_query, 3);
		g_iCmodPlayerCON[id] = SQL_FetchInt(_query, 4);
		g_iCmodPlayerSTR[id] = SQL_FetchInt(_query, 5);
		g_iCmodPlayerDEX[id] = SQL_FetchInt(_query, 6);
	}else{
		g_iCmodLvl[id] = 1;
		g_iCmodExp[id] = 0;
		g_iCmodPlayerPoint[id] = 0;
		g_iCmodPlayerINT[id] = 0;
		g_iCmodPlayerCON[id] = 0;
		g_iCmodPlayerSTR[id] = 0;
		g_iCmodPlayerDEX[id] = 0;
	}
	
	CloseHandle(_query);
	return 1;
}

public SQLSys_LoadLvl(id, classN)
{
	new String:_tmp[513];
	decl String:_authid[64];
	if(!GetClientAuthId(id, AuthId_Steam2, _authid, 63))
		return -1;
	Format(_tmp, sizeof(_tmp), "SELECT lvl FROM codmod WHERE steamID = '%s' AND class = '%s';", _authid, g_sCmodClassName[classN]);
	new Handle:_query = SQL_Query(g_hCmodSQL, _tmp);
	
	if(_query == INVALID_HANDLE){
		SQL_GetError(g_hCmodSQL, g_sCmodSQLError, sizeof(g_sCmodSQLError));
		PrintToServer("Failed to query readLvlClassFromDB (error: %s)", g_sCmodSQLError);
		return -2;
	}
	
	if(SQL_GetRowCount(_query)){
		new _r = SQL_FetchInt(_query, 0);
		CloseHandle(_query);
		return _r;
	}else{
		CloseHandle(_query);
		return 1;
	}
}
