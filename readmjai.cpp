/* ---------------------------------------------------------------------------------------------- 
 * 
 * プログラム概要 ： Newさくら麻雀(MJAIクライアント実装版)
 * バージョン     ： 0.1.2.1.229(MJAIログ表示：ダブロン表示)
 * プログラム名   ： mjs.exe
 * ファイル名     ： readmjai.cpp
 * クラス名       ： MJSReadMjai
 * 処理概要       ： MJAIログ読み込みクラス
 * Ver0.1.2作成日 ： 2023/10/07 22:32:26
 * 最終更新日     ： 2024/11/17 16:53:23
 * 
 * Copyright (c) 2022-2023 TechMileStoraJP, All rights reserved.
 * 
 * ---------------------------------------------------------------------------------------------- */

#include "readmjai.h"

/* ---------------------------------------------------------------------------------------------- */
// 初期化処理
/* ---------------------------------------------------------------------------------------------- */
void MJSReadMjai::read_logfile_init(MJSGui *gui){

	// ----------------------------------------
	// ファイル初期化
	// ----------------------------------------

	// MJAIログのファイル名定義
	// char fname[] = "mjailog.json";
	// wsprintf(gui->log_name_mjai,"mjailog.json");

	// C11で導入 VisualC++2012以降ではこちらのみ使用可能
	errno_t err; // errno_t型(int型)

	// fopen処理
	// err = fopen_s(&fp, fname, "r");     // ファイルを開く。失敗するとエラーコードを返す。
	err = fopen_s(&fp, gui->log_name_mjai, "r");     // ファイルを開く。失敗するとエラーコードを返す。
	if(err != 0) {
		MessageBox(NULL, "fopen失敗", "失敗", MB_OK);
	} 

	// ----------------------------------------
	// デバグログ
	// ----------------------------------------
/*
	// クライアントクラス向けのデバグログ
	mjaidebug = new MJSCorelog;

	// ログファイル名設定
	wsprintf(mjaidebug_name, ".\\mjai_debuglog.log" );
	mjaidebug->CorelogInit(mjaidebug_name);

	// ヘッダー定義
	wsprintf(mjaidebug_buf, "ヘッダー\n----\n" );

	// ログ出力
	mjaidebug->CorelogPrint(mjaidebug_buf);
*/

}

/* ---------------------------------------------------------------------------------------------- */
// 後処理
/* ---------------------------------------------------------------------------------------------- */
void MJSReadMjai::read_logfile_post(){

	// ----------------------------------------
	// ファイルクローズ
	// ----------------------------------------

	// ファイルクローズ
	fclose(fp); 

	// ----------------------------------------
	// デバグログ
	// ----------------------------------------

	// delete mjaidebug;

}

/* ---------------------------------------------------------------------------------------------- */
// 読み込み実行処理
/* ---------------------------------------------------------------------------------------------- */
void MJSReadMjai::read_logfile_exec(MJSTkinfo *tk, MJSGui *gui){

	// ----------------------------------------
	// fgets処理
	// ----------------------------------------
	while( fgets( line_buf, MJAI_LINE_BUF, fp) != NULL) {

		// ----------------------
		// ライン解析
		// ----------------------
		// wsprintf(line_buf, line_buf);         // ラインバッファへのコピー
		Read_logline(gui);                       // ライン解析

		// ----------------------
		// (デバグ)ログ出力
		// ----------------------
/*
		// Gui_wkクラスの出力
		for(int tmp_i = 0; tmp_i < gui->wk_str_count; tmp_i++){
			wsprintf(mjaidebug_buf, "%d:%s\n", tmp_i, gui->wk_str[tmp_i]);
			mjaidebug->CorelogPrint(mjaidebug_buf);
		}
		wsprintf(mjaidebug_buf, "----\n" );
		mjaidebug->CorelogPrint(mjaidebug_buf);
*/

		// ----------------------
		// 卓情報クラスの設定
		// ----------------------
		set_tkinfo(tk, gui);

	}

}

/* ---------------------------------------------------------------------------------------------- */
// MJAIログの読み込み
/* ---------------------------------------------------------------------------------------------- */
void MJSReadMjai::Read_logline(MJSGui *gui){

	// ----------------------------------------
	// 初期化
	// ----------------------------------------

	// wkインデックスの初期化
	gui->wk_str_count = 0;

	// 読み込み文字定義用
	int  line_buf_point;                //  fgetのバッファの位置取り
	char tmp_wk_str[1024];              //  1ワードのバッファ用
	char tmp_buf[3];                    //  分割処理用

	// 空白確認フラグ
	int space_flg;                      // 0：文字なし(空白スペースのみ) 1：空白以外の文字列

	// 値の初期化
	line_buf_point = 0;
	space_flg = 0;                      // 「空白」「改行」以外の半角文字を読込んだ場合は、「space_flg = 1」とする。
	wsprintf(tmp_wk_str, "");

	/* ---------------------------------------- */
	// fgetで取得した文字列を行末まで確認する
	/* ---------------------------------------- */
    while( line_buf[line_buf_point] != '\0' ){

		// 全角・半角の判定
		if(_ismbblead(line_buf[line_buf_point])){

			/* ---------------------------------------- */
			// 全角文字の格納
			/* ---------------------------------------- */
			tmp_buf[0] = line_buf[line_buf_point];
			tmp_buf[1] = line_buf[line_buf_point+1];
			tmp_buf[2] = '\0';
			line_buf_point+=2;

			// 全角文字処理
			space_flg = 1;
			wsprintf(tmp_wk_str, "%s%s", tmp_wk_str, tmp_buf);

		}else{

			/* ---------------------------------------- */
			// 半角文字の格納
			/* ---------------------------------------- */
			tmp_buf[0] = line_buf[line_buf_point];
			tmp_buf[1] = '\0';
			line_buf_point++;

			/* ---------------------------------------- */
			// 文字抽出(空白)
			/* ---------------------------------------- */
			if ( strcmp(tmp_buf, ":" ) == 0 || strcmp(tmp_buf, "," ) == 0 ){

				// 「空白区切り」で文字を追記
				if(space_flg == 1){
					space_flg = 0;

					// wk構造体に一時データを格納、その後tmp_wk_strは初期化
					set_wkinfo(gui, tmp_wk_str);
					wsprintf(tmp_wk_str, "");

				}

			/* ---------------------------------------- */
			// 無視文字
			/* ---------------------------------------- */
			}else if( strcmp(tmp_buf, "{") == 0  || 
			          strcmp(tmp_buf, "}") == 0  || 
			          strcmp(tmp_buf, "\"") == 0 || 
			          strcmp(tmp_buf, "[") == 0  || 
			          strcmp(tmp_buf, "]") == 0  ){

			/* ---------------------------------------- */
			// 文字抽出(改行)
			/* ---------------------------------------- */
			}else if(strcmp(tmp_buf, "\n") == 0){

				// 「空白区切り」で文字を追記
				if(space_flg == 1){
					space_flg = 0;

					// wk構造体に一時データを格納、その後tmp_wk_strは初期化
					set_wkinfo(gui, tmp_wk_str);
					wsprintf(tmp_wk_str, "");

				}

				// 「改行区切り」処理の場合は、間に「+」文字を挿入する
				wsprintf(tmp_wk_str, "+");
				set_wkinfo(gui, tmp_wk_str);

				// 値の初期化
				wsprintf(tmp_wk_str, "");

			/* ---------------------------------------- */
			// その他の文字抽出
			/* ---------------------------------------- */
			}else{

				// 「空白」「改行」以外の半角文字処理
				space_flg = 1;
				wsprintf(tmp_wk_str, "%s%s", tmp_wk_str, tmp_buf);

			}

		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// Guiクラスに一時データを格納
/* ---------------------------------------------------------------------------------------------- */
void MJSReadMjai::set_wkinfo(MJSGui *gui, char* str){

	wsprintf(gui->wk_str[gui->wk_str_count], "%s", str);
	gui->wk_str_count++;

}

/* ---------------------------------------------------------------------------------------------- */
// 卓情報クラスの設定処理
/* ---------------------------------------------------------------------------------------------- */
void MJSReadMjai::set_tkinfo(MJSTkinfo *tk, MJSGui *gui){

	// ----------------------------------------
	// 受信メッセージの解析
	// ----------------------------------------
	for( int tmp_i = 0; tmp_i < gui->wk_str_count; tmp_i++ ) {

		// -----------------------
		// 改行
		// -----------------------
		if(strcmp(gui->wk_str[tmp_i], "+" ) == 0 ){

			// 改行の場合は何もしない

		// -----------------------
		// 卓開始(01:start_game)
		// -----------------------
		}else if(strcmp(gui->wk_str[tmp_i], "type" ) == 0 && 
			         strcmp(gui->wk_str[tmp_i+1], "start_game" ) == 0 ){

			// アクション設定
			set_type_startgame(tk, gui, tmp_i);

			// メッセージ確定のために処理抜け
			break;

		// -----------------------
		// 局開始(02:start_kyoku)
		// -----------------------
		}else if(strcmp(gui->wk_str[tmp_i], "type" ) == 0 && 
		         strcmp(gui->wk_str[tmp_i+1], "start_kyoku" ) == 0 ){

			// アクション設定
			set_type_startkyoku(tk, gui, tmp_i);

			// メッセージ確定のために処理抜け
			break;

		// -----------------------
		// 自摸アクション(03:type_tsumo)
		// -----------------------
		}else if(strcmp(gui->wk_str[tmp_i], "type"  ) == 0 && 
			         strcmp(gui->wk_str[tmp_i+1], "tsumo" ) == 0 ){

			// アクション設定
			set_type_tsumo(tk, gui, tmp_i);

			// メッセージ確定のために処理抜け
			break;

		// -----------------------
		// 捨牌処理(04:type_dahai)
		// -----------------------
		}else if(strcmp(gui->wk_str[tmp_i], "type"  ) == 0 && 
			         strcmp(gui->wk_str[tmp_i+1], "dahai" ) == 0 ){

			// アクション設定
			set_type_dahai(tk, gui, tmp_i);

			// メッセージ確定のために処理抜け
			break;

		// -----------------------
		// 暗槓アクション
		// -----------------------
		}else if(strcmp(gui->wk_str[tmp_i], "type"  ) == 0 && 
			         strcmp(gui->wk_str[tmp_i+1], "ankan" ) == 0 ){

			// アクション設定：暗槓アクション
			set_type_ankan(tk, gui, tmp_i);

			// メッセージ確定のために処理抜け
			break;

		// -----------------------
		// 加槓アクション
		// -----------------------
		}else if(strcmp(gui->wk_str[tmp_i], "type"  ) == 0 && 
		         strcmp(gui->wk_str[tmp_i+1], "kakan" ) == 0 ){

			// アクション設定：加槓アクション
			set_type_kakan(tk, gui, tmp_i);

			// メッセージ確定のために処理抜け
			break;

		// -----------------------
		// リーチ宣言アクション
		// -----------------------
		}else if(strcmp(gui->wk_str[tmp_i], "type"  ) == 0 && 
			         strcmp(gui->wk_str[tmp_i+1], "reach" ) == 0 ){

			// アクション設定：リーチ宣言アクション
			set_type_riichi(tk, gui, tmp_i);

			// メッセージ確定のために処理抜け
			break;

		// -----------------------
		// リーチ宣言受け入れ
		// -----------------------
		}else if(strcmp(gui->wk_str[tmp_i], "type"  ) == 0 && 
		         strcmp(gui->wk_str[tmp_i+1], "reach_accepted" ) == 0 ){

			// アクション設定
			set_type_reach_accepted(tk, gui, tmp_i);

			// メッセージ確定のために処理抜け
			break;

		// -----------------------
		// ポン処理
		// -----------------------
		}else if(strcmp(gui->wk_str[tmp_i], "type"  ) == 0 && 
			         strcmp(gui->wk_str[tmp_i+1], "pon" ) == 0 ){

			// アクション設定
			set_type_pon(tk, gui, tmp_i);

			// メッセージ確定のために処理抜け
			break;

		// -----------------------
		// チー処理
		// -----------------------
		}else if(strcmp(gui->wk_str[tmp_i], "type"  ) == 0 && 
			         strcmp(gui->wk_str[tmp_i+1], "chi" ) == 0 ){

			// アクション設定
			set_type_chi(tk, gui, tmp_i);

			// メッセージ確定のために処理抜け
			break;

		// -----------------------
		// ミンカン処理
		// -----------------------
		}else if(strcmp(gui->wk_str[tmp_i], "type"  ) == 0 && 
			         strcmp(gui->wk_str[tmp_i+1], "daiminkan" ) == 0 ){

			// アクション設定
			set_type_minkan(tk, gui, tmp_i);

			// メッセージ確定のために処理抜け
			break;

		// -----------------------
		// カンドラ表示
		// -----------------------
		}else if(strcmp(gui->wk_str[tmp_i], "type"  ) == 0 && 
		         strcmp(gui->wk_str[tmp_i+1], "dora" ) == 0 ){

			// アクション設定
			set_type_dora_open(tk, gui, tmp_i);

			// メッセージ確定のために処理抜け
			break;

		// -----------------------
		// 和了確認
		// -----------------------
		}else if(strcmp(gui->wk_str[tmp_i], "type"  ) == 0 && 
			         strcmp(gui->wk_str[tmp_i+1], "hora" ) == 0 ){

			// アクション設定
			set_type_hora(tk, gui, tmp_i);

			// メッセージ確定のために処理抜け
			break;

		// -----------------------
		// 流局
		// -----------------------
		}else if(strcmp(gui->wk_str[tmp_i], "type"  ) == 0 && 
			         strcmp(gui->wk_str[tmp_i+1], "ryukyoku" ) == 0 ){

			// アクション設定
			set_type_ryukyoku(tk, gui, tmp_i);

			// メッセージ確定のために処理抜け
			break;

		// -----------------------
		// 局終了
		// -----------------------
		}else if(strcmp(gui->wk_str[tmp_i], "type"  ) == 0 && 
		         strcmp(gui->wk_str[tmp_i+1], "end_kyoku" ) == 0 ){

			// アクション設定
			set_type_endkyoku(tk, gui, tmp_i);

			// メッセージ確定のために処理抜け
			break;

		// -----------------------
		// 卓ゲーム終了
		// -----------------------
		}else if(strcmp(gui->wk_str[tmp_i], "type"  ) == 0 && 
			         strcmp(gui->wk_str[tmp_i+1], "end_game" ) == 0 ){

			// アクション設定
			set_type_endgame(tk, gui, tmp_i);

			// メッセージ確定のために処理抜け
			break;

		// -----------------------
		// エラー処理
		// -----------------------
		}else if(strcmp(gui->wk_str[tmp_i], "type"  ) == 0 && 
			         strcmp(gui->wk_str[tmp_i+1], "error" ) == 0 ){

			// エラー処理
			tk->stat = TAKUERR;

			// メッセージ確定のために処理抜け
			break;

		// -----------------------
		// その他のアクション
		// -----------------------
		}else{

			// wk_str_countでforループで回している間は何もしない

		}

		// -----------------------
		// アクション確認はここまで
		// -----------------------

	} // gui->wk_countのループ


}

/* ---------------------------------------------------------------------------------------------- */
// 01:type_startgame
/* ---------------------------------------------------------------------------------------------- */
void MJSReadMjai::set_type_startgame(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num){

	// ----------------------------------------
	// 局情報設定
	// ----------------------------------------

	// 局情報
	tk->kyoku[tk->kyoku_index].kyoku = 0;

	// ツミ棒
	tk->kyoku[tk->kyoku_index].tsumibo = 0;

	// リーチ棒
	tk->kyoku[tk->kyoku_index].riichbo = 0;

	// ----------------------------------------
	// プレーヤー名の設定
	// ----------------------------------------

	for( int tmp_pnum = 0; tmp_pnum < PLAYER_MAX; tmp_pnum++ ) {
		// プレーヤ名指定
		wsprintf(tk->plyname[tmp_pnum], gui->wk_str[tmp_pnum+3]);
	}

	// ----------------------------------------
	// 卓ステータス設定
	// ----------------------------------------
	tk->stat = TAKUSTART;

}

/* ---------------------------------------------------------------------------------------------- */
// 02:type_startkyoku
/* ---------------------------------------------------------------------------------------------- */
void MJSReadMjai::set_type_startkyoku(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num){

	// ----------------------------------------
	// 前処理
	// ----------------------------------------

	// 初期化
	int  haipai_point=0;
	int  now_tsumo_hai=0;
	bool now_tsumo_aka = false;
	int  tmp_ie_id;
	int  tmp_dora_hai;
	bool tmp_dora_aka;

	// ----------------------------------------
	// GUIモード初期化
	// ----------------------------------------
	gui->guiTakuInit();

	// ----------------------------------------
	// 局IDのカウント
	// ----------------------------------------

	// 卓開始であるならば
	if (tk->stat == TAKUSTART){
		tk->kyoku_index = 0;
	}else{

	}

	// ----------------------------------------
	// 局情報初期化
	// ----------------------------------------
	tk->KyokuInit();

	// ----------------------------------------
	// 局の算出
	// ----------------------------------------
	// 局
	tk->kyoku[tk->kyoku_index].kyoku = ( Get_hainum(gui->wk_str[tmp_wk_num+3] ) - 31 )*4 + // E(東場)かS(南場)の文字列確認
	                                  atoi(gui->wk_str[tmp_wk_num+7]) - 1;                 // 局情報取得

	// ----------------------------------------
	// 局情報定義
	// ----------------------------------------

	// 本場
	tk->kyoku[tk->kyoku_index].tsumibo = atoi(gui->wk_str[tmp_wk_num+9]);

	// リーチ棒
	tk->kyoku[tk->kyoku_index].riichbo = atoi(gui->wk_str[tmp_wk_num+11]);

	// シード番号
	tk->kyoku[tk->kyoku_index].seed_num = 0;

	// ----------------------------------------
	// 得点定義
	// ----------------------------------------
	for(int tmp_pnum = 0; tmp_pnum < 4; tmp_pnum++){
		tk->kyoku[tk->kyoku_index].ply_kyoku_start_score[tmp_pnum] = atoi(gui->wk_str[tmp_wk_num+15+tmp_pnum]);
	}

	// ----------------------------------------
	// ドラ定義
	// ----------------------------------------

	// ドラ表示牌
	tmp_dora_hai = Get_hainum(gui->wk_str[tmp_wk_num+5]);

	// 赤牌確認
	if (tmp_dora_hai > 100){
		tmp_dora_hai = tmp_dora_hai - 100;
		tmp_dora_aka = true;
	}else{
		tmp_dora_aka = false;
	}

	// ドラ表示牌定義
	tk->kyoku[tk->kyoku_index].doracount     = 1;
	tk->kyoku[tk->kyoku_index].dora_actid[0] = 0;
	tk->kyoku[tk->kyoku_index].dora[0]       = tmp_dora_hai;
	tk->kyoku[tk->kyoku_index].dora_aka[0]   = tmp_dora_aka;

	// ----------------------------------------
	// 家情報
	// ----------------------------------------
	tk->kyoku[tk->kyoku_index].kyoku_oya = atoi(gui->wk_str[tmp_wk_num+13]);
	tmp_ie_id                            = atoi(gui->wk_str[tmp_wk_num+13]);
	for( int tmp_i = 0; tmp_i < PLAYER_MAX; tmp_i++ ) {
		tk->kyoku[tk->kyoku_index].ie[tmp_ie_id] = tmp_i;
		tmp_ie_id = (tmp_ie_id+1) % 4;
	}

	// ----------------------------------------
	// 配牌設定
	// ----------------------------------------

	// 配牌設定
	for(int tmp_pnum=0; tmp_pnum < 4; tmp_pnum++){

		// 配牌ポインター設定
		haipai_point=tmp_wk_num + 20 + TEHAI_MAX * tmp_pnum;

		for(int tmp_i=0; tmp_i < TEHAI_MAX; tmp_i++){

			// ----------------------------------------
			// 牌情報設定
			// ----------------------------------------

			// 配牌確認
			now_tsumo_hai=Get_hainum(gui->wk_str[haipai_point+tmp_i]);

			// 赤牌確認
			if (now_tsumo_hai > 100){
				now_tsumo_hai = now_tsumo_hai - 100;
				now_tsumo_aka = true;
			}else{
				now_tsumo_aka = false;
			}

			// ----------------------------------------
			// Tkinfoクラス配牌設定
			// ----------------------------------------

			// 手牌追加
			tk->kyoku[tk->kyoku_index].tehai[tmp_pnum][now_tsumo_hai]++;

			// 赤牌追加
			if(now_tsumo_aka == true){
				tk->kyoku[tk->kyoku_index].aka_count[tmp_pnum][(now_tsumo_hai-5)/10]++;
			}
		}
	}

	// ----------------------------------------
	// アクション情報設定 - 配牌時
	// ----------------------------------------

	// ACT_IDの設定
	tk->kyoku[tk->kyoku_index].act_count = 0;

	// 定義設定
	tk->kyoku[tk->kyoku_index].act_stat[0]  = HAIPAI;
	tk->kyoku[tk->kyoku_index].act_ply[0]   = 4;
	tk->kyoku[tk->kyoku_index].react_ply[0] = 4;
	tk->kyoku[tk->kyoku_index].act_hai[0]   = 0;

	// ----------------------------------------
	// プレーヤー手牌情報設定
	// ----------------------------------------
	// 手牌枚数
	for(int tmp_i=0; tmp_i < PLAYER_MAX; tmp_i++){
		tk->ply_act_tehaicount[tmp_i] = TEHAI_MAX;
	}

	// ----------------------------------------
	// 卓ステータス設定
	// ----------------------------------------
	tk->stat = HAIPAI;

}

/* ---------------------------------------------------------------------------------------------- */
// 03:type_tsumo
/* ---------------------------------------------------------------------------------------------- */
void MJSReadMjai::set_type_tsumo(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num){

	// アクション定義
	// https://gimite.net/pukiwiki/index.php?Mjai%20%E9%BA%BB%E9%9B%80AI%E5%AF%BE%E6%88%A6%E3%82%B5%E3%83%BC%E3%83%90

	// 初期化
	int tmp_ply_id;

	// 卓ステータス設定
	tk->stat = PLYACTTSUMO;

	// 手番設定
	tmp_ply_id = atoi(gui->wk_str[tmp_wk_num+3]);

	// ----------------------------------------
	// 牌情報設定
	// ----------------------------------------

	// 自摸牌確認
	tk->ply_act_tsumo[tmp_ply_id] = Get_hainum(gui->wk_str[tmp_wk_num+5]);

	// 赤牌確認
	if (tk->ply_act_tsumo[tmp_ply_id]  > 100){
		tk->ply_act_tsumo[tmp_ply_id]  = tk->ply_act_tsumo[tmp_ply_id]  - 100;
		tk->ply_act_tsumo_aka[tmp_ply_id] = true;
	}else{
		tk->ply_act_tsumo_aka[tmp_ply_id] = false;
	}

	// -----------------------------------------------------------
	// アクション設定 - 自摸処理
	// -----------------------------------------------------------
	tk->SetActInfo(tk->kyoku_index,
			PLYACTTSUMO,
			tmp_ply_id,
			4,
			tk->ply_act_tsumo[tmp_ply_id],
			tk->ply_act_tsumo_aka[tmp_ply_id]
	);

}

/* ---------------------------------------------------------------------------------------------- */
// 04:type_dahai
/* ---------------------------------------------------------------------------------------------- */
void MJSReadMjai::set_type_dahai(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num){

	// アクション定義
	// https://gimite.net/pukiwiki/index.php?Mjai%20%E9%BA%BB%E9%9B%80AI%E5%AF%BE%E6%88%A6%E3%82%B5%E3%83%BC%E3%83%90

	// ----------------------------------------
	// 初期化
	// ----------------------------------------
	int tmp_ply_id;

	// 手番設定
	tmp_ply_id = atoi(gui->wk_str[tmp_wk_num+3]);

	// ----------------------------------------
	// 卓ステータス設定(dahai処理)
	// ----------------------------------------
	if(strcmp(gui->wk_str[tmp_wk_num+7], "true") == 0 ){
			// 自摸切りアクション
			tk->stat = PLYACTTSUMOGIRI;
	// 捨牌処理
	}else{
		// 一つ前の処理鳴きアクションの場合は
		if(tk->kyoku[tk->kyoku_index].act_stat[tk->kyoku[tk->kyoku_index].act_count] == PLYACTPON ||
		   tk->kyoku[tk->kyoku_index].act_stat[tk->kyoku[tk->kyoku_index].act_count] == PLYACTCHI ){
			// 鳴牌アクション
			tk->stat = PLYACTNAKISUTE;
		}else{
			// 捨牌アクション
			tk->stat = PLYACTSUTE;
		}
	}

	// ----------------------------------------
	// 捨牌定義
	// ----------------------------------------

	// 捨牌設定
	tk->ply_act_sute[tmp_ply_id] = Get_hainum(gui->wk_str[tmp_wk_num+5]);

	// 赤牌確認
	if ( tk->ply_act_sute[tmp_ply_id] > 100){
		 tk->ply_act_sute[tmp_ply_id] = tk->ply_act_sute[tmp_ply_id] - 100;
		 tk->ply_act_sute_aka[tmp_ply_id] = true;
	}else{
		 tk->ply_act_sute_aka[tmp_ply_id] = false;
	}

	// デバグ用
	if ( tk->ply_act_sute[tmp_ply_id] > 37 || tk->ply_act_sute[tmp_ply_id] < 0){
		 tk->ply_act_sute[tmp_ply_id] = 0;
	}

	// -----------------------------------------------------------
	// アクション設定
	// -----------------------------------------------------------
	tk->SetActInfo(tk->kyoku_index,
		tk->stat,
		tmp_ply_id,
		4,
		tk->ply_act_sute[tmp_ply_id],
		tk->ply_act_sute_aka[tmp_ply_id]
	);

}

/* ---------------------------------------------------------------------------------------------- */
// 05:type_ankan
/* ---------------------------------------------------------------------------------------------- */
void MJSReadMjai::set_type_ankan(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num){

	int tmp_naki_seki;

	int  tmp_naki_hai = 0;
	bool tmp_naki_aka = false ;
	int  tmp_aka_count = 0;

	// ----------------------------------------
	// REACTプレーヤー(targetプレーヤー)の特定
	// ----------------------------------------

	// プレーヤーID確認
	tmp_naki_seki  = atoi(gui->wk_str[tmp_wk_num+3]);

	// ----------------------------------------
	// カカン牌確認
	// ----------------------------------------

	// 手牌読込
	tmp_naki_hai = Get_hainum(gui->wk_str[tmp_wk_num+5]);

	// 赤牌確認
	if (tmp_naki_hai > 100){
		tmp_naki_hai = tmp_naki_hai - 100;
		tmp_naki_aka = true;
		// 赤牌加算
		tmp_aka_count++;
	}else{
		tmp_naki_aka = false;
	}

	// ----------------------------------------
	// アクション設定 - アンカン
	// ----------------------------------------
	tk->SetActInfo(tk->kyoku_index,
		PLYACTANKAN,
		tmp_naki_seki,
		4,
		tmp_naki_hai,
		tmp_naki_aka
	);

	// ----------------------------------------
	// 晒し情報設定 - アンカン
	// ----------------------------------------
	tk->SetNakiInfo(tk->kyoku_index,                                                // 局INDEX
		ANKAN,                                                                      // プレーヤアクション
		tmp_naki_seki,                                                              // 鳴きプレーヤー
		tk->kyoku[tk->kyoku_index].act_count,                                       // ACTID
		tk->kyoku[tk->kyoku_index].act_hai[tk->kyoku[tk->kyoku_index].act_count],   // 鳴き牌定義
		tk->kyoku[tk->kyoku_index].act_hai[tk->kyoku[tk->kyoku_index].act_count],   // 鳴きINDEX牌定義
		tmp_aka_count);                                                             // 赤牌枚数

	// ----------------------------------------
	// 卓ステータス設定
	// ----------------------------------------
	tk->stat = PLYACTANKAN;

}

/* ---------------------------------------------------------------------------------------------- */
// 06:type_kakan
/* ---------------------------------------------------------------------------------------------- */
void MJSReadMjai::set_type_kakan(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num){

	int tmp_naki_seki;

	int  tmp_naki_hai = 0;
	bool tmp_naki_aka = false ;
	int  tmp_aka_count = 0;

	// ----------------------------------------
	// REACTプレーヤー(targetプレーヤー)の特定
	// ----------------------------------------

	// プレーヤーID確認
	tmp_naki_seki  = atoi(gui->wk_str[tmp_wk_num+3]);

	// ----------------------------------------
	// カカン牌確認
	// ----------------------------------------

	// 手牌読込
	tmp_naki_hai = Get_hainum(gui->wk_str[tmp_wk_num+5]);

	// 赤牌確認
	if (tmp_naki_hai > 100){
		tmp_naki_hai = tmp_naki_hai - 100;
		tmp_naki_aka = true;
		// 赤牌加算
		tmp_aka_count++;
	}else{
		tmp_naki_aka = false;
	}

	// ----------------------------------------
	// アクション設定 - カカン
	// ----------------------------------------
	tk->SetActInfo(tk->kyoku_index,
		PLYACTKAKAN,
		tmp_naki_seki,
		4,
		tmp_naki_hai,
		tmp_naki_aka
	);

	// ----------------------------------------
	// 晒し情報設定 - カカン
	// ----------------------------------------
	tk->SetNakiInfo(tk->kyoku_index, 
		KAKAN, 
		tmp_naki_seki,                                                              // 鳴きプレーヤー
		tk->kyoku[tk->kyoku_index].act_count,                                       // ACTID
		tk->kyoku[tk->kyoku_index].act_hai[tk->kyoku[tk->kyoku_index].act_count],   // 鳴き牌定義
		tk->kyoku[tk->kyoku_index].act_hai[tk->kyoku[tk->kyoku_index].act_count],   // 鳴きINDEX牌定義
		tmp_aka_count);

	// ----------------------------------------
	// 卓ステータス設定
	// ----------------------------------------
	tk->stat = PLYACTKAKAN;

}

/* ---------------------------------------------------------------------------------------------- */
// 07:type_riichi
/* ---------------------------------------------------------------------------------------------- */
void MJSReadMjai::set_type_riichi(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num){

	// ----------------------------------------
	// 初期化
	// ----------------------------------------
	int tmp_ply_id;

	// ----------------------------------------
	// REACTプレーヤー(targetプレーヤー)の特定
	// ----------------------------------------

	// プレーヤーID確認
	tmp_ply_id  = atoi(gui->wk_str[tmp_wk_num+3]);

	// -----------------------------------------------------------
	// アクション設定 - リーチ宣言
	// -----------------------------------------------------------
	tk->SetActInfo(tk->kyoku_index, // 局INDEX
		PLYACTRIICH,                // アクション情報 / リーチ
		tmp_ply_id,                 // アクションプレーヤ
		4,                          // リアクションプレーヤ
		0,                          // 牌番号
		false                       // 赤牌
	);

}

/* ---------------------------------------------------------------------------------------------- */
// 08:set_type_reach_accepted
/* ---------------------------------------------------------------------------------------------- */
void MJSReadMjai::set_type_reach_accepted(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num){

	// ----------------------------------------
	// 初期化
	// ----------------------------------------
	int tmp_ply_id;

	// ----------------------------------------
	// REACTプレーヤー(targetプレーヤー)の特定
	// ----------------------------------------

	// プレーヤーID確認
	tmp_ply_id  = atoi(gui->wk_str[tmp_wk_num+3]);

	// -----------------------------------------------------------
	// アクション設定 - リーチ宣言受入
	// -----------------------------------------------------------
	tk->SetActInfo(tk->kyoku_index, // 局INDEX
		PLYRIICHACCEPTED,           // アクション情報 / リーチ受入
		4,                          // アクションプレーヤ
		4,                          // リアクションプレーヤ
		0,                          // 牌番号
		false                       // 赤牌
	);

}

/* ---------------------------------------------------------------------------------------------- */
// 08:set_type_pon
/* ---------------------------------------------------------------------------------------------- */
void MJSReadMjai::set_type_pon(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num){

	int tmp_naki_seki;
	int tmp_react_seki;

	int  tmp_naki_hai = 0;
	bool tmp_naki_aka = false ;
	int  tmp_aka_count = 0;

	// ----------------------------------------
	// REACTプレーヤー(targetプレーヤー)の特定
	// ----------------------------------------

	// プレーヤーID確認
	tmp_naki_seki  = atoi(gui->wk_str[tmp_wk_num+3]);
	tmp_react_seki = atoi(gui->wk_str[tmp_wk_num+5]);

	// ----------------------------------------
	// ポン牌確認(捨牌)
	// ----------------------------------------

	// 手牌読込
	tmp_naki_hai = Get_hainum(gui->wk_str[tmp_wk_num+7]);

	// 赤牌確認
	if (tmp_naki_hai > 100){
		tmp_naki_hai = tmp_naki_hai - 100;
		tmp_naki_aka = true;
		// 赤牌加算
		tmp_aka_count++;
	}else{
		tmp_naki_aka = false;
	}

	// ----------------------------------------
	// ポン牌確認(1枚目)
	// ----------------------------------------


	// ----------------------------------------
	// ポン牌確認(2枚目)
	// ----------------------------------------


	// ----------------------------------------
	// アクション設定 - ポン
	// ----------------------------------------
	tk->SetActInfo(tk->kyoku_index,
		PLYACTPON,
		tmp_naki_seki,
		tmp_react_seki,
		tmp_naki_hai,
		tmp_naki_aka
	);

	// ----------------------------------------
	// 晒し情報設定 - ポン
	// ----------------------------------------
	tk->SetNakiInfo(tk->kyoku_index, 
		MINKO, 
		tmp_naki_seki,                            // 鳴きプレーヤー
		tk->kyoku[tk->kyoku_index].act_count,     // ACTID
		// tk->kyoku[tk->kyoku_index].act_hai[tk->kyoku[tk->kyoku_index].act_count-1], // 鳴き牌定義
		// tk->kyoku[tk->kyoku_index].act_hai[tk->kyoku[tk->kyoku_index].act_count-1], // 鳴きINDEX牌定義
		tmp_naki_hai,                             // 鳴き牌定義
		tmp_naki_hai,                             // 鳴きINDEX牌定義
		tmp_aka_count);

	// ----------------------------------------
	// 卓ステータス設定
	// ----------------------------------------
	tk->stat = PLYACTPON;

}

/* ---------------------------------------------------------------------------------------------- */
// 09:set_type_chi
/* ---------------------------------------------------------------------------------------------- */
void MJSReadMjai::set_type_chi(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num){

	int tmp_naki_seki;
	int tmp_react_seki;

	int  tmp_naki_hai = 0;
	bool tmp_naki_aka = false ;
	int  tmp_aka_count = 0;

	int tmp_naki_tehai_hai1 = 0;
	int tmp_naki_tehai_hai2 = 0;
	int tmp_hai = 0;
	int tmp_chi_idx = 0;

	// ----------------------------------------
	// REACTプレーヤー(targetプレーヤー)の特定
	// ----------------------------------------

	// プレーヤーID確認
	tmp_naki_seki  = atoi(gui->wk_str[tmp_wk_num+3]);
	tmp_react_seki = atoi(gui->wk_str[tmp_wk_num+5]);

	// ----------------------------------------
	// チー牌確認(捨牌)
	// ----------------------------------------
		tmp_naki_hai = Get_hainum(gui->wk_str[tmp_wk_num+7]);
		if (tmp_naki_hai > 100){
			tmp_naki_hai = tmp_naki_hai - 100;
			tmp_naki_aka = true ;
			tmp_aka_count++;
		}

	// ----------------------------------------
	// チー構成牌(1枚目)
	// ----------------------------------------
		tmp_naki_tehai_hai1 = Get_hainum(gui->wk_str[tmp_wk_num+9]);
		if (tmp_naki_tehai_hai1 > 100){
			tmp_naki_tehai_hai1 = tmp_naki_tehai_hai1 - 100;
			tmp_aka_count++;
		}

	// ----------------------------------------
	// チー構成牌(2枚目)
	// ----------------------------------------
		tmp_naki_tehai_hai2 = Get_hainum(gui->wk_str[tmp_wk_num+10]);
		if (tmp_naki_tehai_hai2 > 100){
			tmp_naki_tehai_hai2 = tmp_naki_tehai_hai2 - 100;
			tmp_aka_count++;
		}

	// ----------------------------------------
	// チーINDEX牌算出
	// ----------------------------------------

		// 1枚目2枚目の大小比較・交換
		if(tmp_naki_tehai_hai1 > tmp_naki_tehai_hai2){
			tmp_hai = tmp_naki_tehai_hai1;
			tmp_naki_tehai_hai1 = tmp_naki_tehai_hai2;
			tmp_naki_tehai_hai2 = tmp_hai;
		}

		// チーINDEX牌を算出
		if (tmp_naki_tehai_hai1 == tmp_naki_hai - 2 ){
			tmp_chi_idx = tmp_naki_tehai_hai1;
		}else if (tmp_naki_tehai_hai1 == tmp_naki_hai - 1 ){
			tmp_chi_idx = tmp_naki_tehai_hai1;
		}else if (tmp_naki_tehai_hai1 == tmp_naki_hai + 1 ){
			tmp_chi_idx = tmp_naki_hai;
		}else {
			tmp_chi_idx = 0;
		}

	// ----------------------------------------
	// アクション設定 - チー
	// ----------------------------------------
	tk->SetActInfo(tk->kyoku_index,
		PLYACTCHI,
		tmp_naki_seki,
		tmp_react_seki,
		tmp_naki_hai,
		tmp_naki_aka
	);

	// ----------------------------------------
	// 晒し情報設定 - チー
	// ----------------------------------------
	tk->SetNakiInfo(tk->kyoku_index, 
		MINSHUN, 
		tmp_naki_seki,                            // 鳴きプレーヤー
		tk->kyoku[tk->kyoku_index].act_count,     // ACTID
		tmp_naki_hai,                             // 鳴き牌
		tmp_chi_idx,                              // 鳴き牌INDEX
		tmp_aka_count                             // 赤牌枚数 
	);

	// ----------------------------------------
	// 卓ステータス設定
	// ----------------------------------------
	tk->stat = PLYACTCHI;

}

/* ---------------------------------------------------------------------------------------------- */
// 10:set_type_minkan
/* ---------------------------------------------------------------------------------------------- */
void MJSReadMjai::set_type_minkan(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num){

	int tmp_naki_seki;
	int tmp_react_seki;

	int  tmp_naki_hai = 0;
	bool tmp_naki_aka = false ;
	int  tmp_aka_count = 0;

	// ----------------------------------------
	// REACTプレーヤー(targetプレーヤー)の特定
	// ----------------------------------------

	// プレーヤーID確認
	tmp_naki_seki  = atoi(gui->wk_str[tmp_wk_num+3]);
	tmp_react_seki = atoi(gui->wk_str[tmp_wk_num+5]);

	// ----------------------------------------
	// ミンカン牌確認(捨牌)
	// ----------------------------------------

	// 手牌読込
	tmp_naki_hai = Get_hainum(gui->wk_str[tmp_wk_num+7]);

	// 赤牌確認
	if (tmp_naki_hai > 100){
		tmp_naki_hai = tmp_naki_hai - 100;
		tmp_naki_aka = true;
		// 赤牌加算
		tmp_aka_count++;
	}else{
		tmp_naki_aka = false;
	}

	// ----------------------------------------
	// ミンカン牌確認(1枚目)
	// ----------------------------------------

	// ----------------------------------------
	// ミンカン牌確認(2枚目)
	// ----------------------------------------

	// ----------------------------------------
	// ミンカン牌確認(3枚目)
	// ----------------------------------------


	// ----------------------------------------
	// アクション設定 - ミンカン
	// ----------------------------------------
	tk->SetActInfo(tk->kyoku_index,
		PLYACTMINKAN,
		tmp_naki_seki,
		tmp_react_seki,
		tmp_naki_hai,
		tmp_naki_aka
	);

	// ----------------------------------------
	// 晒し情報設定 - ミンカン
	// ----------------------------------------
	tk->SetNakiInfo(tk->kyoku_index, 
		MINKAN, 
		tmp_naki_seki,                                                              // 鳴きプレーヤー
		tk->kyoku[tk->kyoku_index].act_count,                                       // ACTID
		tk->kyoku[tk->kyoku_index].act_hai[tk->kyoku[tk->kyoku_index].act_count-1], // 鳴き牌定義
		tk->kyoku[tk->kyoku_index].act_hai[tk->kyoku[tk->kyoku_index].act_count-1], // 鳴きINDEX牌定義
		tmp_aka_count);

	// ----------------------------------------
	// 卓ステータス設定
	// ----------------------------------------
	tk->stat = PLYACTMINKAN;


}

/* ---------------------------------------------------------------------------------------------- */
// 95:type_dora
/* ---------------------------------------------------------------------------------------------- */
void MJSReadMjai::set_type_dora_open(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num){

	int tmp_dora_hai;
	int tmp_dora_aka;

	// ----------------------------------------
	// ドラ定義
	// ----------------------------------------

	// ドラ表示牌
	tmp_dora_hai = Get_hainum(gui->wk_str[tmp_wk_num+3]);

	// 赤牌確認
	if (tmp_dora_hai > 100){
		tmp_dora_hai = tmp_dora_hai - 100;
		tmp_dora_aka = true;
	}else{
		tmp_dora_aka = false;
	}

/*
	// ----------------------------------------
	// アクション設定 - 自摸時ドラ表示
	// ----------------------------------------
	tk->SetActInfo(tk->kyoku_index,
		TSUMOKANDORAOPEN,
		4,
		4,
		tmp_dora_hai,
		tmp_dora_aka
	);
*/

	// ドラ表示牌定義
	tk->kyoku[tk->kyoku_index].dora_actid[tk->kyoku[tk->kyoku_index].doracount] = tk->kyoku[tk->kyoku_index].act_count;
	tk->kyoku[tk->kyoku_index].dora[tk->kyoku[tk->kyoku_index].doracount]       = tmp_dora_hai;
	tk->kyoku[tk->kyoku_index].dora_aka[tk->kyoku[tk->kyoku_index].doracount]   = tmp_dora_aka;
	tk->kyoku[tk->kyoku_index].doracount++;

}

/* ---------------------------------------------------------------------------------------------- */
// 96:type_hora
/* ---------------------------------------------------------------------------------------------- */
void MJSReadMjai::set_type_hora(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num){

	// 初期化
	int tmp_agari_ply_id;
	int tmp_target_ply_id;
	int tmp_hai;
	int tmp_hai_aka;
	int tmp_tsumo_agari_flg;
	int tmp_dora_hai;
	int tmp_dora_aka;

	// ----------------------------------------
	// 裏ドラ設定
	// ----------------------------------------
	// 裏ドラが「+」でないなら、ドラ情報取得
	if( strcmp(gui->wk_str[tmp_wk_num+12], "+"  ) != 0 ){
		// ドラ枚数だけ取得
		for(int tmp_i = 0; tmp_i < tk->kyoku[tk->kyoku_index].doracount; tmp_i++){
			// 裏ドラ読込
			tmp_dora_hai = Get_hainum(gui->wk_str[tmp_wk_num+12+tmp_i]);
			// 赤牌確認
			if (tmp_dora_hai > 100){
				tmp_dora_hai = tmp_dora_hai - 100;
				tmp_dora_aka = true;
			}else{
				tmp_dora_aka = false;
			}
			// 裏ドラ設定
			tk->kyoku[tk->kyoku_index].uradora[tmp_i]       = tmp_dora_hai;
			tk->kyoku[tk->kyoku_index].uradora_aka[tmp_i]   = tmp_dora_aka;
			tk->kyoku[tk->kyoku_index].uradora_actid[tmp_i] = 0;
		}
	}

	// ----------------------------------------
	// 和了情報取得
	// ----------------------------------------
	// プレーヤーID確認
	tmp_agari_ply_id  = atoi(gui->wk_str[tmp_wk_num+3]);
	tmp_target_ply_id = atoi(gui->wk_str[tmp_wk_num+5]);

	// アクション牌設定
	tmp_hai     = tk->kyoku[tk->kyoku_index].act_hai[tk->kyoku[tk->kyoku_index].act_count];
	tmp_hai_aka = tk->kyoku[tk->kyoku_index].act_aka[tk->kyoku[tk->kyoku_index].act_count];

	// ----------------------------------------
	// 和了情報設定
	// ----------------------------------------

	// 和了フラグ
	tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].ryukyoku_flg  = false;

	// 卓ステータス設定(和了プレーヤーとターゲットが同じならば自摸和了の設定)
	if ( tmp_agari_ply_id == tmp_target_ply_id ){
		// 自摸和了設定
		tmp_target_ply_id = 4;
		tk->stat = PLYTSUMOAGARI;
		tmp_tsumo_agari_flg = true;
	}else{
		// ロン和了設定
		tk->stat = PLYACTRON;
		tmp_tsumo_agari_flg = false;
	}

	// 和了プレーヤ設定
	tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_num    = tmp_agari_ply_id;
	tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].furikomi_ply_num = tmp_target_ply_id;
	tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_hai        = tmp_hai;
	tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_aka        = tmp_hai_aka;

	// ----------------------------------------
	// アクション設定 - 和了宣言
	// ----------------------------------------
	tk->SetActInfo(tk->kyoku_index, // 局INDEX
		tk->stat,                   // アクション情報 / 和了宣言
		tmp_agari_ply_id,           // アクションプレーヤ
		tmp_target_ply_id,          // リアクションプレーヤ
		tmp_hai,                    // 牌番号
		tmp_hai_aka                 // 赤牌
	);

	// -----------------------------------------------------------
	// tkクラスのアクション情報の最新化
	// -----------------------------------------------------------
	tk->Check_Ply_ActTehai(tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count);

	// -----------------------------------------------------------
	// 和了情報設定
	// -----------------------------------------------------------

	// 和了形式確認
	if( tk->shanten_normal[tmp_agari_ply_id] == -1 ){

		// 通常形式の和了
		tk->SetAgariInfo(tk->kyoku_index,
			AGARI_NORMAL,
			tmp_agari_ply_id,
			tmp_target_ply_id,
			tmp_tsumo_agari_flg,
			tk->kyoku[tk->kyoku_index].act_hai[tk->kyoku[tk->kyoku_index].act_count],
			tk->kyoku[tk->kyoku_index].act_aka[tk->kyoku[tk->kyoku_index].act_count]
		);

	}else if( tk->shanten_chitoi[tmp_agari_ply_id] == -1){

		// 七対子形式の和了
		tk->SetAgariInfo(tk->kyoku_index,
			AGARI_CHITOI,
			tmp_agari_ply_id,
			tmp_target_ply_id,
			tmp_tsumo_agari_flg,
			tk->kyoku[tk->kyoku_index].act_hai[tk->kyoku[tk->kyoku_index].act_count],
			tk->kyoku[tk->kyoku_index].act_aka[tk->kyoku[tk->kyoku_index].act_count]
		);

	}else if( tk->shanten_kokushi[tmp_agari_ply_id] == -1){

		// 国士形式の和了
		tk->SetAgariInfo(tk->kyoku_index,
			AGARI_KOKUSHI,
			tmp_agari_ply_id,
			tmp_target_ply_id,
			tmp_tsumo_agari_flg,
			tk->kyoku[tk->kyoku_index].act_hai[tk->kyoku[tk->kyoku_index].act_count],
			tk->kyoku[tk->kyoku_index].act_aka[tk->kyoku[tk->kyoku_index].act_count]
		);

	}

	// ----------------------------------------
	// 局得点の設定
	// ----------------------------------------
	for(int ply_i = 0; ply_i < 4; ply_i++){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].kyoku_score[ply_i] = atoi(gui->wk_str[tmp_wk_num+7+ply_i]);
		tk->kyoku[tk->kyoku_index].ply_kyoku_end_score[ply_i] = tk->kyoku[tk->kyoku_index].ply_kyoku_start_score[ply_i] + 
		                                                        tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].kyoku_score[ply_i];
	}

}

/* ---------------------------------------------------------------------------------------------- */
// 97:type_ryukyoku
/* ---------------------------------------------------------------------------------------------- */
void MJSReadMjai::set_type_ryukyoku(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num){

	// ----------------------------------------
	// アクション設定 - 荒局
	// ----------------------------------------
	tk->SetActInfo(tk->kyoku_index,
		RYUKYOKU,
		4,
		4,
		0,
		false
	);

	// -----------------------------------------------------------
	// tkクラスのアクション情報の最新化
	// -----------------------------------------------------------
	tk->Check_Ply_ActTehai(tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count);

	// -----------------------------------------------------------
	// 局終了設定(荒牌)
	// -----------------------------------------------------------
	tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].ryukyoku_flg  = true;
	tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].ryukyoku_stat = HOWANPAI;
	tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakuman_count = 0;
	tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakucount     = 0;

	// 局得点の設定
	for(int ply_i = 0; ply_i < 4; ply_i++){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].kyoku_score[ply_i] = atoi(gui->wk_str[tmp_wk_num+3+ply_i]);
		tk->kyoku[tk->kyoku_index].ply_kyoku_end_score[ply_i] = tk->kyoku[tk->kyoku_index].ply_kyoku_start_score[ply_i] + 
		                                                        tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].kyoku_score[ply_i];
	}

}

/* ---------------------------------------------------------------------------------------------- */
// 98:type_endkyoku
/* ---------------------------------------------------------------------------------------------- */
void MJSReadMjai::set_type_endkyoku(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num){

	// ----------------------------------------
	// アクション設定 - 局結果(流局)
	// ----------------------------------------
	if( tk->kyoku[tk->kyoku_index].act_stat[tk->kyoku[tk->kyoku_index].act_count] == RYUKYOKU){

		// アクション指定(局結果 - 流局)
		tk->SetActInfo(tk->kyoku_index,
			KYOKURESULT,
			4,
			4,
			0,
			false
		);

	// ----------------------------------------
	// アクション設定 - 局結果(ダブロンを含む和了画面)
	// ----------------------------------------
	}else{

		// アクション指定(局結果 - ダブロンを含む和了画面)
		for(int tmp_disp_num = 0; tmp_disp_num < tk->kyoku[tk->kyoku_index].agari_ply_count; tmp_disp_num++){
			tk->SetActInfo(tk->kyoku_index,
				KYOKURESULT,
				tk->kyoku[tk->kyoku_index].ply_agari_yk[tmp_disp_num].agari_ply_num,  // 結果表示する和了プレーヤを設定する
				4,
				0,
				false
			);
		}
	}

	// アクション番号の加算(最終値)
	tk->kyoku[tk->kyoku_index].act_count++;

	// 局IDを加算
	tk->kyoku_index++;

}

/* ---------------------------------------------------------------------------------------------- */
// 99:type_endgame
/* ---------------------------------------------------------------------------------------------- */
void MJSReadMjai::set_type_endgame(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num){

	// 最終得点
	for(int ply_i = 0; ply_i < PLAYER_MAX; ply_i++){
		tk->plyEndscore[ply_i] = tk->kyoku[tk->kyoku_index-1].ply_kyoku_end_score[ply_i];
	}

}

/* ---------------------------------------------------------------------------------------------- */
// 牌番号取得
/* ---------------------------------------------------------------------------------------------- */
int MJSReadMjai::Get_hainum(char hai_str[]){

	char tmp_str[8];
	int  hainum;

	// ----------------------------------------
	// 1文字目
	// ----------------------------------------

	tmp_str[0] = hai_str[0];
	tmp_str[1] = '\0';

	// 文字抽出(半角_前半分)
	if(      strcmp( tmp_str, "1" ) == 0){
		hainum = 1;
	}else if(strcmp( tmp_str, "2" ) == 0){
		hainum = 2;
	}else if(strcmp( tmp_str, "3" ) == 0){
		hainum = 3;
	}else if(strcmp( tmp_str, "4" ) == 0){
		hainum = 4;
	}else if(strcmp( tmp_str, "5" ) == 0){
		hainum = 5;
	}else if(strcmp( tmp_str, "6" ) == 0){
		hainum = 6;
	}else if(strcmp( tmp_str, "7" ) == 0){
		hainum = 7;
	}else if(strcmp( tmp_str, "8" ) == 0){
		hainum = 8;
	}else if(strcmp( tmp_str, "9" ) == 0){
		hainum = 9;
	}else if(strcmp( tmp_str, "E" ) == 0){
		hainum = 31;
	}else if(strcmp( tmp_str, "S" ) == 0){
		hainum = 32;
	}else if(strcmp( tmp_str, "W" ) == 0){
		hainum = 33;
	}else if(strcmp( tmp_str, "N" ) == 0){
		hainum = 34;
	}else if(strcmp( tmp_str, "P" ) == 0){
		hainum = 35;
	}else if(strcmp( tmp_str, "F" ) == 0){
		hainum = 36;
	}else if(strcmp( tmp_str, "C" ) == 0){
		hainum = 37;
	}else if(strcmp( tmp_str, "?" ) == 0){
		hainum = 0;
	}else{
		hainum = 0;
	}

	// ----------------------------------------
	// 2文字目
	// ----------------------------------------

	if( hai_str[1] != '\0'){	

		tmp_str[0] = hai_str[1];
		tmp_str[1] = '\0';

		if(      strcmp( tmp_str, "m" ) == 0){

		}else if(strcmp( tmp_str, "p" ) == 0){
			hainum = hainum + 10;
		}else if(strcmp( tmp_str, "s" ) == 0){
			hainum = hainum + 20;
		}else{

		}

	}

	// ----------------------------------------
	// 3文字目
	// ----------------------------------------

	if(( hai_str[1] != '\0' ) && ( hai_str[2] != '\0' )){

		tmp_str[0] = hai_str[2];
		tmp_str[1] = '\0';

		if( strcmp( tmp_str, "r" ) == 0){
			hainum = hainum + 100;
		}else{

		}

	}

	// ----------------------------------------
	// 返り値
	// ----------------------------------------
	return hainum;

}

/* ---------------------------------------------------------------------------------------------- 
 * ソース終了
 * ---------------------------------------------------------------------------------------------- */
