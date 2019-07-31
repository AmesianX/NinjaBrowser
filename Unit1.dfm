object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'NinjaBrowser'
  ClientHeight = 775
  ClientWidth = 1116
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poScreenCenter
  OnCloseQuery = FormCloseQuery
  PixelsPerInch = 96
  TextHeight = 13
  object PageControl2: TPageControl
    Left = 0
    Top = 0
    Width = 1116
    Height = 600
    ActivePage = TabSheet1
    Align = alClient
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Fixedsys'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    TabStop = False
    OnChange = PageControl2Change
    object TabSheet1: TTabSheet
      Caption = 'NinjaBrowser'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Fixedsys'
      Font.Style = []
      ParentFont = False
      object Splitter1: TSplitter
        Left = 602
        Top = 36
        Width = 6
        Height = 513
        Align = alRight
        AutoSnap = False
        Color = clRed
        ParentColor = False
        ResizeStyle = rsUpdate
        Visible = False
        ExplicitLeft = 803
        ExplicitHeight = 534
      end
      object PanelTopMain: TPanel
        Left = 0
        Top = 0
        Width = 1108
        Height = 36
        Align = alTop
        BevelOuter = bvNone
        TabOrder = 0
        object PanelForward: TPanel
          Left = 108
          Top = 0
          Width = 36
          Height = 36
          Align = alLeft
          BevelOuter = bvNone
          Padding.Left = 4
          Padding.Top = 4
          Padding.Right = 4
          Padding.Bottom = 4
          TabOrder = 0
          object SpeedButtonGoForward: TSpeedButton
            Left = 4
            Top = 4
            Width = 28
            Height = 28
            Align = alClient
            Caption = '>'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Fixedsys'
            Font.Style = []
            ParentFont = False
            OnClick = SpeedButtonGoForwardClick
            ExplicitTop = 5
            ExplicitHeight = 26
          end
        end
        object PanelURL: TPanel
          Left = 144
          Top = 0
          Width = 690
          Height = 36
          Align = alClient
          BevelOuter = bvNone
          Padding.Left = 6
          Padding.Top = 6
          Padding.Right = 6
          Padding.Bottom = 6
          TabOrder = 1
          object EditURL: TEdit
            Left = 6
            Top = 6
            Width = 678
            Height = 24
            Align = alClient
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Fixedsys'
            Font.Style = []
            ParentFont = False
            TabOrder = 0
            OnKeyDown = EditURLKeyDown
          end
        end
        object PanelGo: TPanel
          Left = 834
          Top = 0
          Width = 36
          Height = 36
          Align = alRight
          BevelOuter = bvNone
          Padding.Left = 4
          Padding.Top = 4
          Padding.Right = 4
          Padding.Bottom = 4
          TabOrder = 2
          object SpeedButtonGo: TSpeedButton
            Left = 4
            Top = 4
            Width = 28
            Height = 28
            Align = alClient
            Caption = 'Go'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Fixedsys'
            Font.Style = []
            ParentFont = False
            OnClick = SpeedButtonGoClick
            ExplicitLeft = 0
            ExplicitTop = 0
            ExplicitWidth = 10
            ExplicitHeight = 39
          end
        end
        object PanelBackward: TPanel
          Left = 72
          Top = 0
          Width = 36
          Height = 36
          Align = alLeft
          BevelOuter = bvNone
          Padding.Left = 4
          Padding.Top = 4
          Padding.Right = 4
          Padding.Bottom = 4
          TabOrder = 3
          object SpeedButtonGoBack: TSpeedButton
            Left = 4
            Top = 4
            Width = 28
            Height = 28
            Align = alClient
            Caption = '<'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Fixedsys'
            Font.Style = []
            ParentFont = False
            OnClick = SpeedButtonGoBackClick
            ExplicitTop = 5
            ExplicitHeight = 26
          end
        end
        object PanelLockURL: TPanel
          Left = 0
          Top = 0
          Width = 72
          Height = 36
          Align = alLeft
          BevelOuter = bvNone
          Padding.Left = 4
          Padding.Top = 4
          Padding.Right = 4
          Padding.Bottom = 4
          TabOrder = 4
          object CheckBoxLockURL: TCheckBox
            AlignWithMargins = True
            Left = 7
            Top = 7
            Width = 58
            Height = 22
            Align = alClient
            Caption = 'Lock'
            TabOrder = 0
          end
        end
        object PanelAddTab: TPanel
          Left = 870
          Top = 0
          Width = 36
          Height = 36
          Align = alRight
          BevelOuter = bvNone
          Padding.Left = 4
          Padding.Top = 4
          Padding.Right = 4
          Padding.Bottom = 4
          TabOrder = 5
          object SpeedButtonAddTab: TSpeedButton
            Left = 4
            Top = 4
            Width = 28
            Height = 28
            Align = alClient
            Caption = '+'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Fixedsys'
            Font.Style = []
            ParentFont = False
            OnClick = SpeedButtonAddTabClick
            ExplicitLeft = 0
            ExplicitTop = 0
            ExplicitWidth = 10
            ExplicitHeight = 39
          end
        end
        object PanelRight: TPanel
          Left = 1050
          Top = 0
          Width = 58
          Height = 36
          Align = alRight
          BevelOuter = bvNone
          TabOrder = 6
          object CheckBoxExit: TCheckBox
            Left = 5
            Top = 8
            Width = 55
            Height = 20
            Caption = 'Exit'
            Checked = True
            State = cbChecked
            TabOrder = 0
          end
        end
        object PanelDeleteTab: TPanel
          Left = 906
          Top = 0
          Width = 36
          Height = 36
          Align = alRight
          BevelOuter = bvNone
          Padding.Left = 4
          Padding.Top = 4
          Padding.Right = 4
          Padding.Bottom = 4
          TabOrder = 7
          object SpeedButtonDeleteTab: TSpeedButton
            Left = 4
            Top = 4
            Width = 28
            Height = 28
            Align = alClient
            Caption = '-'
            OnClick = SpeedButtonDeleteTabClick
            ExplicitLeft = 13
            ExplicitTop = -24
            ExplicitWidth = 23
            ExplicitHeight = 22
          end
        end
        object PanelO: TPanel
          Left = 942
          Top = 0
          Width = 36
          Height = 36
          Align = alRight
          BevelOuter = bvNone
          Caption = 'O'
          Padding.Left = 4
          Padding.Top = 4
          Padding.Right = 4
          Padding.Bottom = 4
          TabOrder = 8
          object SpeedButtonOpenOptions: TSpeedButton
            Left = 4
            Top = 4
            Width = 28
            Height = 28
            Align = alClient
            Caption = 'O'
            OnClick = SpeedButtonOpenOptionsClick
            ExplicitLeft = -4
            ExplicitTop = 14
            ExplicitWidth = 23
            ExplicitHeight = 22
          end
        end
        object PanelG: TPanel
          Left = 1014
          Top = 0
          Width = 36
          Height = 36
          Align = alRight
          BevelOuter = bvNone
          Caption = 'G'
          Padding.Left = 4
          Padding.Top = 4
          Padding.Right = 4
          Padding.Bottom = 4
          TabOrder = 9
          object SpeedButtonG: TSpeedButton
            Left = 4
            Top = 4
            Width = 28
            Height = 28
            Align = alClient
            Caption = 'G'
            OnClick = SpeedButtonGClick
            ExplicitLeft = 13
            ExplicitTop = 14
            ExplicitWidth = 23
            ExplicitHeight = 22
          end
        end
        object PanelE: TPanel
          Left = 978
          Top = 0
          Width = 36
          Height = 36
          Align = alRight
          BevelOuter = bvNone
          Caption = 'E'
          Padding.Left = 4
          Padding.Top = 4
          Padding.Right = 4
          Padding.Bottom = 4
          TabOrder = 10
          object SpeedButtonE: TSpeedButton
            Left = 4
            Top = 4
            Width = 28
            Height = 28
            Align = alClient
            Caption = 'E'
            OnClick = SpeedButtonEClick
            ExplicitLeft = 13
            ExplicitTop = 14
            ExplicitWidth = 23
            ExplicitHeight = 22
          end
        end
      end
      object StatusBar1: TStatusBar
        Left = 0
        Top = 549
        Width = 1108
        Height = 19
        Panels = <
          item
            Width = 140
          end
          item
            Width = 500
          end>
      end
      object PageControl1: TPageControl
        Left = 273
        Top = 36
        Width = 329
        Height = 513
        Align = alClient
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        MultiLine = True
        ParentFont = False
        PopupMenu = PopupMenuTab
        TabOrder = 2
        TabPosition = tpBottom
        TabStop = False
        OnChange = PageControl1Change
        OnChanging = PageControl1Changing
        OnMouseDown = PageControl1MouseDown
      end
      object PanelHistory: TPanel
        Left = 0
        Top = 36
        Width = 273
        Height = 513
        Align = alLeft
        BevelOuter = bvNone
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        TabOrder = 3
        Visible = False
        object PanelMenu: TPanel
          AlignWithMargins = True
          Left = 3
          Top = 3
          Width = 267
          Height = 41
          ParentCustomHint = False
          Align = alTop
          BevelOuter = bvNone
          BorderStyle = bsSingle
          Ctl3D = False
          DoubleBuffered = False
          ParentCtl3D = False
          ParentDoubleBuffered = False
          TabOrder = 0
          object ButtonAddHistory: TButton
            Left = 91
            Top = 8
            Width = 25
            Height = 25
            Caption = '<'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Fixedsys'
            Font.Style = []
            ParentFont = False
            TabOrder = 0
            OnClick = ButtonAddHistoryClick
          end
          object ButtonDeleteHistory: TButton
            Left = 122
            Top = 8
            Width = 25
            Height = 25
            Caption = 'X'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Fixedsys'
            Font.Style = []
            ParentFont = False
            TabOrder = 1
            OnClick = ButtonDeleteHistoryClick
          end
          object ButtonLoadAll: TButton
            Left = 184
            Top = 8
            Width = 25
            Height = 25
            Caption = '>>'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Fixedsys'
            Font.Style = []
            ParentFont = False
            TabOrder = 2
            OnClick = ButtonLoadAllClick
          end
          object ButtonGetAll: TButton
            Left = 60
            Top = 8
            Width = 25
            Height = 25
            Caption = '<<'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Fixedsys'
            Font.Style = []
            ParentFont = False
            TabOrder = 3
            OnClick = ButtonGetAllClick
          end
          object ButtonLoadHistory: TButton
            Left = 153
            Top = 8
            Width = 25
            Height = 25
            Caption = '>'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Fixedsys'
            Font.Style = []
            ParentFont = False
            TabOrder = 4
            OnClick = ButtonLoadHistoryClick
          end
          object CheckBoxAllSelect: TCheckBox
            Left = 12
            Top = 12
            Width = 35
            Height = 17
            Caption = 'All'
            TabOrder = 5
            OnClick = CheckBoxAllSelectClick
          end
        end
        object ListViewHistory: TListView
          AlignWithMargins = True
          Left = 3
          Top = 50
          Width = 267
          Height = 460
          Align = alClient
          BevelInner = bvNone
          BevelOuter = bvNone
          Checkboxes = True
          Columns = <
            item
              Caption = 'No'
              MaxWidth = 30
              MinWidth = 30
              Width = 30
            end
            item
              AutoSize = True
              Caption = 'URL'
              MinWidth = 220
            end>
          DoubleBuffered = True
          FlatScrollBars = True
          GridLines = True
          ReadOnly = True
          RowSelect = True
          ParentDoubleBuffered = False
          TabOrder = 1
          ViewStyle = vsReport
          OnDblClick = ListViewHistoryDblClick
          OnKeyUp = ListViewHistoryKeyUp
          OnItemChecked = ListViewHistoryItemChecked
        end
      end
      object PanelDevTools: TPanel
        Left = 608
        Top = 36
        Width = 500
        Height = 513
        Align = alRight
        BevelOuter = bvNone
        DoubleBuffered = True
        ParentDoubleBuffered = False
        TabOrder = 4
        Visible = False
        object PanelMainDevTools: TCEFWindowParent
          Left = 0
          Top = 37
          Width = 500
          Height = 476
          Align = alClient
          TabOrder = 0
          DoubleBuffered = False
          ParentDoubleBuffered = False
        end
        object PanelDevToolsTop: TPanel
          Left = 0
          Top = 0
          Width = 500
          Height = 37
          Align = alTop
          BevelOuter = bvNone
          BorderWidth = 1
          BorderStyle = bsSingle
          Ctl3D = False
          ParentCtl3D = False
          TabOrder = 1
          object ButtonDevToolsClose: TButton
            Left = 6
            Top = 5
            Width = 65
            Height = 25
            Caption = 'Close'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 0
            OnClick = ButtonDevToolsCloseClick
          end
        end
      end
    end
    object TabSheet5: TTabSheet
      Caption = 'Download'
      ImageIndex = 4
      object PanelDownload: TPanel
        Left = 0
        Top = 0
        Width = 1108
        Height = 568
        Align = alClient
        BevelOuter = bvNone
        TabOrder = 0
        object MemoDownload: TMemo
          Left = 0
          Top = 0
          Width = 1108
          Height = 568
          Align = alClient
          Lines.Strings = (
            
              'The download function works well, but do not download more than ' +
              '3 at a time.'
            'There will be a crash because there is no manager function.'
            
              'If no download path is specified, you will be asked where to sav' +
              'e it.'
            'I do not ask for the next download.'
            'If you want to save to a different path, press the reset button.'
            
              'While downloading, you will not be able to open the link in the ' +
              'new tab from the right mouse button menu.'
            'Do not panic. I will solve the problem soon.')
          ReadOnly = True
          ScrollBars = ssBoth
          TabOrder = 0
        end
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'SpiderMonkey'
      ImageIndex = 2
      object MemoJS: TMemo
        Left = 0
        Top = 24
        Width = 1108
        Height = 544
        Align = alClient
        Lines.Strings = (
          '// [About MonkeySpider]'
          
            '// Like MonkeySpider, we will support js injection before page l' +
            'oading and'
          
            '// js injection after page loading. The following script is an e' +
            'xample.'
          
            '// It is a script that removes the login warning box and removes' +
            ' mosaic and'
          '// blur from the "korean adult live chat site".'
          
            '// This script is executed every 10 milliseconds after the page ' +
            'is loaded.'
          '// setInterval(function() {'
          '    $("#login_modal_mask").remove();'
          '    $(".login_modal_box").remove();'
          '    $("#mosaic").remove();'
          '    $("#adult_hide").remove();'
          '    $("#video")[0].style.filter='#39#39';'
          '    $("#video")[0].style.visibility = '#39#39';'
          '// }, 10);')
        TabOrder = 0
      end
      object Panel3: TPanel
        Left = 0
        Top = 0
        Width = 1108
        Height = 24
        Align = alTop
        BevelOuter = bvNone
        TabOrder = 1
        object StaticTextSpiderMonkey: TStaticText
          Left = 2
          Top = 2
          Width = 124
          Height = 20
          Caption = 'Injection Type:'
          TabOrder = 0
        end
      end
      object CheckBoxPreProcess: TCheckBox
        Left = 131
        Top = 2
        Width = 110
        Height = 17
        Caption = 'Pre-Process'
        TabOrder = 2
      end
      object CheckBoxPostProcess: TCheckBox
        Left = 247
        Top = 2
        Width = 124
        Height = 17
        Caption = 'Post-Process'
        TabOrder = 3
      end
    end
    object TabSheet3: TTabSheet
      Caption = 'Inspector'
      ImageIndex = 1
      object ListViewInspector: TListView
        Left = 0
        Top = 433
        Width = 1108
        Height = 135
        Align = alClient
        Columns = <
          item
            Caption = 'URL'
            Width = 500
          end
          item
            Caption = 'DATA'
            Width = 500
          end>
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
        ViewStyle = vsReport
      end
      object PanelInspector: TPanel
        Left = 0
        Top = 0
        Width = 1108
        Height = 433
        Align = alTop
        BevelOuter = bvNone
        TabOrder = 1
        object StaticTextInspector: TStaticText
          Left = 3
          Top = 10
          Width = 596
          Height = 20
          Caption = 
            'Inspector functionality is not yet implemented and is in the des' +
            'ign phase.'
          TabOrder = 0
        end
      end
    end
    object TabSheet4: TTabSheet
      Caption = 'About'
      ImageIndex = 3
      object MemoREADME: TMemo
        Left = 0
        Top = 0
        Width = 1108
        Height = 568
        Align = alClient
        Lines.Strings = (
          '## [NinjaBrowser]'
          
            '----------------------------------------------------------------' +
            '-------------------------------'
          
            'The NinjaBrowser is an open source browser project based on CEF4' +
            'DELPHI.'
          
            '- Programmed by AmesianX in powerhacker.net. (amesianx@gmail.com' +
            ')'
          '- https://github.com/amesianx/ninjabrowser.git'
          '- The NinjaBrowser is not a ninja bra.'
          ''
          ''
          '## [Why deploy a NinjaBrowser?]'
          
            '----------------------------------------------------------------' +
            '-------------------------------'
          
            'The NinjaBrowser has the most optimized chrome engine options wh' +
            'en using libcef'
          
            'through many tests. The browsing speed of the NinjaBrowser is ve' +
            'ry fast now.'
          
            'I know that there are a number of bugs in other projects using l' +
            'ibcef.'
          
            'I solve the problem and share such a bug. For example, how to fi' +
            'x a DirectWrite 2D'
          
            'problem with the GPU enabled. And I have a solution to the probl' +
            'em of why Netflix'
          'does not play or why regular videos do not play.'
          
            'Netflix is not played unless you enable the widevine DRM module.' +
            ' And The default'
          'distribution of CEF4DELPHI can not play next video link.'
          
            '(Example video test link: https://tv.kakao.com/channel/2653401/c' +
            'liplink/395496297)'
          
            'There are a number of problems and solved most problems. (The hi' +
            'gh DPI resizing'
          'problem causes the CSS layout of the screen to be distorted.)'
          'The features I wanted to develop have not been touched yet.'
          
            'What is the benefit of additional features if you are not at lea' +
            'st comfortable'
          
            'browsing? My additional features are meaningful when basic brows' +
            'ing is perfect.'
          'So I decided to share some basic browsing stability.'
          'The extravagant features still need further development.'
          
            'For example Google translation site features and so on. And a do' +
            'wnload manager'
          
            'with minimal functionality. There are still more luxurious basic' +
            ' features, but'
          
            'I can not touch them. It'#39's just like basic features for ordinary' +
            ' people, and'
          'very extravagant features for developers. :)'
          'I can not download Google Drive from my Ninja browser right now.'
          'I found this problem before the final deployment.'
          'If someone can solve this problem, please let me know how. (T.T)'
          ''
          ''
          '## [Left-hand key usage]'
          
            '----------------------------------------------------------------' +
            '-------------------------------'
          
            'The NinjaBrowser has a key layout that makes it easy to operate ' +
            'the browser with the left hand.'
          ''
          
            'Alt+1 : Open debugging window for hidden NinjaBrowser developmen' +
            't'
          'Alt+2 : Go to left tab'
          'Alt+3 : Go to right tab'
          'Alt+T : Open new tab'
          'Alt+W : Close Tab (or Alt+Q)'
          'Alt+E : Open Developer Tools'
          'Alt+G : NinjaBrowser Bookmark'
          'Alt+R : Reload browser'
          ''
          
            'Lock: The Lock check box locks the URL input window. This featur' +
            'e prevents'
          
            '      hothaeded users from entering incorrectly when attempting ' +
            'to enter'
          
            '      the URL input window while the site navigating is changing' +
            '.'
          ''
          
            'Exit: If you clear the Exit checkbox, when you click Exit on the' +
            ' window'
          '      the tab will close instead of closing the program.'
          ''
          ''
          '## [Download and install CEF4Delphi]'
          
            '----------------------------------------------------------------' +
            '-------------------------------'
          'You must download the CEF4DELPHI source from github.'
          '- git clone https://github.com/salvadordf/CEF4Delphi.git'
          ''
          
            'Then you need to open the "uCEFApplication.pas" file and modify ' +
            'the build version'
          'of libcef as follows:'
          ''
          'CEF_SUPPORTED_VERSION_MAJOR   = 75;'
          'CEF_SUPPORTED_VERSION_MINOR   = 1;'
          'CEF_SUPPORTED_VERSION_RELEASE = 14;'
          'CEF_SUPPORTED_VERSION_BUILD   = 0;'
          ''
          'CEF_CHROMEELF_VERSION_MAJOR   = 75;'
          'CEF_CHROMEELF_VERSION_MINOR   = 0;'
          'CEF_CHROMEELF_VERSION_RELEASE = 3770;'
          'CEF_CHROMEELF_VERSION_BUILD   = 100;'
          ''
          ''
          '## [Using the prebuilt version]'
          
            '----------------------------------------------------------------' +
            '-------------------------------'
          
            'Download the "pre-built_cef_v.75.0.3770.100.zip" file from the f' +
            'ollowing link:'
          
            '- https://drive.google.com/file/d/1eZp0R4l2DZDQU6K18B1arXjLjjzy6' +
            '-7r/view?usp=sharing'
          ''
          
            'Unpack it and rename it to "cef" and place it in the directory w' +
            'here NinjaBrowser'#39's'
          'executable is located.'
          ''
          ''
          '## [How to build libcef]'
          
            '----------------------------------------------------------------' +
            '-------------------------------'
          
            'If you do not want to use prebuilt libcef, you can build libcef ' +
            'in the following'
          'way. But I do not recommend it. Each build takes a half day.'
          'If you try to build for the first time, it will take two days.'
          
            'It is a measure of the Xeon CPU when you build a 2 cpu core usin' +
            'g a VirtualBox'
          
            'virtual machine. There are bugs in the VirtualBox that slow down' +
            ' the use of more'
          
            'than two Xeon CPU cores. On a typical CPU, it will probably take' +
            ' an average of'
          'half a day. If you are ready, please follow me.'
          ''
          
            'You can build the libcef package by running it in the following ' +
            'order:'
          ''
          
            'Download the "libcef_builder_20190731.zip" file and extract it t' +
            'o the "c:\Google".'
          
            '- https://drive.google.com/file/d/1EDg3VgSAhslHmiKZdmzhDaFbXZ5Xl' +
            'rps/view?usp=sharing'
          ''
          
            'The directory name must be the same. Add the "C:\Google\depot_to' +
            'ols" path to'
          'your Windows system'#39's PATH environment variable.'
          ''
          '1. cd c:\Google'
          '2. run_update_cef.bat'
          '3. run_create_cef.bat'
          '4. build_cef.bat'
          ''
          ''
          '## [How to build to support widevine module]'
          
            '----------------------------------------------------------------' +
            '-------------------------------'
          
            'The widevine module is a DRM module. And without this module, yo' +
            'u can not see Netflix.'
          
            'You need to modify the following files before running create_cef' +
            '.bat:'
          ''
          
            'C:\Google\chromium_git\chromium\src\third_party\widevine\cdm\wid' +
            'evine_cdm_version.h'
          ''
          'Added two lines into it:'
          '+--------------------------------------------------+'
          '| #define WIDEVINE_CDM_AVAILABLE                   |'
          '| #define WIDEVINE_CDM_VERSION_STRING 4.10.1440.18 |'
          '+--------------------------------------------------+'
          ''
          
            'After compilation is finished, you must include the widevinecdm.' +
            'dll file'
          
            'in the final build package. You can extract the widevine.dll fil' +
            'e from'
          'the latest 32-bit version of the Google Chrome browser.'
          
            'At this time, the manifest.json file should have the following c' +
            'onfiguration.'
          
            'Also, if you do not use ia32 in the manifest.json file, it will ' +
            'not be loaded.'
          'Many people may mistake it to be x86, not ia32.'
          ''
          'The contents of the "manifest.json" file should look like this:'
          ''
          '{'
          '  "manifest_version": 2,'
          
            '  "update_url": "https://clients2.google.com/service/update2/crx' +
            '",'
          '  "name": "WidevineCdm",'
          '  "description": "Widevine Content Decryption Module",'
          '  "version": "4.10.1440.18",'
          '  "minimum_chrome_version": "68.0.3430.0",'
          '  "x-cdm-module-versions": "4",'
          '  "x-cdm-interface-versions": "10",'
          '  "x-cdm-host-versions": "10",'
          '  "x-cdm-codecs": "vp8,vp9.0,avc1",'
          '  "x-cdm-persistent-license-support": true,'
          '  "x-cdm-supported-encryption-schemes": ["cenc","cbcs"],'
          '  "os": "win",'
          '  "arch": "ia32"'
          '}'
          ''
          ''
          '## [Development History]'
          
            '----------------------------------------------------------------' +
            '-------------------------------'
          
            'I started developing my own browser with the earliest version of' +
            ' DCEF3.'
          
            'I have been developing a NinjaBrowser since 2010 whenever I have' +
            ' free time.'
          
            'The NinjaBrowser is my private browser that uses the Chrome Brow' +
            'ser Engine'
          
            'as the core. I wanted to develop a private browser as an HTTP In' +
            'spector'
          
            'like a proxy. But it'#39's not just for that reason. I have more ide' +
            'as.'
          
            'For example, build qemu and attach it to the NinjaBrowser. I wil' +
            'l install'
          
            'the Mattermost server to qemu. I will port the qemu console scre' +
            'en to the'
          
            'NinjaBrowser tab. The NinjaBrowser will have a portable mattermo' +
            'st chat'
          
            'server. The idea of porting qemu to NinjaBrowser will allow a lo' +
            't of services'
          
            'to work locally. And a portable program. This idea is just the t' +
            'ip of the'
          
            'iceberg. Browser-based GDB is also planned. Installing python in' +
            'side qemu'
          
            'will also enable browser-based GDB(MultiArch GDB) in the NinjaBr' +
            'owser.'
          
            'It also uses python in qemu, so you can call youtube-dl from a N' +
            'injaBrowser.'
          
            'This makes it easy to implement the youtube video download featu' +
            're in the'
          
            'NinjaBrowser. All these ideas are just planned. I have not been ' +
            'able to'
          'implement because of a lack of time because of my damn job.'
          
            'I will also work on porting JavaScript editors to NinjaBrowser j' +
            'ust like'
          
            'electron based programs(like embedded nodejs). And I will also a' +
            'ttach d8.exe'
          '(v8 debugger). This is because of my vulnerability exploit job.'
          
            'During the initial development, the project had been delayed for' +
            ' years'
          
            'because of a critical bug in the libcef library and DCEF3 wrappe' +
            'r.'
          
            'DCEF means DelphiChromiumEmbedded and DCEF3 is a project that wr' +
            'aps the chrome'
          
            'engine in the Delphi language. This DCEF3 component can also be ' +
            'used in C++ Builder'
          
            'when installed in Delphi. However, the initial version of DCEF3 ' +
            'was very unstable.'
          
            'It was almost impossible to make a program. Moreover, I could no' +
            't solve the problem'
          
            'of crashing while scrolling the browser. Ten years later, someon' +
            'e started an amazing'
          
            'project called CEF4DELPHI. I really want to thank the CEF4DELPHI' +
            ' developers.'
          
            'Thank you so much that I can achieve my ideals. So I was able to' +
            ' rebuild the existing'
          
            'code from the CEF4DELPHI component and test it. The bug has disa' +
            'ppeared.'
          'Moreover, I was able to update a lot of existing code recently.'
          
            'For example, The NinjaBrowser use GPU rendering instead of softw' +
            'are rendering.'
          
            'And solved the DirectWrite 2D problem, which is a critical probl' +
            'em.'
          '(GDI font blurring due to GPU compositing acceleration problem).'
          
            'As a result, the browsing speed was greatly improved. It also en' +
            'abled h264 multimedia'
          
            'features in Chrome Engine. I also added the ability to play Netf' +
            'lix by enabling'
          
            'widevine DRM and the Adobe Flash enabling. Netflix uses DRM to p' +
            'rotect the video'
          
            'stream, so you need to enable a DRM module called widevine. It a' +
            'lso has full-screen'
          
            'capabilities. In addition, the locale for the country is display' +
            'ed correctly on Google'
          
            'or YouTube. It works much more reliably than with previous DCEF3' +
            '.'
          
            'However, there is still a problem. If you add a tab quickly or c' +
            'lose a tab quickly'
          
            'a crash occurs. So it takes a way to give delay. This problem is' +
            ' the most dirty'
          
            'code part. There is a flicker on the site where Adobe Flash is c' +
            'urrently running.'
          
            'The console window is briefly visible and disappears. I plan to ' +
            'apply the MS Detours'
          
            'library to solve this problem. You need to hook the CreateProces' +
            's win32 API function.'
          
            'I will hook the Adobe Flash plug-in to prevent the console windo' +
            'w from showing.'
          
            'The MS Detours library is my area of expertise and can be easily' +
            ' applied.'
          ''
          ''
          '## [Why C++ Builder? Not Delphi?]'
          
            '----------------------------------------------------------------' +
            '-------------------------------'
          
            'I can use various languages, but I use C/C++ as my main language' +
            '.'
          'The C/C++ language is the easiest.'
          'If I joke a bit, it'#39's even easier than Python.'
          
            'The reason is that too much code is hidden in Python'#39's component' +
            's.'
          'I have been using the C/C++ as the main language since 1992.'
          'But, you know, most core programmers have a fatal problem.'
          
            'It does not study frontend code. I can produce all the function ' +
            'code.'
          'But it is not easy to write the best UI code that looks pretty.'
          'In fact, for the core programmer, UI code is wasted code.'
          
            'This is not really the code that performs the core functions of ' +
            'the program.'
          'It is the reality of all programmers. So we have to choose.'
          
            'You should find and use a framework or library that will take ca' +
            're of this waste code.'
          
            'Therefore, C++ Builder and QT are the frameworks that will cover' +
            ' this frontend code'
          
            'for core programmers. As a matter of fact, Microsoft'#39's MFC is wh' +
            'at it provided originally'
          
            'as a framework. There is also a Win32++ framework. However, MFC ' +
            'is not intuitive'
          
            'and so is Win32++. QT is beautiful code and it is really perfect' +
            ', but the IDE(Design'
          
            'Studio) is still not intuitive. Although unstable, C++ Builder h' +
            'as the most intuitive'
          
            'IDE design interface. I can use the Delphi language, but I hate ' +
            'the Delphi language.'
          
            'I hate the Microsoft Basic feeling of low-level sentence style l' +
            'ike.'
          
            'The code itself is not intuitive and beautiful. There are many C' +
            '/C++ code stuffs'
          'available on the Internet, but these codes are not compatible.'
          'That'#39's why I do not implement code using QT and Delphi ETC.'
          
            'C++ Builder has the same intuitive advantages as Delphi programm' +
            'ing, but it can be'
          
            'compatible with all existing Win32 API code without much modific' +
            'ation.'
          
            'Also, if you do not need to program dynamic design code, IDE'#39's d' +
            'esign studio is'
          
            'very intuitive. (If you compare to QT, the dynamic design code i' +
            's written to the'
          '.moc files). We often use IDEs rather than dynamic design code.'
          
            'This is because the interface design is fully tested through the' +
            ' IDE and then'
          
            'moved to dynamic code. Therefore, the IDE must provide an intuit' +
            'ive design'
          
            'of the component. C++ Builder is more satisfied than most other ' +
            'languages.'
          
            'So, from time to time, Microsoft is copying Delphi'#39's design stud' +
            'io.'
          
            'if you can write a perfect backend code(Non-UI core frameworks) ' +
            'and easily even'
          'a perfect frontend code(UI core frameworks), you can fly.'
          'Is it enough to explain why I chose C++ Builder?'
          
            'I am a perfectionist, but I do not want to suffer from programmi' +
            'ng.'
          
            'If you care about a perfect GUI front engine, you can probably d' +
            'ie..'
          'You just need to find and use the best GUI framework.'
          
            'I will eventually use QT for high quality. But, C++ Builder is s' +
            'imilar to the most'
          
            'complete Japanese high quality instant food. So I just use C++ B' +
            'uilder instead of'
          
            'a microwave oven. This is because it only requires cooking for 3' +
            ' minutes.'
          'If you are in the same style as me, C++ Builder is the answer.'
          
            'So, Chinese hackers are using C++ Builder very much. This is bec' +
            'ause you can build'
          
            'hacking tools quickly without investing a lot of time on the fro' +
            'ntend.'
          
            'I have no plans to use more than what I use for my fast code pro' +
            'gramming.'
          
            'Commercial projects should use QT for long-term development purp' +
            'oses.'
          
            'The final answer is QT. The NinjaBrowser still has no plans for ' +
            'QT porting.'
          'This is because there is no commercial purpose yet.'
          ''
          ''
          
            '## Is there a security issue when surfing the web with a NinjaBr' +
            'owser?'
          
            '----------------------------------------------------------------' +
            '-------------------------------'
          
            'I am not responsible for your security. So if you are concerned ' +
            'about'
          
            'security, you should not use this browser. However, most hackers' +
            ' do not'
          
            'typically create 32-bit exploits. They just create 64-bit exploi' +
            'ts.'
          
            'So the 32-bit NinjaBrowser might be safer than Google'#39's current ' +
            'Chrome'
          
            'Browser. This is because Google'#39's official Chrome distribution w' +
            'ill install'
          
            '64-bit by default. For 64-bit hacking code to work on 32-bit, th' +
            'e expert'
          
            'will have to manually rewrite the code. Experts are not free. Sc' +
            'ript kids'
          
            'can not reuse attack code in a simple way. My job is a security ' +
            'expert, so'
          
            'I know very well. Converting a one-day exploit code from 64-bit ' +
            'to 32-bit'
          
            'is not a simple matter without the best hacker. Ironically, 32-b' +
            'it browsers'
          
            'are more secure. I will always rebuild and distribute Google'#39's l' +
            'atest Chrome'
          
            'engine at deployment time. Sometimes you may not keep up with Go' +
            'ogle'#39's update'
          'speed. But do not worry too much you are 32 bits.'
          ''
          ''
          '## P.S'
          
            '----------------------------------------------------------------' +
            '-------------------------------'
          
            'I could not change the comment in the source code to English. I ' +
            'am not good at English.'
          
            'I am studying English. I do not know English. I just use the hel' +
            'p of Google Translator.'
          
            'Of course, I manually correct the wrong translation part. So eve' +
            'n if there is a wrong'
          'translation, please forgive me.'
          'Thank you.'
          '')
        ReadOnly = True
        ScrollBars = ssBoth
        TabOrder = 0
      end
    end
  end
  object EditSearch: TEdit
    Left = 7
    Top = 64
    Width = 262
    Height = 21
    TabOrder = 1
    Visible = False
    OnKeyUp = EditSearchKeyUp
  end
  object ProgressBar1: TProgressBar
    Left = 444
    Top = 2
    Width = 132
    Height = 20
    TabOrder = 2
  end
  object ButtonResetDir: TButton
    Left = 578
    Top = 1
    Width = 54
    Height = 22
    Caption = 'Reset'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Fixedsys'
    Font.Style = []
    ParentFont = False
    TabOrder = 3
    OnClick = ButtonResetDirClick
  end
  object StaticTextDownPath: TStaticText
    Left = 713
    Top = 4
    Width = 116
    Height = 20
    Caption = 'Download Path:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Fixedsys'
    Font.Style = []
    ParentFont = False
    TabOrder = 4
  end
  object ButtonExplorer: TButton
    Left = 633
    Top = 1
    Width = 75
    Height = 22
    Caption = 'Explorer'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Fixedsys'
    Font.Style = []
    ParentFont = False
    TabOrder = 5
    OnClick = ButtonExplorerClick
  end
  object PanelOptions: TPanel
    Left = 0
    Top = 600
    Width = 1116
    Height = 175
    Align = alBottom
    Ctl3D = False
    ParentCtl3D = False
    TabOrder = 6
    Visible = False
    object PanelDBG: TPanel
      Left = 1
      Top = 1
      Width = 823
      Height = 173
      Align = alClient
      BevelOuter = bvNone
      Ctl3D = False
      ParentCtl3D = False
      TabOrder = 0
      object MemoDBG: TMemo
        Left = 0
        Top = 0
        Width = 823
        Height = 173
        TabStop = False
        Align = alClient
        BevelInner = bvNone
        BevelOuter = bvNone
        Color = clNavy
        Ctl3D = True
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = 'Fixedsys'
        Font.Style = []
        Lines.Strings = (
          'MemoDBG')
        ParentCtl3D = False
        ParentFont = False
        ScrollBars = ssBoth
        TabOrder = 0
        WantTabs = True
        WordWrap = False
        OnKeyDown = MemoDBGKeyDown
      end
    end
    object PanelOption: TPanel
      Left = 824
      Top = 1
      Width = 267
      Height = 173
      Margins.Left = 10
      Margins.Top = 10
      Margins.Right = 10
      Margins.Bottom = 10
      Align = alRight
      BevelOuter = bvNone
      Ctl3D = False
      ParentCtl3D = False
      TabOrder = 1
      object GroupBoxOption: TGroupBox
        AlignWithMargins = True
        Left = 10
        Top = 10
        Width = 247
        Height = 153
        Margins.Left = 10
        Margins.Top = 10
        Margins.Right = 10
        Margins.Bottom = 10
        Align = alClient
        Caption = 'Configurations'
        Padding.Left = 3
        Padding.Top = 3
        Padding.Right = 3
        Padding.Bottom = 3
        TabOrder = 0
        object CheckBoxWebtoonAutoSlider: TCheckBox
          Left = 17
          Top = 77
          Width = 124
          Height = 17
          Caption = 'Webtoon Auto Slider'
          TabOrder = 0
          OnClick = CheckBoxWebtoonAutoSliderClick
        end
        object CheckBoxPopup: TCheckBox
          Left = 17
          Top = 56
          Width = 97
          Height = 17
          Caption = 'Allow Popup'
          TabOrder = 1
          OnClick = CheckBoxPopupClick
        end
        object ComboBoxLocale: TComboBox
          Left = 17
          Top = 27
          Width = 85
          Height = 21
          Style = csDropDownList
          CharCase = ecUpperCase
          DropDownCount = 6
          ItemIndex = 0
          TabOrder = 2
          Text = 'ENG'
          OnSelect = ComboBoxLocaleSelect
          Items.Strings = (
            'ENG'
            'KOR'
            'JPN'
            'TW'
            'RU'
            'CN')
        end
      end
    end
    object PanelCloseOption: TPanel
      Left = 1091
      Top = 1
      Width = 24
      Height = 173
      Align = alRight
      BevelOuter = bvNone
      TabOrder = 2
      object Panel2: TPanel
        Left = 0
        Top = 0
        Width = 24
        Height = 24
        Align = alTop
        BevelOuter = bvNone
        TabOrder = 0
        object SpeedButtonClose: TSpeedButton
          Left = 0
          Top = 0
          Width = 24
          Height = 24
          Align = alClient
          Caption = 'X'
          OnClick = SpeedButtonCloseClick
        end
      end
    end
  end
  object EditTimerInterval: TEdit
    Left = 869
    Top = 2
    Width = 50
    Height = 21
    Hint = 'Interval Time'
    NumbersOnly = True
    TabOrder = 7
    Visible = False
    OnClick = EditTimerIntervalClick
    OnKeyDown = EditTimerIntervalKeyDown
  end
  object EditScroll: TEdit
    Left = 923
    Top = 2
    Width = 50
    Height = 21
    Hint = 'Scroll Value'
    NumbersOnly = True
    TabOrder = 8
    Visible = False
    OnClick = EditScrollClick
    OnKeyDown = EditScrollKeyDown
  end
  object PopupMenuTab: TPopupMenu
    Left = 311
    Top = 92
    object CopyTab: TMenuItem
      Caption = 'copy tab'
      OnClick = CopyTabClick
    end
    object ClosePopup: TMenuItem
      Caption = 'close'
      OnClick = ClosePopupClick
    end
  end
  object TimerWebtoon: TTimer
    Enabled = False
    Interval = 5000
    OnTimer = TimerWebtoonTimer
    Left = 393
    Top = 92
  end
end
