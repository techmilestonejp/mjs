/* ---------------------------------------------------------------------------------------------- 
 * 
 * プログラム概要 ： さくら麻雀(Ver0.1.2：開発版)
 * バージョン     ： 0.1.2.1.225(MJAIログ表示：3プレーヤ分の役情報構造体定義)
 * プログラム名   ： mjs.exe
 * ファイル名     ： tklog.h
 * クラス名       ： MJSTklog
 * 処理概要       ： 卓情報ログクラス
 * 作成日         ： 2018/11/18 10:12:12
 * Ver0.0.1作成日 ： 2022/04/11 15:57:39
 * Ver0.1.2作成日 ： 2022/08/31 22:19:54
 * Ver0.1.2改変日 ： 2024/09/15 15:28:15
 * 最終更新日     ： 2024/11/07 19:11:07
 * 
 * Copyright (c) 2010-2024 Techmilestone, All rights reserved.
 * 
 * ---------------------------------------------------------------------------------------------- */

#pragma once

#ifndef TKLOG_H_INCLUDED
#define TKLOG_H_INCLUDED

#include <windows.h>
#include "stdafx.h"

#include "corelog.h"
#include "tkinfo.h"

/* ---------------------------------------------------------------------------------------------- */
// クラス定義
/* ---------------------------------------------------------------------------------------------- */
class MJSTklog
{

	/* ----------------------------- */
	// 公開関数定義
	/* ----------------------------- */
	public:

	// クラス定義
	MJSCorelog  *core_log;   // コアログ処理クラス

	// Windows用ログハンドル
	HANDLE   hFile;
	DWORD    dwBytes;

	// 作業用変数
	char tmp_msg[256];        // 一時処理用

	// 表示用麻雀牌
	char CharHai[41][4];
	char kyokutbl[12][8];

	/* ----------------------------- */
	// コンストラクタ
	/* ----------------------------- */

	// コンストラクタ定義
	MJSTklog() {};

	// デストラクタ定義
	~MJSTklog() {};

	// -----------------------------
	// 関数定義
	// -----------------------------

	// 全体処理
	void tklog_init(char *logname);          // ログ処理開始処理
	void tklog_post();                       // ログ処理終了処理

	// ファイル処理
	void tklog_file_init(char *logname);     // ファイル初期化
	void tklog_file_close();                 // ファイルクローズ

	// ログ出力
	void tklog_print(char *msg);             // ログ出力

	// 共通関数
	void tklog_space();                      // 空白
	void tklog_cr();                         // 改行
	void tklog_time();                       // 時間出力

	// -----------------------------
	// MJSログ出力関数
	// -----------------------------

	// メイン処理
	void tklog_print(MJSTkinfo *tk, int log_ver1, int log_ver2, int log_ver3, int log_ver4);   // MJSログ出力メイン処理

	// サブ処理 - 卓開始
	void tklog_000_MJSlogStart(int log_ver1, int log_ver2, int log_ver3, int log_ver4);        // 000：MJSログ開始
	void tklog_011_TakuStart(MJSTkinfo *tk);                                                   // 011：卓開始
	void tklog_012_PlayerInfo(MJSTkinfo *tk);                                                  // 012：プレーヤー情報

	// サブ処理 - 局情報
	void tklog_101_KyokuStart(MJSTkinfo *tk, int kyoku_index);                                 // 101：局開始
	void tklog_102_KyokuPlyInfo(MJSTkinfo *tk, int kyoku_index);                               // 102：局プレーヤー情報
	void tklog_103_DoraInfo(MJSTkinfo *tk, int kyoku_index);                                   // 103：表ドラ情報
	void tklog_11x_HaipaiInfo(MJSTkinfo *tk, int kyoku_index);                                 // 11x：配牌情報
	void tklog_201_Actinfo(MJSTkinfo *tk, int kyoku_index);                                    // 201：アクション情報
	void tklog_21x_Nakiinfo(MJSTkinfo *tk, int kyoku_index);                                   // 21x：鳴き情報
	void tklog_901_AgariInfo(MJSTkinfo *tk, int kyoku_index);                                  // 901：和了情報
	void tklog_902_YakuInfo(MJSTkinfo *tk, int kyoku_index);                                   // 902：役情報
	void tklog_903_kyokuScore(MJSTkinfo *tk, int kyoku_index);                                 // 903：局の合計得点

	// サブ処理 - 卓終了
	void tklog_911_TakuEndScore(MJSTkinfo *tk);                                                // 911：得点結果
	void tklog_919_TakuEnd(MJSTkinfo *tk);                                                     // 919：卓終了
	void tklog_999_MJSlogEnd(int log_ver1, int log_ver2, int log_ver3, int log_ver4);          // 999：MJSログ終了

};

#endif/* TKLOG_H_INCLUDED */

/* ---------------------------------------------------------------------------------------------- 
 * ソース終了
 * ---------------------------------------------------------------------------------------------- */
