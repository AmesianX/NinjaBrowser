//---------------------------------------------------------------------------
// The NinjaBrowser was programmed by AmesianX in powerhacker.net.
// - The ninja browser is not a ninja bra. (amesianx@gmail.com)
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "uCEFWinControl"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
#define KEYDOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000 ? 1 : 0))
#define KEYUP(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000 ? 0 : 1))
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	// A flag that indicates whether the tab browser will attempt to terminate
	// after receiving a Windows message.
	// In addition to keyboard shortcuts, you can also try closing the browser
	// by clicking the Exit button with your mouse. You can also press the right
	// mouse button on the tab and try to exit. A flag is required because there
	// are multiple exit methods. The problem is that if you close a tab after
	// receiving a window message, you will have to call CloseBrowser.
	// (It is a monster that was born as a garbage while quickly implementing
	// code)
	is_DestroyTabBrowser = false;

	// Chrome windows do not appear anywhere, like panels, etc.
	// And you have to create a special window(TCEFWindowParent)
	// and paste it into it. Create a FullScreenWindow panel for
	// TChromium and attach it to the Form1(Main Form).
	// Make it invisible at first and make it visible when a fullscreen
	// request event occurs.
	FullScreenWindow = new TCEFWindowParent(Form1);
	FullScreenWindow->Parent = Form1;
	FullScreenWindow->Visible = false;
	is_FullScreen = false;

	// Put the address of the FullScreenWindow panel in the Form1's empty tag
	// value. This is because there is only one full screen in the program
	// anyway. It is a trick to make it easy to use the pointer at any time.
	// I will say one more time. Anyway the program has only one full screen.
	Form1->Tag = reinterpret_cast<NativeUInt>(FullScreenWindow);

	MemoDBG->Clear();
	MemoDBG->Font->Color = clWhite;

	PanelDevTools->Visible = false;
	Splitter1->Visible = false;

	// It is a measurement variable that stores how much time has passed.
	// Closing the tab too quickly will crash the program. I would like to
	// resolve this bug please. Conversely, creating a new tab too quickly
	// will also crash. Why does this problem occur? Somebody please fix it.
	// And please let me know.
	tCheckExit = time(0);
	tCheckExit2 = time(0);

	// Application exception handling routines and window message routines
	// for handling keyboard input.
	Application->OnException = AppException;
	Application->OnMessage = ApplicationEventsMessage;

	// First page
	AddTab("http://google.com");

	// Bookmark loading
	UnicodeString CurrDir = ExtractFilePath(ParamStr(0));
	UnicodeString BookMarkFile = CurrDir + "bookmark.dat";
	if (FileExists(BookMarkFile))
		LoadFile(BookMarkFile, ListViewHistory);

	// Loading locale options
	UnicodeString OptionFile = CurrDir + "locale.dat";
	if (FileExists(OptionFile))
		LoadOptions(OptionFile);
	else {
        locale = "ENG";
    }
}
//---------------------------------------------------------------------------
BOOL TForm1::CheckTimeOver(time_t tTime, time_t dwCheckTime)
{
	// This function is used to check how much time has passed.
	// I will not explain.
	time_t tCurrentTime = time(0);

	if(tCurrentTime >= tTime)
	{
		return ((tCurrentTime-tTime) >= dwCheckTime) ? TRUE : FALSE;
	}

	return ((tTime-((((time_t)(-1))-tTime)+tCurrentTime)) >= dwCheckTime) ? TRUE : FALSE;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::AppException(TObject *Sender, Exception *E)
{
	MemoDBG->Lines->Add("[+] AppException: "  + E->Message);
	ExitProcess(1);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCloseQuery(TObject *Sender, bool &CanClose)
{
	if (CheckBoxExit->Checked && !is_DestroyTabBrowser) {
		ExitProcess(1);
	}

	// If CanClose is false, the program will not be terminated.
	// Ordinary programmers may be confused. When the CloseBrowser
	// function is called, the program is terminated. Because it closes
	// the process. A single process is like a program itself, but
	// in a multiprocess, the process is a tab. (It is not a perfect
	// explanation. It is roughly so.)
	// Therefore, when CloseBrowser is called, program termination
	// is executed. You need to close the tab, not the program.
	CanClose = false;
	ExitBrowser(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::DestroyTabBrowser(TMessage &Message)
{
	// Get the TChromium pointer from the sender of the message.
	TChromium *chrome = reinterpret_cast<TChromium *>(Message.WParam);

	// If you are trying to close a tab, you must close it by calling
	// CloseBrowser in the case of a multiprocess. If the DevTools window
	// is open before calling this CloseBrowser, it must be closed with
	// CloseDevTools. Otherwise, the program crashes.
	if (PanelDevTools->Visible) {
		PanelDevTools->Visible = false;
		Splitter1->Visible = false;
		chrome->CloseDevTools(PanelMainDevTools);
	}

	if (PageControl1->PageCount == 1)
	{
		if (Application->MessageBox(L"Close the window and exit the program?", L"WARNING", MB_OKCANCEL|MB_ICONWARNING) == IDOK)
		{
			ExitProcess(1);
		}
	}
	else {
		if (chrome->Initialized)
		{
			// The currently closed window sets a flag that the message
			// is received and processed. (is_DestroyTabMsg).
			// That is, it means that the window is closed by the keyboard
			// shortcut.
			is_DestroyTabBrowser = true;
			chrome->CloseBrowser(true);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ChromiumAfterCreated(TObject *Sender, ICefBrowser * const browser)
{
	// Creating a new tab should be done with PostMessage. If you do not do
	// asynchronous processing, the chrome pointer is tied to the tab.
	// Pause coding and think about why. Then you will know easily.
	// Therefore, even if you release the tab, the chrome pointer remains, so
	// if you force the release, a memory leak occurs. Then all the malicious
	// bugs are potentially created. (For example, the window will disappear
	// while the browser is scrolling.)
	PostMessage(Handle, CEF_AFTERCREATED, reinterpret_cast<NativeUInt>(Sender), 0);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ChromiumBeforePopup(TObject *Sender, ICefBrowser * const browser,
		  ICefFrame * const frame, const ustring targetUrl, const ustring targetFrameName,
		  TCefWindowOpenDisposition targetDisposition, bool userGesture,
		  const TCefPopupFeatures &popupFeatures, TCefWindowInfo &windowInfo,
		  ICefClient *&client, TCefBrowserSettings &settings, ICefDictionaryValue *&extra_info,
		  bool &noJavascriptAccess, bool &Result)
{
	// Chrome will determine its behavior through options such as whether
	// to open a new window in itself or a tab in the NinjaBrowser.
	if (CheckBoxPopup->Checked) {
		// If "about:blank" comes in the targetUrl value, you should prevent it
		// from loading. Sometimes this happens when you enter a pop-up ad page
		// that appears several times at a time.
		if (targetUrl.Pos(L"about:blank") != 0) return;

		// I am testing these options. (Why use it?)
		windowInfo.external_begin_frame_enabled = true;
		windowInfo.shared_texture_enabled = true;

		// Open pop-up window with top-level window.
		windowInfo.ex_style = WS_EX_TOPMOST;

		EditSearch->Visible = false;

		// True : This option allows pop-up windows on its own by chrome engine core
		// False : This option can not pop-up itself. It opens in the NinjaBrowser tab.
		Result = False;
	}
	else {
		// If about: blank comes in the targetUrl value, you should prevent it
		// from loading. Sometimes this happens when you enter a pop-up ad page
		// that appears several times at a time.
		if (targetUrl.Pos(L"about:blank") != 0) return;

		windowInfo.external_begin_frame_enabled = true;
		windowInfo.shared_texture_enabled = true;

		SendURL = targetUrl;
		PostMessage(Handle, CHROMIUM_CREATE_BROWSER, reinterpret_cast<NativeUInt>(&SendURL), 0);

		EditSearch->Visible = false;

		// True : This option allows pop-up windows on its own by chrome engine core
		// False : This option can not pop-up itself. It opens in the NinjaBrowser tab.
		Result = True;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ChromiumConsoleMessage(TObject *Sender, ICefBrowser * const browser,
		  DWORD level, const ustring message, const ustring source,
		  int line, bool Result)
{
	// TChromium *chrome = reinterpret_cast<TChromium *>(Sender);

	// You can communicate with the NinjaBrowser through JavaScript's
	// console.log() function. It is very useful for simple communication
	// without using the Mojom IPC functions.
	// In this case, I made the JavaScript send a message when the window
	// close is executed. This is because the NinjaBrowser must be prevented
	// from closing by JavaScript. It is a temporary code and very bad code.
	// Most recently, the DisableJavascriptCloseWindows option was introduced
	// in CEF4DELPHI. So let's test this option.
	/*
	if (message.Pos("[IoCtlNinjaBrowser:OnClose]") > 0)
	{
		tCheckExit = time(0);
		tCheckExit2 = time(0);

		// Full screen mode should be turned off.
		// Otherwise, tab calculation may be incorrect.
		if (is_FullScreen) FullScreen(false);
		PostMessage(Handle, CHROMIUM_DESTROY_BROWSER, reinterpret_cast<NativeUInt>(chrome), 0);
	}
	*/
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ChromiumLoadStart(TObject *Sender, ICefBrowser * const browser,
		  ICefFrame * const frame, DWORD transitionType)
{
	// It is a MonkeySpider function.
	// You can run private JavaScript first when you start loading the page.
	if (CheckBoxPostProcess->Checked)
	{
		frame->ExecuteJavaScript(MemoJS->Text, "", 0);
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ChromiumLoadEnd(TObject *Sender, ICefBrowser * const browser,
		  ICefFrame * const frame, int httpStatusCode)
{
	StatusBar1->Panels->Items[0]->Width = 110;
	StatusBar1->Panels->Items[0]->Text = "Complete Loaded";

	UnicodeString javascript;

	// It is a MonkeySpider function.
	// It loads private JavaScript after the page is loaded.
	if (CheckBoxPostProcess->Checked) {
		frame->ExecuteJavaScript(MemoJS->Text, "", 0);
	}

	// This is a bad code. Implementation should be changed in the message
	// processing process.
	// You should prevent JavaScript from closing the NinjaBrowser.
	// Most recently, the DisableJavascriptCloseWindows option was introduced
	// in CEF4DELPHI. So let's test this option.
	/*
	frame->ExecuteJavaScript("window.close = function() {\r\n"
							 "    // Do Not Edit Code Here..\r\n"
							 "    console.log('[IoCtlNinjaBrowser:OnClose]');\r\n"
							 "};", "", 0);
	*/
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ExitBrowser(TObject *Sender)
{
	__try
	{
		// Get the chrome parent(TCEFWindowParent) window and chrome window
		// (TChromium) in the current tab.
		TCEFWindowParent *window = reinterpret_cast<TCEFWindowParent *>(PageControl1->ActivePage->Tag);
		TChromium *chrome = reinterpret_cast<TChromium *>(window->Tag);

		// Close search box
		EditSearch->Visible = false;

		// If the DevTools window is open, close it. If you do not, when
		// you try to close the window with a mouse click, it will be
		// displayed if the DevTools window is open.
		if (!is_DestroyTabBrowser && PanelDevTools->Visible) {
			PanelDevTools->Visible = false;
			Splitter1->Visible = false;
			chrome->CloseDevTools(PanelMainDevTools);
		}

		// The is_DirectCloseTab value is true when trying to close with
		// the mouse button. If the current page number is 1, closing
		// the window means ending the program. If cancel, simply return.
		// If you just close the program, you will get the PageIndex == -1
		// and the ExitProcess function will be executed.
		if (!is_DestroyTabBrowser && PageControl1->PageCount == 1)
		{
			if (Application->MessageBox(L"Close the window and exit the program?", L"WARNING", MB_OKCANCEL|MB_ICONWARNING) == IDCANCEL)
			{
				return;
			}
		}

		try {
			PageControl1->ActivePage->Free();
			PageControl1->SelectNextPage(false, true);
		} catch(const Exception &e) {
			// If you can not close the tab properly, you will get access
			// violation. If an exception occurs, print the log.
			// At this time, a memory leak occurs and the memory continues
			// to increase. But do not worry now that all bugs are fixed.
			// It was an old story.
			MemoDBG->Lines->Add("[-] ExitBrowser: " + e.Message);
		}

		// If the page count value is 0, there is no tab.
		// Therefore, exit the program with ExitProcess.
		// Why do not you do a normal shutdown process?
		// If you do a normal shutdown process with Application->Terminate etc.
		// you will get an error "Abnormal Terminate".
		// It is a chrome disease that happens when the Chrome browser
		// is not able to release memory quickly when unloading.
		// The libcef library is a chronic disease rather than a chronic disease
		// of chromium. So if you want to keep your mental health, it's a good
		// idea to just force it to ExitProcess.
		if (PageControl1->PageCount == 0) {
			ExitProcess(1);
		}
		else {
			TCEFWindowParent *window = reinterpret_cast<TCEFWindowParent *>(PageControl1->ActivePage->Tag);
			TChromium *chrome = reinterpret_cast<TChromium *>(window->Tag);
			chrome->SetFocus(true);
			EditURL->Text = chrome->DocumentURL;
		}
	}
	__finally {
		// It initializes each time the tab is closed.
		// This is because you can double-check whether you want to close
		// the window with a keyboard shortcut or with a mouse click.
		is_DestroyTabBrowser = false;

		StatusBar1->Panels->Items[0]->Width = 80;
		StatusBar1->Panels->Items[0]->Text = "Tab Deleted";
		StatusBar1->Panels->Items[1]->Text = "";
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ChromiumAddressChange(TObject *Sender, ICefBrowser * const browser,
          ICefFrame * const frame, const ustring url)
{
    TChromium *chrome = reinterpret_cast<TChromium *>(Sender);

    // MemoDBG->Lines->Add("[+] ChromiumAddressChange: " + chrome->Name);

    // It's just to more clearly verify the browser pointer.
    if (chrome->IsSameBrowser(browser))
    {
        // If you have a URL lock
        if (CheckBoxLockURL->Checked) {
            // Dynamically change the URL in the address bar only if you have
            // not modified it in the address bar. The reason is to prevent
            // the input value from being altered because the address is changed
            // during parameter modification like SQL Injection in URL.
            if (!EditURL->Focused()) {
                EditURL->Text = reinterpret_cast<TChromium *>(Sender)->Browser->MainFrame->Url;
            }
        } else {
            // If you do not want to lock, you can just change the URL.
            EditURL->Text = reinterpret_cast<TChromium *>(Sender)->Browser->MainFrame->Url;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ChromiumTitleChange(TObject *Sender, ICefBrowser * const browser,
          const ustring title)
{
    // of the NinjaBrowser. The reason is already annotated.
    TChromium *chrome = reinterpret_cast<TChromium *>(Sender);
    TTabSheet *tab = reinterpret_cast<TTabSheet *>(chrome->Tag);

    // MemoDBG->Lines->Add("[+] ChromiumTitleChange: " + chrome->Name);

    if (chrome->IsSameBrowser(browser))
    {
        // When TChromium navigates and the page moves, the title changes.
        // Set the changed value in the caption of the tab each time
        // the title is changed.
        if (title.Length() > 10)
        {
            UnicodeString retitle = title.SubString(1, 10);
            tab->Caption = retitle + "...";
        }
        else
        {
            tab->Caption = title;
        }
    }

    chrome->Name = "Automatic";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::AfterCreatedBrowser(TMessage &Message)
{
    // This is because the pop-up is not created in the tab.
    // The chrome engine opens the pop-up window itself.
    TChromium *chrome = reinterpret_cast<TChromium *>(Message.WParam);
    TTabSheet *tab = reinterpret_cast<TTabSheet *>(chrome->Tag);

    // MemoDBG->Lines->Add("[+] AfterCreatedBrowser: " + chrome->Name);

    // If the pop-up window is enabled and "Automatic" is selected, tap
    // processing is disabled. Because the pop-up window is processed
    // by Chrome itself.
    if (chrome->Name == "Automatic" && CheckBoxPopup->Checked) {
        return;
    }

    // If it is "Automatic" or "Direct", it processes the tab normally.
    if (chrome->Name == "Automatic" || chrome->Name == "Direct") {
        PageControl1->SelectNextPage(true, true);
        chrome->SetFocus(true);
        chrome->LoadURL(tab->Hint);
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CreateTabBrowser(TMessage &Message)
{
	EditSearch->Visible = false;

	StatusBar1->Panels->Items[0]->Width = 60;
	StatusBar1->Panels->Items[0]->Text = "Loading..";
	UnicodeString *URL = reinterpret_cast<UnicodeString *>(Message.WParam);

	if (URL->IsEmpty()) return;

	TTabSheet *tab = new TTabSheet(PageControl1);
	tab->Caption = "New Tab";

	// Calculate the page index where the newly created tab should be located.
	int PageIndex = PageControl1->TabIndex + 1;

	tab->PageControl = PageControl1;
	tab->PageIndex = PageIndex;

	// The TChromium component must be inserted into the TCEFWindowParent panel.
	TCEFWindowParent *window = new TCEFWindowParent(tab);
	window->Parent = tab;
	window->Color = clWhite;
	window->Align = alClient;
	tab->Tag = reinterpret_cast<NativeUInt>(window);

	// I program each time with a Chrome component inserted into the IDE.
	// When the code is complete, delete the component.
	// This is because the component is generated by dynamic code.
	TChromium *chrome = new TChromium(window);
	window->Tag = reinterpret_cast<NativeUInt>(chrome);
	tab->Hint = *URL;

	// If you do not set the DefaultUrl value, backtracking will be enabled
	// when you create a chrome window with a new tab.
	// To prevent this, you have to set the DefaultUrl value each time
	// you create a new chrome window.
	chrome->DefaultUrl = *URL;
	chrome->Tag = reinterpret_cast<NativeUInt>(tab);
	chrome->OnAfterCreated = (TOnAfterCreated)&ChromiumAfterCreated;
	chrome->OnAddressChange = (TOnAddressChange)&ChromiumAddressChange;
	chrome->OnTitleChange = (TOnTitleChange)&ChromiumTitleChange;
	chrome->OnBeforePopup = (TOnBeforePopup)&ChromiumBeforePopup;
	chrome->OnConsoleMessage = (TOnConsoleMessage)&ChromiumConsoleMessage;
	chrome->OnBeforeResourceLoad = (TOnBeforeResourceLoad)&ChromiumBeforeResourceLoad;
	chrome->OnFullScreenModeChange = (TOnFullScreenModeChange)&ChromiumFullScreenModeChange;
	chrome->OnPreKeyEvent = (TOnPreKeyEvent)&ChromiumPreKeyEvent;
	chrome->OnLoadStart = (TOnLoadStart)&ChromiumLoadStart;
	chrome->OnLoadEnd = (TOnLoadEnd)&ChromiumLoadEnd;
	chrome->OnBeforeContextMenu = (TOnBeforeContextMenu)&ChromiumBeforeContextMenu;
	chrome->OnContextMenuCommand = (TOnContextMenuCommand)&ChromiumContextMenuCommand;
	chrome->OnStatusMessage = (TOnStatusMessage)&ChromiumStatusMessage;
	chrome->OnTextResultAvailable = (TOnTextResultAvailableEvent)&ChromiumTextResultAvailable;
	chrome->OnLoadError = (TOnLoadError)&ChromiumLoadError;
	chrome->OnBeforeDownload = (TOnBeforeDownload)&ChromiumBeforeDownload;
	chrome->OnDownloadUpdated = (TOnDownloadUpdated)&ChromiumDownloadUpdated;
	chrome->CreateBrowser(window, "");
    // The "Automatic" flag means that the Chrome browser was created automatically.
    // Example: Link click or pop-up.
    // The reason for this markup is that tabs behave incorrectly
    // when opening a popup window.
    chrome->Name = "Automatic";

	StatusBar1->Panels->Items[0]->Width = 80;
	StatusBar1->Panels->Items[0]->Text = "Tab Created";
	StatusBar1->Panels->Items[1]->Text = "";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ButtonAddTabBrowserClick(TObject *Sender)
{
	EditSearch->Visible = false;

	StatusBar1->Panels->Items[0]->Width = 60;
	StatusBar1->Panels->Items[0]->Text = "Loading..";
	UnicodeString *URL = reinterpret_cast<UnicodeString *>(Sender);

	if (URL->IsEmpty()) return;

	TTabSheet *tab = new TTabSheet(PageControl1);
	tab->Caption = "New Tab";

	// Calculate the page index where the newly created tab should be located.
	int PageIndex = PageControl1->TabIndex + 1;

	tab->PageControl = PageControl1;
	tab->PageIndex = PageIndex;

	// The TChromium component must be inserted into the TCEFWindowParent panel.
	TCEFWindowParent *window = new TCEFWindowParent(tab);
	window->Parent = tab;
	window->Color = clWhite;
	window->Align = alClient;
	tab->Tag = reinterpret_cast<NativeUInt>(window);

	// I program each time with a TChromium component inserted into the IDE.
	// When the code is complete, delete the component.
	// This is because the TChromium is generated by dynamic code.
	TChromium *chrome = new TChromium(window);
	window->Tag = reinterpret_cast<NativeUInt>(chrome);
	tab->Hint = *URL;

	// If you do not set the DefaultUrl value, backtracking will be enabled
	// when you create a chrome window with a new tab.
	// To prevent this, you have to set the DefaultUrl value each time
	// you create a new chrome window.
	chrome->DefaultUrl = *URL;
	chrome->Tag = reinterpret_cast<NativeUInt>(tab);
	chrome->OnAfterCreated = (TOnAfterCreated)&ChromiumAfterCreated;
	chrome->OnAddressChange = (TOnAddressChange)&ChromiumAddressChange;
	chrome->OnTitleChange = (TOnTitleChange)&ChromiumTitleChange;
	chrome->OnBeforePopup = (TOnBeforePopup)&ChromiumBeforePopup;
	chrome->OnConsoleMessage = (TOnConsoleMessage)&ChromiumConsoleMessage;
	chrome->OnBeforeResourceLoad = (TOnBeforeResourceLoad)&ChromiumBeforeResourceLoad;
	chrome->OnFullScreenModeChange = (TOnFullScreenModeChange)&ChromiumFullScreenModeChange;
	chrome->OnPreKeyEvent = (TOnPreKeyEvent)&ChromiumPreKeyEvent;
	chrome->OnLoadStart = (TOnLoadStart)&ChromiumLoadStart;
	chrome->OnLoadEnd = (TOnLoadEnd)&ChromiumLoadEnd;
	chrome->OnBeforeContextMenu = (TOnBeforeContextMenu)&ChromiumBeforeContextMenu;
	chrome->OnContextMenuCommand = (TOnContextMenuCommand)&ChromiumContextMenuCommand;
	chrome->OnStatusMessage = (TOnStatusMessage)&ChromiumStatusMessage;
	chrome->OnTextResultAvailable = (TOnTextResultAvailableEvent)&ChromiumTextResultAvailable;
	chrome->OnLoadError = (TOnLoadError)&ChromiumLoadError;
	chrome->OnBeforeDownload = (TOnBeforeDownload)&ChromiumBeforeDownload;
	chrome->OnDownloadUpdated = (TOnDownloadUpdated)&ChromiumDownloadUpdated;
	chrome->CreateBrowser(window, "");
    // The "Direct" flag means that the Chrome browser was created manually.
    // Example: Button click or keyboard shortcut.
    // The reason for this markup is that tabs behave incorrectly
    // when opening a popup window.
    chrome->Name = "Direct";

	StatusBar1->Panels->Items[0]->Width = 80;
	StatusBar1->Panels->Items[0]->Text = "Tab Created";
	StatusBar1->Panels->Items[1]->Text = "";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::AddTab(UnicodeString URL)
{
	ButtonAddTabBrowserClick(reinterpret_cast<TObject *>(&URL));
}
//---------------------------------------------------------------------------
void __fastcall TForm1::PageControl1Change(TObject *Sender)
{
	TCEFWindowParent *window = reinterpret_cast<TCEFWindowParent *>(PageControl1->ActivePage->Tag);
	TChromium *chrome = reinterpret_cast<TChromium *>(window->Tag);
	TTabSheet *tab = reinterpret_cast<TTabSheet*>(chrome->Tag);

	// Close text search window
	EditSearch->Visible = false;

	if (tab->PageIndex == PageControl1->ActivePage->PageIndex)
	{
		// Each time a tab is changed, it is updated with the changed URL
		// in the URL window.
		EditURL->Text = chrome->DocumentURL;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::PageControl2Change(TObject *Sender)
{
	// Close text search window
	EditSearch->Visible = false;
}
//-------------------------------------------------------------------
void __fastcall TForm1::ApplicationEventsMessage(tagMSG &Msg, bool &Handled)
{
	TCEFWindowParent *window = reinterpret_cast<TCEFWindowParent *>(PageControl1->ActivePage->Tag);
	TChromium *chrome = reinterpret_cast<TChromium *>(window->Tag);

	TKeyboardState LKeyState;

	bool LIsAlt = false;
	bool LIsCtrl = false;

	if (Msg.message == CHROMIUM_KEYDOWN || Msg.message == WM_KEYDOWN)
	{
		if (GetKeyboardState(LKeyState)) {
			bool LIsF5 = (LKeyState[VK_F5] & 0x80) != 0 ? true : false;
			if (LIsF5) {
				// Full screen mode should be turned off.
				// Otherwise, tab calculation may be incorrect.
				if (is_FullScreen) FullScreen(false);

				EditSearch->Visible = false;
				chrome->Reload();
			}
		}
	}

	if (Msg.message == CHROMIUM_KEYUP || Msg.message == CHROMIUM_KEYDOWN ||
		Msg.message == WM_KEYDOWN)
	{
		if (Msg.wParam == VK_ESCAPE) {
			// Full screen mode should be turned off.
			// Otherwise, tab calculation may be incorrect.
			if (is_FullScreen) FullScreen(false);

			EditSearch->Visible = false;
			EditURL->Text = chrome->DocumentURL;
			chrome->StopFinding(true);
			Form1->Perform(WM_SETFOCUS, 0, 0);
			chrome->SetFocus(true);
		}
	}

	if (Msg.message == CHROMIUM_KEYDOWN || Msg.message == WM_KEYDOWN)
	{
		if (GetKeyboardState(LKeyState)) {
			LIsCtrl = (LKeyState[VK_CONTROL] & 0x80) != 0 ? true : false;
		}

		if ((Msg.wParam == 'f' || Msg.wParam == 'F') && LIsCtrl) {
			// Full screen mode should be turned off.
			// Otherwise, tab calculation may be incorrect.
			if (is_FullScreen) FullScreen(false);

			EditSearch->Visible = true;
			Form1->Perform(WM_SETFOCUS, 0, 0);
			EditSearch->SetFocus();
			EditSearch->SelectAll();
		}
	}

	// If you received a CHROMIUM_KEYDOWN message or received a WM_KEYDOWN
	if (Msg.message == CHROMIUM_KEYDOWN || Msg.message == WM_KEYDOWN)
	{
		if (GetKeyboardState(LKeyState)) {
			LIsAlt = (LKeyState[VK_LMENU] & 0x80) != 0 ? true : false;
		}

		if ((Msg.wParam == 'g' || Msg.wParam == 'G') && LIsAlt) {
			// Full screen mode should be turned off.
			// Otherwise, tab calculation may be incorrect.
			if (is_FullScreen) FullScreen(false);

			EditSearch->Visible = false;

			if (PanelHistory->Visible) {
				PanelHistory->Visible = false;
			}
			else if (!PanelHistory->Visible) {
				PanelHistory->Visible = true;
			}
		}
	}

	// If you received a CHROMIUM_KEYDOWN message or received WM_SYSCOMMAND (ALT key)
	if (Msg.message == CHROMIUM_KEYDOWN || Msg.message == WM_SYSCOMMAND)
	{
		// If the VK_LMENU (ALT) key is pressed
		if (GetKeyboardState(LKeyState)) {
			LIsAlt = (LKeyState[VK_LMENU] & 0x80) != 0 ? true : false;
		}

		if ((Msg.wParam == 'f' || Msg.wParam == 'F') && LIsAlt) {
			if (is_FullScreen) FullScreen(false);

			EditSearch->Visible = true;
			Form1->Perform(WM_SETFOCUS, 0, 0);
			EditSearch->SetFocus();
			EditSearch->SelectAll();
		}

		if ((Msg.wParam == 't' || Msg.wParam == 'T') && LIsAlt) {
			if (is_FullScreen) FullScreen(false);

			AddTab("https://google.com");
			Form1->Perform(WM_SETFOCUS, 0, 0);
			EditURL->SelectAll();
		}

		if (Msg.lParam == 'd' || Msg.lParam == 'D')
		{
			if (is_FullScreen) FullScreen(false);

			Form1->Perform(WM_SETFOCUS, 0, 0);
			EditURL->SetFocus();
			EditURL->SelectAll();
		}

		if (Msg.lParam == 'e' || Msg.lParam == 'E')
		{
			if (is_FullScreen) FullScreen(false);

			EditSearch->Visible = false;

			// If DevTools is open, close it and open it if it is closed.
			// The order of creation of panels and splitter is very important.
			// If you change the order of the splitter and panel, the splitter
			// can stick to the right end of the window.
			if (PanelDevTools->Visible) {
				// Do not change the visible order.
				PanelDevTools->Visible = false;
				Splitter1->Visible = false;
				chrome->CloseDevTools(PanelMainDevTools);
			}
			else {
				// DDo not change the visible order.
				chrome->ShowDevTools(TPoint(0, PanelDevToolsTop->Height), PanelMainDevTools);
				PanelDevTools->Visible = true;

				Splitter1->Width = 3;
				Splitter1->Align = alRight;
				Splitter1->Color = clRed;
				Splitter1->Visible = true;
			}

			// Open or close the DevTools window, and then focus again
			// on the chrome window. This is because it is easy to process
			// hot key input.
			Form1->Perform(WM_SETFOCUS, 0, 0);
			chrome->SetFocus(true);
		}

		if (Msg.lParam == '1')
		{
			if (is_FullScreen) FullScreen(false);

			if (PanelOptions->Visible) {
				PanelOptions->Visible = false;
			}
			else {
				PanelOptions->Visible = true;
				// Actually, the locale is treated as a "locale" variable.
				// However, if you want to show the ComboBoxLocale, find and set
				// the index.
				ComboBoxLocale->ItemIndex = ComboBoxLocale->Items->IndexOf(locale);
			}
		}

		if (Msg.lParam == '2')
		{
			if (is_FullScreen) FullScreen(false);

			PageControl1->SelectNextPage(false, true);
			chrome->SetFocus(true);
		}

		if (Msg.lParam == '3')
		{
			if (is_FullScreen) FullScreen(false);

			PageControl1->SelectNextPage(true, true);
			chrome->SetFocus(true);
		}

		if (Msg.lParam == 'r' || Msg.lParam == 'R')
		{
			if (is_FullScreen) FullScreen(false);

			chrome->Reload();
		}

		if (Msg.lParam == 'w' || Msg.lParam == 'W' ||
			Msg.lParam == 'q' || Msg.lParam == 'Q')
		{
			if (is_FullScreen) FullScreen(false);

			if (CheckTimeOver(tCheckExit, 2) || PageControl1->PageCount == 1)
			{
				tCheckExit = time(0);
				PostMessage(Handle, CHROMIUM_DESTROY_BROWSER, reinterpret_cast<NativeUInt>(chrome), 0);
			}
			else
			{
				// I want to fix a crash bug that occurs when I create a chrome
				// tab quickly or close it quickly. Please fix it. I'm wait for
				// the skilled person.
				StatusBar1->Panels->Items[0]->Width = 60;
				StatusBar1->Panels->Items[0]->Text = "Warning";
				StatusBar1->Panels->Items[1]->Text = "Continuously closing browsers is performed once every two seconds.";
				Form1->Perform(WM_SETFOCUS, 0, 0);
				chrome->SetFocus(true);
			}
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::EditURLKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	TCEFWindowParent *window = reinterpret_cast<TCEFWindowParent *>(PageControl1->ActivePage->Tag);
	TChromium *chrome = reinterpret_cast<TChromium *>(window->Tag);

	if (Key == vkReturn)
	{
		if (is_FullScreen) FullScreen(false);

		chrome->LoadURL(EditURL->Text);
	}

	if (Key == vkEscape)
	{
		EditURL->Text = chrome->DocumentURL;
		Form1->Perform(WM_SETFOCUS, 0, 0);
		chrome->SetFocus(true);
	}

	if ((Key == 'd' || Key == 'D') && Shift.Contains(ssAlt))
	{
		if (is_FullScreen) FullScreen(false);

		EditURL->SetFocus();
		EditURL->SelectAll();
	}

	if ((Key == 'e' || Key == 'E') && Shift.Contains(ssAlt))
	{
		if (is_FullScreen) FullScreen(false);

		EditSearch->Visible = false;

		if (PanelDevTools->Visible) {
			PanelDevTools->Visible = false;
			Splitter1->Visible = false;
			chrome->CloseDevTools(PanelMainDevTools);
		}
		else {
			chrome->ShowDevTools(TPoint(0, PanelDevToolsTop->Height), PanelMainDevTools);
			PanelDevTools->Visible = true;

			Splitter1->Width = 3;
			Splitter1->Align = alRight;
			Splitter1->Color = clRed;
			Splitter1->Visible = true;
		}

		Form1->Perform(WM_SETFOCUS, 0, 0);
		chrome->SetFocus(true);
	}

	if ((Key == '1') && Shift.Contains(ssAlt))
	{
		if (is_FullScreen) FullScreen(false);

		if (PanelOptions->Visible) {
			PanelOptions->Visible = false;
		}
		else {
			PanelOptions->Visible = true;
            ComboBoxLocale->ItemIndex = ComboBoxLocale->Items->IndexOf(locale);
		}
	}

	if ((Key == '2') && Shift.Contains(ssAlt))
	{
		if (is_FullScreen) FullScreen(false);

		PageControl1->SelectNextPage(false, true);
		chrome->SetFocus(true);
	}

	if ((Key == '3') && Shift.Contains(ssAlt))
	{
		if (is_FullScreen) FullScreen(false);

		PageControl1->SelectNextPage(true, true);
		chrome->SetFocus(true);
	}

	if ((Key == 'r' || Key == 'R') && Shift.Contains(ssAlt))
	{
		if (is_FullScreen) FullScreen(false);

		chrome->Reload();
	}

	if ((Key == 't' || Key == 'T') && Shift.Contains(ssAlt))
	{
		if (is_FullScreen) FullScreen(false);

		AddTab("https://google.com");
		Form1->Perform(WM_SETFOCUS, 0, 0);
		EditURL->SelectAll();
	}

	if ((Key == 'w' || Key == 'W' || Key == 'q' || Key == 'Q') && Shift.Contains(ssAlt))
	{
		if (is_FullScreen) FullScreen(false);

		if (CheckTimeOver(tCheckExit2, 2) || PageControl1->PageCount == 1)
		{
			tCheckExit2 = time(0);
			PostMessage(Handle, CHROMIUM_DESTROY_BROWSER, reinterpret_cast<NativeUInt>(chrome), 0);
		}
		else
		{
			// I want to fix a crash bug that occurs when I create a chrome tab
			// quickly or close it quickly. Please fix it. I'm wait for the
			// skilled person.
			StatusBar1->Panels->Items[0]->Width = 60;
			StatusBar1->Panels->Items[0]->Text = "Warning";
			StatusBar1->Panels->Items[1]->Text = "Continuously closing browsers is performed once every two seconds.";
			Form1->Perform(WM_SETFOCUS, 0, 0);
			chrome->SetFocus(true);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::EditSearchKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)
{
	TCEFWindowParent *window = reinterpret_cast<TCEFWindowParent *>(PageControl1->ActivePage->Tag);
	TChromium *chrome = reinterpret_cast<TChromium *>(window->Tag);

	if (Key == vkReturn)
	{
		if (EditSearch->Focused()) {
			chrome->Find(1, EditSearch->Text, true, false, false);
		}
	}

	if (Key == vkEscape)
	{
		EditSearch->Visible = false;
		chrome->StopFinding(true);
		Form1->Perform(WM_SETFOCUS, 0, 0);
		chrome->SetFocus(true);
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ChromiumPreKeyEvent(TObject *Sender, ICefBrowser * const browser,
		  const PCefKeyEvent event, PMsg osEvent, bool isKeyboardShortcut,
		  bool Result)
{
	TChromium *chrome = reinterpret_cast<TChromium *>(Sender);

	TMsg LMsg;

	if (!chrome->IsSameBrowser(browser)) return;
	if (event == NULL || osEvent == NULL) return;

	if (osEvent->message == WM_KEYDOWN) {
		LMsg = *osEvent;
		PostMessage(Handle, CHROMIUM_KEYDOWN, LMsg.wParam, LMsg.lParam);
		return;
	}

	if (osEvent->message == WM_KEYUP) {
		LMsg = *osEvent;
		PostMessage(Handle, CHROMIUM_KEYUP, LMsg.wParam, LMsg.lParam);
		return;
	}

	if (osEvent->message == WM_SYSKEYDOWN) {
		LMsg = *osEvent;
		PostMessage(Handle, CHROMIUM_KEYDOWN, LMsg.wParam, LMsg.lParam);
		return;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ChromiumBeforeResourceLoad(TObject *Sender, ICefBrowser * const browser,
		  ICefFrame * const frame, ICefRequest * const request,
		  ICefRequestCallback * const callback, TCefReturnValue Result)
{
	_di_ICefStringMultimap headers = new TCefStringMultimapOwn()->operator _di_ICefStringMultimap();
	const_cast<ICefRequest*>(request)->GetHeaderMap(headers);

	if (locale == "ENG") {
		headers->Append("Accept-Language", "en-US,en");
	}
	else if (locale == "KOR") {
		headers->Append("Accept-Language", "ko-KR,ko;en-US,en");
	}
	else if (locale == "JPN") {
		headers->Append("Accept-Language", "ja-JP,ja;en-US,en");
	}
	else if (locale == "TW") {
		headers->Append("Accept-Language", "zh-TW,tw;en-US,en");
	}
	else if (locale == "RU") {
		headers->Append("Accept-Language", "ru_RU,ru;en-US,en");
	}
	else if (locale == "CN") {
		headers->Append("Accept-Language", "zh-CN,cn;en-US,en");
	}
	else {
		headers->Append("Accept-Language", "ko-KR,ko;en-US,en");
        locale = "ENG";
	}

	const_cast<ICefRequest*>(request)->SetHeaderMap(headers);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::PageControl1Changing(TObject *Sender, bool &AllowChange)
{
	TCEFWindowParent *window = reinterpret_cast<TCEFWindowParent *>(PageControl1->ActivePage->Tag);
	TChromium *chrome = reinterpret_cast<TChromium *>(window->Tag);

	if (PanelDevTools->Visible)
	{
		Splitter1->Visible = false;
		PanelDevTools->Visible = false;
		chrome->CloseDevTools(PanelMainDevTools);

		Form1->Perform(WM_SETFOCUS, 0, 0);
		chrome->SetFocus(true);
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ChromiumFullScreenModeChange(TObject *Sender, ICefBrowser * const browser,
		  bool fullscreen)
{
	is_FullScreen = fullscreen;
	FullScreen(fullscreen);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FullScreen(bool fullscreen)
{
	TCEFWindowParent *window = reinterpret_cast<TCEFWindowParent *>(PageControl1->ActivePage->Tag);
	TChromium *chrome = reinterpret_cast<TChromium *>(window->Tag);

	if (fullscreen)
	{
		// Stores the form information of Form1.
		saved_Top = Form1->Top;
		saved_Left = Form1->Left;
		saved_Width = Form1->Width;
		saved_Height = Form1->Height;
		saved_Position = Form1->Position;
		saved_FormStyle = Form1->FormStyle;
		saved_BorderStyle = Form1->BorderStyle;

		// Eliminate Form1's title bar and increase it to full screen size.
		Form1->Top = 0;
		Form1->Left = 0;
		Form1->Width = Screen->Width;
		Form1->Height = Screen->Height;
		Form1->BorderStyle = bsNone;

		// Make the background of the full screen panel black.
		FullScreenWindow->Color = clBlack;
		// Make full-screen panels maximized.
		FullScreenWindow->Align = alClient;
		// Full-screen coordinates adjusted to maximum.
		FullScreenWindow->Left = 0;
		FullScreenWindow->Top = 0;
		FullScreenWindow->Width = Screen->Width;
		FullScreenWindow->Height = Screen->Height;

		// Replace the parent of the current chrome window
		// that was already created with the FullScreen panel.
		chrome->SetNewBrowserParent(FullScreenWindow->Handle);
		// Increase the size of the chrome window to the Form1 size.
		chrome->ResizeFormWidthTo(Form1->Width + 1);
		chrome->ResizeFormHeightTo(Form1->Height + 1);

		// Hide page controls to show them when restored.
		PageControl1->Visible = false;
		PageControl2->Visible = false;

		// Show full screen.
		FullScreenWindow->Visible = true;

		// Set to full screen with global flag value.
		is_FullScreen = true;
	}
	else {
		// Hides the full-screen panel.
		FullScreenWindow->Visible = false;

		// Chrome's parent window will be restored to its original panel window.
		chrome->SetNewBrowserParent(window->Handle);
		chrome->ResizeFormWidthTo(Form1->Width + 1);
		chrome->ResizeFormHeightTo(Form1->Height + 1);

		// Restore coordinate values and styles that were backed up before
		// full screen
		Form1->Top = saved_Top;
		Form1->Left = saved_Left;
		Form1->Width = saved_Width;
		Form1->Height = saved_Height;
		Form1->Position = saved_Position;
		Form1->FormStyle = saved_FormStyle;
		Form1->BorderStyle = saved_BorderStyle;

		// Finally, show the tab control again. The reason for taking this
		// method is that if you draw it again after the screening, it will
		// automatically draw and readjust it.
		PageControl1->Visible = true;
		PageControl2->Visible = true;

		// The global flag value indicates that the full screen is turned off.
		is_FullScreen = false;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SpeedButtonGoBackClick(TObject *Sender)
{
	// Go Back button
	TCEFWindowParent *window = reinterpret_cast<TCEFWindowParent *>(PageControl1->ActivePage->Tag);
	TChromium *chrome = reinterpret_cast<TChromium *>(window->Tag);
	chrome->GoBack();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SpeedButtonGoForwardClick(TObject *Sender)
{
	// Forward button
	TCEFWindowParent *window = reinterpret_cast<TCEFWindowParent *>(PageControl1->ActivePage->Tag);
	TChromium *chrome = reinterpret_cast<TChromium *>(window->Tag);
	chrome->GoForward();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SpeedButtonGoClick(TObject *Sender)
{
	TCEFWindowParent *window = reinterpret_cast<TCEFWindowParent *>(PageControl1->ActivePage->Tag);
	TChromium *chrome = reinterpret_cast<TChromium *>(window->Tag);

	if (is_FullScreen) FullScreen(false);

	EditSearch->Visible = false;

	if (PanelDevTools->Visible) {
		PanelDevTools->Visible = false;
		Splitter1->Visible = false;
		chrome->CloseDevTools(PanelMainDevTools);
	}

	chrome->LoadURL(EditURL->Text);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SpeedButtonAddTabClick(TObject *Sender)
{
	TCEFWindowParent *window = reinterpret_cast<TCEFWindowParent *>(PageControl1->ActivePage->Tag);
	TChromium *chrome = reinterpret_cast<TChromium *>(window->Tag);

	if (is_FullScreen) FullScreen(false);

	EditSearch->Visible = false;

	if (PanelDevTools->Visible) {
		PanelDevTools->Visible = false;
		Splitter1->Visible = false;
		chrome->CloseDevTools(PanelMainDevTools);
	}

	AddTab("https://google.com");

	Form1->Perform(WM_SETFOCUS, 0, 0);
	EditURL->SelectAll();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SpeedButtonDeleteTabClick(TObject *Sender)
{
	TCEFWindowParent *window = reinterpret_cast<TCEFWindowParent *>(PageControl1->ActivePage->Tag);
	TChromium *chrome = reinterpret_cast<TChromium *>(window->Tag);

	if (CheckTimeOver(tCheckExit, 2) || PageControl1->PageCount == 1)
	{
		tCheckExit = time(0);
		PostMessage(Handle, CHROMIUM_DESTROY_BROWSER, reinterpret_cast<NativeUInt>(chrome), 0);
	}
	else
	{
		StatusBar1->Panels->Items[0]->Width = 60;
		StatusBar1->Panels->Items[0]->Text = "Warning";
		StatusBar1->Panels->Items[1]->Text = "Continuously closing browsers is performed once every two seconds.";
		Form1->Perform(WM_SETFOCUS, 0, 0);
		chrome->SetFocus(true);
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SaveFile(UnicodeString filename, TComponent *a)
{
	// The following code saves the component itself as a file. (Serialize)
	int BufferSize;

	TWriter *FileWriter;
	TFileStream *FileStream;

	try {
		BufferSize = 1024;
		FileStream = new TFileStream(filename, fmOpenWrite | fmCreate);
		FileWriter = new TWriter(FileStream, BufferSize);
		FileWriter->WriteRootComponent(a);
	}
	__finally {
		delete FileWriter;
		delete FileStream;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::LoadFile(UnicodeString filename, TComponent *a)
{
	// The following code loads the components stored in the file. (DeSerialize)
	int BufferSize;

	TReader *FileReader;
	TFileStream *FileStream;
	UnicodeString Identification;

	try {
		BufferSize = 1024;
		FileStream = new TFileStream(filename, fmOpenRead);
		FileReader = new TReader(FileStream, BufferSize);
		FileReader->ReadRootComponent(a);
	}
	__finally {
		delete FileReader;
		delete FileStream;
	}
}
//-------------------------------------------------------------------------------
void __fastcall TForm1::SaveOptions(UnicodeString filename, UnicodeString locale)
{
	// The following code stores simple text in a file.
	// It is used to save the combo box locale selection to a file.
	int BufferSize;

	TWriter *FileWriter;
	TFileStream *FileStream;

	try {
		BufferSize = 1024;
		FileStream = new TFileStream(filename, fmOpenWrite | fmCreate);
		FileWriter = new TWriter(FileStream, BufferSize);
		FileWriter->WriteString(locale);
		MemoDBG->Lines->Add("[+] SaveOptions: " + locale);
	}
	__finally {
		delete FileWriter;
		delete FileStream;
	}
}
//------------------------------------------------------------------------------
void __fastcall TForm1::LoadOptions(UnicodeString filename)
{
	// The following code loads text from a file.
	// Used to set the locale selection in the combo box.
	int BufferSize;

	TReader *FileReader;
	TFileStream *FileStream;
	UnicodeString Identification;

	try {
		BufferSize = 1024;
		FileStream = new TFileStream(filename, fmOpenRead);
		FileReader = new TReader(FileStream, BufferSize);
		locale = FileReader->ReadString();
		MemoDBG->Lines->Add("[+] LoadOptions: " + locale);
	}
	__finally {
		delete FileReader;
		delete FileStream;
	}
}
//------------------------------------------------------------------------------
void __fastcall TForm1::ButtonGetAllClick(TObject *Sender)
{
	// Bookmark all the URLs of the open tabs at once.
	// I need to create a nesting removal function.
	__try {
		ListViewHistory->Items->BeginUpdate();

		for (int i = 0; i < PageControl1->PageCount; i++)
		{
			TCEFWindowParent *window = reinterpret_cast<TCEFWindowParent *>(PageControl1->Pages[i]->Tag);
			TChromium *chrome = reinterpret_cast<TChromium *>(window->Tag);
			TListItem *m_pItem = ListViewHistory->Items->Add();
			if (m_pItem)
			{
				m_pItem->SubItems->Add(chrome->DocumentURL);
			}
		}
	}
	__finally {
		ListViewHistory->Items->EndUpdate();

		// Save the contents of the history view as a bookmark file.
		UnicodeString CurrDir = ExtractFilePath(ParamStr(0));
		UnicodeString BookMarkFile = CurrDir + "bookmark.dat";
		SaveFile(BookMarkFile, ListViewHistory);
	}
}
//------------------------------------------------------------------------------
void __fastcall TForm1::ButtonAddHistoryClick(TObject *Sender)
{
	// Bookmark only the URL of the current tab.
	TCEFWindowParent *window = reinterpret_cast<TCEFWindowParent *>(PageControl1->ActivePage->Tag);
	TChromium *chrome = reinterpret_cast<TChromium *>(window->Tag);

	__try {
		ListViewHistory->Items->BeginUpdate();
		TListItem *m_pItem = ListViewHistory->Items->Add();
		if (m_pItem)
		{
			m_pItem->SubItems->Add(chrome->DocumentURL);
		}
	}
	__finally {
		ListViewHistory->Items->EndUpdate();

		UnicodeString CurrDir = ExtractFilePath(ParamStr(0));
		UnicodeString BookMarkFile = CurrDir + "bookmark.dat";
		SaveFile(BookMarkFile, ListViewHistory);
	}
}
//------------------------------------------------------------------------------
void __fastcall TForm1::ButtonDeleteHistoryClick(TObject *Sender)
{
	// If there is a selected item in the list view but no checked item, the
	// selected item is deleted.
	if (item.empty() && ListViewHistory->Selected)
	{
		ListViewHistory->Selected->Free();
	}

	TThread::Queue(NULL, Classes::_di_TThreadProcedure(new TListViewDeleteRef(ListViewHistory, &item)));

	UnicodeString CurrDir = ExtractFilePath(ParamStr(0));
	UnicodeString BookMarkFile = CurrDir + "bookmark.dat";
	SaveFile(BookMarkFile, ListViewHistory);

	CheckBoxAllSelect->Checked = false;
}
//------------------------------------------------------------------------------
void __fastcall TForm1::ButtonLoadHistoryClick(TObject *Sender)
{
    // Loads the currently selected bookmark item into the new tab.
	if (ListViewHistory->Selected)
	{
		SendURL = ListViewHistory->Selected->SubItems->Strings[0];
		PostMessage(Handle, CHROMIUM_CREATE_BROWSER, reinterpret_cast<NativeUInt>(&SendURL), 0);
	}
}
//--------------------------------------------------------------------------------
void __fastcall TForm1::ButtonLoadAllClick(TObject *Sender)
{
	// This feature is not yet implemented.
	// for (int i = 0; i < ListViewHistory->Items->Count; i++)
	// {
	if (ListViewHistory->Selected)
	{
		// SendURL = ListViewHistory->Items->Item[i]->SubItems->Strings[0];
		SendURL = ListViewHistory->Selected->SubItems->Strings[0];
		PostMessage(Handle, CHROMIUM_CREATE_BROWSER, reinterpret_cast<NativeUInt>(&SendURL), 0);
		Application->ProcessMessages();
	}
	// }
}
//--------------------------------------------------------------------------------
void __fastcall TForm1::ListViewHistoryDblClick(TObject *Sender)
{
	// Double-clicking on the bookmark will load the selected item
	// into the new tab.
	if (ListViewHistory->Selected)
	{
		SendURL = ListViewHistory->Selected->SubItems->Strings[0];
		PostMessage(Handle, CHROMIUM_CREATE_BROWSER, reinterpret_cast<NativeUInt>(&SendURL), 0);
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ListViewHistoryKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)
{
	// DEL key deletes the URL item from the history list.
	if (Key == vkDelete && ListViewHistory->Selected)
	{
		__try {
			ListViewHistory->Items->BeginUpdate();
			ListViewHistory->Selected->Free();
		}
		__finally {
			ListViewHistory->Items->EndUpdate();

			// Save it to your bookmark file because it has changed.
			UnicodeString CurrDir = ExtractFilePath(ParamStr(0));
			UnicodeString BookMarkFile = CurrDir + "bookmark.dat";
			SaveFile(BookMarkFile, ListViewHistory);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ListViewHistoryItemChecked(TObject *Sender, TListItem *Item)
{
	// If you check the URL item in the history list window.
	if (Item->Checked)
	{
		// Store the currently selected item in the vector for deletion.
		item.push_back(Item);
	}
	// What if you suddenly unchecked the URL item in the history list window?
	else
	{
		// Searches from vector and matches pointer value, deletes from
		// vector list.
		for(std::vector<TListItem*>::iterator it = item.begin(); it != item.end();)
		{
			if ((*it) == Item) {
				it = item.erase(it);
			} else {
				it++;
			}
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CheckBoxAllSelectClick(TObject *Sender)
{
	__try {

		if (ListViewHistory->Items->Count == 0) {
			CheckBoxAllSelect->Checked = false;
			return;
		}

		ListViewHistory->Items->BeginUpdate();

		for (int i = 0; i < ListViewHistory->Items->Count; i++)
		{
			// Select All URL list checked.
			if (CheckBoxAllSelect->Checked)
				ListViewHistory->Items->Item[i]->Checked = true;
			else
				ListViewHistory->Items->Item[i]->Checked = false;

			// It is used in loops to prevent unresponsiveness.
			Application->ProcessMessages();
		}
	}
	__finally {
		ListViewHistory->Items->EndUpdate();
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::PageControl1MouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	TCEFWindowParent *window = reinterpret_cast<TCEFWindowParent *>(PageControl1->ActivePage->Tag);
	TChromium *chrome = reinterpret_cast<TChromium *>(window->Tag);

	// This function allows you to select another tab with the right mouse button.
	if (Button == mbRight)
	{
		// You can get the tab index from the coordinates.
		int PageIndex = PageControl1->IndexOfTabAt(X, Y);

		if (PageIndex != PageControl1->TabIndex)
		{
			if (PanelDevTools->Visible) {
				PanelDevTools->Visible = false;
				Splitter1->Visible = false;
				chrome->CloseDevTools(PanelMainDevTools);
			}

			// Change tabs with mouse coordinates.
			PageControl1->TabIndex = PageControl1->IndexOfTabAt(X, Y);
			PageControl1->UpdateControlState();

			window = reinterpret_cast<TCEFWindowParent *>(PageControl1->ActivePage->Tag);
			chrome = reinterpret_cast<TChromium *>(window->Tag);

			Form1->Perform(WM_SETFOCUS, 0, 0);
			chrome->SetFocus(true);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ClosePopupClick(TObject *Sender)
{
	// Right-click to close the tab from the pop-up menu.
	TCEFWindowParent *window = reinterpret_cast<TCEFWindowParent *>(PageControl1->ActivePage->Tag);
	TChromium *chrome = reinterpret_cast<TChromium *>(window->Tag);
	PostMessage(Handle, CHROMIUM_DESTROY_BROWSER, reinterpret_cast<NativeUInt>(chrome), 0);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CopyTabClick(TObject *Sender)
{
	// Right mouse button Copy to new tab button.
	TCEFWindowParent *window = reinterpret_cast<TCEFWindowParent *>(PageControl1->ActivePage->Tag);
	TChromium *chrome = reinterpret_cast<TChromium *>(window->Tag);

	AddTab(chrome->DocumentURL);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ButtonDevToolsCloseClick(TObject *Sender)
{
	// Button to close DevTools.
	TCEFWindowParent *window = reinterpret_cast<TCEFWindowParent *>(PageControl1->ActivePage->Tag);
	TChromium *chrome = reinterpret_cast<TChromium *>(window->Tag);

	if (PanelDevTools->Visible) {
		PanelDevTools->Visible = false;
		Splitter1->Visible = false;
		chrome->CloseDevTools(PanelMainDevTools);
	}

	Form1->Perform(WM_SETFOCUS, 0, 0);
	chrome->SetFocus(true);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ChromiumStatusMessage(TObject *Sender, ICefBrowser * const browser, const ustring value)
{
	// Print a message in the status bar.
	StatusBar1->Panels->Items[0]->Width = 80;
	StatusBar1->Panels->Items[0]->Text = "NinjaBrowser";
	StatusBar1->Panels->Items[1]->Text = value;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ChromiumTextResultAvailable(TObject *Sender, const ustring aText)
{
	// It is a function used to view HTML source.
	// The function works, but I have not yet decided how to design the output.
	UnicodeString text = StringReplace(aText, "\n", "\r\n", TReplaceFlags()<<rfReplaceAll);
	MemoDBG->Lines->Add("[+] ChromiumTextResultAvailable:");
	MemoDBG->Lines->Add(text);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ChromiumBeforeContextMenu(TObject *Sender, ICefBrowser * const browser,
		  ICefFrame * const frame, ICefContextMenuParams * const params,
		  ICefMenuModel * const model)
{
	// Context menu that is visible when the right mouse button is clicked
	// in the browser.

	// This is a temporary code to implement opening in a new tab.
	// Do not implement this. This feature will not work properly
	// during download. This is due to the output of progress messages
	// during the download.
	if (StatusBar1->Panels->Items[1]->Text.SubString(0,8).LowerCase() == "https://" ||
		StatusBar1->Panels->Items[1]->Text.SubString(0,7).LowerCase() == "http://" ||
		StatusBar1->Panels->Items[1]->Text.SubString(0,6).LowerCase() == "ftp://")
	{
		model->Clear();
		model->AddItem(0, "Open Link in New &Tab");
		model->AddSeparator();
		model->AddItem(6, "Copy Link Loc&ation");
	}
	/*
	{
		model->Clear();
		model->AddItem(0, "Open Link in New &Tab");
		model->AddItem(1, "Open Link in New &Window");
		model->AddItem(2, "Open Link in &Private Window");
		model->AddSeparator();
		model->AddItem(3, "Bookmark This &Link");
		model->AddItem(4, "Save Lin&k As...");
		model->AddItem(5, "Copy Link Loc&ation");
		model->AddItem(6, "&Search Google for \"" + StatusBar1->Panels->Items[1]->Text.SubString(0,15) + "...\"");
		model->AddSeparator();
		model->AddItem(7, "Inspect Element (&O)");
	}
	*/
	else
	{
		model->Clear();
		model->AddItem(1, "Back");
		model->AddItem(2, "Forward");
		model->AddSeparator();
		model->AddItem(3, "Copy");
		model->AddItem(4, "Paste");
		model->AddSeparator();
		model->AddItem(5, "Reload");
		model->AddSeparator();
		model->AddItem(6, "Copy Link Loc&ation");
		model->AddItem(7, "View Page Source");
		model->AddSeparator();
		model->AddItem(999, "Quit");

		if (browser->CanGoBack()) {
			model->SetEnabled(1, true);
		}
		else {
			model->SetEnabled(1, false);
		}

		if (browser->CanGoForward()) {
			model->SetEnabled(2, true);
		}
		else {
            model->SetEnabled(2, false);
		}

		if (StatusBar1->Panels->Items[1]->Text.SubString(0,8).LowerCase() == "https://" ||
			StatusBar1->Panels->Items[1]->Text.SubString(0,7).LowerCase() == "http://" ||
			StatusBar1->Panels->Items[1]->Text.SubString(0,6).LowerCase() == "ftp://")
		{
			model->SetEnabled(6, true);
		}
		else {
			model->SetEnabled(6, false);
        }
	}
	/*
	else
	{
		model->Clear();
		model->AddItem(1, "Back");
		model->AddItem(2, "Forward");
		model->AddItem(3, "Reload");
		model->AddSeparator();
		model->AddItem(4, "Save As...");
		model->AddItem(5, "Print...");
		model->AddItem(6, "Cast...");
		model->AddItem(7, "Translate to English");
		model->AddSeparator();
		model->AddItem(8, "View Page Source");
		model->AddItem(9, "Inspect");
		model->AddSeparator();
		model->AddItem(10, "View Page Text");
		model->AddItem(999, "Quit");

		// model->SetAccelerator(1, VK_RIGHT, false, false, false);
		// model->SetAccelerator(2, VK_LEFT, false, false, false);
		// model->SetAccelerator(999, VK_ESCAPE, false, false, false);
	}
	*/
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ChromiumContextMenuCommand(TObject *Sender, ICefBrowser * const browser,
												   ICefFrame * const frame, ICefContextMenuParams * const params,
												   int commandId, DWORD eventFlags, bool Result)
{
	// Context menu that is visible when the right mouse button is clicked
	// in the browser.
	TChromium *chrome = reinterpret_cast<TChromium *>(Sender);

	switch(commandId) {
		case 0:
			SendURL = StatusBar1->Panels->Items[1]->Text;
			PostMessage(Handle, CHROMIUM_CREATE_BROWSER, reinterpret_cast<NativeUInt>(&SendURL), 0);
			break;
		case 1:
			browser->GoBack();
			break;
		case 2:
			browser->GoForward();
			break;
		case 3:
			frame->Copy();
			break;
		case 4:
			frame->Paste();
			break;
		case 5:
			browser->Reload();
			break;
		case 6:
			Clipboard()->SetTextBuf(StatusBar1->Panels->Items[1]->Text.c_str());
			break;
		case 7:
			chrome->RetrieveHTML(frame->Name);
			break;
		case 8:
			chrome->RetrieveText(frame->Name);
			break;
		case 999:
			PostMessage(Handle, CHROMIUM_DESTROY_BROWSER, reinterpret_cast<NativeUInt>(chrome), 0);
			break;
		default:
			break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ChromiumLoadError(TObject *Sender, ICefBrowser * const browser,
		  ICefFrame * const frame, int errorCode, const ustring errorText,
		  const ustring failedUrl)
{
	// It is not so difficult code, so I do not explain it.
	MemoDBG->Lines->Add("[-] ChromiumLoadError: " + errorText);
	MemoDBG->Lines->Add("[-] ChromiumLoadError URL: " + failedUrl);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ChromiumBeforeDownload(TObject *Sender, ICefBrowser * const browser,
		  ICefDownloadItem * const downloadItem, const ustring suggestedName,
		  ICefBeforeDownloadCallback * const callback)
{
	// It is not so difficult code, so I do not explain it.
	TChromium *chrome = reinterpret_cast<TChromium *>(Sender);

	ProgressBar1->Position = 0;

	bool flag;
	UnicodeString LSaveFullPath;
	UnicodeString LTempName;

	if (!chrome->IsSameBrowser(browser))
		return;

	if (downloadItem == NULL || !chrome->IsSameBrowser(browser) || !downloadItem->IsValid())
	{
		return;
	}

	if (suggestedName.IsEmpty()) {
		LTempName = "DownloadedFile.ninja";
	}
	else {
		LTempName = suggestedName;
	}

	if (LSaveDir.IsEmpty()) {
		LSaveDir = ExtractFileDir(Application->ExeName);
		flag = true;
	}
	else {
		flag = false;
	}

	LSaveFullPath = IncludeTrailingPathDelimiter(LSaveDir) + LTempName;

	callback->Cont(LSaveFullPath, flag);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ButtonResetDirClick(TObject *Sender)
{
	LSaveDir = "";
	StaticTextDownPath->Caption = "Download Path: ";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ChromiumDownloadUpdated(TObject *Sender, ICefBrowser * const browser,
		  ICefDownloadItem * const downloadItem, ICefDownloadItemCallback * const callback)
{
	// It is not so difficult code, so I do not explain it.
	TChromium *chrome = reinterpret_cast<TChromium *>(Sender);

	UnicodeString LTempString;

	if (!chrome->IsSameBrowser(browser))
		return;

	if (downloadItem->IsComplete()) {
		StatusBar1->Panels->Items[0]->Width =130;
		StatusBar1->Panels->Items[0]->Text = "Download Completed";
		StatusBar1->Panels->Items[1]->Text = downloadItem->FullPath;
		LSaveDir = ExtractFileDir(downloadItem->FullPath);
		StaticTextDownPath->Caption = "Download Path: " + ExtractFileDir(downloadItem->FullPath);
		ProgressBar1->Position = 100;
	}
	else if (downloadItem->IsCanceled()) {
		StatusBar1->Panels->Items[0]->Width =120;
		StatusBar1->Panels->Items[0]->Text = "Download Canceled";
		StatusBar1->Panels->Items[1]->Text = downloadItem->FullPath;
		LSaveDir = ExtractFileDir(downloadItem->FullPath);
		StaticTextDownPath->Caption = "Download Path: " + ExtractFileDir(downloadItem->FullPath);
		ProgressBar1->Position = 0;
	}
	else if (downloadItem->IsInProgress()) {
		//There are two cases where progress is processed as a percentage and
		// as bytes. When the total capacity is unknown, byte processing is
		// performed.
		if (downloadItem->FullPath.Length() > 0) {
			if (downloadItem->PercentComplete > 0) {
				LTempString = downloadItem->FullPath + " : " + IntToStr(downloadItem->PercentComplete) + "%";
				ProgressBar1->Position = downloadItem->PercentComplete;
				LSaveDir = ExtractFileDir(downloadItem->FullPath);
				StaticTextDownPath->Caption = "Download Path: " + ExtractFileDir(downloadItem->FullPath);
			}
			else if (downloadItem->ReceivedBytes > 0) {
				LTempString = downloadItem->FullPath + " : " + IntToStr(downloadItem->ReceivedBytes/1024) + " KBytes received";
				ProgressBar1->Position = 100;
				LSaveDir = ExtractFileDir(downloadItem->FullPath);
				StaticTextDownPath->Caption = "Download Path: " + ExtractFileDir(downloadItem->FullPath);
			}
			StatusBar1->Panels->Items[0]->Width = 90;
			StatusBar1->Panels->Items[0]->Text = "Downloading..";
			StatusBar1->Panels->Items[1]->Text = LTempString;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ButtonExplorerClick(TObject *Sender)
{
	if (LSaveDir.IsEmpty()) {
		ShellExecute(Application->Handle, NULL, L"explorer.exe", L"%userprofile%\\Documents", NULL, SW_NORMAL);
	}
	else {
		ShellExecute(Application->Handle, NULL, L"explorer.exe", LSaveDir.c_str(), NULL, SW_NORMAL);
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SpeedButtonCloseClick(TObject *Sender)
{
	PanelOptions->Visible = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::MemoDBGKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	TCEFWindowParent *window = reinterpret_cast<TCEFWindowParent *>(PageControl1->ActivePage->Tag);
	TChromium *chrome = reinterpret_cast<TChromium *>(window->Tag);

	if (Key == '1') {
		if (is_FullScreen) FullScreen(false);

		if (PanelOptions->Visible) {
			PanelOptions->Visible = false;
		}
		else {
			PanelOptions->Visible = true;
			ComboBoxLocale->ItemIndex = ComboBoxLocale->Items->IndexOf(locale);
		}

		Form1->Perform(WM_SETFOCUS, 0, 0);
		chrome->SetFocus(true);
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CheckBoxPopupClick(TObject *Sender)
{
	// Checkboxes can not process Alt + 1 messages. So I have to move focusing.
	MemoDBG->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ComboBoxLocaleSelect(TObject *Sender)
{
	MemoDBG->Lines->Add("[+] ComboBoxLocaleSelect: " + ComboBoxLocale->Text);

	UnicodeString CurrDir = ExtractFilePath(ParamStr(0));
	UnicodeString OptionFile = CurrDir + "locale.dat";
	SaveOptions(OptionFile, ComboBoxLocale->Text);

    // locale is a global variable.
	locale = ComboBoxLocale->Text;

	// Checkboxes can not process Alt + 1 messages. So I have to move focusing.
	MemoDBG->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SpeedButtonOpenOptionsClick(TObject *Sender)
{
	// Full screen mode should be turned off.
	// Otherwise, tab calculation may be incorrect.
	if (is_FullScreen) FullScreen(false);

	if (PanelOptions->Visible) {
		PanelOptions->Visible = false;
	}
	else {
		PanelOptions->Visible = true;
		ComboBoxLocale->ItemIndex = ComboBoxLocale->Items->IndexOf(locale);
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SpeedButtonEClick(TObject *Sender)
{
	TCEFWindowParent *window = reinterpret_cast<TCEFWindowParent *>(PageControl1->ActivePage->Tag);
	TChromium *chrome = reinterpret_cast<TChromium *>(window->Tag);

	if (is_FullScreen) FullScreen(false);

	EditSearch->Visible = false;

	if (PanelDevTools->Visible) {
		PanelDevTools->Visible = false;
		Splitter1->Visible = false;
		chrome->CloseDevTools(PanelMainDevTools);
	}
	else {
		chrome->ShowDevTools(TPoint(0, PanelDevToolsTop->Height), PanelMainDevTools);
		PanelDevTools->Visible = true;

		Splitter1->Width = 3;
		Splitter1->Align = alRight;
		Splitter1->Color = clRed;
		Splitter1->Visible = true;
	}

	Form1->Perform(WM_SETFOCUS, 0, 0);
	chrome->SetFocus(true);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SpeedButtonGClick(TObject *Sender)
{
	if (is_FullScreen) FullScreen(false);

	EditSearch->Visible = false;

	if (PanelHistory->Visible) {
		PanelHistory->Visible = false;
	}
	else if (!PanelHistory->Visible) {
		PanelHistory->Visible = true;
	}
}
//---------------------------------------------------------------------------
// Ignore this part of the code. It is a feature to view manga personally.
//---------------------------------------------------------------------------
void __fastcall TForm1::EditTimerIntervalClick(TObject *Sender)
{
	TimerWebtoon->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::EditScrollClick(TObject *Sender)
{
	TimerWebtoon->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::EditTimerIntervalKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if (Key == vkReturn)
	{
		TimerWebtoon->Interval = EditTimerInterval->Text.ToInt();
		TimerWebtoon->Enabled = true;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::EditScrollKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if (Key == vkReturn)
	{
		TimerWebtoon->Interval = EditTimerInterval->Text.ToInt();
		TimerWebtoon->Enabled = true;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CheckBoxWebtoonAutoSliderClick(TObject *Sender)
{
	if (CheckBoxWebtoonAutoSlider->Checked) {
		EditScroll->Text = "800";
		EditTimerInterval->Text = "3000";
		EditScroll->Visible = true;
		EditTimerInterval->Visible = true;
	}
	else {
		TimerWebtoon->Enabled = false;
		EditScroll->Visible = false;
		EditTimerInterval->Visible = false;
	}

	// Checkboxes can not process Alt + 1 messages. So I have to move focusing.
	MemoDBG->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::TimerWebtoonTimer(TObject *Sender)
{
	if (EditTimerInterval->Text.Trim().ToInt() == 0 ||
		EditScroll->Text.Trim().ToInt() == 0) {
		TimerWebtoon->Enabled = false;
	}
	else {
		TCEFWindowParent *window = reinterpret_cast<TCEFWindowParent *>(PageControl1->ActivePage->Tag);
		TChromium *chrome = reinterpret_cast<TChromium *>(window->Tag);
		chrome->SimulateMouseWheel(0, ("-" + EditScroll->Text.Trim()).ToInt());
		// keybd_event(VK_SPACE, 0x20, KEYEVENTF_EXTENDEDKEY | 0, 0);
	}

	// Checkboxes can not process Alt + 1 messages. So I have to move focusing.
	MemoDBG->SetFocus();
}
