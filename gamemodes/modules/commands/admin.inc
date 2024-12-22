
CMD:ban(playerid, params[])
{
    new targetid, banDays, banReason[40];
    if (sscanf(params, "uds[40]", targetid, banDays, banReason)){
        return SendClientMessage(playerid, -1, "Usage: /ban [Player] [Days] [Reason (40 Chars)]");
    }

    if (!(0 <= targetid <= MAX_PLAYERS)){
        return SendClientMessage(playerid, -1, "(error) Invalid player id");
    }

    if (!IsPlayerConnected(targetid) || !GetPVarInt(targetid, "alreadySpawned")){
        return SendClientMessage(playerid, -1, "(error) Player not found");
    }

    if (targetid == playerid){
        return SendClientMessage(playerid, -1, "(error) You cannot use in yourself");
    }

    new ts = gettime(), unbanTs = ts + (banDays * 24 * 60 * 60);

    SendClientMessageToAll(0xb58a93ff, "** %s banned player %s[%d] until %s (%d days)", playerInfo[playerid][e_PlayerName], playerInfo[targetid][e_PlayerName], targetid, ReturnDate(unbanTs, 6), banDays);
    BanPlayer(targetid, ts, unbanTs, playerInfo[playerid][e_PlayerName], banReason);
    return true;
}