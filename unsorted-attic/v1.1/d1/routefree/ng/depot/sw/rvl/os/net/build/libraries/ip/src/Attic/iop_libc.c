a54 13
u32 utoa(u32 n, char s[])
{
	u32 i = 0;

	do
	{
		s[i++] = (n%10) + '0';
	
	} while ((n/=10)>0);

    return i;
}

