#include <sourcemod>
#include <sdkhooks>
#include <cmod>

public Plugin:myinfo = {
	name = "Cmod Item: ExampleItem",
	author = "PLX",
	description = "Class example",
	version = "0.1",
	url = "http://steamcommunity.com/id/plx211"
};

public OnPluginStart(){
	Cmod_RegisterItem("ExampleItem", "Example desc", 1, 9);
}

public Cmod_OnItemEnabled(client, ItemID:id, value){
	PrintToChatAll("Player: %d enableitem: %d value: %d", client, id, value);
	PrintToChat(client, "You enable ExampleItem");
}

public Cmod_OnItemDisabled(client, ItemID:id){
	PrintToChatAll("Player: %d disable: %d", client, id);
	PrintToChat(client, "You disable ExampleItem");
}

public Cmod_OnClientUseItem(client, ItemID:id){
	PrintToChatAll("Player: %d use item: %d", client, id);
	PrintToChat(client, "You use ExampleItem");
}
