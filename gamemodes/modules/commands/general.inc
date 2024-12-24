
alias:setskin("ss", "skin")
CMD:setskin(playerid, params[])
{
    new id;
    if (sscanf(params, "d", id)){
        return SendClientMessage(playerid, 0xbd9099ff, "(usage) /setskin [skin id]");
    }

    if (!(0 <= id <= 311)){
        return SendClientMessage(playerid, 0xbd9099ff, "(error) This skin ID is blocked or invalid!");
    }

    for (new i; i < sizeof blockedSkins; i ++)
    {
        if (id == blockedSkins[i]){
            return SendClientMessage(playerid, 0xbd9099ff, "(error) This skin ID is blocked or invalid!");
        }
    }

    if (id != playerInfo[playerid][e_PlayerSkin])
        SendClientMessage(playerid, 0xf5ff9fff, "(system) You have set your skin to: %d (previous skin: %d)", id, playerInfo[playerid][e_PlayerSkin]);
    else
        SendClientMessage(playerid, 0xf5ff9fff, "(system) You have set your skin to: %d", id);

    playerInfo[playerid][e_PlayerSkin] = id;
    SetPlayerSkin(playerid, playerInfo[playerid][e_PlayerSkin]);
    return true;
}

alias:weather("w")
CMD:weather(playerid, params[])
{
    new id;
    if (sscanf(params, "d", id)){
        return SendClientMessage(playerid, 0xbd9099ff, "(usage) /weather [0-50]");
    }

    if (!(0 <= id <= 50)){
        return SendClientMessage(playerid, 0xbd9099ff, "(usage) /weather [0-50]");
    }

    if (id != playerInfo[playerid][e_PlayerWeather])
        SendClientMessage(playerid, 0xf5ff9fff, "(system) You have set your weather to: %d (previous weather: %d)", id, playerInfo[playerid][e_PlayerWeather]);
    else
        SendClientMessage(playerid, 0xf5ff9fff, "(system) You have set your weather to: %d", id);

    playerInfo[playerid][e_PlayerWeather] = id;
    SetPlayerWeather(playerid, playerInfo[playerid][e_PlayerWeather]);
    return true;
}

alias:time("t")
CMD:time(playerid, params[])
{
    new id;
    if (sscanf(params, "d", id)){
        return SendClientMessage(playerid, 0xbd9099ff, "(usage) /time [0-23]");
    }

    if (!(0 <= id <= 23)){
        return SendClientMessage(playerid, 0xbd9099ff, "(usage) /time [0-23]");
    }

    if (id != playerInfo[playerid][e_PlayerTime])
        SendClientMessage(playerid, 0xf5ff9fff, "(system) You have set your time to: %d (previous time: %d)", id, playerInfo[playerid][e_PlayerTime]);
    else
        SendClientMessage(playerid, 0xf5ff9fff, "(system) You have set your time to: %d", id);

    playerInfo[playerid][e_PlayerTime] = id;
    SetPlayerTime(playerid, playerInfo[playerid][e_PlayerTime], 0);
    return true;
}

CMD:gunmenu(playerid)
{
    ShowGunMenu(playerid);
    return true;
}

CMD:comandos(playerid)
{
    // preguica de fazer
    return true;
}