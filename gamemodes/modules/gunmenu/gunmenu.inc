
stock ShowGunMenu(playerid)
{
    new str[500] = "Slot\tSelected Weapon\n";

    for (new i; i < MAX_GUNMENU_SLOTS; i ++){
        format(str, sizeof str, "%s{ffffff}Slot %d\t%s%s\n", str, i + 1, playerInfo[playerid][e_PlayerWeapons][i] != 0 ? "{008000}" : "{ff0000}", ReturnWeaponName(playerInfo[playerid][e_PlayerWeapons][i]));
    }

    return Dialog_Show(playerid, DIALOG_GUNMENU, DIALOG_STYLE_TABLIST_HEADERS, "{f3e5ab}Select a slot", str, "Select", "Close");
}

Dialog:DIALOG_GUNMENU(playerid, response, listitem, inputtext[])
{
    if (response)
    {
        SetPVarInt(playerid, "gunmenuSlot", listitem);
        ShowGunMenuSlot(playerid);
    }
    else{

        new bool:allEmpty = true;
        for (new i; i < MAX_GUNMENU_SLOTS; i ++)
        {
            if (playerInfo[playerid][e_PlayerWeapons][i] != 0)
            {
                allEmpty = false;
                break;
            }
        }

        if (allEmpty){
            return SendClientMessage(playerid, 0xbd9099ff, "(error) Select at least one weapon to play."), ShowGunMenu(playerid);
        }

        GivePlayerWeapons(playerid);
        SetPlayerVirtualWorld(playerid, ARENA_VW);
    }
    return true;
}

stock ShowGunMenuSlot(playerid)
{
    new str[500], title[65], slot = GetPVarInt(playerid, "gunmenuSlot");

    format(title, sizeof title, "{f3e5ab}Choose a weapon for slot [%d]", slot + 1);

    for (new i; i < sizeof gunMenuAvailableWeapons; i ++){
        format(str, sizeof str, "%s%s%s\t\t%s\n", str, i == 0 ? "{ff0000}" : "{ffffff}", ReturnWeaponName(gunMenuAvailableWeapons[i]), playerInfo[playerid][e_PlayerWeapons][slot] == gunMenuAvailableWeapons[i] ? "{008000}(selected)" : "");        
    }

    return Dialog_Show(playerid, DIALOG_GUNMENU_SLOT, DIALOG_STYLE_LIST, title, str, "Select", "Return");
}

Dialog:DIALOG_GUNMENU_SLOT(playerid, response, listitem, inputtext[])
{
    if (response)
    {
        new slot = GetPVarInt(playerid, "gunmenuSlot");
        playerInfo[playerid][e_PlayerWeapons][slot] = gunMenuAvailableWeapons[listitem];
    
        ShowGunMenu(playerid);
    }
    else
        ShowGunMenu(playerid);

    return true;
}