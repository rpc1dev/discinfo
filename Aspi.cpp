#include "Extra.h"
#include "stdafx.h"
#include "Stdio.h"
#include "Stdlib.h"
#include "String.h"
//#include "CDVDMain.h"

DWORD (*_ptr_GetASPI32SupportInfo)(VOID);
DWORD (*_ptr_SendASPI32Command)(LPSRB);

// Initializes WNASPI32.DLL
// It really does not matter that this doesn't intend on ever freeing the
// library.  It even discards the return value of LoadLibrary.
DWORD InitASPI(void)
{
	HINSTANCE handle;
	DWORD temp;

	handle = LoadLibrary (WNASPI32_DLL);
	if (!handle)
	{
		temp = GetLastError();
		return (!temp) ? 1 : temp;
	}

	_ptr_GetASPI32SupportInfo = (DWORD (*)(VOID)) GetProcAddress(handle,
		"GetASPI32SupportInfo");
	_ptr_SendASPI32Command = (DWORD (*)(LPSRB)) GetProcAddress(handle,
		"SendASPI32Command");

	if (!_ptr_GetASPI32SupportInfo || !_ptr_SendASPI32Command)
		return 1;

	return 0;
}

