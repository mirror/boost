#include <iconv.h>

int main()
{
	iconv_t d = iconv_open(0,0);
	(void)(d);
}
