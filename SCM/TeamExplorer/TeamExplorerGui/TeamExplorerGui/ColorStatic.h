#pragma once

// CColorStatic
class CColorStatic : public CStatic
{
	DECLARE_DYNAMIC(CColorStatic)

public:
	CColorStatic();
	virtual ~CColorStatic();

protected:
	DECLARE_MESSAGE_MAP()

public:
	COLORREF m_TextColor;
	void SetTextColor(COLORREF crText );
	CBrush m_Brush;

	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
};


