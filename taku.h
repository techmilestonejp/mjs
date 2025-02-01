/* ---------------------------------------------------------------------------------------------- 
 * 
 * プログラム概要 ： Newさくら麻雀(MJAIクライアント実装版)
 * バージョン     ： 0.1.2.0.168(鳴有無プレート実装)
 * プログラム名   ： mjs.exe
 * ファイル名     ： taku.h
 * クラス名       ： MJSTaku
 * 処理概要       ： 麻雀卓ゲーム処理クラス
 * Ver0.0.8作成日 ： 2011/11/23 21:26:17
 * Ver0.0.8更新日 ： 2012/05/04 08:58:06
 * Ver0.1.0作成日 ： 2022/06/04 10:13:26
 * Ver0.1.1作成日 ： 2022/06/30 21:19:01
 * Ver0.1.2作成日 ： 2022/08/31 22:19:54
 * 最終更新日     ： 2024/05/25 09:28:29
 * 
 * Copyright (c) 2010-2024 Techmilestone, All rights reserved.
 * 
 * ---------------------------------------------------------------------------------------------- */

#ifndef TAKU_H_INCLUDED
#define TAKU_H_INCLUDED

#include <windows.h>
#include "stdafx.h"

#include "tkinfo.h"
#include "player.h"

/* ---------------------------------------------------------------------------------------------- 
 * クラス定義
 * ---------------------------------------------------------------------------------------------- */

class MJSTaku
{

	// 公開定義
	public:

	/* ----------------------------------------------------------------------
	 * コンストラクタ
	 * ---------------------------------------------------------------------- */

	//コンストラクタ
    MJSTaku(){};

	//デストラクタ
    ~MJSTaku(){};

	/* ----------------------------------------------------------------------
	 * 関数
	 * ---------------------------------------------------------------------- */

	// 卓クラス初期化・終了処理
	void TakuInit();                    // 卓クラスの初期化処理
	void TakuPost();                    // 卓クラスの終了処理

	// システム関連処理
	void SetNowTime(MJSTkinfo *tk);     // 現在日時の取得

	// メイン処理
	void CheckTakuStatus(MJSTkinfo *tk, MJSPlayer *ply, bool tmp_push_flg);

	// 卓開始処理
	void TakuGameInit(MJSTkinfo *tk, MJSPlayer *ply);

	// 局開始処理
	void KyokuInit(MJSTkinfo *tk, MJSPlayer *ply);

	// プレーヤーの席決め
	void SetPlySeki(MJSTkinfo *tk, MJSPlayer *ply);   // プレーヤーの席決め

	// 牌山設定
	void ActSeepai(MJSTkinfo *tk);                    // 洗牌処理
	void SetTimeSeedNum(MJSTkinfo *tk);               // 時間によるシード値の設定
	void SetYamahai(MJSTkinfo *tk);                   // 牌山設定(指定の値を入れる)

	// ドラ設定
	void SetDora(MJSTkinfo *tk);

	// 配牌処理
	void SetHaipai(MJSTkinfo *tk, MJSPlayer *ply);

	// ツモ処理
	void TakuActTsumo(MJSTkinfo *tk, MJSPlayer *ply, int tmp_tsumo_hai, int tmp_tsumo_hai_index, bool tmp_rinshan_mode);

	// 自摸後アクション処理(捨て、ツモ和了等の処理を定義)
	void TakuActPostTsumo(MJSTkinfo *tk, MJSPlayer *ply);                  // メイン用
	void TakuActPostTsumo_HumPly(MJSTkinfo *tk);                           // HUM用
	void TakuActPostTsumo_ComPly(MJSTkinfo *tk, MJSPlayer *ply);           // COM用

	// 自摸後アクション処理・個別処理
	void TakuActSutehai(MJSTkinfo *tk, int sute_hai, bool sute_aka);       // 捨牌処理
	void TakuActTsumoGiri(MJSTkinfo *tk);                                  // 自摸切り処理
	void TakuActTsumoAgari(MJSTkinfo *tk);                                 // 自摸和了
	void TakuActRiichi(MJSTkinfo *tk);                                     // リーチ処理
	void TakuActAnkan(MJSTkinfo *tk, int kan_hai);                         // 暗槓処理
	void TakuActKakan(MJSTkinfo *tk, int kan_hai, int kan_aka);            // 加槓処理

	// 鳴き後アクション処理(鳴き捨て処理の定義)
	void TakuActPostNaki(MJSTkinfo *tk, MJSPlayer *ply);                   // メイン用
	void TakuActPostNaki_HumPly(MJSTkinfo *tk);                            // HUM用
	void TakuActPostNaki_ComPly(MJSTkinfo *tk, MJSPlayer *ply);            // COM用

	// 鳴き確認
	void ChkPlayNaki(MJSTkinfo *tk, MJSPlayer *ply);                       // メイン用

	// 鳴き実行・個別処理
	void SetPlayNaki(MJSTkinfo *tk, MJSPlayer *ply);
	void TakuActRonAgari(MJSTkinfo *tk);
	void TakuActPon(MJSTkinfo *tk);
	void TakuActChi(MJSTkinfo *tk);
	void TakuActMinkan(MJSTkinfo *tk);

	// 和了処理
	void SetAgari(MJSTkinfo *tk, MJSPlayer *ply);

	// 荒牌処理
	void SetHowanpai(MJSTkinfo *tk, MJSPlayer *ply);

	// 次局初期化処理
	void KyokuNextInit(MJSTkinfo *tk, MJSPlayer *ply);

	// 卓終了情報設定
	void SetTakuReSult(MJSTkinfo *tk, MJSPlayer *ply);

	// 卓終了処理
	void TakuGameEnd(MJSTkinfo *tk, MJSPlayer *ply);

};

#endif /* TAKU_H_INCLUDED */

/* ---------------------------------------------------------------------------------------------- 
 * ソース終了
 * ---------------------------------------------------------------------------------------------- */
