/* ---------------------------------------------------------------------------------------------- 
 * 
 * プログラム概要 ： さくら麻雀(Ver0.1.2：開発版)
 * バージョン     ： 0.1.2.1.225(MJAIログ表示：3プレーヤ分の役情報構造体定義)
 * プログラム名   ： mjs.exe
 * ファイル名     ： tklog.cpp
 * クラス名       ： MJSTklog
 * 処理概要       ： 卓情報ログクラス
 * 作成日         ： 2018/11/18 10:12:12
 * Ver0.0.1作成日 ： 2022/04/11 15:57:39
 * Ver0.1.2作成日 ： 2022/08/31 22:19:54
 * 最終更新日     ： 2024/11/07 19:11:07
 * 
 * Copyright (c) 2010-2024 Techmilestone, All rights reserved.
 * 
 * ---------------------------------------------------------------------------------------------- */

#include "tklog.h"

/* ---------------------------------------------------------------------------------------------- */
// ログ処理開始処理
/* ---------------------------------------------------------------------------------------------- */
void MJSTklog::tklog_init(char *logname){

	// クラス定義
	core_log = new MJSCorelog;         // コアログクラスの初期化

	// コアログ初期化
	core_log->CorelogInit(logname);

	// ファイル初期化
	tklog_file_init(logname);

}

/* ---------------------------------------------------------------------------------------------- */
// ログ処理終了処理
/* ---------------------------------------------------------------------------------------------- */
void MJSTklog::tklog_post(){

	// コアログ後処理
	core_log->CorelogPost();

	// クラス削除
	delete core_log;

	// ファイルクローズ
	tklog_file_close();

}

/* ---------------------------------------------------------------------------------------------- */
// ファイル初期化
/* ---------------------------------------------------------------------------------------------- */
void MJSTklog::tklog_file_init(char *logname){

	// ファイルポイント定義
	hFile = CreateFile( logname, GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );

	// 処理確認
	if (hFile == INVALID_HANDLE_VALUE) {
		MessageBox(NULL, "ファイル読込エラーです", "メッセージ", MB_OK);
	}

	// ポインタを一番最後にして追記書きこみ
	SetFilePointer( hFile, 0, NULL, FILE_END );

}

/* ---------------------------------------------------------------------------------------------- */
// ファイルクローズ
/* ---------------------------------------------------------------------------------------------- */
void MJSTklog::tklog_file_close(){

	// ファイルクローズ
	CloseHandle(hFile);

}

/* ---------------------------------------------------------------------------------------------- */
// ログ出力・メイン処理
/* ---------------------------------------------------------------------------------------------- */
void MJSTklog::tklog_print(char *msg){

	// 書きこみ処理開始
	WriteFile(hFile, msg, (DWORD)strlen(msg), &dwBytes, NULL);

}

/* ---------------------------------------------------------------------------------------------- */
// 空白出力
/* ---------------------------------------------------------------------------------------------- */
void MJSTklog::tklog_space(){

	wsprintf(tmp_msg, "　");
	tklog_print(tmp_msg);

}

/* ---------------------------------------------------------------------------------------------- */
// 改行出力
/* ---------------------------------------------------------------------------------------------- */
void MJSTklog::tklog_cr(){

	wsprintf(tmp_msg, "\n");
	tklog_print(tmp_msg);

}

/* ---------------------------------------------------------------------------------------------- */
// 時間出力
/* ---------------------------------------------------------------------------------------------- */
void MJSTklog::tklog_time(){

	// 関数定義 

    time_t jikan = time(NULL);
    struct tm imanojikan;
	errno_t error;

	int year, mon, day;
	int hour, min, sec;

	// 現在の日時を取得 
	error = localtime_s(&imanojikan, &jikan);

	year = imanojikan.tm_year + 1900;
	mon  = imanojikan.tm_mon  + 1;
	day  = imanojikan.tm_mday ;

	hour = imanojikan.tm_hour;
	min  = imanojikan.tm_min;
	sec  = imanojikan.tm_sec;

	wsprintf(tmp_msg,"%d/%02d/%02d %02d:%02d:%02d",year,mon,day,hour,min,sec);
	tklog_print(tmp_msg);

}

/* ---------------------------------------------------------------------------------------------- */
// MJSログ出力・メイン処理
/* ---------------------------------------------------------------------------------------------- */
void MJSTklog::tklog_print(MJSTkinfo *tk, int log_ver1, int log_ver2, int log_ver3, int log_ver4){

	// ログ開始処理
	tklog_000_MJSlogStart(log_ver1, log_ver2,log_ver3,log_ver4); // 000：MJSログ開始

	// 卓開始処理
	tklog_011_TakuStart(tk);                                     // 011：卓開始情報
	tklog_012_PlayerInfo(tk);                                    // 012：プレーヤー情報

	// 局情報
	for (int tmp_i = 0; tmp_i < tk->kyoku_index+1; tmp_i++){
		tklog_101_KyokuStart(tk, tmp_i);                         // 101：局開始
		tklog_11x_HaipaiInfo(tk, tmp_i);                         // 11x：配牌
		tklog_201_Actinfo(tk, tmp_i);                            // 201：アクション情報
		tklog_21x_Nakiinfo(tk, tmp_i);                           // 21x：鳴き情報
		tklog_901_AgariInfo(tk, tmp_i);
		tklog_902_YakuInfo(tk, tmp_i);
		tklog_903_kyokuScore(tk, tmp_i);
	}

	// 卓終了処理
	tklog_911_TakuEndScore(tk);                                  // 911：得点結果
	tklog_919_TakuEnd(tk);                                       // 919：卓終了情報

	// ログ終了処理
	tklog_999_MJSlogEnd(log_ver1, log_ver2,log_ver3,log_ver4);   // 999：MJSログ終了
	
	// 改行(ログ終了確認用の空白行)
	tklog_cr();

}

/* ---------------------------------------------------------------------------------------------- */
// 000：MJSログ開始
/* ---------------------------------------------------------------------------------------------- */
void MJSTklog::tklog_000_MJSlogStart(int log_ver1, int log_ver2, int log_ver3, int log_ver4){

	// ログ出力
	wsprintf(tmp_msg, "000 MJSlog START %d %d %d %d ", log_ver1, log_ver2, log_ver3, log_ver4);
	tklog_print(tmp_msg);

	// 時刻表示
	tklog_time();

	// 改行
	tklog_cr();

}

/* ---------------------------------------------------------------------------------------------- */
// 999：MJSログ終了
/* ---------------------------------------------------------------------------------------------- */
void MJSTklog::tklog_999_MJSlogEnd(int log_ver1, int log_ver2, int log_ver3, int log_ver4){

	// ログ出力
	wsprintf(tmp_msg, "999 MJSlog END %d %d %d %d ", log_ver1, log_ver2, log_ver3, log_ver4);
	tklog_print(tmp_msg);

	// 時刻表示
	tklog_time();

	// 改行
	tklog_cr();

}

/* ---------------------------------------------------------------------------------------------- */
// 011：卓開始
/* ---------------------------------------------------------------------------------------------- */
void MJSTklog::tklog_011_TakuStart(MJSTkinfo *tk){

	// ログ出力
	wsprintf(tmp_msg, "011 %s %s %s %s %s", tk->tkgname, tk->tkname, tk->tkno, tk->startdate, tk->starttime);
	tklog_print(tmp_msg);

	// 時刻表示
	// tklog_time();

	// 改行
	tklog_cr();

}

/* ---------------------------------------------------------------------------------------------- */
// 012：プレーヤー情報
/* ---------------------------------------------------------------------------------------------- */
void MJSTklog::tklog_012_PlayerInfo(MJSTkinfo *tk){

	// ログ出力
	wsprintf(tmp_msg, "012 %d 0 %s R1500 1 %s R1500 2 %s R1500 3 %s R1500", tk->init_score, tk->plyname[0], tk->plyname[1], tk->plyname[2], tk->plyname[3]);
	tklog_print(tmp_msg);

	// 改行
	tklog_cr();

}

/* ---------------------------------------------------------------------------------------------- */
// 101：局開始
/* ---------------------------------------------------------------------------------------------- */
void MJSTklog::tklog_101_KyokuStart(MJSTkinfo *tk, int kyoku_index){

	// ログ出力
	wsprintf(tmp_msg, "101 %d %d %d %d ", kyoku_index, tk->kyoku[kyoku_index].kyoku ,tk->kyoku[kyoku_index].tsumibo , tk->kyoku[kyoku_index].riichbo);
	tklog_print(tmp_msg);

	// 改行
	tklog_cr();

}

/* ---------------------------------------------------------------------------------------------- */
// 11x：配牌情報
/* ---------------------------------------------------------------------------------------------- */
void MJSTklog::tklog_11x_HaipaiInfo(MJSTkinfo *tk, int kyoku_index){

	// 配牌表示
	for (int tmp_ply_num = 0; tmp_ply_num < PLAYER_MAX; tmp_ply_num++){

		// ヘッダー表示
		wsprintf(tmp_msg, "11%d", tmp_ply_num+1);

		// 牌定義
		for (int tmp_i = 0; tmp_i < PAI_MAX; tmp_i++){
			for (int tmp_j = 0; tmp_j < tk->kyoku[kyoku_index].tehai[tmp_ply_num][tmp_i]; tmp_j++){
				// 牌定義
				wsprintf(tmp_msg, "%s %d", tmp_msg, tmp_i);
			}
		}

		// ログ出力
		tklog_print(tmp_msg);
		tklog_cr();

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 201：アクション情報
/* ---------------------------------------------------------------------------------------------- */
void MJSTklog::tklog_201_Actinfo(MJSTkinfo *tk, int kyoku_index){

	// act_countの仕様を理由として値を加算する
	// tk->kyoku[kyoku_index].act_count++;

	// アクション情報のログ出力
	for (int tmp_i = 0; tmp_i < tk->kyoku[kyoku_index].act_count; tmp_i++){

		// ヘッダー表示
		wsprintf(tmp_msg, "201 %d", tmp_i);

		// アクション表示
		if ( tk->kyoku[kyoku_index].act_stat[tmp_i] == HAIPAI){
			wsprintf(tmp_msg, "%s 配牌　　", tmp_msg);
		}else if( tk->kyoku[kyoku_index].act_stat[tmp_i] == PLYACTTSUMO){
			wsprintf(tmp_msg, "%s 自摸　　", tmp_msg);
		}else if( tk->kyoku[kyoku_index].act_stat[tmp_i] == PLYACTSUTE){
			wsprintf(tmp_msg, "%s 捨牌　　", tmp_msg);
		}else if( tk->kyoku[kyoku_index].act_stat[tmp_i] == PLYACTTSUMOGIRI){
			wsprintf(tmp_msg, "%s 自摸切り", tmp_msg);
		}else if( tk->kyoku[kyoku_index].act_stat[tmp_i] == PLYACTPON){
			wsprintf(tmp_msg, "%s ポン　　", tmp_msg);
		}else if( tk->kyoku[kyoku_index].act_stat[tmp_i] == PLYACTANKAN){
			wsprintf(tmp_msg, "%s 暗槓　　", tmp_msg);
		}else if( tk->kyoku[kyoku_index].act_stat[tmp_i] == PLYACTMINKAN){
			wsprintf(tmp_msg, "%s 明槓　　", tmp_msg);
		}else if( tk->kyoku[kyoku_index].act_stat[tmp_i] == PLYACTKAKAN){
			wsprintf(tmp_msg, "%s 加槓　　", tmp_msg);
		}else if( tk->kyoku[kyoku_index].act_stat[tmp_i] == PLYACTCHI){
			wsprintf(tmp_msg, "%s チー　　", tmp_msg);
		}else if( tk->kyoku[kyoku_index].act_stat[tmp_i] == PLYACTRIICH){
			wsprintf(tmp_msg, "%s リーチ　", tmp_msg);
		}else if( tk->kyoku[kyoku_index].act_stat[tmp_i] == PLYTSUMOAGARI){
			wsprintf(tmp_msg, "%s 自摸和了", tmp_msg);
		}else if( tk->kyoku[kyoku_index].act_stat[tmp_i] == PLYACTRON){
			wsprintf(tmp_msg, "%s ロン和了", tmp_msg);
		}else if( tk->kyoku[kyoku_index].act_stat[tmp_i] == RYUKYOKU){
			wsprintf(tmp_msg, "%s 流局　　", tmp_msg);
		}else if( tk->kyoku[kyoku_index].act_stat[tmp_i] == KYOKURESULT){
			wsprintf(tmp_msg, "%s 局結果　", tmp_msg);
		}else if( tk->kyoku[kyoku_index].act_stat[tmp_i] == KYOKUEND){
			wsprintf(tmp_msg, "%s 局終了　", tmp_msg);
		}else{
			wsprintf(tmp_msg, "%s 不明　　", tmp_msg);
		}

		// Ply情報・牌情報の追記
		wsprintf(tmp_msg, "%s %d %d %d", tmp_msg, tk->kyoku[kyoku_index].act_ply[tmp_i], tk->kyoku[kyoku_index].react_ply[tmp_i], tk->kyoku[kyoku_index].act_hai[tmp_i]);

		// ログ出力
		tklog_print(tmp_msg);
		tklog_cr();

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 21x：鳴き情報
/* ---------------------------------------------------------------------------------------------- */
void MJSTklog::tklog_21x_Nakiinfo(MJSTkinfo *tk, int kyoku_index){

	// 鳴き表示
	for (int tmp_ply_num = 0; tmp_ply_num < PLAYER_MAX; tmp_ply_num++){

		// 鳴き枚数の確認
		if(tk->kyoku[kyoku_index].naki_count[tmp_ply_num] == 0){

			// 0枚表示
			wsprintf(tmp_msg, "21%d 0 無し 0 0 0 0", tmp_ply_num+1);

			// ログ出力
			tklog_print(tmp_msg);
			tklog_cr();

		}else{

			// 複数表示
			for (int tmp_i = 0; tmp_i < tk->kyoku[kyoku_index].naki_count[tmp_ply_num]; tmp_i++){

				// ヘッダー表示
				wsprintf(tmp_msg, "21%d %d", tmp_ply_num, tmp_i);

				// メンツ情報
				if ( tk->kyoku[kyoku_index]. naki_stat[tmp_ply_num][tmp_i] == MINSHUN){
					wsprintf(tmp_msg, "%s 明順", tmp_msg);
				}else if( tk->kyoku[kyoku_index]. naki_stat[tmp_ply_num][tmp_i] == MINKO){
					wsprintf(tmp_msg, "%s 明刻", tmp_msg);
				}else if( tk->kyoku[kyoku_index]. naki_stat[tmp_ply_num][tmp_i] == ANKAN){
					wsprintf(tmp_msg, "%s 暗槓", tmp_msg);
				}else if( tk->kyoku[kyoku_index]. naki_stat[tmp_ply_num][tmp_i] == MINKAN){
					wsprintf(tmp_msg, "%s 明槓", tmp_msg);
				}else if( tk->kyoku[kyoku_index]. naki_stat[tmp_ply_num][tmp_i] == KAKAN){
					wsprintf(tmp_msg, "%s 加槓", tmp_msg);
				}else{
					wsprintf(tmp_msg, "%s 不明　　", tmp_msg);
				}

				// 牌情報
				wsprintf(tmp_msg, "%s %d %d %d %d", tmp_msg, tk->kyoku[kyoku_index].naki_actid[tmp_ply_num][tmp_i], tk->kyoku[kyoku_index].naki_hai[tmp_ply_num][tmp_i], tk->kyoku[kyoku_index].naki_idx[tmp_ply_num][tmp_i], tk->kyoku[kyoku_index].naki_aka[tmp_ply_num][tmp_i]);

				// ログ出力
				tklog_print(tmp_msg);
				tklog_cr();

			}

		}

	}

	// 鳴き枚数表示
	wsprintf(tmp_msg, "215 %d %d %d %d", tk->kyoku[kyoku_index].naki_count[0], tk->kyoku[kyoku_index].naki_count[1], tk->kyoku[kyoku_index].naki_count[2], tk->kyoku[kyoku_index].naki_count[3]);

	// ログ出力
	tklog_print(tmp_msg);
	tklog_cr();

}

/* ---------------------------------------------------------------------------------------------- */
// 901：和了情報
/* ---------------------------------------------------------------------------------------------- */
void MJSTklog::tklog_901_AgariInfo(MJSTkinfo *tk, int kyoku_index){

}

/* ---------------------------------------------------------------------------------------------- */
// 902：役情報
/* ---------------------------------------------------------------------------------------------- */
void MJSTklog::tklog_902_YakuInfo(MJSTkinfo *tk, int kyoku_index){
/*
	// 局得点情報
	for (int tmp_i = 0; tmp_i < tk->kyoku[kyoku_index].ply_agari_yk[tk->kyoku[kyoku_index].agari_ply_count].yakucount; tmp_i++){

		// 役表示
		wsprintf(tmp_msg, "902 %s", tk->kyoku[kyoku_index].yakuname[tmp_i]);

		// ログ出力
		tklog_print(tmp_msg);
		tklog_cr();

	}
*/
}

/* ---------------------------------------------------------------------------------------------- */
// 903：局の合計得点
/* ---------------------------------------------------------------------------------------------- */
void MJSTklog::tklog_903_kyokuScore(MJSTkinfo *tk, int kyoku_index){

	// ヘッダー表示
	wsprintf(tmp_msg, "903");

	// 局得点情報
	for (int tmp_ply_num = 0; tmp_ply_num < PLAYER_MAX; tmp_ply_num++){
			wsprintf(tmp_msg, "%s %d %d", tmp_msg, tmp_ply_num, tk->kyoku[kyoku_index].ply_agari_yk[tk->kyoku[kyoku_index].agari_ply_count].kyoku_score[tmp_ply_num]);
	}

	// ログ出力
	tklog_print(tmp_msg);
	tklog_cr();

}

/* ---------------------------------------------------------------------------------------------- */
// 911：得点結果
/* ---------------------------------------------------------------------------------------------- */
void MJSTklog::tklog_911_TakuEndScore(MJSTkinfo *tk){

	// ヘッダー表示
	wsprintf(tmp_msg, "911");

	// 局得点情報
	for (int tmp_ply_num = 0; tmp_ply_num < PLAYER_MAX; tmp_ply_num++){
		wsprintf(tmp_msg, "%s %d %d", tmp_msg, tk->plyjun[tmp_ply_num], tk->plyEndscore[tmp_ply_num]);
	}

	// ログ出力
	tklog_print(tmp_msg);
	tklog_cr();

}

/* ---------------------------------------------------------------------------------------------- */
// 919：卓終了
/* ---------------------------------------------------------------------------------------------- */
void MJSTklog::tklog_919_TakuEnd(MJSTkinfo *tk){

	// ログ出力
	wsprintf(tmp_msg, "919 %s %s %s %s %s", tk->tkgname, tk->tkname, tk->tkno, tk->enddate, tk->endtime);
	tklog_print(tmp_msg);

	// 時刻表示
	// tklog_time();

	// 改行
	tklog_cr();

}

/* ---------------------------------------------------------------------------------------------- */
// ソース終了
/* ---------------------------------------------------------------------------------------------- */
