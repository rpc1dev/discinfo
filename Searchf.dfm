object Search_Box: TSearch_Box
  Left = 655
  Top = 184
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Search for updates'
  ClientHeight = 244
  ClientWidth = 305
  Color = clBtnFace
  Font.Charset = EASTEUROPE_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object MainPanel: TPanel
    Left = 0
    Top = 0
    Width = 305
    Height = 244
    Align = alClient
    TabOrder = 0
    object DriveName: TPanel
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
      object TheName: TLabel
        Left = 8
        Top = 6
        Width = 257
        Height = 13
        Alignment = taCenter
        AutoSize = False
        Caption = 'TOSHIBA DVD-ROM SD-M1712'
      end
    end
    object GroupOkno: TGroupBox
      Left = 16
      Top = 120
      Width = 273
      Height = 81
      Caption = ' Search options '
      TabOrder = 1
      object Label2: TLabel
        Left = 56
        Top = 24
        Width = 41
        Height = 13
        Alignment = taRightJustify
        AutoSize = False
        Caption = 'Vendor:'
      end
      object Label3: TLabel
        Left = 56
        Top = 48
        Width = 41
        Height = 13
        Alignment = taRightJustify
        AutoSize = False
        Caption = 'Model:'
      end
      object VendorBox: TCheckBox
        Left = 104
        Top = 24
        Width = 129
        Height = 17
        Caption = 'TOSHIBA'
        TabOrder = 0
        OnKeyPress = VendorBoxKeyPress
      end
      object ModelBox: TCheckBox
        Left = 104
        Top = 48
        Width = 121
        Height = 17
        Caption = 'SD-M1712'
        Checked = True
        State = cbChecked
        TabOrder = 1
        OnKeyPress = ModelBoxKeyPress
      end
    end
    object SrchButton: TBitBtn
      Left = 64
      Top = 208
      Width = 75
      Height = 25
      Caption = '&Search'
      Default = True
      TabOrder = 2
      OnClick = SrchButtonClick
      OnKeyPress = SrchButtonKeyPress
      Glyph.Data = {
        DE010000424DDE01000000000000760000002800000024000000120000000100
        0400000000006801000000000000000000001000000000000000000000000000
        80000080000000808000800000008000800080800000C0C0C000808080000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
        3333333333333333333333330000333333333333333333333333F33333333333
        00003333344333333333333333388F3333333333000033334224333333333333
        338338F3333333330000333422224333333333333833338F3333333300003342
        222224333333333383333338F3333333000034222A22224333333338F338F333
        8F33333300003222A3A2224333333338F3838F338F33333300003A2A333A2224
        33333338F83338F338F33333000033A33333A222433333338333338F338F3333
        0000333333333A222433333333333338F338F33300003333333333A222433333
        333333338F338F33000033333333333A222433333333333338F338F300003333
        33333333A222433333333333338F338F00003333333333333A22433333333333
        3338F38F000033333333333333A223333333333333338F830000333333333333
        333A333333333333333338330000333333333333333333333333333333333333
        0000}
      NumGlyphs = 2
    end
    object TextPanel: TPanel
      Left = 16
      Top = 40
      Width = 273
      Height = 73
      BevelOuter = bvLowered
      TabOrder = 3
      object Label1: TLabel
        Left = 8
        Top = 8
        Width = 257
        Height = 57
        AutoSize = False
        Caption = 
          'This section will search for the drives firmware updates on the ' +
          'firmware page. Just select what you wish to search.  My advise i' +
          's to search only by model. Please do not search info about Virtu' +
          'al Drives!'
        WordWrap = True
      end
    end
    object CloseBtn: TBitBtn
      Left = 160
      Top = 208
      Width = 75
      Height = 25
      TabOrder = 4
      OnClick = CloseBtnClick
      OnKeyPress = CloseBtnKeyPress
      Kind = bkClose
    end
  end
end
