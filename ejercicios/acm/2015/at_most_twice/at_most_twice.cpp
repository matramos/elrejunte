#include <cstdio>
#include <cstring>

using namespace std;

char entrada[19], resultado[19], frecuencia[10];
int i, num, len;

inline void rellenar(int inicio, int fin)
{
    int f = 9;
    while(inicio < fin)
    {
        if(frecuencia[f] < 2) 
            resultado[inicio] = f+'0', ++frecuencia[f], ++inicio;
        else --f;
    }
    resultado[fin] = '\0';
}

int main(int argc, char const *argv[])
{
    while(scanf("%s",entrada)!=EOF)
    {
        memset(frecuencia,0,sizeof frecuencia);
        memset(resultado,'\0',sizeof resultado);

        len = strlen(entrada);
        
        for(i=0;i<len;++i)
        {
            num = entrada[i]-'0';
            if(frecuencia[num] < 2)
            {
                ++frecuencia[num];
                resultado[i] = num + '0';
            }else break;
        }

        if(i != len) 
        {
            for(num = entrada[i]-'0'-1; num>=0 && frecuencia[num]==2; --num);

            if(num == -1)
            {
                for(--i, --frecuencia[entrada[i]-'0']; i>=0; --i, --frecuencia[entrada[i]-'0'])
                {
                    for(num = entrada[i]-'0'-1; num>=0 && frecuencia[num]==2; --num);
                    if(i == 0 && num == 0) {rellenar(0, len-1); break;}
                    if(num == -1) continue;
                    ++frecuencia[num];
                    resultado[i] = num + '0';
                    rellenar(i+1, len);
                    break;
                }
            }else
            {
                ++frecuencia[num];
                resultado[i] = num + '0';
                rellenar(i+1, len);
            }
        }

        printf("%s\n", resultado);
    }
    return 0;
}