
#undef MAX_PLAYERS
#define MAX_PLAYERS (120)

#define MIN_PASSWORD_LENGTH (5)
#define MAX_PASSWORD_LENGTH (25)

#define PASSWORD_HASH_LENGTH (64)
#define PASSWORD_SALT_LENGTH (10)

#define DISCORD_LINK "discord.gg/#"

#define KILL_FEED_TIME (7500)
#define KILL_FEED_LINES (6)
#define KILL_FEED_SIZE (64 * KILL_FEED_LINES)


#define DelayedKick(%0) SetTimerEx("OnDelayedKick", 250, false, "d", %0)