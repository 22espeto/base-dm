
new MySQL:dbHandle, bool:inClassSelection[MAX_PLAYERS], bool:alreadySpawned[MAX_PLAYERS];

enum e_playerInfo
{
    e_PlayerId,
    e_PlayerName[MAX_PLAYER_NAME + 1],
    e_PlayerPassword[BCRYPT_HASH_LENGTH],
    e_PlayerRegIp[16],
    e_PlayerLastIp[16],
    e_PlayerKills,
    e_PlayerDeaths,
    e_PlayerSkin,
    bool:e_PlayerLogged
};
new playerInfo[MAX_PLAYERS][e_playerInfo];

new const AvailableSkins[] = 
{
    0,
    21,
    29,
    27,
    45,
    154,
    61,
    134,
    153,
    158,
    159,
    164,
    176,
    177
};