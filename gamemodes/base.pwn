#define YSI_NO_HEAP_MALLOC
#pragma dynamic 8192

#include <a_samp>
#include <a_mysql>
#include <a_zone>
#include <streamer>
#include <samp_bcrypt>
#include <YSF>
#include <Pawn.RakNet>
#include <Pawn.CMD>
#include <weapon-config>
#include <sort-inline>
#include <strlib>
#include <slcrypt>
#include <timestamp>

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

#include "modules/global/defines.inc"
#include "modules/global/variables.inc"
#include "modules/functions.inc"
#include "modules/auth.inc"

main()
{
    bcrypt_set_thread_limit(3);
} 

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
    return true;
}

public OnGameModeExit()
{
    return true;
}

public OnPlayerConnect(playerid)
{
    GetPlayerName(playerid, playerInfo[playerid][e_PlayerName], MAX_PLAYER_NAME + 1);
    GetPlayerIp(playerid, playerInfo[playerid][e_PlayerLastIp]);

    LoadPlayerAccount(playerid);
    return true;
}

public OnPlayerDisconnect(playerid)
{
    return true;
}

public OnPlayerRequestClass(playerid, classid)
{
    return true;
}

public OnPlayerRequestSpawn(playerid)
{
    return true;
}

public OnPlayerSpawn(playerid)
{
    SetPlayerInterior(playerid, 0);
    SetPlayerWorldBounds(playerid, 20000.0, -20000.0, 20000.0, -20000.0);

    if (IsPlayerInAnyVehicle(playerid)){
        RemovePlayerFromVehicle(playerid);
    }

    return true;
}

public OnPlayerText(playerid, text[])
{
    return false;
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    return true;
}

public OnPlayerDeath(playerid, killerid, reason)
{
    if(playerid == INVALID_PLAYER_ID && killerid == INVALID_PLAYER_ID)
    {
        return false;
    }

    return true;
}

public OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ)
{
    return true;
}

public OnPlayerDamage(&playerid, &Float:amount, &issuerid, &weapon, &bodypart)
{
    if (issuerid == INVALID_PLAYER_ID || playerid == INVALID_PLAYER_ID || weapon == WEAPON_COLLISION){
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