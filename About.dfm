object About_Box: TAbout_Box
  Left = 705
  Top = 177
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = 'About DVD-IDE-SCSI-CD Info Program'
  ClientHeight = 305
  ClientWidth = 434
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
    Width = 434
    Height = 305
    Align = alClient
    TabOrder = 0
    object GroupBox1: TGroupBox
      Left = 8
      Top = 8
      Width = 417
      Height = 289
      TabOrder = 0
      object BitBtn1: TBitBtn
        Left = 176
        Top = 240
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
        Top = 160
        Width = 401
        Height = 25
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
        Height = 113
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
        object Label10: TLabel
          Left = 4
          Top = 79
          Width = 377
          Height = 33
          AutoSize = False
          Caption = 
            'You can save all this information into a file. Send the file to ' +
            'me. I will use it to make a database of all the CD/DVD devices i' +
            'dentified by my program.'
          Font.Charset = EASTEUROPE_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          WordWrap = True
        end
      end
      object GroupBox2: TGroupBox
        Left = 8
        Top = 210
        Width = 161
        Height = 73
        Caption = ' Program Sponsored By: '
        TabOrder = 4
        object Image1: TImage
          Left = 9
          Top = 16
          Width = 145
          Height = 48
          Cursor = crHandPoint
          Hint = 'Your source of optical media supplies'
          HelpType = htKeyword
          Align = alCustom
          AutoSize = True
          Center = True
          ParentShowHint = False
          Picture.Data = {
            07544269746D6170B60E0000424DB60E00000000000076000000280000009100
            0000300000000100040000000000400E0000130B0000130B0000100000001000
            000099663300F9F5F20000CCFF00D0B7A000C3A68800A37446002FACC000E5D9
            CC00B18A6300737F6500F2EBE500DCCAB9001BBADB004C999900FFFFFF00608C
            7F00EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
            EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
            EEEEEEEEEEEEEEEEEEEEE0000000EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
            EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
            EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE0000000EEEEEEEEEEEE
            EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
            EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
            EEEEE0000000EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
            EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
            EEEEEEEEEEEEEEEEEEEEEEEEEEEEE0000000EEEEEEEEEEEEEEEEEEEEEEEEEEEE
            EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE111
            EEEEEEE111EEEEEEEE111EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE0000000EEEE
            EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
            EEEEEEEEEEEEEEEEEEEE1BB7EEEEEEE7771EEEEEE1BB7EEEEEEEEEEEEEEEEEEE
            EEEEEEEEEEEEE0000000EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
            EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE1BB7EEEEEEE7771EEEEE
            E1BB7EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE0000000EEEEEEEEEEEEEEEEEEEE
            EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
            EEEE1BB7EEEEEEE7771EEEEEE1BB7EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE000
            0000EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
            EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
            EEEEEEEEEEEEEEEEEEEEE0000000EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
            EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
            EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE0000000EEEEEEEEEEEE
            EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
            EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
            EEEEE0000000EEEEEEEAB33433BAEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
            EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
            884EEEEEEEEEEEEEEEEEEEEEEEEEE0000000EEEEEB5000000000083AEEEEEEEE
            EEEEEEEEEEEEEEEEE4EE8EE8E8EEEEEBAE4EE4EBBEEA88BEEEEE4A4BAE48BEE4
            EEE413EB43EEB3EABEE4E4EE488EEEEEA88AEE347EE4EEEEEEEEE0000000EEE1
            80000000000000008BEEEEEEEEEEEEEEEEEEEEEEE4884EE0E0EEEEE37E8EE815
            3EE51B8EEEEE83537E03BEE8EEE887E834EE37E73EE8E8EA818EEEEE87A3EE8E
            8EEEEEEEEEEEE0000000EE18000000000000000000531EEEEEEEEEEEEEEEEEEE
            E748AEE5B8EEEEE3888EE8833EE8E3BEEEEE88387E483EE0BEE88AE8B0EE83E7
            3EE5B8E18B4EEEEE8EEEEE5B5EEEEEEEEEEEE0000000EE300000000000000000
            000053EEEEEEEEEEEEEEEEEEEE88EEEAAAEEEEE37E8EE8873EE8B33EEEEE8875
            7EA7EEEA7EE81AE171EE4BEA7EEA71EEAAAEEEEE3334EE171EEEEEEEEEEEE000
            0000EE5000000000000000000000005BEEEEEEEEEEEEEEEEEE77EEEEEEEEEEE7
            AEBEEB1A7EE1331EEEEEB7E3AEEEEEEEEEEBEEEEEEEE11EA7EEEEEEEEEEEEEEE
            EB31EEEEEEEEEEEEEEEEE0000000EA0000000000000000000000000081EEEEEE
            EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
            EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE0000000E70000000000
            000000000000000005BEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
            EEEEEEEEEEEEEEE771EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
            EEEEE0000000E7000000000000000000000000000004EEEEEEEEEEEEEEEEEEEE
            EEEEEEEEEEEEEE4008EEEEEE8004EEEEEEEEEA0005BEEEEEEEEEEEEEEEEEEEEE
            EEEEEEEEEEEEEEEEEEEEEEEEEEEEE0000000E700000000000000000000000000
            000081EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE3005EEEEEE3005EEEEEEEEEE00
            000AEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE0000000E100
            000000000000000000000000000005AEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE70
            001EEEEE70001EEEEEEEEE778008EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
            EEEEEEEEEEEEE0000000EE805777777B380000377740004777777B4AEEEEEEEE
            EEEEE74858831E14583A888000B3854AE00073854A4883EEB000BEE400004400
            000004E4000000040000440000400004EEEEE0000000EE3001EEEEEEEEB500AE
            EE15008EEEEEEEE1AEEEEEEEEEEEB00000005A30000850080050000518005000
            054008EE30005EE0D66600FC222CF0409C222690F66600666F0966604EEEE000
            0000EEA007EEEEEEEEEB00EEEEEB005EEEEEEEEEE1EEEEEEEEE1500544500830
            004500080008B800440008B8008000EE800003E0D2220D22222226092222222F
            F2220062260022290EEEE0000000EEE403EEE805AEEE88EE1EEE500AEEA004EE
            EA1E73333AE7000BEEB0004000E15008000AE70003000AEB0000007E50850510
            92229C2269D2229C22696222922290D22C00C22D0EEEE0000000EEEA58EEE400
            8EEEB4EE77EE700BEEE000BEEE3E300003E1B33AE140003000AE40080007EE00
            0B000AEE0005003A008300340DDD9222900DDD9222900C22FC22D09222006226
            0EEEE0000000EEEE35EEE3000AEEE3EEB8EEE803EEE8005EEEB3A00004EEEEEA
            450005E000BEB0005003EE0007000BEE000800470031500A4000022290400002
            22900D22662260022290D22C04EEE0000000EEEEE8AEEA0003EEE7EE307EEA08
            EEE40001EE70AEEEEEEEE180000057E8003E10008005AA00078005AA00040053
            003E3004EEEE06226000999C22D00D226F22200C2260922250EEE0000000EEEE
            EA7EEE0003EEEEEE408EEE45EEEB0007EE708EEEEEEEE4000054AEE4008EE500
            800000005130000000570008003E15007EEE09222D9F222F222FFC22D9222CD2
            2226622290EEE0000000EEEEEEAEEE8003EEEEEE8007EEA5AEEA0001EEB007EE
            EEEEE500531A7EEB000EE40080088005BEB0088005BE0005007EE3008EEE40F2
            222222D06222222200222C2222C2222290EEE0000000EEEEEEEEEE3831EEAEEE
            5004EEE3BEEE88BEEE4008EEEEEEE5004EE4005EEEEEEEEEEEEEEA7EEEEEEEEA
            7EEE8003EEEEEEEEEEEEE4096222CF040FC22265006669622609C22D04EEE000
            0000EEEEEEEEEEEEEEEEBEEE0000AEE14EEEEEEEEA5000AEEEEEE3000880004E
            EEEEEEEEEEEEEEEEEEEEEEEEEEEE4008EEEEEEEEEEEEEE400000004E40000000
            44000000000000004EEEE0000000EEEEEEEEEEEEEE147EEA00004EEE7EEEEEEE
            7800004EEEEEEE400000081EEEEEEEEEEEEEEEEEEEEEEEEEEEEE3005EEEEEEEE
            EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE0000000EEEEEEEEEE38
            8800888800000888888888850000005EEEEEEEEA3333AEEEEEEEEEEEEEEEEEEE
            EEEEEEEEEEEE1777EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
            EEEEE0000000EEEEEEEEEEEB0000000000000000000000000000000EEEEEEEEE
            EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
            EEEEEEEEEEEEEEEEEEEEEEEEEEEEE0000000EEEEEEEEEEEE7500000000000000
            0000000000000007EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
            EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE0000000EEEE
            EEEEEEEEEA800000000000000000000000000007EEEEEEEEEEEEEEEEEEEEEEEE
            EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
            EEEEEEEEEEEEE0000000EEEEEEEEEEEEEEE3000000000000000000000000000A
            EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
            EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE0000000EEEEEEEEEEEEEEEEA800
            00000000000000000000005EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
            EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE000
            0000EEEEEEEEEEEEEEEEEEB500000000000000000000003EEEEEEEEEEEEEEEEE
            EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
            EEEEEEEEEEEEEEEEEEEEE0000000EEEEEEEEEEEEEEEEEEEEB500000000000000
            0000051EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
            EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE0000000EEEEEEEEEEEE
            EEEEEEEEEEB800000000000000005AEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
            EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
            EEEEE0000000EEEEEEEEEEEEEEEEEEEEEEEEA480000000000008AEEEEEEEEEEE
            EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
            EEEEEEEEEEEEEEEEEEEEEEEEEEEEE0000000EEEEEEEEEEEEEEEEEEEEEEEEEEEA
            B485000583AEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
            EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE0000000EEEE
            EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
            EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
            EEEEEEEEEEEEE0000000EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
            EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
            EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE0000000EEEEEEEEEEEEEEEEEEEE
            EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
            EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE000
            0000}
          Proportional = True
          ShowHint = True
          OnClick = Image1Click
        end
      end
    end
    object Panel5: TPanel
      Left = 16
      Top = 184
      Width = 401
      Height = 33
      BevelInner = bvSpace
      BevelOuter = bvLowered
      TabOrder = 1
      object Label9: TLabel
        Left = 50
        Top = 17
        Width = 151
        Height = 13
        AutoSize = False
        Caption = 'nicw and all the testers on the'
        Font.Charset = EASTEUROPE_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object Label8: TLabel
        Left = 202
        Top = 17
        Width = 94
        Height = 13
        Cursor = crHandPoint
        Hint = 'visit the main firmware page'
        Caption = 'main firmware page'
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
        Width = 325
        Height = 13
        Caption = 'XVI,  Arzeno, >NIL:, dhc014, FLASHMAN, Cigo, Klaus Jensen, Paul,'
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