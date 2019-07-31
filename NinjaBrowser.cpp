//---------------------------------------------------------------------------
// The NinjaBrowser was programmed by AmesianX in powerhacker.net.
// - The ninja browser is not a ninja bra. (amesianx@gmail.com)
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
#include "Unit1.h"
//---------------------------------------------------------------------------
USEFORM("Unit1.cpp", Form1);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		GlobalCEFApp = new TCefApplication();
		GlobalCEFApp->AddCustomCommandLine("flag-switches-begin", "1");
		GlobalCEFApp->CheckCEFFiles = true;
		GlobalCEFApp->FrameworkDirPath = "cef";
		GlobalCEFApp->ResourcesDirPath = "cef";
		GlobalCEFApp->LocalesDirPath = "cef\\locales";
		GlobalCEFApp->Cache = "cef\\cache";
		GlobalCEFApp->UserDataPath = "cef\\User Data";
		GlobalCEFApp->CustomFlashPath = "cef\\flash";
		GlobalCEFApp->WidevinePath = "cef\\WidevineCdm";
		GlobalCEFApp->DeleteCache = true;
		GlobalCEFApp->DeleteCookies = true;
		GlobalCEFApp->FlashEnabled = true;
		GlobalCEFApp->EnableSpeechInput = true;
		GlobalCEFApp->EnableMediaStream = true;
		GlobalCEFApp->DisableSafeBrowsing = true;
		GlobalCEFApp->DisableWebSecurity = false;
		// Do not annotate. high DPI problems may occur.
		// GlobalCEFApp->EnableHighDPISupport = true;
		// I've given the option with the same effect here, but it does not
		// seem to be activated.
		GlobalCEFApp->AddCustomCommandLine("high-dpi-support", "1");
		// The high DPI problem has been solved. It seems to be due to
		// the scale factor. It was resolved anyway.
		GlobalCEFApp->AddCustomCommandLine("force-device-scale-factor", "1");
		// If WindowlessRenderingEnabled is true, the Viz Service Display
		// Compositor is disabled. This feature is enabled in official Chrome.
		// <Pseudo Code of google's chromium sources>
		// if (WindowlessRenderingEnabled != true) {
		//     Viz Service Display Compositor = enabled;
		// }
		// else {
		//     Viz Service Display Compositor = disabled;
		// }
		GlobalCEFApp->WindowlessRenderingEnabled = false;
		// Never use a single process, you will have problems with the browser
		// disappearing. Use it only for debugging.
		GlobalCEFApp->SingleProcess = false;
		GlobalCEFApp->SitePerProcess = false;
		GlobalCEFApp->FastUnload = true;
		// If you want to be concerned about security, you must activate
		// the sandbox.
		GlobalCEFApp->NoSandbox = false;
		// Turning on the GPU option will speed up your browsing speeds dramatically.
		GlobalCEFApp->EnableGPU = true;
		GlobalCEFApp->Locale = "en";

		GlobalCEFApp->AddCustomCommandLine("enable-webgl-image-chromium", "1");
		GlobalCEFApp->AddCustomCommandLine("ignore-gpu-blacklist", "1");
		GlobalCEFApp->AddCustomCommandLine("enable-experimental-canvas-features", "1");
		GlobalCEFApp->AddCustomCommandLine("canvas-msaa-sample-count", "2");
		GlobalCEFApp->AddCustomCommandLine("force-display-list-2d-canvas", "1");
		GlobalCEFApp->AddCustomCommandLine("enable-accelerated-vpx-decode", "3");
		GlobalCEFApp->AddCustomCommandLine("enable-tcp-fastopen", "1");
		GlobalCEFApp->AddCustomCommandLine("javascript-harmony", "1");
		GlobalCEFApp->AddCustomCommandLine("enable-checker-imaging", "1");
		GlobalCEFApp->AddCustomCommandLine("v8-cache-options", "code");
		GlobalCEFApp->AddCustomCommandLine("v8-cache-strategies-for-cache-storage", "aggressive");
		GlobalCEFApp->AddCustomCommandLine("enable-accelerated-2d-canvas", "1");
		GlobalCEFApp->AddCustomCommandLine("enable-accelerated-video", "1");
		GlobalCEFApp->AddCustomCommandLine("enable-directwrite-for-ui", "1");
		GlobalCEFApp->AddCustomCommandLine("enable-direct-write", "1");
		// -----------
		// [WARNING!!]
		// -----------
		// If you want to use the "chrome://accessibility" feature, you need
		// to enable the following options. But this is an option you should
		// never use. This option creates a huge load on the dome. Some sites
		// are not browsable due to this option.
		// Therefore, be sure to turn it off.
		GlobalCEFApp->AddCustomCommandLine("force-renderer-accessibility", "0");
		GlobalCEFApp->AddCustomCommandLine("enable-native-gpu-memory-buffers", "1");
		GlobalCEFApp->AddCustomCommandLine("enable-zero-copy", "1");
		GlobalCEFApp->AddCustomCommandLine("ui-enable-zero-copy", "1");
		GlobalCEFApp->AddCustomCommandLine("enable-download-resumption", "1");
		GlobalCEFApp->AddCustomCommandLine("enable-smooth-scrolling", "1");
		// -----------
		// [WARNING!!]
		// -----------
		// Watch the video on YouTube after enabling the GPU option.
		// If the font is blurred and you can not see it correctly
		// during movie playback, there is a problem with DirectWrite 2D.
		// This problem is due to the gpu-compositing option in the GPU
		// acceleration. If this option is off, fonts will not break
		// even under GPU acceleration. It can degrade very little
		// performance. However, there is no performance degradation
		// compared to GPU full acceleration.
		// After checking with "chrome://gpu", check the performance
		// on the 3D WebGL site. Fitting the current options will result
		// in much faster 2D output.
		GlobalCEFApp->AddCustomCommandLine("disable-gpu-compositing", "1");
		GlobalCEFApp->AddCustomCommandLine("enable-gpu-rasterization", "1");
		GlobalCEFApp->AddCustomCommandLine("gpu-rasterization-msaa-sample-count", "2");
		GlobalCEFApp->AddCustomCommandLine("enable-begin-frame-scheduling", "1");
		GlobalCEFApp->AddCustomCommandLine("enable-vulkan", "1");
		GlobalCEFApp->AddCustomCommandLine("force-gpu-rasterization", "1");
		GlobalCEFApp->AddCustomCommandLine("flag-switches-end", "1");

		__try {

			if (GlobalCEFApp->StartMainProcess())
			{
				Application->Initialize();
				Application->MainFormOnTaskBar = true;
				Application->CreateForm(__classid(TForm1), &Form1);
				Application->Run();
			}
		}
		__finally {
			try {
				GlobalCEFApp->Free();
			}
			catch (Exception &exception)
			{
				ExitProcess(1);
			}
		}
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}

