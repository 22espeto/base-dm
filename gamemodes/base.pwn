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
#include <md-sort\md-sort>
#include <strlib>
#include <slcrypt>
#include <timestamp>
#include <fly>

#include <YSI_Coding\y_timers>
#include <YSI_Coding\y_va>
#include <YSI_Coding\y_timers>
#include <YSI_Coding\y_inline>
#include <YSI_Extra\y_inline_mysql>
#include <YSI_Extra\y_inline_timers>
#include <YSI_Visual\y_dialog>
#include <YSI_Data\y_iterate>
#include <YSI_Game\y_vehicledata>

#include <sscanf2>
#include <easydialog>

#include "include/colors.inc"
#include "include/messages.inc"
#include "include/global.inc"
#include "include/player.inc"
#include "include/textdraws.inc"
#include "include/objects.inc"
#include "zones/h_zones.inc"
#include "commands/h_cmds.inc"
#include "location/h_location.inc"
#include "clan/h_clan.inc"
#include "duel/h_duel.inc"
#include "admin/h_admin.inc"
#include "frenzy/h_frenzy.inc"
#include "dox/h_dox.inc"

#include "anti-cheat/functions.inc"

#include "utils/functions.inc"
#include "admin/functions.inc"
#include "admin/admin.inc"
#include "location/location.inc"
#include "zones/zones.inc"
#include "clan/clan.inc"
#include "duel/duel.inc"
#include "frenzy/frenzy.inc"
#include "dox/dox.inc"

#include "include/dialogs.inc"

#include "account/constructor.inc"

#include "commands/cmds.inc"

public OnGameModeInit()
{
    mysql_log(ERROR | WARNING);
    // dbHandle = mysql_connect("localhost", "root", "", "lwz remake");
    dbHandle = mysql_connect("177.54.147.212", "enzob_3463", "4NRs607Xdv", "enzob_3463");

    if(dbHandle == MYSQL_INVALID_HANDLE || mysql_errno() != 0)
    {
        print("MySQL Fail to connect.");
        SendRconCommand("exit");
        return false;
    }
    print("MySQL Connected.");

    SendRconCommandf("hostname %s", SERVER_HOSTNAME);
    SendRconCommandf("gamemodetext %s", SERVER_MODE);
    SendRconCommandf("language %s", SERVER_LANGUAGE);
    SendRconCommandf("weburl %s", SERVER_WEBURL);

	UsePlayerPedAnims();
	EnableStuntBonusForAll(false);
	EnableVehicleFriendlyFire();
	DisableInteriorEnterExits();
    SetDamageSounds(0, 0);
    SetRespawnTime(2000);
    InitLocations();
    CreateTrainingNPCS();

    LoadClans();
    LoadZones();

	for (new i; i < 30; i++){
		AddPlayerClass(random(200), 375.9649,-2025.7683,7.8301,89.9547, 0, 0, 0, 0, 0, 0);
    }

    return true;
}

public OnGameModeExit()
{
    foreach(new i:Clans){
        SaveClan(i);
    }

    for (new i; i < MAX_PLAYERS; i ++)
    {
        if (IsPlayerConnected(i) && AlreadySpawned[i])
        {
            SavePlayerAccount(i);

            if (eAdmin[i][e_ADMIN_DUTY]){
                SaveAdmin(i);
            }
        }
    }

    return true;
}

public OnPlayerConnect(playerid)
{
    InitFly(playerid);

    SetPlayerColor(playerid, COLOR_LIGHT_GRAY);
    ResetPlayerVars(playerid);
    
    if(IsPlayerNPC(playerid))
    {
        SpawnPlayer(playerid);
        SetPlayerVirtualWorld(playerid, 555);
        return false;
    }

    SetSpawnInfo(playerid, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    
    GetPlayerName(playerid, eUser[playerid][e_USER_NAME], MAX_PLAYER_NAME);
    GetPlayerIp(playerid, eUser[playerid][e_USER_LAST_IP], 16);
    GetPlayerVersion(playerid, eUser[playerid][e_USER_CLIENT]);

    eUser[playerid][e_USER_LAST_GPCI] = ReturnGPCI(playerid); 
    eUser[playerid][e_USER_NAME] = RemoveClanTagFromName(playerid);

    foreach(new i:Player)
    {
        if (i != playerid)
        {
          
            if (strequal(eUser[i][e_USER_NAME], eUser[playerid][e_USER_NAME]))
            {
                SendErrorMessage(playerid, "Some nickname is already used");
                return DelayedKick(playerid, 200);
            }
        }
    }

    SetTimerEx("LoadPlayerAccount", 500, false, "d", playerid);
    return true;
}

public OnPlayerDisconnect(playerid)
{
    if (!eUser[playerid][e_USER_LOGGED])
    {
        return false;
    }

    SavePlayerAccount(playerid);
    return true;
}

public OnPlayerRequestClass(playerid, classid)
{
    if(IsPlayerNPC(playerid))
    {
        SetPlayerSkin(playerid, random(200));
        return false;
    }

	if (eUser[playerid][e_USER_SKIN] != 0 && !AlreadySetedClassSkin[playerid])
    {
		SetPlayerSkin(playerid, eUser[playerid][e_USER_SKIN]);
        AlreadySetedClassSkin[playerid] = true;
    }

    return true;
}

public OnPlayerRequestSpawn(playerid)
{
    if(!AlreadySpawned[playerid])
    {
        eUser[playerid][e_USER_SKIN] = GetPlayerSkin(playerid);
        SetSpawnInfo(playerid, 0, eUser[playerid][e_USER_SKIN], 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
        ShowLocationsDialog(playerid);
        return false;
    }

    return true;
}

public OnPlayerSpawn(playerid)
{
    if (!eUser[playerid][e_USER_LOGGED] && !IsPlayerNPC(playerid))
        DelayedKick(playerid, 200);

    SetPlayerInterior(playerid, 0);
    SetPlayerWorldBounds(playerid, 20000.0, -20000.0, 20000.0, -20000.0);
    SetPlayerSkin(playerid, eUser[playerid][e_USER_SKIN]);
    SetPlayerClanColor(playerid);
    SetPlayerScore(playerid, eUser[playerid][e_USER_KILLS]);

    if (IsPlayerInAnyVehicle(playerid))
    {
        RemovePlayerFromVehicle(playerid);
    }

    if (GetPVarInt(playerid, "last_vehicle") != -1)
    {
        DestroyVehicle(GetPVarInt(playerid, "last_vehicle"));
        SetPVarInt(playerid, "last_vehicle", -1);
    }

    StopFly(playerid);

    if (!AlreadySpawned[playerid])
    {
        ShowTextdraws(playerid);
        GameTextForPlayer(playerid, "~y~welcome_~r~%s", 5000, 1, eUser[playerid][e_USER_NAME]);

        if (IsPlayerInClan(playerid))
        {
            SetPlayerNameWithTag(playerid);
        }
        
        if (!eUser[playerid][e_USER_WEAPONS][0] && !eUser[playerid][e_USER_WEAPONS][1] &&
        !eUser[playerid][e_USER_WEAPONS][2] && !eUser[playerid][e_USER_WEAPONS][3])
        {
            // eUser[playerid][e_USER_WEAPONS][0] = WEAPON_DEAGLE;
            // eUser[playerid][e_USER_WEAPONS][1] = WEAPON_SHOTGUN;

            Dialog_Show(playerid, 0, DIALOG_STYLE_MSGBOX, 
            "Weapon configuration", 
            "Your account does not have a weapon configuration set up.\n\
            You can customize it using the /gunmenu command", 
            "Next", "");
        }

        AlreadySpawned[playerid] = true;
    }

    if(IsPlayerInDuel(playerid))
    {
        OnDuelSpawn(GetPlayerDuelID(playerid));
        return true;
    }

    SetPlayerHealth(playerid, 100);
    SetPlayerArmour(playerid, 100);

    if (!eUser[playerid][e_USER_IN_LOUNGE] && !eUser[playerid][e_USER_IN_TRAINING])
        SpawnOnLocation(playerid);
    else if (eUser[playerid][e_USER_IN_LOUNGE])
    {
        SetPlayerToLounge(playerid);
    }
    else if (eUser[playerid][e_USER_IN_TRAINING])
    {
        SetPlayerToTraining(playerid);
    }

    return true;
}

public OnPlayerText(playerid, text[])
{
    if (!eUser[playerid][e_USER_LOGGED] || !AlreadySpawned[playerid]){
        return false;
    }

    if (eUser[playerid][e_USER_MUTE_TIME] > gettime()){
        return !SendClientMessage(playerid, COLOR_GRAY, "You're in trouble! %d seconds left", eUser[playerid][e_USER_MUTE_TIME]-gettime());
    }

    new 
        LocationID = GetPlayerLocationID(playerid)
    ;

    if (text[0] == ' ' || text[0] == '0')
    {
        SendClientMessageToAll(COLOR_ICE, "[0.GL] %s: %s", ReturnPlayerName(playerid), text[1]);
        return false;
    }

    if (text[0] == '!' && IsPlayerInClan(playerid))
    {
        callcmd::cchat(playerid, text[1]);
        return false;
    }

    if (eUser[playerid][e_USER_IN_LOUNGE])
    {
        foreach(new i:Player)
        {
            if (eUser[i][e_USER_IN_LOUNGE]){
                SendClientMessage(i, COLOR_ICE, "[LNG] %s: %s", ReturnPlayerName(playerid), text);
            }
        }

        return false;
    }
    
    if (eUser[playerid][e_USER_IN_TRAINING])
    {
        foreach(new i:Player)
        {
            if (eUser[i][e_USER_IN_TRAINING]){
                SendClientMessage(i, COLOR_ICE, "[TRN] %s: %s", ReturnPlayerName(playerid), text);
            }
        }

        return false;
    }
    
    SendLocationMessage(LocationID, COLOR_ICE, "[%d.LC] %s: %s", LocationID + 1, ReturnPlayerName(playerid), text);
    return false;
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if (newkeys & KEY_YES)
    {
        if (!IsPlayerInDuel(playerid))
        {
            callcmd::menu(playerid);
        }
    }

    if (newkeys == 160 && !IsBulletWeapon(GetPlayerWeapon(playerid)) && !IsPlayerInAnyVehicle(playerid))
    {
        SyncPlayer(playerid);
	}

    if(newkeys == KEY_FIRE && GetPVarInt(playerid, "ShowingScoreboard") == 1 
    && GetPlayerLocationID(playerid) != -1)
    {
        HideLocationScoreboard(playerid, GetPlayerLocationID(playerid));
    }

    if(newkeys == KEY_CTRL_BACK)
    {
        if (!IsPlayerInDuel(playerid))
        {
            callcmd::respawn(playerid);
        }
    }

    return true;
}

public OnPlayerDeath(playerid, killerid, reason)
{
    if(playerid == INVALID_PLAYER_ID && killerid == INVALID_PLAYER_ID)
    {
        return false;
    }

	SetPlayerChatBubble(playerid, "{d18080}Killer: {FFFFFF}%s", -1, 30.0, 6000, eUser[killerid][e_USER_NAME]);

    new 
        LocationID = GetPlayerLocationID(killerid)
    ;

    if (!IsPlayerInDuel(killerid))
    {
        new respects = random(10);

        eUser[killerid][e_USER_KILLS] ++;
        eUser[killerid][e_USER_DAY_KILLS] ++;
        eUser[killerid][e_USER_RESPECTS] += respects;
        eUser[playerid][e_USER_DEATHS] ++;

        SetPlayerHealth(killerid, 100);
        SetPlayerArmour(killerid, 100);
        SetPlayerScore(killerid, eUser[killerid][e_USER_KILLS]);

        SetPlayerMoney(killerid, 500, true);
        SetPlayerMoney(playerid, -50, false);

        new 
            givenExp = random(4) + 1
        ;

        if (LevelBonusTick[killerid] > GetTickCount()){
            givenExp = (givenExp * 2);
        }

        PlayerTextDrawSetString(killerid, PLAYER_GIVEN_EXP_TD[killerid], sprintf("~y~~h~+%d_~w~exp", givenExp));
        PlayerTextDrawShow(killerid, PLAYER_GIVEN_EXP_TD[killerid]);
        
        KillTimer(eTimer[e_EXP_TIMER][killerid]);
        eTimer[e_EXP_TIMER][killerid] = SetTimerEx("HideExpTextdraw", 2000 , false, "d", killerid);

        eUser[killerid][e_USER_EXP] += givenExp;

        if (eUser[killerid][e_USER_EXP] >= PlayerExpGoal(killerid))
        {
            eUser[killerid][e_USER_EXP] = eUser[killerid][e_USER_EXP] - PlayerExpGoal(killerid);
            eUser[killerid][e_USER_LEVEL] ++;

            LevelBonusTick[killerid] = GetTickCount() + 45000;
            LevelBonusEnabled[killerid] = true;
            SendInfoMessage(killerid, COLOR_LOAFER, "Congratulations you have moved to level %d! A 45-second bonus has been activated", eUser[killerid][e_USER_LEVEL]);
         
            GameTextForPlayer(killerid, "~y~LVL_UP", 3000, 1);
        }

        if (LocationID != -1)
        {
            SendDeathMessage(killerid, playerid, reason);
            DropPlayerSniper(playerid);

            eUserLocation[killerid][LocationID][e_USER_LOCATION_KILLS] ++;
            eUserLocation[killerid][LocationID][e_USER_LOCATION_STREAK] ++;
            eUserLocation[playerid][LocationID][e_USER_LOCATION_DEATHS] ++;
            
            ShowStreakTextdraw(killerid);
            
            if (eUserLocation[playerid][LocationID][e_USER_LOCATION_STREAK] > eUser[playerid][e_USER_TOP_STREAK])
            {
                eUser[playerid][e_USER_TOP_STREAK] = eUserLocation[playerid][LocationID][e_USER_LOCATION_STREAK];
                SendInfoMessage(playerid, COLOR_GOLD, "You have broken your kill-streak record, Your new record: %d", eUser[playerid][e_USER_TOP_STREAK]);
            }
            
            if (eUserLocation[playerid][LocationID][e_USER_LOCATION_STREAK] >= 5)
            {
                SendLocationInfoMessage(LocationID, COLOR_GOLD, "%s hit a kill-streak of %d kills.", eUser[playerid][e_USER_NAME], eUserLocation[playerid][LocationID][e_USER_LOCATION_STREAK]);
            }

            eUserLocation[playerid][LocationID][e_USER_LOCATION_STREAK] = 0;

            if (IsPlayerInClan(killerid) && GetPlayerClanID(killerid) != GetPlayerClanID(playerid))
            {
                new 
                    clan_id = GetPlayerClanID(killerid)
                ;

                eUser[killerid][e_USER_CLAN_RESPECTS] += respects;
                eClan[clan_id][e_CLAN_RESPECTS] += respects;
                eClan[clan_id][e_CLAN_LOCATION_RESPECTS][LocationID] += respects;
                eClan[clan_id][e_CLAN_KILLS] ++;
            }
        }
    }
    else
    {
        SetPVarInt(killerid, "duel_kills", GetPVarInt(killerid, "duel_kills") + 1);

        eDuel[GetPlayerDuelID(killerid)][e_DUEL_ROUNDS] --;

        if(eDuel[GetPlayerDuelID(killerid)][e_DUEL_ROUNDS] == 0)
        {
            EndDuel(GetPlayerDuelID(killerid));
        }
    }

    return true;
}

public: HideExpTextdraw(playerid)
{
    PlayerTextDrawHide(playerid, PLAYER_GIVEN_EXP_TD[playerid]);
    return true;
}

public OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ)
{
    new 
        LocationID = GetPlayerLocationID(playerid)
    ;

    if (LocationID != -1 && !eUser[playerid][e_USER_IN_LOUNGE] && !eUser[playerid][e_USER_IN_TRAINING])
    {
        eUserLocation[playerid][LocationID][e_USER_LOCATION_SHOTS] ++;
        eUserLocation[playerid][LocationID][e_USER_LOCATION_ACCURACY] = floatround(floatmul(100.0, floatdiv(eUserLocation[playerid][LocationID][e_USER_LOCATION_HITS], eUserLocation[playerid][LocationID][e_USER_LOCATION_SHOTS])));
    }

    return true;
}

public OnPlayerDamage(&playerid, &Float:amount, &issuerid, &weapon, &bodypart)
{
    if 
    (
        issuerid == INVALID_PLAYER_ID               || 
        playerid == INVALID_PLAYER_ID               ||
        !eUser[issuerid][e_USER_LOGGED]             || 
        eUser[issuerid][e_USER_IN_LOUNGE]           ||
        eUser[issuerid][e_USER_IN_TRAINING]         ||
        weapon == WEAPON_COLLISION                  || 
        GetPVarInt(playerid, "SpawnProtected") 
    )
    {

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

	if (weapon == 27)
	    amount = 8.0;

    new 
        LocationID = GetPlayerLocationID(issuerid)
    ;
   
    if (LocationID != -1)
    {
        eUserLocation[issuerid][LocationID][e_USER_LOCATION_HITS] ++;
        
        if (!IsPlayerInDuel(issuerid))
        {
            eUserLocation[issuerid][LocationID][e_USER_LOCATION_DAMAGE] += floatround(amount);
            
            if (IsPlayerInClan(issuerid))
            {
                if (GetPlayerClanID(issuerid) == GetPlayerClanID(playerid)) 
                {
                    TextDrawShowForPlayer(issuerid, HIT_CLAN_MEMBER_TD);
                    KillTimer(eTimer[e_HIT_CLAN_MEMBER_TIMER][issuerid]);
                    eTimer[e_HIT_CLAN_MEMBER_TIMER][issuerid] = SetTimerEx("HideClanHitTextdraw", 2000, false, "d", issuerid);    
                }
            }
        }
    }
    
    return true;
}

stock ShowPlayerHitMark(showid, issuerid, Float:amount)
{
    new
        Float:Origin[3], 
        Float:HitPos[3],
        PlayerText3D:DamageLabel
    ;

	GetPlayerLastShotVectors(issuerid, Origin[0], Origin[1], Origin[2], HitPos[0], HitPos[1], HitPos[2]);
    
    if (eUser[showid][e_USER_DAMAGE_STYLE] == 0)
        DamageLabel = CreatePlayer3DTextLabel(showid, "%d", SetAlpha(0xFFFFFFFF, 185), HitPos[0], HitPos[1], HitPos[2], 80.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, false, floatround(amount));
    else
        DamageLabel = CreatePlayer3DTextLabel(showid, "•", SetAlpha(0xFFFFFFFF, 185), HitPos[0], HitPos[1], HitPos[2], 80.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, false);
    
    SetTimerEx("DestroyDamageLabel", 2000, false, "dd", showid, _:DamageLabel);

    foreach(new i:Player)
    {
        if (eSpectate[i][e_SPECTATE_ID] == issuerid)
        {
            ShowPlayerHitMark(i, issuerid, amount);
        }
    }
}

public OnPlayerDamageDone(playerid, Float:amount, issuerid, WEAPON:weapon, bodypart)
{
    ShowPlayerHitMark(issuerid, issuerid, amount);

    if (eUser[issuerid][e_USER_HITSOUND])
        PlayerPlaySound(issuerid, 17802, 0, 0, 0);

    return true;
}

public OnPlayerGiveDamageDynamicActor(playerid, STREAMER_TAG_ACTOR:actorid, Float:amount, weaponid, bodypart)
{
    if (weaponid == WEAPON_DEAGLE)
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

	if (weaponid == 27)
    {
	    amount = 8.0;
    }

    ShowPlayerHitMark(playerid, playerid, amount);

    if (eUser[playerid][e_USER_HITSOUND])
    {
        PlayerPlaySound(playerid, 17802, 0, 0, 0);   
    }
    
    new Float:x, Float:y, Float:z;
    ClearDynamicActorAnimations(actorid);
    GetDynamicActorPos(actorid, x, y, z);
    SetDynamicActorPos(actorid, x, y ,z);
    return true;
}

public: HideClanHitTextdraw(playerid)
{
    TextDrawHideForPlayer(playerid, HIT_CLAN_MEMBER_TD);
    return true;
}

public: DestroyDamageLabel(issuerid, PlayerText3D:DamageLabel)
{
	DeletePlayer3DTextLabel(issuerid, DamageLabel);
	return true;
}

public OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ)
{
    if (!eUser[playerid][e_USER_IN_LOUNGE])
    {
        return false;
    }

    SetPlayerPosFindZ(playerid, fX, fY, fZ);
    return true;
}

public OnPlayerClickPlayer(playerid, clickedplayerid, source)
{
    if (AlreadySpawned[playerid] && AlreadySpawned[clickedplayerid])
    {
        GetPlayerStats(playerid, clickedplayerid);
    }

    return true;
}
