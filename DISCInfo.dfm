object Form1: TForm1
  Left = 753
  Top = 44
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'Toshiba Revision Check 2.0'
  ClientHeight = 309
  ClientWidth = 298
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 298
    Height = 309
    Align = alClient
    TabOrder = 0
    object GroupBox1: TGroupBox
      Left = 8
      Top = 8
      Width = 281
      Height = 273
      TabOrder = 0
      object GroupBox2: TGroupBox
        Left = 8
        Top = 48
        Width = 265
        Height = 217
        TabOrder = 0
        object xtest: TLabel
          Left = 200
          Top = 24
          Width = 32
          Height = 13
          Caption = 'Kr neki'
          Font.Charset = EASTEUROPE_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
        end
      end
    end
  end
  object MainMenu1: TMainMenu
    Left = 264
    Top = 32
    object File1: TMenuItem
      Caption = 'File'
      object SaveToFile1: TMenuItem
        Caption = 'Save To File'
      end
      object Exit1: TMenuItem
        Caption = 'Exit'
        OnClick = Exit1Click
      end
    end
    object About1: TMenuItem
      Caption = 'About'
    end
  end
end
