#ifndef __ASPI_H__
#define __ASPI_H__

#include "scsidefs.h"
#include "wnaspi32.h"
#include "Device.h"

typedef wchar_t wchar;

// Dynamic loading of the WNASPI32.DLL library
extern DWORD (*_ptr_GetASPI32SupportInfo)(VOID);
#define GetASPI32SupportInfo (*_ptr_GetASPI32SupportInfo)
extern DWORD (*_ptr_SendASPI32Command)(LPSRB);
#define SendASPI32Command (*_ptr_SendASPI32Command)

DWORD InitASPI(void);

#define OEM_CODE_PAGE 437
#define MAX_ID 8
#define WNASPI32_DLL "WNASPI32.DLL"

#endif // __ASPI_H__
