// ColorStatic.cpp : implementation file
//

#include "stdafx.h"
#include "TeamExplorerGui.h"
#include "ColorStatic.h"

// CColorStatic
IMPLEMENT_DYNAMIC(CColorStatic, CStatic)

CColorStatic::CColorStatic()
{
	CDC *pDc = GetDC();
	COLORREF BkColor = pDc->GetBkColor();
	m_Brush.CreateSolidBrush(BkColor);
	ReleaseDC(pDc);
	m_TextColor = RGB(0, 0, 0);
}

CColorStatic::~CColorStatic()
{
}

BEGIN_MESSAGE_MAP(CColorStatic, CStatic)
	ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()

void CColorStatic::SetTextColor(COLORREF crText)  
{
	m_TextColor = crText;
	RedrawWindow();  
}

// CColorStatic message handlers
HBRUSH CColorStatic::CtlColor(CDC* pDC, UINT nCtlColor)
{
	// TODO:  Change any attributes of the DC here
	pDC->SetTextColor(m_TextColor);  
	pDC->SetBkMode(TRANSPARENT);  

	// TODO:  Return a non-NULL brush if the parent's handler should not be called
	return m_Brush;
}
