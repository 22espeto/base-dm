#define YSI_NO_HEAP_MALLOC
#pragma dynamic 8192

#include <a_samp>
#include <a_mysql>
#include <a_zone>
#include <streamer>
#include <YSF>
#include <Pawn.RakNet>
#include <Pawn.CMD>
#include <weapon-config>
#include <sort-inline>
#include <strlib>
#include <slcrypt>
#include <timestamp>
#include <crashdetect>

#include <YSI_Coding\y_timers>
#include <YSI_Coding\y_va>
#include <YSI_Coding\y_timers>
#include <YSI_Coding\y_inline>
#include <YSI_Extra\y_inline_mysql>
#include <YSI_Extra\y_inline_timers>
#include <YSI_Visual\y_dialog>
#include <YSI_Data\y_iterate>

#include <sscanf2>
#include <easydialog>

#include "modules/textdraws/textdraws.inc"

#include "modules/global/colors.inc"
#include "modules/global/defines.inc"
#include "modules/gunmenu/header.inc"
#include "modules/global/variables.inc"

#include "modules/arena/h_arena.inc"

#include "modules/functions.inc"
#include "modules/ban/functions.inc"
#include "modules/account.inc"

#include "modules/arena/functions.inc"
#include "modules/arena/arena.inc"

#include "modules/commands/header.inc"
#include "modules/commands/commands.inc"
#include "modules/commands/general.inc"
#include "modules/commands/admin.inc"

#include "modules/gunmenu/gunmenu.inc"

public OnGameModeInit()
{
    mysql_log(ERROR | WARNING);
    dbHandle = mysql_connect_file("mysql.ini");

    if(dbHandle == MYSQL_INVALID_HANDLE || mysql_errno() != 0)
    {
        print("MySQL Failed");
        SendRconCommand("exit");
        return false;
    }

    print("MySQL Connected");

	UsePlayerPedAnims();
	EnableStuntBonusForAll(false);
	EnableVehicleFriendlyFire();
	DisableInteriorEnterExits();
    SetDamageSounds(0, 0);
    SetRespawnTime(2000);

    for (new i; i < sizeof AvailableSkins; i ++){
        AddPlayerClass(AvailableSkins[i], 411.1662, 2534.0742, 19.1484, 0.1074, 0, 0, 0, 0, 0, 0);
    }

    return true;
}

public OnGameModeExit()
{
    return true;
}

public OnPlayerConnect(playerid)
{
    InicializePlayer(playerid);
    
    GetPlayerName(playerid, playerInfo[playerid][e_PlayerName], MAX_PLAYER_NAME + 1);
    GetPlayerIp(playerid, playerInfo[playerid][e_PlayerLastIp]);
    
    FixRequestClass(playerid);
    return true;
}

public OnPlayerRequestClass(playerid, classid)
{    
    if (!playerInfo[playerid][e_PlayerLogged] && !inClassSelection[playerid]){
        LoadPlayerAccount(playerid);
    }

    inClassSelection[playerid] = true;

    SetPlayerSkin(playerid, !classid ? playerInfo[playerid][e_PlayerSkin] : AvailableSkins[classid]);
    return true;
}

public OnPlayerRequestSpawn(playerid)
{
    if (!playerInfo[playerid][e_PlayerLogged] || GetPVarInt(playerid, "alreadySpawned")){
        return false;
    }

    playerInfo[playerid][e_PlayerSkin] = GetPlayerSkin(playerid);
    return true;
}

public OnPlayerDisconnect(playerid, reason)
{
    if (!playerInfo[playerid][e_PlayerLogged]){
        return false;
    }
    
    if (reason != 2){
        SendClientMessageToAll(COLOR_GRAY, "%s has left the server", playerInfo[playerid][e_PlayerName]);
    }

    SavePlayerAccount(playerid);
    return true;
}

public OnPlayerSpawn(playerid)
{
    if (IsPlayerInAnyVehicle(playerid)){
        RemovePlayerFromVehicle(playerid);
    }

    SetPlayerInterior(playerid, 0);
    SetPlayerWorldBounds(playerid, 20000.0, -20000.0, 20000.0, -20000.0);
    SetPlayerSkin(playerid, playerInfo[playerid][e_PlayerSkin]);
    SetPlayerColor(playerid, COLOR_GRAY);
    SpawnPlayerOnArena(playerid);

    if (!GetPVarInt(playerid, "alreadySpawned"))
    {
        ShowTextdraws(playerid);

        if (arenaInfo[e_ArenaRunning]){
            ZoneNumberFlashForPlayer(playerid, arenaInfo[e_ArenaId], 0xDB0000FF);
        }
        else
        {
            TogglePlayerControllable(playerid, false);
            ShowArenaScoreboard(playerid);
        }

        SetPVarInt(playerid, "alreadySpawned", 1);
    }

    return true;
}

public OnPlayerText(playerid, text[])
{
    if (!playerInfo[playerid][e_PlayerLogged]){
        return false;
    }

    SendClientMessageToAll(COLOR_GRAY, "%s (%d): %s", playerInfo[playerid][e_PlayerName], playerid, text);
    return false;
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if (newkeys == KEY_CTRL_BACK)
    {
        if (IsPlayerInArena(playerid)){
            SpawnPlayer(playerid);
        }
    }

    if (newkeys == 160 && !IsBulletWeapon(GetPlayerWeapon(playerid)) && !IsPlayerInAnyVehicle(playerid))
    {
        if (GetTickCount() - GetPVarInt(playerid, "resyncTick") >= 2500)
        {
            ResyncPlayer(playerid);
            SetPVarInt(playerid, "resyncTick", GetTickCount());
        }
	}

    return true;
}

public OnPlayerDeath(playerid, killerid, reason)
{
    if (playerid == INVALID_PLAYER_ID && killerid == INVALID_PLAYER_ID){
        return false;
    }

    KillMessages(killerid, playerid);

    if (arenaInfo[e_ArenaRunning] && IsPlayerInArena(killerid) && IsPlayerInArena(playerid))
    {   
        playerArenaInfo[killerid][e_ArenaKills] ++;
        playerArenaInfo[playerid][e_ArenaDeaths] ++;

        playerInfo[killerid][e_PlayerKills] ++;
        playerInfo[playerid][e_PlayerDeaths] ++;
    }

    return true;
}

public OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ)
{
    return true;
}

public OnPlayerDamage(&playerid, &Float:amount, &issuerid, &weapon, &bodypart)
{
    if (issuerid == INVALID_PLAYER_ID || playerid == INVALID_PLAYER_ID || weapon == WEAPON_COLLISION || !playerInfo[issuerid][e_PlayerLogged]){
        return false;
    }

    if (weapon == WEAPON_DEAGLE)
	{
	    switch(bodypart)
		{
			case 3: amount = 35.0;
			case 4: amount = 35.0;
			case 5: amount = 30.0;
			case 6: amount = 30.0;
			case 7: amount = 30.0;
			case 8: amount = 30.0;
			case 9: amount = 40.0;
		}
	}
    
    if (IsPlayerInArena(issuerid) && arenaInfo[e_ArenaRunning])
    {
        playerArenaInfo[issuerid][e_ArenaDamage] += floatround(amount);
    }

    return true;
}

public OnPlayerDamageDone(playerid, Float:amount, issuerid, WEAPON:weapon, bodypart)
{
    new Float:shotPos[6], PlayerText3D:DamageLabel;

	GetPlayerLastShotVectors(issuerid, shotPos[0], shotPos[1], shotPos[2], shotPos[0], shotPos[1], shotPos[2]);
    DamageLabel = CreatePlayer3DTextLabel(issuerid, "%d", SetAlpha(0xFFFFFFFF, 185), shotPos[0], shotPos[1], shotPos[2], 80.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, false, floatround(amount));
    
    SetTimerEx("DestroyDamageLabel", 2000, false, "dd", issuerid, _:DamageLabel);
    PlayerPlaySound(issuerid, 17802, 0, 0, 0);
    return true;
}

forward DestroyDamageLabel(issuerid, PlayerText3D:DamageLabel);
public DestroyDamageLabel(issuerid, PlayerText3D:DamageLabel)
{
	DeletePlayer3DTextLabel(issuerid, DamageLabel);
	return true;
}

public OnPlayerClickPlayer(playerid, clickedplayerid, source)
{
    return true;
}