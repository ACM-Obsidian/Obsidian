#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

int main ()
{
	int kase; scanf("%d", &kase);
	for (int _ = 1; _ <= kase; ++_)
	{
		int n, l; scanf("%d %d", &n, &l);
		printf("Case #%d: ", _);
		if (n >= 3)
		{
			for (int i = 0, t = 0; i < l; i++, t++)
			{
				if (t == 3) t = 0;
				printf("%c", 'a' + t); 
			}
			printf("\n");
		}
		else if (n == 1)
		{
			for (int i = 0; i < l; i++)
				printf("a");
			printf("\n");
		}
		else // n == 2
		{
			switch (l)
			{
				case 1: printf("a\n"); break;
				case 2: printf("ab\n"); break;
				case 3: printf("aab\n"); break;
				case 4: printf("aabb\n"); break;
				case 5: printf("aaaba\n"); break;
				case 6: printf("aaabab\n"); break;
				case 7: printf("aaababb\n"); break;
				case 8: printf("aaababbb\n"); break;
				default:
					printf("aaaa");
					int r = l - 4, tt = r / 6;;
					for (int i = 0; i < tt; i++) printf("babbaa");
					int rm = r % 6;
					if (rm == 0);
					else if (rm == 1) printf("a");
					else if (rm == 2) printf("aa");
					else
					{
						for (int i = 0; i < rm; i++) printf("%c", "babbaa"[i]);
					}
					printf("\n");
			}
		}
	}
	return 0;
}
