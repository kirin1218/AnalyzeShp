
// AnalyzeShp.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです。
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// CAnalyzeShpApp:
// このクラスの実装については、AnalyzeShp.cpp を参照してください。
//

class CAnalyzeShpApp : public CWinApp
{
public:
	CAnalyzeShpApp();

// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CAnalyzeShpApp theApp;
