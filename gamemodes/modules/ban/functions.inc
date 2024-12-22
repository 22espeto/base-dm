
stock BanPlayer(playerid, banTs, unbanTs, const admin[], const reason[])
{
    new str[350];

    mysql_format(dbHandle, str, sizeof str, 
        "INSERT INTO banneds (name, admin, banTimestamp, unbanTimestamp, reason, ip) VALUES \
        ('%e', '%e', %d, %d, '%e', %e')", 
    playerInfo[playerid][e_PlayerName], admin, banTs, unbanTs, reason, playerInfo[playerid][e_PlayerLastIp]);

    mysql_tquery(dbHandle, str);

    DelayedKick(playerid);
}