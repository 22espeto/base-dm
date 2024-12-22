
new MySQL:dbHandle;

enum e_playerInfo
{
    e_PlayerId,
    e_PlayerName[MAX_PLAYER_NAME + 1],
    e_PlayerPassword[BCRYPT_HASH_LENGTH],
    e_PlayerRegIp[16],
    e_PlayerLastIp[16]
};
new playerInfo[MAX_PLAYERS][e_playerInfo];