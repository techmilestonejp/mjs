/* ---------------------------------------------------------------------------------------------- 
 * 
 * プログラム概要 ： さくら麻雀(Ver0.1.2：開発版)
 * バージョン     ： 0.1.2.0.215(MJAIログ表示：ボタン表示修正)
 * プログラム名   ： mjs.exe
 * ファイル名     ： gui.cpp
 * クラス名       ： MJSGui
 * 処理概要       ： GUI操作クラス
 * Ver0.1.0作成日 ： 2022/05/03 18:50:06
 * 最終更新日     ： 2024/10/26 15:15:34
 * 
 * Copyright (c) 2010-2024 Techmilestone, All rights reserved.
 *  
 * ---------------------------------------------------------------------------------------------- */

#include "gui.h"

/* ---------------------------------------------------------------------------------------------- */
// 初期化処理
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::GuiInit(){

	// -----------------------------
	// 変数定義
	// -----------------------------
	char cdir[192];

	// -----------------------------
	// 卓ゲームモード初期化
	// -----------------------------

	// ログ出力の無効化
	tklog_output_flg     = false;
	clientlog_output_flg = false;

	// カレントディレクトリ名取得
	GetCurrentDirectory(192,cdir);

	// 卓ログ名定義
	wsprintf(tklog_name, "%s\\mjslog.log", cdir);

	// クライアントログ名定義
	wsprintf(clientlog_name, "%s\\mjai_client.log", cdir);

	// MJAI牌譜ログ名定義
	// wsprintf(log_name_mjai, "C:\\Users\\era27\\source\\repos\\mjs0120_126\\Debug\\mjailog.json");
	// wsprintf(log_name_mjai, "mjailog.json");
	wsprintf(log_name_mjai, "%s\\mjailog.json", cdir);

	// 東風荘牌譜ログ名定義
	// wsprintf(log_name_mjsocre, "C:\\Users\\era27\\source\\repos\\mjs0120_126\\Debug\\mjscore.txt");
	// wsprintf(log_name_mjsocre, "mjscore.txt");
	wsprintf(log_name_mjsocre, "%s\\mjscore.txt", cdir);

	// GUIメインステータス
	gui_main_stat = GUI_NO_MAIN_STAT;
	gui_next_stat = GUI_NO_MAIN_STAT;

	// 卓ステータス変数の初期化
	guiTakuInit();

	// -----------------------------
	// プレート文字定義
	// -----------------------------

	wsprintf(plt_name[PLT_RIICHI], "リーチ");
	wsprintf(plt_name[PLT_PON]   , "ポ　ン");
	wsprintf(plt_name[PLT_KAN]   , "カ　ン");
	wsprintf(plt_name[PLT_CHI]   , "チ　ー");
	wsprintf(plt_name[PLT_AGARI] , "和　了");
	wsprintf(plt_name[PLT_NEXT]  , "次　へ");

	// -----------------------------
	// 手牌モード設定
	// -----------------------------
	disp_tehai_mode         = DISP_TEHAI_MODE_DEF;          // 卓表示モード
	disp_square_naki_mentsu = DISP_SQUARE_NAKI_MENTSU_DEF;  // 鳴き牌表示モード

	// -----------------------------
	// 手牌位置の設定
	// -----------------------------

	// ライナー表示
	if(disp_tehai_mode == 0){

		// 手牌位置定義
		tehai_x = SPACE_XSIZE;
		tehai_y = PLY_YSTART + PLY_YSIZE*HUM_PLY_SEKI_NUM + 40;

	// スクエア表示
	}else if( disp_tehai_mode == 1 || disp_tehai_mode == 2 ){

		// UPプレーヤー手牌位置
		sutehai_up_x         = (TAKU_PLT_X_SIZE + TAKU_PLT_X_STAT)/2 - HAI_XSIZE*3;
		sutehai_up_y         = (TAKU_PLT_Y_SIZE + TAKU_PLT_Y_STAT)/2 - HAI_XSIZE*3 - SUTEHAI_CENTERPLT_RANGE - HAI_YSIZE*4;
		tehai_up_x           = (TAKU_PLT_X_SIZE + TAKU_PLT_X_STAT)/2 - HAI_XSIZE*6; // 自摸分だけ右に移動する
		tehai_up_y           = (TAKU_PLT_Y_SIZE + TAKU_PLT_Y_STAT)/2 - HAI_XSIZE*3 - SUTEHAI_CENTERPLT_RANGE - HAI_YSIZE*4 - SUTEHAI_TEHAI_RANGE;
		nakihai_line_up_x    = tehai_up_x - NAKI_RANGE + HAI_XSIZE*TEHAI_MAX - HAI_XSIZE;
		nakihai_line_up_y    = tehai_up_y;
		nakihai_up_x         = 0;
		nakihai_up_y         = 0;

		// DOWNプレーヤー手牌位置
		sutehai_down_x       = (TAKU_PLT_X_SIZE + TAKU_PLT_X_STAT)/2 - HAI_XSIZE*3;
		sutehai_down_y       = (TAKU_PLT_Y_SIZE + TAKU_PLT_Y_STAT)/2 + HAI_XSIZE*3 + SUTEHAI_CENTERPLT_RANGE;
		tehai_x              = (TAKU_PLT_X_SIZE + TAKU_PLT_X_STAT)/2 - HAI_XSIZE*7;
		tehai_y              = (TAKU_PLT_Y_SIZE + TAKU_PLT_Y_STAT)/2 + HAI_XSIZE*3 + SUTEHAI_CENTERPLT_RANGE + HAI_YSIZE*4 + SUTEHAI_TEHAI_RANGE;
		nakihai_line_down_x  = tehai_x + NAKI_RANGE;
		nakihai_line_down_y  = tehai_y;
		nakihai_down_x       = 0;
		nakihai_down_y       = 0;

		// LEFTプレーヤー手牌位置
		sutehai_left_x       = (TAKU_PLT_X_SIZE + TAKU_PLT_X_STAT)/2 - HAI_XSIZE*3 - SUTEHAI_CENTERPLT_RANGE - HAI_YSIZE;
		sutehai_left_y       = (TAKU_PLT_Y_SIZE + TAKU_PLT_Y_STAT)/2 - HAI_XSIZE*3;
		tehai_left_x         = (TAKU_PLT_X_SIZE + TAKU_PLT_X_STAT)/2 - HAI_XSIZE*3 - SUTEHAI_CENTERPLT_RANGE - HAI_YSIZE*4 - SUTEHAI_TEHAI_RANGE - HAI_YSIZE;
		tehai_left_y         = (TAKU_PLT_Y_SIZE + TAKU_PLT_Y_STAT)/2 - HAI_XSIZE*8;
		nakihai_line_left_x  = tehai_left_x;
		nakihai_line_left_y  = tehai_left_x + NAKI_RANGE + HAI_XSIZE*4;
		nakihai_left_x       = 0;
		nakihai_left_y       = 0;

		// RIGHTプレーヤー手牌位置
		sutehai_right_x      = (TAKU_PLT_X_SIZE + TAKU_PLT_X_STAT)/2 + HAI_XSIZE*3 + SUTEHAI_CENTERPLT_RANGE;
		sutehai_right_y      = (TAKU_PLT_Y_SIZE + TAKU_PLT_Y_STAT)/2 - HAI_XSIZE*3;
		tehai_right_x        = (TAKU_PLT_X_SIZE + TAKU_PLT_X_STAT)/2 + HAI_XSIZE*3 + SUTEHAI_CENTERPLT_RANGE + HAI_YSIZE*4 + SUTEHAI_TEHAI_RANGE;
		tehai_right_y        = (TAKU_PLT_Y_SIZE + TAKU_PLT_Y_STAT)/2 - HAI_XSIZE*7;
		nakihai_line_right_x = tehai_right_x;
		nakihai_line_right_y = tehai_right_y - NAKI_RANGE + HAI_XSIZE*TEHAI_MAX;
		nakihai_right_x      = 0;
		nakihai_right_y      = 0;

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 終了処理
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::GuiPost(){

	// 卓ステータス変数の初期化
	guiTakuInit();

}

/* ---------------------------------------------------------------------------------------------- */
// マウス情報取得
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::MouseStat(){

    GetMousePoint( &msx, &msy );         // マウスの位置取得

    int MouseInput = GetMouseInput();    // マウスの押した状態取得

    for(int i = 0; i < 8; i++){          // マウスのキーは最大8個まで確認出来る

		Button[i] = 0;

        if( (MouseInput & 1<<i ) != 0 ){

			Button[i]++;   //押されていたらカウントアップ

		}else{

			Button[i] = 0; //押されてなかったら0
		}
	}

	wheelrotvol = GetMouseWheelRotVol() ;    //ホイール回転量取得

}

/* ---------------------------------------------------------------------------------------------- */
// オープニング状態確認
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::chk_opening(MJSTkinfo *tk){

	// -----------------------------
	// マウス情報取得
	// -----------------------------
	MouseStat();

	// -----------------------------
	// マウスが押されていないなら、「マウス開放状態(mouse_push_flg=0)」とする
	// -----------------------------
	if( Button[0] == 0 && Button[1] == 0 ){
		// マウスチェックフラグ無効化
		mouse_push_flg=0;
	}

	// -----------------------------
	// マウスが押されたなら
	// -----------------------------
	if( Button[0] > 0 && mouse_push_flg == 0){

		// ----------------------------------------
		// 00:設定
		// ----------------------------------------
		if( msx>OPENING_BUT01_X_START && msx<OPENING_BUT01_X_START+BUT_ICON_XSIZE && 
		    msy>OPENING_BUT01_Y_START && msy<OPENING_BUT01_Y_START+BUT_ICON_YSIZE ){

			// ----------------------------------------
			// ゲームモードの変更
			// ----------------------------------------
			gui_main_stat = GUI_OPENING_POST;               // オープニング後処理
			gui_next_stat = GUI_SETTING_INIT;               // ビューワーモード

		// ----------------------------------------
		// 01:ビューワーモード・MJAIログ
		// ----------------------------------------
		}else if( msx>OPENING_BUT01_X_START && msx<OPENING_BUT01_X_START+BUT_ICON_XSIZE && 
		          msy>OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*1 && 
		          msy<OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*1+BUT_ICON_YSIZE ){

			// ----------------------------------------
			// ゲームモードの変更
			// ----------------------------------------
			gui_main_stat = GUI_OPENING_POST;               // オープニング後処理
			gui_next_stat = GUI_VIEWING_INIT;               // ビューワーモード

			// ----------------------------------------
			// 各クラスの変数定義
			// ----------------------------------------
			tk->ply_hum_mode = 0;                                // 卓ゲームHUMモード：0(COM対戦)
			tk->tkgame_type = TKGAME_VIEWER;                     // ビューアモード
			gui_logtype = GUI_LOG_MJAILOG;                       // MJAIログ

		// ----------------------------------------
		// 02:ビューワーモード・東風荘ログ
		// ----------------------------------------
		}else if( msx>OPENING_BUT01_X_START && msx<OPENING_BUT01_X_START+BUT_ICON_XSIZE && 
		    msy>OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*2 && 
		    msy<OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*2+BUT_ICON_YSIZE ){

			// ----------------------------------------
			// ゲームモードの変更
			// ----------------------------------------
			gui_main_stat = GUI_OPENING_POST;               // オープニング後処理
			gui_next_stat = GUI_VIEWING_INIT;               // ビューワーモード

			// ----------------------------------------
			// 各クラスの変数定義
			// ----------------------------------------
			tk->ply_hum_mode = 0;                           // 卓ゲームHUMモード：0(COM対戦)
			tk->tkgame_type = TKGAME_VIEWER;                // ビューアモード
			gui_logtype = GUI_LOG_MJSCORE;                  // 東風荘ログ

		// ----------------------------------------
		// 03:4COM対決・一局対戦・自摸テーブル読込
		// ----------------------------------------
		}else if( msx>OPENING_BUT01_X_START && msx<OPENING_BUT01_X_START+BUT_ICON_XSIZE && 
		    msy>OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*3 && 
		    msy<OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*3+BUT_ICON_YSIZE ){

			// ----------------------------------------
			// メインステータス変更
			// ----------------------------------------
			gui_main_stat = GUI_OPENING_POST;               // オープニング後処理
			gui_next_stat = GUI_PLAYING_INIT;               // 卓プレイモード

			// ----------------------------------------
			// 各クラスの変数定義
			// ----------------------------------------
			tk->ply_hum_mode = 0;                 // 卓ゲームHUMモード：0(COM対戦)
			tk->tkgame_type = TKGAME_1KYOKU;      // 卓ゲーム種別：一局戦
			tk->yama_setting_mode = 0;            // 牌山状態：牌テーブル読み込み

		// ----------------------------------------
		// 04:4COM対決・シード値ランダム
		// ----------------------------------------
		}else if( msx>OPENING_BUT01_X_START && msx<OPENING_BUT01_X_START+BUT_ICON_XSIZE && 
		    msy>OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*4 && 
		    msy<OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*4+BUT_ICON_YSIZE ){

			// ----------------------------------------
			// メインステータス変更
			// ----------------------------------------
			gui_main_stat = GUI_OPENING_POST;               // オープニング後処理
			gui_next_stat = GUI_PLAYING_INIT;               // 卓プレイモード

			// ----------------------------------------
			// 各クラスの変数定義
			// ----------------------------------------
			tk->ply_hum_mode = 0;                           // 卓ゲームHUMモード：0(COM対戦)
			tk->tkgame_type = TKGAME_TONPU;                 // 卓ゲーム種別：東風戦
			tk->yama_setting_mode = 1;                      // 牌山状態：シード値指定

		// ----------------------------------------
		// 05:HUM対決・一局対戦・自摸テーブル読込
		// ----------------------------------------
		}else if( msx>OPENING_BUT01_X_START && msx<OPENING_BUT01_X_START+BUT_ICON_XSIZE && 
		          msy>OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*5 && 
		          msy<OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*5+BUT_ICON_YSIZE ){

			// ----------------------------------------
			// メインステータス変更
			// ----------------------------------------
			gui_main_stat = GUI_OPENING_POST;          // オープニング後処理
			gui_next_stat = GUI_PLAYING_INIT;          // 卓プレイモード

			// ----------------------------------------
			// 各クラスの変数定義
			// ----------------------------------------
			tk->ply_hum_mode = 1;                      // 卓ゲームHUMモード：1(HUM対戦)
			tk->tkgame_type = TKGAME_1KYOKU;           // 卓ゲーム種別：一局戦
			tk->yama_setting_mode = 0;                 // 牌山状態：牌テーブル読み込み

		// ----------------------------------------
		// 06:HUM対決・シード値固定
		// ----------------------------------------
		}else if( msx>OPENING_BUT01_X_START && msx<OPENING_BUT01_X_START+BUT_ICON_XSIZE && 
		          msy>OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*6 && 
		          msy<OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*6+BUT_ICON_YSIZE ){

			// ----------------------------------------
			// メインステータス変更
			// ----------------------------------------
			gui_main_stat = GUI_OPENING_POST;          // オープニング後処理
			gui_next_stat = GUI_PLAYING_INIT;          // 卓プレイモード

			// ----------------------------------------
			// 各クラスの変数定義
			// ----------------------------------------
			tk->ply_hum_mode = 1;                           // 卓ゲームHUMモード：1(HUM対戦)
			tk->tkgame_type = TKGAME_TONPU;                 // 卓ゲーム種別：東風戦
			tk->yama_setting_mode = 2;                      // 牌山状態：シード値固定

		// ----------------------------------------
		// 07:HUM対決・シード値ランダム
		// ----------------------------------------
		}else if( msx>OPENING_BUT01_X_START && msx<OPENING_BUT01_X_START+BUT_ICON_XSIZE && 
		          msy>OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*7 && 
		          msy<OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*7+BUT_ICON_YSIZE ){

			// ----------------------------------------
			// メインステータス変更
			// ----------------------------------------
			gui_main_stat = GUI_OPENING_POST;          // オープニング後処理
			gui_next_stat = GUI_PLAYING_INIT;          // 卓プレイモード

			// ----------------------------------------
			// 各クラスの変数定義
			// ----------------------------------------
			tk->ply_hum_mode = 1;                           // 卓ゲームHUMモード：1(HUM対戦)
			tk->tkgame_type = TKGAME_TONPU;                 // 卓ゲーム種別：東風戦
			tk->yama_setting_mode = 1;                      // 牌山状態：シード値指定

		// ----------------------------------------
		// 08:MJAIクライアントモード(GUIモード)
		// ----------------------------------------
		}else if( msx>OPENING_BUT01_X_START && msx<OPENING_BUT01_X_START+BUT_ICON_XSIZE && 
		          msy>OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*8 && 
		          msy<OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*8+BUT_ICON_YSIZE ){

			// ----------------------------------------
			// メインステータス変更
			// ----------------------------------------
			gui_main_stat = GUI_OPENING_POST;               // オープニング後処理
			gui_next_stat = GUI_CLIENT_INIT;                // クライアントモード

			// ----------------------------------------
			// 各クラスの変数定義
			// ----------------------------------------
			tk->ply_hum_mode = 1;                 // 卓ゲームHUMモード：1(HUM対戦)

		// ----------------------------------------
		// 09:MJAIクライアントモード(PLYモード)
		// ----------------------------------------
		}else if( msx>OPENING_BUT01_X_START && msx<OPENING_BUT01_X_START+BUT_ICON_XSIZE && 
		          msy>OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*9 && 
		          msy<OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*9+BUT_ICON_YSIZE ){

			// ----------------------------------------
			// メインステータス変更
			// ----------------------------------------
			gui_main_stat = GUI_OPENING_POST;               // オープニング後処理
			gui_next_stat = GUI_CLIENT_INIT;                // クライアントモード

			// ----------------------------------------
			// 各クラスの変数定義
			// ----------------------------------------
			tk->ply_hum_mode = 0;                      // 卓ゲームHUMモード：0(COM対戦)

		// ----------------------------------------
		// 10:検証モード・ACTID_MAX
		// ----------------------------------------
		}else if( msx>OPENING_BUT01_X_START && msx<OPENING_BUT01_X_START+BUT_ICON_XSIZE && 
		    msy>OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*10 && 
			msy<OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*10+BUT_ICON_YSIZE ){

			// ----------------------------------------
			// ゲームモードの変更
			// ----------------------------------------
			gui_main_stat = GUI_OPENING_POST;               // オープニング後処理
			gui_next_stat = GUI_RUNNING_INIT;               // 検証モード

			// ----------------------------------------
			// 各クラスの変数定義
			// ----------------------------------------
			tk->ply_hum_mode = 0;                                // 卓ゲームHUMモード：0(COM対戦)
			tk->tkgame_type = TKGAME_MAXID_TEST;
			tk->yama_setting_mode = 1;                           // 牌山状態：シード値指定

		// ----------------------------------------
		// 11:検証モード・東風戦
		// ----------------------------------------
		}else if( msx>OPENING_BUT01_X_START && msx<OPENING_BUT01_X_START+BUT_ICON_XSIZE && 
		    msy>OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*11 && 
		    msy<OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*11+BUT_ICON_YSIZE ){

			// ----------------------------------------
			// ゲームモードの変更
			// ----------------------------------------
			gui_main_stat = GUI_OPENING_POST;               // オープニング後処理
			gui_next_stat = GUI_RUNNING_INIT;               // 検証モード

			// ----------------------------------------
			// 各クラスの変数定義
			// ----------------------------------------
			tk->ply_hum_mode = 0;                           // 卓ゲームHUMモード：0(COM対戦)
			tk->tkgame_type = TKGAME_TONPU;                 // 卓ゲーム種別：東風戦
			tk->yama_setting_mode = 1;                      // 牌山状態：シード値指定

		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 卓処理(ゲームモード)
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::guiTakuInit(){

	// -----------------------------
	// GUI初期化
	// -----------------------------

	// マウス情報初期化
	MouseStat();
	mouse_push_flg = 0;
	Button[0] = 0;
	Button[1] = 0;

	// フレームカウント
	frame_count = 0;

	// -----------------------------
	// プレート文字定義
	// -----------------------------

	// HUMアクションプレート
	plt_mode[PLT_RIICHI] = false;
	plt_mode[PLT_PON]    = false;
	plt_mode[PLT_KAN]    = false;
	plt_mode[PLT_CHI]    = false;
	plt_mode[PLT_AGARI]  = false;
	plt_mode[PLT_NEXT]   = true;
	// plt_mode[PLT_NEXT]   = false;

	// 鳴有/鳴無フラグ
	plt_nakiari_flg = true;

	// -----------------------------
	// ボタン押下フラグ初期化
	// -----------------------------
	act_push_flg = false;               // マウス押下フラグ
	but_push_flg = false;               // ボタン押下フラグ

	// -----------------------------
	// 卓ステータス初期化
	// -----------------------------

	// GUIモード設定
	gui_taku_mode = COMMON_PLAY_MODE;   // 通常モード
	gui_ply_tehai_mode = TEHAI_NORMAL;  // 手牌表示モード

	// 鳴き情報(暗槓・加槓)
	naki_ankan_hai_count = 0;           // 暗槓牌枚数
	naki_kakan_hai_count = 0;           // 加槓牌枚数

	// 鳴き情報
	chihai_count = 0;
	for(int tmp_i = 0; tmp_i < CHI_KOHO_COUNT_MAX; tmp_i++){
		chihai_mode[tmp_i]   = false;
		chi_idx_hai[tmp_i]   = 0; 
		chi_aka_count[tmp_i] = 0;
	}

	// 捨牌不可テーブル
	cannot_sutehai_count = 0;

	// ビューアーモード
	gui_kyoku_index = 0;
	gui_actid = 0;

	// クライアントモード
	cli_mode = GUI_MJAI_NOTCONNECT;

	// 下段手牌表示プレーヤID
	disp_down_tehai_pnum = HUM_PLY_SEKI_NUM;

}

/* ---------------------------------------------------------------------------------------------- */
// 卓終了(ゲームモード)
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::guiTakuPost(){

}

/* ---------------------------------------------------------------------------------------------- */
// 卓処理(ゲームモード)・通常画面
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::guiTaku(MJSTkinfo *tk){

	// 卓ステータスごとの処理変化
	if(tk->stat == KYOKUSTART){
		// GUI初期化
		guiTakuInit();
	}

	// 人なら、鳴きアクションの確認(プレート状態確認)
	if( tk->ply_hum_mode == 1){

		// クリック前処理
		guiTakuChkPreClick(tk);

	}

	// クリック後処理
	guiTakuActClick(tk);

}

/* ---------------------------------------------------------------------------------------------- */
// クリック前処理(メイン)
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::guiTakuChkPreClick(MJSTkinfo *tk){

		// -----------------------------
		// 自分の番であれば、自摸時アクション確認
		// -----------------------------
		if(tk->ply_turn == HUM_PLY_SEKI_NUM){

			// 自分番の最終アクションが自摸(リンシャン)なら、自摸後アクションの確認
			if( ( tk->stat == PLYACTSUTEWAIT) &&
			    ( tk->kyoku[tk->kyoku_index].act_stat[tk->kyoku[tk->kyoku_index].act_count] == PLYACTTSUMO  ||
			      tk->kyoku[tk->kyoku_index].act_stat[tk->kyoku[tk->kyoku_index].act_count] == PLYRINSHAN   )
			){

				// プレーヤーの自摸時アクション確認
				guiChkPlyTsumoStat(tk);

			}

		// -----------------------------
		// 相手の番であれば、鳴き時アクション確認
		// -----------------------------
		}else{

			// 前プレーヤーのアクション牌の確認
			if( ( tk->stat == PLYACTNAKIWAIT) &&
				( tk->kyoku[tk->kyoku_index].act_stat[tk->kyoku[tk->kyoku_index].act_count] == PLYACTSUTE      ||
			      tk->kyoku[tk->kyoku_index].act_stat[tk->kyoku[tk->kyoku_index].act_count] == PLYACTTSUMOGIRI ||
			      tk->kyoku[tk->kyoku_index].act_stat[tk->kyoku[tk->kyoku_index].act_count] == PLYACTNAKISUTE  ) 
			  ){

				// ロン確認
				guiChkPlyRonStat(tk);

				// 鳴き牌確認
				// 鳴き有無フラグがtrue(鳴き有)
				// → リーチモードの時には鳴き確認はスキップする
				// if( gui_ply_tehai_mode != TEHAI_RIICHI_YUKO && gui_ply_tehai_mode != TEHAI_CHI_SELECT){
				if( ( plt_nakiari_flg == true ) &&
				    ( gui_ply_tehai_mode != TEHAI_RIICHI_YUKO && gui_ply_tehai_mode != TEHAI_CHI_SELECT )
				){

					// HUMプレーヤの鳴牌確認(チー、ポン、明槓)
					guiChkPlyNakiStat(tk);

				}

			// 捨牌アクションでないなら、プレートは無効化
			}else{

				// 「相手鳴きプレート」の無効化
				plt_mode[PLT_CHI]   = false;
				plt_mode[PLT_PON]   = false;
				plt_mode[PLT_KAN]   = false;
				plt_mode[PLT_AGARI] = false;
				// plt_mode[PLT_NEXT]  = false;

			}

		}

}

/* ---------------------------------------------------------------------------------------------- */
// プレーヤーの自摸状態確認
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::guiChkPlyTsumoStat(MJSTkinfo *tk){

	// -----------------------------
	// 暗槓確認
	// -----------------------------

	// 初期化
	naki_ankan_hai_count = 0;

	// 暗槓確認
	for(int tmp_i = 0; tmp_i < PAI_MAX; tmp_i++){

		// tmp_iが自摸牌なら
		if ( ( tmp_i == tk->ply_act_tsumo[HUM_PLY_SEKI_NUM] && tk->ply_act_tehai[HUM_PLY_SEKI_NUM][tmp_i] == 3) ||
		     ( tk->ply_act_tehai[HUM_PLY_SEKI_NUM][tmp_i] == 4) ){

			// カン候補を加算
			naki_ankan_hai[naki_ankan_hai_count] = tmp_i;
			naki_ankan_hai_count++;
		}
	}

	// 残りを0埋め
	for(int tmp_i = naki_ankan_hai_count; tmp_i < 3; tmp_i++){
		// 残り0埋め
		naki_ankan_hai[tmp_i] = 0;
	}

	// -----------------------------
	// 加槓確認
	// -----------------------------

	// 初期化
	naki_kakan_hai_count=0;

	// 加槓確認
	for(int tmp_i = 0; tmp_i < tk->kyoku[tk->kyoku_index].naki_count[HUM_PLY_SEKI_NUM]; tmp_i++){

		// 加槓牌ならば
		if( tk->ply_act_tehai[HUM_PLY_SEKI_NUM][tk->kyoku[tk->kyoku_index].naki_hai[HUM_PLY_SEKI_NUM][tmp_i]] > 0 &&
		    tk->kyoku[tk->kyoku_index].naki_stat[HUM_PLY_SEKI_NUM][tmp_i] == MINKO ){

			// 加槓候補を加算
			naki_kakan_hai[naki_kakan_hai_count] = tk->kyoku[tk->kyoku_index].naki_hai[HUM_PLY_SEKI_NUM][tmp_i];
			naki_kakan_hai_count++;

		}
	}

	// 残りを0埋め
	for(int tmp_i = naki_kakan_hai_count; tmp_i < 3; tmp_i++){

		// 残り0埋め
		naki_kakan_hai[tmp_i] = 0;

	}

	// -----------------------------
	// 暗槓又は加槓なら、槓プレート有効化
	// -----------------------------
	if( ( naki_ankan_hai_count > 0 || naki_kakan_hai_count > 0 ) && 
	    gui_ply_tehai_mode == TEHAI_NORMAL){
		// プレート有効化
		plt_mode[PLT_KAN] = true;
	}else{
		// プレート無効化
		plt_mode[PLT_KAN] = false;
	}

	// -----------------------------
	// 面前でテンパイ以下のシャンテンなら、リーチプレート有効化
	// -----------------------------
	if(tk->shanten_total[HUM_PLY_SEKI_NUM] <= 0 && 
	   tk->kyoku[tk->kyoku_index].naki_count[HUM_PLY_SEKI_NUM] - tk->kyoku[tk->kyoku_index].ankan_count[HUM_PLY_SEKI_NUM] == 0 && // 暗槓以外の鳴きなし
	   gui_ply_tehai_mode == TEHAI_NORMAL){
		// プレート有効化
		plt_mode[PLT_RIICHI] = true;
	}else{
		// プレート無効化
		plt_mode[PLT_RIICHI] = false;
	}

	// -----------------------------
	// 自摸和了なら、和了プレート有効化
	// -----------------------------
	if( (tk->shanten_total[HUM_PLY_SEKI_NUM] == -1) && (gui_ply_tehai_mode == TEHAI_NORMAL || gui_ply_tehai_mode == TEHAI_RIICHI_YUKO) ){
		// プレート有効化
		plt_mode[PLT_AGARI] = true;
	}else{
		// プレート無効化
		plt_mode[PLT_AGARI] = false;
	}

}

/* ---------------------------------------------------------------------------------------------- */
// HUMプレーヤのロン確認
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::guiChkPlyRonStat(MJSTkinfo *tk){

	// 事前定義
	int tmp_sute_hai;
	int tmp_sute_ply;

	// -----------------------------
	// 他プレーヤの捨牌定義
	// -----------------------------
	tmp_sute_hai = tk->kyoku[tk->kyoku_index].act_hai[tk->kyoku[tk->kyoku_index].act_count];
	tmp_sute_ply = tk->kyoku[tk->kyoku_index].act_ply[tk->kyoku[tk->kyoku_index].act_count];

	// -----------------------------
	// 和了プレートの無効化
	// -----------------------------
	plt_mode[PLT_AGARI] = false;

	// -----------------------------
	// 待牌確認
	// -----------------------------
	for(int tmp_i = 0; tmp_i < tk->ply_act_machi_count[HUM_PLY_SEKI_NUM]; tmp_i++){

		// ロンなら(待ちヒストグラムと一致するのか？)
		if( tk->ply_act_machi_hai[HUM_PLY_SEKI_NUM][tmp_i] == tk->kyoku[tk->kyoku_index].act_hai[tk->kyoku[tk->kyoku_index].act_count]){

			// プレート有効化
			plt_mode[PLT_AGARI] = true;
			plt_mode[PLT_NEXT]  = true;

			// 捨牌着色
			if ( ( tk->ply_act_kawa_mode[tmp_sute_ply][tk->ply_act_kawa_count[tmp_sute_ply]-1] == 0) || 
			     ( tk->ply_act_kawa_mode[tmp_sute_ply][tk->ply_act_kawa_count[tmp_sute_ply]-1] == 5)
			   ){
				tk->ply_act_kawa_mode[tmp_sute_ply][tk->ply_act_kawa_count[tmp_sute_ply]-1] = tk->ply_act_kawa_mode[tmp_sute_ply][tk->ply_act_kawa_count[tmp_sute_ply]-1] + HAI_COLOR_NUM_BLUE;
			}

			break;

		}else{
			// プレート無効化
			plt_mode[PLT_AGARI] = false;
		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// HUMプレーヤの鳴牌確認
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::guiChkPlyNakiStat(MJSTkinfo *tk){

	// 事前定義
	int tmp_sute_hai;
	int tmp_sute_ply;
	chihai_count = 0;

	// -----------------------------
	// 他プレーヤの捨牌定義
	// -----------------------------
	tmp_sute_hai = tk->kyoku[tk->kyoku_index].act_hai[tk->kyoku[tk->kyoku_index].act_count];
	tmp_sute_ply = tk->kyoku[tk->kyoku_index].act_ply[tk->kyoku[tk->kyoku_index].act_count];

	// -----------------------------
	// ポン確認
	// -----------------------------
	if ( tk->ply_act_tehai[HUM_PLY_SEKI_NUM][tmp_sute_hai] > 1){

		// プレート有効化
		plt_mode[PLT_PON]   = true;
		plt_mode[PLT_NEXT]  = true;

		// 鳴き牌定義
		// tk->ply_naki_idx[HUM_PLY_SEKI_NUM] = tmp_sute_hai;

		// 捨牌着色
		if ( ( tk->ply_act_kawa_mode[tmp_sute_ply][tk->ply_act_kawa_count[tmp_sute_ply]-1] == 0) || // 通常捨牌の場合
		     ( tk->ply_act_kawa_mode[tmp_sute_ply][tk->ply_act_kawa_count[tmp_sute_ply]-1] == 5) ){ // リーチ宣言時の捨牌の場合
			// 捨牌を着色
			tk->ply_act_kawa_mode[tmp_sute_ply][tk->ply_act_kawa_count[tmp_sute_ply]-1] = tk->ply_act_kawa_mode[tmp_sute_ply][tk->ply_act_kawa_count[tmp_sute_ply]-1] + HAI_COLOR_NUM_BLUE;
		}

	}

	// -----------------------------
	// 明槓確認
	// -----------------------------
	if ( tk->ply_act_tehai[HUM_PLY_SEKI_NUM][tmp_sute_hai] > 2){

		// プレート有効化
		plt_mode[PLT_KAN]   = true;
		plt_mode[PLT_NEXT]  = true;

		// 鳴き牌定義
		// tk->ply_naki_idx[HUM_PLY_SEKI_NUM]       = tmp_sute_hai;
		// tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = 0;

		// 捨牌着色
		if ( ( tk->ply_act_kawa_mode[tmp_sute_ply][tk->ply_act_kawa_count[tmp_sute_ply]-1] == 0) ||      // 通常捨牌の場合
		     ( tk->ply_act_kawa_mode[tmp_sute_ply][tk->ply_act_kawa_count[tmp_sute_ply]-1] == 5) ){      // リーチ宣言時の捨牌の場合

			// 捨牌を着色
			tk->ply_act_kawa_mode[tmp_sute_ply][tk->ply_act_kawa_count[tmp_sute_ply]-1] = tk->ply_act_kawa_mode[tmp_sute_ply][tk->ply_act_kawa_count[tmp_sute_ply]-1] + HAI_COLOR_NUM_BLUE;
		}

	}

	// -----------------------------
	// チー確認(鳴き牌が1枚目)
	// -----------------------------
	if ( tk->ply_act_tehai[HUM_PLY_SEKI_NUM][tmp_sute_hai+1] > 0 && 
         tk->ply_act_tehai[HUM_PLY_SEKI_NUM][tmp_sute_hai+2] > 0 &&
		 tmp_sute_ply == HUM_PLY_SEKI_NUM - 1 &&
		 tmp_sute_hai > 0 &&
		 tmp_sute_hai < 30 ){

		// プレート有効化
		plt_mode[PLT_CHI]   = true;
		plt_mode[PLT_NEXT]  = true;

		// 鳴き牌定義(GUIクラス)
		chihai_count ++;    // チー候補数+1
		chihai_mode[0] = true;
		chi_idx_hai[0] = tmp_sute_hai;

		chi_hai_num1[0] = tmp_sute_hai+1;
		chi_hai_num2[0] = tmp_sute_hai+2;

		// 赤牌枚数確認(「3」-4-5のパターン)
		if( tmp_sute_hai == 3        && tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][0] > 0){
		 chi_aka_count[0] = 1;
		}else if( tmp_sute_hai == 13 && tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][1] > 0){
		 chi_aka_count[0] = 1;
		}else if( tmp_sute_hai == 23 && tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][2] > 0){
		 chi_aka_count[0] = 1;

		// 赤牌枚数確認(「4」-5-6のパターン)
		}else if( tmp_sute_hai ==  4 && tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][0] > 0){
		 chi_aka_count[0] = 1;
		}else if( tmp_sute_hai == 14 && tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][1] > 0){
		 chi_aka_count[0] = 1;
		}else if( tmp_sute_hai == 24 && tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][2] > 0){
		 chi_aka_count[0] = 1;
		}else{
		 chi_aka_count[0] = 0;
		}

		// 捨牌着色
		if ( ( tk->ply_act_kawa_mode[tmp_sute_ply][tk->ply_act_kawa_count[tmp_sute_ply]-1] == 0) || 
		     ( tk->ply_act_kawa_mode[tmp_sute_ply][tk->ply_act_kawa_count[tmp_sute_ply]-1] == 5)
		   ){
			tk->ply_act_kawa_mode[tmp_sute_ply][tk->ply_act_kawa_count[tmp_sute_ply]-1] = tk->ply_act_kawa_mode[tmp_sute_ply][tk->ply_act_kawa_count[tmp_sute_ply]-1] + HAI_COLOR_NUM_BLUE;
		}

	}else{

		// 鳴き牌定義(GUIクラス)
		chihai_mode[0] = false;

	}

	// -----------------------------
	// チー確認(鳴き牌が2枚目)
	// -----------------------------
	if ( tk->ply_act_tehai[HUM_PLY_SEKI_NUM][tmp_sute_hai-1] > 0 && 
	     tk->ply_act_tehai[HUM_PLY_SEKI_NUM][tmp_sute_hai+1] > 0 &&
		 tmp_sute_ply == HUM_PLY_SEKI_NUM - 1 &&
                 tmp_sute_hai > 1 &&
		         tmp_sute_hai < 30 ){

		// プレート有効化
		plt_mode[PLT_CHI]   = true;
		plt_mode[PLT_NEXT]  = true;

		// 鳴き牌定義(GUIクラス)
		chihai_count ++;    // チー候補数+1
		chihai_mode[1] = true;
		chi_idx_hai[1] = tmp_sute_hai-1;

		chi_hai_num1[1] = tmp_sute_hai-1;
		chi_hai_num2[1] = tmp_sute_hai+1;

		// 赤牌枚数確認(3-「4」-5のパターン)
		if( tmp_sute_hai == 4        && tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][0] > 0){
		 chi_aka_count[1] = 1;
		}else if( tmp_sute_hai == 14 && tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][1] > 0){
		 chi_aka_count[1] = 1;
		}else if( tmp_sute_hai == 24 && tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][2] > 0){
		 chi_aka_count[1] = 1;

		// 赤牌枚数確認(5-「6」-7のパターン)
		}else if( tmp_sute_hai ==  6 && tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][0] > 0){
		 chi_aka_count[1] = 1;
		}else if( tmp_sute_hai == 16 && tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][1] > 0){
		 chi_aka_count[1] = 1;
		}else if( tmp_sute_hai == 26 && tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][2] > 0){
		 chi_aka_count[1] = 1;

		}else{
		 chi_aka_count[1] = 0;
		}

		// 捨牌着色
		if ( ( tk->ply_act_kawa_mode[tmp_sute_ply][tk->ply_act_kawa_count[tmp_sute_ply]-1] == 0) || 
		     ( tk->ply_act_kawa_mode[tmp_sute_ply][tk->ply_act_kawa_count[tmp_sute_ply]-1] == 5)
		   ){
			tk->ply_act_kawa_mode[tmp_sute_ply][tk->ply_act_kawa_count[tmp_sute_ply]-1] = tk->ply_act_kawa_mode[tmp_sute_ply][tk->ply_act_kawa_count[tmp_sute_ply]-1] + HAI_COLOR_NUM_BLUE;
		}

	}else{

		// 鳴き牌定義(GUIクラス)
		chihai_mode[1] = false;

	}

	// -----------------------------
	// チー確認(鳴き牌が3枚目)
	// -----------------------------
	if ( tk->ply_act_tehai[HUM_PLY_SEKI_NUM][tmp_sute_hai-2] > 0 && 
	     tk->ply_act_tehai[HUM_PLY_SEKI_NUM][tmp_sute_hai-1] > 0 &&
		 tmp_sute_ply == HUM_PLY_SEKI_NUM - 1 &&
	     tmp_sute_hai > 2 &&
	     tmp_sute_hai < 30 ){

		// プレート有効化
		plt_mode[PLT_CHI]   = true;
		plt_mode[PLT_NEXT]  = true;

		// 鳴き牌定義(GUIクラス)
		chihai_count ++;    // チー候補数+1
		chihai_mode[2] = true;
		chi_idx_hai[2] = tmp_sute_hai-2;

		chi_hai_num1[2] = tmp_sute_hai-2;
		chi_hai_num2[2] = tmp_sute_hai-1;

		// 赤牌枚数確認(4-5-「6」のパターン)
		if( tmp_sute_hai == 6        && tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][0] > 0){
		 chi_aka_count[2] = 1;
		}else if( tmp_sute_hai == 16 && tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][1] > 0){
		 chi_aka_count[2] = 1;
		}else if( tmp_sute_hai == 26 && tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][2] > 0){
		 chi_aka_count[2] = 1;

		// 赤牌枚数確認(5-6-「7」のパターン)
		}else if( tmp_sute_hai ==  7 && tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][0] > 0){
		 chi_aka_count[2] = 1;
		}else if( tmp_sute_hai == 17 && tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][1] > 0){
		 chi_aka_count[2] = 1;
		}else if( tmp_sute_hai == 27 && tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][2] > 0){
		 chi_aka_count[2] = 1;

		}else{
		 chi_aka_count[2] = 0;
		}

		// 捨牌着色
		if ( ( tk->ply_act_kawa_mode[tmp_sute_ply][tk->ply_act_kawa_count[tmp_sute_ply]-1] == 0) || 
		     ( tk->ply_act_kawa_mode[tmp_sute_ply][tk->ply_act_kawa_count[tmp_sute_ply]-1] == 5)
		   ){
			tk->ply_act_kawa_mode[tmp_sute_ply][tk->ply_act_kawa_count[tmp_sute_ply]-1] = tk->ply_act_kawa_mode[tmp_sute_ply][tk->ply_act_kawa_count[tmp_sute_ply]-1] + HAI_COLOR_NUM_BLUE;
		}

	}else{

		// 鳴き牌定義(GUIクラス)
		chihai_mode[2] = false;

	}

}

/* ---------------------------------------------------------------------------------------------- */
// クリック後処理(メイン)
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::guiTakuActClick(MJSTkinfo *tk){

	// マウス情報取得
	MouseStat();

	// ----------------------------------------
	// マウス開放
	// ----------------------------------------

	// マウスが押されていないなら、「マウス開放状態(mouse_push_flg=0)」とする
	if( Button[0]==0 && Button[1]==0 ){

		// マウスチェックフラグ無効化
		mouse_push_flg = 0;

		// クリック確認フラグ無効化
		act_push_flg = false;

	}

	// ----------------------------------------
	// ボタンが押された場合の処理
	// ----------------------------------------

	// マウスが押されたか、フレームが超過したなら、
//	if( (Button[0] > 0 && mouse_push_flg == 0) || ( frame_count > AUTO_FRAME_COUNT_PLAYING) ){
	if(  Button[0] > 0 && mouse_push_flg == 0){

		// フレーム初期化
		frame_count = 0;

		// マウスチェックフラグ有効化
		mouse_push_flg = 1;
	
		// ----------------------------------------
		// メイン処理：ステータスごとのパーツ表示
		// ----------------------------------------

		// ----------------------------------------
		// 卓開始
		// ----------------------------------------
		if( tk->stat == TAKUSTART){

		// ----------------------------------------
		// 場決め
		// ----------------------------------------
		}else if(tk->stat == BAGIME){

			// 「次へ」プレートが押されている場合には
			// if( msx > SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_NEXT && 
			//    msx < SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_NEXT + PLT_ICON_XSIZE &&
			//    msy > PLT_Y_STAT && 
			//    msy < PLT_Y_STAT + PLT_ICON_YSIZE ){

				//プッシュフラグ有効
				act_push_flg = true;

			// }

		// ----------------------------------------
		// 局結果表示
		// ----------------------------------------
		}else if(tk->stat == KYOKURESULT){

			// 次へプレート有効化
			plt_mode[PLT_NEXT]  = true;

			// 表示処理は無し
			guiKyokuEnd(tk);

		// ----------------------------------------
		// 卓結果表示
		// ----------------------------------------
		}else if(tk->stat == TAKURESULT){

			// 次へプレート有効化
			plt_mode[PLT_NEXT]  = true;

			// 表示処理は無し
			guiTakuEnd(tk);

		// ----------------------------------------
		// 自摸時のアクション待ち
		// ----------------------------------------
		}else if(tk->stat == PLYACTSUTEWAIT){

			// GUIステータスが通常の場合
			if( gui_taku_mode == COMMON_PLAY_MODE){

				// ボタン確認
				chk_but(tk);
				set_plt_naki_arinashi();

				// ボタンが押されてないなら
				if(but_push_flg == false){

					// 人ならプレート状態確認
					if( tk->ply_hum_mode == 1 && tk->ply_turn == HUM_PLY_SEKI_NUM){
						// 通常状態確認
						guiSetPlyNormalActMain(tk);
					}else{
						// クリックフラグ有効化
						act_push_flg = true;
					}

				}

			// GUIステータスが通常以外の場合
			}else{
				// ボタン確認
				chk_but(tk);
				set_plt_naki_arinashi();
			}

		// ----------------------------------------
		// HUMプレーヤの鳴き待ち
		// ----------------------------------------
		}else if(tk->stat == PLYACTNAKIWAIT){

			// GUIステータスが通常の場合
			if( gui_taku_mode == COMMON_PLAY_MODE){

				// ボタン確認
				chk_but(tk);
				set_plt_naki_arinashi();

				// ボタンが押されてないなら
				if(but_push_flg == false){
					// HUMプレーヤの鳴き待ち
					guiSetPlyNakiActMain(tk);
				}

			// GUIステータスが通常以外の場合
			}else{
				// ボタン確認
				chk_but(tk);
				set_plt_naki_arinashi();
			}

		// ----------------------------------------
		// 鳴き捨牌待ち
		// ----------------------------------------
		}else if(tk->stat == PLYACTNAKISUTEWAIT){

			// GUIステータスが通常の場合
			if( gui_taku_mode == COMMON_PLAY_MODE){

				// ボタン確認
				chk_but(tk);
				set_plt_naki_arinashi();

				// ボタンが押されてないなら
				if(but_push_flg == false){

					// 人ならプレート状態確認
					if( tk->ply_hum_mode == 1 && tk->ply_turn == HUM_PLY_SEKI_NUM){
						// 鳴き捨牌待ち
						guiSetPlyNakiSuteAct(tk);
					}else{
						// クリックフラグ有効化
						act_push_flg = true;
					}

				}

			// GUIステータスが通常以外の場合
			}else{
				// ボタン確認
				chk_but(tk);
				set_plt_naki_arinashi();
			}

		// ----------------------------------------
		// 標準処理(その他処理)
		// ----------------------------------------
		}else{

			// GUIステータスが通常の場合
			if( gui_taku_mode == COMMON_PLAY_MODE){

				// ボタン確認
				chk_but(tk);
				set_plt_naki_arinashi();

				// ボタンが押されてないなら
				if(but_push_flg == false){
					// クリックフラグ有効化
					act_push_flg = true;
				}

			// GUIステータスが通常以外の場合
			}else{
				// ボタン確認
				chk_but(tk);
				set_plt_naki_arinashi();
			}

		} // tk->statの条件分岐

	// ----------------------------------------
	// マウスが押されていないなら、フレームをカウントアップ
	// ----------------------------------------
	}else{

			//フレームカウント
			frame_count++;
	}

}

/* ---------------------------------------------------------------------------------------------- */
// 1.GUI操作通常処理（メイン）
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::guiSetPlyNormalActMain(MJSTkinfo *tk){

	// プレーヤー通常アクション定義(mode:TEHAI_NORMAL)
	if( gui_ply_tehai_mode == TEHAI_NORMAL ){
		guiSetPlyNormalAct(tk);
	// リーチ宣言後の捨牌選択(mode:TEHAI_RIICHI_SUTEHAI)
	}else if( gui_ply_tehai_mode == TEHAI_RIICHI_SUTEHAI ){
		guiSetPlyRiichiSutehaiAct(tk);
	// リーチ有効後のアクション(自摸切り、自摸和了、暗槓)(mode:TEHAI_RIICHI_YUKO)
	}else if( gui_ply_tehai_mode == TEHAI_RIICHI_YUKO ){
		guiSetPlyRiichiYukoAct(tk);
	// プレーヤー暗槓アクション定義(mode:TEHAI_ANKAN_KAKAN_SELECT)
	}else if( gui_ply_tehai_mode == TEHAI_ANKAN_KAKAN_SELECT ){
		guiSetPlyAnkanKakanAct(tk);
	}

}

/* ---------------------------------------------------------------------------------------------- */
// 1-1.GUI操作通常処理・プレーヤー通常アクション定義(mode:TEHAI_NORMAL)
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::guiSetPlyNormalAct(MJSTkinfo *tk){

	// ----------------------------------------
	// 手牌内の捨牌処理
	// ----------------------------------------
	if( msx > tehai_x && 
	    msx < tehai_x + (tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM]-1)*HAI_XSIZE+HAI_XSIZE &&
	    msy > tehai_y && 
	    msy < tehai_y + HAI_YSIZE ){

		// クリックフラグ有効化
		act_push_flg = true;

		// 手牌テーブルクリックフラグ有効化とアクション定義
		tk->ply_act = ACTSUTE;

		// 捨牌番号設定(マウス選択位置)
		tk->ply_tbl_hum_sutehai_statnum = (msx-tehai_x) / HAI_XSIZE;

		// プレート無効化
		plt_mode[PLT_RIICHI] = false;
		plt_mode[PLT_PON]    = false;
		plt_mode[PLT_KAN]    = false;
		plt_mode[PLT_CHI]    = false;
		plt_mode[PLT_AGARI]  = false;

	// ----------------------------------------
	// 自摸牌の捨牌処理
	// ----------------------------------------
	}else if( msx > tehai_x + (tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM]*HAI_XSIZE) + SPACE_XSIZE && 
			  msx < tehai_x + (tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM]*HAI_XSIZE) + SPACE_XSIZE + HAI_XSIZE && 
			  msy > tehai_y && 
			  msy < tehai_y + HAI_YSIZE ){

		// クリックフラグ有効化
		act_push_flg = true;

		// テーブルクリックフラグ有効化
		tk->ply_act = ACTTSUMOGIRI;

		// 捨牌番号設定
		tk->ply_tbl_hum_sutehai_statnum = tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM]; // 自摸牌

		// プレート無効化
		plt_mode[PLT_RIICHI] = false;
		plt_mode[PLT_PON]    = false;
		plt_mode[PLT_KAN]    = false;
		plt_mode[PLT_CHI]    = false;
		plt_mode[PLT_AGARI]  = false;

	// ----------------------------------------
	// 槓プレートが押されたなら
	// ----------------------------------------
	}else if( plt_mode[PLT_KAN] == true &&
	          msx > SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_KAN && 
		      msx < SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_KAN + PLT_ICON_XSIZE &&
		      msy > PLT_Y_STAT && 
		      msy < PLT_Y_STAT + PLT_ICON_YSIZE ){

		// 暗槓牌ならば
		if ( naki_ankan_hai_count == 1 && naki_kakan_hai_count == 0 ){

			// クリックフラグ有効化
			act_push_flg = true;

			// HUMプレーヤーのアクション定義
			tk->ply_act = ACTANKAN;
			tk->ply_naki_idx[HUM_PLY_SEKI_NUM] = naki_ankan_hai[0];

		// 加槓牌ならば
		}else if( naki_ankan_hai_count == 0 && naki_kakan_hai_count == 1 ){

			// クリックフラグ有効化
			act_push_flg = true;

			// HUMプレーヤーのアクション定義
			tk->ply_act = ACTKAKAN;
			tk->ply_naki_idx[HUM_PLY_SEKI_NUM] = naki_kakan_hai[0];

			// 加槓牌が赤牌ならば
			if ( tk->ply_naki_idx[HUM_PLY_SEKI_NUM] == 5 && tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][0] > 0){
				tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = 1;
			}else if ( tk->ply_naki_idx[HUM_PLY_SEKI_NUM] == 15 && tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][1] > 0){
				tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = 1;
			}else if ( tk->ply_naki_idx[HUM_PLY_SEKI_NUM] == 25 && tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][2] > 0){
				tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = 1;
			}else{
				tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = 0;
			}

		// 候補牌が複数ある場合には
		}else{

			// ----------------------------------------
			// GUI手牌モードの変更
			// ----------------------------------------
			gui_ply_tehai_mode = TEHAI_ANKAN_KAKAN_SELECT;

/*
			// ----------------------------------------
			// 暗槓牌ならば
			// ----------------------------------------
			if ( naki_ankan_hai_count > 0){
				// HUMプレーヤーのアクション定義
				tk->ply_act = ACTANKAN;
				tk->ply_naki_idx[HUM_PLY_SEKI_NUM] = naki_ankan_hai[0];
			}

			// ----------------------------------------
			// 加槓牌ならば
			// ----------------------------------------
			if ( naki_kakan_hai_count > 0){

				// HUMプレーヤーのアクション定義
				tk->ply_act = ACTKAKAN;
				tk->ply_naki_idx[HUM_PLY_SEKI_NUM] = naki_kakan_hai[0];

				// 加槓牌が赤牌ならば
				if ( tk->ply_naki_idx[HUM_PLY_SEKI_NUM] == 5 && tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][0] > 0){
					tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = 1;
				}else if ( tk->ply_naki_idx[HUM_PLY_SEKI_NUM] == 15 && tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][1] > 0){
					tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = 1;
				}else if ( tk->ply_naki_idx[HUM_PLY_SEKI_NUM] == 25 && tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][2] > 0){
					tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = 1;
				}else{
					tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = 0;
				}
			}
*/

		}

		// ----------------------------------------
		// プレート無効化
		// ----------------------------------------
		plt_mode[PLT_RIICHI] = false;
		plt_mode[PLT_PON]    = false;
		plt_mode[PLT_KAN]    = false;
		plt_mode[PLT_CHI]    = false;
		plt_mode[PLT_AGARI]  = false;

	// ----------------------------------------
	// リーチプレートが押されたなら
	// ----------------------------------------
	}else if( plt_mode[PLT_RIICHI] == true &&
	          msx > SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_RIICHI && 
		      msx < SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_RIICHI + PLT_ICON_XSIZE &&
		      msy > PLT_Y_STAT && 
		      msy < PLT_Y_STAT + PLT_ICON_YSIZE ){

		// クリックフラグ有効化
		act_push_flg = true;

		// HUMプレーヤーのアクション定義
		tk->ply_act = ACTRIICH;

		// GUI手牌モードの変更
		gui_ply_tehai_mode = TEHAI_RIICHI_SUTEHAI;

		// プレート無効化
		plt_mode[PLT_RIICHI] = false;
		plt_mode[PLT_PON]    = false;
		plt_mode[PLT_KAN]    = false;
		plt_mode[PLT_CHI]    = false;
		plt_mode[PLT_AGARI]  = false;

	// ----------------------------------------
	// 和了プレートが押されたなら
	// ----------------------------------------
	}else if( plt_mode[PLT_AGARI] == true &&
		      msx > SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_AGARI && 
		      msx < SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_AGARI + PLT_ICON_XSIZE &&
		      msy > PLT_Y_STAT && 
		      msy < PLT_Y_STAT + PLT_ICON_YSIZE ){

		// クリックフラグ有効化
		act_push_flg = true;

		// HUMプレーヤーのアクション定義
		tk->ply_act = ACTTSUMOAGARI;

		// プレート無効化
		plt_mode[PLT_RIICHI] = false;
		plt_mode[PLT_PON]    = false;
		plt_mode[PLT_KAN]    = false;
		plt_mode[PLT_CHI]    = false;
		plt_mode[PLT_AGARI]  = false;

	// ----------------------------------------
	// 他の場所が押された場合は、クリックフラグを無効化する
	// ----------------------------------------
	}else{

		// クリックフラグ無効化
		act_push_flg = false;

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 1-2.GUI操作通常処理・リーチ宣言後の捨牌選択(mode:TEHAI_RIICHI_SUTEHAI)
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::guiSetPlyRiichiSutehaiAct(MJSTkinfo *tk){

	// ----------------------------------------
	// 手牌内の捨牌処理
	// ----------------------------------------
	if( msx > tehai_x && 
	    msx < tehai_x + (tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM]-1)*HAI_XSIZE + HAI_XSIZE &&
	    msy > tehai_y && 
	    msy < tehai_y + HAI_YSIZE ){

		// リーチ時の選択捨牌のシャンテンが0であるなら
		if(tk->ply_act_tehai_can_sute_tbl[HUM_PLY_SEKI_NUM][(msx-tehai_x)/HAI_XSIZE] == true){

			// クリックフラグ有効化
			act_push_flg = true;

			// 手牌テーブルクリックフラグ有効化とアクション定義
			tk->ply_act = ACTSUTE;

			// 捨牌番号設定(マウス選択位置)
			tk->ply_tbl_hum_sutehai_statnum = (msx-tehai_x) / HAI_XSIZE;

			// GUI手牌モードの変更
			gui_ply_tehai_mode = TEHAI_RIICHI_YUKO;

		}

	// ----------------------------------------
	// 自摸牌でクリックしたなら捨牌を定義する
	// ----------------------------------------
	}else if( msx > tehai_x + (tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM]*HAI_XSIZE) + SPACE_XSIZE && 
			  msx < tehai_x + (tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM]*HAI_XSIZE) + SPACE_XSIZE + HAI_XSIZE &&
			  msy > tehai_y && 
			  msy < tehai_y + HAI_YSIZE ){

		// リーチ時の選択捨牌のシャンテンが0であるなら
		if( tk->ply_act_tsumo_can_sute[HUM_PLY_SEKI_NUM] == true ){

			// クリックフラグ有効化
			act_push_flg = true;

			// テーブルクリックフラグ有効化
			tk->ply_act = ACTTSUMOGIRI;

			// 捨牌番号設定
			tk->ply_tbl_hum_sutehai_statnum = (tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM]); // 自摸牌

			// GUI手牌モードの変更
			gui_ply_tehai_mode = TEHAI_RIICHI_YUKO;

		}
	}
}

/* ---------------------------------------------------------------------------------------------- */
// 1-3.GUI操作通常処理・リーチ有効後のアクション(自摸切り、自摸和了、暗槓)(mode:TEHAI_RIICHI_YUKO)
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::guiSetPlyRiichiYukoAct(MJSTkinfo *tk){

	// ----------------------------------------
	// 自摸牌でクリックしたなら捨牌を定義する
	// ----------------------------------------
	if( msx > tehai_x + (tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM]*HAI_XSIZE) + SPACE_XSIZE && 
		msx < tehai_x + (tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM]*HAI_XSIZE) + SPACE_XSIZE + HAI_XSIZE &&
		msy > tehai_y && 
		msy < tehai_y + HAI_YSIZE ){

		// クリックフラグ有効化
		act_push_flg = true;

		// テーブルクリックフラグ有効化
		tk->ply_act = ACTTSUMOGIRI;

		// 捨牌番号設定
		tk->ply_tbl_hum_sutehai_statnum = tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM]; // 自摸牌

	// ----------------------------------------
	// 槓プレートが押されたなら
	// ----------------------------------------
	}else if( plt_mode[PLT_KAN] == true &&
	          msx > SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_KAN && 
		      msx < SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_KAN + PLT_ICON_XSIZE &&
		      msy > PLT_Y_STAT && 
		      msy < PLT_Y_STAT + PLT_ICON_YSIZE ){

		// クリックフラグ有効化
		act_push_flg = true;

		// 暗槓牌ならば
		if ( naki_ankan_hai_count > 0){
			// HUMプレーヤーのアクション定義
			tk->ply_act = ACTANKAN;
			tk->ply_naki_idx[HUM_PLY_SEKI_NUM] = naki_ankan_hai[0];
		}

		// プレート無効化
		plt_mode[PLT_RIICHI] = false;
		plt_mode[PLT_PON]    = false;
		plt_mode[PLT_KAN]    = false;
		plt_mode[PLT_CHI]    = false;
		plt_mode[PLT_AGARI]  = false;

		// GUI手牌モードの変更
		// gui_ply_tehai_mode = TEHAI_ANKAN_KAKAN_SELECT;

	// ----------------------------------------
	// 和了プレートが押されたなら
	// ----------------------------------------
	}else if( plt_mode[PLT_AGARI] == true &&
		      msx > SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_AGARI && 
		      msx < SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_AGARI + PLT_ICON_XSIZE &&
		      msy > PLT_Y_STAT && 
		      msy < PLT_Y_STAT + PLT_ICON_YSIZE ){

		// クリックフラグ有効化
		act_push_flg = true;

		// 手牌テーブルクリックフラグ有効化とアクション定義
		tk->ply_act = ACTTSUMOAGARI;

		// プレート無効化
		plt_mode[PLT_RIICHI] = false;
		plt_mode[PLT_PON]    = false;
		plt_mode[PLT_KAN]    = false;
		plt_mode[PLT_CHI]    = false;
		plt_mode[PLT_AGARI]  = false;

	// ----------------------------------------
	// 他の場所が押された場合は、クリックフラグを無効化する
	// ----------------------------------------
	}else{

		// クリックフラグ無効化
		act_push_flg = false;

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 1-4.GUI操作通常処理・プレーヤー暗槓アクション定義(mode:TEHAI_ANKAN_KAKAN_SELECT)
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::guiSetPlyAnkanKakanAct(MJSTkinfo *tk){

	// ----------------------------------------
	// 槓牌の選択
	// ----------------------------------------
	if( msx > tehai_x && 
	    msx < tehai_x + (tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM]-1)*HAI_XSIZE + HAI_XSIZE &&
	    msy > tehai_y && 
	    msy < tehai_y + HAI_YSIZE ){

		// 暗槓牌0なら
		if( tk->ply_act_tehaitbl[HUM_PLY_SEKI_NUM][(msx-tehai_x)/HAI_XSIZE] == naki_ankan_hai[0]){

			// クリックフラグ有効化
			act_push_flg = true;

			// HUMプレーヤーのアクション定義
			tk->ply_act = ACTANKAN;
			tk->ply_naki_idx[HUM_PLY_SEKI_NUM] = naki_ankan_hai[0];

			// GUI手牌モードの変更
			gui_ply_tehai_mode = TEHAI_NORMAL;

		}

		// 暗槓牌1なら
		if( tk->ply_act_tehaitbl[HUM_PLY_SEKI_NUM][(msx-tehai_x)/HAI_XSIZE] == naki_ankan_hai[1]){

			// クリックフラグ有効化
			act_push_flg = true;

			// HUMプレーヤーのアクション定義
			tk->ply_act = ACTANKAN;
			tk->ply_naki_idx[HUM_PLY_SEKI_NUM] = naki_ankan_hai[1];

			// GUI手牌モードの変更
			gui_ply_tehai_mode = TEHAI_NORMAL;

		}

		// 暗槓牌2なら
		if( tk->ply_act_tehaitbl[HUM_PLY_SEKI_NUM][(msx-tehai_x)/HAI_XSIZE] == naki_ankan_hai[2]){

			// クリックフラグ有効化
			act_push_flg = true;

			// HUMプレーヤーのアクション定義
			tk->ply_act = ACTANKAN;
			tk->ply_naki_idx[HUM_PLY_SEKI_NUM] = naki_ankan_hai[2];

			// GUI手牌モードの変更
			gui_ply_tehai_mode = TEHAI_NORMAL;

		}

		// 加槓牌0なら
		if( tk->ply_act_tehaitbl[HUM_PLY_SEKI_NUM][(msx-tehai_x)/HAI_XSIZE] == naki_kakan_hai[0]){

			// クリックフラグ有効化
			act_push_flg = true;

			// HUMプレーヤーのアクション定義
			tk->ply_act = ACTKAKAN;
			tk->ply_naki_idx[HUM_PLY_SEKI_NUM] = naki_kakan_hai[0];

			// 加槓牌が赤牌ならば
			if ( tk->ply_naki_idx[HUM_PLY_SEKI_NUM] == 5 && tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][0] > 0){
				tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = 1;
			}else if ( tk->ply_naki_idx[HUM_PLY_SEKI_NUM] == 15 && tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][1] > 0){
				tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = 1;
			}else if ( tk->ply_naki_idx[HUM_PLY_SEKI_NUM] == 25 && tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][2] > 0){
				tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = 1;
			}else{
				tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = 0;
			}

			// GUI手牌モードの変更
			gui_ply_tehai_mode = TEHAI_NORMAL;

		}

		// 加槓牌1なら
		if( tk->ply_act_tehaitbl[HUM_PLY_SEKI_NUM][(msx-tehai_x)/HAI_XSIZE] == naki_kakan_hai[1]){

			// クリックフラグ有効化
			act_push_flg = true;

			// HUMプレーヤーのアクション定義
			tk->ply_act = ACTKAKAN;
			tk->ply_naki_idx[HUM_PLY_SEKI_NUM] = naki_kakan_hai[1];

			// 加槓牌が赤牌ならば
			if ( tk->ply_naki_idx[HUM_PLY_SEKI_NUM] == 5 && tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][0] > 0){
				tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = 1;
			}else if ( tk->ply_naki_idx[HUM_PLY_SEKI_NUM] == 15 && tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][1] > 0){
				tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = 1;
			}else if ( tk->ply_naki_idx[HUM_PLY_SEKI_NUM] == 25 && tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][2] > 0){
				tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = 1;
			}else{
				tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = 0;
			}

			// GUI手牌モードの変更
			gui_ply_tehai_mode = TEHAI_NORMAL;

		}

		// 加槓牌2なら
		if( tk->ply_act_tehaitbl[HUM_PLY_SEKI_NUM][(msx-tehai_x)/HAI_XSIZE] == naki_kakan_hai[2]){

			// クリックフラグ有効化
			act_push_flg = true;

			// HUMプレーヤーのアクション定義
			tk->ply_act = ACTKAKAN;
			tk->ply_naki_idx[HUM_PLY_SEKI_NUM] = naki_kakan_hai[2];

			// 加槓牌が赤牌ならば
			if ( tk->ply_naki_idx[HUM_PLY_SEKI_NUM] == 5 && tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][0] > 0){
				tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = 1;
			}else if ( tk->ply_naki_idx[HUM_PLY_SEKI_NUM] == 15 && tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][1] > 0){
				tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = 1;
			}else if ( tk->ply_naki_idx[HUM_PLY_SEKI_NUM] == 25 && tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][2] > 0){
				tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = 1;
			}else{
				tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = 0;
			}

			// GUI手牌モードの変更
			gui_ply_tehai_mode = TEHAI_NORMAL;

		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 2.GUI操作通常処理・プレーヤー個別鳴き確認(メイン)
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::guiSetPlyNakiActMain(MJSTkinfo *tk){

	// ----------------------------------------
	// 手番が自分であるなら、「鳴きなし」アクション
	// ----------------------------------------
	if( tk->ply_turn == HUM_PLY_SEKI_NUM){

		// クリックフラグ有効化
		act_push_flg = true;

		// アクション定義：鳴きなし
		tk->ply_act_naki[HUM_PLY_SEKI_NUM] = ACTNONAKI;

	// ----------------------------------------
	// 手番が他プレーヤの場合
	// ----------------------------------------
	}else{

		// -----------------------
		// 「通常モード」「リーチ後モード」のアクション処理
		// -----------------------
		if( gui_ply_tehai_mode == TEHAI_NORMAL || gui_ply_tehai_mode == TEHAI_RIICHI_YUKO){

			// HUMで鳴きアクションできない場合(NONAKIの設定)
			if( plt_mode[PLT_PON]   == false && 
		        plt_mode[PLT_KAN]   == false && 
		        plt_mode[PLT_CHI]   == false && 
		        plt_mode[PLT_AGARI] == false){

				// クリックフラグ有効化
				act_push_flg = true;

				// アクション定義：鳴きなし
				tk->ply_act_naki[HUM_PLY_SEKI_NUM] = ACTNONAKI;

			// HUMで鳴きアクション可能な場合
			}else{
				guiSetPlyNakiAct(tk);
			}

		// -----------------------
		// 「チー牌選択モード」のアクション定義
		// -----------------------
		}else if( gui_ply_tehai_mode == TEHAI_CHI_SELECT){
			guiSetPlyChiPaiAct(tk);
		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 2-1.GUI操作通常処理・プレーヤー個別鳴きアクション定義(mode:TEHAI_NORMAL || mode:TEHAI_RIICHI_YUKO)
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::guiSetPlyNakiAct(MJSTkinfo *tk){

	// ----------------------------------------
	// 次へプレートが押されたなら
	// ----------------------------------------
	if( msx > SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_NEXT && 
	          msx < SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_NEXT + PLT_ICON_XSIZE &&
	          msy > PLT_Y_STAT && 
	          msy < PLT_Y_STAT + PLT_ICON_YSIZE ){

		// クリックフラグ有効化
		act_push_flg = true;

		// HUMプレーヤーの鳴きアクション定義
		tk->ply_act_naki[HUM_PLY_SEKI_NUM]       = ACTNONAKI;
		tk->ply_naki_hai[HUM_PLY_SEKI_NUM]       = 0;
		tk->ply_naki_idx[HUM_PLY_SEKI_NUM]       = 0;
		tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = 0;

		// プレート無効化
		plt_mode[PLT_RIICHI] = false;
		plt_mode[PLT_PON]    = false;
		plt_mode[PLT_KAN]    = false;
		plt_mode[PLT_CHI]    = false;
		plt_mode[PLT_AGARI]  = false;

	// ----------------------------------------
	// 和了プレートが押されたなら
	// ----------------------------------------
	}else if( plt_mode[PLT_AGARI] == true &&
	      msx > SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_AGARI && 
	      msx < SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_AGARI + PLT_ICON_XSIZE &&
	      msy > PLT_Y_STAT && 
	      msy < PLT_Y_STAT + PLT_ICON_YSIZE ){

		// クリックフラグ有効化
		act_push_flg = true;

		// HUMプレーヤーの鳴きアクション定義
		tk->ply_act_naki[HUM_PLY_SEKI_NUM] = ACTRON;
		tk->ply_naki_hai[HUM_PLY_SEKI_NUM] = tk->kyoku[tk->kyoku_index].act_hai[tk->kyoku[tk->kyoku_index].act_count];
		tk->ply_naki_idx[HUM_PLY_SEKI_NUM] = tk->kyoku[tk->kyoku_index].act_hai[tk->kyoku[tk->kyoku_index].act_count];

		// 赤牌定義
		tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = 0;

		// プレート無効化
		plt_mode[PLT_RIICHI] = false;
		plt_mode[PLT_PON]    = false;
		plt_mode[PLT_KAN]    = false;
		plt_mode[PLT_CHI]    = false;
		plt_mode[PLT_AGARI]  = false;

	// ----------------------------------------
	// ポンプレートが押されたなら
	// ----------------------------------------
	}else if( plt_mode[PLT_PON] == true &&
	      msx > SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_PON && 
	      msx < SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_PON + PLT_ICON_XSIZE &&
	      msy > PLT_Y_STAT && 
	      msy < PLT_Y_STAT + PLT_ICON_YSIZE ){

		// クリックフラグ有効化
		act_push_flg = true;

		// HUMプレーヤーの鳴きアクション定義
		tk->ply_act_naki[HUM_PLY_SEKI_NUM] = ACTPON;
		tk->ply_naki_hai[HUM_PLY_SEKI_NUM] = tk->kyoku[tk->kyoku_index].act_hai[tk->kyoku[tk->kyoku_index].act_count];
		tk->ply_naki_idx[HUM_PLY_SEKI_NUM] = tk->kyoku[tk->kyoku_index].act_hai[tk->kyoku[tk->kyoku_index].act_count];

		// 赤牌定義
		if( tk->ply_naki_idx[HUM_PLY_SEKI_NUM] ==  5 || 
		    tk->ply_naki_idx[HUM_PLY_SEKI_NUM] == 15 || 
		    tk->ply_naki_idx[HUM_PLY_SEKI_NUM] == 25 ){

			if ( tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][(tk->ply_naki_idx[HUM_PLY_SEKI_NUM]-5)/10] > 2){
				tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = 2;
			}else{
				tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][(tk->ply_naki_idx[HUM_PLY_SEKI_NUM]-5)/10];
			}

		}else{
				tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = 0;
		}

		// プレート無効化
		plt_mode[PLT_RIICHI] = false;
		plt_mode[PLT_PON]    = false;
		plt_mode[PLT_KAN]    = false;
		plt_mode[PLT_CHI]    = false;
		plt_mode[PLT_AGARI]  = false;

	// ----------------------------------------
	// 槓プレートが押されたなら
	// ----------------------------------------
	}else if( plt_mode[PLT_KAN] == true &&
	      msx > SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_KAN && 
	      msx < SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_KAN + PLT_ICON_XSIZE &&
	      msy > PLT_Y_STAT && 
	      msy < PLT_Y_STAT + PLT_ICON_YSIZE ){

		// クリックフラグ有効化
		act_push_flg = true;

		// HUMプレーヤーの鳴きアクション定義
		tk->ply_act_naki[HUM_PLY_SEKI_NUM] = ACTMINKAN;
		tk->ply_naki_hai[HUM_PLY_SEKI_NUM] = tk->kyoku[tk->kyoku_index].act_hai[tk->kyoku[tk->kyoku_index].act_count];
		tk->ply_naki_idx[HUM_PLY_SEKI_NUM] = tk->kyoku[tk->kyoku_index].act_hai[tk->kyoku[tk->kyoku_index].act_count];
		tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = 0;

		// プレート無効化
		plt_mode[PLT_RIICHI] = false;
		plt_mode[PLT_PON]    = false;
		plt_mode[PLT_KAN]    = false;
		plt_mode[PLT_CHI]    = false;
		plt_mode[PLT_AGARI]  = false;

	// ----------------------------------------
	// チープレートが押されたなら
	// ----------------------------------------
	}else if( plt_mode[PLT_CHI] == true &&
	      msx > SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_CHI && 
	      msx < SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_CHI + PLT_ICON_XSIZE &&
	      msy > PLT_Y_STAT && 
	      msy < PLT_Y_STAT + PLT_ICON_YSIZE ){

		// チー候補牌が2枚以上であれば、牌選択処理を行う
		if (chihai_count > 1){

			// モード変更
			gui_ply_tehai_mode = TEHAI_CHI_SELECT;

		// チー候補牌が1枚であれば、自動チー処理
		}else{

			// クリックフラグ有効化
			act_push_flg = true;

			// HUMプレーヤーの鳴きアクション定義
			tk->ply_act_naki[HUM_PLY_SEKI_NUM] = ACTCHI;

			// チーINDEX牌定義(0)
			if (chihai_mode[0]== true){

				// チー牌定義(0)
				tk->ply_naki_hai[HUM_PLY_SEKI_NUM] = tk->kyoku[tk->kyoku_index].act_hai[tk->kyoku[tk->kyoku_index].act_count];
				tk->ply_naki_idx[HUM_PLY_SEKI_NUM] = chi_idx_hai[0];
				tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = chi_aka_count[0];

			// チーINDEX牌定義(1)
			}else if (chihai_mode[1]== true){

				// チー牌定義(1)
				tk->ply_naki_hai[HUM_PLY_SEKI_NUM] = tk->kyoku[tk->kyoku_index].act_hai[tk->kyoku[tk->kyoku_index].act_count];
				tk->ply_naki_idx[HUM_PLY_SEKI_NUM] = chi_idx_hai[1];
				tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = chi_aka_count[1];

			// チーINDEX牌定義(2)
			}else if (chihai_mode[2]== true){

				// チー牌定義(2)
				tk->ply_naki_hai[HUM_PLY_SEKI_NUM] = tk->kyoku[tk->kyoku_index].act_hai[tk->kyoku[tk->kyoku_index].act_count];
				tk->ply_naki_idx[HUM_PLY_SEKI_NUM] = chi_idx_hai[2];
				tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = chi_aka_count[2];

			// チーINDEX牌定義(例外処理)
			}else{

			}

		}

		// チー枚数初期化
		chihai_count = 0;

		// プレート無効化
		plt_mode[PLT_RIICHI] = false;
		plt_mode[PLT_PON]    = false;
		plt_mode[PLT_KAN]    = false;
		plt_mode[PLT_CHI]    = false;
		plt_mode[PLT_AGARI]  = false;

	// ----------------------------------------
	// それ以外の処理は無効化
	// ----------------------------------------
	}else{

		// クリックフラグ無効化
		act_push_flg = false;

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 2-2.GUI操作通常処理・プレーヤーチー牌アクション定義(mode:TEHAI_CHI_SELECT)
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::guiSetPlyChiPaiAct(MJSTkinfo *tk){

	// 変数定義
	int tmp_chi_idx;

	// ----------------------------------------
	// チー牌の選択
	// ----------------------------------------
	if( msx > tehai_x && 
	    msx < tehai_x + (tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM]-1)*HAI_XSIZE + HAI_XSIZE &&
	    msy > tehai_y && 
	    msy < tehai_y + HAI_YSIZE ){

		// 牌番号設定
		tmp_chi_idx = (msx-tehai_x) / HAI_XSIZE;

		// チーアクション設定
		if ( tk->ply_act_tehaitbl[HUM_PLY_SEKI_NUM][tmp_chi_idx] == chi_hai_num1[0] || 
		     tk->ply_act_tehaitbl[HUM_PLY_SEKI_NUM][tmp_chi_idx] == chi_hai_num1[1] || 
		     tk->ply_act_tehaitbl[HUM_PLY_SEKI_NUM][tmp_chi_idx] == chi_hai_num1[2] ){

			// クリックフラグ有効化
			act_push_flg = true;

			// HUMプレーヤーの鳴きアクション定義
			tk->ply_act_naki[HUM_PLY_SEKI_NUM] = ACTCHI;

			// 手牌モード変更
			gui_ply_tehai_mode = TEHAI_NORMAL;

			// チーINDEX牌定義
			if ( tk->ply_act_tehaitbl[HUM_PLY_SEKI_NUM][tmp_chi_idx] == chi_hai_num1[0]){
				tk->ply_naki_idx[HUM_PLY_SEKI_NUM]       = chi_idx_hai[0];
				tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = chi_aka_count[0];
			}

			// チーINDEX牌定義
			if ( tk->ply_act_tehaitbl[HUM_PLY_SEKI_NUM][tmp_chi_idx] == chi_hai_num1[1]){
				tk->ply_naki_idx[HUM_PLY_SEKI_NUM]       = chi_idx_hai[1];
				tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = chi_aka_count[1];
			}

			// チーINDEX牌定義
			if ( tk->ply_act_tehaitbl[HUM_PLY_SEKI_NUM][tmp_chi_idx] == chi_hai_num1[2]){
				tk->ply_naki_idx[HUM_PLY_SEKI_NUM]       = chi_idx_hai[2];
				tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = chi_aka_count[2];
			}

			// チー枚数初期化
			chihai_count = 0;

			// 赤牌枚数
			// tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = 0;

			// プレート無効化
			plt_mode[PLT_PON]    = false;
			plt_mode[PLT_KAN]    = false;
			plt_mode[PLT_CHI]    = false;
			plt_mode[PLT_AGARI]  = false;

		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 3.GUI操作通常処理・プレーヤー鳴き後の捨牌処理
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::guiSetPlyNakiSuteAct(MJSTkinfo *tk){

	// ----------------------------------------
	// 手牌内の捨牌処理
	// ----------------------------------------
	if( msx > tehai_x && 
	    msx < tehai_x + (tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM]-1)*HAI_XSIZE + HAI_XSIZE &&
	    msy > tehai_y && 
	    msy < tehai_y + HAI_YSIZE ){

		// クリックフラグ有効化
		act_push_flg = true;

		// HUMプレーヤーのアクション定義
		tk->ply_act = ACTNAKISUTE;

		// 捨牌番号設定(マウス選択位置)
		tk->ply_tbl_hum_sutehai_statnum = (msx-tehai_x) / HAI_XSIZE;

		// HUMプレーヤーの鳴きアクション定義
		tk->ply_act_naki[HUM_PLY_SEKI_NUM]       = ACTNONAKI;
		tk->ply_naki_idx[HUM_PLY_SEKI_NUM]       = 0;
		tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = 0;

	}

}

/* ---------------------------------------------------------------------------------------------- */
// (デバグ用)ply情報画面操作
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::guiPlyDetailInfo(MJSTkinfo *tk){

	// ----------------------------------------
	// BUT04が押されたなら
	// ----------------------------------------

	if( msx > THINFO_BUT_X_STAT && 
		msx < THINFO_BUT_X_STAT + 32 &&
		msy > BUT02_Y_STAT && 
		msy < BUT02_Y_STAT + 32 ){

		// (デバグ用)クリックフラグ無効化(プレートが押された場合は常にfalse)
		act_push_flg = false;

	}
}

/* ---------------------------------------------------------------------------------------------- */
// 卓処理(ゲームーモード)・局終了
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::guiKyokuEnd(MJSTkinfo *tk){

	// ----------------------------------------
	// 次へプレートが押されたら
	// ----------------------------------------

/*	if( ( msx > SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLTSTATNUM_NEXT && 
		msx < SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLTSTATNUM_NEXT + PLT_ICON_XSIZE &&
		msy > PLT_Y_STAT && 
		msy < PLT_Y_STAT + PLT_ICON_YSIZE ) || ( frame_count > AUTO_PUSH_FRAME_COUNT ) ){*/

		// クリックフラグ有効化
		act_push_flg = true;

//	}

}

/* ---------------------------------------------------------------------------------------------- */
// 卓処理(ゲームーモード)・卓終了
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::guiTakuEnd(MJSTkinfo *tk){

	// ----------------------------------------
	// 次へプレートが押されたら
	// ----------------------------------------

/*	if( ( msx > SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLTSTATNUM_NEXT && 
		msx < SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLTSTATNUM_NEXT + PLT_ICON_XSIZE &&
		msy > PLT_Y_STAT && 
		msy < PLT_Y_STAT + PLT_ICON_YSIZE ) || ( frame_count > AUTO_PUSH_FRAME_COUNT) ){*/

		// クリックフラグ有効化
		act_push_flg = true;

//	}

}

/* ---------------------------------------------------------------------------------------------- */
// ビューワーモードの初期化
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::guiViewerInitTaku(MJSTkinfo *tk){

	// 局情報初期化
	tk->KyokuInit();

	// 初期化
	gui_kyoku_index = 0;
	gui_actid = 0;

	// 下段手牌表示プレーヤID
	disp_down_tehai_pnum = 0;

	// tkクラスのアクション情報の最新化
	tk->Check_Ply_ActTehai(gui_kyoku_index, gui_actid);

	// GUIモード設定
	gui_taku_mode = COMMON_PLAY_MODE;                   // 卓ステータスモード：通常モード

	// 卓名定義
	wsprintf(tk->tkname, "%s", "ビューアモード牌譜");

}

/* ---------------------------------------------------------------------------------------------- */
// 卓処理(ビューアーモード)・メイン
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::guiViewerTaku(MJSTkinfo *tk){

	// マウス情報取得
	MouseStat();

	// ----------------------------------------
	// マウス開放
	// ----------------------------------------

	// マウスが押されていないなら、「マウス開放状態(mouse_push_flg=0)」とする
	if( Button[0] == 0 && Button[1] == 0 ){
		mouse_push_flg = 0;
	}

	// ----------------------------------------
	// ボタンが押された場合の処理
	// ----------------------------------------

	// マウスが押されたなら
	if( Button[0] > 0 && mouse_push_flg == 0){

		// マウスチェックフラグ有効化
		mouse_push_flg=1;

		// 終了ボタン確認
		chk_but(tk);

		// 終了ボタン以外の処理
		if(gui_taku_mode != COMMON_END_CHECK_MODE){
			count_plyact(tk);
		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 卓処理(ビューアーモード)：局・ACTIDのカウント
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::count_plyact(MJSTkinfo *tk){

	// ----------------------------------------
	// 局INDEX
	// ----------------------------------------

	// 局ID・カウントダウン
	if( msx > KYOID_X_STAT && msx < KYOID_X_STAT + BUT_ICON_XSIZE && 
		msy > ACTID_Y_STAT && msy < ACTID_Y_STAT + BUT_ICON_YSIZE && gui_kyoku_index > 0){

		// 表示モード変更
		gui_taku_mode = COMMON_PLAY_MODE;

		// 局ID変更
		gui_kyoku_index--;
		gui_actid = 0;

		// ----------------------------------------
		// tkクラスのアクション情報の最新化
		// ----------------------------------------
		tk->Check_Ply_ActTehai(gui_kyoku_index, gui_actid);

	// 局ID・カウントアップ
	}else if( msx>KYOID_X_STAT+BUT_ICON_XSIZE && msx<KYOID_X_STAT+BUT_ICON_XSIZE*2 && 
		      msy>ACTID_Y_STAT && msy<ACTID_Y_STAT+BUT_ICON_YSIZE && gui_kyoku_index < tk->kyoku_index-1){

		// 表示モード変更
		gui_taku_mode = COMMON_PLAY_MODE;

		// 局ID変更
		gui_kyoku_index++;
		gui_actid = 0;

		// ----------------------------------------
		// tkクラスのアクション情報の最新化
		// ----------------------------------------
		tk->Check_Ply_ActTehai(gui_kyoku_index, gui_actid);

	}

	// ----------------------------------------
	// アクション番号
	// ----------------------------------------

	// ActID・カウントダウンMIN
	if( msx>ACTID_X_STAT && msx<ACTID_X_STAT+BUT_ICON_XSIZE && 
		msy>ACTID_Y_STAT && msy<ACTID_Y_STAT+BUT_ICON_YSIZE){

		// 表示モード変更
		gui_taku_mode = COMMON_PLAY_MODE;

		// ActID変更
		gui_actid = 0;

		// ----------------------------------------
		// tkクラスのアクション情報の最新化
		// ----------------------------------------
		tk->Check_Ply_ActTehai(gui_kyoku_index, gui_actid);

	}

	// ActID・カウントダウン-4
	if( msx>ACTID_X_STAT+BUT_ICON_XSIZE*1 && msx<ACTID_X_STAT+BUT_ICON_XSIZE*2 && 
		msy>ACTID_Y_STAT && msy<ACTID_Y_STAT+BUT_ICON_YSIZE && gui_actid >= 4){

		// 表示モード変更
		gui_taku_mode = COMMON_PLAY_MODE;

		// ActID変更
		gui_actid=gui_actid-4;

		// ----------------------------------------
		// tkクラスのアクション情報の最新化
		// ----------------------------------------
		tk->Check_Ply_ActTehai(gui_kyoku_index, gui_actid);

	}

	// ActID・カウントダウン-1
	if( msx>ACTID_X_STAT+BUT_ICON_XSIZE*2 && msx<ACTID_X_STAT+BUT_ICON_XSIZE*3 && 
		msy>ACTID_Y_STAT && msy<ACTID_Y_STAT+BUT_ICON_YSIZE && gui_actid > 0){

		// 表示モード変更
		gui_taku_mode = COMMON_PLAY_MODE;

		// ActID変更
		gui_actid--;

		// ----------------------------------------
		// tkクラスのアクション情報の最新化
		// ----------------------------------------
		tk->Check_Ply_ActTehai(gui_kyoku_index, gui_actid);

	}

	// ActID・カウントアップ+1
	if( msx>ACTID_X_STAT+BUT_ICON_XSIZE*3 && msx<ACTID_X_STAT+BUT_ICON_XSIZE*4 && 
		msy>ACTID_Y_STAT && msy<ACTID_Y_STAT+BUT_ICON_YSIZE && gui_actid < tk->kyoku[gui_kyoku_index].act_count-1){

		// 表示モード変更
		gui_taku_mode = COMMON_PLAY_MODE;

		// ActID変更
		gui_actid++;

		// ----------------------------------------
		// tkクラスのアクション情報の最新化
		// ----------------------------------------
		tk->Check_Ply_ActTehai(gui_kyoku_index, gui_actid);

	}

	// ActID・カウントアップ+4
	if( msx>ACTID_X_STAT+BUT_ICON_XSIZE*4 && msx<ACTID_X_STAT+BUT_ICON_XSIZE*5 && 
		msy>ACTID_Y_STAT && msy<ACTID_Y_STAT+BUT_ICON_YSIZE && Button[0]>0 && gui_actid < tk->kyoku[gui_kyoku_index].act_count-1-4){

		// 表示モード変更
		gui_taku_mode = COMMON_PLAY_MODE;

		// ActID変更
		gui_actid=gui_actid+4;

		// ----------------------------------------
		// tkクラスのアクション情報の最新化
		// ----------------------------------------
		tk->Check_Ply_ActTehai(gui_kyoku_index, gui_actid);

	}

	// ActID・カウントアップMAX
	if( msx>ACTID_X_STAT+BUT_ICON_XSIZE*5 && msx<ACTID_X_STAT+BUT_ICON_XSIZE*6 && 
		msy>ACTID_Y_STAT && msy<ACTID_Y_STAT+BUT_ICON_YSIZE && Button[0]>0){

		// 表示モード変更
		gui_taku_mode = COMMON_PLAY_MODE;

		// ActID変更
		gui_actid=tk->kyoku[gui_kyoku_index].act_count-1;

		// ----------------------------------------
		// tkクラスのアクション情報の最新化
		// ----------------------------------------
		tk->Check_Ply_ActTehai(gui_kyoku_index, gui_actid);

	}

	// ----------------------------------------
	// 場決めボタン
	// ----------------------------------------
	if( msx>BAGIME_X_STAT && msx<BAGIME_X_STAT+BUT_ICON_XSIZE && 
		msy>BAGIME_Y_STAT && msy<BAGIME_Y_STAT+BUT_ICON_YSIZE && Button[0]>0){

		// ビュー表示モード変更
		if( gui_taku_mode != COMMON_BAGIME_MODE){
			gui_taku_mode = COMMON_BAGIME_MODE;
		}else{
			gui_taku_mode = COMMON_PLAY_MODE;
		}

	}

	// ----------------------------------------
	// 卓結果ボタン
	// ----------------------------------------
	if( msx>TKEND_X_STAT && msx<TKEND_X_STAT+BUT_ICON_XSIZE && 
		msy>BAGIME_Y_STAT && msy<BAGIME_Y_STAT+BUT_ICON_YSIZE && Button[0]>0){

		// ビュー表示モード変更
		if( gui_taku_mode != COMMON_TAKURESULT_MODE){
			gui_taku_mode = COMMON_TAKURESULT_MODE;
		}else{
			gui_taku_mode = COMMON_PLAY_MODE;
		}

	}

	// ----------------------------------------
	// 席変更番号
	// ----------------------------------------
	// 席番号-1
	if( msx>VIEWER_SEKI_X_STAT && msx<VIEWER_SEKI_X_STAT+BUT_ICON_XSIZE*1 && 
		msy>VIEWER_SEKI_Y_STAT && msy<VIEWER_SEKI_Y_STAT+BUT_ICON_YSIZE && Button[0]>0){

		// 表示席番号の変更
		disp_down_tehai_pnum = (disp_down_tehai_pnum + 3) % 4;

	// 席番号+1
	}else if( msx>VIEWER_SEKI_X_STAT + BUT_ICON_XSIZE*1 && msx<VIEWER_SEKI_X_STAT+BUT_ICON_XSIZE*2 && 
		msy>VIEWER_SEKI_Y_STAT                    && msy<VIEWER_SEKI_Y_STAT+BUT_ICON_YSIZE && Button[0]>0){

		// 表示席番号の変更
		disp_down_tehai_pnum = (disp_down_tehai_pnum + 1) % 4;

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 検証モード・初期化
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::guiRunningInit(){

	// GUIモード初期化
	guiTakuInit();

}

/* ---------------------------------------------------------------------------------------------- */
// 検証モード・メイン
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::guiRunningMain(MJSTkinfo *tk){

	// マウス情報取得
	MouseStat();

	// ----------------------------------------
	// マウス開放
	// ----------------------------------------

	// マウスが押されていないなら、「マウス開放状態(mouse_push_flg=0)」とする
	if( Button[0]==0 && Button[1]==0 ){

		// マウスチェックフラグ無効化
		mouse_push_flg = 0;

		// クリック確認フラグ無効化
		act_push_flg = false;

	}

	// クリックされているなら
	if(  Button[0] > 0 && mouse_push_flg == 0){

		// ボタン確認
		chk_but(tk);

		// マウスチェックフラグ有効化
		mouse_push_flg = 1;

	}

	// ----------------------------------------
	// メイン処理
	// ----------------------------------------

	// フレームが超過数確認
	if( frame_count > AUTO_FRAME_COUNT_RUNNING ){

		// 終了ボタンでないなら
		if( gui_taku_mode != COMMON_END_CHECK_MODE && gui_taku_mode != COMMON_END_MODE){

			// クリックフラグ有効化
			act_push_flg = true;

			// フレーム初期化
			frame_count = 0;

		}else{

			// クリック確認フラグ無効化
			act_push_flg = false;

		}

	}else{

		// フレームカウント
		frame_count++;

	}

}

/* ---------------------------------------------------------------------------------------------- */
// クライアントモード・初期化
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::guiClientInit(MJSTkinfo *tk){

	// GUIモード初期化
	guiTakuInit();

}

/* ---------------------------------------------------------------------------------------------- */
// クライアントモード・メイン処理
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::guiClientMain(MJSTkinfo *tk){

	// マウス情報取得
	MouseStat();

	// ----------------------------------------
	// マウスのボタンが開放されているならば
	// ----------------------------------------

	// マウスが押されていないなら、「マウス開放状態(mouse_push_flg=0)」とする
	if( Button[0]==0 && Button[1]==0 ){

		// マウスチェックフラグ無効化
		mouse_push_flg = 0;

		// クリック確認フラグ無効化
		act_push_flg = false;

	}

	// ----------------------------------------
	// クライアントモードごとの処理：通常卓モード
	// ----------------------------------------
	if( cli_mode == GUI_MJAI_WAIT_TAKU_PLYACT){

		// -------------------------------
		// 自摸アクション待ち状態であれば
		// -------------------------------
		if( tk->stat == PLYACTTSUMO   || 
		    tk->stat == PLYRINSHAN    || 
		    tk->stat == PLYACTRIICH   ){ 

			// GUIモードの場合
			if( tk->ply_hum_mode == 1 && tk->ply_turn == HUM_PLY_SEKI_NUM ){

				// リーチ後モードでプレートが有効化でないなら、オート自摸処理
				if( ( gui_ply_tehai_mode == TEHAI_RIICHI_YUKO ) &&
				    ( plt_mode[PLT_KAN] == false && plt_mode[PLT_AGARI] == false ) ){

						// フレーム自動クリック処理(AUTO_FRAME_COUNT_RESULTだけ待ち時間)
						auto_frame_click_riichi(tk, 30);

				// それ以外はクリック確認
				}else{

					// ボタンの押下確認
					if(  Button[0] > 0 && mouse_push_flg == 0){

						// マウスチェックフラグ有効化
						mouse_push_flg = 1;

						// ボタン確認
						chk_but(tk);
						set_plt_naki_arinashi();

						// 自摸時処理
						guiClientSetPlyNormalActMain(tk);

					}

				}

			// PLYアクション又はCOM操作の場合
			}else{

				// ボタンの押下確認
				if( Button[0] > 0 && mouse_push_flg == 0){

					// マウスチェックフラグ有効化
					mouse_push_flg = 1;

					// ボタン確認
					chk_but(tk);
					// set_plt_naki_arinashi();

				}

				// フレーム自動クリック処理
				auto_frame_click(AUTO_FRAME_COUNT_CLIENT);
			}

		// -------------------------------
		// 捨牌アクション→鳴き確認
		// -------------------------------
		}else if( ( tk->stat == PLYACTSUTE      || 
		            tk->stat == PLYACTTSUMOGIRI ||
		            tk->stat == PLYACTNAKISUTE  ) && 
		          ( tk->ply_turn != HUM_PLY_SEKI_NUM) ){

			// GUIモードの場合
			if( tk->ply_hum_mode == 1){

				// 鳴きが可能ならば
				if ( plt_mode[PLT_PON]   == true ||
				     plt_mode[PLT_KAN]   == true ||
				     plt_mode[PLT_CHI]   == true ||
				     plt_mode[PLT_AGARI] == true ){

					// ボタンの押下確認
					if(  Button[0] > 0 && mouse_push_flg == 0){

						// マウスチェックフラグ有効化
						mouse_push_flg = 1;

						// ボタン確認
						chk_but(tk);
						set_plt_naki_arinashi();

						// 鳴き確認
						guiClientSetPlyNakiAct(tk);

					}

				// 鳴きが不可ならば
				}else{

					// ボタンの押下確認
					if( Button[0] > 0 && mouse_push_flg == 0){

						// マウスチェックフラグ有効化
						mouse_push_flg = 1;

						// ボタン確認
						chk_but(tk);
						set_plt_naki_arinashi();

					}

					// フレーム自動クリック処理
					auto_frame_click(AUTO_FRAME_COUNT_CLIENT);
				}

			// PLYアクション又はCOM操作の場合
			}else{

				// ボタンの押下確認
				if( Button[0] > 0 && mouse_push_flg == 0){

					// マウスチェックフラグ有効化
					mouse_push_flg = 1;

					// ボタン確認
					chk_but(tk);
					// set_plt_naki_arinashi();

				}

				// フレーム自動クリック処理
				auto_frame_click(AUTO_FRAME_COUNT_CLIENT);

			}

		// -------------------------------
		// 鳴き捨牌処理(自プレーヤ)
		// -------------------------------
		}else if( tk->stat == PLYACTPON  || 
		          tk->stat == PLYACTCHI  ){

			// GUI操作の場合
			if( tk->ply_hum_mode == 1 && tk->ply_turn == HUM_PLY_SEKI_NUM ){

				// ボタンの押下確認
				if( Button[0] > 0 && mouse_push_flg == 0 ){

					// マウスチェックフラグ有効化
					mouse_push_flg = 1;

					// ボタン確認
					chk_but(tk);
					set_plt_naki_arinashi();

					// 鳴き捨牌時処理
					guiClienSetPlyNakiSuteAct(tk);
				}

			// PLYアクション又はCOM操作の場合
			}else{
				// フレーム自動クリック処理
				auto_frame_click(AUTO_FRAME_COUNT_CLIENT);
			}

		// -------------------------------
		// 和了・流れ処理の場合
		// -------------------------------
		}else if( tk->stat == PLYACTRON  || 
		          tk->stat == PLYTSUMOAGARI ||
		          tk->stat == RYUKYOKU  ){

			// GUIモードの場合
			if ( tk->ply_hum_mode == 1){

				// ボタンの押下確認
				if(  Button[0] > 0 && mouse_push_flg == 0){

					// マウスチェックフラグ有効化
					mouse_push_flg = 1;

					// ボタン確認
					chk_but(tk);
					set_plt_naki_arinashi();

					// 次へボタンの確認
					set_plt_next();  

				}

			// PLYモードの場合
			}else{
				// フレーム自動クリック処理(AUTO_FRAME_COUNT_RESULTだけ待ち時間)
				auto_frame_click(AUTO_FRAME_COUNT_RESULT);
			}

		// -------------------------------
		// それ以外であれば
		// -------------------------------
		}else{

			// ボタンの押下確認
			if( Button[0] > 0 && mouse_push_flg == 0){

				// マウスチェックフラグ有効化
				mouse_push_flg = 1;

				// ボタン確認
				chk_but(tk);
				set_plt_naki_arinashi();

			}

			// フレーム自動クリック処理
			auto_frame_click(AUTO_FRAME_COUNT_CLIENT);
		}

	// ----------------------------------------
	// 画面遷移待ちの場合
	// ----------------------------------------
	}else if( cli_mode == GUI_MJAI_BAGIME       || 
	          cli_mode == GUI_MJAI_KYOKUEND     ||
	          cli_mode == GUI_MJAI_TAKURESULT   ||
	          cli_mode == GUI_MJAI_ERR_CONNECT  ||
	          cli_mode == GUI_MJAI_ERR_RES_MES  ){

		// GUIモードの場合
		if ( tk->ply_hum_mode == 1){

			// ボタンの押下確認
			if(  Button[0] > 0 && mouse_push_flg == 0){

				// マウスチェックフラグ有効化
				mouse_push_flg = 1;

				// ボタン確認
				chk_but(tk);
				// set_plt_naki_arinashi();

				// 次へボタンの確認
				set_plt_next();  

			}

		// PLYモードの場合
		}else{

			// ボタンの押下確認
			if(  Button[0] > 0 && mouse_push_flg == 0){

				// マウスチェックフラグ有効化
				mouse_push_flg = 1;

				// ボタン確認
				chk_but(tk);
				// set_plt_naki_arinashi();

			}

			// フレーム自動クリック処理(AUTO_FRAME_COUNT_RESULTだけ待ち時間)
			auto_frame_click(AUTO_FRAME_COUNT_RESULT);

		}

	// ----------------------------------------
	// それ以外
	// ----------------------------------------
	}else{

		// ボタンの押下確認
		if(  Button[0] > 0 && mouse_push_flg == 0){

			// マウスチェックフラグ有効化
			mouse_push_flg = 1;

			// ボタン確認
			chk_but(tk);
			set_plt_naki_arinashi();

		}

		// フレーム自動クリック処理
		auto_frame_click(AUTO_FRAME_COUNT_CLIENT);

	}

}

/* ---------------------------------------------------------------------------------------------- */
// GUI操作通常処理（メイン）
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::guiClientSetPlyNormalActMain(MJSTkinfo *tk){

	// プレーヤー通常アクション定義(mode:TEHAI_NORMAL)
	if( gui_ply_tehai_mode == TEHAI_NORMAL ){
		guiClientSetPlyNormalAct(tk);
	// リーチ宣言後の捨牌選択(mode:TEHAI_RIICHI_SUTEHAI)
	}else if( gui_ply_tehai_mode == TEHAI_RIICHI_SUTEHAI ){
		guiClientSetPlyRiichiSutehaiAct(tk);
	// リーチ有効後のアクション(自摸切り、自摸和了、暗槓)(mode:TEHAI_RIICHI_YUKO)
	}else if( gui_ply_tehai_mode == TEHAI_RIICHI_YUKO ){
		guiClientSetPlyRiichiYukoAct(tk);
	}

}

/* ---------------------------------------------------------------------------------------------- */
// GUI操作通常処理・プレーヤー通常アクション定義(mode:TEHAI_NORMAL)
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::guiClientSetPlyNormalAct(MJSTkinfo *tk){

	// ----------------------------------------
	// 手牌内の捨牌処理
	// ----------------------------------------
	if( msx > tehai_x && 
	    msx < tehai_x + (tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM]-1)*HAI_XSIZE + HAI_XSIZE &&
	    msy > tehai_y && 
	    msy < tehai_y + HAI_YSIZE ){

		// クリックフラグ有効化
		act_push_flg = true;

		// 手牌テーブルクリックフラグ有効化とアクション定義
		tk->ply_act = ACTSUTE;

		// 捨牌番号設定(マウス選択位置)
		tk->ply_tbl_hum_sutehai_statnum = (msx-tehai_x) / HAI_XSIZE;

		// プレート無効化
		plt_mode[PLT_RIICHI] = false;
		plt_mode[PLT_PON]    = false;
		plt_mode[PLT_KAN]    = false;
		plt_mode[PLT_CHI]    = false;
		plt_mode[PLT_AGARI]  = false;

	// ----------------------------------------
	// 自摸牌の捨牌処理
	// ----------------------------------------
	}else if( msx > tehai_x + (tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM]*HAI_XSIZE) + SPACE_XSIZE && 
			  msx < tehai_x + (tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM]*HAI_XSIZE) + SPACE_XSIZE + HAI_XSIZE &&
			  msy > tehai_y && 
			  msy < tehai_y + HAI_YSIZE ){

		// クリックフラグ有効化
		act_push_flg = true;

		// テーブルクリックフラグ有効化
		tk->ply_act = ACTTSUMOGIRI;

		// 捨牌番号設定
		tk->ply_tbl_hum_sutehai_statnum = tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM]; // 自摸牌

		// プレート無効化
		plt_mode[PLT_RIICHI] = false;
		plt_mode[PLT_PON]    = false;
		plt_mode[PLT_KAN]    = false;
		plt_mode[PLT_CHI]    = false;
		plt_mode[PLT_AGARI]  = false;

	// ----------------------------------------
	// 槓プレートが押されたなら
	// ----------------------------------------
	}else if( plt_mode[PLT_KAN] == true &&
	          msx > SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_KAN && 
		      msx < SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_KAN + PLT_ICON_XSIZE &&
		      msy > PLT_Y_STAT && 
		      msy < PLT_Y_STAT + PLT_ICON_YSIZE ){

		// 暗槓牌が1枚ならば
		if ( naki_ankan_hai_count == 1 && naki_kakan_hai_count == 0 ){

			// クリックフラグ有効化
			act_push_flg = true;

			// HUMプレーヤーのアクション定義
			tk->ply_act = ACTANKAN;
			tk->ply_naki_idx[HUM_PLY_SEKI_NUM] = naki_ankan_hai[0];

		// 加槓牌が1枚ならば
		}else if( naki_ankan_hai_count == 0 && naki_kakan_hai_count == 1 ){

			// クリックフラグ有効化
			act_push_flg = true;

			// HUMプレーヤーのアクション定義
			tk->ply_act = ACTKAKAN;
			tk->ply_naki_idx[HUM_PLY_SEKI_NUM] = naki_kakan_hai[0];

			// 加槓牌が赤牌ならば
			if ( tk->ply_naki_idx[HUM_PLY_SEKI_NUM] == 5 && tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][0] > 0){
				tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = 1;
			}else if ( tk->ply_naki_idx[HUM_PLY_SEKI_NUM] == 15 && tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][1] > 0){
				tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = 1;
			}else if ( tk->ply_naki_idx[HUM_PLY_SEKI_NUM] == 25 && tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][2] > 0){
				tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = 1;
			}else{
				tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = 0;
			}

		// 候補牌が複数ある場合には
		}else{

			// ----------------------------------------
			// GUI手牌モードの変更
			// ----------------------------------------
			gui_ply_tehai_mode = TEHAI_ANKAN_KAKAN_SELECT;

		}

		// ----------------------------------------
		// プレート無効化
		// ----------------------------------------
		plt_mode[PLT_RIICHI] = false;
		plt_mode[PLT_PON]    = false;
		plt_mode[PLT_KAN]    = false;
		plt_mode[PLT_CHI]    = false;
		plt_mode[PLT_AGARI]  = false;

	// ----------------------------------------
	// リーチプレートが押されたなら
	// ----------------------------------------
	}else if( plt_mode[PLT_RIICHI] == true &&
	          msx > SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_RIICHI && 
		      msx < SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_RIICHI + PLT_ICON_XSIZE &&
		      msy > PLT_Y_STAT && 
		      msy < PLT_Y_STAT + PLT_ICON_YSIZE ){

		// クリックフラグ有効化
		act_push_flg = true;

		// HUMプレーヤーのアクション定義
		tk->ply_act = ACTRIICH;

		// GUI手牌モードの変更
		gui_ply_tehai_mode = TEHAI_RIICHI_SUTEHAI;

		// プレート無効化
		plt_mode[PLT_RIICHI] = false;
		plt_mode[PLT_PON]    = false;
		plt_mode[PLT_KAN]    = false;
		plt_mode[PLT_CHI]    = false;
		plt_mode[PLT_AGARI]  = false;

	// ----------------------------------------
	// 和了プレートが押されたなら
	// ----------------------------------------
	}else if( plt_mode[PLT_AGARI] == true &&
		      msx > SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_AGARI && 
		      msx < SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_AGARI + PLT_ICON_XSIZE &&
		      msy > PLT_Y_STAT && 
		      msy < PLT_Y_STAT + PLT_ICON_YSIZE ){

		// クリックフラグ有効化
		act_push_flg = true;

		// HUMプレーヤーのアクション定義
		tk->ply_act = ACTTSUMOAGARI;

		// プレート無効化
		plt_mode[PLT_RIICHI] = false;
		plt_mode[PLT_PON]    = false;
		plt_mode[PLT_KAN]    = false;
		plt_mode[PLT_CHI]    = false;
		plt_mode[PLT_AGARI]  = false;

	// ----------------------------------------
	// 他の場所が押された場合は、クリックフラグを無効化する
	// ----------------------------------------
	}else{

		// クリックフラグ無効化
		act_push_flg = false;

	}

}

/* ---------------------------------------------------------------------------------------------- */
// GUI操作通常処理・リーチ宣言後の捨牌選択(mode:TEHAI_RIICHI_SUTEHAI)
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::guiClientSetPlyRiichiSutehaiAct(MJSTkinfo *tk){

	// ----------------------------------------
	// 手牌内の捨牌処理
	// ----------------------------------------
	if( msx > tehai_x && 
	    msx < tehai_x + (tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM]-1)*HAI_XSIZE + HAI_XSIZE &&
	    msy > tehai_y && 
	    msy < tehai_y + HAI_YSIZE ){

		// リーチ時の選択捨牌のシャンテンが0であるなら
		if(tk->ply_act_tehai_can_sute_tbl[HUM_PLY_SEKI_NUM][(msx-tehai_x)/HAI_XSIZE] == true){

			// クリックフラグ有効化
			act_push_flg = true;

			// 手牌テーブルクリックフラグ有効化とアクション定義
			tk->ply_act = ACTSUTE;

			// 捨牌番号設定(マウス選択位置)
			tk->ply_tbl_hum_sutehai_statnum = (msx-tehai_x) / HAI_XSIZE;        // 手牌選択牌

			// GUI手牌モードの変更
			gui_ply_tehai_mode = TEHAI_RIICHI_YUKO;

		}

	// ----------------------------------------
	// 自摸牌でクリックしたなら捨牌を定義する
	// ----------------------------------------
	}else if( msx > tehai_x + (tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM]*HAI_XSIZE) + SPACE_XSIZE && 
			  msx < tehai_x + (tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM]*HAI_XSIZE) + SPACE_XSIZE + HAI_XSIZE &&
			  msy > tehai_y && 
			  msy < tehai_y + HAI_YSIZE ){

		// リーチ時の選択捨牌のシャンテンが0であるなら
		if( tk->ply_act_tsumo_can_sute[HUM_PLY_SEKI_NUM] == true ){

			// クリックフラグ有効化
			act_push_flg = true;

			// テーブルクリックフラグ有効化
			tk->ply_act = ACTTSUMOGIRI;

			// 捨牌番号設定
			tk->ply_tbl_hum_sutehai_statnum = (tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM]); // 自摸牌

			// GUI手牌モードの変更
			gui_ply_tehai_mode = TEHAI_RIICHI_YUKO;

		}
	}

}

/* ---------------------------------------------------------------------------------------------- */
// GUI操作通常処理・リーチ有効後のアクション(自摸切り、自摸和了、暗槓)(mode:TEHAI_RIICHI_YUKO)
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::guiClientSetPlyRiichiYukoAct(MJSTkinfo *tk){

	// ----------------------------------------
	// 自摸牌の捨牌処理
	// ----------------------------------------
	if( msx > tehai_x + (tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM]*HAI_XSIZE) + SPACE_XSIZE && 
		msx < tehai_x + (tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM]*HAI_XSIZE) + SPACE_XSIZE + HAI_XSIZE &&
		msy > tehai_y && 
		msy < tehai_y + HAI_YSIZE ){

		// クリックフラグ有効化
		act_push_flg = true;

		// テーブルクリックフラグ有効化
		tk->ply_act = ACTTSUMOGIRI;

		// 捨牌番号設定
		tk->ply_tbl_hum_sutehai_statnum = tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM]; // 自摸牌

	// ----------------------------------------
	// 槓プレートが押されたなら
	// ----------------------------------------
	}else if( plt_mode[PLT_KAN] == true &&
	          msx > SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_KAN && 
		      msx < SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_KAN + PLT_ICON_XSIZE &&
		      msy > PLT_Y_STAT && 
		      msy < PLT_Y_STAT + PLT_ICON_YSIZE ){

		// クリックフラグ有効化
		act_push_flg = true;

		// 暗槓牌ならば
		if ( naki_ankan_hai_count > 0){
			// HUMプレーヤーのアクション定義
			tk->ply_act = ACTANKAN;
			tk->ply_naki_idx[HUM_PLY_SEKI_NUM] = naki_ankan_hai[0];
		}

		// プレート無効化
		plt_mode[PLT_RIICHI] = false;
		plt_mode[PLT_PON]    = false;
		plt_mode[PLT_KAN]    = false;
		plt_mode[PLT_CHI]    = false;
		plt_mode[PLT_AGARI]  = false;

		// GUI手牌モードの変更
		// gui_ply_tehai_mode = TEHAI_ANKAN_KAKAN_SELECT;

	// ----------------------------------------
	// 和了プレートが押されたなら
	// ----------------------------------------
	}else if( plt_mode[PLT_AGARI] == true &&
		      msx > SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_AGARI && 
		      msx < SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_AGARI + PLT_ICON_XSIZE &&
		      msy > PLT_Y_STAT && 
		      msy < PLT_Y_STAT + PLT_ICON_YSIZE ){

		// クリックフラグ有効化
		act_push_flg = true;

		// 手牌テーブルクリックフラグ有効化とアクション定義
		tk->ply_act = ACTTSUMOAGARI;

		// プレート無効化
		plt_mode[PLT_RIICHI] = false;
		plt_mode[PLT_PON]    = false;
		plt_mode[PLT_KAN]    = false;
		plt_mode[PLT_CHI]    = false;
		plt_mode[PLT_AGARI]  = false;

	// ----------------------------------------
	// 他の場所が押された場合は、クリックフラグを無効化する
	// ----------------------------------------
	}else{

		// クリックフラグ無効化
		act_push_flg = false;

	}

}

/* ---------------------------------------------------------------------------------------------- */
// GUI操作通常処理・プレーヤー暗槓アクション定義(mode:TEHAI_ANKAN_KAKAN_SELECT)
/* ---------------------------------------------------------------------------------------------- */




/* ---------------------------------------------------------------------------------------------- */
// GUI操作通常処理・プレーヤー個別鳴き確認(メイン)
/* ---------------------------------------------------------------------------------------------- */




/* ---------------------------------------------------------------------------------------------- */
// GUI操作通常処理・プレーヤー個別鳴きアクション定義(mode:TEHAI_NORMAL || mode:TEHAI_RIICHI_YUKO)
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::guiClientSetPlyNakiAct(MJSTkinfo *tk){

	// ----------------------------------------
	// 「次へ」プレートが押されている場合には
	// ----------------------------------------
	if( msx > SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_NEXT && 
	    msx < SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_NEXT + PLT_ICON_XSIZE &&
	    msy > PLT_Y_STAT && 
	    msy < PLT_Y_STAT + PLT_ICON_YSIZE ){

		// クリックフラグ有効化
		act_push_flg = true;

		// HUMプレーヤーのアクション定義
		tk->ply_act_naki[HUM_PLY_SEKI_NUM] = ACTNONAKI;

		// プレート無効化
		plt_mode[PLT_RIICHI] = false;
		plt_mode[PLT_PON]    = false;
		plt_mode[PLT_KAN]    = false;
		plt_mode[PLT_CHI]    = false;
		plt_mode[PLT_AGARI]  = false;

	// ----------------------------------------
	// 和了プレートが押されたなら
	// ----------------------------------------
	}else if( plt_mode[PLT_AGARI] == true &&
		      msx > SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_AGARI && 
		      msx < SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_AGARI + PLT_ICON_XSIZE &&
		      msy > PLT_Y_STAT && 
		      msy < PLT_Y_STAT + PLT_ICON_YSIZE ){

		// クリックフラグ有効化
		act_push_flg = true;

		// HUMプレーヤーのアクション定義
		tk->ply_act_naki[HUM_PLY_SEKI_NUM] = ACTRON;

		// プレート無効化
		plt_mode[PLT_RIICHI] = false;
		plt_mode[PLT_PON]    = false;
		plt_mode[PLT_KAN]    = false;
		plt_mode[PLT_CHI]    = false;
		plt_mode[PLT_AGARI]  = false;

	// ----------------------------------------
	// ポンプレートが押されたなら
	// ----------------------------------------
	}else if( plt_mode[PLT_PON] == true &&
		      msx > SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_PON && 
		      msx < SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_PON + PLT_ICON_XSIZE &&
		      msy > PLT_Y_STAT && 
		      msy < PLT_Y_STAT + PLT_ICON_YSIZE ){

		// クリックフラグ有効化
		act_push_flg = true;

		// HUMプレーヤーのアクション定義
		tk->ply_act_naki[HUM_PLY_SEKI_NUM] = ACTPON;

		// プレート無効化
		plt_mode[PLT_RIICHI] = false;
		plt_mode[PLT_PON]    = false;
		plt_mode[PLT_KAN]    = false;
		plt_mode[PLT_CHI]    = false;
		plt_mode[PLT_AGARI]  = false;

	// ----------------------------------------
	// 槓プレートが押されたなら
	// ----------------------------------------
	}else if( plt_mode[PLT_KAN] == true &&
		      msx > SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_KAN && 
		      msx < SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_KAN + PLT_ICON_XSIZE &&
		      msy > PLT_Y_STAT && 
		      msy < PLT_Y_STAT + PLT_ICON_YSIZE ){

		// クリックフラグ有効化
		act_push_flg = true;

		// HUMプレーヤーのアクション定義
		tk->ply_act_naki[HUM_PLY_SEKI_NUM] = ACTMINKAN;

		// プレート無効化
		plt_mode[PLT_RIICHI] = false;
		plt_mode[PLT_PON]    = false;
		plt_mode[PLT_KAN]    = false;
		plt_mode[PLT_CHI]    = false;
		plt_mode[PLT_AGARI]  = false;

	// ----------------------------------------
	// チープレートが押されたなら
	// ----------------------------------------
	}else if( plt_mode[PLT_CHI] == true &&
		      msx > SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_CHI && 
		      msx < SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_CHI + PLT_ICON_XSIZE &&
		      msy > PLT_Y_STAT && 
		      msy < PLT_Y_STAT + PLT_ICON_YSIZE ){
/*
		// チー候補牌が2枚以上であれば、牌選択処理を行う
		if (chihai_count > 1){

			// モード変更
			gui_ply_tehai_mode = TEHAI_CHI_SELECT;

		// チー候補牌が1枚であれば、自動チー処理
		}else{
*/
			// クリックフラグ有効化
			act_push_flg = true;

			// HUMプレーヤーのアクション定義
			tk->ply_act_naki[HUM_PLY_SEKI_NUM] = ACTCHI;

			// 鳴牌設定
			// tk->ply_naki_hai[HUM_PLY_SEKI_NUM] = ;

			// 赤枚数定義

			// チーINDEX牌定義
			tk->ply_naki_idx[HUM_PLY_SEKI_NUM] = chi_idx_hai[0];

			// 赤枚数定義
			tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = chi_aka_count[0];

			// プレート無効化
			plt_mode[PLT_RIICHI] = false;
			plt_mode[PLT_PON]    = false;
			plt_mode[PLT_KAN]    = false;
			plt_mode[PLT_CHI]    = false;
			plt_mode[PLT_AGARI]  = false;

	// ----------------------------------------
	// それ以外の処理は無効化
	// ----------------------------------------
	}else{

		// クリックフラグ無効化
		act_push_flg = false;

	}

}

/* ---------------------------------------------------------------------------------------------- */
// GUI操作通常処理・プレーヤーチー牌アクション定義(mode:TEHAI_CHI_SELECT)
/* ---------------------------------------------------------------------------------------------- */




/* ---------------------------------------------------------------------------------------------- */
// GUI操作通常処理・プレーヤー鳴き後の捨牌処理
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::guiClienSetPlyNakiSuteAct(MJSTkinfo *tk){

	// ----------------------------------------
	// 手牌内の捨牌処理
	// ----------------------------------------
	if( msx > tehai_x && 
	    msx < tehai_x + (tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM]-1)*HAI_XSIZE + HAI_XSIZE &&
	    msy > tehai_y && 
	    msy < tehai_y + HAI_YSIZE ){

		// 捨牌番号設定(マウス選択位置)
		tk->ply_tbl_hum_sutehai_statnum = (msx-tehai_x) / HAI_XSIZE;

		// 鳴き捨て可能なら
		if(tk->ply_act_tehai_can_sute_tbl[HUM_PLY_SEKI_NUM][tk->ply_tbl_hum_sutehai_statnum] == true){

			// クリックフラグ有効化
			act_push_flg = true;

			// 手牌テーブルクリックフラグ有効化とアクション定義
			tk->ply_act = ACTNAKISUTE;

			// HUMプレーヤーの鳴きアクション定義
			tk->ply_act_naki[HUM_PLY_SEKI_NUM]       = ACTNONAKI;
			tk->ply_naki_idx[HUM_PLY_SEKI_NUM]       = 0;
			tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = 0;
		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// クライアントモード・フレーム自動カウント
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::auto_frame_click(int tmp_coint_max){

	// フレームが超過数確認
	if( frame_count > tmp_coint_max ){

		// 終了ボタンでないなら
		if( gui_taku_mode != COMMON_END_CHECK_MODE && gui_taku_mode != COMMON_END_MODE){

			// クリックフラグ有効化
			act_push_flg = true;

			// フレーム初期化
			frame_count = 0;

		}else{

			// クリック確認フラグ無効化
			act_push_flg = false;

		}

	}else{

		// フレームカウント
		frame_count++;

	}

}

/* ---------------------------------------------------------------------------------------------- */
// クライアントモード・フレーム自動カウント(リーチ用)
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::auto_frame_click_riichi(MJSTkinfo *tk, int tmp_coint_max){

	// フレームが超過数確認
	if( frame_count > tmp_coint_max ){

		// 終了ボタンでないなら
		if( gui_taku_mode != COMMON_END_CHECK_MODE && gui_taku_mode != COMMON_END_MODE){

			// クリックフラグ有効化
			act_push_flg = true;

			// テーブルクリックフラグ有効化
			tk->ply_act = ACTTSUMOGIRI;

			// 捨牌番号設定
			tk->ply_tbl_hum_sutehai_statnum = tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM]; // 自摸牌

			// フレーム初期化
			frame_count = 0;

		}else{

			// クリック確認フラグ無効化
			act_push_flg = false;

		}

	}else{

		// フレームカウント
		frame_count++;

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 各ボタンの状態確認
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::chk_but(MJSTkinfo *tk){

	// ----------------------------------------
	// クライアントモード
	// ----------------------------------------
	if ( gui_main_stat == GUI_CLIENT ){

		// 終了ボタンが押されたら
		if( msx > QUIT_BUT_X_STAT && 
		    msx < QUIT_BUT_X_STAT + BUT_ICON_XSIZE && 
		    msy > BUT02_Y_STAT && 
		    msy < BUT02_Y_STAT + BUT_ICON_YSIZE){

			// GUIボタンの有効化
			but_push_flg = true;

			// クリックフラグ無効化(ボタンが押された場合は常にfalse)
			act_push_flg = false;

			// モード変更
			if(gui_taku_mode != COMMON_END_CHECK_MODE){

				// 終了確認ステータス
				gui_taku_mode = COMMON_END_CHECK_MODE;

			}else if(gui_taku_mode == COMMON_END_CHECK_MODE){

				// 終了処理
				cli_mode = GUI_MJAI_DISCONNECT;

			}

		// ボタンが押されていないなら
		}else{

			// GUIボタン無効化
			but_push_flg = false;

		}

	// ----------------------------------------
	// 卓モード専用処理
	// ----------------------------------------
	}else{

		// 終了ボタンが押されたら
		if( msx > QUIT_BUT_X_STAT && 
		    msx < QUIT_BUT_X_STAT + BUT_ICON_XSIZE && 
		    msy > BUT02_Y_STAT && 
		    msy < BUT02_Y_STAT + BUT_ICON_YSIZE){

			// GUIボタンの有効化
			but_push_flg = true;

			// クリックフラグ無効化(ボタンが押された場合は常にfalse)
			act_push_flg = false;

			// モード変更
			if(gui_taku_mode != COMMON_END_CHECK_MODE){
				// 終了確認ステータス
				gui_taku_mode = COMMON_END_CHECK_MODE;
			}else if(gui_taku_mode == COMMON_END_CHECK_MODE){
				// 終了処理
				gui_taku_mode = COMMON_END_MODE;
			}

		// TKINFO情報ボタンが押されたら
		} else if( msx > TKINFO_BUT_X_STAT && 
		    msx < TKINFO_BUT_X_STAT + BUT_ICON_XSIZE && 
		    msy > BUT02_Y_STAT && 
		    msy < BUT02_Y_STAT + BUT_ICON_YSIZE){

			// GUIボタンの有効化
			but_push_flg = true;

			// クリックフラグ無効化(ボタンが押された場合は常にfalse)
			act_push_flg = false;

			// モード変更
			if(gui_taku_mode == COMMON_TKINFO_MODE){
				// 通常モードに戻す
				gui_taku_mode = COMMON_PLAY_MODE;
			}else{
				// ACT手牌情報表示モード
				gui_taku_mode = COMMON_TKINFO_MODE;
			}

		// PLYINFO_BUTが押されたら
		}else if( msx > PLYINFO_BUT_X_STAT && 
			      msx < PLYINFO_BUT_X_STAT + BUT_ICON_XSIZE && 
			      msy > BUT02_Y_STAT && 
			      msy < BUT02_Y_STAT + BUT_ICON_YSIZE){

			// GUIボタンの有効化
			but_push_flg = true;

			// クリックフラグ無効化(ボタンが押された場合は常にfalse)
			act_push_flg = false;

			// モード変更
			if(gui_taku_mode == GAME_PLY_INFO_MODE){
				// 通常モードに戻す
				gui_taku_mode = COMMON_PLAY_MODE;
			}else{
				// ACT手牌情報表示モード
				gui_taku_mode = GAME_PLY_INFO_MODE;
			}

		// ボタンが押されていないなら
		}else{

			// GUIボタン無効化
			but_push_flg = false;

		}

	}
}

/* ---------------------------------------------------------------------------------------------- */
// 次へプレート押下確認
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::set_plt_next(){

	// ----------------------------------------
	// 次へプレートが押されたら
	// ----------------------------------------

	// クリックフラグ有効化
	act_push_flg = true;

}

/* ---------------------------------------------------------------------------------------------- */
// 「鳴有/鳴無」プレートの表示変更
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::set_plt_naki_arinashi(){

	// ----------------------------------------
	// 「鳴有/鳴無」プレートが押されたら
	// ----------------------------------------
	if( msx > PLT_NAKIARI_X_STAT && 
		msx < PLT_NAKIARI_X_STAT + PLT_ICON_XSIZE &&
		msy > PLT_Y_STAT && 
		msy < PLT_Y_STAT + PLT_ICON_YSIZE ){

		// 値変更
		if (plt_nakiari_flg == true){
			plt_nakiari_flg = false;
		}else{
			plt_nakiari_flg = true;
		}

	}

	// クリックフラグ無効化(ボタンが押された場合は常にfalse)
	act_push_flg = false;
}

/* ---------------------------------------------------------------------------------------------- */
// 設定モード：初期化処理
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::guiSettingInit(){

	// モード初期化
	set_mode = SETTING_INFO_MODE;

}

/* ---------------------------------------------------------------------------------------------- */
// 設定モード：メイン処理
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::guiSetting(){

	// マウス情報取得
	MouseStat();

	// ----------------------------------------
	// マウス開放
	// ----------------------------------------

	// マウスが押されていないなら、「マウス開放状態(mouse_push_flg=0)」とする
	if( Button[0] == 0 && Button[1] == 0 ){
		mouse_push_flg = 0;
	}

	// ----------------------------------------
	// ボタンが押された場合の処理
	// ----------------------------------------

	// マウスが押されたなら
	if( Button[0] > 0 && mouse_push_flg == 0){

		// マウスチェックフラグ有効化
		mouse_push_flg=1;

		// ボタン1が押されたら
		if( msx > SETTING_X_START && 
			msx < SETTING_X_START + BUT_ICON_XSIZE &&
			msy > SETTING_Y_START && 
			msy < SETTING_Y_START + BUT_ICON_YSIZE ){

			// モード変更
			set_mode = SETTING_FILENAME_MJAI_MODE;

		// ボタン2が押されたら
		}else if( msx > SETTING_X_START && 
			      msx < SETTING_X_START + BUT_ICON_XSIZE  &&
			      msy > SETTING_Y_START+1*SETTING_Y_RANGE && 
			      msy < SETTING_Y_START+1*SETTING_Y_RANGE + BUT_ICON_YSIZE ){

			// モード変更
			set_mode = SETTING_FILENAME_MJSCORE_MODE;

		// 終了ボタンが押されたら
		}else if( msx > SETTING_X_START && 
			      msx < SETTING_X_START + BUT_ICON_XSIZE &&
			      msy > SETTING_ENDBUT_Y_START && 
			      msy < SETTING_ENDBUT_Y_START + BUT_ICON_YSIZE ){

			// メインステータス変更
			gui_main_stat = GUI_SETTING_POST;

		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// ソース終了
/* ---------------------------------------------------------------------------------------------- */
