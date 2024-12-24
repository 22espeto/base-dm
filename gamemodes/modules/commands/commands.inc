public OnPlayerCommandPerformed(playerid, cmd[], params[], result, flags)
{
    if (!playerInfo[playerid][e_PlayerLogged]){
        return false;
    }

    if (result == -1){
        return SendClientMessage(playerid, 0xbd9099ff, "(error) \"/%s\" is an invalid command, see /commands", cmd);
    }

    return true;
}

public OnPlayerCommandReceived(playerid, cmd[], params[], flags)
{
    if (GetPVarInt(playerid, "commandTick") > GetTickCount()){
        return !SendClientMessage(playerid, 0xbd9099ff, "(error) Wait to send a command again");
    }
    
    SetPVarInt(playerid, "commandTick", GetTickCount() + 1000); 

    // altere "IsPlayerAdmin" para sua variavel de admin caso voce faca um sistema de admin.
    // abaixo é so uma demonstracao de uso.

    if (flags & FLAG_ADMIN && !IsPlayerAdmin(playerid)){
        return !SendClientMessage(playerid, 0xbd9099ff, "(error) Access denied."); // o "!" da na mesma se voce enviar a mensagem e dps retornar a false
    }
 
    return true;
}