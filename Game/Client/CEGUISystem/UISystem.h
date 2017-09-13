#pragma once
#include "UIGlobal.h"
#include "TDUISystem.h"
#include <OgreRoot.h>
#include <imm.h>
#include "CEGUIString.h"

namespace Ogre
{
	class Root;
};

namespace CEGUI
{
	class System;
	class OgreCEGUIRenderer;
	class CGameUIScript;
	class FalagardActionButton;
	class EventArgs;
	class Window;
};

class CUIWindowMng;
class CUIIconsManager;
class CUIStringSystem;
class CUICreatureBoardSystem;

class CUISystem : public tUISystem
{
public:
	// ���ڴ�С�����ı�
	virtual VOID			OnSizeChange(UINT message, WPARAM wParam, LPARAM lParam);
	// ��������
	virtual VOID			InjectInput(VOID);
	// ����������Ϣ
	virtual BOOL			MessageProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	//����Ƿ���ui�Ͽ�
	virtual BOOL			IsMouseHover(VOID);
	//����Ƿ���������Ϣ�Ͽ�
	virtual BOOL			IsMouseHover_ChatBoard(LONG x, LONG y);
	//���������Ϣ��ĳ����е���Ϣ
	virtual STRING			getChatBoard_HyplinkContex(LONG x, LONG y);
	//����һ���µĽ�ɫ��Ϣ��
	virtual tCreatureBoard*	CreateCreatureBoard(VOID);
	virtual VOID			AddNewBeHitBoard( bool bDouble, LPCTSTR szInfo, FLOAT nStartX, FLOAT nStartY,int nType = 0, int nMoveType = 0);
	//ĳһ��UI�Ƿ��ڴ���
	virtual BOOL			IsWindowShow(LPCTSTR szUIName);
	virtual BOOL			CloseAllWindow();
	//֪ͨUI����һ��UI��ʾģ��
	virtual VOID			FakeObj_Show(LPCTSTR szWinName, LPCTSTR szName);
	//֪ͨUI����һ��UI��ʾģ��
	virtual VOID			FakeObj_Close(LPCTSTR szWinName, LPCTSTR szName);
	
	//--- FOR DEBUG
	virtual VOID		Debug_PushChatString(LPCTSTR szName, LPCTSTR szMsg)	{};
	virtual VOID		Debug_SaveFontTexture(VOID);
	//--- FOR DEBUG
	virtual VOID			ChangeDragFlag(bool Flag);// {m_bIsDragEnd = Flag;}
	virtual BOOL			IsDragFlag(VOID); //{return m_bIsDragEnd;}

	//�߼�������ϵͳ֪ͨ��Ϣ

	//�����ֵ��ļ���strID��Ӧ���ִ������������еĿɱ������%s,%d,....etc��
	virtual STRING			ParserString_VarParam(LPCTSTR strID, ... );
	//�����ֵ��ļ���strID��Ӧ���ִ������������еĿɱ������%s,%d,....etc����Ȼ��ȥ���ִ��е���ɫ���Ʒ�
	virtual STRING			ParserString_NoColor_VarParam(LPCTSTR strID, ... );

	//��strSrc�ִ��е���ɫ���Ʒ�(#B,#Y.....#c00FF00FF....etc)ȥ����������ŵ�strOut
	virtual VOID			ParserString_NoColor(const STRING& strSrc, STRING& strOut, BOOL bControl = FALSE);

	//�����ֵ��ļ���strID��Ӧ���ִ��������޸����еĿɱ������%s,%d,....etc��
	virtual STRING			ParserString_NoVarParam(LPCTSTR strID);
	//�����ֵ��ļ���strID��Ӧ���ִ��������޸����еĿɱ������%s,%d,....etc����Ȼ��ȥ���ִ��е���ɫ���Ʒ�
	virtual STRING			ParserString_NoColor_NoVarParam(LPCTSTR strID);

	//����ģ���ִ���ȡ��
	virtual STRING			getTalkTemplate(const STRING& strKey, UINT index);
	virtual STRING			ModifyChatTemplate(const STRING& strTemp, const STRING& strTalker, const STRING& strTarget);

	virtual STRING			getTalkRandHelpMsg();

	//�鿴��ǰ��ȡ�����EditBox
	virtual BOOL			IsIMEEditboxActive(LPCTSTR szWinName);
	virtual BOOL			IsIMEEditboxEmpty(VOID);
	//���뷨״̬
	virtual INT				GetCurrentIMEState();

	virtual void			OnPushEcsape();

	virtual void			SetPaoPaoActive( bool bActive ) { m_bActivePaoPao = bActive; };

	virtual bool			IsPaoPaoActive() { return m_bActivePaoPao; };

	//��ɫ��ת��
//	FLOAT		OgreColor_CEGUIColor(const Ogre::ColourValue OgreColor);
	virtual UINT				Lumination_OgreColor( UINT OgreColor, INT Lumination );
	virtual INT					OgreColor_Lumination( UINT OgreColor );
//	virtual UINT				OgreColor_CEGUIColor_Limit_Lumination( UINT OgreColor,FLOAT fLumination);
public:
	//�õ�ͼ�������
	CUIIconsManager*			GetIconManager(VOID) { return m_pIconsMng; }
	
	//-----------------------------------------------------------------------
	//ActionButton���
public:
	//�����϶���ʼ(ActionButton����)
	bool						handleActionDragDropStarted(const CEGUI::EventArgs& e);
	//�����룬��ʾSuperTooltip
	bool						handleActionButtonMouseEnter(const CEGUI::EventArgs& e);
	//����뿪������SuperTooltip
	bool						handleActionButtonMouseLeave(const CEGUI::EventArgs& e);
	//ActionButton�ĸ����ڹر�
	bool						handleActionButtonParentHidden(const CEGUI::EventArgs& e);

	//-----------------------------------------------------------------------
	//ActionButton���
public:
	//MeshWindow��ʼ��ʾ
	bool						handleMeshWindowShown(const CEGUI::EventArgs& e);
	//MeshWindow����
	bool						handleMeshWindowHiden(const CEGUI::EventArgs& e);


	//-----------------------------------------------------------------------
	//���������
public:
	//��������Ӻ�
	bool						handleHyperLinkActive(const CEGUI::EventArgs &e);
	bool						handleHyperLinkLeftActive(const CEGUI::EventArgs &e);
	bool						handleHyperLinkRightActive(const CEGUI::EventArgs &e);
	bool						handleHyperLinkInactive(const CEGUI::EventArgs &e);

public:
	//�����ַ����еķǷ������ַ� 2006-3-22
	BOOL		CheckStringFilter(const STRING& strIn);
	//���˽ض��ַ���<ERROR>
	BOOL		CheckStringCode(const STRING& strIn, STRING& strOut);
	//��ȫƥ�����
	virtual BOOL		CheckStringFullCompare(const STRING& strIn, const STRING& strFilterType = "all", BOOL bUseAllTable = TRUE);
	
protected:
	//�϶���ʼ
	VOID		OnDragBeging(CEGUI::FalagardActionButton* pBtnDraging);
	//�϶�������pBtnTargetΪĿ��Btn���Ϊ�գ����ʾ�϶����հ�
	VOID		OnDragEnd(CEGUI::Window* pWindowTarget);

public:
	virtual VOID Initial(VOID*);				// ��ʼ��
	virtual VOID Release(VOID);					// �ͷ�
	virtual VOID Tick(VOID);

	
protected:
	Ogre::Root*					m_pOgreRoot;
	CEGUI::System*				m_pCEGUISystem;
	CEGUI::OgreCEGUIRenderer*	m_pCEGUIRender;

	//�ű�����
	CEGUI::CGameUIScript*		m_pCEGUIScript;
	//���ڹ�����
	CUIWindowMng*				m_pWindowMng;
	//ͼ�������
	CUIIconsManager*			m_pIconsMng;
	//�ı���Դ������
	CUIStringSystem*			m_pStringSystem;
	//��ɫ��Ϣ�������
	CUICreatureBoardSystem*		m_pCreatureBoardSystem;

	//�϶���
	//CEGUI::FalagardActionButton*		m_pBtnInDragging;
	CEGUI::String						m_szNameBtnInDragging;
	bool								m_bIsDragEnd;
	HCURSOR								m_hDraggingCursor;
	bool								m_bActivePaoPao;

//	bool
//	HCURSOR
	
public:
	CUISystem(VOID);
	virtual ~CUISystem(VOID);
	static CUISystem*	GetMe(VOID) { return s_pMe; }

protected:
	static CUISystem* s_pMe;

	WX_DECLARE_DYNAMIC(CUISystem);
};