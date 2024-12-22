
stock SetAlpha(color, alpha)
{
    return color & ~0xFF | clamp(alpha, 0, 255);
}

forward OnDelayedKick(playerid);
public OnDelayedKick(playerid)
{
    return Kick(playerid);
}

stock IsValidString(const str[])
{
	for(new i; str[i] != EOS; ++i)
	{
		switch(str[i])
		{
			case '0'..'9', 'A'..'Z', 'a'..'z': continue;
			default: return false;
		}
	}
	return true;
}