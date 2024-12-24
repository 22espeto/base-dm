#include <YSI_Coding/y_hooks>

new 
    Text:TD_ArenaScoreboard[24], 
    Text:TD_ArenaStats[2], 
    PlayerText:TD_PlayerStats[MAX_PLAYERS][3]
;

hook OnGameModeInit()
{
    CreateGlobalTextdraws();
    return true;
}

hook OnPlayerConnect(playerid)
{
    CreatePlayerTextdraws(playerid);
    return true;
}

stock ShowTextdraws(playerid)
{
    TextDrawShowForPlayer(playerid, TD_ArenaStats[0]);
    TextDrawShowForPlayer(playerid, TD_ArenaStats[1]);

    PlayerTextDrawShow(playerid, TD_PlayerStats[playerid][0]);
    PlayerTextDrawShow(playerid, TD_PlayerStats[playerid][1]);
}

stock CreatePlayerTextdraws(playerid)
{
    TD_PlayerStats[playerid][0] = CreatePlayerTextDraw(playerid, 3.000000, 414.000000, "");
    PlayerTextDrawLetterSize(playerid, TD_PlayerStats[playerid][0], 0.175000, 0.800000);
    PlayerTextDrawTextSize(playerid, TD_PlayerStats[playerid][0], 400.000000, 17.000000);
    PlayerTextDrawAlignment(playerid, TD_PlayerStats[playerid][0], 1);
    PlayerTextDrawColor(playerid, TD_PlayerStats[playerid][0], 0xFFFFFFFF);
    PlayerTextDrawBoxColor(playerid, TD_PlayerStats[playerid][0], 0x00000050);
    PlayerTextDrawSetShadow(playerid, TD_PlayerStats[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, TD_PlayerStats[playerid][0], 1);
    PlayerTextDrawBackgroundColor(playerid, TD_PlayerStats[playerid][0], 0x0000002D);
    PlayerTextDrawFont(playerid, TD_PlayerStats[playerid][0], 1);
    PlayerTextDrawSetProportional(playerid, TD_PlayerStats[playerid][0], 1);
    PlayerTextDrawSetSelectable(playerid, TD_PlayerStats[playerid][0], 0);

    TD_PlayerStats[playerid][1] = CreatePlayerTextDraw(playerid, 554.400024, 2.986654, "");
    PlayerTextDrawLetterSize(playerid, TD_PlayerStats[playerid][1], 0.210795, 0.843375);
    PlayerTextDrawTextSize(playerid, TD_PlayerStats[playerid][1], 1280.000000, 1280.000000);
    PlayerTextDrawAlignment(playerid, TD_PlayerStats[playerid][1], 2);
    PlayerTextDrawColor(playerid, TD_PlayerStats[playerid][1], 0xFFFFFFFF);
    PlayerTextDrawBoxColor(playerid, TD_PlayerStats[playerid][1], 0x00000050);
    PlayerTextDrawSetShadow(playerid, TD_PlayerStats[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, TD_PlayerStats[playerid][1], 1);
    PlayerTextDrawBackgroundColor(playerid, TD_PlayerStats[playerid][1], 0x0000002D);
    PlayerTextDrawFont(playerid, TD_PlayerStats[playerid][1], 1);
    PlayerTextDrawSetProportional(playerid, TD_PlayerStats[playerid][1], 1);

   	TD_PlayerStats[playerid][2] = CreatePlayerTextDraw(playerid, 319.000000, 389.000000, "");
    PlayerTextDrawLetterSize(playerid, TD_PlayerStats[playerid][2], 0.250, 0.80);
    PlayerTextDrawAlignment(playerid, TD_PlayerStats[playerid][2], 2);
    PlayerTextDrawColor(playerid, TD_PlayerStats[playerid][1], 0xFFFFFFFF);
    PlayerTextDrawBoxColor(playerid, TD_PlayerStats[playerid][1], 0x00000050);
    PlayerTextDrawSetShadow(playerid, TD_PlayerStats[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, TD_PlayerStats[playerid][2], 1);
    PlayerTextDrawBackgroundColor(playerid, TD_PlayerStats[playerid][2], 0x0000002D);
    PlayerTextDrawFont(playerid, TD_PlayerStats[playerid][2], 1);
    PlayerTextDrawSetProportional(playerid, TD_PlayerStats[playerid][2], 1);
}

stock CreateGlobalTextdraws()
{
    TD_ArenaStats[0] = TextDrawCreate(553.000000, 22.000000, "");
    TextDrawLetterSize(TD_ArenaStats[0], 0.589999, 2.200000);
    TextDrawTextSize(TD_ArenaStats[0], 1280.000000, 1280.000000);
    TextDrawColor(TD_ArenaStats[0], 0xFFFFFFFF);
    TextDrawBoxColor(TD_ArenaStats[0], 0x80808080);
    TextDrawSetShadow(TD_ArenaStats[0], 0);
    TextDrawSetOutline(TD_ArenaStats[0], 1);
    TextDrawBackgroundColor(TD_ArenaStats[0], 0x00000033);
    TextDrawFont(TD_ArenaStats[0], 3);
    TextDrawSetProportional(TD_ArenaStats[0], 1);
    TextDrawSetSelectable(TD_ArenaStats[0], 0);

    TD_ArenaStats[1] = TextDrawCreate(568.000000, 12.000000, "");
    TextDrawLetterSize(TD_ArenaStats[1], 0.179157, 0.949993);
    TextDrawTextSize(TD_ArenaStats[1], 931.500000, 158.000000);
    TextDrawAlignment(TD_ArenaStats[1], 2);
    TextDrawColor(TD_ArenaStats[1], 0xFFFFFFFF);
    TextDrawBoxColor(TD_ArenaStats[1], 0x00000050);
    TextDrawSetShadow(TD_ArenaStats[1], 0);
    TextDrawSetOutline(TD_ArenaStats[1], 1);
    TextDrawBackgroundColor(TD_ArenaStats[1], 0x0000002D);
    TextDrawFont(TD_ArenaStats[1], 1);
    TextDrawSetProportional(TD_ArenaStats[1], 1);
    TextDrawSetSelectable(TD_ArenaStats[1], 0);

    TD_ArenaScoreboard[0] = TextDrawCreate(232.000000, 105.500000, "ld_spac:white");
    TextDrawFont(TD_ArenaScoreboard[0], 4);
    TextDrawLetterSize(TD_ArenaScoreboard[0], 0.600000, 2.000000);
    TextDrawTextSize(TD_ArenaScoreboard[0], 189.500000, 119.000000);
    TextDrawSetOutline(TD_ArenaScoreboard[0], 1);
    TextDrawSetShadow(TD_ArenaScoreboard[0], 0);
    TextDrawAlignment(TD_ArenaScoreboard[0], 1);
    TextDrawColor(TD_ArenaScoreboard[0], 0x246415FF);
    TextDrawBackgroundColor(TD_ArenaScoreboard[0], 255);
    TextDrawBoxColor(TD_ArenaScoreboard[0], 50);
    TextDrawUseBox(TD_ArenaScoreboard[0], 1);
    TextDrawSetProportional(TD_ArenaScoreboard[0], 1);
    TextDrawSetSelectable(TD_ArenaScoreboard[0], 0);

    TD_ArenaScoreboard[1] = TextDrawCreate(410.000000, 102.000000, "ld_beat:chit");
    TextDrawFont(TD_ArenaScoreboard[1], 4);
    TextDrawLetterSize(TD_ArenaScoreboard[1], 0.600000, 2.000000);
    TextDrawTextSize(TD_ArenaScoreboard[1], 24.500000, 21.500000);
    TextDrawSetOutline(TD_ArenaScoreboard[1], 1);
    TextDrawSetShadow(TD_ArenaScoreboard[1], 0);
    TextDrawAlignment(TD_ArenaScoreboard[1], 1);
    TextDrawColor(TD_ArenaScoreboard[1], 0x246415FF);
    TextDrawBackgroundColor(TD_ArenaScoreboard[1], 255);
    TextDrawBoxColor(TD_ArenaScoreboard[1], 50);
    TextDrawUseBox(TD_ArenaScoreboard[1], 1);
    TextDrawSetProportional(TD_ArenaScoreboard[1], 1);
    TextDrawSetSelectable(TD_ArenaScoreboard[1], 0);

    TD_ArenaScoreboard[2] = TextDrawCreate(220.000000, 102.000000, "ld_beat:chit");
    TextDrawFont(TD_ArenaScoreboard[2], 4);
    TextDrawLetterSize(TD_ArenaScoreboard[2], 0.600000, 2.000000);
    TextDrawTextSize(TD_ArenaScoreboard[2], 24.500000, 21.500000);
    TextDrawSetOutline(TD_ArenaScoreboard[2], 1);
    TextDrawSetShadow(TD_ArenaScoreboard[2], 0);
    TextDrawAlignment(TD_ArenaScoreboard[2], 1);
    TextDrawColor(TD_ArenaScoreboard[2], 0x246415FF);
    TextDrawBackgroundColor(TD_ArenaScoreboard[2], 255);
    TextDrawBoxColor(TD_ArenaScoreboard[2], 50);
    TextDrawUseBox(TD_ArenaScoreboard[2], 1);
    TextDrawSetProportional(TD_ArenaScoreboard[2], 1);
    TextDrawSetSelectable(TD_ArenaScoreboard[2], 0);

    TD_ArenaScoreboard[3] = TextDrawCreate(220.000000, 206.000000, "ld_beat:chit");
    TextDrawFont(TD_ArenaScoreboard[3], 4);
    TextDrawLetterSize(TD_ArenaScoreboard[3], 0.600000, 2.000000);
    TextDrawTextSize(TD_ArenaScoreboard[3], 24.500000, 21.500000);
    TextDrawSetOutline(TD_ArenaScoreboard[3], 1);
    TextDrawSetShadow(TD_ArenaScoreboard[3], 0);
    TextDrawAlignment(TD_ArenaScoreboard[3], 1);
    TextDrawColor(TD_ArenaScoreboard[3], 0x246415FF);
    TextDrawBackgroundColor(TD_ArenaScoreboard[3], 255);
    TextDrawBoxColor(TD_ArenaScoreboard[3], 50);
    TextDrawUseBox(TD_ArenaScoreboard[3], 1);
    TextDrawSetProportional(TD_ArenaScoreboard[3], 1);
    TextDrawSetSelectable(TD_ArenaScoreboard[3], 0);

    TD_ArenaScoreboard[4] = TextDrawCreate(410.000000, 206.000000, "ld_beat:chit");
    TextDrawFont(TD_ArenaScoreboard[4], 4);
    TextDrawLetterSize(TD_ArenaScoreboard[4], 0.600000, 2.000000);
    TextDrawTextSize(TD_ArenaScoreboard[4], 24.500000, 22.000000);
    TextDrawSetOutline(TD_ArenaScoreboard[4], 1);
    TextDrawSetShadow(TD_ArenaScoreboard[4], 0);
    TextDrawAlignment(TD_ArenaScoreboard[4], 1);
    TextDrawColor(TD_ArenaScoreboard[4], 0x246415FF); 
    TextDrawBackgroundColor(TD_ArenaScoreboard[4], 255);
    TextDrawBoxColor(TD_ArenaScoreboard[4], 50);
    TextDrawUseBox(TD_ArenaScoreboard[4], 1);
    TextDrawSetProportional(TD_ArenaScoreboard[4], 1);
    TextDrawSetSelectable(TD_ArenaScoreboard[4], 0);

    TD_ArenaScoreboard[5] = TextDrawCreate(224.000000, 111.000000, "ld_spac:white");
    TextDrawFont(TD_ArenaScoreboard[5], 4);
    TextDrawLetterSize(TD_ArenaScoreboard[5], 0.600000, 2.000000);
    TextDrawTextSize(TD_ArenaScoreboard[5], 207.000000, 107.500000);
    TextDrawSetOutline(TD_ArenaScoreboard[5], 1);
    TextDrawSetShadow(TD_ArenaScoreboard[5], 0);
    TextDrawAlignment(TD_ArenaScoreboard[5], 1);
    TextDrawColor(TD_ArenaScoreboard[5], 303109119);
    TextDrawBackgroundColor(TD_ArenaScoreboard[5], 255);
    TextDrawBoxColor(TD_ArenaScoreboard[5], 50);
    TextDrawUseBox(TD_ArenaScoreboard[5], 1);
    TextDrawSetProportional(TD_ArenaScoreboard[5], 1);
    TextDrawSetSelectable(TD_ArenaScoreboard[5], 0);

    TD_ArenaScoreboard[6] = TextDrawCreate(327.000000, 92.000000, "ROUND_RESULTS");
    TextDrawFont(TD_ArenaScoreboard[6], 2);
    TextDrawLetterSize(TD_ArenaScoreboard[6], 0.208333, 1.299998);
    TextDrawTextSize(TD_ArenaScoreboard[6], 400.000000, 17.000000);
    TextDrawSetOutline(TD_ArenaScoreboard[6], 1);
    TextDrawSetShadow(TD_ArenaScoreboard[6], 0);
    TextDrawAlignment(TD_ArenaScoreboard[6], 2);
    TextDrawColor(TD_ArenaScoreboard[6], -1);
    TextDrawBackgroundColor(TD_ArenaScoreboard[6], 85);
    TextDrawBoxColor(TD_ArenaScoreboard[6], 50);
    TextDrawUseBox(TD_ArenaScoreboard[6], 0);
    TextDrawSetProportional(TD_ArenaScoreboard[6], 1);
    TextDrawSetSelectable(TD_ArenaScoreboard[6], 0);

    TD_ArenaScoreboard[7] = TextDrawCreate(229.500000, 112.500000, "N");
    TextDrawFont(TD_ArenaScoreboard[7], 1);
    TextDrawLetterSize(TD_ArenaScoreboard[7], 0.174998, 0.800000);
    TextDrawTextSize(TD_ArenaScoreboard[7], 400.000000, 17.000000);
    TextDrawSetOutline(TD_ArenaScoreboard[7], 0);
    TextDrawSetShadow(TD_ArenaScoreboard[7], 0);
    TextDrawAlignment(TD_ArenaScoreboard[7], 1);
    TextDrawColor(TD_ArenaScoreboard[7], -1);
    TextDrawBackgroundColor(TD_ArenaScoreboard[7], 85);
    TextDrawBoxColor(TD_ArenaScoreboard[7], 50);
    TextDrawUseBox(TD_ArenaScoreboard[7], 0);
    TextDrawSetProportional(TD_ArenaScoreboard[7], 1);
    TextDrawSetSelectable(TD_ArenaScoreboard[7], 0);

    TD_ArenaScoreboard[8] = TextDrawCreate(255.000000, 112.500000, "NickName");
    TextDrawFont(TD_ArenaScoreboard[8], 1);
    TextDrawLetterSize(TD_ArenaScoreboard[8], 0.174998, 0.800000);
    TextDrawTextSize(TD_ArenaScoreboard[8], 400.000000, 17.000000);
    TextDrawSetOutline(TD_ArenaScoreboard[8], 0);
    TextDrawSetShadow(TD_ArenaScoreboard[8], 0);
    TextDrawAlignment(TD_ArenaScoreboard[8], 2);
    TextDrawColor(TD_ArenaScoreboard[8], -1);
    TextDrawBackgroundColor(TD_ArenaScoreboard[8], 85);
    TextDrawBoxColor(TD_ArenaScoreboard[8], 50);
    TextDrawUseBox(TD_ArenaScoreboard[8], 0);
    TextDrawSetProportional(TD_ArenaScoreboard[8], 1);
    TextDrawSetSelectable(TD_ArenaScoreboard[8], 0);

    TD_ArenaScoreboard[9] = TextDrawCreate(342.000000, 112.500000, "Damage");
    TextDrawFont(TD_ArenaScoreboard[9], 1);
    TextDrawLetterSize(TD_ArenaScoreboard[9], 0.174998, 0.800000);
    TextDrawTextSize(TD_ArenaScoreboard[9], 400.000000, 17.000000);
    TextDrawSetOutline(TD_ArenaScoreboard[9], 0);
    TextDrawSetShadow(TD_ArenaScoreboard[9], 0);
    TextDrawAlignment(TD_ArenaScoreboard[9], 2);
    TextDrawColor(TD_ArenaScoreboard[9], -1);
    TextDrawBackgroundColor(TD_ArenaScoreboard[9], 85);
    TextDrawBoxColor(TD_ArenaScoreboard[9], 50);
    TextDrawUseBox(TD_ArenaScoreboard[9], 0);
    TextDrawSetProportional(TD_ArenaScoreboard[9], 1);
    TextDrawSetSelectable(TD_ArenaScoreboard[9], 0);

    TD_ArenaScoreboard[10] = TextDrawCreate(370.000000, 112.500000, "Kills");
    TextDrawFont(TD_ArenaScoreboard[10], 1);
    TextDrawLetterSize(TD_ArenaScoreboard[10], 0.174998, 0.800000);
    TextDrawTextSize(TD_ArenaScoreboard[10], 400.000000, 17.000000);
    TextDrawSetOutline(TD_ArenaScoreboard[10], 0);
    TextDrawSetShadow(TD_ArenaScoreboard[10], 0);
    TextDrawAlignment(TD_ArenaScoreboard[10], 2);
    TextDrawColor(TD_ArenaScoreboard[10], -1);
    TextDrawBackgroundColor(TD_ArenaScoreboard[10], 85);
    TextDrawBoxColor(TD_ArenaScoreboard[10], 50);
    TextDrawUseBox(TD_ArenaScoreboard[10], 0);
    TextDrawSetProportional(TD_ArenaScoreboard[10], 1);
    TextDrawSetSelectable(TD_ArenaScoreboard[10], 0);

    TD_ArenaScoreboard[11] = TextDrawCreate(388.500000, 112.500000, "K/D");
    TextDrawFont(TD_ArenaScoreboard[11], 1);
    TextDrawLetterSize(TD_ArenaScoreboard[11], 0.174998, 0.800000);
    TextDrawTextSize(TD_ArenaScoreboard[11], 400.000000, 17.000000);
    TextDrawSetOutline(TD_ArenaScoreboard[11], 0);
    TextDrawSetShadow(TD_ArenaScoreboard[11], 0);
    TextDrawAlignment(TD_ArenaScoreboard[11], 2);
    TextDrawColor(TD_ArenaScoreboard[11], -1);
    TextDrawBackgroundColor(TD_ArenaScoreboard[11], 85);
    TextDrawBoxColor(TD_ArenaScoreboard[11], 50);
    TextDrawUseBox(TD_ArenaScoreboard[11], 0);
    TextDrawSetProportional(TD_ArenaScoreboard[11], 1);
    TextDrawSetSelectable(TD_ArenaScoreboard[11], 0);

    TD_ArenaScoreboard[12] = TextDrawCreate(420.500000, 112.500000, "Clan");
    TextDrawFont(TD_ArenaScoreboard[12], 1);
    TextDrawLetterSize(TD_ArenaScoreboard[12], 0.174998, 0.800000);
    TextDrawTextSize(TD_ArenaScoreboard[12], 400.000000, 17.000000);
    TextDrawSetOutline(TD_ArenaScoreboard[12], 0);
    TextDrawSetShadow(TD_ArenaScoreboard[12], 0);
    TextDrawAlignment(TD_ArenaScoreboard[12], 2);
    TextDrawColor(TD_ArenaScoreboard[12], -1);
    TextDrawBackgroundColor(TD_ArenaScoreboard[12], 85);
    TextDrawBoxColor(TD_ArenaScoreboard[12], 50);
    TextDrawUseBox(TD_ArenaScoreboard[12], 0);
    TextDrawSetProportional(TD_ArenaScoreboard[12], 1);
    TextDrawSetSelectable(TD_ArenaScoreboard[12], 0);

    TD_ArenaScoreboard[13] = TextDrawCreate(228.000000, 199.800003, "ld_spac:white");
    TextDrawFont(TD_ArenaScoreboard[13], 4);
    TextDrawLetterSize(TD_ArenaScoreboard[13], 0.600000, 2.000000);
    TextDrawTextSize(TD_ArenaScoreboard[13], 83.500000, 1.500000);
    TextDrawSetOutline(TD_ArenaScoreboard[13], 1);
    TextDrawSetShadow(TD_ArenaScoreboard[13], 0);
    TextDrawAlignment(TD_ArenaScoreboard[13], 1);
    TextDrawColor(TD_ArenaScoreboard[13], -1);
    TextDrawBackgroundColor(TD_ArenaScoreboard[13], 255);
    TextDrawBoxColor(TD_ArenaScoreboard[13], 50);
    TextDrawUseBox(TD_ArenaScoreboard[13], 0);
    TextDrawSetProportional(TD_ArenaScoreboard[13], 1);
    TextDrawSetSelectable(TD_ArenaScoreboard[13], 0);

    TD_ArenaScoreboard[14] = TextDrawCreate(327.000000, 196.500000, "Top_Clans");
    TextDrawFont(TD_ArenaScoreboard[14], 1);
    TextDrawLetterSize(TD_ArenaScoreboard[14], 0.154164, 0.750000);
    TextDrawTextSize(TD_ArenaScoreboard[14], 400.000000, 17.000000);
    TextDrawSetOutline(TD_ArenaScoreboard[14], 0);
    TextDrawSetShadow(TD_ArenaScoreboard[14], 0);
    TextDrawAlignment(TD_ArenaScoreboard[14], 2);
    TextDrawColor(TD_ArenaScoreboard[14], -1);
    TextDrawBackgroundColor(TD_ArenaScoreboard[14], 85);
    TextDrawBoxColor(TD_ArenaScoreboard[14], 50);
    TextDrawUseBox(TD_ArenaScoreboard[14], 0);
    TextDrawSetProportional(TD_ArenaScoreboard[14], 1);
    TextDrawSetSelectable(TD_ArenaScoreboard[14], 0);

    TD_ArenaScoreboard[15] = TextDrawCreate(343.500000, 199.800003, "ld_spac:white");
    TextDrawFont(TD_ArenaScoreboard[15], 4);
    TextDrawLetterSize(TD_ArenaScoreboard[15], 0.600000, 2.000000);
    TextDrawTextSize(TD_ArenaScoreboard[15], 83.500000, 1.500000);
    TextDrawSetOutline(TD_ArenaScoreboard[15], 1);
    TextDrawSetShadow(TD_ArenaScoreboard[15], 0);
    TextDrawAlignment(TD_ArenaScoreboard[15], 1);
    TextDrawColor(TD_ArenaScoreboard[15], -1);
    TextDrawBackgroundColor(TD_ArenaScoreboard[15], 255);
    TextDrawBoxColor(TD_ArenaScoreboard[15], 50);
    TextDrawUseBox(TD_ArenaScoreboard[15], 0);
    TextDrawSetProportional(TD_ArenaScoreboard[15], 1);
    TextDrawSetSelectable(TD_ArenaScoreboard[15], 0);

    TD_ArenaScoreboard[16] = TextDrawCreate(327.000000, 203.000000, "Kills:_~y~None_(0)");
    TextDrawFont(TD_ArenaScoreboard[16], 1);
    TextDrawLetterSize(TD_ArenaScoreboard[16], 0.154164, 0.750000);
    TextDrawTextSize(TD_ArenaScoreboard[16], 430.000000, 227.000000);
    TextDrawSetOutline(TD_ArenaScoreboard[16], 0);
    TextDrawSetShadow(TD_ArenaScoreboard[16], 0);
    TextDrawAlignment(TD_ArenaScoreboard[16], 2);
    TextDrawColor(TD_ArenaScoreboard[16], -1);
    TextDrawBackgroundColor(TD_ArenaScoreboard[16], 85);
    TextDrawBoxColor(TD_ArenaScoreboard[16], 50);
    TextDrawUseBox(TD_ArenaScoreboard[16], 0);
    TextDrawSetProportional(TD_ArenaScoreboard[16], 1);
    TextDrawSetSelectable(TD_ArenaScoreboard[16], 0);

    TD_ArenaScoreboard[17] = TextDrawCreate(327.000000, 208.500000, "Damage:_~y~None_(0)");
    TextDrawFont(TD_ArenaScoreboard[17], 1);
    TextDrawLetterSize(TD_ArenaScoreboard[17], 0.154164, 0.750000);
    TextDrawTextSize(TD_ArenaScoreboard[17], 430.000000, 227.000000);
    TextDrawSetOutline(TD_ArenaScoreboard[17], 0);
    TextDrawSetShadow(TD_ArenaScoreboard[17], 0);
    TextDrawAlignment(TD_ArenaScoreboard[17], 2);
    TextDrawColor(TD_ArenaScoreboard[17], -1);
    TextDrawBackgroundColor(TD_ArenaScoreboard[17], 85);
    TextDrawBoxColor(TD_ArenaScoreboard[17], 50);
    TextDrawUseBox(TD_ArenaScoreboard[17], 0);
    TextDrawSetProportional(TD_ArenaScoreboard[17], 1);
    TextDrawSetSelectable(TD_ArenaScoreboard[17], 0);

    TD_ArenaScoreboard[18] = TextDrawCreate(230.000000, 120.500000, "1~n~2~n~3~n~4~n~5~n~6~n~7~n~8~n~9~n~10");
    TextDrawFont(TD_ArenaScoreboard[18], 1);
    TextDrawLetterSize(TD_ArenaScoreboard[18], 0.174998, 0.800000);
    TextDrawTextSize(TD_ArenaScoreboard[18], 400.000000, 17.000000);
    TextDrawSetOutline(TD_ArenaScoreboard[18], 0);
    TextDrawSetShadow(TD_ArenaScoreboard[18], 0);
    TextDrawAlignment(TD_ArenaScoreboard[18], 1);
    TextDrawColor(TD_ArenaScoreboard[18], -1);
    TextDrawBackgroundColor(TD_ArenaScoreboard[18], 85);
    TextDrawBoxColor(TD_ArenaScoreboard[18], 50);
    TextDrawUseBox(TD_ArenaScoreboard[18], 0);
    TextDrawSetProportional(TD_ArenaScoreboard[18], 1);
    TextDrawSetSelectable(TD_ArenaScoreboard[18], 0);

    TD_ArenaScoreboard[19] = TextDrawCreate(242.000000, 120.500000, "espeto~n~espeto~n~espeto~n~espeto~n~espeto~n~espeto~n~espeto~n~espeto~n~espeto~n~espeto");
    TextDrawFont(TD_ArenaScoreboard[19], 1);
    TextDrawLetterSize(TD_ArenaScoreboard[19], 0.174998, 0.800000);
    TextDrawTextSize(TD_ArenaScoreboard[19], 400.000000, 17.000000);
    TextDrawSetOutline(TD_ArenaScoreboard[19], 0);
    TextDrawSetShadow(TD_ArenaScoreboard[19], 0);
    TextDrawAlignment(TD_ArenaScoreboard[19], 1);
    TextDrawColor(TD_ArenaScoreboard[19], -1);
    TextDrawBackgroundColor(TD_ArenaScoreboard[19], 85);
    TextDrawBoxColor(TD_ArenaScoreboard[19], 50);
    TextDrawUseBox(TD_ArenaScoreboard[19], 0);
    TextDrawSetProportional(TD_ArenaScoreboard[19], 1);
    TextDrawSetSelectable(TD_ArenaScoreboard[19], 0);

    TD_ArenaScoreboard[20] = TextDrawCreate(342.000000, 120.500000, "9000~n~9000~n~9000~n~9000~n~9000~n~9000~n~9000~n~9000~n~9000~n~9000");
    TextDrawFont(TD_ArenaScoreboard[20], 1);
    TextDrawLetterSize(TD_ArenaScoreboard[20], 0.174998, 0.800000);
    TextDrawTextSize(TD_ArenaScoreboard[20], 400.000000, 52.000000);
    TextDrawSetOutline(TD_ArenaScoreboard[20], 0);
    TextDrawSetShadow(TD_ArenaScoreboard[20], 0);
    TextDrawAlignment(TD_ArenaScoreboard[20], 2);
    TextDrawColor(TD_ArenaScoreboard[20], -1);
    TextDrawBackgroundColor(TD_ArenaScoreboard[20], 85);
    TextDrawBoxColor(TD_ArenaScoreboard[20], 50);
    TextDrawUseBox(TD_ArenaScoreboard[20], 0);
    TextDrawSetProportional(TD_ArenaScoreboard[20], 1);
    TextDrawSetSelectable(TD_ArenaScoreboard[20], 0);

    TD_ArenaScoreboard[21] = TextDrawCreate(370.000000, 120.500000, "65~n~65~n~65~n~65~n~65~n~65~n~65~n~65~n~65~n~65");
    TextDrawFont(TD_ArenaScoreboard[21], 1);
    TextDrawLetterSize(TD_ArenaScoreboard[21], 0.174998, 0.800000);
    TextDrawTextSize(TD_ArenaScoreboard[21], 400.000000, 32.000000);
    TextDrawSetOutline(TD_ArenaScoreboard[21], 0);
    TextDrawSetShadow(TD_ArenaScoreboard[21], 0);
    TextDrawAlignment(TD_ArenaScoreboard[21], 2);
    TextDrawColor(TD_ArenaScoreboard[21], -1);
    TextDrawBackgroundColor(TD_ArenaScoreboard[21], 85);
    TextDrawBoxColor(TD_ArenaScoreboard[21], 50);
    TextDrawUseBox(TD_ArenaScoreboard[21], 0);
    TextDrawSetProportional(TD_ArenaScoreboard[21], 1);
    TextDrawSetSelectable(TD_ArenaScoreboard[21], 0);

    TD_ArenaScoreboard[22] = TextDrawCreate(388.000000, 120.500000, "2.00~n~2.00~n~2.00~n~2.00~n~2.00~n~2.00~n~2.00~n~2.00~n~2.00~n~2.00");
    TextDrawFont(TD_ArenaScoreboard[22], 1);
    TextDrawLetterSize(TD_ArenaScoreboard[22], 0.174998, 0.800000);
    TextDrawTextSize(TD_ArenaScoreboard[22], 400.000000, 32.000000);
    TextDrawSetOutline(TD_ArenaScoreboard[22], 0);
    TextDrawSetShadow(TD_ArenaScoreboard[22], 0);
    TextDrawAlignment(TD_ArenaScoreboard[22], 2);
    TextDrawColor(TD_ArenaScoreboard[22], -1);
    TextDrawBackgroundColor(TD_ArenaScoreboard[22], 85);
    TextDrawBoxColor(TD_ArenaScoreboard[22], 50);
    TextDrawUseBox(TD_ArenaScoreboard[22], 0);
    TextDrawSetProportional(TD_ArenaScoreboard[22], 1);
    TextDrawSetSelectable(TD_ArenaScoreboard[22], 0);

    TD_ArenaScoreboard[23] = TextDrawCreate(420.000000, 120.500000, "N/A~n~N/A~n~N/A~n~N/A~n~N/A~n~N/A~n~N/A~n~N/A~n~N/A~n~N/A");
    TextDrawFont(TD_ArenaScoreboard[23], 1);
    TextDrawLetterSize(TD_ArenaScoreboard[23], 0.174998, 0.800000);
    TextDrawTextSize(TD_ArenaScoreboard[23], 400.000000, 32.000000);
    TextDrawSetOutline(TD_ArenaScoreboard[23], 0);
    TextDrawSetShadow(TD_ArenaScoreboard[23], 0);
    TextDrawAlignment(TD_ArenaScoreboard[23], 2);
    TextDrawColor(TD_ArenaScoreboard[23], -1);
    TextDrawBackgroundColor(TD_ArenaScoreboard[23], 85);
    TextDrawBoxColor(TD_ArenaScoreboard[23], 50);
    TextDrawUseBox(TD_ArenaScoreboard[23], 0);
    TextDrawSetProportional(TD_ArenaScoreboard[23], 1);
    TextDrawSetSelectable(TD_ArenaScoreboard[23], 0);
}