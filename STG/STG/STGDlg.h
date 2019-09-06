#include "Background.h"
#include "Player.h"
// STGDlg.h: 头文件
//

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
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnUpdateStart(CCmdUI* pCmdUI);
	void PlayMusic(bool mcheck);
	afx_msg void OnUpdateMusic(CCmdUI* pCmdUI);
	afx_msg void OnUpdateQuit(CCmdUI* pCmdUI);
	afx_msg void OnStart();
};
