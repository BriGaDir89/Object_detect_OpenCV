object FormAbout: TFormAbout
  Left = 0
  Top = 0
  BorderStyle = bsSizeToolWin
  Caption = 'About'
  ClientHeight = 77
  ClientWidth = 271
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'Arial'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 16
  object LabelEmail: TLinkLabel
    Left = 8
    Top = 25
    Width = 131
    Height = 19
    BevelInner = bvNone
    Caption = 'E-mail: vitaly@levikin.ru'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Arial'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    UseVisualStyle = True
  end
  object LabelDev: TLinkLabel
    Left = 8
    Top = 8
    Width = 176
    Height = 19
    Caption = #1056#1072#1079#1088#1072#1073#1086#1090#1095#1080#1082': '#1051#1077#1074#1080#1082#1080#1085' '#1042#1080#1090#1072#1083#1080#1081
    TabOrder = 1
    UseVisualStyle = True
  end
  object ButtonClose: TButton
    Left = 188
    Top = 44
    Width = 75
    Height = 25
    Caption = #1047#1072#1082#1088#1099#1090#1100
    TabOrder = 2
    OnClick = ButtonCloseClick
  end
end
