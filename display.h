/* ---------------------------------------------------------------------------------------------- 
 * 
 * プログラム概要 ： さくら麻雀(Ver0.1.2：開発版)
 * バージョン     ： 0.1.2.1.229(MJAIログ表示：ダブロン表示)
 * プログラム名   ： mjs.exe
 * ファイル名     ： display.h
 * クラス名       ： MJSDisplay
 * 処理概要       ： 画面表示処理クラス
 * Ver0.0.8作成日 ： 2012/05/12 11:06:22
 * Ver0.1.0作成日 ： 2022/05/03 18:50:06
 * Ver0.1.1作成日 ： 2022/06/30 21:19:01
 * Ver0.1.2作成日 ： 2022/08/31 22:19:54
 * 最終更新日     ： 2024/11/17 16:53:23
 * 
 * Copyright (c) 2010-2024 TechMileStoraJP, All rights reserved.
 * 
 * ---------------------------------------------------------------------------------------------- */

#include <windows.h>
#include "stdafx.h"
#include "DxLib.h"

#include "dispparts.h"
#include "gui.h"
#include "player.h"
#include "tkinfo.h"

#ifndef MJSDISPLAY_H_INCLUDED
#define MJSDISPLAY_H_INCLUDED

/* ---------------------------------------------------------------------------------------------- */
// クラス定義
/* ---------------------------------------------------------------------------------------------- */
class MJSDisplay
{

	// ------------------------------------------------------------------- 
	// 公開関数定義
	// ------------------------------------------------------------------- 
	public:

	// ------------------------------------------------------------------- 
	// クラス定義
	// ------------------------------------------------------------------- 

	MJSDisplayParts  *dparts;           // パーツ表示クラス

	// ------------------------------------------------------------------- 
	// 文字列
	// ------------------------------------------------------------------- 

	// ディスプレイ表示用・メッセージ用
	char tmp_disp_msg[256];

	// ------------------------------------------------------------------- 
	// 画面の設定変数
	// ------------------------------------------------------------------- 

	// デバグ情報表示モード
	bool disp_debug_info_mode;          // バグ情報の表示モード

	// 牌裏面の色
	int hai_color;

	// ------------------------------------------------------------------- 
	// コンストラクタ
	// ------------------------------------------------------------------- 

	//コンストラクタ
    MJSDisplay(){};

	//デストラクタ
    ~MJSDisplay(){};

	// ------------------------------------------------------------------- 
	// 関数定義(初期処理・後処理)
	// ------------------------------------------------------------------- 

	// 初期処理
	void DisplayInit();

	// 後処理
	void DisplayPost();

	// ------------------------------------------------------------------- 
	// メイン画面表示(テスト用卓表示)
	// ------------------------------------------------------------------- 
	void DisplaySampleTitle(MJSTkinfo *tk, MJSGui *gui, float mFps, int total_frame_count, int ver1, int ver2, int ver3, int ver4, int ver5);

	// ------------------------------------------------------------------- 
	// メイン画面表示(オープニング)
	// ------------------------------------------------------------------- 
	void DisplayOpening(MJSGui *gui, float mFps, int total_frame_count, int ver1, int ver2, int ver3, int ver4, int ver5);  // ゲームモード卓表示(メイン処理)

	// ------------------------------------------------------------------- 
	// メイン画面表示(卓ゲームモード表示)
	// ------------------------------------------------------------------- 

	// ゲームモード卓表示(メイン処理)
	void DisplayTaku(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui, float mFps, int total_frame_count, int ver1, int ver2, int ver3, int ver4, int ver5);
	void DisplayBagime(MJSTkinfo *tk, MJSGui *gui);                                                 // 場決め画面
	void DispNormalTakuStat(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui);                            // 通常の卓表示

	// 局終了処理
	void DispKyokuEnd(MJSTkinfo *tk, MJSGui *gui, int kyoku_index, int tmp_actid);                  // 局結果表示：メイン処理
	// 局終了処理/サブ処理
	void DispKyokuEndTehai(MJSTkinfo *tk, int kyoku_index, int disp_agari_num);                     // 手牌表示
	void DispKyokuEndHanInfo(MJSTkinfo *tk, int kyoku_index, int disp_agari_num);                   // 翻情報表示
	void DispKyokuEndYakuInfo(MJSTkinfo *tk, int kyoku_index, int tmp_actid, int disp_agari_num);   // 役有時の表示
	void DispKyokuEndMentsuInfoNormal(MJSTkinfo *tk, int kyoku_index, int disp_agari_num);          // 通常手役・面子情報
	void DispKyokuEndAgariInfoNormal(MJSTkinfo *tk, int kyoku_index, int disp_agari_num);           // 通常和了・詳細情報
	void DispKyokuEndMentsuInfoChitoi(MJSTkinfo *tk, int kyoku_index, int disp_agari_num);          // 七対手役・面子情報
	void DispKyokuEndAgariInfoChitoi(MJSTkinfo *tk, int kyoku_index, int disp_agari_num);           // 七対手役・詳細情報
	void DisplayRyukyokuMachiHai(MJSTkinfo *tk, int kyoku_index);                                   // 流局時表示

	// 卓ゲーム終了処理
	void DisplayGameResult(MJSTkinfo *tk, MJSGui *gui);                                             // 卓終了

	// パーツ情報
	void DispTehaiLineMessage(MJSTkinfo *tk, MJSGui *gui, int x, int y);                            // 手牌ラインメッセージ

	// ------------------------------------------------------------------- 
	// メイン画面表示(ビューアーモード表示)
	// ------------------------------------------------------------------- 

	// ビューアーモード卓表示(メイン処理)
	void DisplayViewerTaku(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui, float mFps, int total_frame_count, int ver1, int ver2, int ver3, int ver4, int ver5);
	void DisplayViewerStatparts(MJSTkinfo *tk, MJSGui *gui);                                        // 「卓ステータス」ごとの手牌、パーツ表示
	void DispViewerKyokuEnd_mjscore(MJSTkinfo *tk, int kyoku_index, int tmp_actid);                 // 局結果(和了情報)：東風荘ログ表示
	void DispViewerKyokuEnd_mjailog(MJSTkinfo *tk, int kyoku_index, int tmp_actid);                 // 局結果(和了情報)：MJAIログ表示
	void DispViewerGameResult(MJSTkinfo *tk);                                                       // 卓終了処理

	// ------------------------------------------------------------------- 
	// メイン画面表示(MJAIクライアントモード表示)
	// ------------------------------------------------------------------- 

	// クライアントモード卓表示(メイン処理)
	void DisplayMjaiClientTaku(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui, float mFps, int total_frame_count, int ver1, int ver2, int ver3, int ver4, int ver5);
	void DisplayMjaiConnect(MJSTkinfo *tk, MJSGui *gui);                                  // 接続確認画面
	void DisplayClientModeBagime(MJSTkinfo *tk, MJSGui *gui, int kyoku_index);            // 場決め表示(クライアントモード)
	void DispyMjaiClientNormalTakuStat(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui);       // 通常の卓表示(クライアントモード)
	void DisplayMjaiClientKyokuEnd(MJSTkinfo *tk, MJSGui *gui, int kyoku_index);          // 局結果表示(クライアントモード)
	void DisplayMjaiClientGameResult(MJSTkinfo *tk, MJSGui *gui);                         // 卓終了(クライアントモード)
	void DisplayMjaiClientErrMes(MJSTkinfo *tk, MJSGui *gui);                             // エラー表示(クライアントモード)

	// サブ処理(クライアントモード：卓情報)
	void DisplayClientModeInfo(MJSTkinfo *tk, MJSGui *gui, int x, int y);                 // クライアントモードの設定情報

	// ------------------------------------------------------------------- 
	// 関数定義(アクション手牌表示・ライナー表示)
	// ------------------------------------------------------------------- 

	// アクション手牌表示・ライナーHUM表示、COM表示
	void DispActTehaiHum(MJSTkinfo *tk, MJSGui *gui, int kyoku_index, int actid, int pnum, int msx, int msy);           // アクション手牌HUM向け(スクエア兼用)
	void DispActTehaiCom(MJSTkinfo *tk, MJSGui *gui, int kyoku_index, int actid, int pnum, int msx, int msy);           // アクション手牌COM向け
	void DispActSarashi(MJSTkinfo *tk, int kyoku_index, int pnum, int actid);                                           // アクション番号を考慮したさらし牌の表示(ライナー) 
	void DispActKawa(MJSTkinfo *tk, int kyoku_index, int actid, int pnum);                                              // アクション手牌の河牌(ライナー) 
	void DispTakuActplt(MJSTkinfo *tk, MJSGui *gui, int kyoku_index, int actid, int pnum);                              // アクションプレート表示

	// ------------------------------------------------------------------- 
	// 関数定義(アクション手牌表示・スクエア表示)
	// ------------------------------------------------------------------- 

	// アクション手牌表示・スクエア表示
	void DispActTehaiCom_square(MJSTkinfo *tk, MJSGui *gui, int kyoku_index, int actid, int pnum, int msx, int msy);    // アクション手牌COM向け(スクエア)
	void DispActSarashi_square(MJSTkinfo *tk, MJSGui *gui, int kyoku_index, int actid, int pnum);                       // アクション手牌を考慮したさらし牌(スクエア) 
	void DispActKawa_square(MJSTkinfo *tk, MJSGui *gui, int kyoku_index, int actid, int pnum);                          // アクション手牌の河牌(スクエア) 

	// アクション手牌表示・テスト表示
	void DispActTehai_test_square(MJSGui *gui);

	// アクション手牌表示・文字列表示(デバグ用)
	void DispActTehai_info_all();

	// ------------------------------------------------------------------- 
	// 手牌情報詳細(tkinfoクラス情報表示)
	// ------------------------------------------------------------------- 

	// メイン関数
	void DispKyokuInfo(MJSTkinfo *tk, int kyoku_index);                                                                 // 局情報
	void DispPlyInfo(MJSTkinfo *tk, int kyoku_index, int pnum);                                                         // プレーヤー情報

	// tkinfoクラス情報表示/メイン関数
	void DispActNumInfo(MJSTkinfo *tk, int x, int y, int kyoku_index, int actid);                                       // 番号ごとのアクション情報
	void DispTakuStat(MJSTkinfo *tk, int x, int y);                                                                     // 卓情報
	void DispTkInfoStat(MJSTkinfo *tk, int x, int y);                                                                   // 卓クラス情報

	// tkinfoクラス情報表示/サブ関数
	void DisplayTehaiDetail(MJSTkinfo *tk, int pnum);                                                                   // 手牌情報の詳細
	void DisplayTkinfoDetail(MJSTkinfo *tk);                                                                            // tkinfo情報詳細
	void DisplayTkinfoDetail_sub_tehai(MJSTkinfo *tk, int x, int y, int pnum);                                          // tkinfo情報詳細(サブ処理：手牌情報)
	void DisplayTkinfoDetail_sub_hist(MJSTkinfo *tk, int x, int y, int pnum);                                           // tkinfo情報詳細(サブ処理：手牌ヒストグラム情報)
	void DisplayTkinfoDetail_sub_sute(MJSTkinfo *tk, int x, int y, int pnum, int line_num);                             // tkinfo情報詳細(サブ処理：捨牌情報)
	void DisplayTkinfoDetail_sub_naki(MJSTkinfo *tk, int kyoku_index, int actid, int pnum, int x, int y);               // tkinfo情報詳細(サブ処理：鳴牌情報)
	void DisplayTkinfoDetail_sub_shanten(MJSTkinfo *tk, int x, int y, int pnum);                                        // tkinfo情報詳細(サブ処理：赤牌、向聴、待牌情報)
	void DisplayTkinfoDetail_sub_ply_actnaki_info(MJSTkinfo *tk, int x, int y, int pnum);                               // tkinfo情報詳細(サブ処理：Act鳴牌情報)
	void DisplayTkinfoDetail_sub_tkstat(MJSTkinfo *tk, LBTkSt tk_stat, int x, int y);                                   // tkinfo情報詳細(サブ処理：tkinfoステータス)
	void DisplayTkinfoDetail_sub_plyactInfo(MJSTkinfo *tk, LBPAct tmp_act, int x, int y);                               // tkinfo情報詳細(サブ処理：ply_actステータス)
	void DisplayTkinfoDetail_sub_tehai_count(MJSTkinfo *tk, int x, int y, int pnum);                                    // tkinfo情報詳細(サブ処理：手牌枚数)

	// デバグ用
	void DispYamahai(MJSTkinfo *tk);                                                                                    // 牌山表示(デバグ用)

	// ------------------------------------------------------------------- 
	// 手牌情報詳細(GUIクラス情報表示)
	// ------------------------------------------------------------------- 

	void DispGuiInfo(MJSGui *gui, int x, int y);                                                                        // GUI情報
	void DisplayGuiClientMode(MJSGui *gui, int x, int y);                                                               // GUI情報・GUIクライアントモード
	void DisplayGuiTakuMode(MJSGui *gui, int x, int y);                                                                 // GUI情報・GUI卓ゲームモード
	void DisplayGuiTehaiMode(MJSGui *gui, int x, int y);                                                                // GUI情報・GUI手牌モード
	void DisplayGuiChiKoho(MJSGui *gui, int x, int y);                                                                  // GUI情報・プレーヤーのチー候補情報
	void DisplayGuiLogType(MJSGui *gui, int x, int y);                                                                  // GUI情報・牌譜ログ形式

	// ------------------------------------------------------------------- 
	// 手牌情報詳細(plyクラス情報表示)
	// ------------------------------------------------------------------- 

	// 手牌情報詳細(plyクラス情報表示)
	void DisplayPlyTehaiDetail(MJSTkinfo *tk, MJSPlayer *ply, int pnum);                                                // ply手牌の詳細情報
	void DisplayClientPlyTehaiDetail(MJSTkinfo *tk, MJSPlayer *ply);                                                    // クライアントモードply手牌の詳細情報

	// サブ処理
	void DisplayPlyTehaiDetailTsumoAri(MJSTkinfo *tk, MJSPlayer *ply, int pnum, int x, int y);                          // ply手牌の詳細情報(自摸有り時)
	void DisplayPlyTehaiDetailTsumoNashi(MJSTkinfo *tk, MJSPlayer *ply, int pnum, int x, int y);                        // ply手牌の詳細情報(自摸無し時)
	void DisplaySutekoho(MJSTkinfo *tk, MJSPlayer *ply, int pnum, int x, int y, int sutenum);                           // 捨牌候補
	void DisplayOpenhai(MJSTkinfo *tk, MJSPlayer *ply, int pnum, int x, int y);                                         // 表示牌枚数

	// ------------------------------------------------------------------- 
	// 関数定義(設定画面)
	// ------------------------------------------------------------------- 

	// 設定画面
	void DisplaySetting(MJSGui *gui, float mFps, int total_frame_count, int ver1, int ver2, int ver3, int ver4, int ver5);  // 設定画面(メイン処理)
	void DisplaySettingInfo(MJSGui *gui);                             // 設定画面情報
	void DisplayFileNameDiag(MJSGui *gui, LBGuiLogType log_type);     // ファイル選択ダイアグ
	void DisplayParamSet(MJSGui *gui);                                // パラメータ設定
	void DisplayTotalScore();                                         // 成績表示
	void DisplayRule();                                               // ルール表示

};

#endif/* MJSDISPLAY_H_INCLUDED */

/* ---------------------------------------------------------------------------------------------- */
// ソース終了
/* ---------------------------------------------------------------------------------------------- */
