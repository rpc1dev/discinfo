object Extra_Box: TExtra_Box
  Left = 839
  Top = 196
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'Capabilities Information'
  ClientHeight = 463
  ClientWidth = 305
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Extra_Panel: TPanel
    Left = 0
    Top = 0
    Width = 305
    Height = 463
    Align = alClient
    Font.Charset = EASTEUROPE_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 0
    object CD_DVD_Name: TPanel
      Left = 16
      Top = 8
      Width = 273
      Height = 25
      Font.Charset = EASTEUROPE_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      object l_name: TLabel
        Left = 8
        Top = 6
        Width = 257
        Height = 13
        Alignment = taCenter
        AutoSize = False
        Caption = 'TOSHIBA DVD-ROM SD-M1712'
      end
    end
    object Close: TBitBtn
      Left = 168
      Top = 432
      Width = 107
      Height = 25
      Caption = '&Close'
      Font.Charset = EASTEUROPE_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ModalResult = 2
      ParentFont = False
      TabOrder = 1
      OnClick = CloseClick
      OnKeyPress = CloseKeyPress
      Glyph.Data = {
        DE010000424DDE01000000000000760000002800000024000000120000000100
        0400000000006801000000000000000000001000000000000000000000000000
        80000080000000808000800000008000800080800000C0C0C000808080000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00388888888877
        F7F787F8888888888333333F00004444400888FFF444448888888888F333FF8F
        000033334D5007FFF4333388888888883338888F0000333345D50FFFF4333333
        338F888F3338F33F000033334D5D0FFFF43333333388788F3338F33F00003333
        45D50FEFE4333333338F878F3338F33F000033334D5D0FFFF43333333388788F
        3338F33F0000333345D50FEFE4333333338F878F3338F33F000033334D5D0FFF
        F43333333388788F3338F33F0000333345D50FEFE4333333338F878F3338F33F
        000033334D5D0EFEF43333333388788F3338F33F0000333345D50FEFE4333333
        338F878F3338F33F000033334D5D0EFEF43333333388788F3338F33F00003333
        4444444444333333338F8F8FFFF8F33F00003333333333333333333333888888
        8888333F00003333330000003333333333333FFFFFF3333F00003333330AAAA0
        333333333333888888F3333F00003333330000003333333333338FFFF8F3333F
        0000}
      NumGlyphs = 2
    end
    object Read_Info: TGroupBox
      Left = 16
      Top = 272
      Width = 273
      Height = 73
      Caption = 'Read Capabilities'
      Font.Charset = EASTEUROPE_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      object Label1: TLabel
        Left = 8
        Top = 16
        Width = 25
        Height = 13
        Caption = 'CD-R'
        ParentShowHint = False
        ShowHint = True
      end
      object Label2: TLabel
        Left = 8
        Top = 32
        Width = 35
        Height = 13
        Caption = 'CD-RW'
        ParentShowHint = False
        ShowHint = True
      end
      object Label3: TLabel
        Left = 8
        Top = 48
        Width = 45
        Height = 13
        Caption = 'Method 2'
        ParentShowHint = False
        ShowHint = True
      end
      object Label5: TLabel
        Left = 96
        Top = 16
        Width = 47
        Height = 13
        Caption = 'DVD-ROM'
        ParentShowHint = False
        ShowHint = True
      end
      object Label6: TLabel
        Left = 184
        Top = 16
        Width = 46
        Height = 13
        Caption = 'DVD-RAM'
        ParentShowHint = False
        ShowHint = True
      end
      object Label7: TLabel
        Left = 96
        Top = 32
        Width = 31
        Height = 13
        Caption = 'DVD-R'
        ParentShowHint = False
        ShowHint = True
      end
      object Label13: TLabel
        Left = 96
        Top = 48
        Width = 41
        Height = 13
        Caption = 'DVD-RW'
        ParentShowHint = False
        ShowHint = True
      end
      object Label14: TLabel
        Left = 184
        Top = 32
        Width = 35
        Height = 13
        Caption = 'DVD+R'
        ParentShowHint = False
        ShowHint = True
      end
      object Label15: TLabel
        Left = 184
        Top = 48
        Width = 45
        Height = 13
        Caption = 'DVD+RW'
        ParentShowHint = False
        ShowHint = True
      end
      object r_cdr: TCheckBox
        Left = 64
        Top = 16
        Width = 17
        Height = 17
        TabOrder = 0
        OnKeyDown = r_cdrKeyDown
        OnMouseDown = r_cdrMouseDown
      end
      object r_cdrw: TCheckBox
        Left = 64
        Top = 32
        Width = 17
        Height = 17
        TabOrder = 1
        OnKeyDown = r_cdrKeyDown
        OnMouseDown = r_cdrMouseDown
      end
      object r_m2: TCheckBox
        Left = 64
        Top = 48
        Width = 17
        Height = 17
        TabOrder = 2
        OnKeyDown = r_cdrKeyDown
        OnMouseDown = r_cdrMouseDown
      end
      object r_dvdrom: TCheckBox
        Left = 152
        Top = 16
        Width = 17
        Height = 17
        TabOrder = 3
        OnKeyDown = r_cdrKeyDown
        OnMouseDown = r_cdrMouseDown
      end
      object r_dvdram: TCheckBox
        Left = 240
        Top = 16
        Width = 17
        Height = 17
        TabOrder = 4
        OnKeyDown = r_cdrKeyDown
        OnMouseDown = r_cdrMouseDown
      end
      object r_dvdr: TCheckBox
        Left = 152
        Top = 32
        Width = 17
        Height = 17
        TabOrder = 5
        OnKeyDown = r_cdrKeyDown
        OnMouseDown = r_cdrMouseDown
      end
      object r_dvdrw: TCheckBox
        Left = 152
        Top = 48
        Width = 17
        Height = 17
        TabOrder = 6
        OnKeyDown = r_cdrKeyDown
        OnMouseDown = r_cdrMouseDown
      end
      object r_dvdpr: TCheckBox
        Left = 240
        Top = 32
        Width = 17
        Height = 17
        TabOrder = 7
        OnKeyDown = r_cdrKeyDown
        OnMouseDown = r_cdrMouseDown
      end
      object r_dvdprw: TCheckBox
        Left = 240
        Top = 48
        Width = 17
        Height = 17
        TabOrder = 8
        OnKeyDown = r_cdrKeyDown
        OnMouseDown = r_cdrMouseDown
      end
    end
    object Write_Info: TGroupBox
      Left = 16
      Top = 352
      Width = 273
      Height = 73
      Caption = 'Write Capabilities'
      Font.Charset = EASTEUROPE_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      object Label8: TLabel
        Left = 8
        Top = 16
        Width = 25
        Height = 13
        Caption = 'CD-R'
        ParentShowHint = False
        ShowHint = True
      end
      object Label9: TLabel
        Left = 8
        Top = 32
        Width = 35
        Height = 13
        Caption = 'CD-RW'
        ParentShowHint = False
        ShowHint = True
      end
      object Label10: TLabel
        Left = 96
        Top = 16
        Width = 31
        Height = 13
        Caption = 'DVD-R'
        ParentShowHint = False
        ShowHint = True
      end
      object Label11: TLabel
        Left = 96
        Top = 48
        Width = 46
        Height = 13
        Caption = 'DVD-RAM'
        ParentShowHint = False
        ShowHint = True
      end
      object Label4: TLabel
        Left = 96
        Top = 32
        Width = 41
        Height = 13
        Caption = 'DVD-RW'
        ParentShowHint = False
        ShowHint = True
      end
      object Label12: TLabel
        Left = 8
        Top = 48
        Width = 50
        Height = 13
        Caption = 'Test Write'
        ParentShowHint = False
        ShowHint = True
      end
      object Label16: TLabel
        Left = 184
        Top = 16
        Width = 35
        Height = 13
        Caption = 'DVD+R'
        ParentShowHint = False
        ShowHint = True
      end
      object Label17: TLabel
        Left = 184
        Top = 32
        Width = 45
        Height = 13
        Caption = 'DVD+RW'
        ParentShowHint = False
        ShowHint = True
      end
      object w_cdr: TCheckBox
        Left = 64
        Top = 16
        Width = 17
        Height = 17
        TabOrder = 0
        OnKeyDown = r_cdrKeyDown
        OnMouseDown = r_cdrMouseDown
      end
      object w_cdrw: TCheckBox
        Left = 64
        Top = 32
        Width = 17
        Height = 17
        TabOrder = 1
        OnKeyDown = r_cdrKeyDown
        OnMouseDown = r_cdrMouseDown
      end
      object w_dvdr: TCheckBox
        Left = 152
        Top = 16
        Width = 17
        Height = 17
        TabOrder = 2
        OnKeyDown = r_cdrKeyDown
        OnMouseDown = r_cdrMouseDown
      end
      object w_dvdram: TCheckBox
        Left = 152
        Top = 48
        Width = 17
        Height = 17
        TabOrder = 3
        OnKeyDown = r_cdrKeyDown
        OnMouseDown = r_cdrMouseDown
      end
      object w_dvdrw: TCheckBox
        Left = 152
        Top = 32
        Width = 17
        Height = 17
        TabOrder = 4
        OnKeyDown = r_cdrKeyDown
        OnMouseDown = r_cdrMouseDown
      end
      object w_test: TCheckBox
        Left = 64
        Top = 48
        Width = 17
        Height = 17
        TabOrder = 5
        OnKeyDown = r_cdrKeyDown
        OnMouseDown = r_cdrMouseDown
      end
      object w_dvdpr: TCheckBox
        Left = 240
        Top = 16
        Width = 17
        Height = 17
        TabOrder = 6
        OnKeyDown = r_cdrKeyDown
        OnMouseDown = r_cdrMouseDown
      end
      object w_dvdprw: TCheckBox
        Left = 240
        Top = 32
        Width = 17
        Height = 17
        TabOrder = 7
        OnKeyDown = r_cdrKeyDown
        OnMouseDown = r_cdrMouseDown
      end
    end
    object GroupBox1: TGroupBox
      Left = 16
      Top = 35
      Width = 273
      Height = 105
      Caption = 'General'
      Font.Charset = EASTEUROPE_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 4
      object SNText: TLabel
        Left = 8
        Top = 16
        Width = 69
        Height = 13
        Caption = 'Serial number:'
        ParentShowHint = False
        ShowHint = True
      end
      object LevelText: TLabel
        Left = 8
        Top = 64
        Width = 121
        Height = 13
        Caption = 'Number of volume levels:'
        ParentShowHint = False
        ShowHint = True
      end
      object BufferText: TLabel
        Left = 8
        Top = 80
        Width = 55
        Height = 13
        Caption = 'Buffer size:'
        ParentShowHint = False
        ShowHint = True
      end
      object SerialNum: TLabel
        Left = 120
        Top = 16
        Width = 141
        Height = 13
        Alignment = taRightJustify
        AutoSize = False
        Caption = 'n/a'
      end
      object VolumeLevel: TLabel
        Left = 168
        Top = 64
        Width = 93
        Height = 13
        Alignment = taRightJustify
        AutoSize = False
        Caption = 'n/a'
      end
      object BufferSize: TLabel
        Left = 168
        Top = 80
        Width = 93
        Height = 13
        Alignment = taRightJustify
        AutoSize = False
        Caption = 'n/a'
      end
      object Label30: TLabel
        Left = 8
        Top = 48
        Width = 121
        Height = 13
        Caption = 'Loading mechanism type:'
        ParentShowHint = False
        ShowHint = True
      end
      object Mechanism: TLabel
        Left = 168
        Top = 48
        Width = 93
        Height = 13
        Alignment = taRightJustify
        AutoSize = False
        Caption = 'n/a'
      end
      object Label31: TLabel
        Left = 8
        Top = 32
        Width = 49
        Height = 13
        Caption = 'Interface:'
        ParentShowHint = False
        ShowHint = True
      end
      object Interface: TLabel
        Left = 168
        Top = 32
        Width = 93
        Height = 13
        Alignment = taRightJustify
        AutoSize = False
        Caption = 'n/a'
      end
    end
    object GroupBox2: TGroupBox
      Left = 16
      Top = 144
      Width = 273
      Height = 121
      Caption = 'Supported features'
      Font.Charset = EASTEUROPE_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 5
      object Label18: TLabel
        Left = 8
        Top = 16
        Width = 86
        Height = 13
        Caption = 'Analog Audio Play'
        ParentShowHint = False
        ShowHint = True
      end
      object Label19: TLabel
        Left = 8
        Top = 32
        Width = 87
        Height = 13
        Caption = 'Composite Output'
        ParentShowHint = False
        ShowHint = True
      end
      object Label20: TLabel
        Left = 8
        Top = 48
        Width = 101
        Height = 13
        Caption = 'Digital Port On Port 1'
        ParentShowHint = False
        ShowHint = True
      end
      object Label21: TLabel
        Left = 8
        Top = 64
        Width = 101
        Height = 13
        Caption = 'Digital Port On Port 2'
        ParentShowHint = False
        ShowHint = True
      end
      object Label22: TLabel
        Left = 144
        Top = 32
        Width = 71
        Height = 13
        Caption = 'Mode 2 Form 1'
        ParentShowHint = False
        ShowHint = True
      end
      object Label23: TLabel
        Left = 144
        Top = 48
        Width = 71
        Height = 13
        Caption = 'Mode 2 Form 2'
        ParentShowHint = False
        ShowHint = True
      end
      object Label24: TLabel
        Left = 144
        Top = 16
        Width = 85
        Height = 13
        Caption = 'Multisession Read'
        ParentShowHint = False
        ShowHint = True
      end
      object Label25: TLabel
        Left = 144
        Top = 64
        Width = 52
        Height = 13
        Caption = 'ISRC Read'
        ParentShowHint = False
        ShowHint = True
      end
      object Label26: TLabel
        Left = 8
        Top = 80
        Width = 48
        Height = 13
        Caption = 'UPC Read'
        ParentShowHint = False
        ShowHint = True
      end
      object Label27: TLabel
        Left = 144
        Top = 80
        Width = 72
        Height = 13
        Caption = 'Bar Code Read'
        ParentShowHint = False
        ShowHint = True
      end
      object Label28: TLabel
        Left = 8
        Top = 96
        Width = 82
        Height = 13
        Caption = 'Buffer Under-run'
        ParentShowHint = False
        ShowHint = True
      end
      object Label29: TLabel
        Left = 144
        Top = 96
        Width = 52
        Height = 13
        Caption = 'Mt. Rainier'
        ParentShowHint = False
        ShowHint = True
      end
      object AudioPlay: TCheckBox
        Left = 120
        Top = 16
        Width = 17
        Height = 17
        TabOrder = 0
        OnKeyDown = r_cdrKeyDown
        OnMouseDown = r_cdrMouseDown
      end
      object Composite: TCheckBox
        Left = 120
        Top = 32
        Width = 17
        Height = 17
        TabOrder = 1
        OnKeyDown = r_cdrKeyDown
        OnMouseDown = r_cdrMouseDown
      end
      object Digiport1: TCheckBox
        Left = 120
        Top = 48
        Width = 17
        Height = 17
        TabOrder = 2
        OnKeyDown = r_cdrKeyDown
        OnMouseDown = r_cdrMouseDown
      end
      object Digiport2: TCheckBox
        Left = 120
        Top = 64
        Width = 17
        Height = 17
        TabOrder = 3
        OnKeyDown = r_cdrKeyDown
        OnMouseDown = r_cdrMouseDown
      end
      object upcread: TCheckBox
        Left = 120
        Top = 80
        Width = 17
        Height = 17
        TabOrder = 4
        OnKeyDown = r_cdrKeyDown
        OnMouseDown = r_cdrMouseDown
      end
      object BufferUnder: TCheckBox
        Left = 120
        Top = 96
        Width = 17
        Height = 17
        TabOrder = 5
        OnKeyDown = r_cdrKeyDown
        OnMouseDown = r_cdrMouseDown
      end
      object Multisession: TCheckBox
        Left = 248
        Top = 16
        Width = 17
        Height = 17
        TabOrder = 6
        OnKeyDown = r_cdrKeyDown
        OnMouseDown = r_cdrMouseDown
      end
      object Mode2F1: TCheckBox
        Left = 248
        Top = 32
        Width = 17
        Height = 17
        TabOrder = 7
        OnKeyDown = r_cdrKeyDown
        OnMouseDown = r_cdrMouseDown
      end
      object Mode2F2: TCheckBox
        Left = 248
        Top = 48
        Width = 17
        Height = 17
        TabOrder = 8
        OnKeyDown = r_cdrKeyDown
        OnMouseDown = r_cdrMouseDown
      end
      object isrc: TCheckBox
        Left = 248
        Top = 64
        Width = 17
        Height = 17
        TabOrder = 9
        OnKeyDown = r_cdrKeyDown
        OnMouseDown = r_cdrMouseDown
      end
      object BarCode: TCheckBox
        Left = 248
        Top = 80
        Width = 17
        Height = 17
        TabOrder = 10
        OnKeyDown = r_cdrKeyDown
        OnMouseDown = r_cdrMouseDown
      end
      object mtrainier: TCheckBox
        Left = 248
        Top = 96
        Width = 17
        Height = 17
        TabOrder = 11
        OnKeyDown = r_cdrKeyDown
        OnMouseDown = r_cdrMouseDown
      end
    end
    object Button1: TButton
      Left = 40
      Top = 432
      Width = 105
      Height = 25
      Caption = 'Take Screenshot'
      Font.Charset = EASTEUROPE_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 6
      OnClick = Button1Click
    end
  end
end
