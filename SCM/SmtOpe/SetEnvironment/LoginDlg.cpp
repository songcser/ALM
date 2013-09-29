// LoginDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LoginDlg.h"
#include "afxdialogex.h"
#include "SmATL_SetEnvDlg.h"

// CLoginDlg dialog

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLoginDlg::IDD, pParent)
{

}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_Name);
	DDX_Control(pDX, IDC_EDIT2, m_Password);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
//	ON_EN_CHANGE(IDC_EDIT1, &CLoginDlg::OnEnChangeEdit1)
//	ON_EN_CHANGE(IDC_EDIT2, &CLoginDlg::OnEnChangeEdit2)
	ON_BN_CLICKED(IDOK, &CLoginDlg::OnBnClickedOk)
END_MESSAGE_MAP()

void CLoginDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here

	m_Name.GetWindowTextA(m_strName);
	m_Password.GetWindowTextA(m_strPassword);

	CDialogEx::OnOK();
}
