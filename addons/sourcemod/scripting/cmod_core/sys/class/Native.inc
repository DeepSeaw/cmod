#if defined CLASS_SYS
#define CLASS_NATIVE;
public Class_Native_GetClientClass(Handle:plugin, numParams){
	if(1 <= GetNativeCell(1) && GetNativeCell(1) <= MaxClients && IsClientConnected(GetNativeCell(1)) && IsClientInGame(GetNativeCell(1))){
		return g_iCmodPlayerClass[GetNativeCell(1)];
	}
	return -1;
}

public Class_Native_GetClassNameByID(Handle:plugin, numParams){
	if(GetNativeCell(1) <= g_iCmodClassCount && GetNativeCell(1) >= 0){
		SetNativeString(2, g_sCmodClassName[GetNativeCell(1)], GetNativeCell(3));	
		return 1;	
	}
	
	return 0;
}

public Class_Native_GetClassIDByName(Handle:plugin, numParams){
	decl String:_tmp[MAX_NAME_LONG+1];
	GetNativeString(1, _tmp, sizeof(_tmp));
	for(new i; i <= g_iCmodClassCount; i++){
		if(StrEqual(_tmp, g_sCmodClassName[i])){
			return i;
		}
	}
	return -1;
}

public Class_Native_GetClassDesc(Handle:plugin, numParams){
	if(GetNativeCell(1) <= g_iCmodClassCount && GetNativeCell(1) >= 0){
		SetNativeString(2, g_sCmodClassDesc[GetNativeCell(1)], GetNativeCell(3));	
		return 1;	
	}
	
	return 0;
}

public Class_Native_SortClass(Handle:plugin, numParams){
	#if defined CLASS_SORT
		Class_Sort_Start();
	#endif
}

public Class_Native_GetClassINT(Handle:plugin, numParams){
	return g_iCmodClassINT[GetNativeCell(1)];
}

public Class_Native_GetClassCON(Handle:plugin, numParams){
	return g_iCmodClassCON[GetNativeCell(1)];
}

public Class_Native_GetClassSTR(Handle:plugin, numParams){
	return g_iCmodClassSTR[GetNativeCell(1)];
}

public Class_Native_GetClassDEX(Handle:plugin, numParams){
	return g_iCmodClassDEX[GetNativeCell(1)];
}

public Class_Native_SetClassINT(Handle:plugin, numParams){
	g_iCmodClassINT[GetNativeCell(1)] = GetNativeCell(2);
}

public Class_Native_SetClassCON(Handle:plugin, numParams){
	g_iCmodClassCON[GetNativeCell(1)] = GetNativeCell(2);
}

public Class_Native_SetClassSTR(Handle:plugin, numParams){
	g_iCmodClassSTR[GetNativeCell(1)] = GetNativeCell(2);
}

public Class_Native_SetClassDEX(Handle:plugin, numParams){
	g_iCmodClassDEX[GetNativeCell(1)] = GetNativeCell(2);
}

public Class_Native_AddClassINT(Handle:plugin, numParams){
	g_iCmodClassINT[GetNativeCell(1)] += GetNativeCell(2);
}

public Class_Native_AddClassCON(Handle:plugin, numParams){
	g_iCmodClassCON[GetNativeCell(1)] += GetNativeCell(2);
}

public Class_Native_AddClassSTR(Handle:plugin, numParams){
	g_iCmodClassSTR[GetNativeCell(1)] += GetNativeCell(2);
}

public Class_Native_AddClassDEX(Handle:plugin, numParams){
	g_iCmodClassDEX[GetNativeCell(1)] += GetNativeCell(2);
}

public Class_Native_GetClassWeapons(Handle:plugin, numParams){
	#if defined CLASS_WEAPONS
		return _:g_hCmodClassWeapons[GetNativeCell(1)];
	#else
		return 0;
	#endif
}

public Class_Native_GetClientWeapons(Handle:plugin, numParams){
	#if defined CLASS_WEAPONS
		return _:g_hCmodPlayerAllowsWeapons[GetNativeCell(1)];
	#else
		return 0;
	#endif
}

public Class_Native_GetAllowWeapons(Handle:plugin, numParams){
	#if defined CLASS_WEAPONS
		return _:g_hCmodAllowsWeapons;
	#else
		return 0;
	#endif
}

public Class_Native_GetBonusWeapons(Handle:plugin, numParams){
	#if defined CLASS_WEAPONS
		return _:g_hCmodPlayerBonusWeapons[GetNativeCell(1)];
	#else
		return 0;
	#endif
}

#endif
