/**
 * @file trlEmuShellDebug.cpp
 * @author zhfang, Chentian
 * @date 2010.03.15
 * @brief TRL Emulate - EmuShell Debug Module
 */
#include "trlEmuShell.h"
#include "trlEmuShellDebug.h"
#include "trlEmuShellFont.h"
#include "trlEmuShellVideo.h"
#include "trlEmuShellAudio.h"
#include "trlEmuShellData.h"
#include "trlEmuShellNetwork.h"
#include "trlEmuShellStruct.h"
#include "trlEmuShellSuspend.h"
#include "trlEmuShellInput.h"

#ifdef TRL_PLATFORM_CTR
#include <nn\os.h>
#include <nn\hid.h>
#include <nn/snd.h>
using namespace nn::os;
using namespace nn::snd;
using namespace nn::os;
using namespace nn::hid::CTR;
using namespace nn::snd;

#define A_BUTTON BUTTON_A
#define B_BUTTON BUTTON_B
#define SELECT_BUTTON PSEUDO_BUTTON_SELECT
#define START_BUTTON  BUTTON_START
#define RIGHT_BUTTON BUTTON_RIGHT
#define LEFT_BUTTON BUTTON_LEFT
#define UP_BUTTON BUTTON_UP
#define DOWN_BUTTON BUTTON_DOWN
#define X_BUTTON BUTTON_X
#define Y_BUTTON BUTTON_Y

extern Voice*		g_pTrlAudioVoice;
#else

#define A_BUTTON 0x1
#define B_BUTTON 0x2
#define SELECT_BUTTON 0x4
#define START_BUTTON 0x8
#define RIGHT_BUTTON 0x10
#define LEFT_BUTTON 0x20
#define UP_BUTTON 0x40
#define DOWN_BUTTON 0x80
#define X_BUTTON 0x400
#define Y_BUTTON 0x800
#endif

u32 nMenuColor_Disable = TRL_FONT_WHITE;//0x808080FF;
u32 nMenuColor_Normal = TRL_FONT_WHITE;//0x000000FF;
u32 nMenuColor_Title = TRL_FONT_YELLOW;//0x0000FFFF;
u32 nMenuColor_Line = TRL_FONT_WHITE;//0x000000FF;
u32 nMenuColor_Select = TRL_FONT_RED;//0xFF0000FF;

#if TRL_SOUND_DEBUG
s32			g_bCgbSndResetCH1 = 0;
s32			g_bCgbSndResetCH2 = 0;
s32			g_bCgbSndResetCH3 = 0;
s32			g_bCgbSndResetCH4 = 1;

s32			g_bCgbSndOnOffCH1 = 1;
s32			g_bCgbSndOnOffCH2 = 1;
s32			g_bCgbSndOnOffCH3 = 1;
s32			g_bCgbSndOnOffCH4 = 1;
#endif


extern f32 g_fNesSndScaleA;
extern f32 g_fNesSndScaleB;
extern f32 g_fNesSndScaleC;
extern f32 g_fNesSndScaleD;
extern f32 g_fNesSndScaleE;
extern f32 g_fNesSndScaleF;
extern f32 g_fNesSndScale5A;
extern f32 g_fNesSndScale5B;
extern f32 g_fNesSndScaleZ;
extern f32 g_fNesSndScaleQ1;
extern f32 g_fNesSndScaleQ2;
extern f32 g_fNesSndScaleQ3;

#if TRL_HVC_SOUND_TEST
extern u32 g_bNesSndA;
extern u32 g_bNesSndB;
extern u32 g_bNesSndC;
extern u32 g_bNesSndD;
extern u32 g_bNesSndE;
extern u32 g_bNesSndF;
extern u32 g_bNesSnd5A;
extern u32 g_bNesSnd5B;
extern u32 g_bNesSndZ;
extern u32 g_bNesSndQ1;
extern u32 g_bNesSndQ2;
extern u32 g_bNesSndQ3;
#endif

#if TRL_DEBUG
s32 g_nTrlEmuCoreOn = 1;
s32 g_nTrlEmuSoundOn = 1;
s32 g_nTrlEmuGraphicOn = 1;
s32 g_nTrlEmuOBJNum = 0;
s32 g_nTrlEmuMapper = 0;
s32 g_nTrlEmuFdiskSide = 0;
#endif

extern u32	g_pNesGrpClip[4];						///< Clip Pixel

extern trlSEmuShellVideoMask	g_sTrlVideoMaskData;
s32 g_nFrameCount = 0;
s32 g_nFrameTime = 0;
s32 g_nTotalTime = 0;
s32 g_nMaxTime = 0;
f32 g_nAvgTime = 0;
s32 g_nFrameTimeV = 0;
s32 g_nTotalTimeV = 0;
s32 g_nMaxTimeV = 0;
f32 g_nAvgTimeV = 0;
u32	g_nDebugInfoEnable;			///< Debug Info Enable Flag

char g_szTrlMenuString[128];
char pMenuLine[] = "================================";

#ifdef TRL_PLATFORM_CTR
extern u32 g_bQuit;
#endif
extern s32 g_sEmuShellRomIndex;


class CDebugMenuItem
{
public:	
	enum EItemType
	{
		eItemTypeMsg,
		eItemTypeButton
	};

	enum EMsgType
	{
		eMsgTypeTitle,
		eMsgTypeNormal,
		eMsgTypeComment
	};

	enum EButtonType
	{
		eButtonTypeNormal,
		eButtonTypeNum,
		eButtonTypeTextSelect		
	};


	bool beTitle(){return (itemtype == eItemTypeMsg)&&(msgtype == eMsgTypeTitle);}
	bool beMsg(){return (itemtype == eItemTypeMsg)&&(msgtype == eMsgTypeNormal);}
	bool beComment(){return (itemtype == eItemTypeMsg)&&(msgtype == eMsgTypeComment);}
	bool beButton(){return (itemtype == eItemTypeButton);}
	bool beNumButton(){return (itemtype == eItemTypeButton)&&(buttontype == eButtonTypeNum);}

	CDebugMenuItem()
	{
		haveonoff = 0;		
	}
	
	

	void SetButtonTextSelect(char *pname, char *pstr)
	{
		name = pname;
		str[0] = pstr;
		itemtype = eItemTypeButton;
		buttontype = eButtonTypeTextSelect;
		nStrNum = 1;
		nMsgNo = 0;
	}

	void AddButtonTextSelect(char *pstr)
	{
		str[nStrNum] = pstr;
		nStrNum++;
	}


	void SetTitleItem(char *pname, char *pstr)
	{
		name = pname;
		str[0] = pstr;
		msgtype = eMsgTypeTitle;
		itemtype = eItemTypeMsg;
	}
	
	void SetCommentItem(char *pname, char *pstr)
	{
		name = pname;
		str[0] = pstr;
		itemtype = eItemTypeMsg;
		msgtype = eMsgTypeComment;		
	}

	void SetMsgItem(char *pname, char *pstr)
	{
		name = pname;
		str[0] = pstr;
		msgtype = eMsgTypeNormal;
		itemtype = eItemTypeMsg;
		nMsgNo = 0;
		nStrNum = 1;
	}
	void AddMsgItem(char *pstr)
	{
		str[nStrNum++] = pstr;
	}

	void SetButtonNormal(char *pname, char *pstr)
	{
		name = pname;
		str[0] = pstr;
		itemtype = eItemTypeButton;
		buttontype = eButtonTypeNormal;
	}

	void SetButtonNum(char *pname, char *pstr, s32 nOriNum, s32 nMin, s32 nMax, s32 delta = 1)
	{
		name = pname;
		str[0] = pstr;
		itemtype = eItemTypeButton;
		buttontype = eButtonTypeNum;
		curnum = nOriNum;
		numrange_min = nMin;
		numrange_max = nMax;
		numdelta = delta;
	}

	void ButtonNumAdd(s32 add = 1)
	{
		if(itemtype == eItemTypeButton && buttontype == eButtonTypeNum)
		{
			curnum += add*numdelta;
			if(curnum > numrange_max)
				curnum = numrange_max;
			if(curnum < numrange_min)
				curnum = numrange_min;
		}
		else if(itemtype == eItemTypeButton && buttontype == eButtonTypeTextSelect)			
		{
			nMsgNo += add;
			if(nMsgNo >= nStrNum)
				nMsgNo = 0;
			else if(nMsgNo < 0)
				nMsgNo = nStrNum - 1;
		}
	}

	void SetHaveOnOff(u32 value)
	{
		haveonoff = value;
	}

	void SetOnOff(u32 value)
	{
		onoff = value;
	}

	void SetString(char *pstr)
	{
		str[0] = pstr;
		return;
	}

	char* GetString()
	{
		static char buf[256];
		if(itemtype == eItemTypeMsg)
		{
			if(msgtype == eMsgTypeTitle)
				return str[0];
			else if(msgtype == eMsgTypeComment)
				return str[0];
			else if(msgtype == eMsgTypeNormal)
			{
				return str[nMsgNo];
			}
		}
		else if(itemtype == eItemTypeButton)
		{
			if(buttontype == eButtonTypeNormal)
			{
				if(haveonoff)
				{
					if(onoff == 0)
						sprintf(buf, "%s <OFF>", str[0]);
					else
						sprintf(buf, "%s <ON>", str[0]);
					return buf;
				}
				else
					return str[0];
			}
			else if(buttontype == eButtonTypeNum)
			{
				if(haveonoff)
				{
					if(onoff == 0)
						sprintf(buf, "%s <%d> <OFF>", str[0], curnum);
					else
						sprintf(buf, "%s <%d> <ON>", str[0], curnum);
				}
				else
					sprintf(buf, "%s <%d>", str[0], curnum);
				return buf;
			}
			else if(buttontype == eButtonTypeTextSelect)
			{
				if(haveonoff)
				{
					if(onoff == 0)
						sprintf(buf, "%s <OFF>", str[nMsgNo]);
					else
						sprintf(buf, "%s <ON>", str[nMsgNo]);
					return buf;
				}
				else
					return str[nMsgNo];
			}			
		}
		return NULL;
	}

	char *GetName(){return name;}

	s32 GetMsgNo(){ return nMsgNo;}
	void SetMsgNo(s32 value){ nMsgNo = value;}

	s32 GetCurNum(){return curnum;}
	void SetCurNum(s32 value){curnum = value;};

protected:
	char *name;
	char *str[8];
	s32 nStrNum;
	s32 nMsgNo;
	EItemType itemtype;
	EMsgType msgtype;
	EButtonType buttontype;
	EButtonType padding;
	s32 curnum;
	s32 numrange_min;
	s32 numrange_max;
	s32 numdelta;

	u32 haveonoff;
	u32 onoff;
};

class CDebugMenu
{
public:
	CDebugMenu()
	{
		nItemNum = 0;
		nSelected = -1;
	}

	void Reset()
	{
		nItemNum = 0;
		nSelected = -1;
	}

	void SetText(char *name, char *str)
	{
		CDebugMenuItem *pItem = this->GetItem(this->GetItemByName(name));
		if(pItem != NULL)
			pItem->SetString(str);
	}
	void AddComment(char *name, char *str)
	{
		items[nItemNum++].SetCommentItem(name, str);
	}

	void AddMenuTitle(char *name, char *str)
	{
		items[nItemNum++].SetTitleItem(name, str);
	}
	void AddMsgItem(char *name, char *str)
	{
		items[nItemNum++].SetMsgItem(name, str);
	}

	void AddButtonItem(char *name, char *str)
	{
		items[nItemNum++].SetButtonNormal(name, str);
		if(nSelected == -1)
			nSelected = nItemNum-1;
	}
	void AddNumButtonItem(char *name, char *str, s32 nOri, s32 nMin, s32 nMax, s32 delta = 1)
	{
		items[nItemNum++].SetButtonNum(name, str, nOri, nMin, nMax, delta);
		if(nSelected == -1)
			nSelected = nItemNum-1;
	}
	void AddTextButtonItem(char *name, char *str)
	{
		items[nItemNum++].SetButtonTextSelect(name, str);
		if(nSelected == -1)
			nSelected = nItemNum-1;
	}

	s32 FindTitle()
	{
		for(int i=0;i<nItemNum;i++)		
			if(items[i].beTitle())
				return i;
		return -1;
	}
	s32 FindComment()
	{
		for(int i=0;i<nItemNum;i++)		
			if(items[i].beComment())
				return i;
		return -1;
	}

	s32 FindNextButton(s32 curindex)
	{
		for(int i=curindex+1;i<nItemNum;i++)
			if(items[i].beButton())
				return i;
		for(int i=0;i<curindex;i++)
			if(items[i].beButton())
				return i;
		return curindex;
	}

	s32 FindPreButton(s32 curindex)
	{
		for(int i=curindex-1;i>=0;i--)
			if(items[i].beButton())
				return i;
		for(int i=nItemNum-1;i> curindex;i--)
			if(items[i].beButton())
				return i;		
		return curindex;
	}

	s32 GetItemByName(char *name)
	{
		for(int i=0;i<nItemNum;i++)	
			if(strcmp(name, items[i].GetName()) == 0)
				return i;
		return -1;
	}

	CDebugMenuItem *GetItem(s32 index)
	{
		return &items[index];
	}
	s32 GetSelectIndex(){return nSelected;}

	void SetTitle(char *str)
	{
		s32 titleindex = FindTitle();
		
		if(titleindex != -1)
			items[titleindex].SetString(str);
	}

	void SetComment(char *str)
	{
		s32 comment = FindComment();
		if(comment != -1)
			items[comment].SetString(str);
	}
	
	void update(u16 keyinput)
	{
		pPressConfirm = NULL;
		pPressCancel = NULL;
		if(keyinput & UP_BUTTON)
		{
			nSelected = FindPreButton(nSelected);
		}
		else if(keyinput & DOWN_BUTTON)
		{
			nSelected = FindNextButton(nSelected);
		}
		else if(keyinput & LEFT_BUTTON)
		{
			GetItem(nSelected)->ButtonNumAdd(-1);
		}
		else if(keyinput & RIGHT_BUTTON)
		{
			GetItem(nSelected)->ButtonNumAdd(1);
		}
		else if(keyinput & Y_BUTTON)
		{
			pPressConfirm = GetItem(nSelected);
		}
		else if(keyinput & X_BUTTON)
		{
			pPressCancel = GetItem(nSelected);
		}
	}

	CDebugMenuItem *GetPressConfirmButton(){return pPressConfirm;}
	CDebugMenuItem *GetPressCancelButton(){return pPressCancel;}
	CDebugMenuItem *GetSelectButton(){return GetItem(nSelected);};


	void draw()
	{
		int linebegin = 2;

		s32 titleindex = FindTitle();
		s32 comment = FindComment();
		
		if(titleindex != -1)
			trlEmuShellVideoDrawText(nMenuColor_Title, 0, 0, items[titleindex].GetString());
		trlEmuShellVideoDrawText(nMenuColor_Line, 0, 1, pMenuLine);

		int itemct = 0;
		for(int i=0;i<nItemNum;i++)
		{
			if(i == titleindex) continue;
			if(i == comment) continue;
			if(i == nSelected)
				trlEmuShellVideoDrawText(nMenuColor_Select, 1, linebegin + itemct, items[i].GetString());
			else
				trlEmuShellVideoDrawText(nMenuColor_Normal, 1, linebegin + itemct, items[i].GetString());
			itemct++;
		}
#ifdef TRL_PLATFORM_CTR
		if(comment != -1)
			trlEmuShellVideoDrawText(nMenuColor_Normal, 0, 22, items[comment].GetString());
		trlEmuShellVideoDrawText(nMenuColor_Normal, 0, 23, TRL_VERSION);
#endif		
#ifdef TRL_PLATFORM_PC
		trlEmuShellVideoDrawText(nMenuColor_Normal, 0, 23, TRL_VERSION);
		trlEmuShellVideoDrawText(nMenuColor_Normal, 0, 24, "\n");
#endif
	}
protected:
	static const s32 MENUITEM_NUM_MAX = 24;
	s32 nItemNum;
	CDebugMenuItem items[MENUITEM_NUM_MAX];

	CDebugMenuItem *pPressConfirm;
	CDebugMenuItem *pPressCancel;

	s32 nSelected;
};

CDebugMenu debugmain, confirm, waitmsg;
CDebugMenu colormain, color4, color3,color, cgbpalette, colormask;
CDebugMenu nesclip;
CDebugMenu filelist;
CDebugMenu debuginfo;
CDebugMenu soundreset;
CDebugMenu soundonoff;
CDebugMenu soundset;
CDebugMenu network;
CDebugMenu buttonrepeat;

CDebugMenu hvcsoundonoff;
CDebugMenu hvcsoundvolume;

s32 FILE_LIST_MAX = 256;
#ifdef TRL_PLATFORM_PC
s32 FILE_PER_PAGE = 5;
#endif
#ifdef TRL_PLATFORM_CTR
s32 FILE_PER_PAGE = 10;
#endif
s32 filelistnum = 0;
s32 selectedfile = 0;
s32 curfileno;
char *filelistname[] = 
{
	"file0", "file1", "file2", "file3", "file4",
	"file5", "file6", "file7", "file8", "file9"
};

void updateColorMaskData();

extern u32 trlEmuShellDataGetConfigData(const char* szSection, const char* szValue, u32 nDefault);

void resetdebugmenu()
{
	debugmain.Reset();
	confirm.Reset();
	waitmsg.Reset();
	colormain.Reset();
	hvcsoundonoff.Reset();
	hvcsoundvolume.Reset();
	soundreset.Reset();
	nesclip.Reset();
	soundonoff.Reset();
	soundset.Reset();
	color4.Reset();
	color3.Reset();
	color.Reset();
	cgbpalette.Reset();
	colormask.Reset();
	filelist.Reset();
	debuginfo.Reset();
	network.Reset();
	buttonrepeat.Reset();
}
void initdebugmenu()
{
	resetdebugmenu();
	debugmain.AddMenuTitle("title", "Menu");
	debugmain.AddButtonItem("save", "Interruption Save");
	debugmain.AddButtonItem("load", "Interruption Load");
	debugmain.AddButtonItem("capture", "Capture");
	debugmain.AddButtonItem("reset", "Reset");
	debugmain.AddButtonItem("rom", "Change Rom");
	debugmain.AddButtonItem("net", "NetWork");
	debugmain.AddButtonItem("buttonrepeat", "ButtonRepeat");
	debugmain.AddButtonItem("quit", "Quit");

	buttonrepeat.AddMenuTitle("title", "ButtonRepeat");
	buttonrepeat.AddNumButtonItem("holdframs", "HoldFrames", g_nTrlInputAutoFireFrame[TRL_INPUT_AUTOFIRE_HOLD], 0, 10000, 1);
	buttonrepeat.AddNumButtonItem("releaseframes", "ReleaseFrames", g_nTrlInputAutoFireFrame[TRL_INPUT_AUTOFIRE_RELEASE], 0, 10000,1);
	buttonrepeat.AddButtonItem("back", "Back");
	network.AddMenuTitle("title", "NetWork");
	network.AddButtonItem("server", "Server");
	network.AddButtonItem("client", "Client");
	network.AddNumButtonItem("delay", "Delay",  trlEmuShellDataGetConfigData("NES", "NetDelay", 2),0,10);
	network.AddButtonItem("back", "Back");

	
	confirm.AddMenuTitle("title", "confirm");
	confirm.AddMsgItem("msg", "Do you want xxx");
	confirm.AddButtonItem("yes", "Yes");
	confirm.AddButtonItem("no", "No");

	waitmsg.AddMenuTitle("title", "waiting");
	waitmsg.AddMsgItem("msg", "saving...");
	CDebugMenuItem *pItem = waitmsg.GetItem(waitmsg.GetItemByName("msg"));
	pItem->AddMsgItem("save success");
	pItem->AddMsgItem("save failed");
	pItem->AddMsgItem("loading...");
	pItem->AddMsgItem("load success");
	pItem->AddMsgItem("load failed");

	colormain.AddMenuTitle("tilte", "Graphic");
	colormain.AddTextButtonItem("filter", "TexFilter <LINEAR>");
	pItem = colormain.GetItem(colormain.GetItemByName("filter"));
	pItem->AddButtonTextSelect("TexFilter <NEAREST>");
	colormain.AddButtonItem("dmggray", "DMG Gray Palette");
	colormain.AddButtonItem("dmgcolor", "DMG Color Palette");
	colormain.AddButtonItem("lcd", "LCD Palette");
	colormain.AddButtonItem("mask", "Mask");	
	colormain.AddTextButtonItem("vsync", "VSync <ON>");	
	pItem = colormain.GetItem(colormain.GetItemByName("vsync"));
	pItem->AddButtonTextSelect("VSync <OFF>");
	if(g_sEmuShellBuffer.nVSyncEnable == 0)
		pItem->SetMsgNo(1);

#if TRL_DEBUG
	colormain.AddTextButtonItem("soundon", "Sound <ON>");
	pItem = colormain.GetItem(colormain.GetItemByName("soundon"));
	pItem->AddButtonTextSelect("Sound <OFF>");
	if(g_nTrlEmuSoundOn == 0)
		pItem->SetMsgNo(1);

	colormain.AddTextButtonItem("graphicon", "Graphic <ON>");
	pItem = colormain.GetItem(colormain.GetItemByName("graphicon"));
	pItem->AddButtonTextSelect("Graphic <OFF>");
	if(g_nTrlEmuGraphicOn == 0)
		pItem->SetMsgNo(1);

	colormain.AddTextButtonItem("emucore", "EmuCore <ON>");
	pItem = colormain.GetItem(colormain.GetItemByName("emucore"));
	pItem->AddButtonTextSelect("EmuCore <OFF>");
	if(g_nTrlEmuCoreOn == 0)
		pItem->SetMsgNo(1);
#endif

	colormain.AddButtonItem("soundreset","SoundReset");
	colormain.AddButtonItem("soundonoff","SoundOnOff");
	colormain.AddButtonItem("soundset","SoundSet");
#if TRL_HVC_SOUND_TEST
	colormain.AddButtonItem("hvcsoundonoff","HVCSoundOnOff");
	colormain.AddButtonItem("hvcsoundvolume","HVCSoundVolume");
#endif	

	colormain.AddTextButtonItem("debugprint", "DebugPrint <ON>");
	pItem = colormain.GetItem(colormain.GetItemByName("debugprint"));
	pItem->AddButtonTextSelect("DebugPrint <OFF>");
	if(g_nDebugInfoEnable == 0)
		pItem->SetMsgNo(1);
	colormain.AddButtonItem("nesclip", "NES Clip");
	colormain.AddButtonItem("quit", "Quit");
	colormain.AddComment("comment", "");

#if TRL_HVC_SOUND_TEST
	hvcsoundonoff.AddMenuTitle("title", "HVC Snd Channel");
	hvcsoundonoff.AddButtonItem("CH_A", "Ch_A");
	hvcsoundonoff.AddButtonItem("CH_B", "Ch_B");
	hvcsoundonoff.AddButtonItem("CH_C", "Ch_C");
	hvcsoundonoff.AddButtonItem("CH_D", "Ch_D");
	hvcsoundonoff.AddButtonItem("CH_E", "Ch_E");
	hvcsoundonoff.AddButtonItem("CH_F", "Ch_F");
	hvcsoundonoff.AddButtonItem("CH_5A", "Ch_5A");
	hvcsoundonoff.AddButtonItem("CH_5B", "Ch_5B");
	hvcsoundonoff.AddButtonItem("CH_Z", "Ch_Z");
	hvcsoundonoff.AddButtonItem("CH_Q1", "CH_Q1");
	hvcsoundonoff.AddButtonItem("CH_Q2", "CH_Q2");
	hvcsoundonoff.AddButtonItem("CH_Q3", "CH_Q3");
	hvcsoundonoff.AddButtonItem("back", "Back");

	hvcsoundonoff.GetItem(hvcsoundonoff.GetItemByName("CH_A"))->SetHaveOnOff(1);
	hvcsoundonoff.GetItem(hvcsoundonoff.GetItemByName("CH_B"))->SetHaveOnOff(1);
	hvcsoundonoff.GetItem(hvcsoundonoff.GetItemByName("CH_C"))->SetHaveOnOff(1);
	hvcsoundonoff.GetItem(hvcsoundonoff.GetItemByName("CH_D"))->SetHaveOnOff(1);
	hvcsoundonoff.GetItem(hvcsoundonoff.GetItemByName("CH_E"))->SetHaveOnOff(1);
	hvcsoundonoff.GetItem(hvcsoundonoff.GetItemByName("CH_F"))->SetHaveOnOff(1);
	hvcsoundonoff.GetItem(hvcsoundonoff.GetItemByName("CH_5A"))->SetHaveOnOff(1);
	hvcsoundonoff.GetItem(hvcsoundonoff.GetItemByName("CH_5B"))->SetHaveOnOff(1);
	hvcsoundonoff.GetItem(hvcsoundonoff.GetItemByName("CH_Z"))->SetHaveOnOff(1);

	hvcsoundonoff.GetItem(hvcsoundonoff.GetItemByName("CH_Q1"))->SetHaveOnOff(1);
	hvcsoundonoff.GetItem(hvcsoundonoff.GetItemByName("CH_Q2"))->SetHaveOnOff(1);
	hvcsoundonoff.GetItem(hvcsoundonoff.GetItemByName("CH_Q3"))->SetHaveOnOff(1);

	hvcsoundonoff.GetItem(hvcsoundonoff.GetItemByName("CH_A"))->SetOnOff(g_bNesSndA);
	hvcsoundonoff.GetItem(hvcsoundonoff.GetItemByName("CH_B"))->SetOnOff(g_bNesSndB);
	hvcsoundonoff.GetItem(hvcsoundonoff.GetItemByName("CH_C"))->SetOnOff(g_bNesSndC);
	hvcsoundonoff.GetItem(hvcsoundonoff.GetItemByName("CH_D"))->SetOnOff(g_bNesSndD);
	hvcsoundonoff.GetItem(hvcsoundonoff.GetItemByName("CH_E"))->SetOnOff(g_bNesSndE);
	hvcsoundonoff.GetItem(hvcsoundonoff.GetItemByName("CH_F"))->SetOnOff(g_bNesSndF);
	hvcsoundonoff.GetItem(hvcsoundonoff.GetItemByName("CH_5A"))->SetOnOff(g_bNesSnd5A);
	hvcsoundonoff.GetItem(hvcsoundonoff.GetItemByName("CH_5B"))->SetOnOff(g_bNesSnd5B);
	hvcsoundonoff.GetItem(hvcsoundonoff.GetItemByName("CH_Z"))->SetOnOff(g_bNesSndZ);

	hvcsoundonoff.GetItem(hvcsoundonoff.GetItemByName("CH_Q1"))->SetOnOff(g_bNesSndQ1);
	hvcsoundonoff.GetItem(hvcsoundonoff.GetItemByName("CH_Q2"))->SetOnOff(g_bNesSndQ2);
	hvcsoundonoff.GetItem(hvcsoundonoff.GetItemByName("CH_Q3"))->SetOnOff(g_bNesSndQ3);

	hvcsoundvolume.AddMenuTitle("title", "HVC Snd Volume");
	hvcsoundvolume.AddNumButtonItem("CH_A", "ch_a", (int)(g_fNesSndScaleA*10), 0, 30);
	hvcsoundvolume.AddNumButtonItem("CH_B", "ch_b", (int)(g_fNesSndScaleB*10), 0, 30);
	hvcsoundvolume.AddNumButtonItem("CH_C", "ch_c", (int)(g_fNesSndScaleC*10), 0, 30);
	hvcsoundvolume.AddNumButtonItem("CH_D", "ch_d", (int)(g_fNesSndScaleD*10), 0, 30);
	hvcsoundvolume.AddNumButtonItem("CH_E", "ch_e", (int)(g_fNesSndScaleE*10), 0, 30);
	hvcsoundvolume.AddNumButtonItem("CH_F", "ch_f", (int)(g_fNesSndScaleF*10), 0, 30);
	hvcsoundvolume.AddNumButtonItem("CH_5A", "ch_5a", (int)(g_fNesSndScale5A*10), 0, 30);
	hvcsoundvolume.AddNumButtonItem("CH_5B", "ch_5b", (int)(g_fNesSndScale5B*10), 0, 30);
	hvcsoundvolume.AddNumButtonItem("CH_Z", "ch_z", (int)(g_fNesSndScaleZ*10), 0, 30);

	hvcsoundvolume.AddNumButtonItem("CH_Q1", "CH_Q1", (int)(g_fNesSndScaleQ1*10), 0, 30);
	hvcsoundvolume.AddNumButtonItem("CH_Q2", "CH_Q2", (int)(g_fNesSndScaleQ2*10), 0, 30);
	hvcsoundvolume.AddNumButtonItem("CH_Q3", "CH_Q3", (int)(g_fNesSndScaleQ3*10), 0, 30);

	hvcsoundvolume.AddButtonItem("back", "Back");
	
#endif

#if TRL_SOUND_DEBUG
	soundreset.AddMenuTitle("title", "Snd WaveForm Reset");
	soundreset.AddButtonItem("ch1", "Ch1");
	soundreset.AddButtonItem("ch2", "Ch2");
	soundreset.AddButtonItem("ch3", "Ch3");
	soundreset.AddButtonItem("ch4", "Ch4");
	soundreset.AddButtonItem("back", "Back");
	soundreset.GetItem(soundreset.GetItemByName("ch1"))->SetHaveOnOff(1);
	soundreset.GetItem(soundreset.GetItemByName("ch2"))->SetHaveOnOff(1);
	soundreset.GetItem(soundreset.GetItemByName("ch3"))->SetHaveOnOff(1);
	soundreset.GetItem(soundreset.GetItemByName("ch4"))->SetHaveOnOff(1);
	soundreset.GetItem(soundreset.GetItemByName("ch1"))->SetOnOff(g_bCgbSndResetCH1);
	soundreset.GetItem(soundreset.GetItemByName("ch2"))->SetOnOff(g_bCgbSndResetCH2);
	soundreset.GetItem(soundreset.GetItemByName("ch3"))->SetOnOff(g_bCgbSndResetCH3);
	soundreset.GetItem(soundreset.GetItemByName("ch4"))->SetOnOff(g_bCgbSndResetCH4);

	soundonoff.AddMenuTitle("title", "Snd Channel");
	soundonoff.AddButtonItem("ch1", "Ch1");
	soundonoff.AddButtonItem("ch2", "Ch2");
	soundonoff.AddButtonItem("ch3", "Ch3");
	soundonoff.AddButtonItem("ch4", "Ch4");
	soundonoff.AddButtonItem("back", "Back");
	soundonoff.GetItem(soundonoff.GetItemByName("ch1"))->SetHaveOnOff(1);
	soundonoff.GetItem(soundonoff.GetItemByName("ch2"))->SetHaveOnOff(1);
	soundonoff.GetItem(soundonoff.GetItemByName("ch3"))->SetHaveOnOff(1);
	soundonoff.GetItem(soundonoff.GetItemByName("ch4"))->SetHaveOnOff(1);
	soundonoff.GetItem(soundonoff.GetItemByName("ch1"))->SetOnOff(g_bCgbSndOnOffCH1);
	soundonoff.GetItem(soundonoff.GetItemByName("ch2"))->SetOnOff(g_bCgbSndOnOffCH2);
	soundonoff.GetItem(soundonoff.GetItemByName("ch3"))->SetOnOff(g_bCgbSndOnOffCH3);
	soundonoff.GetItem(soundonoff.GetItemByName("ch4"))->SetOnOff(g_bCgbSndOnOffCH4);
#endif

	soundset.AddMenuTitle("title", "Snd Set");
	soundset.AddNumButtonItem("volume", "Volume",  trlEmuShellDataGetConfigData("Sound", "Volume", 88),0,20000);
	soundset.AddNumButtonItem("cutrate", "Cut Rate", trlEmuShellDataGetConfigData("Sound", "CutRate", 2500), 0, 25000, 100);		
	soundset.AddButtonItem("back", "Back");
	

	color4.AddMenuTitle("title", "Palette");
	color4.AddButtonItem("color0", "Color0");
	color4.AddButtonItem("color1", "Color1");
	color4.AddButtonItem("color2", "Color2");
	color4.AddButtonItem("color3", "Color3");
	color4.AddButtonItem("back", "Back");

	color3.AddMenuTitle("title", "Palette");
	color3.AddButtonItem("color0", "Color0");
	color3.AddButtonItem("color1", "Color1");
	color3.AddButtonItem("color2", "Color2");
	color3.AddButtonItem("color3", "Color3");
	color3.AddButtonItem("back", "Back");

	color.AddMenuTitle("title", "Color");
	color.AddNumButtonItem("red", "Red", 0, 0, 31);
	color.AddNumButtonItem("green", "Green", 0, 0, 31);
	color.AddNumButtonItem("blue", "Blue", 0, 0, 31);
	color.AddButtonItem("back", "Back");
	color.AddComment("comment", "Left/Right: change the value");

	cgbpalette.AddMenuTitle("title", "Graphic>DMG Color Palette");
	cgbpalette.AddButtonItem("bg", "BG Palette");
	cgbpalette.AddButtonItem("obj0", "OBJ Palette 0");
	cgbpalette.AddButtonItem("obj1", "OBJ Palette 1");
	cgbpalette.AddButtonItem("back", "Back");
	

	nesclip.AddMenuTitle("title", "Graphic>Clip");
	nesclip.AddNumButtonItem("clipup", "Clip Up", trlEmuShellDataGetConfigData("NES", "ClipUp", 0), 0, 30);
	nesclip.AddNumButtonItem("clipdown", "Clip Down", trlEmuShellDataGetConfigData("NES", "ClipDown", 0), 0, 30);
	nesclip.AddNumButtonItem("clipleft", "Clip Left", trlEmuShellDataGetConfigData("NES", "ClipLeft", 0), 0, 30);
	nesclip.AddNumButtonItem("clipright", "Clip Right", trlEmuShellDataGetConfigData("NES", "ClipRight", 0), 0, 30);
	nesclip.AddButtonItem("back", "Back");


	colormask.AddMenuTitle("title", "mask");
	colormask.AddButtonItem("normal", "ALL OFF");
	colormask.AddNumButtonItem("dark", "Dark", *g_sTrlVideoMaskData.pDark, 0, 10);
	colormask.AddButtonItem("reduce", "Reduce Color");
	colormask.AddNumButtonItem("motionblurmode", "Motion Blur Mode", *g_sTrlVideoMaskData.pMotionBEnable, 0, 3);
	colormask.AddNumButtonItem("motionblur", "Motion Blur Value", *g_sTrlVideoMaskData.pMotionBlur, 0, 31);		
	colormask.AddButtonItem("back", "Back");
	colormask.AddComment("comment", "");

	colormask.GetItem(colormask.GetItemByName("dark"))->SetHaveOnOff(1);	
	colormask.GetItem(colormask.GetItemByName("reduce"))->SetHaveOnOff(1);	
	//colormask.GetItem(colormask.GetItemByName("motionblur"))->SetHaveOnOff(1);

	updateColorMaskData();	
	
	filelist.AddMenuTitle("title", "filelist");
	
	filelist.AddButtonItem("pre", "PrePage");
	for(int i=0;i<FILE_PER_PAGE;i++)
		filelist.AddButtonItem(filelistname[i], "new file");
	filelist.AddButtonItem("next", "NextPage");
	filelist.AddButtonItem("back", "Back");
	filelist.AddComment("comment", "Y: Load  X: Delete");
	curfileno = 0;

	debuginfo.AddMenuTitle("debuginfo", "Debug Info Version");
}


void updateColorMaskData()
{
	colormask.GetItem(colormask.GetItemByName("reduce"))->SetOnOff(*g_sTrlVideoMaskData.pReduceEnable);
	colormask.GetItem(colormask.GetItemByName("dark"))->SetOnOff(*g_sTrlVideoMaskData.pDarkEnable);	
	colormask.GetItem(colormask.GetItemByName("dark"))->SetCurNum(*g_sTrlVideoMaskData.pDark);
	colormask.GetItem(colormask.GetItemByName("motionblurmode"))->SetOnOff(*g_sTrlVideoMaskData.pMotionBEnable);
	colormask.GetItem(colormask.GetItemByName("motionblur"))->SetCurNum(*g_sTrlVideoMaskData.pMotionBlur);	
}
//extern s32 FILE_LIST_MAX = 256;
//extern s32 FILE_PER_PAGE = 5;
//extern s32 filelistnum = 0;
//extern s32 curfileno;

void BuildRomFileList()
{
	filelistnum = trlEmuShellDataGetRomListCountDebug();
	static char temp[256];
	if(filelistnum == 0)
		sprintf(temp, "ROM List (Page 1 of 1)");
	else
		sprintf(temp, "ROM List (Page %d of %d)", curfileno/FILE_PER_PAGE + 1, (filelistnum+4)/FILE_PER_PAGE);
	filelist.GetItem(filelist.GetItemByName("title"))->SetString(temp);
	for(int i=0;i<FILE_PER_PAGE;i++)
	{
		s32 index = curfileno + i;
		if(index < filelistnum)
			filelist.GetItem(filelist.GetItemByName(filelistname[i]))->SetString(trlEmuShellDataGetRomListFileDebug(filelistnum -1 - index));
		else
			filelist.GetItem(filelist.GetItemByName(filelistname[i]))->SetString("NULL");
	}
}

void BuildFileList()
{
	filelistnum = trlEmuShellDataGetResumeListCountDebug();
	static char temp[256];
	if(filelistnum == 0)
		sprintf(temp, "File List (Page 1 of 1)");
	else
		sprintf(temp, "File List (Page %d of %d)", curfileno/FILE_PER_PAGE + 1, (filelistnum+4)/FILE_PER_PAGE);
	filelist.GetItem(filelist.GetItemByName("title"))->SetString(temp);
	for(int i=0;i<FILE_PER_PAGE;i++)
	{
		s32 index = curfileno + i;
		if(index < filelistnum)
			filelist.GetItem(filelist.GetItemByName(filelistname[i]))->SetString(trlEmuShellDataGetResumeListFileDebug(index));
		else
			filelist.GetItem(filelist.GetItemByName(filelistname[i]))->SetString("NULL");
	}
}

s16 nDMGColorChangeMenuValue[3];
s16 nColorChangeMenuValue[3];
s16 nLCDColorChangeMenuValue[3];

u8 g_bMenuOpen = 0;

enum
{
	MENU_STATE_CLOSED = 0,
	MENU_STATE_MAIN,
	MENU_STATE_SAVE_CONFIRM,
	MENU_STATE_SAVEING,
	MENU_STATE_SAVE_SUCCESS,
	MENU_STATE_SAVE_FAIL,
	MENU_STATE_LOAD_LIST,	
	MENU_STATE_LOAD_CONFIRM,
	MENU_STATE_LOADING,
	MENU_STATE_LOAD_SUCCESS,
	MENU_STATE_LOAD_FAIL,
	MENU_STATE_DEL_CONFIRM,
	MENU_STATE_DELING,
	MENU_STATE_DEL_SUCCESS,
	MENU_STATE_DEL_FAIL,
	MENU_STATE_ROM_LIST,
	MENU_STATE_ROM_CONFIRM,
	MENU_STATE_ROM_SUCCESS,
	MENU_STATE_NETWORK,
	MENU_STATE_NETWORK_SERVER,
	MENU_STATE_NETWORK_CLIENT,	
	MENU_STATE_RESET_CONFIRM,
	MENU_STATE_BUTTONREPEAT,


	GMENU_STATE_MAIN,
	GMENU_STATE_TEXFILTER,
	GMENU_STATE_DMG,
	GMENU_STATE_DMGCOLORCHANGE0,
	GMENU_STATE_DMGCOLORCHANGE1,
	GMENU_STATE_DMGCOLORCHANGE2,
	GMENU_STATE_DMGCOLORCHANGE3,
	GMENU_STATE_CGB,
	GMENU_STATE_BGCOLOR,
	GMENU_STATE_OBJCOLOR0,
	GMENU_STATE_OBJCOLOR1,
	GMENU_STATE_CGBCOLORCHANGEBG0,
	GMENU_STATE_CGBCOLORCHANGEBG1,	
	GMENU_STATE_CGBCOLORCHANGEBG2,	
	GMENU_STATE_CGBCOLORCHANGEBG3,
	GMENU_STATE_CGBCOLORCHANGEOBJ10,
	GMENU_STATE_CGBCOLORCHANGEOBJ11,
	GMENU_STATE_CGBCOLORCHANGEOBJ12,
	GMENU_STATE_CGBCOLORCHANGEOBJ13,
	GMENU_STATE_CGBCOLORCHANGEOBJ20,
	GMENU_STATE_CGBCOLORCHANGEOBJ21,
	GMENU_STATE_CGBCOLORCHANGEOBJ22,
	GMENU_STATE_CGBCOLORCHANGEOBJ23,
	GMENU_STATE_LCDCOLORCHANGE,
	GMENU_STATE_MASK,
	GMENU_STATE_MASKCOLORCHANGE,
	GMENU_STATE_SOUNDRESET,
	GMENU_STATE_SOUNDONOFF,
	GMENU_STATE_HVCSOUNDONOFF,
	GMENU_STATE_HVCSOUNDVOLUME,
	GMENU_STATE_NESCLIP,
	GMENU_STATE_SOUNDSET
};

int menu_state;


void trlEmuShellMenuColorConvert(u16 ori, s16 *colorvalue)
{
	colorvalue[0] = (ori>>11)&0x1F;
	colorvalue[1] = (ori>>6)&0x1F;
	colorvalue[2] = (ori>>1)&0x1F;
}

u16 trlEmuShellMenuColorGetU16(s16 *colorvalue)
{
	return ((colorvalue[0]&0x1f)<<11) |
		((colorvalue[1]&0x1f)<<6)  |
		((colorvalue[2]&0x1f)<<1);
}

/** @brief EmuShell Debug Init */
void trlEmuShellDebugInit()
{	
	nColorChangeMenuValue[0] = nColorChangeMenuValue[1] = nColorChangeMenuValue[2] = 0;

	menu_state = MENU_STATE_CLOSED;
	g_nDebugInfoEnable = 1;

	initdebugmenu();
}

extern CDebugMenu debugmain, confirm, waitmsg;
extern CDebugMenu colormain, color4, color3,color, cgbpalette, colormask;
#ifdef TRL_PLATFORM_CTR
extern u32					g_bQuit;
#endif
/** @brief EmuShell Debug Menu Main */
inline void trlEmuShellDebugMenuUpdate(u16 nInput)
{
	static u8 delay_ct = 0;

	CDebugMenuItem *pItem;
	switch(menu_state)
	{
	case MENU_STATE_MAIN:
		{
			debugmain.update(nInput);
			pItem = debugmain.GetPressConfirmButton();
			if(pItem != NULL)
			{
				if(strcmp(pItem->GetName(), "save") == 0)
				{
					confirm.SetTitle("Menu>Interruption Save");
					confirm.SetText("msg", "Do you want save?");
					menu_state = MENU_STATE_SAVE_CONFIRM;
				}
				else if(strcmp(pItem->GetName(), "load") == 0)
				{					
					BuildFileList();
					menu_state = MENU_STATE_LOAD_LIST;
				}
				else if(strcmp(pItem->GetName(), "reset") == 0)
				{
					confirm.SetTitle("Menu>Reset");
					confirm.SetText("msg", "Do you want reset");
					menu_state = MENU_STATE_RESET_CONFIRM;
				}
				else if(strcmp(pItem->GetName(), "rom") == 0)
				{
					BuildRomFileList();
					menu_state = MENU_STATE_ROM_LIST;
				}
				else if(strcmp(pItem->GetName(), "net") == 0)
				{					
					menu_state = MENU_STATE_NETWORK;
				}
				else if(strcmp(pItem->GetName(), "capture") == 0)
				{
					trlEmuShellVideoCapture();
					menu_state = MENU_STATE_CLOSED;
				}
				else if(strcmp(pItem->GetName(), "buttonrepeat") == 0)
				{					
					menu_state = MENU_STATE_BUTTONREPEAT;
				}
				else if(strcmp(pItem->GetName(), "quit") == 0)
				{
					menu_state = MENU_STATE_CLOSED;
				}
			}
		}
		break;
	case MENU_STATE_BUTTONREPEAT:
		{
			buttonrepeat.update(nInput);
			pItem = buttonrepeat.GetPressConfirmButton();
			if(pItem != NULL)
			{
				if(strcmp(pItem->GetName(), "back") == 0)
				{
					menu_state = MENU_STATE_MAIN;
				}
			}
			pItem = buttonrepeat.GetSelectButton();
			if(pItem != NULL)
			{
				if(strcmp(pItem->GetName(), "back") == 0)
				{					
				}
				else
				{
					buttonrepeat.SetComment("LEFT/RIGHT: Change Value");
				}
			}
			g_nTrlInputAutoFireFrame[TRL_INPUT_AUTOFIRE_HOLD] = buttonrepeat.GetItem(buttonrepeat.GetItemByName("holdframs"))->GetCurNum();
			g_nTrlInputAutoFireFrame[TRL_INPUT_AUTOFIRE_RELEASE] = buttonrepeat.GetItem(buttonrepeat.GetItemByName("releaseframes"))->GetCurNum();			
		}
		break;
	case MENU_STATE_NETWORK:
		{
			network.update(nInput);
			pItem = network.GetPressConfirmButton();
			if(pItem != NULL)
			{
				if(strcmp(pItem->GetName(), "server") == 0)
				{
					#ifdef TRL_PLATFORM_CTR
					void triPiaCommonInit();
					triPiaCommonInit();
					trlEmuShellNetworkInit(1);
					g_bTrlEmuNetRole = eTrlEmuNetMaster;
					#endif
					menu_state = MENU_STATE_CLOSED;
				}
				else if(strcmp(pItem->GetName(), "client") == 0)
				{
					#ifdef TRL_PLATFORM_CTR
					void triPiaCommonInit();
					triPiaCommonInit();
					trlEmuShellNetworkInit(0);
					g_bTrlEmuNetRole = eTrlEmuNetSlave;
					#endif
					menu_state = MENU_STATE_CLOSED;
				}				
				else if(strcmp(pItem->GetName(), "back") == 0)
				{
					menu_state = MENU_STATE_MAIN;
				}
			}
			pItem = network.GetSelectButton();
			if(strcmp(pItem->GetName(), "delay") == 0)					
			{
				#ifdef TRL_PLATFORM_CTR
				#if TRL_NETWORK_PIA
				extern s32 g_nTrlNetworkDelay;
				g_nTrlNetworkDelay = network.GetItem(network.GetItemByName("delay"))->GetCurNum();
				#endif
				#endif
			}
		}
		break;
	case MENU_STATE_ROM_LIST:
		{
			filelist.update(nInput);
			pItem = filelist.GetPressConfirmButton();
			if(pItem != NULL)
			{
				if(strcmp(pItem->GetName(), "back") == 0)
				{
					menu_state = MENU_STATE_MAIN;
				}
				else if(strcmp(pItem->GetName(), "pre") == 0)
				{
					if(curfileno>0)
						curfileno -= FILE_PER_PAGE;
					BuildRomFileList();
				}
				else if(strcmp(pItem->GetName(), "next") == 0)
				{
					if((curfileno+ FILE_PER_PAGE) < filelistnum)
						curfileno += FILE_PER_PAGE;
					BuildRomFileList();
				}
				else
				{
					for(int i=0;i<FILE_PER_PAGE;i++)
					{
						if(strcmp(pItem->GetName(), filelistname[i]) == 0)
						{
							s32 index = curfileno + i;
							if(index < filelistnum)
							{
								confirm.SetTitle("Menu>ROM Switch");
								confirm.SetText("msg", "Do you want switch to this rom?");
								selectedfile = index;
								g_sEmuShellRomIndex = index;
								menu_state = MENU_STATE_ROM_CONFIRM;
							}
						}
					}
				}
			}
		}
		break;	
	case MENU_STATE_LOAD_LIST:
		{
			filelist.update(nInput);
			pItem = filelist.GetPressConfirmButton();
			if(pItem != NULL)
			{
				if(strcmp(pItem->GetName(), "back") == 0)
				{
					menu_state = MENU_STATE_MAIN;
				}
				else if(strcmp(pItem->GetName(), "pre") == 0)
				{
					if(curfileno>0)
						curfileno -= FILE_PER_PAGE;
					BuildFileList();
				}
				else if(strcmp(pItem->GetName(), "next") == 0)
				{
					if((curfileno+ FILE_PER_PAGE) < filelistnum)
						curfileno += FILE_PER_PAGE;
					BuildFileList();
				}
				else
				{
					for(int i=0;i<FILE_PER_PAGE;i++)
					{
						if(strcmp(pItem->GetName(), filelistname[i]) == 0)
						{
							s32 index = curfileno + i;
							if(index < filelistnum)
							{
								confirm.SetTitle("Menu>Interruption Load");
								confirm.SetText("msg", "Do you want load?");
								selectedfile = index;
								menu_state = MENU_STATE_LOAD_CONFIRM;
							}
						}
					}
				}
			}
			else
			{
				pItem = filelist.GetPressCancelButton();
				if(pItem != NULL)
				{					
					for(int i=0;i<FILE_PER_PAGE;i++)
					{
						if(strcmp(pItem->GetName(), filelistname[i]) == 0)
						{
							s32 index = curfileno + i;
							if(index < filelistnum)
							{
								confirm.SetTitle("Menu>Interruption Delete");
								confirm.SetText("msg", "Do you want Delete?");
								selectedfile = index;
								menu_state = MENU_STATE_DEL_CONFIRM;
							}
						}
					}					
				}
			}

		}
		break;	
	case MENU_STATE_SAVE_CONFIRM:
	case MENU_STATE_DEL_CONFIRM:
	case MENU_STATE_LOAD_CONFIRM:
	case MENU_STATE_RESET_CONFIRM:
	case MENU_STATE_ROM_CONFIRM:
		{
			confirm.update(nInput);
			pItem = confirm.GetPressConfirmButton();
			if(pItem != NULL)
			{
				if(strcmp(pItem->GetName(), "no") == 0)
				{
					menu_state = MENU_STATE_MAIN;
				}
				else if(strcmp(pItem->GetName(), "yes") == 0)
				{
					switch(menu_state)
					{
					case MENU_STATE_SAVE_CONFIRM:
						waitmsg.SetText("msg", "saving");
						menu_state = MENU_STATE_SAVEING;
						break;
					case MENU_STATE_LOAD_CONFIRM:
						waitmsg.SetText("msg", "loading");
						menu_state = MENU_STATE_LOADING;
						break;
					case MENU_STATE_DEL_CONFIRM:
						waitmsg.SetText("msg", "deling");
						menu_state = MENU_STATE_DELING;
						break;
					case MENU_STATE_RESET_CONFIRM:
						trlEmuShellDataReset();
						menu_state = MENU_STATE_CLOSED;
						break;
					case MENU_STATE_ROM_CONFIRM:
						g_bQuit = eTrlQuit_ReBoot;
						menu_state = MENU_STATE_CLOSED;
						break;
					}
				}
			}
		}
		break;
	case MENU_STATE_SAVEING:
		{
			delay_ct++;
			if(delay_ct > 5)
			{
				if(trlEmuShellDataSaveResumeDebug())
				{
					waitmsg.SetText("msg", "save success");
					menu_state = MENU_STATE_SAVE_SUCCESS;
				}
				else
				{
					waitmsg.SetText("msg", "save fail");
					menu_state = MENU_STATE_SAVE_FAIL;
				}
				delay_ct = 0;				
			}
		}
		break;	
	case MENU_STATE_LOADING:
		{
			delay_ct++;
			if(delay_ct > 5)
			{
				if(trlEmuShellDataLoadResumeDebug(selectedfile))
				{
					trlEmuShellDataResume();
					waitmsg.SetText("msg", "load success");
					menu_state = MENU_STATE_LOAD_SUCCESS;
				}
				else
				{
					waitmsg.SetText("msg", "load fail");
					menu_state = MENU_STATE_LOAD_FAIL;
				}
				delay_ct = 0;
			}
		}
		break;
	case MENU_STATE_DELING:
		{
			delay_ct++;
			if(delay_ct > 5)
			{
				if(trlEmuShellDataDeleteResumeDebug(selectedfile))
				{
					waitmsg.SetText("msg", "delete fail");
					menu_state = MENU_STATE_DEL_FAIL;
				}
				else
				{
					waitmsg.SetText("msg", "delete success");
					menu_state = MENU_STATE_DEL_SUCCESS;
				}
				delay_ct = 0;
			}
		}
		break;
	case MENU_STATE_SAVE_SUCCESS:
	case MENU_STATE_LOAD_SUCCESS:
		{
			delay_ct++;
			if(delay_ct > 5)
			{
				menu_state = MENU_STATE_CLOSED;
				delay_ct = 0;
			}
		}
		break;
	case MENU_STATE_SAVE_FAIL:	
		{
			delay_ct++;
			if(delay_ct > 5)
			{
				menu_state = MENU_STATE_MAIN;
				delay_ct = 0;
			}
		}
		break;
	case MENU_STATE_DEL_SUCCESS:
	case MENU_STATE_LOAD_FAIL:
	case MENU_STATE_DEL_FAIL:	
		trlEmuShellDataListResumeDebug();
		BuildFileList();
		menu_state = MENU_STATE_LOAD_LIST;
		break;
	case GMENU_STATE_MAIN:
		colormain.update(nInput);
		colormain.SetComment("");
		pItem = colormain.GetPressConfirmButton();
		if(pItem != NULL)
		{			
			if(strcmp(pItem->GetName(), "dmggray") == 0)
			{
				if(g_sEmuShellBuffer.nRomSubType == TRL_EMUCORE_GBTYPE_DMG)
				{
					color4.SetTitle("Graphic>DMG Gray Palette");
					g_pEmuShellCore->trlEmuCoreSwap(0);
					menu_state = GMENU_STATE_DMG;
				}
			}
			else if(strcmp(pItem->GetName(), "dmgcolor") == 0)
			{
				if(g_sEmuShellBuffer.nRomSubType == TRL_EMUCORE_GBTYPE_DMG)
				{
					color4.SetTitle("Graphic>DMG Color Palette");
					g_pEmuShellCore->trlEmuCoreSwap(1);
					menu_state = GMENU_STATE_CGB;
				}
			}
			else if(strcmp(pItem->GetName(), "lcd") == 0)
			{
				color.SetTitle("Graphic>LCD Palette");
				trlEmuShellMenuColorConvert(g_pEmuShellCore->trlEmuCoreGetPalette(12), nLCDColorChangeMenuValue);
				color.GetItem(color.GetItemByName("red"))->SetCurNum(nLCDColorChangeMenuValue[0]);
				color.GetItem(color.GetItemByName("green"))->SetCurNum(nLCDColorChangeMenuValue[1]);
				color.GetItem(color.GetItemByName("blue"))->SetCurNum(nLCDColorChangeMenuValue[2]);
				menu_state = GMENU_STATE_LCDCOLORCHANGE;
			}
			else if(strcmp(pItem->GetName(), "mask") == 0)
			{
				colormask.SetTitle("Graphic> Mask");
				menu_state = GMENU_STATE_MASK;
			}
			else if(strcmp(pItem->GetName(), "soundreset") == 0)
			{
				menu_state = GMENU_STATE_SOUNDRESET;
			}
			else if(strcmp(pItem->GetName(), "hvcsoundonoff") == 0)
			{
				menu_state = GMENU_STATE_HVCSOUNDONOFF;
			}
			else if(strcmp(pItem->GetName(), "hvcsoundvolume") == 0)
			{
				menu_state = GMENU_STATE_HVCSOUNDVOLUME;
			}
			else if(strcmp(pItem->GetName(), "soundonoff") == 0)
			{
				menu_state = GMENU_STATE_SOUNDONOFF;
			}
			else if(strcmp(pItem->GetName(), "soundset") == 0)
			{
				menu_state = GMENU_STATE_SOUNDSET;
			}
			else if(strcmp(pItem->GetName(), "nesclip") == 0)
			{
				menu_state = GMENU_STATE_NESCLIP;
			}
			else if(strcmp(pItem->GetName(), "quit") == 0)
			{
				menu_state = MENU_STATE_CLOSED;
			}
		}
		else
		{
			pItem = colormain.GetSelectButton();
			if(pItem != NULL)
			{
				if(strcmp(pItem->GetName(), "filter") == 0)
				{
					#ifdef TRL_PLATFORM_CTR
					if(pItem->GetMsgNo() == 0)
						trlEmuShellVideoFilterMode(GL_LINEAR);
					else
						trlEmuShellVideoFilterMode(GL_NEAREST);
					#endif
					colormain.SetComment("Left/Right: change the value");
				}
				else if(strcmp(pItem->GetName(), "vsync") == 0)
				{
					g_sEmuShellBuffer.nVSyncEnable = 1 - pItem->GetMsgNo();
					colormain.SetComment("Left/Right: change the value");
				}
#if TRL_DEBUG
				else if(strcmp(pItem->GetName(), "soundon") == 0)
				{
					g_nTrlEmuSoundOn = 1 - pItem->GetMsgNo();
					colormain.SetComment("Left/Right: change the value");
				}
				else if(strcmp(pItem->GetName(), "graphicon") == 0)
				{
					g_nTrlEmuGraphicOn = 1 - pItem->GetMsgNo();
					colormain.SetComment("Left/Right: change the value");
				}
				else if(strcmp(pItem->GetName(), "emucore") == 0)
				{
					g_nTrlEmuCoreOn = 1 - pItem->GetMsgNo();
					colormain.SetComment("Left/Right: change the value");
				}
#endif
				else if(strcmp(pItem->GetName(), "debugprint") == 0)
				{
					if(g_nDebugInfoEnable < 2)
						if(g_nDebugInfoEnable != (1 - pItem->GetMsgNo()))
							g_nDebugInfoEnable++;
					colormain.SetComment("Left/Right: change the value");
				}
				else if(strcmp(pItem->GetName(), "debugprint") == 0)
				{
					colormain.SetComment("X: On/Off");
				}
			}		
		}
		break;
	case GMENU_STATE_NESCLIP:
		{			
			nesclip.update(nInput);
			pItem = nesclip.GetPressConfirmButton();
			if(pItem != NULL)
			{
				if(strcmp(pItem->GetName(), "back") == 0)
					menu_state = GMENU_STATE_MAIN;
			}
			u32 nTemp;
			nTemp = nesclip.GetItem(nesclip.GetItemByName("clipup"))->GetCurNum();
			g_pNesGrpClip[0] = nTemp;
			nTemp = nesclip.GetItem(nesclip.GetItemByName("clipdown"))->GetCurNum();
			g_pNesGrpClip[1] = 240 - nTemp;
			nTemp = nesclip.GetItem(nesclip.GetItemByName("clipleft"))->GetCurNum();
			g_pNesGrpClip[2] = nTemp;
			nTemp = nesclip.GetItem(nesclip.GetItemByName("clipright"))->GetCurNum();
			g_pNesGrpClip[3] = 256 - nTemp;
		}
		break;
	case GMENU_STATE_SOUNDRESET:
		{
			soundreset.update(nInput);
			pItem = soundreset.GetPressConfirmButton();
			if(pItem != NULL)
			{
				if(strcmp(pItem->GetName(), "back") == 0)
					menu_state = GMENU_STATE_MAIN;
			}
			pItem = soundreset.GetSelectButton();
#if TRL_SOUND_DEBUG
			if(pItem != NULL)
			{
				if(strcmp(pItem->GetName(), "back") == 0)
				{					
				}
				else
				{
					soundreset.SetComment("X: On/Off");
				}
			}
			pItem = soundreset.GetPressCancelButton();
			if(pItem != NULL)
			{
				if(strcmp(pItem->GetName(), "ch1") == 0)	
				{
					g_bCgbSndResetCH1 = 1- g_bCgbSndResetCH1;
					soundreset.GetItem(soundreset.GetItemByName("ch1"))->SetOnOff(g_bCgbSndResetCH1);
				}
				else if(strcmp(pItem->GetName(), "ch2") == 0)	
				{
					g_bCgbSndResetCH2 = 1- g_bCgbSndResetCH2;
					soundreset.GetItem(soundreset.GetItemByName("ch2"))->SetOnOff(g_bCgbSndResetCH2);
				}
				else if(strcmp(pItem->GetName(), "ch3") == 0)	
				{
					g_bCgbSndResetCH3 = 1- g_bCgbSndResetCH3;
					soundreset.GetItem(soundreset.GetItemByName("ch3"))->SetOnOff(g_bCgbSndResetCH3);
				}
				else if(strcmp(pItem->GetName(), "ch4") == 0)
				{
					g_bCgbSndResetCH4 = 1- g_bCgbSndResetCH4;
					soundreset.GetItem(soundreset.GetItemByName("ch4"))->SetOnOff(g_bCgbSndResetCH4);
				}
			}
#endif
		}
		break;
#if TRL_HVC_SOUND_TEST
	case GMENU_STATE_HVCSOUNDONOFF:
		{
			hvcsoundonoff.update(nInput);
			pItem = hvcsoundonoff.GetPressConfirmButton();
			if(pItem != NULL)
			{
				if(strcmp(pItem->GetName(), "back") == 0)
					menu_state = GMENU_STATE_MAIN;
			}
			pItem = hvcsoundonoff.GetSelectButton();
			if(pItem != NULL)
			{
				if(strcmp(pItem->GetName(), "back") == 0)
				{					
				}
				else
				{
					hvcsoundonoff.SetComment("X: On/Off");
				}
			}
			pItem = hvcsoundonoff.GetPressCancelButton();
			if(pItem != NULL)
			{
				if(strcmp(pItem->GetName(), "CH_A") == 0)	
				{
					g_bNesSndA = 1- g_bNesSndA;
					hvcsoundonoff.GetItem(hvcsoundonoff.GetItemByName("CH_A"))->SetOnOff(g_bNesSndA);
				}
				else if(strcmp(pItem->GetName(), "CH_B") == 0)	
				{
					g_bNesSndB = 1- g_bNesSndB;
					hvcsoundonoff.GetItem(hvcsoundonoff.GetItemByName("CH_B"))->SetOnOff(g_bNesSndB);
				}
				else if(strcmp(pItem->GetName(), "CH_C") == 0)	
				{
					g_bNesSndC = 1- g_bNesSndC;
					hvcsoundonoff.GetItem(hvcsoundonoff.GetItemByName("CH_C"))->SetOnOff(g_bNesSndC);
				}
				else if(strcmp(pItem->GetName(), "CH_D") == 0)	
				{
					g_bNesSndD = 1- g_bNesSndD;
					hvcsoundonoff.GetItem(hvcsoundonoff.GetItemByName("CH_D"))->SetOnOff(g_bNesSndD);
				}
				else if(strcmp(pItem->GetName(), "CH_E") == 0)	
				{
					g_bNesSndE = 1- g_bNesSndE;
					hvcsoundonoff.GetItem(hvcsoundonoff.GetItemByName("CH_E"))->SetOnOff(g_bNesSndE);
				}
				else if(strcmp(pItem->GetName(), "CH_F") == 0)	
				{
					g_bNesSndF = 1- g_bNesSndF;
					hvcsoundonoff.GetItem(hvcsoundonoff.GetItemByName("CH_F"))->SetOnOff(g_bNesSndF);
				}
				else if(strcmp(pItem->GetName(), "CH_5A") == 0)	
				{
					g_bNesSnd5A = 1- g_bNesSnd5A;
					hvcsoundonoff.GetItem(hvcsoundonoff.GetItemByName("CH_5A"))->SetOnOff(g_bNesSnd5A);
				}
				else if(strcmp(pItem->GetName(), "CH_5B") == 0)	
				{
					g_bNesSnd5B = 1- g_bNesSnd5B;
					hvcsoundonoff.GetItem(hvcsoundonoff.GetItemByName("CH_5B"))->SetOnOff(g_bNesSnd5B);
				}
				else if(strcmp(pItem->GetName(), "CH_Z") == 0)	
				{
					g_bNesSndZ = 1- g_bNesSndZ;
					hvcsoundonoff.GetItem(hvcsoundonoff.GetItemByName("CH_Z"))->SetOnOff(g_bNesSndZ);
				}
				else if(strcmp(pItem->GetName(), "CH_Q1") == 0)	
				{
					g_bNesSndQ1 = 1- g_bNesSndQ1;
					hvcsoundonoff.GetItem(hvcsoundonoff.GetItemByName("CH_Q1"))->SetOnOff(g_bNesSndQ1);
				}	
				else if(strcmp(pItem->GetName(), "CH_Q2") == 0)	
				{
					g_bNesSndQ2 = 1- g_bNesSndQ2;
					hvcsoundonoff.GetItem(hvcsoundonoff.GetItemByName("CH_Q2"))->SetOnOff(g_bNesSndQ2);
				}
				else if(strcmp(pItem->GetName(), "CH_Q3") == 0)	
				{
					g_bNesSndQ3 = 1- g_bNesSndQ3;
					hvcsoundonoff.GetItem(hvcsoundonoff.GetItemByName("CH_Q3"))->SetOnOff(g_bNesSndQ3);
				}
			}
		}
		break;
	case GMENU_STATE_HVCSOUNDVOLUME:
		{
			hvcsoundvolume.update(nInput);
			pItem = hvcsoundvolume.GetPressConfirmButton();
			if(pItem != NULL)
			{
				if(strcmp(pItem->GetName(), "back") == 0)
					menu_state = GMENU_STATE_MAIN;
			}
			u32 nTemp;
			nTemp = hvcsoundvolume.GetItem(hvcsoundvolume.GetItemByName("CH_A"))->GetCurNum();
			g_fNesSndScaleA = nTemp/10.0;
			nTemp = hvcsoundvolume.GetItem(hvcsoundvolume.GetItemByName("CH_B"))->GetCurNum();
			g_fNesSndScaleB = nTemp/10.0;
			nTemp = hvcsoundvolume.GetItem(hvcsoundvolume.GetItemByName("CH_C"))->GetCurNum();
			g_fNesSndScaleC = nTemp/10.0;
			nTemp = hvcsoundvolume.GetItem(hvcsoundvolume.GetItemByName("CH_D"))->GetCurNum();
			g_fNesSndScaleD = nTemp/10.0;
			nTemp = hvcsoundvolume.GetItem(hvcsoundvolume.GetItemByName("CH_E"))->GetCurNum();
			g_fNesSndScaleE = nTemp/10.0;
			nTemp = hvcsoundvolume.GetItem(hvcsoundvolume.GetItemByName("CH_F"))->GetCurNum();
			g_fNesSndScaleF = nTemp/10.0;
			nTemp = hvcsoundvolume.GetItem(hvcsoundvolume.GetItemByName("CH_5A"))->GetCurNum();
			g_fNesSndScale5A = nTemp/10.0;
			nTemp = hvcsoundvolume.GetItem(hvcsoundvolume.GetItemByName("CH_5B"))->GetCurNum();
			g_fNesSndScale5B = nTemp/10.0;
			nTemp = hvcsoundvolume.GetItem(hvcsoundvolume.GetItemByName("CH_Z"))->GetCurNum();
			g_fNesSndScaleZ = nTemp/10.0;

			nTemp = hvcsoundvolume.GetItem(hvcsoundvolume.GetItemByName("CH_Q1"))->GetCurNum();
			g_fNesSndScaleQ1 = nTemp/10.0;
			nTemp = hvcsoundvolume.GetItem(hvcsoundvolume.GetItemByName("CH_Q2"))->GetCurNum();
			g_fNesSndScaleQ2 = nTemp/10.0;
			nTemp = hvcsoundvolume.GetItem(hvcsoundvolume.GetItemByName("CH_Q3"))->GetCurNum();
			g_fNesSndScaleQ3 = nTemp/10.0;
		}
		break;
#endif
	case GMENU_STATE_SOUNDONOFF:
		{
			soundonoff.update(nInput);
			pItem = soundonoff.GetPressConfirmButton();
			if(pItem != NULL)
			{
				if(strcmp(pItem->GetName(), "back") == 0)
					menu_state = GMENU_STATE_MAIN;
			}
#if TRL_SOUND_DEBUG
			pItem = soundonoff.GetSelectButton();
			if(pItem != NULL)
			{
				if(strcmp(pItem->GetName(), "back") == 0)
				{					
				}
				else
				{
					soundonoff.SetComment("X: On/Off");
				}
			}
			pItem = soundonoff.GetPressCancelButton();
			if(pItem != NULL)
			{
				if(strcmp(pItem->GetName(), "ch1") == 0)	
				{
					g_bCgbSndOnOffCH1 = 1- g_bCgbSndOnOffCH1;
					soundonoff.GetItem(soundonoff.GetItemByName("ch1"))->SetOnOff(g_bCgbSndOnOffCH1);
				}
				else if(strcmp(pItem->GetName(), "ch2") == 0)	
				{
					g_bCgbSndOnOffCH2 = 1- g_bCgbSndOnOffCH2;
					soundonoff.GetItem(soundonoff.GetItemByName("ch2"))->SetOnOff(g_bCgbSndOnOffCH2);
				}
				else if(strcmp(pItem->GetName(), "ch3") == 0)	
				{
					g_bCgbSndOnOffCH3 = 1- g_bCgbSndOnOffCH3;
					soundonoff.GetItem(soundonoff.GetItemByName("ch3"))->SetOnOff(g_bCgbSndOnOffCH3);
				}
				else if(strcmp(pItem->GetName(), "ch4") == 0)
				{
					g_bCgbSndOnOffCH4 = 1- g_bCgbSndOnOffCH4;
					soundonoff.GetItem(soundonoff.GetItemByName("ch4"))->SetOnOff(g_bCgbSndOnOffCH4);
				}
			}
#endif
		}
		break;
	case GMENU_STATE_SOUNDSET:
		{
			soundset.update(nInput);
			pItem = soundset.GetPressConfirmButton();
			if(pItem != NULL)
			{
				if(strcmp(pItem->GetName(), "back") == 0)
					menu_state = GMENU_STATE_MAIN;
			}
			pItem = soundset.GetSelectButton();
			if(pItem != NULL)
			{
				if(strcmp(pItem->GetName(), "back") == 0)
				{					
				}
				else
				{
					soundset.SetComment("LEFT/RIGHT: Change Value");
				}
			}
#ifdef TRL_PLATFORM_CTR
			g_pTrlAudioVoice->SetVolume(soundset.GetItem(soundset.GetItemByName("volume"))->GetCurNum()*1.0f/100.0f);			
			g_pTrlAudioVoice->SetMonoFilterCoefficients(soundset.GetItem(soundset.GetItemByName("cutrate"))->GetCurNum());
			
#endif
		}
		break;
	case GMENU_STATE_MASK:
		{
			colormask.update(nInput);
			u32 nTemp = colormask.GetItem(colormask.GetItemByName("dark"))->GetCurNum();
			if(nTemp!=*g_sTrlVideoMaskData.pDark)
			{
				*g_sTrlVideoMaskData.pDark = nTemp;
				trlEmuShellVideoMaskMode();
			}
			nTemp = colormask.GetItem(colormask.GetItemByName("motionblurmode"))->GetCurNum();
			if(nTemp!=*g_sTrlVideoMaskData.pMotionBlur)
			{
				*g_sTrlVideoMaskData.pMotionBEnable = nTemp;
				trlEmuShellVideoMotionBlur();
			}
			nTemp = colormask.GetItem(colormask.GetItemByName("motionblur"))->GetCurNum();
			if(nTemp!=*g_sTrlVideoMaskData.pMotionBlur)
			{
				*g_sTrlVideoMaskData.pMotionBlur = nTemp;
				trlEmuShellVideoMotionBlur();
			}
			pItem = colormask.GetPressConfirmButton();
			if(pItem != NULL)
			{		

				if(strcmp(pItem->GetName(), "back") == 0)
					menu_state = GMENU_STATE_MAIN;
				else if(strcmp(pItem->GetName(), "reduce") == 0)
				{				
					color.SetTitle("Graphic >Mask >Reduce Color");
					color.GetItem(color.GetItemByName("red"))->SetCurNum(*g_sTrlVideoMaskData.pReduceColorR);
					color.GetItem(color.GetItemByName("green"))->SetCurNum(*g_sTrlVideoMaskData.pReduceColorG);
					color.GetItem(color.GetItemByName("blue"))->SetCurNum(*g_sTrlVideoMaskData.pReduceColorB);
					menu_state = GMENU_STATE_MASKCOLORCHANGE;
				}			
			}

			pItem = colormask.GetSelectButton();
			if(pItem != NULL)
			{
				if(strcmp(pItem->GetName(), "normal") == 0)
				{
					colormask.SetComment("X: All Off");
				}
				else if(strcmp(pItem->GetName(), "reduce") == 0)
				{
					colormask.SetComment("Y: Enter    X: On/Off");
				}
				else if(strcmp(pItem->GetName(), "motionblurmode") == 0)
				{
					colormask.SetComment("Left/Right: change the value");
				}
				else if(strcmp(pItem->GetName(), "motionblur") == 0)
				{
					colormask.SetComment("Left/Right: change the value");
				}
				else if(strcmp(pItem->GetName(), "dark") == 0)
				{
					colormask.SetComment("Left/Right: change the value    X: On/Off");
				}
			}

			pItem = colormask.GetPressCancelButton();
			if(pItem != NULL)
			{
				if(strcmp(pItem->GetName(), "normal") == 0)	
				{
					*g_sTrlVideoMaskData.pReduceEnable = 0;
					*g_sTrlVideoMaskData.pDarkEnable = 0;
					*g_sTrlVideoMaskData.pMotionBEnable = 0;
					
					colormask.GetItem(colormask.GetItemByName("dark"))->SetOnOff(*g_sTrlVideoMaskData.pDarkEnable);	
					colormask.GetItem(colormask.GetItemByName("reduce"))->SetOnOff(*g_sTrlVideoMaskData.pReduceEnable);	
					colormask.GetItem(colormask.GetItemByName("motionblurmode"))->SetCurNum(*g_sTrlVideoMaskData.pMotionBEnable);
					trlEmuShellVideoMaskMode();
				}
				else if(strcmp(pItem->GetName(), "reduce") == 0)
				{
					*g_sTrlVideoMaskData.pReduceEnable = 1- *g_sTrlVideoMaskData.pReduceEnable;
					colormask.GetItem(colormask.GetItemByName("reduce"))->SetOnOff(*g_sTrlVideoMaskData.pReduceEnable);	
					trlEmuShellVideoMaskMode();
				}
				else if(strcmp(pItem->GetName(), "dark") == 0)
				{
					*g_sTrlVideoMaskData.pDarkEnable = 1 - *g_sTrlVideoMaskData.pDarkEnable;
					colormask.GetItem(colormask.GetItemByName("dark"))->SetOnOff(*g_sTrlVideoMaskData.pDarkEnable);	
					trlEmuShellVideoMaskMode();
				}
				/*else if(strcmp(pItem->GetName(), "motionblur") == 0)
				{
					*g_sTrlVideoMaskData.pMotionBEnable = 1- *g_sTrlVideoMaskData.pMotionBEnable;
					colormask.GetItem(colormask.GetItemByName("motionblur"))->SetOnOff(*g_sTrlVideoMaskData.pMotionBEnable);
				}*/
			}
		}
		break;
	case GMENU_STATE_DMG:
		color4.update(nInput);		
		pItem = color4.GetPressConfirmButton();
		if(pItem != NULL)
		{			
			if(strcmp(pItem->GetName(), "back") == 0)
				menu_state = GMENU_STATE_MAIN;
			else
			{
				if(strcmp(pItem->GetName(), "color0") == 0)
				{
					color.SetTitle("Graphic>DMG Gary Palette>Color0");
					trlEmuShellMenuColorConvert(g_pEmuShellCore->trlEmuCoreGetPalette(0), nDMGColorChangeMenuValue);
					menu_state = GMENU_STATE_DMGCOLORCHANGE0;
				}
				else if(strcmp(pItem->GetName(), "color1") == 0)
				{
					color.SetTitle("Graphic>DMG Gary Palette>Color1");
					trlEmuShellMenuColorConvert(g_pEmuShellCore->trlEmuCoreGetPalette(1), nDMGColorChangeMenuValue);
					menu_state = GMENU_STATE_DMGCOLORCHANGE1;
				}
				else if(strcmp(pItem->GetName(), "color2") == 0)
				{
					color.SetTitle("Graphic>DMG Gary Palette>Color2");
					trlEmuShellMenuColorConvert(g_pEmuShellCore->trlEmuCoreGetPalette(2), nDMGColorChangeMenuValue);
					menu_state = GMENU_STATE_DMGCOLORCHANGE2;
				}
				else if(strcmp(pItem->GetName(), "color3") == 0)
				{
					color.SetTitle("Graphic>DMG Gary Palette>Color3");
					trlEmuShellMenuColorConvert(g_pEmuShellCore->trlEmuCoreGetPalette(3), nDMGColorChangeMenuValue);
					menu_state = GMENU_STATE_DMGCOLORCHANGE3;
				}
				color.GetItem(color.GetItemByName("red"))->SetCurNum(nDMGColorChangeMenuValue[0]);
				color.GetItem(color.GetItemByName("green"))->SetCurNum(nDMGColorChangeMenuValue[1]);
				color.GetItem(color.GetItemByName("blue"))->SetCurNum(nDMGColorChangeMenuValue[2]);
			}
		}
		break;
	case GMENU_STATE_CGB:
		cgbpalette.update(nInput);		
		pItem = cgbpalette.GetPressConfirmButton();
		if(pItem != NULL)
		{			
			if(strcmp(pItem->GetName(), "back") == 0)
				menu_state = GMENU_STATE_MAIN;
			else if(strcmp(pItem->GetName(), "bg") == 0)
			{
				color3.SetTitle("Graphic>DMG Color Palette>BG");
				menu_state = GMENU_STATE_BGCOLOR;
			}
			else if(strcmp(pItem->GetName(), "obj0") == 0)
			{
				color3.SetTitle("Graphic>DMG Color Palette>OBJ0");
				menu_state = GMENU_STATE_OBJCOLOR0;
			}
			else if(strcmp(pItem->GetName(), "obj1") == 0)
			{
				color3.SetTitle("Graphic>DMG Color Palette>OBJ1");
				menu_state = GMENU_STATE_OBJCOLOR1;
			}
		}
		break;
	case GMENU_STATE_BGCOLOR:
		color4.update(nInput);
		pItem = color4.GetPressConfirmButton();
		if(pItem != NULL)
		{			
			if(strcmp(pItem->GetName(), "back") == 0)
				menu_state = GMENU_STATE_CGB;
			{
				if(strcmp(pItem->GetName(), "color0") == 0)
				{
					color.SetTitle("Graphic>DMG Color Palette>BG>Color0");
					trlEmuShellMenuColorConvert(g_pEmuShellCore->trlEmuCoreGetPalette(0), nColorChangeMenuValue);
					menu_state = GMENU_STATE_CGBCOLORCHANGEBG0;
				}
				else if(strcmp(pItem->GetName(), "color1") == 0)
				{
					color.SetTitle("Graphic>DMG Color Palette>BG>Color1");
					trlEmuShellMenuColorConvert(g_pEmuShellCore->trlEmuCoreGetPalette(1), nColorChangeMenuValue);
					menu_state = GMENU_STATE_CGBCOLORCHANGEBG1;
				}
				else if(strcmp(pItem->GetName(), "color2") == 0)
				{
					color.SetTitle("Graphic>DMG Color Palette>BG>Color2");
					trlEmuShellMenuColorConvert(g_pEmuShellCore->trlEmuCoreGetPalette(2), nColorChangeMenuValue);
					menu_state = GMENU_STATE_CGBCOLORCHANGEBG2;
				}
				else if(strcmp(pItem->GetName(), "color3") == 0)
				{
					color.SetTitle("Graphic>DMG Color Palette>BG>Color3");
					trlEmuShellMenuColorConvert(g_pEmuShellCore->trlEmuCoreGetPalette(3), nColorChangeMenuValue);
					menu_state = GMENU_STATE_CGBCOLORCHANGEBG3;
				}
				color.GetItem(color.GetItemByName("red"))->SetCurNum(nColorChangeMenuValue[0]);
				color.GetItem(color.GetItemByName("green"))->SetCurNum(nColorChangeMenuValue[1]);
				color.GetItem(color.GetItemByName("blue"))->SetCurNum(nColorChangeMenuValue[2]);
			}
		}
		break;
	case GMENU_STATE_OBJCOLOR0:
		color3.update(nInput);
		pItem = color3.GetPressConfirmButton();
		if(pItem != NULL)
		{			
			if(strcmp(pItem->GetName(), "back") == 0)
				menu_state = GMENU_STATE_CGB;
			{
				if(strcmp(pItem->GetName(), "color0") == 0)
				{
					color.SetTitle("Graphic>DMG Color Palette>OBJ0>Color0");
					trlEmuShellMenuColorConvert(g_pEmuShellCore->trlEmuCoreGetPalette(4), nColorChangeMenuValue);
					menu_state = GMENU_STATE_CGBCOLORCHANGEOBJ10;
				}
				else if(strcmp(pItem->GetName(), "color1") == 0)
				{
					color.SetTitle("Graphic>DMG Color Palette>OBJ0>Color1");
					trlEmuShellMenuColorConvert(g_pEmuShellCore->trlEmuCoreGetPalette(5), nColorChangeMenuValue);
					menu_state = GMENU_STATE_CGBCOLORCHANGEOBJ11;
				}
				else if(strcmp(pItem->GetName(), "color2") == 0)
				{
					color.SetTitle("Graphic>DMG Color Palette>OBJ0>Color2");
					trlEmuShellMenuColorConvert(g_pEmuShellCore->trlEmuCoreGetPalette(6), nColorChangeMenuValue);
					menu_state = GMENU_STATE_CGBCOLORCHANGEOBJ12;
				}
				else if(strcmp(pItem->GetName(), "color3") == 0)
				{
					color.SetTitle("Graphic>DMG Color Palette>OBJ0>Color3");
					trlEmuShellMenuColorConvert(g_pEmuShellCore->trlEmuCoreGetPalette(7), nColorChangeMenuValue);
					menu_state = GMENU_STATE_CGBCOLORCHANGEOBJ13;
				}
				color.GetItem(color.GetItemByName("red"))->SetCurNum(nColorChangeMenuValue[0]);
				color.GetItem(color.GetItemByName("green"))->SetCurNum(nColorChangeMenuValue[1]);
				color.GetItem(color.GetItemByName("blue"))->SetCurNum(nColorChangeMenuValue[2]);
			}
		}
		break;
	case GMENU_STATE_OBJCOLOR1:
		color3.update(nInput);
		pItem = color3.GetPressConfirmButton();
		if(pItem != NULL)
		{			
			if(strcmp(pItem->GetName(), "back") == 0)
				menu_state = GMENU_STATE_CGB;
			else 
			{
				if(strcmp(pItem->GetName(), "color0") == 0)
				{
					color.SetTitle("Graphic>DMG Color Palette>OBJ1>Color0");
					trlEmuShellMenuColorConvert(g_pEmuShellCore->trlEmuCoreGetPalette(8), nColorChangeMenuValue);
					menu_state = GMENU_STATE_CGBCOLORCHANGEOBJ20;
				}
				else if(strcmp(pItem->GetName(), "color1") == 0)
				{
					color.SetTitle("Graphic>DMG Color Palette>OBJ1>Color1");
					trlEmuShellMenuColorConvert(g_pEmuShellCore->trlEmuCoreGetPalette(9), nColorChangeMenuValue);
					menu_state = GMENU_STATE_CGBCOLORCHANGEOBJ21;
				}
				else if(strcmp(pItem->GetName(), "color2") == 0)
				{
					color.SetTitle("Graphic>DMG Color Palette>OBJ1>Color2");
					trlEmuShellMenuColorConvert(g_pEmuShellCore->trlEmuCoreGetPalette(10), nColorChangeMenuValue);
					menu_state = GMENU_STATE_CGBCOLORCHANGEOBJ22;
				}
				else if(strcmp(pItem->GetName(), "color3") == 0)
				{
					color.SetTitle("Graphic>DMG Color Palette>OBJ1>Color3");
					trlEmuShellMenuColorConvert(g_pEmuShellCore->trlEmuCoreGetPalette(11), nColorChangeMenuValue);
					menu_state = GMENU_STATE_CGBCOLORCHANGEOBJ23;
				}
				color.GetItem(color.GetItemByName("red"))->SetCurNum(nColorChangeMenuValue[0]);
				color.GetItem(color.GetItemByName("green"))->SetCurNum(nColorChangeMenuValue[1]);
				color.GetItem(color.GetItemByName("blue"))->SetCurNum(nColorChangeMenuValue[2]);
			}
		}
		break;
	case GMENU_STATE_DMGCOLORCHANGE0:
	case GMENU_STATE_DMGCOLORCHANGE1:
	case GMENU_STATE_DMGCOLORCHANGE2:
	case GMENU_STATE_DMGCOLORCHANGE3:
		color.update(nInput);		
		nDMGColorChangeMenuValue[0] = color.GetItem(color.GetItemByName("red"))->GetCurNum();
		nDMGColorChangeMenuValue[1] = color.GetItem(color.GetItemByName("green"))->GetCurNum();
		nDMGColorChangeMenuValue[2] = color.GetItem(color.GetItemByName("blue"))->GetCurNum();
		g_pEmuShellCore->trlEmuCoreSetPalette(menu_state - GMENU_STATE_DMGCOLORCHANGE0, trlEmuShellMenuColorGetU16(nDMGColorChangeMenuValue), 1);

		pItem = color.GetPressConfirmButton();
		if(pItem != NULL)
		{
			if(strcmp(pItem->GetName(), "back") == 0)
				menu_state = GMENU_STATE_DMG;
		}
		break;
	case GMENU_STATE_CGBCOLORCHANGEBG0:
	case GMENU_STATE_CGBCOLORCHANGEBG1:
	case GMENU_STATE_CGBCOLORCHANGEBG2:
	case GMENU_STATE_CGBCOLORCHANGEBG3:
	case GMENU_STATE_CGBCOLORCHANGEOBJ10:
	case GMENU_STATE_CGBCOLORCHANGEOBJ11:
	case GMENU_STATE_CGBCOLORCHANGEOBJ12:
	case GMENU_STATE_CGBCOLORCHANGEOBJ13:
	case GMENU_STATE_CGBCOLORCHANGEOBJ20:
	case GMENU_STATE_CGBCOLORCHANGEOBJ21:
	case GMENU_STATE_CGBCOLORCHANGEOBJ22:
	case GMENU_STATE_CGBCOLORCHANGEOBJ23:
		color.update(nInput);
		nColorChangeMenuValue[0] = color.GetItem(color.GetItemByName("red"))->GetCurNum();
		nColorChangeMenuValue[1] = color.GetItem(color.GetItemByName("green"))->GetCurNum();
		nColorChangeMenuValue[2] = color.GetItem(color.GetItemByName("blue"))->GetCurNum();		
		g_pEmuShellCore->trlEmuCoreSetPalette(menu_state - GMENU_STATE_CGBCOLORCHANGEBG0, trlEmuShellMenuColorGetU16(nColorChangeMenuValue), 0);

		pItem = color.GetPressConfirmButton();
		if(pItem != NULL)
		{
			if(strcmp(pItem->GetName(), "back") == 0)
			{
				switch(menu_state)
				{
				case GMENU_STATE_CGBCOLORCHANGEBG0:
				case GMENU_STATE_CGBCOLORCHANGEBG1:
				case GMENU_STATE_CGBCOLORCHANGEBG2:
				case GMENU_STATE_CGBCOLORCHANGEBG3:
					menu_state = GMENU_STATE_BGCOLOR;
					break;
				case GMENU_STATE_CGBCOLORCHANGEOBJ10:
				case GMENU_STATE_CGBCOLORCHANGEOBJ11:
				case GMENU_STATE_CGBCOLORCHANGEOBJ12:
				case GMENU_STATE_CGBCOLORCHANGEOBJ13:
					menu_state = GMENU_STATE_OBJCOLOR0;
					break;
				case GMENU_STATE_CGBCOLORCHANGEOBJ20:
				case GMENU_STATE_CGBCOLORCHANGEOBJ21:
				case GMENU_STATE_CGBCOLORCHANGEOBJ22:
				case GMENU_STATE_CGBCOLORCHANGEOBJ23:
					menu_state = GMENU_STATE_OBJCOLOR1;
					break;
				}
			}
		}		
		break;
	case GMENU_STATE_LCDCOLORCHANGE:
		color.update(nInput);
		nLCDColorChangeMenuValue[0] = color.GetItem(color.GetItemByName("red"))->GetCurNum();
		nLCDColorChangeMenuValue[1] = color.GetItem(color.GetItemByName("green"))->GetCurNum();
		nLCDColorChangeMenuValue[2] = color.GetItem(color.GetItemByName("blue"))->GetCurNum();		
		g_pEmuShellCore->trlEmuCoreSetPalette(12, trlEmuShellMenuColorGetU16(nLCDColorChangeMenuValue), 0);
		pItem = color.GetPressConfirmButton();
		if(pItem != NULL)
		{
			if(strcmp(pItem->GetName(), "back") == 0)
			{
				menu_state = GMENU_STATE_MAIN;				
			}
		}		
		break;
	case GMENU_STATE_MASKCOLORCHANGE:		
		color.update(nInput);
		*g_sTrlVideoMaskData.pReduceColorR = color.GetItem(color.GetItemByName("red"))->GetCurNum();
		*g_sTrlVideoMaskData.pReduceColorG = color.GetItem(color.GetItemByName("green"))->GetCurNum();
		*g_sTrlVideoMaskData.pReduceColorB = color.GetItem(color.GetItemByName("blue"))->GetCurNum();
		trlEmuShellVideoMaskMode();
		pItem = color.GetPressConfirmButton();
		if(pItem != NULL)
		{
			if(strcmp(pItem->GetName(), "back") == 0)
				menu_state = GMENU_STATE_MASK;
		}
		
		break;
	case MENU_STATE_CLOSED:
		g_bMenuOpen = 0;
		break;
	}
}


/** @brief EmuShell Debug Menu Draw*/
void trlEmuShellDebugMenuDraw()
{
	trlEmuShellVideoClear();
	switch(menu_state)
	{
	case MENU_STATE_MAIN:
		debugmain.draw();
		break;
	case MENU_STATE_SAVE_CONFIRM:
	case MENU_STATE_LOAD_CONFIRM:
	case MENU_STATE_DEL_CONFIRM:
	case MENU_STATE_RESET_CONFIRM:
	case MENU_STATE_ROM_CONFIRM:
		confirm.draw();
		break;
	case MENU_STATE_LOAD_LIST:
	case MENU_STATE_ROM_LIST:
		filelist.draw();
		break;
	case MENU_STATE_BUTTONREPEAT:
		buttonrepeat.draw();
		break;
	case MENU_STATE_NETWORK:		
		network.draw();
		break;
	case MENU_STATE_SAVEING:	
	case MENU_STATE_SAVE_SUCCESS:
	case MENU_STATE_SAVE_FAIL:
	case MENU_STATE_LOADING:
	case MENU_STATE_LOAD_SUCCESS:
	case MENU_STATE_LOAD_FAIL:
	case MENU_STATE_DELING:
	case MENU_STATE_DEL_SUCCESS:
	case MENU_STATE_DEL_FAIL:
		waitmsg.draw();
		break;

	case GMENU_STATE_MAIN:
		colormain.draw();
		break;
	case GMENU_STATE_NESCLIP:
		nesclip.draw();
		break;
	case GMENU_STATE_SOUNDRESET:
		soundreset.draw();
		break;
	case GMENU_STATE_HVCSOUNDONOFF:
		hvcsoundonoff.draw();
		break;
	case GMENU_STATE_HVCSOUNDVOLUME:
		hvcsoundvolume.draw();
		break;
	case GMENU_STATE_SOUNDONOFF:
		soundonoff.draw();
		break;
	case GMENU_STATE_SOUNDSET:
		soundset.draw();
		break;
	case GMENU_STATE_MASK:
		colormask.draw();
		break;
	case GMENU_STATE_DMG:
		color4.draw();
		break;
	case GMENU_STATE_CGB:
		cgbpalette.draw();
		break;
	case GMENU_STATE_BGCOLOR:
		color4.draw();
		break;
	case GMENU_STATE_OBJCOLOR0:
		color3.draw();
		break;
	case GMENU_STATE_OBJCOLOR1:
		color3.draw();
		break;
	case GMENU_STATE_DMGCOLORCHANGE0:
	case GMENU_STATE_DMGCOLORCHANGE1:
	case GMENU_STATE_DMGCOLORCHANGE2:
	case GMENU_STATE_DMGCOLORCHANGE3:
		color.draw();
		break;
	case GMENU_STATE_CGBCOLORCHANGEBG0:
	case GMENU_STATE_CGBCOLORCHANGEBG1:
	case GMENU_STATE_CGBCOLORCHANGEBG2:
	case GMENU_STATE_CGBCOLORCHANGEBG3:
	case GMENU_STATE_CGBCOLORCHANGEOBJ10:
	case GMENU_STATE_CGBCOLORCHANGEOBJ11:
	case GMENU_STATE_CGBCOLORCHANGEOBJ12:
	case GMENU_STATE_CGBCOLORCHANGEOBJ13:
	case GMENU_STATE_CGBCOLORCHANGEOBJ20:
	case GMENU_STATE_CGBCOLORCHANGEOBJ21:
	case GMENU_STATE_CGBCOLORCHANGEOBJ22:
	case GMENU_STATE_CGBCOLORCHANGEOBJ23:
		color.draw();
		break;
	case GMENU_STATE_MASKCOLORCHANGE:
		color.draw();
		break;
	case GMENU_STATE_LCDCOLORCHANGE:
		color.draw();
		break;
	case MENU_STATE_CLOSED:
		g_bMenuOpen = 0;
		break;
	}
}

void trlEmuShellDebugMenuUpdate(u16 nInput, u16 nHold)
{
	static int oldhold = 0;
	static int ct = 0;
	if(nHold != 0)
	{
		if(oldhold == nHold)
			ct++;
		else
			ct = 0;
		if(ct >= 80)
			ct = 80;
	}
	else
		ct = 0;
	if(ct>=80)
		trlEmuShellDebugMenuUpdate(nHold);	
	else
		trlEmuShellDebugMenuUpdate(nInput);	
	oldhold = nHold;
}

void trlEmuShellOpenDebugMenu()
{
	if(g_bMenuOpen == 0)
	{
		g_bMenuOpen = 1;
		trlEmuShellDataListResumeDebug();
		menu_state = MENU_STATE_MAIN;
	}
}
void trlEmushellOpenSwitchRom()
{
	if(g_bMenuOpen == 0)
	{
		g_bMenuOpen = 1;
		trlEmuShellDataListResumeDebug();
		BuildRomFileList();
		menu_state = MENU_STATE_ROM_LIST;
	}
}

void trlEmuShellOpenColorMenu()
{
	if(g_bMenuOpen == 0)
	{
		g_bMenuOpen = 2;
		menu_state = GMENU_STATE_MAIN;
		updateColorMaskData();
	}
}

/** @brief EmuShell Debug Info Update */
void trlEmuShellDebugInfoUpdate()
{
	switch(g_nDebugInfoEnable)
	{
	case 1:
		// Error Flag
		if(g_sEmuShellBuffer.bError == 1)
			trlEmuShellVideoDrawDebugWarn(0, "Error!!!");
		else
		{
			// Saving Flag
			if(g_sEmuShellBuffer.nSaveFlag == 1)
			{
				g_sEmuShellBuffer.nSaveFlag = 2;
				trlEmuShellVideoDrawDebugWarn(0, "Saving.");
			}
			else if(g_sEmuShellBuffer.nSaveFlag == 2)
			{
				g_sEmuShellBuffer.nSaveFlag = 0;
				trlEmuShellVideoDrawDebugInfo(0, "        ");
			}
		}

		// FPS Info
		if(g_nFrameTime>0)
		{
			g_nTotalTime += g_nFrameTime;
			g_nTotalTimeV += g_nFrameTimeV;
			++g_nFrameCount;
			if((g_nFrameCount&0x1F) == 0x1F)
			{
				g_nAvgTime = g_nTotalTime/32.0f;
				g_nTotalTime = 0;

				g_nAvgTimeV = g_nTotalTimeV/32.0f;
				g_nTotalTimeV = 0;
			}
			if(g_nMaxTime<g_nFrameTime)
				g_nMaxTime = g_nFrameTime;

			if(g_nMaxTimeV<g_nFrameTimeV)
				g_nMaxTimeV = g_nFrameTimeV;
		}		

		extern s32 g_nTrlEmuOBJNum;
#if TRL_DEBUG
		trlEmuShellVideoDrawDebugInfo(0, "OBJ %3d ", g_nTrlEmuOBJNum);
#endif
		trlEmuShellVideoDrawDebugInfo(1, "%3.2f", g_nAvgTime/100.0f);
		trlEmuShellVideoDrawDebugInfo(2, "%3.2f", g_nFrameTime/100.0f);
		if(g_nMaxTime>17)
			trlEmuShellVideoDrawDebugWarn(3, "%d  ", g_nMaxTime/100);
		else
			trlEmuShellVideoDrawDebugInfo(3, "%d  ", g_nMaxTime/100);


		trlEmuShellVideoDrawDebugInfo(5, "%3.2f", g_nAvgTimeV/100.0f);
		trlEmuShellVideoDrawDebugInfo(6, "%3.2f", g_nFrameTimeV/100.0f);
		trlEmuShellVideoDrawDebugInfo(7, "%3.2f", g_nMaxTimeV/100.0f);
#if TRL_DEBUG
		if(g_nTrlEmuMapper==100){
			switch(g_nTrlEmuFdiskSide){
				case 0:
					trlEmuShellVideoDrawDebugInfo(4, "FDISK1A\n");
					break;
				case 1:
					trlEmuShellVideoDrawDebugInfo(4, "FDISK1B\n");
					break;
				case 2:
					trlEmuShellVideoDrawDebugInfo(4, "FDISK2A\n");
					break;
				case 3:
					trlEmuShellVideoDrawDebugInfo(4, "FDISK2B\n");
					break;
				default:
					trlEmuShellVideoDrawDebugInfo(4, "FDISK%02d\n", g_nTrlEmuFdiskSide);
			}
		}
#endif
#if TRL_PROFILER
		{
			static int ct = 0;
			ct++;
			if((ct%60) == 0)
			{
				NN_LOG("%d:g_nFrameTimeV  = %d  %d  %d %d %d\n", g_sEmuShellBuffer.nFrames, g_nFrameTimeV, g_sEmuShellBuffer.nProfiler1, g_sEmuShellBuffer.nProfiler2, g_sEmuShellBuffer.nProfiler3, g_sEmuShellBuffer.nProfiler4);
			}
		}
		g_sEmuShellBuffer.nProfiler1 = 0;
		g_sEmuShellBuffer.nProfiler2 = 0;
		g_sEmuShellBuffer.nProfiler3 = 0;
		g_sEmuShellBuffer.nProfiler4 = 0;
#endif


		// Nes Info
		//extern u64 g_nNesTimeCPU;
		//extern u64 g_nNesTimeGPU;
		//extern u64 g_nNesTimeAPU;
		//trlEmuShellVideoDrawDebugInfo(5, "%0.2f ", g_nNesTimeCPU/1000.f);
		//trlEmuShellVideoDrawDebugInfo(6, "%0.2f ", g_nNesTimeGPU/1000.f);
		//trlEmuShellVideoDrawDebugInfo(7, "%0.2f ", g_nNesTimeAPU/1000.f);
		//extern u64 g_nCgbTimeOBJ;
		//trlEmuShellVideoDrawDebugInfo(5, "%0.2f ", g_nCgbTimeOBJ/1000.f);
		//g_nCgbTimeOBJ = 0;

		// Network
#if TRL_DEBUG
		if(g_nTrlEmuMapper==100)
			break;
#endif
		#if TRL_NETWORK_IR
		trlEmuShellVideoDrawDebugInfo(debugStringLine, "%d  ", g_sEmuShellBuffer.bNetworkAsync);debugStringLine++;
		#endif

		#if TRL_NETWORK_PIA && TRL_PLATFORM_CTR
		{
			extern bool s_IsInitPiaSync;
			extern s32 s_nHidSyncState;
			extern s32 s_nHidSyncFrameNo;
			int debugStringLine = 4;
			trlEmuShellVideoDrawDebugInfo(debugStringLine, "%s", s_IsInitPiaSync?"Init   ":"NotInit"); debugStringLine++;
			if( s_IsInitPiaSync )
			{
				trlEmuShellVideoDrawDebugInfo(debugStringLine, "F:%05d", s_nHidSyncFrameNo); debugStringLine++;
				trlEmuShellVideoDrawDebugInfo(debugStringLine, "S:%01d", s_nHidSyncState); debugStringLine++;
			} 
			
		}
		#endif		
		break;
	case 2:
		for(u32 n=0; n<8; ++n)
			trlEmuShellVideoDrawDebugInfo(n, "        ");
		g_nDebugInfoEnable = 0;
		break;
	}
}
