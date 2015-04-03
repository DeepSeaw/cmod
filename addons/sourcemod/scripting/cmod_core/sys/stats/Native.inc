#if defined STATS_SYS
#define STATS_NATIVE

public Stats_Native_GetPlayerPoint(Handle:plugin, numParams){
	return g_iCmodPlayerPoint[GetNativeCell(1)]; 
}

public Stats_Native_SetPlayerPoint(Handle:plugin, numParams){
	g_iCmodPlayerPoint[GetNativeCell(1)] = GetNativeCell(2); 
}

public Stats_Native_GetPlayerINT(Handle:plugin, numParams){
	return g_iCmodPlayerINT[GetNativeCell(1)]; 
}

public Stats_Native_SetPlayerINT(Handle:plugin, numParams){
	g_iCmodPlayerINT[GetNativeCell(1)] = GetNativeCell(2); 
}

public Stats_Native_GetPlayerCON(Handle:plugin, numParams){
	return g_iCmodPlayerCON[GetNativeCell(1)]; 
}

public Stats_Native_SetPlayerCON(Handle:plugin, numParams){
	g_iCmodPlayerCON[GetNativeCell(1)] = GetNativeCell(2); 
}

public Stats_Native_GetPlayerSTR(Handle:plugin, numParams){
	return g_iCmodPlayerSTR[GetNativeCell(1)]; 
}

public Stats_Native_SetPlayerSTR(Handle:plugin, numParams){
	g_iCmodPlayerSTR[GetNativeCell(1)] = GetNativeCell(2); 
}

public Stats_Native_GetPlayerDEX(Handle:plugin, numParams){
	return g_iCmodPlayerDEX[GetNativeCell(1)]; 
}

public Stats_Native_SetPlayerDEX(Handle:plugin, numParams){
	g_iCmodPlayerDEX[GetNativeCell(1)] = GetNativeCell(2); 
}

public Stats_Native_GetBonusINT(Handle:plugin, numParams){
	return g_iCmodBonusINT[GetNativeCell(1)]; 
}

public Stats_Native_SetBonusINT(Handle:plugin, numParams){
	g_iCmodBonusINT[GetNativeCell(1)] = GetNativeCell(2); 
}

public Stats_Native_GetBonusCON(Handle:plugin, numParams){
	return g_iCmodBonusCON[GetNativeCell(1)]; 
}

public Stats_Native_SetBonusCON(Handle:plugin, numParams){
	g_iCmodBonusCON[GetNativeCell(1)] = GetNativeCell(2); 
}

public Stats_Native_GetBonusSTR(Handle:plugin, numParams){
	return g_iCmodBonusSTR[GetNativeCell(1)]; 
}

public Stats_Native_SetBonusSTR(Handle:plugin, numParams){
	g_iCmodBonusSTR[GetNativeCell(1)] = GetNativeCell(2); 
}

public Stats_Native_GetBonusDEX(Handle:plugin, numParams){
	return g_iCmodBonusDEX[GetNativeCell(1)]; 
}

public Stats_Native_SetBonusDEX(Handle:plugin, numParams){
	g_iCmodBonusDEX[GetNativeCell(1)] = GetNativeCell(2); 
}

public Stats_Native_ResetPlayerStats(Handle:plugin, numParams){
	#if defined STATS_RESET
		Stats_Reset_Start(GetNativeCell(1));
	#endif 
}

public Stats_Native_ShowStatsMenu(Handle:plugin, numParams){
	#if defined STATS_MENU
		Stats_Menu_Show(GetNativeCell(1));
	#endif 	
}

public Stats_Native_GetResistance(Handle:plugin, numParams){
	return _:FloatMul(float(Stats_GetSTR(GetNativeCell(1))), 0.2); 
}


#endif
