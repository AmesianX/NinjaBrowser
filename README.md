## [NinjaBrowser]  
The NinjaBrowser is an open source browser project based on CEF4DELPHI.  
- Programmed by AmesianX in powerhacker.net. (amesianx@gmail.com)  
- https://github.com/amesianx/ninjabrowser.git  
- The NinjaBrowser is not a ninja bra.  
  
  
## [Why deploy a NinjaBrowser?]  
The NinjaBrowser has the most optimized chrome engine options when using libcef  
through many tests. The browsing speed of the NinjaBrowser is very fast now.  
I know that there are a number of bugs in other projects using libcef.  
I solve the problem and share such a bug. For example, how to fix a DirectWrite 2D  
problem with the GPU enabled. And I have a solution to the problem of why Netflix  
does not play or why regular videos do not play.  
Netflix is not played unless you enable the widevine DRM module. And The default  
distribution of CEF4DELPHI can not play next video link.  
(Example video test link: https://tv.kakao.com/channel/2653401/cliplink/395496297)  
There are a number of problems and solved most problems. (The high DPI resizing  
problem causes the CSS layout of the screen to be distorted.)  
The features I wanted to develop have not been touched yet.  
What is the benefit of additional features if you are not at least comfortable  
browsing? My additional features are meaningful when basic browsing is perfect.  
So I decided to share some basic browsing stability.  
The extravagant features still need further development.  
For example Google translation site features and so on. And a download manager  
with minimal functionality. There are still more luxurious basic features, but  
I can not touch them. It's just like basic features for ordinary people, and  
very extravagant features for developers. :)  
I can not download Google Drive from my Ninja browser right now.  
I found this problem before the final deployment.  
If someone can solve this problem, please let me know how. (T.T)  
  
  
## [Left-hand key usage]  
The NinjaBrowser has a key layout that makes it easy to operate the browser with the left hand.  
  
Alt+1 : Open debugging window for hidden NinjaBrowser development  
Alt+2 : Go to left tab  
Alt+3 : Go to right tab  
Alt+T : Open new tab  
Alt+W : Close Tab (or Alt+Q)  
Alt+E : Open Developer Tools  
Alt+G : NinjaBrowser Bookmark  
Alt+R : Reload browser  
  
Lock: The Lock check box locks the URL input window. This feature prevents  
      hothaeded users from entering incorrectly when attempting to enter  
      the URL input window while the site navigating is changing.  
  
Exit: If you clear the Exit checkbox, when you click Exit on the window  
      the tab will close instead of closing the program.  
  
  
## [Download and install CEF4Delphi]  
You must download the CEF4DELPHI source from github.  
- git clone https://github.com/salvadordf/CEF4Delphi.git  
  
Then you need to open the "uCEFApplication.pas" file and modify the build version  
of libcef as follows:  
  
CEF_SUPPORTED_VERSION_MAJOR   = 75;  
CEF_SUPPORTED_VERSION_MINOR   = 1;  
CEF_SUPPORTED_VERSION_RELEASE = 14;  
CEF_SUPPORTED_VERSION_BUILD   = 0;  
  
CEF_CHROMEELF_VERSION_MAJOR   = 75;  
CEF_CHROMEELF_VERSION_MINOR   = 0;  
CEF_CHROMEELF_VERSION_RELEASE = 3770;  
CEF_CHROMEELF_VERSION_BUILD   = 100;  
  
  
## [Using the prebuilt version]  
Download the "pre-built_cef_v.75.0.3770.100.zip" file from the following link:  
- https://drive.google.com/file/d/1eZp0R4l2DZDQU6K18B1arXjLjjzy6-7r/view?usp=sharing  
  
Unpack it and rename it to "cef" and place it in the directory where NinjaBrowser's  
executable is located.  
  
  
## [How to build libcef]  
If you do not want to use prebuilt libcef, you can build libcef in the following  
way. But I do not recommend it. Each build takes a half day.  
If you try to build for the first time, it will take two days.  
It is a measure of the Xeon CPU when you build a 2 cpu core using a VirtualBox  
virtual machine. There are bugs in the VirtualBox that slow down the use of more  
than two Xeon CPU cores. On a typical CPU, it will probably take an average of  
half a day. If you are ready, please follow me.  
  
You can build the libcef package by running it in the following order:  
  
Download the "libcef_builder_20190731.zip" file and extract it to the "c:\Google".  
- https://drive.google.com/file/d/1EDg3VgSAhslHmiKZdmzhDaFbXZ5Xlrps/view?usp=sharing  
  
The directory name must be the same. Add the "C:\Google\depot_tools" path to  
your Windows system's PATH environment variable.  
  
1. cd c:\Google  
2. run_update_cef.bat  
3. run_create_cef.bat  
4. build_cef.bat  
  
  
## [How to build to support widevine module]  
The widevine module is a DRM module. And without this module, you can not see Netflix.  
You need to modify the following files before running create_cef.bat:  
  
C:\Google\chromium_git\chromium\src\third_party\widevine\cdm\widevine_cdm_version.h  
  
Added two lines into it:  

#define WIDEVINE_CDM_AVAILABLE
#define WIDEVINE_CDM_VERSION_STRING 4.10.1440.18
  
After compilation is finished, you must include the widevinecdm.dll file  
in the final build package. You can extract the widevine.dll file from  
the latest 32-bit version of the Google Chrome browser.  
At this time, the manifest.json file should have the following configuration.  
Also, if you do not use ia32 in the manifest.json file, it will not be loaded.  
Many people may mistake it to be x86, not ia32.  
  
The contents of the "manifest.json" file should look like this:  
  
{  
  "manifest_version": 2,  
  "update_url": "https://clients2.google.com/service/update2/crx",  
  "name": "WidevineCdm",  
  "description": "Widevine Content Decryption Module",  
  "version": "4.10.1440.18",  
  "minimum_chrome_version": "68.0.3430.0",  
  "x-cdm-module-versions": "4",  
  "x-cdm-interface-versions": "10",  
  "x-cdm-host-versions": "10",  
  "x-cdm-codecs": "vp8,vp9.0,avc1",  
  "x-cdm-persistent-license-support": true,  
  "x-cdm-supported-encryption-schemes": ["cenc","cbcs"],  
  "os": "win",  
  "arch": "ia32"  
}  
  
  
## [Development History]  
I started developing my own browser with the earliest version of DCEF3.  
I have been developing a NinjaBrowser since 2010 whenever I have free time.  
The NinjaBrowser is my private browser that uses the Chrome Browser Engine  
as the core. I wanted to develop a private browser as an HTTP Inspector  
like a proxy. But it's not just for that reason. I have more ideas.  
For example, build qemu and attach it to the NinjaBrowser. I will install  
the Mattermost server to qemu. I will port the qemu console screen to the  
NinjaBrowser tab. The NinjaBrowser will have a portable mattermost chat  
server. The idea of porting qemu to NinjaBrowser will allow a lot of services  
to work locally. And a portable program. This idea is just the tip of the  
iceberg. Browser-based GDB is also planned. Installing python inside qemu  
will also enable browser-based GDB(MultiArch GDB) in the NinjaBrowser.  
It also uses python in qemu, so you can call youtube-dl from a NinjaBrowser.  
This makes it easy to implement the youtube video download feature in the  
NinjaBrowser. All these ideas are just planned. I have not been able to  
implement because of a lack of time because of my damn job.  
I will also work on porting JavaScript editors to NinjaBrowser just like  
electron based programs(like embedded nodejs). And I will also attach d8.exe  
(v8 debugger). This is because of my vulnerability exploit job.  
During the initial development, the project had been delayed for years  
because of a critical bug in the libcef library and DCEF3 wrapper.  
DCEF means DelphiChromiumEmbedded and DCEF3 is a project that wraps the chrome  
engine in the Delphi language. This DCEF3 component can also be used in C++ Builder  
when installed in Delphi. However, the initial version of DCEF3 was very unstable.  
It was almost impossible to make a program. Moreover, I could not solve the problem  
of crashing while scrolling the browser. Ten years later, someone started an amazing  
project called CEF4DELPHI. I really want to thank the CEF4DELPHI developers.  
Thank you so much that I can achieve my ideals. So I was able to rebuild the existing  
code from the CEF4DELPHI component and test it. The bug has disappeared.  
Moreover, I was able to update a lot of existing code recently.  
For example, The NinjaBrowser use GPU rendering instead of software rendering.  
And solved the DirectWrite 2D problem, which is a critical problem.  
(GDI font blurring due to GPU compositing acceleration problem).  
As a result, the browsing speed was greatly improved. It also enabled h264 multimedia  
features in Chrome Engine. I also added the ability to play Netflix by enabling  
widevine DRM and the Adobe Flash enabling. Netflix uses DRM to protect the video  
stream, so you need to enable a DRM module called widevine. It also has full-screen  
capabilities. In addition, the locale for the country is displayed correctly on Google  
or YouTube. It works much more reliably than with previous DCEF3.  
However, there is still a problem. If you add a tab quickly or close a tab quickly  
a crash occurs. So it takes a way to give delay. This problem is the most dirty  
code part. There is a flicker on the site where Adobe Flash is currently running.  
The console window is briefly visible and disappears. I plan to apply the MS Detours  
library to solve this problem. You need to hook the CreateProcess win32 API function.  
I will hook the Adobe Flash plug-in to prevent the console window from showing.  
The MS Detours library is my area of expertise and can be easily applied.  
  
  
## [Why C++ Builder? Not Delphi?]  
I can use various languages, but I use C/C++ as my main language.  
The C/C++ language is the easiest.  
If I joke a bit, it's even easier than Python.  
The reason is that too much code is hidden in Python's components.  
I have been using the C/C++ as the main language since 1992.  
But, you know, most core programmers have a fatal problem.  
It does not study frontend code. I can produce all the function code.  
But it is not easy to write the best UI code that looks pretty.  
In fact, for the core programmer, UI code is wasted code.  
This is not really the code that performs the core functions of the program.  
It is the reality of all programmers. So we have to choose.  
You should find and use a framework or library that will take care of this waste code.  
Therefore, C++ Builder and QT are the frameworks that will cover this frontend code  
for core programmers. As a matter of fact, Microsoft's MFC is what it provided originally  
as a framework. There is also a Win32++ framework. However, MFC is not intuitive  
and so is Win32++. QT is beautiful code and it is really perfect, but the IDE(Design  
Studio) is still not intuitive. Although unstable, C++ Builder has the most intuitive  
IDE design interface. I can use the Delphi language, but I hate the Delphi language.  
I hate the Microsoft Basic feeling of low-level sentence style like.  
The code itself is not intuitive and beautiful. There are many C/C++ code stuffs  
available on the Internet, but these codes are not compatible.  
That's why I do not implement code using QT and Delphi ETC.  
C++ Builder has the same intuitive advantages as Delphi programming, but it can be  
compatible with all existing Win32 API code without much modification.  
Also, if you do not need to program dynamic design code, IDE's design studio is  
very intuitive. (If you compare to QT, the dynamic design code is written to the  
.moc files). We often use IDEs rather than dynamic design code.  
This is because the interface design is fully tested through the IDE and then  
moved to dynamic code. Therefore, the IDE must provide an intuitive design  
of the component. C++ Builder is more satisfied than most other languages.  
So, from time to time, Microsoft is copying Delphi's design studio.  
if you can write a perfect backend code(Non-UI core frameworks) and easily even  
a perfect frontend code(UI core frameworks), you can fly.  
Is it enough to explain why I chose C++ Builder?  
I am a perfectionist, but I do not want to suffer from programming.  
If you care about a perfect GUI front engine, you can probably die..  
You just need to find and use the best GUI framework.  
I will eventually use QT for high quality. But, C++ Builder is similar to the most  
complete Japanese high quality instant food. So I just use C++ Builder instead of  
a microwave oven. This is because it only requires cooking for 3 minutes.  
If you are in the same style as me, C++ Builder is the answer.  
So, Chinese hackers are using C++ Builder very much. This is because you can build  
hacking tools quickly without investing a lot of time on the frontend.  
I have no plans to use more than what I use for my fast code programming.  
Commercial projects should use QT for long-term development purposes.  
The final answer is QT. The NinjaBrowser still has no plans for QT porting.  
This is because there is no commercial purpose yet.  
  
  
## Is there a security issue when surfing the web with a NinjaBrowser?  
I am not responsible for your security. So if you are concerned about  
security, you should not use this browser. However, most hackers do not  
typically create 32-bit exploits. They just create 64-bit exploits.  
So the 32-bit NinjaBrowser might be safer than Google's current Chrome  
Browser. This is because Google's official Chrome distribution will install  
64-bit by default. For 64-bit hacking code to work on 32-bit, the expert  
will have to manually rewrite the code. Experts are not free. Script kids  
can not reuse attack code in a simple way. My job is a security expert, so  
I know very well. Converting a one-day exploit code from 64-bit to 32-bit  
is not a simple matter without the best hacker. Ironically, 32-bit browsers  
are more secure. I will always rebuild and distribute Google's latest Chrome  
engine at deployment time. Sometimes you may not keep up with Google's update  
speed. But do not worry too much you are 32 bits.  
  
  
## P.S  
I could not change the comment in the source code to English. I am not good at English.  
I am studying English. I do not know English. I just use the help of Google Translator.  
Of course, I manually correct the wrong translation part. So even if there is a wrong  
translation, please forgive me.  
Thank you.  
