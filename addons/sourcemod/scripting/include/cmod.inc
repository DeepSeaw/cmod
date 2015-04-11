#if defined _cmod_included
 #endinput
#endif
#define _cmod_included

#if !defined _sdkhooks_included
#include <sdkhooks>
#endif

#define CMOD_DISABLE -1
#define CMOD_CONTINUE 0
#define MOD_TAG "[Cmod]"

enum ClassID{
	INVALID_CLASS = -1,
};

enum ItemID{
	INVALID_ITEM = -1,
};


/**
 * ----------------------------------------
 *                   Stats
 * ----------------------------------------
 */

native Cmod_GetClientPoint(const client);

native Cmod_SetClientPoint(const client, const value);

native Cmod_AddClientPoint(const client, const value);

native Cmod_GetClientINT(const client);

native Cmod_SetClientINT(const client, const value);

native Cmod_AddClientINT(const client, const value);

native Cmod_GetClientCON(const client);

native Cmod_SetClientCON(const client, const value);

native Cmod_AddClientCON(const client, const value);

native Cmod_GetClientSTR(const client);

native Cmod_SetClientSTR(const client, const value);

native Cmod_AddClientSTR(const client);

native Cmod_GetClientDEX(const client);

native Cmod_SetClientDEX(const client, const value);

native Cmod_AddClientDEX(const client, const value);

native Cmod_GetBonusINT(const client);

native Cmod_SetBonusINT(const client, const value);

native Cmod_AddBonusINT(const client, const value);

native Cmod_GetBonusCON(const client);

native Cmod_SetBonusCON(const client, const value);

native Cmod_AddBonusCON(const client, const value);

native Cmod_GetBonusSTR(const client);

native Cmod_SetBonusSTR(const client, const value);

native Cmod_AddBonusSTR(const client, const value);

native Cmod_GetBonusDEX(const client);

native Cmod_SetBonusDEX(const client, const value);

native Cmod_AddBonusDEX(const client, const value);

native Cmod_GetClassINT(const ClassID:id);

native Cmod_GetClassCON(const ClassID:id);

native Cmod_GetClassSTR(const ClassID:id);

native Cmod_GetClassDEX(const ClassID:id);

native Cmod_SetClassINT(const ClassID:id, const value);

native Cmod_SetClassCON(const ClassID:id, const value);

native Cmod_SetClassSTR(const ClassID:id, const value);

native Cmod_SetClassDEX(const ClassID:id, const value);

native Cmod_AddClassINT(const ClassID:id, const value);

native Cmod_AddClassCON(const ClassID:id, const value);

native Cmod_AddClassSTR(const ClassID:id, const value);

native Cmod_AddClassDEX(const ClassID:id, const value);

native Cmod_ResetPlayerStats(const client);

native Cmod_ShowStatsMenu(const client);

native Float:Cmod_GetResistance(const client);

/**
 * ----------------------------------------
 *                  lvl/exp
 * ----------------------------------------
 */
  
native Cmod_GetExp(const client);

native Cmod_SetExp(const client, const value);

native Cmod_AddExp(const client, const value);

native Cmod_GetBonusExp(const client);

native Cmod_SetBonusExp(const client, const value);

native Cmod_AddBonusExp(const client, const value);

native Cmod_GetExpForLvl(const lvl);

native Cmod_CheckClientLvl(const client);  
  
/** 
 * ----------------------------------------
 *                  Class
 * ----------------------------------------
 */
 
native ClassID:Cmod_RegisterClass(const String:name[], const String:desc[], const pINT = 0, const pCON = 0, const pSTR = 0, const pDEX = 0, const Handle:weapons = INVALID_HANDLE);

native ClassID:Cmod_GetClientClass(const client);

native Cmod_GetClassNameByID(const ClassID:id, const String:buffer[], const MaxLeng);

native ClassID:Cmod_GetClassIDByName(const String:ClassName);

native Cmod_GetClassDesc(const ClassID:id, const String:buffer[], const MaxLeng);

native Cmod_SortClass();

native Handle:Cmod_GetClassWeapons(const ClassID:id);

native Handle:Cmod_GetClientWeapons(const client);

native Handle:Cmod_GetAllowWeapons();

native Handle:Cmod_GetClientBonusWeapons(const client);

forward Cmod_OnClassEnabled(client, ClassID:id);

forward Cmod_OnClassDisabled(client, ClassID:id);

forward Cmod_OnClientUseSkill(client, ClassID:id);

forward Cmod_OnGetNewClassID(ClassID:oldId, ClassID:newId);
 
/** 
 * ----------------------------------------
 *                  Item
 * ----------------------------------------
 */

native ItemID:Cmod_RegisterItem(const String:name[], const String:desc[], const minValue = 0, const maxValue = 0);

native ItemID:Cmod_GetClientItem(const client);

native Cmod_GetItemNameByID(const ItemID:id, const String:buffer[], const MaxLeng);

native ItemID:Cmod_GetItemIDByName(const String:ItemName[]);

native Cmod_GetItemDesc(const ItemID:id, const String:buffer[], const MaxLeng);

native Cmod_GetMinItemValue(const ItemID:id);

native Cmod_GetMaxItemValue(const ItemID:id)

native Cmod_GetClientItemValue(const client);

native Cmod_SetMinItemValue(const ItemID:id, const value);

native Cmod_SetMaxItemValue(const ItemID:id, const value);

native Cmod_SetClientItemValue(const client, const value);

native Cmod_GetItemCount();

native Cmod_SetClientItem(const client, const ItemID:id);

forward Cmod_OnItemEnabled(client, ItemID:id, value);

forward Cmod_OnItemDisabled(client, ItemID:id);

forward Cmod_OnClientUseItem(client, ItemID:id);

/**
 * ----------------------------------------
 *                   Stock
 * ----------------------------------------
 */

stock Cmod_GetINT(const client){
	new _point;
	_point += Cmod_GetClientINT(client);
	_point += Cmod_GetClassINT(Cmod_GetClientClass(client));
	_point += Cmod_GetBonusINT(client);
	return _point;
}

stock Cmod_GetCON(const client){
	new _point;
	_point += Cmod_GetClientCON(client);
	_point += Cmod_GetClassCON(Cmod_GetClientClass(client));
	_point += Cmod_GetBonusCON(client);
	return _point;
}

stock Cmod_GetSTR(const client){
	new _point;
	_point += Cmod_GetClientSTR(client);
	_point += Cmod_GetClassSTR(Cmod_GetClientClass(client));
	_point += Cmod_GetBonusSTR(client);
	return _point;
}

stock Cmod_GetDEX(const client){
	new _point;
	_point += Cmod_GetClientDEX(client);
	_point += Cmod_GetClassDEX(Cmod_GetClientClass(client));
	_point += Cmod_GetBonusDEX(client);
	return _point;
}

stock Cmod_InflictDMG(victim, inflictor, attacker, Float:damage, damageType=DMG_GENERIC, weapon=-1, const Float:damageForce[3]=NULL_VECTOR, const Float:damagePosition[3]=NULL_VECTOR){
	new Float:_tmp = FloatSub(damage, FloatMul(damage, Cmod_GetResistance(victim)));
	if(FloatCompare(_tmp, 0.0) == 1)
		damage = _tmp;
	else
		damage = 1.0;
	SDKHooks_TakeDamage(victim, inflictor, attacker, damage, damageType, weapon, damageForce, damagePosition); 
}

