#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>

int main()
{
	int size = 12;
	setlocale (LC_ALL, "C.UTF-8");
	FILE* tex = fopen("tematix.txt", "r");
	if(tex == NULL)
	{
		wprintf(L"~The text file not found or not connected~\n");
		return 0;
	}
//	fseek(tex, 0, SEEK_END);
//	size = ftell(tex) / 2 + 1;
	fclose(tex);
	wchar_t str[size];
	wchar_t l;
	FILE* tems = fopen("tematix.txt", "r");
	int i, j;
	for(i = 0; i <= size; i++)
	{
		str[i] = fgetwc(tems);
		if(str[i] == '\n')
		{
			str[i] = '\0';
			break;
		}
		if(str[i - 1] == ' ')
		{
			l = str[i];
			continue;
		}
		if(str[i] == EOF)
		{
			str[i] = '\0';
			break;
		}
	}
	str[i - 2] = '\0';
	wprintf(L"тема 1:\n%ls\nколичество слов:\n%lc\n", str, l);
	return 0;
}