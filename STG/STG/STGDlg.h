#include "Background.h"
#include "Player.h"
#pragma once


// CSTGDlg 对话框
class CSTGDlg : public CDialogEx
{
// 构造
public:
	CSTGDlg(CWnd* pParent = nullptr);	// 标准构造函数
	Background m_Background;
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STG_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	CMenu m_menu;
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnUpdateQuit(CCmdUI* pCmdUI);
	afx_msg void OnStart();
	afx_msg void OnEasy();
	afx_msg void OnNormal();
	afx_msg void OnHard();
	afx_msg void OnLunatic();
};
