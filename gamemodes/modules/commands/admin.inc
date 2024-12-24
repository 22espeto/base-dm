
flags:ban(FLAG_ADMIN)
alias:ban("banir")
CMD:ban(playerid, params[])
{
    new targetid, banDays, banReason[40];
    if (sscanf(params, "uds[40]", targetid, banDays, banReason)){
        return SendClientMessage(playerid, 0xbd9099ff, "(usage) /ban [Player] [Days] [Reason (40 Chars)]");
    }

    if (!(0 <= targetid <= MAX_PLAYERS)){
        return SendClientMessage(playerid, 0xbd9099ff, "(error) Invalid player");
    }

    if (!IsPlayerConnected(targetid) || !GetPVarInt(targetid, "alreadySpawned")){
        return SendClientMessage(playerid, 0xbd9099ff, "(error) Player not found");
    }

    if (targetid == playerid){
        return SendClientMessage(playerid, 0xbd9099ff, "(error) You cannot use in yourself");
    }

    new ts = gettime(), unbanTs = ts + (banDays * 24 * 60 * 60);

    SendClientMessageToAll(0xA9C4E4FF, " -> %s has banned player %s[%d] until %s (%d days)", playerInfo[playerid][e_PlayerName], playerInfo[targetid][e_PlayerName], targetid, ReturnDate(unbanTs, 6), banDays);
    BanPlayer(targetid, ts, unbanTs, playerInfo[playerid][e_PlayerName], banReason);
    return true;
}

flags:unban(FLAG_ADMIN)
alias:unban("desban", "desbanir")
CMD:unban(playerid, params[])
{
    new account[MAX_PLAYER_NAME + 1];
    if (sscanf(params, "s[24]", account)){
        return SendClientMessage(playerid, 0xbd9099ff, "(usage) /unban [Account]");
    }

    inline const SearchAccount()
    {
        new rows = cache_num_rows();
        if (!rows){
            return SendClientMessage(playerid, 0xbd9099ff, "(error) The account you entered does not exist or may have been entered incorrectly.");
        }

        inline const SearchBan()
        {           
            rows = cache_num_rows();
            if (!rows){
                return SendClientMessage(playerid, 0xbd9099ff, "(error) The account you entered is not banned or may have been entered incorrectly.");
            }

            new str[100];
            mysql_format(dbHandle, str, sizeof str, "DELETE FROM banneds WHRE name = '%e'", account);
            mysql_tquery(dbHandle, str);

            SendClientMessage(playerid, 0xA9C4E4FF, "You have successfully removed the ban from the %s account.", account);
        }
        MySQL_TQueryInline(dbHandle, using inline SearchBan, "SELECT * FROM banneds WHERE name = '%e'", account);
    }
    MySQL_TQueryInline(dbHandle, using inline SearchAccount, "SELECT * FROM players WHERE name = '%e'", account); 
    return true;
}

flags:changearena(FLAG_ADMIN)
CMD:changearena(playerid, params[])
{
    new arenaid;
    if (sscanf(params, "d", arenaid)){
        return SendClientMessage(playerid, 0xbd9099ff, "(usage) /changearena [0-%d]", Iter_Count(Arenas) - 1);
    }

    if (!(0 <= arenaid <= Iter_Count(Arenas) - 1)){
        return SendClientMessage(playerid, 0xbd9099ff, "(usage) /changearena [0-%d]", Iter_Count(Arenas) - 1);
    }

    SendClientMessageToAll(0xA9C4E4FF, " -> %s has changed the arena.", playerInfo[playerid][e_PlayerName]);
    FinishArena(arenaid);
    return true;
}