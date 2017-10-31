//Solo para enteros positivos
inline void Scanf(int& a)
{
	char c = 0;
	while(c<33) c = getc(stdin);
	a = 0;
	while(c>33) a = a*10 + c - '0', c = getc(stdin);
}
