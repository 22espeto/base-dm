#include <YSI_Coding/y_hooks>

new 
    Text:TD_ArenaScoreboard[21], Text:TD_ArenaStats[2], PlayerText:TD_PlayerStats[MAX_PLAYERS][2]
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
    TD_PlayerStats[playerid][0] = CreatePlayerTextDraw(playerid, 3.000000, 416.000000, "");
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

    TD_ArenaScoreboard[0] = TextDrawCreate(320.000000, 102.911003, "_");
    TextDrawFont(TD_ArenaScoreboard[0], 1);
    TextDrawLetterSize(TD_ArenaScoreboard[0], 0.000000, 0.433299);
    TextDrawTextSize(TD_ArenaScoreboard[0], 0.000000, 208.000000);
    TextDrawSetOutline(TD_ArenaScoreboard[0], 1);
    TextDrawSetShadow(TD_ArenaScoreboard[0], 0);
    TextDrawAlignment(TD_ArenaScoreboard[0], 2);
    TextDrawColor(TD_ArenaScoreboard[0], 1044266751);
    TextDrawBackgroundColor(TD_ArenaScoreboard[0], 255);
    TextDrawBoxColor(TD_ArenaScoreboard[0], 1044266751);
    TextDrawUseBox(TD_ArenaScoreboard[0], 1);
    TextDrawSetProportional(TD_ArenaScoreboard[0], 1);
    TextDrawSetSelectable(TD_ArenaScoreboard[0], 0);

    TD_ArenaScoreboard[1] = TextDrawCreate(320.000000, 98.810997, "_");
    TextDrawFont(TD_ArenaScoreboard[1], 1);
    TextDrawLetterSize(TD_ArenaScoreboard[1], 0.000000, 0.166599);
    TextDrawTextSize(TD_ArenaScoreboard[1], 0.000000, 196.000000);
    TextDrawSetOutline(TD_ArenaScoreboard[1], 1);
    TextDrawSetShadow(TD_ArenaScoreboard[1], 0);
    TextDrawAlignment(TD_ArenaScoreboard[1], 2);
    TextDrawColor(TD_ArenaScoreboard[1], 1044266751);
    TextDrawBackgroundColor(TD_ArenaScoreboard[1], 255);
    TextDrawBoxColor(TD_ArenaScoreboard[1], 1044266751);
    TextDrawUseBox(TD_ArenaScoreboard[1], 1);
    TextDrawSetProportional(TD_ArenaScoreboard[1], 1);
    TextDrawSetSelectable(TD_ArenaScoreboard[1], 0);

    TD_ArenaScoreboard[2] = TextDrawCreate(211.366577, 93.499900, "ld_beat:chit");
    TextDrawFont(TD_ArenaScoreboard[2], 4);
    TextDrawLetterSize(TD_ArenaScoreboard[2], 0.600000, 2.000000);
    TextDrawTextSize(TD_ArenaScoreboard[2], 14.000000, 19.000000);
    TextDrawSetOutline(TD_ArenaScoreboard[2], 1);
    TextDrawSetShadow(TD_ArenaScoreboard[2], 0);
    TextDrawAlignment(TD_ArenaScoreboard[2], 1);
    TextDrawColor(TD_ArenaScoreboard[2], 1044266751);
    TextDrawBackgroundColor(TD_ArenaScoreboard[2], 255);
    TextDrawBoxColor(TD_ArenaScoreboard[2], 50);
    TextDrawUseBox(TD_ArenaScoreboard[2], 0);
    TextDrawSetProportional(TD_ArenaScoreboard[2], 1);
    TextDrawSetSelectable(TD_ArenaScoreboard[2], 0);

    TD_ArenaScoreboard[3] = TextDrawCreate(412.366577, 93.499900, "ld_beat:chit");
    TextDrawFont(TD_ArenaScoreboard[3], 4);
    TextDrawLetterSize(TD_ArenaScoreboard[3], 0.600000, 2.000000);
    TextDrawTextSize(TD_ArenaScoreboard[3], 16.000000, 19.000000);
    TextDrawSetOutline(TD_ArenaScoreboard[3], 1);
    TextDrawSetShadow(TD_ArenaScoreboard[3], 0);
    TextDrawAlignment(TD_ArenaScoreboard[3], 1);
    TextDrawColor(TD_ArenaScoreboard[3], 1044266751);
    TextDrawBackgroundColor(TD_ArenaScoreboard[3], 255);
    TextDrawBoxColor(TD_ArenaScoreboard[3], 50);
    TextDrawUseBox(TD_ArenaScoreboard[3], 0);
    TextDrawSetProportional(TD_ArenaScoreboard[3], 1);
    TextDrawSetSelectable(TD_ArenaScoreboard[3], 0);

    TD_ArenaScoreboard[4] = TextDrawCreate(320.000000, 105.110000, "_");
    TextDrawFont(TD_ArenaScoreboard[4], 1);
    TextDrawLetterSize(TD_ArenaScoreboard[4], 0.000000, 10.249999);
    TextDrawTextSize(TD_ArenaScoreboard[4], 0.000000, 208.000000);
    TextDrawSetOutline(TD_ArenaScoreboard[4], 1);
    TextDrawSetShadow(TD_ArenaScoreboard[4], 0);
    TextDrawAlignment(TD_ArenaScoreboard[4], 2);
    TextDrawColor(TD_ArenaScoreboard[4], -1);
    TextDrawBackgroundColor(TD_ArenaScoreboard[4], 255);
    TextDrawBoxColor(TD_ArenaScoreboard[4], 218959359);
    TextDrawUseBox(TD_ArenaScoreboard[4], 1);
    TextDrawSetProportional(TD_ArenaScoreboard[4], 1);
    TextDrawSetSelectable(TD_ArenaScoreboard[4], 0);

    TD_ArenaScoreboard[5] = TextDrawCreate(220.266799, 106.000000, "N");
    TextDrawFont(TD_ArenaScoreboard[5], 1);
    TextDrawLetterSize(TD_ArenaScoreboard[5], 0.201297, 0.802398);
    TextDrawTextSize(TD_ArenaScoreboard[5], 400.000000, 17.000000);
    TextDrawSetOutline(TD_ArenaScoreboard[5], 0);
    TextDrawSetShadow(TD_ArenaScoreboard[5], 1);
    TextDrawAlignment(TD_ArenaScoreboard[5], 1);
    TextDrawColor(TD_ArenaScoreboard[5], -1);
    TextDrawBackgroundColor(TD_ArenaScoreboard[5], 140);
    TextDrawBoxColor(TD_ArenaScoreboard[5], 50);
    TextDrawUseBox(TD_ArenaScoreboard[5], 0);
    TextDrawSetProportional(TD_ArenaScoreboard[5], 1);
    TextDrawSetSelectable(TD_ArenaScoreboard[5], 0);

    TD_ArenaScoreboard[6] = TextDrawCreate(229.934204, 106.018501, "PLAYER");
    TextDrawFont(TD_ArenaScoreboard[6], 1);
    TextDrawLetterSize(TD_ArenaScoreboard[6], 0.201297, 0.802398);
    TextDrawTextSize(TD_ArenaScoreboard[6], 400.000000, 17.000000);
    TextDrawSetOutline(TD_ArenaScoreboard[6], 0);
    TextDrawSetShadow(TD_ArenaScoreboard[6], 1);
    TextDrawAlignment(TD_ArenaScoreboard[6], 1);
    TextDrawColor(TD_ArenaScoreboard[6], -1);
    TextDrawBackgroundColor(TD_ArenaScoreboard[6], 140);
    TextDrawBoxColor(TD_ArenaScoreboard[6], 50);
    TextDrawUseBox(TD_ArenaScoreboard[6], 0);
    TextDrawSetProportional(TD_ArenaScoreboard[6], 1);
    TextDrawSetSelectable(TD_ArenaScoreboard[6], 0);

    TD_ArenaScoreboard[7] = TextDrawCreate(390.743804, 106.029602, "RATIO");
    TextDrawFont(TD_ArenaScoreboard[7], 1);
    TextDrawLetterSize(TD_ArenaScoreboard[7], 0.201297, 0.802398);
    TextDrawTextSize(TD_ArenaScoreboard[7], 400.000000, 17.000000);
    TextDrawSetOutline(TD_ArenaScoreboard[7], 0);
    TextDrawSetShadow(TD_ArenaScoreboard[7], 1);
    TextDrawAlignment(TD_ArenaScoreboard[7], 1);
    TextDrawColor(TD_ArenaScoreboard[7], -1);
    TextDrawBackgroundColor(TD_ArenaScoreboard[7], 140);
    TextDrawBoxColor(TD_ArenaScoreboard[7], 50);
    TextDrawUseBox(TD_ArenaScoreboard[7], 0);
    TextDrawSetProportional(TD_ArenaScoreboard[7], 1);
    TextDrawSetSelectable(TD_ArenaScoreboard[7], 0);

    TD_ArenaScoreboard[8] = TextDrawCreate(305.989807, 106.029602, "DAMAGE");
    TextDrawFont(TD_ArenaScoreboard[8], 1);
    TextDrawLetterSize(TD_ArenaScoreboard[8], 0.201297, 0.802398);
    TextDrawTextSize(TD_ArenaScoreboard[8], 400.000000, 17.000000);
    TextDrawSetOutline(TD_ArenaScoreboard[8], 0);
    TextDrawSetShadow(TD_ArenaScoreboard[8], 1);
    TextDrawAlignment(TD_ArenaScoreboard[8], 1);
    TextDrawColor(TD_ArenaScoreboard[8], -1);
    TextDrawBackgroundColor(TD_ArenaScoreboard[8], 140);
    TextDrawBoxColor(TD_ArenaScoreboard[8], 50);
    TextDrawUseBox(TD_ArenaScoreboard[8], 0);
    TextDrawSetProportional(TD_ArenaScoreboard[8], 1);
    TextDrawSetSelectable(TD_ArenaScoreboard[8], 0);

    TD_ArenaScoreboard[9] = TextDrawCreate(356.691802, 106.029602, "KILLS");
    TextDrawFont(TD_ArenaScoreboard[9], 1);
    TextDrawLetterSize(TD_ArenaScoreboard[9], 0.201297, 0.802398);
    TextDrawTextSize(TD_ArenaScoreboard[9], 400.000000, 17.000000);
    TextDrawSetOutline(TD_ArenaScoreboard[9], 0);
    TextDrawSetShadow(TD_ArenaScoreboard[9], 1);
    TextDrawAlignment(TD_ArenaScoreboard[9], 1);
    TextDrawColor(TD_ArenaScoreboard[9], -1);
    TextDrawBackgroundColor(TD_ArenaScoreboard[9], 140);
    TextDrawBoxColor(TD_ArenaScoreboard[9], 50);
    TextDrawUseBox(TD_ArenaScoreboard[9], 0);
    TextDrawSetProportional(TD_ArenaScoreboard[9], 1);
    TextDrawSetSelectable(TD_ArenaScoreboard[9], 0);

    TD_ArenaScoreboard[10] = TextDrawCreate(320.000000, 120.000000, "_");
    TextDrawFont(TD_ArenaScoreboard[10], 1);
    TextDrawLetterSize(TD_ArenaScoreboard[10], 0.000000, 0.833298);
    TextDrawTextSize(TD_ArenaScoreboard[10], 0.000000, 201.000000);
    TextDrawSetOutline(TD_ArenaScoreboard[10], 1);
    TextDrawSetShadow(TD_ArenaScoreboard[10], 0);
    TextDrawAlignment(TD_ArenaScoreboard[10], 2);
    TextDrawColor(TD_ArenaScoreboard[10], -1);
    TextDrawBackgroundColor(TD_ArenaScoreboard[10], 255);
    TextDrawBoxColor(TD_ArenaScoreboard[10], 471604479);
    TextDrawUseBox(TD_ArenaScoreboard[10], 1);
    TextDrawSetProportional(TD_ArenaScoreboard[10], 1);
    TextDrawSetSelectable(TD_ArenaScoreboard[10], 0);

    TD_ArenaScoreboard[11] = TextDrawCreate(320.000000, 134.000000, "_");
    TextDrawFont(TD_ArenaScoreboard[11], 1);
    TextDrawLetterSize(TD_ArenaScoreboard[11], 0.000000, 0.833298);
    TextDrawTextSize(TD_ArenaScoreboard[11], 0.000000, 201.000000);
    TextDrawSetOutline(TD_ArenaScoreboard[11], 1);
    TextDrawSetShadow(TD_ArenaScoreboard[11], 0);
    TextDrawAlignment(TD_ArenaScoreboard[11], 2);
    TextDrawColor(TD_ArenaScoreboard[11], 471604479);
    TextDrawBackgroundColor(TD_ArenaScoreboard[11], 255);
    TextDrawBoxColor(TD_ArenaScoreboard[11], 471604479);
    TextDrawUseBox(TD_ArenaScoreboard[11], 1);
    TextDrawSetProportional(TD_ArenaScoreboard[11], 1);
    TextDrawSetSelectable(TD_ArenaScoreboard[11], 0);

    TD_ArenaScoreboard[12] = TextDrawCreate(320.000000, 148.500000, "_");
    TextDrawFont(TD_ArenaScoreboard[12], 1);
    TextDrawLetterSize(TD_ArenaScoreboard[12], 0.000000, 0.833298);
    TextDrawTextSize(TD_ArenaScoreboard[12], 0.000000, 201.000000);
    TextDrawSetOutline(TD_ArenaScoreboard[12], 1);
    TextDrawSetShadow(TD_ArenaScoreboard[12], 0);
    TextDrawAlignment(TD_ArenaScoreboard[12], 2);
    TextDrawColor(TD_ArenaScoreboard[12], -1);
    TextDrawBackgroundColor(TD_ArenaScoreboard[12], 255);
    TextDrawBoxColor(TD_ArenaScoreboard[12], 471604479);
    TextDrawUseBox(TD_ArenaScoreboard[12], 1);
    TextDrawSetProportional(TD_ArenaScoreboard[12], 1);
    TextDrawSetSelectable(TD_ArenaScoreboard[12], 0);

    TD_ArenaScoreboard[13] = TextDrawCreate(320.000000, 162.500000, "_");
    TextDrawFont(TD_ArenaScoreboard[13], 1);
    TextDrawLetterSize(TD_ArenaScoreboard[13], 0.000000, 0.833298);
    TextDrawTextSize(TD_ArenaScoreboard[13], 0.000000, 201.000000);
    TextDrawSetOutline(TD_ArenaScoreboard[13], 1);
    TextDrawSetShadow(TD_ArenaScoreboard[13], 0);
    TextDrawAlignment(TD_ArenaScoreboard[13], 2);
    TextDrawColor(TD_ArenaScoreboard[13], -1);
    TextDrawBackgroundColor(TD_ArenaScoreboard[13], 255);
    TextDrawBoxColor(TD_ArenaScoreboard[13], 471604479);
    TextDrawUseBox(TD_ArenaScoreboard[13], 1);
    TextDrawSetProportional(TD_ArenaScoreboard[13], 1);
    TextDrawSetSelectable(TD_ArenaScoreboard[13], 0);

    TD_ArenaScoreboard[14] = TextDrawCreate(320.000000, 177.000000, "_");
    TextDrawFont(TD_ArenaScoreboard[14], 1);
    TextDrawLetterSize(TD_ArenaScoreboard[14], 0.000000, 0.833298);
    TextDrawTextSize(TD_ArenaScoreboard[14], 0.000000, 201.000000);
    TextDrawSetOutline(TD_ArenaScoreboard[14], 1);
    TextDrawSetShadow(TD_ArenaScoreboard[14], 0);
    TextDrawAlignment(TD_ArenaScoreboard[14], 2);
    TextDrawColor(TD_ArenaScoreboard[14], -1);
    TextDrawBackgroundColor(TD_ArenaScoreboard[14], 255);
    TextDrawBoxColor(TD_ArenaScoreboard[14], 471604479);
    TextDrawUseBox(TD_ArenaScoreboard[14], 1);
    TextDrawSetProportional(TD_ArenaScoreboard[14], 1);
    TextDrawSetSelectable(TD_ArenaScoreboard[14], 0);

    TD_ArenaScoreboard[15] = TextDrawCreate(228.100006, 107.599899, "_");
    TextDrawFont(TD_ArenaScoreboard[15], 1);
    TextDrawLetterSize(TD_ArenaScoreboard[15], 0.000000, 8.980600);
    TextDrawTextSize(TD_ArenaScoreboard[15], 0.000000, -1.749899);
    TextDrawSetOutline(TD_ArenaScoreboard[15], 1);
    TextDrawSetShadow(TD_ArenaScoreboard[15], 0);
    TextDrawAlignment(TD_ArenaScoreboard[15], 2);
    TextDrawColor(TD_ArenaScoreboard[15], -1);
    TextDrawBackgroundColor(TD_ArenaScoreboard[15], 255);
    TextDrawBoxColor(TD_ArenaScoreboard[15], 218959359);
    TextDrawUseBox(TD_ArenaScoreboard[15], 1);
    TextDrawSetProportional(TD_ArenaScoreboard[15], 1);
    TextDrawSetSelectable(TD_ArenaScoreboard[15], 0);

    TD_ArenaScoreboard[16] = TextDrawCreate(220.500000, 119.000000, "1~n~~n~2~n~~n~3~n~~n~4~n~~n~5");
    TextDrawFont(TD_ArenaScoreboard[16], 1);
    TextDrawLetterSize(TD_ArenaScoreboard[16], 0.201297, 0.795000);
    TextDrawTextSize(TD_ArenaScoreboard[16], 400.000000, 17.000000);
    TextDrawSetOutline(TD_ArenaScoreboard[16], 0);
    TextDrawSetShadow(TD_ArenaScoreboard[16], 1);
    TextDrawAlignment(TD_ArenaScoreboard[16], 1);
    TextDrawColor(TD_ArenaScoreboard[16], -1);
    TextDrawBackgroundColor(TD_ArenaScoreboard[16], 140);
    TextDrawBoxColor(TD_ArenaScoreboard[16], 50);
    TextDrawUseBox(TD_ArenaScoreboard[16], 0);
    TextDrawSetProportional(TD_ArenaScoreboard[16], 1);
    TextDrawSetSelectable(TD_ArenaScoreboard[16], 0);

    TD_ArenaScoreboard[17] = TextDrawCreate(231.899902, 119.000000, "retcheeee~n~~n~retcheeee~n~~n~retcheeee~n~~n~retcheeee~n~~n~retcheeee~n~~n~");
    TextDrawFont(TD_ArenaScoreboard[17], 1);
    TextDrawLetterSize(TD_ArenaScoreboard[17], 0.194297, 0.795000);
    TextDrawTextSize(TD_ArenaScoreboard[17], 400.000000, 17.000000);
    TextDrawSetOutline(TD_ArenaScoreboard[17], 0);
    TextDrawSetShadow(TD_ArenaScoreboard[17], 1);
    TextDrawAlignment(TD_ArenaScoreboard[17], 1);
    TextDrawColor(TD_ArenaScoreboard[17], -1);
    TextDrawBackgroundColor(TD_ArenaScoreboard[17], 140);
    TextDrawBoxColor(TD_ArenaScoreboard[17], 50);
    TextDrawUseBox(TD_ArenaScoreboard[17], 0);
    TextDrawSetProportional(TD_ArenaScoreboard[17], 1);
    TextDrawSetSelectable(TD_ArenaScoreboard[17], 0);

    TD_ArenaScoreboard[18] = TextDrawCreate(319.500000, 119.000000, "10000~n~~n~10000~n~~n~10000~n~~n~10000~n~~n~10000~n~~n~");
    TextDrawFont(TD_ArenaScoreboard[18], 1);
    TextDrawLetterSize(TD_ArenaScoreboard[18], 0.194297, 0.795000);
    TextDrawTextSize(TD_ArenaScoreboard[18], 400.000000, 17.000000);
    TextDrawSetOutline(TD_ArenaScoreboard[18], 0);
    TextDrawSetShadow(TD_ArenaScoreboard[18], 1);
    TextDrawAlignment(TD_ArenaScoreboard[18], 2);
    TextDrawColor(TD_ArenaScoreboard[18], -1);
    TextDrawBackgroundColor(TD_ArenaScoreboard[18], 140);
    TextDrawBoxColor(TD_ArenaScoreboard[18], 50);
    TextDrawUseBox(TD_ArenaScoreboard[18], 0);
    TextDrawSetProportional(TD_ArenaScoreboard[18], 1);
    TextDrawSetSelectable(TD_ArenaScoreboard[18], 0);

    TD_ArenaScoreboard[19] = TextDrawCreate(364.500000, 119.000000, "60~n~~n~60~n~~n~60~n~~n~60~n~~n~60~n~~n~");
    TextDrawFont(TD_ArenaScoreboard[19], 1);
    TextDrawLetterSize(TD_ArenaScoreboard[19], 0.194297, 0.795000);
    TextDrawTextSize(TD_ArenaScoreboard[19], 400.000000, 17.000000);
    TextDrawSetOutline(TD_ArenaScoreboard[19], 0);
    TextDrawSetShadow(TD_ArenaScoreboard[19], 1);
    TextDrawAlignment(TD_ArenaScoreboard[19], 2);
    TextDrawColor(TD_ArenaScoreboard[19], -1);
    TextDrawBackgroundColor(TD_ArenaScoreboard[19], 140);
    TextDrawBoxColor(TD_ArenaScoreboard[19], 50);
    TextDrawUseBox(TD_ArenaScoreboard[19], 0);
    TextDrawSetProportional(TD_ArenaScoreboard[19], 1);
    TextDrawSetSelectable(TD_ArenaScoreboard[19], 0);

    TD_ArenaScoreboard[20] = TextDrawCreate(399.500000, 119.000000, "999.0~n~~n~999.0~n~~n~999.0~n~~n~999.0~n~~n~999.0~n~~n~");
    TextDrawFont(TD_ArenaScoreboard[20], 1);
    TextDrawLetterSize(TD_ArenaScoreboard[20], 0.194297, 0.795000);
    TextDrawTextSize(TD_ArenaScoreboard[20], 400.000000, 17.000000);
    TextDrawSetOutline(TD_ArenaScoreboard[20], 0);
    TextDrawSetShadow(TD_ArenaScoreboard[20], 1);
    TextDrawAlignment(TD_ArenaScoreboard[20], 2);
    TextDrawColor(TD_ArenaScoreboard[20], -1);
    TextDrawBackgroundColor(TD_ArenaScoreboard[20], 140);
    TextDrawBoxColor(TD_ArenaScoreboard[20], 50);
    TextDrawUseBox(TD_ArenaScoreboard[20], 0);
    TextDrawSetProportional(TD_ArenaScoreboard[20], 1);
    TextDrawSetSelectable(TD_ArenaScoreboard[20], 0);
}