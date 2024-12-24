#include <YSI_Coding/y_hooks>

stock LoadPlayerAccount(playerid)
{
    for (new i; i < 20; i ++){
        SendClientMessage(playerid, -1, "");
    }

    AuthScreen(playerid);

    inline const CheckPlayerBan()
    {
        new rows = cache_num_rows();
        if (rows)
        {
            new banTs, unbanTs, accountName[MAX_PLAYER_NAME + 1], adminName[MAX_PLAYER_NAME + 1], banReason[40];

            cache_get_value_int(0, "banTimestamp", banTs);
            cache_get_value_int(0, "unbanTimestamp", unbanTs);
            cache_get_value_name(0, "name", accountName);
            cache_get_value_name(0, "admin", adminName);
            cache_get_value_name(0, "reason", banReason);

            SendClientMessage(playerid, 0xA9C4E4FF, "Your account and/or IP address is banned. You cannot log in.");
            SendClientMessage(playerid, 0xA9C4E4FF, "Account: %s | Admin: %s | Reason: %s", accountName, adminName, banReason);
            SendClientMessage(playerid, 0xA9C4E4FF, "Ban Duration: From %s to %s | Time Remaining: %s", ReturnDate(banTs, 6), ReturnDate(unbanTs, 6), FormatTimeleft(gettime(), unbanTs));
            SendClientMessage(playerid, 0xA9C4E4FF, "If you believe this ban is a mistake, please contact the administration at: %s", DISCORD_LINK);
            SendClientMessage(playerid, 0xA9C4E4FF, "");

            DelayedKick(playerid);
        }
        else
        {
            inline const CheckPlayerAccount()
            {
                rows = cache_num_rows();
                if (rows)
                {
                    cache_get_value_int(0, "id", playerInfo[playerid][e_PlayerId]);
                    cache_get_value_name(0, "password", playerInfo[playerid][e_PlayerPassword]);
                    cache_get_value_name(0, "salt", playerInfo[playerid][e_PlayerSalt]);
                    cache_get_value_name(0, "regIp", playerInfo[playerid][e_PlayerRegIp]);
                    cache_get_value_name(0, "lastIp", playerInfo[playerid][e_PlayerLastIp]);
                    cache_get_value_int(0, "kills", playerInfo[playerid][e_PlayerKills]);
                    cache_get_value_int(0, "deaths", playerInfo[playerid][e_PlayerDeaths]);
                    cache_get_value_int(0, "skin", playerInfo[playerid][e_PlayerSkin]);
                    cache_get_value_int(0, "weather", playerInfo[playerid][e_PlayerWeather]);
                    cache_get_value_int(0, "time", playerInfo[playerid][e_PlayerTime]);
                    
                    new weaponsStr[100];
                    cache_get_value_name(0, "weapons", weaponsStr);
                    sscanf(weaponsStr, "p<,>a<i>["#MAX_GUNMENU_SLOTS"]", playerInfo[playerid][e_PlayerWeapons]);

                    SetPlayerWeather(playerid, playerInfo[playerid][e_PlayerWeather]);
                    SetPlayerTime(playerid, playerInfo[playerid][e_PlayerTime], 0);

                    ShowAuthorizationDialog(playerid);
                }
                else
                    ShowRegistrationDialog(playerid);
            }
            MySQL_TQueryInline(dbHandle, using inline CheckPlayerAccount, 
                "SELECT * FROM players WHERE name = '%e'", playerInfo[playerid][e_PlayerName]);
        }
    }
    MySQL_TQueryInline(dbHandle, using inline CheckPlayerBan, 
        "SELECT * FROM banneds WHERE name = '%e' OR ip = '%e'", 
    playerInfo[playerid][e_PlayerName], playerInfo[playerid][e_PlayerLastIp]);
}

stock SavePlayerAccount(playerid)
{
    new str[1000], weaponsStr[100];

    for (new i; i < MAX_GUNMENU_SLOTS; i ++){
        format(weaponsStr, sizeof weaponsStr, "%s%s%d", weaponsStr, i ? "," : "", playerInfo[playerid][e_PlayerWeapons][i]);
    }

    mysql_format(dbHandle, str, sizeof str, 
    "UPDATE players SET \
        lastIp = '%e', \
        kills = %d, \
        deaths = %d, \
        skin = %d, \
        weather = %d, \
        time = %d, \
        weapons = '%e' \
        WHERE name = '%e'",
    playerInfo[playerid][e_PlayerLastIp],
    playerInfo[playerid][e_PlayerKills],
    playerInfo[playerid][e_PlayerDeaths],
    playerInfo[playerid][e_PlayerSkin],
    playerInfo[playerid][e_PlayerWeather],
    playerInfo[playerid][e_PlayerTime],
    weaponsStr,
    playerInfo[playerid][e_PlayerName]);

    mysql_tquery(dbHandle, str);

}

stock ShowAuthorizationDialog(playerid)
{
    return Dialog_Show(playerid, DIALOG_LOGIN, DIALOG_STYLE_PASSWORD, "Authorization", "This account is in the database. Enter the password correctly to log in.", "Enter", "Leave");
}

stock ShowRegistrationDialog(playerid)
{
    new str[65];

    format(str, sizeof str, "Enter a password between %d and %d to register on the server.", MIN_PASSWORD_LENGTH, MAX_PASSWORD_LENGTH);
    return Dialog_Show(playerid, DIALOG_REGISTRATION, DIALOG_STYLE_PASSWORD, "Registration", str, "Enter", "Leave");
}

stock AuthScreen(playerid)
{
    SetPlayerVirtualWorld(playerid, playerid);
    SetPlayerPos(playerid, 411.1662, 2534.0742, 19.1484);
    SetPlayerFacingAngle(playerid, 0.1074);
    SetPlayerCameraPos(playerid, 411.098144, 2538.930664, 20.827701);
    SetPlayerCameraLookAt(playerid, 410.990295, 2534.153808, 19.354814);
}

stock AuthorizePlayer(playerid)
{
    playerInfo[playerid][e_PlayerLogged] = true;

    SendClientMessage(playerid, 0x6f8cffff, "(auth) You have successfully authed as %s!", playerInfo[playerid][e_PlayerName]);
    SendClientMessageToAll(COLOR_GRAY, "%s has joined the server", playerInfo[playerid][e_PlayerName]);
}

Dialog:DIALOG_REGISTRATION(playerid, response, listitem, inputtext[])
{
    if (response)
    {
        if (IsNull(inputtext) || !IsValidString(inputtext) || !(MIN_PASSWORD_LENGTH <= strlen(inputtext) <= MAX_PASSWORD_LENGTH))
            return ShowRegistrationDialog(playerid);

        new passwordSalt[PASSWORD_SALT_LENGTH + 1];
        for (new i; i < PASSWORD_SALT_LENGTH; i ++){
            passwordSalt[i] = random(55) + (22);
        }
        passwordSalt[10] = 0;

        SHA256_PassHash(inputtext, passwordSalt, playerInfo[playerid][e_PlayerPassword]);
        format(playerInfo[playerid][e_PlayerRegIp], 16, playerInfo[playerid][e_PlayerLastIp]);

        inline const OnRegistrationAccount()
        {
            playerInfo[playerid][e_PlayerId] = cache_insert_id();
        }
        MySQL_TQueryInline(dbHandle, using inline OnRegistrationAccount, 
            "INSERT INTO players (name, password, salt, regIp, lastIp) VALUES ('%e', '%e', '%e', '%e', '%e')", 
        playerInfo[playerid][e_PlayerName], playerInfo[playerid][e_PlayerPassword], passwordSalt,
        playerInfo[playerid][e_PlayerRegIp], playerInfo[playerid][e_PlayerLastIp]);

        AuthorizePlayer(playerid);
    }
    else
        DelayedKick(playerid);

    return true;
}

Dialog:DIALOG_LOGIN(playerid, response, listitem, inputtext[])
{
    if (response)
    {
        if (IsNull(inputtext)){
           return ShowAuthorizationDialog(playerid);
        }

        new passwordHashed[PASSWORD_HASH_LENGTH + 1];
        SHA256_PassHash(inputtext, playerInfo[playerid][e_PlayerSalt], passwordHashed);

        if (!strequal(passwordHashed, playerInfo[playerid][e_PlayerPassword])){
            return ShowAuthorizationDialog(playerid);
        }

        AuthorizePlayer(playerid);
    }
    else
        DelayedKick(playerid);

    return true;
}