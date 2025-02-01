/* ---------------------------------------------------------------------------------------------- 
 * 
 * プログラム概要 ： Newさくら麻雀(MJAIクライアント実装版)
 * バージョン     ： 0.1.2.1.232(関数名mentsu,taatsuの名称共通化)
 * プログラム名   ： mjs.exe
 * ファイル名     ： client.cpp
 * クラス名       ： MJSMjaiClient
 * 処理概要       ： Mjaiクライアント処理クラス
 * Ver0.1.2作成日 ： 2023/11/19 21:38:17
 * 最終更新日     ： 2025/01/04 11:21:26
 * 
 * Copyright (c) 2010-2025 TechMileStoraJP, All rights reserved.
 * 
 * ---------------------------------------------------------------------------------------------- */

#include "client.h"

/* ---------------------------------------------------------------------------------------------- */
// 前処理
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::ClientInit(MJSTkinfo *tk, MJSGui *gui, MJSReadMjai *tmp_mjai){

	// ----------------------------------------
	// クラス定義
	// ----------------------------------------
	mjai = new MJSReadMjai;             // MJAI関連メッセージ処理クラス
	clientlog = new MJSCorelog;         // クライアントクラス向けのデバグログ

	// ----------------------------------------
	// メッセージ処理クラスの初期化
	// ----------------------------------------
	if( gui->clientlog_output_flg == true){

		// ログファイル名設定
		// wsprintf(clientlog_name, "mjai_client.log" );
		// clientlog->CorelogInit(clientlog_name);
		clientlog->CorelogInit(gui->clientlog_name);

	}

	// ----------------------------------------
	// デバグログヘッダー出力
	// ----------------------------------------
	if( gui->clientlog_output_flg == true){

		// ログファイル名設定
		wsprintf(clientlog_buf, "ヘッダー\n----\n" );

		// ログ出力
		clientlog->CorelogPrint(clientlog_buf);

	}

	// 時刻設定
	SetNowTime(tk);

}

/* ---------------------------------------------------------------------------------------------- */
// 終了処理
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::ClientPost(MJSGui *gui){

	// ----------------------------------------
	// クラスの終了
	// ----------------------------------------

	// ログ後処理
	if( gui->clientlog_output_flg == true){
		clientlog->CorelogPost();
	}

	// ----------------------------------------
	// クラス削除
	// ----------------------------------------
	delete mjai;                        // MJAIクラス
	delete clientlog;                   // クライアントデバグログ

}

/* ---------------------------------------------------------------------------------------------- */
// メッセージ送信処理
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::ClientSendMes(MJSGui *gui){

	// メッセージ送信
	sock.SendMes(gui);

	// ログ出力
	if( gui->clientlog_output_flg == true){
		wsprintf(clientlog_buf, "SND:");
		clientlog->CorelogPrint(clientlog_buf);
		clientlog->CorelogPrint(gui->snd_mes);
		wsprintf(clientlog_buf, "----\n");
		clientlog->CorelogPrint(clientlog_buf);
	}

	// 送信バッファのクリア
	memset(gui->snd_mes, 0, sizeof(gui->snd_mes));

}

/* ---------------------------------------------------------------------------------------------- */
// 現在時刻の取得
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::SetNowTime(MJSTkinfo *tk){

	// システム関数定義 
    time_t jikan = time(NULL);
    struct tm imanojikan;
	errno_t error;

	// 時間変数の定義
	int year, mon, day;
	int hour, min, sec;

	// 現在の日時を取得 
	error = localtime_s(&imanojikan, &jikan);

	// 時間変数の代入
	year = imanojikan.tm_year + 1900;
	mon  = imanojikan.tm_mon  + 1;
	day  = imanojikan.tm_mday ;

	hour = imanojikan.tm_hour;
	min  = imanojikan.tm_min;
	sec  = imanojikan.tm_sec;

	wsprintf(tk->startdate, "%04d/%02d/%02d", year, mon, day);     // 卓開始日
	wsprintf(tk->starttime, "%02d:%02d:%02d", hour, min, sec);     // 卓開始時刻

}

/* ---------------------------------------------------------------------------------------------- */
// メイン処理
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::CheckTakuStatus(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui, bool tmp_push_flg){

	// HUM手牌確認フラグ
	tk->com_no_chk_tehai_flg = true;

	// 最大赤牌数
	tk->aka_max[0] = 1;
	tk->aka_max[1] = 1;
	tk->aka_max[2] = 1;

	//-----------------------------------------------------------
	// 接続前状態
	//-----------------------------------------------------------
	if( gui->cli_mode == GUI_MJAI_NOTCONNECT){

		// メッセージ表示
		wsprintf(gui->stat_mes, "接続してユーザデータを送信しますか？");

		// モード変更
		gui->cli_mode = GUI_MJAI_CONNECT_ACTION;

	//-----------------------------------------------------------
	// 接続処理
	//-----------------------------------------------------------
	}else if( gui->cli_mode == GUI_MJAI_CONNECT_ACTION){

		// クリックされていれば
		if( tmp_push_flg == true){

			// 接続処理
			if ( sock.SocketConect() == 0 ){

				// メッセージ表示
				wsprintf(gui->stat_mes, "接続に成功しました");

				// sendメッセージ設定
				wsprintf(gui->snd_mes, res_join);

				// メッセージ送信(joinメッセージ)
				ClientSendMes(gui);

				// モード変更
				gui->cli_mode = GUI_MJAI_WAIT_HELO_RESMES;

			}else{

				// 受信メッセージの設定
				wsprintf(gui->stat_mes, "接続エラー");

				// モード変更
				gui->cli_mode = GUI_MJAI_ERR_CONNECT;

			}
		}

	//-----------------------------------------------------------
	// 接続エラー時
	//-----------------------------------------------------------
	}else if( gui->cli_mode == GUI_MJAI_ERR_CONNECT){

		// クリックされていれば
		if( tmp_push_flg == true){

			// モード変更：クライアントモード終了
			gui->cli_mode = GUI_MJAI_DISCONNECT;

		}

	//-----------------------------------------------------------
	// HELLOメッセージ受信待ち
	//-----------------------------------------------------------
	}else if( gui->cli_mode == GUI_MJAI_WAIT_HELO_RESMES){

		// メッセージ受信
		sock.ResponseMes(gui);

		// データ受信があれば
		if (sock.data_size > 0){

			// メッセージ表示
			wsprintf(gui->stat_mes, "HELLOメッセージを受信しました");

			// ログ出力(HELLOメッセージ)
			if( gui->clientlog_output_flg == true){
				clientlog->CorelogPrint(gui->res_mes);
				clientlog->CorelogPrint(clientlog_buf);
				// ログ出力(区切り線)
				wsprintf(clientlog_buf, "----\n");
				clientlog->CorelogPrint(clientlog_buf);
			}

			// モード変更
			gui->cli_mode = GUI_MJAI_WAIT_TAKU_START_RESMES;

		}else{

			// メッセージ表示
			wsprintf(gui->stat_mes, "HELLOメッセージの受信待ちです");

		}

	//-----------------------------------------------------------
	// taku_startメッセージ受信待ち
	//-----------------------------------------------------------
	}else if( gui->cli_mode == GUI_MJAI_WAIT_TAKU_START_RESMES){

		// メッセージ受信
		sock.ResponseMes(gui);

		// データ受信があれば
		if (sock.data_size > 0){

			// メッセージ表示
			wsprintf(gui->stat_mes, "ゲーム開始メッセージを受信しました");

			// ログ出力(gui->res_mes出力)
			if( gui->clientlog_output_flg == true){
				clientlog->CorelogPrint(gui->res_mes);
				wsprintf(clientlog_buf, "----\n");
				clientlog->CorelogPrint(clientlog_buf);
			}

			// ライン解析
			wsprintf(mjai->line_buf, gui->res_mes);    // ラインバッファへのコピー
			mjai->Read_logline(gui);                   // ライン解析

			// メッセージ確認(メイン処理)
			ChkResMesMain(tk, ply, gui);

			// モード変更
			gui->cli_mode = GUI_MJAI_BAGIME;

		}else{

			// メッセージ表示
			wsprintf(gui->stat_mes, "ゲーム開始メッセージの受信待ちです");

		}

	//-----------------------------------------------------------
	// 場決め表示
	//-----------------------------------------------------------
	}else if( gui->cli_mode == GUI_MJAI_BAGIME){

		// クリックされていれば
		if( tmp_push_flg == true){

			// 受信バッファのクリア
			sock.data_size = 0;
			memset(gui->res_mes, 0, sizeof(gui->res_mes));

			// Noneリクエストの送信処理
			ActSndNoneMes(gui);

			// メッセージ送信
			ClientSendMes(gui);

			// モード変更
			gui->cli_mode = GUI_MJAI_WAIT_KYOKU_START_RESMES;

		}

	//-----------------------------------------------------------
	// 局開始メッセージ待ち
	//-----------------------------------------------------------
	}else if( gui->cli_mode == GUI_MJAI_WAIT_KYOKU_START_RESMES){

		// メッセージ表示
		wsprintf(gui->stat_mes, "局情報のメッセージの受信待ちです");

		// メッセージ受信
		sock.ResponseMes(gui);

		// データ受信があれば
		if (sock.data_size > 0){

			// ログ出力
			if( gui->clientlog_output_flg == true){
				clientlog->CorelogPrint(gui->res_mes);
				wsprintf(clientlog_buf, "----\n");
				clientlog->CorelogPrint(clientlog_buf);
			}

			// ライン解析
			wsprintf(mjai->line_buf, gui->res_mes);  // ライン設定
			mjai->Read_logline(gui);                  // ライン解析

			// メッセージ確認(メイン処理)
			ChkResMesMain(tk, ply, gui);

			// モード変更
			gui->cli_mode = GUI_MJAI_HAIPAI;

		}

	//-----------------------------------------------------------
	// 配牌状態
	//-----------------------------------------------------------
	}else if( gui->cli_mode == GUI_MJAI_HAIPAI){

		// クリックされていれば
		if( tmp_push_flg == true){

			// バッファクリア
			sock.data_size = 0;
			memset(gui->res_mes, 0, sizeof(gui->res_mes));

			// Noneリクエストの送信処理
			ActSndNoneMes(gui);

			// メッセージ送信
			ClientSendMes(gui);

			// モード変更
			gui->cli_mode = GUI_MJAI_WAIT_TAKU_RESMES;

		}

	//-----------------------------------------------------------
	// 卓メインの受信メッセージ待ち
	//-----------------------------------------------------------
	}else if( gui->cli_mode == GUI_MJAI_WAIT_TAKU_RESMES){

		// バッファクリア
		sock.data_size = 0;
		memset(gui->res_mes, 0, sizeof(gui->res_mes));

		// メッセージ受信
		sock.ResponseMes(gui);

		// データ受信があれば
		if (sock.data_size > 0){

			// ログ出力
			if( gui->clientlog_output_flg == true){
				wsprintf(clientlog_buf, "RES:");
				clientlog->CorelogPrint(clientlog_buf);
				clientlog->CorelogPrint(gui->res_mes);
				wsprintf(clientlog_buf, "----\n");
				clientlog->CorelogPrint(clientlog_buf);
			}

			// ライン解析
			wsprintf(mjai->line_buf, gui->res_mes);  // ラインの値設定
			mjai->Read_logline(gui);                  // ライン解析(wk配列に値を代入)

			// ログ出力(wk構造体)
			if( gui->clientlog_output_flg == true){
				for(int tmp_i = 0; tmp_i < gui->wk_str_count; tmp_i++){
					wsprintf(clientlog_buf, "%d:%s\n", tmp_i, gui->wk_str[tmp_i]);
					clientlog->CorelogPrint(clientlog_buf);
				}
				wsprintf(clientlog_buf, "----\n");
				clientlog->CorelogPrint(clientlog_buf);
			}

			// メッセージ確認(メイン処理)
			ChkResMesMain(tk, ply, gui);

			// モード変更
			gui->cli_mode = GUI_MJAI_WAIT_TAKU_PLYACT;

		}

	//-----------------------------------------------------------
	// 卓メイン：自分プレーヤーのアクション決定待ち
	//-----------------------------------------------------------
	}else if( gui->cli_mode == GUI_MJAI_WAIT_TAKU_PLYACT){

		// クリックされていれば
		if( tmp_push_flg == true){

			// ----------------------------------------
			// 卓ステータスごとに処理(自摸の場合)
			// ----------------------------------------
			if( tk->stat == PLYACTTSUMO ){

				// 自摸時のメッセージ送信
				SetActTsumo(tk, ply, gui);

				// SND待ちカウントを初期化
				gui->send_wait_frame_count = 0;

				// モード変更
				gui->cli_mode = GUI_MJAI_WAIT_SED_MES;

			// ----------------------------------------
			// 卓ステータスごとに処理(リーチの場合)
			// ----------------------------------------
			}else if(tk->stat == PLYACTRIICH){

				// リーチ時のメッセージ送信
				SetActRiichi(tk, ply, gui);

				// SND待ちカウントを初期化
				gui->send_wait_frame_count = 0;

				// モード変更
				gui->cli_mode = GUI_MJAI_WAIT_SED_MES;

			// ----------------------------------------
			// 卓ステータスごとに処理(捨牌の場合→捨牌後の鳴き確認)
			// ---------------------------------------
			}else if( tk->stat == PLYACTSUTE       || 
			          tk->stat == PLYACTTSUMOGIRI  ||
			          tk->stat == PLYACTNAKISUTE   ){

				// 鳴き処理
				SetActNaki(tk, ply, gui);

				// SND待ちカウントを初期化
				gui->send_wait_frame_count = 0;

				// モード変更
				gui->cli_mode = GUI_MJAI_WAIT_SED_MES;

			// ----------------------------------------
			// 卓ステータスごとに処理(ポンチーの場合→捨牌後の鳴き確認)
			// ----------------------------------------
			}else if( tk->stat == PLYACTPON  || 
			          tk->stat == PLYACTCHI  ){ 

				// 鳴き捨牌時のメッセージ送信
				SetActNakiSute(tk, ply, gui);

				// SND待ちカウントを初期化
				gui->send_wait_frame_count = 0;

				// モード変更
				gui->cli_mode = GUI_MJAI_WAIT_SED_MES;

			// ----------------------------------------
			// 卓ステータスごとに処理(カンの場合→何もしない)
			// ----------------------------------------
			}else if( tk->stat == PLYACTANKAN  ||
			          tk->stat == PLYACTKAKAN  || 
			          tk->stat == PLYACTMINKAN ){ 

				// カン時のメッセージ送信
				SetActkan(tk, ply, gui);

				// SND待ちカウントを初期化
				gui->send_wait_frame_count = 0;

				// モード変更
				gui->cli_mode = GUI_MJAI_WAIT_SED_MES;

			// ----------------------------------------
			// 局終了
			// ----------------------------------------
			}else if(tk->stat == KYOKURESULT){

				// モード変更
				gui->cli_mode = GUI_MJAI_KYOKUEND;

			// ----------------------------------------
			// エラー状態
			// ----------------------------------------
			}else if(tk->stat == TAKUERR){

				// モード変更
				gui->cli_mode = GUI_MJAI_ERR_RES_MES;

			// ----------------------------------------
			// それ以外の場合
			// ----------------------------------------
			}else{

				// Noneリクエストの送信処理
				ActSndNoneMes(gui);

				// SND待ちカウントを初期化
				gui->send_wait_frame_count = 0;

				// モード変更
				gui->cli_mode = GUI_MJAI_WAIT_SED_MES;

			}

		}

	//-----------------------------------------------------------
	// 卓メイン：局終了モード
	//-----------------------------------------------------------
	}else if( gui->cli_mode == GUI_MJAI_KYOKUEND){

		// クリックされていれば
		if( tmp_push_flg == true){

			// Noneリクエストの送信処理
			ActSndNoneMes(gui);

			// モード変更
			gui->cli_mode = GUI_MJAI_WAIT_SED_MES;

		}

	//-----------------------------------------------------------
	// 卓メイン：メッセージ送信のウエイト処理
	//-----------------------------------------------------------
	}else if( gui->cli_mode == GUI_MJAI_WAIT_SED_MES){

		// カウント値を超過するまでウェイト
		if( gui->send_wait_frame_count > AUTO_FRAME_COUNT_CLIENT_SND){

			// メッセージ送信
			ClientSendMes(gui);

			// ウェイト処理を終了して、モード変更
			if(tk->stat == TAKURESULT){
				// 卓終了モード
				gui->cli_mode = GUI_MJAI_TAKURESULT;
			}else{
				// メッセージ受信
				gui->cli_mode = GUI_MJAI_WAIT_TAKU_RESMES;
			}

		}else{
			// SND待ちカウントを+1
			gui->send_wait_frame_count++;
		}

	//-----------------------------------------------------------
	// 卓メイン：卓終了モード
	//-----------------------------------------------------------
	}else if( gui->cli_mode == GUI_MJAI_TAKURESULT){

		// クリックされていれば
		if( tmp_push_flg == true){

			// モード変更：クライアントモード終了
			gui->cli_mode = GUI_MJAI_DISCONNECT;

		}

	//-----------------------------------------------------------
	// 卓メイン：エラー処理
	//-----------------------------------------------------------
	}else if( gui->cli_mode == GUI_MJAI_ERR_RES_MES){

		// クリックされていれば
		if( tmp_push_flg == true){

			// モード変更：クライアントモード終了
			gui->cli_mode = GUI_MJAI_DISCONNECT;

		}

	//-----------------------------------------------------------
	// 切断処理→クライアントモード終了
	//-----------------------------------------------------------
	}else if( gui->cli_mode == GUI_MJAI_DISCONNECT){

		// クリックされていれば
	//	if( tmp_push_flg == true){

			// 切断
			sock.SocketDisconect();

			// モード変更
			gui->cli_mode = GUI_MJAI_END_MODE;

	//	}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 自摸時のアクション設定
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::SetActTsumo(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui){

	// 変数
	int tmp_aka_count = 0;

	// プレーヤが自分なら
	if( tk->ply_turn == HUM_PLY_SEKI_NUM ){

		// ----------------------------------------
		// plyクラス捨牌設定
		// ----------------------------------------

		// クライアントゲームモードがPLYモードであるか
		if ( tk->ply_hum_mode == 0 ){

			// アクション定義
			tk->ply_act = ply[HUM_PLY_SEKI_NUM].ply_act;

		}

		// -----------------------------------------------------------
		// プレーヤーのアクション定義(捨牌時)
		// -----------------------------------------------------------
		if(tk->ply_act == ACTSUTE){

			// 捨牌アクション
			SetActSute(tk, ply, gui);

		// -----------------------------------------------------------
		// プレーヤーのアクション定義(リーチ時)
		// -----------------------------------------------------------
		}else if(tk->ply_act == ACTRIICH){

			// ----------------------------------------
			// 卓ステータス設定
			// ----------------------------------------
			tk->stat = PLYACTRIICH;

			// ----------------------------------------
			// メッセージ定義(リーチ宣言)
			// ----------------------------------------
			ActSndRiichiMes(gui, tk->ply_mjai_hum_id);

			// ----------------------------------------
			// アクション設定 - リーチ宣言
			// ----------------------------------------
			tk->SetActInfo(tk->kyoku_index,
				PLYACTRIICH,
				tk->ply_turn,
				4,
				0,
				false
			);

			// ----------------------------------------
			// tkクラスのアクション情報の最新化
			// ----------------------------------------
			tk->Check_Ply_ActTehai(tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count);

			// ----------------------------------------
			// アクション設定/ログ出力
			// ----------------------------------------
			if( gui->clientlog_output_flg == true){
				Output_Actionlog(tk, tk->kyoku_index);
			}

			// ----------------------------------------
			// 手牌テーブルの更新(手牌捨ての無効化)
			// ----------------------------------------

			// 手牌のシャンテン初期化
			for( int tmp_i = 0; tmp_i < TEHAI_MAX; tmp_i++ ) {
				tk->ply_act_tehai_shanten_tbl[HUM_PLY_SEKI_NUM][tmp_i] = 9;
			}

			// 自摸牌のシャンテン初期化
			tk->ply_act_tsumo_shanten[HUM_PLY_SEKI_NUM] = 9;

		// -----------------------------------------------------------
		// 自プレーヤーのアクション(暗槓宣言)
		// -----------------------------------------------------------
		}else if(tk->ply_act == ACTANKAN){

			// -----------------------------------------------------------
			// 鳴き牌取得
			// -----------------------------------------------------------
			// クライアントゲームモードがPLYモードであるか
			if ( tk->ply_hum_mode == 0 ){

				// 暗槓牌定義
				tk->ply_naki_idx[HUM_PLY_SEKI_NUM] = ply[HUM_PLY_SEKI_NUM].ply_naki_idx;

			}

			// -----------------------------------------------------------
			// 卓ステータス設定
			// -----------------------------------------------------------
			tk->stat = PLYACTANKAN;

			// -----------------------------------------------------------
			// メッセージ定義(暗槓)
			// -----------------------------------------------------------

			// 赤枚数確認
			if (tk->ply_naki_idx[HUM_PLY_SEKI_NUM] == MAN5NUM || 
			    tk->ply_naki_idx[HUM_PLY_SEKI_NUM] == PIN5NUM || 
			    tk->ply_naki_idx[HUM_PLY_SEKI_NUM] == SOU5NUM ){

				// メッセージ定義
				ActSndAnkanMes(gui, tk->ply_mjai_hum_id,                                            // プレーヤーID
				                    tk->ply_naki_idx[HUM_PLY_SEKI_NUM],                             // 自摸牌
				                    tk->aka_max[(tk->ply_naki_idx[HUM_PLY_SEKI_NUM]-5)/10]);        // 赤牌合計枚数
			}else{

				// メッセージ定義
				ActSndAnkanMes(gui, tk->ply_mjai_hum_id,                        // プレーヤーID
				                    tk->ply_naki_idx[HUM_PLY_SEKI_NUM],         // 自摸牌
				                    0);                                         // 赤牌合計枚数
			}

			// -----------------------------------------------------------
			// アクション設定 - 暗槓
			// -----------------------------------------------------------
			tk->SetActInfo(tk->kyoku_index,
				PLYACTANKAN,
				tk->ply_turn,
				4,
				tk->ply_naki_idx[HUM_PLY_SEKI_NUM],  
				false                                // 暗槓時の赤牌有無は常にfalse
			);

			// ----------------------------------------
			// アクション設定/ログ出力
			// ----------------------------------------
			if( gui->clientlog_output_flg == true){
				Output_Actionlog(tk, tk->kyoku_index);
			}

			// ----------------------------------------
			// tkクラスのアクション情報の最新化
			// ----------------------------------------
			tk->Check_Ply_ActTehai(tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count);

			// ----------------------------------------
			// 晒し情報設定 - 暗槓
			// ----------------------------------------

			// 赤枚数確認
			if (tk->ply_naki_idx[HUM_PLY_SEKI_NUM] == MAN5NUM || 
			    tk->ply_naki_idx[HUM_PLY_SEKI_NUM] == PIN5NUM || 
			    tk->ply_naki_idx[HUM_PLY_SEKI_NUM] == SOU5NUM ){

				// 鳴牌設定
				tk->SetNakiInfo(tk->kyoku_index, 
					ANKAN, 
					tk->ply_turn,                                                                  // 自プレーヤー
					tk->kyoku[tk->kyoku_index].act_count,                                          // ACTID
					tk->ply_naki_idx[HUM_PLY_SEKI_NUM],    // 鳴き牌定義
					tk->ply_naki_idx[HUM_PLY_SEKI_NUM],    // 鳴きINDEX牌定義
					tk->aka_max[(tk->ply_naki_idx[HUM_PLY_SEKI_NUM]-5)/10]);                       // 鳴き面子の合計赤枚数

			}else{

				// 鳴牌設定(通常牌)
				tk->SetNakiInfo(tk->kyoku_index, 
					ANKAN, 
					tk->ply_turn,                                                                  // 自プレーヤー
					tk->kyoku[tk->kyoku_index].act_count,                                          // ACTID
					tk->ply_naki_idx[HUM_PLY_SEKI_NUM],    // 鳴き牌定義
					tk->ply_naki_idx[HUM_PLY_SEKI_NUM],    // 鳴きINDEX牌定義
					0);                                                                            // 鳴き面子の合計赤枚数

			}

			// ----------------------------------------
			// plyクラス捨牌後の処理
			// ----------------------------------------

			// クライアントゲームモードがPLYモードであるか
			if ( tk->ply_hum_mode == 0 ){

				// プレーヤーアクション - 暗槓
				ply[HUM_PLY_SEKI_NUM].PlyActAnkan(ply[HUM_PLY_SEKI_NUM].ply_naki_idx);

			}

		// -----------------------------------------------------------
		// プレーヤーのアクション(加槓宣言)
		// -----------------------------------------------------------
		}else if(tk->ply_act == ACTKAKAN){

			// -----------------------------------------------------------
			// 鳴き牌取得
			// -----------------------------------------------------------
			// クライアントゲームモードがPLYモードであるか
			if ( tk->ply_hum_mode == 0 ){

				// 暗槓牌定義
				tk->ply_naki_idx[HUM_PLY_SEKI_NUM]       = ply[HUM_PLY_SEKI_NUM].ply_naki_idx;
				tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = ply[HUM_PLY_SEKI_NUM].ply_naki_aka_count;

			}

			// -----------------------------------------------------------
			// 卓ステータス設定
			// -----------------------------------------------------------
			tk->stat = PLYACTKAKAN;

			// -----------------------------------------------------------
			// メッセージ定義(加槓)
			// -----------------------------------------------------------

			// 加槓する対象のポン面子の赤枚数確認
			for( int tmp_i = 0; tmp_i < tk->kyoku[tk->kyoku_index].naki_count[HUM_PLY_SEKI_NUM]; tmp_i++ ) { 

				// 牌番号の確認
				if( ( tk->kyoku[tk->kyoku_index].naki_stat[HUM_PLY_SEKI_NUM][tmp_i] == MINKO) &&   // ポンであること
				    ( tk->kyoku[tk->kyoku_index].naki_hai[HUM_PLY_SEKI_NUM][tmp_i]  == tk->ply_naki_idx[HUM_PLY_SEKI_NUM]) ){  // 牌番号が一致していること

					// 赤牌枚数の設定
					tmp_aka_count = tk->kyoku[tk->kyoku_index].naki_aka[HUM_PLY_SEKI_NUM][tmp_i];

				}

			}

			// 赤枚数確認
			if (tk->ply_naki_idx[HUM_PLY_SEKI_NUM] ==  5 || 
			    tk->ply_naki_idx[HUM_PLY_SEKI_NUM] == 15 || 
			    tk->ply_naki_idx[HUM_PLY_SEKI_NUM] == 25 ){

				// メッセージ定義
				ActSndkakanMes(gui, tk->ply_mjai_hum_id,                        // プレーヤーID
				                    tk->ply_naki_idx[HUM_PLY_SEKI_NUM],         // 加槓牌
				                    tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM],   // 加槓牌の赤牌枚数
				                    tmp_aka_count);                             // ポンの赤牌枚数
			}else{

				// メッセージ定義
				ActSndkakanMes(gui, tk->ply_mjai_hum_id,                        // プレーヤーID
				                    tk->ply_naki_idx[HUM_PLY_SEKI_NUM],         // 加槓牌
				                    tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM],   // 加槓牌の赤牌枚数
				                    0);                                         // ポンの赤牌枚数
			}

			// -----------------------------------------------------------
			// アクション設定 - 加槓
			// -----------------------------------------------------------
			tk->SetActInfo(tk->kyoku_index,
				PLYACTKAKAN,
				tk->ply_turn,
				4,
				tk->ply_naki_idx[HUM_PLY_SEKI_NUM],
				false                                // 加槓牌の赤牌情報
			);

			// ----------------------------------------
			// アクション設定/ログ出力
			// ----------------------------------------
			if( gui->clientlog_output_flg == true){
				Output_Actionlog(tk, tk->kyoku_index);
			}

			// ----------------------------------------
			// 晒し情報設定 - 加槓
			// ----------------------------------------

			// 赤枚数確認
			if (tk->ply_naki_idx[HUM_PLY_SEKI_NUM] ==  5 || 
			    tk->ply_naki_idx[HUM_PLY_SEKI_NUM] == 15 || 
			    tk->ply_naki_idx[HUM_PLY_SEKI_NUM] == 25 ){

				// 鳴牌設定(赤牌)
				tk->SetNakiInfo(tk->kyoku_index, 
					KAKAN, 
					tk->ply_turn,                                                                  // 自プレーヤー
					tk->kyoku[tk->kyoku_index].act_count,                                          // ACTID
					tk->kyoku[tk->kyoku_index].act_hai[tk->kyoku[tk->kyoku_index].act_count-1],    // 鳴き牌定義
					tk->kyoku[tk->kyoku_index].act_hai[tk->kyoku[tk->kyoku_index].act_count-1],    // 鳴きINDEX牌定義
					tmp_aka_count);                                                                // 鳴き面子の合計赤枚数

			}else{

				// 鳴牌設定(通常牌)
				tk->SetNakiInfo(tk->kyoku_index, 
					KAKAN, 
					tk->ply_turn,                                                                  // 自プレーヤー
					tk->kyoku[tk->kyoku_index].act_count,                                          // ACTID
					tk->kyoku[tk->kyoku_index].act_hai[tk->kyoku[tk->kyoku_index].act_count-1],    // 鳴き牌定義
					tk->kyoku[tk->kyoku_index].act_hai[tk->kyoku[tk->kyoku_index].act_count-1],    // 鳴きINDEX牌定義
					0);                                                                            // 鳴き面子の合計赤枚数

			}

			// ----------------------------------------
			// plyクラス捨牌後の処理
			// ----------------------------------------

			// クライアントゲームモードがPLYモードであるか
			if ( tk->ply_hum_mode == 0 ){

				// プレーヤーアクション - 加槓
				ply[HUM_PLY_SEKI_NUM].PlyActKakan(ply[HUM_PLY_SEKI_NUM].ply_naki_idx, ply[HUM_PLY_SEKI_NUM].ply_naki_aka_count);

			}

		// -----------------------------------------------------------
		// プレーヤーのアクション(自摸和了)
		// -----------------------------------------------------------
		}else if(tk->ply_act == ACTTSUMOAGARI){

			// -----------------------------------------------------------
			// 卓ステータス設定
			// -----------------------------------------------------------
			tk->stat = PLYTSUMOAGARI;

			// -----------------------------------------------------------
			// メッセージ定義(自摸和了)
			// -----------------------------------------------------------
			ActSndHoraMes(gui, tk->ply_mjai_hum_id,                        // 和了プレーヤー
			                   tk->ply_mjai_hum_id,                        // リアクションプレーヤー(自プレーヤと同じ)
			                   tk->ply_act_tsumo[HUM_PLY_SEKI_NUM],        // 自摸牌
			                   tk->ply_act_tsumo_aka[HUM_PLY_SEKI_NUM]);   // 自摸赤

			// -----------------------------------------------------------
			// アクション設定 - 自摸和了
			// -----------------------------------------------------------
			tk->SetActInfo(tk->kyoku_index,
				PLYTSUMOAGARI,
				tk->ply_turn,
				4,
				tk->ply_act_tsumo[HUM_PLY_SEKI_NUM],
				tk->ply_act_tsumo_aka[HUM_PLY_SEKI_NUM]
			);

			// ----------------------------------------
			// tkクラスのアクション情報の最新化
			// ----------------------------------------
			tk->Check_Ply_ActTehai(tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count);

			// ----------------------------------------
			// アクション設定/ログ出力
			// ----------------------------------------
			if( gui->clientlog_output_flg == true){
				Output_Actionlog(tk, tk->kyoku_index);
			}

		// -----------------------------------------------------------
		// プレーヤーのアクション(自摸切り)
		// -----------------------------------------------------------
		}else{

			// -----------------------------------------------------------
			// 卓ステータス設定
			// -----------------------------------------------------------
			tk->stat = PLYACTTSUMOGIRI;

			// -----------------------------------------------------------
			// メッセージ定義(自摸切り)
			// -----------------------------------------------------------
			ActSndDahaiMes(gui, tk->ply_mjai_hum_id, tk->ply_act_tsumo[HUM_PLY_SEKI_NUM], tk->ply_act_tsumo_aka[HUM_PLY_SEKI_NUM], true);   // 捨牌メッセージ

			// -----------------------------------------------------------
			// アクション定義(自摸切り)
			// -----------------------------------------------------------
			// アクション設定 - 自摸切り処理
			tk->SetActInfo(tk->kyoku_index,
				PLYACTTSUMOGIRI,
				tk->ply_turn,
				4,
				tk->ply_act_tsumo[HUM_PLY_SEKI_NUM],
				tk->ply_act_tsumo_aka[HUM_PLY_SEKI_NUM]
			);

			// -----------------------------------------------------------
			// tkクラスのアクション情報の最新化
			// -----------------------------------------------------------
			tk->Check_Ply_ActTehai(tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count);

			// ----------------------------------------
			// アクション設定/ログ出力
			// ----------------------------------------
			if( gui->clientlog_output_flg == true){
				Output_Actionlog(tk, tk->kyoku_index);
			}

			// ----------------------------------------
			// plyクラス捨牌後の処理
			// ----------------------------------------

			// クライアントゲームモードがPLYモードであるか
			if ( tk->ply_hum_mode == 0 ){

				// 自摸捨牌処理
				ply[HUM_PLY_SEKI_NUM].PlyActTsumoSute();

			}

		}

	// -----------------------------------------------------------
	// それ以外のプレーヤーの場合
	// -----------------------------------------------------------
	}else{
		// Noneリクエストの送信処理
		ActSndNoneMes(gui);
	}

}

/* ---------------------------------------------------------------------------------------------- */
// 暗槓時のアクション設定
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::SetActkan(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui){

	// -----------------------------------------------------------
	// プレーヤが自分なら
	// -----------------------------------------------------------
	if( tk->ply_turn == HUM_PLY_SEKI_NUM ){

		// Noneリクエストの送信処理
		ActSndNoneMes(gui);

	// -----------------------------------------------------------
	// それ以外のプレーヤーの場合
	// -----------------------------------------------------------
	}else{
		// Noneリクエストの送信処理
		ActSndNoneMes(gui);
	}

}

/* ---------------------------------------------------------------------------------------------- */
// リーチ時のアクション設定
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::SetActRiichi(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui){

	// -----------------------------------------------------------
	// プレーヤが自分なら
	// -----------------------------------------------------------
	if( tk->ply_turn == HUM_PLY_SEKI_NUM ){

		// ----------------------------------------
		// plyクラス配牌設定
		// ----------------------------------------

		// クライアントゲームモードがPLYモードであるか
		if ( tk->ply_hum_mode == 0 ){

			// アクション定義
			tk->ply_act = ply[HUM_PLY_SEKI_NUM].ply_act;

		}

		// -----------------------------------------------------------
		// プレーヤーのアクション定義(捨牌時)
		// -----------------------------------------------------------
		if(tk->ply_act == ACTSUTE){

			// 捨牌アクション
			SetActSute(tk, ply, gui);

		// -----------------------------------------------------------
		// プレーヤーのアクション(例外処理→自摸切り)
		// -----------------------------------------------------------
		}else{

			// -----------------------------------------------------------
			// 卓ステータス設定
			// -----------------------------------------------------------
			tk->stat = PLYACTTSUMOGIRI;

			// -----------------------------------------------------------
			// メッセージ定義(自摸切り)
			// -----------------------------------------------------------
			ActSndDahaiMes(gui, tk->ply_mjai_hum_id, 
			                    tk->ply_act_tsumo[HUM_PLY_SEKI_NUM], 
			                    tk->ply_act_tsumo_aka[HUM_PLY_SEKI_NUM], 
			                    true);   // 捨牌メッセージ

			// -----------------------------------------------------------
			// アクション定義(自摸切り)
			// -----------------------------------------------------------
			// アクション設定 - 自摸切り処理
			tk->SetActInfo(tk->kyoku_index,
				PLYACTTSUMOGIRI,
				tk->ply_turn,
				4,
				tk->ply_act_tsumo[HUM_PLY_SEKI_NUM],
				tk->ply_act_tsumo_aka[HUM_PLY_SEKI_NUM]
			);

			// -----------------------------------------------------------
			// tkクラスのアクション情報の最新化
			// -----------------------------------------------------------
			tk->Check_Ply_ActTehai(tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count);

			// ----------------------------------------
			// アクション設定/ログ出力
			// ----------------------------------------
			if( gui->clientlog_output_flg == true){
				Output_Actionlog(tk, tk->kyoku_index);
			}

			// ----------------------------------------
			// plyクラス捨牌後の処理
			// ----------------------------------------

			// クライアントゲームモードがPLYモードであるか
			if ( tk->ply_hum_mode == 0 ){

				// 自摸捨牌処理
				ply[HUM_PLY_SEKI_NUM].PlyActTsumoSute();

			}

		}

	// -----------------------------------------------------------
	// それ以外のプレーヤーの場合
	// -----------------------------------------------------------
	}else{

		// Noneリクエストの送信処理
		ActSndNoneMes(gui);

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 捨牌アクション設定
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::SetActSute(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui){

	// -----------------------------------------------------------
	// 捨牌定義
	// -----------------------------------------------------------

	// クライアントゲームモードがPLYモードであるか
	if ( tk->ply_hum_mode == 0 ){
		// 捨牌定義
		tk->ply_act_sute[HUM_PLY_SEKI_NUM]     = ply[HUM_PLY_SEKI_NUM].ply_sute_hai;
		tk->ply_act_sute_aka[HUM_PLY_SEKI_NUM] = ply[HUM_PLY_SEKI_NUM].ply_sute_aka;
	}else{
		// 捨牌定義
		tk->ply_act_sute[HUM_PLY_SEKI_NUM]     = tk->ply_act_tehaitbl[HUM_PLY_SEKI_NUM][tk->ply_tbl_hum_sutehai_statnum];       // 捨牌
		tk->ply_act_sute_aka[HUM_PLY_SEKI_NUM] = tk->ply_act_tehai_tbl_aka[HUM_PLY_SEKI_NUM][tk->ply_tbl_hum_sutehai_statnum];  // 捨牌赤
	}

	// -----------------------------------------------------------
	// メッセージ定義(捨牌)
	// -----------------------------------------------------------
	ActSndDahaiMes(gui, tk->ply_mjai_hum_id, 
	                    tk->ply_act_sute[HUM_PLY_SEKI_NUM],           // 捨牌
	                    tk->ply_act_sute_aka[HUM_PLY_SEKI_NUM],       // 捨牌赤
	                    false);                                       // 自摸切りflg

	// -----------------------------------------------------------
	// アクション定義(捨牌)
	// -----------------------------------------------------------
	// アクション設定 - 捨牌
	tk->SetActInfo(tk->kyoku_index,
		PLYACTSUTE,
		tk->ply_turn,
		4,
		tk->ply_act_sute[HUM_PLY_SEKI_NUM],
		tk->ply_act_sute_aka[HUM_PLY_SEKI_NUM]
	);

	// -----------------------------------------------------------
	// tkクラスのアクション情報の最新化
	// -----------------------------------------------------------
	tk->Check_Ply_ActTehai(tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count);

	// ----------------------------------------
	// アクション設定/ログ出力
	// ----------------------------------------
	if( gui->clientlog_output_flg == true){
		Output_Actionlog(tk, tk->kyoku_index);
	}

	// ----------------------------------------
	// plyクラス捨牌後の処理
	// ----------------------------------------

	// クライアントゲームモードがPLYモードであるか
	if ( tk->ply_hum_mode == 0 ){

		// 自摸捨牌処理
		ply[HUM_PLY_SEKI_NUM].PlyActTsumoSute();

	}

	// -----------------------------------------------------------
	// 卓ステータス設定
	// -----------------------------------------------------------
	tk->stat = PLYACTSUTE;

}

/* ---------------------------------------------------------------------------------------------- */
// 鳴捨アクション設定
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::SetActNakiSuteSub(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui){

	// -----------------------------------------------------------
	// 捨牌定義
	// -----------------------------------------------------------

	// クライアントゲームモードがPLYモードであるか
	if ( tk->ply_hum_mode == 0 ){
		// 捨牌定義
		tk->ply_act_sute[HUM_PLY_SEKI_NUM]     = ply[HUM_PLY_SEKI_NUM].ply_sute_hai;
		tk->ply_act_sute_aka[HUM_PLY_SEKI_NUM] = ply[HUM_PLY_SEKI_NUM].ply_sute_aka;
	}else{
		// 捨牌定義
		tk->ply_act_sute[HUM_PLY_SEKI_NUM]     = tk->ply_act_tehaitbl[HUM_PLY_SEKI_NUM][tk->ply_tbl_hum_sutehai_statnum];       // 捨牌
		tk->ply_act_sute_aka[HUM_PLY_SEKI_NUM] = tk->ply_act_tehai_tbl_aka[HUM_PLY_SEKI_NUM][tk->ply_tbl_hum_sutehai_statnum];  // 捨牌赤
	}

	// -----------------------------------------------------------
	// メッセージ定義(捨牌)
	// -----------------------------------------------------------
	ActSndDahaiMes(gui, tk->ply_mjai_hum_id, 
	                    tk->ply_act_sute[HUM_PLY_SEKI_NUM],           // 捨牌
	                    tk->ply_act_sute_aka[HUM_PLY_SEKI_NUM],       // 捨牌赤
	                    false);                                       // 自摸切りflg

	// -----------------------------------------------------------
	// アクション定義(捨牌)
	// -----------------------------------------------------------
	// アクション設定 - 捨牌
	tk->SetActInfo(tk->kyoku_index,
		PLYACTNAKISUTE,
		tk->ply_turn,
		4,
		tk->ply_act_sute[HUM_PLY_SEKI_NUM],
		tk->ply_act_sute_aka[HUM_PLY_SEKI_NUM]
	);

	// -----------------------------------------------------------
	// tkクラスのアクション情報の最新化
	// -----------------------------------------------------------
	tk->Check_Ply_ActTehai(tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count);

	// ----------------------------------------
	// アクション設定/ログ出力
	// ----------------------------------------
	if( gui->clientlog_output_flg == true){
		Output_Actionlog(tk, tk->kyoku_index);
	}

	// ----------------------------------------
	// plyクラス捨牌後の処理
	// ----------------------------------------

	// クライアントゲームモードがPLYモードであるか
	if ( tk->ply_hum_mode == 0 ){

		// 自摸捨牌処理
		ply[HUM_PLY_SEKI_NUM].PlyActTsumoSute();

	}

	// -----------------------------------------------------------
	// 卓ステータス設定
	// -----------------------------------------------------------
	tk->stat = PLYACTNAKISUTE;

}

/* ---------------------------------------------------------------------------------------------- */
// 鳴き時のアクション設定
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::SetActNaki(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui){

	// 初期化
	int tmp_sute_hai  = 0;
	int tmp_aka_count = 0;

	// -----------------------------------------------------------
	// プレーヤが相手なら
	// -----------------------------------------------------------
	if( tk->ply_turn != HUM_PLY_SEKI_NUM ){

		// ----------------------------------------
		// plyクラス配牌設定
		// ----------------------------------------

		// クライアントゲームモードがPLYモードであるか
		if ( tk->ply_hum_mode == 0 ){

			// アクション定義
			tk->ply_act_naki[HUM_PLY_SEKI_NUM]       = ply[HUM_PLY_SEKI_NUM].ply_act;               // 鳴きアクション
			tk->ply_naki_idx[HUM_PLY_SEKI_NUM]       = ply[HUM_PLY_SEKI_NUM].ply_naki_idx;          // 鳴き牌INDEX
			tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = ply[HUM_PLY_SEKI_NUM].ply_naki_aka_count;    // 手牌赤の合計数

		}

		// -----------------------------------------------------------
		// プレーヤーのアクション定義(ロン時)
		// -----------------------------------------------------------
		if( tk->ply_act_naki[HUM_PLY_SEKI_NUM] == ACTRON){

			// ロン和了リクエストの送信処理
			ActSndHoraMes(gui, tk->ply_mjai_hum_id,                        // 和了プレーヤー
			                   tk->ply_mjai_id[tk->ply_turn],              // リアクションプレーヤー(手番プレーヤー)
			                   tk->ply_act_sute[tk->ply_turn],             // 捨牌
			                   tk->ply_act_sute_aka[tk->ply_turn]);        // 捨牌赤

			// アクション定義：鳴きなし
			tk->ply_act_naki[HUM_PLY_SEKI_NUM] = ACTNONAKI;

		// -----------------------------------------------------------
		// プレーヤーのアクション定義(ポン時)
		// -----------------------------------------------------------
		}else if( tk->ply_act_naki[HUM_PLY_SEKI_NUM] == ACTPON){

			// 捨牌を仮置き
			tmp_sute_hai = tk->ply_act_sute[tk->ply_turn];

			// 手牌の赤牌枚数確認
			if ( ( tmp_sute_hai  ==  5 ) ||
			     ( tmp_sute_hai  == 15 ) ||
			     ( tmp_sute_hai  == 25 ) ){

				// 赤牌枚数をカウント
				if ( tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][(tmp_sute_hai-5)/10] > 2){
					// 3枚以上なら2
					tmp_aka_count = 2;
					tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][(tmp_sute_hai-5)/10] = tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][(tmp_sute_hai-5)/10] - 2;
					// 2枚以下なら手牌の赤牌枚数
				}else{
					tmp_aka_count = tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][(tmp_sute_hai-5)/10];
					tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][(tmp_sute_hai-5)/10] = 0;
				}

			// 赤牌でないなら
			}else{
					tmp_aka_count = 0;
			}

			// ポンメッセージを定義
			ActSndPonMes(gui, tk->ply_mjai_hum_id,                           // 鳴きプレーヤー
			                     tk->ply_mjai_id[tk->ply_turn],              // リアクションプレーヤー(手番プレーヤー)
			                     tk->ply_act_sute[tk->ply_turn],             // 鳴き牌(捨牌)
			                     tk->ply_act_sute_aka[tk->ply_turn],         // 捨牌赤(捨牌赤)
			                     tmp_aka_count);                             // 手牌赤の合計数

			// アクション定義：鳴きなし
			tk->ply_act_naki[HUM_PLY_SEKI_NUM] = ACTNONAKI;

		// -----------------------------------------------------------
		// プレーヤーのアクション定義(チー時)
		// -----------------------------------------------------------
		}else if( tk->ply_act_naki[HUM_PLY_SEKI_NUM] == ACTCHI){

			// チーメッセージを定義
			ActSndChiMes(gui, tk->ply_mjai_hum_id,                           // 鳴きプレーヤー
			                     tk->ply_mjai_id[tk->ply_turn],              // リアクションプレーヤー(手番プレーヤー)
			                     tk->ply_act_sute[tk->ply_turn],             // 鳴き牌(捨牌)
			                     tk->ply_act_sute_aka[tk->ply_turn],         // 捨牌赤(捨牌赤)
			                     tk->ply_naki_idx[HUM_PLY_SEKI_NUM],         // チーINDEX牌
			                     tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM]);  // 手牌赤の合計数

			// アクション定義：鳴きなし
			tk->ply_act_naki[HUM_PLY_SEKI_NUM] = ACTNONAKI;

		// -----------------------------------------------------------
		// プレーヤーのアクション定義(ミンカン時)
		// -----------------------------------------------------------
		}else if( tk->ply_act_naki[HUM_PLY_SEKI_NUM] == ACTMINKAN){

			// 捨牌を仮置き
			tmp_sute_hai = tk->ply_act_sute[tk->ply_turn];

			// 手牌の赤牌枚数確認
			if ( ( tmp_sute_hai  ==  5 ) ||
			     ( tmp_sute_hai  == 15 ) ||
			     ( tmp_sute_hai  == 25 ) ){

					// 赤牌定義
					tmp_aka_count = tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][(tmp_sute_hai-5)/10];
					tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][(tmp_sute_hai-5)/10] = 0;

			// 赤牌でないなら
			}else{
					tmp_aka_count = 0;
			}

			// ミンカンメッセージを定義
			ActSndMinkanMes(gui, tk->ply_mjai_hum_id,                        // 鳴きプレーヤー
			                     tk->ply_mjai_id[tk->ply_turn],              // リアクションプレーヤー(手番プレーヤー)
			                     tk->ply_act_sute[tk->ply_turn],             // 鳴き牌(捨牌)
			                     tk->ply_act_sute_aka[tk->ply_turn],         // 捨牌赤(捨牌赤)
			                     tmp_aka_count);                             // 手牌赤の合計数

			// アクション定義：鳴きなし
			tk->ply_act_naki[HUM_PLY_SEKI_NUM] = ACTNONAKI;

		// -----------------------------------------------------------
		// プレーヤーのアクション(例外処理→何もしない)
		// -----------------------------------------------------------
		}else{

			// Noneリクエストの送信処理
			ActSndNoneMes(gui);

		}

	// -----------------------------------------------------------
	// プレーヤーが自分の場合
	// -----------------------------------------------------------
	}else{

		// Noneリクエストの送信処理
		ActSndNoneMes(gui);

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 鳴き捨牌時のアクション設定
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::SetActNakiSute(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui){

	// プレーヤが自分なら
	if( tk->ply_turn == HUM_PLY_SEKI_NUM ){

		// ----------------------------------------
		// plyクラス捨牌設定
		// ----------------------------------------

		// クライアントゲームモードがPLYモードであるか
		if ( tk->ply_hum_mode == 0 ){

			// アクション定義
			tk->ply_act = ply[HUM_PLY_SEKI_NUM].ply_act;

		}

		// -----------------------------------------------------------
		// プレーヤーのアクション定義(捨牌時)
		// -----------------------------------------------------------
		if(tk->ply_act == ACTNAKISUTE){

			// 捨牌アクション
			SetActNakiSuteSub(tk, ply, gui);

		}

	// -----------------------------------------------------------
	// それ以外のプレーヤーの場合
	// -----------------------------------------------------------
	}else{
		// Noneリクエストの送信処理
		ActSndNoneMes(gui);
	}

}

/* ---------------------------------------------------------------------------------------------- */
// typeごとメッセージ確認(メイン処理)
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::ChkResMesMain(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui){

	// アクション定義
	// https://gimite.net/pukiwiki/index.php?Mjai%20%E9%BA%BB%E9%9B%80AI%E5%AF%BE%E6%88%A6%E3%82%B5%E3%83%BC%E3%83%90

	// 初期化
	bool possible_mode = false;

	// プレート無効化
	gui->plt_mode[PLT_RIICHI] = false;
	gui->plt_mode[PLT_PON]    = false;
	gui->plt_mode[PLT_KAN]    = false;
	gui->plt_mode[PLT_CHI]    = false;
	gui->plt_mode[PLT_AGARI]  = false;

	// 鳴き関連変数の初期化
	gui->chihai_count = 0;              // チー候補牌の初期化
	gui->naki_ankan_hai_count = 0;      // 暗槓牌枚数
	gui->naki_kakan_hai_count = 0;      // 加槓牌枚数

	// ----------------------------------------
	// 受信メッセージの解析
	// ----------------------------------------
	for( int tmp_i = 0; tmp_i < gui->wk_str_count; tmp_i++ ) {

		// ----------------------------------------
		// possible_actionsモード
		// ----------------------------------------

		if( possible_mode == true ){

			// 改行
			if(strcmp(gui->wk_str[tmp_i], "+" ) == 0 ){

				// possible_modeの有効化
				possible_mode = false;

			// possible_actions読み込み
			}else if(strcmp(gui->wk_str[tmp_i], "type" ) == 0 ){

				// アクション設定
				Set_possible_actions(tk, gui, tmp_i);

				// possible_actionsの値を確認するためにbreakで抜けない
				// break;

			}

		// ----------------------------------------
		// 通常モード
		// ----------------------------------------
		}else{

			// -----------------------
			// 改行
			// -----------------------
			if(strcmp(gui->wk_str[tmp_i], "+" ) == 0 ){

				// 改行の場合は何もしない

			// -----------------------
			// possible_actionsの有効化
			// -----------------------
			}else if(strcmp(gui->wk_str[tmp_i], "possible_actions" ) == 0 ){

				// 初期化
				possible_mode = true;

			// -----------------------
			// 卓開始
			// -----------------------
			}else if(strcmp(gui->wk_str[tmp_i], "type" ) == 0 && 
			         strcmp(gui->wk_str[tmp_i+1], "start_game" ) == 0 ){

				// アクション設定
				Set_type_startgame(tk, ply, gui, tmp_i);

				// メッセージ確定のために処理抜け
				break;

			// -----------------------
			// 局開始
			// -----------------------
			}else if(strcmp(gui->wk_str[tmp_i], "type" ) == 0 && 
			         strcmp(gui->wk_str[tmp_i+1], "start_kyoku" ) == 0 ){

				// アクション設定
				Set_type_startkyoku(tk, ply, gui, tmp_i);

				// メッセージ確定のために処理抜け
				break;

			// -----------------------
			// 自摸アクション
			// -----------------------
			}else if(strcmp(gui->wk_str[tmp_i], "type"  ) == 0 && 
			         strcmp(gui->wk_str[tmp_i+1], "tsumo" ) == 0 ){

				// アクション設定
				Set_type_tsumo(tk, ply, gui, tmp_i);

				// possible_actionsの値を確認するためにbreakで抜けない
				// break;

			// -----------------------
			// 暗槓アクション
			// -----------------------
			}else if(strcmp(gui->wk_str[tmp_i], "type"  ) == 0 && 
			         strcmp(gui->wk_str[tmp_i+1], "ankan" ) == 0 ){

				// アクション設定：リーチ後の捨牌処理
				Set_type_ankan(tk, ply, gui, tmp_i);

				// メッセージ確定のために処理抜け
				break;

			// -----------------------
			// 加槓アクション
			// -----------------------
			}else if(strcmp(gui->wk_str[tmp_i], "type"  ) == 0 && 
			         strcmp(gui->wk_str[tmp_i+1], "kakan" ) == 0 ){

				// アクション設定：リーチ後の捨牌処理
				Set_type_kakan(tk, ply, gui, tmp_i);

				// メッセージ確定のために処理抜け
				break;

			// -----------------------
			// リーチアクション
			// -----------------------
			}else if(strcmp(gui->wk_str[tmp_i], "type"  ) == 0 && 
			         strcmp(gui->wk_str[tmp_i+1], "reach" ) == 0 ){

				// アクション設定：リーチ後の捨牌処理
				Set_type_riichi(tk, ply, gui, tmp_i);

				// メッセージ確定のために処理抜け
				break;

			// -----------------------
			// 捨牌処理
			// -----------------------
			}else if(strcmp(gui->wk_str[tmp_i], "type"  ) == 0 && 
			         strcmp(gui->wk_str[tmp_i+1], "dahai" ) == 0 ){

				// アクション設定
				Set_type_dahai(tk, ply, gui, tmp_i);

				// possible_actionsの値を確認するためにbreakで抜けない
				// break;

			// -----------------------
			// ポン処理
			// -----------------------
			}else if(strcmp(gui->wk_str[tmp_i], "type"  ) == 0 && 
			         strcmp(gui->wk_str[tmp_i+1], "pon" ) == 0 ){

				// アクション設定
				Set_type_pon(tk, ply, gui, tmp_i);

				// メッセージ確定のために処理抜け
				break;

			// -----------------------
			// チー処理
			// -----------------------
			}else if(strcmp(gui->wk_str[tmp_i], "type"  ) == 0 && 
			         strcmp(gui->wk_str[tmp_i+1], "chi" ) == 0 ){

				// アクション設定
				Set_type_chi(tk, ply, gui, tmp_i);

				// メッセージ確定のために処理抜け
				break;

			// -----------------------
			// ミンカン処理
			// -----------------------
			}else if(strcmp(gui->wk_str[tmp_i], "type"  ) == 0 && 
			         strcmp(gui->wk_str[tmp_i+1], "daiminkan" ) == 0 ){

				// アクション設定
				Set_type_minkan(tk, ply, gui, tmp_i);

				// メッセージ確定のために処理抜け
				break;

			// -----------------------
			// リーチ宣言受け入れ
			// -----------------------
			}else if(strcmp(gui->wk_str[tmp_i], "type"  ) == 0 && 
			         strcmp(gui->wk_str[tmp_i+1], "reach_accepted" ) == 0 ){

				// アクション設定
				Set_type_reach_accepted(tk, ply, gui, tmp_i);

				// メッセージ確定のために処理抜け
				break;

			// -----------------------
			// 和了確認
			// -----------------------
			}else if(strcmp(gui->wk_str[tmp_i], "type"  ) == 0 && 
			         strcmp(gui->wk_str[tmp_i+1], "hora" ) == 0 ){

				// アクション設定
				Set_type_hora(tk, ply, gui, tmp_i);

				// メッセージ確定のために処理抜け
				break;

			// -----------------------
			// 流局
			// -----------------------
			}else if(strcmp(gui->wk_str[tmp_i], "type"  ) == 0 && 
			         strcmp(gui->wk_str[tmp_i+1], "ryukyoku" ) == 0 ){

				// アクション設定
				Set_type_ryukyoku(tk, ply, gui, tmp_i);

				// メッセージ確定のために処理抜け
				break;

			// -----------------------
			// 終局
			// -----------------------
			}else if(strcmp(gui->wk_str[tmp_i], "type"  ) == 0 && 
			         strcmp(gui->wk_str[tmp_i+1], "end_kyoku" ) == 0 ){

				// アクション設定
				Set_type_endkyoku(tk, gui, tmp_i);

				// メッセージ確定のために処理抜け
				break;

			// -----------------------
			// 卓終了
			// -----------------------
			}else if(strcmp(gui->wk_str[tmp_i], "type"  ) == 0 && 
			         strcmp(gui->wk_str[tmp_i+1], "end_game" ) == 0 ){

				// アクション設定
				Set_type_endgame(tk, gui, tmp_i);

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

		}
	}

	// ----------------------------------------
	// 有効なアクション情報が得られない場合
	// ----------------------------------------

}

/* ---------------------------------------------------------------------------------------------- */
// typeごとでの値設定(start_game)
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::Set_type_startgame(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui, int tmp_wk_num){

	// ----------------------------------------
	// 局情報設定
	// ----------------------------------------

	// 卓ゲーム種別
	tk->tkgame_type = TKGAME_MJAI;

	// 局情報
	tk->kyoku[tk->kyoku_index].kyoku = 0;

	// ツミ棒
	tk->kyoku[tk->kyoku_index].tsumibo = 0;

	// リーチ棒
	tk->kyoku[tk->kyoku_index].riichbo = 0;

	// ----------------------------------------
	// 前処理
	// ----------------------------------------

	// HUMプレーヤーのPly_id設定
	tk->ply_mjai_hum_id = atoi(gui->wk_str[tmp_wk_num+3]);

	// ----------------------------------------
	// ply_idとプレーヤー名の設定
	// ----------------------------------------

	for( int tmp_i = 0; tmp_i < PLAYER_MAX; tmp_i++ ) {
		// ply_id設定
		tk->ply_mjai_id[tmp_i] = ( tmp_i + 1 + tk->ply_mjai_hum_id ) % 4;
		// プレーヤ名指定
		wsprintf(tk->plyname[tmp_i], gui->wk_str[ tk->ply_mjai_id[tmp_i] + tmp_wk_num+5 ]);
	}

	// ----------------------------------------
	// ply設定(卓開始)
	// ----------------------------------------
	// クライアントゲームモードがPLYモードであるか
	if ( tk->ply_hum_mode == 0 ){
		ply[HUM_PLY_SEKI_NUM].PlyActTakuStart(HUM_PLY_SEKI_NUM);
	}

	// ----------------------------------------
	// 卓ステータス設定
	// ----------------------------------------
	tk->stat = TAKUSTART;

}

/* ---------------------------------------------------------------------------------------------- */
// typeごとでの値設定(start_kyoku)
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::Set_type_startkyoku(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui, int tmp_wk_num){

	// ----------------------------------------
	// 前処理
	// ----------------------------------------

	// 初期化
	int  tmp_ply_id;
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
		tk->kyoku_index=0;
	}else{
		tk->kyoku_index++;
	}

	// ----------------------------------------
	// 局情報初期化
	// ----------------------------------------
	tk->KyokuInit();

	// ----------------------------------------
	// 局の算出
	// ----------------------------------------

	// 局
	tk->kyoku[tk->kyoku_index].kyoku = Get_hainum(gui->wk_str[tmp_wk_num+3] ) - 31 + // E(東場)かS(南場)の文字列確認
	                                  atoi(gui->wk_str[tmp_wk_num+5]) - 1;          // 局情報取得

	// ----------------------------------------
	// 局情報定義
	// ----------------------------------------

	// 本場
	tk->kyoku[tk->kyoku_index].tsumibo = atoi(gui->wk_str[tmp_wk_num+7]);

	// リーチ棒
	tk->kyoku[tk->kyoku_index].riichbo = atoi(gui->wk_str[tmp_wk_num+9]);

	// シード番号
	tk->kyoku[tk->kyoku_index].seed_num = 0;

	// ----------------------------------------
	// 得点定義
	// ----------------------------------------
	if(tk->kyoku_index > 0){
		tk->kyoku[tk->kyoku_index].ply_kyoku_start_score[0] = tk->kyoku[tk->kyoku_index-1].ply_kyoku_end_score[0];
		tk->kyoku[tk->kyoku_index].ply_kyoku_start_score[1] = tk->kyoku[tk->kyoku_index-1].ply_kyoku_end_score[1];
		tk->kyoku[tk->kyoku_index].ply_kyoku_start_score[2] = tk->kyoku[tk->kyoku_index-1].ply_kyoku_end_score[2];
		tk->kyoku[tk->kyoku_index].ply_kyoku_start_score[3] = tk->kyoku[tk->kyoku_index-1].ply_kyoku_end_score[3];
	}

	// ----------------------------------------
	// ドラ定義
	// ----------------------------------------

	// ドラ表示牌
	tmp_dora_hai = Get_hainum(gui->wk_str[tmp_wk_num+13]);

	// 赤牌確認
	if (tmp_dora_hai > 100){
		tmp_dora_hai = tmp_dora_hai - 100;
		tmp_dora_aka = true;
	}else{
		tmp_dora_aka = false;
	}

	// ドラ表示牌定義
	tk->kyoku[tk->kyoku_index].dora[0]     = tmp_dora_hai;
	tk->kyoku[tk->kyoku_index].dora_aka[0] = tmp_dora_aka;

	// ----------------------------------------
	// 手番設定(親の席番号指定)
	// ----------------------------------------
	tmp_ply_id = atoi(gui->wk_str[tmp_wk_num+11]);

	// 順番設定
	// tk->ply_turn = ( tmp_ply_id + 1 + tk->ply_mjai_hum_id ) % 4; // tmp_i = tmp_ply_id - ( 3 - tk->ply_mjai_hum_id)
	for( int tmp_i = 0; tmp_i < PLAYER_MAX; tmp_i++ ) {
		if (tmp_ply_id == tk->ply_mjai_id[tmp_i]){
			tk->ply_turn = tmp_i;
			break;
		}
	}

	// ----------------------------------------
	// 家情報
	// ----------------------------------------
	tmp_ie_id = tk->ply_turn;
	for( int tmp_i = 0; tmp_i < PLAYER_MAX; tmp_i++ ) {
		tk->kyoku[tk->kyoku_index].ie[tmp_ie_id] = tmp_i;
		tmp_ie_id = (tmp_ie_id+1) % 4;
	}

	// ----------------------------------------
	// pinfo設定(局開始)
	// ----------------------------------------
	// クライアントゲームモードがPLYモードであるか
	if ( tk->ply_hum_mode == 0 ){
		// ply[HUM_PLY_SEKI_NUM].PlyActKyokuStart(tk->kyoku[tk->kyoku_index].ie[HUM_PLY_SEKI_NUM]);
		ply[HUM_PLY_SEKI_NUM].PlyActKyokuStart(0,0,0,0, tk->kyoku[tk->kyoku_index].ie[HUM_PLY_SEKI_NUM], tk->kyoku[tk->kyoku_index].dora[0]);
	}

	// ----------------------------------------
	// 配牌設定
	// ----------------------------------------

	// 配牌ポインター設定
	haipai_point=tmp_wk_num + 15 + TEHAI_MAX * tk->ply_mjai_hum_id;

	// 配牌設定
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
		tk->kyoku[tk->kyoku_index].tehai[HUM_PLY_SEKI_NUM][now_tsumo_hai]++;

		// 赤牌追加
		if(now_tsumo_aka == true){
			tk->kyoku[tk->kyoku_index].aka_count[HUM_PLY_SEKI_NUM][(now_tsumo_hai-5)/10]++;
		}

		// ----------------------------------------
		// plyクラス配牌設定
		// ----------------------------------------

		// クライアントゲームモードがPLYモードであるか
		if ( tk->ply_hum_mode == 0 ){

			// plyクラス配牌
			ply[HUM_PLY_SEKI_NUM].PlyActHaipai(now_tsumo_hai, now_tsumo_aka);

			// 赤牌設定
			for(int tmp_aka_grp = 0; tmp_aka_grp < AKA_TYPE_MAX_COUNT; tmp_aka_grp++){;
				ply[HUM_PLY_SEKI_NUM].aka_count[tmp_aka_grp] = tk->kyoku[tk->kyoku_index].aka_count[HUM_PLY_SEKI_NUM][tmp_aka_grp];
			}

			// 配牌後の確認処理
			ply[HUM_PLY_SEKI_NUM].PlyActPostHaipai();

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

	// -----------------------------------------------------------
	// tkクラスのアクション情報の最新化
	// -----------------------------------------------------------
	tk->Check_Ply_ActTehai(tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count);

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
// typeごとでの値設定(tsumo)
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::Set_type_tsumo(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui, int tmp_wk_num){

	// アクション定義
	// https://gimite.net/pukiwiki/index.php?Mjai%20%E9%BA%BB%E9%9B%80AI%E5%AF%BE%E6%88%A6%E3%82%B5%E3%83%BC%E3%83%90

	// 初期化
	int tmp_ply_id;

	// 卓ステータス設定
	tk->stat = PLYACTTSUMO;

	// 手番設定
	tmp_ply_id = atoi(gui->wk_str[tmp_wk_num+3]);
	// tk->ply_turn = ( tmp_ply_id + 1 + tk->ply_mjai_hum_id ) % 4; // tmp_i = tmp_ply_id - ( 3 - tk->ply_mjai_hum_id)
	for( int tmp_i = 0; tmp_i < PLAYER_MAX; tmp_i++ ) {
		if (tmp_ply_id == tk->ply_mjai_id[tmp_i]){
			tk->ply_turn = tmp_i;
			break;
		}
	}

	// ----------------------------------------
	// 自摸プレーヤが自分ならば
	// ----------------------------------------
	if( tk->ply_turn == HUM_PLY_SEKI_NUM ){

		// ----------------------------------------
		// 牌情報設定
		// ----------------------------------------

		// 自摸牌確認
		tk->ply_act_tsumo[HUM_PLY_SEKI_NUM] = Get_hainum(gui->wk_str[tmp_wk_num+5]);

		// 赤牌確認
		if (tk->ply_act_tsumo[HUM_PLY_SEKI_NUM]  > 100){
			tk->ply_act_tsumo[HUM_PLY_SEKI_NUM]  = tk->ply_act_tsumo[HUM_PLY_SEKI_NUM]  - 100;
			tk->ply_act_tsumo_aka[HUM_PLY_SEKI_NUM] = true;
		}else{
			tk->ply_act_tsumo_aka[HUM_PLY_SEKI_NUM] = false;
		}

		// -----------------------------------------------------------
		// アクション設定 - 自摸処理
		// -----------------------------------------------------------
		tk->SetActInfo(tk->kyoku_index,
			PLYACTTSUMO,
			tk->ply_turn,
			4,
			tk->ply_act_tsumo[HUM_PLY_SEKI_NUM],
			tk->ply_act_tsumo_aka[HUM_PLY_SEKI_NUM]
		);

		// -----------------------------------------------------------
		// tkクラスのアクション情報の最新化
		// -----------------------------------------------------------
		tk->Check_Ply_ActTehai(tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count);

		// -----------------------------------------------------------
		// アクション設定/ログ出力
		// -----------------------------------------------------------
		if( gui->clientlog_output_flg == true){
			Output_Actionlog(tk, tk->kyoku_index);
		}

		// ----------------------------------------
		// pinfo設定(自摸処理)
		// ----------------------------------------
		// クライアントゲームモードがPLYモードであるか
		if ( tk->ply_hum_mode == 0 ){
			ply[HUM_PLY_SEKI_NUM].PlyActTsumo(tk->ply_act_tsumo[HUM_PLY_SEKI_NUM], tk->ply_act_tsumo_aka[HUM_PLY_SEKI_NUM]);
		}

	// ----------------------------------------
	// 自摸プレーヤがCOMならば
	// ----------------------------------------
	}else{

		// -----------------------------------------------------------
		// アクション設定 - 自摸処理(COM)
		// -----------------------------------------------------------

		// アクション設定 - 自摸処理(COM)
		tk->SetActInfo(tk->kyoku_index,
			PLYACTTSUMO,
			tk->ply_turn,
			4,
			0,                              // 自摸牌が不明な場合は「0」とする
			false
		);

		// -----------------------------------------------------------
		// tkクラスのアクション情報の最新化
		// -----------------------------------------------------------
		tk->Check_Ply_ActTehai(tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count);

		// -----------------------------------------------------------
		// アクション設定/ログ出力
		// -----------------------------------------------------------
		if( gui->clientlog_output_flg == true){
			Output_Actionlog(tk, tk->kyoku_index);
		}

	}
}

/* ---------------------------------------------------------------------------------------------- */
// typeごとでの値設定(ankan)
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::Set_type_ankan(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui, int tmp_wk_num){

	// ----------------------------------------
	// 初期化
	// ----------------------------------------

	int tmp_act_ply_id;
	int tmp_act_seki;

	int  tmp_naki_hai = 0;
	bool tmp_naki_aka =false;
	int  tmp_aka_count = 0;

	// ----------------------------------------
	// 卓ステータス設定
	// ----------------------------------------
	tk->stat = PLYACTANKAN;

	// ----------------------------------------
	// ACTプレーヤーの特定
	// ----------------------------------------

	// プレーヤーID確認
	tmp_act_ply_id  = atoi(gui->wk_str[tmp_wk_num+3]);

	// 席ID確認
	// tk->ply_turn = ( tmp_ply_id + 1 + tk->ply_mjai_hum_id ) % 4; // tmp_i = tmp_ply_id - ( 3 - tk->ply_mjai_hum_id)
	for( int tmp_i = 0; tmp_i < PLAYER_MAX; tmp_i++ ) {

		// 鳴きプレーヤ番号の設定
		if (tmp_act_ply_id == tk->ply_mjai_id[tmp_i]){
			tmp_act_seki = tmp_i;
		}

	}

	// ----------------------------------------
	// 捨牌設定(牌テーブル処理：相手プレーヤー)
	// ----------------------------------------
	if( tk->ply_turn != HUM_PLY_SEKI_NUM ){

		// ----------------------------------------
		// 暗槓牌確認(1枚目)
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
		// 暗槓牌確認(2枚目)
		// ----------------------------------------

		// 手牌読込
		tmp_naki_hai = Get_hainum(gui->wk_str[tmp_wk_num+6]);
		// 赤牌確認
		if (tmp_naki_hai > 100){
			tmp_naki_hai = tmp_naki_hai - 100;
			// 赤牌加算
			tmp_aka_count++;
		}

		// ----------------------------------------
		// 暗槓牌確認(3枚目)
		// ----------------------------------------

		// 手牌読込
		tmp_naki_hai = Get_hainum(gui->wk_str[tmp_wk_num+7]);
		// 赤牌確認
		if (tmp_naki_hai > 100){
			tmp_naki_hai = tmp_naki_hai - 100;
			// 赤牌加算
			tmp_aka_count++;
		}

		// ----------------------------------------
		// 暗槓牌確認(4枚目)
		// ----------------------------------------

		// 手牌読込
		tmp_naki_hai = Get_hainum(gui->wk_str[tmp_wk_num+8]);
		// 赤牌確認
		if (tmp_naki_hai > 100){
			tmp_naki_hai = tmp_naki_hai - 100;
			// 赤牌加算
			tmp_aka_count++;
		}

		// ----------------------------------------
		// アクション設定 - 暗槓
		// ----------------------------------------
		tk->SetActInfo(tk->kyoku_index,
			PLYACTANKAN,
			tmp_act_seki,
			4,
			tmp_naki_hai,
			tmp_naki_aka
		);

		// ----------------------------------------
		// tkクラスのアクション情報の最新化
		// ----------------------------------------
		tk->Check_Ply_ActTehai(tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count);

		// ----------------------------------------
		// アクション設定/ログ出力
		// ----------------------------------------
		if( gui->clientlog_output_flg == true){
			Output_Actionlog(tk, tk->kyoku_index);
		}

		// ----------------------------------------
		// 晒し情報設定 - 暗槓
		// ----------------------------------------
		tk->SetNakiInfo(tk->kyoku_index, 
			ANKAN, 
			tmp_act_seki,                                                            // 自プレーヤー
			tk->kyoku[tk->kyoku_index].act_count,                                    // ACTID
			tmp_naki_hai,                                                            // 鳴き牌定義
			tmp_naki_hai,                                                            // 鳴きINDEX牌定義
			tmp_aka_count);                                                          // 赤牌の枚数

	// ----------------------------------------
	// 捨牌設定(牌テーブル処理：自分プレーヤー)
	// ----------------------------------------
	}else{

		// 何もアクションしない

	}

}

/* ---------------------------------------------------------------------------------------------- */
// typeごとでの値設定(kakan)
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::Set_type_kakan(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui, int tmp_wk_num){

	// ----------------------------------------
	// 初期化
	// ----------------------------------------

	int tmp_act_ply_id;
	int tmp_act_seki;

	int  tmp_naki_hai = 0;
	bool tmp_naki_aka =false;
	int  tmp_aka_count = 0;

	// ----------------------------------------
	// 卓ステータス設定
	// ----------------------------------------
	tk->stat = PLYACTKAKAN;

	// ----------------------------------------
	// ACTプレーヤーの特定
	// ----------------------------------------

	// プレーヤーID確認
	tmp_act_ply_id  = atoi(gui->wk_str[tmp_wk_num+3]);

	// 席ID確認
	// tk->ply_turn = ( tmp_ply_id + 1 + tk->ply_mjai_hum_id ) % 4; // tmp_i = tmp_ply_id - ( 3 - tk->ply_mjai_hum_id)
	for( int tmp_i = 0; tmp_i < PLAYER_MAX; tmp_i++ ) {

		// 鳴きプレーヤ番号の設定
		if (tmp_act_ply_id == tk->ply_mjai_id[tmp_i]){
			tmp_act_seki = tmp_i;
		}

	}

	// ----------------------------------------
	// 捨牌設定(牌テーブル処理：相手プレーヤー)
	// ----------------------------------------
	if( tk->ply_turn != HUM_PLY_SEKI_NUM ){

		// ----------------------------------------
		// 暗槓牌確認(1枚目)
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
		// アクション設定 - 暗槓
		// ----------------------------------------
		tk->SetActInfo(tk->kyoku_index,
			PLYACTKAKAN,
			tmp_act_seki,
			4,
			tmp_naki_hai,
			tmp_naki_aka
		);

		// ----------------------------------------
		// tkクラスのアクション情報の最新化
		// ----------------------------------------
		tk->Check_Ply_ActTehai(tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count);

		// ----------------------------------------
		// アクション設定/ログ出力
		// ----------------------------------------
		if( gui->clientlog_output_flg == true){
			Output_Actionlog(tk, tk->kyoku_index);
		}

		// ----------------------------------------
		// 晒し情報設定 - 暗槓
		// ----------------------------------------
		tk->SetNakiInfo(tk->kyoku_index, 
			KAKAN, 
			tmp_act_seki,                                                            // 自プレーヤー
			tk->kyoku[tk->kyoku_index].act_count,                                    // ACTID
			tmp_naki_hai,                                                            // 鳴き牌定義
			tmp_naki_hai,                                                            // 鳴きINDEX牌定義
			tmp_aka_count);                                                          // 赤牌の枚数

	// ----------------------------------------
	// 捨牌設定(牌テーブル処理：自分プレーヤー)
	// ----------------------------------------
	}else{

		// 何もアクションしない

	}
}

/* ---------------------------------------------------------------------------------------------- */
// typeごとでの値設定(reach：リーチ後の捨牌決定)
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::Set_type_riichi(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui, int tmp_wk_num){

	// 変数定義
	int tmp_hai = 0;

	// ----------------------------------------
	// 自摸プレーヤがCOMならば
	// ----------------------------------------
	if( tk->ply_turn != HUM_PLY_SEKI_NUM ){

		// ----------------------------------------
		// アクション設定 - リーチ宣言
		// ----------------------------------------
		tk->SetActInfo(tk->kyoku_index,
			PLYACTRIICH,
			tk->ply_turn,
			4,
			0,
			false
		);

		// ----------------------------------------
		// tkクラスのアクション情報の最新化
		// ----------------------------------------
		tk->Check_Ply_ActTehai(tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count);

		// ----------------------------------------
		// アクション設定/ログ出力
		// ----------------------------------------
		if( gui->clientlog_output_flg == true){
			Output_Actionlog(tk, tk->kyoku_index);
		}

	// ----------------------------------------
	// 自摸プレーヤが自分ならば
	// ----------------------------------------
	}else{

		// ----------------------------------------
		// 捨牌不可有無の確認
		// ----------------------------------------
		if( (strcmp(gui->wk_str[tmp_wk_num+4], "cannot_dahai") == 0 ) && 
		    (strcmp(gui->wk_str[tmp_wk_num+5], "+") != 0 )            ){

			// 初期化
			gui->cannot_sutehai_count = 0;

			// GUIモード変更
			// gui->gui_ply_tehai_mode = TEHAI_RIICHI_SUTEHAI;

			// 捨牌不可テーブル定義
			for(int tmp_i = tmp_wk_num+5; tmp_i < gui->wk_str_count; tmp_i++){

				// 改行でないなら
				if(strcmp(gui->wk_str[tmp_i], "+") != 0 ){

					// 捨牌不可の算出
					tmp_hai = Get_hainum(gui->wk_str[tmp_i]);
					if ( tmp_hai > 100){
						tmp_hai = tmp_hai - 100;
					}

					// 捨牌不可テーブル定義
					gui->cannot_sutehai[gui->cannot_sutehai_count] = tmp_hai;
					gui->cannot_sutehai_count++;

				}
			}

			// シャンテン数テーブル定義
			for(int tmp_i = 0; tmp_i < TEHAI_MAX; tmp_i++){

				// 初期化
				tk->ply_act_tehai_shanten_tbl[HUM_PLY_SEKI_NUM][tmp_i] = 0;
				tk->ply_act_tehai_can_sute_tbl[HUM_PLY_SEKI_NUM][tmp_i] = true;

				// 比較
				for(int tmp_j = 0; tmp_j < gui->cannot_sutehai_count; tmp_j++){
					 if(gui->cannot_sutehai[tmp_j] == tk->ply_act_tehaitbl[HUM_PLY_SEKI_NUM][tmp_i]){
						// 不可テーブルに牌があれば
						tk->ply_act_tehai_shanten_tbl[HUM_PLY_SEKI_NUM][tmp_i] = 1;
						tk->ply_act_tehai_can_sute_tbl[HUM_PLY_SEKI_NUM][tmp_i] = false;
						break;
					 }
				}
			}

			// シャンテン数・自摸牌

				// 初期化
				tk->ply_act_tsumo_shanten[HUM_PLY_SEKI_NUM] = 0;
				tk->ply_act_tsumo_can_sute[HUM_PLY_SEKI_NUM] = true;

				// 比較
				for(int tmp_j = 0; tmp_j < gui->cannot_sutehai_count; tmp_j++){
					 if(gui->cannot_sutehai[tmp_j] == tk->ply_act_tsumo[HUM_PLY_SEKI_NUM]){
						// 不可テーブルに牌があれば
						tk->ply_act_tsumo_shanten[HUM_PLY_SEKI_NUM] = 1;
						tk->ply_act_tsumo_can_sute[HUM_PLY_SEKI_NUM] = false;
						break;
					 }
				}

		}

		// ----------------------------------------
		// pinfo設定(リーチ後処理)
		// ----------------------------------------
		// クライアントゲームモードがPLYモードであるか
		if ( tk->ply_hum_mode == 0 ){
			ply[HUM_PLY_SEKI_NUM].PlyActTsumo(tk->ply_act_tsumo[HUM_PLY_SEKI_NUM], tk->ply_act_tsumo_aka[HUM_PLY_SEKI_NUM]);
		};

	}

	// ----------------------------------------
	// 卓ステータス設定
	// ----------------------------------------
	tk->stat = PLYACTRIICH;


}

/* ---------------------------------------------------------------------------------------------- */
// typeごとでの値設定(dahai)
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::Set_type_dahai(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui, int tmp_wk_num){

	// アクション定義
	// https://gimite.net/pukiwiki/index.php?Mjai%20%E9%BA%BB%E9%9B%80AI%E5%AF%BE%E6%88%A6%E3%82%B5%E3%83%BC%E3%83%90

	// ----------------------------------------
	// 初期化
	// ----------------------------------------
	int tmp_ply_id;

	// 手番設定
	tmp_ply_id = atoi(gui->wk_str[tmp_wk_num+3]);
	for( int tmp_i = 0; tmp_i < PLAYER_MAX; tmp_i++ ) {
		if (tmp_ply_id == tk->ply_mjai_id[tmp_i]){
			tk->ply_turn = tmp_i;
			break;
		}
	}

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
	// 捨牌設定(牌テーブル処理：相手プレーヤー)
	// ----------------------------------------
	if( tk->ply_turn != HUM_PLY_SEKI_NUM ){

		// 捨牌設定
		tk->ply_act_sute[tk->ply_turn] = Get_hainum(gui->wk_str[tmp_wk_num+5]);

		// 赤牌確認
		if ( tk->ply_act_sute[tk->ply_turn] > 100){
			 tk->ply_act_sute[tk->ply_turn] = tk->ply_act_sute[tk->ply_turn] - 100;
			 tk->ply_act_sute_aka[tk->ply_turn] = true;
		}else{
			 tk->ply_act_sute_aka[tk->ply_turn] = false;
		}

		// デバグ用
		if ( tk->ply_act_sute[tk->ply_turn] > 37 || tk->ply_act_sute[tk->ply_turn] < 0){
			 tk->ply_act_sute[tk->ply_turn] = 0;
		}

		// -----------------------------------------------------------
		// アクション設定
		// -----------------------------------------------------------
		tk->SetActInfo(tk->kyoku_index,
			tk->stat,
			tk->ply_turn,
			4,
			tk->ply_act_sute[tk->ply_turn],
			tk->ply_act_sute_aka[tk->ply_turn]
		);

		// -----------------------------------------------------------
		// tkクラスのアクション情報の最新化
		// -----------------------------------------------------------
		tk->Check_Ply_ActTehai(tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count);

		// ----------------------------------------
		// アクション設定/ログ出力
		// ----------------------------------------
		if( gui->clientlog_output_flg == true){
			Output_Actionlog(tk, tk->kyoku_index);
		}

		// -----------------------------------------------------------
		// 自分プレーヤー鳴きアクション定義
		// -----------------------------------------------------------

		// クライアントゲームモードがPLYモードであるか
		if ( tk->ply_hum_mode == 0 ){
			// ply[HUM_PLY_SEKI_NUM].PlyChkNaki(tk->ply_turn, tk->kyoku[tk->kyoku_index].act_hai[tk->kyoku[tk->kyoku_index].act_count]);
			ply[HUM_PLY_SEKI_NUM].PlyChkNaki(tk->ply_turn, tk->ply_act_sute[tk->ply_turn]);
		}

		// -----------------------------------------------------------
		// 捨牌位置設定
		// -----------------------------------------------------------
		tk->ply_tbl_com_sutehai_statnum[tk->ply_turn] = rand() % tk->ply_act_tehaicount[tk->ply_turn];

	// ----------------------------------------
	// 捨牌設定(牌テーブル処理：自分プレーヤー)
	// ----------------------------------------
	}else{

		// 何もアクションしない

	}

}

/* ---------------------------------------------------------------------------------------------- */
// typeごとでの値設定(pon)
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::Set_type_pon(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui, int tmp_wk_num){

	// ----------------------------------------
	// 初期化
	// ----------------------------------------

	int tmp_naki_ply_id;
	int tmp_naki_seki;

	int tmp_target_ply_id;
	int tmp_react_seki;

	int  tmp_naki_hai = 0;
	bool tmp_naki_aka = false ;
	int  tmp_aka_count = 0;

	// ----------------------------------------
	// REACTプレーヤー(targetプレーヤー)の特定
	// ----------------------------------------

	// プレーヤーID確認
	tmp_naki_ply_id  = atoi(gui->wk_str[tmp_wk_num+3]);
	tmp_target_ply_id = atoi(gui->wk_str[tmp_wk_num+5]);

	// 席ID確認
	// tk->ply_turn = ( tmp_ply_id + 1 + tk->ply_mjai_hum_id ) % 4; // tmp_i = tmp_ply_id - ( 3 - tk->ply_mjai_hum_id)
	for( int tmp_i = 0; tmp_i < PLAYER_MAX; tmp_i++ ) {

		// 鳴きプレーヤ番号の設定
		if (tmp_naki_ply_id == tk->ply_mjai_id[tmp_i]){
			tmp_naki_seki = tmp_i;
		}

		// REACTプレーヤ番号の設定
		if (tmp_target_ply_id == tk->ply_mjai_id[tmp_i]){
			tmp_react_seki = tmp_i;
		}

	}

	// 順番変更
	tk->ply_turn = tmp_naki_seki;

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
		tmp_naki_seki,                                                            // 鳴きプレーヤー
		tk->kyoku[tk->kyoku_index].act_count,                                      // ACTID
		tk->kyoku[tk->kyoku_index].act_hai[tk->kyoku[tk->kyoku_index].act_count-1], // 鳴き牌定義
		tk->kyoku[tk->kyoku_index].act_hai[tk->kyoku[tk->kyoku_index].act_count-1], // 鳴きINDEX牌定義
		tmp_aka_count);                                                           // 赤牌の枚数

	// ----------------------------------------
	// tkクラスのアクション情報の最新化
	// ----------------------------------------
	tk->Check_Ply_ActTehai(tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count);

	// ----------------------------------------
	// アクション設定/ログ出力
	// ----------------------------------------
	if( gui->clientlog_output_flg == true){
		Output_Actionlog(tk, tk->kyoku_index);
	}

	// ----------------------------------------
	// 捨牌不可テーブル定義
	// ----------------------------------------

	// 捨牌不可テーブル定義(全て捨牌可能)
	for(int tmp_i = 0; tmp_i < tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM]; tmp_i++){
		// 初期化
		tk->ply_act_tehai_can_sute_tbl[HUM_PLY_SEKI_NUM][tmp_i] = true;
	}

	// ----------------------------------------
	// plyクラスにアクション情報を引き渡し
	// ----------------------------------------

	// クライアントゲームモードがPLYモードであるか
	if ( tk->ply_hum_mode == 0 ){

		// 鳴き情報引き渡し
		ply[HUM_PLY_SEKI_NUM].PlyActNaki( tmp_naki_seki,   // 引数：鳴きプレーヤー番号
		                      ACTPON,                  // 鳴きアクション
		                      tmp_naki_hai,            // 鳴き牌
		                      tmp_naki_hai,            // 鳴きINDEX
		                      tmp_naki_aka             // 赤牌枚数
		); 

	}

	// ----------------------------------------
	// 卓ステータス設定
	// ----------------------------------------
	tk->stat = PLYACTPON;

}

/* ---------------------------------------------------------------------------------------------- */
// typeごとでの値設定(chi)
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::Set_type_chi(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui, int tmp_wk_num){

	// ----------------------------------------
	// 初期化
	// ----------------------------------------

	int tmp_naki_ply_id;
	int tmp_naki_seki;

	int tmp_target_ply_id;
	int tmp_react_seki;

	int  tmp_naki_hai = 0;
	bool tmp_naki_aka = false ;
	int  tmp_aka_count = 0;

	int tmp_naki_tehai_hai1 = 0;
	int tmp_naki_tehai_hai2 = 0;
	int tmp_hai = 0;
	int tmp_chi_idx = 0;

	// cannot_dahai定義用
	int cannot_hai_count=0;
	int tmp_cannot_hai = 0;

	// ----------------------------------------
	// REACTプレーヤー(targetプレーヤー)の特定
	// ----------------------------------------

	// プレーヤーID確認
	tmp_naki_ply_id  = atoi(gui->wk_str[tmp_wk_num+3]);
	tmp_target_ply_id = atoi(gui->wk_str[tmp_wk_num+5]);

	// 席ID確認
	// tk->ply_turn = ( tmp_ply_id + 1 + tk->ply_mjai_hum_id ) % 4; // tmp_i = tmp_ply_id - ( 3 - tk->ply_mjai_hum_id )
	for( int tmp_i = 0; tmp_i < PLAYER_MAX; tmp_i++ ) {

		// 鳴きプレーヤ番号の設定
		if (tmp_naki_ply_id == tk->ply_mjai_id[tmp_i]){
			tmp_naki_seki = tmp_i;
		}

		// REACTプレーヤ番号の設定
		if (tmp_target_ply_id == tk->ply_mjai_id[tmp_i]){
			tmp_react_seki = tmp_i;
		}

	}

	// 順番変更
	tk->ply_turn = tmp_naki_seki;

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
		tmp_naki_seki,                       // 鳴きプレーヤー
		tk->kyoku[tk->kyoku_index].act_count, // ACTID
		tmp_naki_hai,                        // 鳴き牌
		tmp_chi_idx,                         // 鳴き牌INDEX
		tmp_aka_count                        // 赤牌枚数 
	);

	// ----------------------------------------
	// tkクラスのアクション情報の最新化
	// ----------------------------------------
	tk->Check_Ply_ActTehai(tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count);

	// ----------------------------------------
	// アクション設定/ログ出力
	// ----------------------------------------
	if( gui->clientlog_output_flg == true){
		Output_Actionlog(tk, tk->kyoku_index);
	}

	// ----------------------------------------
	// 捨牌不可有無の確認(鳴き捨牌時)
	// ----------------------------------------

	// 捨牌不可テーブル定義
	for(int tmp_i = 0; tmp_i < tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM]; tmp_i++){
		tk->ply_act_tehai_can_sute_tbl[HUM_PLY_SEKI_NUM][tmp_i] = true;
	}

	// cannot_dahai牌の確認
	if( (strcmp(gui->wk_str[tmp_wk_num+11], "cannot_dahai") == 0 ) && 
	    (strcmp(gui->wk_str[tmp_wk_num+12], "+") != 0 )            ){

		// 初期化
		gui->cannot_sutehai_count = 0;

		// テーブル定義
		for(int tmp_i = tmp_wk_num+12; tmp_i < gui->wk_str_count; tmp_i++){

			// 改行でないなら
			if(strcmp(gui->wk_str[tmp_i], "+") != 0 ){

				// 捨牌不可の算出
				tmp_hai = Get_hainum(gui->wk_str[tmp_i]);
				if ( tmp_hai > 100){
					tmp_hai = tmp_hai - 100;
				}

				// 捨牌不可テーブル定義
				gui->cannot_sutehai[gui->cannot_sutehai_count] = tmp_hai;
				gui->cannot_sutehai_count++;

			}
		}

		// 捨牌不可テーブル定義
		for(int tmp_i = 0; tmp_i < tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM]; tmp_i++){
			// 初期化
			tk->ply_act_tehai_can_sute_tbl[HUM_PLY_SEKI_NUM][tmp_i] = true;

			// 比較
			for(int tmp_j = 0; tmp_j < gui->cannot_sutehai_count; tmp_j++){
				 if(gui->cannot_sutehai[tmp_j] == tk->ply_act_tehaitbl[HUM_PLY_SEKI_NUM][tmp_i]){
					// 不可テーブルに牌があれば
					tk->ply_act_tehai_can_sute_tbl[HUM_PLY_SEKI_NUM][tmp_i] = false;
					break;
				 }
			}

		}

	}

	// ----------------------------------------
	// plyクラスにアクション情報を引き渡し
	// ----------------------------------------

	// クライアントゲームモードがPLYモードであるか
	if ( tk->ply_hum_mode == 0 ){

		// 鳴き情報引き渡し
		ply[HUM_PLY_SEKI_NUM].PlyActNaki( tmp_naki_seki,   // 引数：鳴きプレーヤー番号
		                      ACTCHI,                  // 鳴きアクション
		                      tmp_naki_hai,            // 鳴き牌
		                      tmp_chi_idx,             // 鳴きINDEX
		                      tmp_aka_count            // 赤牌枚数
		);
	}

	// ----------------------------------------
	// 卓ステータス設定
	// ----------------------------------------
	tk->stat = PLYACTCHI;

}

/* ---------------------------------------------------------------------------------------------- */
// typeごとでの値設定(minkan)
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::Set_type_minkan(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui, int tmp_wk_num){

	// ----------------------------------------
	// 初期化
	// ----------------------------------------

	int tmp_naki_ply_id;
	int tmp_naki_seki;

	int tmp_target_ply_id;
	int tmp_react_seki;

	int  tmp_naki_hai = 0;
	bool tmp_naki_aka = false ;
	int  tmp_aka_count = 0;

	// ----------------------------------------
	// REACTプレーヤー(targetプレーヤー)の特定
	// ----------------------------------------

	// プレーヤーID確認
	tmp_naki_ply_id  = atoi(gui->wk_str[tmp_wk_num+3]);
	tmp_target_ply_id = atoi(gui->wk_str[tmp_wk_num+5]);

	// 席ID確認
	// tk->ply_turn = ( tmp_ply_id + 1 + tk->ply_mjai_hum_id ) % 4; // tmp_i = tmp_ply_id - ( 3 - tk->ply_mjai_hum_id)
	for( int tmp_i = 0; tmp_i < PLAYER_MAX; tmp_i++ ) {

		// 鳴きプレーヤ番号の設定
		if (tmp_naki_ply_id == tk->ply_mjai_id[tmp_i]){
			tmp_naki_seki = tmp_i;
		}

		// REACTプレーヤ番号の設定
		if (tmp_target_ply_id == tk->ply_mjai_id[tmp_i]){
			tmp_react_seki = tmp_i;
		}

	}

	// 順番変更
	tk->ply_turn = tmp_naki_seki;

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

	// 手牌の赤牌枚数確認
	if ( ( tmp_naki_hai  == MAN5NUM ) ||
	     ( tmp_naki_hai  == PIN5NUM ) ||
	     ( tmp_naki_hai  == SOU5NUM ) ){
			// 赤牌定義
			tmp_aka_count = tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][(tmp_naki_hai-5)/10];
			tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][(tmp_naki_hai-5)/10] = 0;
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
		tmp_naki_seki,                                                                    // 鳴きプレーヤー
		tk->kyoku[tk->kyoku_index].act_count,                                             // ACTID
		tk->kyoku[tk->kyoku_index].act_hai[tk->kyoku[tk->kyoku_index].act_count-1],       // 鳴き牌定義
		tk->kyoku[tk->kyoku_index].act_hai[tk->kyoku[tk->kyoku_index].act_count-1],       // 鳴きINDEX牌定義
		tmp_aka_count);                                                                   // 赤牌の枚数

	// ----------------------------------------
	// tkクラスのアクション情報の最新化
	// ----------------------------------------
	tk->Check_Ply_ActTehai(tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count);

	// ----------------------------------------
	// アクション設定/ログ出力
	// ----------------------------------------
	if( gui->clientlog_output_flg == true){
		Output_Actionlog(tk, tk->kyoku_index);
	}

	// ----------------------------------------
	// 卓ステータス設定
	// ----------------------------------------
	tk->stat = PLYACTMINKAN;

}

/* ---------------------------------------------------------------------------------------------- */
// typeごとでの値設定(reach_accepted)
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::Set_type_reach_accepted(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui, int tmp_wk_num){

	// ----------------------------------------
	// 現在得点を設定
	// ----------------------------------------

	// ply_id関連
	int tmp_ply_id_0_seki;

	// 席ID確認
	// tk->ply_turn = ( tmp_ply_id + 1 + tk->ply_mjai_hum_id ) % 4; // tmp_i = tmp_ply_id - ( 3 - tk->ply_mjai_hum_id)
	for( int tmp_i = 0; tmp_i < PLAYER_MAX; tmp_i++ ) {

		// ply_mjai_id = 0のプレーヤ番号の設定
		if (tk->ply_mjai_id[tmp_i] == 0){
			tmp_ply_id_0_seki = tmp_i;
		}

	}

	// 得点導入

	// ----------------------------------------
	// 卓ステータス設定
	// ----------------------------------------
	tk->stat = PLYRIICHACCEPTED;

}

/* ---------------------------------------------------------------------------------------------- */
// typeごとでの値設定(hora)
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::Set_type_hora(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui, int tmp_wk_num){

	// ----------------------------------------
	// 初期化
	// ----------------------------------------

	// 読み込みモード
	int yakus_read_mode = 0; // (0:読込開始前、1:裏ドラ読込中、2:和了手牌読込中、3:役情報読込中、4:読込終了)

	// ply_id関連
	int tmp_agari_ply_id;
	int tmp_target_ply_id;
	int tmp_ply_id_0_seki;

	// 牌関連
	int tmp_hai = 0;
	int tmp_aka = false;

	// 手牌枚数初期化
	tk->kyoku[tk->kyoku_index].agari_tehaicount = 0;
	tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakucount = 0;

	// -----------------------------
	// 値定義
	// -----------------------------
	tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakucount     = 0;
	tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakuman_count = 0;
	tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han = 0;
	tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_mangan_count = 0;
	tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakuman_agari_ply_bai=0;

	// ----------------------------------------
	// 流局フラグ
	// ----------------------------------------
	tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].ryukyoku_flg = false;

	// ----------------------------------------
	// 和了プレーヤーの指定
	// ----------------------------------------

	// プレーヤーID確認
	tmp_agari_ply_id  = atoi(gui->wk_str[tmp_wk_num+3]);
	tmp_target_ply_id = atoi(gui->wk_str[tmp_wk_num+5]);

	// 席ID確認
	// tk->ply_turn = ( tmp_ply_id + 1 + tk->ply_mjai_hum_id ) % 4; // tmp_i = tmp_ply_id - ( 3 - tk->ply_mjai_hum_id)
	for( int tmp_i = 0; tmp_i < PLAYER_MAX; tmp_i++ ) {

		// 和了プレーヤ番号の設定
		if (tmp_agari_ply_id == tk->ply_mjai_id[tmp_i]){
			tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_num = tmp_i;
		}

		// 振込プレーヤ番号の設定
		if (tmp_target_ply_id == tk->ply_mjai_id[tmp_i]){
			tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].furikomi_ply_num = tmp_i;
		}

		// ply_mjai_id = 0のプレーヤ番号の設定
		if (tk->ply_mjai_id[tmp_i] == 0){
			tmp_ply_id_0_seki = tmp_i;
		}

	}

	// ----------------------------------------
	// 卓ステータス設定(和了プレーヤーとターゲットが同じならば自摸和了の設定)
	// ----------------------------------------
	if ( tmp_agari_ply_id == tmp_target_ply_id ){
		tk->stat = PLYTSUMOAGARI;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].tsumo_agari_flg = true;
	}else{
		tk->stat = PLYACTRON;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].tsumo_agari_flg = false;
	}

	// ----------------------------------------
	// 役解析
	// ----------------------------------------
	// wk構造体読込
	for(int tmp_i = 0; tmp_i < gui->wk_str_count-tmp_wk_num; tmp_i++){

		// -----------------------------
		// 0:読込開始前
		// -----------------------------
		if( yakus_read_mode == 0){

			// 和了プレーヤ
			if(strcmp(gui->wk_str[tmp_wk_num+tmp_i], "actor") == 0 ){
				// 何もしない
			}

			// 振込プレーヤ
			if(strcmp(gui->wk_str[tmp_wk_num+tmp_i], "target") == 0 ){
				// 何もしない
			}

			// 和了牌
			if(strcmp(gui->wk_str[tmp_wk_num+tmp_i], "pai") == 0 ){

				// 牌読み込み
				tmp_hai = Get_hainum(gui->wk_str[tmp_wk_num+tmp_i+1]);
				// 赤牌確認
				if (tmp_hai > 100){
					tmp_hai = tmp_hai - 100;
					tmp_aka = true;
				}else{
					tmp_aka = false;
				}

				// 和了牌登録
				tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_hai = tmp_hai;
				tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_aka = tmp_aka;

				// 次にカウントする
				tmp_i++;

			}

			// 役読込開始なら
			if(strcmp(gui->wk_str[tmp_wk_num+tmp_i], "uradora_markers") == 0 ){
				yakus_read_mode = 1;
			}

		// -----------------------------
		// 1:裏ドラ読込中
		// -----------------------------
		}else if( yakus_read_mode == 1){

			// 手牌確認
			if(strcmp(gui->wk_str[tmp_wk_num+tmp_i], "hora_tehais") == 0 ){
				yakus_read_mode = 2;
			}else{
				// 手牌読込
				tmp_hai = Get_hainum(gui->wk_str[tmp_wk_num+tmp_i]);
				// 赤牌確認
				if (tmp_hai > 100){
					tmp_hai = tmp_hai - 100;
					tmp_aka = true;
				}else{
					tmp_aka = false;
				}
				// 裏ドラ登録
			}

		// -----------------------------
		// 2:和了手牌情報読込中
		// -----------------------------
		}else if( yakus_read_mode == 2){

			// 役読込開始なら
			if(strcmp(gui->wk_str[tmp_wk_num+tmp_i], "yakus") == 0 ){
				yakus_read_mode = 3;
			}else{
				// 和了牌以外を手牌読込
				// if (tk->kyoku[tk->kyoku_index].agari_tehaicount < TEHAI_MAX){
				if ( tk->kyoku[tk->kyoku_index].agari_tehaicount < tk->ply_act_tehaicount[tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_num] ){
					// 牌番号取得
					tmp_hai = Get_hainum(gui->wk_str[tmp_wk_num+tmp_i]);
					// 赤牌確認
					if (tmp_hai > 100){
						tmp_hai = tmp_hai - 100;
						tmp_aka = true;
					}else{
						tmp_aka = false;
					}
					// 和了テーブルに登録
					tk->kyoku[tk->kyoku_index].agari_tehaitbl[tk->kyoku[tk->kyoku_index].agari_tehaicount]     = tmp_hai;
					tk->kyoku[tk->kyoku_index].agari_tehaitbl_aka[tk->kyoku[tk->kyoku_index].agari_tehaicount] = tmp_aka;
					tk->kyoku[tk->kyoku_index].agari_tehaicount++;
				}

			}

		// -----------------------------
		// 3:役情報読込中
		// -----------------------------
		}else if( yakus_read_mode == 3){

			// 符であるなら
			if(strcmp(gui->wk_str[tmp_wk_num+tmp_i], "fu") == 0 ){

				// 符読み込み
				tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].scoreFu = atoi(gui->wk_str[tmp_wk_num+tmp_i+1]);

				// 次にカウントする
				tmp_i++;

				// モード変更
				yakus_read_mode = 4;

			// 役情報読み込み
			}else{

				// 役読み込み
				Set_type_hora_yaku_check(tk, ply, gui, tmp_wk_num+tmp_i);

				// +1カウントする
				tmp_i++;

			}

		// -----------------------------
		// 4:読込終了
		// -----------------------------
		}else if( yakus_read_mode == 4){

			// 翻情報
			if(strcmp(gui->wk_str[tmp_wk_num+tmp_i], "fan") == 0 ){
				tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han = atoi(gui->wk_str[tmp_wk_num+tmp_i+1]);
			}

			// 和了得点(delta)
			if(strcmp(gui->wk_str[tmp_wk_num+tmp_i], "deltas") == 0 ){

				// 得点設定
				for(int ply_i = 0; ply_i < PLAYER_MAX; ply_i++){
					tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].kyoku_score[(tmp_ply_id_0_seki + ply_i)%4] = atoi(gui->wk_str[tmp_wk_num+tmp_i+ply_i+1]);
				}

				// 次にカウントする
				tmp_i = tmp_i + 4;

			}

			// 局終了得点
			if(strcmp(gui->wk_str[tmp_wk_num+tmp_i], "scores") == 0 ){

				// 得点設定
				for(int ply_i = 0; ply_i < PLAYER_MAX; ply_i++){
					tk->kyoku[tk->kyoku_index].ply_kyoku_end_score[(tmp_ply_id_0_seki + ply_i)%4] = atoi(gui->wk_str[tmp_wk_num+tmp_i+ply_i+1]);
				}

				// 次にカウントする
				tmp_i = tmp_i + 4;

			}

		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// typeごとでの値設定(hora：役確認)
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::Set_type_hora_yaku_check(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui, int tmp_yaku_num){

	// -----------------------------
	// 通常役
	// -----------------------------

	// 01: リーチ
	if(strcmp(gui->wk_str[tmp_yaku_num], "reach") == 0 ){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_flg[RIICH] = true;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[RIICH] = atoi(gui->wk_str[tmp_yaku_num+1]);
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han   = tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han + tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[RIICH];
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakucount++;

	// 02: ダブルリーチ
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "double_reach") == 0 ){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_flg[WRIICH] = true;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[WRIICH] = atoi(gui->wk_str[tmp_yaku_num+1]);
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han   = tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han + tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[WRIICH];
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakucount++;

	// 03: 一発
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "ippatsu") == 0 ){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_flg[IPPATSU] = true;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[IPPATSU] = atoi(gui->wk_str[tmp_yaku_num+1]);
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han   = tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han + tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[IPPATSU];
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakucount++;

	// 04: 清一色
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "chiniso") == 0 ){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_flg[CHINISO] = true;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[CHINISO] = atoi(gui->wk_str[tmp_yaku_num+1]);
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han   = tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han + tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[CHINISO];
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakucount++;

	// 05: 混一色
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "honiso") == 0 ){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_flg[HONISO] = true;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[HONISO] = atoi(gui->wk_str[tmp_yaku_num+1]);
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han   = tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han + tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[HONISO];
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakucount++;

	// 06: 純全帯
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "junchantaiyao") == 0 ){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_flg[JUNCHAN] = true;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[JUNCHAN] = atoi(gui->wk_str[tmp_yaku_num+1]);
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han   = tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han + tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[JUNCHAN];
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakucount++;

	// 07: 二盃口
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "ryanpeko") == 0 ){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_flg[RYANPEKO] = true;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[RYANPEKO] = atoi(gui->wk_str[tmp_yaku_num+1]);
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han   = tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han + tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[RYANPEKO];
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakucount++;

	// 08: 混老頭
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "honroto") == 0 ){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_flg[HONROTO] = true;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[HONROTO] = atoi(gui->wk_str[tmp_yaku_num+1]);
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han   = tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han + tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[HONROTO];
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakucount++;

	// 09: 小三元
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "shosangen") == 0 ){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_flg[SHOSANGEN] = true;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[SHOSANGEN] = atoi(gui->wk_str[tmp_yaku_num+1]);
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han   = tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han + tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[SHOSANGEN];
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakucount++;

	// 10: 一気通貫
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "ikkitsukan") == 0 ){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_flg[ITSU] = true;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[ITSU] = atoi(gui->wk_str[tmp_yaku_num+1]);
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han   = tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han + tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[ITSU];
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakucount++;

	// 11: 三色同刻
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "sanshokudoko") == 0 ){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_flg[SANDOKOU] = true;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[SANDOKOU] = atoi(gui->wk_str[tmp_yaku_num+1]);
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han   = tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han + tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[SANDOKOU];
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakucount++;

	// 12: 三色同順
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "sanshokudojun") == 0 ){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_flg[SANDOJUN] = true;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[SANDOJUN] = atoi(gui->wk_str[tmp_yaku_num+1]);
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han   = tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han + tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[SANDOJUN];
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakucount++;

	// 13: 三槓子
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "sankantsu") == 0 ){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_flg[SANKANTSU] = true;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[SANKANTSU] = atoi(gui->wk_str[tmp_yaku_num+1]);
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han = tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han + tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[SANKANTSU];
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakucount++;

	// 14: 三暗刻
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "sananko") == 0 ){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_flg[SANANKO] = true;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[SANANKO] = atoi(gui->wk_str[tmp_yaku_num+1]);
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han = tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han + tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[SANANKO];
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakucount++;

	// 15: 対々和
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "toitoiho") == 0 ){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_flg[TOITOI] = true;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[TOITOI] = atoi(gui->wk_str[tmp_yaku_num+1]);
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han   = tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han + tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[TOITOI];
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakucount++;

	// 16: 混全帯
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "honchantaiyao") == 0 ){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_flg[CHANTA] = true;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[CHANTA] = atoi(gui->wk_str[tmp_yaku_num+1]);
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han   = tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han + tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[CHANTA];
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakucount++;

	// 17: 七対子
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "chitoitsu") == 0 ){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_flg[CHITOI] = true;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[CHITOI] = atoi(gui->wk_str[tmp_yaku_num+1]);
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han   = tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han + tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[CHITOI];
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakucount++;

	// 18: 平和
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "pinfu") == 0 ){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_flg[PINFU] = true;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[PINFU] = atoi(gui->wk_str[tmp_yaku_num+1]);
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han   = tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han + tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[PINFU];
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakucount++;

	// 19: 断公九
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "tanyaochu") == 0 ){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_flg[TANYAO] = true;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[TANYAO] = atoi(gui->wk_str[tmp_yaku_num+1]);
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han   = tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han + tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[TANYAO];
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakucount++;

	// 20: 一盃口
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "ipeko") == 0 ){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_flg[IPEKO] = true;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[IPEKO] = atoi(gui->wk_str[tmp_yaku_num+1]);
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han   = tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han + tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[IPEKO];
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakucount++;

	// 21: 場風牌
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "bakaze") == 0 ){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_flg[BAKAZE] = true;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[BAKAZE] = atoi(gui->wk_str[tmp_yaku_num+1]);
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han   = tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han + tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[BAKAZE];
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakucount++;

	// 22: 自風牌
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "jikaze") == 0 ){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_flg[ZIKAZE] = true;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[ZIKAZE] = atoi(gui->wk_str[tmp_yaku_num+1]);
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han   = tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han + tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[ZIKAZE];
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakucount++;

	// 23: 三元牌
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "sangenpai") == 0 ){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_flg[YAKUHAI] = true;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[YAKUHAI] = atoi(gui->wk_str[tmp_yaku_num+1]);
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han   = tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han + tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[YAKUHAI];
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakucount++;

	// 27: 海底摸月
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "haiteiraoyue") == 0 ){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_flg[HAITEI] = true;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[HAITEI] = atoi(gui->wk_str[tmp_yaku_num+1]);
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han   = tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han + tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[HAITEI];
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakucount++;

	// 28: 河底撈魚
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "hoteiraoyui") == 0 ){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_flg[HOUTEI] = true;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[HOUTEI] = atoi(gui->wk_str[tmp_yaku_num+1]);
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han   = tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han + tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[HOUTEI];
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakucount++;

	// 29: 嶺上開花
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "rinshankaiho") == 0 ){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_flg[RINSHAN] = true;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[RINSHAN] = atoi(gui->wk_str[tmp_yaku_num+1]);
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han   = tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han + tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[RINSHAN];
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakucount++;

	// 30: 槍槓
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "chankan") == 0 ){

	// 31: 門前清自摸和
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "menzenchin_tsumoho") == 0 ){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_flg[TSUMO] = true;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[TSUMO] = atoi(gui->wk_str[tmp_yaku_num+1]);
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han   = tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han + tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[TSUMO];
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakucount++;

	// 32: ドラ(表ドラ)
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "dora") == 0 ){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_flg[DORA] = true;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[DORA] = atoi(gui->wk_str[tmp_yaku_num+1]);
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han  = tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han + tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[DORA];
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakucount++;

	// 33: 裏ドラ
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "uradora") == 0 ){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_flg[URADORA] = true;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[URADORA] = atoi(gui->wk_str[tmp_yaku_num+1]);
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han     = tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han + tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[URADORA];
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakucount++;

	// 34: 赤牌
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "akadora") == 0 ){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_flg[AKAHAI] = true;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[AKAHAI] = atoi(gui->wk_str[tmp_yaku_num+1]);
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han   = tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han + tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[AKAHAI];
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakucount++;

	// -----------------------------
	// 役満
	// -----------------------------

	// 役満01: 天和
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "tenho") == 0 ){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakuman_flg[TENHO] = true;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakuman_bai[TENHO] = atoi(gui->wk_str[tmp_yaku_num+1]);
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakuman_agari_ply_bai = tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakuman_agari_ply_bai + tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakuman_bai[TENHO];
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakuman_count++;

	// 役満02: 地和
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "chiho") == 0 ){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakuman_flg[CHIHO] = true;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakuman_bai[CHIHO] = atoi(gui->wk_str[tmp_yaku_num+1]);
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakuman_agari_ply_bai = tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakuman_agari_ply_bai + tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakuman_bai[CHIHO];
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakuman_count++;

	// 役満03: 九連九面待ち
	// 役満04: 九連宝燈
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "churenpoton") == 0 ){

	// 役満05: 国士13面
	// 役満06: 国士無双
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "kokushimuso") == 0 ){

	// 役満07: 大三元
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "daisangen") == 0 ){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakuman_flg[DAISANGEN] = true;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakuman_bai[DAISANGEN] = atoi(gui->wk_str[tmp_yaku_num+1]);
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakuman_agari_ply_bai = tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakuman_agari_ply_bai + tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakuman_bai[DAISANGEN];
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakuman_count++;

	// 役満08: 大四喜和
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "daisushi") == 0 ){

	// 役満09: 小四喜和
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "shosushi") == 0 ){

	// 役満10: 字一色
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "tsuiso") == 0 ){

	// 役満11: 清老頭
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "chinroto") == 0 ){

	// 役満12: 緑一色
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "ryuiso") == 0 ){

	// 役満13: 四槓子
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "sukantsu") == 0 ){

	// 役満15: 四暗刻
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "suanko") == 0 ){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakuman_flg[SUANKO] = true;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakuman_bai[SUANKO] = atoi(gui->wk_str[tmp_yaku_num+1]);
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakuman_agari_ply_bai = tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakuman_agari_ply_bai + tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakuman_bai[SUANKO];
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakuman_count++;

	// 役満16: 人和(役満)
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "renho") == 0 ){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakuman_flg[RENHOYAKUMAN] = true;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakuman_bai[RENHOYAKUMAN] = atoi(gui->wk_str[tmp_yaku_num+1]);
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakuman_agari_ply_bai = tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakuman_agari_ply_bai + tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakuman_bai[RENHOYAKUMAN];
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakuman_count++;
	}

}

/* ---------------------------------------------------------------------------------------------- */
// typeごとでの値設定(ryukyoku)
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::Set_type_ryukyoku(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui, int tmp_wk_num){

	// ----------------------------------------
	// 変数定義
	// ----------------------------------------
	int tmp_ply_id_0_seki;

	// ----------------------------------------
	// 席ID確認
	// ----------------------------------------
	for( int tmp_pnum = 0; tmp_pnum < PLAYER_MAX; tmp_pnum++ ) {
		// ply_mjai_id = 0のプレーヤ番号の設定
		if (tk->ply_mjai_id[tmp_pnum] == 0){
			tmp_ply_id_0_seki = tmp_pnum;
		}
	}

	// ----------------------------------------
	// 流局フラグ
	// ----------------------------------------
	tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].ryukyoku_flg  = true;
	tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakuman_count = 0;
	tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakucount     = 0;

	// ----------------------------------------
	// 流局ステータス設定
	// ----------------------------------------
	if(strcmp(gui->wk_str[tmp_wk_num+3], "fanpai") == 0 ){
		// 流局：荒牌
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].ryukyoku_stat = HOWANPAI;
	}else if(strcmp(gui->wk_str[tmp_wk_num+3], "sufonrenta") == 0 ){
		// 流局：四風連打
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].ryukyoku_stat = SUFURENDA;
	}else if(strcmp(gui->wk_str[tmp_wk_num+3], "suchareach") == 0 ){
		// 流局：四人リーチ
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].ryukyoku_stat = RIICHI4PLY;
	}else{
		// 流局：不明
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].ryukyoku_stat = UNKNOWNRKK;
	}

	// -----------------------------
	// wk構造体読込
	// -----------------------------
	for(int tmp_ryukyoku_num = tmp_wk_num+4; tmp_ryukyoku_num < gui->wk_str_count; tmp_ryukyoku_num++){

		// テンパイ確認(tenpais)
		if(strcmp(gui->wk_str[tmp_ryukyoku_num], "tenpais") == 0 ){

			// テンパイ人数の初期化
			tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].ply_tempai_count = 0;

			// プレーヤごとのテンパイ確認
			for(int ply_i = 0; ply_i < PLAYER_MAX; ply_i++){
				if(strcmp(gui->wk_str[tmp_ryukyoku_num+1+ply_i], "true") == 0 ){
					tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].ply_tempai_flg[(tmp_ply_id_0_seki + ply_i)%4] = true;
					tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].ply_tempai_count++;
				}else{
					tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].ply_tempai_flg[(tmp_ply_id_0_seki + ply_i)%4] = false;
				}
			}
		}

		// 局得点(delta)
		if(strcmp(gui->wk_str[tmp_ryukyoku_num], "deltas") == 0 ){
			for(int ply_i = 0; ply_i < PLAYER_MAX; ply_i++){
				tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].kyoku_score[(tmp_ply_id_0_seki + ply_i)%4] = atoi(gui->wk_str[tmp_ryukyoku_num+1+ply_i]);
			}
		}

		// 局終了時得点(score)
		if(strcmp(gui->wk_str[tmp_ryukyoku_num], "scores") == 0 ){
			for(int ply_i = 0; ply_i < PLAYER_MAX; ply_i++){
				tk->kyoku[tk->kyoku_index].ply_kyoku_end_score[(tmp_ply_id_0_seki + ply_i)%4] = atoi(gui->wk_str[tmp_ryukyoku_num+1+ply_i]);
			}
		}

	}

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

	// ----------------------------------------
	// tkクラスのアクション情報の最新化
	// ----------------------------------------
	tk->Check_Ply_ActTehai(tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count);

	// ----------------------------------------
	// アクション設定/ログ出力
	// ----------------------------------------
	if( gui->clientlog_output_flg == true){
		Output_Actionlog(tk, tk->kyoku_index);
	}

	// ----------------------------------------
	// 卓ステータス設定
	// ----------------------------------------
	tk->stat = RYUKYOKU;

}

/* ---------------------------------------------------------------------------------------------- */
// typeごとでの値設定(endkyoku)
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::Set_type_endkyoku(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num){

	// ----------------------------------------
	// 卓ステータス設定
	// ----------------------------------------
	tk->stat = KYOKURESULT;

}

/* ---------------------------------------------------------------------------------------------- */
// typeごとでの値設定(endgame)
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::Set_type_endgame(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num){

	// ----------------------------------------
	// 変数定義
	// ----------------------------------------
	int tmp_ply_id_0_seki;

	// ----------------------------------------
	// 席ID確認
	// ----------------------------------------
	for( int tmp_pnum = 0; tmp_pnum < PLAYER_MAX; tmp_pnum++ ) {
		// ply_mjai_id = 0のプレーヤ番号の設定
		if (tk->ply_mjai_id[tmp_pnum] == 0){
			tmp_ply_id_0_seki = tmp_pnum;
		}
	}

	// ----------------------------------------
	// 最終得点得点設定
	// ----------------------------------------
	for(int ply_i = 0; ply_i < PLAYER_MAX; ply_i++){
		tk->plyEndscore[(tmp_ply_id_0_seki + ply_i)%4] = atoi(gui->wk_str[tmp_wk_num+3+ply_i]);
	}

	// ----------------------------------------
	// 卓ステータス設定
	// ----------------------------------------
	tk->stat = TAKURESULT;

}

/* ---------------------------------------------------------------------------------------------- */
// typeごとでの値設定(possible_actions)
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::Set_possible_actions(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num){

	// ----------------------------------------
	// 変数定義
	// ----------------------------------------
	int tmp_naki_hai = 0;
	int tmp_naki_tehai_hai1 = 0;   // 鳴牌1枚目
	int tmp_naki_tehai_hai2 = 0;   // 鳴牌2枚目
	int tmp_num = 0;               // 交換用変数
	int tmp_chi_idx = 0;           // チー牌INDEX

	// 赤牌カウント
	int tmp_aka_count = 0;

	// ----------------------------------------
	// 和了アクション
	// ----------------------------------------
	if(strcmp(gui->wk_str[tmp_wk_num], "type"  ) == 0 && 
	   strcmp(gui->wk_str[tmp_wk_num+1], "hora" ) == 0 ){

		// プレート有効化
		gui->plt_mode[PLT_AGARI]  = true;

		// ロン和了であるなら→自分以外の手番なら
		if ( tk->ply_turn != HUM_PLY_SEKI_NUM){

			// 鳴き確認時の捨牌着色
			if ( ( tk->ply_act_kawa_mode[tk->ply_turn][tk->ply_act_kawa_count[tk->ply_turn]-1] == 0) || 
			     ( tk->ply_act_kawa_mode[tk->ply_turn][tk->ply_act_kawa_count[tk->ply_turn]-1] == 5)
			   ){
				// 青色着色
				tk->ply_act_kawa_mode[tk->ply_turn][tk->ply_act_kawa_count[tk->ply_turn]-1] = 
				tk->ply_act_kawa_mode[tk->ply_turn][tk->ply_act_kawa_count[tk->ply_turn]-1] + HAI_COLOR_NUM_BLUE;
			}
		}

	// ----------------------------------------
	// リーチアクション
	// ----------------------------------------
	}else if(strcmp(gui->wk_str[tmp_wk_num], "type"  ) == 0 && 
	         strcmp(gui->wk_str[tmp_wk_num+1], "reach" ) == 0 ){

		// プレート有効化
		gui->plt_mode[PLT_RIICHI] = true;

	// ----------------------------------------
	// 暗槓アクション
	// ----------------------------------------
	}else if(strcmp(gui->wk_str[tmp_wk_num], "type"  ) == 0 && 
	         strcmp(gui->wk_str[tmp_wk_num+1], "ankan" ) == 0 ){

		// プレート有効化
		gui->plt_mode[PLT_KAN]    = true;

		// 鳴き牌の算出
		tmp_naki_hai = Get_hainum(gui->wk_str[tmp_wk_num+5]);
		if (tmp_naki_hai > 100){
			tmp_naki_hai = tmp_naki_hai - 100;
		}

		// 暗槓候補牌の設定
		gui->naki_ankan_hai[gui->naki_ankan_hai_count] = tmp_naki_hai;
		gui->naki_ankan_hai_count++;

	// ----------------------------------------
	// 加槓アクション
	// ----------------------------------------
	}else if(strcmp(gui->wk_str[tmp_wk_num], "type"  ) == 0 && 
	         strcmp(gui->wk_str[tmp_wk_num+1], "kakan" ) == 0 ){

		// プレート有効化
		gui->plt_mode[PLT_KAN]    = true;

		// 鳴き牌の算出
		tmp_naki_hai = Get_hainum(gui->wk_str[tmp_wk_num+5]);
		if (tmp_naki_hai > 100){
			tmp_naki_hai = tmp_naki_hai - 100;
		}

		// 加槓候補牌の設定
		gui->naki_kakan_hai[gui->naki_kakan_hai_count] = tmp_naki_hai;
		gui->naki_kakan_hai_count++;

	// ----------------------------------------
	// 明槓アクション
	// ----------------------------------------
	}else if(strcmp(gui->wk_str[tmp_wk_num], "type"  ) == 0 && 
	         strcmp(gui->wk_str[tmp_wk_num+1], "daiminkan" ) == 0 ){

		// 鳴有フラグが有効であるなら
		if( gui->plt_nakiari_flg == true ){

			// プレート有効化
			gui->plt_mode[PLT_KAN]    = true;

			// 鳴き確認時の捨牌着色
			if ( ( tk->ply_act_kawa_mode[tk->ply_turn][tk->ply_act_kawa_count[tk->ply_turn]-1] == 0) || 
			     ( tk->ply_act_kawa_mode[tk->ply_turn][tk->ply_act_kawa_count[tk->ply_turn]-1] == 5)
			   ){
				// 青色着色
				tk->ply_act_kawa_mode[tk->ply_turn][tk->ply_act_kawa_count[tk->ply_turn]-1] = 
				tk->ply_act_kawa_mode[tk->ply_turn][tk->ply_act_kawa_count[tk->ply_turn]-1] + HAI_COLOR_NUM_BLUE;
			}

		}

	// ----------------------------------------
	// ポンアクション
	// ----------------------------------------
	}else if(strcmp(gui->wk_str[tmp_wk_num], "type"  ) == 0 && 
	         strcmp(gui->wk_str[tmp_wk_num+1], "pon" ) == 0 ){

		// 鳴有フラグが有効であるなら
		if( gui->plt_nakiari_flg == true ){

			// プレート有効化
			gui->plt_mode[PLT_PON]    = true;

			// 鳴き確認時の捨牌着色
			if ( ( tk->ply_act_kawa_mode[tk->ply_turn][tk->ply_act_kawa_count[tk->ply_turn]-1] == 0) || 
			     ( tk->ply_act_kawa_mode[tk->ply_turn][tk->ply_act_kawa_count[tk->ply_turn]-1] == 5)
			   ){
				// 青色着色
				tk->ply_act_kawa_mode[tk->ply_turn][tk->ply_act_kawa_count[tk->ply_turn]-1] = 
				tk->ply_act_kawa_mode[tk->ply_turn][tk->ply_act_kawa_count[tk->ply_turn]-1] + HAI_COLOR_NUM_BLUE;
			}
		}

	// ----------------------------------------
	// チーアクション
	// ----------------------------------------
	}else if(strcmp(gui->wk_str[tmp_wk_num], "type"  ) == 0 && 
	         strcmp(gui->wk_str[tmp_wk_num+1], "chi" ) == 0 ){

		// 鳴有フラグが有効であるなら
		if( gui->plt_nakiari_flg == true ){

			// プレート有効化
			gui->plt_mode[PLT_CHI]    = true;

			// 鳴き確認時の捨牌着色
			if ( ( tk->ply_act_kawa_mode[tk->ply_turn][tk->ply_act_kawa_count[tk->ply_turn]-1] == 0) || 
			     ( tk->ply_act_kawa_mode[tk->ply_turn][tk->ply_act_kawa_count[tk->ply_turn]-1] == 5)
			   ){
				// 青色着色
				tk->ply_act_kawa_mode[tk->ply_turn][tk->ply_act_kawa_count[tk->ply_turn]-1] = 
				tk->ply_act_kawa_mode[tk->ply_turn][tk->ply_act_kawa_count[tk->ply_turn]-1] + HAI_COLOR_NUM_BLUE;
			}

			// 鳴き牌の算出
			tmp_naki_hai = Get_hainum(gui->wk_str[tmp_wk_num+7]);
			if (tmp_naki_hai > 100){
				tmp_naki_hai = tmp_naki_hai - 100;
			}

			// 構成牌1枚目確認
			tmp_naki_tehai_hai1 = Get_hainum(gui->wk_str[tmp_wk_num+9]);
			if (tmp_naki_tehai_hai1 > 100){
				tmp_naki_tehai_hai1 = tmp_naki_tehai_hai1 - 100;
				tmp_aka_count++;
			}

			// 構成牌2枚目確認
			tmp_naki_tehai_hai2 = Get_hainum(gui->wk_str[tmp_wk_num+10]);
			if (tmp_naki_tehai_hai2 > 100){
				tmp_naki_tehai_hai2 = tmp_naki_tehai_hai2 - 100;
				tmp_aka_count++;
			}

			// 1枚目2枚目の大小比較・交換
			if(tmp_naki_tehai_hai1 > tmp_naki_tehai_hai2){
				tmp_num = tmp_naki_tehai_hai1;
				tmp_naki_tehai_hai1 = tmp_naki_tehai_hai2;
				tmp_naki_tehai_hai2 = tmp_num;
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

			// チー牌設定
			gui->chi_idx_hai[gui->chihai_count]   = tmp_chi_idx;
			gui->chi_aka_count[gui->chihai_count] = tmp_aka_count;
			gui->chihai_count++;
		}

	} // "type"確認終了

}

/* ---------------------------------------------------------------------------------------------- */
// 捨牌のメッセージ定義
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::ActSndDahaiMes(MJSGui *gui, int ply_mjai_id, int hai, bool aka_flg, bool tsumogiri_flg){

	// 変数定義
	char tmp_hai_chr[5];

	// Mes取得準備：文字取得
	Get_haichr(hai, aka_flg, tmp_hai_chr);

	// バッファクリア
	memset(gui->snd_mes, 0, sizeof(gui->snd_mes));

	// sendメッセージ設定
	if( tsumogiri_flg == true ){
		// アクション：自摸切り
		wsprintf(gui->snd_mes, "{\"type\":\"dahai\",\"actor\":%d,\"pai\":\"%s\",\"tsumogiri\":true}\n", ply_mjai_id, tmp_hai_chr);
	}else{
		// アクション：捨牌処理
		wsprintf(gui->snd_mes, "{\"type\":\"dahai\",\"actor\":%d,\"pai\":\"%s\",\"tsumogiri\":false}\n", ply_mjai_id, tmp_hai_chr);
	}

}

/* ---------------------------------------------------------------------------------------------- */
// リーチのメッセージ定義
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::ActSndRiichiMes(MJSGui *gui, int ply_mjai_id){

	// バッファクリア
	memset(gui->snd_mes, 0, sizeof(gui->snd_mes));

	// sendメッセージ設定　アクション：リーチ
	wsprintf(gui->snd_mes, "{\"type\":\"reach\",\"actor\":%d}\n", ply_mjai_id);

}

/* ---------------------------------------------------------------------------------------------- */
// 暗槓メッセージ定義
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::ActSndAnkanMes(MJSGui *gui, int ply_mjai_id, int ankan_hai, int tehai_aka_count){

	// 変数定義
	char tmp_ankan_hai_chr[5];

	// Mes取得準備：文字取得(鳴き牌)
	Get_haichr(ankan_hai, false, tmp_ankan_hai_chr);

	// sendメッセージ設定
	if( tehai_aka_count == 0 ){
		// 赤牌なし
		wsprintf(gui->snd_mes, "{\"type\":\"ankan\",\"actor\":%d,\"consumed\":[\"%s\",\"%s\",\"%s\",\"%s\"]}\n",     ply_mjai_id, tmp_ankan_hai_chr, tmp_ankan_hai_chr, tmp_ankan_hai_chr, tmp_ankan_hai_chr);
	}else if( tehai_aka_count == 1 ){
		// 赤牌1枚
		wsprintf(gui->snd_mes, "{\"type\":\"ankan\",\"actor\":%d,\"consumed\":[\"%s\",\"%s\",\"%s\",\"%sr\"]}\n",    ply_mjai_id, tmp_ankan_hai_chr, tmp_ankan_hai_chr, tmp_ankan_hai_chr, tmp_ankan_hai_chr);
	}else if( tehai_aka_count == 2 ){
		// 赤牌2枚
		wsprintf(gui->snd_mes, "{\"type\":\"ankan\",\"actor\":%d,\"consumed\":[\"%s\",\"%s\",\"%sr\",\"%sr\"]}\n",   ply_mjai_id, tmp_ankan_hai_chr, tmp_ankan_hai_chr, tmp_ankan_hai_chr, tmp_ankan_hai_chr);
	}else if( tehai_aka_count == 3 ){
		// 赤牌3枚
		wsprintf(gui->snd_mes, "{\"type\":\"ankan\",\"actor\":%d,\"consumed\":[\"%s\",\"%sr\",\"%sr\",\"%sr\"]}\n",  ply_mjai_id, tmp_ankan_hai_chr, tmp_ankan_hai_chr, tmp_ankan_hai_chr, tmp_ankan_hai_chr);
	}else if( tehai_aka_count == 4 ){
		// 赤牌4枚
		wsprintf(gui->snd_mes, "{\"type\":\"ankan\",\"actor\":%d,\"consumed\":[\"%sr\",\"%sr\",\"%sr\",\"%sr\"]}\n", ply_mjai_id, tmp_ankan_hai_chr, tmp_ankan_hai_chr, tmp_ankan_hai_chr, tmp_ankan_hai_chr);
	}

}

/* ---------------------------------------------------------------------------------------------- */
// 加槓メッセージ定義
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::ActSndkakanMes(MJSGui *gui, int ply_mjai_id, int naki_hai, bool naki_aka, int tehai_aka_count){

	// 変数定義
	char tmp_kakan_hai_chr[5];

	// Mes取得準備：文字取得(鳴き牌)
	Get_haichr(naki_hai, false, tmp_kakan_hai_chr);

	// sendメッセージ設定
	if( naki_aka == true ){

		// Act牌が赤牌
		if( tehai_aka_count == 0 ){
			// 赤牌なし
			wsprintf(gui->snd_mes, "{\"type\":\"kakan\",\"actor\":%d,\"pai\":\"%sr\",\"consumed\":[\"%s\",\"%s\",\"%s\"]}\n",    ply_mjai_id, tmp_kakan_hai_chr, tmp_kakan_hai_chr, tmp_kakan_hai_chr, tmp_kakan_hai_chr);
		}else if( tehai_aka_count == 1 ){
			// 赤牌3枚
			wsprintf(gui->snd_mes, "{\"type\":\"kakan\",\"actor\":%d,\"pai\":\"%sr\",\"consumed\":[\"%s\",\"%s\",\"%sr\"]}\n",   ply_mjai_id, tmp_kakan_hai_chr, tmp_kakan_hai_chr, tmp_kakan_hai_chr, tmp_kakan_hai_chr);
		}else if( tehai_aka_count == 2 ){
			// 赤牌3枚
			wsprintf(gui->snd_mes, "{\"type\":\"kakan\",\"actor\":%d,\"pai\":\"%sr\",\"consumed\":[\"%s\",\"%sr\",\"%sr\"]}\n",  ply_mjai_id, tmp_kakan_hai_chr, tmp_kakan_hai_chr, tmp_kakan_hai_chr, tmp_kakan_hai_chr);
		}else if( tehai_aka_count == 3 ){
			// 赤牌3枚
			wsprintf(gui->snd_mes, "{\"type\":\"kakan\",\"actor\":%d,\"pai\":\"%sr\",\"consumed\":[\"%sr\",\"%sr\",\"%sr\"]}\n", ply_mjai_id, tmp_kakan_hai_chr, tmp_kakan_hai_chr, tmp_kakan_hai_chr, tmp_kakan_hai_chr);
		}

	}else{

		// Act牌が黒牌
		if( tehai_aka_count == 0 ){
			// 赤牌なし
			wsprintf(gui->snd_mes, "{\"type\":\"kakan\",\"actor\":%d,\"pai\":\"%s\",\"consumed\":[\"%s\",\"%s\",\"%s\"]}\n",     ply_mjai_id, tmp_kakan_hai_chr, tmp_kakan_hai_chr, tmp_kakan_hai_chr, tmp_kakan_hai_chr);
		}else if( tehai_aka_count == 1 ){
			// 赤牌3枚
			wsprintf(gui->snd_mes, "{\"type\":\"kakan\",\"actor\":%d,\"pai\":\"%s\",\"consumed\":[\"%s\",\"%s\",\"%sr\"]}\n",    ply_mjai_id, tmp_kakan_hai_chr, tmp_kakan_hai_chr, tmp_kakan_hai_chr, tmp_kakan_hai_chr);
		}else if( tehai_aka_count == 2 ){
			// 赤牌3枚
			wsprintf(gui->snd_mes, "{\"type\":\"kakan\",\"actor\":%d,\"pai\":\"%s\",\"consumed\":[\"%s\",\"%sr\",\"%sr\"]}\n",   ply_mjai_id, tmp_kakan_hai_chr, tmp_kakan_hai_chr, tmp_kakan_hai_chr, tmp_kakan_hai_chr);
		}else if( tehai_aka_count == 3 ){
			// 赤牌3枚
			wsprintf(gui->snd_mes, "{\"type\":\"kakan\",\"actor\":%d,\"pai\":\"%s\",\"consumed\":[\"%sr\",\"%sr\",\"%sr\"]}\n",  ply_mjai_id, tmp_kakan_hai_chr, tmp_kakan_hai_chr, tmp_kakan_hai_chr, tmp_kakan_hai_chr);
		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 和了(ロン・ツモ)メッセージ定義
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::ActSndHoraMes(MJSGui *gui, int ply_mjai_id, int ply_target, int agari_hai, bool agari_aka){

	// 変数定義
	char tmp_hai_chr[5];

	// Mes取得準備：文字取得
	Get_haichr(agari_hai, agari_aka, tmp_hai_chr);

	// バッファクリア
	memset(gui->snd_mes, 0, sizeof(gui->snd_mes));

	// sendメッセージ設定
	wsprintf(gui->snd_mes, "{\"type\":\"hora\",\"actor\":%d,\"target\":%d,\"pai\":\"%s\"}\n", ply_mjai_id, ply_target, tmp_hai_chr);

}

/* ---------------------------------------------------------------------------------------------- */
// ポンメッセージ定義
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::ActSndPonMes(MJSGui *gui, int ply_mjai_id, int ply_target, int nakl_hai, bool nakl_aka, int tehai_aka_count){

	// 変数定義
	char tmp_naki_hai_chr[5];
	char tmp_tehai_chr[5];

	// Mes取得準備：文字取得(鳴き牌)
	Get_haichr(nakl_hai, nakl_aka, tmp_naki_hai_chr);

	// Mes取得準備：文字取得(手牌)
	Get_haichr(nakl_hai, false, tmp_tehai_chr);

	// sendメッセージ設定
	if( tehai_aka_count == 0 ){
		// 赤牌なし
		wsprintf(gui->snd_mes, "{\"type\":\"pon\",\"actor\":%d,\"target\":%d,\"pai\":\"%s\",\"consumed\":[\"%s\",\"%s\"]}\n",   ply_mjai_id, ply_target, tmp_naki_hai_chr, tmp_tehai_chr, tmp_tehai_chr);
	}else if( tehai_aka_count == 1 ){
		// 赤牌1枚
		wsprintf(gui->snd_mes, "{\"type\":\"pon\",\"actor\":%d,\"target\":%d,\"pai\":\"%s\",\"consumed\":[\"%s\",\"%sr\"]}\n",  ply_mjai_id, ply_target, tmp_naki_hai_chr, tmp_tehai_chr, tmp_tehai_chr);
	}else if( tehai_aka_count == 2 ){
		// 赤牌2枚
		wsprintf(gui->snd_mes, "{\"type\":\"pon\",\"actor\":%d,\"target\":%d,\"pai\":\"%s\",\"consumed\":[\"%sr\",\"%sr\"]}\n", ply_mjai_id, ply_target, tmp_naki_hai_chr, tmp_tehai_chr, tmp_tehai_chr);
	}

}

/* ---------------------------------------------------------------------------------------------- */
// チーメッセージ定義
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::ActSndChiMes(MJSGui *gui, int ply_mjai_id, int ply_target, int nakl_hai, bool nakl_aka, int naki_idx, int tehai_aka_count){

	// 変数定義
	char tmp_hai_chr[5];
	int tmp_chi_count = 0;

	// バッファクリア
	// memset(gui->snd_mes, 0, sizeof(gui->snd_mes));

	// sendメッセージ設定(デバグ用)
	// wsprintf(gui->snd_mes, "{\"type\":\"chi\",\"actor\":%d,\"target\":%d,\"pai\":\"%s\"}\n", ply_mjai_id, ply_target, tmp_hai_chr);

	// Mes取得準備：文字取得(鳴き牌)
	Get_haichr(nakl_hai, nakl_aka, tmp_hai_chr);

	// メッセージ設定(ヘッダー)
	wsprintf(gui->snd_mes, "{\"type\":\"chi\",\"actor\":%d,\"target\":%d,\"pai\":\"%s\",\"consumed\":[", ply_mjai_id, ply_target, tmp_hai_chr);

	// チー牌設定
	for(int tmp_i=0; tmp_i < 3; tmp_i++){

		// 鳴き牌でないなら
		if( nakl_hai != naki_idx + tmp_i ){
			// チーの仮枚数
			tmp_chi_count++;
			// Mes取得準備：文字取得(赤牌確認)
			if(( naki_idx + tmp_i == MAN5NUM || 
		         naki_idx + tmp_i == PIN5NUM || 
		         naki_idx + tmp_i == SOU5NUM )&& (tehai_aka_count > 0)){
				Get_haichr(naki_idx + tmp_i, true, tmp_hai_chr);
			}else{
				Get_haichr(naki_idx + tmp_i, false, tmp_hai_chr);
			}
			// 鳴きメッセージ作成
			wsprintf(gui->snd_mes, "%s\"%s\"", gui->snd_mes, tmp_hai_chr);
			// 最後でないなら、カンマ追加
			if(tmp_chi_count != 2){
				wsprintf(gui->snd_mes, "%s,", gui->snd_mes);
			}
		}
	}

	// メッセージ設定(フッター)
	wsprintf(gui->snd_mes, "%s]}\n", gui->snd_mes);

}

/* ---------------------------------------------------------------------------------------------- */
// ミンカンメッセージ定義
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::ActSndMinkanMes(MJSGui *gui, int ply_mjai_id, int ply_target, int nakl_hai, bool nakl_aka, int tehai_aka_count){

	// 変数定義
	char tmp_naki_hai_chr[5];
	char tmp_tehai_chr[5];

	// Mes取得準備：文字取得(鳴き牌)
	Get_haichr(nakl_hai, nakl_aka, tmp_naki_hai_chr);

	// Mes取得準備：文字取得(手牌)
	Get_haichr(nakl_hai, false, tmp_tehai_chr);

	// sendメッセージ設定
	if( tehai_aka_count == 0 ){
		// 赤牌なし
		wsprintf(gui->snd_mes, "{\"type\":\"daiminkan\",\"actor\":%d,\"target\":%d,\"pai\":\"%s\",\"consumed\":[\"%s\",\"%s\",\"%s\"]}\n",   ply_mjai_id, ply_target, tmp_naki_hai_chr, tmp_tehai_chr, tmp_tehai_chr, tmp_tehai_chr);
	}else if( tehai_aka_count == 1 ){
		// 赤牌1枚
		wsprintf(gui->snd_mes, "{\"type\":\"daiminkan\",\"actor\":%d,\"target\":%d,\"pai\":\"%s\",\"consumed\":[\"%s\",\"%s\",\"%sr\"]}\n",  ply_mjai_id, ply_target, tmp_naki_hai_chr, tmp_tehai_chr, tmp_tehai_chr, tmp_tehai_chr);
	}else if( tehai_aka_count == 2 ){
		// 赤牌1枚
		wsprintf(gui->snd_mes, "{\"type\":\"daiminkan\",\"actor\":%d,\"target\":%d,\"pai\":\"%s\",\"consumed\":[\"%s\",\"%sr\",\"%sr\"]}\n",  ply_mjai_id, ply_target, tmp_naki_hai_chr, tmp_tehai_chr, tmp_tehai_chr, tmp_tehai_chr);
	}else if( tehai_aka_count == 3 ){
		// 赤牌2枚
		wsprintf(gui->snd_mes, "{\"type\":\"daiminkan\",\"actor\":%d,\"target\":%d,\"pai\":\"%s\",\"consumed\":[\"%sr\",\"%sr\",\"%sr\"]}\n", ply_mjai_id, ply_target, tmp_naki_hai_chr, tmp_tehai_chr, tmp_tehai_chr, tmp_tehai_chr);
	}

}

/* ---------------------------------------------------------------------------------------------- */
// 処理なしメッセージ定義
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::ActSndNoneMes(MJSGui *gui){

	// sendメッセージ設定
	wsprintf(gui->snd_mes, res_none);

}

/* ---------------------------------------------------------------------------------------------- */
// 牌番号取得
/* ---------------------------------------------------------------------------------------------- */
int MJSMjaiClient::Get_hainum(char hai_str[]){

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

/* ---------------------------------------------------------------------------------------------- */
// 牌文字取得
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::Get_haichr(int hai_num, bool hai_aka, char hai_str[]){

	// 字牌処理
	if(hai_num > 30){

		if(hai_num == 31){
			wsprintf(hai_str, "E");
		}else if(hai_num == 32){
			wsprintf(hai_str, "S");
		}else if(hai_num == 33){
			wsprintf(hai_str, "W");
		}else if(hai_num == 34){
			wsprintf(hai_str, "N");
		}else if(hai_num == 35){
			wsprintf(hai_str, "P");
		}else if(hai_num == 36){
			wsprintf(hai_str, "F");
		}else if(hai_num == 37){
			wsprintf(hai_str, "C");
		}else{
			wsprintf(hai_str, "-");
		}

	}else if (hai_num > 0 && hai_num < 10){
		if(hai_aka==true){
			wsprintf(hai_str, "%dmr", hai_num%10);
		}else{
			wsprintf(hai_str, "%dm" , hai_num%10);
		}
	}else if (hai_num > 10 && hai_num < 20){
		if(hai_aka==true){
			wsprintf(hai_str, "%dpr", hai_num%10);
		}else{
			wsprintf(hai_str, "%dp" , hai_num%10);
		}
	}else if (hai_num > 20 && hai_num < 30){
		if(hai_aka==true){
			wsprintf(hai_str, "%dsr", hai_num%10);
		}else{
			wsprintf(hai_str, "%ds" , hai_num%10);
		}
	}

}

/* ---------------------------------------------------------------------------------------------- */
// 卓アクションのログ出力
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::Output_Actionlog(MJSTkinfo *tk, int kyoku_index){

		// ヘッダー表示
		wsprintf(clientlog_buf, "ACT_ID:%d", tk->kyoku[kyoku_index].act_count);

		// アクション表示
		if ( tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count] == PLYNOACT){
			wsprintf(clientlog_buf, "%s 定義なし", clientlog_buf);
		}else if( tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count] == HAIPAI){
			wsprintf(clientlog_buf, "%s 配牌　　", clientlog_buf);
		}else if( tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count] == PLYACTTSUMO){
			wsprintf(clientlog_buf, "%s 自摸　　", clientlog_buf);
		}else if( tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count] == PLYRINSHAN){
			wsprintf(clientlog_buf, "%s 嶺上自摸", clientlog_buf);
		}else if( tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count] == PLYACTSUTE){
			wsprintf(clientlog_buf, "%s 捨牌　　", clientlog_buf);
		}else if( tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count] == PLYACTTSUMOGIRI){
			wsprintf(clientlog_buf, "%s 自摸切り", clientlog_buf);
		}else if( tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count] == PLYACTPON){
			wsprintf(clientlog_buf, "%s ポン　　", clientlog_buf);
		}else if( tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count] == PLYACTANKAN){
			wsprintf(clientlog_buf, "%s 暗槓　　", clientlog_buf);
		}else if( tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count] == PLYACTMINKAN){
			wsprintf(clientlog_buf, "%s 明槓　　", clientlog_buf);
		}else if( tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count] == PLYACTKAKAN){
			wsprintf(clientlog_buf, "%s 加槓　　", clientlog_buf);
		}else if( tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count] == PLYACTCHI){
			wsprintf(clientlog_buf, "%s チー　　", clientlog_buf);
		}else if( tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count] == PLYACTRIICH){
			wsprintf(clientlog_buf, "%s リーチ　", clientlog_buf);
		}else if( tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count] == PLYTSUMOAGARI){
			wsprintf(clientlog_buf, "%s 自摸和了", clientlog_buf);
		}else if( tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count] == PLYACTRON){
			wsprintf(clientlog_buf, "%s ロン和了", clientlog_buf);
		}else if( tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count] == RYUKYOKU){
			wsprintf(clientlog_buf, "%s 流局　　", clientlog_buf);
		}else if( tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count] == KYOKURESULT){
			wsprintf(clientlog_buf, "%s 局結果　", clientlog_buf);
		}else if( tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count] == KYOKUEND){
			wsprintf(clientlog_buf, "%s 局終了　", clientlog_buf);
		}else{
			wsprintf(clientlog_buf, "%s 不明　　", clientlog_buf);
		}

		// Ply情報・牌情報の追記
		wsprintf(clientlog_buf, "%s 牌番号；%d ACTプレーヤー：%d 非ACTプレーヤー：%d\n", 
		clientlog_buf,
		tk->kyoku[kyoku_index].act_hai  [tk->kyoku[kyoku_index].act_count],
		tk->kyoku[kyoku_index].act_ply  [tk->kyoku[kyoku_index].act_count], 
		tk->kyoku[kyoku_index].react_ply[tk->kyoku[kyoku_index].act_count]);

		// ログ出力
		clientlog->CorelogPrint(clientlog_buf);

		// 仕切り線
		wsprintf(clientlog_buf, "----\n");
		clientlog->CorelogPrint(clientlog_buf);

}

/* ---------------------------------------------------------------------------------------------- */
// ソース終了
/* ---------------------------------------------------------------------------------------------- */
