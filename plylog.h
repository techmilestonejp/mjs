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

#ifndef PLYLOG_H_INCLUDED
#define PLYLOG_H_INCLUDED

#include "corelog.h"

/* --------------------------------------------------------------- */
// 変数定義
/* --------------------------------------------------------------- */

class MJSPlylog
{

	/* ----------------------------- */
	// 公開関数定義 
	/* ----------------------------- */

	// 公開関数定義
	public:

	// 個別ログ出力
	MJSCorelog corelog;

	// ログ名
	char *logname;

	// ログ出力レベル
	int loglevel;

	/* ----------------------------- */
	// 関数定義
	/* ----------------------------- */

	// コンストラクタ定義
    MJSPlylog(){};

	// デストラクタ定義
    ~MJSPlylog(){};

	/* ----------------------------- */
	// Playerクラス向け関数
	/* ----------------------------- */

	// クラス初期化・後処理
	void PlylogInit();                                    // 得点計算クラスの初期化
	void PlylogPost();                                    // 得点計算クラスの終了処理

	// 卓開始・終了
	void PlylogTakuStart(MJSTkinfo *tk);
	void PlylogTakuEnd(MJSTkinfo *tk);

	// 局開始・終了
	void PlylogKyokuStart(MJSTkinfo *tk);
	void PlylogKyokuEnd(MJSTkinfo *tk);

	// 配牌処理
	void PlylogAllHaipai(MJSTkinfo *tk);
	void PlylogHaipai(MJSTkinfo *tk,int pnum);

	// 自摸処理
	void PlylogTsumoHai(MJSTkinfo *tk,int pnum);

	// 自摸捨牌処理
	void PlylogTsumoSute(MJSTkinfo *tk,int pnum);
	void PlylogAllTsumoSute(MJSTkinfo *tk);
	void PlylogSute(MJSTkinfo *tk,int pnum);

	// プレーヤー情報
	void PlylogPlayer(MJSTkinfo *tk, int pnum);
	void PlylogDisplayPlyinfo(MJSTkinfo *tk);

	// 鳴き
	void PlylogOtherNaki(MJSTkinfo *tk);
	void PlylogDisplayPlyNaki(MJSTkinfo *tk);

	// リアクション表示
	void PlylogOwnReact(MJSTkinfo *tk);

	// 全員のリアクション結果の表示
	void PlylogAllReact(MJSTkinfo *tk);

	// 和了アクション表示
	void PlylogAgari(MJSTkinfo *tk,int pnum);

	// 和了結果出力
	void PlylogDisplayPlyAgari(MJSTkinfo *tk);
	void PlylogNormalYaku(MJSTkinfo *tk);
	void PlylogYakuman(MJSTkinfo *tk);

	// 流局
	void PlylogRyukyoku(MJSTkinfo *tk);
	void PlylogyHaigire(MJSTkinfo *tk);

	/* ----------------------------- */
	// AI向け関数
	/* ----------------------------- */
	// PlaeyAI詳細情報
	void PlylogDisplayPlyAIinfo(MJSTkinfo *tk, MJSPlyAI *ai);

};

#endif/* PLYLOG_H_INCLUDED */

/* ---------------------------------------------------------------------------------------------- */
// ソース終了
/* ---------------------------------------------------------------------------------------------- */
