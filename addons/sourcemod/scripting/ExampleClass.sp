#include <sourcemod>
#include <sdkhooks>
#include <cmod>

public Plugin:myinfo = {
	name = "Cmod class: ExampleClass",
	author = "PLX",
	description = "Class example",
	version = "0.1",
	url = "http://steamcommunity.com/id/plx211"
};

public OnPluginStart(){
	new Handle:weapons = CreateArray(32);
	PushArrayString(weapons, "weapon_awp");
	PushArrayString(weapons, "weapon_hkp2000");
	Cmod_RegisterClass("ExampleClass", "Example desc", 10, 20, 30, 40, weapons);
}

public Cmod_OnClassEnabled(client, ClassID:id){
	PrintToChatAll("Player: %d enable: %d", client, id);
	PrintToChat(client, "You enable ExampleClass");
}

public Cmod_OnClassDisabled(client, ClassID:id){
	PrintToChatAll("Player: %d disable: %d", client, id);
	PrintToChat(client, "You disable ExampleClass");
}

public Cmod_OnClientUseSkill(client, ClassID:id){
	PrintToChatAll("Player: %d use skill class: %d", client, id);
	PrintToChat(client, "You use ExampleClass skill");
}
