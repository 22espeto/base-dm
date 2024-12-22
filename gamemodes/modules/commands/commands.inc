public OnPlayerCommandPerformed(playerid, cmd[], params[], result, flags)
{
    if (!playerInfo[playerid][e_PlayerLogged]){
        return false;
    }

    if (result == -1){
        return SendClientMessage(playerid, -1, "Non-existent command.");
    }

    return true;
}

public OnPlayerCommandReceived(playerid, cmd[], params[], flags)
{
    if (GetPVarInt(playerid, "commandTick") > GetTickCount()){
        return !SendClientMessage(playerid, -1, "Wait to send a command again");
    }
    
    SetPVarInt(playerid, "commandTick", GetTickCount() + 1000); 
    return true;
}