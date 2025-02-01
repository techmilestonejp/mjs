/* ---------------------------------------------------------------------------------------------- 
 * 
 * プログラム概要 ： Newさくら麻雀(MJAIクライアント実装版)
 * バージョン     ： 0.1.2.1.229(東風荘ログ読み込み処理修正)
 * プログラム名   ： mjs.exe
 * ファイル名     ： tpread.cpp
 * クラス名       ： MJSReadTplog
 * 処理概要       ： 東風荘ログ読み込みクラス
 * Ver0.1.0作成日 ： 2022/04/11 15:57:39
 * Ver0.1.1作成日 ： 2022/05/14 22:27:08
 * Ver0.1.2作成日 ： 2022/08/31 22:19:54
 * 最終更新日     ： 2024/11/17 16:53:23
 * 
 * Copyright (c) 2010-2022 Techmilestone, All rights reserved.
 * 
 * ---------------------------------------------------------------------------------------------- */

#include "tpread.h"

/* ---------------------------------------------------------------------------------------------- */
// 初期化処理
/* ---------------------------------------------------------------------------------------------- */
void MJSReadTplog::TpreadInit(MJSGui *gui){

	// ----------------------------------------
	// 値の初期化
	// ----------------------------------------
	wk_str_count = 0;

	// ----------------------------------------
	// malloc定義
	// ----------------------------------------

	// malloc定義(構造体本体)
	wk_str = (char**)malloc(sizeof(char*) * MJSCORE_WORK_COL);

	// malloc定義(構造体の各要素)
	for(int i = 0; i < MJSCORE_WORK_COL; i++){
		wk_str[i] = (char*)malloc(sizeof(char) * MJSCORE_WORK_BUF);
	}

	// ----------------------------------------
	// ファイル初期化
	// ----------------------------------------

	// ファイル名
	// char fname[] = "mjscore.txt";

	// C11で導入　VisualC++2012以降ではこちらのみ使用可能
	errno_t err;                        // errno_t型(int型)

	// fopen処理
	// err = fopen_s(&fp, fname, "r");     // ファイルを開く。失敗するとエラーコードを返す。
	err = fopen_s(&fp, gui->log_name_mjsocre, "r");     // ファイルを開く。失敗するとエラーコードを返す。
	if(err != 0) {
		MessageBox(NULL, "fopen失敗", "失敗", MB_OK);
	} 

}

/* ---------------------------------------------------------------------------------------------- */
// 後処理
/* ---------------------------------------------------------------------------------------------- */
void MJSReadTplog::TpreadPost(){

	// ----------------------------------------
	// free定義
	// ----------------------------------------

	// free定義
	for(int i = 0; i < MJSCORE_WORK_COL; i++){
		free(wk_str[i]);
	}

	// free定義
	free(wk_str);

	// ----------------------------------------
	// ファイルクローズ
	// ----------------------------------------

	// ファイルクローズ
	fclose(fp); 

}

/* ---------------------------------------------------------------------------------------------- */
// 読み込み実行処理
/* ---------------------------------------------------------------------------------------------- */
void MJSReadTplog::TpreadExec(MJSTkinfo *tk){

	// Mjscore読み込み処理
	Read_mjscore();

	// Tkinfo設定処理
	Set_tkinfo(tk);

}

/* ---------------------------------------------------------------------------------------------- */
// mjscoreの読み込み
/* ---------------------------------------------------------------------------------------------- */
void MJSReadTplog::Read_mjscore(){

	// ----------------------------------------
	// 初期化
	// ----------------------------------------

	// バッファ定義
	char fgets_buf[MJSCORE_FGET_BUF];   //  fgetsの1行読み込み用
	int  fgets_buf_point;               //  fgetのバッファの位置取り

	// 読み込み文字定義用
	char tmp_wk_str[MJSCORE_WORK_BUF];  //  1ワードのバッファ用
	char tmp_buf[3];                    //  分割処理用

	// 空白確認フラグ
	int space_flg;                      // 0：文字なし(空白スペースのみ) 1：空白以外の文字列

	// ----------------------------------------
	// fgets処理
	// ----------------------------------------
	while( fgets( fgets_buf, MJSCORE_FGET_BUF, fp) != NULL) {

		// 値の初期化
		fgets_buf_point = 0;
		space_flg = 0;              // 「空白」「改行」以外の半角文字を読込んだ場合は、「space_flg = 1」とする。
		wsprintf(tmp_wk_str, "");   

		/* ---------------------------------------- */
		// fgetで取得した文字列を行末まで確認する
		/* ---------------------------------------- */
	    while( fgets_buf[fgets_buf_point] != '\0' ){

			// 全角・半角の判定
			if(_ismbblead(fgets_buf[fgets_buf_point])){

				/* ---------------------------------------- */
				// 全角文字の格納
				/* ---------------------------------------- */
				tmp_buf[0] = fgets_buf[fgets_buf_point];
				tmp_buf[1] = fgets_buf[fgets_buf_point+1];
				tmp_buf[2] = '\0';
				fgets_buf_point+=2;

				// 全角文字処理
				space_flg = 1;
				wsprintf(tmp_wk_str, "%s%s", tmp_wk_str, tmp_buf);

			}else{

				/* ---------------------------------------- */
				// 半角文字の格納
				/* ---------------------------------------- */
				tmp_buf[0] = fgets_buf[fgets_buf_point];
				tmp_buf[1] = '\0';
				fgets_buf_point++;

				/* ---------------------------------------- */
				// 文字抽出(空白)
				/* ---------------------------------------- */
				if ( strcmp(tmp_buf, " " ) == 0 ){

					// 「空白区切り」で文字を追記
					if(space_flg == 1){
						space_flg = 0;

						// wk構造体に一時データを格納、その後tmp_wk_strは初期化
						Set_wk(tmp_wk_str);
						wsprintf(tmp_wk_str, "");

					}

				/* ---------------------------------------- */
				// 文字抽出(改行)
				/* ---------------------------------------- */
				}else if(strcmp(tmp_buf, "\n") == 0){

					// 「空白区切り」で文字を追記
					if(space_flg == 1){
						space_flg = 0;

						// wk構造体に一時データを格納、その後tmp_wk_strは初期化
						Set_wk(tmp_wk_str);
						wsprintf(tmp_wk_str, "");

					}

					// 「改行区切り」処理の場合は、間に「+」文字を挿入する
					wsprintf(tmp_wk_str, "+");
					Set_wk(tmp_wk_str);
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

}

/* ---------------------------------------------------------------------------------------------- */
// wk構造体に一時データを格納
/* ---------------------------------------------------------------------------------------------- */
void MJSReadTplog::Set_wk(char* str){

	wsprintf(wk_str[wk_str_count], "%s", str);
	wk_str_count ++;

}

/* ---------------------------------------------------------------------------------------------- */
// 牌番号確認処理
/* ---------------------------------------------------------------------------------------------- */
int MJSReadTplog::Chk_painum(char* str){

	// 牌番号設定
	int hainum = 0;

	// 文字処理用
	char tmp_str[10];
	char tmp_hai_str_init[3];
	char tmp_hai_str_post[3];

	// 作業用変数に代入
	wsprintf(tmp_str, "%s", str);

	// 全角・半角の判定
	if(_ismbblead(tmp_str[0])){

		// 文字抽出(全角)
		if(      strcmp( tmp_str, "東" ) == 0){
			hainum = 31;
		}else if(strcmp( tmp_str, "南" ) == 0){
			hainum = 32;
		}else if(strcmp( tmp_str, "西" ) == 0){
			hainum = 33;
		}else if(strcmp( tmp_str, "北" ) == 0){
			hainum = 34;
		}else if(strcmp( tmp_str, "白" ) == 0){
			hainum = 35;
		}else if(strcmp( tmp_str, "発" ) == 0){
			hainum = 36;
		}else if(strcmp( tmp_str, "中" ) == 0){
			hainum = 37;
		}else{
			hainum = 0;
		}

	}else{

		// 半角文字の場合の前半
		tmp_hai_str_init[0] = tmp_str[0];
		tmp_hai_str_init[1] = '\0';

		// 半角文字の場合の後半
		tmp_hai_str_post[0] = tmp_str[1];
		tmp_hai_str_post[1] = '\0';

		// 文字抽出(半角_前半分)
		if(      strcmp( tmp_hai_str_init, "1" ) == 0){
			hainum = 1;
		}else if(strcmp( tmp_hai_str_init, "2" ) == 0){
			hainum = 2;
		}else if(strcmp( tmp_hai_str_init, "3" ) == 0){
			hainum = 3;
		}else if(strcmp( tmp_hai_str_init, "4" ) == 0){
			hainum = 4;
		}else if(strcmp( tmp_hai_str_init, "5" ) == 0){
			hainum = 5;
		}else if(strcmp( tmp_hai_str_init, "6" ) == 0){
			hainum = 6;
		}else if(strcmp( tmp_hai_str_init, "7" ) == 0){
			hainum = 7;
		}else if(strcmp( tmp_hai_str_init, "8" ) == 0){
			hainum = 8;
		}else if(strcmp( tmp_hai_str_init, "9" ) == 0){
			hainum = 9;
		}else{
			hainum = 0;
		}

		// 文字抽出(半角_後半分)
		if(      strcmp( tmp_hai_str_post, "m" ) == 0){

		}else if(strcmp( tmp_hai_str_post, "M" ) == 0){
			hainum = hainum + 100;
		}else if(strcmp( tmp_hai_str_post, "p" ) == 0){
			hainum = hainum + 10;
		}else if(strcmp( tmp_hai_str_post, "P" ) == 0){
			hainum = hainum + 110;
		}else if(strcmp( tmp_hai_str_post, "s" ) == 0){
			hainum = hainum + 20;
		}else if(strcmp( tmp_hai_str_post, "S" ) == 0){
			hainum = hainum + 120;
		}else{
			hainum = 0;
		}

	}

	return hainum;

}

/* ---------------------------------------------------------------------------------------------- */
// ドラ表示確認
/* ---------------------------------------------------------------------------------------------- */
int MJSReadTplog::Chk_DoraHyoji(int hai){

	return 0;

}

/* ---------------------------------------------------------------------------------------------- */
// Tkinfo設定処理：メイン処理
/* ---------------------------------------------------------------------------------------------- */
void MJSReadTplog::Set_tkinfo(MJSTkinfo *tk){

	bool chk_kyoku_mode = true ;   // 局読み込みモードの確認
	tk->kyoku_index = 0;           // 局のインデックス
	wk_index = 0;                  // 作業用構造体のインデックス

	// mjscore_read_mode = 1 ： 卓開始情報読み込み
	Set_tkinfo_tkstart(tk);

	// mjscore_read_mode = 2 ： プレーヤー情報読み込み
	Set_tkinfo_plyprof(tk);

	// 局情報の読み込み
	while(chk_kyoku_mode) {

		// mjscore_read_mode = 3 ： 局情報
		Set_tkinfo_kyoku_score(tk, tk->kyoku_index);

		// mjscore_read_mode = 4 ： 和了情報
		Set_tkinfo_agariinfo(tk, tk->kyoku_index);

		// mjscore_read_mode = 5 ： 配牌情報
		Set_tkinfo_haipai(tk, tk->kyoku_index);

		// mjscore_read_mode = 6 ： ドラ情報
		Set_tkinfo_dora(tk, tk->kyoku_index);

		// mjscore_read_mode = 7 ： アクション情報
		Set_tkinfo_actinfo(tk, tk->kyoku_index);

		// mjscore_read_mode = 8 ： 卓終了確認
		chk_kyoku_mode = Set_tkinfo_checkend();

		// 局インデックスを+1
		tk->kyoku_index++;

	 }

	// mjscore_read_mode = 9 ： 卓終了情報読み込み
	Set_tkinfo_tkend(tk);

}

/* ---------------------------------------------------------------------------------------------- */
// Tkinfo設定処理： mjscore_read_mode = 1 ： 卓開始情報読み込み
/* ---------------------------------------------------------------------------------------------- */
void MJSReadTplog::Set_tkinfo_tkstart(MJSTkinfo *tk){

	// INDEXを+1する。(区切り文字「===」があるため)
	wk_index++;

	// 卓名
	wsprintf(tk->tkname, "%s", wk_str[wk_index]);
	wk_index++;

	// 卓番号
	wsprintf(tk->tkno  , "%s", wk_str[wk_index]);
	wk_index++;
	wk_index++;

	// 卓開始日
	wsprintf(tk->startdate, "%s", wk_str[wk_index]);
	wk_index++;

	// 卓開始時刻
	wsprintf(tk->starttime, "%s:00", wk_str[wk_index]);
	wk_index++;

	// ゲーム名
	wsprintf(tk->tkgname, "%s", "東風荘");

}

/* ---------------------------------------------------------------------------------------------- */
// Tkinfo設定処理： mjscore_read_mode = 2 ： プレーヤー情報読み込み
/* ---------------------------------------------------------------------------------------------- */
void MJSReadTplog::Set_tkinfo_plyprof(MJSTkinfo *tk){

	// 変数定義
	char tmp_str[10];
	int i=0;
	int j=0;

	// ----------------------------------------
	// 得点情報を繰り返し読み込む
	// ----------------------------------------

	// 「wk_indexを+2する
	wk_index=wk_index+2;

	// ----------------------------------------
	// 得点情報の読み込み
	// ----------------------------------------

	// 初期得点の読み込み
	while(wk_str[wk_index][i] != '\0'){
		// 全角判定
		if(_ismbblead(wk_str[wk_index][i])){
			i+=2;
		}else{
			// 半角文字の格納
			tmp_str[j] = wk_str[wk_index][i];
			i++;
			j++;
		}
	}

	// 終了文字の挿入
	tmp_str[j] = '\0';

	// 得点の挿入
	tk->init_score = atoi(tmp_str);

	// wk_indexを+1
	wk_index++;

	// ----------------------------------------
	// プレーヤー情報の読み込み
	// ----------------------------------------

	for(int ply_i = 0; ply_i < 4; ply_i++){

		// 初期化
		i=3;  // プレーヤー名の前にある[1]は読み込まない
		j=0;
		wsprintf(tk->plyname[ply_i], "" );

		// プレーヤー名の読み込み処理
		while(wk_str[wk_index][i] != '\0'){

			// 全角判定
			if(_ismbblead(wk_str[wk_index][i])){

				// 全角文字追記
				tmp_str[0] = wk_str[wk_index][i];
				tmp_str[1] = wk_str[wk_index][i+1];
				tmp_str[2] = '\0';
				wsprintf(tk->plyname[ply_i], "%s%s", tk->plyname[ply_i], tmp_str);
				i+=2;

			}else{

				// 半角文字追記
				tmp_str[0] = wk_str[wk_index][i];
				tmp_str[1] = '\0';
				wsprintf(tk->plyname[ply_i], "%s%s", tk->plyname[ply_i], tmp_str);
				i++;
			}
		}

		// レート確認処理
		wk_index++; 

		// wk_indexを+1
		wk_index++;

	}

	// wk_indexを+1
	wk_index++;

}

/* ---------------------------------------------------------------------------------------------- */
// Tkinfo設定処理： mjscore_read_mode = 3 ： 局情報とプレーヤー得点情報
/* ---------------------------------------------------------------------------------------------- */
void MJSReadTplog::Set_tkinfo_kyoku_score(MJSTkinfo *tk, int kyoku_index){

	// ----------------------------------------
	// 初期化
	// ----------------------------------------

	// 乱数シードの初期化
	tk->kyoku[kyoku_index].seed_num = 0;

	// 局変数の初期化
	for(int tmp_ply_num = 0; tmp_ply_num < PLAYER_MAX; tmp_ply_num++){

		// 配牌
		for(int i = 0; i < PAI_MAX; i++){
			tk->kyoku[kyoku_index].tehai[tmp_ply_num][i] = 0;
		}

		// 配牌の赤数
		for(int i = 0; i < AKA_TYPE_MAX_COUNT; i++){
			tk->kyoku[kyoku_index].aka_count[tmp_ply_num][i] = 0;
		}

		// 変数定義(鳴き数)
		tk->kyoku[kyoku_index].naki_count[tmp_ply_num] = 0;

	}

	// ----------------------------------------
	// 局開始得点の設定
	// ----------------------------------------

	// 局開始得点の設定
	if(kyoku_index > 0){
		for(int ply_i = 0; ply_i < 4; ply_i++){
			tk->kyoku[kyoku_index].ply_kyoku_start_score[ply_i] = tk->kyoku[kyoku_index-1].ply_kyoku_end_score[ply_i];
		}
	}

	// ----------------------------------------
	// 局情報の読み込み
	// ----------------------------------------

	// 変数定義
	char tmp_str[10];
	int i=0;
	int j=0;
	tk->kyoku[kyoku_index].kyoku=0;

	while(wk_str[wk_index][i] != '\0'){

		// 全角判定
		if(_ismbblead(wk_str[wk_index][i])){

			// 全角文字の格納
			tmp_str[0] = wk_str[wk_index][i];
			tmp_str[1] = wk_str[wk_index][i+1];
			tmp_str[2] = '\0';
			i+=2;

			// 文字抽出(全角)
			if ( strcmp( tmp_str, "東" ) == 0){
				tk->kyoku[kyoku_index].kyoku=0;
			}else if(strcmp(tmp_str, "南") == 0){
				tk->kyoku[kyoku_index].kyoku=4;
			}

		}else{

			// 半角文字の格納
			tmp_str[0] = wk_str[wk_index][i];
			tmp_str[1] = '\0';
			i++;

			// 文字抽出(半角)
			if (strcmp( tmp_str, "1" ) == 0){
				// 処理なし
			}else if(strcmp( tmp_str, "2" ) == 0){
				tk->kyoku[kyoku_index].kyoku++;
			}else if(strcmp( tmp_str, "3" ) == 0){
				tk->kyoku[kyoku_index].kyoku+=2;
			}else if(strcmp( tmp_str, "4" ) == 0){
				tk->kyoku[kyoku_index].kyoku+=3;
			}else{
				tk->kyoku[kyoku_index].kyoku=0;
			}
		}
	}

	// wk_indexを+1
	wk_index++;

	// ----------------------------------------
	// ツミ棒情報の読み込み
	// ----------------------------------------

	// ツミ棒・リーチ棒
	tk->kyoku[kyoku_index].tsumibo = 0;
	tk->kyoku[kyoku_index].riichbo = 0;

	// wk_indexを+1
	wk_index++;

	// ----------------------------------------
	// 終局時の得点情報の読み込み
	// ----------------------------------------

	// モード設定
	int mode=0;

	// 得点初期化
	for(int ply_i = 0; ply_i < 4; ply_i++){
		tk->kyoku[kyoku_index].ply_agari_yk[0].kyoku_score[ply_i] = 0;
	}

	// 得点代入
	while(mode == 0){
		// 文字抽出(全角)
		if ( strcmp( wk_str[wk_index], "+" ) == 0){
			mode=1;
		}else if(strcmp(wk_str[wk_index], tk->plyname[0]) == 0){
			tk->kyoku[kyoku_index].ply_agari_yk[0].kyoku_score[0]=atoi(wk_str[wk_index+1]);
			wk_index++;
		}else if(strcmp(wk_str[wk_index], tk->plyname[1]) == 0){
			tk->kyoku[kyoku_index].ply_agari_yk[0].kyoku_score[1]=atoi(wk_str[wk_index+1]);
			wk_index++;
		}else if(strcmp(wk_str[wk_index], tk->plyname[2]) == 0){
			tk->kyoku[kyoku_index].ply_agari_yk[0].kyoku_score[2]=atoi(wk_str[wk_index+1]);
			wk_index++;
		}else if(strcmp(wk_str[wk_index], tk->plyname[3]) == 0){
			tk->kyoku[kyoku_index].ply_agari_yk[0].kyoku_score[3]=atoi(wk_str[wk_index+1]);
			wk_index++;
		}
		// wk_indexを+1
		wk_index++;
	}

	// 局得点の設定
	for(int ply_i = 0; ply_i < 4; ply_i++){
		tk->kyoku[kyoku_index].ply_kyoku_end_score[ply_i] = tk->kyoku[kyoku_index].ply_kyoku_start_score[ply_i] + 
		                                                    tk->kyoku[kyoku_index].ply_agari_yk[0].kyoku_score[ply_i];
	}
}

/* ---------------------------------------------------------------------------------------------- */
// Tkinfo設定処理： mjscore_read_mode = 4 ： 和了情報読み込み
/* ---------------------------------------------------------------------------------------------- */
void MJSReadTplog::Set_tkinfo_agariinfo(MJSTkinfo *tk, int kyoku_index){

	// 変数定義
	int mode = 0;
	tk->kyoku[kyoku_index].ply_agari_yk[0].yakucount = 0;

	// 役名代入
	while(mode == 0){
		// 文字列比較
		if ( strcmp( wk_str[wk_index], "+" ) == 0){
			mode = 1;
		}else{

			// 役情報の投入
			wsprintf(tk->kyoku[kyoku_index].yakuname[tk->kyoku[kyoku_index].ply_agari_yk[0].yakucount], "%s", wk_str[wk_index]);
			tk->kyoku[kyoku_index].ply_agari_yk[0].yakucount++;

		}
		// wk_indexを+1
		wk_index++;
	}

}

/* ---------------------------------------------------------------------------------------------- */
// Tkinfo設定処理： mjscore_read_mode = 5 ： 配牌情報
/* ---------------------------------------------------------------------------------------------- */
void MJSReadTplog::Set_tkinfo_haipai(MJSTkinfo *tk, int kyoku_index){

	// 配牌読み込み
	for(int ply_i = 0; ply_i < 4; ply_i++){
		Set_tkinfo_haipai_sub(tk, kyoku_index, ply_i);
		wk_index++;
		wk_index++;
	}

}


/* ---------------------------------------------------------------------------------------------- */
// Tkinfo設定処理： mjscore_read_mode = 5a ： 配牌情報(サブ処理)
/* ---------------------------------------------------------------------------------------------- */
void MJSReadTplog::Set_tkinfo_haipai_sub(MJSTkinfo *tk, int kyoku_index, int pnum){

	// ----------------------------------------
	// 初期化
	// ----------------------------------------

	// 分割処理用
	char tmp_str[3];

	// 文字読み込みポインタ
	int i=0;

	// 東風荘ログ関連の変数定義
	int ply_ie = 0;       // 家情報
	int hai_read = 0 ;    // 牌読み取りモード
	int hai_num = 0 ;     // 牌番号

	// ----------------------------------------
	// 配牌読み込み
	// ----------------------------------------

	while(wk_str[wk_index][i] != '\0'){

		// ----------------------------------------
		// hai_read = 0の処理
		// ----------------------------------------

		if(hai_read == 0){

			// 全角判定
			if(_ismbblead(wk_str[wk_index][i])){

				// 全角文字の格納
				tmp_str[0] = wk_str[wk_index][i];
				tmp_str[1] = wk_str[wk_index][i+1];
				tmp_str[2] = '\0';
				i+=2;

				// 席の確認(hai_read == 0)
				if ( strcmp( tmp_str, "東" ) == 0){
					tk->kyoku[kyoku_index].ie[ply_ie]=0;
				}else if(strcmp(tmp_str, "南") == 0){
					tk->kyoku[kyoku_index].ie[ply_ie]=1;
				}else if(strcmp(tmp_str, "西") == 0){
					tk->kyoku[kyoku_index].ie[ply_ie]=2;
				}else if(strcmp(tmp_str, "北") == 0){
					tk->kyoku[kyoku_index].ie[ply_ie]=3;
				}

			}else{

				// 半角文字の格納
				tmp_str[0] = wk_str[wk_index][i];
				tmp_str[1] = '\0';
				i++;

				// 家情報の終了
				if ( strcmp( tmp_str, "]" ) == 0){
					// モード変更
					 hai_read = 1 ;
				}else if(strcmp(tmp_str, "1") == 0){
					// 牌番号指定
					ply_ie = 0 ;
				}else if(strcmp(tmp_str, "2") == 0){
					// 牌番号指定
					ply_ie = 1 ;
				}else if(strcmp(tmp_str, "3") == 0){
					// 牌番号指定
					ply_ie = 2 ;
				}else if(strcmp(tmp_str, "4") == 0){
					// 牌番号指定
					ply_ie = 3 ;
				}

			}

		// ----------------------------------------
		// hai_read = 1の処理
		// ----------------------------------------

		}else if(hai_read == 1){

			// 文字情報の格納
			tmp_str[0] = wk_str[wk_index][i];
			tmp_str[1] = wk_str[wk_index][i+1];
			tmp_str[2] = '\0';
			i+=2;

			// 牌番号の設定
			hai_num = Chk_painum(tmp_str);

			// 赤牌確認
			if(hai_num > 100){

				// 牌番号初期化
				hai_num = hai_num - 100;

				// 赤牌加算
				if( (hai_num-5)/10 == 0 || (hai_num-5)/10 == 1 || (hai_num-5)/10 == 2 ){
					tk->kyoku[kyoku_index].aka_count[pnum][(hai_num-5)/10]++;
				}
			}

			// 卓情報クラスに牌番号を設定
			tk->kyoku[kyoku_index].tehai[pnum][hai_num] ++;

			// 牌番号初期化
			hai_num = 0 ;

		}else{

		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// Tkinfo設定処理： mjscore_read_mode = 6 ： ドラ情報
/* ---------------------------------------------------------------------------------------------- */
void MJSReadTplog::Set_tkinfo_dora(MJSTkinfo *tk, int kyoku_index){

	// ----------------------------------------
	// 卓情報設定 - ドラ設定(仮置き)
	// ----------------------------------------
	tk->kyoku[kyoku_index].doracount   = 1;
	tk->kyoku[kyoku_index].dora[0]     = 21;
	tk->kyoku[kyoku_index].dora_aka[0] = false;

	// ----------------------------------------
	// ドラ情報読み込み
	// ----------------------------------------
	wk_index++;
	wk_index++;

}

/* ---------------------------------------------------------------------------------------------- */
// Tkinfo設定処理： mjscore_read_mode = 7 ： アクション情報
/* ---------------------------------------------------------------------------------------------- */
void MJSReadTplog::Set_tkinfo_actinfo(MJSTkinfo *tk, int kyoku_index){

	// ----------------------------------------
	// 「+」「*」と続くのでスキップする
	// ----------------------------------------
	wk_index++;
	wk_index++;

	// ----------------------------------------
	// 変数定義
	// ----------------------------------------

	// 全角表示定義
	char tmp_str[3];         // 分割処理用

	// 家番号の格納
	int ply_ie = 0;          // プレーヤーごとの家番号定義

	// 牌読み込み開始であるかのか？
	int act_read_mode = 0 ;  // +が二回続いてないか？
	int hai_read = 0 ;       // プレーヤー=1、アクション=2、牌種別=3、補足=4
	int hai_num = 0 ;        // 牌番号

	// カカンフラグ
	int kakan_flg;

	// ----------------------------------------
	// アクション情報設定 - 配牌時
	// ----------------------------------------
	tk->kyoku[kyoku_index].act_stat[0]  = HAIPAI;
	tk->kyoku[kyoku_index].act_ply[0]   = 4;
	tk->kyoku[kyoku_index].react_ply[0] = 4;
	tk->kyoku[kyoku_index].act_hai[0]   = 0;
	tk->kyoku[kyoku_index].act_count    = 1;

	// ----------------------------------------
	// アクション読み込み
	// ----------------------------------------

	// 卓アクションの読み込み
	while( act_read_mode < 2){

	// 文字読み込みポインタ
	int i=0;
	tk->kyoku[kyoku_index].act_hai[tk->kyoku[kyoku_index].act_count]=0;

		// ----------------------------------------
		// 行読み込み
		// ----------------------------------------

		while(wk_str[wk_index][i] != '\0'){

			// ----------------------------------------
			// hai_read = 0の処理
			// ----------------------------------------

			if(hai_read == 0){

				// 半角文字の格納
				tmp_str[0] = wk_str[wk_index][i];
				tmp_str[1] = '\0';
				i++;

				// 「*」であれば、読込再開
				if ( strcmp( tmp_str, "*" ) == 0 ){

					// モード変更
					act_read_mode = 0 ;

				// 改行区切り文字
				}else if(strcmp(tmp_str, "+") == 0 && act_read_mode == 0){

					// モード変更
					act_read_mode = 1 ;

				// 「+」が二つ続いた場合には読込終了

				}else if(strcmp(tmp_str, "+") == 0 && act_read_mode == 1){

					// 最後のアクションが「和了」であれば「局終了」、「捨牌」であれば「流局」と「局終了」
					if ( tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count-1] != PLYTSUMOAGARI && tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count-1] != PLYACTRON ){

						// アクション情報 - 流局
						tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count]  = RYUKYOKU;
						tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]   = 4;
						tk->kyoku[kyoku_index].react_ply[tk->kyoku[kyoku_index].act_count] = 4;
						tk->kyoku[kyoku_index].act_hai[tk->kyoku[kyoku_index].act_count]   = 0;
						tk->kyoku[kyoku_index].act_count++;

					}

						// アクション情報 - 局結果表示
						tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count]  = KYOKURESULT;
						tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]   = 4;
						tk->kyoku[kyoku_index].react_ply[tk->kyoku[kyoku_index].act_count] = 4;
						tk->kyoku[kyoku_index].act_hai[tk->kyoku[kyoku_index].act_count]   = 0;
						tk->kyoku[kyoku_index].act_count++;

					// 牌番号指定：(読込終了)
					act_read_mode = 2 ;

				}else if(strcmp(tmp_str, "1") == 0 && hai_read == 0){

					// プレーヤー番号指定
					tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]=0;
					hai_read = 1;

					// リアクションプレーヤーを仮定義
					tk->kyoku[kyoku_index].react_ply[tk->kyoku[kyoku_index].act_count] = 4;

				}else if(strcmp(tmp_str, "2") == 0 && hai_read == 0){

					// プレーヤー番号指定
					tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]=1;
					hai_read = 1;

					// リアクションプレーヤーを仮定義
					tk->kyoku[kyoku_index].react_ply[tk->kyoku[kyoku_index].act_count] = 4;

				}else if(strcmp(tmp_str, "3") == 0 && hai_read == 0){

					// プレーヤー番号指定
					tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]=2;
					hai_read = 1;

					// リアクションプレーヤーを仮定義
					tk->kyoku[kyoku_index].react_ply[tk->kyoku[kyoku_index].act_count] = 4;

				}else if(strcmp(tmp_str, "4") == 0 && hai_read == 0){

					// プレーヤー番号指定
					tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]=3;
					hai_read = 1;

					// リアクションプレーヤーを仮定義
					tk->kyoku[kyoku_index].react_ply[tk->kyoku[kyoku_index].act_count] = 4;

				}

			// ----------------------------------------
			// hai_read = 1の処理：アクション情報
			// ----------------------------------------

			}else if(hai_read == 1){

				// 半角文字の格納
				tmp_str[0] = wk_str[wk_index][i];
				tmp_str[1] = '\0';
				i++;

				// ----------------------------------------
				// アクション情報 -「G」：自摸処理(Get)
				// ----------------------------------------
				if(strcmp(tmp_str, "G") == 0 && hai_read == 1){

					tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count]=PLYACTTSUMO;
					hai_read = 2;

				// ----------------------------------------
				// アクション情報 - 捨牌
				// ----------------------------------------
				}else if(strcmp(tmp_str, "d") == 0 && hai_read == 1){

					//  tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count] = PLYACTSUTE;
					// 一つ前の処理鳴きアクションの場合は鳴き捨
					if(tk->kyoku[tk->kyoku_index].act_stat[tk->kyoku[tk->kyoku_index].act_count-1] == PLYACTPON ||
					   tk->kyoku[tk->kyoku_index].act_stat[tk->kyoku[tk->kyoku_index].act_count-1] == PLYACTCHI ){
						// 鳴牌アクション
						tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count] = PLYACTNAKISUTE;
					}else{
						// 捨牌アクション
						tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count] = PLYACTSUTE;
					}
					hai_read = 2;

				// ----------------------------------------
				// アクション情報 - 自摸切り
				// ----------------------------------------
				}else if(strcmp(tmp_str, "D") == 0 && hai_read == 1){

					tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count]=PLYACTTSUMOGIRI;
					hai_read = 2;

				// ----------------------------------------
				// アクション情報 - リーチ
				// ----------------------------------------
				}else if(strcmp(tmp_str, "R") == 0 && hai_read == 1){

					tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count]=PLYACTRIICH;
					hai_read = 2;

				// ----------------------------------------
				// アクション情報 -「N」：ポン処理
				// ----------------------------------------
				}else if(strcmp(tmp_str, "N") == 0 && hai_read == 1){

					// アクション情報 - ポン処理
					tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count]  = PLYACTPON;                                                          // アクション定義 - ポン
					tk->kyoku[kyoku_index].react_ply[tk->kyoku[kyoku_index].act_count] = tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count-1]; // リアクションプレーヤー - 直前のプレーヤーと同じ
					tk->kyoku[kyoku_index].act_hai[tk->kyoku[kyoku_index].act_count]   = tk->kyoku[kyoku_index].act_hai[tk->kyoku[kyoku_index].act_count-1]; // 牌番号 - 直前の牌と同じ
					tk->kyoku[kyoku_index].act_aka[tk->kyoku[kyoku_index].act_count]   = tk->kyoku[kyoku_index].act_aka[tk->kyoku[kyoku_index].act_count-1]; // 赤牌定義

					// 鳴き情報設定 - ポン処理
					tk->kyoku[kyoku_index].naki_actid[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]]] = tk->kyoku[kyoku_index].act_count;
					tk->kyoku[kyoku_index].naki_stat[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]]] = MINKO;
					tk->kyoku[kyoku_index].naki_hai[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]]] = tk->kyoku[kyoku_index].act_hai[tk->kyoku[kyoku_index].act_count-1]; 
					tk->kyoku[kyoku_index].naki_idx[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]]] = tk->kyoku[kyoku_index].act_hai[tk->kyoku[kyoku_index].act_count-1]; 

					// 鳴き情報設定(赤牌確認・アクション牌) - ポン処理
					if (tk->kyoku[kyoku_index].act_aka[tk->kyoku[kyoku_index].act_count] == true){
						tk->kyoku[kyoku_index].naki_aka[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]]]=1;
					}else{
						tk->kyoku[kyoku_index].naki_aka[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]]]=0;
					}

					// 鳴き情報設定(赤牌確認・手牌内) - ポン処理
					// 牌譜に赤牌情報がないので自分で数える。
					// tk->Check_Actid_Aka_count(kyoku_index, tk->kyoku[kyoku_index].act_count, tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]);
					tk->Check_Ply_ActTehai(kyoku_index, tk->kyoku[kyoku_index].act_count);
					if ( tk->kyoku[kyoku_index].act_hai[tk->kyoku[kyoku_index].act_count] == 5){ 
						// 赤牌マンズの設定
						tk->kyoku[kyoku_index].naki_aka[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]]] =
						tk->kyoku[kyoku_index].naki_aka[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]]] + tk->ply_act_aka_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][0];
					}else if( tk->kyoku[kyoku_index].act_hai[tk->kyoku[kyoku_index].act_count] == 15){
						// 赤牌ピンズの設定
						tk->kyoku[kyoku_index].naki_aka[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]]] =
						tk->kyoku[kyoku_index].naki_aka[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]]] + tk->ply_act_aka_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][1];
					}else if( tk->kyoku[kyoku_index].act_hai[tk->kyoku[kyoku_index].act_count] == 25){
						// 赤牌ソウズの設定
						tk->kyoku[kyoku_index].naki_aka[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]]] =
						tk->kyoku[kyoku_index].naki_aka[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]]] + tk->ply_act_aka_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][2];
					}else{
						// 通常牌の設定
						tk->kyoku[kyoku_index].naki_aka[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]]] = 0;
					}

					// 鳴き数を+1
					tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]] ++;

					// モード変更
					hai_read = 2;

				// ----------------------------------------
				// アクション情報 -「C」：チー処理
				// ----------------------------------------
				}else if(strcmp(tmp_str, "C") == 0 && hai_read == 1){

					// アクション情報 - チー
					tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count]  = PLYACTCHI;                                                          // アクション定義 - チー
					tk->kyoku[kyoku_index].react_ply[tk->kyoku[kyoku_index].act_count] = tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count-1]; // リアクションプレーヤー - 直前のプレーヤーと同じ
					tk->kyoku[kyoku_index].act_hai[tk->kyoku[kyoku_index].act_count]   = tk->kyoku[kyoku_index].act_hai[tk->kyoku[kyoku_index].act_count-1]; // 牌番号 - 直前の牌と同じ
					tk->kyoku[kyoku_index].act_aka[tk->kyoku[kyoku_index].act_count]   = tk->kyoku[kyoku_index].act_aka[tk->kyoku[kyoku_index].act_count-1]; // 赤牌定義

					// 鳴き情報設定 - チー
					tk->kyoku[kyoku_index].naki_actid[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]]] = tk->kyoku[kyoku_index].act_count;
					tk->kyoku[kyoku_index].naki_stat[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]]] = MINSHUN;
					tk->kyoku[kyoku_index].naki_hai [tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]]] = tk->kyoku[kyoku_index].act_hai[tk->kyoku[kyoku_index].act_count-1];

					// 鳴き情報設定(赤牌確認・アクション牌) - チー処理
					if(tk->kyoku[kyoku_index].act_aka[tk->kyoku[kyoku_index].act_count]){
						tk->kyoku[kyoku_index].naki_aka[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]]] = 1;
					}else{
						tk->kyoku[kyoku_index].naki_aka[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]]] = 0;
					}

					// 鳴き数を+1
					tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]] ++;

					// モード変更
					hai_read = 2;

				// ----------------------------------------
				// アクション情報 -「K」：カン処理
				// ----------------------------------------
				}else if(strcmp(tmp_str, "K") == 0 && hai_read == 1){

					// 一つ前が自分の自摸であるならば、暗槓か加槓
					if (tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count-1] == PLYACTTSUMO){

						// 加槓フラグの設定
						kakan_flg=0;
						for(int tmp_i = 0; tmp_i < tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]]; tmp_i++){
							// ポンした牌であれば、カカンフラグを立てる
							if (tk->kyoku[kyoku_index].naki_hai[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][tmp_i] == tk->kyoku[kyoku_index].act_hai[tk->kyoku[kyoku_index].act_count-1] ){
								kakan_flg=1;
							}
						}

						// 暗槓・加槓の確認
						if (kakan_flg == 1){

							// アクション情報設定 - 加槓
							tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count]=PLYACTKAKAN;                                                        // アクション定義 - 加槓
							tk->kyoku[kyoku_index].act_hai[tk->kyoku[kyoku_index].act_count]=tk->kyoku[kyoku_index].act_hai[tk->kyoku[kyoku_index].act_count-1];  // 牌番号 - 直前の牌と同じ	

							// 鳴き情報設定 - 加槓
							tk->kyoku[kyoku_index].naki_actid[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]]] = tk->kyoku[kyoku_index].act_count;
							tk->kyoku[kyoku_index].naki_stat[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]]] = KAKAN;
							tk->kyoku[kyoku_index].naki_hai[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]]] = tk->kyoku[kyoku_index].act_hai[tk->kyoku[kyoku_index].act_count-1];
							tk->kyoku[kyoku_index].naki_idx[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]]] = tk->kyoku[kyoku_index].act_hai[tk->kyoku[kyoku_index].act_count-1];

							// 赤牌確認 - 加槓
							tk->kyoku[kyoku_index].naki_aka[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]]] = 0;

							// 鳴き数を+1
							tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]] ++;

						}else{
							// アクション情報設定 - 暗槓
							tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count]=PLYACTANKAN;                                                       // アクション定義 - 暗槓
							tk->kyoku[kyoku_index].act_hai[tk->kyoku[kyoku_index].act_count]=tk->kyoku[kyoku_index].act_hai[tk->kyoku[kyoku_index].act_count-1]; // 牌番号 - 直前の牌と同じ	

							// 鳴き情報設定 - 暗槓
							tk->kyoku[kyoku_index].naki_actid[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]]] = tk->kyoku[kyoku_index].act_count;
							tk->kyoku[kyoku_index].naki_stat[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]]] = ANKAN;
							tk->kyoku[kyoku_index].naki_hai[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]]] = tk->kyoku[kyoku_index].act_hai[tk->kyoku[kyoku_index].act_count-1];
							tk->kyoku[kyoku_index].naki_idx[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]]] = tk->kyoku[kyoku_index].act_hai[tk->kyoku[kyoku_index].act_count-1];


							// 赤牌確認 - 暗槓
							tk->kyoku[kyoku_index].naki_aka[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]]] = 0;

							// 鳴き数を+1
							tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]] ++;

						}

					// 自分の自摸でないならば、明槓
					}else{

							// アクション情報設定 - 明槓
							tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count]=PLYACTMINKAN;                                                       // アクション定義 - 暗槓
							tk->kyoku[kyoku_index].act_hai[tk->kyoku[kyoku_index].act_count]=tk->kyoku[kyoku_index].act_hai[tk->kyoku[kyoku_index].act_count-1];  // 牌番号 - 直前の牌と同じ	

							// 鳴き情報設定 - 明槓
							tk->kyoku[kyoku_index].naki_actid[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]]] = tk->kyoku[kyoku_index].act_count;
							tk->kyoku[kyoku_index].naki_stat[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]]]  = MINKAN;
							tk->kyoku[kyoku_index].naki_hai[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]]]   = tk->kyoku[kyoku_index].act_hai[tk->kyoku[kyoku_index].act_count-1];
							tk->kyoku[kyoku_index].naki_idx[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]]]  = tk->kyoku[kyoku_index].act_hai[tk->kyoku[kyoku_index].act_count-1];

							// 赤牌確認 - 明槓
							tk->kyoku[kyoku_index].naki_aka[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]]] = 0;

							// 鳴き数を+1
							tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]] ++;

					}

					// モード変更
					hai_read = 2;

				// ----------------------------------------
				// アクション情報 -「A」：和了処理
				// ----------------------------------------
				}else if(strcmp(tmp_str, "A") == 0 && hai_read == 1){

					// 一つ前が自分の自摸であるならば、自摸和了
					if (tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count-1] == PLYACTTSUMO){

						// アクション情報 - 自摸和了
						tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count] = PLYTSUMOAGARI;
						tk->kyoku[kyoku_index].act_hai[tk->kyoku[kyoku_index].act_count]  = tk->kyoku[kyoku_index].act_hai[tk->kyoku[kyoku_index].act_count-1];
						tk->kyoku[kyoku_index].act_aka[tk->kyoku[kyoku_index].act_count]  = tk->kyoku[kyoku_index].act_aka[tk->kyoku[kyoku_index].act_count-1];

					}else{

						// アクション情報 - ロン和了
						tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count]  = PLYACTRON;
						tk->kyoku[kyoku_index].react_ply[tk->kyoku[kyoku_index].act_count] = tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count-1];
						tk->kyoku[kyoku_index].act_hai[tk->kyoku[kyoku_index].act_count]   = tk->kyoku[kyoku_index].act_hai[tk->kyoku[kyoku_index].act_count-1];
						tk->kyoku[kyoku_index].act_aka[tk->kyoku[kyoku_index].act_count]   = tk->kyoku[kyoku_index].act_aka[tk->kyoku[kyoku_index].act_count-1];

					}

					// モード変更
					hai_read = 2;

				}

			// ----------------------------------------
			// 牌番号読み込み(hai_read = 2：自摸・捨ての牌、チー牌の1枚目)
			// ----------------------------------------

			}else if(hai_read == 2){

				// 2文字の格納
				tmp_str[0] = wk_str[wk_index][i];
				tmp_str[1] = wk_str[wk_index][i+1];
				tmp_str[2] = '\0';
				i+=2;

				// 牌番号の設定
				hai_num = Chk_painum(tmp_str);

				// 赤牌確認
				if(hai_num > 100){
					hai_num = hai_num - 100;
					tk->kyoku[kyoku_index].act_aka[tk->kyoku[kyoku_index].act_count] = true;
				}else{
					tk->kyoku[kyoku_index].act_aka[tk->kyoku[kyoku_index].act_count] = false;
				}

				// アクション設定
				tk->kyoku[kyoku_index].act_hai[tk->kyoku[kyoku_index].act_count] = hai_num;

				// 鳴き情報設定
				if (tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count] == PLYACTCHI){
					// tpscoreログ専用の鳴牌INDEXの値の設定
					tk->kyoku[kyoku_index].naki_mj_idx[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]]-1] = hai_num;
				}

				// 牌番号初期化
				hai_num = 0 ;

				// モード変更
				hai_read = 3;

			// ----------------------------------------
			// hai_read = 3の処理(チー牌の2枚目)
			// ----------------------------------------

			}else if(hai_read == 3){

				// 2文字の格納
				tmp_str[0] = wk_str[wk_index][i];
				tmp_str[1] = wk_str[wk_index][i+1];
				tmp_str[2] = '\0';
				i+=2;

			}else{

			}

		}

		// 文字読み込み終了なら次に行く
		wk_index ++;
		hai_read = 0;

		// 終了文字(*,+)でないなら、アクションIDを次に行く
		if ( strcmp( tmp_str, "*" ) != 0 && strcmp( tmp_str, "+" ) != 0 ){

			tk->kyoku[kyoku_index].act_count ++;

		}

	}

	// ----------------------------------------
	// 後処理
	// ----------------------------------------

	// チー時の「頭牌情報」の設定
	for(int tmp_pnum = 0; tmp_pnum < PLAYER_MAX; tmp_pnum++){
		for(int tmp_i = 0; tmp_i < tk->kyoku[kyoku_index].naki_count[tmp_pnum]; tmp_i++){
			if ( tk->kyoku[kyoku_index].naki_stat[tmp_pnum][tmp_i] == MINSHUN){
				if ( tk->kyoku[kyoku_index].naki_hai[tmp_pnum][tmp_i] - tk->kyoku[kyoku_index].naki_mj_idx[tmp_pnum][tmp_i] == -1){
					tk->kyoku[kyoku_index].naki_idx[tmp_pnum][tmp_i] = tk->kyoku[kyoku_index].naki_hai[tmp_pnum][tmp_i];
				}
				if ( tk->kyoku[kyoku_index].naki_hai[tmp_pnum][tmp_i] - tk->kyoku[kyoku_index].naki_mj_idx[tmp_pnum][tmp_i] == 1){
					tk->kyoku[kyoku_index].naki_idx[tmp_pnum][tmp_i] = tk->kyoku[kyoku_index].naki_mj_idx[tmp_pnum][tmp_i];
				}
				if ( tk->kyoku[kyoku_index].naki_hai[tmp_pnum][tmp_i] - tk->kyoku[kyoku_index].naki_mj_idx[tmp_pnum][tmp_i] == 2){
					tk->kyoku[kyoku_index].naki_idx[tmp_pnum][tmp_i] = tk->kyoku[kyoku_index].naki_mj_idx[tmp_pnum][tmp_i];
				}
			}else{
					// tk->kyoku[kyoku_index].naki_idx[tmp_pnum][tmp_i] = 0;
			}
		}
	}

}

/* ---------------------------------------------------------------------------------------------- */
// Tkinfo設定処理： mjscore_read_mode = 8 ： 卓終了確認
/* ---------------------------------------------------------------------------------------------- */
bool MJSReadTplog::Set_tkinfo_checkend(){

	// 分割処理用
	char tmp_str[3];

	// 全角判定
	if(_ismbblead(wk_str[wk_index][0])){

		// 全角文字の格納
		tmp_str[0] = wk_str[wk_index][0];
		tmp_str[1] = wk_str[wk_index][1];
		tmp_str[2] = '\0';

		// 文字抽出(全角)
		if ( strcmp( tmp_str, "東" ) == 0 || strcmp(tmp_str, "南") == 0 ){
			return true;
		}else{
			return false;
		}

	}else{
	
		// 半角文字の格納
		tmp_str[0] = wk_str[wk_index][0];
		tmp_str[1] = '\0';

		// 文字抽出(半角)
		if ( strcmp( tmp_str, "-" ) == 0 ){
			return false;
		}else{
			return true;
		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// Tkinfo設定処理： mjscore_read_mode = 9 ： 卓終了情報読み込み
/* ---------------------------------------------------------------------------------------------- */
void MJSReadTplog::Set_tkinfo_tkend(MJSTkinfo *tk){

	// 「wk_indexを+5にする
	wk_index=wk_index+5;

	// ----------------------------------------
	// 順位格納
	// ----------------------------------------

	for(int jun = 0; jun < PLAYER_MAX; jun++){
		// [卓1]プレーヤの順位の抽出
		if(strcmp(wk_str[wk_index], tk->plyname[0]) == 0){
			tk->plyjun[jun]=0;
			tk->plyEndscore[jun]=atoi(wk_str[wk_index+1]);
			wk_index=wk_index+4;
		// [卓2]プレーヤの順位の抽出
		}else if(strcmp(wk_str[wk_index], tk->plyname[1]) == 0){
			tk->plyjun[jun]=1;
			tk->plyEndscore[jun]=atoi(wk_str[wk_index+1]);
			wk_index=wk_index+4;
		// [卓3]プレーヤの順位の抽出
		}else if(strcmp(wk_str[wk_index], tk->plyname[2]) == 0){
			tk->plyjun[jun]=2;
			tk->plyEndscore[jun]=atoi(wk_str[wk_index+1]);
			wk_index=wk_index+4;
		// [卓4]プレーヤの順位の抽出
		}else if(strcmp(wk_str[wk_index], tk->plyname[3]) == 0){
			tk->plyjun[jun]=3;
			tk->plyEndscore[jun]=atoi(wk_str[wk_index+1]);
			wk_index=wk_index+4;
		}
	}

	// ----------------------------------------
	// 卓終了処理
	// ----------------------------------------

	// wk_indexを+2にする
	wk_index=wk_index+2;

	// 卓終了時刻定義
	wsprintf(tk->enddate, "%s", wk_str[wk_index]);
	wk_index++;

	// 卓終了日付定義
	wsprintf(tk->endtime, "%s", wk_str[wk_index]);
	wk_index++;

}

/* ---------------------------------------------------------------------------------------------- */
// ソース終了
/* ---------------------------------------------------------------------------------------------- */
