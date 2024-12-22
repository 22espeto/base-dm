
#undef MAX_PLAYERS
#define MAX_PLAYERS 120

#define MIN_PASSWORD_LENGTH 5
#define MAX_PASSWORD_LENGTH 25

#define DelayedKick(%0) SetTimerEx("OnDelayedKick", 250, false, "d")