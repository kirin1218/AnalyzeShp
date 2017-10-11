
// AnalyzeShpDlg.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "AnalyzeShp.h"
#include "AnalyzeShpDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// �A�v���P�[�V�����̃o�[�W�������Ɏg���� CAboutDlg �_�C�A���O

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �_�C�A���O �f�[�^
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

// ����
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


// CAnalyzeShpDlg �_�C�A���O



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


// CAnalyzeShpDlg ���b�Z�[�W �n���h���[

BOOL CAnalyzeShpDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// "�o�[�W�������..." ���j���[���V�X�e�� ���j���[�ɒǉ����܂��B

	// IDM_ABOUTBOX �́A�V�X�e�� �R�}���h�͈͓̔��ɂȂ���΂Ȃ�܂���B
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

	// ���̃_�C�A���O�̃A�C�R����ݒ肵�܂��B�A�v���P�[�V�����̃��C�� �E�B���h�E���_�C�A���O�łȂ��ꍇ�A
	//  Framework �́A���̐ݒ�������I�ɍs���܂��B
	SetIcon(m_hIcon, TRUE);			// �傫���A�C�R���̐ݒ�
	SetIcon(m_hIcon, FALSE);		// �������A�C�R���̐ݒ�

	// TODO: �������������ɒǉ����܂��B

	return TRUE;  // �t�H�[�J�X���R���g���[���ɐݒ肵���ꍇ�������ATRUE ��Ԃ��܂��B
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

// �_�C�A���O�ɍŏ����{�^����ǉ�����ꍇ�A�A�C�R����`�悷�邽�߂�
//  ���̃R�[�h���K�v�ł��B�h�L�������g/�r���[ ���f�����g�� MFC �A�v���P�[�V�����̏ꍇ�A
//  ����́AFramework �ɂ���Ď����I�ɐݒ肳��܂��B

void CAnalyzeShpDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �`��̃f�o�C�X �R���e�L�X�g

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// �N���C�A���g�̎l�p�`�̈���̒���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �A�C�R���̕`��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ���[�U�[���ŏ��������E�B���h�E���h���b�O���Ă���Ƃ��ɕ\������J�[�\�����擾���邽�߂ɁA
//  �V�X�e�������̊֐����Ăяo���܂��B
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
	//	�r�b�N�G���f�B�A��
	if (bBig == FALSE) {
		for (int i = 0; i < bytesize; i++) {
			pData[i] = pCur[i];
		}
	}
	//	���g���G���f�B�A��
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

		//	���R�[�h�f�[�^��ǂݍ���
		while (ReadFile(hFile, byteRecord, sizeof(byteRecord), &dwReadedSize, NULL) && dwReadedSize == sizeof(byteRecord)) {
			pCur = byteRecord;
			pCur = ReadData(pCur, 4, (PBYTE)&record.dwRecordNo, TRUE);
			pCur = ReadData(pCur, 4, (PBYTE)&record.dwContentsLength, TRUE);

			if (header.dwSharpType == 5) {
				//�R���e���c�T�C�Y���ǂݍ���
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
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
	CDialogEx::OnOK();
}
