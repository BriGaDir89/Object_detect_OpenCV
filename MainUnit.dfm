object FormMain: TFormMain
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = #1044#1077#1090#1077#1082#1090#1086#1088' '#1086#1073#1098#1077#1082#1090#1086#1074
  ClientHeight = 496
  ClientWidth = 895
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Arial'
  Font.Style = []
  Menu = MainMenu
  OldCreateOrder = False
  Position = poMainFormCenter
  PrintScale = poPrintToFit
  OnClose = FormClose
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 15
  object Label1: TLabel
    Left = 8
    Top = 8
    Width = 251
    Height = 15
    Caption = #1042#1099#1073#1077#1088#1080#1090#1077' '#1090#1080#1087' '#1086#1073#1098#1077#1082#1090#1072' '#1076#1083#1103' '#1076#1077#1090#1077#1082#1090#1080#1088#1086#1074#1072#1085#1080#1103':'
  end
  object ButtonStartStop: TButton
    Left = 8
    Top = 449
    Width = 253
    Height = 41
    Caption = #1047#1072#1087#1091#1089#1090#1080#1090#1100
    TabOrder = 0
    OnClick = ButtonStartStopClick
  end
  object VideoFrame: TScrollBox
    Left = 265
    Top = 8
    Width = 624
    Height = 481
    Ctl3D = False
    ParentCtl3D = False
    TabOrder = 1
  end
  object ListBox: TListBox
    Left = 8
    Top = 27
    Width = 251
    Height = 318
    Style = lbOwnerDrawFixed
    ItemHeight = 50
    TabOrder = 2
    OnClick = ListBoxClick
    OnDrawItem = ListBoxDrawItem
  end
  object GroupBox1: TGroupBox
    Left = 8
    Top = 351
    Width = 251
    Height = 92
    Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1072' '#1074#1099#1076#1077#1083#1077#1085#1080#1103
    TabOrder = 3
    object Label2: TLabel
      Left = 8
      Top = 27
      Width = 77
      Height = 15
      Caption = #1062#1074#1077#1090' '#1082#1086#1085#1090#1091#1088#1072':'
    end
    object Label3: TLabel
      Left = 8
      Top = 55
      Width = 100
      Height = 15
      Caption = #1058#1086#1083#1097#1080#1085#1072' '#1082#1086#1085#1090#1091#1088#1072':'
    end
    object ColorBoxColor: TColorBox
      Left = 114
      Top = 24
      Width = 126
      Height = 22
      Selected = clLime
      Style = [cbStandardColors, cbExtendedColors, cbSystemColors, cbPrettyNames]
      TabOrder = 0
      OnChange = ColorBoxColorChange
    end
    object ComboBoxSize: TComboBox
      Left = 114
      Top = 52
      Width = 126
      Height = 22
      Style = csOwnerDrawFixed
      ItemIndex = 1
      TabOrder = 1
      Text = '2 px'
      OnChange = ComboBoxSizeChange
      Items.Strings = (
        '1 px'
        '2 px'
        '3 px'
        '4 px'
        '5 px'
        '6 px'
        '7 px'
        '8 px'
        '9 px'
        '10 px')
    end
  end
  object ImageList: TImageList
    Height = 36
    Width = 36
    Left = 447
    Top = 16
  end
  object MainMenu: TMainMenu
    Left = 328
    Top = 16
    object File1: TMenuItem
      Caption = #1060#1072#1081#1083
      object N1: TMenuItem
        Action = FileExit
      end
    end
    object NAbout: TMenuItem
      Caption = '?'
      OnClick = NAboutClick
    end
  end
  object ActionList: TActionList
    Left = 393
    Top = 16
    object FileExit: TFileExit
      Category = 'File'
      Caption = #1042#1099#1093#1086#1076
      Hint = 'Exit|Quits the application'
      ImageIndex = 43
    end
  end
end
