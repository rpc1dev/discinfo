//---------------------------------------------------------------------------

#include <vcl.h>
#include "aspi_w32.h"

USERES("cdvdinfo.res");
USEFORM("dvdcdinfo.cpp", Form1);
USEUNIT("aspi.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        #ifdef CDVDinfo_DEBUG
        start_debug();
        #endif

        if(!loadASPI())
        {
            #ifdef CDVDinfo_DEBUG
             write_debug_info("Load ASPI failed\n\r");
            #endif
           return 0;
        }

        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TForm1), &Form1);
                 Application->Run();
        }
        catch (Exception &exception)
        {
           #ifdef CDVDinfo_DEBUG
            write_debug_info("Exception\n\r");
           #endif

           Application->ShowException(&exception);
        }

        #ifdef CDVDinfo_DEBUG
            write_debug_info("Exit normal\n\r");
        #endif
        return 0;
}
//---------------------------------------------------------------------------
