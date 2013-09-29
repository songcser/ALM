// ProjectName.cpp : implementation file
//

#include "stdafx.h"
#include "ProjectName.h"
#include "afxdialogex.h"



// CProjectName dialog

IMPLEMENT_DYNAMIC(CProjectName, CDialogEx)

CProjectName::CProjectName(CWnd* pParent /*=NULL*/)
	: CDialogEx(CProjectName::IDD, pParent)
{

}

CProjectName::~CProjectName()
{
}

void CProjectName::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_ProjectPath);
}


BEGIN_MESSAGE_MAP(CProjectName, CDialogEx)
//	ON_EN_CHANGE(IDC_EDIT1, &CProjectName::OnEnChangeEdit1)
	ON_BN_CLICKED(IDOK, &CProjectName::OnBnClickedOk)
END_MESSAGE_MAP()



void CProjectName::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	m_ProjectPath.GetWindowTextA(m_strPath);
	CDialogEx::OnOK();
}
