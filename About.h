//---------------------------------------------------------------------------

#ifndef AboutH
#define AboutH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TAbout_Box : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TGroupBox *GroupBox1;
        TBitBtn *BitBtn1;
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
        TPanel *Panel2;
        TPanel *Panel3;
        TPanel *Panel4;
        TPanel *Panel5;
    TImage *Image1;
    TGroupBox *GroupBox2;
        void __fastcall About_CloseClick(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall Label3Click(TObject *Sender);
        void __fastcall Label8Click(TObject *Sender);
        void __fastcall Label5Click(TObject *Sender);
    void __fastcall Image1Click(TObject *Sender);
    void __fastcall BitBtn1KeyPress(TObject *Sender, char &Key);
private:	// User declarations
public:		// User declarations
        __fastcall TAbout_Box(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAbout_Box *About_Box;
//---------------------------------------------------------------------------
#endif
