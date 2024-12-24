
stock InicializePlayer(playerid)
{
	playerInfo[playerid][e_PlayerLogged] = false;
	playerInfo[playerid][e_PlayerId] = -1;
	playerInfo[playerid][e_PlayerName][0] = EOS;
	playerInfo[playerid][e_PlayerPassword][0] = EOS;
	playerInfo[playerid][e_PlayerSalt][0] = EOS;
	playerInfo[playerid][e_PlayerRegIp][0] = EOS;
	playerInfo[playerid][e_PlayerLastIp][0] = EOS;
	playerInfo[playerid][e_PlayerKills] = 0;
	playerInfo[playerid][e_PlayerDeaths] = 0;
	
	playerInfo[playerid][e_PlayerWeather] = 32;
	playerInfo[playerid][e_PlayerTime] = 7;

	SetPlayerWeather(playerid, playerInfo[playerid][e_PlayerWeather]);
	SetPlayerTime(playerid, playerInfo[playerid][e_PlayerTime], 0);

	playerInfo[playerid][e_PlayerSkin] = random(200);

	for (new i; i < MAX_GUNMENU_SLOTS; i ++){
		playerInfo[playerid][e_PlayerWeapons][i] = 0;
	}
	
    playerArenaInfo[playerid][e_ArenaKills] = 0;
    playerArenaInfo[playerid][e_ArenaDeaths] = 0;
    playerArenaInfo[playerid][e_ArenaDamage] = 0;

    killFeedStr[playerid][0] = EOS, 
    killFeedTick[playerid] = 0;
    killFeedLines[playerid] = 0;

	inClassSelection[playerid] = false;
	alreadySpawned[playerid] = false;

	SetPVarInt(playerid, "current_skinIdx", 0);
	SetPVarInt(playerid, "firstTimeGunmenu", 1);
}

stock GetPlayerFps(playerid)
{
	return GetPVarInt(playerid, "playerFps");
}

stock UpdatePlayerTextdraws(playerid)
{
	PlayerTextDrawSetString(playerid, TD_PlayerStats[playerid][0], "~w~K ~y~%d~n~~w~D ~y~%d~n~~w~Damage ~y~%d~n~~w~Ratio ~y~%.2f~n~", playerInfo[playerid][e_PlayerKills], playerInfo[playerid][e_PlayerDeaths], playerArenaInfo[playerid][e_ArenaDamage], floatdiv(playerInfo[playerid][e_PlayerKills], playerInfo[playerid][e_PlayerDeaths]));
	PlayerTextDrawSetString(playerid, TD_PlayerStats[playerid][1], "~w~FPS ~y~%d ~w~Ping ~y~%d ~w~PacketLoss ~y~%.1f%%", GetPlayerFps(playerid), GetPlayerPing(playerid), NetStats_PacketLossPercent(playerid));
}

ptask PlayerSecondTimer[1000](playerid) 
{
    SetPVarInt(playerid, !"DrunkL", GetPlayerDrunkLevel(playerid));

    if (GetPVarInt(playerid, !"DrunkL") < 100)
        SetPlayerDrunkLevel(playerid, 2000);
    else
    {
        if (GetPVarInt(playerid, !"LDrunkL") != GetPVarInt(playerid, !"DrunkL"))
        {
            SetPVarInt(playerid, !"FPS", (GetPVarInt(playerid, !"LDrunkL") - GetPVarInt(playerid,"DrunkL")));
            SetPVarInt(playerid, !"LDrunkL", GetPVarInt(playerid, !"DrunkL"));
            
            if ((GetPVarInt(playerid, !"FPS") > 0) && (GetPVarInt(playerid, !"FPS") < 256)){
                SetPVarInt(playerid, "playerFps", GetPVarInt(playerid, "FPS") - 1);
            }
        }
    }

	UpdatePlayerTextdraws(playerid);

	if (killFeedTick[playerid] != 0 && GetTickCount() >= killFeedTick[playerid])
	{
		killFeedStr[playerid][0] = EOS;
		killFeedLines[playerid] = 0;
		
		PlayerTextDrawHide(playerid, TD_PlayerStats[playerid][2]);
	}

	return true;
}

stock SetAlpha(color, alpha)
{
    return color & ~0xFF | clamp(alpha, 0, 255);
}

stock IsValidString(const str[])
{
	for(new i; str[i] != EOS; ++i)
	{
		switch(str[i])
		{
			case '0'..'9', 'A'..'Z', 'a'..'z': continue;
			default: return false;
		}
	}
	return true;
}

stock Float:minf(Float:a, Float:b)
{
    return a < b ? a : b;
}

stock Float:maxf(Float:a, Float:b)
{
    return a > b ? a : b;
}

forward OnDelayedKick(playerid);
public OnDelayedKick(playerid)
{
    return Kick(playerid);
}

stock FixRequestClass(playerid)
{
    if (inClassSelection[playerid]){
        return false;
    }

	return SetTimerEx("OnPlayerRequestClass", 350, false, "dd", playerid, 0);
}

stock KillMessages(killerid, playerid)
{
	static const killFeedMessages[][KILL_FEED_SIZE] = 
	{
		{"~w~You killed ~y~%s"},
		{"~w~You fucked ~y~%s"},
		{"~w~You smeared ~y~%s ~w~in shit"},
		{"~w~You send ~y~%s ~w~to cemetery"},
		{"~w~You murdered ~y~%s"},
		{"~w~You owned ~y~%s"},
		{"~w~You decapitated ~y~%s"},
		{"~w~You raped ~y~%s"},
		{"~w~You sent ~y~%s ~w~to heaven"},
		{"~w~You ate ~y~%s's ~w~ass"}
	};
	
	if (killFeedLines[killerid] == KILL_FEED_LINES)
	{	
		killFeedStr[killerid][0] = EOS;
		killFeedLines[killerid] = 0;
	}

	killFeedLines[killerid] ++;

	killFeedStr[playerid][0] = EOS;
	killFeedLines[playerid] = 0;

	new tmp[KILL_FEED_SIZE];
	format(tmp, sizeof tmp, killFeedMessages[random(sizeof(killFeedMessages))], playerInfo[playerid][e_PlayerName]);
	format(killFeedStr[killerid], KILL_FEED_SIZE, "%s%s~n~", killFeedStr[killerid], tmp);

	PlayerTextDrawSetString(killerid, TD_PlayerStats[killerid][2], killFeedStr[killerid]);
	PlayerTextDrawShow(killerid, TD_PlayerStats[killerid][2]);
	killFeedTick[killerid] = GetTickCount() + KILL_FEED_TIME;

	PlayerTextDrawSetString(playerid, TD_PlayerStats[playerid][2], "~y~You killed by ~w~%s", playerInfo[killerid][e_PlayerName]);
	PlayerTextDrawShow(playerid, TD_PlayerStats[playerid][2]);
	killFeedTick[playerid] = GetTickCount() + KILL_FEED_TIME / 2;
}