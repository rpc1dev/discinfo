//---------------------------------------------------------------------------

#ifndef dvdcdinfoH
#define dvdcdinfoH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "SHDocVw_OCX.h"
#include <OleCtrls.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TComboBox *ComboBox1;
        TPanel *Panel2;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *Label6;
        TLabel *Label7;
        TLabel *Label8;
        TLabel *Label9;
        TLabel *Label10;
        TLabel *Label11;
        TLabel *Label12;
        TLabel *Label13;
        TLabel *Label14;
        TSaveDialog *SaveDialog1;
        TMainMenu *MainMenu1;
        TMenuItem *Files1;
        TMenuItem *SaveInfo1;
        TMenuItem *eXit1;
        TMenuItem *About1;
        TStaticText *StaticText1;
        TStaticText *StaticText2;
        TLabel *Label15;
        TLabel *Label16;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall EditCompo(TObject *Sender);
        void __fastcall RunSaveDialog(TObject *Sender);
        void __fastcall eXit1Click(TObject *Sender);
        void __fastcall About1Click(TObject *Sender);
       
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
