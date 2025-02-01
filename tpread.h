/* ---------------------------------------------------------------------------------------------- 
 * 
 * プログラム概要 ： Newさくら麻雀(MJAIクライアント実装版)
 * バージョン     ： 0.1.2.0.204(牌譜ログ名設定処理実装)
 * プログラム名   ： mjs.exe
 * ファイル名     ： tpread.h
 * クラス名       ： MJSTpread
 * 処理概要       ： 東風荘ログ読み込みクラス
 * Ver0.1.0作成日 ： 2022/04/11 15:57:39
 * Ver0.1.1作成日 ： 2022/05/14 22:27:08
 * Ver0.1.2作成日 ： 2022/08/31 22:19:54
 * 最終更新日     ： 2024/10/05 21:35:42
 * 
 * Copyright (c) 2010-2022 Techmilestone, All rights reserved.
 * 
 * ---------------------------------------------------------------------------------------------- */

#pragma once

#ifndef MJSREADTPLOG_H_INCLUDED
#define MJSREADTPLOG_H_INCLUDED

#include <windows.h>
#include "gui.h"
#include "tkinfo.h"

/* ---------------------------------------------------------------------------------------------- */
// 固定値
/* ---------------------------------------------------------------------------------------------- */

// 作業文字配列のサイズ

#define MJSCORE_WORK_COL    8192   // 項目数
#define MJSCORE_WORK_BUF    64     // 作業用配列のバッファサイズ

#define MJSCORE_FGET_BUF    128    // fget処理用のバッファサイズ

/* ---------------------------------------------------------------------------------------------- */
// クラス定義
/* ---------------------------------------------------------------------------------------------- */
class MJSReadTplog
{

	// ------------------------------------------------------------------- 
	// 公開関数定義
	// ------------------------------------------------------------------- 
	public:

	// fgets用ファイル構造体
	FILE *fp;                 // FILE型構造体

	// 作業用文字配列
	char** wk_str;            // 作業用文字配列
	int wk_str_count;         // 作業用文字配列の総数
	int wk_index;             // 作業用文字配列のINDEX

	// ------------------------------------------------------------------- 
	// コンストラクタ
	// ------------------------------------------------------------------- 

	// コンストラクタ定義
	MJSReadTplog() {};

	// デストラクタ定義
	~MJSReadTplog() {};

	/* ----------------------------- */
	// 関数定義
	/* ----------------------------- */

	// ログ確認処理
	int checklog();                          // ログ種別確認：返り値=ログ種別の値

	// 全体処理
	void TpreadInit(MJSGui *gui);            // 初期化処理
	void TpreadExec(MJSTkinfo *tk);          // 読み込み実行処理
	void TpreadPost();                       // 後処理

	// Mjscore読み込み処理
	void Read_mjscore();
	void Set_wk(char* str);

	// 牌番号確認処理
	int Chk_painum(char* str);               // 牌番号の算出
	int Chk_DoraHyoji(int hai);              // ドラ表示牌の算出

	// Tkinfo設定処理
	void Set_tkinfo(MJSTkinfo *tk);                                        // メイン処理
	void Set_tkinfo_tkstart(MJSTkinfo *tk);                                // mjscore_read_mode = 1  ： 卓開始情報読み込み
	void Set_tkinfo_plyprof(MJSTkinfo *tk);                                // mjscore_read_mode = 2  ： プレーヤー情報読み込み
	void Set_tkinfo_kyoku_score(MJSTkinfo *tk, int kyoku_index);           // mjscore_read_mode = 3  ： 局情報とプレーヤー得点情報
	void Set_tkinfo_agariinfo(MJSTkinfo *tk, int kyoku_index);             // mjscore_read_mode = 4  ： 和了情報読み込み
	void Set_tkinfo_haipai(MJSTkinfo *tk, int kyoku_index);                // mjscore_read_mode = 5  ： 配牌情報
	void Set_tkinfo_haipai_sub(MJSTkinfo *tk, int kyoku_index, int pnum);  // mjscore_read_mode = 5a ： 配牌情報(そのサブ処理)
	void Set_tkinfo_dora(MJSTkinfo *tk, int kyoku_index);                  // mjscore_read_mode = 6  ： ドラ情報
	void Set_tkinfo_actinfo(MJSTkinfo *tk, int kyoku_index);               // mjscore_read_mode = 7  ： アクション情報
	bool Set_tkinfo_checkend();                                            // mjscore_read_mode = 8  ： 卓終了確認
	void Set_tkinfo_tkend(MJSTkinfo *tk);                                  // mjscore_read_mode = 9  ： 卓終了情報読み込み

};

#endif/* MJSREADTPLOG_H_INCLUDED */

/* ---------------------------------------------------------------------------------------------- 
 * ソース終了
 * ---------------------------------------------------------------------------------------------- */
