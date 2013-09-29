// ShowRetMsgDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TeamExplorerGui.h"
#include "ShowRetMsgDlg.h"
#include "afxdialogex.h"
#include "CheckoutDlg.h"
#include "Public.h"

// CShowRetMsgDlg dialog
IMPLEMENT_DYNAMIC(CShowRetMsgDlg, CDialogEx)

CShowRetMsgDlg::CShowRetMsgDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CShowRetMsgDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_TEAMEXPLORER_ICON);
}

CShowRetMsgDlg::~CShowRetMsgDlg()
{
}

void CShowRetMsgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SHOWRETMSG_RICHEDIT, m_eShowRetMsg);
}

BEGIN_MESSAGE_MAP(CShowRetMsgDlg, CDialogEx)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDOK, &CShowRetMsgDlg::OnBnOK)
	ON_BN_CLICKED(IDCANCEL, &CShowRetMsgDlg::OnBnCancel)
END_MESSAGE_MAP()

// CShowRetMsgDlg message handlers
BOOL CShowRetMsgDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	if(__argc >= 2){
		if(!memcmp("00", __argv[1], 2)){
			ShowSetEnvMsg();
		}
		else if(!memcmp("02", __argv[1], 2)){
			ShowUpdateMsg();
		}
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CShowRetMsgDlg::ShowMergeMsg(int iFrom, BOOL bMergeFlag)
{
	if(iFrom < 0){
		return;
	}

	int iTextLen = m_eShowRetMsg.GetWindowTextLengthA();
	m_eShowRetMsg.SetFocus();
	m_eShowRetMsg.SetSel(iTextLen, iTextLen);

	if(bMergeFlag){
		if(m_pKernel->m_RetMsgs.size() > iFrom){
			m_eShowRetMsg.ReplaceSel((char *)m_pKernel->m_RetMsgs[iFrom].c_str(), 0);
		}
	}
	else{
		if(m_pKernel->m_RetMsgs.size() > iFrom){
			CString cCheckinMsg;
			m_eShowRetMsg.GetWindowTextA(cCheckinMsg);

			int lSelBegin, lSelEnd;
			lSelBegin = cCheckinMsg.GetLength();
			lSelEnd = lSelBegin + (m_pKernel->m_RetMsgs[iFrom]).length();

			if(lSelBegin <= 0){
				lSelBegin = 1;
			}

			CHARFORMAT cf;
			cf.cbSize = sizeof(CHARFORMAT);
			m_eShowRetMsg.SetSel(lSelBegin, lSelEnd);
			m_eShowRetMsg.GetSelectionCharFormat(cf);
			cf.dwEffects ^= CFE_AUTOCOLOR|CFM_SIZE;
			cf.dwMask = CFM_COLOR|CFM_SIZE|CFM_BOLD|CFM_FACE;
			cf.yHeight = 14*14;
			cf.crTextColor = RGB(255, 0, 0);
			m_eShowRetMsg.SetSelectionCharFormat(cf); 
			m_eShowRetMsg.SetSel(-1,-1); 

			m_eShowRetMsg.ReplaceSel(m_pKernel->m_RetMsgs[iFrom].c_str(), 0);
			if(string::npos != m_pKernel->m_RetMsgs[iFrom].find("E160006:")){
				m_eShowRetMsg.ReplaceSel("the revision doesn't exsiting.\r\n");
			}
			else if(string::npos != m_pKernel->m_RetMsgs[iFrom].find("E205000:")){
				m_eShowRetMsg.ReplaceSel("can't have character in revision number.\r\n");
			}
			else if(string::npos != m_pKernel->m_RetMsgs[iFrom].find("E160013:")){
				m_eShowRetMsg.ReplaceSel("the source paths of merge doesn't existiong.\r\n");
			}
		}
	}
}

void CShowRetMsgDlg::ShowRevertMsg(int iFrom, BOOL bRevertFlag)
{
	if(iFrom < 0){
		return;
	}

	int iTextLen = m_eShowRetMsg.GetWindowTextLengthA();
	m_eShowRetMsg.SetFocus();
	m_eShowRetMsg.SetSel(iTextLen, iTextLen);

	if(bRevertFlag){
		if(m_pKernel->m_RetMsgs.size() > iFrom){
			m_eShowRetMsg.ReplaceSel((char *)m_pKernel->m_RetMsgs[iFrom].c_str(), 0);
		}
	}
	else{
		if(m_pKernel->m_RetMsgs.size() > iFrom){
			CString cCheckinMsg;
			m_eShowRetMsg.GetWindowTextA(cCheckinMsg);

			int lSelBegin, lSelEnd;
			lSelBegin = cCheckinMsg.GetLength();
			lSelEnd = lSelBegin + (m_pKernel->m_RetMsgs[iFrom]).length();

			if(lSelBegin <= 0){
				lSelBegin = 1;
			}

			CHARFORMAT cf;
			cf.cbSize = sizeof(CHARFORMAT);
			m_eShowRetMsg.SetSel(lSelBegin, lSelEnd);
			m_eShowRetMsg.GetSelectionCharFormat(cf);
			cf.dwEffects ^= CFE_AUTOCOLOR|CFM_SIZE;
			cf.dwMask = CFM_COLOR|CFM_SIZE|CFM_BOLD|CFM_FACE;
			cf.yHeight = 14*14;
			cf.crTextColor = RGB(255, 0, 0);
			m_eShowRetMsg.SetSelectionCharFormat(cf); 
			m_eShowRetMsg.SetSel(-1,-1); 

			m_eShowRetMsg.ReplaceSel(m_pKernel->m_RetMsgs[iFrom].c_str(), 0);
		}
	}
}

void CShowRetMsgDlg::ShowAddMsg(int iFrom, BOOL bAddFlag)
{
	if(iFrom < 0){
		return;
	}

	int iTextLen = m_eShowRetMsg.GetWindowTextLengthA();
	m_eShowRetMsg.SetFocus();
	m_eShowRetMsg.SetSel(iTextLen, iTextLen);

	if(bAddFlag){
		if(m_pKernel->m_RetMsgs.size() > iFrom){
			m_eShowRetMsg.ReplaceSel((char *)m_pKernel->m_RetMsgs[iFrom].c_str(), 0);
		}
	}
	else{
		if(m_pKernel->m_RetMsgs.size() > iFrom){
			CString cCheckinMsg;
			m_eShowRetMsg.GetWindowTextA(cCheckinMsg);

			int lSelBegin, lSelEnd;
			lSelBegin = cCheckinMsg.GetLength();
			lSelEnd = lSelBegin + (m_pKernel->m_RetMsgs[iFrom]).length();

			if(lSelBegin <= 0){
				lSelBegin = 1;
			}

			CHARFORMAT cf;
			cf.cbSize = sizeof(CHARFORMAT);
			m_eShowRetMsg.SetSel(lSelBegin, lSelEnd);
			m_eShowRetMsg.GetSelectionCharFormat(cf);
			cf.dwEffects ^= CFE_AUTOCOLOR|CFM_SIZE;
			cf.dwMask = CFM_COLOR|CFM_SIZE|CFM_BOLD|CFM_FACE;
			cf.yHeight = 14*14;
			cf.crTextColor = RGB(255, 0, 0);
			m_eShowRetMsg.SetSelectionCharFormat(cf); 
			m_eShowRetMsg.SetSel(-1,-1); 

			m_eShowRetMsg.ReplaceSel(m_pKernel->m_RetMsgs[iFrom].c_str(), 0);
		}
	}
}

void CShowRetMsgDlg::ShowCancelMsg(int iFrom, BOOL bCancelFlag)
{
	if(iFrom < 0){
		return;
	}

	int iTextLen = m_eShowRetMsg.GetWindowTextLengthA();
	m_eShowRetMsg.SetFocus();
	m_eShowRetMsg.SetSel(iTextLen, iTextLen);

	if(bCancelFlag){
		if(m_pKernel->m_RetMsgs.size() > iFrom){
			m_eShowRetMsg.ReplaceSel((char *)m_pKernel->m_RetMsgs[iFrom].c_str(), 0);
		}
	}
	else{
		if(m_pKernel->m_RetMsgs.size() > iFrom){
			CString cCheckinMsg;
			m_eShowRetMsg.GetWindowTextA(cCheckinMsg);

			int lSelBegin, lSelEnd;
			lSelBegin = cCheckinMsg.GetLength();
			lSelEnd = lSelBegin + (m_pKernel->m_RetMsgs[iFrom]).length();

			if(lSelBegin <= 0){
				lSelBegin = 1;
			}

			CHARFORMAT cf;
			cf.cbSize = sizeof(CHARFORMAT);
			m_eShowRetMsg.SetSel(lSelBegin, lSelEnd);
			m_eShowRetMsg.GetSelectionCharFormat(cf);
			cf.dwEffects ^= CFE_AUTOCOLOR|CFM_SIZE;
			cf.dwMask = CFM_COLOR|CFM_SIZE|CFM_BOLD|CFM_FACE;
			cf.yHeight = 14*14;
			cf.crTextColor = RGB(255, 0, 0);
			m_eShowRetMsg.SetSelectionCharFormat(cf); 
			m_eShowRetMsg.SetSel(-1,-1); 

			m_eShowRetMsg.ReplaceSel(m_pKernel->m_RetMsgs[iFrom].c_str(), 0);
		}
	}
}

void CShowRetMsgDlg::ShowCheckinMsg(int iFrom, BOOL bCheckinFlag)
{
	if(iFrom < 0){
		return;
	}

	int iTextLen = m_eShowRetMsg.GetWindowTextLengthA();
	m_eShowRetMsg.SetFocus();
	m_eShowRetMsg.SetSel(iTextLen, iTextLen);

	if(bCheckinFlag){
		if(m_pKernel->m_RetMsgs.size() > iFrom){
			m_eShowRetMsg.ReplaceSel((char *)m_pKernel->m_RetMsgs[iFrom].c_str(), 0);
		}
	}
	else{
		if(m_pKernel->m_RetMsgs.size() > iFrom){
			CString cCheckinMsg;
			m_eShowRetMsg.GetWindowTextA(cCheckinMsg);

			int lSelBegin, lSelEnd;
			lSelBegin = cCheckinMsg.GetLength();
			lSelEnd = lSelBegin + (m_pKernel->m_RetMsgs[iFrom]).length();

			if(lSelBegin <= 0){
				lSelBegin = 1;
			}

			CHARFORMAT cf;
			cf.cbSize = sizeof(CHARFORMAT);
			m_eShowRetMsg.SetSel(lSelBegin, lSelEnd);
			m_eShowRetMsg.GetSelectionCharFormat(cf);
			cf.dwEffects ^= CFE_AUTOCOLOR|CFM_SIZE;
			cf.dwMask = CFM_COLOR|CFM_SIZE|CFM_BOLD|CFM_FACE;
			cf.yHeight = 14*14;
			cf.crTextColor = RGB(255, 0, 0);
			m_eShowRetMsg.SetSelectionCharFormat(cf); 
			m_eShowRetMsg.SetSel(-1,-1); 

			m_eShowRetMsg.ReplaceSel(m_pKernel->m_RetMsgs[iFrom].c_str(), 0);
		}
	}
}

void CShowRetMsgDlg::ShowCommitMsg(int iFrom, BOOL bCommitFlag)
{
	if(iFrom < 0){
		return;
	}

	int iTextLen = m_eShowRetMsg.GetWindowTextLengthA();
	m_eShowRetMsg.SetFocus();
	m_eShowRetMsg.SetSel(iTextLen, iTextLen);

	if(!bCommitFlag){
		CHARFORMAT cf;
		cf.cbSize = sizeof(CHARFORMAT); 
		m_eShowRetMsg.GetDefaultCharFormat(cf);
		cf.dwEffects ^= CFE_AUTOCOLOR;
		cf.dwMask = CFM_COLOR|CFM_SIZE|CFM_BOLD|CFM_FACE;
		cf.yHeight = 14*14;
		cf.crTextColor  = RGB(255, 0, 0);
		m_eShowRetMsg.SetDefaultCharFormat(cf); 
		if(m_pKernel->m_RetMsgs.size() > 0){
			m_eShowRetMsg.ReplaceSel(m_pKernel->m_RetMsgs[0].c_str(), 0);
		}
		return;
	}

	int iSize = m_pKernel->m_RetMsgs.size();
	for(int i = iFrom; i < iSize; i++){
		if(string::npos == m_pKernel->m_RetMsgs[i].find("svn: ")){
			m_eShowRetMsg.ReplaceSel(m_pKernel->m_RetMsgs[i].c_str(), 0);
		}
		else{
			CString cCommitMsg;
			m_eShowRetMsg.GetWindowTextA(cCommitMsg);

			int lSelBegin, lSelEnd;
			lSelBegin = cCommitMsg.GetLength();
			lSelEnd = lSelBegin + (m_pKernel->m_RetMsgs[i]).length();

			if(lSelBegin <= 0){
				lSelBegin = 1;
			}

			CHARFORMAT cf;
			cf.cbSize = sizeof(CHARFORMAT);
			m_eShowRetMsg.SetSel(lSelBegin, lSelEnd);
			m_eShowRetMsg.GetSelectionCharFormat(cf);
			cf.dwEffects ^= CFE_AUTOCOLOR|CFM_SIZE;
			cf.dwMask = CFM_COLOR|CFM_SIZE|CFM_BOLD|CFM_FACE;
			cf.yHeight = 14*14;
			cf.crTextColor = RGB(255, 0, 0);
			m_eShowRetMsg.SetSelectionCharFormat(cf); 
			m_eShowRetMsg.SetSel(-1,-1); 

			m_eShowRetMsg.ReplaceSel(m_pKernel->m_RetMsgs[i].c_str(), 0);
		}
	}
}

void CShowRetMsgDlg::ShowUpdateMsg()
{
	m_pKernel = new CTeamExplorerKernel;

	int j = 0;
	for(int i = 2; i < __argc; i++){
		m_pKernel->ExeUpdate(__argv[i]);
		m_eShowRetMsg.ReplaceSel(m_pKernel->m_RetMsgs[j].c_str(), 0);
		j++;
	}

	m_eShowRetMsg.ReplaceSel("Update completed!", 0);

	delete m_pKernel;
	m_pKernel = NULL;
}

void CShowRetMsgDlg::ShowCheckoutMsg(int iIndex, BOOL bCheckoutFlag)
{
	if(iIndex < 0 || iIndex >= m_pKernel->m_RetMsgs.size()){
		return;
	}

	int iTextLen = m_eShowRetMsg.GetWindowTextLengthA();
	m_eShowRetMsg.SetFocus();
	m_eShowRetMsg.SetSel(iTextLen, iTextLen);

	if(bCheckoutFlag){
		m_eShowRetMsg.ReplaceSel(m_pKernel->m_RetMsgs[iIndex].c_str(), 0);
	}
	else{
		CString cCheckoutMsg;
		m_eShowRetMsg.GetWindowTextA(cCheckoutMsg);

		int lSelBegin, lSelEnd;
		lSelBegin = cCheckoutMsg.GetLength();
		lSelEnd = lSelBegin + (m_pKernel->m_RetMsgs[iIndex]).length();

		if(lSelBegin <= 0){
			lSelBegin = 1;
		}

		CHARFORMAT cf;
		cf.cbSize = sizeof(CHARFORMAT);
		m_eShowRetMsg.SetSel(lSelBegin, lSelEnd);
		m_eShowRetMsg.GetSelectionCharFormat(cf);
		cf.dwEffects ^= CFE_AUTOCOLOR|CFM_SIZE;
		cf.dwMask = CFM_COLOR|CFM_SIZE|CFM_BOLD|CFM_FACE;
		cf.yHeight = 14*14;
		cf.crTextColor = RGB(255, 0, 0);
		m_eShowRetMsg.SetSelectionCharFormat(cf); 
		m_eShowRetMsg.SetSel(-1,-1); 

		m_eShowRetMsg.ReplaceSel(m_pKernel->m_RetMsgs[iIndex].c_str(), 0);
	}
}

void CShowRetMsgDlg::ShowSetEnvMsg()
{
	if(m_pKernel->m_RetMsgs.size() > 0){
		if(0 == (m_pKernel->m_RetMsgs[0]).find("svn: E195012:")){
			CHARFORMAT cf;
			cf.cbSize = sizeof(CHARFORMAT); 
			m_eShowRetMsg.GetDefaultCharFormat(cf);
			cf.dwEffects ^= CFE_AUTOCOLOR;
			cf.dwMask = CFM_COLOR|CFM_SIZE|CFM_BOLD|CFM_FACE;
			cf.yHeight = 14*14;
			cf.crTextColor  = RGB(255, 0, 0);
			m_eShowRetMsg.SetDefaultCharFormat(cf); 

			m_eShowRetMsg.ReplaceSel((m_pKernel->m_RetMsgs[0]).c_str(), 0);
			m_eShowRetMsg.ReplaceSel("the revision doesn't exsiting.\r\n", 0);
		}
		else if(0 == (m_pKernel->m_RetMsgs[0]).find("svn: E170001:")){
			CHARFORMAT cf;
			cf.cbSize = sizeof(CHARFORMAT); 
			m_eShowRetMsg.GetDefaultCharFormat(cf);
			cf.dwEffects ^= CFE_AUTOCOLOR;
			cf.dwMask = CFM_COLOR|CFM_SIZE|CFM_BOLD|CFM_FACE;
			cf.yHeight = 14*14;
			cf.crTextColor  = RGB(255, 0, 0);
			m_eShowRetMsg.SetDefaultCharFormat(cf); 

			m_eShowRetMsg.ReplaceSel((m_pKernel->m_RetMsgs[0]).c_str(), 0);
			m_eShowRetMsg.ReplaceSel("sorry, you have no permission.\r\n", 0);
		}
		else if(0 == (m_pKernel->m_RetMsgs[0]).find("svn: ")){
			CHARFORMAT cf;
			cf.cbSize = sizeof(CHARFORMAT); 
			m_eShowRetMsg.GetDefaultCharFormat(cf);
			cf.dwEffects ^= CFE_AUTOCOLOR;
			cf.dwMask = CFM_COLOR|CFM_SIZE|CFM_BOLD|CFM_FACE;
			cf.yHeight = 14*14;
			cf.crTextColor  = RGB(255, 0, 0);
			m_eShowRetMsg.SetDefaultCharFormat(cf); 

			m_eShowRetMsg.ReplaceSel((m_pKernel->m_RetMsgs[0]).c_str(), 0);
			m_eShowRetMsg.ReplaceSel("arguments error, perhaps, you need input a right revision number.\r\n", 0);
		}
		else{
			m_eShowRetMsg.ReplaceSel((m_pKernel->m_RetMsgs[0]).c_str(), 0);
		}
	}

	if(m_pKernel->m_RetMsgs.size() > 1){
		m_eShowRetMsg.ReplaceSel((m_pKernel->m_RetMsgs[1]).c_str(), 0);
	}
}

void CShowRetMsgDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default

	if(__argc >= 2){
		if(memcmp("02", __argv[1], 2) && memcmp("00", __argv[1], 2)){
			AfxGetApp()->GetMainWnd()->PostMessage(WM_TEAM_EXPLORER_EXIT);
		}
		else{
			CDialogEx::OnClose();
		}
	}
}

void CShowRetMsgDlg::OnBnOK()
{
	// TODO: Add your control notification handler code here
	if(__argc >= 2){
		if(memcmp("02", __argv[1], 2) && memcmp("00", __argv[1], 2)){
			AfxGetApp()->GetMainWnd()->PostMessage(WM_TEAM_EXPLORER_EXIT);
		}
		else{
			CDialogEx::OnOK();
		}
	}
}

void CShowRetMsgDlg::OnBnCancel()
{
	// TODO: Add your control notification handler code here

	if(__argc >= 2){
		if(memcmp("02", __argv[1], 2) && memcmp("00", __argv[1], 2)){
			AfxGetApp()->GetMainWnd()->PostMessage(WM_TEAM_EXPLORER_EXIT);
		}
		else{
			CDialogEx::OnCancel();
		}
	}
}
