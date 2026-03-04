
// MFCTestDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCTest.h"
#include "MFCTestDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonMoverect();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_MOVERECT, &CAboutDlg::OnBnClickedButtonMoverect)
END_MESSAGE_MAP()


// CMFCTestDlg 대화 상자



CMFCTestDlg::CMFCTestDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCTEST_DIALOG, pParent)
	, resultNum(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_Text_Result, resultNum);
}

BEGIN_MESSAGE_MAP(CMFCTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_Sum, &CMFCTestDlg::OnBnClickedButtonSum)
	ON_EN_CHANGE(IDC_EDIT_Num1, &CMFCTestDlg::OnEnChangeEditNum1)
	ON_BN_CLICKED(IDC_BUTTON_MAKEIMAGE, &CMFCTestDlg::OnBnClickedButtonMakeimage)
	ON_BN_CLICKED(IDC_BUTTON_MOVERECT, &CMFCTestDlg::OnBnClickedButtonMoverect)
END_MESSAGE_MAP()


// CMFCTestDlg 메시지 처리기

BOOL CMFCTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	SetDlgItemInt(IDC_EDIT_Num1, 0);
	SetDlgItemInt(IDC_EDIT_Num2, 0);

	UpdateData(false);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCTestDlg::InitImage()
{

	if(m_Image != nullptr)
		m_Image.Destroy();



	//Height에 따라 할당되는 메모리 주소 값이 달라지기에, 아래 예제처럼 연속적으로 할 거면 반드시 지켜주어야 할 사항
	m_Image.Create(nWidth, -nHeight, 8);

	if (nGrayLevel == 8)
	{
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++)
		{
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		}

		m_Image.SetColorTable(0, 256, rgb);
	}
}

void CMFCTestDlg::DrawImage()
{
	if (m_Image == nullptr)
		return;

	CClientDC dc(this);
	m_Image.Draw(dc, 0, 0);
}


void CMFCTestDlg::OnBnClickedButtonSum()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	int num1 = GetDlgItemInt(IDC_EDIT_Num1);
	int num2 = GetDlgItemInt(IDC_EDIT_Num2);

	SetDlgItemInt(IDC_Text_Result, num1 + num2);
}

void CMFCTestDlg::OnEnChangeEditNum1()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// ENM_CHANGE가 있으면 마스크에 ORed를 플래그합니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CMFCTestDlg::OnBnClickedButtonMakeimage()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	InitImage();



	//한줄 메모리 바이트 수 
	// 너비가 200픽셀이고, 현재 한 픽셀당 그레이레벨 8을 부여했기에 1바이트가 부여됨, 고러 한줄은 200바이트 크기가 된다.
	// 추가로, MFC에서 이미지 크기는 4Byte(32bit 때 만들어진거라서 그런가)단위로 정렬이 되어야 함으로, 만약 너비가 200픽셀이였다면 -> 201바이트가 아닌 204바이트가 되어, pitch 값이 204가 됨.
	// 아무튼 그래서, Pitch가 있어야 하는거야, 그냥 width가 아니라
	//
	int nPitch = m_Image.GetPitch();
	unsigned char* fm = (unsigned char*)m_Image.GetBits();

	for (int i = 0; i < 200; i++)
	{
		for (int j = 0; j < 200; j++)
		{
			fm[i * nPitch + j] = j % 256;
		}
	}


	DrawImage();
}

void CAboutDlg::OnBnClickedButtonMoverect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CMFCTestDlg::OnBnClickedButtonMoverect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	for (int i = 0; i < 50; i++)
	{
		MoveRect();
		Sleep(10);
	}
}

void CMFCTestDlg::MoveRect()
{
	if (m_Image == nullptr)
	{
		InitImage();
	}


	unsigned char* fm = (unsigned char*)m_Image.GetBits();
	memset(fm, 0, m_Image.GetWidth() * m_Image.GetHeight());


	for (int i = movingPos_Y; i < rectSize + movingPos_Y; i++)
	{
		for (int j = movingPos_X; j < rectSize + movingPos_X; j++)
		{
			int nPitch = m_Image.GetPitch();

			if(ValidImagePos(j,i))
				fm[i * nPitch + j] = 255;
			
		}
	}

	movingPos_X++;
	movingPos_Y++;

	DrawImage();
}

bool CMFCTestDlg::ValidImagePos(int x, int y)
{

	CRect rect(0, 0, nWidth, nHeight);
	return rect.PtInRect(CPoint(x, y));

}
