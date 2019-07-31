//---------------------------------------------------------------------------
// The NinjaBrowser was programmed by AmesianX in powerhacker.net.
// - The ninja browser is not a ninja bra. (amesianx@gmail.com)
//---------------------------------------------------------------------------
#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include "uCEFApplication.hpp"
#include "uCEFChromium.hpp"
#include "uCEFWindowParent.hpp"
#include "uCEFStringMultimap.hpp"
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.Menus.hpp>
#include <Clipbrd.hpp>
#include "uCEFWinControl.hpp"
#include <vector>
//---------------------------------------------------------------------------
#include <map>
#define CHROMIUM_CREATE_BROWSER          WM_APP + 0x100
#define CHROMIUM_DESTROY_BROWSER         WM_APP + 0x101
#define CHROMIUM_AFTERCREATED_BROWSER    CEF_AFTERCREATED
#define CHROMIUM_KEYDOWN                 WM_APP + 0x103
#define CHROMIUM_KEYUP                   WM_APP + 0x104
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TMemo *MemoDBG;
	TEdit *EditURL;
	TEdit *EditSearch;
	TPanel *PanelTopMain;
	TPanel *PanelForward;
	TPanel *PanelURL;
	TPanel *PanelGo;
	TPanel *PanelBackward;
	TPanel *PanelDevTools;
	TPanel *PanelHistory;
	TPanel *PanelLockURL;
	TPanel *PanelAddTab;
	TPanel *PanelMenu;
	TPanel *PanelDevToolsTop;
	TButton *ButtonAddHistory;
	TButton *ButtonDeleteHistory;
	TButton *ButtonLoadAll;
	TButton *ButtonGetAll;
	TButton *ButtonLoadHistory;
	TButton *ButtonDevToolsClose;
	TSpeedButton *SpeedButtonGo;
	TSpeedButton *SpeedButtonGoBack;
	TSpeedButton *SpeedButtonAddTab;
	TSpeedButton *SpeedButtonGoForward;
	TPageControl *PageControl1;
	TPageControl *PageControl2;
	TTabSheet *TabSheet1;
	TTabSheet *TabSheet3;
	TListView *ListViewInspector;
	TListView *ListViewHistory;
	TCheckBox *CheckBoxLockURL;
	TCheckBox *CheckBoxAllSelect;
	TProgressBar *ProgressBar1;
	TStatusBar *StatusBar1;
	TSplitter *Splitter1;
	TPopupMenu *PopupMenuTab;
	TMenuItem *ClosePopup;
	TMenuItem *CopyTab;
	TButton *ButtonResetDir;
	TStaticText *StaticTextDownPath;
	TButton *ButtonExplorer;
	TCheckBox *CheckBoxExit;
	TPanel *PanelRight;
	TPanel *PanelOptions;
	TPanel *PanelDBG;
	TPanel *PanelOption;
	TGroupBox *GroupBoxOption;
	TSpeedButton *SpeedButtonClose;
	TPanel *PanelCloseOption;
	TPanel *Panel2;
	TTabSheet *TabSheet2;
	TMemo *MemoJS;
	TPanel *Panel3;
	TCheckBox *CheckBoxPreProcess;
	TCheckBox *CheckBoxPostProcess;
	TStaticText *StaticTextSpiderMonkey;
	TTimer *TimerWebtoon;
	TEdit *EditTimerInterval;
	TPanel *PanelDeleteTab;
	TSpeedButton *SpeedButtonDeleteTab;
	TCheckBox *CheckBoxWebtoonAutoSlider;
	TCEFWindowParent *PanelMainDevTools;
	TEdit *EditScroll;
	TTabSheet *TabSheet4;
	TPanel *PanelInspector;
	TStaticText *StaticTextInspector;
	TTabSheet *TabSheet5;
	TPanel *PanelDownload;
	TMemo *MemoDownload;
	TMemo *MemoREADME;
	TComboBox *ComboBoxLocale;
	TCheckBox *CheckBoxPopup;
	TPanel *PanelO;
	TSpeedButton *SpeedButtonOpenOptions;
	TPanel *PanelG;
	TPanel *PanelE;
	TSpeedButton *SpeedButtonG;
	TSpeedButton *SpeedButtonE;
	void __fastcall ChromiumAddressChange(TObject *Sender, ICefBrowser * const browser, ICefFrame * const frame, const ustring url);
	void __fastcall ChromiumAfterCreated(TObject *Sender, ICefBrowser * const browser);
	void __fastcall ChromiumTitleChange(TObject *Sender, ICefBrowser * const browser, const ustring title);
	void __fastcall ChromiumBeforePopup(TObject *Sender, ICefBrowser * const browser, ICefFrame * const frame, const ustring targetUrl, const ustring targetFrameName, TCefWindowOpenDisposition targetDisposition, bool userGesture, const TCefPopupFeatures &popupFeatures, TCefWindowInfo &windowInfo, ICefClient *&client, TCefBrowserSettings &settings, ICefDictionaryValue *&extra_info, bool &noJavascriptAccess, bool &Result);
	void __fastcall ChromiumConsoleMessage(TObject *Sender, ICefBrowser * const browser, DWORD level, const ustring message, const ustring source, int line, bool Result);
	void __fastcall ChromiumLoadEnd(TObject *Sender, ICefBrowser * const browser, ICefFrame * const frame, int httpStatusCode);
	void __fastcall ChromiumLoadStart(TObject *Sender, ICefBrowser * const browser, ICefFrame * const frame, DWORD transitionType);
	void __fastcall ChromiumPreKeyEvent(TObject *Sender, ICefBrowser * const browser, const PCefKeyEvent event, PMsg osEvent, bool isKeyboardShortcut, bool Result);
	void __fastcall ChromiumBeforeResourceLoad(TObject *Sender, ICefBrowser * const browser, ICefFrame * const frame, ICefRequest * const request, ICefRequestCallback * const callback, TCefReturnValue Result);
	void __fastcall ChromiumFullScreenModeChange(TObject *Sender, ICefBrowser * const browser, bool fullscreen);
	void __fastcall ChromiumContextMenuCommand(TObject *Sender, ICefBrowser * const browser, ICefFrame * const frame, ICefContextMenuParams * const params, int commandId, DWORD eventFlags, bool Result);
	void __fastcall ChromiumBeforeContextMenu(TObject *Sender, ICefBrowser * const browser, ICefFrame * const frame, ICefContextMenuParams * const params, ICefMenuModel * const model);
	void __fastcall ChromiumStatusMessage(TObject *Sender, ICefBrowser * const browser, const ustring value);
	void __fastcall ChromiumTextResultAvailable(TObject *Sender, const ustring aText);
	void __fastcall ChromiumLoadError(TObject *Sender, ICefBrowser * const browser, ICefFrame * const frame, int errorCode, const ustring errorText, const ustring failedUrl);
	void __fastcall ChromiumBeforeDownload(TObject *Sender, ICefBrowser * const browser, ICefDownloadItem * const downloadItem, const ustring suggestedName, ICefBeforeDownloadCallback * const callback);
	void __fastcall ChromiumDownloadUpdated(TObject *Sender, ICefBrowser * const browser, ICefDownloadItem * const downloadItem, ICefDownloadItemCallback * const callback);
	void __fastcall PageControl1Change(TObject *Sender);
	void __fastcall PageControl1Changing(TObject *Sender, bool &AllowChange);
	void __fastcall PageControl1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall PageControl2Change(TObject *Sender);
	void __fastcall SpeedButtonGoBackClick(TObject *Sender);
	void __fastcall SpeedButtonGoForwardClick(TObject *Sender);
	void __fastcall SpeedButtonGoClick(TObject *Sender);
	void __fastcall SpeedButtonAddTabClick(TObject *Sender);
	void __fastcall ButtonAddHistoryClick(TObject *Sender);
	void __fastcall ButtonLoadAllClick(TObject *Sender);
	void __fastcall ButtonDeleteHistoryClick(TObject *Sender);
	void __fastcall ButtonGetAllClick(TObject *Sender);
	void __fastcall ButtonLoadHistoryClick(TObject *Sender);
	void __fastcall ListViewHistoryDblClick(TObject *Sender);
	void __fastcall ListViewHistoryKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall ListViewHistoryItemChecked(TObject *Sender, TListItem *Item);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall EditURLKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall EditSearchKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall CheckBoxAllSelectClick(TObject *Sender);
	void __fastcall ButtonDevToolsCloseClick(TObject *Sender);
	void __fastcall CopyTabClick(TObject *Sender);
	void __fastcall ClosePopupClick(TObject *Sender);
	void __fastcall ButtonResetDirClick(TObject *Sender);
	void __fastcall ButtonExplorerClick(TObject *Sender);
	void __fastcall SpeedButtonCloseClick(TObject *Sender);
	void __fastcall MemoDBGKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall TimerWebtoonTimer(TObject *Sender);
	void __fastcall EditTimerIntervalKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall EditTimerIntervalClick(TObject *Sender);
	void __fastcall SpeedButtonDeleteTabClick(TObject *Sender);
	void __fastcall EditScrollClick(TObject *Sender);
	void __fastcall EditScrollKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall CheckBoxWebtoonAutoSliderClick(TObject *Sender);
	void __fastcall CheckBoxPopupClick(TObject *Sender);
	void __fastcall ComboBoxLocaleSelect(TObject *Sender);
	void __fastcall SpeedButtonOpenOptionsClick(TObject *Sender);
	void __fastcall SpeedButtonEClick(TObject *Sender);
	void __fastcall SpeedButtonGClick(TObject *Sender);

private:	// User declarations
	UnicodeString SendURL;
	std::vector<TListItem*> item;
	void __fastcall FullScreen(bool fullscreen);
	void __fastcall AddTab(UnicodeString URL);
	void __fastcall ExitBrowser(TObject *Sender);
	void __fastcall AppException(TObject *Sender, Exception *E);
	void __fastcall ApplicationEventsMessage(tagMSG &Msg, bool &Handled);
	void __fastcall ButtonAddTabBrowserClick(TObject *Sender);
	MESSAGE void __fastcall CreateTabBrowser(Winapi::Messages::TMessage &Message);
	MESSAGE void __fastcall DestroyTabBrowser(Winapi::Messages::TMessage &aMessage);
	MESSAGE void __fastcall AfterCreatedBrowser(Winapi::Messages::TMessage &aMessage);
	BEGIN_MESSAGE_MAP
		VCL_MESSAGE_HANDLER(CHROMIUM_CREATE_BROWSER, TMessage, CreateTabBrowser);
		VCL_MESSAGE_HANDLER(CHROMIUM_DESTROY_BROWSER, TMessage, DestroyTabBrowser);
		VCL_MESSAGE_HANDLER(CHROMIUM_AFTERCREATED_BROWSER, TMessage, AfterCreatedBrowser);
	END_MESSAGE_MAP(TForm)

public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
	BOOL CheckTimeOver(time_t, time_t);
	void __fastcall LoadFile(UnicodeString, TComponent *);
	void __fastcall SaveFile(UnicodeString, TComponent *);
	void __fastcall SaveOptions(UnicodeString, UnicodeString);
	void __fastcall LoadOptions(UnicodeString);

	int saved_Left;
	int saved_Top;
	int saved_Width;
	int saved_Height;

	bool is_FullScreen;
	bool is_DestroyTabBrowser;

	UnicodeString locale;
	UnicodeString LSaveDir;

	TPosition saved_Position;
	TFormStyle saved_FormStyle;
	TFormBorderStyle saved_BorderStyle;
	TCEFWindowParent *FullScreenWindow;
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
static time_t tCheckExit;
static time_t tCheckExit2;
//------------------------------------------------------------------------------
class TListViewDeleteRef : public TCppInterfacedObject<Classes::TThreadProcedure>
{
private:
	TListView *listview;
	std::vector<TListItem*> *item;
public:
	TListViewDeleteRef(TListView *_listview, std::vector<TListItem*> *_item)
	: listview(_listview), item(_item) { }
	INTFOBJECT_IMPL_IUNKNOWN(TInterfacedObject);

	void __fastcall Invoke()
	{
		__try {
			listview->Items->BeginUpdate();

			for (std::vector<TListItem*>::iterator it = item->begin();
				 it != item->end(); ++it)
			{
				(*it)->Delete();
			}
		}
		__finally {
			listview->Items->EndUpdate();
			item->clear();
		}
	}
};
//---------------------------------------------------------------------------
// There are two ways to retrieve and retrieve components that are mounted
// within a component.
/*
void EnumerateAll(TComponent *container)
{
	// Enumarate its children
	for (int i = 0; i < container->ComponentCount; i++)
	{
		// extract the control at index i
		TComponent *child = container->Components[i];

		if (child->InheritsFrom (__classid(TComponent))) //this check is optional
			Form1->MemoDBG->Lines->Add(child->Name);
	}
}
//---------------------------------------------------------------------------
void ExtractAll_Structure(TWinControl *container, int &indent)
{
	// Enumarate its children
	for (int i = 0; i < container->ControlCount; i++)
	{
		// extract the control at index i
		TComponent *child2 = container->Controls[i];

		if (child2->InheritsFrom(__classid(TComponent)) )  // this check if optional
		{
			Form1->MemoDBG->Lines->Add(child2->Name);

			// Is this a container for other controls
			TWinControl *winctrl = dynamic_cast<TWinControl*>(child2);
			if (winctrl)
			{
				indent++;
				ExtractAll_Structure(winctrl, indent);
				indent--;
			}
		}
	}
}
*/
//---------------------------------------------------------------------------
#endif
