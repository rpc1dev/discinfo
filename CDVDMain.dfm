object Main_Form: TMain_Form
  Left = 694
  Top = 355
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'DISCInfo 1.X.X'
  ClientHeight = 251
  ClientWidth = 294
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poScreenCenter
  OnResize = FormResize
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 294
    Height = 251
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 0
    object GroupBox1: TGroupBox
      Left = 8
      Top = 8
      Width = 281
      Height = 233
      TabOrder = 0
      object GroupBox2: TGroupBox
        Left = 8
        Top = 40
        Width = 265
        Height = 185
        TabOrder = 0
        object fw_version: TLabel
          Left = 15
          Top = 16
          Width = 95
          Height = 14
          Caption = 'Firmware version:'
          Font.Charset = EASTEUROPE_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
        end
        object fw_date: TLabel
          Left = 15
          Top = 32
          Width = 87
          Height = 14
          Caption = 'Vendor specific:'
          Font.Charset = EASTEUROPE_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
        end
        object specific: TLabel
          Left = 16
          Top = 48
          Width = 56
          Height = 14
          Caption = 'Extra info:'
          Font.Charset = EASTEUROPE_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
        end
        object region_status: TLabel
          Left = 16
          Top = 80
          Width = 106
          Height = 14
          Caption = 'Drive region status:'
          Font.Charset = EASTEUROPE_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
        end
        object version: TLabel
          Left = 208
          Top = 16
          Width = 44
          Height = 14
          Alignment = taRightJustify
          AutoSize = False
          Caption = '9999'
          Font.Charset = EASTEUROPE_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          OnDblClick = versionDblClick
        end
        object date: TLabel
          Left = 112
          Top = 32
          Width = 140
          Height = 14
          Alignment = taRightJustify
          AutoSize = False
          Caption = '99/99/99'
          Font.Charset = EASTEUROPE_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
        end
        object specific_d: TLabel
          Left = 16
          Top = 63
          Width = 234
          Height = 17
          Alignment = taCenter
          AutoSize = False
          Caption = 'Name Of Actual Toshiba Model'
          Font.Charset = EASTEUROPE_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
        end
        object status_rpc: TLabel
          Left = 133
          Top = 80
          Width = 118
          Height = 14
          Alignment = taRightJustify
          Caption = '(No) Lock Detected'
          Font.Charset = EASTEUROPE_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object reg_status: TLabel
          Left = 16
          Top = 96
          Width = 120
          Height = 14
          Caption = 'Region setting status:'
          Font.Charset = EASTEUROPE_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
        end
        object permanent_status: TLabel
          Left = 158
          Top = 96
          Width = 94
          Height = 14
          Alignment = taRightJustify
          Caption = '(Not Permanent)'
          Font.Charset = EASTEUROPE_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
        end
        object changes_left: TLabel
          Left = 16
          Top = 112
          Width = 99
          Height = 14
          Caption = 'User changes left:'
          Font.Charset = EASTEUROPE_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
        end
        object manuf_left: TLabel
          Left = 16
          Top = 128
          Width = 124
          Height = 14
          Caption = 'Manufactor resets left:'
          Font.Charset = EASTEUROPE_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
        end
        object region_set: TLabel
          Left = 16
          Top = 144
          Width = 135
          Height = 14
          Caption = 'Current region code set:'
          Font.Charset = EASTEUROPE_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
        end
        object fw_code: TLabel
          Left = 112
          Top = 48
          Width = 140
          Height = 14
          Alignment = taRightJustify
          AutoSize = False
          Caption = 'XX'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
        end
        object change_data: TLabel
          Left = 216
          Top = 112
          Width = 35
          Height = 14
          Alignment = taRightJustify
          AutoSize = False
          Caption = '9'
          Font.Charset = EASTEUROPE_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
        end
        object man_data: TLabel
          Left = 216
          Top = 128
          Width = 35
          Height = 14
          Alignment = taRightJustify
          AutoSize = False
          Caption = '9'
          Font.Charset = EASTEUROPE_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
        end
        object set_data: TLabel
          Left = 152
          Top = 144
          Width = 99
          Height = 14
          Alignment = taRightJustify
          AutoSize = False
          Caption = 'none'
          Font.Charset = EASTEUROPE_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
        end
        object read_s: TLabel
          Left = 16
          Top = 160
          Width = 68
          Height = 14
          Caption = 'Read speed:'
          Font.Charset = EASTEUROPE_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
        end
        object write_s: TLabel
          Left = 155
          Top = 160
          Width = 71
          Height = 14
          Caption = 'Write speed:'
          Font.Charset = EASTEUROPE_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
        end
        object readval: TLabel
          Left = 89
          Top = 160
          Width = 18
          Height = 14
          Alignment = taRightJustify
          Caption = '??x'
          Font.Charset = EASTEUROPE_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
        end
        object writeval: TLabel
          Left = 232
          Top = 160
          Width = 18
          Height = 14
          Alignment = taRightJustify
          Caption = '??x'
          Font.Charset = EASTEUROPE_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
        end
      end
      object ComboBox: TComboBox
        Left = 8
        Top = 16
        Width = 265
        Height = 24
        Style = csDropDownList
        Font.Charset = EASTEUROPE_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = []
        ItemHeight = 16
        ParentFont = False
        TabOrder = 1
        OnChange = ComboBoxChange
        OnKeyPress = ComboBoxKeyPress
      end
    end
  end
  object MainMenu1: TMainMenu
    BiDiMode = bdLeftToRight
    ParentBiDiMode = False
    Left = 264
    object File1: TMenuItem
      Caption = 'File'
      object SaveData1: TMenuItem
        Caption = '&Save CD/DVD Info'
        ShortCut = 16467
        OnClick = SaveData1Click
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object Exit1: TMenuItem
        Caption = 'Exit'
        ShortCut = 16472
        OnClick = Exit1Click
      end
    end
    object View1: TMenuItem
      Caption = 'View'
      object Displayotherdevices1: TMenuItem
        Caption = 'Show All &Devices'
        ShortCut = 16452
        OnClick = Displayotherdevices1Click
      end
      object ExtraInfo1: TMenuItem
        Caption = '&Capabilities Info'
        ShortCut = 16451
        OnClick = ExtraInfo1Click
      end
      object CopyToClipboard1: TMenuItem
        Caption = 'Show Sum&mary'
        ShortCut = 16457
        OnClick = CopyToClipboard1Click
      end
      object Firmwareupdates1: TMenuItem
        Caption = '&Firmware Updates'
        ShortCut = 16454
        OnClick = Firmwareupdates1Click
      end
    end
    object Options1: TMenuItem
      Caption = 'Access Driver'
      object ASPI1: TMenuItem
        Caption = 'ASPI (Win9x/Me)'
        OnClick = ASPI1Click
      end
      object SPTI1: TMenuItem
        Caption = 'SPTI (WinNT/2k/XP)'
        OnClick = SPTI1Click
      end
      object N2: TMenuItem
        Caption = '-'
      end
      object Resfresh1: TMenuItem
        Caption = 'Refresh current'
        OnClick = Resfresh1Click
      end
    end
    object About1: TMenuItem
      Caption = '&About'
      ShortCut = 16449
      OnClick = About1Click
    end
  end
  object SaveDialog: TSaveDialog
    DefaultExt = 'hif'
    Filter = 'CD/DVD Info File|*.hif'
    Options = [ofOverwritePrompt, ofHideReadOnly, ofEnableSizing]
    Title = 'Save the CD/DVD informations into a file'
    Left = 232
  end
end
