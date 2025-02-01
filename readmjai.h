/* ---------------------------------------------------------------------------------------------- 
 * 
 * プログラム概要 ： Newさくら麻雀(MJAIクライアント実装版)
 * バージョン     ： 0.1.2.0.220(MJAIログ表示：カンドラ表示)
 * プログラム名   ： mjs.exe
 * ファイル名     ： readmjai.h
 * クラス名       ： MJSReadMjai
 * 処理概要       ： MJAIログ読み込みクラス
 * Ver0.1.2作成日 ： 2023/10/07 22:32:26
 * 最終更新日     ： 2024/10/30 16:22:54
 * 
 * Copyright (c) 2022-2023 TechMileStoraJP, All rights reserved.
 * 
 * ---------------------------------------------------------------------------------------------- */

#pragma once

#ifndef MJSREADMJAI_H_INCLUDED
#define MJSREADMJAI_H_INCLUDED

#include "stdafx.h"

#include <windows.h>
#include "player.h"
#include "gui.h"
#include "corelog.h"

/* ---------------------------------------------------------------------------------------------- */
// 固定値
/* ---------------------------------------------------------------------------------------------- */

// 作業文字配列のサイズ
#define MJAI_LINE_BUF     1024     // ライン1行(fget処理の1ライン)のバッファサイズ

/* ---------------------------------------------------------------------------------------------- */
// クラス定義
/* ---------------------------------------------------------------------------------------------- */
class MJSReadMjai
{

	// ------------------------------------------------------------------- 
	// 公開関数定義
	// ------------------------------------------------------------------- 
	public:

	// fgets用ファイル構造体
	FILE *fp;                      // FILE型構造体

	// ライン用バッファ
	char line_buf[MJAI_LINE_BUF];  // ライン処理用

	// デバグログ用
	MJSCorelog  *mjaidebug;        // Mjaiデバグログ処理クラス
	char mjaidebug_name[50];       // Mjaiデバグログファイル名
	char mjaidebug_buf[1024];      // Mjaiデバグログバッファ

	// ------------------------------------------------------------------- 
	// コンストラクタ
	// ------------------------------------------------------------------- 

	// コンストラクタ定義
	MJSReadMjai(){};

	// デストラクタ定義
	~MJSReadMjai(){};

	/* ----------------------------- */
	// 関数定義
	/* ----------------------------- */

	// ログファイル読み込み
	void read_logfile_init(MJSGui *gui);                    // 初期化処理
	void read_logfile_exec(MJSTkinfo *tk, MJSGui *gui);     // 読み込み実行処理
	void read_logfile_post();                               // 後処理

	// MJAIログの読み込み処理
	void Read_logline(MJSGui *gui);
	void set_wkinfo(MJSGui *gui, char* str);

	// 卓情報クラスの設定処理
	void set_tkinfo(MJSTkinfo *tk, MJSGui *gui);                                // メイン処理
	void set_type_startgame(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num);        // 01:type_startgame
	void set_type_startkyoku(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num);       // 02:type_startkyoku
	void set_type_tsumo(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num);            // 03:type_tsumo
	void set_type_dahai(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num);            // 04:type_dahai
	void set_type_ankan(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num);            // 05:type_ankan
	void set_type_kakan(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num);            // 06:type_kakan
	void set_type_riichi(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num);           // 07:type_riichi
	void set_type_reach_accepted(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num);   // 08:set_type_reach_accepted
	void set_type_pon(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num);              // 09:set_type_pon
	void set_type_chi(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num);              // 10:set_type_chi
	void set_type_minkan(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num);           // 11:set_type_minkan
	void set_type_dora_open(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num);        // 95:type_dora
	void set_type_hora(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num);             // 96:type_hora
	void set_type_ryukyoku(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num);         // 97:type_ryukyoku
	void set_type_endkyoku(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num);         // 98:type_endkyoku
	void set_type_endgame(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num);          // 99:type_endgame

	// サブ処理
	int Get_hainum(char hai_str[]);

};

#endif /* MJSREADMJAI_H_INCLUDED */

/* ---------------------------------------------------------------------------------------------- 
 * ソース終了
 * ---------------------------------------------------------------------------------------------- */
