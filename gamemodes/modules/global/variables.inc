
new MySQL:dbHandle, bool:inClassSelection[MAX_PLAYERS], bool:alreadySpawned[MAX_PLAYERS];

new 
    killFeedStr[MAX_PLAYERS][KILL_FEED_SIZE], 
    killFeedTick[MAX_PLAYERS], 
    killFeedLines[MAX_PLAYERS]
;

enum e_playerInfo
{
    e_PlayerId,
    e_PlayerName[MAX_PLAYER_NAME + 1],
    e_PlayerPassword[PASSWORD_HASH_LENGTH + 1],
    e_PlayerSalt[PASSWORD_SALT_LENGTH + 1],
    e_PlayerRegIp[16],
    e_PlayerLastIp[16],
    e_PlayerWeapons[MAX_GUNMENU_SLOTS],
    e_PlayerKills,
    e_PlayerDeaths,
    e_PlayerSkin,
    e_PlayerWeather,
    e_PlayerTime,
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

// fast turn skins
new const blockedSkins[] = 
{
    0,
    1,
    2,
    265,
    266,
    267,
    268,
    269,
    270,
    271,
    300,
    301,
    303,
};