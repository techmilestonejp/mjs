/* ---------------------------------------------------------------------------------------------- 
 * 
 * プログラム概要 ： Newさくら麻雀(MJAIクライアント実装版)
 * バージョン     ： 0.1.2.1.227(tkinfoに一発、ダブリー変数を導入)
 * プログラム名   ： mjs.exe
 * ファイル名     ： tkinfo.h
 * クラス名       ： MJSTkinfo
 * 処理概要       ： 卓情報クラス
 * Ver0.0.8作成日 ： 2012/05/04 08:57:12
 * Ver0.1.0作成日 ： 2022/04/11 15:57:39
 * Ver0.1.1作成日 ： 2022/06/30 21:19:01
 * Ver0.1.2作成日 ： 2022/08/31 22:19:54
 * 最終更新日     ： 2024/11/16 06:30:45
 * 
 * Copyright (c) 2010-2023 Techmilestone, All rights reserved.
 * 
 * ---------------------------------------------------------------------------------------------- */

#pragma once

#ifndef TKINFO_H_INCLUDED
#define TKINFO_H_INCLUDED

#include "stdafx.h"
#include "common.h"
#include "score.h"

/* ---------------------------------------------------------------------------------------------- */
//  構造体
/* ---------------------------------------------------------------------------------------------- */
// 局プロファイル構造体
struct MJSkyokuinfo{

	// -----------------------------
	// 麻雀卓情報
	// -----------------------------

	// 局情報
	int kyoku_index;                    // 局整理番号
	int kyoku;                          // 局は何か？( 東一局 = 0、 東二局 = 1 )
	int tsumibo;                        // 積み棒
	int riichbo;                        // リーチ棒

	// 乱数シード番号
	int seed_num;                       // 局ごとの乱数シード番号

	// プレーヤー家情報
	int ie[PLAYER_MAX];                 // それぞれに家情報を格納する、東家：0、南家：1、ie[0]=2でプレーヤ0が西家
	int kyoku_oya;                      // その局の親プレーヤー番号

	// プレーヤー得点
	int ply_kyoku_start_score[PLAYER_MAX];  
	int ply_kyoku_end_score[PLAYER_MAX];    

	// -----------------------------
	// 処理時刻
	// -----------------------------

	char kyoku_startdate[12];           // 局の開始日
	char kyoku_starttime[12];           // 局の開始時刻
	char kyoku_enddate[12];             // 局の終了日
	char kyoku_endtime[12];             // 局の終了時刻

	// -----------------------------
	// ドラ情報
	// -----------------------------

	int  doracount;                    // ドラ(裏ドラ)の表示枚数
	int  dora[5];                      // 変換済表ドラの牌番号(標準ドラ0、カンドラ1～4)
	bool dora_aka[5];                  // 表ドラの赤牌有無
	int  dora_actid[5];                // 表ドラのアクション番号
	int  uradora[5];                   // 変換済裏ドラの牌番号(標準ドラ0、カンドラ1～4)
	bool uradora_aka[5];               // 裏ドラの赤牌有無
	int  uradora_actid[5];             // 裏ドラのアクション番号

	// -----------------------------
	// 手牌情報
	// -----------------------------

	int tehai[PLAYER_MAX][PAI_MAX];                    // 配牌時の手牌
	int tehai_mode[PLAYER_MAX][PAI_MAX];               // 配牌時の手牌種別モード(牌4種の区別=2の4乗=16)
	int aka_count[PLAYER_MAX][AKA_TYPE_MAX_COUNT];     // 配牌時の赤牌の枚数

	// -----------------------------
	// 鳴き面子(晒し面子)情報
	// -----------------------------

	int naki_count[PLAYER_MAX];                   // 鳴いた合計メンツ数
	int ankan_count[PLAYER_MAX];                  // アンカン合計面子数
	int kakan_count[PLAYER_MAX];                  // カカン合計面子数

	int   naki_actid[PLAYER_MAX][MEN_MAX];        // 鳴いた時アクション番号(actid)
	LBMen naki_stat[PLAYER_MAX][MEN_MAX];         // 鳴き形式
	int   naki_hai[PLAYER_MAX][MEN_MAX];          // 鳴き牌
	int   naki_mode[PLAYER_MAX][MEN_MAX];         // 鳴き牌の牌種別モード(牌4種の区別：4×4×4=64)
	int   naki_idx[PLAYER_MAX][MEN_MAX];          // 鳴き時の頭牌
	int   naki_aka[PLAYER_MAX][MEN_MAX];          // 赤牌の合計数

	int   naki_mj_idx[PLAYER_MAX][MEN_MAX];       // mjscore牌譜用の鳴きインデックス(作業用)

	// -----------------------------
	// 卓アクション情報
	// -----------------------------

	int    act_count;                             // Act番号
	LBTkSt act_stat[ACTID_MAX];                   // Actステータス
	int    act_ply[ACTID_MAX];                    // Actしたプレーヤの番号
	int    react_ply[ACTID_MAX];                  // Actされた(鳴かれた場合)プレーヤの番号
	int    act_hai[ACTID_MAX];                    // Act牌番号
	int    act_hai_mode[ACTID_MAX];               // Act牌の牌種別モード(牌4種の区別：4種類)
	int    act_idx[ACTID_MAX];                    // Act牌の頭牌
	bool   act_aka[ACTID_MAX];                    // Act牌の赤牌有無
	int    act_hai_sutenum[ACTID_MAX];            // Act牌が左から何番目に切られたのか？

	// -----------------------------
	// 和了情報
	// -----------------------------

	// 和了情報構造体
	int agari_ply_count;                          // 和了プレーヤ数
	MJSYakuinfo ply_agari_yk[3];                  // 3プレーヤの和了役情報(構造体)

	// 役名テーブル情報(東風荘ログ用：通常役・役満共通)
	char yakuname[NORMALYAKU_MAX][40];            // 手役名

	// 和了手牌テーブル(MJAI処理用)
	int  agari_tehaicount;                        // 手牌の合計枚数(自摸牌は含む)
	int  agari_tehaitbl[TEHAI_MAX];               // 牌テーブル
	bool agari_tehaitbl_aka[TEHAI_MAX];           // 牌テーブル(赤牌)

};

/* --------------------------------------------------------------- */
// クラス定義                                                      
/* --------------------------------------------------------------- */

class MJSTkinfo
{
	public:

	// -----------------------------
	// 得点計算用クラス
	// -----------------------------
	MJSScore *sc;                       // 得点計算処理用クラス

	// -----------------------------
	// 局情報構造体
	// -----------------------------

	int kyoku_index;                    // 局数
	MJSkyokuinfo *kyoku;                // 局構造体(ポインタ定義)

	// -----------------------------
	// GUIモードかPLYモードか？
	// -----------------------------

	int  ply_hum_mode;                  // 人かCOMか(0：PLYモード・全員COM、1：GUIモード・人プレーヤーあり)
	bool com_no_chk_tehai_flg;          // COMの手牌情報の有無
	int  runing_mode;                   // 検証モード

	// -----------------------------
	// 卓情報
	// -----------------------------

	char tkgname[32];                   // ゲーム名
	char tkname[64];                    // 卓名
	char tkno[8];                       // 卓番号
	char startdate[12];                 // 開始日
	char starttime[12];                 // 開始時刻
	char enddate[12];                   // 終了日
	char endtime[12];                   // 終了時刻
	int  core_seed_num;                 // コア乱数シード番号
	char mjai_seed_num[24];             // MJAI用シード番号

	/* ----------------------------- */
	// プレーヤ情報
	/* ----------------------------- */

	// プレーヤ名
	char plyname[PLAYER_MAX][24];       // プレーヤー名
	char plyrate[PLAYER_MAX][8];        // プレーヤRait

	// MJAI用変数
	int ply_mjai_id[PLAYER_MAX];        // プレーヤーごとID(MJAI用)
	int ply_mjai_hum_id;                // 人プレーヤーのID(MJAI用)

	// 卓ゲーム結果
	int plyjun[PLAYER_MAX];             // プレーヤー順位
	int plyEndscore[PLAYER_MAX];        // プレーヤ最終得点

	/* ----------------------------- */
	// 卓ルール情報
	/* ----------------------------- */

	int init_score;                     // 初期得点
	LBTkGmTYPE tkgame_type;             // 卓ゲーム種別(東風戦、半荘戦)
	int aka_max[AKA_TYPE_MAX_COUNT];    // 赤牌の最大枚数

	// -----------------------------
	// 牌山読み込みモード
	// -----------------------------
	int yama_setting_mode;              // 0：値読み込み、1：ランダム設定。2：シード値固定

	// -----------------------------
	// 現時点の卓ステータス
	// -----------------------------

	bool end_flg;                       // 終了フラグ
	LBTkSt stat;                        // 卓状態
	int ply_turn;                       // 現在のプレーヤーの順番
	LBPAct ply_act;                     // プレーヤーアクション

	// -----------------------------
	// 牌山情報
	// -----------------------------

	// 自摸牌のポインタ
	int hai_point;                      // 牌の読み込みはどこであるのか？
	int rinshan_point;                  // リンシャン牌の読み込みはどこであるのか？

	// 残り枚数(ビューアー用)
	int remain_hai_count;               // 残り枚数
	int remain_rinshan_count;           // 残り枚数(リンシャン用)

	// 牌山テーブル
	int hai_yama[PAI_COUNT_MAX];        //  0 -   1 表ドラ       - 裏ドラ
                                        //  2 -   3 表槓ドラ1    - 裏槓ドラ1
                                        //  4 -   9 表槓ドラ2～4 - 裏槓ドラ2～4
                                        // 10 -  13 リンシャン牌
                                        // 14 -  26 プレーヤー配牌(プレーヤー1)
                                        // 27 -  39 プレーヤー配牌(プレーヤー2)
                                        // 40 -  52 プレーヤー配牌(プレーヤー3)
                                        // 53 -  65 プレーヤー配牌(プレーヤー4)
                                        // 66 - 135 ツモ牌

	int yamahai_index[PAI_COUNT_MAX];   // 牌山の牌種別

	// -----------------------------
	// プレーヤーAct手牌ヒストグラム情報
	// -----------------------------

	// 現在の手牌ヒストグラム情報
	int ply_act_tehai[PLAYER_MAX][PAI_MAX];                 // アクション手牌
	int ply_act_aka_count[PLAYER_MAX][AKA_TYPE_MAX_COUNT];  // アクション手牌の赤牌枚数

	// 自摸情報
	int  ply_act_tsumo[PLAYER_MAX];               // 自摸牌
	bool ply_act_tsumo_aka[PLAYER_MAX];           // 自摸の赤牌
	int  ply_act_tsumo_shanten[PLAYER_MAX];       // 自摸の向聴数(自摸牌を捨てた場合の向聴数)
	bool ply_act_tsumo_can_sute[PLAYER_MAX];      // 捨牌不可有無(リーチ時点のノーテン牌、鳴き捨牌時の喰い替え禁止牌)

	// 手牌からの捨牌情報
	int  ply_act_sute[PLAYER_MAX];                // 捨牌牌
	bool ply_act_sute_aka[PLAYER_MAX];            // 捨牌の赤牌

	// 向聴計算用鳴きカウント
	int naki_count_none_kakan[PLAYER_MAX];        // 鳴き面子数(カカンなし)

	// 向聴数
	int shanten_total[PLAYER_MAX];                // 総合向聴数：三種類のうちで最も少ない向聴数
	int shanten_normal[PLAYER_MAX];               // 通常向聴数
	int shanten_kokushi[PLAYER_MAX];              // 国士向聴数
	int shanten_chitoi[PLAYER_MAX];               // 七対向聴数

	// 待牌
	int ply_act_machi_count[PLAYER_MAX];                                  // 待牌合計枚数
	int ply_act_machi_hai[PLAYER_MAX][NORMAL_MACHI_MAX_COUNT];            // 待牌の牌番号
	int ply_act_machi_furiten_mode[PLAYER_MAX][NORMAL_MACHI_MAX_COUNT];   // 待牌のフリテン形式

	// 天和有無
	bool tenho_chiho_flg[PLAYER_MAX];             // 天和・地和有無
	bool renho_flg[PLAYER_MAX];                   // 人和有無

	// リーチ有無
	bool riichi_flg[PLAYER_MAX];                  // リーチ有無
	bool riichi_ippatsu_flg[PLAYER_MAX];          // リーチ一発有無
	bool double_riichi_flg[PLAYER_MAX];           // ダブルリーチ有無

	// フリテン有無
	bool   furiten_flg[PLAYER_MAX];               // フリテン有無
	LBCbSt furiten_mode[PLAYER_MAX];              // フリテンモード

	// -----------------------------
	// プレーヤーアクション手牌テーブル
	// -----------------------------

	// 手牌テーブル
	int  ply_act_tehaicount[PLAYER_MAX];                         // 手牌の合計枚数(自摸牌は含む)
	int  ply_act_tehaitbl[PLAYER_MAX][TEHAI_MAX];                // 牌テーブル
	bool ply_act_tehai_tbl_aka[PLAYER_MAX][TEHAI_MAX];           // 牌テーブル(赤牌)
	int  ply_act_tehai_shanten_tbl[PLAYER_MAX][TEHAI_MAX];       // 牌テーブル(向聴数)
	bool ply_act_tehai_can_sute_tbl[PLAYER_MAX][TEHAI_MAX];      // 牌テーブル(リーチ時点のノーテン牌、鳴き捨牌時の喰い替え禁止牌)

	// 牌テーブルの捨牌位置番号
	int ply_tbl_com_sutehai_statnum[PLAYER_MAX];                 // 牌テーブルの捨牌位置番号(COM用)
	int ply_tbl_hum_sutehai_statnum;                             // 牌テーブルの捨牌位置番号(HUM用)

	// -----------------------------
	// アクション河情報
	// -----------------------------

	int  ply_act_kawa_count[PLAYER_MAX];                 // 河牌の合計枚数
	int  ply_act_kawa[PLAYER_MAX][KAWA_HAI_MAX];         // 河牌
	bool ply_act_kawa_aka[PLAYER_MAX][KAWA_HAI_MAX];     // 河牌の赤牌
	int  ply_act_kawa_mode[PLAYER_MAX][KAWA_HAI_MAX];    // 河牌の状態(0:通常、1:リーチ、2:鳴き状態)

	// -----------------------------
	// プレーヤーごとの鳴き確認処理
	// -----------------------------

	int naki_ply_num;                     // 鳴きアクションを行うプレーヤ番号
	LBPAct ply_act_naki[PLAYER_MAX];      // 鳴き確認時の各プレーヤーアクション
	int ply_naki_hai[PLAYER_MAX];         // 鳴き牌
	int ply_naki_idx[PLAYER_MAX];         // チー時の頭牌
	int ply_naki_aka_count[PLAYER_MAX];   // 赤カウント数

	// -----------------------------
	// 向聴数算出
	// -----------------------------

	int kokushi_hai_num[13];         // 国士無双の構成牌の番号

	int atama_count;                 // 頭牌の枚数(値は0又は1)
	int atama_hai;                   // 頭牌の牌番号

	int mentu_count;                 // 面子数
	LBMen mentu_stat[MEN_MAX];       // 面子状態
	int mentu_hai[MEN_MAX];          // 面子牌

	int taatu_count;                 // 塔子数
	LBMen taatsu_stat[MEN_MAX];      // 塔子状態
	int taatsu_hai[MEN_MAX];         // 塔子牌

	// -----------------------------
	// 向聴数算出用(計算処理用)
	// -----------------------------

	int tmp_shanten;                    // (計算処理用)通常シャンテン

	int tmp_atama_count;                // 頭牌の枚数(値は0又は1)
	int tmp_atama_hai;                  // 頭牌の牌番号

	int tmp_mentu_count;                // 面子数
	LBMen tmp_mentu_stat[MEN_MAX];      // 面子状態
	int tmp_mentu_hai[MEN_MAX];         // 面子牌

	int tmp_taatu_count;                // 塔子数
	LBMen tmp_taatsu_stat[MEN_MAX];     // 塔子状態
	int tmp_taatsu_hai[MEN_MAX];        // 塔子牌

	// -----------------------------
	// コンストラクタ
	// -----------------------------

	// コンストラクタ
    MJSTkinfo(){};

	// デストラクタ
    ~MJSTkinfo(){};

	// -----------------------------
	// 関数
	// -----------------------------

	// クラス初期化・後処理
	void TkinfoInit();
	void TkinfoPost();

	// 卓の初期化・後処理
	void TakuInit();
	void TakuPost();

	// 局の初期化・後処理
	void KyokuInit();
	void KyokuPost();

	// アクション情報設定
	void SetActInfo(int kyoku_index, LBTkSt tmp_act_stat, int tmp_act_ply, int tmp_react_ply, int tmp_act_hai, bool tmp_act_aka);

	// 鳴き情報設定
	void SetNakiInfo(int kyoku_index, LBMen tmp_naki_stat, int tmp_naki_ply, int tmp_naki_actid, int tmp_naki_hai, int tmp_naki_idx, int tmp_naki_aka_count);

	// 和了情報設定
	void SetAgariInfo(int kyoku_index, LBAgariTehai tmp_agari_stat, int tmp_agari_ply, int tmp_furikomi_ply, bool tmp_tsumoagari_flg, int tmp_agari_hai, bool tmp_agari_aka);

	// 天和・リーチ確認
	void Check_Tenho_Riichi(int kyoku_index, int tmp_agari_ply);

	// アクション情報取得メイン処理
	void Check_Ply_ActTehai(int kyoku_index, int actid);                       // 全プレーヤーの手牌確認

	// アクション情報取得
	void Check_Actid_Haipai(int kyoku_index, int actid);                       // 配牌時の処理
	void Check_Actid_Hai_count(int kyoku_index, int actid);                    // 特定プレーヤーの手牌状態
	void Check_Actid_LastHai(int kyoku_index, int actid);                      // 最後牌の処理

	// 手牌テーブル設定
	void settehaitbl(int kyoku_index, int actid, int pnum);                    // 手牌テーブル定義
	void settehaitbl_sute_stat(int kyoku_index, int actid, int pnum);          // 捨牌のテーブル位置設定
	void settehaitbl_shanten(int kyoku_index, int actid, int pnum);            // 自摸有り(捨牌前)状態の捨牌ごとの向聴数確認
	void setmachi(int kyoku_index, int actid, int pnum);                       // 待ち牌設定

	// 向聴数確認 - メイン処理
	void ChkShanten(int pnum);                  // 向聴数確認(メイン)

	// 向聴数確認 - 通常形式
	void NormalShanten(int pnum);               // 向聴数確認(通常)
	void mentu_cut(int pnum,int hai);           // 面子削除処理(サブ関数)
	void taatu_cut(int pnum,int hai);           // 塔子削除処理(サブ関数)

	// 向聴数確認 - 特殊形式
	void KokushiShanten(int pnum);              // 向聴数確認(国士無双)

};

#endif /* TKINFO_H_INCLUDED */

/* ---------------------------------------------------------------------------------------------- */
// ソース終了
/* ---------------------------------------------------------------------------------------------- */
