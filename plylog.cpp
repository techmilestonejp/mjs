/* ---------------------------------------------------------------------------------------------- 
 * 
 * プログラム概要 ： Newさくら麻雀(Ver0.1.2：ログビュアー実装版)
 * バージョン     ： 0.1.2.12(役実装・リーチ実装)
 * プログラム名   ： mjs.exe
 * ファイル名     ： plylog.h 
 * クラス名       ： MJSPlylog
 * 処理概要       ： Plyログ処理
 * Ver0.0.1作成日 ： 2010/10/03 00:00:00
 * Ver0.0.8作成日 ： 2011/11/26 17:31:00
 * Ver0.1.2作成日 ： 2022/10/23 23:38:32
 * 最終更新日     ： 2022/10/31 22:29:08
 * 
 * Copyright (c) 2010-2022 Techmilestone, All rights reserved.
 * 
 * ---------------------------------------------------------------------------------------------- */

#include "plylog.h"

/* --------------------------------------------------------------- */
// 卓開始
/* --------------------------------------------------------------- */
void MJSPlylog::PlylogTakuStart(MJSTkinfo *tk){

	if( loglevel > 0 ){

		// ファイル初期化
		show.PlylogFileInit(logname);

		// 共通関数呼び出し
		// show.ShowTakuStart(tk);
	
		// 卓情報表示
		// show.ShowRule(tk);
	
		//出力終了処理
		show.PlylogFilePost();

	}

}

/* --------------------------------------------------------------- */
// 卓終了
/* --------------------------------------------------------------- */
void MJSPlylog::PlylogTakuEnd(MJSTkinfo *tk){

	if( loglevel > 0 ){

		// ファイル初期化
		show.PlylogFileInit(logname);

		// 共通関数呼び出し
		// show.ShowTakuEnd(tk);

		// 出力終了処理
		show.PlylogFilePost();

	}

}

/* --------------------------------------------------------------- */
// 局開始
/* --------------------------------------------------------------- */
void MJSPlylog::PlylogKyokuStart(MJSTkinfo *tk){

	if( loglevel > 0 ){

		// ファイル初期化
		show.PlylogFileInit(logname);

		// 共通関数呼び出し
		// show.ShowKyokuStart(tk);

		//出力終了処理
		show.PlylogFilePost();

	}

}

/* --------------------------------------------------------------- */
// 局終了
/* --------------------------------------------------------------- */
void MJSPlylog::PlylogKyokuEnd(MJSTkinfo *tk){

	if( loglevel > 0 ){

		// ファイル初期化
		show.PlylogFileInit(logname);

		// 共通関数呼び出し
		// show.ShowKyokuEnd(tk);

		// 出力終了処理
		show.PlylogFilePost();

	}

}

/* --------------------------------------------------------------- */
// 配牌処理(全員)
/* --------------------------------------------------------------- */
void MJSPlylog::PlylogAllHaipai(MJSTkinfo *tk){

	if( loglevel > 0 ){

		// ファイル初期化
		show.PlylogFileInit(logname);

		// 区切り線
		show.ShowBorder();

		//卓情報表示
		// show.ShowAllHaipai(tk);
		// show.PlylogPrint("\n");

		//出力終了処理
		show.PlylogFilePost();

	}

}

/* --------------------------------------------------------------- */
// 配牌処理
/* --------------------------------------------------------------- */
void MJSPlylog::PlylogHaipai(MJSTkinfo *tk,int pnum){

	if( loglevel > 0 ){

		// ファイル初期化
		show.PlylogFileInit(logname);

		// 区切り線
		show.ShowBorder();

		// アクション表示
		// show.ShowAct(tk, pnum);

		// 卓情報表示
		// show.ShowHaipai(tk,pnum);
		show.PlylogPrint("\n");

		//出力終了処理
		show.PlylogFilePost();

	}

}

/* --------------------------------------------------------------- */
// ツモ時手牌
/* --------------------------------------------------------------- */
void MJSPlylog::PlylogTsumoHai(MJSTkinfo *tk,int pnum){

	if( loglevel > 0 ){

		//ファイル初期化
		show.PlylogFileInit(logname);

		//区切り線
		show.ShowBorder();

		// 卓情報表示
		// show.ShowKyokuInfo(tk);
		// show.PlylogPrint("\n");

		// プレーヤー情報表示
		// show.ShowKyokuPlyInfo(tk, pnum);
		// show.PlylogPrint("\n");

		// アクション表示
		// show.ShowAct(tk, pnum);

		// ツモ牌表示
		// show.PlylogPrint("ツモ牌　");
		// show.ShowNormalHai(tk->pinfo[pnum].Tsumo);
		// show.PlylogPrint("\n");

		// 河表示
		// show.ShowSutehai(tk, pnum);
		// show.PlylogPrint("\n");

		//手牌表示
		show.ShowTehaiTsumo(tk, pnum);
		show.PlylogPrint("\n"); 

		// 向聴情報
		show.ShowShanten(tk, pnum);

		// 待ち情報
		show.ShowMatchiHai(tk, pnum);

		// ツモ時向聴
		show.ShowTsumoShanten(tk, pnum);

		//出力終了処理
		show.PlylogFilePost();

	}

}

/* --------------------------------------------------------------- */
// ツモ・捨牌の出力(自分のみ)
/* --------------------------------------------------------------- */
void MJSPlylog::PlylogTsumoSute(MJSTkinfo *tk,int pnum){

	if( loglevel > 0 ){

		//ファイル初期化
		show.PlylogFileInit(logname);

		//区切り線
		show.ShowBorder();

		//プレーヤー情報表示
		show.ShowKyokuPlyInfo(tk, pnum);
		show.PlylogPrint("\n");

		//アクション表示
		show.ShowAct(tk, pnum);

		//区切り線
		show.ShowBorder();

		//卓情報表示
		show.ShowKyokuInfo(tk);
		show.PlylogPrint("\n");

		//プレーヤー情報表示
		show.ShowKyokuPlyInfo(tk, pnum);
		show.PlylogPrint("\n");

		//ツモ牌表示
		show.PlylogPrint("　　　");
		show.PlylogPrint("ツモ牌　");
		show.ShowNormalHai(tk->pinfo[pnum].Tsumo);
		show.PlylogPrint("\n");

		//捨牌表示
		show.PlylogPrint("　　　");
		show.ShowSutehai(tk, pnum);
		show.PlylogPrint("\n");

		//手牌表示
		show.ShowTsumoSute(tk, pnum);
		show.PlylogPrint("\n"); 

		//向聴情報
		show.ShowShanten(tk, pnum);

		//待ち情報
		show.ShowMatchiHai(tk, pnum);

		//出力終了処理
		show.PlylogFilePost();

	}

}

/* --------------------------------------------------------------- */
// 捨牌出力(全員・手牌あり)
/* --------------------------------------------------------------- */
void MJSPlylog::PlylogAllTsumoSute(MJSTkinfo *tk){

	if( loglevel > 0 ){

		//変数定義
		int i;

		//ファイル初期化
		show.PlylogFileInit(logname);

		//区切り線
		show.ShowBorder();

		//卓情報表示
		show.ShowKyokuInfo(tk);
		show.PlylogPrint("\n");

		//手牌表示
		for(i = 0; i < 4; i++){

			// 区切り線	
			show.PlylogPrint("\n");

			//各プレーヤー情報
			show.ShowKyokuPlyInfo(tk, i);
			show.PlylogPrint("\n");

			if( i == tk->pnum ){

				//ツモ・捨て表示
				show.PlylogPrint("ツモ牌　");
				show.ShowNormalHai(tk->pinfo[i].Tsumo);
				show.PlylogPrint("　　　");

			}

			show.ShowSutehai(tk, i);
			show.PlylogPrint("\n");

			if( i == tk->pnum ){

				show.ShowTsumoSute(tk, i);
				show.PlylogPrint("\n"); 

			}else{

				show.ShowTehai(tk, i);
				show.PlylogPrint("\n"); 
			}

			//向聴情報
			show.ShowShanten(tk, i);

			//待ち情報
			show.ShowMatchiHai(tk, i);

		}

		//出力終了処理
		show.PlylogFilePost();

	}

}

/* --------------------------------------------------------------- */
// 捨牌のみの出力
/* --------------------------------------------------------------- */
void MJSPlylog::PlylogSute(MJSTkinfo *tk,int pnum){

	if( loglevel > 0 ){

		//ファイル初期化
		show.PlylogFileInit(logname);

		//区切り線
		show.ShowBorder();

		//プレーヤー情報表示
		show.ShowKyokuPlyInfo(tk, pnum);
		show.PlylogPrint("\n");

		//アクション表示
		show.ShowAct(tk, pnum);

		//区切り線
		show.ShowBorder();

		//卓情報表示
		show.ShowKyokuInfo(tk);
		show.PlylogPrint("\n");

		//プレーヤー情報表示
		show.ShowKyokuPlyInfo(tk, pnum);
		show.PlylogPrint("\n");

		//捨牌表示
		show.ShowSutehai(tk, pnum);
		show.PlylogPrint("\n");

		//出力終了処理
		show.PlylogFilePost();

	}

}

/* --------------------------------------------------------------- */
// 自分のリアクション表示
/* --------------------------------------------------------------- */
void MJSPlylog::PlylogOwnReact(MJSTkinfo *tk){

	if( loglevel > 0 ){

		//ファイル初期化
		show.PlylogFileInit(logname);

		//区切り線
		show.ShowBorder();

		//プレーヤー情報表示
		show.PlylogPrint("自プレーヤーのリアクション：");
		show.PlylogPrint("\n");

		//アクション表示
		show.ShowAct(tk, tk->tkid);

		//出力終了処理
		show.PlylogFilePost();

	}

}

/* --------------------------------------------------------------- */
// 全員の鳴きアクション表示
/* --------------------------------------------------------------- */
void MJSPlylog::PlylogAllReact(MJSTkinfo *tk){

	int i;

	if( loglevel > 0 ){

		//ファイル初期化
		show.PlylogFileInit(logname);

		//区切り線
		show.ShowBorder();

		//プレーヤー情報表示
		show.ShowKyokuPlyInfo(tk, tk->pnum);
		show.PlylogPrint("\n");

		//動作表示
		for(i = 0; i < 4; i++){

			//アクション表示
			show.ShowAct(tk, i);

		}
	
		//出力終了処理
		show.PlylogFilePost();

	}
}

/* --------------------------------------------------------------- */
// 鳴きアクション表示
/* --------------------------------------------------------------- */
void MJSPlylog::PlylogDisplayPlyNaki(MJSTkinfo *tk){

	if( loglevel > 0 ){

		//ファイル初期化
		show.PlylogFileInit(logname);

		//区切り線
		show.ShowBorder();

		//卓情報表示
		show.ShowKyokuInfo(tk);
		show.PlylogPrint("\n");

		//プレーヤー情報表示
		show.ShowKyokuPlyInfo(tk, tk->pnum);
		show.PlylogPrint("\n");

		// 鳴きアクション表示
		show.ShowNakiAct(tk, tk->pnum);

		// 出力終了処理
		show.PlylogFilePost();

	}

}

/* --------------------------------------------------------------- */
// 和了アクション表示
/* --------------------------------------------------------------- */
void MJSPlylog::PlylogAgari(MJSTkinfo *tk,int pnum){

	if( loglevel > 0 ){

		//ファイル初期化
		show.PlylogFileInit(logname);

		//区切り線
		show.ShowBorder();

		// 和了表示
		show.ShowAgariInfo(tk);

		//出力終了処理
		show.PlylogFilePost();

	}

}

/* --------------------------------------------------------------- */
// DLL向けの簡易版の和了表示
/* --------------------------------------------------------------- */
void MJSPlylog::PlylogDisplayPlyAgari(MJSTkinfo *tk){

	if( loglevel > 0 ){

		// ファイル初期化
		show.PlylogFileInit(logname);

		// 区切り線
		show.ShowBorder();

		// 和了表示
		show.ShowClientCalcAgariInfo(tk);

		//出力終了処理
		show.PlylogFilePost();

	}

}

/* --------------------------------------------------------------- */
// 流局結果出力
/* --------------------------------------------------------------- */
void MJSPlylog::PlylogRyukyoku(MJSTkinfo *tk){

	if( loglevel > 0 ){

		// ファイル初期化
		show.PlylogFileInit(logname);

		// 区切り線
		show.ShowBorder();

		// 和了結果表示
		show.PlylogPrint("　　　流局　　　");

		// 改行
		show.PlylogPrint("\n");

		// 区切り線
		show.ShowBorder();

		// 聴牌有無

		// 出力終了処理
		show.PlylogFilePost();

	}

}

/* --------------------------------------------------------------- */
// PlaeyAI詳細情報
/* --------------------------------------------------------------- */
void MJSPlylog::PlylogDisplayPlyAIinfo(MJSTkinfo *tk, MJSPlyAI *ai){

	if( loglevel > 0 ){

		//ファイル初期化
		show.PlylogFileInit(logname);

		//AI情報表示
		show.ShowPlyAIinfo(tk,ai);

		//出力終了処理
		show.PlylogFilePost();

	}

}

/* --------------------------------------------------------------- */
// ファイルここまで
/* --------------------------------------------------------------- */
