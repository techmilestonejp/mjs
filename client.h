/* ---------------------------------------------------------------------------------------------- 
 * 
 * プログラム概要 ： Newさくら麻雀(MJAIクライアント実装版)
 * バージョン     ： 0.1.2.0.206(カレントパスの取得)
 * プログラム名   ： mjs.exe
 * ファイル名     ： client.h
 * クラス名       ： MJSMjaiClient
 * 処理概要       ： Mjaiクライアント処理クラス
 * Ver0.1.2作成日 ： 2023/11/19 21:38:17
 * 最終更新日     ： 2024/10/12 15:21:12
 * 
 * Copyright (c) 2010-2024 TechMileStoraJP, All rights reserved.
 * 
 * ---------------------------------------------------------------------------------------------- */

#pragma once

#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED

#include <windows.h>
#include "stdafx.h"

#include "tkinfo.h"
#include "corelog.h"
#include "player.h"
#include "socket.h"
#include "readmjai.h"


/* ---------------------------------------------------------------------------------------------- */
// クラス定義
/* ---------------------------------------------------------------------------------------------- */
class MJSMjaiClient
{

	// -----------------------------
	// 公開関数定義
	// -----------------------------
	public:

	// クラス定義
	MJSCorelog  *clientlog;   // コアログ処理クラス
	MJSSocket sock;           // Socketクラス
	MJSReadMjai *mjai;        // MJAIログ読込みクラス

	// 固定メッセージ
	const char* res_join = "{\"type\":\"join\",\"name\":\"tampopo\",\"room\":\"default\"}\n";
	const char* res_none = "{\"type\":\"none\"}\n";

	// Socketデバグログ
	// char clientlog_name[50];       // ログファイル名
	char clientlog_buf[1024];      // ログバッファ

	// -----------------------------
	// コンストラクタ
	// -----------------------------

	// コンストラクタ定義
	MJSMjaiClient() {};

	// デストラクタ定義
	~MJSMjaiClient() {};

	// -----------------------------
	// 関数定義
	// -----------------------------

	// クライアントクラス初期化・終了処理
	void ClientInit(MJSTkinfo *tk, MJSGui *gui, MJSReadMjai *tmp_mjai);    // Mjaiクライアントの処理開始
	void ClientPost(MJSGui *gui);                                          // Mjaiクライアントの処理終了

	// Socket通信
	void ClientResponseMes(MJSGui *gui);     // 受信処理
	void ClientSendMes(MJSGui *gui);         // 送信処理

	// システム関連処理
	void SetNowTime(MJSTkinfo *tk);          // 現在日時の取得

	// -----------------------------
	// メイン処理
	// -----------------------------
	void CheckTakuStatus(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui, bool tmp_push_flg);

	// -----------------------------
	// 受信処理
	// -----------------------------

	// MJAIメッセージ受信(メイン処理)
	void ChkResMesMain(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui);

	// typeごとでの卓ステー卓設定(MJAIメッセージ受信・サブ処理)
	void Set_possible_actions(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num);                          // possible_actionsメッセージ確認
	void Set_type_hello(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num);                                // helloメッセージ確認
	void Set_type_startgame(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui, int tmp_wk_num);            // 卓ゲーム開始処理
	void Set_type_startkyoku(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui, int tmp_wk_num);           // 局開始処理
	void Set_type_tsumo(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui, int tmp_wk_num);                // 自摸処理
	void Set_type_dahai(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui, int tmp_wk_num);                // 捨牌処理
	void Set_type_riichi(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui, int tmp_wk_num);               // リーチ処理
	void Set_type_ankan(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui, int tmp_wk_num);                // 暗槓処理
	void Set_type_kakan(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui, int tmp_wk_num);                // 加槓処理
	void Set_type_pon(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui, int tmp_wk_num);                  // ポン処理
	void Set_type_chi(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui, int tmp_wk_num);                  // チー処理
	void Set_type_minkan(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui, int tmp_wk_num);               // 明槓処理
	void Set_type_reach_accepted(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui, int tmp_wk_num);       // リーチ受け入れ確認
	void Set_type_hora(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui, int tmp_wk_num);                 // 和了確認
	void Set_type_hora_yaku_check(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui, int tmp_yaku_num);    // 役確認処理用のサブ関数
	void Set_type_ryukyoku(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui, int tmp_wk_num);             // 流局
	void Set_type_endkyoku(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num);                             // 局終了
	void Set_type_endgame(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num);                              // 卓ゲーム終了
	void Set_type_error(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num);                                // errorメッセージ受信時
	void Set_type_others(MJSTkinfo *tk, MJSGui *gui);                                               // 例外処理

	// -----------------------------
	// アクション決定・送信処理
	// -----------------------------

	void SetActTsumo(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui);                                   // 自摸アクション処理
	void SetActSute(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui);                                    // 捨牌アクション処理
	void SetActTsumogiri(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui);                               // 自摸切りアクション処理
	void SetActRiichi(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui);                                  // リーチアクション処理
	void SetActkan(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui);                                     // 暗槓アクション処理
	void SetActNaki(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui);                                    // 鳴きアクション(チー・ポン)処理
	void SetActNakiSute(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui);                                // 鳴き捨牌処理
	void SetActNakiSuteSub(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui);                             // 鳴き捨牌処理(サブ処理)

	// -----------------------------
	// MJAIメッセージ送信
	// -----------------------------

	void ActSndJoinMes(MJSGui *gui);                                                                                                  // ジョインメッセージ
	void ActSndDahaiMes(MJSGui *gui, int ply_mjai_id, int hai, bool aka_flg, bool tsumogiri_flg);                                     // 捨牌メッセージ
	void ActSndRiichiMes(MJSGui *gui, int ply_mjai_id);                                                                               // リーチメッセージ
	void ActSndAnkanMes(MJSGui *gui, int ply_mjai_id, int ankan_hai, int tehai_aka_count);                                            // 暗槓メッセージ
	void ActSndkakanMes(MJSGui *gui, int ply_mjai_id, int nakl_hai, bool naki_aka, int tehai_aka_count);                              // 加槓メッセージ
	void ActSndPonMes(MJSGui *gui, int ply_mjai_id, int ply_target, int nakl_hai, bool nakl_aka, int tehai_aka_count);                // ポンメッセージ
	void ActSndChiMes(MJSGui *gui, int ply_mjai_id, int ply_target, int nakl_hai, bool nakl_aka, int naki_idx, int tehai_aka_count);  // チーメッセージ
	void ActSndMinkanMes(MJSGui *gui, int ply_mjai_id, int ply_target, int nakl_hai, bool nakl_aka, int tehai_aka_count);             // 明槓メッセージ
	void ActSndHoraMes(MJSGui *gui, int ply_mjai_id, int ply_target, int agari_hai, bool agari_aka);                                  // 和了(ロン・ツモ)メッセージ
	void ActSndNoneMes(MJSGui *gui);                                                                                                  // 無効メッセージ

	// -----------------------------
	// サブ関数
	// -----------------------------
	int  Get_hainum(char hai_str[]);                                  // 牌番号取得
	void Get_haichr(int hai_num, bool hai_aka, char hai_str[]);       // Mjai向け牌文字取得
	void Set_uradora(MJSTkinfo *tk, int hai_num, bool hai_aka);       // 裏ドラ取得

	// デバグ用
	void Output_Actionlog(MJSTkinfo *tk, int kyoku_index);            // 卓アクションのログ出力

};

#endif/* CLIENT_H_INCLUDED */

/* ---------------------------------------------------------------------------------------------- 
 * ソース終了
 * ---------------------------------------------------------------------------------------------- */
