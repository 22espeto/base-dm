#include <YSI_Coding/y_hooks>

hook OnGameModeInit()
{
    Iter_Init(Arenas);
    Iter_Init(ArenaPlayers);

    CreateArenaZones();
    InitArena();
    return true;
}

hook OnPlayerConnect(playerid)
{
    foreach(new i:Arenas){
        ShowZoneForPlayer(playerid, i, SetAlpha(0xFFFFFFFF, 120), 0xFFFFFFFF);
    }

    return true;
}

hook OnPlayerDisconnect(playerid, reason)
{
    if (Iter_Contains(ArenaPlayers, playerid)){
        Iter_Remove(ArenaPlayers, playerid);
    }

    return true;
}

task ArenaSecondTimer[1000]() 
{
    if (arenaInfo[e_ArenaRunning])
    {
        if (arenaInfo[e_ArenaSeconds] == 0 && arenaInfo[e_ArenaMinutes] > 0)
        {
            arenaInfo[e_ArenaMinutes] --;
            arenaInfo[e_ArenaSeconds] = 60;
        }

        if (arenaInfo[e_ArenaSeconds] > 0){
            arenaInfo[e_ArenaSeconds] --;
        }
        
        if (arenaInfo[e_ArenaMinutes] == 0 && arenaInfo[e_ArenaSeconds] == 0){
            FinishArena(Iter_Random(Arenas));
        }
    }

    TextDrawSetString(TD_ArenaStats[0], "%d:%02d", arenaInfo[e_ArenaMinutes], arenaInfo[e_ArenaSeconds]);
    TextDrawSetString(TD_ArenaStats[1], "~w~Arena: ~Y~%s ~w~(ID: ~y~%d~w~)", ArenaNames[arenaInfo[e_ArenaId]], arenaInfo[e_ArenaId]);
}
