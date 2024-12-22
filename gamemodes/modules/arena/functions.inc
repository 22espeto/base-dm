
stock DetermineArenaTime()
{
    return Iter_Count(ArenaPlayers) <= 5 ? 4 : 8;
}

stock InitArena()
{
    arenaInfo[e_ArenaId] = Iter_Random(Arenas);
    arenaInfo[e_ArenaMinutes] = DetermineArenaTime();
    arenaInfo[e_ArenaSeconds] = 30;
    arenaInfo[e_ArenaRunning] = true;
}

stock CreateArenaZones()
{
    new Float:zoneCoord[MAX_ARENAS][4];

    for (new i; i < MAX_ARENAS; i ++) 
    {
        zoneCoord[i][0] = zoneCoord[i][1] = 999999.0;
        zoneCoord[i][2] = zoneCoord[i][3] = -999999.0;

        for (new j; j < sizeof ArenaSpawns[]; j ++) 
        {
            zoneCoord[i][0] = minf(zoneCoord[i][0], ArenaSpawns[i][j][0]);
            zoneCoord[i][1] = minf(zoneCoord[i][1], ArenaSpawns[i][j][1]);

            zoneCoord[i][2] = maxf(zoneCoord[i][2], ArenaSpawns[i][j][0]);
            zoneCoord[i][3] = maxf(zoneCoord[i][3], ArenaSpawns[i][j][1]);
        }

        CreateZone(zoneCoord[i][0], zoneCoord[i][1], zoneCoord[i][2], zoneCoord[i][3]);
        CreateZoneNumber(i, i, 1.0);

        Iter_Add(Arenas, i);
    }
}

stock GivePlayerWeapons(playerid)
{
    ResetPlayerWeapons(playerid);

    GivePlayerWeapon(playerid, WEAPON_SHOTGUN, 700);
    GivePlayerWeapon(playerid, WEAPON_DEAGLE, 700);
}

stock SpawnPlayerOnArena(playerid)
{
    if (!Iter_Contains(ArenaPlayers, playerid)){
        Iter_Add(ArenaPlayers, playerid);
    }

    new spawnIdx = random(sizeof(ArenaSpawns[])), arenaId = arenaInfo[e_ArenaId];

    SetPlayerPos(playerid, ArenaSpawns[arenaId][spawnIdx][0], ArenaSpawns[arenaId][spawnIdx][1], ArenaSpawns[arenaId][spawnIdx][2]);
    SetPlayerFacingAngle(playerid, ArenaSpawns[arenaId][spawnIdx][3]);
    SetCameraBehindPlayer(playerid);
    SetPlayerVirtualWorld(playerid, ARENA_VW);

    SetPlayerHealth(playerid, 100);
    SetPlayerArmour(playerid, 100);

    GivePlayerWeapons(playerid);
}

stock ShowArenaScoreboard(playerid)
{
    for (new i; i < sizeof TD_ArenaScoreboard; i ++){
        TextDrawShowForPlayer(playerid, TD_ArenaScoreboard[i]);
    }
}

stock HideArenaScoreboard(playerid)
{
    for (new i; i < sizeof TD_ArenaScoreboard; i ++){
        TextDrawHideForPlayer(playerid, TD_ArenaScoreboard[i]);
    }
}

stock FinishArena()
{
    arenaInfo[e_ArenaRunning] = false;
    arenaInfo[e_ArenaMinutes] = 0;
    arenaInfo[e_ArenaSeconds] = 0;

    ZoneNumberStopFlashForAll(arenaInfo[e_ArenaId]);

    SendClientMessageToAll(COLOR_GRAY, "(info) Arena %s #%d is over. The next one will start soon.", ArenaNames[arenaInfo[e_ArenaId]], arenaInfo[e_ArenaId]);

    new g_PlayerArray<TopPlayers>;

	sortPlayersInline TopPlayers => (R = l > r)
	{
		new lc = IsPlayerConnected(l) && !IsPlayerNPC(l);
		new rc = IsPlayerConnected(r) && !IsPlayerNPC(r);
		
		if (lc != rc)
			R = lc > rc;
		else
			R = playerArenaInfo[l][e_ArenaDamage] > playerArenaInfo[r][e_ArenaDamage];
	}

    new str[4][50 * 5];
    for (new i; i < 5; i ++)
	{
		if (IsPlayerConnected(TopPlayers[i]) && playerArenaInfo[TopPlayers[i]][e_ArenaDamage] > 0)
		{
			new topId = TopPlayers[i];
            
            format(str[0], sizeof str[], "%s%s~n~~n~", str[0], playerInfo[topId][e_PlayerName]);
            format(str[1], sizeof str[], "%s%d~n~~n~", str[1], playerArenaInfo[topId][e_ArenaDamage]);
            format(str[2], sizeof str[], "%s%d~n~~n~", str[2], playerArenaInfo[topId][e_ArenaKills]);
            format(str[3], sizeof str[], "%s%.2f~n~~n~", str[3], floatdiv(playerArenaInfo[topId][e_ArenaKills], playerArenaInfo[topId][e_ArenaDeaths]));
		}
	}

	TextDrawSetString(TD_ArenaScoreboard[17], str[0]);
	TextDrawSetString(TD_ArenaScoreboard[18], str[1]);
	TextDrawSetString(TD_ArenaScoreboard[19], str[2]);
	TextDrawSetString(TD_ArenaScoreboard[20], str[3]);

    foreach(new i:ArenaPlayers)
    {
        TogglePlayerControllable(i, false);
        ShowArenaScoreboard(i);
    }

    KillTimer(arenaInfo[e_ArenaTimer]);
    arenaInfo[e_ArenaTimer] = SetTimer("LaunchArena", 8500, false);
}

forward LaunchArena();
public LaunchArena()
{
    arenaInfo[e_ArenaId] = Iter_Random(Arenas);
    arenaInfo[e_ArenaMinutes] = DetermineArenaTime();
    arenaInfo[e_ArenaSeconds] = 30;
    arenaInfo[e_ArenaRunning] = true;

    ZoneNumberFlashForAll(arenaInfo[e_ArenaId], 0xDB0000FF);

    foreach(new i:Player)
    {
        playerArenaInfo[i][e_ArenaKills] = 0;
        playerArenaInfo[i][e_ArenaDeaths] = 0;
        playerArenaInfo[i][e_ArenaDamage] = 0;

        HideArenaScoreboard(i);

        if (Iter_Contains(ArenaPlayers, i))
        {
            SpawnPlayer(i);
            SendClientMessage(i, COLOR_GRAY, "(info) Arena %s #%d has started", ArenaNames[arenaInfo[e_ArenaId]], arenaInfo[e_ArenaId]);
        }
    }
}
