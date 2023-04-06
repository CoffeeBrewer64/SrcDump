/**
 * @file trlEmuMenuButtonSet.h
 * @author zhfang
 * @date 2010.03.26
 * @brief trlEmuMenu Button Set
 */
#pragma once
#include <nw/font.h>

class CButtonSet2
{
private:
public:
	~CButtonSet2(){Release();};
	nw::lyt::Layout* pLayout;
	nw::lyt::ArcResourceAccessor* pResAccessor;
	nw::lyt::DrawInfo* pDrawInfo;
	nw::lyt::Drawer* pDrawer;

	static const s32 ANIM_MAX = 32;

	static const s32 PANE_NUM_MAX = 64;
	static const s32 PANE_NAME_LENGTH_MAX = 32;
	char pSetStringPaneName[PANE_NUM_MAX][PANE_NAME_LENGTH_MAX];
	float pSetStringPaneFontSizeX[PANE_NUM_MAX];
	float pSetStringPaneFontSizeY[PANE_NUM_MAX];


	nw::lyt::AnimTransform *pAnimTrans[ANIM_MAX];
	u32 nAnimNum;
	f32 nAnimFrames[ANIM_MAX];
	u32 bAnimEnd[ANIM_MAX];
	u32 bAnimLoop[ANIM_MAX];
	bool bUpdate;

public:
	void InitGX();
	void SetupCamera();

public:
	CButtonSet2(void *arcbuff, const char *lyt_name, nw::lyt::DrawInfo *pDrawInfo, nw::lyt::Drawer *pDrawer);
	CButtonSet2(void *arcbuff, const char *lyt_name, nw::lyt::DrawInfo *pDrawInfo, nw::lyt::Drawer *pDrawer, nw::font::ResFont *pFont);
	void Release();

	s32 addanim(const char *anim_name);

	void bindanim(const char *button_name, u32 anim_index, u32 bLoop = 0, u32 bRecursive = 1);
	void bindanimall(u32 anim_index, u32 bLoop = 0);



	void unbindanim(const char *button_name, u32 anim_index);
	void unbindanim(u32 anim_index);

	void unbindallanim(const char *button_name);
	void unbindallanim();

	void init();
	void update();
	void draw();

	s32 inPaneArea(const char *button_name, s16 x, s16 y);
	s32 inPaneAreaSpecial(const char *button_name, s16 x, s16 y);

	nw::lyt::Pane* searchchild(nw::lyt::Pane *pParent, const char *name);
	nw::lyt::Pane* search(const char *name);

	void SetStringByName(const char *name, const wchar_t *str);
	void SetStringByUserStr(const char *userstr, const wchar_t *str, const int strlen, const float scale = 1.0f);
	void SetStringChildByUserStr(nw::lyt::Pane *pParent, const char *userstr, const wchar_t *str, const int strlen, const float scale = 1.0f);

	void SetFont(nw::lyt::Pane *pParent, nw::font::ResFont *pFont);
	void SetFont(nw::font::ResFont *pFont);

	nw::lyt::AnimTransform* GetAnimTrans(u32 index)
	{
		if(index < nAnimNum)
			return pAnimTrans[index];
		return NULL;
	};

	bool animisend(u32 index);
};
