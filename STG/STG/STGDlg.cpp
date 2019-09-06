
// STGDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "STG.h"
#include "STGDlg.h"
#include "afxdialogex.h"
#include "Background.h"
#include <mmsystem.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif





CSTGDlg::CSTGDlg(CWnd* pParent)
	: CDialogEx(IDD_STG_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSTGDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSTGDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_UPDATE_COMMAND_UI(ID_START, &CSTGDlg::OnUpdateStart)
	ON_UPDATE_COMMAND_UI(ID_MUSIC, &CSTGDlg::OnUpdateMusic)
	ON_UPDATE_COMMAND_UI(ID_QUIT, &CSTGDlg::OnUpdateQuit)
	ON_COMMAND(ID_START, &CSTGDlg::OnStart)
END_MESSAGE_MAP()



BOOL CSTGDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);	
	SetIcon(m_hIcon, FALSE);

	m_menu.LoadMenuW(IDR_MENU);
	SetMenu(& m_menu);

	m_Background.create(CRect(0, 0, 0, 0), this, IDB_BACKGROUND);

	::SetWindowPos(this->m_hWnd, HWND_BOTTOM, 0, 0, 768, 960, SWP_NOZORDER);
	return TRUE; 
}

void CSTGDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this);

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

HCURSOR CSTGDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSTGDlg::OnUpdateStart(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
}

void CSTGDlg::PlayMusic(bool mcheck)
{
	if (mcheck)
		sndPlaySound(TEXT("少女さとり ～ 3rd eye.wav"), SND_ASYNC);
	else
		sndPlaySound(NULL, SND_PURGE);
}


void CSTGDlg::OnUpdateMusic(CCmdUI* pCmdUI)
{
	CWnd* pMain = AfxGetMainWnd();
	CMenu* pMenu = pMain->GetMenu();
	bool bcheck = (bool)pMenu->GetMenuState(ID_MUSIC, MF_CHECKED);
	if (bcheck)
		pMenu->CheckMenuItem(ID_MUSIC, MF_BYCOMMAND | MF_UNCHECKED);
	else
		pMenu->CheckMenuItem(ID_MUSIC, MF_BYCOMMAND | MF_CHECKED);
	PlayMusic(!bcheck);
}



void CSTGDlg::OnUpdateQuit(CCmdUI* pCmdUI)
{
	CDialog::OnCancel();
}


void CSTGDlg::OnStart()
{
	if(!m_Background.startGame())
		CDialog::OnCancel();
}
