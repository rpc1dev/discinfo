object About_Box: TAbout_Box
  Left = 417
  Top = 157
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = 'About DVD-IDE-SCSI-CD Info Program'
  ClientHeight = 240
  ClientWidth = 431
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  Scaled = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 431
    Height = 240
    Align = alClient
    TabOrder = 0
    object GroupBox1: TGroupBox
      Left = 8
      Top = 8
      Width = 417
      Height = 225
      TabOrder = 0
      object BitBtn1: TBitBtn
        Left = 168
        Top = 192
        Width = 75
        Height = 25
        Font.Charset = EASTEUROPE_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
        OnKeyPress = BitBtn1KeyPress
        Kind = bkOK
      end
      object Panel2: TPanel
        Left = 8
        Top = 128
        Width = 401
        Height = 17
        BevelInner = bvSpace
        BevelOuter = bvLowered
        TabOrder = 1
        object Label6: TLabel
          Left = 4
          Top = 2
          Width = 42
          Height = 13
          Caption = 'Author:'
          Font.Charset = EASTEUROPE_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label3: TLabel
          Left = 52
          Top = 2
          Width = 38
          Height = 13
          Cursor = crHandPoint
          Hint = 'email the author'
          Caption = 'Hijacker'
          Font.Charset = EASTEUROPE_CHARSET
          Font.Color = clBlue
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
          WordWrap = True
          OnClick = Label3Click
        end
      end
      object Panel3: TPanel
        Left = 8
        Top = 12
        Width = 401
        Height = 25
        BevelInner = bvLowered
        TabOrder = 2
        object Label5: TLabel
          Left = 4
          Top = 3
          Width = 392
          Height = 23
          Cursor = crHandPoint
          Hint = 'visit the homepage of DISCInfo'
          Alignment = taCenter
          AutoSize = False
          Caption = 'DISC Info 9.9.9'
          Font.Charset = EASTEUROPE_CHARSET
          Font.Color = clBlue
          Font.Height = -15
          Font.Name = 'Verdana'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
          Transparent = True
          OnClick = Label5Click
        end
      end
      object Panel4: TPanel
        Left = 8
        Top = 42
        Width = 401
        Height = 79
        BevelOuter = bvLowered
        TabOrder = 3
        object Label1: TLabel
          Left = 5
          Top = 3
          Width = 392
          Height = 32
          AutoSize = False
          Caption = 
            'This program will show information about any IDE/SCSI device ext' +
            'racted from inside the drive. You can even see what the device i' +
            's capable of reading/writing.'
          Font.Charset = EASTEUROPE_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          WordWrap = True
        end
        object Label2: TLabel
          Left = 4
          Top = 35
          Width = 389
          Height = 40
          AutoSize = False
          Caption = 
            'Above all that it can also show you the DVD drive region status.' +
            ' You can see if your drive is region free (RPC-1) and current re' +
            'gion settings if the drive is region protected (RPC-2).'
          Font.Charset = EASTEUROPE_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          WordWrap = True
        end
      end
    end
    object Panel5: TPanel
      Left = 16
      Top = 159
      Width = 401
      Height = 33
      BevelInner = bvSpace
      BevelOuter = bvLowered
      TabOrder = 1
      object Label9: TLabel
        Left = 50
        Top = 17
        Width = 199
        Height = 13
        AutoSize = False
        Caption = 'nicw, Toshibaer and all the testers on the'
        Font.Charset = EASTEUROPE_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object Label8: TLabel
        Left = 252
        Top = 17
        Width = 98
        Height = 13
        Cursor = crHandPoint
        Hint = 'visit the main firmware page'
        Caption = 'main firmware page.'
        Font.Charset = EASTEUROPE_CHARSET
        Font.Color = clBlue
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        ParentShowHint = False
        ShowHint = True
        OnClick = Label8Click
      end
      object Label7: TLabel
        Left = 4
        Top = 4
        Width = 43
        Height = 13
        Caption = 'Credits:'
        Font.Charset = EASTEUROPE_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label4: TLabel
        Left = 51
        Top = 4
        Width = 322
        Height = 13
        Caption = 'XVI, Arzeno, >NIL:, dhc014, FLASHMAN, Cigo, Klaus Jensen, Paul,'
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
