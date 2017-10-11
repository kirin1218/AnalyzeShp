
// AnalyzeShpDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "AnalyzeShp.h"
#include "AnalyzeShpDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// アプリケーションのバージョン情報に使われる CAboutDlg ダイアログ

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

// 実装
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CAnalyzeShpDlg ダイアログ



CAnalyzeShpDlg::CAnalyzeShpDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ANALYZESHP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAnalyzeShpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAnalyzeShpDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CAnalyzeShpDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CAnalyzeShpDlg メッセージ ハンドラー

BOOL CAnalyzeShpDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// "バージョン情報..." メニューをシステム メニューに追加します。

	// IDM_ABOUTBOX は、システム コマンドの範囲内になければなりません。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定

	// TODO: 初期化をここに追加します。

	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

void CAnalyzeShpDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。

void CAnalyzeShpDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// クライアントの四角形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンの描画
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR CAnalyzeShpDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

#include <string>
#include <vector>
#define DATA_DIR "C:\\FastSource\\AnalyzeShp\\Data\\SampleShp\\"

using namespace std;

typedef struct _SHP_FILE_HEADER {
	DWORD dwFileCode;
	DWORD dwNotUse1;
	DWORD dwNotUse2;
	DWORD dwNotUse3;
	DWORD dwNotUse4;
	DWORD dwNotUse5;
	DWORD dwFileLength;
	DWORD dwVer;
	DWORD dwSharpType;
	double dBBXmin;
	double dBBYmin;
	double dBBXmax;
	double dBBYmax;
	double dBBZmin;
	double dBBZmax;
	double dBBMmin;
	double dBBMmax;
}SHP_FILE_HEADER,*PSHP_FILE_HEADER;

typedef struct _RECODE_DATA {
	DWORD dwRecordNo;
	DWORD dwContentsLength;
}RECODE_DATA,*PRECODE_DATA;

BYTE* ReadData(BYTE* pCur, int bytesize, BYTE* pData, BOOL bBig)
{
	//	ビックエンディアン
	if (bBig == FALSE) {
		for (int i = 0; i < bytesize; i++) {
			pData[i] = pCur[i];
		}
	}
	//	リトルエンディアン
	else {
		for (int i = 0; i < bytesize; i++) {
			pData[i] = pCur[bytesize - 1 - i];
		}
	}

	return pCur + bytesize;
}

class CPint
{
public:
	CPint() {};
	CPint( double d1, double d2) {
		x = d1;
		y = d2;
	};
	~CPint() {};
	double x;
	double y;
};
class CPolygon
{
public:
	CPolygon() {};
	~CPolygon() {};

	int type;
	double Box[4];
	int nNumParts;
	int nNumPoints;
	vector<int> vParts;
	vector<CPint*> vPoints;
};

void CAnalyzeShpDlg::OnBnClickedOk()
{
	string strShpFile;
	HANDLE hFile = INVALID_HANDLE_VALUE;
	SHP_FILE_HEADER header;
	RECODE_DATA record;
	vector<RECODE_DATA> vRecord;
	BYTE byteHeader[100];
	BYTE byteRecord[8];
	DWORD dwReadedSize;

	strShpFile = DATA_DIR + string("japan_ver81.shp");

	hFile = CreateFile(strShpFile.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile != INVALID_HANDLE_VALUE) {
		ReadFile(hFile, byteHeader, sizeof(byteHeader), &dwReadedSize, NULL);

		BYTE* pCur = byteHeader;

		pCur = ReadData(pCur, 4, (PBYTE)&header.dwFileCode, TRUE);
		pCur = ReadData(pCur, 4, (PBYTE)&header.dwNotUse1, TRUE);
		pCur = ReadData(pCur, 4, (PBYTE)&header.dwNotUse2, TRUE);
		pCur = ReadData(pCur, 4, (PBYTE)&header.dwNotUse3, TRUE);
		pCur = ReadData(pCur, 4, (PBYTE)&header.dwNotUse4, TRUE);
		pCur = ReadData(pCur, 4, (PBYTE)&header.dwNotUse5, TRUE);
		pCur = ReadData(pCur, 4, (PBYTE)&header.dwFileLength, TRUE);
		pCur = ReadData(pCur, 4, (PBYTE)&header.dwVer, FALSE);
		pCur = ReadData(pCur, 4, (PBYTE)&header.dwSharpType, FALSE);
		pCur = ReadData(pCur, 8, (PBYTE)&header.dBBXmin, FALSE);
		pCur = ReadData(pCur, 8, (PBYTE)&header.dBBYmin, FALSE);
		pCur = ReadData(pCur, 8, (PBYTE)&header.dBBXmax, FALSE);
		pCur = ReadData(pCur, 8, (PBYTE)&header.dBBYmax, FALSE);
		pCur = ReadData(pCur, 8, (PBYTE)&header.dBBZmin, FALSE);
		pCur = ReadData(pCur, 8, (PBYTE)&header.dBBZmax, FALSE);
		pCur = ReadData(pCur, 8, (PBYTE)&header.dBBMmin, FALSE);
		pCur = ReadData(pCur, 8, (PBYTE)&header.dBBMmax, FALSE);

		//	レコードデータを読み込む
		while (ReadFile(hFile, byteRecord, sizeof(byteRecord), &dwReadedSize, NULL) && dwReadedSize == sizeof(byteRecord)) {
			pCur = byteRecord;
			pCur = ReadData(pCur, 4, (PBYTE)&record.dwRecordNo, TRUE);
			pCur = ReadData(pCur, 4, (PBYTE)&record.dwContentsLength, TRUE);

			if (header.dwSharpType == 5) {
				//コンテンツサイズ分読み込む
				BYTE* pData = (BYTE*)LocalAlloc(LMEM_FIXED, record.dwContentsLength);
				if (pData != NULL) {
					int j;
					CPolygon* pPolygon = new CPolygon();

					ReadFile(hFile, pData, record.dwContentsLength, &dwReadedSize, NULL);

					pCur = pData;
					pCur = ReadData(pCur, 4, (PBYTE)&pPolygon->type, FALSE);
					pCur = ReadData(pCur, 8, (PBYTE)&pPolygon->Box[0], FALSE);
					pCur = ReadData(pCur, 8, (PBYTE)&pPolygon->Box[1], FALSE);
					pCur = ReadData(pCur, 8, (PBYTE)&pPolygon->Box[2], FALSE);
					pCur = ReadData(pCur, 8, (PBYTE)&pPolygon->Box[3], FALSE);
					pCur = ReadData(pCur, 4, (PBYTE)&pPolygon->nNumParts, FALSE);
					pCur = ReadData(pCur, 4, (PBYTE)&pPolygon->nNumPoints, FALSE);

					for (j = 0; j < pPolygon->nNumParts; j++) {
						int nPart;
						pCur = ReadData(pCur, 4, (PBYTE)&nPart, FALSE);
						pPolygon->vParts.push_back(nPart);
					}

					for (j = 0; j < pPolygon->nNumPoints; j++) {
						double x;
						double y;
						pCur = ReadData(pCur, 8, (PBYTE)&x, FALSE);
						pCur = ReadData(pCur, 8, (PBYTE)&y, FALSE);
						CPint* pt = new CPint(x, y);
						pPolygon->vPoints.push_back(pt);
					}

					LocalFree(pData);
				}
			}

			vRecord.push_back(record);
		}

		CloseHandle(hFile);
	}
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CDialogEx::OnOK();
}
