

alias:setskin("ss", "skin")
CMD:setskin(playerid, params[])
{
    new skinid;
    if (sscanf(params, "d", skinid)){
        return SendClientMessage(playerid, -1, "Usage: /setskin [id]");
    }

    playerInfo[playerid][e_PlayerSkin] = skinid;
    SetPlayerSkin(playerid, playerInfo[playerid][e_PlayerSkin]);
    return true;
}

CMD:finish(playerid)
{
    FinishArena();
    return true;
}