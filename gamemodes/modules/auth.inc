#include <YSI_Coding/y_hooks>

stock LoadPlayerAccount(playerid)
{
    for (new i; i < 20; i ++){
        SendClientMessage(playerid, -1, "");
    }

    inline const CheckPlayerAccount()
    {
        new rows = cache_num_rows();
        if (rows)
        {
            cache_get_value_int(0, "id", playerInfo[playerid][e_PlayerId]);
            cache_get_value_name(0, "password", playerInfo[playerid][e_PlayerPassword]);
            cache_get_value_name(0, "regIp", playerInfo[playerid][e_PlayerRegIp]);
            cache_get_value_name(0, "lastIp", playerInfo[playerid][e_PlayerLastp]);

            ShowAuthorizationDialog(playerid);
        }
        else
            ShowRegistrationDialog(playerid);
    }
    MySQL_TQueryInline(dbHandle, using inline CheckPlayerAccount, 
        "SELECT * FROM players WHERE name = '%e'", playerInfo[playerid][e_PlayerName]);
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

Dialog:DIALOG_REGISTRATION(playerid, response, listitem, inputtext[])
{
    if (response)
    {
        if (IsNull(inputtext) || !IsValidString(inputtext) || !(MIN_PASSWORD_LENGTH <= strlen(inputtext) <= MAX_PASSWORD_LENGTH))
            return ShowRegistrationDialog(playerid);

        bcrypt_hash(playerid, "OnRegistrationHash", inputtext, BCRYPT_COST);
    }
    else
        DelayedKick(playerid);

    return true;
}

forward OnRegistrationHash(playerid);
public OnRegistrationHash(playerid)
{
    new encryptedpPassword[BCRYPT_HASH_LENGTH];
    bcrypt_get_hash(encryptedpPassword);

    format(playerInfo[playerid][e_PlayerRegIp], 16, playerInfo[playerid][e_PlayerLastIp]);

    inline const OnRegistrationAccount()
    {
        playerInfo[playerid][e_PlayerId] = cache_insert_id();
    }
    MySQL_TQueryInline(dbHandle, using inline OnRegistrationAccount, 
        "INSERT INTO players (name, password, regIp, lastIp) VALUES ('%e', '%e', '%e', '%e')", 
    playerInfo[playerid][e_PlayerName], encryptedpPassword, playerInfo[playerid][e_PlayerRegIp], 
    playerInfo[playerid][e_PlayerLastIp]);   
    return true;
}

Dialog:DIALOG_LOGIN(playerid, response, listitem, inputtext[])
{
    if (response)
    {
        if (IsNull(inputtext)){
           return ShowAuthorizationDialog(playerid);
        }

        bcrypt_verify(playerid, "OnAuthorizationHash", inputtext, playerInfo[playerid][e_PlayerPassword]);
    }
    else
        DelayedKick(playerid);

    return true;
}

forward OnAuthorizationHash(playerid, bool:success);
public OnAuthorizationHash(playerid, bool:success)
{
    if (!success){
        ShowAuthorizationDialog(playerid);
    }

    return true;
}