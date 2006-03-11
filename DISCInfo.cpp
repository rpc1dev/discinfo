//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

//---------------------------------------------------------------------------
USEFORM("CDVDMain.cpp", Main_Form);
USEFORM("About.cpp", About_Box);
USEFORM("Extra.cpp", Extra_Box);
USEFORM("Searchf.cpp", Search_Box);
USEFORM("Summary.cpp", SumInfo);
//---------------------------------------------------------------------------
#pragma resource "*.dfm"

WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        #ifdef DISCInfo_DEBUG
            start_log();
        #endif

        try
        {
            Application->Initialize();
            Application->Title = "DISC Info version 1.6.1";
            Application->CreateForm(__classid(TMain_Form), &Main_Form);
           Application->Run();
        }
        catch (Exception &exception)
        {
                 #ifdef DISCInfo_DEBUG
                    write_log("Exception\n\r");
                 #endif
                 Application->ShowException(&exception);
        }
        catch (...)
        {
                 try
                 {
                         throw Exception("");
                 }
                 catch (Exception &exception)
                 {
                         Application->ShowException(&exception);
                 }
        }
        #ifdef DISCInfo_DEBUG
            write_log("Program exited correctly");
        #endif
        return 0;
}
//---------------------------------------------------------------------------
