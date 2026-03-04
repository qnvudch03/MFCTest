
// MFCTestDlg.h: 헤더 파일
//

#pragma once


// CMFCTestDlg 대화 상자
class CMFCTestDlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCTestDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

	CImage m_Image;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCTEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	void InitImage();
	void DrawImage();

	void MoveRect();

	bool ValidImagePos(int x, int y);

public:
	afx_msg void OnBnClickedButtonSum();
	afx_msg void OnEnChangeEditNum1();
	CString resultNum;
	afx_msg void OnBnClickedButtonMakeimage();
	afx_msg void OnBnClickedButtonMoverect();


private:
	int nWidth = 200;
	int nHeight = 200;
	int nGrayLevel = 8;

	int movingPos_X = 0;
	int movingPos_Y = 0;

	int rectSize = 40;
};
