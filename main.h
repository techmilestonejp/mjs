/* ---------------------------------------------------------------------------------------------- 
 * 
 * プログラム概要 ： さくら麻雀(Ver0.1.2.1：開発版)
 * バージョン     ： 0.1.2.1.222(Mainクラスの導入)
 * プログラム名   ： mjs.exe
 * ファイル名     ： main.h
 * クラス名       ： MJSMain
 * 処理概要       ： メイン処理
 * Ver0.0.8.0作成 ： 2012/07/29 11:09:51
 * Ver0.1.0.0作成 ： 2022/05/03 18:50:06
 * Ver0.1.1.0作成 ： 2022/06/30 21:19:01
 * Ver0.1.2.0作成 ： 2022/08/31 22:19:54
 * Ver0.1.2.1作成 ： 2024/10/30 16:40:44
 * 最終更新日     ： 2024/11/02 09:38:41
 * 
 * Copyright (c) 2010-2024 TechMileStoraJP, All rights reserved.
 * 
 * ---------------------------------------------------------------------------------------------- */

#pragma once

#ifndef MJSMAIN_H_INCLUDED
#define MJSMAIN_H_INCLUDED

#include <windows.h>
#include "stdafx.h"
#include "DxLib.h"

#include "display.h"
#include "gui.h"

#include "taku.h"
#include "tkinfo.h"
#include "player.h"
#include "client.h"

#include "tklog.h"
#include "tpread.h"

/* ---------------------------------------------------------------------------------------------- */
// クラス定義
/* ---------------------------------------------------------------------------------------------- */
class MJSMain
{

	// ------------------------------------------------------------------- 
	// バージョン情報
	// ------------------------------------------------------------------- 
	public:

	// バージョン情報
	int ver1;
	int ver2;
	int ver3;
	int ver4;
	int ver5;

	// バージョン情報(MJSlog)
	int log_ver1;
	int log_ver2;
	int log_ver3;
	int log_ver4;

	// ------------------------------------------------------------------- 
	// フレーム処理
	// ------------------------------------------------------------------- 

	// フレーム処理用定数
	int SAMPLE_FRAME_COUNT = 60;        // フレームのサンプル数
	int FPS                = 60;        // 想定のFPS値 (待ち時間の算出用)

	// FPS算出用変数(フレーム定義)
	int frame_count;                    // サンプルフレームのカウンタ数
	int total_frame_count;              // 処理したフレームの合計数

	// FPS算出用変数(時間定義)
	int checkpoint_time;                // 定点時刻(チェックポイントごとの時刻)
	int wait_time;                      // 待ち時間(Sleep関数を利用するために単位はミリ秒)

	// FPS算出用変数(FPS数)
	float ave_fps;                      // 実測のFPS値

	// ------------------------------------------------------------------- 
	// モード定義
	// ------------------------------------------------------------------- 

	// ビューアーモードの有無
	bool haifu_read_mode;

	// ------------------------------------------------------------------- 
	// クラス定義
	// ------------------------------------------------------------------- 

	// クラス定義
	MJSGui gui;                         // GUI操作クラス(マウス操作情報)
	MJSTkinfo tk;                       // 卓情報クラス
	MJSTaku taku;                       // 麻雀卓ゲーム処理クラス
	MJSPlayer* ply;                     // プレーヤークラス(ポインタ定義)
	MJSDisplay dsp;                     // 画面表示処理クラス
	MJSMjaiClient cli;                  // MJAIクライアントクラス
	MJSReadTplog tp;                    // 東風荘ログ読込クラス
	MJSReadMjai  mjai;                  // MJAIログ読込みクラス
	MJSTklog log;                       // mjs卓ゲームログクラス

	/* ----------------------------- */
	// コンストラクタ
	/* ----------------------------- */

	// コンストラクタ定義
	MJSMain(){};

	// デストラクタ定義
	~MJSMain(){};

	/* ----------------------------- */
	// 関数定義
	/* ----------------------------- */

	// 全体処理
	void MainInit();                    // 開始処理
	void MainExe();                     // 実行処理
	void MainExe_ChkStat();             // 実行処理中のステータス確認
	void MainPost();                    // 終了処理

	// Fps算出処理
	void FpsParamInit();
	void FpsUpdate();
	void FpsWait();

	// 卓ステータスの初期化と終了処理
	void MainTakuInit();                // メインクラスからの卓ゲーム開始処理
	void MainTakuPost();                // メインクラスからの卓ゲーム終了処理

	// オープニング画面
	void OpeningInit();
	void OpeningExe();
	void OpeningPost();

	// ゲームモード
	void PlayingInit();
	void PlayingExe();
	void PlayingPost();

	// ビューアーモード
	void ViewingInit();
	void ViewingExe();
	void ViewingPost();

	// 検証モード
	void RunningInit();
	void RunningExec();
	void RunningPost();

	// Mjaiクライアントモード
	void ClientInit();
	void ClientExec();
	void ClientPost();

	// Mjaiサーバモード
	void MJServerInit();
	void MJServerExe();
	void MJServerPost();

	// 設定画面
	void SettingInit();
	void SettingExe();
	void SettingPost();

};

#endif/* MJSMAIN_H_INCLUDED */

/* ---------------------------------------------------------------------------------------------- */
// ソース終了
/* ---------------------------------------------------------------------------------------------- */
