//---------------------------------------------------------------------------

#ifndef ExtraH
#define ExtraH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TExtra_Box : public TForm
{
__published:	// IDE-managed Components
        TPanel *Extra_Panel;
        TBitBtn *Close;
        TGroupBox *Read_Info;
        TGroupBox *Write_Info;
        TPanel *CD_DVD_Name;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TCheckBox *r_cdr;
        TCheckBox *r_cdrw;
        TCheckBox *r_m2;
        TLabel *l_name;
        TLabel *Label5;
        TLabel *Label6;
        TLabel *Label7;
        TCheckBox *r_dvdrom;
        TCheckBox *r_dvdram;
        TCheckBox *r_dvdr;
        TLabel *Label8;
        TLabel *Label9;
        TLabel *Label10;
        TLabel *Label11;
        TCheckBox *w_cdr;
        TCheckBox *w_cdrw;
        TCheckBox *w_dvdr;
        TCheckBox *w_dvdram;
    TGroupBox *GroupBox1;
    TGroupBox *GroupBox2;
    TLabel *SNText;
    TLabel *LevelText;
    TLabel *BufferText;
    TLabel *SerialNum;
    TLabel *VolumeLevel;
    TLabel *BufferSize;
    TLabel *Label4;
    TCheckBox *w_dvdrw;
    TLabel *Label12;
    TCheckBox *w_test;
    TLabel *Label13;
    TCheckBox *r_dvdrw;
    TLabel *Label14;
    TLabel *Label15;
    TCheckBox *r_dvdpr;
    TCheckBox *r_dvdprw;
    TLabel *Label16;
    TLabel *Label17;
    TCheckBox *w_dvdpr;
    TCheckBox *w_dvdprw;
    TLabel *Label18;
    TLabel *Label19;
    TLabel *Label20;
    TLabel *Label21;
    TLabel *Label22;
    TLabel *Label23;
    TLabel *Label24;
    TLabel *Label25;
    TLabel *Label26;
    TLabel *Label27;
    TLabel *Label28;
    TCheckBox *AudioPlay;
    TCheckBox *Composite;
    TCheckBox *Digiport1;
    TCheckBox *Digiport2;
    TCheckBox *upcread;
    TCheckBox *BufferUnder;
    TCheckBox *Multisession;
    TCheckBox *Mode2F1;
    TCheckBox *Mode2F2;
    TCheckBox *isrc;
    TCheckBox *BarCode;
    TButton *Button1;
    TLabel *Label29;
    TCheckBox *mtrainier;
    TLabel *Label30;
    TLabel *Mechanism;
    TLabel *Label31;
    TLabel *Interface;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall r_cdrKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall r_cdrMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall CloseClick(TObject *Sender);
    void __fastcall CloseKeyPress(TObject *Sender, char &Key);
    void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TExtra_Box(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TExtra_Box *Extra_Box;
//---------------------------------------------------------------------------
#endif
