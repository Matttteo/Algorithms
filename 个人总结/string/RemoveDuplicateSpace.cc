#include <iostream>
#include <cstring>
using namespace std;
void removeDuplicateSpace(char* str, int);

int main(int argc, char** argv)
{
	char* line = "   a  b ccc d  ";
	char str[100];
	strcpy(str, line);

	removeDuplicateSpace(str, 15);
	cout << str << "|" << endl;
	return 0;
}

void removeDuplicateSpace(char* str, int size)
{
	if (size < 2)
	{
		return;
	}
	int lo, hi;
	lo = hi = 0;

	while(hi < size)
	{
		if (str[hi] != ' ')
		{
			str[lo] = str[hi];
			if (lo != hi)
			{
				str[hi] = ' ';
			}
			lo++;
			hi++;
		}
		else if (hi + 1 < size && str[hi + 1] != ' ')
		{
			hi++;
			lo++;
		}
		else
		{
			hi++;
		}

	}
	str[lo + 1] = '\0';
}