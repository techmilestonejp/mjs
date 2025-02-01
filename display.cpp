/* ---------------------------------------------------------------------------------------------- 
 * 
 * プログラム概要 ： さくら麻雀(Ver0.1.2.1：開発版)
 * バージョン     ： 0.1.2.1.234(表示牌(open_haiparts)一覧表示)
 * プログラム名   ： mjs.exe
 * ファイル名     ： display.cpp
 * クラス名       ： MJSDisplay
 * 処理概要       ： 画面表示処理クラス
 * Ver0.0.8作成日 ： 2012/03/17 13:21:58
 * Ver0.1.0作成日 ： 2022/05/03 18:50:06
 * Ver0.1.1作成日 ： 2022/06/30 21:19:01
 * Ver0.1.2作成日 ： 2022/08/31 22:19:54
 * 最終更新日     ： 2025/02/01 09:57:37
 * 
 * Copyright (c) 2010-2025 TechMileStoraJP, All rights reserved.
 * 
 * ---------------------------------------------------------------------------------------------- */

#include "display.h"

/* ---------------------------------------------------------------------------------------------- */
// 前処理
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplayInit(){

	// ----------------------------------------
	// クラス定義
	// ----------------------------------------

	 // パーツ表示クラス初期化
	dparts = new MJSDisplayParts;

	// ----------------------------------------
	// クラス初期化処理
	// ----------------------------------------

	// クラス初期化
	dparts->DispPartsInit();

	// DXライブラリ画面初期化処理
	if (dparts->DispPartsFrameInit() != 0){

	}

	// DXライブラリ初期化
	if (dparts->DispPartsLibInit() != 0){

	}

	// ----------------------------------------
	// 画面表示設定
	// ----------------------------------------

	// デバグ情報の表示
	if(DISP_DEBUG_INFO == 0){
		disp_debug_info_mode = false;
	}else{
		disp_debug_info_mode = true;
	}

}

/* ---------------------------------------------------------------------------------------------- */
// 後処理 
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplayPost(){

	// ----------------------------------------
	// DXライブラリ終了
	// ----------------------------------------
	dparts->DispPartsLibPost();

}

/* ---------------------------------------------------------------------------------------------- */
// テスト用表示
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplaySampleTitle(MJSTkinfo *tk, MJSGui *gui, float mFps, int total_frame_count, int ver1, int ver2, int ver3, int ver4, int ver5){

	// ----------------------------------------
	// 変数定義
	// ----------------------------------------
	tk->kyoku_index = 0;
	tk->kyoku[tk->kyoku_index].doracount     = 1;
	tk->kyoku[tk->kyoku_index].dora[0]       = 31;
	tk->kyoku[tk->kyoku_index].dora_aka[0]   = false;
	tk->kyoku[tk->kyoku_index].dora_actid[0] = 0;

	// ----------------------------------------
	// 初期描画処理
	// ----------------------------------------
	dparts->DispPartsClearDraw();

	// ----------------------------------------
	// パーツ表示
	// ----------------------------------------
	dparts->DispBunner(ver1, ver2, ver3, ver4, ver5);                                     // バナー
	dparts->DispMousepoint(5, 750, gui->msx, gui->msy, gui->Button[0], gui->Button[1]);   // マウス位置
	dparts->DispFps(670, 750, mFps, total_frame_count, 0);                                // FPS

	// ドラ表示
	dparts->DispDora(DORA_XSIZE, SPACE_YSIZE, 
	                 tk->kyoku[tk->kyoku_index].doracount, 
	                 tk->kyoku[tk->kyoku_index].dora, 
	                 tk->kyoku[tk->kyoku_index].dora_aka,
	                 tk->kyoku[tk->kyoku_index].dora_actid,
	                 0);

	// プレート表示
	dparts->DispPltline(SPACE_XSIZE, PLT_Y_STAT, PLT_ICON_XSIZE+SPACE_XSIZE, gui->plt_mode);

	// プレート鳴有/鳴無
	dparts->DispPltNakiAriNashi(PLT_NAKIARI_X_STAT, PLT_Y_STAT, gui->plt_nakiari_flg);

	// ゲームモードのボタン表示
	// dparts->DispGameModeButton();
	dparts->DispInfoButton(THINFO_BUT_X_STAT, TKINFO_BUT_X_STAT, PLYINFO_BUT_X_STAT, QUIT_BUT_X_STAT, BUT02_Y_STAT);

	// ----------------------------------------
	// 裏画面を表画面に反映
	// ----------------------------------------
	dparts->DispPartsFlip();

}

/* ---------------------------------------------------------------------------------------------- */
// オープニング画面
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplayOpening(MJSGui *gui, float mFps, int total_frame_count, int ver1, int ver2, int ver3, int ver4, int ver5){

	// ----------------------------------------
	// 初期描画処理
	// ----------------------------------------
	dparts->DispPartsClearDraw();

	// ----------------------------------------
	// パーツ表示
	// ----------------------------------------

	// マウスポイント
	dparts->DispMousepoint(SPACE_XSIZE, 750, gui->msx, gui->msy, gui->Button[0], gui->Button[1]);

	// FPS
	dparts->DispFps(670, 750, mFps, total_frame_count, gui->frame_count);

	// タイトル表示
	dparts->DispOpeningTitle(ver1, ver2, ver3, ver4, ver5);

	// ----------------------------------------
	// 00:設定画面
	// ----------------------------------------
	dparts->DispButton(OPENING_BUT01_X_START,  OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*0,   PARTS_BUT_BLUE);
	DrawFormatString(OPENING_BUT01_X_START+50, OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*0+8, GetColor(255,255,255),  "設定");

	// ----------------------------------------
	// 01:牌譜面読込(ビューワーモード：MJAIログ)
	// ----------------------------------------
	dparts->DispButton(OPENING_BUT01_X_START,  OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*1,   PARTS_BUT_BLUE);
	DrawFormatString(OPENING_BUT01_X_START+50, OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*1+8, GetColor(255,255,255),  "牌譜読込：MJAIログ");

	// ----------------------------------------
	// 02:牌譜面読込(ビューワーモード：東風荘ログ)
	// ----------------------------------------
	dparts->DispButton(OPENING_BUT01_X_START,  OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*2,   PARTS_BUT_BLUE);
	DrawFormatString(OPENING_BUT01_X_START+50, OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*2+8, GetColor(255,255,255),  "牌譜読込：東風荘ログ");

	// ----------------------------------------
	// 03:4COM対決・自摸テーブル読込
	// ----------------------------------------
	dparts->DispButton(OPENING_BUT01_X_START,  OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*3,   PARTS_BUT_BLUE);
	DrawFormatString(OPENING_BUT01_X_START+50, OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*3+8, GetColor(255,255,255),  "4COM対決・一局モード：牌譜読込");

	// ----------------------------------------
	// 04:4COM対決・シード値ランダム
	// ----------------------------------------
	dparts->DispButton(OPENING_BUT01_X_START,  OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*4,   PARTS_BUT_BLUE);
	DrawFormatString(OPENING_BUT01_X_START+50, OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*4+8, GetColor(255,255,255),  "4COM対決・一局モード：ランダム自摸(時間変数)");

	// ----------------------------------------
	// 05:HUM対決・一局対戦・自摸テーブル読込
	// ----------------------------------------
	dparts->DispButton(OPENING_BUT01_X_START,  OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*5,   PARTS_BUT_GREEN);
	DrawFormatString(OPENING_BUT01_X_START+50, OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*5+8, GetColor(255,255,255),  "HUM対決・一局モード：牌譜読込");

	// ----------------------------------------
	// 06:HUM対決・東風戦モード・シード値固定
	// ----------------------------------------
	dparts->DispButton(OPENING_BUT01_X_START,  OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*6,   PARTS_BUT_GREEN);
	DrawFormatString(OPENING_BUT01_X_START+50, OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*6+8, GetColor(255,255,255),  "HUM対決・東風戦モード：ランダム自摸(固定値)");

	// ----------------------------------------
	// 07:HUM対決・東風戦モード・シード値ランダム
	// ----------------------------------------
	dparts->DispButton(OPENING_BUT01_X_START,  OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*7,   PARTS_BUT_GREEN);
	DrawFormatString(OPENING_BUT01_X_START+50, OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*7+8, GetColor(255,255,255),  "HUM対決・東風戦モード：ランダム自摸(時間変数)");

	// ----------------------------------------
	// 08:MJAIクライアント(GUIモード)
	// ----------------------------------------
	dparts->DispButton(OPENING_BUT01_X_START,  OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*8,   PARTS_BUT_BLUE);
	DrawFormatString(OPENING_BUT01_X_START+50, OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*8+8, GetColor(255,255,255), "MJAIクライアント：GUIモード");

	// ----------------------------------------
	// 09:MJAIクライアント(Plyモード)
	// ----------------------------------------
	dparts->DispButton(OPENING_BUT01_X_START,  OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*9,   PARTS_BUT_BLUE);
	DrawFormatString(OPENING_BUT01_X_START+50, OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*9+8, GetColor(255,255,255), "MJAIクライアント：Plyモード");


	// ----------------------------------------
	// 10:検証モード・ACTID_MAX
	// ----------------------------------------
	dparts->DispButton(OPENING_BUT01_X_START,  OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*10,   PARTS_BUT_YELLOW);
	DrawFormatString(OPENING_BUT01_X_START+50, OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*10+8, GetColor(255,255,255),  "検証モード：局ID無限モード");

	// ----------------------------------------
	// 11:検証モード・東風戦
	// ----------------------------------------
	dparts->DispButton(OPENING_BUT01_X_START,  OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*11,   PARTS_BUT_YELLOW);
	DrawFormatString(OPENING_BUT01_X_START+50, OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*11+8, GetColor(255,255,255),  "検証モード：東風戦モード");

	// ----------------------------------------
	// 裏画面を表画面に反映
	// ----------------------------------------
	dparts->DispPartsFlip();

}

/* ---------------------------------------------------------------------------------------------- */
// 卓表示(ゲームモード)のメイン処理
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplayTaku(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui, float mFps, int total_frame_count, int ver1, int ver2, int ver3, int ver4, int ver5){

	// ----------------------------------------
	// 初期描画処理
	// ----------------------------------------
	dparts->DispPartsClearDraw();

	// ----------------------------------------
	// パーツ表示
	// ----------------------------------------

	// バナー
	dparts->DispBunner(ver1, ver2, ver3, ver4, ver5);

	// マウスポイント
	dparts->DispMousepoint(SPACE_XSIZE, 750, gui->msx, gui->msy, gui->Button[0], gui->Button[1]);

	// FPS
	dparts->DispFps(670, 750, mFps, total_frame_count, gui->frame_count);

	// ----------------------------------------
	// ステータスごとのパーツ表示
	// ----------------------------------------

	// ステータスごとのパーツ表示
	switch(tk->stat){

		// 卓開始
		case TAKUSTART:
			// 表示処理は無し
		break;

		// 場決め
		case BAGIME:
			// 場決め情報
			DisplayBagime(tk,gui);
		break;

		// 局開始
		case KYOKUSTART:
			// 表示処理は無し
		break;

		// 局終了
		case KYOKUEND:
			// 表示処理は無し
		break;

		// 卓終了
		case TAKUEND:
			// 表示処理は無し
		break;

		// 局結果表示
		case KYOKURESULT:

			// 局情報
			DispKyokuInfo(tk,tk->kyoku_index);

			// ドラ
			dparts->DispDora(DORA_XSIZE, SPACE_YSIZE, 
	                 tk->kyoku[tk->kyoku_index].doracount, 
	                 tk->kyoku[tk->kyoku_index].dora, 
	                 tk->kyoku[tk->kyoku_index].dora_aka,
	                 tk->kyoku[tk->kyoku_index].dora_actid,
	                 tk->kyoku[tk->kyoku_index].act_count);

			// 卓情報
			DispTakuStat(tk, SPACE_XSIZE, DEBUG_INFO_Y_STAT + STRING_YSIZE);

			// 卓クラス情報
			DispTkInfoStat(tk, SPACE_XSIZE, DEBUG_INFO_Y_STAT + STRING_YSIZE*2);

			// 局終了表示
			DispKyokuEnd(tk, gui, tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count);

		break;

		// 卓結果表示
		case TAKURESULT:

			// 卓終了情報
			DisplayGameResult(tk, gui);

		break;

		// 標準処理(その他処理)
		default:

			// 通常状態
			DispNormalTakuStat(tk,ply,gui);

	}

	// ----------------------------------------
	// 裏画面を表画面に反映
	// ----------------------------------------
	dparts->DispPartsFlip();

}

/* ---------------------------------------------------------------------------------------------- */
// 場決め情報
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplayBagime(MJSTkinfo *tk, MJSGui *gui){

	// -----------------------------------------------------------
	// プレーヤ情報の表示
	// -----------------------------------------------------------

	// 局戦情報
	dparts->DispString( BAGIME_X_START, BAGIME_Y_START, tk->tkname );

	// 席表示
	for(int tmp_pnum = 0; tmp_pnum < PLAYER_MAX; tmp_pnum++){

		// プレーヤ名
		      if(tk->kyoku[0].ie[tmp_pnum] == 0){
			DrawFormatString(BAGIME_X_START, BAGIME_Y_START + 50 + 50 * tmp_pnum, GetColor(255,255,255), "[席%d]東家　%s", tmp_pnum+1, tk->plyname[tmp_pnum]);
		}else if(tk->kyoku[0].ie[tmp_pnum] == 1){
			DrawFormatString(BAGIME_X_START, BAGIME_Y_START + 50 + 50 * tmp_pnum, GetColor(255,255,255), "[席%d]南家　%s", tmp_pnum+1, tk->plyname[tmp_pnum]);
		}else if(tk->kyoku[0].ie[tmp_pnum] == 2){
			DrawFormatString(BAGIME_X_START, BAGIME_Y_START + 50 + 50 * tmp_pnum, GetColor(255,255,255), "[席%d]西家　%s", tmp_pnum+1, tk->plyname[tmp_pnum]);
		}else if(tk->kyoku[0].ie[tmp_pnum] == 3){
			DrawFormatString(BAGIME_X_START, BAGIME_Y_START + 50 + 50 * tmp_pnum, GetColor(255,255,255), "[席%d]北家　%s", tmp_pnum+1, tk->plyname[tmp_pnum]);
		}else{
			DrawFormatString(BAGIME_X_START, BAGIME_Y_START + 50 + 50 * tmp_pnum, GetColor(255,255,255), "[席%d]不明　%s", tmp_pnum+1, tk->plyname[tmp_pnum]);
		}

	}

	// 乱数シード(core)
	wsprintf(tmp_disp_msg,"乱数SEED %10d", tk->core_seed_num);
	dparts->DispString( 100, 400, tmp_disp_msg);

	// クリック案内
	wsprintf(tmp_disp_msg, "クリックしてください");
	dparts->DispString( 100, 450, tmp_disp_msg);

	// プレート表示
	// dparts->DispPltline(SPACE_XSIZE, PLT_Y_STAT, PLT_ICON_XSIZE+SPACE_XSIZE, gui->plt_mode);

}

/* ---------------------------------------------------------------------------------------------- */
// ゲームモード表示・通常状態
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DispNormalTakuStat(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui){

	// -----------------------------------------------------------
	// 局情報
	// -----------------------------------------------------------

	// 局情報
	DispKyokuInfo(tk,tk->kyoku_index);

	// ドラ
	dparts->DispDora(DORA_XSIZE, SPACE_YSIZE, 
	                 tk->kyoku[tk->kyoku_index].doracount, 
	                 tk->kyoku[tk->kyoku_index].dora, 
	                 tk->kyoku[tk->kyoku_index].dora_aka,
	                 tk->kyoku[tk->kyoku_index].dora_actid,
	                 tk->kyoku[tk->kyoku_index].act_count);

	// ボタン表示
	dparts->DispInfoButton(THINFO_BUT_X_STAT, TKINFO_BUT_X_STAT, PLYINFO_BUT_X_STAT, QUIT_BUT_X_STAT, BUT02_Y_STAT);

	// 通常モードで表示するパーツ
	if( gui->gui_taku_mode == COMMON_PLAY_MODE){
		// プレート表示
		dparts->DispPltline(SPACE_XSIZE, PLT_Y_STAT, PLT_ICON_XSIZE+SPACE_XSIZE, gui->plt_mode);
		// プレート鳴有/鳴無
		dparts->DispPltNakiAriNashi(PLT_NAKIARI_X_STAT, PLT_Y_STAT, gui->plt_nakiari_flg);
		// 手牌ラインメッセージ
		DispTehaiLineMessage(tk, gui, PLY_MES_X_STAT, PLY_MES_Y_STAT);
	}

	// -----------------------------------------------------------
	// デバグ情報
	// -----------------------------------------------------------
	if(disp_debug_info_mode == true){
		// 個別アクション情報
		DispActNumInfo(tk, SPACE_XSIZE, DEBUG_INFO_Y_STAT, tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count);
		// 卓情報
		DispTakuStat(tk, SPACE_XSIZE, DEBUG_INFO_Y_STAT + STRING_YSIZE);
		// 卓クラス情報
		DispTkInfoStat(tk, SPACE_XSIZE, DEBUG_INFO_Y_STAT + STRING_YSIZE*2);
		// GUI情報
		DispGuiInfo(gui,SPACE_XSIZE, GUI_INFO_Y_STAT);
	}

	// -----------------------------------------------------------
	// 卓GUIモード(gui->gui_taku_mode)ごとの表示
	// -----------------------------------------------------------
	if( gui->gui_taku_mode == COMMON_PLAY_MODE){

		// -----------------------------------------------------------
		// 「手牌ライナー」モード表示
		// -----------------------------------------------------------
		if( gui->disp_tehai_mode == 0){

			// ライナーモード表示
			for( int tmp_pnum = 0; tmp_pnum < PLAYER_MAX ; tmp_pnum++ ) {

				// 手牌
				if( tk->ply_hum_mode == 1 && tmp_pnum == HUM_PLY_SEKI_NUM){
					// 手牌(HUM表示)
					DispActTehaiHum(tk, gui, tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count, tmp_pnum, gui->msx, gui->msy);
				}else{
					// 手牌(COM表示)
					DispActTehaiCom(tk, gui, tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count, tmp_pnum, gui->msx, gui->msy);
				}

				// 晒し表示
				DispActSarashi(tk, tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count, tmp_pnum);

				// 河表示(ライナー表示)
				DispActKawa(tk, tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count, tmp_pnum);

				// プレーヤごとの得点情報
				DispPlyInfo(tk, tk->kyoku_index, tmp_pnum);

			}

		// -----------------------------------------------------------
		// 「手牌囲み」モード表示
		// -----------------------------------------------------------
		}else if( gui->disp_tehai_mode == 1 ){

			// アクションプレート表示
			

			// 卓プレート表示
			DrawBox( TAKU_PLT_X_STAT, TAKU_PLT_Y_STAT, TAKU_PLT_X_SIZE-1, TAKU_PLT_Y_SIZE-1, GetColor( 0, 64, 0 ), TRUE ) ;

			// センタープレート
			dparts->DispCenterPlt( (TAKU_PLT_X_SIZE + TAKU_PLT_X_STAT)/2 - HAI_XSIZE*3,
			                       (TAKU_PLT_Y_SIZE + TAKU_PLT_Y_STAT)/2 - HAI_XSIZE*3 );

			// 手牌囲みモード表示
			for( int tmp_pnum = 0; tmp_pnum < PLAYER_MAX ; tmp_pnum++ ) {

				// 手牌
				if( tk->ply_hum_mode == 1 && tmp_pnum == HUM_PLY_SEKI_NUM){
					// 手牌(HUM表示)
					DispActTehaiHum(tk, gui, tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count, tmp_pnum, gui->msx, gui->msy);
				}else{
					// 手牌(COM表示)
					DispActTehaiCom_square(tk, gui, tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count, tmp_pnum, gui->msx, gui->msy);
				}

				// 晒し表示
				DispActSarashi_square(tk, gui, tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count, tmp_pnum);

				// 河表示
				DispActKawa_square(tk, gui, tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count, tmp_pnum);

				// プレーヤごとの得点情報
				DispPlyInfo(tk, tk->kyoku_index, tmp_pnum);

			}

		// -----------------------------------------------------------
		// 「テスト表示」モード
		// -----------------------------------------------------------
		}else if( gui->disp_tehai_mode == 2 ){

			// 囲み手牌のサンプル表示
			DispActTehai_test_square(gui);

		}

	// -----------------------------------------------------------
	// 終了表示
	// -----------------------------------------------------------
	}else if(gui->gui_taku_mode == COMMON_END_CHECK_MODE){

		// 終了ボタンの確認
		DispTehaiLineMessage(tk, gui, PLY_MES_X_STAT, PLY_MES_Y_STAT);

	// -----------------------------------------------------------
	// tkinfoクラス情報
	// -----------------------------------------------------------
	}else if(gui->gui_taku_mode == COMMON_TKINFO_MODE){

		// tkinfoクラス表示
		DisplayTkinfoDetail(tk);

	// -----------------------------------------------------------
	// 手牌情報詳細(plyクラス情報表示)
	// -----------------------------------------------------------
	}else if(gui->gui_taku_mode == GAME_PLY_INFO_MODE){

		// 手牌情報詳細(plyクラス情報表示)
		DisplayPlyTehaiDetail(tk, ply, tk->ply_turn);

		// サブ手牌の表示モード設定
		// sub_tehai_display_mode = SUB_TEHAI_DISP_MODE;

		// 手牌情報詳細(plyクラス情報表示)
		// if( sub_tehai_display_mode == 0){
		// 	DisplayTakuDetail(tk,ply,tk->ply_turn);
		// }else{
		//	DispYamahai(tk);
		// }

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 卓表示(ビューアーモード)のメイン処理
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplayViewerTaku(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui, float mFps, int total_frame_count, int ver1, int ver2, int ver3, int ver4, int ver5){

	// -----------------------------------------------------------
	// 画面の初期化
	// -----------------------------------------------------------
	dparts->DispPartsClearDraw();

	// -----------------------------------------------------------
	// パーツ表示
	// -----------------------------------------------------------

	// バナー
	dparts->DispBunner(ver1, ver2, ver3, ver4, ver5);

	// マウスポイント
	dparts->DispMousepoint(SPACE_XSIZE, 750, gui->msx, gui->msy, gui->Button[0], gui->Button[1]);

	// FPS
	dparts->DispFps(670, 750, mFps, total_frame_count, gui->frame_count);

	// プレート表示
	dparts->DispPltline(SPACE_XSIZE, PLT_Y_STAT, PLT_ICON_XSIZE+SPACE_XSIZE, gui->plt_mode);

	// -----------------------------------------------------------
	// 操作ボタン
	// -----------------------------------------------------------

	// ボタン表示(削除用)
	// dparts->DispViewerModeButton();
	dparts->DispActidButton(KYOID_X_STAT, ACTID_X_STAT, ACTID_Y_STAT);          // ACTIDボタン
	dparts->DispBagimeButton(BAGIME_X_STAT, TKEND_X_STAT, BAGIME_Y_STAT);       // 場決めボタン
	dparts->DispSekiButton(VIEWER_SEKI_X_STAT, VIEWER_SEKI_Y_STAT);             // 席変更ボタン

	// 情報操作ボタン
	dparts->DispInfoButton(THINFO_BUT_X_STAT, TKINFO_BUT_X_STAT, PLYINFO_BUT_X_STAT, QUIT_BUT_X_STAT, BUT02_Y_STAT);

	// ログ形式
	DisplayGuiLogType(gui, KYOID_X_STAT, ACTID_Y_STAT - STRING_YSIZE*4);

	// アクション情報
	DispActNumInfo(tk, KYOID_X_STAT, ACTID_Y_STAT - STRING_YSIZE, gui->gui_kyoku_index, gui->gui_actid);

	// GUI卓ゲーム表示モード
	DisplayGuiTakuMode(gui, KYOID_X_STAT+80, ACTID_Y_STAT+48);

	// DOWN手牌のプレーヤID
	DrawFormatString(KYOID_X_STAT+80, ACTID_Y_STAT+88, GetColor(255,255,255), "DOWN手牌[席%d]", gui->disp_down_tehai_pnum+1);

	// -----------------------------------------------------------
	// 卓標準表示
	// -----------------------------------------------------------

	// 局情報
	DispKyokuInfo(tk, gui->gui_kyoku_index);

	// ドラ表示
	/* dparts->DispDora(DORA_XSIZE, SPACE_YSIZE, 
	tk->kyoku[gui->gui_kyoku_index].doracount, 
	tk->kyoku[gui->gui_kyoku_index].dora, 
	tk->kyoku[gui->gui_kyoku_index].dora_aka);*/
	dparts->DispDora(DORA_XSIZE, SPACE_YSIZE, 
	                 tk->kyoku[gui->gui_kyoku_index].doracount, 
	                 tk->kyoku[gui->gui_kyoku_index].dora, 
	                 tk->kyoku[gui->gui_kyoku_index].dora_aka,
	                 tk->kyoku[gui->gui_kyoku_index].dora_actid,
	                 gui->gui_actid);

	// メッセージ表示
	if(gui->gui_taku_mode == COMMON_END_CHECK_MODE){

		// 終了ボタンの確認
		DispTehaiLineMessage(tk, gui, PLY_MES_X_STAT, PLY_MES_Y_STAT);

	}

/*
	// デバグ卓情報表示
	if(gui->gui_taku_mode != COMMON_END_CHECK_MODE){
		// 個別アクション情報
		DispActNumInfo(tk, SPACE_XSIZE, DEBUG_INFO_Y_STAT, gui->gui_kyoku_index, gui->gui_actid);
		// 卓クラス情報
		DispTkInfoStat(tk, SPACE_XSIZE, DEBUG_INFO_Y_STAT+STRING_YSIZE*2);
	}
*/

	/*-----------------------------------------------------------*/
	// 卓ステータスごとの表示
	/*-----------------------------------------------------------*/

	// 通常表示
	if(gui->gui_taku_mode == COMMON_PLAY_MODE){

		// 局結果表示
		if(tk->kyoku[gui->gui_kyoku_index].act_stat[gui->gui_actid] == KYOKURESULT){

				// ログ形式ごとで表示
				if (gui->gui_logtype == GUI_LOG_MJSCORE){
					// 局結果：東風荘ログ
					DispViewerKyokuEnd_mjscore(tk, gui->gui_kyoku_index, gui->gui_actid);
				}else if(gui->gui_logtype == GUI_LOG_MJAILOG){
					// 局結果：MJAIログ
					DispViewerKyokuEnd_mjailog(tk, gui->gui_kyoku_index, gui->gui_actid);
				}

		}else{

			// アクションごとの卓表示
			DisplayViewerStatparts(tk, gui);

		}

	// 場決め表示
	}else if(gui->gui_taku_mode == COMMON_BAGIME_MODE){

			// 場決め表示
			DisplayBagime(tk, gui);

	// 卓結果表示
	}else if(gui->gui_taku_mode == COMMON_TAKURESULT_MODE){

			// 卓結果表示
			DispViewerGameResult(tk);

	}

	/*-----------------------------------------------------------*/
	// 裏画面を表画面に反映
	/*-----------------------------------------------------------*/
	dparts->DispPartsFlip();

}

/* ---------------------------------------------------------------------------------------------- */
// ステータスごとのパーツ表示(ビューアーモード)
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplayViewerStatparts(MJSTkinfo *tk, MJSGui *gui){

	// -----------------------------------------------------------
	// 「手牌ライナー」モード表示
	// -----------------------------------------------------------
	if( gui->disp_tehai_mode == 0){

		// プレーヤ一覧表示
		for( int tmp_pnum = 0; tmp_pnum < PLAYER_MAX ; tmp_pnum++ ) {

			// 手牌(COM表示)
			DispActTehaiCom(tk, gui, gui->gui_kyoku_index, gui->gui_actid, tmp_pnum, gui->msx, gui->msy);

			// 晒し表示
			DispActSarashi(tk, gui->gui_kyoku_index, gui->gui_actid, tmp_pnum);

			// 捨牌描写
			DispActKawa(tk, gui->gui_kyoku_index, gui->gui_actid, tmp_pnum);

			// プレーヤごとの得点情報
			DispPlyInfo(tk, gui->gui_kyoku_index, tmp_pnum);

		}

	// -----------------------------------------------------------
	// 「手牌囲み」モード表示
	// -----------------------------------------------------------
	}else if( gui->disp_tehai_mode == 1 ){

		// 卓プレート表示
		DrawBox( TAKU_PLT_X_STAT, TAKU_PLT_Y_STAT, TAKU_PLT_X_SIZE-1, TAKU_PLT_Y_SIZE-1, GetColor( 0, 64, 0 ), TRUE ) ;

		// センタープレート
		dparts->DispCenterPlt( (TAKU_PLT_X_SIZE + TAKU_PLT_X_STAT)/2 - HAI_XSIZE*3,
			                       (TAKU_PLT_Y_SIZE + TAKU_PLT_Y_STAT)/2 - HAI_XSIZE*3 );

		// 手牌囲みモード表示
		for( int tmp_pnum = 0; tmp_pnum < PLAYER_MAX ; tmp_pnum++ ) {

			// 手牌(COM表示)
			DispActTehaiCom_square(tk, gui, gui->gui_kyoku_index, gui->gui_actid, tmp_pnum, gui->msx, gui->msy);

			// 晒し表示
			DispActSarashi_square(tk, gui, gui->gui_kyoku_index, gui->gui_actid, tmp_pnum);

			// 河表示
			DispActKawa_square(tk, gui, gui->gui_kyoku_index, gui->gui_actid, tmp_pnum);

			// プレーヤごとの得点情報
			DispPlyInfo(tk, gui->gui_kyoku_index, tmp_pnum);

		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 手牌情報詳細(tkinfoクラス情報表示)
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplayTkinfoDetail(MJSTkinfo *tk){

	// tkinfo情報
	for( int tmp_pnum = 0; tmp_pnum < PLAYER_MAX ; tmp_pnum++ ) {
		// 個別表示
		DisplayTkinfoDetail_sub_sute(tk, SPACE_XSIZE,(PLY_YSTART-34)    + tmp_pnum*102 + 17*1, tmp_pnum, 0);                                                         // 1段目：捨牌情報
		DisplayTkinfoDetail_sub_sute(tk, SPACE_XSIZE,(PLY_YSTART-34)    + tmp_pnum*102 + 17*2, tmp_pnum, 1);                                                         // 2段目：捨牌情報
		DisplayTkinfoDetail_sub_tehai(tk, SPACE_XSIZE,(PLY_YSTART-34)   + tmp_pnum*102 + 17*3, tmp_pnum);                                                            // 3段目：手牌テーブル
		DisplayTkinfoDetail_sub_hist(tk, SPACE_XSIZE,(PLY_YSTART-34)    + tmp_pnum*102 + 17*4, tmp_pnum);                                                            // 4段目：手牌ヒストグラム情報
		DisplayTkinfoDetail_sub_naki(tk, tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count, tmp_pnum, SPACE_XSIZE, (PLY_YSTART-34) + tmp_pnum*102 + 17*5);       // 5段目：鳴き情報
		DisplayTkinfoDetail_sub_shanten(tk, SPACE_XSIZE,(PLY_YSTART-34) + tmp_pnum*102 + 17*6, tmp_pnum);                                                            // 6段目：待牌情報

		// DrawFormatString(SPACE_XSIZE, (PLY_YSTART-17) + tmp_pnum*95, GetColor(255,255,255), "[席%d捨牌1]",tmp_pnum+1);
		// DisplayTkinfoDetail_sub_tehai(tk, SPACE_XSIZE, (PLY_YSTART-17) + tmp_pnum*95 + 17*2, tmp_pnum);
		// DrawFormatString(SPACE_XSIZE, (PLY_YSTART-17) + tmp_pnum*95 + 17*2, GetColor(255,255,255), "[席%dHist]",tmp_pnum+1);
		// DrawFormatString(SPACE_XSIZE, (PLY_YSTART-17) + tmp_pnum*95 + 17*3, GetColor(255,255,255), "[席%d鳴牌]",tmp_pnum+1);
	}

}

/* ---------------------------------------------------------------------------------------------- */
// tkinfo情報の詳細(サブ処理：手牌情報)
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplayTkinfoDetail_sub_tehai(MJSTkinfo *tk, int x, int y, int pnum){

	// 手牌の合計枚数
	DrawFormatString(x, y, GetColor(255,255,255), "[席%d]%2d枚:", pnum+1,tk->ply_act_tehaicount[pnum]);

	// 手牌情報
	for(int tmp_i = 0; tmp_i < tk->ply_act_tehaicount[pnum]; tmp_i++){

		// 捨牌アクションなら
		if( tk->kyoku[tk->kyoku_index].act_stat[tk->kyoku[tk->kyoku_index].act_count] == PLYACTSUTE      || 
		    tk->kyoku[tk->kyoku_index].act_stat[tk->kyoku[tk->kyoku_index].act_count] == PLYACTTSUMOGIRI || 
		    tk->kyoku[tk->kyoku_index].act_stat[tk->kyoku[tk->kyoku_index].act_count] == PLYACTNAKISUTE  || 
			tk->ply_turn != pnum){

			// 手牌情報(赤牌確認)
			if(tk->ply_act_tehai_tbl_aka[pnum][tmp_i] == true){
				DrawFormatString(x+tmp_i*58+110, y, GetColor(255,255,255), "%2d赤-",tk->ply_act_tehaitbl[pnum][tmp_i]);
			}else{
				DrawFormatString(x+tmp_i*58+110, y, GetColor(255,255,255), "%2d黒-",tk->ply_act_tehaitbl[pnum][tmp_i]);
			}

		}else{

			// 手牌情報(赤牌確認)
			if(tk->ply_act_tehai_tbl_aka[pnum][tmp_i] == true){
				DrawFormatString(x+tmp_i*58+110, y, GetColor(255,255,255), "%2d赤%d",tk->ply_act_tehaitbl[pnum][tmp_i],tk->ply_act_tehai_shanten_tbl[pnum][tmp_i]);
			}else{
				DrawFormatString(x+tmp_i*58+110, y, GetColor(255,255,255), "%2d黒%d",tk->ply_act_tehaitbl[pnum][tmp_i],tk->ply_act_tehai_shanten_tbl[pnum][tmp_i]);
			}

		}

	}

			// 自摸情報
			if(tk->ply_act_tsumo_aka[pnum] == true){
				DrawFormatString(x+13*58+110, y, GetColor(255,255,255), "%2d赤%d",tk->ply_act_tsumo[pnum],tk->ply_act_tsumo_shanten[pnum]);
			}else{
				DrawFormatString(x+13*58+110, y, GetColor(255,255,255), "%2d黒%d",tk->ply_act_tsumo[pnum],tk->ply_act_tsumo_shanten[pnum]);
			}

			// 捨牌情報
			if(tk->ply_act_sute_aka[pnum] == true){
				DrawFormatString(x+14*58+110, y, GetColor(255,255,255), "捨%2d赤位%2d",tk->ply_act_sute[pnum],tk->ply_tbl_com_sutehai_statnum[pnum]);
			}else{
				DrawFormatString(x+14*58+110, y, GetColor(255,255,255), "捨%2d赤位%2d",tk->ply_act_sute[pnum],tk->ply_tbl_com_sutehai_statnum[pnum]);
			}

}

/* ---------------------------------------------------------------------------------------------- */
// tkinfo情報の詳細(サブ処理：手牌ヒストグラム情報)
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplayTkinfoDetail_sub_hist(MJSTkinfo *tk, int x, int y, int pnum){

	// ヒストグラム情報
	DrawFormatString(x, y, GetColor(255,255,255), "[席%d]", pnum+1);

	// 萬子、筒子、索子
	for(int tmp_syubetsu = 0; tmp_syubetsu < 3; tmp_syubetsu++){
		// 0牌
			DrawFormatString(tmp_syubetsu*95 +         + x+50, y, GetColor(255,255,255), "%d",tk->ply_act_tehai[pnum][tmp_syubetsu*10]);
		// 1-9牌
		for(int tmp_i = 0; tmp_i < 9; tmp_i++){
			DrawFormatString(tmp_syubetsu*95 + tmp_i*8 + x+65, y, GetColor(255,255,255), "%d",tk->ply_act_tehai[pnum][tmp_syubetsu*10+tmp_i+1]);
		}
	}

	// 字牌
		// 0牌
			 DrawFormatString(             95*3 + x+50, y, GetColor(255,255,255), "%d",tk->ply_act_tehai[pnum][30]);
		// 1-9牌
		for(int tmp_i = 0; tmp_i < 7; tmp_i++){
			DrawFormatString(              95*3 + x+65 + (tmp_i)*8, y, GetColor(255,255,255), "%d",tk->ply_act_tehai[pnum][31+tmp_i]);
		}

}

/* ---------------------------------------------------------------------------------------------- */
// tkinfo情報の詳細(サブ処理：捨牌情報)
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplayTkinfoDetail_sub_sute(MJSTkinfo *tk, int x, int y, int pnum, int line_num){

	// 捨牌情報1段目
	if(line_num == 0){

		// プレーヤ情報
		DrawFormatString(x, y, GetColor(255,255,255), "[席%d]捨%2d枚:", pnum+1, tk->ply_act_kawa_count[pnum]);

		// 捨牌情報
		if(tk->ply_act_kawa_count[pnum] >= 15){
			for(int tmp_i = 0; tmp_i < 15; tmp_i++){
				DrawFormatString(tmp_i*58+x+110, y, GetColor(255,255,255), "%2d黒%d",tk->ply_act_kawa[pnum][tmp_i],tk->ply_act_kawa_mode[pnum][tmp_i]);
			}
		}else{
			for(int tmp_i = 0; tmp_i < tk->ply_act_kawa_count[pnum]; tmp_i++){
				DrawFormatString(tmp_i*58+x+110, y, GetColor(255,255,255), "%2d黒%d",tk->ply_act_kawa[pnum][tmp_i],tk->ply_act_kawa_mode[pnum][tmp_i]);
			}
		}

	// 捨牌情報2段目
	}else{

		// プレーヤ情報
		DrawFormatString(x, y, GetColor(255,255,255), "[席%d]:　　　", pnum+1);
		// 捨牌情報
		if(tk->ply_act_kawa_count[pnum] >= 15){
			for(int tmp_i = 15; tmp_i < tk->ply_act_kawa_count[pnum]; tmp_i++){
				DrawFormatString((tmp_i-15)*58+x+110, y, GetColor(255,255,255), "%2d黒%d",tk->ply_act_kawa[pnum][tmp_i],tk->ply_act_kawa_mode[pnum][tmp_i]);
			}
		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// tkinfo情報の詳細(サブ処理：鳴牌情報)
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplayTkinfoDetail_sub_naki(MJSTkinfo *tk, int kyoku_index, int actid, int pnum, int x, int y){

	// 鳴き情報
	DrawFormatString(x, y, GetColor(255,255,255), "[席%d]鳴%d 暗%d 加%d", pnum+1, tk->kyoku[kyoku_index].naki_count[pnum], tk->kyoku[kyoku_index].ankan_count[pnum] , tk->kyoku[kyoku_index].kakan_count[pnum]);

	// 鳴き情報・詳細
	for(int tmp_i = 0; tmp_i < tk->kyoku[kyoku_index].naki_count[pnum]; tmp_i++){
		if(tk->kyoku[kyoku_index].naki_stat[pnum][tmp_i] == MINKO){
			DrawFormatString(tmp_i*100+x+150, y, GetColor(255,255,255), "ポン%2d赤%d",tk->kyoku[kyoku_index].naki_hai[pnum][tmp_i],0);
		}else if(tk->kyoku[kyoku_index].naki_stat[pnum][tmp_i]==MINSHUN){
			DrawFormatString(tmp_i*100+x+150, y, GetColor(255,255,255), "チー%2d,%2d赤%d",tk->kyoku[kyoku_index].naki_idx[pnum][tmp_i],tk->kyoku[kyoku_index].naki_hai[pnum][tmp_i],0);
		}else if(tk->kyoku[kyoku_index].naki_stat[pnum][tmp_i]==ANKAN){
			DrawFormatString(tmp_i*100+x+150, y, GetColor(255,255,255), "暗槓%2d赤%d",tk->kyoku[kyoku_index].naki_hai[pnum][tmp_i],0);
		}else if(tk->kyoku[kyoku_index].naki_stat[pnum][tmp_i]==MINKAN){
			DrawFormatString(tmp_i*100+x+150, y, GetColor(255,255,255), "明槓%2d赤%d",tk->kyoku[kyoku_index].naki_hai[pnum][tmp_i],0);
		}else if(tk->kyoku[kyoku_index].naki_stat[pnum][tmp_i]==KAKAN){
			DrawFormatString(tmp_i*100+x+150, y, GetColor(255,255,255), "加槓%2d赤%d",tk->kyoku[kyoku_index].naki_hai[pnum][tmp_i],0);
		}else{
			DrawFormatString(tmp_i*100+x+150, y, GetColor(255,255,255), "不明%2d赤%d",tk->kyoku[kyoku_index].naki_hai[pnum][tmp_i],0);
		}
	}

}

/* ---------------------------------------------------------------------------------------------- */
// tkinfo情報の詳細(サブ処理：赤牌、向聴、待牌情報)
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplayTkinfoDetail_sub_shanten(MJSTkinfo *tk, int x, int y, int pnum){

	// DrawFormatString(x, y, GetColor(255,255,255), "[席%d待牌]",pnum+1);

	// 赤牌枚数、向聴数
	DrawFormatString(x, y, GetColor(255,255,255), "[席%d]赤%d,%d,%d鳴%d総%2d通%2d七%2d国%2d待%2d:", 
		       pnum+1, 
		       tk->ply_act_aka_count[pnum][0],   // 赤牌枚数萬子
		       tk->ply_act_aka_count[pnum][1],   // 赤牌枚数筒子
		       tk->ply_act_aka_count[pnum][2],   // 赤牌枚数索子
		       tk->naki_count_none_kakan[pnum],  // 鳴牌枚数
		       tk->shanten_total[pnum], 
		       tk->shanten_normal[pnum], tk->shanten_chitoi[pnum],tk->shanten_kokushi[pnum], tk->ply_act_machi_count[pnum]);

	// 待牌
	for(int tmp_i = 0; tmp_i < tk->ply_act_machi_count[pnum]; tmp_i++){
		DrawFormatString(x+320+tmp_i*25, y, GetColor(255,255,255), "%2d,", tk->ply_act_machi_hai[pnum][tmp_i]);
	}

}

/* ---------------------------------------------------------------------------------------------- */
// tkinfo情報の詳細(サブ処理：Act鳴牌情報)
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplayTkinfoDetail_sub_ply_actnaki_info(MJSTkinfo *tk, int x, int y, int pnum){

	// 鳴き牌情報
	DrawFormatString(x, y, GetColor(255,255,255), "[席%d]", pnum+1);

	// 鳴きアクション表示
	DisplayTkinfoDetail_sub_plyactInfo(tk, tk->ply_act_naki[pnum], x+50, y);

	// 鳴き詳細
	DrawFormatString(x+125, y, GetColor(255,255,255), "鳴%2d頭%2d赤%d",
	tk->ply_naki_hai[pnum], 
	tk->ply_naki_idx[pnum], 
	tk->ply_naki_aka_count[pnum]);

}

/* ---------------------------------------------------------------------------------------------- */
// tkinfo情報の詳細(サブ処理：tkinfoステータス)
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplayTkinfoDetail_sub_tkstat(MJSTkinfo *tk, LBTkSt tk_stat, int x, int y){

	// -----------------------------------------------------------
	// 卓状態
	// -----------------------------------------------------------
	if( tk_stat == PLYNOACT){
			wsprintf(tmp_disp_msg, "定義なし");   // 00: 卓状態の定義なし
	}else if( tk_stat == TAKUSTART){
			wsprintf(tmp_disp_msg, "卓開始　");   // 01: 卓開始
	}else if( tk_stat == BAGIME){
			wsprintf(tmp_disp_msg, "場決め　");   // 02: 場決め
	}else if( tk_stat == KYOKUSTART){
			wsprintf(tmp_disp_msg, "局開始　");   // 03: 局開始
	}else if( tk_stat == HAIPAI){
			wsprintf(tmp_disp_msg, "配牌　　");   // 04: 配牌
	}else if( tk_stat == PLYACTTSUMOWAIT){
			wsprintf(tmp_disp_msg, "自摸待ち");   // 05: 自摸牌待ち
	}else if( tk_stat == PLYACTTSUMO){
			wsprintf(tmp_disp_msg, "自摸　　");   // 06: 自摸牌受取
	}else if( tk_stat == PLYRINSHAN){
			wsprintf(tmp_disp_msg, "嶺上自摸");   // 07: 嶺上牌受取
	}else if( tk_stat == PLYACTSUTEWAIT){
			wsprintf(tmp_disp_msg, "捨牌待ち");   // 08: 自摸後の捨牌待ち
	}else if( tk_stat == PLYACTNAKISUTEWAIT){
			wsprintf(tmp_disp_msg, "鳴捨待ち");   // 09: 鳴後の捨牌待ち
	}else if( tk_stat == PLYACTSUTE){
			wsprintf(tmp_disp_msg, "捨牌　　");   // 10: 捨牌
	}else if( tk_stat == PLYACTTSUMOGIRI){
			wsprintf(tmp_disp_msg, "自摸切り");   // 11: 自摸切り
	}else if( tk_stat == PLYACTNAKISUTE){
			wsprintf(tmp_disp_msg, "鳴き捨牌");   // 12: 鳴き捨牌
	}else if( tk_stat == PLYACTRIICH){
			wsprintf(tmp_disp_msg, "リーチ　");   // 13: リーチ宣言
	}else if( tk_stat == PLYRIICHACCEPTED){
			wsprintf(tmp_disp_msg, "リーチ承");   // 14: リーチ宣言受け入れ
	}else if( tk_stat == PLYTSUMOAGARI){
			wsprintf(tmp_disp_msg, "自摸和了");   // 15: 自摸和了
	}else if( tk_stat == PLYACTANKAN){
			wsprintf(tmp_disp_msg, "暗槓　　");   // 16: 暗槓
	}else if( tk_stat == PLYACTKAKAN){
			wsprintf(tmp_disp_msg, "加槓　　");   // 17: 加槓
	}else if( tk_stat == PLYACTNAKIWAIT){
			wsprintf(tmp_disp_msg, "鳴き待ち");   // 18: 鳴き待ち
	}else if( tk_stat == PLYACTRON){
			wsprintf(tmp_disp_msg, "ロン和了");   // 19: ロン和了
	}else if( tk_stat == PLYACTPON){
			wsprintf(tmp_disp_msg, "ポン　　");   // 20: ポン
	}else if( tk_stat == PLYACTCHI){
			wsprintf(tmp_disp_msg, "チー　　");   // 21: チー
	}else if( tk_stat == PLYACTMINKAN){
			wsprintf(tmp_disp_msg, "明槓　　");   // 22: 明槓
	}else if( tk_stat == TSUMOKANDORAOPEN){
			wsprintf(tmp_disp_msg, "自摸ドラ");   // 24: 自摸時カンドラ表示
	}else if( tk_stat == SUTEKANDORAOPEN){
			wsprintf(tmp_disp_msg, "捨牌ドラ");   // 25: 捨牌時カンドラ表示
	}else if( tk_stat == RYUKYOKU){
			wsprintf(tmp_disp_msg, "流局　　");   // 26: 流局
	}else if( tk_stat == KYOKURESULT){
			wsprintf(tmp_disp_msg, "局結果　");   // 26: 局結果表示
	}else if( tk_stat == KYOKUEND){
			wsprintf(tmp_disp_msg, "局終了　");   // 26: 局終了
	}else if( tk_stat == TAKURESULT){
			wsprintf(tmp_disp_msg, "卓結果　");   // 27: 卓結果表示
	}else if( tk_stat == TAKUEND){
			wsprintf(tmp_disp_msg, "卓終了　");   // 28: 卓終了
	}else if( tk_stat == TAKUERR){
			wsprintf(tmp_disp_msg, "卓エラー");   // 29: 卓エラー状態
	}else{
			wsprintf(tmp_disp_msg, "不明　　");   // 99: 不明
	}

	// アクション情報表示
	DrawFormatString(x, y, GetColor(255,255,255), "%s", tmp_disp_msg);

}

/* ---------------------------------------------------------------------------------------------- */
// tkinfo情報の詳細(サブ処理：ply_actステータス)
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplayTkinfoDetail_sub_plyactInfo(MJSTkinfo *tk, LBPAct tmp_act, int x, int y){

	// -----------------------------------------------------------
	// プレーヤのアクションステータス
	// -----------------------------------------------------------
	if( tmp_act == NOACT){
			wsprintf(tmp_disp_msg, "ACTなし 　"); // 00: アクションなし
	}else if( tmp_act == ACTHAIPAI){
			wsprintf(tmp_disp_msg, "配牌時　　"); // 01: 配牌時
	}else if( tmp_act == ACTTSUMO){
			wsprintf(tmp_disp_msg, "自摸牌受取"); // 02: 自摸牌受取
	}else if( tmp_act == ACTRINSHAN){
			wsprintf(tmp_disp_msg, "嶺上牌受取"); // 03: 嶺上牌受取
	}else if( tmp_act == ACTSUTEWAIT){
			wsprintf(tmp_disp_msg, "捨牌待ち　"); // 04: 捨牌待ち
	}else if( tmp_act == ACNAKITSUTEWAIT){
			wsprintf(tmp_disp_msg, "鳴き捨牌待"); // 05: 鳴き捨牌待ち
	}else if( tmp_act == ACTSUTE){
			wsprintf(tmp_disp_msg, "捨牌　　　"); // 06: 捨牌
	}else if( tmp_act == ACTNAKISUTE){
			wsprintf(tmp_disp_msg, "鳴き捨牌　"); // 07: 鳴き捨牌
	}else if( tmp_act == ACTTSUMOGIRI){
			wsprintf(tmp_disp_msg, "自摸切り　"); // 08: 自摸切り
	}else if( tmp_act == ACTRIICH){
			wsprintf(tmp_disp_msg, "リーチ宣言"); // 09: リーチ宣言
	}else if( tmp_act == ACTTSUMOAGARI){
			wsprintf(tmp_disp_msg, "自摸和了　"); // 10: 自摸和了宣言
	}else if( tmp_act == ACTNAKIWAIT){
			wsprintf(tmp_disp_msg, "鳴き待ち　"); // 11: 鳴き待ち
	}else if( tmp_act == ACTNONAKI){
			wsprintf(tmp_disp_msg, "鳴きなし　"); // 12: 鳴きをしない
	}else if( tmp_act == ACTRON){
			wsprintf(tmp_disp_msg, "ロン和了　"); // 13: ロン和了宣言
	}else if( tmp_act == ACTPON){
			wsprintf(tmp_disp_msg, "ポン鳴き　"); // 14: ポン鳴き宣言
	}else if( tmp_act == ACTCHI){
			wsprintf(tmp_disp_msg, "チー鳴き　"); // 15: チー鳴き宣言
	}else if( tmp_act == ACTMINKAN){
			wsprintf(tmp_disp_msg, "明槓鳴き　"); // 16: 明槓鳴き宣言
	}else if( tmp_act == ACTANKAN){
			wsprintf(tmp_disp_msg, "暗槓鳴き　"); // 17: 暗槓鳴き宣言
	}else if( tmp_act == ACTKAKAN){
			wsprintf(tmp_disp_msg, "加槓鳴き　"); // 18: 加槓鳴き宣言
	}else{
			wsprintf(tmp_disp_msg, "不明　　　"); // 99: 不明
	}

	// アクション情報表示
	DrawFormatString(x, y, GetColor(255,255,255), "%s", tmp_disp_msg);

}

/* ---------------------------------------------------------------------------------------------- */
// GUI情報・// tkinfo情報詳細(サブ処理：手牌枚数)
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplayTkinfoDetail_sub_tehai_count(MJSTkinfo *tk, int x, int y, int pnum){

	// 手牌枚数表示
	DrawFormatString(x, y, GetColor(255,255,255), "[席%d]%d枚", pnum+1, tk->ply_act_tehaicount[pnum]);

}

/* ---------------------------------------------------------------------------------------------- */
// GUI情報・GUIクライアントモードのステータス表示
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplayGuiClientMode(MJSGui *gui, int x, int y){

	// メッセージ設定
	if( gui->cli_mode == GUI_MJAI_CLIENT_NO_MODE){
		wsprintf(tmp_disp_msg, "状態なし　　　");                // 00:状態なし
	}else if( gui->cli_mode == GUI_MJAI_NOTCONNECT){
		wsprintf(tmp_disp_msg, "接続前待ち　　");                // 01:接続前待ち
	}else if( gui->cli_mode == GUI_MJAI_CONNECT_ACTION){
		wsprintf(tmp_disp_msg, "接続処理　　　");                // 02:接続処理
	}else if( gui->cli_mode == GUI_MJAI_DISCONNECT){
		wsprintf(tmp_disp_msg, "切断処理　　　");                // 04:切断処理
	}else if( gui->cli_mode == GUI_MJAI_ERR_CONNECT){
		wsprintf(tmp_disp_msg, "接続時エラー　");                // 05:Socket接続時エラー
	}else if( gui->cli_mode == GUI_MJAI_WAIT_HELO_RESMES){
		wsprintf(tmp_disp_msg, "HELO待ち　　　");                // 06:HELLOリクエスト待ち
	}else if( gui->cli_mode == GUI_MJAI_WAIT_TAKU_START_RESMES){
		wsprintf(tmp_disp_msg, "卓開始待ち　　");                // 07:卓開始待ち
	}else if( gui->cli_mode == GUI_MJAI_BAGIME){
		wsprintf(tmp_disp_msg, "場決め　　　　");                // 08:場決め
	}else if( gui->cli_mode == GUI_MJAI_WAIT_KYOKU_START_RESMES){
		wsprintf(tmp_disp_msg, "局開始待ち　　");                // 09:局開始待ち
	}else if( gui->cli_mode == GUI_MJAI_HAIPAI){
		wsprintf(tmp_disp_msg, "配牌表示");                      // 10:配牌表示
	}else if( gui->cli_mode == GUI_MJAI_WAIT_TAKU_RESMES){
		wsprintf(tmp_disp_msg, "卓情報受信待ち");                // 11:卓モード：受信メッセージ待ち
	}else if( gui->cli_mode == GUI_MJAI_WAIT_TAKU_PLYACT){
		wsprintf(tmp_disp_msg, "PLYACT待ち　　");                // 12:卓モード：プレーヤアクション待ち
	}else if( gui->cli_mode == GUI_MJAI_WAIT_SED_MES){
		wsprintf(tmp_disp_msg, "送信待ち　　　");                // 13:卓モード：メッセージ送信の処理待ち時間
	}else if( gui->cli_mode == GUI_MJAI_ERR_RES_MES){
		wsprintf(tmp_disp_msg, "エラー受信　　");                // 14:卓モード：エラーメッセージ受信時状態
	}else if( gui->cli_mode == GUI_MJAI_KYOKUEND){
		wsprintf(tmp_disp_msg, "局終了表示　　");                // 15:局結果：局終了処理
	}else if( gui->cli_mode == GUI_MJAI_KYOKUEND_SED_MES){
		wsprintf(tmp_disp_msg, "局終了送信待ち");                // 16:局結果：局終了時の確認メッセージ送信の待ち時間
	}else if( gui->cli_mode == GUI_MJAI_TAKURESULT){
		wsprintf(tmp_disp_msg, "卓結果表示　　");                // 17:卓結果：卓結果処理
	}else if( gui->cli_mode == GUI_MJAI_END_MODE){
		wsprintf(tmp_disp_msg, "卓終了　　");                    // 18:終了モード
	}else{
		wsprintf(tmp_disp_msg, "不明　　");                      // 99:例外モード
	}

	// GUI情報表示
	DrawFormatString(x, y, GetColor(255,255,255), "[Stat]%s", tmp_disp_msg);

}

/* ---------------------------------------------------------------------------------------------- */
// 手牌情報詳細(plyクラス情報表示)
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplayPlyTehaiDetail(MJSTkinfo *tk, MJSPlayer *ply, int pnum){

	// -----------------------------------------------------------
	// 卓情報表示
	// -----------------------------------------------------------

	if(ply[pnum].ie == 0){
		DrawFormatString(SPACE_XSIZE, PLY_YSTART-17, GetColor(255,255,255), "[席%d][下席%d]東家", 
					ply[pnum].ply_num+1, 
					ply[pnum].ply_num_shimo+1);
	}else if(ply[pnum].ie == 1){
		DrawFormatString(SPACE_XSIZE, PLY_YSTART-17, GetColor(255,255,255), "[席%d][下席%d]南家", 
					ply[pnum].ply_num+1, 
					ply[pnum].ply_num_shimo+1);
	}else if(ply[pnum].ie == 2){
		DrawFormatString(SPACE_XSIZE, PLY_YSTART-17, GetColor(255,255,255), "[席%d][下席%d]西家", 
					ply[pnum].ply_num+1, 
					ply[pnum].ply_num_shimo+1);
	}else if(ply[pnum].ie == 3){
		DrawFormatString(SPACE_XSIZE, PLY_YSTART-17, GetColor(255,255,255), "[席%d][下席%d]北家", 
					ply[pnum].ply_num+1, 
					ply[pnum].ply_num_shimo+1);
	}

	// 赤牌情報
	DrawFormatString(SPACE_XSIZE, PLY_YSTART, GetColor(255,255,255), "赤萬%d 赤筒%d 赤索%d", 
				ply[pnum].aka_count[0], 
				ply[pnum].aka_count[1], 
				ply[pnum].aka_count[2]);

	//-----------------------------------------------------------
	// 捨牌候補表示(自摸ありパターン)
	//-----------------------------------------------------------
	if (tk->stat == PLYACTTSUMO        || 
	    tk->stat == PLYACTSUTEWAIT     || 
		tk->stat == PLYACTNAKISUTEWAIT || 
		tk->stat == PLYACTRIICH        ){ 

		// 自摸ありパターン詳細情報
		DisplayPlyTehaiDetailTsumoAri(tk, ply, pnum, SPACE_XSIZE, PLY_YSTART);

	//-----------------------------------------------------------
	// 捨牌候補表示(自摸なしパターン)
	//-----------------------------------------------------------

	}else if( tk->stat == PLYACTSUTE      || 
	          tk->stat == PLYACTTSUMOGIRI || 
	          tk->stat == PLYACTNAKISUTE  || 
	          tk->stat == PLYACTNAKIWAIT  || 
	          tk->stat == HAIPAI          || 
	          tk->stat == PLYACTANKAN     || 
	          tk->stat == PLYACTKAKAN     ){

		// 自摸なしパターン詳細情報
		DisplayPlyTehaiDetailTsumoNashi(tk, ply, pnum, SPACE_XSIZE, PLY_YSTART);

	//-----------------------------------------------------------
	// 捨牌候補表示(和了パターン)
	//-----------------------------------------------------------

	}else if(tk->stat == PLYTSUMOAGARI || tk->stat == PLYACTRON){

		// 和了情報
		DrawFormatString(SPACE_XSIZE, PLY_YSTART+ 90, GetColor(255,255,255), "プレーヤ和了");

	//-----------------------------------------------------------
	// 捨牌候補表示(例外処理)
	//-----------------------------------------------------------

	}else{

		// デバグ用
		DrawFormatString(SPACE_XSIZE, PLY_YSTART+ 90, GetColor(255,255,255), "例外状態");

	}

}

/* ---------------------------------------------------------------------------------------------- */
// ply手牌の詳細情報(自摸有り時)
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplayPlyTehaiDetailTsumoAri(MJSTkinfo *tk, MJSPlayer *ply, int pnum, int x, int y){

	// -----------------------------------------------------------
	// 手牌表示
	// -----------------------------------------------------------

	// 手牌テーブル更新処理
	ply[pnum].settehaitbl();

	// 自摸あり手牌表示
	dparts->DispActTehaiParts( SPACE_XSIZE, PLY_YSTART+40,
		                  ply[pnum].tehai_count,
		                  ply[pnum].tehaitbl,
		                  ply[pnum].tehaitbl_aka, 
		                  ply[pnum].ply_tsumo_hai,                         // 自摸牌
	                      ply[pnum].ply_tsumo_aka,                         // 自摸赤
	                      EXCEPT_VALUE,                                    // 捨牌：なし
	                      EXCEPT_VALUE, EXCEPT_VALUE, false);              // カーソル選択：なし

	// -----------------------------------------------------------
	// 晒し牌表示
	// -----------------------------------------------------------
	dparts->DispAllSarashiParts(600, PLY_YSTART+40,    // XY位置
	ply[pnum].naki_count,          // 鳴き合計面子数
	ply[pnum].naki_stat,           // 鳴き状態
	ply[pnum].naki_hai,            // 鳴き牌
	ply[pnum].naki_idx,            // チー時の頭牌
	ply[pnum].naki_aka             // 赤牌の数
	);

	//-----------------------------------------------------------
	// 向聴情報
	//-----------------------------------------------------------
	DrawFormatString(SPACE_XSIZE+150, PLY_YSTART-17, GetColor(255,255,255), "晒し牌%d面子 通常%d向聴(最大有効牌%d枚) 七対%d向聴 国士%d向聴", 
				ply[pnum].naki_count,
				ply[pnum].shanten_normal, 
				ply[pnum].yuko_max_count, 
				ply[pnum].shanten_chitoi, 
				ply[pnum].shanten_kokushi);

	// 自摸あり表記
	DrawFormatString(SPACE_XSIZE, PLY_YSTART+19, GetColor(255,255,255), "手牌情報：自摸有り");

	//-----------------------------------------------------------
	// 捨牌候補数
	//-----------------------------------------------------------

	// 候補数
	DrawFormatString(SPACE_XSIZE, PLY_YSTART+80, GetColor(255,255,255), "捨牌候補%d種", ply[pnum].sutekoho_count);

	// 一覧表示
	if(ply[pnum].sutekoho_count > 7){

		// 捨牌候補(左段表示)
		for(int tmp_i = 0; tmp_i < 7; tmp_i++){
			DisplaySutekoho(tk, ply, pnum, SPACE_XSIZE, PLY_YSTART+100+tmp_i*40, tmp_i);
		}

		// 捨牌候補(右段表示)
		for(int tmp_i = 7; tmp_i < ply[pnum].sutekoho_count; tmp_i++){
			DisplaySutekoho(tk, ply, pnum, SPACE_XSIZE+510, PLY_YSTART+100+(tmp_i-7)*40, tmp_i);
		}

	}else{

		// 捨牌候補(左段表示)
		for(int tmp_i = 0; tmp_i < ply[pnum].sutekoho_count; tmp_i++){
			DisplaySutekoho(tk, ply, pnum, SPACE_XSIZE, PLY_YSTART+100+tmp_i*40, tmp_i);
		}

	}

	//-----------------------------------------------------------
	// 最終捨牌候補
	//-----------------------------------------------------------
	DrawFormatString(SPACE_XSIZE, PLY_YSTART+400, GetColor(255,255,255), "捨牌候補");
	dparts->DispHai( SPACE_XSIZE+80, PLY_YSTART+380, ply[pnum].sutekoho_hai[ply[pnum].fixed_sutekoho_num], false, false, 0, 0);

	//-----------------------------------------------------------
	// アクション表示
	//-----------------------------------------------------------
	if( ply[pnum].ply_act == ACTSUTE){
		wsprintf(tmp_disp_msg, "捨牌　　");

		// 牌表示
		if(ply[pnum].ply_sute_aka == true){
			dparts->DispHai( 270, PLY_YSTART+380, ply[pnum].ply_sute_hai, true, false, 0, 0);
		}else{
			dparts->DispHai( 270, PLY_YSTART+380, ply[pnum].ply_sute_hai, false, false, 0, 0);
		}

	}else if(ply[pnum].ply_act == ACTTSUMOGIRI){

		// アクション表示
		wsprintf(tmp_disp_msg, "自摸切り");

		// 牌表示
		if(ply[pnum].ply_sute_aka == true){
			dparts->DispHai( 270, PLY_YSTART+380, ply[pnum].ply_sute_hai, true, false, 0, 0);
		}else{
			dparts->DispHai( 270, PLY_YSTART+380, ply[pnum].ply_sute_hai, false, false, 0, 0);
		}

	}else if(ply[pnum].ply_act == ACTNAKISUTE){

		// アクション表示
		wsprintf(tmp_disp_msg, "鳴き捨て");

		// 牌表示
		if(ply[pnum].ply_sute_aka == true){
			dparts->DispHai( 270, PLY_YSTART+380, ply[pnum].ply_sute_hai, true, false, 0, 0);
		}else{
			dparts->DispHai( 270, PLY_YSTART+380, ply[pnum].ply_sute_hai, false, false, 0, 0);
		}

	}else if(ply[pnum].ply_act == ACTRIICH){

		// アクション表示
		wsprintf(tmp_disp_msg, "リーチ　");

	}else if(ply[pnum].ply_act == ACTANKAN){

		// アクション表示
		wsprintf(tmp_disp_msg, "暗槓　　");

		// 牌表示
		dparts->DispHai( 270, PLY_YSTART+380, ply[pnum].ply_naki_idx, false, false, 0, 0);

	}else if(ply[pnum].ply_act == ACTKAKAN){

		// アクション表示
		wsprintf(tmp_disp_msg, "加槓　　");

		// 牌表示
		dparts->DispHai( 270, PLY_YSTART+380, ply[pnum].ply_naki_idx, false, false, 0, 0);

	}else{

		// アクション表示
		wsprintf(tmp_disp_msg, "不明　　");

	}

	// アクション表示
	DrawFormatString(150, PLY_YSTART+400, GetColor(255,255,255), "Act：%s", tmp_disp_msg);

	//-----------------------------------------------------------
	// 表示牌一覧
	//-----------------------------------------------------------
	DisplayOpenhai(tk, ply, pnum, SPACE_XSIZE, PLY_YSTART+450);

	//-----------------------------------------------------------
	// 処理時間
	//-----------------------------------------------------------
	DrawFormatString(SPACE_XSIZE, PLY_YSTART+490, GetColor(255,255,255), "処理時間(ply) :%dミリ秒",ply[pnum].action_timestamp2 - ply[pnum].action_timestamp1);    // 処理時間

}

/* ---------------------------------------------------------------------------------------------- */
// ply手牌の詳細情報(自摸無し時)
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplayPlyTehaiDetailTsumoNashi(MJSTkinfo *tk, MJSPlayer *ply, int pnum, int x, int y){

	// -----------------------------------------------------------
	// 手牌表示
	// -----------------------------------------------------------

	// 手牌テーブル更新処理
	ply[pnum].settehaitbl();

	// 自摸なし手牌表示
	dparts->DispActTehaiParts( SPACE_XSIZE, PLY_YSTART+40,
		                  ply[pnum].tehai_count,
		                  ply[pnum].tehaitbl,
		                  ply[pnum].tehaitbl_aka, 
		                  EXCEPT_VALUE,                                    // 自摸牌：なし
	                      false,                                           // 自摸赤・なし
	                      EXCEPT_VALUE,                                    // 捨牌：なし
	                      EXCEPT_VALUE, EXCEPT_VALUE, false);              // カーソル選択：なし

	// -----------------------------------------------------------
	// 晒し牌表示
	// -----------------------------------------------------------
	dparts->DispAllSarashiParts(600, PLY_YSTART+40,    // XY位置
	ply[pnum].naki_count,          // 鳴き合計面子数
	ply[pnum].naki_stat,           // 鳴き状態
	ply[pnum].naki_hai,            // 鳴き牌
	ply[pnum].naki_idx,            // チー時の頭牌
	ply[pnum].naki_aka             // 赤牌の数
	);

	// -----------------------------------------------------------
	// 向聴情報
	// -----------------------------------------------------------

	DrawFormatString(SPACE_XSIZE+150, PLY_YSTART-17, GetColor(255,255,255), "晒し牌%d面子 通常%d向聴 七対%d向聴 国士%d向聴", 
				ply[pnum].naki_count,
				ply[pnum].shanten_normal, 
				ply[pnum].shanten_chitoi, 
				ply[pnum].shanten_kokushi);

	// 自摸無し表記
	DrawFormatString(SPACE_XSIZE, PLY_YSTART+19, GetColor(255,255,255), "手牌情報：自摸無し");

	// 有効牌
	DrawFormatString(SPACE_XSIZE, PLY_YSTART+ 90, GetColor(255,255,255), "頭枚数%d枚"  , ply[pnum].atama_count);
	DrawFormatString(SPACE_XSIZE, PLY_YSTART+110, GetColor(255,255,255), "メンツ数%d枚", ply[pnum].mentsu_count);
	DrawFormatString(SPACE_XSIZE, PLY_YSTART+130, GetColor(255,255,255), "ターツ数%d枚", ply[pnum].taatsu_count);

	// 有効牌情報
	x=5;
	y=250;

	// 萬子
	DrawFormatString(x+127, y+10, GetColor(255,255,255), "m");
	for(int tmp_j = 0; tmp_j < 9; tmp_j++){
		if(ply[pnum].yuko_hai_13mai[tmp_j+1] == true){
			DrawFormatString(x+135+tmp_j*8, y+10, GetColor(255,255,255), "%d",tmp_j+1);
		}
	}

	// 筒子
	DrawFormatString(x+227, y+10, GetColor(255,255,255), "p");
	for(int tmp_j = 0; tmp_j < 9; tmp_j++){
		if(ply[pnum].yuko_hai_13mai[tmp_j+11] == true){
			DrawFormatString(x+235+tmp_j*8, y+10, GetColor(255,255,255), "%d",tmp_j+1);
		}
	}

	// 索子
	DrawFormatString(x+327, y+10, GetColor(255,255,255), "s");
	for(int tmp_j = 0; tmp_j < 9; tmp_j++){
		if(ply[pnum].yuko_hai_13mai[tmp_j+21] == true){
			DrawFormatString(x+335+tmp_j*8, y+10, GetColor(255,255,255), "%d",tmp_j+1);
		}
	}

	// 字牌
	DrawFormatString(x+427, y+10, GetColor(255,255,255), "z");
	for(int tmp_j = 0; tmp_j < 7; tmp_j++){
		if(ply[pnum].yuko_hai_13mai[tmp_j+31] == true){
			DrawFormatString(x+435+tmp_j*8, y+10, GetColor(255,255,255), "%d",tmp_j+1);
		}
	}

	// 鳴き情報
	DrawFormatString(SPACE_XSIZE, 300, GetColor(255,255,255), "鳴き候補枚数%d枚", ply[pnum].nakikoho_tbl_count);

	// 鳴きテーブル情報
	for(int tmp_i = 0; tmp_i < ply[pnum].nakikoho_tbl_count; tmp_i++){

		// 1段目・牌番号
		DrawFormatString(SPACE_XSIZE+tmp_i*100, 320, GetColor(255,255,255), "牌%d,IDX%d", ply[pnum].nakikoho_tbl_hai[tmp_i], ply[pnum].nakikoho_tbl_idx[tmp_i]);

		// 2段目・アクション
		if( ply[pnum].nakikoho_tbl_act[tmp_i] == ACTRON){
			DrawFormatString(SPACE_XSIZE+tmp_i*100, 340, GetColor(255,255,255), "Act:ロン");
		}else if( ply[pnum].nakikoho_tbl_act[tmp_i] == ACTPON){
			DrawFormatString(SPACE_XSIZE+tmp_i*100, 340, GetColor(255,255,255), "Act:ポン");
		}else if( ply[pnum].nakikoho_tbl_act[tmp_i] == ACTCHI){
			DrawFormatString(SPACE_XSIZE+tmp_i*100, 340, GetColor(255,255,255), "Act:チー");
		}else{
			DrawFormatString(SPACE_XSIZE+tmp_i*100, 340, GetColor(255,255,255), "Act:不明");
		}

		// 3段目・鳴きの有無
		if( ply[pnum].nakikoho_tbl_yesno[tmp_i] == true){
			DrawFormatString(SPACE_XSIZE+tmp_i*100, 360, GetColor(255,255,255), "鳴有");
		}else{
			DrawFormatString(SPACE_XSIZE+tmp_i*100, 360, GetColor(255,255,255), "鳴無");
		}

	}

	//-----------------------------------------------------------
	// 表示牌一覧
	//-----------------------------------------------------------
	DisplayOpenhai(tk, ply, pnum, SPACE_XSIZE, PLY_YSTART+450);

	//-----------------------------------------------------------
	// 処理時間
	//-----------------------------------------------------------
	DrawFormatString(SPACE_XSIZE, PLY_YSTART+490, GetColor(255,255,255), "処理時間(ply) :%dミリ秒",ply[pnum].action_timestamp2 - ply[pnum].action_timestamp1);    // 処理時間

}

/* ---------------------------------------------------------------------------------------------- */
// 捨牌候補情報
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplaySutekoho(MJSTkinfo *tk, MJSPlayer *ply, int pnum, int x, int y, int sutenum){

	// パーツ表示(候補牌)
	dparts->DispHai( x, y, ply[pnum].sutekoho_hai[sutenum], false, false, 0, 0);

	// 期待値
	DrawFormatString(x+25, y+STRING_YSIZE+2, GetColor(255,255,0), "期待値%6d", 1300);

	// 候補数表示
	DrawFormatString(x+25, y, GetColor(255,255,255), "%d向%2d種%2d枚%dp", 
		ply[pnum].sutekoho_shanten[sutenum], 
		ply[pnum].yuko_haishu_count[sutenum],
		ply[pnum].yuko_hai_count[sutenum],
		ply[pnum].sutekoho_priority[sutenum]);

	// 候補牌 - 萬子
	DrawFormatString(x+138, y, GetColor(255,255,255), "m");
	for(int tmp_j = 0; tmp_j < 9; tmp_j++){
		if(ply[pnum].yuko_hai[sutenum][tmp_j+1] == true){
			DrawFormatString(x+148+tmp_j*8, y, GetColor(255,255,255), "%d",tmp_j+1);
		}
	}

	// 候補牌 - 筒子
	DrawFormatString(x+238, y, GetColor(255,255,255), "p");
	for(int tmp_j = 0; tmp_j < 9; tmp_j++){
		if(ply[pnum].yuko_hai[sutenum][tmp_j+11] == true){
			DrawFormatString(x+248+tmp_j*8, y, GetColor(255,255,255), "%d",tmp_j+1);
		}
	}

	// 候補牌 - 索子
	DrawFormatString(x+338, y, GetColor(255,255,255), "s");
	for(int tmp_j = 0; tmp_j < 9; tmp_j++){
		if(ply[pnum].yuko_hai[sutenum][tmp_j+21] == true){
			DrawFormatString(x+348+tmp_j*8, y, GetColor(255,255,255), "%d",tmp_j+1);
		}
	}

	// 候補牌 - 字牌
	DrawFormatString(x+438, y, GetColor(255,255,255), "z");
	for(int tmp_j = 0; tmp_j < 7; tmp_j++){
		if(ply[pnum].yuko_hai[sutenum][tmp_j+31] == true){
			DrawFormatString(x+448+tmp_j*8, y, GetColor(255,255,255), "%d",tmp_j+1);
		}
	}

}

/* ---------------------------------------------------------------------------------------------- */
// 表示牌(open_haiparts)枚数
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplayOpenhai(MJSTkinfo *tk, MJSPlayer *ply, int pnum, int x, int y){

	// 候補牌 - 萬子
	DrawFormatString(x, y+20, GetColor(255,255,255), "m");
	for(int tmp_i = 1; tmp_i < 10; tmp_i++){
		DrawFormatString(x+10+tmp_i*8, y, GetColor(255,255,255), "%d",tmp_i);
		DrawFormatString(x+10+tmp_i*8, y+20, GetColor(255,255,255), "%d",ply[pnum].open_haiparts_count[tmp_i]);
	}

	// 候補牌 - 筒子
	DrawFormatString(x+100, y+20, GetColor(255,255,255), "p");
	for(int tmp_i = 1; tmp_i < 10; tmp_i++){
		DrawFormatString(x+110+tmp_i*8, y, GetColor(255,255,255), "%d",tmp_i);
		DrawFormatString(x+110+tmp_i*8, y+20, GetColor(255,255,255), "%d",ply[pnum].open_haiparts_count[tmp_i+10]);
	}

	// 候補牌 - 索子
	DrawFormatString(x+200, y+20, GetColor(255,255,255), "s");
	for(int tmp_i = 1; tmp_i < 10; tmp_i++){
		DrawFormatString(x+210+tmp_i*8, y, GetColor(255,255,255), "%d",tmp_i);
		DrawFormatString(x+210+tmp_i*8, y+20, GetColor(255,255,255), "%d",ply[pnum].open_haiparts_count[tmp_i+20]);
	}

	// 候補牌 - 字牌
	DrawFormatString(x+300, y+20, GetColor(255,255,255), "z");
	for(int tmp_i = 1; tmp_i < 8; tmp_i++){
		DrawFormatString(x+310+tmp_i*8, y, GetColor(255,255,255), "%d",tmp_i);
		DrawFormatString(x+310+tmp_i*8, y+20, GetColor(255,255,255), "%d",ply[pnum].open_haiparts_count[tmp_i+30]);
	}

}

/* ---------------------------------------------------------------------------------------------- */
// 局情報
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DispKyokuInfo(MJSTkinfo *tk, int kyoku_index){

	//-----------------------------------------------------------
	// デバグ用
	//-----------------------------------------------------------
	if (tk->kyoku[kyoku_index].kyoku < 0 || tk->kyoku[kyoku_index].kyoku > 11){
		tk->kyoku[kyoku_index].kyoku = 0;
	}

	//-----------------------------------------------------------
	// 半荘形式の表示
	//-----------------------------------------------------------
	if(tk->tkgame_type == TKGAME_HANCHAN){
		wsprintf(tmp_disp_msg,"半荘戦 %s %d本場", dparts->kyokutbl[tk->kyoku[kyoku_index].kyoku], tk->kyoku[kyoku_index].tsumibo);
	}else if(tk->tkgame_type == TKGAME_TONPU){
		wsprintf(tmp_disp_msg,"東風戦 %s %d本場", dparts->kyokutbl[tk->kyoku[kyoku_index].kyoku], tk->kyoku[kyoku_index].tsumibo);
	}else if(tk->tkgame_type == TKGAME_1KYOKU){
		wsprintf(tmp_disp_msg,"一局戦 %s %d本場", dparts->kyokutbl[tk->kyoku[kyoku_index].kyoku], tk->kyoku[kyoku_index].tsumibo);
	}else if(tk->tkgame_type == TKGAME_MJAI){
		wsprintf(tmp_disp_msg,"Mjai戦 %s %d本場", dparts->kyokutbl[tk->kyoku[kyoku_index].kyoku], tk->kyoku[kyoku_index].tsumibo);
	}else if(tk->tkgame_type == TKGAME_MAXID_TEST){
		wsprintf(tmp_disp_msg,"検証用 %s %d本場", dparts->kyokutbl[tk->kyoku[kyoku_index].kyoku], tk->kyoku[kyoku_index].tsumibo);
	}else if(tk->tkgame_type == TKGAME_VIEWER){
		wsprintf(tmp_disp_msg,"表示用 %s %d本場", dparts->kyokutbl[tk->kyoku[kyoku_index].kyoku], tk->kyoku[kyoku_index].tsumibo);
	}else{
		wsprintf(tmp_disp_msg,"不明　 %s %d本場", dparts->kyokutbl[tk->kyoku[kyoku_index].kyoku], tk->kyoku[kyoku_index].tsumibo);
	}

	dparts->DispString( SPACE_XSIZE, 8 + STRING_YSIZE * 0, tmp_disp_msg);

	/*-----------------------------------------------------------*/
	// モード表示
	/*-----------------------------------------------------------*/
	if( tk->ply_hum_mode == 0 ){
		DrawFormatString(SPACE_XSIZE+230, 8 + STRING_YSIZE * 0, GetColor(255,255,255), "4Com戦");
	}else{
		DrawFormatString(SPACE_XSIZE+230, 8 + STRING_YSIZE * 0, GetColor(255,255,255), "Hum戦 ");
	}

	//-----------------------------------------------------------
	// リーチ棒・残り牌表示
	//-----------------------------------------------------------
	wsprintf(tmp_disp_msg,"リーチ棒%d 残牌%d 嶺上牌%d", tk->kyoku[kyoku_index].riichbo, tk->remain_hai_count, tk->remain_rinshan_count);
	dparts->DispString( SPACE_XSIZE, 8 + STRING_YSIZE * 1, tmp_disp_msg);

	//-----------------------------------------------------------
	// 最大赤牌枚数
	//-----------------------------------------------------------
	wsprintf(tmp_disp_msg,"MAX赤 萬%d 筒%d 索%d", tk->aka_max[0], tk->aka_max[1], tk->aka_max[2]);
	dparts->DispString( SPACE_XSIZE+230, 8 + STRING_YSIZE * 1, tmp_disp_msg);

	//-----------------------------------------------------------
	// 開始時刻
	//-----------------------------------------------------------
	wsprintf(tmp_disp_msg,"開始:%s %s", tk->startdate, tk->starttime);
	dparts->DispString( SPACE_XSIZE, 8 + STRING_YSIZE * 2, tmp_disp_msg);

	//-----------------------------------------------------------
	// 乱数シード
	//-----------------------------------------------------------
//	if(tk->kyoku[kyoku_index].seed_num != 0){
		wsprintf(tmp_disp_msg,"乱数SEED:%10d", tk->kyoku[kyoku_index].seed_num);
		dparts->DispString( SPACE_XSIZE + 230, 8 + STRING_YSIZE * 2, tmp_disp_msg);
//	}

}

/* ---------------------------------------------------------------------------------------------- */
// プレーヤ情報
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DispPlyInfo(MJSTkinfo *tk, int kyoku_index, int pnum){

	//-----------------------------------------------------------
	// 1行目
	//-----------------------------------------------------------

	// プレーヤ名
	DrawFormatString(800, PLY_YSTART+pnum*PLY_YSIZE, GetColor(255,255,255), "[席%d]%s", pnum+1, tk->plyname[pnum]);

	// 家表示
	if(tk->kyoku[kyoku_index].ie[pnum] == 0){
		DrawFormatString(800, PLY_YSTART+pnum*PLY_YSIZE + STRING_YSIZE, GetColor(255,255,255), "東家");
	}else if(tk->kyoku[kyoku_index].ie[pnum] == 1){
		DrawFormatString(800, PLY_YSTART+pnum*PLY_YSIZE + STRING_YSIZE, GetColor(255,255,255), "南家");
	}else if(tk->kyoku[kyoku_index].ie[pnum] == 2){
		DrawFormatString(800, PLY_YSTART+pnum*PLY_YSIZE + STRING_YSIZE, GetColor(255,255,255), "西家");
	}else if(tk->kyoku[kyoku_index].ie[pnum] == 3){
		DrawFormatString(800, PLY_YSTART+pnum*PLY_YSIZE + STRING_YSIZE, GetColor(255,255,255), "北家");
	}else{
		DrawFormatString(800, PLY_YSTART+pnum*PLY_YSIZE + STRING_YSIZE, GetColor(255,255,255), "不明");
	}

	//-----------------------------------------------------------
	// 2行目
	//-----------------------------------------------------------

	// 得点
	DrawFormatString(840, PLY_YSTART+pnum*PLY_YSIZE + STRING_YSIZE, GetColor(255,255,255), "%6d", tk->kyoku[kyoku_index].ply_kyoku_start_score[pnum]);

	//-----------------------------------------------------------
	// 3行目
	//-----------------------------------------------------------

	// テンパイ情報
	if (tk->stat == RYUKYOKU){

		// テンパイ結果を表示する
		if(tk->kyoku[kyoku_index].ply_agari_yk[0].ply_tempai_flg[pnum] == true){
			DrawFormatString(800, PLY_YSTART+pnum*PLY_YSIZE + STRING_YSIZE*2, GetColor(255,255,255), "聴牌");
		}else{
			DrawFormatString(800, PLY_YSTART+pnum*PLY_YSIZE + STRING_YSIZE*2, GetColor(255,255,255), "不聴");
		}

			// テンパイ人数
			DrawFormatString(800, PLY_YSTART+4*PLY_YSIZE, GetColor(255,255,255), "聴牌%d人", tk->kyoku[kyoku_index].ply_agari_yk[0].ply_tempai_count);

	// プレーヤID
	}else{

		// Mjaiモードであるなら
		if(tk->tkgame_type == TKGAME_MJAI){
			DrawFormatString(800, PLY_YSTART+pnum*PLY_YSIZE + STRING_YSIZE*2, GetColor(255,255,255), "Ply_id:%d", tk->ply_mjai_id[pnum]);
		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// プレーヤアクション情報表示
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DispActNumInfo(MJSTkinfo *tk, int x, int y, int kyoku_index, int actid){

	// 局情報
	DrawFormatString(x   , y-32, GetColor(255,255,255), "局ID %2d"  ,kyoku_index );

	// アクションID
	DrawFormatString(x+80, y-32, GetColor(255,255,255), "ACTID %3d" ,actid);

	// アクション情報の値があれば
	if (actid > 0){

		// TKINFOのステータス情報
		DisplayTkinfoDetail_sub_tkstat(tk, tk->kyoku[kyoku_index].act_stat[actid], x, y-16);

		// 牌情報表示・赤牌
		if ( tk->kyoku[kyoku_index].act_aka[actid] == true){
			DrawFormatString(x+80, y-16, GetColor(255,255,255), "牌%2d赤,IDX%2d", tk->kyoku[kyoku_index].act_hai[actid], 0);
		}else{
			DrawFormatString(x+80, y-16, GetColor(255,255,255), "牌%2d黒,IDX%2d", tk->kyoku[kyoku_index].act_hai[actid], 0);
		}

/*
		if ( tk->kyoku[kyoku_index].act_aka[actid] == true){
			DrawFormatString(x+80, y-16, GetColor(255,255,255), "牌番号：%3d　赤牌　", tk->kyoku[kyoku_index].act_hai[actid]);
		}else{
			DrawFormatString(x+80, y-16, GetColor(255,255,255), "牌番号：%3d　通常牌", tk->kyoku[kyoku_index].act_hai[actid]);
		}
*/
		// アクションプレーヤ表示
		       if( tk->kyoku[kyoku_index].act_ply[actid] > -1 && tk->kyoku[kyoku_index].act_ply[actid] < 4){
			DrawFormatString(x, y, GetColor(255,255,255), "Act_ply  ：[席%d]", tk->kyoku[kyoku_index].act_ply[actid]+1 );
		 }else if( tk->kyoku[kyoku_index].act_ply[actid] == 4){
			DrawFormatString(x, y, GetColor(255,255,255), "Act_ply  ：[ - ]", tk->kyoku[kyoku_index].act_ply[actid]+1 );
		 }else {
			DrawFormatString(x, y, GetColor(255,255,255), "Act_ply  ：[例外]", tk->kyoku[kyoku_index].act_ply[actid]+1 );
		 }

		// リアクションプレーヤ表示
		      if( tk->kyoku[kyoku_index].react_ply[actid] > -1 && tk->kyoku[kyoku_index].react_ply[actid] < 4){
			DrawFormatString(x+150, y, GetColor(255,255,255), "ReAct_ply：[席%d]", tk->kyoku[kyoku_index].react_ply[actid]+1 );
		}else if( tk->kyoku[kyoku_index].react_ply[actid] == 4){
			DrawFormatString(x+150, y, GetColor(255,255,255), "ReAct_ply：[ - ]",  tk->kyoku[kyoku_index].react_ply[actid]+1 );
		}else{
			DrawFormatString(x+150, y, GetColor(255,255,255), "ReAct_ply：[例外]", tk->kyoku[kyoku_index].react_ply[actid]+1 );
		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// TKINFO情報の表示
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DispTakuStat(MJSTkinfo *tk, int x, int y){

	// TKINFOのステータス情報
	DisplayTkinfoDetail_sub_tkstat(tk, tk->stat, x, y);

	// 順番
	DrawFormatString(x+90, y, GetColor(255,255,255), "順番：[席%d]", tk->ply_turn+1);

	// Plyアクション
	DisplayTkinfoDetail_sub_plyactInfo(tk, tk->ply_act, x+250, y);

	// Hum捨牌位置番号
	DrawFormatString(x+400, y, GetColor(255,255,255), "Hum捨位置：%3d" ,tk->ply_tbl_hum_sutehai_statnum);

}

/* ---------------------------------------------------------------------------------------------- */
// 卓情報クラス(tkinfoクラス)情報
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DispTkInfoStat(MJSTkinfo *tk, int x, int y){

	// プレーヤごとの鳴きアクション
	for(int tmp_pnum = 0; tmp_pnum < 4; tmp_pnum++){
		DisplayTkinfoDetail_sub_ply_actnaki_info(tk, x+255*tmp_pnum, y, tmp_pnum);
	}

	// プレーヤごとの手牌情報
	for(int tmp_pnum = 0; tmp_pnum < 4; tmp_pnum++){
		DisplayTkinfoDetail_sub_tehai(tk, x, y+STRING_YSIZE*(1+tmp_pnum),tmp_pnum);
	}

	// 赤牌枚数、向聴数：席1
	DrawFormatString(x, y+STRING_YSIZE*5, GetColor(255,255,255), "[席1]赤%d,%d,%d鳴%d総%2d通%2d七%2d国%2d待%2d:", 
	       tk->ply_act_aka_count[0][0], tk->ply_act_aka_count[0][1], tk->ply_act_aka_count[0][2],
	       tk->naki_count_none_kakan[0], tk->shanten_total[0], tk->shanten_normal[0], tk->shanten_chitoi[0],tk->shanten_kokushi[0], tk->ply_act_machi_count[0]);

	// 待牌：席1
	for(int tmp_i = 0; tmp_i < tk->ply_act_machi_count[0]; tmp_i++){
		DrawFormatString(x+320+tmp_i*25,   y+STRING_YSIZE*5, GetColor(255,255,255), "%2d,", tk->ply_act_machi_hai[0][tmp_i]);
	}

	// 赤牌枚数、向聴数：席2
	DrawFormatString(x+500, y+STRING_YSIZE*5, GetColor(255,255,255), "[席2]赤%d,%d,%d鳴%d総%2d通%2d七%2d国%2d待%2d:", 
	       tk->ply_act_aka_count[1][0], tk->ply_act_aka_count[1][1], tk->ply_act_aka_count[1][2],
	       tk->naki_count_none_kakan[1], tk->shanten_total[1], tk->shanten_normal[1], tk->shanten_chitoi[1],tk->shanten_kokushi[1], tk->ply_act_machi_count[1]);

	// 待牌：席2
	for(int tmp_i = 0; tmp_i < tk->ply_act_machi_count[1]; tmp_i++){
		DrawFormatString(x+820+tmp_i*25,   y+STRING_YSIZE*5, GetColor(255,255,255), "%2d,", tk->ply_act_machi_hai[1][tmp_i]);
	}

	// 赤牌枚数、向聴数：席3
	DrawFormatString(x, y+STRING_YSIZE*6, GetColor(255,255,255), "[席3]赤%d,%d,%d鳴%d総%2d通%2d七%2d国%2d待%2d:", 
	       tk->ply_act_aka_count[2][0], tk->ply_act_aka_count[2][1], tk->ply_act_aka_count[2][2],
	       tk->naki_count_none_kakan[2], tk->shanten_total[2], tk->shanten_normal[2], tk->shanten_chitoi[2],tk->shanten_kokushi[2], tk->ply_act_machi_count[2]);

	// 待牌：席3
	for(int tmp_i = 0; tmp_i < tk->ply_act_machi_count[2]; tmp_i++){
		DrawFormatString(x+320+tmp_i*25,   y+STRING_YSIZE*6, GetColor(255,255,255), "%2d,", tk->ply_act_machi_hai[2][tmp_i]);
	}

	// 赤牌枚数、向聴数：席4
	DrawFormatString(x+500, y+STRING_YSIZE*6, GetColor(255,255,255), "[席4]赤%d,%d,%d鳴%d総%2d通%2d七%2d国%2d待%2d:", 
	       tk->ply_act_aka_count[3][0], tk->ply_act_aka_count[3][1], tk->ply_act_aka_count[3][2],
	       tk->naki_count_none_kakan[3], tk->shanten_total[3], tk->shanten_normal[3], tk->shanten_chitoi[3],tk->shanten_kokushi[3], tk->ply_act_machi_count[3]);

	// 待牌：席4
	for(int tmp_i = 0; tmp_i < tk->ply_act_machi_count[3]; tmp_i++){
		DrawFormatString(x+820+tmp_i*25,   y+STRING_YSIZE*6, GetColor(255,255,255), "%2d,", tk->ply_act_machi_hai[3][tmp_i]);
	}

}

/* ---------------------------------------------------------------------------------------------- */
// GUIクラス情報
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DispGuiInfo(MJSGui *gui, int x, int y){

	//-----------------------------------------------------------
	// GUIステータス(0行目)
	//-----------------------------------------------------------

	// GUI情報・メインステータス
	if(gui->gui_main_stat == GUI_NO_MAIN_STAT){
		DrawFormatString(x, y, GetColor(255,255,255), "[Main]モード未設定");
	}else if(gui->gui_main_stat == GUI_PLAYING_INIT){
		DrawFormatString(x, y, GetColor(255,255,255), "[Main]プレイモード前処理");
	}else if(gui->gui_main_stat == GUI_PLAYING){
		DrawFormatString(x, y, GetColor(255,255,255), "[Main]プレイモード");
	}else if(gui->gui_main_stat == GUI_PLAYING_POST){
		DrawFormatString(x, y, GetColor(255,255,255), "[Main]プレイモード後処理");
	}else if(gui->gui_main_stat == GUI_RUNNING_INIT){
		DrawFormatString(x, y, GetColor(255,255,255), "[Main]検証モード前処理");
	}else if(gui->gui_main_stat == GUI_RUNNING){
		DrawFormatString(x, y, GetColor(255,255,255), "[Main]検証モード");
	}else if(gui->gui_main_stat == GUI_RUNNING_POST){
		DrawFormatString(x, y, GetColor(255,255,255), "[Main]検証モード後処理");
	}else if(gui->gui_main_stat == GUI_CLIENT_INIT){
		DrawFormatString(x, y, GetColor(255,255,255), "[Main]クライアント前処理");
	}else if(gui->gui_main_stat == GUI_CLIENT){
		DrawFormatString(x, y, GetColor(255,255,255), "[Main]クライアントモード");
	}else if(gui->gui_main_stat == GUI_CLIENT_POST){
		DrawFormatString(x, y, GetColor(255,255,255), "[Main]クライアント後処理");
	}else{
		DrawFormatString(x, y, GetColor(255,255,255), "[Main]例外処理");
	}

	// GUI情報・卓モード
	DisplayGuiTakuMode(gui, x+250, y);

	// GUI情報・手牌モード
	DisplayGuiTehaiMode(gui, x+400, y);

	//-----------------------------------------------------------
	// 鳴き牌候補情報(1行目)
	//-----------------------------------------------------------

	// 暗槓情報
	if(gui->gui_taku_mode == COMMON_PLAY_MODE){
		DrawFormatString( x,    y+STRING_YSIZE, GetColor(255,255,255), "[暗槓]%2d,%2d,%2d", gui->naki_ankan_hai[0], gui->naki_ankan_hai[1], gui->naki_ankan_hai[2]);
	}

	// 加槓情報
	if(gui->gui_taku_mode == COMMON_PLAY_MODE){
		DrawFormatString( x+130, y+STRING_YSIZE, GetColor(255,255,255), "[加槓]%2d,%2d,%2d", gui->naki_kakan_hai[0], gui->naki_kakan_hai[1], gui->naki_kakan_hai[2]);
	}

	// GUI情報・チー候補の情報
	DisplayGuiChiKoho(gui, x+260, y+STRING_YSIZE);

}

/* ---------------------------------------------------------------------------------------------- */
// GUI情報・GUI卓モード
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplayGuiTakuMode(MJSGui *gui, int x, int y){

	// GUI情報・GUI卓モード表示
	      if(gui->gui_taku_mode == COMMON_PLAY_MODE){
		DrawFormatString(x, y, GetColor(255,255,255), "[画面]手牌表示　");
	}else if( gui->gui_taku_mode == COMMON_BAGIME_MODE){
		DrawFormatString(x, y, GetColor(255,255,255), "[画面]場決め　　");
	}else if( gui->gui_taku_mode == COMMON_TAKURESULT_MODE){
		DrawFormatString(x, y, GetColor(255,255,255), "[画面]卓結果表示");
	}else if(gui->gui_taku_mode == COMMON_TKINFO_MODE){
		DrawFormatString(x, y, GetColor(255,255,255), "[画面]TK詳細　　");
	}else{
		DrawFormatString(x, y, GetColor(255,255,255), "[画面]例外処理　");
	}

}

/* ---------------------------------------------------------------------------------------------- */
// GUI情報・GUI手牌モード
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplayGuiTehaiMode(MJSGui *gui, int x, int y){

	if(gui->gui_ply_tehai_mode == TEHAI_NORMAL){
		DrawFormatString(x, y, GetColor(255,255,255), "[手牌]通常手牌　");
	}else if(gui->gui_ply_tehai_mode == TEHAI_RIICHI_SUTEHAI){
		DrawFormatString(x, y, GetColor(255,255,255), "[手牌]リーチ選択");
	}else if(gui->gui_ply_tehai_mode == TEHAI_RIICHI_YUKO){
		DrawFormatString(x, y, GetColor(255,255,255), "[手牌]リーチ有効");
	}else if(gui->gui_ply_tehai_mode == TEHAI_ANKAN_KAKAN_SELECT){
		DrawFormatString(x, y, GetColor(255,255,255), "[手牌]暗加槓選択");
	}else if(gui->gui_ply_tehai_mode == TEHAI_CHI_SELECT){
		DrawFormatString(x, y, GetColor(255,255,255), "[手牌]チー選択　");
	}else{
		DrawFormatString(x, y, GetColor(255,255,255), "[手牌]例外処理　");
	}

}

/* ---------------------------------------------------------------------------------------------- */
// GUI情報・チー候補情報
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplayGuiChiKoho(MJSGui *gui, int x, int y){

	// チー候補の個数
	DrawFormatString(x, y, GetColor(255,255,255), "[チ牌]%d枚",gui->chihai_count);

	// チー牌情報
	for(int tmp_i = 0; tmp_i < CHI_KOHO_COUNT_MAX; tmp_i++){
		// 有効であれば
//		if(gui->chihai_mode[tmp_i] == true){
			if (gui->chi_aka_count[tmp_i] > 0){
				DrawFormatString(x+tmp_i*90+80, y, GetColor(255,255,255), "%d:頭:%2d赤|", tmp_i, gui->chi_idx_hai[tmp_i]);
			}else{
				DrawFormatString(x+tmp_i*90+80, y, GetColor(255,255,255), "%d:頭:%2d黒|", tmp_i, gui->chi_idx_hai[tmp_i]);
			}
//		}
	}

}

/* ---------------------------------------------------------------------------------------------- */
// GUI情報・牌譜ログ形式
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplayGuiLogType(MJSGui *gui, int x, int y){

	if( gui->gui_logtype == GUI_LOG_MJAILOG){
		DrawFormatString(x, y, GetColor(255,255,255), "[ログ形式]MJAIログ");
	}else if( gui->gui_logtype == GUI_LOG_MJSCORE){
		DrawFormatString(x, y, GetColor(255,255,255), "[ログ形式]東風荘ログ");
	}

}

/* ---------------------------------------------------------------------------------------------- */
// 手牌ラインメッセージ
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DispTehaiLineMessage(MJSTkinfo *tk, MJSGui *gui, int x, int y){

	// gui_taku_modeモードごとにメッセージ表示
	if(gui->gui_taku_mode == COMMON_PLAY_MODE){

		// gui_ply_tehai_modeモードごとにメッセージ表示
		if(gui->gui_ply_tehai_mode == TEHAI_NORMAL || gui->gui_ply_tehai_mode == TEHAI_RIICHI_YUKO){

			// GUIモードの場合
			if( tk->ply_hum_mode == 1 && 
			    tk->kyoku[tk->kyoku_index].act_ply[tk->kyoku[tk->kyoku_index].act_count] == HUM_PLY_SEKI_NUM ){

				// HUM自摸和了
				if( tk->kyoku[tk->kyoku_index].act_stat[tk->kyoku[tk->kyoku_index].act_count] == PLYTSUMOAGARI){
					DrawFormatString(x, y,    GetColor(255,255,255), "おめでとうございます");
					DrawFormatString(x, y+STRING_YSIZE, GetColor(255,255,255), "あなたの自摸和了です");

				// HUMロン和了
				}else if( tk->kyoku[tk->kyoku_index].act_stat[tk->kyoku[tk->kyoku_index].act_count] == PLYACTRON){
					DrawFormatString(x, y,    GetColor(255,255,255), "おめでとうございます");
					DrawFormatString(x, y+STRING_YSIZE, GetColor(255,255,255), "あなたのロン和了です");

				// 自摸アクションの場合
				}else if( tk->kyoku[tk->kyoku_index].act_stat[tk->kyoku[tk->kyoku_index].act_count] == PLYACTTSUMO ||
				          tk->kyoku[tk->kyoku_index].act_stat[tk->kyoku[tk->kyoku_index].act_count] == PLYRINSHAN  ){

					// HUMの捨牌メッセージ
					if(gui->gui_ply_tehai_mode == TEHAI_RIICHI_YUKO){
						DrawFormatString(x, y,    GetColor(255,255,255), "リーチ宣言してます");
						DrawFormatString(x, y+STRING_YSIZE, GetColor(255,255,255), "自動捨牌をします");
					}else{
						DrawFormatString(x, y, GetColor(255,255,255), "捨牌をしてください");
					}

				// 鳴き後のアクション
				// }else if( tk->stat == PLYACTSUTEWAIT || tk->stat == PLYACTNAKISUTEWAIT){
				}else if( tk->kyoku[tk->kyoku_index].act_stat[tk->kyoku[tk->kyoku_index].act_count] == PLYACTPON ||
				          tk->kyoku[tk->kyoku_index].act_stat[tk->kyoku[tk->kyoku_index].act_count] == PLYACTCHI ){
					DrawFormatString(x, y, GetColor(255,255,255), "鳴き後の捨牌をしてください");

				// 捨牌アクションの場合
				}else if( tk->kyoku[tk->kyoku_index].act_stat[tk->kyoku[tk->kyoku_index].act_count] == PLYACTSUTE ||
				          tk->kyoku[tk->kyoku_index].act_stat[tk->kyoku[tk->kyoku_index].act_count] == PLYACTTSUMOGIRI ||
				          tk->kyoku[tk->kyoku_index].act_stat[tk->kyoku[tk->kyoku_index].act_count] == PLYACTNAKISUTE  ){
					DrawFormatString(x, y, GetColor(255,255,255), "捨牌しました");

				// 例外処理
				}else{
					DrawFormatString(x, y, GetColor(255,255,255), "例外処理：act_HUM_PLY_SEKI_NUM");
				}

			// 他が手番の場合
			}else{

				// COM自摸和了
				if( tk->kyoku[tk->kyoku_index].act_stat[tk->kyoku[tk->kyoku_index].act_count] == PLYTSUMOAGARI ){
					DrawFormatString(x, y, GetColor(255,255,255), "COMプレーヤが自摸和了です");

				// COMロン和了
				}else if( tk->kyoku[tk->kyoku_index].act_stat[tk->kyoku[tk->kyoku_index].act_count] == PLYACTRON ){

					// 振りプレーヤがHUM
					if( tk->ply_hum_mode == 1 && tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].furikomi_ply_num == HUM_PLY_SEKI_NUM){
						DrawFormatString(x, y, GetColor(255,255,255), "残念！あなたが振りこみました");
					}else{
						DrawFormatString(x, y, GetColor(255,255,255), "COMプレーヤがロン和了です");
					}

				// その他処理
				}else{
					DrawFormatString(x, y, GetColor(255,255,255), "COMプレーヤ処理中");
				}

			}

		// リーチモード
		}else if(gui->gui_ply_tehai_mode == TEHAI_RIICHI_SUTEHAI){
			DrawFormatString(x, y, GetColor(255,255,255), "リーチ宣言後の捨牌を選択してください");
		// チー宣言モード
		}else if(gui->gui_ply_tehai_mode == TEHAI_CHI_SELECT){
			DrawFormatString(x, y, GetColor(255,255,255), "チー牌を宣言してください");
		// 例外処理
		}else{
			DrawFormatString(x, y, GetColor(255,255,255), "例外処理：gui_ply_tehai_mode");
		}

	// 終了確認メッセージ
	}else if(gui->gui_taku_mode == COMMON_END_CHECK_MODE){
		DrawFormatString(x, y, GetColor(255,255,255), "処理を終了します");
	// 例外処理
	}else{
		DrawFormatString(x, y, GetColor(255,255,255), "例外処理：gui_taku_mode");
	}

}

/* ---------------------------------------------------------------------------------------------- */
// アクション手牌の表示(COM用スクエア)
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DispActTehaiCom_square(MJSTkinfo *tk, MJSGui *gui, int kyoku_index, int actid, int pnum, int msx, int msy){

	// チェックフラグ
	int tmp_chi_num = 0;
	int sute_chk    = 0;

	// 牌のX位置表示用
	int xstat = 0;

	// ----------------------------------------
	// アクションプレート表示
	// ----------------------------------------
	DispTakuActplt(tk, gui, kyoku_index, actid, pnum);

	// ----------------------------------------
	// 席情報表示
	// ----------------------------------------

	// 席情報設定
	wsprintf(tmp_disp_msg,"[席%d]%s", pnum+1, tk->plyname[pnum]);

	// 手牌パーツの表示(Right)
	if( pnum == (gui->disp_down_tehai_pnum+1) % 4){

		// 席情報_RIGHT
		dparts->DispName_right( gui->tehai_right_x - STRING_YSIZE - NAME_TEHAI_RANGE, 
	                gui->tehai_right_y + HAI_XSIZE * TEHAI_MAX + HAI_XSIZE+10, 
	                tmp_disp_msg);

	}else if( pnum == (gui->disp_down_tehai_pnum+2) % 4){

		// 席情報_UP
		dparts->DispName_up( gui->tehai_up_x + HAI_XSIZE * TEHAI_MAX, 
	             gui->tehai_up_y + HAI_YSIZE + STRING_YSIZE + NAME_TEHAI_RANGE, 
	             tmp_disp_msg);

	}else if( pnum == (gui->disp_down_tehai_pnum+3) % 4){

		// 席情報_LEFT
		dparts->DispName_left( gui->tehai_left_x + HAI_YSIZE + STRING_YSIZE + NAME_TEHAI_RANGE, 
	               gui->tehai_left_y,
	               tmp_disp_msg);

	}else if( pnum == gui->disp_down_tehai_pnum){

		// 席情報_DOWN
		dparts->DispString( gui->tehai_x, 
	                    gui->tehai_y - STRING_YSIZE - NAME_TEHAI_RANGE, 
	                   tmp_disp_msg);

	}

	// -----------------------------------------------------------
	// 1.手牌表示：自摸時
	// -----------------------------------------------------------
	if ( ( tk->kyoku[kyoku_index].act_stat[actid] == PLYACTTSUMO || 
	       tk->kyoku[kyoku_index].act_stat[actid] == PLYRINSHAN  || 
	       tk->kyoku[kyoku_index].act_stat[actid] == PLYTSUMOAGARI ) &&
	       tk->kyoku[kyoku_index].act_ply[actid]  == pnum ){

		// 手牌パーツの表示(Right)
		if( pnum == (gui->disp_down_tehai_pnum+1) % 4){
			dparts->DispActTehaiParts_right( gui->tehai_right_x, gui->tehai_right_y,
				                        tk->ply_act_tehaicount[pnum],
					                    tk->ply_act_tehaitbl[pnum],
					                    tk->ply_act_tehai_tbl_aka[pnum], 
					                    tk->kyoku[kyoku_index].act_hai[actid],
					                    tk->kyoku[kyoku_index].act_aka[actid],
					                    EXCEPT_VALUE);
		// 手牌パーツの表示(UP)
		}else if( pnum == (gui->disp_down_tehai_pnum+2) % 4){
			dparts->DispActTehaiParts_up( gui->tehai_up_x, gui->tehai_up_y,
					                   tk->ply_act_tehaicount[pnum], 
					                   tk->ply_act_tehaitbl[pnum],
					                   tk->ply_act_tehai_tbl_aka[pnum], 
					                   tk->kyoku[kyoku_index].act_hai[actid],
					                   tk->kyoku[kyoku_index].act_aka[actid],
					                   EXCEPT_VALUE);
		// 手牌パーツの表示(Left)
		}else if( pnum == (gui->disp_down_tehai_pnum+3) % 4){
				dparts->DispActTehaiParts_left( gui->tehai_left_x, gui->tehai_left_y,
				                        tk->ply_act_tehaicount[pnum],
					                   tk->ply_act_tehaitbl[pnum],
					                   tk->ply_act_tehai_tbl_aka[pnum], 
					                   tk->kyoku[kyoku_index].act_hai[actid],
					                   tk->kyoku[kyoku_index].act_aka[actid],
					                   EXCEPT_VALUE);
		// 手牌パーツの表示(Down)
		}else if( pnum == gui->disp_down_tehai_pnum){
				dparts->DispActTehaiParts(gui->tehai_x, gui->tehai_y,
				                       tk->ply_act_tehaicount[pnum], 
					                   tk->ply_act_tehaitbl[pnum],
					                   tk->ply_act_tehai_tbl_aka[pnum], 
					                   tk->kyoku[kyoku_index].act_hai[actid],
					                   tk->kyoku[kyoku_index].act_aka[actid],
					                   EXCEPT_VALUE,
					                   EXCEPT_VALUE,
					                   EXCEPT_VALUE,
					                   false);
		}

	// ----------------------------------------
	// 2.手牌表示：自摸時リーチ宣言
	// ----------------------------------------
	}else if( tk->kyoku[kyoku_index].act_stat[actid] == PLYACTRIICH && tk->kyoku[kyoku_index].act_ply[actid] == pnum ){

		// 手牌パーツの表示(Right)
		if( pnum == (gui->disp_down_tehai_pnum+1) % 4){
			dparts->DispActTehaiParts_right( gui->tehai_right_x, gui->tehai_right_y,
				                        tk->ply_act_tehaicount[pnum],
					                    tk->ply_act_tehaitbl[pnum],
					                    tk->ply_act_tehai_tbl_aka[pnum], 
					                    tk->kyoku[kyoku_index].act_hai[actid-1],
					                    tk->kyoku[kyoku_index].act_aka[actid-1],
					                    EXCEPT_VALUE);
		// 手牌パーツの表示(UP)
		}else if( pnum == (gui->disp_down_tehai_pnum+2) % 4){
			dparts->DispActTehaiParts_up( gui->tehai_up_x, gui->tehai_up_y,
					                   tk->ply_act_tehaicount[pnum], 
					                   tk->ply_act_tehaitbl[pnum],
					                   tk->ply_act_tehai_tbl_aka[pnum], 
					                   tk->kyoku[kyoku_index].act_hai[actid-1],
					                   tk->kyoku[kyoku_index].act_aka[actid-1],
					                   EXCEPT_VALUE);
		// 手牌パーツの表示(Left)
		}else if( pnum == (gui->disp_down_tehai_pnum+3) % 4){
			dparts->DispActTehaiParts_left( gui->tehai_left_x, gui->tehai_left_y,
				                        tk->ply_act_tehaicount[pnum],
					                   tk->ply_act_tehaitbl[pnum],
					                   tk->ply_act_tehai_tbl_aka[pnum], 
					                   tk->kyoku[kyoku_index].act_hai[actid-1],
					                   tk->kyoku[kyoku_index].act_aka[actid-1],
					                   EXCEPT_VALUE);
		// 手牌パーツの表示(Down)
		}else if( pnum == gui->disp_down_tehai_pnum){
			dparts->DispActTehaiParts(gui->tehai_x, gui->tehai_y,
				                       tk->ply_act_tehaicount[pnum], 
					                   tk->ply_act_tehaitbl[pnum],
					                   tk->ply_act_tehai_tbl_aka[pnum], 
					                   tk->kyoku[kyoku_index].act_hai[actid-1],
					                   tk->kyoku[kyoku_index].act_aka[actid-1],
					                   EXCEPT_VALUE,
					                   EXCEPT_VALUE,
					                   EXCEPT_VALUE,
					                   false);
		}

	// ----------------------------------------
	// 3.手牌表示：自摸捨牌時
	// ----------------------------------------
	}else if( tk->kyoku[kyoku_index].act_ply[actid] == pnum && tk->kyoku[kyoku_index].act_stat[actid] == PLYACTSUTE){

		// 手牌パーツの表示(Right)
		if( pnum == (gui->disp_down_tehai_pnum+1) % 4){
			dparts->DispActTehaiParts_right( gui->tehai_right_x,                // 01:X座標
				                             gui->tehai_right_y,                // 02:Y座標
				                        tk->ply_act_tehaicount[pnum],           // 03:手牌数
					                    tk->ply_act_tehaitbl[pnum],             
					                    tk->ply_act_tehai_tbl_aka[pnum], 
					                    tk->ply_act_tsumo[pnum],
					                    tk->ply_act_tsumo_aka[pnum],
					                    tk->ply_tbl_com_sutehai_statnum[pnum]);

		// 手牌パーツの表示(UP)
		}else if( pnum == (gui->disp_down_tehai_pnum+2) % 4){
					dparts->DispActTehaiParts_up( gui->tehai_up_x, gui->tehai_up_y,
					                   tk->ply_act_tehaicount[pnum], 
					                   tk->ply_act_tehaitbl[pnum],
					                   tk->ply_act_tehai_tbl_aka[pnum], 
					                   tk->ply_act_tsumo[pnum],
					                   tk->ply_act_tsumo_aka[pnum],
					                   tk->ply_tbl_com_sutehai_statnum[pnum]);

		// 手牌パーツの表示(Left)
		}else if( pnum == (gui->disp_down_tehai_pnum+3) % 4){
					dparts->DispActTehaiParts_left(  gui->tehai_left_x, gui->tehai_left_y,
				                        tk->ply_act_tehaicount[pnum],
					                    tk->ply_act_tehaitbl[pnum],
					                    tk->ply_act_tehai_tbl_aka[pnum], 
					                    tk->ply_act_tsumo[pnum],
					                    tk->ply_act_tsumo_aka[pnum],
					                    tk->ply_tbl_com_sutehai_statnum[pnum]);

		// 手牌パーツの表示(Down)
		}else if( pnum == gui->disp_down_tehai_pnum){
					dparts->DispActTehaiParts(gui->tehai_x, gui->tehai_y,
					                   tk->ply_act_tehaicount[pnum], 
					                   tk->ply_act_tehaitbl[pnum],
					                   tk->ply_act_tehai_tbl_aka[pnum], 
					                   tk->ply_act_tsumo[pnum],
					                   tk->ply_act_tsumo_aka[pnum],
					                   tk->ply_tbl_com_sutehai_statnum[pnum],
					                   EXCEPT_VALUE,
					                   EXCEPT_VALUE,
					                   false);
		}

	// -----------------------------------------------------------
	// 5.手牌表示：鳴き捨牌時
	// -----------------------------------------------------------
	}else if( tk->kyoku[kyoku_index].act_stat[actid] == PLYACTNAKISUTE &&
	          tk->kyoku[kyoku_index].act_ply[actid]  == pnum       ){

		// 手牌パーツの表示(Right)
		if( pnum == (gui->disp_down_tehai_pnum+1) % 4){
					dparts->DispActTehaiParts_right( gui->tehai_right_x,        // 01:X座標
				                                     gui->tehai_right_y,        // 02:Y座標
					                    tk->ply_act_tehaicount[pnum],           // 03:手牌数
					                    tk->ply_act_tehaitbl[pnum],             
					                    tk->ply_act_tehai_tbl_aka[pnum], 
					                    EXCEPT_VALUE, 
					                    false,
					                    tk->ply_tbl_com_sutehai_statnum[pnum]);

		// 手牌パーツの表示(UP)
		}else if( pnum == (gui->disp_down_tehai_pnum+2) % 4){
					dparts->DispActTehaiParts_up( gui->tehai_up_x, gui->tehai_up_y,
					                    tk->ply_act_tehaicount[pnum], 
					                    tk->ply_act_tehaitbl[pnum],
					                    tk->ply_act_tehai_tbl_aka[pnum], 
					                    EXCEPT_VALUE, 
					                    false,
					                    tk->ply_tbl_com_sutehai_statnum[pnum]);

		// 手牌パーツの表示(Left)
		}else if( pnum == (gui->disp_down_tehai_pnum+3) % 4){
					dparts->DispActTehaiParts_left(  gui->tehai_left_x,         // 01:X座標
					                                 gui->tehai_left_y,         // 02:Y座標
					                    tk->ply_act_tehaicount[pnum],           // 03:手牌数
					                    tk->ply_act_tehaitbl[pnum],
					                    tk->ply_act_tehai_tbl_aka[pnum], 
					                    EXCEPT_VALUE, 
					                    false,
					                    tk->ply_tbl_com_sutehai_statnum[pnum]);

		// 手牌パーツの表示(Down)
		}else if( pnum == gui->disp_down_tehai_pnum){
					dparts->DispActTehaiParts(gui->tehai_x, gui->tehai_y,
					                    tk->ply_act_tehaicount[pnum], 
					                    tk->ply_act_tehaitbl[pnum],
					                    tk->ply_act_tehai_tbl_aka[pnum], 
					                    EXCEPT_VALUE, 
					                    false,
					                    tk->ply_tbl_com_sutehai_statnum[pnum],
					                    EXCEPT_VALUE,
					                    EXCEPT_VALUE,
					                    false);
		}

	// ----------------------------------------
	// 7.手牌表示：それ以外の手牌表示(自摸なし・捨牌なし)
	// ----------------------------------------
	}else{

		// チー牌選択
		if( pnum == HUM_PLY_SEKI_NUM && gui->gui_ply_tehai_mode == TEHAI_CHI_SELECT){

		// その他通常手牌表示
		}else{

			// 手牌パーツの表示(Right)
			if( pnum == (gui->disp_down_tehai_pnum+1) % 4){
				dparts->DispActTehaiParts_right( gui->tehai_right_x, gui->tehai_right_y,
				                        tk->ply_act_tehaicount[pnum],
					                    tk->ply_act_tehaitbl[pnum],
					                    tk->ply_act_tehai_tbl_aka[pnum], 
					                    EXCEPT_VALUE, false,
					                    EXCEPT_VALUE);

			// 手牌パーツの表示(UP)
			}else if( pnum == (gui->disp_down_tehai_pnum+2) % 4){
				dparts->DispActTehaiParts_up( gui->tehai_up_x, gui->tehai_up_y,
					                    tk->ply_act_tehaicount[pnum], 
					                    tk->ply_act_tehaitbl[pnum],
					                    tk->ply_act_tehai_tbl_aka[pnum], 
				                        EXCEPT_VALUE, false,
					                    EXCEPT_VALUE);

			// 手牌パーツの表示(Left)
			}else if( pnum == (gui->disp_down_tehai_pnum+3) % 4){
				dparts->DispActTehaiParts_left(  gui->tehai_left_x, gui->tehai_left_y,    // 01-02:X,Y座
				                        tk->ply_act_tehaicount[pnum],
					                    tk->ply_act_tehaitbl[pnum],
					                    tk->ply_act_tehai_tbl_aka[pnum], 
				                        EXCEPT_VALUE, false,
					                    EXCEPT_VALUE);

			// 手牌パーツの表示(Down)
			}else if( pnum == gui->disp_down_tehai_pnum){
				// ライナー表示と共通
				dparts->DispActTehaiParts(gui->tehai_x, gui->tehai_y,
				                       tk->ply_act_tehaicount[pnum], 
					                   tk->ply_act_tehaitbl[pnum],
					                   tk->ply_act_tehai_tbl_aka[pnum], 
				                       EXCEPT_VALUE, false,
					                   EXCEPT_VALUE,
					                   EXCEPT_VALUE,
					                   EXCEPT_VALUE,
					                   false);
			}
		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// アクション情報の晒し表示
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DispActSarashi(MJSTkinfo *tk, int kyoku_index, int actid, int pnum){

	// 変数定義
	int tmp_xstat_count  = 0;
	int tmp_aka_count    = 0;

	// さらし表示
	for(int tmp_i = 0; tmp_i < tk->kyoku[kyoku_index].naki_count[pnum]; tmp_i++){

		// アクションが行われたかの確認
		if( tk->kyoku[kyoku_index].naki_actid[pnum][tmp_i] <= actid ){

			// 赤牌の設定
			tmp_aka_count=tk->kyoku[kyoku_index].naki_aka[pnum][tmp_i];

			// ----------------------------------------
			// ポン牌の表示・明槓牌の表示・暗槓牌の表示
			// ----------------------------------------
			if( tk->kyoku[kyoku_index].naki_stat[pnum][tmp_i] == MINKO  || 
                tk->kyoku[kyoku_index].naki_stat[pnum][tmp_i] == MINKAN || 
                tk->kyoku[kyoku_index].naki_stat[pnum][tmp_i] == ANKAN  ){

				dparts->DispActSarashiParts( 600 - tmp_xstat_count*NAKI_MENTSU_RANGE, PLY_YSTART+pnum*PLY_YSIZE+40, 
				                     tk->kyoku[kyoku_index].naki_stat[pnum][tmp_i], 
				                     tk->kyoku[kyoku_index].naki_hai[pnum][tmp_i], 
				                     tk->kyoku[kyoku_index].naki_aka[pnum][tmp_i]);

				// 鳴き面子の表示位置移動
				tmp_xstat_count++;

			// ----------------------------------------
			// チー牌の表示
			// ----------------------------------------
			}else if(tk->kyoku[kyoku_index].naki_stat[pnum][tmp_i] == MINSHUN){

				dparts->DispActSarashiParts( 600 - tmp_xstat_count*NAKI_MENTSU_RANGE, PLY_YSTART+pnum*PLY_YSIZE+40, 
				                     tk->kyoku[kyoku_index].naki_stat[pnum][tmp_i], 
				                     tk->kyoku[kyoku_index].naki_idx[pnum][tmp_i], 
				                     tk->kyoku[kyoku_index].naki_aka[pnum][tmp_i]);

				// 鳴き面子の表示位置移動
				tmp_xstat_count++;

			// ----------------------------------------
			// 加槓牌の表示
			// ----------------------------------------
			}else if(tk->kyoku[kyoku_index].naki_stat[pnum][tmp_i] == KAKAN){

				// 加槓の晒し牌番号の確認
				for(int tmp_j = 0; tmp_j < tk->kyoku[kyoku_index].naki_count[pnum]; tmp_j++){

					// 既存晒し面子と同じならば
					if (tk->kyoku[kyoku_index].naki_hai[pnum][tmp_j] == tk->kyoku[kyoku_index].naki_hai[pnum][tmp_i]){

						// 晒し面子パーツ表示
						if(tmp_aka_count > 0){
							dparts->DispActSarashiParts(600 - tmp_j*NAKI_MENTSU_RANGE, PLY_YSTART+pnum*PLY_YSIZE+40, KAKAN, tk->kyoku[kyoku_index].naki_hai[pnum][tmp_j], 1);
						}else{
							dparts->DispActSarashiParts(600 - tmp_j*NAKI_MENTSU_RANGE, PLY_YSTART+pnum*PLY_YSIZE+40, KAKAN, tk->kyoku[kyoku_index].naki_hai[pnum][tmp_j], 0);
						}

						// 加槓があるので、ここで抜ける(抜けないと加槓で重複処理になってしまう)
						break;

					}
				}

			// ----------------------------------------
			// その他の表示
			// ----------------------------------------
			}else{
				// その他処理
				DrawFormatString(900, PLY_YSTART+pnum*PLY_YSIZE+40, GetColor(255,255,255), "その他");
			}

		}
	}

	// さらし情報
	// wsprintf(tmp_disp_msg, "晒し総数：%d", tk->kyoku[kyoku_index].naki_count[pnum]);
	// ShowlogPrint(tmp_disp_msg);

}

/* ---------------------------------------------------------------------------------------------- */
// アクション情報の晒し表示(スクエア)
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DispActSarashi_square(MJSTkinfo *tk, MJSGui *gui, int kyoku_index, int actid, int pnum){

	// 変数定義
	int tmp_nakimen_count  = 0;  // 面子数
	int tmp_naki_x         = 0;  // 鳴き面子のX表示位置
	int tmp_naki_y         = 0;  // 鳴き面子のY表示位置

	// さらし表示
	for(int tmp_i = 0; tmp_i < tk->kyoku[kyoku_index].naki_count[pnum]; tmp_i++){

		// アクションが行われたかの確認
		if( tk->kyoku[kyoku_index].naki_actid[pnum][tmp_i] <= actid ){

			// ----------------------------------------
			// ポン牌の表示・明槓牌の表示・暗槓牌の表示
			// ----------------------------------------
			if( tk->kyoku[kyoku_index].naki_stat[pnum][tmp_i] == MINKO   || 
			    tk->kyoku[kyoku_index].naki_stat[pnum][tmp_i] == MINKAN  || 
			    tk->kyoku[kyoku_index].naki_stat[pnum][tmp_i] == ANKAN   ){

				// ----------------------------------------
				// 手牌パーツの表示(Right)
				// ----------------------------------------
				if( pnum == (gui->disp_down_tehai_pnum+1) % 4){

					// 鳴き面子の表示位置
					if( gui->disp_square_naki_mentsu == 0 ){
						// 横列鳴き表示
						tmp_naki_x = gui->nakihai_line_right_x;
						tmp_naki_y = gui->nakihai_line_right_y + NAKI_MENTSU_RANGE*tmp_nakimen_count - HAI_XSIZE*3;
					}else{
//						tmp_naki_x = TEHAI_RIGHT_NAKI_X_START + (3-tmp_nakimen_count)*LHAI_XSIZE;
//						tmp_naki_y = TEHAI_RIGHT_NAKI_Y_START;
					}

					// 鳴き面子の表示
					dparts->DispActSarashiParts_right( 
					                     tmp_naki_x, 
				                         tmp_naki_y,
					                     tk->kyoku[kyoku_index].naki_stat[pnum][tmp_i], 
					                     tk->kyoku[kyoku_index].naki_hai[pnum][tmp_i], 
					                     tk->kyoku[kyoku_index].naki_aka[pnum][tmp_i]);

				// ----------------------------------------
				// 手牌パーツの表示(UP)
				// ----------------------------------------
				}else if( pnum == (gui->disp_down_tehai_pnum+2) % 4){

					// 鳴き面子の表示位置
					if( gui->disp_square_naki_mentsu == 0 ){
						// 横列鳴き表示
						tmp_naki_x = gui->nakihai_line_up_x + NAKI_MENTSU_RANGE*tmp_nakimen_count;
						tmp_naki_y = gui->nakihai_line_up_y;
					}else{
//						tmp_naki_x = TEHAI_RIGHT_NAKI_X_START + (3-tmp_nakimen_count)*LHAI_XSIZE;
//						tmp_naki_y = TEHAI_RIGHT_NAKI_Y_START;
					}

					// 鳴き面子の表示
					dparts->DispActSarashiParts_up( 
					                     tmp_naki_x,
					                     tmp_naki_y,
					                     tk->kyoku[kyoku_index].naki_stat[pnum][tmp_i], 
					                     tk->kyoku[kyoku_index].naki_hai[pnum][tmp_i], 
					                     tk->kyoku[kyoku_index].naki_aka[pnum][tmp_i]);

				// ----------------------------------------
				// 手牌パーツの表示(Left)
				// ----------------------------------------
				}else if( pnum == (gui->disp_down_tehai_pnum+3) % 4){

					// 鳴き面子の表示位置
					if( gui->disp_square_naki_mentsu == 0 ){
						// 横列鳴き表示
						tmp_naki_x = gui->nakihai_line_left_x;
						tmp_naki_y = gui->nakihai_line_left_y - NAKI_MENTSU_RANGE*tmp_nakimen_count;
					}else{
//						tmp_naki_x = TEHAI_RIGHT_NAKI_X_START + (3-tmp_nakimen_count)*LHAI_XSIZE;
//						tmp_naki_y = TEHAI_RIGHT_NAKI_Y_START;
					}

					// 鳴き面子の表示
					dparts->DispActSarashiParts_left( 
					                     tmp_naki_x, 
					                     tmp_naki_y, 
					                     tk->kyoku[kyoku_index].naki_stat[pnum][tmp_i], 
					                     tk->kyoku[kyoku_index].naki_hai[pnum][tmp_i], 
					                     tk->kyoku[kyoku_index].naki_aka[pnum][tmp_i]);

				// ----------------------------------------
				// 手牌パーツの表示(Down：ライナーと共通)
				// ----------------------------------------
				}else if( pnum == gui->disp_down_tehai_pnum){

					// 鳴き面子の表示位置
					if( gui->disp_square_naki_mentsu == 0 ){
						tmp_naki_x = gui->nakihai_line_down_x - NAKI_MENTSU_RANGE*tmp_nakimen_count;
						tmp_naki_y = gui->nakihai_line_down_y;
					}else{

					}

					// 鳴き面子の表示
					dparts->DispActSarashiParts( 
					                     tmp_naki_x, 
					                     tmp_naki_y,
					                     tk->kyoku[kyoku_index].naki_stat[pnum][tmp_i], 
					                     tk->kyoku[kyoku_index].naki_hai[pnum][tmp_i], 
					                     tk->kyoku[kyoku_index].naki_aka[pnum][tmp_i]);

				}

				// ----------------------------------------
				// 鳴き面子の表示位置移動
				// ----------------------------------------
				tmp_nakimen_count++;

			// ----------------------------------------
			// チー牌の表示
			// ----------------------------------------
			}else if(tk->kyoku[kyoku_index].naki_stat[pnum][tmp_i] == MINSHUN){

				// ----------------------------------------
				// 手牌パーツの表示(Right)
				// ----------------------------------------
				if( pnum == (gui->disp_down_tehai_pnum+1) % 4){

					// 鳴き面子の表示位置
					// 横列鳴き表示
					if( gui->disp_square_naki_mentsu == 0 ){
						tmp_naki_x = gui->nakihai_line_right_x;
						tmp_naki_y = gui->nakihai_line_right_y + NAKI_MENTSU_RANGE*tmp_nakimen_count - HAI_XSIZE*3;
					}else{
						// tmp_naki_x = TEHAI_RIGHT_NAKI_X_START + (3-tmp_nakimen_count)*LHAI_XSIZE;
						// tmp_naki_y = TEHAI_RIGHT_NAKI_Y_START;
					}

					// 鳴き面子の表示
					dparts->DispActSarashiParts_right( 
					                     tmp_naki_x, 
				                         tmp_naki_y,
					                     tk->kyoku[kyoku_index].naki_stat[pnum][tmp_i], 
					                     tk->kyoku[kyoku_index].naki_idx[pnum][tmp_i], 
					                     tk->kyoku[kyoku_index].naki_aka[pnum][tmp_i]);

				// ----------------------------------------
				// 手牌パーツの表示(UP)
				// ----------------------------------------
				}else if( pnum == (gui->disp_down_tehai_pnum+2) % 4){

					// 鳴き面子の表示位置
					if( gui->disp_square_naki_mentsu == 0 ){
						// 横列鳴き表示
						tmp_naki_x = gui->nakihai_line_up_x + NAKI_MENTSU_RANGE*tmp_nakimen_count;
						tmp_naki_y = gui->nakihai_line_up_y;
					}else{
//						tmp_naki_x = TEHAI_RIGHT_NAKI_X_START + (3-tmp_nakimen_count)*LHAI_XSIZE;
//						tmp_naki_y = TEHAI_RIGHT_NAKI_Y_START;
					}

					// 鳴き面子の表示
					dparts->DispActSarashiParts_up( 
					                     tmp_naki_x,
				                         tmp_naki_y,
					                     tk->kyoku[kyoku_index].naki_stat[pnum][tmp_i], 
					                     tk->kyoku[kyoku_index].naki_idx[pnum][tmp_i], 
					                     tk->kyoku[kyoku_index].naki_aka[pnum][tmp_i]);

				// ----------------------------------------
				// 手牌パーツの表示(Left)
				// ----------------------------------------
				}else if( pnum == (gui->disp_down_tehai_pnum+3) % 4){

					// 鳴き面子の表示位置
					if( gui->disp_square_naki_mentsu == 0 ){
						// 横列鳴き表示
						tmp_naki_x = gui->nakihai_line_left_x;
						tmp_naki_y = gui->nakihai_line_left_y - NAKI_MENTSU_RANGE*tmp_nakimen_count;
					}else{
						// 縦列鳴き表示
//						tmp_naki_x = TEHAI_RIGHT_NAKI_X_START + (3-tmp_nakimen_count)*LHAI_XSIZE;
//						tmp_naki_y = TEHAI_RIGHT_NAKI_Y_START;
					}

					// 鳴き面子の表示
					dparts->DispActSarashiParts_left(
					                     tmp_naki_x, 
					                     tmp_naki_y, 
					                     tk->kyoku[kyoku_index].naki_stat[pnum][tmp_i], 
					                     tk->kyoku[kyoku_index].naki_idx[pnum][tmp_i], 
					                     tk->kyoku[kyoku_index].naki_aka[pnum][tmp_i]);

				// ----------------------------------------
				// 手牌パーツの表示(Down：ライナーと共通)
				// ----------------------------------------
				}else if( pnum == gui->disp_down_tehai_pnum){

					// 鳴き面子の表示位置
						tmp_naki_x = gui->nakihai_line_down_x - NAKI_MENTSU_RANGE*tmp_nakimen_count;
						tmp_naki_y = gui->nakihai_line_down_y;

					// 鳴き面子の表示
					dparts->DispActSarashiParts(  
					                     tmp_naki_x, 
					                     tmp_naki_y, 
					                     tk->kyoku[kyoku_index].naki_stat[pnum][tmp_i], 
					                     tk->kyoku[kyoku_index].naki_idx[pnum][tmp_i], 
					                     tk->kyoku[kyoku_index].naki_aka[pnum][tmp_i]);

				}

				// ----------------------------------------
				// 鳴き面子の表示位置移動
				// ----------------------------------------
				tmp_nakimen_count++;

			// ----------------------------------------
			// 加槓牌の表示
			// ----------------------------------------
			}else if(tk->kyoku[kyoku_index].naki_stat[pnum][tmp_i] == KAKAN){

				// ----------------------------------------
				// 加槓の晒し牌番号の確認
				// ----------------------------------------
				for(int tmp_j = 0; tmp_j < tk->kyoku[kyoku_index].naki_count[pnum]; tmp_j++){

					// 既存晒し面子と同じならば
					if (tk->kyoku[kyoku_index].naki_hai[pnum][tmp_j] == tk->kyoku[kyoku_index].naki_hai[pnum][tmp_i]){

						// ----------------------------------------
						// 手牌パーツの表示(Right)
						// ----------------------------------------
						if( pnum == (gui->disp_down_tehai_pnum+1) % 4 ){

							// 鳴き面子の表示位置
							if( gui->disp_square_naki_mentsu == 0 ){
								// 横列鳴き表示
								tmp_naki_x = gui->nakihai_line_right_x;
								tmp_naki_y = gui->nakihai_line_right_y + NAKI_MENTSU_RANGE*tmp_j - HAI_XSIZE*3;
							}else{
								// 縦列鳴き表示
								// tmp_naki_x = TEHAI_RIGHT_NAKI_X_START + (3-tmp_nakimen_count)*LHAI_XSIZE;
								// tmp_naki_y = TEHAI_RIGHT_NAKI_Y_START;
							}

							// 鳴き面子の表示
							dparts->DispActSarashiParts_right( 
					                     tmp_naki_x, 
				                         tmp_naki_y,
					                     tk->kyoku[kyoku_index].naki_stat[pnum][tmp_i], 
					                     tk->kyoku[kyoku_index].naki_idx[pnum][tmp_i], 
					                     tk->kyoku[kyoku_index].naki_aka[pnum][tmp_i]);

						// ----------------------------------------
						// 手牌パーツの表示(UP)
						// ----------------------------------------
						}else if( pnum == (gui->disp_down_tehai_pnum+2) % 4 ){

							// 鳴き面子の表示位置
							if( gui->disp_square_naki_mentsu == 0 ){
								// 横列鳴き表示
								tmp_naki_x = gui->nakihai_line_up_x + NAKI_MENTSU_RANGE*tmp_j;
								tmp_naki_y = gui->nakihai_line_up_y;
							}else{
//								tmp_naki_x = TEHAI_RIGHT_NAKI_X_START + (3-tmp_nakimen_count)*LHAI_XSIZE;
//								tmp_naki_y = TEHAI_RIGHT_NAKI_Y_START;
							}

							// 鳴き面子の表示
							dparts->DispActSarashiParts_up(
					                     tmp_naki_x, 
					                     tmp_naki_y, 
					                     tk->kyoku[kyoku_index].naki_stat[pnum][tmp_i], 
					                     tk->kyoku[kyoku_index].naki_idx[pnum][tmp_i], 
					                     tk->kyoku[kyoku_index].naki_aka[pnum][tmp_i]);

						// ----------------------------------------
						// 手牌パーツの表示(Left)
						// ----------------------------------------
						}else if( pnum == (gui->disp_down_tehai_pnum+3) % 4 ){

							// 鳴き面子の表示位置
							if( gui->disp_square_naki_mentsu == 0 ){
								// 横列鳴き表示
								tmp_naki_x = gui->nakihai_line_left_x;
								tmp_naki_y = gui->nakihai_line_left_y - NAKI_MENTSU_RANGE*tmp_j;
							}else{
//								tmp_naki_x = TEHAI_RIGHT_NAKI_X_START + (3-tmp_nakimen_count)*LHAI_XSIZE;
//								tmp_naki_y = TEHAI_RIGHT_NAKI_Y_START;
							}

							// 鳴き面子の表示
							dparts->DispActSarashiParts_left( 
					                     tmp_naki_x, 
					                     tmp_naki_y, 
					                     tk->kyoku[kyoku_index].naki_stat[pnum][tmp_i], 
					                     tk->kyoku[kyoku_index].naki_idx[pnum][tmp_i], 
					                     tk->kyoku[kyoku_index].naki_aka[pnum][tmp_i]);

						// ----------------------------------------
						// 手牌パーツの表示(Down：ライナーと共通)
						// ----------------------------------------
						}else if( pnum == gui->disp_down_tehai_pnum ){

							// 鳴き面子の表示位置
							if( gui->disp_square_naki_mentsu == 0 ){
								// 横列鳴き表示
								tmp_naki_x = gui->nakihai_line_down_x - NAKI_MENTSU_RANGE*tmp_j;
								tmp_naki_y = gui->nakihai_line_down_y;
							}else{
								// 縦列鳴き表示
//								tmp_naki_x = TEHAI_RIGHT_NAKI_X_START + (3-tmp_nakimen_count)*LHAI_XSIZE;
//								tmp_naki_y = TEHAI_RIGHT_NAKI_Y_START;
							}

							// 鳴き面子の表示
							dparts->DispActSarashiParts( 
					                     tmp_naki_x, 
					                     tmp_naki_y, 
					                     tk->kyoku[kyoku_index].naki_stat[pnum][tmp_i],
					                     tk->kyoku[kyoku_index].naki_idx[pnum][tmp_i], 
					                     tk->kyoku[kyoku_index].naki_aka[pnum][tmp_i]);

						}

						// 加槓があるので、ここで抜ける(抜けないと加槓で重複処理になってしまう)
						break;

					}
				}
			}
		}
	}

}

/* ---------------------------------------------------------------------------------------------- */
// アクション河情報
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DispActKawa(MJSTkinfo *tk, int kyoku_index, int actid, int pnum){

	// 河表示(パーツ表示)
	dparts->DispActKawaParts_liner( SPACE_XSIZE, 
	                        PLY_YSTART+pnum*PLY_YSIZE, 
	                        tk->ply_act_kawa_count[pnum], 
	                        tk->ply_act_kawa[pnum], 
	                        tk->ply_act_kawa_aka[pnum], 
	                        tk->ply_act_kawa_mode[pnum]);

}

/* ---------------------------------------------------------------------------------------------- */
// アクション河情報(スクエア)
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DispActKawa_square(MJSTkinfo *tk, MJSGui *gui, int kyoku_index, int actid, int pnum){

	// RIGHTプレーヤの表示
	if( pnum == (gui->disp_down_tehai_pnum+1) % 4 ){
		dparts->DispActKawaParts_right( gui->sutehai_right_x, 
	                                    gui->sutehai_right_y, 
	                            tk->ply_act_kawa_count[pnum], 
	                            tk->ply_act_kawa[pnum], 
	                            tk->ply_act_kawa_aka[pnum], 
	                            tk->ply_act_kawa_mode[pnum]);

	// UPプレーヤの表示
	}else if( pnum == (gui->disp_down_tehai_pnum+2) % 4 ){

		dparts->DispActKawaParts_up( gui->sutehai_up_x, 
	                                 gui->sutehai_up_y, 
	                            tk->ply_act_kawa_count[pnum], 
	                            tk->ply_act_kawa[pnum], 
	                            tk->ply_act_kawa_aka[pnum], 
	                            tk->ply_act_kawa_mode[pnum]);

	// LEFTプレーヤの表示
	}else if( pnum == (gui->disp_down_tehai_pnum+3) % 4 ){
		dparts->DispActKawaParts_left( gui->sutehai_left_x, 
	                                   gui->sutehai_left_y,
	                            tk->ply_act_kawa_count[pnum], 
	                            tk->ply_act_kawa[pnum], 
	                            tk->ply_act_kawa_aka[pnum], 
	                            tk->ply_act_kawa_mode[pnum]);

	// DOWNプレーヤの表示
	}else if( pnum == gui->disp_down_tehai_pnum ){
		dparts->DispActKawaParts_down( gui->sutehai_down_x, 
	                                   gui->sutehai_down_y, 
	                            tk->ply_act_kawa_count[pnum], 
	                            tk->ply_act_kawa[pnum], 
	                            tk->ply_act_kawa_aka[pnum], 
	                            tk->ply_act_kawa_mode[pnum]);

	}

}

/* ---------------------------------------------------------------------------------------------- */
// アクションプレート表示
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DispTakuActplt(MJSTkinfo *tk, MJSGui *gui, int kyoku_index, int actid, int pnum){

	// ----------------------------------------
	// アクションプレートを表示するアクション確認
	// ----------------------------------------
	if (tk->kyoku[kyoku_index].act_stat[actid] == PLYACTRIICH   ||  // リーチ
	    tk->kyoku[kyoku_index].act_stat[actid] == PLYACTPON     ||  // ポン
	    tk->kyoku[kyoku_index].act_stat[actid] == PLYACTCHI     ||  // チー
	    tk->kyoku[kyoku_index].act_stat[actid] == PLYACTMINKAN  ||  // 明カン
	    tk->kyoku[kyoku_index].act_stat[actid] == PLYACTANKAN   ||  // 暗カン
	    tk->kyoku[kyoku_index].act_stat[actid] == PLYACTKAKAN   ||  // 加カン
	    tk->kyoku[kyoku_index].act_stat[actid] == PLYTSUMOAGARI ||  // 自摸和了
	    tk->kyoku[kyoku_index].act_stat[actid] == PLYACTRON     ){  // ロン和了

		// ----------------------------------------
		// アクションメッセージの定義
		// ----------------------------------------
		if (tk->kyoku[kyoku_index].act_stat[actid] == PLYACTRIICH){
			// リーチ
			wsprintf(tmp_disp_msg,"リーチ");
		}else if(tk->kyoku[kyoku_index].act_stat[actid] == PLYACTPON){
			// ポン
			wsprintf(tmp_disp_msg,"ポン！");
		}else if(tk->kyoku[kyoku_index].act_stat[actid] == PLYACTCHI){
			// チー
			wsprintf(tmp_disp_msg,"チー！");
		}else if(tk->kyoku[kyoku_index].act_stat[actid] == PLYACTMINKAN){
			// 明カン
			wsprintf(tmp_disp_msg,"明カン");
		}else if(tk->kyoku[kyoku_index].act_stat[actid] == PLYACTANKAN){
			// 暗カン
			wsprintf(tmp_disp_msg,"暗カン");
		}else if(tk->kyoku[kyoku_index].act_stat[actid] == PLYACTKAKAN){
			// 加カン
			wsprintf(tmp_disp_msg,"加カン");
		}else if(tk->kyoku[kyoku_index].act_stat[actid] == PLYTSUMOAGARI){
			// 自摸和了
			wsprintf(tmp_disp_msg,"自摸！");
		}else if(tk->kyoku[kyoku_index].act_stat[actid] == PLYACTRON){
			// ロン和了
			wsprintf(tmp_disp_msg,"ロン！");
		}else{
			// 不明
			wsprintf(tmp_disp_msg,"不明");
		}

		// ----------------------------------------
		// アクションプレーヤーの確認
		// ----------------------------------------
		     if( tk->kyoku[kyoku_index].act_ply[actid] == (gui->disp_down_tehai_pnum+1) % 4 ){
			// RIGHTプレートの表示
			dparts->DispActplt_right( gui->tehai_right_x - STRING_YSIZE - NAME_TEHAI_RANGE, 
	                          gui->tehai_right_y + HAI_XSIZE * TEHAI_MAX + HAI_XSIZE + 10 + 56, 
	                          tmp_disp_msg);

		}else if( tk->kyoku[kyoku_index].act_ply[actid] == (gui->disp_down_tehai_pnum+2) % 4 ){
			// UPプレートの表示
			dparts->DispActplt_up( gui->tehai_up_x + HAI_XSIZE * TEHAI_MAX + 56, 
	                       gui->tehai_up_y + HAI_YSIZE + STRING_YSIZE + NAME_TEHAI_RANGE, 
	                       tmp_disp_msg);

		}else if( tk->kyoku[kyoku_index].act_ply[actid] == (gui->disp_down_tehai_pnum+3) % 4 ){
			// LEFTプレートの表示
			dparts->DispActplt_left( gui->tehai_left_x + HAI_YSIZE + STRING_YSIZE + NAME_TEHAI_RANGE, 
	                         gui->tehai_left_y - 56,
	                         tmp_disp_msg);

		}else if( tk->kyoku[kyoku_index].act_ply[actid] == gui->disp_down_tehai_pnum ){
			// DOWNプレートの表示
			dparts->DispActplt_down( gui->tehai_x - 56, 
	                         gui->tehai_y - STRING_YSIZE - NAME_TEHAI_RANGE, 
	                         tmp_disp_msg);

		}

	// ----------------------------------------
	// アクションプレートを表示するアクション確認
	// ----------------------------------------
	}else if(tk->kyoku[kyoku_index].act_stat[actid] == RYUKYOKU){ // 流局は全員表示


			// 流局定義
			wsprintf(tmp_disp_msg,"流局　");

			// RIGHTプレートの表示
			dparts->DispActplt_right( gui->tehai_right_x - STRING_YSIZE - NAME_TEHAI_RANGE, 
	                          gui->tehai_right_y + HAI_XSIZE * TEHAI_MAX + HAI_XSIZE + 10 + 56, 
	                          tmp_disp_msg);

			// UPプレートの表示
			dparts->DispActplt_up( gui->tehai_up_x + HAI_XSIZE * TEHAI_MAX + 56, 
	                       gui->tehai_up_y + HAI_YSIZE + STRING_YSIZE + NAME_TEHAI_RANGE, 
	                       tmp_disp_msg);

			// LEFTプレートの表示
			dparts->DispActplt_left( gui->tehai_left_x + HAI_YSIZE + STRING_YSIZE + NAME_TEHAI_RANGE, 
	                         gui->tehai_left_y - 56,
	                         tmp_disp_msg);

			// DOWNプレートの表示
			dparts->DispActplt_down( gui->tehai_x - 56, 
	                         gui->tehai_y - STRING_YSIZE - NAME_TEHAI_RANGE, 
	                         tmp_disp_msg);

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 局終了表示(得点表示)
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DispKyokuEnd(MJSTkinfo *tk, MJSGui *gui, int kyoku_index, int tmp_actid){

	int disp_agari_num = 0;
	int tmp_disp_yaku_count = 0;

	// ----------------------------------------
	// 流局時
	// ----------------------------------------
	if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].ryukyoku_flg == true ){

		// 流局結果を表示
		if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].ryukyoku_stat == HOWANPAI ){
			dparts->DispString( 10, PLY_YSTART + 100 + STRING_YSIZE * tmp_disp_yaku_count, dparts->ryukyokuname[HOWANPAI]);
		}else if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].ryukyoku_stat == SUFURENDA ){
			dparts->DispString( 10, PLY_YSTART + 100 + STRING_YSIZE * tmp_disp_yaku_count, dparts->ryukyokuname[SUFURENDA]);
		}else if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].ryukyoku_stat == RIICHI4PLY ){
			dparts->DispString( 10, PLY_YSTART + 100 + STRING_YSIZE * tmp_disp_yaku_count, dparts->ryukyokuname[RIICHI4PLY]);
		}else if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].ryukyoku_stat == UNKNOWNRKK ){
			dparts->DispString( 10, PLY_YSTART + 100 + STRING_YSIZE * tmp_disp_yaku_count, dparts->ryukyokuname[UNKNOWNRKK]);
		}

	// ----------------------------------------
	// 役名表示：役有り時
	// ----------------------------------------
	}else{

		// 手牌表示
		DispKyokuEndTehai(tk, kyoku_index, 0);

		// 翻情報表示
		DispKyokuEndHanInfo(tk, kyoku_index, 0);

		// 和了役の詳細情報
		DispKyokuEndYakuInfo(tk, kyoku_index, tmp_actid, 0);

	}

	// ----------------------------------------
	// プレーヤの得点状況
	// ----------------------------------------
	for(int ply_i = 0; ply_i < PLAYER_MAX; ply_i++){

		// プレーヤ名
		DrawFormatString(800, PLY_YSTART+ply_i*PLY_YSIZE, GetColor(255,255,255), "[席%d]%s", ply_i+1, tk->plyname[ply_i]);

		// 家表示
		if(tk->kyoku[kyoku_index].ie[ply_i] == 0){
			DrawFormatString(800, PLY_YSTART+ply_i*PLY_YSIZE + STRING_YSIZE, GetColor(255,255,255), "東家");
		}else if(tk->kyoku[kyoku_index].ie[ply_i] == 1){
			DrawFormatString(800, PLY_YSTART+ply_i*PLY_YSIZE + STRING_YSIZE, GetColor(255,255,255), "南家");
		}else if(tk->kyoku[kyoku_index].ie[ply_i] == 2){
			DrawFormatString(800, PLY_YSTART+ply_i*PLY_YSIZE + STRING_YSIZE, GetColor(255,255,255), "西家");
		}else if(tk->kyoku[kyoku_index].ie[ply_i] == 3){
			DrawFormatString(800, PLY_YSTART+ply_i*PLY_YSIZE + STRING_YSIZE, GetColor(255,255,255), "北家");
		}else{
			DrawFormatString(800, PLY_YSTART+ply_i*PLY_YSIZE + STRING_YSIZE, GetColor(255,255,255), "不明");
		}

		// 開始得点
		DrawFormatString(840, PLY_YSTART+ply_i*PLY_YSIZE + STRING_YSIZE*1, GetColor(255,255,255), "%6d", tk->kyoku[kyoku_index].ply_kyoku_start_score[ply_i]);

		// 局の得点
		DrawFormatString(840, PLY_YSTART+ply_i*PLY_YSIZE + STRING_YSIZE*2, GetColor(255,255,255), "%6d", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].kyoku_score[ply_i]);

		// 終了得点
		DrawFormatString(840, PLY_YSTART+ply_i*PLY_YSIZE + STRING_YSIZE*3, GetColor(255,255,255), "%6d", tk->kyoku[kyoku_index].ply_kyoku_end_score[ply_i]);

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 局終了表示(手牌表示)
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DispKyokuEndTehai(MJSTkinfo *tk, int kyoku_index, int disp_agari_num){

	// ----------------------------------------
	// 和了手牌の表示
	// ----------------------------------------

/*
	// 手牌パーツの表示(人プレーヤ用_自摸無し：カーソル選択無し)
	dparts->DispActTehaiParts( SPACE_XSIZE, 
	                      PLY_YSTART,
	                      tk->ply_act_tehaicount[tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_num],     
	                      tk->ply_act_tehaitbl[tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_num],       
	                      tk->ply_act_tehai_tbl_aka[tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_num],  
	                      tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_hai,       // 自摸牌：和了牌
	                      tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_aka,       // 自摸赤：和了牌赤
	                      EXCEPT_VALUE,                                                        // 捨牌：なし
	                      EXCEPT_VALUE, EXCEPT_VALUE, false);                                  // カーソル選択：なし
*/

	// 手牌パーツの表示(人プレーヤ用_自摸無し：カーソル選択無し)
	dparts->DispActTehaiParts( SPACE_XSIZE, 
	                      PLY_YSTART,
	                      tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_tehaicount,     // 手牌数
	                      tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_tehaitbl,       // 手牌テーブル
	                      tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_tehai_tbl_aka,  // 手牌テーブル赤
	                      tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_hai,            // 自摸牌：和了牌
	                      tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_aka,            // 自摸赤：和了牌赤
	                      EXCEPT_VALUE,                                                             // 捨牌：なし
	                      EXCEPT_VALUE, EXCEPT_VALUE, false);                                       // カーソル選択：なし

	// 晒し牌表示
	dparts->DispAllSarashiParts(600, PLY_YSTART,
		tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_num],     
		tk->kyoku[kyoku_index].naki_stat[tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_num],      
		tk->kyoku[kyoku_index].naki_hai[tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_num],       
		tk->kyoku[kyoku_index].naki_idx[tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_num],       
		tk->kyoku[kyoku_index].naki_aka[tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_num]        
	);

}

/* ---------------------------------------------------------------------------------------------- */
// 局終了表示(翻情報表示)
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DispKyokuEndHanInfo(MJSTkinfo *tk, int kyoku_index, int disp_agari_num){

	// ----------------------------------------
	// 変数定義
	// ----------------------------------------
	int tmp_disp_yaku_count=0;

	// 通常役(役満なし時)
	if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].yakuman_count == 0 ){

		// 通常役確認
		for(int tmp_i = 0; tmp_i < YAKU_SHUBETSU_MAX; tmp_i++){

			// 役設定有無
			if(tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].yaku_flg[tmp_i] == true){

				// 個別役名
				wsprintf(tmp_disp_msg, "%s … %d翻", dparts->yakuname[tmp_i], tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].yaku_han[tmp_i]);
				dparts->DispString( 10, PLY_YSTART + 100 + STRING_YSIZE * tmp_disp_yaku_count, tmp_disp_msg);
				tmp_disp_yaku_count++;
			}
		}

	}else{

		// 役満確認
		for(int tmp_i = 0; tmp_i < YAKUMAN_SHUBETSU_MAX; tmp_i++){

			// 役設定有無
			if(tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].yakuman_flg[tmp_i] == true){

				// 役テーブル設定
				wsprintf(tmp_disp_msg, "%s … 役満　　", dparts->yakumanname[tmp_i]);
				dparts->DispString( 10, PLY_YSTART + 100 + STRING_YSIZE * tmp_disp_yaku_count, tmp_disp_msg);
				tmp_disp_yaku_count++;

			}

		}
	}

}

/* ---------------------------------------------------------------------------------------------- */
// 局終了表示(得点表示)
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DispKyokuEndYakuInfo(MJSTkinfo *tk, int kyoku_index, int tmp_actid, int disp_agari_num){

	// ----------------------------------------
	// 和了情報
	// ----------------------------------------
	if (tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].tsumo_agari_flg == true){
		DrawFormatString(5, PLY_YSTART+50, GetColor(255,255,255), "自摸和了　和了[席%d]", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_num+1);
	}else{
		DrawFormatString(5, PLY_YSTART+50, GetColor(255,255,255), "ロン和了　和了[席%d]　放銃：[席%d]", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_num+1, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].furikomi_ply_num+1);
	}

	// 和了プレーヤ数
		DrawFormatString(300, PLY_YSTART+50, GetColor(255,255,255), "和了プレーヤ数 %d人", tk->kyoku[kyoku_index].agari_ply_count);

	// ----------------------------------------
	// 裏ドラ表示
	// ----------------------------------------
	if(tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].riichi_flg == true){
		// 裏ドラ表示
		dparts->DispDora(DORA_XSIZE+URADORA_XSIZE_RANGE, SPACE_YSIZE, 
	                 tk->kyoku[kyoku_index].doracount, 
	                 tk->kyoku[kyoku_index].uradora, 
	                 tk->kyoku[kyoku_index].uradora_aka,
	                 tk->kyoku[kyoku_index].uradora_actid,
	                 tmp_actid);
	}

	// ----------------------------------------
	// 和了時の面子情報
	// ----------------------------------------
	if(tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_stat == AGARI_NORMAL){
		DispKyokuEndMentsuInfoNormal(tk, kyoku_index, disp_agari_num);
	}else if(tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_stat == AGARI_CHITOI){
//		DispKyokuEndMentsuInfoChitoi(tk, kyoku_index, disp_agari_num);
	}

	// ----------------------------------------
	// 和了牌
	// ----------------------------------------
	if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_aka == true ){
		DrawFormatString(AGARI_INFO_X2, PLY_YSTART+70+STRING_YSIZE*0, GetColor(255,255,255), "和了牌　：%2d赤", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_hai);
	}else{
		DrawFormatString(AGARI_INFO_X2, PLY_YSTART+70+STRING_YSIZE*0, GetColor(255,255,255), "和了牌　：%2d黒", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_hai);
	}

	// ----------------------------------------
	// 和了形式
	// ----------------------------------------
	if(tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_stat == AGARI_NORMAL){
		DrawFormatString(AGARI_INFO_X2, PLY_YSTART+70+STRING_YSIZE*1, GetColor(255,255,255), "和了形式：通常形式");
	}else if(tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_stat == AGARI_CHITOI){
		DrawFormatString(AGARI_INFO_X2, PLY_YSTART+70+STRING_YSIZE*1, GetColor(255,255,255), "和了形式：七対形式");
	}else if(tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_stat == AGARI_KOKUSHI){
		DrawFormatString(AGARI_INFO_X2, PLY_YSTART+70+STRING_YSIZE*1, GetColor(255,255,255), "和了形式：国士形式");
	}else{
		DrawFormatString(AGARI_INFO_X2, PLY_YSTART+70+STRING_YSIZE*1, GetColor(255,255,255), "和了形式：形式不明");
	}

	// ----------------------------------------
	// 親子情報
	// ----------------------------------------
	if (tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_oya_flg == true){
		DrawFormatString(AGARI_INFO_X2, PLY_YSTART+70+STRING_YSIZE*2, GetColor(255,255,255), "親子　　：親和了");
	}else{
		DrawFormatString(AGARI_INFO_X2, PLY_YSTART+70+STRING_YSIZE*2, GetColor(255,255,255), "親子　　：子和了");
	}

	// ----------------------------------------
	// 自摸和了有無
	// ----------------------------------------
	if (tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].tsumo_agari_flg == true){
		DrawFormatString(AGARI_INFO_X2, PLY_YSTART+70+STRING_YSIZE*3, GetColor(255,255,255), "自摸ロン：自摸和了");
	}else{
		DrawFormatString(AGARI_INFO_X2, PLY_YSTART+70+STRING_YSIZE*3, GetColor(255,255,255), "自摸ロン：ロン和了");
	}

	// ----------------------------------------
	// 面前情報
	// ----------------------------------------
	if(tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].menzen_flg==true){
		DrawFormatString(AGARI_INFO_X2, PLY_YSTART+70+STRING_YSIZE*4, GetColor(255,255,255), "鳴き状態：面前");
	}else{
		DrawFormatString(AGARI_INFO_X2, PLY_YSTART+70+STRING_YSIZE*4, GetColor(255,255,255), "鳴き状態：鳴有");
	}

	// ----------------------------------------
	// 待ち形式
	// ----------------------------------------
	if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_machi_stat == TANKI){
		DrawFormatString(AGARI_INFO_X2, PLY_YSTART+70+STRING_YSIZE*5, GetColor(255,255,255), "待ち形式：単騎待ち");
	}else if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_machi_stat == RYANMEN){
		DrawFormatString(AGARI_INFO_X2, PLY_YSTART+70+STRING_YSIZE*5, GetColor(255,255,255), "待ち形式：両面待ち");
	}else if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_machi_stat == KANCHAN){
		DrawFormatString(AGARI_INFO_X2, PLY_YSTART+70+STRING_YSIZE*5, GetColor(255,255,255), "待ち形式：嵌張待ち");
	}else if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_machi_stat == PENCHAN){
		DrawFormatString(AGARI_INFO_X2, PLY_YSTART+70+STRING_YSIZE*5, GetColor(255,255,255), "待ち形式：辺張待ち");
	}else if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_machi_stat == TOITSU){
		DrawFormatString(AGARI_INFO_X2, PLY_YSTART+70+STRING_YSIZE*5, GetColor(255,255,255), "待ち形式：双椪待ち");
	}else{
		DrawFormatString(AGARI_INFO_X2, PLY_YSTART+70+STRING_YSIZE*5, GetColor(255,255,255), "待ち形式：形式不明");
	}

	// ----------------------------------------
	// 合計符
	// ----------------------------------------
	DrawFormatString(AGARI_INFO_X2, PLY_YSTART+70+STRING_YSIZE* 7, GetColor(255,255,255), "基本符　　%3d符", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].basefu);
	DrawFormatString(AGARI_INFO_X2, PLY_YSTART+70+STRING_YSIZE* 8, GetColor(255,255,255), "面子符小計%3d符", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].atamaFu+tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_Fu[0]+tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_Fu[1]+tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_Fu[2]+tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_Fu[3]);
	DrawFormatString(AGARI_INFO_X2, PLY_YSTART+70+STRING_YSIZE* 9, GetColor(255,255,255), "面前符　　%3d符", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].menzenFu);
	DrawFormatString(AGARI_INFO_X2, PLY_YSTART+70+STRING_YSIZE*10, GetColor(255,255,255), "待ち符　　%3d符", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].machiFu);
	DrawFormatString(AGARI_INFO_X2, PLY_YSTART+70+STRING_YSIZE*11, GetColor(255,255,255), "自摸符　　%3d符", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].tsumoFu);
	DrawFormatString(AGARI_INFO_X2, PLY_YSTART+70+STRING_YSIZE*12, GetColor(255,255,255), "小計符　　%3d符", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].totalFu);
	DrawFormatString(AGARI_INFO_X2, PLY_YSTART+70+STRING_YSIZE*13, GetColor(255,255,255), "合計符　　%3d符", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].scoreFu);

	// ----------------------------------------
	// 和了牌の含むメンツ番号
	// ----------------------------------------
	DrawFormatString(AGARI_INFO_X3, PLY_YSTART+70+STRING_YSIZE*0, GetColor(255,255,255), "和了牌面子:%d", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_num_agari_hai);

	// ----------------------------------------
	// ドラ・赤牌情報
	// ----------------------------------------
	// ドラ
	DrawFormatString(AGARI_INFO_X3, PLY_YSTART+70+STRING_YSIZE*1, GetColor(255,255,255), "ドラ%d 裏ドラ%d", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_dora_count, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_uradora_count);

	// 赤牌
	DrawFormatString(AGARI_INFO_X3, PLY_YSTART+70+STRING_YSIZE*2, GetColor(255,255,255), "赤萬%d 赤筒%d 赤索%d", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_aka_count[0], tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_aka_count[1], tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_aka_count[2]);

	// ----------------------------------------
	// リーチ情報
	// ----------------------------------------
	// リーチ状態
	if(tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].riichi_flg == true){
		DrawFormatString(AGARI_INFO_X3, PLY_YSTART+70+STRING_YSIZE*3, GetColor(255,255,255), "R有");
	}else{
		DrawFormatString(AGARI_INFO_X3, PLY_YSTART+70+STRING_YSIZE*3, GetColor(255,255,255), "R無");
	}

	if(tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].double_riichi_flg == true){
		DrawFormatString(AGARI_INFO_X3+40, PLY_YSTART+70+STRING_YSIZE*3, GetColor(255,255,255), "WR有");
	}else{
		DrawFormatString(AGARI_INFO_X3+40, PLY_YSTART+70+STRING_YSIZE*3, GetColor(255,255,255), "WR無");
	}

	if(tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].riichi_ippatsu_flg == true){
		DrawFormatString(AGARI_INFO_X3+95, PLY_YSTART+70+STRING_YSIZE*3, GetColor(255,255,255), "一発有");
	}else{
		DrawFormatString(AGARI_INFO_X3+95, PLY_YSTART+70+STRING_YSIZE*3, GetColor(255,255,255), "一発無");
	}

	// 自摸回数
	DrawFormatString(AGARI_INFO_X3, PLY_YSTART+70+STRING_YSIZE*4, GetColor(255,255,255), "自摸巡:%d Ｒ巡:%d", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_tsumo_count, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_riichi_count);

	// ----------------------------------------
	// その他の和了情報
	// ----------------------------------------
	if(tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_stat == AGARI_NORMAL){
		DispKyokuEndAgariInfoNormal(tk, kyoku_index, disp_agari_num);
	}else if(tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_stat == AGARI_CHITOI){
		DispKyokuEndAgariInfoChitoi(tk, kyoku_index, disp_agari_num);
	}

	// ----------------------------------------
	// 合計翻・満貫・合計役満倍
	// ----------------------------------------
	if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].yakuman_agari_ply_bai == 0 ){

		if(tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_mangan_count == 0){
			DrawFormatString(AGARI_INFO_X1, PLY_YSTART+355, GetColor(255,255,255), "%2d翻", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_han);
		}else if(tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_mangan_count == 1){
			DrawFormatString(AGARI_INFO_X1, PLY_YSTART+355, GetColor(255,255,255), "%2d翻　満貫　　", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_han);
		}else if(tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_mangan_count == 2){
			DrawFormatString(AGARI_INFO_X1, PLY_YSTART+355, GetColor(255,255,255), "%2d翻　跳満　　", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_han);
		}else if(tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_mangan_count == 3){
			DrawFormatString(AGARI_INFO_X1, PLY_YSTART+355, GetColor(255,255,255), "%2d翻　倍満　　", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_han);
		}else if(tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_mangan_count == 4){
			DrawFormatString(AGARI_INFO_X1, PLY_YSTART+355, GetColor(255,255,255), "%2d翻　三倍満　", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_han);
		}else if(tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_mangan_count == 5){
			DrawFormatString(AGARI_INFO_X1, PLY_YSTART+355, GetColor(255,255,255), "%2d翻　数え役満", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_han);
		}

	}else if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].yakuman_agari_ply_bai == 1 ){
		// 役満表示
		DrawFormatString(AGARI_INFO_X1, PLY_YSTART+355, GetColor(255,255,255), "役満　　");
	}else if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].yakuman_agari_ply_bai == 2 ){
		// 役満表示
		DrawFormatString(AGARI_INFO_X1, PLY_YSTART+355, GetColor(255,255,255), "二倍役満");
	}else if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].yakuman_agari_ply_bai == 3 ){
		// 役満表示
		DrawFormatString(AGARI_INFO_X1, PLY_YSTART+355, GetColor(255,255,255), "三倍役満");
	}else if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].yakuman_agari_ply_bai == 4 ){
		// 役満表示
		DrawFormatString(AGARI_INFO_X1, PLY_YSTART+355, GetColor(255,255,255), "四倍役満");
	}else if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].yakuman_agari_ply_bai >  4 ){
		// 役満表示
		DrawFormatString(AGARI_INFO_X1, PLY_YSTART+355, GetColor(255,255,255), "五倍役満");
	}

	// ----------------------------------------
	// 得点
	// ----------------------------------------
	if (tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].tsumo_agari_flg == true){

		// ツモ和了・親
		if (tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_oya_flg == true){
			DrawFormatString(AGARI_INFO_X1,PLY_YSTART+372, GetColor(255,255,255), "%d点オール", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_tsumo_oya);
		// ツモ和了・子
		}else{
			DrawFormatString(AGARI_INFO_X1,PLY_YSTART+372, GetColor(255,255,255), "%d点 %d点", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_tsumo_oya, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_tsumo_ko);
		}

	}else{

		// ロン和了
		if (tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_oya_flg == true){
			DrawFormatString(AGARI_INFO_X1,PLY_YSTART+372, GetColor(255,255,255), "%d点", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_ron);
		}else{
			DrawFormatString(AGARI_INFO_X1,PLY_YSTART+372, GetColor(255,255,255), "%d点", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_ron);
		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 局終了表示(通常形式面子情報)
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DispKyokuEndMentsuInfoNormal(MJSTkinfo *tk, int kyoku_index, int disp_agari_num){

	// ----------------------------------------
	// 和了時の雀頭情報
	// ----------------------------------------
	// 牌表示
		dparts->DispActSarashiParts(
			AGARI_INFO_X1, 
			PLY_YSTART+70,
			ATAMA,
			tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ata_hai,
			tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ata_aka);

	// 和了牌変色
	if (tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_num_agari_hai == EXCEPT_VALUE){
		// 赤牌表示
		if(tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ata_aka>0){
			dparts->DispHai( AGARI_INFO_X1, PLY_YSTART+70, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ata_hai, true,  false, DISP_HAI_COLOR_NUM_PINK, 0);
		}else{
			dparts->DispHai( AGARI_INFO_X1, PLY_YSTART+70, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ata_hai, false, false, DISP_HAI_COLOR_NUM_PINK, 0);
		}
	}

	// 雀頭・符
	DrawFormatString( AGARI_INFO_X1_1,PLY_YSTART+70, GetColor(255,255,255), "雀頭");
	DrawFormatString( AGARI_INFO_X1_1,PLY_YSTART+87, GetColor(255,255,255), "%2d符", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].atamaFu);

	// 赤牌枚数
	DrawFormatString(AGARI_INFO_X1_2,PLY_YSTART+70, GetColor(255,255,255), "赤%d枚", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ata_aka);

	// 一九字・中張牌の種別
	if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ata_19zi == 0){
		DrawFormatString(AGARI_INFO_X1_2,PLY_YSTART+87, GetColor(255,255,255), "中張牌");
	}else if(tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ata_19zi == 1){
		DrawFormatString(AGARI_INFO_X1_2,PLY_YSTART+87, GetColor(255,255,255), "一九字");
	}else if(tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ata_19zi == 2){
		DrawFormatString(AGARI_INFO_X1_2,PLY_YSTART+87, GetColor(255,255,255), "役牌　");
	}

	// ----------------------------------------
	// 和了時の面子情報
	// ----------------------------------------
	for(int tmp_i = 0; tmp_i < 4; tmp_i++){

		// ----------------------------------------
		// 面子牌
		// ----------------------------------------
		dparts->DispActSarashiParts(
			AGARI_INFO_X1, 
			PLY_YSTART+70+(tmp_i+1)*40,
			tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_stat[tmp_i],
			tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_hai[tmp_i],
			tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_aka_count[tmp_i]);

		// ----------------------------------------
		// 和了牌変色
		// ----------------------------------------

		// 和了牌なら
		if (tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_num_agari_hai == tmp_i){
			// 面子形式・暗刻表示
			if (tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_stat[tmp_i] == ANKO || tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_stat[tmp_i] == MINKO){
					dparts->DispHai( AGARI_INFO_X1,             PLY_YSTART+70+(tmp_i+1)*40, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_hai[tmp_i],  tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_aka, false, DISP_HAI_COLOR_NUM_PINK, 0);
			// 面子形式・順子表示
			}else if(tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_stat[tmp_i] == SHUNTSU || tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_stat[tmp_i] == MINSHUN){
				// 順子の順番確認
				if(       tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_hai == tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_hai[tmp_i]){
					// 順子の1枚目
					dparts->DispHai( AGARI_INFO_X1,             PLY_YSTART+70+(tmp_i+1)*40, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_hai[tmp_i],  tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_aka, false, DISP_HAI_COLOR_NUM_PINK, 0);
				}else if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_hai == tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_hai[tmp_i]+1){
					// 順子の2枚目
					dparts->DispHai( AGARI_INFO_X1+HAI_XSIZE*1, PLY_YSTART+70+(tmp_i+1)*40, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_hai[tmp_i]+1,tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_aka, false, DISP_HAI_COLOR_NUM_PINK, 0);
				}else if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_hai == tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_hai[tmp_i]+2){
					// 順子の3枚目
					dparts->DispHai( AGARI_INFO_X1+HAI_XSIZE*2, PLY_YSTART+70+(tmp_i+1)*40, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_hai[tmp_i]+2,tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_aka, false, DISP_HAI_COLOR_NUM_PINK, 0);
				}

			}
		}

		// ----------------------------------------
		// 面子表示
		// ----------------------------------------
		// メンツ形式
		if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_stat[tmp_i] == SHUNTSU){
			DrawFormatString( AGARI_INFO_X1_1,PLY_YSTART+110+tmp_i*40, GetColor(255,255,255), "順子");
		}else if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_stat[tmp_i] == MINSHUN){
			DrawFormatString( AGARI_INFO_X1_1,PLY_YSTART+110+tmp_i*40, GetColor(255,255,255), "明順");
		}else if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_stat[tmp_i] == ANKO){
			DrawFormatString( AGARI_INFO_X1_1,PLY_YSTART+110+tmp_i*40, GetColor(255,255,255), "暗刻");
		}else if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_stat[tmp_i] == MINKO){
			DrawFormatString( AGARI_INFO_X1_1,PLY_YSTART+110+tmp_i*40, GetColor(255,255,255), "明刻");
		}else if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_stat[tmp_i] == ANKAN){
			DrawFormatString( AGARI_INFO_X1_1,PLY_YSTART+110+tmp_i*40, GetColor(255,255,255), "暗槓");
		}else if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_stat[tmp_i] == MINKAN){
			DrawFormatString( AGARI_INFO_X1_1,PLY_YSTART+110+tmp_i*40, GetColor(255,255,255), "明槓");
		}else{
			DrawFormatString( AGARI_INFO_X1_1,PLY_YSTART+110+tmp_i*40, GetColor(255,255,255), "不明");
		}

		// メンツ符
		DrawFormatString( AGARI_INFO_X1_1, PLY_YSTART+127+tmp_i*40, GetColor(255,255,255), "%2d符",tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_Fu[tmp_i]);

		// 赤牌枚数
		DrawFormatString( AGARI_INFO_X1_2, PLY_YSTART+110+tmp_i*40, GetColor(255,255,255), "赤%d枚",tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_aka_count[tmp_i]);

		// 一九字・中張牌の種別
		if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_19zi[tmp_i] == 0){
			DrawFormatString(AGARI_INFO_X1_2, PLY_YSTART+127+tmp_i*40, GetColor(255,255,255), "中張牌");
		}else if(tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_19zi[tmp_i] == 1){
			DrawFormatString(AGARI_INFO_X1_2, PLY_YSTART+127+tmp_i*40, GetColor(255,255,255), "一九字");
		}else if(tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_19zi[tmp_i] == 2){
			DrawFormatString(AGARI_INFO_X1_2, PLY_YSTART+127+tmp_i*40, GetColor(255,255,255), "役牌　");
		}

	}

/*
	// 赤牌枚数の仮設定
	tmp_aka_count=tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ata_aka;

	// 雀頭1枚目
	if (tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_num_agari_hai == EXCEPT_VALUE){

		// 赤牌表示
		if(tmp_aka_count>0){
			dparts->DispHai( AGARI_INFO_X1, PLY_YSTART+70, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ata_hai, true, false,DISP_HAI_COLOR_NUM_PINK, 0);
			tmp_aka_count--;
		}else{
			dparts->DispHai( AGARI_INFO_X1, PLY_YSTART+70, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ata_hai, false, false,DISP_HAI_COLOR_NUM_PINK, 0);
		}

	}else{

		// 赤牌表示
		if(tmp_aka_count>0){
			dparts->DispHai( AGARI_INFO_X1, PLY_YSTART+70, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ata_hai, true, false , 0, 0);
			tmp_aka_count--;
		}else{
			dparts->DispHai( AGARI_INFO_X1, PLY_YSTART+70, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ata_hai, false, false, 0, 0);
		}
	}

	// 雀頭2枚目

		// 赤牌表示
		if(tmp_aka_count>0){
			dparts->DispHai( AGARI_INFO_X1+HAI_XSIZE*1 ,PLY_YSTART+70, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ata_hai, true, false , 0, 0);
			tmp_aka_count--;
		}else{
			dparts->DispHai( AGARI_INFO_X1+HAI_XSIZE*1 ,PLY_YSTART+70, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ata_hai, false, false, 0, 0);
		}

	// 雀頭・符
	DrawFormatString( AGARI_INFO_X1_1,PLY_YSTART+70, GetColor(255,255,255), "雀頭");
	DrawFormatString( AGARI_INFO_X1_1,PLY_YSTART+87, GetColor(255,255,255), "%2d符", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].atamaFu);

	// 赤牌枚数
	DrawFormatString(AGARI_INFO_X1_2,PLY_YSTART+70, GetColor(255,255,255), "赤%d枚", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ata_aka);

	// 一九字
	if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ata_19zi == 0){
		DrawFormatString(AGARI_INFO_X1_2,PLY_YSTART+87, GetColor(255,255,255), "中張牌");
	}else if(tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ata_19zi == 1){
		DrawFormatString(AGARI_INFO_X1_2,PLY_YSTART+87, GetColor(255,255,255), "一九字");
	}else if(tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ata_19zi == 2){
		DrawFormatString(AGARI_INFO_X1_2,PLY_YSTART+87, GetColor(255,255,255), "役牌　");
	}
*/

/*
		// ----------------------------------------
		// メンツ表示 - 暗刻表示
		// ----------------------------------------
		if (tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_stat[tmp_i] == ANKO || tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_stat[tmp_i] == MINKO){

			// 雀頭1枚目
			if (tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_num_agari_hai == tmp_i){
				dparts->DispHai( AGARI_INFO_X1, PLY_YSTART+110+tmp_i*40, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_hai[tmp_i], false, false, DISP_HAI_COLOR_NUM_PINK, 0);
			}else{
				dparts->DispHai( AGARI_INFO_X1, PLY_YSTART+110+tmp_i*40, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_hai[tmp_i], false, false, 0, 0);
			}

			// 暗刻の牌表示(2枚目以降)
			dparts->DispHai( AGARI_INFO_X1+HAI_XSIZE*1 ,PLY_YSTART+110+tmp_i*40, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_hai[tmp_i], false, false, 0, 0);
			dparts->DispHai( AGARI_INFO_X1+HAI_XSIZE*2 ,PLY_YSTART+110+tmp_i*40, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_hai[tmp_i], false, false, 0, 0);

		// ----------------------------------------
		// メンツ表示 - 順子表示
		// ----------------------------------------
		}else if(tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_stat[tmp_i] == SHUNTSU || tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_stat[tmp_i] == MINSHUN){

			// 順子の1枚目
			if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_num_agari_hai == tmp_i && tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_hai == tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_hai[tmp_i]){
				dparts->DispHai( AGARI_INFO_X1             ,PLY_YSTART+110+tmp_i*40, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_hai[tmp_i]  ,false, false, DISP_HAI_COLOR_NUM_PINK, 0);
			}else{
				dparts->DispHai( AGARI_INFO_X1             ,PLY_YSTART+110+tmp_i*40, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_hai[tmp_i]  ,false, false,  0, 0);
			}

			// 順子の2枚目
			if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_num_agari_hai == tmp_i && tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_hai == tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_hai[tmp_i]+1){
				dparts->DispHai( AGARI_INFO_X1+HAI_XSIZE*1 ,PLY_YSTART+110+tmp_i*40, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_hai[tmp_i]+1, false, false, DISP_HAI_COLOR_NUM_PINK, 0);
			}else{
				dparts->DispHai( AGARI_INFO_X1+HAI_XSIZE*1 ,PLY_YSTART+110+tmp_i*40, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_hai[tmp_i]+1, false, false, 0, 0);
			}

			// 順子の3枚目
			if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_num_agari_hai == tmp_i && tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_hai == tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_hai[tmp_i]+2){
				dparts->DispHai( AGARI_INFO_X1+HAI_XSIZE*2 ,PLY_YSTART+110+tmp_i*40, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_hai[tmp_i]+2, false, false, DISP_HAI_COLOR_NUM_PINK, 0);
			}else{
				dparts->DispHai( AGARI_INFO_X1+HAI_XSIZE*2 ,PLY_YSTART+110+tmp_i*40, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_hai[tmp_i]+2, false, false, 0, 0);
			}

		// ----------------------------------------
		// メンツ表示 - 暗槓表示
		// ----------------------------------------
		}else if (tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_stat[tmp_i] == ANKAN || tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_stat[tmp_i] == MINKAN ){

		// 晒し牌の表示(オープン1枚目)
		if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_aka_count[tmp_i] > 0 ){
			dparts->DispHai( AGARI_INFO_X1+HAI_XSIZE*1 ,PLY_YSTART+110+tmp_i*40,tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_hai[tmp_i], true, false, 0, 0);
		}else{
			dparts->DispHai( AGARI_INFO_X1+HAI_XSIZE*1 ,PLY_YSTART+110+tmp_i*40,tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_hai[tmp_i], false, false, 0, 0);
		}

		// 晒し牌の表示(オープン2枚目)
		if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_aka_count[tmp_i] > 1 ){
			dparts->DispHai( AGARI_INFO_X1+HAI_XSIZE*2 ,PLY_YSTART+110+tmp_i*40,tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_hai[tmp_i], true, false, 0, 0);
		}else{
			dparts->DispHai( AGARI_INFO_X1+HAI_XSIZE*2 ,PLY_YSTART+110+tmp_i*40,tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_hai[tmp_i], false, false, 0, 0);
		}

			// 裏向き牌
			dparts->DispHai( AGARI_INFO_X1+HAI_XSIZE*0 ,PLY_YSTART+110+tmp_i*40, 0, false, false, 0, 0);
			dparts->DispHai( AGARI_INFO_X1+HAI_XSIZE*3 ,PLY_YSTART+110+tmp_i*40, 0, false, false, 0, 0);

		// ----------------------------------------
		// メンツ表示 - 明槓表示
		// ----------------------------------------

		// 晒し牌の表示(オープン1枚目)
		if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_aka_count[tmp_i] > 0 ){
			dparts->DispHai( AGARI_INFO_X1+HAI_XSIZE*0 ,PLY_YSTART+110+tmp_i*40,tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_hai[tmp_i], true, false, 0, 0);
		}else{
			dparts->DispHai( AGARI_INFO_X1+HAI_XSIZE*0 ,PLY_YSTART+110+tmp_i*40,tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_hai[tmp_i], false, false, 0, 0);
		}

		// 晒し牌の表示(オープン2枚目)
		if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_aka_count[tmp_i] > 1 ){
			dparts->DispHai( AGARI_INFO_X1+HAI_XSIZE*1 ,PLY_YSTART+110+tmp_i*40,tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_hai[tmp_i], true, false, 0, 0);
		}else{
			dparts->DispHai( AGARI_INFO_X1+HAI_XSIZE*1 ,PLY_YSTART+110+tmp_i*40,tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_hai[tmp_i], false, false, 0, 0);
		}

		// 晒し牌の表示(オープン3枚目)
		if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_aka_count[tmp_i] > 2 ){
			dparts->DispHai( AGARI_INFO_X1+HAI_XSIZE*2 ,PLY_YSTART+110+tmp_i*40,tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_hai[tmp_i], true, false, 0, 0);
		}else{
			dparts->DispHai( AGARI_INFO_X1+HAI_XSIZE*2 ,PLY_YSTART+110+tmp_i*40,tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_hai[tmp_i], false, false, 0, 0);
		}

		// 晒し牌の表示(オープン4枚目)
		if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_aka_count[tmp_i] > 3 ){
			dparts->DispHai( AGARI_INFO_X1+HAI_XSIZE*3 ,PLY_YSTART+110+tmp_i*40,tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_hai[tmp_i], true, false, 0, 0);
		}else{
			dparts->DispHai( AGARI_INFO_X1+HAI_XSIZE*3 ,PLY_YSTART+110+tmp_i*40,tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_hai[tmp_i], false, false, 0, 0);
		}

		// ----------------------------------------
		// (デバグ用)不明の面子
		// ----------------------------------------
		}else{
				DrawFormatString( AGARI_INFO_X1, PLY_YSTART+140+tmp_i*40, GetColor(255,255,255), "形式不明");
		}

		// ----------------------------------------
		// 面子表示
		// ----------------------------------------

		// メンツ形式
		if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_stat[tmp_i] == SHUNTSU){
			DrawFormatString( AGARI_INFO_X1_1,PLY_YSTART+110+tmp_i*40, GetColor(255,255,255), "順子");
		}else if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_stat[tmp_i] == MINSHUN){
			DrawFormatString( AGARI_INFO_X1_1,PLY_YSTART+110+tmp_i*40, GetColor(255,255,255), "明順");
		}else if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_stat[tmp_i] == ANKO){
			DrawFormatString( AGARI_INFO_X1_1,PLY_YSTART+110+tmp_i*40, GetColor(255,255,255), "暗刻");
		}else if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_stat[tmp_i] == MINKO){
			DrawFormatString( AGARI_INFO_X1_1,PLY_YSTART+110+tmp_i*40, GetColor(255,255,255), "明刻");
		}else if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_stat[tmp_i] == ANKAN){
			DrawFormatString( AGARI_INFO_X1_1,PLY_YSTART+110+tmp_i*40, GetColor(255,255,255), "暗槓");
		}else if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_stat[tmp_i] == MINKAN){
			DrawFormatString( AGARI_INFO_X1_1,PLY_YSTART+110+tmp_i*40, GetColor(255,255,255), "明槓");
		}else{
			DrawFormatString( AGARI_INFO_X1_1,PLY_YSTART+110+tmp_i*40, GetColor(255,255,255), "不明");
		}

		// メンツ符
		DrawFormatString( AGARI_INFO_X1_1, PLY_YSTART+127+tmp_i*40, GetColor(255,255,255), "%2d符",tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_Fu[tmp_i]);

		// 赤牌枚数
		DrawFormatString( AGARI_INFO_X1_2, PLY_YSTART+110+tmp_i*40, GetColor(255,255,255), "赤%d枚",tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_aka_count[tmp_i]);

		// ヤオチュウ
		if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_19zi[tmp_i] == 0){
			DrawFormatString(AGARI_INFO_X1_2, PLY_YSTART+127+tmp_i*40, GetColor(255,255,255), "中張牌");
		}else if(tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_19zi[tmp_i] == 1){
			DrawFormatString(AGARI_INFO_X1_2, PLY_YSTART+127+tmp_i*40, GetColor(255,255,255), "一九字");
		}else if(tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_19zi[tmp_i] == 2){
			DrawFormatString(AGARI_INFO_X1_2, PLY_YSTART+127+tmp_i*40, GetColor(255,255,255), "役牌　");
		}

	}
*/

}

/* ---------------------------------------------------------------------------------------------- */
// 局終了表示(通常形式和了情報)
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DispKyokuEndAgariInfoNormal(MJSTkinfo *tk, int kyoku_index, int disp_agari_num){

	// ----------------------------------------
	// 場風自風の牌番号
	// ----------------------------------------
	DrawFormatString(AGARI_INFO_X3, PLY_YSTART+70+STRING_YSIZE* 5, GetColor(255,255,255), "場風:%d 自風:%d", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_bakaze, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_zikaze);

	// ----------------------------------------
	// 面子枚数(通常和了)
	// ----------------------------------------
	DrawFormatString(AGARI_INFO_X3, PLY_YSTART+70+STRING_YSIZE* 6, GetColor(255,255,255), "一九字:%d 中張牌:%d", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].mentsu_count_19zi, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].mentsu_count_chunchan);
	DrawFormatString(AGARI_INFO_X3, PLY_YSTART+70+STRING_YSIZE* 7, GetColor(255,255,255), "萬子:%d 筒子:%d",tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].mentsu_count_manzu, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].mentsu_count_pinzu);
	DrawFormatString(AGARI_INFO_X3, PLY_YSTART+70+STRING_YSIZE* 8, GetColor(255,255,255), "索子:%d 字牌:%d",tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].mentsu_count_souzu, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].mentsu_count_zihai);
	DrawFormatString(AGARI_INFO_X3, PLY_YSTART+70+STRING_YSIZE* 9, GetColor(255,255,255), "緑牌:%d", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].mentsu_count_green);

	// ----------------------------------------
	// 面子形式枚数(通常和了)
	// ----------------------------------------
	DrawFormatString(AGARI_INFO_X3, PLY_YSTART+70+STRING_YSIZE*10, GetColor(255,255,255), "順子:%d 明順:%d", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].mentsu_count_shuntsu, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].mentsu_count_minshun);
	DrawFormatString(AGARI_INFO_X3, PLY_YSTART+70+STRING_YSIZE*11, GetColor(255,255,255), "暗刻:%d 明刻:%d", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].mentsu_count_anko,    tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].mentsu_count_minko);
	DrawFormatString(AGARI_INFO_X3, PLY_YSTART+70+STRING_YSIZE*12, GetColor(255,255,255), "暗槓:%d 明槓:%d", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].mentsu_count_ankan,   tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].mentsu_count_minkan);

	// ----------------------------------------
	// 手牌ヒストグラム(刻子)
	// ----------------------------------------

	// ヒストグラム用
	int tmp_hist;
	tmp_hist=0;

	DrawFormatString(AGARI_INFO_X3, PLY_YSTART+70+STRING_YSIZE*13, GetColor(255,255,255), "刻子:");
	for(int tmp_i = 1; tmp_i < PAI_MAX; tmp_i++){
		for(int tmp_j = 0; tmp_j < tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].anko_hist[tmp_i]; tmp_j++){
			// ヒストグラム
			DrawFormatString(AGARI_INFO_X3+45+tmp_hist*24, PLY_YSTART+70+STRING_YSIZE*13, GetColor(255,255,255), "%2d,", tmp_i);
			tmp_hist++;
		}
	}
	// ----------------------------------------
	// 手牌ヒストグラム(順子)
	// ----------------------------------------
	tmp_hist=0;

	DrawFormatString(AGARI_INFO_X3, PLY_YSTART+70+STRING_YSIZE*14, GetColor(255,255,255), "順子:");
	for(int tmp_i = 1; tmp_i < PAI_MAX; tmp_i++){
		for(int tmp_j = 0; tmp_j < tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].shuntsu_hist[tmp_i]; tmp_j++){
			// ヒストグラム
			DrawFormatString(AGARI_INFO_X3+45+tmp_hist*24, PLY_YSTART+70+STRING_YSIZE*14, GetColor(255,255,255), "%2d,", tmp_i);
			tmp_hist++;
		}
	}

}

/* ---------------------------------------------------------------------------------------------- */
// 局終了表示(七対子形式面子情報)
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DispKyokuEndMentsuInfoChitoi(MJSTkinfo *tk, int kyoku_index, int disp_agari_num){

	// ----------------------------------------
	// 和了時の面子情報
	// ----------------------------------------
	for(int tmp_i = 0; tmp_i < 7; tmp_i++){

		// 対子1枚目
		if (tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_num_agari_hai == tmp_i){
			dparts->DispHai( AGARI_INFO_X1, PLY_YSTART+70+tmp_i*40, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_chitoi_men_hai[tmp_i], false, false, DISP_HAI_COLOR_NUM_PINK, 0);
		}else{
			dparts->DispHai( AGARI_INFO_X1, PLY_YSTART+70+tmp_i*40, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_chitoi_men_hai[tmp_i], false, false, 0, 0);
		}

		// 対子2枚目
		dparts->DispHai( AGARI_INFO_X1+HAI_XSIZE*1 ,PLY_YSTART+70+tmp_i*40, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_chitoi_men_hai[tmp_i], false, false, 0, 0);

		// メンツ形式
		DrawFormatString( AGARI_INFO_X1_1,PLY_YSTART+70+tmp_i*40, GetColor(255,255,255), "対子");

		// 赤牌枚数
		// DrawFormatString( AGARI_INFO_X1_2, PLY_YSTART+70+tmp_i*40, GetColor(255,255,255), "赤%d枚",tk->kyoku[kyoku_index].agari_men_aka_count[tmp_i]);
		DrawFormatString( AGARI_INFO_X1_2, PLY_YSTART+70+tmp_i*40, GetColor(255,255,255), "赤%d枚",0);

		// メンツ符
		DrawFormatString( AGARI_INFO_X1_1, PLY_YSTART+87+tmp_i*40, GetColor(255,255,255), "%2d符",0);

		// 一九字牌
		DrawFormatString(AGARI_INFO_X1_2, PLY_YSTART+87+tmp_i*40, GetColor(255,255,255), "一九字");
/*		if( tk->kyoku[kyoku_index].agari_men_19zi[tmp_i] == 0){
			DrawFormatString(AGARI_INFO_X1_2, PLY_YSTART+87+tmp_i*40, GetColor(255,255,255), "中張牌");
		}else if(tk->kyoku[kyoku_index].agari_men_19zi[tmp_i] == 1){
			DrawFormatString(AGARI_INFO_X1_2, PLY_YSTART+87+tmp_i*40, GetColor(255,255,255), "一九字");
		}*/

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 局終了表示(七対子形式和了情報)
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DispKyokuEndAgariInfoChitoi(MJSTkinfo *tk, int kyoku_index, int disp_agari_num){

	// ----------------------------------------
	// 面子枚数(通常和了)
	// ----------------------------------------
	DrawFormatString(AGARI_INFO_X3, PLY_YSTART+70+STRING_YSIZE* 6, GetColor(255,255,255), "一九字:%d 中張牌:%d", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].mentsu_count_19zi,  tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].mentsu_count_chunchan);
	DrawFormatString(AGARI_INFO_X3, PLY_YSTART+70+STRING_YSIZE* 7, GetColor(255,255,255), "萬子:%d 筒子:%d",     tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].mentsu_count_manzu, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].mentsu_count_pinzu);
	DrawFormatString(AGARI_INFO_X3, PLY_YSTART+70+STRING_YSIZE* 8, GetColor(255,255,255), "索子:%d 字牌:%d",     tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].mentsu_count_souzu, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].mentsu_count_zihai);

}

/* ---------------------------------------------------------------------------------------------- */
// 局終了表示(ビューアモード：東風荘ログ)
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DispViewerKyokuEnd_mjscore(MJSTkinfo *tk, int kyoku_index, int tmp_actid){

	int disp_agari_num = 0;

	// ----------------------------------------
	// 役名表示
	// ----------------------------------------

	// 役名表示
	for(int tmp_i = 0; tmp_i < tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].yakucount; tmp_i++){

		// 個別役名
		wsprintf(tmp_disp_msg, "%s", tk->kyoku[kyoku_index].yakuname[tmp_i]);
		dparts->DispString( 10, PLY_YSTART + 100 + STRING_YSIZE * tmp_i, tmp_disp_msg);

	}

	// ----------------------------------------
	// プレーヤの得点状況
	// ----------------------------------------
	for(int ply_i = 0; ply_i < PLAYER_MAX; ply_i++){

		// プレーヤ名
		DrawFormatString(800, PLY_YSTART+ply_i*PLY_YSIZE, GetColor(255,255,255), "[席%d]%s", ply_i+1, tk->plyname[ply_i]);

		// 家表示
		if(tk->kyoku[kyoku_index].ie[ply_i] == 0){
			DrawFormatString(800, PLY_YSTART+ply_i*PLY_YSIZE + STRING_YSIZE, GetColor(255,255,255), "東家");
		}else if(tk->kyoku[kyoku_index].ie[ply_i] == 1){
			DrawFormatString(800, PLY_YSTART+ply_i*PLY_YSIZE + STRING_YSIZE, GetColor(255,255,255), "南家");
		}else if(tk->kyoku[kyoku_index].ie[ply_i] == 2){
			DrawFormatString(800, PLY_YSTART+ply_i*PLY_YSIZE + STRING_YSIZE, GetColor(255,255,255), "西家");
		}else if(tk->kyoku[kyoku_index].ie[ply_i] == 3){
			DrawFormatString(800, PLY_YSTART+ply_i*PLY_YSIZE + STRING_YSIZE, GetColor(255,255,255), "北家");
		}else{
			DrawFormatString(800, PLY_YSTART+ply_i*PLY_YSIZE + STRING_YSIZE, GetColor(255,255,255), "不明");
		}

		// 得点
		DrawFormatString(840, PLY_YSTART+ply_i*PLY_YSIZE + STRING_YSIZE*1, GetColor(255,255,255), "%6d", tk->kyoku[kyoku_index].ply_kyoku_start_score[ply_i]);
		DrawFormatString(840, PLY_YSTART+ply_i*PLY_YSIZE + STRING_YSIZE*2, GetColor(255,255,255), "%6d", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].kyoku_score[ply_i]);
		DrawFormatString(840, PLY_YSTART+ply_i*PLY_YSIZE + STRING_YSIZE*3, GetColor(255,255,255), "%6d", tk->kyoku[kyoku_index].ply_kyoku_end_score[ply_i]);

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 局終了表示(ビューアモード：MJAIログ)
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DispViewerKyokuEnd_mjailog(MJSTkinfo *tk, int kyoku_index, int tmp_actid){

	// ----------------------------------------
	// 初期化
	// ----------------------------------------
	int tmp_disp_yaku_count = 0;  
	int disp_agari_num = 0;

	// ----------------------------------------
	// 画面番号算出
	// ----------------------------------------

	// 和了画面番号の確認
	for(int tmp_disp_num = 0; tmp_disp_num < tk->kyoku[kyoku_index].agari_ply_count; tmp_disp_num++){
		if( tk->kyoku[kyoku_index].ply_agari_yk[tmp_disp_num].agari_ply_num == tk->kyoku[kyoku_index].act_ply[tmp_actid]){
			disp_agari_num = tmp_disp_num;
		}
	}

	// ----------------------------------------
	// 流局情報
	// ----------------------------------------
	if(tk->kyoku[kyoku_index].ply_agari_yk[0].ryukyoku_flg == true){

		// 流局結果を表示
		if(       tk->kyoku[kyoku_index].ply_agari_yk[0].ryukyoku_stat == HOWANPAI ){
			dparts->DispString( 10, PLY_YSTART + 100 + STRING_YSIZE * tmp_disp_yaku_count, dparts->ryukyokuname[HOWANPAI]);
		}else if( tk->kyoku[kyoku_index].ply_agari_yk[0].ryukyoku_stat == SUFURENDA ){
			dparts->DispString( 10, PLY_YSTART + 100 + STRING_YSIZE * tmp_disp_yaku_count, dparts->ryukyokuname[SUFURENDA]);
		}else if( tk->kyoku[kyoku_index].ply_agari_yk[0].ryukyoku_stat == RIICHI4PLY ){
			dparts->DispString( 10, PLY_YSTART + 100 + STRING_YSIZE * tmp_disp_yaku_count, dparts->ryukyokuname[RIICHI4PLY]);
		}else if( tk->kyoku[kyoku_index].ply_agari_yk[0].ryukyoku_stat == UNKNOWNRKK ){
			dparts->DispString( 10, PLY_YSTART + 100 + STRING_YSIZE * tmp_disp_yaku_count, dparts->ryukyokuname[UNKNOWNRKK]);
		}

	// ----------------------------------------
	// 和了結果表示
	// ----------------------------------------
	}else{

		// 手牌表示
		DispKyokuEndTehai(tk, kyoku_index, disp_agari_num);

		// 翻情報表示
		DispKyokuEndHanInfo(tk, kyoku_index, disp_agari_num);

		// 和了役の詳細情報
		DispKyokuEndYakuInfo(tk, kyoku_index, tmp_actid, disp_agari_num);

	}

	// ----------------------------------------
	// プレーヤの得点状況
	// ----------------------------------------
	for(int ply_i = 0; ply_i < PLAYER_MAX; ply_i++){

		// プレーヤ名
		DrawFormatString(800, PLY_YSTART+ply_i*PLY_YSIZE, GetColor(255,255,255), "[席%d]%s", ply_i+1, tk->plyname[ply_i]);

		// 家表示
		if(tk->kyoku[kyoku_index].ie[ply_i] == 0){
			DrawFormatString(800, PLY_YSTART+ply_i*PLY_YSIZE + STRING_YSIZE, GetColor(255,255,255), "東家");
		}else if(tk->kyoku[kyoku_index].ie[ply_i] == 1){
			DrawFormatString(800, PLY_YSTART+ply_i*PLY_YSIZE + STRING_YSIZE, GetColor(255,255,255), "南家");
		}else if(tk->kyoku[kyoku_index].ie[ply_i] == 2){
			DrawFormatString(800, PLY_YSTART+ply_i*PLY_YSIZE + STRING_YSIZE, GetColor(255,255,255), "西家");
		}else if(tk->kyoku[kyoku_index].ie[ply_i] == 3){
			DrawFormatString(800, PLY_YSTART+ply_i*PLY_YSIZE + STRING_YSIZE, GetColor(255,255,255), "北家");
		}else{
			DrawFormatString(800, PLY_YSTART+ply_i*PLY_YSIZE + STRING_YSIZE, GetColor(255,255,255), "不明");
		}

		// 得点
		DrawFormatString(840, PLY_YSTART+ply_i*PLY_YSIZE + STRING_YSIZE*1, GetColor(255,255,255), "%6d", tk->kyoku[kyoku_index].ply_kyoku_start_score[ply_i]);
		DrawFormatString(840, PLY_YSTART+ply_i*PLY_YSIZE + STRING_YSIZE*2, GetColor(255,255,255), "%6d", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].kyoku_score[ply_i]);
		DrawFormatString(840, PLY_YSTART+ply_i*PLY_YSIZE + STRING_YSIZE*3, GetColor(255,255,255), "%6d", tk->kyoku[kyoku_index].ply_kyoku_end_score[ply_i]);

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 卓終了表示
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplayGameResult(MJSTkinfo *tk, MJSGui *gui){

	// ----------------------------------------
	// パーツ表示
	// ----------------------------------------

	// プレート表示
	dparts->DispPltline(SPACE_XSIZE, PLT_Y_STAT, PLT_ICON_XSIZE+SPACE_XSIZE, gui->plt_mode);

	// ----------------------------------------
	// 得点一覧
	// ----------------------------------------

	// 表題
	wsprintf(tmp_disp_msg, "成績　：");
	dparts->DispString(GAMERESULT_X_START, GAMERESULT_Y_START, tmp_disp_msg);

	// 順位表示
	for(int rank = 0; rank < PLAYER_MAX; rank++){

		// 順位一覧
		wsprintf(tmp_disp_msg, "%d位　：　%s", rank+1, tk->plyname[tk->plyjun[rank]] );
		dparts->DispString(  GAMERESULT_X_START, GAMERESULT_Y_START+50 + 50 * rank, tmp_disp_msg);

		// 得点表示
		wsprintf(tmp_disp_msg, "　%4d", tk->plyEndscore[rank] );
		dparts->DispString( GAMERESULT_X_START+300, GAMERESULT_Y_START+50 + 50 * rank, tmp_disp_msg);

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 卓ゲーム終了表示(ビューアモード)
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DispViewerGameResult(MJSTkinfo *tk){

	// 表題
	wsprintf(tmp_disp_msg, "成績　：");
	dparts->DispString(GAMERESULT_X_START, GAMERESULT_Y_START, tmp_disp_msg);

	// 順位表示
	for(int tmp_pnum = 0; tmp_pnum < PLAYER_MAX; tmp_pnum++){

		// 順位一覧
		wsprintf(tmp_disp_msg, "[席%d]%s", tmp_pnum+1, tk->plyname[tmp_pnum] );
		dparts->DispString(  GAMERESULT_X_START, GAMERESULT_Y_START+50 + 50 * tmp_pnum, tmp_disp_msg);

		// 得点表示
		wsprintf(tmp_disp_msg, "　%8d", tk->plyEndscore[tmp_pnum] );
		dparts->DispString( GAMERESULT_X_START+300, GAMERESULT_Y_START+50 + 50 * tmp_pnum, tmp_disp_msg);

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 牌山表示
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DispYamahai(MJSTkinfo *tk){

	// 牌山・牌山INDEX表示
	for(int ply_i = 0; ply_i < 8; ply_i++){
		for(int ply_j = 0; ply_j < 17; ply_j++){
			DrawFormatString(SPACE_XSIZE+42*ply_j, PLY_YSTART+20*ply_i, GetColor(255,255,255), "%2d-%d ", tk->hai_yama[ply_i*17+ply_j], tk->yamahai_index[ply_i*17+ply_j]);
		}
	}

}

/* ---------------------------------------------------------------------------------------------- */
// MJAIクライアントモード：メイン処理
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplayMjaiClientTaku(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui, float mFps, int total_frame_count, int ver1, int ver2, int ver3, int ver4, int ver5){

	// ----------------------------------------
	// 初期描画処理
	// ----------------------------------------
	dparts->DispPartsClearDraw();

	// ----------------------------------------
	// パーツ表示
	// ----------------------------------------

	// バナー
	dparts->DispBunner(ver1, ver2, ver3, ver4, ver5);

	// マウスポイント
	dparts->DispMousepoint(SPACE_XSIZE, 750, gui->msx, gui->msy, gui->Button[0], gui->Button[1]);

	// FPS
	dparts->DispFps(670, 750, mFps, total_frame_count, gui->frame_count);

	// デバグ情報
	if(disp_debug_info_mode == TRUE){
		// クライアントモード情報の表示
		DisplayClientModeInfo(tk, gui, SPACE_XSIZE, DEBUG_INFO_Y_STAT + STRING_YSIZE);
	}

	/*-----------------------------------------------------------*/
	// ステータスごとのパーツ表示(接続情報)
	/*-----------------------------------------------------------*/
	if( gui->cli_mode == GUI_MJAI_NOTCONNECT              ||
	    gui->cli_mode == GUI_MJAI_CONNECT_ACTION          ||
	    gui->cli_mode == GUI_MJAI_ERR_CONNECT             ||
	    gui->cli_mode == GUI_MJAI_WAIT_HELO_RESMES        ||
	    gui->cli_mode == GUI_MJAI_WAIT_TAKU_START_RESMES  ||
	    gui->cli_mode == GUI_MJAI_WAIT_KYOKU_START_RESMES ||
	    gui->cli_mode == GUI_MJAI_DISCONNECT              ){

		// 接続確認
		DisplayMjaiConnect(tk,gui);

	/*-----------------------------------------------------------*/
	// ステータスごとのパーツ表示(場決め表示)
	/*-----------------------------------------------------------*/
	}else if( gui->cli_mode == GUI_MJAI_BAGIME                  || 
	          gui->cli_mode == GUI_MJAI_WAIT_KYOKU_START_RESMES ){

		// 場決め表示
		DisplayClientModeBagime(tk, gui, tk->kyoku_index);

	/*-----------------------------------------------------------*/
	// ステータスごとのパーツ表示(卓モード表示)
	/*-----------------------------------------------------------*/
	}else if(gui->cli_mode == GUI_MJAI_HAIPAI                ||
	         gui->cli_mode == GUI_MJAI_WAIT_TAKU_RESMES      ||
	         gui->cli_mode == GUI_MJAI_WAIT_TAKU_PLYACT      ||
	         gui->cli_mode == GUI_MJAI_WAIT_SED_MES          ||
	         gui->cli_mode == GUI_MJAI_CHECK_DISCONNECT      ){

		// 局終了表示なら
		if(tk->stat == KYOKURESULT || tk->stat == KYOKUEND){
			// 和了情報
			DisplayMjaiClientKyokuEnd(tk, gui, tk->kyoku_index);
		// 局終了表示なら
		}else if(tk->stat == TAKURESULT || tk->stat == TAKUEND){
			// 卓終了
			DisplayMjaiClientGameResult(tk, gui);
		// それ以外なら
		}else{
			// 卓表示モード
			DispyMjaiClientNormalTakuStat(tk, ply, gui);
		}

	/*-----------------------------------------------------------*/
	// ステータスごとのパーツ表示(局終了)
	/*-----------------------------------------------------------*/
	}else if(gui->cli_mode == GUI_MJAI_KYOKUEND){

		// 和了情報
		DisplayMjaiClientKyokuEnd(tk, gui, tk->kyoku_index);

	/*-----------------------------------------------------------*/
	// ステータスごとのパーツ表示(卓終了)
	/*-----------------------------------------------------------*/
	}else if(gui->cli_mode == GUI_MJAI_TAKURESULT){

		// 卓終了
		DisplayMjaiClientGameResult(tk, gui);

	/*-----------------------------------------------------------*/
	// ステータスごとのパーツ表示(エラー表示)
	/*-----------------------------------------------------------*/
	}else if(gui->cli_mode == GUI_MJAI_ERR_RES_MES){

		// エラー表示
		DisplayMjaiClientErrMes(tk, gui);

	}

	/*-----------------------------------------------------------*/
	// 裏画面を表画面に反映
	/*-----------------------------------------------------------*/
	dparts->DispPartsFlip();

}

/* ---------------------------------------------------------------------------------------------- */
// MJAIクライアントモード：接続確認
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplayMjaiConnect(MJSTkinfo *tk, MJSGui *gui){

	// 接続先情報
	DrawFormatString(50, 250, GetColor(255,255,255), "接続先IPアドレス：%d.%d.%d.%d", 127,0,0,1);

	// ステータスメッセージの表示
	DrawFormatString(50, 300, GetColor(255,255,255), gui->stat_mes);

	// Socket受信メッセージの表示
	if( gui->cli_mode == GUI_MJAI_WAIT_HELO_RESMES        || 
	    gui->cli_mode == GUI_MJAI_WAIT_TAKU_START_RESMES  ||
	    gui->cli_mode == GUI_MJAI_WAIT_KYOKU_START_RESMES ){

		// 受信メッセージを表示
		DrawFormatString(50, 320, GetColor(255,255,255), gui->res_mes);

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 場決め情報
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplayClientModeBagime(MJSTkinfo *tk, MJSGui *gui, int kyoku_index){

	/*-----------------------------------------------------------*/
	// プレーヤ情報の表示
	/*-----------------------------------------------------------*/

	// ステータスメッセージ
	DrawFormatString(BAGIME_X_START, BAGIME_Y_START, GetColor(255,255,255), gui->stat_mes);

	// プレーヤ情報(Ply_id順)
	DrawFormatString(BAGIME_X_START, 70, GetColor(255,255,255), "Hum_Ply_id %d", tk->ply_mjai_hum_id);
	for(int tmp_ply_id = 0; tmp_ply_id < PLAYER_MAX; tmp_ply_id++){
		for(int tmp_i = 0; tmp_i < PLAYER_MAX; tmp_i++){
			if(tk->ply_mjai_id[tmp_i] == tmp_ply_id){
				DrawFormatString(BAGIME_X_START , BAGIME_Y_START + 40 + tmp_ply_id * 20, GetColor(255,255,255), "Ply_id:%d [席%d] %s", tmp_ply_id, tmp_i+1, tk->plyname[tmp_i]);
			}
		}
	}

	/*-----------------------------------------------------------*/
	// クリック案内
	/*-----------------------------------------------------------*/
	wsprintf(tmp_disp_msg, "クリックしてください");
	dparts->DispString( 100, 450, tmp_disp_msg);

	// プレート表示
	// dparts->DispPltline(SPACE_XSIZE, PLT_Y_STAT, PLT_ICON_XSIZE+SPACE_XSIZE, gui->plt_mode);

/*
	// プレーヤ情報(席順)
	DrawFormatString(50, 70, GetColor(255,255,255), "Hum_Ply_id %d", tk->ply_mjai_hum_id);
	for(int tmp_i = 0; tmp_i < 4; tmp_i++){
		DrawFormatString(50 , 90 + tmp_i * 20, GetColor(255,255,255), "[席%d]:Ply_id %d:%s：", tmp_i+1, tk->ply_mjai_id[tmp_i], tk->plyname[tmp_i]);
	}
*/

/*
	// 表題
	dparts->DispString( 50, 50, tk->tkname );

	// 席表示
	for(int tmp_pnum = 0; tmp_pnum < 4; tmp_pnum++){

		// プレーヤ名
		if(tk->kyoku[kyoku_index].ie[tmp_pnum] == 0){
			DrawFormatString(50, 100 + 50 * tmp_pnum, GetColor(255,255,255), "[席%d]東家　%s", tmp_pnum+1, tk->plyname[tmp_pnum]);
		}else if(tk->kyoku[kyoku_index].ie[tmp_pnum] == 1){
			DrawFormatString(50, 100 + 50 * tmp_pnum, GetColor(255,255,255), "[席%d]南家　%s", tmp_pnum+1, tk->plyname[tmp_pnum]);
		}else if(tk->kyoku[kyoku_index].ie[tmp_pnum] == 2){
			DrawFormatString(50, 100 + 50 * tmp_pnum, GetColor(255,255,255), "[席%d]西家　%s", tmp_pnum+1, tk->plyname[tmp_pnum]);
		}else if(tk->kyoku[kyoku_index].ie[tmp_pnum] == 3){
			DrawFormatString(50, 100 + 50 * tmp_pnum, GetColor(255,255,255), "[席%d]北家　%s", tmp_pnum+1, tk->plyname[tmp_pnum]);
		}else{
			DrawFormatString(50, 100 + 50 * tmp_pnum, GetColor(255,255,255), "[席%d]不明　%s", tmp_pnum+1, tk->plyname[tmp_pnum]);
		}

	}
*/

}

/* ---------------------------------------------------------------------------------------------- */
// 通常の卓表示(クライアントモード)
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DispyMjaiClientNormalTakuStat(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui){

	// -----------------------------------------------------------
	// 局情報
	// -----------------------------------------------------------

	// 局情報
	DispKyokuInfo(tk,tk->kyoku_index);

	// ドラ
	dparts->DispDora(DORA_XSIZE, SPACE_YSIZE, 
	                 tk->kyoku[tk->kyoku_index].doracount, 
	                 tk->kyoku[tk->kyoku_index].dora, 
	                 tk->kyoku[tk->kyoku_index].dora_aka,
	                 tk->kyoku[tk->kyoku_index].dora_actid,
	                 tk->kyoku[tk->kyoku_index].act_count);

	// ボタン表示
	// dparts->DispGameModeButton();
	dparts->DispInfoButton(THINFO_BUT_X_STAT, TKINFO_BUT_X_STAT, PLYINFO_BUT_X_STAT, QUIT_BUT_X_STAT, BUT02_Y_STAT);

	// プレート表示
	dparts->DispPltline(SPACE_XSIZE, PLT_Y_STAT, PLT_ICON_XSIZE+SPACE_XSIZE, gui->plt_mode);

	// プレート鳴有/鳴無
	dparts->DispPltNakiAriNashi(PLT_NAKIARI_X_STAT, PLT_Y_STAT, gui->plt_nakiari_flg);

	// 手牌ラインメッセージ
	DispTehaiLineMessage(tk, gui, PLY_MES_X_STAT, PLY_MES_Y_STAT);

	// -----------------------------------------------------------
	// 卓GUIモード(gui->gui_taku_mode)ごとの表示
	// -----------------------------------------------------------

		// -----------------------------------------------------------
		// 「手牌ライナー」モード表示
		// -----------------------------------------------------------
		if( gui->disp_tehai_mode == 0 ){

			// ライナーモード表示(COM)
			for( int tmp_pnum = 0; tmp_pnum < PLAYER_MAX; tmp_pnum++ ) {

				// 手牌
				if( tmp_pnum == HUM_PLY_SEKI_NUM){
					// 手牌(HUM表示)
					DispActTehaiHum(tk, gui, tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count, tmp_pnum, gui->msx, gui->msy);
				}else{
					// 手牌(COM表示)
					DispActTehaiCom(tk, gui, tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count, tmp_pnum, gui->msx, gui->msy);
				}

				// 晒し表示
				DispActSarashi(tk, tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count, tmp_pnum);

				// 河表示(ライナー表示)
				DispActKawa(tk, tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count, tmp_pnum);

				// プレーヤごとの得点情報
				DispPlyInfo(tk, tk->kyoku_index, tmp_pnum);

			}

		// -----------------------------------------------------------
		// 「手牌囲み」モード表示
		// -----------------------------------------------------------
		}else if( gui->disp_tehai_mode == 1 ){

			// センタープレート
			dparts->DispCenterPlt( (TAKU_PLT_X_SIZE + TAKU_PLT_X_STAT)/2 - HAI_XSIZE*3,
			                       (TAKU_PLT_Y_SIZE + TAKU_PLT_Y_STAT)/2 - HAI_XSIZE*3 );

			// 手牌囲みモード表示
			for( int tmp_pnum = 0; tmp_pnum < PLAYER_MAX ; tmp_pnum++ ) {

				// 手牌
				if( tk->ply_hum_mode == 1 && tmp_pnum == HUM_PLY_SEKI_NUM){
					// 手牌(HUM表示)
					DispActTehaiHum(tk, gui, tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count, tmp_pnum, gui->msx, gui->msy);
				}else{
					// 手牌(COM表示)
					DispActTehaiCom_square(tk, gui, tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count, tmp_pnum, gui->msx, gui->msy);
				}

				// 晒し表示
				DispActSarashi_square(tk, gui, tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count, tmp_pnum);

				// 河表示
				DispActKawa_square(tk, gui, tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count, tmp_pnum);

				// プレーヤごとの得点情報
				DispPlyInfo(tk, tk->kyoku_index, tmp_pnum);

			}

		// -----------------------------------------------------------
		// 「テスト表示」モード
		// -----------------------------------------------------------
		}else if( gui->disp_tehai_mode == 2 ){

			// 囲み手牌のサンプル表示
			DispActTehai_test_square(gui);

		}

	// -----------------------------------------------------------
	// 終了表示
	// -----------------------------------------------------------
	// }else if(gui->gui_taku_mode == COMMON_END_CHECK_MODE){

		// 終了ボタンの確認
		// DispTehaiLineMessage(tk, gui, PLY_MES_X_STAT, PLY_MES_Y_STAT);

	// -----------------------------------------------------------
	// tkinfoクラス情報
	// -----------------------------------------------------------
	// }else if(gui->gui_taku_mode == COMMON_TKINFO_MODE){

		// tkinfoクラス表示
		// DisplayTkinfoDetail(tk);

}

/* ---------------------------------------------------------------------------------------------- */
// 和了結果表示(クライアントモード)
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplayMjaiClientKyokuEnd(MJSTkinfo *tk, MJSGui *gui, int kyoku_index){

	// デバグ用
	int disp_agari_num=0;

	// -----------------------------------------------------------
	// 局情報
	// -----------------------------------------------------------

	// 局情報
	DispKyokuInfo(tk,tk->kyoku_index);

	// ドラ
	// dparts->DispDora(DORA_XSIZE, 5, tk->kyoku[tk->kyoku_index].doracount, tk->kyoku[tk->kyoku_index].dora, tk->kyoku[tk->kyoku_index].dora_aka);
	dparts->DispDora(DORA_XSIZE, SPACE_YSIZE, 
	                 tk->kyoku[tk->kyoku_index].doracount, 
	                 tk->kyoku[tk->kyoku_index].dora, 
	                 tk->kyoku[tk->kyoku_index].dora_aka,
	                 tk->kyoku[tk->kyoku_index].dora_actid,
	                 tk->kyoku[tk->kyoku_index].act_count);

	// ----------------------------------------
	// 和了情報：役有り時
	// ----------------------------------------

	// 変数定義
	int tmp_disp_yaku_count = 0;

	// 和了フラグ確認
	if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].ryukyoku_flg == false ){

		// 和了役の詳細表示
		// DispClientKyokuEndYakuari(tk, gui, kyoku_index);

		// 和了プレーヤ
		if (tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].tsumo_agari_flg == true){
			DrawFormatString(5, PLY_YSTART+50, GetColor(255,255,255), "自摸和了　和了[席%d]", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_num+1);
		}else{
			DrawFormatString(5, PLY_YSTART+50, GetColor(255,255,255), "ロン和了　和了[席%d]　放銃：[席%d]", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_num+1, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].furikomi_ply_num+1);
		}

		// 手牌パーツの表示(人プレーヤ用_自摸無し：カーソル選択無し)
		dparts->DispActTehaiParts( SPACE_XSIZE, PLY_YSTART,
	                      tk->kyoku[kyoku_index].agari_tehaicount,    
	                      tk->kyoku[kyoku_index].agari_tehaitbl,      
	                      tk->kyoku[kyoku_index].agari_tehaitbl_aka,  
	                      tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_hai,        // 自摸牌：和了牌
	                      tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_aka,        // 自摸赤：和了牌赤
	                      EXCEPT_VALUE,                               // 捨牌：なし
	                      EXCEPT_VALUE, EXCEPT_VALUE, false);         // カーソル選択：なし

		// 晒し牌表示
		dparts->DispAllSarashiParts(600, PLY_YSTART,
		tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_num], 
		tk->kyoku[kyoku_index].naki_stat[tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_num],
		tk->kyoku[kyoku_index].naki_hai[tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_num],
		tk->kyoku[kyoku_index].naki_idx[tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_num],
		tk->kyoku[kyoku_index].naki_aka[tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_num]);

		// 通常役(役満なし時)
		if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].yakuman_count == 0 ){

			// 通常役確認
			for(int tmp_i = 0; tmp_i < YAKU_SHUBETSU_MAX; tmp_i++){

				// 役設定有無
				if(tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].yaku_flg[tmp_i] == true){

					// 個別役名
					// wsprintf(tmp_disp_msg, "%s", tk->kyoku[kyoku_index].yakuname[tmp_i]);
					wsprintf(tmp_disp_msg, "%s … %d翻", dparts->yakuname[tmp_i], tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].yaku_han[tmp_i]);
					dparts->DispString( 10, PLY_YSTART + 100 + STRING_YSIZE * tmp_disp_yaku_count, tmp_disp_msg);
					tmp_disp_yaku_count++;
				}
			}

		// 合計翻の表示
		DrawFormatString(AGARI_INFO_X1, PLY_YSTART+355, GetColor(255,255,255), "%3d符　%2d翻", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].scoreFu, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_han);

		// ----------------------------------------
		// 役満時
		// ----------------------------------------
		}else{

			// 役満確認
			for(int tmp_i = 0; tmp_i < YAKUMAN_SHUBETSU_MAX; tmp_i++){

				// 役設定有無
				if(tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].yakuman_flg[tmp_i] == true){

					// 役テーブル設定
					// wsprintf(tk->kyoku[kyoku_index].yakuname[tk->kyoku[kyoku_index].yakuman_count], "%s … 役満　　", dparts->yakumanname[tmp_i], 1);
					wsprintf(tmp_disp_msg, "%s … 役満　　", dparts->yakumanname[tmp_i]);
					dparts->DispString( 10, PLY_YSTART + 100 + STRING_YSIZE * tmp_disp_yaku_count, tmp_disp_msg);
					tmp_disp_yaku_count++;

				}

			}
		}

	// ----------------------------------------
	// 流局時
	// ----------------------------------------
	}else{

		// 荒牌
		if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].ryukyoku_stat == HOWANPAI ){
			// 文字列表示
			dparts->DispString( 10, PLY_YSTART + 100 + STRING_YSIZE * tmp_disp_yaku_count, dparts->ryukyokuname[HOWANPAI]);
		}
	}

	// ----------------------------------------
	// プレーヤの得点状況
	// ----------------------------------------
	for(int ply_i = 0; ply_i < PLAYER_MAX; ply_i++){

		// プレーヤ名
		DrawFormatString(800, PLY_YSTART+ply_i*PLY_YSIZE, GetColor(255,255,255), "[席%d]%s", ply_i+1, tk->plyname[ply_i]);

		// 家表示
		if(tk->kyoku[kyoku_index].ie[ply_i] == 0){
			DrawFormatString(800, PLY_YSTART+ply_i*PLY_YSIZE + STRING_YSIZE, GetColor(255,255,255), "東家");
		}else if(tk->kyoku[kyoku_index].ie[ply_i] == 1){
			DrawFormatString(800, PLY_YSTART+ply_i*PLY_YSIZE + STRING_YSIZE, GetColor(255,255,255), "南家");
		}else if(tk->kyoku[kyoku_index].ie[ply_i] == 2){
			DrawFormatString(800, PLY_YSTART+ply_i*PLY_YSIZE + STRING_YSIZE, GetColor(255,255,255), "西家");
		}else if(tk->kyoku[kyoku_index].ie[ply_i] == 3){
			DrawFormatString(800, PLY_YSTART+ply_i*PLY_YSIZE + STRING_YSIZE, GetColor(255,255,255), "北家");
		}else{
			DrawFormatString(800, PLY_YSTART+ply_i*PLY_YSIZE + STRING_YSIZE, GetColor(255,255,255), "不明");
		}

		// 開始得点
		DrawFormatString(840, PLY_YSTART+ply_i*PLY_YSIZE + STRING_YSIZE*1, GetColor(255,255,255), "%6d", tk->kyoku[kyoku_index].ply_kyoku_start_score[ply_i]);

		// 局の得点
		DrawFormatString(840, PLY_YSTART+ply_i*PLY_YSIZE + STRING_YSIZE*2, GetColor(255,255,255), "%6d", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].kyoku_score[ply_i]);

		// 終了得点
		DrawFormatString(840, PLY_YSTART+ply_i*PLY_YSIZE + STRING_YSIZE*3, GetColor(255,255,255), "%6d", tk->kyoku[kyoku_index].ply_kyoku_end_score[ply_i]);

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 卓終了表示(クライアントモード)
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplayMjaiClientGameResult(MJSTkinfo *tk, MJSGui *gui){

	// ----------------------------------------
	// パーツ表示
	// ----------------------------------------

	// プレート表示
	dparts->DispPltline(SPACE_XSIZE, PLT_Y_STAT, PLT_ICON_XSIZE+SPACE_XSIZE, gui->plt_mode);

	// ----------------------------------------
	// 得点一覧
	// ----------------------------------------

	// 表題
	wsprintf(tmp_disp_msg, "成績　：");
	dparts->DispString(GAMERESULT_X_START, GAMERESULT_Y_START, tmp_disp_msg);

	// プレーヤ情報
	for(int tmp_pnum = 0; tmp_pnum < PLAYER_MAX; tmp_pnum++){
		// プレーヤ名
		wsprintf(tmp_disp_msg, "[席%d] Ply_id:%d　%s", tmp_pnum+1, tk->ply_mjai_id[tmp_pnum], tk->plyname[tmp_pnum]);
		dparts->DispString(  GAMERESULT_X_START, GAMERESULT_Y_START+50 + 50 * tmp_pnum, tmp_disp_msg);
		// 得点表示
		wsprintf(tmp_disp_msg, "%10d", tk->plyEndscore[tmp_pnum] );
		dparts->DispString( GAMERESULT_X_START+300, GAMERESULT_Y_START+50 + 50 * tmp_pnum, tmp_disp_msg);

	}

/*
	// 順位表示
	for(int rank = 0; rank < 4; rank++){

		// 順位一覧
		wsprintf(tmp_disp_msg, "%d位　：　%10s", rank+1, tk->plyname[tk->plyjun[rank]] );
		dparts->DispString(  50, 100 + 50 * rank, tmp_disp_msg);

		// 得点表示
		wsprintf(tmp_disp_msg, "　%4d", tk->plyEndscore[rank] );
		dparts->DispString( 250, 100 + 50 * rank, tmp_disp_msg);

	}
*/
}

/* ---------------------------------------------------------------------------------------------- */
// エラー表示(クライアントモード)
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplayMjaiClientErrMes(MJSTkinfo *tk, MJSGui *gui){

	// -----------------------------------------------------------
	// 局情報
	// -----------------------------------------------------------

	// 局情報
	DispKyokuInfo(tk,tk->kyoku_index);

	// ドラ
	// dparts->DispDora(DORA_XSIZE, 5, tk->kyoku[tk->kyoku_index].doracount, tk->kyoku[tk->kyoku_index].dora, tk->kyoku[tk->kyoku_index].dora_aka);
	dparts->DispDora(DORA_XSIZE, SPACE_YSIZE, 
	                 tk->kyoku[tk->kyoku_index].doracount, 
	                 tk->kyoku[tk->kyoku_index].dora, 
	                 tk->kyoku[tk->kyoku_index].dora_aka,
	                 tk->kyoku[tk->kyoku_index].dora_actid,
	                 tk->kyoku[tk->kyoku_index].act_count);

	// ボタン表示
	// dparts->DispGameModeButton();
	dparts->DispInfoButton(THINFO_BUT_X_STAT, TKINFO_BUT_X_STAT, PLYINFO_BUT_X_STAT, QUIT_BUT_X_STAT, BUT02_Y_STAT);

	// プレート表示
	dparts->DispPltline(SPACE_XSIZE, PLT_Y_STAT, PLT_ICON_XSIZE+SPACE_XSIZE, gui->plt_mode);

	// 手牌ラインメッセージ
	// DispTehaiLineMessage(tk, gui, PLY_MES_X_STAT, PLY_MES_Y_STAT);

}

/* ---------------------------------------------------------------------------------------------- */
// クライアントモード：卓情報
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplayClientModeInfo(MJSTkinfo *tk, MJSGui *gui, int x, int y){

	// -----------------------------------------------------------
	// GUIステータス情報(0段目・1番目)
	// -----------------------------------------------------------

	// クライアントモードGUIステータス
	DisplayGuiClientMode(gui, x, y);

	// 手牌枚数
	for(int tmp_pnum = 0; tmp_pnum < 4; tmp_pnum++){
		DisplayTkinfoDetail_sub_tehai_count(tk, x+300+tmp_pnum*150, y, tmp_pnum);
	}

	// -----------------------------------------------------------
	// GUI情報(1-2段目)
	// -----------------------------------------------------------

	// GUI情報
	DispGuiInfo(gui, x, y+STRING_YSIZE);

	// -----------------------------------------------------------
	// TkInfo情報(3-4段目)
	// -----------------------------------------------------------

	// 個別アクション情報
	DispActNumInfo(tk, x, y+STRING_YSIZE*3, tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count);

	// 卓情報
	DispTakuStat(tk, x, y+STRING_YSIZE*4);

	// -----------------------------------------------------------
	// HUM自摸牌(5段目・1番目)
	// -----------------------------------------------------------
	if( tk->ply_act_tsumo_aka[HUM_PLY_SEKI_NUM] == true){
		DrawFormatString(x, y+STRING_YSIZE*5, GetColor(255,255,255), "Ply自摸%2d赤", tk->ply_act_tsumo[HUM_PLY_SEKI_NUM]);
	}else{
		DrawFormatString(x, y+STRING_YSIZE*5, GetColor(255,255,255), "Ply自摸%2d黒", tk->ply_act_tsumo[HUM_PLY_SEKI_NUM]);
	}

	// -----------------------------------------------------------
	// HUM鳴き牌情報(5段目・2番目)
	// -----------------------------------------------------------
	// プレイヤーの鳴き情報詳細
	DisplayTkinfoDetail_sub_ply_actnaki_info(tk, x+120, y+STRING_YSIZE*5, HUM_PLY_SEKI_NUM);

	// -----------------------------------------------------------
	// HUM赤牌枚数(5段目・3番目)
	// -----------------------------------------------------------
	DrawFormatString(x+500, y+STRING_YSIZE*5, GetColor(255,255,255), "[席%d]赤萬%d,赤筒%d,赤索%d", 
		       HUM_PLY_SEKI_NUM+1, 
		       tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][0],    // 赤牌枚数萬子
		       tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][1],    // 赤牌枚数筒子
		       tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][2]);   // 赤牌枚数索子

	// -----------------------------------------------------------
	// 全プレーヤの捨牌(6段目)
	// -----------------------------------------------------------
	for(int tmp_pnum = 0; tmp_pnum < 4; tmp_pnum++){
		if(tk->ply_act_sute_aka[tmp_pnum] == true){
			DrawFormatString(x+tmp_pnum*120, y+STRING_YSIZE*6, GetColor(255,255,255), "[席%d]捨%2d赤",tmp_pnum+1, tk->ply_act_sute[tmp_pnum]);
		}else{
			DrawFormatString(x+tmp_pnum*120, y+STRING_YSIZE*6, GetColor(255,255,255), "[席%d]捨%2d黒",tmp_pnum+1, tk->ply_act_sute[tmp_pnum]);
		}
	}

	// -----------------------------------------------------------
	// Socket情報(7-8段目)
	// -----------------------------------------------------------
	DrawFormatString(x, y+STRING_YSIZE*7, GetColor(255,255,255), gui->res_mes);  // 受信メッセージ
	DrawFormatString(x, y+STRING_YSIZE*8, GetColor(255,255,255), gui->snd_mes);  // 送信メッセージ

	// -----------------------------------------------------------
	// リーチ状態(7-8段目)
	// -----------------------------------------------------------
/*
	// 捨牌不可テーブル情報
	DrawFormatString(x, y+STRING_YSIZE*7, GetColor(255,255,255), "枚数%2d",gui->cannot_sutehai_count);
	for(int tmp_i = 0; tmp_i < gui->cannot_sutehai_count; tmp_i++){
		DrawFormatString(x+100+tmp_i*50, y+STRING_YSIZE*7, GetColor(255,255,255), "%2d ",gui->cannot_sutehai[tmp_i] );
	}

	// シャンテン情報
	for(int tmp_i = 0; tmp_i < TEHAI_MAX; tmp_i++){
		DrawFormatString(x+80+tmp_i*50, y+STRING_YSIZE*8, GetColor(255,255,255), "%2d:%2d ",tmp_i, tk->ply_act_tehai_shanten_tbl[HUM_PLY_SEKI_NUM][tmp_i]);
	} */

	// -----------------------------------------------------------
	// wk_str情報
	// -----------------------------------------------------------
/*
	// 区切り行の値
	const int row_num = 7;

	// work文字列表示(X段目)
	for(int tmp_rank = 0; tmp_rank < 10; tmp_rank++){
		if( gui->wk_str_count > row_num*tmp_rank && gui->wk_str_count <= row_num*(tmp_rank+1) ){
			// 一部表示
			for(int tmp_i = row_num*tmp_rank; tmp_i < gui->wk_str_count; tmp_i++){
				// DrawFormatString(x + 150 * (tmp_i-row_num*tmp_rank), y+50+20*tmp_rank, GetColor(255,255,255), gui->wk_str[tmp_i]);
				wsprintf(tmp_disp_msg, "%2d:%s", tmp_i, gui->wk_str[tmp_i]);
				DrawFormatString(x + 150 * (tmp_i-row_num*tmp_rank), y+64+16*tmp_rank, GetColor(255,255,255), tmp_disp_msg);
			}
		}else{
			// フル表示
			for(int tmp_i = row_num*tmp_rank; tmp_i < row_num*(tmp_rank+1); tmp_i++){
				// DrawFormatString(x + 150 *  (tmp_i-row_num*tmp_rank), y+50+20*tmp_rank, GetColor(255,255,255), gui->wk_str[tmp_i]);
				wsprintf(tmp_disp_msg, "%2d:%s", tmp_i, gui->wk_str[tmp_i]);
				DrawFormatString(x + 150 * (tmp_i-row_num*tmp_rank), y+64+16*tmp_rank, GetColor(255,255,255), tmp_disp_msg);
			}
		}
	}
*/


/*

	// work文字列表示(1段目)
	if(gui->wk_str_count <= 8){
		for(int tmp_i = 0; tmp_i < gui->wk_str_count; tmp_i++){
			DrawFormatString(x + 150 * tmp_i, y+50, GetColor(255,255,255), gui->wk_str[tmp_i]);
		}
	}else{
		for(int tmp_i = 0; tmp_i < 8; tmp_i++){
			DrawFormatString(x + 150 * tmp_i, y+50, GetColor(255,255,255), gui->wk_str[tmp_i]);
		}
	}

	// work文字列表示(2段目)
	if(gui->wk_str_count > 8 && gui->wk_str_count <= 8*2){
		for(int tmp_i = 8*1; tmp_i < gui->wk_str_count; tmp_i++){
			DrawFormatString(x + 150 * tmp_i, y+50, GetColor(255,255,255), gui->wk_str[tmp_i]);
		}
	}else{
		for(int tmp_i = 8*1; tmp_i < 8*2; tmp_i++){
			DrawFormatString(x + 150 * tmp_i, y+50, GetColor(255,255,255), gui->wk_str[tmp_i]);
		}
	}*/


}

/* ---------------------------------------------------------------------------------------------- */
// アクション手牌表示・ライナーHUM表示
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DispActTehaiHum(MJSTkinfo *tk, MJSGui *gui, int kyoku_index, int actid, int pnum, int msx, int msy){

	// 初期化
	int tmp_sute_stat=0;                // 仮用の捨牌の位置番号

	// -----------------------------------------------------------
	// 席情報
	// -----------------------------------------------------------

	// 席情報設定
	wsprintf(tmp_disp_msg,"[席%d]%s", pnum+1, tk->plyname[pnum]);

	// 自プレーヤーの席情報定義
	dparts->DispString( gui->tehai_x, 
	                    gui->tehai_y - STRING_YSIZE - NAME_TEHAI_RANGE, 
	                   tmp_disp_msg);

	// -----------------------------------------------------------
	// 1.手牌表示：自摸時
	// -----------------------------------------------------------

	if ( ( tk->kyoku[kyoku_index].act_stat[actid] == PLYACTTSUMO || 
	       tk->kyoku[kyoku_index].act_stat[actid] == PLYRINSHAN  || 
	       tk->kyoku[kyoku_index].act_stat[actid] == PLYTSUMOAGARI ) &&
	       tk->kyoku[kyoku_index].act_ply[actid]  == pnum ){

			// カン選択モードなら
			if( gui->gui_ply_tehai_mode == TEHAI_ANKAN_KAKAN_SELECT ){

				// マウス位置の確認(通常モード)
				if( msx > gui->tehai_x && 
				    msx < gui->tehai_x + (tk->ply_act_tehaicount[pnum])*HAI_XSIZE && 
				    msy > gui->tehai_y && 
					msy < gui->tehai_y+HAI_YSIZE){

						// 手牌パーツの表示(人プレーヤ用：カーソル選択あり)
						dparts->DispActHumKanSelectTehaiParts( SPACE_XSIZE, 
					                   PLY_YSTART+pnum*PLY_YSIZE+40, 
					                   tk->ply_act_tehaicount[pnum], 
					                   tk->ply_act_tehaitbl[pnum],
					                   tk->ply_act_tehai_tbl_aka[pnum],
					                   tk->kyoku[kyoku_index].act_hai[actid],
					                   tk->kyoku[kyoku_index].act_aka[actid],
					                   gui->naki_ankan_hai[0],
					                   gui->naki_ankan_hai[1],
					                   gui->naki_ankan_hai[2],
					                   gui->naki_kakan_hai[0],
					                   gui->naki_kakan_hai[1],
					                   gui->naki_kakan_hai[2],
					                   (msx-gui->tehai_x)/HAI_XSIZE);

				// マウス位置の確認(自摸牌)
				}else if( msx > gui->tehai_x+(tk->ply_act_tehaicount[pnum])*HAI_XSIZE+SPACE_XSIZE && 
						  msx < gui->tehai_x+(tk->ply_act_tehaicount[pnum])*HAI_XSIZE+SPACE_XSIZE+HAI_XSIZE &&
						  msy > gui->tehai_y && 
						  msy < gui->tehai_y+HAI_YSIZE){

						dparts->DispActHumKanSelectTehaiParts( SPACE_XSIZE, 
					                   PLY_YSTART+pnum*PLY_YSIZE+40, 
					                   tk->ply_act_tehaicount[pnum], 
					                   tk->ply_act_tehaitbl[pnum],
					                   tk->ply_act_tehai_tbl_aka[pnum],
					                   tk->kyoku[kyoku_index].act_hai[actid],
					                   tk->kyoku[kyoku_index].act_aka[actid],
					                   gui->naki_ankan_hai[0],
					                   gui->naki_ankan_hai[1],
					                   gui->naki_ankan_hai[2],
					                   gui->naki_kakan_hai[0],
					                   gui->naki_kakan_hai[1],
					                   gui->naki_kakan_hai[2],
					                   tk->ply_act_tehaicount[pnum]);

				// 手牌選択していないなら
				}else{

						dparts->DispActHumKanSelectTehaiParts( SPACE_XSIZE, 
					                   PLY_YSTART+pnum*PLY_YSIZE+40, 
					                   tk->ply_act_tehaicount[pnum], 
					                   tk->ply_act_tehaitbl[pnum],
					                   tk->ply_act_tehai_tbl_aka[pnum],
					                   tk->kyoku[kyoku_index].act_hai[actid],
					                   tk->kyoku[kyoku_index].act_aka[actid],
					                   gui->naki_ankan_hai[0],
					                   gui->naki_ankan_hai[1],
					                   gui->naki_ankan_hai[2],
					                   gui->naki_kakan_hai[0],
					                   gui->naki_kakan_hai[1],
					                   gui->naki_kakan_hai[2],
			                           EXCEPT_VALUE);

				} // マウス位置の確認(カン選択モード)終わり

			// 通常モードなら
			}else{

				// マウス位置(手牌内)
				if( msx > gui->tehai_x && 
				    msx < gui->tehai_x + (tk->ply_act_tehaicount[pnum])*HAI_XSIZE && 
				    msy > gui->tehai_y && 
					msy < gui->tehai_y+HAI_YSIZE){

					// 手牌パーツの表示(人プレーヤ用_自摸有り：カーソル選択手牌)
					dparts->DispActTehaiParts(gui->tehai_x,                                         // 手牌X位置
					                      gui->tehai_y,                                             // 手牌Y位置
					                      tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM],                 // 手牌枚数
					                      tk->ply_act_tehaitbl[HUM_PLY_SEKI_NUM],                   // 手牌テーブル
					                      tk->ply_act_tehai_tbl_aka[HUM_PLY_SEKI_NUM],              // 手牌テーブル・赤牌
					                      tk->kyoku[kyoku_index].act_hai[actid],                    // 自摸牌：アクションID
					                      tk->kyoku[kyoku_index].act_aka[actid],                    // 自摸赤：アクションID
						                  EXCEPT_VALUE,                                             // 捨牌：なし
					                      (msx-gui->tehai_x)/HAI_XSIZE, EXCEPT_VALUE,false);        // カーソル選択：手牌


				// マウス位置(自摸牌)
				}else if( msx > gui->tehai_x+(tk->ply_act_tehaicount[pnum])*HAI_XSIZE+SPACE_XSIZE && 
						  msx < gui->tehai_x+(tk->ply_act_tehaicount[pnum])*HAI_XSIZE+SPACE_XSIZE+HAI_XSIZE &&
						  msy > gui->tehai_y && 
						  msy < gui->tehai_y+HAI_YSIZE ){

					// 手牌パーツの表示(人プレーヤ用_自摸有り：カーソル選択自摸牌)
					dparts->DispActTehaiParts( gui->tehai_x,                                        // 手牌X位置
					                      gui->tehai_y,                                             // 手牌Y位置
					                      tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM],                 // 手牌枚数
					                      tk->ply_act_tehaitbl[HUM_PLY_SEKI_NUM],                   // 手牌テーブル
					                      tk->ply_act_tehai_tbl_aka[HUM_PLY_SEKI_NUM],              // 手牌テーブル・赤牌
					                      tk->kyoku[kyoku_index].act_hai[actid],                    // 自摸牌：アクションID
					                      tk->kyoku[kyoku_index].act_aka[actid],                    // 自摸赤：アクションID
					                      EXCEPT_VALUE,                                             // 捨牌：なし
					                      tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM], EXCEPT_VALUE,false);  // カーソル選択：自摸牌

				// マウス位置(手牌外)
				}else{

					// 手牌パーツの表示(人プレーヤ用_自摸有り：カーソル選択なし)
					dparts->DispActTehaiParts( gui->tehai_x, 
					                      gui->tehai_y, 
					                      tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM], 
					                      tk->ply_act_tehaitbl[HUM_PLY_SEKI_NUM],
					                      tk->ply_act_tehai_tbl_aka[HUM_PLY_SEKI_NUM],
					                      tk->kyoku[kyoku_index].act_hai[actid],                    // 自摸牌：アクションID
					                      tk->kyoku[kyoku_index].act_aka[actid],                    // 自摸赤：アクションID
					                      EXCEPT_VALUE,
					                      EXCEPT_VALUE, EXCEPT_VALUE,false);

				} // マウス位置

			} // カン選択モードなら

	// -----------------------------------------------------------
	// 2.手牌表示：自摸時リーチ宣言
	// -----------------------------------------------------------
	}else if( tk->kyoku[kyoku_index].act_stat[actid] == PLYACTRIICH &&
	          tk->kyoku[kyoku_index].act_ply[actid]  == pnum        ){

			// マウス位置の確認
			if( msx > gui->tehai_x && 
			    msx < gui->tehai_x + 13*HAI_XSIZE && 
			    msy > gui->tehai_y && 
				msy < gui->tehai_y+HAI_YSIZE){

					// 手牌パーツの表示(人プレーヤ用：リーチ宣言捨牌選択)
					dparts->DispActHumCanSuteParts( gui->tehai_x, 
					                   gui->tehai_y, 
					                   tk->ply_act_tehaicount[pnum], 
					                   tk->ply_act_tehaitbl[pnum], 
					                   tk->ply_act_tehai_tbl_aka[pnum],
					                   tk->ply_act_tehai_can_sute_tbl[pnum],                        // 手牌テーブル：捨牌可否
					                   tk->kyoku[kyoku_index].act_hai[actid-1],                     // 自摸牌：アクションID
					                   tk->kyoku[kyoku_index].act_aka[actid-1],                     // 自摸赤：アクションID
					                   tk->ply_act_tsumo_can_sute[pnum],                            // 自摸牌：捨牌可否
					                   (msx-gui->tehai_x)/HAI_XSIZE                                 // HUM用の捨牌位置
					                   );

			// マウス位置(自摸牌)
			}else if( msx > gui->tehai_x+(tk->ply_act_tehaicount[pnum])*HAI_XSIZE+SPACE_XSIZE && 
					  msx < gui->tehai_x+(tk->ply_act_tehaicount[pnum])*HAI_XSIZE+SPACE_XSIZE+HAI_XSIZE &&
					  msy > gui->tehai_y && 
					  msy < gui->tehai_y+HAI_YSIZE ){

					// 手牌パーツの表示(人プレーヤ用：リーチ宣言捨牌選択)
					dparts->DispActHumCanSuteParts( gui->tehai_x, 
					                   gui->tehai_y, 
					                   tk->ply_act_tehaicount[pnum], 
					                   tk->ply_act_tehaitbl[pnum], 
					                   tk->ply_act_tehai_tbl_aka[pnum],
					                   tk->ply_act_tehai_can_sute_tbl[pnum],                        // 手牌テーブル：捨牌可否
					                   tk->kyoku[kyoku_index].act_hai[actid-1],                     // 自摸牌：アクションID
					                   tk->kyoku[kyoku_index].act_aka[actid-1],                     // 自摸赤：アクションID
					                   tk->ply_act_tsumo_can_sute[pnum],                            // 自摸牌：捨牌可否
					                   tk->ply_act_tehaicount[pnum]                                 // HUM用の捨牌位置
					                   );

			}else{

					// 手牌パーツの表示(人プレーヤ用：リーチ宣言捨牌選択)
					dparts->DispActHumCanSuteParts( gui->tehai_x, 
					                   gui->tehai_y, 
					                   tk->ply_act_tehaicount[pnum], 
					                   tk->ply_act_tehaitbl[pnum], 
					                   tk->ply_act_tehai_tbl_aka[pnum],
					                   tk->ply_act_tehai_can_sute_tbl[pnum],                        // 手牌テーブル：捨牌可否
					                   tk->kyoku[kyoku_index].act_hai[actid-1],                     // 自摸牌：アクションID
					                   tk->kyoku[kyoku_index].act_aka[actid-1],                     // 自摸赤：アクションID
					                   tk->ply_act_tsumo_can_sute[pnum],                            // 自摸牌：捨牌可否
					                   999                                                          // HUM用の捨牌位置：例外
					                   );

			}

	// -----------------------------------------------------------
	// 3.手牌表示：自摸捨牌時
	// -----------------------------------------------------------
	}else if( tk->kyoku[kyoku_index].act_stat[actid] == PLYACTSUTE &&
	          tk->kyoku[kyoku_index].act_ply[actid]  == pnum       ){

		// クライアントゲームモードがPLYモードであるか
		// if (gui->cli_game_mode == GUI_MJAI_GAMEMODE_PLY_MODE){
		if ( tk->ply_hum_mode == 0 ){
			tmp_sute_stat = tk->ply_tbl_com_sutehai_statnum[HUM_PLY_SEKI_NUM];
		}else{
			tmp_sute_stat = tk->ply_tbl_hum_sutehai_statnum;
		}

		// ----------------------------------------
		// 自摸あり捨牌
		// ----------------------------------------
		if ( tk->kyoku[kyoku_index].act_stat[actid-1] == PLYACTTSUMO || tk->kyoku[kyoku_index].act_stat[actid-1] == PLYRINSHAN ){

				// マウス位置(手牌内)
				if( msx > gui->tehai_x && 
				    msx < gui->tehai_x + (tk->ply_act_tehaicount[pnum])*HAI_XSIZE && 
				    msy > gui->tehai_y && 
					msy < gui->tehai_y+HAI_YSIZE){

					// 手牌パーツの表示(人プレーヤ用_自摸有り：カーソル選択手牌)
					dparts->DispActTehaiParts( gui->tehai_x, 
					                      gui->tehai_y, 
					                      tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM], 
					                      tk->ply_act_tehaitbl[HUM_PLY_SEKI_NUM],
					                      tk->ply_act_tehai_tbl_aka[HUM_PLY_SEKI_NUM],
					                      tk->kyoku[kyoku_index].act_hai[actid-1],                  // 自摸牌：アクションID
					                      tk->kyoku[kyoku_index].act_aka[actid-1],                  // 自摸赤：アクションID
					                      tmp_sute_stat,                                            // 捨牌位置
					                      (msx-gui->tehai_x)/HAI_XSIZE, EXCEPT_VALUE,false);        // カーソル選択：手牌

				// マウス位置(自摸牌)
				}else if( msx > gui->tehai_x+(tk->ply_act_tehaicount[pnum])*HAI_XSIZE+SPACE_XSIZE && 
						  msx < gui->tehai_x+(tk->ply_act_tehaicount[pnum])*HAI_XSIZE+SPACE_XSIZE+HAI_XSIZE &&
						  msy > gui->tehai_y && 
						  msy < gui->tehai_y+HAI_YSIZE ){

					// 手牌パーツの表示(人プレーヤ用_自摸有り：カーソル選択手牌)
					dparts->DispActTehaiParts( gui->tehai_x, 
					                      gui->tehai_y, 
					                      tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM], 
					                      tk->ply_act_tehaitbl[HUM_PLY_SEKI_NUM],
					                      tk->ply_act_tehai_tbl_aka[HUM_PLY_SEKI_NUM],
					                      tk->kyoku[kyoku_index].act_hai[actid-1],                    // 自摸牌：アクションID
					                      tk->kyoku[kyoku_index].act_aka[actid-1],                    // 自摸赤：アクションID
					                      tmp_sute_stat,                                                  // 捨牌位置
					                      tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM], EXCEPT_VALUE,false);  // カーソル選択：自摸牌

				// マウス位置(手牌外)
				}else{

					// 手牌パーツの表示(人プレーヤ用_自摸有り：カーソル選択手牌)
					dparts->DispActTehaiParts( gui->tehai_x, 
					                      gui->tehai_y, 
					                      tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM], 
					                      tk->ply_act_tehaitbl[HUM_PLY_SEKI_NUM],
					                      tk->ply_act_tehai_tbl_aka[HUM_PLY_SEKI_NUM],
					                      tk->kyoku[kyoku_index].act_hai[actid-1],                  // 自摸牌：アクションID
					                      tk->kyoku[kyoku_index].act_aka[actid-1],                  // 自摸赤：アクションID
					                      tmp_sute_stat,                                            // 捨牌位置
					                      EXCEPT_VALUE, EXCEPT_VALUE,false);                        // カーソル選択：なし

				} // マウス位置

		// ----------------------------------------
		// 自摸あり捨牌（リーチ）
		// ----------------------------------------
		}else if(tk->kyoku[kyoku_index].act_stat[actid-1] == PLYACTRIICH){

				// マウス位置(手牌内)
				if( msx > gui->tehai_x && 
				    msx < gui->tehai_x + (tk->ply_act_tehaicount[pnum])*HAI_XSIZE && 
				    msy > gui->tehai_y && 
					msy < gui->tehai_y+HAI_YSIZE){

					// 手牌パーツの表示(人プレーヤ用_自摸有り：カーソル選択手牌)
					dparts->DispActTehaiParts( gui->tehai_x, 
					                      gui->tehai_y, 
					                      tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM], 
					                      tk->ply_act_tehaitbl[HUM_PLY_SEKI_NUM],
					                      tk->ply_act_tehai_tbl_aka[HUM_PLY_SEKI_NUM],
					                      tk->kyoku[kyoku_index].act_hai[actid-2],                  // 自摸牌：アクションID
					                      tk->kyoku[kyoku_index].act_aka[actid-2],                  // 自摸赤：アクションID
					                      tmp_sute_stat,                                            // 捨牌位置
					                      (msx-gui->tehai_x)/HAI_XSIZE, EXCEPT_VALUE,false);        // カーソル選択：手牌

				// マウス位置(自摸牌)
				}else if( msx > gui->tehai_x+(tk->ply_act_tehaicount[pnum])*HAI_XSIZE+SPACE_XSIZE && 
						  msx < gui->tehai_x+(tk->ply_act_tehaicount[pnum])*HAI_XSIZE+SPACE_XSIZE+HAI_XSIZE &&
						  msy > gui->tehai_y && 
						  msy < gui->tehai_y+HAI_YSIZE ){

					// 手牌パーツの表示(人プレーヤ用_自摸有り：カーソル選択手牌)
					dparts->DispActTehaiParts( gui->tehai_x, 
					                      gui->tehai_y, 
					                      tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM], 
					                      tk->ply_act_tehaitbl[HUM_PLY_SEKI_NUM],
					                      tk->ply_act_tehai_tbl_aka[HUM_PLY_SEKI_NUM],
					                      tk->kyoku[kyoku_index].act_hai[actid-2],                    // 自摸牌：アクションID
					                      tk->kyoku[kyoku_index].act_aka[actid-2],                    // 自摸赤：アクションID
					                      tmp_sute_stat,                                                  // 捨牌位置
					                      tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM], EXCEPT_VALUE,false);  // カーソル選択：自摸牌

				// マウス位置(手牌外)
				}else{

					// 手牌パーツの表示(人プレーヤ用_自摸有り：カーソル選択手牌)
					dparts->DispActTehaiParts( gui->tehai_x, 
					                      gui->tehai_y, 
					                      tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM], 
					                      tk->ply_act_tehaitbl[HUM_PLY_SEKI_NUM],
					                      tk->ply_act_tehai_tbl_aka[HUM_PLY_SEKI_NUM],
					                      tk->kyoku[kyoku_index].act_hai[actid-2],                  // 自摸牌：アクションID
					                      tk->kyoku[kyoku_index].act_aka[actid-2],                  // 自摸赤：アクションID
					                      tmp_sute_stat,                                            // 捨牌位置
					                      EXCEPT_VALUE, EXCEPT_VALUE,false);                        // カーソル選択：なし

				} // マウス位置
		}

	// -----------------------------------------------------------
	// 4.手牌表示：自摸切り時
	// -----------------------------------------------------------
	}else if( tk->kyoku[kyoku_index].act_stat[actid] == PLYACTTSUMOGIRI &&
	          tk->kyoku[kyoku_index].act_ply[actid]  == pnum ){

				// マウス位置(手牌内)
				if( msx > gui->tehai_x && 
				    msx < gui->tehai_x + (tk->ply_act_tehaicount[pnum])*HAI_XSIZE && 
				    msy > gui->tehai_y && 
					msy < gui->tehai_y+HAI_YSIZE){

					// 手牌パーツの表示(人プレーヤ用_自摸有り：カーソル選択手牌)
					dparts->DispActTehaiParts( gui->tehai_x, 
					                      gui->tehai_y, 
					                      tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM], 
					                      tk->ply_act_tehaitbl[HUM_PLY_SEKI_NUM],
					                      tk->ply_act_tehai_tbl_aka[HUM_PLY_SEKI_NUM],
					                      EXCEPT_VALUE,                                             // 自摸牌：無し
					                      false,                                                    // 自摸赤：false
						                  EXCEPT_VALUE,                                             // 捨牌：なし
					                      (msx-gui->tehai_x)/HAI_XSIZE, EXCEPT_VALUE,false);        // カーソル選択：手牌

				// マウス位置(自摸牌)
				}else if( msx > gui->tehai_x+(tk->ply_act_tehaicount[pnum])*HAI_XSIZE+SPACE_XSIZE && 
						  msx < gui->tehai_x+(tk->ply_act_tehaicount[pnum])*HAI_XSIZE+SPACE_XSIZE+HAI_XSIZE &&
						  msy > gui->tehai_y && 
						  msy < gui->tehai_y+HAI_YSIZE ){

					// 手牌パーツの表示(人プレーヤ用_自摸有り：カーソル選択手牌)
					dparts->DispActTehaiParts( gui->tehai_x, 
					                      gui->tehai_y, 
					                      tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM], 
					                      tk->ply_act_tehaitbl[HUM_PLY_SEKI_NUM],
					                      tk->ply_act_tehai_tbl_aka[HUM_PLY_SEKI_NUM],
					                      EXCEPT_VALUE,                                                   // 自摸牌：無し
					                      false,                                                          // 自摸赤：false
					                      EXCEPT_VALUE,                                                   // 捨牌：なし
					                      tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM], EXCEPT_VALUE,false);  // カーソル選択：自摸牌

				// マウス位置(手牌外)
				}else{

					// 手牌パーツの表示(人プレーヤ用_自摸有り：カーソル選択手牌)
					dparts->DispActTehaiParts( gui->tehai_x, 
					                      gui->tehai_y, 
					                      tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM], 
					                      tk->ply_act_tehaitbl[HUM_PLY_SEKI_NUM],
					                      tk->ply_act_tehai_tbl_aka[HUM_PLY_SEKI_NUM],
					                      EXCEPT_VALUE,                               // 自摸牌：無し
					                      false,                                      // 自摸赤：false
					                      EXCEPT_VALUE,
					                      EXCEPT_VALUE, EXCEPT_VALUE,false);

				} // マウス位置

	// -----------------------------------------------------------
	// 5.手牌表示：鳴き捨牌時
	// -----------------------------------------------------------
	}else if( tk->kyoku[kyoku_index].act_stat[actid] == PLYACTNAKISUTE &&
	          tk->kyoku[kyoku_index].act_ply[actid]  == pnum ){

				// クライアントゲームモードがPLYモードであるか
				// if (gui->cli_game_mode == GUI_MJAI_GAMEMODE_PLY_MODE){
				if ( tk->ply_hum_mode == 0 ){
					tmp_sute_stat = tk->ply_tbl_hum_sutehai_statnum;
				}else{
					tmp_sute_stat = tk->ply_tbl_com_sutehai_statnum[HUM_PLY_SEKI_NUM];
				}

				// マウス位置(手牌内)
				if( msx > gui->tehai_x && 
				    msx < gui->tehai_x + (tk->ply_act_tehaicount[pnum])*HAI_XSIZE && 
				    msy > gui->tehai_y && 
					msy < gui->tehai_y+HAI_YSIZE){

					// 手牌パーツの表示(人プレーヤ用_自摸有り：カーソル選択手牌)
					dparts->DispActTehaiParts( gui->tehai_x, 
					                      gui->tehai_y, 
					                      tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM], 
					                      tk->ply_act_tehaitbl[HUM_PLY_SEKI_NUM],
					                      tk->ply_act_tehai_tbl_aka[HUM_PLY_SEKI_NUM],
					                      EXCEPT_VALUE,                                             // 自摸牌：無し
					                      false,                                                    // 自摸赤：false
					                      tmp_sute_stat,                                            // 捨牌位置
					                      (msx-gui->tehai_x)/HAI_XSIZE, EXCEPT_VALUE,false);        // カーソル選択：手牌

				// マウス位置(手牌外)
				}else{

					// 手牌パーツの表示(人プレーヤ用_自摸有り：カーソル選択手牌)
					dparts->DispActTehaiParts( gui->tehai_x, 
					                      gui->tehai_y, 
					                      tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM], 
					                      tk->ply_act_tehaitbl[HUM_PLY_SEKI_NUM],
					                      tk->ply_act_tehai_tbl_aka[HUM_PLY_SEKI_NUM],
					                      EXCEPT_VALUE,                                                   // 自摸牌：無し
					                      false,                                                          // 自摸赤：false
					                      tmp_sute_stat,                                                  // 捨牌位置
					                      EXCEPT_VALUE, EXCEPT_VALUE,false);                              // カーソル選択：なし

				} // マウス位置

	// -----------------------------------------------------------
	// 6.手牌表示：鳴き直後
	// -----------------------------------------------------------

	}else if( ( tk->kyoku[kyoku_index].act_stat[actid] == PLYACTPON || 
	       tk->kyoku[kyoku_index].act_stat[actid] == PLYACTCHI ) &&
	       tk->kyoku[kyoku_index].act_ply[actid]  == pnum ){

			// マウス位置の確認
			if( msx > gui->tehai_x && 
			    msx < gui->tehai_x + tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM]*HAI_XSIZE && 
			    msy > gui->tehai_y && 
				msy < gui->tehai_y+HAI_YSIZE){

					// 手牌パーツの表示(人プレーヤ用：リーチ宣言捨牌選択)
					dparts->DispActHumCanSuteParts( gui->tehai_x, 
					                   gui->tehai_y, 
					                   tk->ply_act_tehaicount[pnum], 
					                   tk->ply_act_tehaitbl[pnum], 
					                   tk->ply_act_tehai_tbl_aka[pnum],
					                   tk->ply_act_tehai_can_sute_tbl[pnum],                      // 手牌テーブル：捨牌可否
					                   999,                                                        // 自摸牌：アクションID
					                   false,                                                      // 自摸赤：アクションID
					                   false,                                                      // 自摸牌：捨牌可否
					                   (msx-gui->tehai_x)/HAI_XSIZE                                // HUM用の捨牌位置
					                   );

			}else{

					// 手牌パーツの表示(人プレーヤ用：リーチ宣言捨牌選択)
					dparts->DispActHumCanSuteParts( gui->tehai_x, 
					                   gui->tehai_y, 
					                   tk->ply_act_tehaicount[pnum], 
					                   tk->ply_act_tehaitbl[pnum], 
					                   tk->ply_act_tehai_tbl_aka[pnum],
					                   tk->ply_act_tehai_can_sute_tbl[pnum],                       // 手牌テーブル：捨牌可否
					                   999,                                                         // 自摸牌：アクションID
					                   false,                                                       // 自摸赤：アクションID
					                   false,                                                       // 自摸牌：捨牌可否
					                   999                                                          // HUM用の捨牌位置：例外
					                   );
			}

	// -----------------------------------------------------------
	// 7.手牌表示：それ以外の手牌表示(自摸なし・捨牌なし)
	// -----------------------------------------------------------
	}else{

				// マウス位置(手牌内)
				if( msx > gui->tehai_x && 
				    msx < gui->tehai_x + (tk->ply_act_tehaicount[pnum])*HAI_XSIZE && 
				    msy > gui->tehai_y && 
					msy < gui->tehai_y+HAI_YSIZE){

					// 手牌パーツの表示(人プレーヤ用_自摸無し：カーソル選択手牌)
					dparts->DispActTehaiParts( gui->tehai_x, 
					                      gui->tehai_y, 
					                      tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM], 
					                      tk->ply_act_tehaitbl[HUM_PLY_SEKI_NUM],
					                      tk->ply_act_tehai_tbl_aka[HUM_PLY_SEKI_NUM],
					                      EXCEPT_VALUE,                                             // 自摸牌：無し
					                      false,                                                    // 自摸赤：false
						                  EXCEPT_VALUE,                                             // 捨牌：なし
					                      (msx-gui->tehai_x)/HAI_XSIZE, EXCEPT_VALUE,false);        // カーソル選択：手牌

				// マウス位置(自摸牌)
				}else if( msx > gui->tehai_x+(tk->ply_act_tehaicount[pnum])*HAI_XSIZE+SPACE_XSIZE && 
						  msx < gui->tehai_x+(tk->ply_act_tehaicount[pnum])*HAI_XSIZE+SPACE_XSIZE+HAI_XSIZE &&
						  msy > gui->tehai_y && 
						  msy < gui->tehai_y+HAI_YSIZE ){

					// 手牌パーツの表示(人プレーヤ用_自摸無し：カーソル選択手牌)
					dparts->DispActTehaiParts( gui->tehai_x, 
					                      gui->tehai_y, 
					                      tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM], 
					                      tk->ply_act_tehaitbl[HUM_PLY_SEKI_NUM],
					                      tk->ply_act_tehai_tbl_aka[HUM_PLY_SEKI_NUM],
					                      EXCEPT_VALUE,                                                   // 自摸牌：無し
					                      false,                                                          // 自摸赤：false
					                      EXCEPT_VALUE,                                                   // 捨牌：なし
					                      tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM], EXCEPT_VALUE,false);  // カーソル選択：自摸牌

				// マウス位置(手牌外)
				}else{

					// 手牌パーツの表示(人プレーヤ用_自摸無し：カーソル選択無し)
					dparts->DispActTehaiParts( gui->tehai_x, 
					                      gui->tehai_y, 
					                      tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM], 
					                      tk->ply_act_tehaitbl[HUM_PLY_SEKI_NUM],
					                      tk->ply_act_tehai_tbl_aka[HUM_PLY_SEKI_NUM],
					                      EXCEPT_VALUE,                               // 自摸牌：無し
					                      false,                                      // 自摸赤：false
					                      EXCEPT_VALUE,                               // 捨牌：なし
					                      EXCEPT_VALUE, EXCEPT_VALUE, false);         // カーソル選択：なし

				} // マウス位置(処理終了)

	// -----------------------------------------------------------
	// 8.処理終了
	// -----------------------------------------------------------

	}

}

/* ---------------------------------------------------------------------------------------------- */
// アクション手牌表示・ライナーCOM表示
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DispActTehaiCom(MJSTkinfo *tk, MJSGui *gui, int kyoku_index, int actid, int pnum, int msx, int msy){

	// -----------------------------------------------------------
	// 席情報
	// -----------------------------------------------------------

	// 席情報設定
	wsprintf(tmp_disp_msg,"[席%d]%s", pnum+1, tk->plyname[pnum]);

	// 自プレーヤーの席情報定義
	dparts->DispString( gui->tehai_x, 
	                    gui->tehai_y - STRING_YSIZE - NAME_TEHAI_RANGE, 
	                   tmp_disp_msg);

	// -----------------------------------------------------------
	// 1.手牌表示：自摸時
	// -----------------------------------------------------------
	if ( ( tk->kyoku[kyoku_index].act_stat[actid] == PLYACTTSUMO || 
	       tk->kyoku[kyoku_index].act_stat[actid] == PLYRINSHAN  || 
	       tk->kyoku[kyoku_index].act_stat[actid] == PLYTSUMOAGARI ) &&
	       tk->kyoku[kyoku_index].act_ply[actid]  == pnum ){

		// 裏表示であるかどうか
		if ( tk->com_no_chk_tehai_flg == true ){

			// 伏せられた手牌表示(自摸有)
			dparts->DisplayUnkownTehai(0, PLY_YSTART+pnum*PLY_YSIZE+40, tk->ply_act_tehaicount[pnum], true, EXCEPT_VALUE);

		}else{

			// 手牌パーツの表示(COM手牌)
			dparts->DispActTehaiParts( SPACE_XSIZE, 
			                   PLY_YSTART+pnum*PLY_YSIZE+40, 
			                   tk->ply_act_tehaicount[pnum], 
			                   tk->ply_act_tehaitbl[pnum],
			                   tk->ply_act_tehai_tbl_aka[pnum],
			                   tk->kyoku[kyoku_index].act_hai[actid],
			                   tk->kyoku[kyoku_index].act_aka[actid],
			                   EXCEPT_VALUE,
			                   EXCEPT_VALUE, EXCEPT_VALUE,false);

		}

	// -----------------------------------------------------------
	// 2.手牌表示：自摸時リーチ宣言
	// -----------------------------------------------------------
	}else if( tk->kyoku[kyoku_index].act_stat[actid] == PLYACTRIICH &&
	          tk->kyoku[kyoku_index].act_ply[actid]  == pnum        ){

		// 裏表示であるかどうか
		if ( tk->com_no_chk_tehai_flg == true ){

			// 伏せられた手牌表示(自摸有)
			dparts->DisplayUnkownTehai(0, PLY_YSTART+pnum*PLY_YSIZE+40, tk->ply_act_tehaicount[pnum], true, EXCEPT_VALUE);

		}else{

			// 手牌パーツの表示(COM手牌)
			dparts->DispActTehaiParts( SPACE_XSIZE, 
			                   PLY_YSTART+pnum*PLY_YSIZE+40, 
			                   tk->ply_act_tehaicount[pnum], 
			                   tk->ply_act_tehaitbl[pnum],
			                   tk->ply_act_tehai_tbl_aka[pnum],
			                   tk->kyoku[kyoku_index].act_hai[actid-1],
			                   tk->kyoku[kyoku_index].act_aka[actid-1],
			                   EXCEPT_VALUE,
			                   EXCEPT_VALUE, EXCEPT_VALUE,false);

		}

	// -----------------------------------------------------------
	// 3.手牌表示：自摸捨牌時
	// -----------------------------------------------------------
	}else if( tk->kyoku[kyoku_index].act_stat[actid] == PLYACTSUTE &&
	          tk->kyoku[kyoku_index].act_ply[actid]  == pnum       ){

		// 裏表示であるかどうか
		if ( tk->com_no_chk_tehai_flg == true ){

			// 伏せられた手牌表示(自摸捨て)
			dparts->DisplayUnkownTehai(0, PLY_YSTART+pnum*PLY_YSIZE+40, tk->ply_act_tehaicount[pnum], true, tk->ply_tbl_com_sutehai_statnum[pnum]);

		}else{

			// 3-1.自摸あり捨牌（リーチ）
			if(tk->kyoku[kyoku_index].act_stat[actid-1] == PLYACTRIICH){

				// 手牌パーツの表示(自摸あり捨牌：リーチ宣言)
				dparts->DispActTehaiParts( SPACE_XSIZE, 
			                   PLY_YSTART+pnum*PLY_YSIZE+40, 
			                   tk->ply_act_tehaicount[pnum], 
			                   tk->ply_act_tehaitbl[pnum],
			                   tk->ply_act_tehai_tbl_aka[pnum],
			                   tk->kyoku[kyoku_index].act_hai[actid-2],
			                   tk->kyoku[kyoku_index].act_aka[actid-2],
			                   tk->ply_tbl_com_sutehai_statnum[pnum],        // COM手牌の捨牌位置
			                   EXCEPT_VALUE, EXCEPT_VALUE,false);

			// 3-2.通常時(リーチ以外)
			}else{

				// 手牌パーツの表示(自摸あり捨牌)
				dparts->DispActTehaiParts( SPACE_XSIZE, 
			                   PLY_YSTART+pnum*PLY_YSIZE+40, 
			                   tk->ply_act_tehaicount[pnum], 
			                   tk->ply_act_tehaitbl[pnum],
			                   tk->ply_act_tehai_tbl_aka[pnum],
			                   tk->kyoku[kyoku_index].act_hai[actid-1],
			                   tk->kyoku[kyoku_index].act_aka[actid-1],
			                   tk->ply_tbl_com_sutehai_statnum[pnum],
			                   EXCEPT_VALUE, EXCEPT_VALUE,false);

			}

		}

	// -----------------------------------------------------------
	// 4.手牌表示：自摸切り時→それ以外に集約
	// -----------------------------------------------------------

	// -----------------------------------------------------------
	// 5.手牌表示：鳴き捨牌時
	// -----------------------------------------------------------
	}else if( tk->kyoku[kyoku_index].act_stat[actid] == PLYACTNAKISUTE &&
	          tk->kyoku[kyoku_index].act_ply[actid]  == pnum       ){

		// 裏表示であるかどうか
		if ( tk->com_no_chk_tehai_flg == true ){

			// 伏せられた手牌表示(自摸無)
			dparts->DisplayUnkownTehai(0, 
			        PLY_YSTART+pnum*PLY_YSIZE+40, 
			        tk->ply_act_tehaicount[pnum],
			        false, 
			        tk->ply_tbl_com_sutehai_statnum[pnum]
			        );

		}else{
				// 手牌パーツの表示(COM手牌：自摸あり捨牌あり)
				dparts->DispActTehaiParts( SPACE_XSIZE, 
			                   PLY_YSTART+pnum*PLY_YSIZE+40, 
			                   tk->ply_act_tehaicount[pnum],
			                   tk->ply_act_tehaitbl[pnum],
			                   tk->ply_act_tehai_tbl_aka[pnum], 
		                       EXCEPT_VALUE, false,
			                   tk->ply_tbl_com_sutehai_statnum[pnum],        // COM用の捨牌位置
			                   EXCEPT_VALUE, EXCEPT_VALUE,false);

		}


	// -----------------------------------------------------------
	// 6.手牌表示：鳴き直後→COM処理なし
	// -----------------------------------------------------------


	// -----------------------------------------------------------
	// 7.手牌表示：それ以外の手牌表示(自摸なし・捨牌なし)
	// -----------------------------------------------------------
	}else{

		// 裏表示であるかどうか
		if ( tk->com_no_chk_tehai_flg == true ){

			// 伏せられた手牌表示(自摸無)
			dparts->DisplayUnkownTehai(0, PLY_YSTART+pnum*PLY_YSIZE+40, tk->ply_act_tehaicount[pnum], false, EXCEPT_VALUE);

		}else{
			// 手牌パーツの表示(COM手牌)
			dparts->DispActTehaiParts( SPACE_XSIZE, 
			                   PLY_YSTART+pnum*PLY_YSIZE+40, 
			                   tk->ply_act_tehaicount[pnum],
			                   tk->ply_act_tehaitbl[pnum],
			                   tk->ply_act_tehai_tbl_aka[pnum], 
		                       EXCEPT_VALUE, false,
			                   EXCEPT_VALUE,
			                   EXCEPT_VALUE, EXCEPT_VALUE,false);

		}

	// -----------------------------------------------------------
	// 8.処理終了
	// -----------------------------------------------------------

	}
}

/* ---------------------------------------------------------------------------------------------- */
// 囲み卓表示のテスト表示用
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DispActTehai_test_square(MJSGui *gui){

	// ----------------------------------------
	// 手牌数設定
	// ----------------------------------------
	int tmp_tehai_tbl_count_up    =  1;
	int tmp_tehai_tbl_count_down  =  1;
	int tmp_tehai_tbl_count_left  =  1;
	int tmp_tehai_tbl_count_right =  1;

	// 卓ベース表示
	DrawBox( TAKU_PLT_X_STAT, TAKU_PLT_Y_STAT, TAKU_PLT_X_SIZE-1, TAKU_PLT_Y_SIZE-1, GetColor( 0, 64, 0 ), TRUE ) ;

	// センタープレート
	dparts->DispCenterPlt( (TAKU_PLT_X_SIZE + TAKU_PLT_X_STAT)/2 - HAI_XSIZE*3,
	               (TAKU_PLT_Y_SIZE + TAKU_PLT_Y_STAT)/2 - HAI_XSIZE*3 );

	// ----------------------------------------
	// アクションプレート
	// ----------------------------------------

	// アクションプレート_UP
	wsprintf(tmp_disp_msg,"リーチ");
	dparts->DispActplt_up( gui->tehai_up_x + HAI_XSIZE * TEHAI_MAX + 56, 
	                       gui->tehai_up_y + HAI_YSIZE + STRING_YSIZE + NAME_TEHAI_RANGE, 
	                       tmp_disp_msg);

/*
	DrawBox( gui->tehai_up_x + HAI_XSIZE * TEHAI_MAX + 60 - 56, 
	         gui->tehai_up_y + HAI_YSIZE + STRING_YSIZE + NAME_TEHAI_RANGE + 4 - 23, 
	         gui->tehai_up_x + HAI_XSIZE * TEHAI_MAX + 60, 
	         gui->tehai_up_y + HAI_YSIZE + STRING_YSIZE + NAME_TEHAI_RANGE + 4, 
	         GetColor( 128, 0, 0 ), TRUE ) ;

	// アクションプレート(文字)_UP
	wsprintf(tmp_disp_msg,"リーチ");
	DrawRotaString( gui->tehai_up_x + HAI_XSIZE * TEHAI_MAX + 60 - 4, 
	                gui->tehai_up_y + HAI_YSIZE + STRING_YSIZE + NAME_TEHAI_RANGE, 
	                1.0, 1.0, 0, 0, PI, GetColor( 255, 255, 255 ), 0, FALSE, tmp_disp_msg);
*/

	// アクションプレート_DOWN
	wsprintf(tmp_disp_msg,"リーチ");
	dparts->DispActplt_down( gui->tehai_x - 56, 
	                         gui->tehai_y - STRING_YSIZE - NAME_TEHAI_RANGE, 
	                         tmp_disp_msg);

/*
	DrawBox( gui->tehai_x - 56 - 4, 
	         gui->tehai_y - STRING_YSIZE - NAME_TEHAI_RANGE-4,
	         gui->tehai_x - 56 + 56,
	         gui->tehai_y - STRING_YSIZE - NAME_TEHAI_RANGE-4+23,
	         GetColor( 128, 0, 0 ), TRUE ) ;

	// アクションプレート(文字)_DOWN
	dparts->DispString( gui->tehai_x - 56, gui->tehai_y - STRING_YSIZE - NAME_TEHAI_RANGE, tmp_disp_msg);
*/

	// アクションプレート_LEFT
	wsprintf(tmp_disp_msg,"リーチ");
	dparts->DispActplt_left( gui->tehai_left_x + HAI_YSIZE + STRING_YSIZE + NAME_TEHAI_RANGE, 
	                         gui->tehai_left_y - 56,
	                         tmp_disp_msg);

/*
	DrawBox( gui->tehai_left_x + HAI_YSIZE + STRING_YSIZE + NAME_TEHAI_RANGE - 23 + 4 , 
	         gui->tehai_left_y - 60,
             gui->tehai_left_x + HAI_YSIZE + STRING_YSIZE + NAME_TEHAI_RANGE + 4 , 
	         gui->tehai_left_y - 60 + 56,
	         GetColor( 128, 0, 0 ), TRUE ) ;

	// アクションプレート(文字)_LEFT
	DrawRotaString( gui->tehai_left_x + HAI_YSIZE + STRING_YSIZE + NAME_TEHAI_RANGE, 
	                gui->tehai_left_y - 60 + 4,
	                1.0, 1.0, 0, 0, PI / 2.0, GetColor( 255, 255, 255 ), 0, FALSE, tmp_disp_msg);
*/

	// アクションプレート_RIGHT
	wsprintf(tmp_disp_msg,"リーチ");
	dparts->DispActplt_right( gui->tehai_right_x - STRING_YSIZE - NAME_TEHAI_RANGE, 
	                          gui->tehai_right_y + HAI_XSIZE * TEHAI_MAX + HAI_XSIZE + 10 + 56, 
	                          tmp_disp_msg);

/*
	DrawBox( gui->tehai_right_x - STRING_YSIZE - NAME_TEHAI_RANGE - 4 , 
	         gui->tehai_right_y + HAI_XSIZE * TEHAI_MAX + HAI_XSIZE + 10 + 60 - 56,
             gui->tehai_right_x - STRING_YSIZE - NAME_TEHAI_RANGE - 4 + 23, 
	         gui->tehai_right_y + HAI_XSIZE * TEHAI_MAX + HAI_XSIZE + 10 + 60 + 4,
	         GetColor( 128, 0, 0 ), TRUE ) ;

	// アクションプレート(文字)_RIGHT
	wsprintf(tmp_disp_msg,"リーチ");
	DrawRotaString( gui->tehai_right_x - STRING_YSIZE - NAME_TEHAI_RANGE, 
	                gui->tehai_right_y + HAI_XSIZE * TEHAI_MAX + HAI_XSIZE + 10 + 60, 
	                1.0, 1.0, 0, 0, PI*3.0 / 2.0, GetColor( 255, 255, 255 ), 0, FALSE, tmp_disp_msg);
*/

	// ----------------------------------------
	// 席情報の表示
	// ----------------------------------------

	// 席情報UP
	DrawRotaString( gui->tehai_up_x + HAI_XSIZE * TEHAI_MAX, 
	                gui->tehai_up_y + HAI_YSIZE + STRING_YSIZE + NAME_TEHAI_RANGE, 
	                1.0, 1.0, 0, 0, PI, GetColor( 255, 255, 255 ), 0, FALSE, "[席2]ひまわり青");

	// 席情報DONW
	wsprintf(tmp_disp_msg,"[席4]ひまわり緑");
	dparts->DispString( gui->tehai_x, 
	                    gui->tehai_y - STRING_YSIZE - NAME_TEHAI_RANGE, 
	                    tmp_disp_msg);

	// 席情報LEFT
	DrawRotaString( gui->tehai_left_x + HAI_YSIZE + STRING_YSIZE + NAME_TEHAI_RANGE, 
	                gui->tehai_left_y,                                           
	                1.0, 1.0, 0, 0, PI / 2.0, GetColor( 255, 255, 255 ), 0, FALSE, "[席3]ひまわり緑");

	// 席情報RIGHT
	DrawRotaString( gui->tehai_right_x - STRING_YSIZE - NAME_TEHAI_RANGE, 
	                gui->tehai_right_y + HAI_XSIZE * TEHAI_MAX + HAI_XSIZE + 10, 
	                1.0, 1.0, 0, 0, PI*3.0 / 2.0, GetColor( 255, 255, 255 ), 0, FALSE, "[席1]ひまわり赤");

	// ----------------------------------------
	// 手牌の表示
	// ----------------------------------------

	// 手牌表示(Rightプレーヤ)
		dparts->DispLHai( gui->tehai_right_x, (TEHAI_MAX - tmp_tehai_tbl_count_right) * HAI_XSIZE + gui->tehai_right_y               , 31, false, false, 0, 0);         // 右自摸

	for(int tmp_i = 0; tmp_i < tmp_tehai_tbl_count_right; tmp_i++){
		dparts->DispLHai( gui->tehai_right_x, (TEHAI_MAX - tmp_tehai_tbl_count_right) * HAI_XSIZE + gui->tehai_right_y + HAI_XSIZE+10+tmp_i*24, 31, false, false, 0, 0);       // 右手牌
	}

	// 手牌表示(UPプレーヤ)
	for(int tmp_i = 0; tmp_i < tmp_tehai_tbl_count_up; tmp_i++){
		dparts->DispHai( gui->tehai_up_x + (TEHAI_MAX - tmp_tehai_tbl_count_up) * HAI_XSIZE + HAI_XSIZE * tmp_i,       gui->tehai_up_y, 32, false, true, 0, 0);         // UPプレーヤ手牌
	}
		dparts->DispHai( gui->tehai_up_x + (TEHAI_MAX - tmp_tehai_tbl_count_up) * HAI_XSIZE - HAI_XSIZE - SPACE_XSIZE, gui->tehai_up_y, 32, false, true, 0, 0);         // UPプレーヤ自摸

	// 手牌表示(Leftプレーヤ)
	for(int tmp_i = 0; tmp_i < tmp_tehai_tbl_count_left; tmp_i++){
		dparts->DispLHai( gui->tehai_left_x, gui->tehai_left_y + tmp_i * LHAI_YSIZE, 33, false, true, 0, 0);                                                            // 左手牌
	}
		dparts->DispLHai( gui->tehai_left_x, gui->tehai_left_y + tmp_tehai_tbl_count_left * LHAI_YSIZE + 10, 33, false, true, 0, 0);                                    // 左自摸(13*24)

	// 手牌表示(DOWNプレーヤ)
	for(int tmp_i = 0; tmp_i < tmp_tehai_tbl_count_down; tmp_i++){
		dparts->DispHai( gui->tehai_x + HAI_XSIZE * tmp_i,                                  gui->tehai_y, 34, false, false, 0, 0);                                      // DOWNプレーヤ手牌
	}
		dparts->DispHai( gui->tehai_x + HAI_XSIZE * tmp_tehai_tbl_count_down + SPACE_XSIZE, gui->tehai_y, 34, false, false, 0, 0);                                      // DOWNプレーヤ自摸

	// ----------------------------------------
	// 鳴牌の表示
	// ----------------------------------------

	// 横列鳴き表示
	if( gui->disp_square_naki_mentsu == 0 ){

		// 鳴牌表示(UPプレーヤ)
		for(int tmp_i = 0; tmp_i < 4 ; tmp_i++){
			dparts->DispHai( gui->nakihai_line_up_x + NAKI_MENTSU_RANGE*tmp_i - HAI_XSIZE*0, gui->nakihai_line_up_y,  0, false, true, 0, 0);
			dparts->DispHai( gui->nakihai_line_up_x + NAKI_MENTSU_RANGE*tmp_i - HAI_XSIZE*1, gui->nakihai_line_up_y, 32, false, true, 0, 0);
			dparts->DispHai( gui->nakihai_line_up_x + NAKI_MENTSU_RANGE*tmp_i - HAI_XSIZE*2, gui->nakihai_line_up_y, 32, false, true, 0, 0);
			dparts->DispHai( gui->nakihai_line_up_x + NAKI_MENTSU_RANGE*tmp_i - HAI_XSIZE*3, gui->nakihai_line_up_y,  0, false, true, 0, 0);
		}

		// 鳴牌表示(DOWNプレーヤ)
		for(int tmp_i = 0; tmp_i < 4; tmp_i++){
			dparts->DispActSarashiParts( gui->nakihai_line_down_x - NAKI_MENTSU_RANGE*tmp_i, gui->nakihai_line_down_y, ANKAN, 34, false);
		}

		// 鳴牌表示(RIGHTプレーヤ)
		for(int tmp_i = 0; tmp_i < 4; tmp_i++){
			dparts->DispLHai( gui->nakihai_line_right_x, gui->nakihai_line_right_y + NAKI_MENTSU_RANGE*tmp_i - HAI_XSIZE*3,  0, false, false, 0, 0);
			dparts->DispLHai( gui->nakihai_line_right_x, gui->nakihai_line_right_y + NAKI_MENTSU_RANGE*tmp_i - HAI_XSIZE*2, 31, false, false, 0, 0);
			dparts->DispLHai( gui->nakihai_line_right_x, gui->nakihai_line_right_y + NAKI_MENTSU_RANGE*tmp_i - HAI_XSIZE*1, 31, false, false, 0, 0);
			dparts->DispLHai( gui->nakihai_line_right_x, gui->nakihai_line_right_y + NAKI_MENTSU_RANGE*tmp_i - HAI_XSIZE*0,  0, false, false, 0, 0);
		}

		// 鳴牌表示(LEFTプレーヤ)
		for(int tmp_i = 0; tmp_i < 4; tmp_i++){
			dparts->DispLHai( gui->nakihai_line_left_x, gui->nakihai_line_left_y - NAKI_MENTSU_RANGE*tmp_i + HAI_XSIZE*0,  0, false, true, 0, 0);
			dparts->DispLHai( gui->nakihai_line_left_x, gui->nakihai_line_left_y - NAKI_MENTSU_RANGE*tmp_i + HAI_XSIZE*1, 33, false, true, 0, 0);
			dparts->DispLHai( gui->nakihai_line_left_x, gui->nakihai_line_left_y - NAKI_MENTSU_RANGE*tmp_i + HAI_XSIZE*2, 33, false, true, 0, 0);
			dparts->DispLHai( gui->nakihai_line_left_x, gui->nakihai_line_left_y - NAKI_MENTSU_RANGE*tmp_i + HAI_XSIZE*3,  0, false, true, 0, 0);
		}

	// 縦列鳴き表示
	}else{

		// 縦列鳴牌表示(LEFTプレーヤ)
		for(int tmp_i = 0; tmp_i < 4; tmp_i++){
			dparts->DispLHai( gui->nakihai_left_x + tmp_i*LHAI_XSIZE, gui->nakihai_left_y + LHAI_YSIZE*0,  0, false, true, 0, 0);
			dparts->DispLHai( gui->nakihai_left_x + tmp_i*LHAI_XSIZE, gui->nakihai_left_y + LHAI_YSIZE*1, 33, false, true, 0, 0);
			dparts->DispLHai( gui->nakihai_left_x + tmp_i*LHAI_XSIZE, gui->nakihai_left_y + LHAI_YSIZE*2, 33, false, true, 0, 0);
			dparts->DispLHai( gui->nakihai_left_x + tmp_i*LHAI_XSIZE, gui->nakihai_left_y + LHAI_YSIZE*3,  0, false, true, 0, 0);
		}

		// 縦列鳴牌表示(RIGHTプレーヤ)
		for(int tmp_i = 0; tmp_i < 4; tmp_i++){
			dparts->DispLHai( gui->nakihai_right_x + LHAI_XSIZE*(3-tmp_i), gui->nakihai_right_y + LHAI_YSIZE*0,  0, false, false, 0, 0);
			dparts->DispLHai( gui->nakihai_right_x + LHAI_XSIZE*(3-tmp_i), gui->nakihai_right_y + LHAI_YSIZE*1, 31, false, false, 0, 0);
			dparts->DispLHai( gui->nakihai_right_x + LHAI_XSIZE*(3-tmp_i), gui->nakihai_right_y + LHAI_YSIZE*2, 31, false, false, 0, 0);
			dparts->DispLHai( gui->nakihai_right_x + LHAI_XSIZE*(3-tmp_i), gui->nakihai_right_y + LHAI_YSIZE*3,  0, false, false, 0, 0);
		}

	}

	// ----------------------------------------
	// 捨牌の表示
	// ----------------------------------------

	// 捨牌表示(RIGHTプレーヤ)
	for(int tmp_i = 0; tmp_i < LINE_SUTEHAI_COUNT_MAX; tmp_i++){
		dparts->DispLHai( gui->sutehai_right_x + LHAI_XSIZE*0, gui->sutehai_right_y + tmp_i*LHAI_YSIZE, 31, false, false, 0, 0);      // 右一段目
		dparts->DispLHai( gui->sutehai_right_x + LHAI_XSIZE*1, gui->sutehai_right_y + tmp_i*LHAI_YSIZE, 31, false, false, 0, 0);      // 右二段目
		dparts->DispLHai( gui->sutehai_right_x + LHAI_XSIZE*2, gui->sutehai_right_y + tmp_i*LHAI_YSIZE, 31, false, false, 0, 0);      // 右三段目
		dparts->DispLHai( gui->sutehai_right_x + LHAI_XSIZE*3, gui->sutehai_right_y + tmp_i*LHAI_YSIZE, 31, false, false, 0, 0);      // 右四段目
	}

	// 捨牌表示(UPプレーヤ)
	for(int tmp_i = 0; tmp_i < LINE_SUTEHAI_COUNT_MAX; tmp_i++){
		dparts->DispHai( gui->sutehai_up_x + HAI_XSIZE*tmp_i, gui->sutehai_up_y              ,32, false, true, 0, 0);             // 上四段目
		dparts->DispHai( gui->sutehai_up_x + HAI_XSIZE*tmp_i, gui->sutehai_up_y + HAI_YSIZE*1,32, false, true, 0, 0);             // 上三段目
		dparts->DispHai( gui->sutehai_up_x + HAI_XSIZE*tmp_i, gui->sutehai_up_y + HAI_YSIZE*2,32, false, true, 0, 0);             // 上二段目
		dparts->DispHai( gui->sutehai_up_x + HAI_XSIZE*tmp_i, gui->sutehai_up_y + HAI_YSIZE*3,32, false, true, 0, 0);             // 上一段目
	}

	// 捨牌表示(LEFTプレーヤ)
	for(int tmp_i = 0; tmp_i < LINE_SUTEHAI_COUNT_MAX; tmp_i++){
		dparts->DispLHai( gui->sutehai_left_x - LHAI_XSIZE*0, gui->sutehai_left_y + tmp_i*LHAI_YSIZE, 33, false, true, 0, 0);       // 左四段目
		dparts->DispLHai( gui->sutehai_left_x - LHAI_XSIZE*1, gui->sutehai_left_y + tmp_i*LHAI_YSIZE, 33, false, true, 0, 0);       // 左三段目
		dparts->DispLHai( gui->sutehai_left_x - LHAI_XSIZE*2, gui->sutehai_left_y + tmp_i*LHAI_YSIZE, 33, false, true, 0, 0);       // 左二段目
		dparts->DispLHai( gui->sutehai_left_x - LHAI_XSIZE*3, gui->sutehai_left_y + tmp_i*LHAI_YSIZE, 33, false, true, 0, 0);       // 左一段目
	}

	// 捨牌表示(DOWNプレーヤ)
	for(int tmp_i = 0; tmp_i < LINE_SUTEHAI_COUNT_MAX; tmp_i++){
		dparts->DispHai( gui->sutehai_down_x+HAI_XSIZE*tmp_i, gui->sutehai_down_y,             34, false, false, 0, 0);       // 下一段目
		dparts->DispHai( gui->sutehai_down_x+HAI_XSIZE*tmp_i, gui->sutehai_down_y+HAI_YSIZE*1, 34, false, false, 0, 0);       // 下二段目
		dparts->DispHai( gui->sutehai_down_x+HAI_XSIZE*tmp_i, gui->sutehai_down_y+HAI_YSIZE*2, 34, false, false, 0, 0);       // 下三段目
		dparts->DispHai( gui->sutehai_down_x+HAI_XSIZE*tmp_i, gui->sutehai_down_y+HAI_YSIZE*3, 34, false, false, 0, 0);       // 下四段目
	}

}

/* ---------------------------------------------------------------------------------------------- */
// 設定画面：メイン画面
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplaySetting(MJSGui *gui, float mFps, int total_frame_count, int ver1, int ver2, int ver3, int ver4, int ver5){

	// ----------------------------------------
	// 初期描画処理
	// ----------------------------------------
	dparts->DispPartsClearDraw();

	// ----------------------------------------
	// パーツ表示
	// ----------------------------------------
	dparts->DispBunner(ver1, ver2, ver3, ver4, ver5);                                     // バナー
	dparts->DispMousepoint(5, 750, gui->msx, gui->msy, gui->Button[0], gui->Button[1]);   // マウス位置
	dparts->DispFps(670, 750, mFps, total_frame_count, 0);                                // FPS

	// 設定情報表示
	DrawFormatString(4, 4, GetColor(255,255,255), "設定画面");

	// ----------------------------------------
	// 設定画面表示
	// ----------------------------------------
	if(gui->set_mode == SETTING_FILENAME_MJAI_MODE){

		// ファイル名取得
		DisplayFileNameDiag(gui,GUI_LOG_MJAILOG);

		// モード変更
		gui->set_mode = SETTING_INFO_MODE;

	}else if(gui->set_mode == SETTING_FILENAME_MJSCORE_MODE){

		// ファイル名取得
		DisplayFileNameDiag(gui,GUI_LOG_MJSCORE);

		// モード変更
		gui->set_mode = SETTING_INFO_MODE;

	}else{

		// 画面表示
		DisplaySettingInfo(gui);

	}

	// ----------------------------------------
	// 裏画面を表画面に反映
	// ----------------------------------------
	dparts->DispPartsFlip();

}

/* ---------------------------------------------------------------------------------------------- */
// 設定画面：ファイル選択ダイアグ
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplaySettingInfo(MJSGui *gui){

	// 初期設定
	char cdir[192];
	GetCurrentDirectory(192,cdir);

	// 設定ボタン表示
	for(int tmp_i = 0; tmp_i < 5; tmp_i++){
		dparts->DispButton(SETTING_X_START, SETTING_Y_START+tmp_i*SETTING_Y_RANGE, PARTS_BUT_BLUE);
	}

	// ログ名表示(入力用)
	DrawFormatString(SETTING_X_START+40, SETTING_Y_START+0*SETTING_Y_RANGE+8, GetColor(255,255,255), "mjai      PATH:%s", gui->log_name_mjai);
	DrawFormatString(SETTING_X_START+40, SETTING_Y_START+1*SETTING_Y_RANGE+8, GetColor(255,255,255), "mjsocre   PATH:%s", gui->log_name_mjsocre);

	// ログ名表示(出力用)
	DrawFormatString(SETTING_X_START+40, SETTING_Y_START+2*SETTING_Y_RANGE+8, GetColor(255,255,255), "tklog     PATH:%s", gui->tklog_name);
	DrawFormatString(SETTING_X_START+40, SETTING_Y_START+3*SETTING_Y_RANGE+8, GetColor(255,255,255), "clientlog PATH:%s", gui->clientlog_name);

	// (デバグ用)カレントディレクトリ名表示
	DrawFormatString(SETTING_X_START+40, SETTING_Y_START+4*SETTING_Y_RANGE+8, GetColor(255,255,255), "cdir      PATH:%s", cdir);

	// 終了ボタン表示
	dparts->DispButton(SETTING_X_START,    SETTING_ENDBUT_Y_START  , PARTS_BUT_RED);
	DrawFormatString(  SETTING_X_START+40, SETTING_ENDBUT_Y_START+8, GetColor(255,255,255), "設定終了");

}

/* ---------------------------------------------------------------------------------------------- */
// 設定画面：ファイル選択ダイアグ
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplayFileNameDiag(MJSGui *gui, LBGuiLogType log_type){

	// 変数定義
	OPENFILENAME ofn ;
	char tmp_log_name[FULLPATH_LOGNAME_SIZE];               // ファイル名の一時置き

	// 事前定義
	tmp_log_name[0] = '\0' ;
	memset( &ofn, 0, sizeof( OPENFILENAME ) ) ;
	ofn.lStructSize  = sizeof( OPENFILENAME ) ;
	ofn.hwndOwner    = GetMainWindowHandle()  ;             // 親ウインドウは GetMainWindowHandle で取得できるウインドウハンドルにする
	ofn.nFilterIndex = 1 ;
	ofn.nMaxFile     = 256 ;
	ofn.lpstrTitle   = "牌譜ログの選択" ;
	ofn.Flags        = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY ;
	ofn.lpstrFile    = tmp_log_name ;                       // ファイル名を代入

	// ログ種別設定
	      if(log_type == GUI_LOG_MJAILOG){
		ofn.lpstrFilter  = "mjai(*.json)\0*.json"  ;        // 拡張子指定
		ofn.lpstrDefExt  = "json";
	}else if(log_type == GUI_LOG_MJSCORE){
		ofn.lpstrFilter  = "mjscore(*.txt)\0*.txt"  ;       // 拡張子指定
		ofn.lpstrDefExt  = "txt";
	}

	// ファイル名取得
	GetOpenFileName( &ofn ) ;

	// ファイル名定義
	if (tmp_log_name[0] != '\0'){

		// ログ種別ごとのファイル名定義
		      if(log_type == GUI_LOG_MJAILOG){
			wsprintf(gui->log_name_mjai, tmp_log_name);
		}else if(log_type == GUI_LOG_MJSCORE){
			wsprintf(gui->log_name_mjsocre, tmp_log_name);
		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// ソース終了
/* ---------------------------------------------------------------------------------------------- */
