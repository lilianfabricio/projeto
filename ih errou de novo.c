#include <stdio.h>
int main()
{
	int casos_testes, i=0, j=0;
	long long int k, a, b, c, d, x, y, aux, resp;

	scanf("%d", &casos_testes);

	for ( j = 0; j < casos_testes; j++)
	{
	    resp = 0;
		scanf("%lld%lld%lld%lld%lld", &k, &a, &b, &c, &d);

		for (i=a; i<=b; i++)
        {
            aux = k - i + 1;
            //printf("VALOR DO Y %lld\n", aux);
            if ( c > aux )
            {
                aux = c;
            }
            aux = d - aux + 1;
            if ( aux < 0)
            {
                aux = 0;
            }
            //printf("AQUII!! %lld\n", aux);
            resp = resp + aux;
        }
        printf("%lld\n", resp);
	}
}
