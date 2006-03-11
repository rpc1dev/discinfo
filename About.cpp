//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "About.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAbout_Box *About_Box;
//---------------------------------------------------------------------------
__fastcall TAbout_Box::TAbout_Box(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TAbout_Box::About_CloseClick(TObject *Sender)
{
        TAbout_Box::Close();
}
//---------------------------------------------------------------------------

void __fastcall TAbout_Box::FormCreate(TObject *Sender)
{
        Label5->Caption=Application->Title;        
}
//---------------------------------------------------------------------------

void __fastcall TAbout_Box::Label3Click(TObject *Sender)
{
        ShellExecute(About_Box->Handle,"open","mailto:hijacker@rpc1.org?Subject=DISCInfo feedback","","",0);
}
//---------------------------------------------------------------------------

void __fastcall TAbout_Box::Label8Click(TObject *Sender)
{
        ShellExecute(About_Box->Handle,"open","http://www.rpc1.org","","",0);
}
//---------------------------------------------------------------------------

void __fastcall TAbout_Box::Label5Click(TObject *Sender)
{
        ShellExecute(About_Box->Handle,"open","http://discinfo.rpc1.org/","","",0);        
}
//---------------------------------------------------------------------------

void __fastcall TAbout_Box::BitBtn1KeyPress(TObject *Sender, char &Key)
{
    if (Key == 'x' || Key == 'X' || Key == VK_ESCAPE)
    {
        TAbout_Box::Close();
    }
}
//---------------------------------------------------------------------------

