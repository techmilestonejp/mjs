/* ---------------------------------------------------------------------------------------------- 
 * 
 * プログラム概要 ： Newさくら麻雀(MJAIクライアント実装版)
 * バージョン     ： 0.1.2.1.228(MJAIログ表示：Disp関数ダブロン表示準備)
 * プログラム名   ： mjs.exe
 * ファイル名     ： tkinfo.cpp
 * クラス名       ： MJSTkinfo
 * 処理概要       ： 卓情報クラス
 * Ver0.0.8作成日 ： 2012/05/04 08:57:12
 * Ver0.1.0作成日 ： 2022/04/11 15:57:39
 * Ver0.1.1作成日 ： 2022/06/30 21:19:01
 * Ver0.1.2作成日 ： 2022/08/31 22:19:54
 * 最終更新日     ： 2024/11/16 10:47:17
 * 
 * Copyright (c) 2010-2023 Techmilestone, All rights reserved.
 * 
 * ---------------------------------------------------------------------------------------------- */

#include "tkinfo.h"

/* ---------------------------------------------------------------------------------------------- */
// 前処理
/* ---------------------------------------------------------------------------------------------- */
void MJSTkinfo::TkinfoInit(){

	// HUMプレイモードの初期化
	ply_hum_mode = 0;

}

/* ---------------------------------------------------------------------------------------------- */
// 後処理
/* ---------------------------------------------------------------------------------------------- */
void MJSTkinfo::TkinfoPost(){

}

/* ---------------------------------------------------------------------------------------------- */
// 卓初期化
/* ---------------------------------------------------------------------------------------------- */
void MJSTkinfo::TakuInit(){

	// 局構造体の配列定義
	kyoku = new MJSkyokuinfo[KYOKU_MAX];
	sc    = new MJSScore;

	// ----------------------------------------
	// 卓情報の設定
	// ----------------------------------------
	end_flg = false;
	stat = TAKUSTART;
	kyoku_index = 0;     // 内部管理用の局ID
	hai_point  = 0;      // 残り牌数

	// 初期得点
	init_score = INITSCORE;

	// 得点設定
	for( int tmp_pnum = 0; tmp_pnum < PLAYER_MAX; tmp_pnum++){
		kyoku[kyoku_index].ply_kyoku_start_score[tmp_pnum] = init_score;
	}

	// 乱数シード
	core_seed_num = 0;

	// ----------------------------------------
	// 卓情報の設定(局関連)
	// ----------------------------------------

	kyoku[kyoku_index].kyoku    = 0;
	kyoku[kyoku_index].tsumibo  = 0;
	kyoku[kyoku_index].riichbo  = 0;
	kyoku[kyoku_index].seed_num = 0;

	// ----------------------------------------
	// 国士牌の指定
	// ----------------------------------------

	kokushi_hai_num[0]  = MAN1NUM;
	kokushi_hai_num[1]  = PIN1NUM;
	kokushi_hai_num[2]  = SOU1NUM;
	kokushi_hai_num[3]  = MAN9NUM;
	kokushi_hai_num[4]  = PIN9NUM;
	kokushi_hai_num[5]  = SOU9NUM;
	kokushi_hai_num[6]  = TONNUM;
	kokushi_hai_num[7]  = NANNUM;
	kokushi_hai_num[8]  = SHANUM;
	kokushi_hai_num[9]  = PEINUM;
	kokushi_hai_num[10] = HAKUNUM;
	kokushi_hai_num[11] = HATSUNUM;
	kokushi_hai_num[12] = CHUNNUM;

	// ----------------------------------------
	// 局初期化
	// ----------------------------------------
	KyokuInit();

}

/* ---------------------------------------------------------------------------------------------- */
// 卓終了処理
/* ---------------------------------------------------------------------------------------------- */
void MJSTkinfo::TakuPost(){

	// 局終了処理
	KyokuPost();

	// 局構造体の解放
	delete[] kyoku;
	delete sc;

}


/* ---------------------------------------------------------------------------------------------- */
// 局初期化処理
/* ---------------------------------------------------------------------------------------------- */
void MJSTkinfo::KyokuInit(){

	// ----------------------------------------
	// 局初期化
	// ----------------------------------------
	kyoku[kyoku_index].act_count = 0;
	ply_turn = 0;

	// ドラ枚数
	kyoku[kyoku_index].doracount = 1;

	// ドラ表示牌
	for( int tmp_i = 0; tmp_i < 5; tmp_i++){
		kyoku[kyoku_index].dora[tmp_i] = 0;
		kyoku[kyoku_index].uradora[tmp_i] = 0;
		kyoku[kyoku_index].dora_aka[tmp_i] = false;
		kyoku[kyoku_index].uradora_aka[tmp_i] = false;
	}

	// 牌テーブルの捨牌位置番号
	ply_tbl_hum_sutehai_statnum = 0;               // 牌テーブルの捨牌位置番号(HUM用)

	// COMの手牌情報の有無
	com_no_chk_tehai_flg = false;

	// ----------------------------------------
	// plyアクション情報
	// ----------------------------------------
	ply_act = NOACT;

	// ----------------------------------------
	// 牌山ポインタ
	// ----------------------------------------
	hai_point     = HAI_POINT_START;
	rinshan_point = RINSHAN_POINT_START;

	// 和了時
	kyoku[kyoku_index].agari_ply_count = 0;

	// 流局時
	kyoku[kyoku_index].ply_agari_yk[0].ply_tempai_count = 0;

	// ----------------------------------------
	// 局情報の初期化(プレーヤーごと)
	// ----------------------------------------
	for( int tmp_pnum = 0; tmp_pnum  < PLAYER_MAX; tmp_pnum++){

		// ----------------------------------------
		// 局配列情報の初期化
		// ----------------------------------------

		// 配牌初期化
	    for(int tmp_i=0; tmp_i< PAI_MAX; tmp_i++){
			kyoku[kyoku_index].tehai[tmp_pnum][tmp_i] = 0;
		}

		// 赤牌初期化
		kyoku[kyoku_index].aka_count[tmp_pnum][0] = 0;
		kyoku[kyoku_index].aka_count[tmp_pnum][1] = 0;
		kyoku[kyoku_index].aka_count[tmp_pnum][2] = 0;

		// プレーヤーごとの晒し情報の初期化
		kyoku[kyoku_index].naki_count[tmp_pnum]  = 0;
		kyoku[kyoku_index].ankan_count[tmp_pnum] = 0;
		kyoku[kyoku_index].kakan_count[tmp_pnum] = 0;

		// 流局時
		kyoku[kyoku_index].ply_agari_yk[kyoku[kyoku_index].agari_ply_count].ply_tempai_flg[tmp_pnum] = false;

		// ----------------------------------------
		// 手牌ヒストグラム・手牌テーブルの初期化
		// ----------------------------------------

		// 牌テーブルの初期化
		ply_act_tehaicount[tmp_pnum] = 0;
		ply_tbl_com_sutehai_statnum[tmp_pnum] = 0;
		ply_tbl_hum_sutehai_statnum = 0;

		// 牌テーブル(配列)の初期化
	    for(int tmp_i=0; tmp_i< TEHAI_MAX; tmp_i++){
			ply_act_tehai_shanten_tbl[tmp_pnum][tmp_i] = 8; // 牌テーブル(向聴数)
		}

		// 自摸情報
		ply_act_tsumo[tmp_pnum] = 0;              // 自摸牌
		ply_act_tsumo_aka[tmp_pnum] = false;      // 自摸の赤牌
		ply_act_tsumo_shanten[tmp_pnum] = 8;      // 自摸の向聴数

		// 捨牌情報
		ply_act_sute[tmp_pnum] = 0;               // 捨牌
		ply_act_sute_aka[tmp_pnum] = false;       // 捨牌の赤牌

		// 向聴数
		shanten_total[tmp_pnum]   = 14;           // 総合向聴数
		shanten_normal[tmp_pnum]  = 14;           // 通常向聴数
		shanten_chitoi[tmp_pnum]  = 14;           // 七対向聴数
		shanten_kokushi[tmp_pnum] = 14;           // 国士向聴数

		// シャンテン算出鳴き数
		naki_count_none_kakan[tmp_pnum] = 0;

		// 待牌
		ply_act_machi_count[tmp_pnum] = 0;        // 待牌合計数

		// プレーヤーごとの鳴きアクション初期化
		ply_act_naki[tmp_pnum] = ACTNONAKI;

		// 牌テーブルの捨牌位置番号
		ply_tbl_com_sutehai_statnum[tmp_pnum] = 0;     // 牌テーブルの捨牌位置番号(COM用)

		// ----------------------------------------
		// アクション情報初期化
		// ----------------------------------------

		// 鳴き通知情報
		ply_naki_hai[tmp_pnum] = 0;
		ply_naki_idx[tmp_pnum] = 0;
		ply_naki_aka_count[tmp_pnum] = 0;

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 局終了処理
/* ---------------------------------------------------------------------------------------------- */
void MJSTkinfo::KyokuPost(){

}

/* ---------------------------------------------------------------------------------------------- */
// アクション情報設定
/* ---------------------------------------------------------------------------------------------- */
void MJSTkinfo::SetActInfo(int kyoku_index, LBTkSt tmp_act_stat, int tmp_act_ply, int tmp_react_ply, int tmp_act_hai, bool tmp_act_aka){

	// アクション番号の加算
	kyoku[kyoku_index].act_count++;

	// アクション情報登録
	kyoku[kyoku_index].act_stat[kyoku[kyoku_index].act_count]  = tmp_act_stat;
	kyoku[kyoku_index].act_ply[kyoku[kyoku_index].act_count]   = tmp_act_ply;
	kyoku[kyoku_index].react_ply[kyoku[kyoku_index].act_count] = tmp_react_ply;
	kyoku[kyoku_index].act_hai[kyoku[kyoku_index].act_count]   = tmp_act_hai;
	kyoku[kyoku_index].act_aka[kyoku[kyoku_index].act_count]   = tmp_act_aka;

}

/* ---------------------------------------------------------------------------------------------- */
// 鳴き情報設定
/* ---------------------------------------------------------------------------------------------- */
void MJSTkinfo::SetNakiInfo(int kyoku_index, LBMen tmp_naki_stat, int tmp_naki_ply, int tmp_naki_actid, int tmp_naki_hai, int tmp_naki_idx, int tmp_naki_aka_count){

	// 鳴き情報の設定
	kyoku[kyoku_index].naki_actid[tmp_naki_ply][kyoku[kyoku_index].naki_count[tmp_naki_ply]]     = tmp_naki_actid;
	kyoku[kyoku_index].naki_stat[tmp_naki_ply][kyoku[kyoku_index].naki_count[tmp_naki_ply]]      = tmp_naki_stat;
	kyoku[kyoku_index].naki_hai[tmp_naki_ply][kyoku[kyoku_index].naki_count[tmp_naki_ply]]       = tmp_naki_hai;
	kyoku[kyoku_index].naki_idx[tmp_naki_ply][kyoku[kyoku_index].naki_count[tmp_naki_ply]]       = tmp_naki_idx;
	kyoku[kyoku_index].naki_aka[tmp_naki_ply][kyoku[kyoku_index].naki_count[tmp_naki_ply]] = tmp_naki_aka_count;

	// 鳴きメンツ数の加算
	kyoku[kyoku_index].naki_count[tmp_naki_ply]++;

	// 暗槓の個数を加算
	if(tmp_naki_stat == ANKAN){
		// 暗槓の個数を加算
		kyoku[kyoku_index].ankan_count[tmp_naki_ply]++;
	}

	// 加槓の個数を加算
	if(tmp_naki_stat == KAKAN){
		// 加槓の個数を加算
		kyoku[kyoku_index].kakan_count[tmp_naki_ply]++;
	}else{
		// 加槓なし鳴き個数を加算
		naki_count_none_kakan[tmp_naki_ply]++;
	}

}

/* ---------------------------------------------------------------------------------------------- */
// 和了情報設定
/* ---------------------------------------------------------------------------------------------- */
void MJSTkinfo::SetAgariInfo(int kyoku_index, LBAgariTehai tmp_agari_stat, int tmp_agari_ply, int tmp_furikomi_ply, bool tmp_tsumoagari_flg, int tmp_agari_hai, bool tmp_agari_aka){

	// リーチ状態確認
	Check_Tenho_Riichi(kyoku_index, tmp_agari_ply);

	// 和了情報設定(和了情報構造体の設定)
	sc->SetAgari(
	&kyoku[kyoku_index].ply_agari_yk[kyoku[kyoku_index].agari_ply_count],  // 和了役情報構造体
	kyoku[kyoku_index].kyoku,                          // 局番号
	kyoku[kyoku_index].ie,                             // プレーヤの家情報
	kyoku[kyoku_index].doracount,                      // 表ドラ牌枚数
	kyoku[kyoku_index].dora,                           // 表ドラ牌情報
	kyoku[kyoku_index].doracount,                      // 裏ドラ牌枚数
	kyoku[kyoku_index].uradora,                        // 裏ドラ牌情報
	tmp_agari_stat,                                    // 和了形式
	tmp_agari_ply,                                     // 和了プレーヤ
	tmp_furikomi_ply,                                  // 振込プレーヤ
	tmp_tsumoagari_flg,                                // 自摸和了の有無
	tmp_agari_hai,                                     // 和了牌
	tmp_agari_aka,                                     // 和了牌の赤牌有無
	ply_act_tehai[tmp_agari_ply],                      // 和了時の手牌ヒストグラム
	ply_act_aka_count[tmp_agari_ply],                  // 手牌の赤牌枚数
	atama_hai,                                         // 頭牌
	mentu_count,                                       // 面子数
	mentu_stat,                                        // 面子状態
	mentu_hai,                                         // 面子牌
	mentu_hai,                                         // 面子INDEX
	kyoku[kyoku_index].naki_count[tmp_agari_ply],      // 鳴き面子数
	kyoku[kyoku_index].naki_stat[tmp_agari_ply],       // 鳴き面子状態
	kyoku[kyoku_index].naki_hai[tmp_agari_ply],        // 鳴き面子牌
	kyoku[kyoku_index].naki_idx[tmp_agari_ply],        // 鳴き面子INDEX
	kyoku[kyoku_index].naki_aka[tmp_agari_ply],        // 鳴き面子赤牌枚数
	riichi_flg[tmp_agari_ply],                         // リーチフラグ
	riichi_ippatsu_flg[tmp_agari_ply],                 // リーチ一発フラグ
	double_riichi_flg[tmp_agari_ply]                   // ダブルリーチフラグ
	);

	// 局終了得点の設定
	for(int tmp_i = 0; tmp_i < PLAYER_MAX; tmp_i++){
		kyoku[kyoku_index].ply_kyoku_end_score[tmp_i] = kyoku[kyoku_index].ply_kyoku_start_score[tmp_i] 
		                                              + kyoku[kyoku_index].ply_agari_yk[kyoku[kyoku_index].agari_ply_count].kyoku_score[tmp_i];
	}

	// 和了プレーヤ数の加算
	kyoku[kyoku_index].agari_ply_count++;

}

/* ---------------------------------------------------------------------------------------------- */
// 天和・リーチ確認
/* ---------------------------------------------------------------------------------------------- */
void MJSTkinfo::Check_Tenho_Riichi(int kyoku_index, int tmp_agari_ply){

	// -----------------------------
	// 作業用変数の定義
	// -----------------------------

	// 一発鳴きフラグ
	bool tmp_ippatsu_naki_flg;
	int tmp_agari_ply_tsumo_count;
	int tmp_agari_ply_riichi_count;

	// -----------------------------
	// 和了プレーヤーの和了自摸回数・リーチ状態確認(初期化)
	// -----------------------------

	riichi_flg[tmp_agari_ply]          = false;
	riichi_ippatsu_flg[tmp_agari_ply]  = false;
	double_riichi_flg[tmp_agari_ply]   = false;
	tmp_agari_ply_tsumo_count  = 0;
	tmp_agari_ply_riichi_count = 0;

	// -----------------------------
	// 和了プレーヤーの和了自摸回数・リーチ状態確認(メイン処理)
	// -----------------------------

	// 事前処理
	tmp_ippatsu_naki_flg = false;

	// アクションの確認
	for(int tmp_i = 0; tmp_i < kyoku[kyoku_index].act_count+1; tmp_i++){

		// -----------------------------
		// 和了プレーヤの自摸回数カウント
		// -----------------------------
		if(kyoku[kyoku_index].act_stat[tmp_i] == PLYACTTSUMO &&
		   kyoku[kyoku_index].act_ply[tmp_i]  == tmp_agari_ply ){
			// 自摸カウント
			tmp_agari_ply_tsumo_count++;
		}

		// -----------------------------
		// リーチ確認
		// -----------------------------
		if(kyoku[kyoku_index].act_stat[tmp_i] == PLYACTRIICH &&
		   kyoku[kyoku_index].act_ply[tmp_i]  == tmp_agari_ply ){

			// リーチモード変更
			riichi_flg[tmp_agari_ply]=true;

			// ダブルリーチ確認
			if(tmp_agari_ply_tsumo_count == 1){
				// リーチモード変更
				double_riichi_flg[tmp_agari_ply]=true;
			}else{
				// リーチモード変更
				double_riichi_flg[tmp_agari_ply]=false;
			}	

			// リーチ巡目の設定
			tmp_agari_ply_riichi_count = tmp_agari_ply_tsumo_count;

			// 一発鳴きフラグの仮設定
			tmp_ippatsu_naki_flg = true;

		}

		// -----------------------------
		// 鳴き確認
		// -----------------------------
		if( kyoku[kyoku_index].act_stat[tmp_i] == PLYACTPON ||
		    kyoku[kyoku_index].act_stat[tmp_i] == PLYACTCHI ||
		    kyoku[kyoku_index].act_stat[tmp_i] == PLYACTMINKAN ){

			// 一発鳴きフラグの仮設定
			tmp_ippatsu_naki_flg = false;

		}

		// -----------------------------
		// リーチ一発確認(自摸和了)
		// -----------------------------
		if (kyoku[kyoku_index].act_stat[tmp_i] == PLYTSUMOAGARI && 
			riichi_flg[tmp_agari_ply]    == true &&
		    tmp_agari_ply == kyoku[kyoku_index].act_ply[tmp_i]){

			// 次巡で且つ鳴きがないならば一発和了
			if( tmp_agari_ply_riichi_count + 1 == tmp_agari_ply_tsumo_count &&
			    tmp_ippatsu_naki_flg == true){
				// 一発和了
				riichi_ippatsu_flg[tmp_agari_ply]=true;
			}else{
				// 一発和了なし
				riichi_ippatsu_flg[tmp_agari_ply]=false;
			}
		}

		// -----------------------------
		// リーチ一発確認(ロン和了)
		// -----------------------------
		if (kyoku[kyoku_index].act_stat[tmp_i] == PLYACTRON && 
			riichi_flg[tmp_agari_ply] == true &&
		    kyoku[kyoku_index].act_ply[tmp_i]  == tmp_agari_ply ){

			// 次巡であれば一発
			if(tmp_agari_ply_riichi_count == tmp_agari_ply_tsumo_count &&
			    tmp_ippatsu_naki_flg == true){
				// 一発和了
				riichi_ippatsu_flg[tmp_agari_ply]=true;
			}else{
				// 一発和了なし
				riichi_ippatsu_flg[tmp_agari_ply]=false;
			}
		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 全プレーヤーの手牌確認
/* ---------------------------------------------------------------------------------------------- */
void MJSTkinfo::Check_Ply_ActTehai(int kyoku_index, int actid){

	// 配牌
	Check_Actid_Haipai(kyoku_index, actid);

	// メイン処理
	Check_Actid_Hai_count(kyoku_index, actid);

	// 最後牌の処理
	Check_Actid_LastHai(kyoku_index, actid);

}

/* ---------------------------------------------------------------------------------------------- */
// 配牌時の処理
/* ---------------------------------------------------------------------------------------------- */
void MJSTkinfo::Check_Actid_Haipai(int kyoku_index, int actid){

	// ----------------------------------------
	// 配牌場情報の設定
	// ----------------------------------------

	// テーブル情報の更新(全プレーヤー)
	for(int tmp_pnum = 0; tmp_pnum < PLAYER_MAX; tmp_pnum++){

		// 捨牌初期化
		ply_act_kawa_count[tmp_pnum] = 0;

		// ----------------------------------------
		// 手牌確認(配牌)
		// ----------------------------------------
		for(int tmp_i = 0; tmp_i < PAI_MAX; tmp_i++){
			ply_act_tehai[tmp_pnum][tmp_i] = kyoku[kyoku_index].tehai[tmp_pnum][tmp_i];
		}

		// ----------------------------------------
		// 赤牌確認(配牌)
		// ----------------------------------------
		for(int tmp_aka_grp = 0; tmp_aka_grp < AKA_TYPE_MAX_COUNT; tmp_aka_grp++){
			// 赤牌確認(配牌)
			ply_act_aka_count[tmp_pnum][tmp_aka_grp] = kyoku[kyoku_index].aka_count[tmp_pnum][tmp_aka_grp];
		}

		// ----------------------------------------
		// 最後牌確認：配牌時
		// ----------------------------------------
		if( kyoku[kyoku_index].act_stat[actid] == HAIPAI ){

			// ----------------------------------------
			// 1. 自摸・捨牌情報の初期化
			// ----------------------------------------
			ply_act_tsumo[tmp_pnum] = 0;
			ply_act_sute[tmp_pnum]  = 0;
			ply_tbl_com_sutehai_statnum[tmp_pnum] = 0 ;
			ply_act_tsumo_aka[tmp_pnum] = false ;
			ply_act_sute_aka[tmp_pnum]  = false ;

			// ----------------------------------------
			// 2. シャンテン確認(自摸なし：鳴きなし)
			// ----------------------------------------
			if(com_no_chk_tehai_flg == false){
				ChkShanten(tmp_pnum);
			}

			// ----------------------------------------
			// 3. 待牌設定
			// ----------------------------------------
			setmachi(kyoku_index, actid, tmp_pnum);

			// ----------------------------------------
			// 4. テーブル情報設定
			// ----------------------------------------
			settehaitbl(kyoku_index, actid, tmp_pnum);

		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 手牌ヒストグラム、手牌テーブル設定
/* ---------------------------------------------------------------------------------------------- */
void MJSTkinfo::Check_Actid_Hai_count(int kyoku_index, int actid){

	// ----------------------------------------
	// 作業用変数
	// ----------------------------------------
	int tmp_chi_num;
	int pnum;

	// 残り自摸数
	remain_hai_count = PAI_COUNT_MAX - 14 - TEHAI_MAX*PLAYER_MAX; // 残り自摸牌の数：136 - 14 - 13*4(52)
	remain_rinshan_count = 4;                                     // 残りリンシャン牌の数

	// クライアントモード用・枚数定義
	if(com_no_chk_tehai_flg == true){
		// 枚数指定
		ply_act_tehaicount[0] = TEHAI_MAX;
		ply_act_tehaicount[1] = TEHAI_MAX;
		ply_act_tehaicount[2] = TEHAI_MAX;
	}

	// ----------------------------------------
	// 手牌確認(一連のActID)
	// ----------------------------------------
	for(int tmp_i = 0; tmp_i <= actid; tmp_i++){

		// アクションプレーヤの定義
		pnum = kyoku[kyoku_index].act_ply[tmp_i];

		// ----------------------------------------
		// ◎ 1.自摸時の手牌数の増減
		// ----------------------------------------
		if( kyoku[kyoku_index].act_stat[tmp_i] == PLYACTTSUMO ){

			// 手牌ヒストグラムの追加
 			ply_act_tehai[pnum][kyoku[kyoku_index].act_hai[tmp_i]]++;

			// 赤牌の処理
			if( kyoku[kyoku_index].act_aka[tmp_i] == true ){
				ply_act_aka_count[pnum][kyoku[kyoku_index].act_hai[tmp_i]/10]++;
			}

			// 残り牌
			remain_hai_count--;

		// ----------------------------------------
		// ◎ 1.自摸時(リンシャン)の手牌数の増減
		// ----------------------------------------
		}else if( kyoku[kyoku_index].act_stat[tmp_i] == PLYRINSHAN ){

			// 手牌ヒストグラムの追加
 			ply_act_tehai[pnum][kyoku[kyoku_index].act_hai[tmp_i]]++;

			// 赤牌の処理
			if( kyoku[kyoku_index].act_aka[tmp_i] == true ){
				ply_act_aka_count[pnum][kyoku[kyoku_index].act_hai[tmp_i]/10]++;
			}

			// 残り牌
			remain_hai_count--;
			remain_rinshan_count--;

		// ----------------------------------------
		// ◎ 2.捨牌・自摸切り
		// ----------------------------------------
		}else if( kyoku[kyoku_index].act_stat[tmp_i] == PLYACTSUTE || 
		          kyoku[kyoku_index].act_stat[tmp_i] == PLYACTTSUMOGIRI ){

			// 手牌ヒストグラム減算
			ply_act_tehai[pnum][kyoku[kyoku_index].act_hai[tmp_i]]--;

			// 河設定
			ply_act_kawa[pnum][ply_act_kawa_count[pnum]] = kyoku[kyoku_index].act_hai[tmp_i];

			// 赤牌の処理
			if( kyoku[kyoku_index].act_aka[tmp_i] == true ){
				ply_act_aka_count[pnum][kyoku[kyoku_index].act_hai[tmp_i]/10]--;
				ply_act_kawa_aka[pnum][ply_act_kawa_count[pnum]] = true;
			}else{
				// 捨牌は黒牌設定
				ply_act_kawa_aka[pnum][ply_act_kawa_count[pnum]] = false;
			}

			// 河モード設定(リーチ状態確認)
			if( kyoku[kyoku_index].act_stat[tmp_i-1] == PLYACTRIICH ){
				ply_act_kawa_mode[pnum][ply_act_kawa_count[pnum]] = RIICHI_STAT_NUM;
			}else{
				ply_act_kawa_mode[pnum][ply_act_kawa_count[pnum]] = 0;
			}

			// 河枚数の加算
			ply_act_kawa_count[pnum]++;

		// ----------------------------------------
		// ◎ 3.鳴き捨牌
		// ----------------------------------------
		}else if( kyoku[kyoku_index].act_stat[tmp_i] == PLYACTNAKISUTE ){

			// 手牌ヒストグラム減算
			ply_act_tehai[pnum][kyoku[kyoku_index].act_hai[tmp_i]]--;

			// 河設定
			ply_act_kawa[pnum][ply_act_kawa_count[pnum]] = kyoku[kyoku_index].act_hai[tmp_i];

			// 赤牌の処理
			if( kyoku[kyoku_index].act_aka[tmp_i] == true ){
				ply_act_aka_count[pnum][kyoku[kyoku_index].act_hai[tmp_i]/10]--;
				ply_act_kawa_aka[pnum][ply_act_kawa_count[pnum]] = true;
			}else{
				// 捨牌は黒牌設定
				ply_act_kawa_aka[pnum][ply_act_kawa_count[pnum]] = false;
			}

			// 河モード設定
			ply_act_kawa_mode[pnum][ply_act_kawa_count[pnum]] = 0;

			// 河枚数の加算
			ply_act_kawa_count[pnum]++;

		// ----------------------------------------
		// ◎ 4.アクションごとの手牌数の増減 - ポン
		// ----------------------------------------
		}else if( kyoku[kyoku_index].act_stat[tmp_i] == PLYACTPON ){

			// 手牌から2枚減らす
			ply_act_tehai[pnum][kyoku[kyoku_index].act_hai[tmp_i]]-=2;

			// 鳴かれたプレーヤの捨牌を灰色に着色する。
			ply_act_kawa_mode[kyoku[kyoku_index].react_ply[tmp_i]][ply_act_kawa_count[kyoku[kyoku_index].react_ply[tmp_i]]-1] = 
			ply_act_kawa_mode[kyoku[kyoku_index].react_ply[tmp_i]][ply_act_kawa_count[kyoku[kyoku_index].react_ply[tmp_i]]-1] + HAI_COLOR_NUM_GRAY;

			// 裏牌の枚数処理
			if(com_no_chk_tehai_flg == true && pnum != HUM_PLY_SEKI_NUM){
				ply_act_tehaicount[pnum]-=3;
			}

		// ----------------------------------------
		// ◎ 5.アクションごとの手牌数の増減 - チー
		// ----------------------------------------
		}else if( kyoku[kyoku_index].act_stat[tmp_i] == PLYACTCHI ){

			// 鳴いた時の晒し番号抽出
			for(int tmp_j = 0; tmp_j < kyoku[kyoku_index].naki_count[pnum]; tmp_j++){
				if(kyoku[kyoku_index].naki_actid[pnum][tmp_j] == tmp_i){
					tmp_chi_num = tmp_j;
				}
			}

			// 鳴き牌削除
			ply_act_tehai[pnum][kyoku[kyoku_index].naki_idx[pnum][tmp_chi_num]]--;
			ply_act_tehai[pnum][kyoku[kyoku_index].naki_idx[pnum][tmp_chi_num]+1]--;
			ply_act_tehai[pnum][kyoku[kyoku_index].naki_idx[pnum][tmp_chi_num]+2]--;
			ply_act_tehai[pnum][kyoku[kyoku_index].naki_hai[pnum][tmp_chi_num]]++;

			// 鳴かれたプレーヤの捨牌を灰色に着色する。
			ply_act_kawa_mode[kyoku[kyoku_index].react_ply[tmp_i]][ply_act_kawa_count[kyoku[kyoku_index].react_ply[tmp_i]]-1] = 
			ply_act_kawa_mode[kyoku[kyoku_index].react_ply[tmp_i]][ply_act_kawa_count[kyoku[kyoku_index].react_ply[tmp_i]]-1] + HAI_COLOR_NUM_GRAY;

			// 裏牌の枚数処理
			if(com_no_chk_tehai_flg == true && pnum != HUM_PLY_SEKI_NUM){
				ply_act_tehaicount[pnum]-=3;
			}

		// ----------------------------------------
		// ◎ 5.アクションごとの手牌数の増減 - 明槓
		// ----------------------------------------
		}else if( kyoku[kyoku_index].act_stat[tmp_i] == PLYACTMINKAN ){

			// 牌の減算
			ply_act_tehai[pnum][kyoku[kyoku_index].act_hai[tmp_i]]-=3 ;

			// 鳴かれたプレーヤの捨牌を灰色に着色する。
			ply_act_kawa_mode[kyoku[kyoku_index].react_ply[tmp_i]][ply_act_kawa_count[kyoku[kyoku_index].react_ply[tmp_i]]-1] = 
			ply_act_kawa_mode[kyoku[kyoku_index].react_ply[tmp_i]][ply_act_kawa_count[kyoku[kyoku_index].react_ply[tmp_i]]-1] + HAI_COLOR_NUM_GRAY;

			// 裏牌の枚数処理
			if(com_no_chk_tehai_flg == true && pnum != HUM_PLY_SEKI_NUM){
				ply_act_tehaicount[pnum]-=3;
			}

		// ----------------------------------------
		// ◎ 6.アクションごとの手牌数の増減 - 暗槓
		// ----------------------------------------
		}else if( kyoku[kyoku_index].act_stat[tmp_i] == PLYACTANKAN ){
			ply_act_tehai[pnum][kyoku[kyoku_index].act_hai[tmp_i]]-=4 ;

			// 裏牌の枚数処理
			if(com_no_chk_tehai_flg == true && pnum != HUM_PLY_SEKI_NUM){
				ply_act_tehaicount[pnum]-=3;
			}

		// ----------------------------------------
		// ◎ 7.アクションごとの手牌数の増減 - 加槓
		// ----------------------------------------
		}else if( kyoku[kyoku_index].act_stat[tmp_i] == PLYACTKAKAN ){
			ply_act_tehai[pnum][kyoku[kyoku_index].act_hai[tmp_i]]--;

		// ----------------------------------------
		// ◎ 8.例外処理
		// ----------------------------------------
		}else{
			// その他の処理
		}

	}

	// ----------------------------------------
	// 赤牌確認(鳴き・晒し牌)
	// ----------------------------------------

	// テーブル情報の更新(全プレーヤー)
	for(int tmp_pnum = 0; tmp_pnum < PLAYER_MAX; tmp_pnum++){

		// プレーヤーごとの鳴き面子数
		for(int tmp_i = 0; tmp_i < kyoku[kyoku_index].naki_count[tmp_pnum]; tmp_i++){

			// 鳴き牌の赤牌の数を確認
			if( kyoku[kyoku_index].naki_actid[tmp_pnum][tmp_i] <= actid && 
			    kyoku[kyoku_index].naki_aka[tmp_pnum][tmp_i] > 0){

				// 鳴き情報の赤牌枚数だけ減らす
				ply_act_aka_count[tmp_pnum][kyoku[kyoku_index].naki_hai[tmp_pnum][tmp_i]/10] = 
				ply_act_aka_count[tmp_pnum][kyoku[kyoku_index].naki_hai[tmp_pnum][tmp_i]/10] - kyoku[kyoku_index].naki_aka[tmp_pnum][tmp_i];

				// リアクション(捨牌)で拾ってきたなら、+1する
				if(kyoku[kyoku_index].act_aka[kyoku[kyoku_index].naki_actid[tmp_pnum][tmp_i]-1]  == true       && 
				   ( kyoku[kyoku_index].act_stat[kyoku[kyoku_index].naki_actid[tmp_pnum][tmp_i]-1] == PLYACTSUTE || 
				     kyoku[kyoku_index].act_stat[kyoku[kyoku_index].naki_actid[tmp_pnum][tmp_i]-1] == PLYACTTSUMOGIRI || 
				     kyoku[kyoku_index].act_stat[kyoku[kyoku_index].naki_actid[tmp_pnum][tmp_i]-1] == PLYACTNAKISUTE  ) 
				   ){

					// 手牌ヒストグラムの加算
					ply_act_aka_count[tmp_pnum][kyoku[kyoku_index].naki_hai[tmp_pnum][tmp_i]/10]++;

				}
			}
		}
	}

}

/* ---------------------------------------------------------------------------------------------- */
// 最後牌の処理
/* ---------------------------------------------------------------------------------------------- */
void MJSTkinfo::Check_Actid_LastHai(int kyoku_index, int actid){

	// ----------------------------------------
	// 最後牌に関するアクションごとの処理)
	// ----------------------------------------

	int pnum;
	int tmp_tsumoari_shanten_total;
	int tmp_tsumoari_shanten_normal;
	int tmp_tsumoari_shanten_kokushi;
	int tmp_tsumoari_shanten_chitoi;

	// アクションプレーヤの定義
	pnum = kyoku[kyoku_index].act_ply[actid];

	// アクション牌の定義
	// tmp_act_hai  = kyoku[kyoku_index].act_hai[actid];

	// (デバグ用)アクション牌が規定の番号であるなら
	// if ( tmp_act_hai > 0 && tmp_act_hai < PAI_MAX){

	// ----------------------------------------
	// ◎ 1.最後牌：自摸
	// ----------------------------------------
	if ( kyoku[kyoku_index].act_stat[actid] == PLYACTTSUMO || 
	     kyoku[kyoku_index].act_stat[actid] == PLYRINSHAN  ){

		// ----------------------------------------
		// 1-1.自摸・捨牌情報の初期化
		// ----------------------------------------
		for(int tmp_pnum = 0; tmp_pnum < PLAYER_MAX; tmp_pnum++){

			ply_act_tsumo[tmp_pnum] = 0;
			ply_act_tsumo_aka[tmp_pnum] = false ;
			ply_act_tsumo_shanten[pnum] = 0;

			ply_act_sute[tmp_pnum]  = 0;
			ply_tbl_com_sutehai_statnum[tmp_pnum] = 0 ;
			ply_act_sute_aka[tmp_pnum]  = false ;

		}

		// ----------------------------------------
		// 1-2.自摸情報定義
		// ----------------------------------------
		ply_act_tsumo[pnum]      = kyoku[kyoku_index].act_hai[actid];
		ply_act_tsumo_aka[pnum]  = kyoku[kyoku_index].act_aka[actid];

		// ----------------------------------------
		// 1-3.自摸有り向聴数
		// ----------------------------------------
		if(com_no_chk_tehai_flg == false){
			ChkShanten(pnum);
		}

		// 仮置き
		// tmp_tsumoari_shanten = shanten_normal[pnum];
		tmp_tsumoari_shanten_total = shanten_total[pnum];
		tmp_tsumoari_shanten_normal = shanten_normal[pnum];
		tmp_tsumoari_shanten_kokushi = shanten_kokushi[pnum];
		tmp_tsumoari_shanten_chitoi = shanten_chitoi[pnum];

		// ----------------------------------------
		// 1-8.テーブル手牌ごとのシャンテン算出
		// ----------------------------------------
// 		if( shanten_normal[pnum] == 0){
 		if( shanten_total[pnum] == 0){
			settehaitbl_shanten(kyoku_index, actid, pnum);
		}

		// ----------------------------------------
		// 1-4.自摸牌の手牌ヒストグラムは-1する
		// ----------------------------------------
		if ( ply_act_tsumo[pnum] > 0 && ply_act_tsumo[pnum] < 38){
			ply_act_tehai[pnum][ply_act_tsumo[pnum]]--;
		}

		// 赤牌の処理
		if( ply_act_tsumo_aka[pnum] == true ){
			ply_act_aka_count[pnum][ply_act_tsumo[pnum]/10]--;
		}
		
		// ----------------------------------------
		// 1-5.自摸切りのシャンテン(自摸なしシャンテン)
		// ----------------------------------------
		if(com_no_chk_tehai_flg == false){
			ChkShanten(pnum);
		}
		// シャンテン数の設定
		ply_act_tsumo_shanten[pnum] = shanten_total[pnum];
		// 捨牌不可有無の設定
		if( shanten_total[pnum] == 0){
			ply_act_tsumo_can_sute[pnum] = true;
		}else{
			ply_act_tsumo_can_sute[pnum] = false;
		}
		// ----------------------------------------
		// 1-6.シャンテン数の設定
		// ----------------------------------------
		// shanten_normal[pnum] = tmp_tsumoari_shanten;
		shanten_total[pnum] = tmp_tsumoari_shanten_total;
		shanten_normal[pnum] = tmp_tsumoari_shanten_normal;
		shanten_kokushi[pnum] = tmp_tsumoari_shanten_kokushi;
		shanten_chitoi[pnum] = tmp_tsumoari_shanten_chitoi;

		// ----------------------------------------
		// 1-7.テーブル情報設定
		// ----------------------------------------
		settehaitbl(kyoku_index, actid, pnum);

	// ----------------------------------------
	// ◎ 2.最後牌：捨牌
	// ----------------------------------------
	}else if( kyoku[kyoku_index].act_stat[actid] == PLYACTSUTE      || 
			  kyoku[kyoku_index].act_stat[actid] == PLYACTTSUMOGIRI ){

		// ----------------------------------------
		// 2-1. 自摸無しシャンテンの算出
		// ----------------------------------------
		// naki_count[pnum] =  kyoku[kyoku_index].naki_count[pnum] - kyoku[kyoku_index].kakan_count[pnum] ;   // 鳴き面子数
		if(com_no_chk_tehai_flg == false){
			ChkShanten(pnum);
		}

		// ----------------------------------------
		// 2-2. 待牌設定
		// ----------------------------------------
		setmachi(kyoku_index, actid, pnum);

		// ----------------------------------------
		// 2-3. 自摸牌定義
		// ----------------------------------------
		if (kyoku[kyoku_index].act_stat[actid-1] == PLYACTRIICH){
			ply_act_tsumo[pnum]     = kyoku[kyoku_index].act_hai[actid-2];
			ply_act_tsumo_aka[pnum] = kyoku[kyoku_index].act_aka[actid-2];
		}else{
			ply_act_tsumo[pnum]     = kyoku[kyoku_index].act_hai[actid-1];
			ply_act_tsumo_aka[pnum] = kyoku[kyoku_index].act_aka[actid-1];
		}

		// ----------------------------------------
		// 2-4. 捨牌定義
		// ----------------------------------------
		ply_act_sute[pnum]     = kyoku[kyoku_index].act_hai[actid];
		ply_act_sute_aka[pnum] = kyoku[kyoku_index].act_aka[actid]; // 赤牌定義

		// ----------------------------------------
		// 2-5. ツモ分は減算
		// ----------------------------------------
		if(ply_act_tsumo[pnum] > 0 && ply_act_tsumo[pnum] < PAI_MAX){
			ply_act_tehai[pnum][ply_act_tsumo[pnum]]--;
			// 赤牌の処理
			if( ply_act_tsumo_aka[pnum] == true ){
				ply_act_aka_count[pnum][ply_act_tsumo[pnum]/10]--;
			}
		}

		// ----------------------------------------
		// 2-6. 捨牌分は加算
		// ----------------------------------------
		if(ply_act_sute[pnum] > 0 && ply_act_sute[pnum] < PAI_MAX){
			ply_act_tehai[pnum][ply_act_sute[pnum]]++;
			// 赤牌の処理
			if( ply_act_sute_aka[pnum] == true ){
				ply_act_aka_count[pnum][ply_act_sute[pnum]/10]++;
			}
		}

		// ----------------------------------------
		// 2-7. テーブル情報設定
		// ----------------------------------------
		settehaitbl(kyoku_index, actid, pnum);

		// ----------------------------------------
		// 2-8. 捨牌のテーブル位置決定
		// ----------------------------------------
		settehaitbl_sute_stat(kyoku_index, actid, pnum);

	// ----------------------------------------
	// ◎ 3.最後牌：鳴き捨牌
	// ----------------------------------------
	}else if( kyoku[kyoku_index].act_stat[actid] == PLYACTNAKISUTE ){

		// ----------------------------------------
		// 3-1. 自摸無しシャンテンの算出
		// ----------------------------------------
		// naki_count[pnum] =  kyoku[kyoku_index].naki_count[pnum] - kyoku[kyoku_index].kakan_count[pnum] ;   // 鳴き面子数
		// NormalShanten(pnum);
		if(com_no_chk_tehai_flg == false){
			ChkShanten(pnum);
		}

		// ----------------------------------------
		// 3-2. 待牌設定
		// ----------------------------------------
		setmachi(kyoku_index, actid, pnum);

		// ----------------------------------------
		// 3-3. 捨牌情報定義
		// ----------------------------------------
		ply_act_sute[pnum]     = kyoku[kyoku_index].act_hai[actid]; // 捨牌定義
		ply_act_sute_aka[pnum] = kyoku[kyoku_index].act_aka[actid]; // 赤牌定義

		// ----------------------------------------
		// 3-4. 捨牌の手牌ヒストグラムは+1する
		// ----------------------------------------
		ply_act_tehai[pnum][kyoku[kyoku_index].act_hai[actid]]++;

		// 赤牌の処理
		if( kyoku[kyoku_index].act_aka[actid] == true ){
			ply_act_aka_count[pnum][kyoku[kyoku_index].act_hai[actid]/10]--;
		}

		// ----------------------------------------
		// 3-5. テーブル情報設定
		// ----------------------------------------
		settehaitbl(kyoku_index, actid, pnum);

		// ----------------------------------------
		// 3-6. 捨牌のテーブル位置決定
		// ----------------------------------------
		settehaitbl_sute_stat(kyoku_index, actid, pnum);

		// ----------------------------------------
		// 3-7. 裏牌の枚数処理
		// ----------------------------------------
		if(com_no_chk_tehai_flg == true && pnum != HUM_PLY_SEKI_NUM){
			ply_act_tehaicount[pnum]++;
		}

	// ----------------------------------------
	// ◎ 4.最後牌：ポン、チー
	// ----------------------------------------
	// 最後がポン・チーなら自摸ありシャンテン算出
	}else if( kyoku[kyoku_index].act_stat[actid] == PLYACTPON ||
			  kyoku[kyoku_index].act_stat[actid] == PLYACTCHI ){

		// ----------------------------------------
		// 4-1. 自摸有り向聴数
		// ----------------------------------------
		// シャンテン確認(自摸あり)
		// naki_count[pnum] =  kyoku[kyoku_index].naki_count[pnum] - kyoku[kyoku_index].kakan_count[pnum] ;   // 鳴き面子数
		// NormalShanten(pnum);
		if(com_no_chk_tehai_flg == false){
			ChkShanten(pnum);
		}

		// ----------------------------------------
		// 4-2. 自摸・捨牌情報の初期化
		// ----------------------------------------
		for(int tmp_pnum = 0; tmp_pnum < PLAYER_MAX; tmp_pnum++){
			ply_act_tsumo[tmp_pnum] = 0;
			ply_act_sute[tmp_pnum]  = 0;
			ply_tbl_com_sutehai_statnum[tmp_pnum] = 0 ;
			ply_act_tsumo_aka[tmp_pnum] = false ;
			ply_act_sute_aka[tmp_pnum]  = false ;
		}

		// ----------------------------------------
		// 4-3. テーブル情報設定
		// ----------------------------------------
		settehaitbl(kyoku_index, actid, pnum);

		// ----------------------------------------
		// 4-4. 捨牌不可テーブルの更新
		// ----------------------------------------
		for(int tmp_i = 0; tmp_i < ply_act_tehaicount[pnum]; tmp_i++){
			ply_act_tehai_can_sute_tbl[pnum][tmp_i] = true;
		}

		// ----------------------------------------
		// 4-5. 裏牌の枚数処理
		// ----------------------------------------
		if(com_no_chk_tehai_flg == true && pnum != HUM_PLY_SEKI_NUM){
			// ply_act_tehaicount[pnum]++;
		}

	// ----------------------------------------
	// ◎ 5.最後牌：アンカン、ミンカン、カカン
	// ----------------------------------------
	// 最後がカンなら、初期化のみ
	}else if( kyoku[kyoku_index].act_stat[actid] == PLYACTMINKAN || 
	          kyoku[kyoku_index].act_stat[actid] == PLYACTANKAN  || 
	          kyoku[kyoku_index].act_stat[actid] == PLYACTKAKAN  ){

		// ----------------------------------------
		// 5-1. 自摸・捨牌情報の初期化
		// ----------------------------------------
		for(int tmp_pnum = 0; tmp_pnum < PLAYER_MAX; tmp_pnum++){

			ply_act_tsumo[tmp_pnum] = 0;
			ply_act_sute[tmp_pnum]  = 0;
			ply_tbl_com_sutehai_statnum[tmp_pnum] = 0 ;
			ply_act_tsumo_aka[tmp_pnum] = false ;
			ply_act_sute_aka[tmp_pnum]  = false ;

		}

		// ----------------------------------------
		// 5-2. 自摸なしシャンテン計算
		// ----------------------------------------


		// ----------------------------------------
		// 5-3. テーブル情報設定
		// ----------------------------------------
		settehaitbl(kyoku_index, actid, pnum);

	// ----------------------------------------
	// ◎ 6.最後牌：自摸和了時
	// ----------------------------------------
	}else if( kyoku[kyoku_index].act_stat[actid] == PLYTSUMOAGARI){

		// ----------------------------------------
		// 和了牌を含めたシャンテン計算
		// ----------------------------------------
		if(com_no_chk_tehai_flg == false){
			ChkShanten(pnum);
		}

		// ----------------------------------------
		// 自摸分を-1
		// ----------------------------------------
		ply_act_tehai[pnum][kyoku[kyoku_index].act_hai[actid]]--;  // 自摸牌の戻し

		// 赤牌の処理
		if( kyoku[kyoku_index].act_aka[actid] == true ){
			ply_act_aka_count[pnum][kyoku[kyoku_index].act_hai[actid]/10]--;
		}

		// ----------------------------------------
		// テーブル情報設定
		// ----------------------------------------
		settehaitbl(kyoku_index, actid, pnum);

	// ----------------------------------------
	// ◎ 7.最後牌：局結果表示(自摸和了)
	// ----------------------------------------
	}else if( kyoku[kyoku_index].act_stat[actid]   == KYOKURESULT && 
	          kyoku[kyoku_index].act_stat[actid-1] == PLYTSUMOAGARI){

		// ----------------------------------------
		// 和了牌を含めたシャンテン計算
		// ----------------------------------------

		// シャンテン計算
		if(com_no_chk_tehai_flg == false){
			ChkShanten(kyoku[kyoku_index].act_ply[actid-1]);
		}

		// ----------------------------------------
		// 自摸分を-1
		// ----------------------------------------
		ply_act_tehai[kyoku[kyoku_index].act_ply[actid-1]][kyoku[kyoku_index].act_hai[actid-1]]--;             // 自摸牌の戻し

		// 赤牌の処理
		if( kyoku[kyoku_index].act_aka[actid] == true ){
			ply_act_aka_count[kyoku[kyoku_index].act_ply[actid-1]][kyoku[kyoku_index].act_hai[actid-1]/10]--;  // 赤牌戻し
		}

		// ----------------------------------------
		// テーブル情報設定
		// ----------------------------------------
		settehaitbl(kyoku_index, actid, kyoku[kyoku_index].act_ply[actid-1]);

	// ----------------------------------------
	// ◎ 8.最後牌：ロン和了時
	// ----------------------------------------
	}else if( kyoku[kyoku_index].act_stat[actid] == PLYACTRON){

		// ----------------------------------------
		// 8-1. 和了牌を含めたシャンテン計算
		// ----------------------------------------
		ply_act_tehai[pnum][kyoku[kyoku_index].act_hai[actid]]++;   // ロン牌を+1

		// シャンテン計算
		if(com_no_chk_tehai_flg == false){
			ChkShanten(pnum);
		}

		ply_act_tehai[pnum][kyoku[kyoku_index].act_hai[actid]]--;   // ロン牌の戻し

		// ----------------------------------------
		// 8-2. テーブル情報設定
		// ----------------------------------------
		settehaitbl(kyoku_index, actid, pnum);

	// ----------------------------------------
	// ◎ 9.最後牌：その他、自分プレーヤ以外
	// ----------------------------------------
	}else{

	}

	// ----------------------------------------
	// テーブル情報の更新(その他プレーヤー)
	// ----------------------------------------
	for(int tmp_pnum = 0; tmp_pnum < PLAYER_MAX; tmp_pnum++){

		// 最後アクションプレーヤーでない場合
		if ( kyoku[kyoku_index].act_stat[actid] != HAIPAI && tmp_pnum != pnum){

			// ----------------------------------------
			// x-1. テーブル情報設定
			// ----------------------------------------
			settehaitbl(kyoku_index, actid, tmp_pnum);

			// ----------------------------------------
			// x-2.自摸無しシャンテンの算出
			// ロン和了	、自摸和了時の場合、振込プレーヤーの特殊処理が必要となる。
			// それ以外はシャンテンを算出する
			// ----------------------------------------
			if( kyoku[kyoku_index].act_stat[actid] != PLYACTRON && 
				kyoku[kyoku_index].act_stat[actid] != PLYTSUMOAGARI){ 

				// シャンテン算出
				if(com_no_chk_tehai_flg == false){
					ChkShanten(tmp_pnum);
				}

			}

		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 手牌テーブル設定用
/* ---------------------------------------------------------------------------------------------- */
void MJSTkinfo::settehaitbl(int kyoku_index, int actid, int pnum){

	// 赤牌情報の仮設定
	int tmp_aka_man;
	int tmp_aka_pin;
	int tmp_aka_sou;

	tmp_aka_man = ply_act_aka_count[pnum][0];
	tmp_aka_pin = ply_act_aka_count[pnum][1];
	tmp_aka_sou = ply_act_aka_count[pnum][2];

	// ----------------------------------------
	// テーブル情報の格納
	// ----------------------------------------

	// クライアントモードのCOMプレーヤーは処理しない
	if(com_no_chk_tehai_flg == false || pnum == HUM_PLY_SEKI_NUM){

		// 手牌数の初期化
		ply_act_tehaicount[pnum] = 0;

		// 手牌テーブルの設定
		for(int tmp_i = 1; tmp_i < PAI_MAX; tmp_i++){

			// 手牌の数だけ繰り返し
			for(int tmp_j = 0; tmp_j < ply_act_tehai[pnum][tmp_i]; tmp_j++){

				// 手牌テーブル設定
				ply_act_tehaitbl[pnum][ply_act_tehaicount[pnum]]=tmp_i;

				// 赤牌テーブル設定
				if(tmp_i == 5 && tmp_aka_man > 0){
					ply_act_tehai_tbl_aka[pnum][ply_act_tehaicount[pnum]] = true;
					tmp_aka_man--;
				}else if(tmp_i == 15 && tmp_aka_pin > 0){
					ply_act_tehai_tbl_aka[pnum][ply_act_tehaicount[pnum]] = true;
					tmp_aka_pin--;
				}else if(tmp_i == 25 && tmp_aka_sou > 0){
					ply_act_tehai_tbl_aka[pnum][ply_act_tehaicount[pnum]] = true;
					tmp_aka_sou--;
				}else{
					ply_act_tehai_tbl_aka[pnum][ply_act_tehaicount[pnum]] = false;
				}

				// 手牌数を+1
				ply_act_tehaicount[pnum]++;

			}
		}
	}
}

/* ---------------------------------------------------------------------------------------------- */
// 捨牌のテーブル位置設定
/* ---------------------------------------------------------------------------------------------- */
void MJSTkinfo::settehaitbl_sute_stat(int kyoku_index, int actid, int pnum){

	// 手牌の数だけ繰り返し
	for(int tmp_i = 0; tmp_i < ply_act_tehaicount[pnum]; tmp_i++){
		// 捨牌であれば
		if(ply_act_tehaitbl[pnum][tmp_i]      == ply_act_sute[pnum]     && 
		   ply_act_tehai_tbl_aka[pnum][tmp_i] == ply_act_sute_aka[pnum] ){
			// 位置定義
			ply_tbl_com_sutehai_statnum[pnum] = tmp_i;
			break;
		}
	}

		// 自摸切りであれば
		if( ply_act_tsumo[pnum]     == ply_act_sute[pnum]     && 
		    ply_act_tsumo_aka[pnum] == ply_act_sute_aka[pnum] ){
			// 位置定義
			ply_tbl_com_sutehai_statnum[pnum] = ply_act_tehaicount[pnum];
		}

}

/* ---------------------------------------------------------------------------------------------- */
// 牌テーブルごとのシャンテン
/* ---------------------------------------------------------------------------------------------- */
void MJSTkinfo::settehaitbl_shanten(int kyoku_index, int actid, int pnum){

	// ----------------------------------------
	// 手牌ごとのシャンテン
	// ----------------------------------------
	for(int tmp_i = 0; tmp_i < ply_act_tehaicount[pnum]; tmp_i++){
		ply_act_tehai[pnum][ply_act_tehaitbl[pnum][tmp_i]]--;  // テーブル牌ごとの仮抜き取り
		if(com_no_chk_tehai_flg == false){
			ChkShanten(pnum);
		}
		// 手牌ごとのシャンテン数の設定
		ply_act_tehai_shanten_tbl[pnum][tmp_i] = shanten_total[pnum]; 
		// 捨牌禁止テーブルの設定
		if( shanten_total[pnum] == 0){
			ply_act_tehai_can_sute_tbl[pnum][tmp_i] = true;
		}else{
			ply_act_tehai_can_sute_tbl[pnum][tmp_i] = false;
		}
		ply_act_tehai[pnum][ply_act_tehaitbl[pnum][tmp_i]]++;  // 仮抜き取りの戻し
	}

}

/* ---------------------------------------------------------------------------------------------- */
// 待牌確認
/* ---------------------------------------------------------------------------------------------- */
void MJSTkinfo::setmachi(int kyoku_index, int actid, int pnum){

	// ----------------------------------------
	// 待牌確認
	// ----------------------------------------

	// 待牌数の初期化
	ply_act_machi_count[pnum] = 0;

	// テンパイ確認
//	if( shanten_normal[pnum] == 0){
	if( shanten_total[pnum] == 0){

		// 待牌確認
		for(int tmp_pai_num = 1; tmp_pai_num < PAI_MAX; tmp_pai_num++){

			if( tmp_pai_num != 10 && tmp_pai_num != 20 && tmp_pai_num != 30){

				// 自摸牌の仮設定
				ply_act_tehai[pnum][tmp_pai_num]++;

				// シャンテン確認
				if(com_no_chk_tehai_flg == false){
					ChkShanten(pnum);
				}

				// 和了であるなら
				if( shanten_total[pnum] == -1){

					// 待牌設定
					ply_act_machi_hai[pnum][ply_act_machi_count[pnum]] = tmp_pai_num;
					ply_act_machi_count[pnum]++;

				}

				// 自摸牌の仮設定の解除
				ply_act_tehai[pnum][tmp_pai_num]--;

			}

		}

	}

	// ----------------------------------------
	// 待牌のフリテン確認
	// ----------------------------------------


}

/* ---------------------------------------------------------------------------------------------- */
// 向聴数確認(メイン)
/* ---------------------------------------------------------------------------------------------- */
void MJSTkinfo::ChkShanten(int pnum){

	// シャンテン算出
	NormalShanten(pnum);
	KokushiShanten(pnum);

	// 総合シャンテンの設定
	if(shanten_normal[pnum] > shanten_chitoi[pnum] && shanten_kokushi[pnum] > shanten_chitoi[pnum]){
		shanten_total[pnum] = shanten_chitoi[pnum];
	}else if(shanten_normal[pnum] > shanten_kokushi[pnum]){
		shanten_total[pnum] = shanten_kokushi[pnum];
	}else{
		shanten_total[pnum] = shanten_normal[pnum];
	}

}

/* ---------------------------------------------------------------------------------------------- */
// 向聴数確認(国士無双)
/* ---------------------------------------------------------------------------------------------- */
void MJSTkinfo::KokushiShanten(int pnum){

	int  tmp_kokushi_hai_count = 0;
	bool tmp_kokushi_atama_flg = false;

	// 国士牌確認
	for(int tmp_i=0; tmp_i<13; tmp_i++){
		if(ply_act_tehai[pnum][kokushi_hai_num[tmp_i]] > 0){
			tmp_kokushi_hai_count++;
		}
		if(ply_act_tehai[pnum][kokushi_hai_num[tmp_i]] > 1){
			tmp_kokushi_atama_flg = true;
		}
	}

	// 国士の頭あり確認
	if(tmp_kokushi_atama_flg == true){
		tmp_kokushi_hai_count++;
	}

	// シャンテン算出
	shanten_kokushi[pnum] = 13 - tmp_kokushi_hai_count;

}

/* ---------------------------------------------------------------------------------------------- */
// 向聴数確認(通常)
/* ---------------------------------------------------------------------------------------------- */
void MJSTkinfo::NormalShanten(int pnum){

	// ----------------------------------------
	// 初期化
	// ----------------------------------------
	shanten_normal[pnum] = 8;
	tmp_shanten          = 0;
	tmp_atama_count      = 0;
	tmp_mentu_count      = 0;
	tmp_taatu_count      = 0;

	tmp_atama_hai = 0;   // 頭牌番号の初期化

	int tmp_chitoi_atama_count = 0;

	// ----------------------------------------
	// 処理開始
	// ----------------------------------------
	for(int hai=1; hai<PAI_MAX; hai++){

		// 頭処理確認
		if(ply_act_tehai[pnum][hai] >= 2){

			tmp_atama_count++;
			tmp_chitoi_atama_count++;       // チートイ処理向け
			ply_act_tehai[pnum][hai] -= 2;
			tmp_atama_hai = hai;   // 頭牌番号の設定
			mentu_cut(pnum, 1);
			ply_act_tehai[pnum][hai] += 2;
			tmp_atama_hai = 0;     // 頭牌番号の無効化
			tmp_atama_count--;

		}
	}

	// ----------------------------------------
    // 頭なしの場合
	// ----------------------------------------
    mentu_cut(pnum, 1);

	// ----------------------------------------
    // チートイシャンテン
	// ----------------------------------------
	shanten_chitoi[pnum] = 6 - tmp_chitoi_atama_count;

}

/* ---------------------------------------------------------------------------------------------- */
// 面子削除処理
/* ---------------------------------------------------------------------------------------------- */
void MJSTkinfo::mentu_cut(int pnum, int hai){

	// ----------------------------------------
	// 0枚はスキップ
	// ----------------------------------------
	for(;!ply_act_tehai[pnum][hai]; hai++);

	// ----------------------------------------
	// 無ければターツ検索
	// ----------------------------------------
	if( hai >= PAI_MAX ){
		taatu_cut(pnum, 1);

		// 処理の返し
		return;
	}

	// ----------------------------------------
	// アンコ情報セット
	// ----------------------------------------
	if(ply_act_tehai[pnum][hai] >= 3){

		tmp_mentu_stat[tmp_mentu_count] = ANKO;      // 面子情報設定
		tmp_mentu_hai[tmp_mentu_count]  = hai;       // 牌番号設定
		tmp_mentu_count++;
		ply_act_tehai[pnum][hai]-=3;
		mentu_cut(pnum, hai);                               // メンツカットの再起処理
		ply_act_tehai[pnum][hai]+=3;
		tmp_mentu_count--;
		tmp_mentu_stat[tmp_mentu_count] = NOMENTSU;   // 面子情報設定
		tmp_mentu_hai[tmp_mentu_count]  = hai;        // 牌番号設定

	}

	// ----------------------------------------
	// シュンツ情報セット
	// ----------------------------------------
	if(ply_act_tehai[pnum][hai+1] && ply_act_tehai[pnum][hai+2] && hai<30){

		tmp_mentu_stat[tmp_mentu_count] = SHUNTSU;  // 面子情報設定
		tmp_mentu_hai[tmp_mentu_count]  = hai;      // 牌番号設定
		tmp_mentu_count++;
		ply_act_tehai[pnum][hai]--;
		ply_act_tehai[pnum][hai+1]--;
		ply_act_tehai[pnum][hai+2]--;
		mentu_cut(pnum, hai);   // メンツカットの再起処理
		ply_act_tehai[pnum][hai]++;
		ply_act_tehai[pnum][hai+1]++;
		ply_act_tehai[pnum][hai+2]++;
		tmp_mentu_count--;
		tmp_mentu_stat[tmp_mentu_count] = NOMENTSU;   // 面子情報設定
		tmp_mentu_hai[tmp_mentu_count]  = hai;        // 牌番号設定

	}

	// ----------------------------------------
	// 次のメンツカットの再起処理
	// ----------------------------------------
	mentu_cut(pnum, hai+1);

}

/* ---------------------------------------------------------------------------------------------- */
// 塔子削除処理
/* ---------------------------------------------------------------------------------------------- */
void MJSTkinfo::taatu_cut(int pnum, int hai){

	// ----------------------------------------
	// 0枚はスキップ
	// ----------------------------------------
	for(;!ply_act_tehai[pnum][hai]; hai++);

	// ----------------------------------------
	// 無ければシャンテン算出
	// ----------------------------------------
	if( hai >= PAI_MAX ){

		// シャンテン数の算出
		// tmp_shanten = 8-tmp_mentu_count*2-tmp_taatu_count-tmp_atama_count;
		// tmp_shanten = 8-naki_count[pnum]*2-tmp_mentu_count*2-tmp_taatu_count-tmp_atama_count;
		tmp_shanten = 8-naki_count_none_kakan[pnum]*2-tmp_mentu_count*2-tmp_taatu_count-tmp_atama_count;

		if( tmp_shanten < shanten_normal[pnum]){

			// 通常シャンテンの仮置き
			shanten_normal[pnum] = tmp_shanten;

			// アタマ情報セット
			atama_count = tmp_atama_count;
			atama_hai   = tmp_atama_hai;

			// メンツ情報セット
			mentu_count = tmp_mentu_count;
			for(int tmp_i=0;tmp_i<tmp_mentu_count;tmp_i++){
				mentu_stat[tmp_i] = tmp_mentu_stat[tmp_i];  // 面子情報設定
				mentu_hai[tmp_i]  = tmp_mentu_hai[tmp_i];   // 牌番号設定
			}

			// ターツ情報セット
			taatu_count = tmp_taatu_count;
			for(int tmp_i=0;tmp_i<tmp_taatu_count;tmp_i++){
				taatsu_stat[tmp_i]=tmp_mentu_stat[tmp_i];  // ターツ情報設定
				taatsu_hai[tmp_i]=tmp_taatsu_hai[tmp_i];   // 牌番号設定
			}

		}

		// 処理の返し
		return;
	}

	// ----------------------------------------
	// ターツ情報セット
	// ----------------------------------------
	// if(tmp_mentu_count+tmp_taatu_count<4){
	// if( naki_count[pnum]  +tmp_mentu_count+tmp_taatu_count < 4 ){
	if( naki_count_none_kakan[pnum]+tmp_mentu_count+tmp_taatu_count < 4 ){

		// トイツカット
		if( ply_act_tehai[pnum][hai] == 2 ){
			tmp_taatsu_stat[tmp_mentu_count] = TOITSU;   // ターツ情報設定
			tmp_taatsu_hai[tmp_mentu_count]  = hai;      // 牌番号設定
			tmp_taatu_count++;
			ply_act_tehai[pnum][hai]-=2;
			taatu_cut(pnum, hai);
			ply_act_tehai[pnum][hai]+=2;
			tmp_taatu_count--;
			tmp_taatsu_stat[tmp_mentu_count] = NOMENTSU;  // ターツ情報設定
			tmp_taatsu_hai[tmp_mentu_count]  = hai;       // 牌番号設定
		}

		// 両面カット
		if( ply_act_tehai[pnum][hai+1] && hai<30 ){

			tmp_taatsu_stat[tmp_mentu_count] = TOITSU;   // ターツ情報設定
			tmp_taatsu_hai[tmp_mentu_count]  = hai;      // 牌番号設定
			tmp_taatu_count++;
			ply_act_tehai[pnum][hai]--, ply_act_tehai[pnum][hai+1]--;
			taatu_cut(pnum, hai);
			ply_act_tehai[pnum][hai]++, ply_act_tehai[pnum][hai+1]++;
			tmp_taatu_count--;
			tmp_taatsu_stat[tmp_mentu_count] = NOMENTSU;  // ターツ情報設定
			tmp_taatsu_hai[tmp_mentu_count]  = hai;       // 牌番号設定
		}

		// カンチャンカット
		if( ply_act_tehai[pnum][hai+2]&& hai<30 && hai%10<=8 ){

			tmp_taatsu_stat[tmp_mentu_count] = TOITSU;   // ターツ情報設定
			tmp_taatsu_hai[tmp_mentu_count]  = hai;      // 牌番号設定
			tmp_taatu_count++;
			ply_act_tehai[pnum][hai]--, ply_act_tehai[pnum][hai+2]--;
			taatu_cut(pnum, hai);
			ply_act_tehai[pnum][hai]++, ply_act_tehai[pnum][hai+2]++;
			tmp_taatu_count--;
			tmp_taatsu_stat[tmp_mentu_count] = NOMENTSU;  // ターツ情報設定
			tmp_taatsu_hai[tmp_mentu_count]  = hai;       // 牌番号設定
		}
	}

	// ----------------------------------------
	// 次のターツ再起処理
	// ----------------------------------------
	taatu_cut(pnum, hai+1);

}

/* ---------------------------------------------------------------------------------------------- */
// ソース終了
/* ---------------------------------------------------------------------------------------------- */
