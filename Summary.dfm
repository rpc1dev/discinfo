object SumInfo: TSumInfo
  Left = 785
  Top = 144
  BorderStyle = bsSingle
  Caption = 'CD/DVD Summary'
  ClientHeight = 313
  ClientWidth = 360
  Color = clBtnFace
  Font.Charset = EASTEUROPE_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 360
    Height = 313
    Align = alClient
    TabOrder = 0
    object GroupBox1: TGroupBox
      Left = 8
      Top = 8
      Width = 345
      Height = 297
      Caption = ' CD/DVD Summary Page '
      TabOrder = 0
      object SumText: TMemo
        Left = 8
        Top = 16
        Width = 329
        Height = 241
        Color = clWhite
        Font.Charset = EASTEUROPE_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Courier New'
        Font.Style = []
        ParentFont = False
        ReadOnly = True
        ScrollBars = ssBoth
        TabOrder = 0
        WordWrap = False
        OnKeyPress = SumTextKeyPress
      end
      object Clipboard: TBitBtn
        Left = 32
        Top = 264
        Width = 121
        Height = 25
        Caption = 'Copy All To Clipboard'
        TabOrder = 1
        OnClick = ClipboardClick
      end
      object Close: TBitBtn
        Left = 192
        Top = 264
        Width = 121
        Height = 25
        TabOrder = 2
        Kind = bkClose
      end
    end
  end
end
