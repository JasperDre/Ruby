#include "FrameworkPCH.h"
#include "DebugUtility.h"

namespace DebugUtility
{
	void OutputMessage(const char* message, ...)
	{
		char szBuff[1024];
		va_list arg;
		va_start(arg, message);
		vsnprintf_s(szBuff, sizeof(szBuff), _TRUNCATE, message, arg);
		va_end(arg);
		printf("%s\n", szBuff);
	}
}
