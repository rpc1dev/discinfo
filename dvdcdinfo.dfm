object Form1: TForm1
  Left = 183
  Top = 211
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'CDVDInfo Version 1.3.5'
  ClientHeight = 276
  ClientWidth = 346
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  Visible = True
  OnCreate = FormCreate
  PixelsPerInch = 120
  TextHeight = 16
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 345
    Height = 275
    BevelInner = bvRaised
    BevelOuter = bvLowered
    TabOrder = 0
    object Panel2: TPanel
      Left = 24
      Top = 64
      Width = 297
      Height = 185
      BevelInner = bvRaised
      BevelOuter = bvLowered
      TabOrder = 1
      object Label1: TLabel
        Left = 8
        Top = 16
        Width = 117
        Height = 16
        Caption = 'Firmware Revision: '
      end
      object Label2: TLabel
        Left = 274
        Top = 16
        Width = 7
        Height = 16
        Alignment = taRightJustify
        Caption = '?'
      end
      object Label3: TLabel
        Left = 8
        Top = 32
        Width = 98
        Height = 16
        Caption = 'Vendor Specific:'
      end
      object Label4: TLabel
        Left = 274
        Top = 32
        Width = 7
        Height = 16
        Alignment = taRightJustify
        Caption = '?'
      end
      object Label5: TLabel
        Left = 8
        Top = 80
        Width = 127
        Height = 16
        Caption = 'Region setting status:'
      end
      object Label6: TLabel
        Left = 8
        Top = 96
        Width = 172
        Height = 16
        Caption = 'Number of user changes left :'
      end
      object Label7: TLabel
        Left = 8
        Top = 112
        Width = 187
        Height = 16
        Caption = 'Number of manufactor reset left:'
      end
      object Label8: TLabel
        Left = 8
        Top = 128
        Width = 117
        Height = 16
        Caption = 'Current region code'
      end
      object Label9: TLabel
        Left = 8
        Top = 64
        Width = 120
        Height = 16
        Caption = 'Drive region locked:'
      end
      object Label10: TLabel
        Left = 273
        Top = 64
        Width = 7
        Height = 16
        Alignment = taRightJustify
        Caption = '?'
      end
      object Label11: TLabel
        Left = 273
        Top = 80
        Width = 7
        Height = 16
        Alignment = taRightJustify
        Caption = '?'
      end
      object Label12: TLabel
        Left = 273
        Top = 96
        Width = 7
        Height = 16
        Alignment = taRightJustify
        Caption = '?'
      end
      object Label13: TLabel
        Left = 273
        Top = 112
        Width = 7
        Height = 16
        Alignment = taRightJustify
        Caption = '?'
      end
      object Label14: TLabel
        Left = 273
        Top = 128
        Width = 7
        Height = 16
        Alignment = taRightJustify
        Caption = '?'
      end
      object Label15: TLabel
        Left = 120
        Top = 152
        Width = 14
        Height = 16
        Alignment = taRightJustify
        Caption = '??'
        Visible = False
      end
      object Label16: TLabel
        Left = 264
        Top = 152
        Width = 14
        Height = 16
        Alignment = taRightJustify
        Caption = '??'
        Visible = False
      end
      object StaticText1: TStaticText
        Left = 8
        Top = 152
        Width = 110
        Height = 20
        Caption = 'CDR-read speed:'
        TabOrder = 0
        Visible = False
      end
      object StaticText2: TStaticText
        Left = 144
        Top = 152
        Width = 109
        Height = 20
        Caption = 'CDR-write speed:'
        TabOrder = 1
        Visible = False
      end
    end
    object ComboBox1: TComboBox
      Left = 24
      Top = 24
      Width = 297
      Height = 24
      Style = csDropDownList
      ItemHeight = 16
      TabOrder = 0
      OnChange = EditCompo
    end
  end
  object SaveDialog1: TSaveDialog
    DefaultExt = 'ifo'
    Filter = 'DVD/CD-Drive info|*.ifo'
    Left = 40
    Top = 65528
  end
  object MainMenu1: TMainMenu
    Left = 8
    Top = 65528
    object Files1: TMenuItem
      Caption = '&Files'
      object SaveInfo1: TMenuItem
        Caption = '&Save Info'
        OnClick = RunSaveDialog
      end
      object eXit1: TMenuItem
        Caption = 'E&xit'
        OnClick = eXit1Click
      end
    end
    object About1: TMenuItem
      Caption = '&About'
      OnClick = About1Click
    end
  end
end
