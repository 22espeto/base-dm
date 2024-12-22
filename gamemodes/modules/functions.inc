
stock InicializePlayer(playerid)
{
	playerInfo[playerid][e_PlayerId] = -1;
	playerInfo[playerid][e_PlayerName][0] = EOS;
	playerInfo[playerid][e_PlayerPassword][0] = EOS;
	playerInfo[playerid][e_PlayerRegIp][0] = EOS;
	playerInfo[playerid][e_PlayerLastIp][0] = EOS;
	playerInfo[playerid][e_PlayerKills] = 0;
	playerInfo[playerid][e_PlayerDeaths] = 0;
	playerInfo[playerid][e_PlayerSkin] = random(200);
	playerInfo[playerid][e_PlayerLogged] = false;

    playerArenaInfo[playerid][e_ArenaKills] = 0;
    playerArenaInfo[playerid][e_ArenaDeaths] = 0;
    playerArenaInfo[playerid][e_ArenaDamage] = 0;

	inClassSelection[playerid] = false;

	SetPVarInt(playerid, "current_skinIdx", 0);
	alreadySpawned[playerid] = false;
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

forward ForceRequestClass(playerid);
public ForceRequestClass(playerid)
{
    if (inClassSelection[playerid]){
        return false;
    }

	return SetTimerEx("OnPlayerRequestClass", 250, false, "dd", playerid, 0);
}