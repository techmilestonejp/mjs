/* ---------------------------------------------------------------------------------------------- 
 * 
 * プログラム概要 ： さくら麻雀(Ver0.1.2：開発版)
 * バージョン     ： 0.1.2.1.224(桃色牌・黄色牌の表示実装)
 * プログラム名   ： mjs.exe
 * ファイル名     ： dispparts.cpp
 * クラス名       ： MJSDisplayParts
 * 処理概要       ： パーツ描写クラス
 * 初回作成日     ： 2023/05/20 10:59:12
 * Ver0.1.2作成日 ： 2023/05/20 10:59:12
 * Ver0.1.3.0pre  ： 2024/03/19 23:55:27
 * Ver0.1.3.1pre  ： 2024/04/05 19:50:22
 * 最終更新日     ： 2024/11/02 15:07:30
 * 
 * Copyright (c) 2010-2024 TechMileStoraJP, All rights reserved.
 * 
 * ---------------------------------------------------------------------------------------------- */

#include "dispparts.h"

/* ---------------------------------------------------------------------------------------------- */
// 画面初期化処理
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispPartsInit(){

	// ----------------------------------------
	// 事前処理
	// ----------------------------------------

	// 牌番号仮置き
	int tmpPaiImgNum[] = {

		37,
		 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
		10,11,12,13,14,15,16,17,18,19,
		20,21,22,23,24,25,26,27,28,29,
		30,31,32,33,34,35,36,37,37,37,

	};

	// 牌番号格納
	for(int i = 0; i < PAI_MAX; i++){
		// 牌番号を格納
		PaiImgNum[i] = tmpPaiImgNum[i];
	}

	// -----------------------------
	// プレート文字定義
	// -----------------------------

	wsprintf(plt_name[PLT_RIICHI]   , "リーチ");
	wsprintf(plt_name[PLT_PON]      , "ポ　ン");
	wsprintf(plt_name[PLT_KAN]      , "カ　ン");
	wsprintf(plt_name[PLT_CHI]      , "チ　ー");
	wsprintf(plt_name[PLT_AGARI]    , "和　了");
	wsprintf(plt_name[PLT_NEXT]     , "次　へ");


	wsprintf(plt_name[PLT_NAKIARI]  , "鳴　有");
	wsprintf(plt_name[PLT_NAKINASHI], "鳴　無");

	wsprintf(plt_name[PLT_YES]      , "は　い");
	wsprintf(plt_name[PLT_YES]      , "いいえ");

	// ----------------------------------------
	// メッセージ文字列表示
	// ----------------------------------------

	// 局名
	wsprintf(kyokutbl[0],"東一局");
	wsprintf(kyokutbl[1],"東二局");
	wsprintf(kyokutbl[2],"東三局");
	wsprintf(kyokutbl[3],"東四局");
	wsprintf(kyokutbl[4],"南一局");
	wsprintf(kyokutbl[5],"南二局");
	wsprintf(kyokutbl[6],"南三局");
	wsprintf(kyokutbl[7],"南四局");

	// 役情報取得
	SetYakuName();

	// ----------------------------------------
	// 変数初期化
	// ----------------------------------------

	desp_tehai_mode = 0; // (0:ライナー表示、1:スクエア表示、2:文字列表示)

}

/* ---------------------------------------------------------------------------------------------- */
// 画面初期化処理
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispPartsPost(){

}

/* ---------------------------------------------------------------------------------------------- */
// 共通関数 - 役名設定
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::SetYakuName(){

	// 役名定義・通常役
	wsprintf(yakuname[NOYAKU],          "役なし　　　");
	wsprintf(yakuname[RIICH],           "リーチ　　　");
	wsprintf(yakuname[WRIICH],          "ダブルリーチ");
	wsprintf(yakuname[IPPATSU],         "一発　　　　");
	wsprintf(yakuname[CHINISO],         "清一色　　　");
	wsprintf(yakuname[HONISO],          "混一色　　　");
	wsprintf(yakuname[JUNCHAN],         "純全帯　　　");
	wsprintf(yakuname[RYANPEKO],        "二盃口　　　");
	wsprintf(yakuname[HONROTO],         "混老頭　　　");
	wsprintf(yakuname[SHOSANGEN],       "小三元　　　");
	wsprintf(yakuname[ITSU],            "一気通貫　　");
	wsprintf(yakuname[SANDOKOU],        "三色同刻　　");
	wsprintf(yakuname[SANDOJUN],        "三色同順　　");
	wsprintf(yakuname[SANKANTSU],       "三槓子　　　");
	wsprintf(yakuname[SANANKO],         "三暗刻　　　");
	wsprintf(yakuname[TOITOI],          "対々和　　　");
	wsprintf(yakuname[CHANTA],          "混全帯　　　");
	wsprintf(yakuname[CHITOI],          "七対子　　　");
	wsprintf(yakuname[PINFU],           "平和　　　　");
	wsprintf(yakuname[TANYAO],          "断公九　　　");
	wsprintf(yakuname[IPEKO],           "一盃口　　　");
	wsprintf(yakuname[BAKAZE],          "場風牌　　　");
	wsprintf(yakuname[ZIKAZE],          "自風牌　　　");
	wsprintf(yakuname[YAKUHAI],         "三元牌　　　");
	wsprintf(yakuname[YAKUHAIHAKU],     "三元牌白　　");
	wsprintf(yakuname[YAKUHAIHATSU],    "三元牌発　　");
	wsprintf(yakuname[YAKUHAICHUN],     "三元牌中　　");
	wsprintf(yakuname[HAITEI],          "海底摸月　　");
	wsprintf(yakuname[HOUTEI],          "河底撈魚　　");
	wsprintf(yakuname[RINSHAN],         "嶺上開花　　");
	wsprintf(yakuname[CHANKAN],         "槍槓　　　　");
	wsprintf(yakuname[TSUMO],           "門前清自摸和");
	wsprintf(yakuname[DORA],            "表ドラ　　　");
	wsprintf(yakuname[URADORA],         "裏ドラ　　　");
	wsprintf(yakuname[AKAHAI],          "赤牌　　　　");
	wsprintf(yakuname[RENHO],           "人和(満貫)　");
	wsprintf(yakuname[NAGASHIMAN],      "流し満貫　　");
	wsprintf(yakuname[UNKNOWN_YAKU],    "手役不明　　");

	// 役名定義・役満
	wsprintf(yakumanname[NOYAKUMAN],    "役なし　　　");
	wsprintf(yakumanname[TENHO],        "天和　　　　");
	wsprintf(yakumanname[CHIHO],        "地和　　　　");
	wsprintf(yakumanname[CHUREN9MEN],   "九連九面待　");
	wsprintf(yakumanname[CHUREN],       "九連宝燈　　");
	wsprintf(yakumanname[KOKUSHI13MEN], "国士十三面待");
	wsprintf(yakumanname[KOKUSHI],      "国士無双　　");
	wsprintf(yakumanname[DAISANGEN],    "大三元　　　");
	wsprintf(yakumanname[DAISUSHI],     "大四喜和　　");
	wsprintf(yakumanname[SHOSUSHI],     "小四喜和　　");
	wsprintf(yakumanname[TSUISO],       "字一色　　　");
	wsprintf(yakumanname[CHINROTO],     "清老頭　　　");
	wsprintf(yakumanname[RYUISO],       "緑一色　　　");
	wsprintf(yakumanname[SUKANTSU],     "四槓子　　　");
	wsprintf(yakumanname[SUANKOTANKI],  "四暗刻単騎　");
	wsprintf(yakumanname[SUANKO],       "四暗刻　　　");
	wsprintf(yakumanname[RENHOYAKUMAN], "人和　　　　");

	// 流局種別名定義
	wsprintf(ryukyokuname[NORKK],         "流局設定なし　　");
	wsprintf(ryukyokuname[HOWANPAI],      "流局：荒牌　　　");
	wsprintf(ryukyokuname[SUFURENDA],     "流局：四風連打　");
	wsprintf(ryukyokuname[RIICHI4PLY],    "流局：四人リーチ");
	wsprintf(ryukyokuname[RON3PLY],       "流局：三人ロン　");
	wsprintf(ryukyokuname[TEHAI9HAI],     "流局：九種九牌　");
	wsprintf(ryukyokuname[NAGASHIMANGAN], "流局：流し満貫　");
	wsprintf(ryukyokuname[UNKNOWNRKK],    "流局：その他流局");

}

/* ---------------------------------------------------------------------------------------------- */
// 画面初期化処理
/* ---------------------------------------------------------------------------------------------- */
int MJSDisplayParts::DispPartsFrameInit(){

	// Log.txtの出力抑止
	SetOutApplicationLogValidFlag(FALSE);

	// ウインドウモードにする
	// DxLib_Initより前に行う
    if( ChangeWindowMode(TRUE) != DX_CHANGESCREEN_OK ) {

		// 異常終了
		return -1;

	}

	// ウィンドウサイズ変更
	SetGraphMode( 1024 , 768 , 32 );
	SetWindowSize( 1024 , 768 );

	// ウインドウがアクティブではない状態でも処理を続行する
 	SetAlwaysRunFlag(TRUE);

	// 2つ以上同時に起動できるかどうかを設定する。
 	SetDoubleStartValidFlag(TRUE);

	// マウス表示オン
    SetMouseDispFlag(TRUE);

	// 正常終了
	return 0;

}

/* ---------------------------------------------------------------------------------------------- */
// DXLib初期化
/* ---------------------------------------------------------------------------------------------- */
int MJSDisplayParts::DispPartsLibInit(){

	// DXライブラリ初期化
	if (DxLib_Init() != 0){

		// 異常終了
		return -1;

	}

	// 描画先を裏画面に設定
	SetDrawScreen(DX_SCREEN_BACK); 

	// 画像読み込み
	DispPartsReadPic();

	// 正常終了
	return 0;
}

/* ---------------------------------------------------------------------------------------------- */
// 画像読み込み
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispPartsReadPic(){

	// ----------------------------------------
	// 画像読み込み
	// ----------------------------------------

	// 背景画像
	backpic = LoadGraph("bmp\\back.bmp");                   // 背景
	title   = LoadGraph("bmp\\title.bmp");                  // タイトル
	banner  = LoadGraph("bmp\\banner.bmp");                 // バナー
	pltimg  = LoadGraph("bmp\\plt.bmp");                    // プレート
	center_pltimg = LoadGraph("bmp\\center_plt.png");       // 卓センタープレート

	// ボタン画像
	but02      = LoadGraph( "bmp\\but02.bmp");              // ボタン02
	but03      = LoadGraph( "bmp\\but03.bmp");              // ボタン03
	but_red    = LoadGraph( "bmp\\but_red.bmp");            // 赤色ボタン
	but_green  = LoadGraph( "bmp\\but_green.bmp");          // 緑色ボタン
	but_blue   = LoadGraph( "bmp\\but_bule.bmp");           // 青色ボタン
	but_yellow = LoadGraph( "bmp\\but_yellow.bmp");         // 黄色ボタン

	// 背景色
 	gray    = LoadGraph( "bmp\\gray.bmp" );                 // 灰背景用
 	lgray   = LoadGraph( "bmp\\lgray.bmp");                 // 灰背景用_横牌
 	blue    = LoadGraph( "bmp\\blue.bmp" );                 // 青背景用
 	lblue   = LoadGraph( "bmp\\lblue.bmp");                 // 青背景用_横牌
 	pink    = LoadGraph( "bmp\\pink.bmp" );                 // 桃背景用
 	lpink   = LoadGraph( "bmp\\lpink.bmp");                 // 桃背景用_横牌
 	yellow  = LoadGraph( "bmp\\yellow.bmp" );               // 黄背景用
 	lyellow = LoadGraph( "bmp\\lyellow.bmp");               // 黄背景用_横牌


	// 画像を分割して、配列に保存
	LoadDivGraph( "bmp\\pai.bmp",      40, 10, 4,  HAI_XSIZE,  HAI_YSIZE, Pai    );  
	LoadDivGraph( "bmp\\paibase.bmp",   6,  2, 3,         24,         36, PaiBase);  
 
	// 画像の分割格納・横牌
	LoadDivGraph( "bmp\\lpai.bmp",      40, 10, 4,         32,         24, LPai    ); 
	LoadDivGraph( "bmp\\lpaibase.bmp",   6,  2, 3,         32,         29, LPaiBase); 

}

/* ---------------------------------------------------------------------------------------------- */
// DXLib終了処理
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispPartsLibPost(){

	// DXライブラリ使用の終了処理
	DxLib_End();

}

/* ---------------------------------------------------------------------------------------------- */
// 初期描画処理
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispPartsClearDraw(){

	// 画面を消す
	ClearDrawScreen();

	// 背景表示
	DrawGraph( 0, 0, backpic, TRUE );

}

/* ---------------------------------------------------------------------------------------------- */
// フリップ処理
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispPartsFlip(){

	// 裏画面を表画面に反映
	ScreenFlip();

}

/* ---------------------------------------------------------------------------------------------- */
// 共通関数 - 文字出力
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispString(int x, int y, char *str){

	// 文字出力
	DrawFormatString( x, y, GetColor(255,255,255), str);

}

/* ---------------------------------------------------------------------------------------------- */
// パーツ表示/オープニングタイトル
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispOpeningTitle(int ver1, int ver2, int ver3, int ver4, int ver5){

	// タイトル画像
	DrawGraph( 350, 100, title, TRUE );

	// タイトル用のバージョン表示
	DrawFormatString(800, 300, GetColor(255,255,255), "Ver. %d.%d.%d.%d.%d", ver1, ver2, ver3, ver4, ver5);

	// フッター
	DrawFormatString( 425, 720, GetColor(255,255,255), "Copyright (c) 2010-2024 TechMilestone All Rights Reserved.");

}

/* ---------------------------------------------------------------------------------------------- */
// パーツ表示/バナー表示
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispBunner(int ver1, int ver2, int ver3, int ver4, int ver5){

	// バナー表示
	DrawGraph( 884, 0, banner, TRUE ) ;

	// バージョン情報表示
	wsprintf(tmp_disp_msg, "Ver %d.%d.%d.%d.%d", ver1, ver2, ver3, ver4, ver5);
	DispString( 870, 45, tmp_disp_msg );
}

/* ---------------------------------------------------------------------------------------------- */
// パーツ表示/センタープレート表示
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispCenterPlt(int x, int y){

	// センタープレート表示
	DrawGraph( x, y, center_pltimg, TRUE ) ;

}

/* ---------------------------------------------------------------------------------------------- */
// パーツ表示 - マウスポイント
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispMousepoint(int x, int y, int msx,int msy, int b0, int b1){

	// マウスポイント表示
	wsprintf(tmp_disp_msg, "X=%4d Y=%3d B[0]=%d B[1]=%d", msx, msy, b0, b1);
	DispString( x, y, tmp_disp_msg );

}

/* ---------------------------------------------------------------------------------------------- */
// パーツ表示 - FPSフレーム
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispFps(int x, int y, float mFps, int total_frame_count, int frame_count){

	// FPSフレーム表示
	DrawFormatString(x, y, GetColor(255,255,255), "TotalFrCnt:%6d FrCnt:%4d FPS：%03.1f", total_frame_count, frame_count, mFps);

}

/* ---------------------------------------------------------------------------------------------- */
// パーツ表示・プレート表示
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispPltline(int x, int y, int plt_range, bool plt_mode[]){

	// プレート表示
	for(int tmp_i = 0; tmp_i < PLTLINE_COUNT ; tmp_i++ ) {
	    if( plt_mode[tmp_i] == true ) {
			// プレート表示
			DrawGraph       ( x+plt_range*tmp_i,    y,   pltimg, TRUE );
			// 文字表示
			DrawFormatString( x+plt_range*tmp_i+16, y+7, GetColor(255,255,255), plt_name[tmp_i]);
		}
	}

}

/* ---------------------------------------------------------------------------------------------- */
// パーツ表示・鳴きありなしプレート
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispPltNakiAriNashi(int x, int y, bool plt_naki_stat){

	// プレート表示
	DrawGraph( x, y, pltimg, TRUE );

	// 文字表示
	if( plt_naki_stat == true ) {
		DrawFormatString( x+16, y+7, GetColor(255,255,255), plt_name[PLT_NAKIARI]);
	}else{
		DrawFormatString( x+16, y+7, GetColor(255,255,255), plt_name[PLT_NAKINASHI]);
	}

}

/* ---------------------------------------------------------------------------------------------- */
// ボタン表示
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispButton(int x, int y, LBPartsButColor but_color){

	// ボタン表示
	if(but_color == PARTS_BUT_BLUE){
		DrawGraph( x, y, but_blue, TRUE );
	}else if(but_color == PARTS_BUT_GREEN){
		DrawGraph( x, y, but_green, TRUE );
	}else if(but_color == PARTS_BUT_YELLOW){
		DrawGraph( x, y, but_yellow, TRUE );
	}else if(but_color == PARTS_BUT_RED){
		DrawGraph( x, y, but_red, TRUE );
	}else{
		DrawGraph( x, y, but_blue, TRUE );
	}
}

/* ---------------------------------------------------------------------------------------------- */
// 情報操作ボタン
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispInfoButton(int thinfo_x, int tkinfo_x, int plyinfo_x, int quit_x, int y){

	// 情報操作ボタン表示
	DrawGraph( thinfo_x,  y, but_blue,   TRUE );
	DrawGraph( tkinfo_x,  y, but_blue,   TRUE );
	DrawGraph( plyinfo_x, y, but_yellow, TRUE );
	DrawGraph( quit_x,    y, but_red,    TRUE );

}

/* ---------------------------------------------------------------------------------------------- */
// Actidボタン
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispActidButton(int kyoid_x, int actid_x, int y){

	// ビューアーモード用局ID、ACTIDボタン
	DrawGraph( kyoid_x, y, but02, TRUE );         // 局INDEX変更
	DrawGraph( actid_x, y, but03, TRUE );         // ActID変更

}

/* ---------------------------------------------------------------------------------------------- */
// 場決め・卓結果ボタン
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispBagimeButton(int bagime_x, int tkend_x, int y){

	// ビューアーモード用場決め・卓結果ボタン
	DrawGraph( bagime_x, y, but_green, TRUE );    // 場決め表示
	DrawGraph( tkend_x,  y, but_green, TRUE );    // 卓結果表示

}

/* ---------------------------------------------------------------------------------------------- */
// 席変更ボタン
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispSekiButton(int x, int y){

	// ビューアーモード用席変更ボタン
	DrawGraph( x, y, but02, TRUE );

}

/* ---------------------------------------------------------------------------------------------- */
// ラインボタン表示(ビューアーモード)
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispViewerModeButton(){

}

/* ---------------------------------------------------------------------------------------------- */
// ドラ表示
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispDora(int x, int y, int doracount, int dora[], bool dora_aka[], int dora_actid[], int tmp_act_id){

	// ドラ牌表示
	for(int tmp_i = 0; tmp_i < doracount ; tmp_i++ ) {
		// ドラ牌表示するアクション番号確認
		if(dora_actid[tmp_i] <= tmp_act_id){
			DispHai( x+24*tmp_i, y, dora[tmp_i], dora_aka[tmp_i], false, 0, 0);
		}else{
			DispHai( x+24*tmp_i, y, 0, false, false, 0, 0);
		}
	}

	// 裏向き牌
	for(int tmp_i = 0; tmp_i < 5-doracount ; tmp_i++ ) {
			DispHai( x+24*(doracount+tmp_i), y, 0, false, false, 0, 0);
	}

}

/* ---------------------------------------------------------------------------------------------- */
// パーツ表示・牌表示
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispHai(int x, int y, int hai, bool aka, bool hai_turn, int haimode, int haicolor){

	// デバッグ用
	if ( hai < 0 || hai > PAI_MAX){
		hai=0;
	}

	// 赤牌の場合
	      if( hai == MAN5NUM && aka == true ){
		hai=10;
	}else if( hai == PIN5NUM && aka == true ){
		hai=20;
	}else if( hai == SOU5NUM && aka == true ){
		hai=30;
	}

	// 牌表示メイン
	if ( hai == 0 ){
			DrawGraph( x, y, PaiBase[haicolor*2+1], TRUE ) ;                         // 裏面表示
	}else{

		// ----------------------------------------
		// 通常表示
		// ----------------------------------------
		if ( haimode == DISP_HAI_COLOR_NUM_NOCOLOR ){

		 	// 牌枠表示
			DrawGraph( x, y, PaiBase[haicolor*2], TRUE ) ;
			// 牌面表示
			if (hai_turn == true){
				DrawRotaGraph( x+12, y+16, 1.0f, PI, Pai[PaiImgNum[hai]], TRUE );     // 牌の上下反転
			}else{
				DrawGraph( x, y, Pai[PaiImgNum[hai]] , TRUE ) ;                       // 牌面表示
			}

		// ----------------------------------------
		// ブレンドモード - 灰色
		// ----------------------------------------
		}else if( haimode == DISP_HAI_COLOR_NUM_GRAY ){

			// 色ベース表示
			DrawGraph( x, y, gray, TRUE ) ;
			// ブレンド表示開始
			SetDrawBlendMode( DX_BLENDMODE_ADD , 64 ) ;
		    // 牌枠表示
			DrawGraph( x, y, PaiBase[haicolor*2], TRUE );
			// 牌面表示
			if (hai_turn == true){
				DrawRotaGraph( x+12, y+16, 1.0f, PI, Pai[PaiImgNum[hai]], TRUE );    // 牌の上下反転
			}else{
				DrawGraph( x, y, Pai[PaiImgNum[hai]] , TRUE );                       // 牌面表示
			}
		    // ブレンド表示解除
			SetDrawBlendMode( DX_BLENDMODE_NOBLEND , 0 );

		// ----------------------------------------
		// ブレンドモード - 灰色(濃いめ)
		// ----------------------------------------
		}else if( haimode == DISP_HAI_COLOR_NUM_DEEP_GRAY ){

			// 色ベース表示
			DrawGraph( x, y, gray, TRUE ) ;
			// ブレンド表示開始
			SetDrawBlendMode( DX_BLENDMODE_ADD , 48 ) ;
			// 牌枠表示
			DrawGraph( x, y, PaiBase[haicolor*2], TRUE ) ;
			// 牌表示
			if (hai_turn == true){
				DrawRotaGraph( x+12, y+16, 1.0f, PI, Pai[PaiImgNum[hai]], TRUE );     // 牌の上下反転
			}else{
				DrawGraph( x, y, Pai[PaiImgNum[hai]] , TRUE ) ;
			}
			// ブレンド表示解除
			SetDrawBlendMode( DX_BLENDMODE_NOBLEND , 0 ) ;

		// ----------------------------------------
		// ブレンドモード - 青
		// ----------------------------------------
		}else if( haimode == DISP_HAI_COLOR_NUM_BLUE ){

			// 色ベース表示
			DrawGraph( x, y, blue, TRUE ) ;
			// ブレンド表示開始
			SetDrawBlendMode( DX_BLENDMODE_ADD , 64 ) ;
			// 牌枠表示
			DrawGraph( x, y, PaiBase[haicolor*2], TRUE ) ;
			// 牌表示
			if (hai_turn == true){
				DrawRotaGraph( x+12, y+16, 1.0f, PI, Pai[PaiImgNum[hai]], TRUE );     // 牌の上下反転
			}else{
				DrawGraph( x, y, Pai[PaiImgNum[hai]] , TRUE ) ;
			}
			// ブレンド表示解除
			SetDrawBlendMode( DX_BLENDMODE_NOBLEND , 0 ) ;

		// ----------------------------------------
		// ブレンドモード - 青(濃いめ)
		// ----------------------------------------
		}else if( haimode == DISP_HAI_COLOR_NUM_DEEP_BLUE ){

			// 色ベース表示
			DrawGraph( x, y, blue, TRUE ) ;
			// ブレンド表示開始
			SetDrawBlendMode( DX_BLENDMODE_ADD , 48 ) ;
			// 牌枠表示
			DrawGraph( x, y, PaiBase[haicolor*2], TRUE ) ;
			// 牌表示
			if (hai_turn == true){
				DrawRotaGraph( x+12, y+16, 1.0f, PI, Pai[PaiImgNum[hai]], TRUE );     // 牌の上下反転
			}else{
				DrawGraph( x, y, Pai[PaiImgNum[hai]] , TRUE ) ;
			}
			// ブレンド表示解除
			SetDrawBlendMode( DX_BLENDMODE_NOBLEND , 0 ) ;

		// ----------------------------------------
		// ブレンドモード - 桃
		// ----------------------------------------
		}else if( haimode == DISP_HAI_COLOR_NUM_PINK ){

			// 牌枠表示
			DrawGraph( x, y, PaiBase[haicolor*2], TRUE ) ;
			// 色ベース表示
			DrawGraph( x, y, pink, TRUE ) ;
			// ブレンド表示開始
			SetDrawBlendMode( DX_BLENDMODE_ADD , 64 ) ;
			// 牌表示
			if (hai_turn == true){
				DrawRotaGraph( x+12, y+16, 1.0f, PI, Pai[PaiImgNum[hai]], TRUE );     // 牌の上下反転
			}else{
				DrawGraph( x, y, Pai[PaiImgNum[hai]] , TRUE ) ;
			}
			// ブレンド表示解除
			SetDrawBlendMode( DX_BLENDMODE_NOBLEND , 0 ) ;

		// ----------------------------------------
		// ブレンドモード - 黄
		// ----------------------------------------
		}else if( haimode == DISP_HAI_COLOR_NUM_YELLOW ){

			// 牌枠表示
			DrawGraph( x, y, PaiBase[haicolor*2], TRUE ) ;
			// 色ベース表示
			DrawGraph( x, y, yellow, TRUE ) ;
			// ブレンド表示開始
			SetDrawBlendMode( DX_BLENDMODE_ADD , 64 ) ;
			// 牌表示
			if (hai_turn == true){
				DrawRotaGraph( x+12, y+16, 1.0f, PI, Pai[PaiImgNum[hai]], TRUE );     // 牌の上下反転
			}else{
				DrawGraph( x, y, Pai[PaiImgNum[hai]] , TRUE ) ;
			}
			// ブレンド表示解除
			SetDrawBlendMode( DX_BLENDMODE_NOBLEND , 0 ) ;

		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// パーツ表示・横牌表示
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispLHai(int x, int y, int hai, bool aka, bool hai_turn, int haimode, int haicolor){

	// デバッグ用
	if ( hai < 0 || hai > PAI_MAX){
		hai=0;
	}

	// 赤牌の場合
	      if( hai == MAN5NUM && aka == true ){
		hai=10;
	}else if( hai == PIN5NUM && aka == true ){
		hai=20;
	}else if( hai == SOU5NUM && aka == true ){
		hai=30;
	}

	// 牌表示メイン
	if ( hai == 0 ){

		// 裏面表示
		DrawGraph( x, y, LPaiBase[haicolor*2+1], TRUE ) ;

	}else{

		// ----------------------------------------
		// 通常表示
		// ----------------------------------------
		if ( haimode == DISP_HAI_COLOR_NUM_NOCOLOR ){
		 	// 牌枠表示
			DrawGraph( x, y, LPaiBase[haicolor*2], TRUE ) ;
			// 牌面表示
			if (hai_turn == true){
				DrawRotaGraph( x+16, y+12, 1.0f, PI, LPai[PaiImgNum[hai]], TRUE );     // 牌の上下反転
			}else{
				DrawGraph( x, y, LPai[PaiImgNum[hai]] , TRUE ) ;
			}

		// ----------------------------------------
		// ブレンドモード - 灰色
		// ----------------------------------------
		}else if( haimode == DISP_HAI_COLOR_NUM_GRAY ){

			// 色ベース表示
			DrawGraph( x, y, lgray, TRUE ) ;
			// ブレンド表示開始
			SetDrawBlendMode( DX_BLENDMODE_ADD , 64 ) ;
		 	// 牌枠表示
			DrawGraph( x, y, LPaiBase[haicolor*2], TRUE ) ;
			// 牌面表示
			if (hai_turn == true){
				DrawRotaGraph( x+16, y+12, 1.0f, PI, LPai[PaiImgNum[hai]], TRUE );     // 牌の上下反転
			}else{
				DrawGraph( x, y, LPai[PaiImgNum[hai]] , TRUE ) ;
			}
			// ブレンド表示解除
			SetDrawBlendMode( DX_BLENDMODE_NOBLEND , 0 ) ;

		// ----------------------------------------
		// ブレンドモード - 灰色(濃いめ)
		// ----------------------------------------
		}else if( haimode == DISP_HAI_COLOR_NUM_DEEP_GRAY ){

			// 色ベース表示
			DrawGraph( x, y, lgray, TRUE ) ;
			// ブレンド表示開始
			SetDrawBlendMode( DX_BLENDMODE_ADD , 48 ) ;
		 	// 牌枠表示
			DrawGraph( x, y, LPaiBase[haicolor*2], TRUE ) ;
			// 牌面表示
			if (hai_turn == true){
				DrawRotaGraph( x+16, y+12, 1.0f, PI, LPai[PaiImgNum[hai]], TRUE );     // 牌の上下反転
			}else{
				DrawGraph( x, y, LPai[PaiImgNum[hai]] , TRUE ) ;
			}
			// ブレンド表示解除
			SetDrawBlendMode( DX_BLENDMODE_NOBLEND , 0 ) ;

		// ----------------------------------------
		// ブレンドモード - 青
		// ----------------------------------------
		}else if( haimode == DISP_HAI_COLOR_NUM_BLUE ){

			// 色ベース表示
			DrawGraph( x, y, lblue, TRUE ) ;
			// ブレンド表示開始
			SetDrawBlendMode( DX_BLENDMODE_ADD , 64 ) ;
		 	// 牌枠表示
			DrawGraph( x, y, LPaiBase[haicolor*2], TRUE ) ;
			// 牌面表示
			if (hai_turn == true){
				DrawRotaGraph( x+16, y+12, 1.0f, PI, LPai[PaiImgNum[hai]], TRUE );     // 牌の上下反転
			}else{
				DrawGraph( x, y, LPai[PaiImgNum[hai]] , TRUE ) ;
			}
			// ブレンド表示解除
			SetDrawBlendMode( DX_BLENDMODE_NOBLEND , 0 ) ;

		// ----------------------------------------
		// ブレンドモード - 青(濃いめ)
		// ----------------------------------------
		}else if( haimode == DISP_HAI_COLOR_NUM_DEEP_BLUE ){

			// 牌表示
			DrawGraph( x, y, lblue, TRUE ) ;
			// ブレンド表示開始
			SetDrawBlendMode( DX_BLENDMODE_ADD , 48 ) ;
		 	// 牌枠表示
			DrawGraph( x, y, LPaiBase[haicolor*2], TRUE ) ;
			// 牌面表示
			if (hai_turn == true){
				DrawRotaGraph( x+16, y+12, 1.0f, PI, LPai[PaiImgNum[hai]], TRUE );     // 牌の上下反転
			}else{
				DrawGraph( x, y, LPai[PaiImgNum[hai]] , TRUE ) ;
			}
			// ブレンド表示解除
			SetDrawBlendMode( DX_BLENDMODE_NOBLEND , 0 ) ;

		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 手牌パーツの表示(通常版)
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispActTehaiParts(int x, int y,int tehai_tbl_count, int tehai_tbl[], bool tehai_tbl_aka[], int tsumo_hai, bool tsumo_aka, int sute_hai_num, int color_hai, int color_hai2, bool color_ankan){

	int tmp_hai_x;         // 手牌X位置

	// ----------------------------------------
	// 手牌表示
	// ----------------------------------------
	for(int tmp_i = 0; tmp_i < tehai_tbl_count; tmp_i++){

		// X位置
		tmp_hai_x = x + tmp_i*HAI_XSIZE;

		// ----------------------------------------
		// 手牌表示(通常モード)
		// ----------------------------------------
		if( tmp_i != sute_hai_num){

			// 着色牌であるなら
			if( tmp_i == color_hai || tmp_i == color_hai2){

				// 赤牌であるなら
				if( tehai_tbl_aka[tmp_i] == true){
					// 青色・赤牌表示
					DispHai( tmp_hai_x, y, tehai_tbl[tmp_i], true, false, DISP_HAI_COLOR_NUM_BLUE, 0);
				}else{
					// 青色・通常表示
					DispHai( tmp_hai_x, y, tehai_tbl[tmp_i], false, false, DISP_HAI_COLOR_NUM_BLUE, 0);
				}

			// 無色の表示
			}else{

				// 赤牌であるなら
				if( tehai_tbl_aka[tmp_i] == true){
					// 無色・赤牌表示
					DispHai( tmp_hai_x, y, tehai_tbl[tmp_i], true, false, 0, 0);
				}else{
					// 無色・通常表示
					DispHai( tmp_hai_x, y, tehai_tbl[tmp_i], false, false, 0, 0);
				}
			}

		}

	}

	// ----------------------------------------
	// ツモ牌表示
	// ----------------------------------------

	// 自摸牌表示なら
	if (tsumo_hai > 0 && tsumo_hai < 38){

		// 着色牌であるなら
		if( tehai_tbl_count == color_hai){
			DispHai( x+HAI_XSIZE*tehai_tbl_count+SPACE_XSIZE, y, tsumo_hai, tsumo_aka, false, DISP_HAI_COLOR_NUM_BLUE, 0);
		}else{
			DispHai( x+HAI_XSIZE*tehai_tbl_count+SPACE_XSIZE, y, tsumo_hai, tsumo_aka, false, 0, 0);
		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 手牌パーツ(人プレーヤー捨牌禁止表示)
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispActHumCanSuteParts(int x, int y, int  tehai_tbl_count, int tehai_tbl[], bool tehai_tbl_aka[], bool tehai_can_sute_tbl[], int tsumo_hai, bool tsumo_aka, bool tsumo_can_sute, int color_hai){

	int tmp_hai_x;         // 手牌X位置

	// ----------------------------------------
	// 手牌表示
	// ----------------------------------------
	for(int tmp_i = 0; tmp_i < tehai_tbl_count; tmp_i++){

		// X位置
		tmp_hai_x = x+tmp_i*HAI_XSIZE;

		// ----------------------------------------
		// 手牌表示(通常モード)
		// ----------------------------------------
		// tehai_can_sute_tblがtrueなら捨牌可能(無色)
		if( tehai_can_sute_tbl[tmp_i] == true){

			// 着色牌であるなら
			if( tmp_i == color_hai){

				// 赤牌であるなら
				if( tehai_tbl_aka[tmp_i] == true){
					// 青色・赤牌表示
					DispHai( tmp_hai_x, y, tehai_tbl[tmp_i], true, false, DISP_HAI_COLOR_NUM_BLUE, 0);
				}else{
					// 青色・通常表示
					DispHai( tmp_hai_x, y, tehai_tbl[tmp_i], false, false, DISP_HAI_COLOR_NUM_BLUE, 0);
				}

			// 通常牌の表示
			}else{

				// 赤牌であるなら
				if( tehai_tbl_aka[tmp_i] == true){
					// 無色・赤牌表示
					DispHai( tmp_hai_x, y, tehai_tbl[tmp_i], true, false, 0, 0);
				}else{
					// 無色・通常表示
					DispHai( tmp_hai_x, y, tehai_tbl[tmp_i], false, false, 0, 0);
				}
			}

		// tehai_can_sute_tblがtrue以外なら捨牌不可(灰色)
		}else{
				if( tehai_tbl_aka[tmp_i] == true){
					// 無色・赤牌表示
					DispHai( tmp_hai_x, y, tehai_tbl[tmp_i], true, false, DISP_HAI_COLOR_NUM_GRAY, 0);
				}else{
					// 無色・通常表示
					DispHai( tmp_hai_x, y, tehai_tbl[tmp_i], false, false, DISP_HAI_COLOR_NUM_GRAY, 0);
				}

		 }

	}

	// ----------------------------------------
	// ツモ牌表示
	// ----------------------------------------

	// 自摸牌表示なら
	if (tsumo_hai > 0 && tsumo_hai < 38){
		// tsumo_can_suteがtrueなら捨牌可能(無色)
		if( tsumo_can_sute == true ){

			// 着色牌であるなら
			if( tehai_tbl_count == color_hai){
				DispHai( x+HAI_XSIZE*tehai_tbl_count+SPACE_XSIZE, y, tsumo_hai, tsumo_aka, false, DISP_HAI_COLOR_NUM_BLUE, 0);
			}else{
				DispHai( x+HAI_XSIZE*tehai_tbl_count+SPACE_XSIZE, y, tsumo_hai, tsumo_aka, false, 0, 0);
			}

		// tsumo_can_suteがtrue以外なら捨牌不可(灰色)
		}else{
				DispHai( x+HAI_XSIZE*tehai_tbl_count+SPACE_XSIZE, y, tsumo_hai, tsumo_aka, false, DISP_HAI_COLOR_NUM_GRAY, 0);
		}
	}
}

/* ---------------------------------------------------------------------------------------------- */
// 手牌パーツの表示(カン牌選択)
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispActHumKanSelectTehaiParts(int x, int y, int  tehai_tbl_count, int  tehai_tbl[], bool tehai_tbl_aka[], int tsumo_hai, bool tsumo_aka, int ankan_hai1, int ankan_hai2, int ankan_hai3, int kakan_hai1, int kakan_hai2, int kakan_hai3, int color_hai){

	int tmp_hai_x;            // 手牌X位置

	// ----------------------------------------
	// 手牌表示
	// ----------------------------------------
	for(int tmp_i = 0; tmp_i < tehai_tbl_count; tmp_i++){

		// X位置
		tmp_hai_x = SPACE_XSIZE+tmp_i*HAI_XSIZE;

		// ----------------------------------------
		// 手牌表示(通常モード)
		// ----------------------------------------
		// カン候補牌なら着色
		if( tehai_tbl[tmp_i] == ankan_hai1 || tehai_tbl[tmp_i] == ankan_hai2 || tehai_tbl[tmp_i] == ankan_hai3 ||
		    tehai_tbl[tmp_i] == kakan_hai1 || tehai_tbl[tmp_i] == kakan_hai2 || tehai_tbl[tmp_i] == kakan_hai3 ){
			// マウス位置で着有無を確認
			if( tmp_i == color_hai){
				DispHai( tmp_hai_x, y, tehai_tbl[tmp_i], tehai_tbl_aka[tmp_i], false, DISP_HAI_COLOR_NUM_BLUE, 0);
			// 通常牌の表示
			}else{
				DispHai( tmp_hai_x, y, tehai_tbl[tmp_i], tehai_tbl_aka[tmp_i], false, 0, 0);
			}
		// カン候補牌でないなら常に灰色
		}else{
				DispHai( tmp_hai_x, y, tehai_tbl[tmp_i], tehai_tbl_aka[tmp_i], false, DISP_HAI_COLOR_NUM_GRAY, 0);
		}

	}

	// ----------------------------------------
	// ツモ牌表示
	// ----------------------------------------

	// カン候補牌なら着色
	if( tsumo_hai == ankan_hai1 || tsumo_hai == ankan_hai2 || tsumo_hai == ankan_hai3 ||
	    tsumo_hai == kakan_hai1 || tsumo_hai == kakan_hai2 || tsumo_hai == kakan_hai3 ){
		// 着色牌であるなら
		if( tehai_tbl_count == color_hai){
			DispHai( x+HAI_XSIZE*tehai_tbl_count+SPACE_XSIZE, y, tsumo_hai, tsumo_aka, false, DISP_HAI_COLOR_NUM_BLUE, 0);
		}else{
			DispHai( x+HAI_XSIZE*tehai_tbl_count+SPACE_XSIZE, y, tsumo_hai, tsumo_aka, false, 0, 0);
		}
	// テンパイでないなら常に灰色
	}else{
			DispHai( x+HAI_XSIZE*tehai_tbl_count+SPACE_XSIZE, y, tsumo_hai, tsumo_aka, false, DISP_HAI_COLOR_NUM_GRAY, 0);
	}

}

/* ---------------------------------------------------------------------------------------------- */
// 裏向き手牌表示
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DisplayUnkownTehai(int x, int y, int tehai_tbl_count, bool tsumo_flg, int sute_hai_num){

	// 変数定義
	int tmp_hai_x;

	// ----------------------------------------
	// 手牌表示
	// ----------------------------------------
	for(int tmp_i = 0; tmp_i < tehai_tbl_count; tmp_i++){

		// X位置
		tmp_hai_x = SPACE_XSIZE+tmp_i*HAI_XSIZE;

		// 疑似捨牌表示
		// if(sute_flg == false || tmp_i != 5){
		if( tmp_i != sute_hai_num ){
			DispHai( tmp_hai_x, y, 0, false, false, 0, 0);
		}

	}

	// ----------------------------------------
	// 自摸牌表示
	// ----------------------------------------
	if(tsumo_flg == true){
		tmp_hai_x = SPACE_XSIZE+tehai_tbl_count*HAI_XSIZE + SPACE_XSIZE;
		DispHai( tmp_hai_x, y, 0, false, false, 0, 0);
	}


}

/* ---------------------------------------------------------------------------------------------- */
// 晒し面子のパーツ表示
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispActSarashiParts(int x, int y, LBMen naki_stat, int hai_index, int aka_count){

	// 変数の初期化
	int tmp_aka_count = aka_count;

	// ----------------------------------------
	// (デバグ用)赤牌枚数
	// ----------------------------------------
/*
	// 加槓確認
 	if( naki_stat != KAKAN){

			// (デバグ用)鳴き面子の赤牌枚数表示
			DrawFormatString( x+HAI_XSIZE*4+2, y   , GetColor(255,255,255), "赤%d枚", aka_count);

	}else{

		// (デバグ用)加槓・赤牌確認
		if (aka_count>0){
			DrawFormatString( x+HAI_XSIZE*4+2, y+17, GetColor(255,255,255), "赤+1枚");
		}else{
			DrawFormatString( x+HAI_XSIZE*4+2, y+17, GetColor(255,255,255), "赤+0枚");
		}

	}
*/
	// ----------------------------------------
	// ポン牌の表示
	// ----------------------------------------
	if( naki_stat == MINKO || naki_stat == ANKO ){

		// 晒し牌の表示
		for(int tmp_i = 0; tmp_i < 3; tmp_i++){
 			if( ( hai_index == 5 || hai_index == 15 || hai_index == 25) && tmp_aka_count > 0 ){
 				DispHai( x+HAI_XSIZE*tmp_i, y, hai_index, true, false,  0, 0);
				tmp_aka_count--;
			}else{
				DispHai( x+HAI_XSIZE*tmp_i, y, hai_index, false, false, 0, 0);
			}
		}

	// ----------------------------------------
	// チー牌の表示
	// ----------------------------------------
	}else if(naki_stat == MINSHUN || naki_stat == SHUNTSU ){

		// 晒し牌の表示(1枚目)
 		if( ( hai_index == 5 || hai_index == 15 || hai_index == 25) && tmp_aka_count > 0 ){
			DispHai( x            , y, hai_index  , true, false, 0, 0);
			tmp_aka_count--;
		}else{
			DispHai( x            , y, hai_index  , false, false, 0, 0);
		}

		// 晒し牌の表示(2枚目)
 		if( ( hai_index+1 == 5 || hai_index+1 == 15 || hai_index+1 == 25) && tmp_aka_count > 0 ){
			DispHai( x+HAI_XSIZE  , y, hai_index+1, true, false, 0, 0);
			tmp_aka_count--;
		}else{
			DispHai( x+HAI_XSIZE  , y, hai_index+1, false, false, 0, 0);
		}

		// 晒し牌の表示(3枚目)
 		if( ( hai_index+2 == 5 || hai_index+2 == 15 || hai_index+2 == 25) && tmp_aka_count > 0 ){
			DispHai( x+HAI_XSIZE*2, y, hai_index+2, true, false, 0, 0);
			tmp_aka_count--;
		}else{
			DispHai( x+HAI_XSIZE*2, y, hai_index+2, false, false, 0, 0);
		}

	// ----------------------------------------
	// 暗槓牌の表示
	// ----------------------------------------
	}else if(naki_stat == ANKAN){

		// 晒し牌の表示(オープン1枚目)
		if( tmp_aka_count > 0 ){
			DispHai( x+HAI_XSIZE  , y, hai_index, true, false, 0, 0);
		}else{
			DispHai( x+HAI_XSIZE  , y, hai_index, false, false, 0, 0);
		}

		// 晒し牌の表示(オープン2枚目)
		if( tmp_aka_count > 1 ){
			DispHai( x+HAI_XSIZE*2, y, hai_index, true, false, 0, 0);
		}else{
			DispHai( x+HAI_XSIZE*2, y, hai_index, false, false, 0, 0);
		}

		// 裏向き牌
		DispHai( x,             y, 0, false, false, 0, 0);
		DispHai( x+HAI_XSIZE*3, y, 0, false, false, 0, 0);

	// ----------------------------------------
	// 明槓牌の表示
	// ----------------------------------------
	}else if(naki_stat == MINKAN){

		// 晒し牌の表示(オープン1枚目)
		if( tmp_aka_count > 0 ){
			DispHai( x            , y, hai_index, true, false, 0, 0);
		}else{
			DispHai( x            , y, hai_index, false, false, 0, 0);
		}

		// 晒し牌の表示(オープン2枚目)
		if( tmp_aka_count > 1 ){
			DispHai( x+HAI_XSIZE*1, y, hai_index, true, false, 0, 0);
		}else{
			DispHai( x+HAI_XSIZE*1, y, hai_index, false, false, 0, 0);
		}

		// 晒し牌の表示(オープン3枚目)
		if( tmp_aka_count > 2 ){
			DispHai( x+HAI_XSIZE*2, y, hai_index, true, false, 0, 0);
		}else{
			DispHai( x+HAI_XSIZE*2, y, hai_index, false, false, 0, 0);
		}

		// 晒し牌の表示(オープン4枚目)
		if( tmp_aka_count > 3 ){
			DispHai( x+HAI_XSIZE*3, y, hai_index, true, false, 0, 0);
		}else{
			DispHai( x+HAI_XSIZE*3, y, hai_index, false, false, 0, 0);
		}

	// ----------------------------------------
	// 加槓牌の表示
	// ----------------------------------------
	}else if(naki_stat == KAKAN){
		if( tmp_aka_count > 0 ){
			DispHai( x+HAI_XSIZE*3, y, hai_index, true, false, 0, 0);
		}else{
			DispHai( x+HAI_XSIZE*3, y, hai_index, false, false, 0, 0);
		}

	// ----------------------------------------
	// 頭・対子の表示
	// ----------------------------------------
	}else if( naki_stat == ATAMA || naki_stat == TOITSU ){

		// 晒し牌の表示
		for(int tmp_i = 0; tmp_i < 2; tmp_i++){
 			if( ( hai_index == 5 || hai_index == 15 || hai_index == 25) && tmp_aka_count > 0 ){
 				DispHai( x+HAI_XSIZE*tmp_i, y, hai_index, true, false,  0, 0);
				tmp_aka_count--;
			}else{
				DispHai( x+HAI_XSIZE*tmp_i, y, hai_index, false, false, 0, 0);
			}
		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 晒し面子のパーツ表示：全鳴き面子表示
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispAllSarashiParts(int x, int y, int naki_count, LBMen naki_stat[], int naki_hai[], int naki_idx[], int naki_aka[]){

	// 変数定義
	int tmp_xstat_count = 0;

	// さらし表示
	for(int tmp_i = 0; tmp_i < naki_count; tmp_i++){

		// ----------------------------------------
		// ポン牌の表示・明槓牌の表示・暗槓牌の表示
		// ----------------------------------------
		if( naki_stat[tmp_i] == MINKO  || 
		    naki_stat[tmp_i] == MINKAN || 
		    naki_stat[tmp_i] == ANKAN  ){

			// 鳴き表示
			DispActSarashiParts( x - tmp_xstat_count*NAKI_MENTSU_RANGE, y,  naki_stat[tmp_i], naki_hai[tmp_i], naki_aka[tmp_i]);

			// 鳴き面子の表示位置移動
			tmp_xstat_count++;

		// ----------------------------------------
		// チー牌牌の表示
		// ----------------------------------------
		}else if(naki_stat[tmp_i] == MINSHUN){

			// 鳴き表示
			DispActSarashiParts( x - tmp_xstat_count*NAKI_MENTSU_RANGE, y,  naki_stat[tmp_i], naki_idx[tmp_i], naki_aka[tmp_i]);

			// 鳴き面子の表示位置移動
			tmp_xstat_count++;


		// ----------------------------------------
		// 加槓牌の表示
		// ----------------------------------------
		}else if(naki_stat[tmp_i] == KAKAN){

			// 加槓の晒し牌番号の確認
			for(int tmp_j = 0; tmp_j < naki_count; tmp_j++){
				// 既存晒し面子と同じならば
				if (naki_hai[tmp_j] == naki_hai[tmp_i]){
					// 加槓表示
					DispActSarashiParts(x - tmp_j*NAKI_MENTSU_RANGE, y,  KAKAN, naki_hai[tmp_j], naki_hai[tmp_i]);
					// 加槓があるので、ここで抜ける。(抜けないと加槓で重複処理になってしまう)
					break;
				}
			}

		// ----------------------------------------
		// その他の表示
		// ----------------------------------------
		}else{
			// その他処理
			DrawFormatString(x, y,  GetColor(255,255,255), "その他");
		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 牌画パーツ/河情報：ライナー表示
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispActKawaParts_liner(int x, int y, int kawa_tbl_count, int kawa_tbl[], bool kawa_tbl_aka[], int kawa_mode[]){

	// 牌のX位置表示用
	int sute_xstat = 0;

	// 捨牌表示(ライナー表示)
	for(int tmp_i = 0; tmp_i < kawa_tbl_count; tmp_i++){

		// リーチ処理の場合
		if( kawa_mode[tmp_i] >= RIICHI_STAT_NUM ){

			// 捨牌表示 - リーチ牌
			DispLHai( SPACE_XSIZE + sute_xstat, y+7, kawa_tbl[tmp_i], kawa_tbl_aka[tmp_i], false, kawa_mode[tmp_i]-RIICHI_STAT_NUM, 0);

			// 捨牌の位置変更
			sute_xstat = sute_xstat + LHAI_XSIZE;

		// 通常の場合
		}else{

			// 捨牌表示
			DispHai( SPACE_XSIZE + sute_xstat, y, kawa_tbl[tmp_i], kawa_tbl_aka[tmp_i], false,  kawa_mode[tmp_i], 0);

			// 捨牌の位置変更
			sute_xstat = sute_xstat + HAI_XSIZE;

		 }

	}

}

/* ---------------------------------------------------------------------------------------------- */
// アクション手牌・UPプレーヤ表示
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispActTehaiParts_up(int x,int y,int tehai_tbl_count, int tehai_tbl[], bool tehai_tbl_aka[], int tsumo_hai, bool tsumo_aka, int sute_hai_num){

	// 手牌表示(UPプレーヤ)
	for(int tmp_i = 0; tmp_i < tehai_tbl_count; tmp_i++){
		// 捨牌でないなら
		if( sute_hai_num != (tehai_tbl_count-tmp_i-1) ){
			DispHai( x + (13-tehai_tbl_count) * HAI_XSIZE + tmp_i * HAI_XSIZE, 
			         y, 
			         tehai_tbl[tehai_tbl_count-tmp_i-1], tehai_tbl_aka[tehai_tbl_count-tmp_i-1], true, 0, 0);
		}
	}

		// 自摸牌表示(UPプレーヤ)
		if ( tsumo_hai > 0 && tsumo_hai < PAI_MAX){
			DispHai( x + (13-tehai_tbl_count) * HAI_XSIZE - HAI_XSIZE - SPACE_XSIZE, 
			         y, 
			         tsumo_hai, tsumo_aka, true, 0, 0);
		}
}

/* ---------------------------------------------------------------------------------------------- */
// アクション手牌・Leftプレーヤ表示
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispActTehaiParts_left(int x,int y,int tehai_tbl_count, int tehai_tbl[], bool tehai_tbl_aka[], int tsumo_hai, bool tsumo_aka, int sute_hai_num){

	// 手牌表示(Leftプレーヤ)
	for(int tmp_i = 0; tmp_i < tehai_tbl_count; tmp_i++){
		// 捨牌でないなら
		if(tmp_i != sute_hai_num){
			DispLHai( x, y + tmp_i * LHAI_YSIZE, tehai_tbl[tmp_i], tehai_tbl_aka[tmp_i], true, 0, 0);         // 左手牌
		}
	}

		// 自摸牌表示(Leftプレーヤ)
		if ( tsumo_hai > 0 && tsumo_hai < PAI_MAX){
			DispLHai( x, y + tehai_tbl_count * LHAI_YSIZE + 10, tsumo_hai, tsumo_aka, true, 0, 0);            // 左自摸(13*23=299)
		}
}

/* ---------------------------------------------------------------------------------------------- */
// アクション手牌・Rightプレーヤ表示
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispActTehaiParts_right(int x,int y,int tehai_tbl_count, int tehai_tbl[], bool tehai_tbl_aka[], int tsumo_hai, bool tsumo_aka, int sute_hai_num){

	// 手牌表示(Rightプレーヤ)
	for(int tmp_i = 0; tmp_i < tehai_tbl_count; tmp_i++){
		// 捨牌でないなら
		if( sute_hai_num != (tehai_tbl_count-tmp_i-1) ){
			DispLHai( x, 
			          y + 35 + (13-tehai_tbl_count)*LHAI_YSIZE + tmp_i*LHAI_YSIZE, 
			          tehai_tbl[tehai_tbl_count-tmp_i-1], tehai_tbl_aka[tehai_tbl_count-tmp_i-1], false, 0, 0);
		}
	}

		// 自摸牌表示(Rightプレーヤ)
		if ( tsumo_hai > 0 && tsumo_hai < PAI_MAX){
			DispLHai( x, 
			          y + (13-tehai_tbl_count)*LHAI_YSIZE, 
		              tsumo_hai, tsumo_aka, false, 0, 0);
		}

}

/* ---------------------------------------------------------------------------------------------- */
// アクション河情報・UPプレーヤ表示
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispActKawaParts_up(int x, int y, int kawa_tbl_count, int kawa_tbl[], bool kawa_tbl_aka[], int kawa_mode[]){

	// ----------------------------------------
	// 変数初期化
	// ----------------------------------------
	int  tmp_x;
	int  tmp_y;
	int  line_sutehai_count = 0;
	int  tmp_sute_idx   = 0;
	int  tmp_kawa_mode  = 0;
	bool riichi_flg = false;

	// ----------------------------------------
	// 捨牌表示(1段目)
	// ----------------------------------------
	if( kawa_tbl_count > LINE_SUTEHAI_COUNT_MAX*3){

		// 変数定義
		tmp_x = x+HAI_XSIZE*5;
		tmp_y = y;

		// 牌枚数
		line_sutehai_count = kawa_tbl_count - LINE_SUTEHAI_COUNT_MAX*3;

		// 捨牌表示(1段目)
		for(int tmp_i = 0; tmp_i < line_sutehai_count; tmp_i++){

			// 捨牌INDEXの定義
			tmp_sute_idx = tmp_i + LINE_SUTEHAI_COUNT_MAX*3;

			// 牌モード確認
			if( kawa_mode[tmp_sute_idx] >= RIICHI_STAT_NUM ){
				tmp_kawa_mode =  kawa_mode[tmp_sute_idx] - RIICHI_STAT_NUM;
				riichi_flg = true;
			}else{
				tmp_kawa_mode =  kawa_mode[tmp_sute_idx];
				riichi_flg = false;
			}

			// 捨牌表示
			if(riichi_flg == true){
				// 捨牌表示 - リーチ牌
				DispLHai( tmp_x-8,tmp_y+7, kawa_tbl[tmp_sute_idx], kawa_tbl_aka[tmp_sute_idx], true, tmp_kawa_mode, 0);
				tmp_x = tmp_x - LHAI_XSIZE;
			}else{
				// 捨牌表示 - 通常
				DispHai( tmp_x, tmp_y,   kawa_tbl[tmp_sute_idx], kawa_tbl_aka[tmp_sute_idx], true, tmp_kawa_mode, 0);
				tmp_x = tmp_x - HAI_XSIZE;
			}

		}

	}

	// ----------------------------------------
	// 捨牌表示(2段目)
	// ----------------------------------------
	if( kawa_tbl_count > LINE_SUTEHAI_COUNT_MAX*2){

		// 変数定義
		tmp_x = x+HAI_XSIZE*5;
		tmp_y = y+HAI_YSIZE*1;

		// 牌枚数
		if(kawa_tbl_count > LINE_SUTEHAI_COUNT_MAX*3){
			line_sutehai_count = LINE_SUTEHAI_COUNT_MAX;
		}else{
			line_sutehai_count = kawa_tbl_count - LINE_SUTEHAI_COUNT_MAX*2;
		}

		// 捨牌表示(1段目)
		for(int tmp_i = 0; tmp_i < line_sutehai_count; tmp_i++){

			// 捨牌INDEXの定義
			tmp_sute_idx = tmp_i + LINE_SUTEHAI_COUNT_MAX*2;

			// 牌モード確認
			if( kawa_mode[tmp_sute_idx] >= RIICHI_STAT_NUM ){
				tmp_kawa_mode =  kawa_mode[tmp_sute_idx] - RIICHI_STAT_NUM;
				riichi_flg = true;
			}else{
				tmp_kawa_mode =  kawa_mode[tmp_sute_idx];
				riichi_flg = false;
			}

			// 捨牌表示
			if(riichi_flg == true){
				// 捨牌表示 - リーチ牌
				DispLHai( tmp_x-8,tmp_y+7, kawa_tbl[tmp_sute_idx], kawa_tbl_aka[tmp_sute_idx], true, tmp_kawa_mode, 0);
				tmp_x = tmp_x - LHAI_XSIZE;
			}else{
				// 捨牌表示 - 通常
				DispHai( tmp_x, tmp_y,   kawa_tbl[tmp_sute_idx], kawa_tbl_aka[tmp_sute_idx], true, tmp_kawa_mode, 0);
				tmp_x = tmp_x - HAI_XSIZE;
			}

		}

	}

	// ----------------------------------------
	// 捨牌表示(3段目)
	// ----------------------------------------
	if( kawa_tbl_count > LINE_SUTEHAI_COUNT_MAX){

		// 変数定義
		tmp_x = x+HAI_XSIZE*5;
		tmp_y = y+HAI_YSIZE*2;

		// 牌枚数
		if(kawa_tbl_count > LINE_SUTEHAI_COUNT_MAX*2){
			line_sutehai_count = LINE_SUTEHAI_COUNT_MAX;
		}else{
			line_sutehai_count = kawa_tbl_count - LINE_SUTEHAI_COUNT_MAX;
		}

		// 捨牌表示(1段目)
		for(int tmp_i = 0; tmp_i < line_sutehai_count; tmp_i++){

			// 捨牌INDEXの定義
			tmp_sute_idx = tmp_i + LINE_SUTEHAI_COUNT_MAX;

			// 牌モード確認
			if( kawa_mode[tmp_sute_idx] >= RIICHI_STAT_NUM ){
				tmp_kawa_mode =  kawa_mode[tmp_sute_idx] - RIICHI_STAT_NUM;
				riichi_flg = true;
			}else{
				tmp_kawa_mode =  kawa_mode[tmp_sute_idx];
				riichi_flg = false;
			}

			// 捨牌表示
			if(riichi_flg == true){
				// 捨牌表示 - リーチ牌
				DispLHai( tmp_x-8,tmp_y+7, kawa_tbl[tmp_sute_idx], kawa_tbl_aka[tmp_sute_idx], true, tmp_kawa_mode, 0);
				tmp_x = tmp_x - LHAI_XSIZE;
			}else{
				// 捨牌表示 - 通常
				DispHai( tmp_x, tmp_y,   kawa_tbl[tmp_sute_idx], kawa_tbl_aka[tmp_sute_idx], true, tmp_kawa_mode, 0);
				tmp_x = tmp_x - HAI_XSIZE;
			}

		}

	}

	// ----------------------------------------
	// 捨牌表示(4段目)
	// ----------------------------------------
	if( kawa_tbl_count > 0){

		// 変数定義
		tmp_x = x+HAI_XSIZE*5;
		tmp_y = y+HAI_YSIZE*3;

		// 牌枚数
		if(kawa_tbl_count > LINE_SUTEHAI_COUNT_MAX){
			line_sutehai_count = LINE_SUTEHAI_COUNT_MAX;
		}else{
			line_sutehai_count = kawa_tbl_count;
		}

		// 捨牌表示(1段目)
		for(int tmp_i = 0; tmp_i < line_sutehai_count; tmp_i++){

			// 捨牌INDEXの定義
			tmp_sute_idx = tmp_i;

			// 牌モード確認
			if( kawa_mode[tmp_sute_idx] >= RIICHI_STAT_NUM ){
				tmp_kawa_mode =  kawa_mode[tmp_sute_idx] - RIICHI_STAT_NUM;
				riichi_flg = true;
			}else{
				tmp_kawa_mode =  kawa_mode[tmp_sute_idx];
				riichi_flg = false;
			}

			// 捨牌表示
			if(riichi_flg == true){
				// 捨牌表示 - リーチ牌
				DispLHai( tmp_x-8,tmp_y+7, kawa_tbl[tmp_sute_idx], kawa_tbl_aka[tmp_sute_idx], true, tmp_kawa_mode, 0);
				tmp_x = tmp_x - LHAI_XSIZE;
			}else{
				// 捨牌表示 - 通常
				DispHai( tmp_x, tmp_y,   kawa_tbl[tmp_sute_idx], kawa_tbl_aka[tmp_sute_idx], true, tmp_kawa_mode, 0);
				tmp_x = tmp_x - HAI_XSIZE;
			}

		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// アクション河情報・DOWNプレーヤ表示
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispActKawaParts_down(int x, int y, int kawa_tbl_count, int kawa_tbl[], bool kawa_tbl_aka[], int kawa_mode[]){

	// 表示は1段目→4段目の順序は厳守となり、個別に1段目→4段目から表示する

	// ----------------------------------------
	// 変数初期化
	// ----------------------------------------
	int  tmp_x;
	int  tmp_y;
	int  line_sutehai_count = 0;
	int  tmp_sute_idx = 0;
	int  tmp_kawa_mode = 0;
	bool riichi_flg = false;

	// ----------------------------------------
	// 捨牌表示(1段目)
	// ----------------------------------------
	if( kawa_tbl_count > 0){

		// 変数定義
		tmp_x = x;
		tmp_y = y;

		// 牌枚数
		if(kawa_tbl_count > LINE_SUTEHAI_COUNT_MAX){
			line_sutehai_count = LINE_SUTEHAI_COUNT_MAX;
		}else{
			line_sutehai_count = kawa_tbl_count;
		}

		// 捨牌表示(1段目)
		for(int tmp_i = 0; tmp_i < line_sutehai_count; tmp_i++){

			// 捨牌INDEXの定義
			tmp_sute_idx = tmp_i;

			// 牌モード確認
			if( kawa_mode[tmp_sute_idx] >= RIICHI_STAT_NUM ){
				tmp_kawa_mode =  kawa_mode[tmp_sute_idx] - RIICHI_STAT_NUM;
				riichi_flg = true;
			}else{
				tmp_kawa_mode =  kawa_mode[tmp_sute_idx];
				riichi_flg = false;
			}

			// 捨牌表示
			if(riichi_flg == true){
				// 捨牌表示 - リーチ牌
				DispLHai( tmp_x,tmp_y+7, kawa_tbl[tmp_sute_idx], kawa_tbl_aka[tmp_sute_idx], false, tmp_kawa_mode, 0);
				tmp_x = tmp_x + LHAI_XSIZE;
			}else{
				// 捨牌表示 - 通常
				DispHai( tmp_x, tmp_y  , kawa_tbl[tmp_sute_idx], kawa_tbl_aka[tmp_sute_idx], false, tmp_kawa_mode, 0);
				tmp_x = tmp_x + HAI_XSIZE;
			}

		}
	}

	// ----------------------------------------
	// 捨牌表示(2段目)
	// ----------------------------------------
	if(kawa_tbl_count > LINE_SUTEHAI_COUNT_MAX){

		// 変数定義
		tmp_x = x;
		tmp_y = y+HAI_YSIZE*1;

		// 牌枚数
		if(kawa_tbl_count > LINE_SUTEHAI_COUNT_MAX*2){
			line_sutehai_count = LINE_SUTEHAI_COUNT_MAX;
		}else{
			line_sutehai_count = kawa_tbl_count - LINE_SUTEHAI_COUNT_MAX;
		}

		// 捨牌表示(2段目)
		for(int tmp_i = 0; tmp_i < line_sutehai_count; tmp_i++){

			// 捨牌INDEXの定義
			tmp_sute_idx = tmp_i + LINE_SUTEHAI_COUNT_MAX;

			// 牌モード確認
			if( kawa_mode[tmp_sute_idx] >= RIICHI_STAT_NUM ){
				tmp_kawa_mode =  kawa_mode[tmp_sute_idx] - RIICHI_STAT_NUM;
				riichi_flg = true;
			}else{
				tmp_kawa_mode =  kawa_mode[tmp_sute_idx];
				riichi_flg = false;
			}

			// 捨牌表示
			if(riichi_flg == true){
				// 捨牌表示 - リーチ牌
				DispLHai(tmp_x, tmp_y+7, kawa_tbl[tmp_sute_idx], kawa_tbl_aka[tmp_sute_idx], false, tmp_kawa_mode, 0);
				tmp_x = tmp_x + LHAI_XSIZE;
			}else{
				// 捨牌表示 - 通常
				DispHai( tmp_x, tmp_y,   kawa_tbl[tmp_sute_idx], kawa_tbl_aka[tmp_sute_idx], false, tmp_kawa_mode, 0);
				tmp_x = tmp_x + HAI_XSIZE;
			}

		}
	}

	// ----------------------------------------
	// 捨牌表示(3段目)
	// ----------------------------------------
	if(kawa_tbl_count > LINE_SUTEHAI_COUNT_MAX*2){

		// 変数定義
		tmp_x = x;
		tmp_y = y+HAI_YSIZE*2;

		// 牌枚数
		if(kawa_tbl_count > LINE_SUTEHAI_COUNT_MAX*3){
			line_sutehai_count = LINE_SUTEHAI_COUNT_MAX;
		}else{
			line_sutehai_count = kawa_tbl_count - LINE_SUTEHAI_COUNT_MAX*2;
		}

		// 捨牌表示(3段目)
		for(int tmp_i = 0; tmp_i < line_sutehai_count; tmp_i++){

			// 捨牌INDEXの定義
			tmp_sute_idx = tmp_i + LINE_SUTEHAI_COUNT_MAX*2;

			// 牌モード確認
			if( kawa_mode[tmp_sute_idx] >= RIICHI_STAT_NUM ){
				tmp_kawa_mode =  kawa_mode[tmp_sute_idx] - RIICHI_STAT_NUM;
				riichi_flg = true;
			}else{
				tmp_kawa_mode =  kawa_mode[tmp_sute_idx];
				riichi_flg = false;
			}

			// 捨牌表示
			if(riichi_flg == true){
				// 捨牌表示 - リーチ牌
				DispLHai( tmp_x, tmp_y+7, kawa_tbl[tmp_sute_idx], kawa_tbl_aka[tmp_sute_idx], false, tmp_kawa_mode, 0);
				tmp_x = tmp_x + LHAI_XSIZE;
			}else{
				// 捨牌表示 - 通常
				DispHai( tmp_x, tmp_y,    kawa_tbl[tmp_sute_idx], kawa_tbl_aka[tmp_sute_idx], false, tmp_kawa_mode, 0);
				tmp_x = tmp_x + HAI_XSIZE;
			}

		}
	}

	// ----------------------------------------
	// 捨牌表示(4段目)
	// ----------------------------------------
	if(kawa_tbl_count > LINE_SUTEHAI_COUNT_MAX*3){

		// 変数定義
		tmp_x = x;
		tmp_y = y+HAI_YSIZE*3;

		// 牌枚数
		if(kawa_tbl_count > LINE_SUTEHAI_COUNT_MAX*4){
			line_sutehai_count = LINE_SUTEHAI_COUNT_MAX;
		}else{
			line_sutehai_count = kawa_tbl_count - LINE_SUTEHAI_COUNT_MAX*3;
		}

		// 捨牌表示(3段目)
		for(int tmp_i = 0; tmp_i < line_sutehai_count; tmp_i++){

			// 捨牌INDEXの定義
			tmp_sute_idx = tmp_i + LINE_SUTEHAI_COUNT_MAX*3;

			// 牌モード確認
			if( kawa_mode[tmp_sute_idx] >= RIICHI_STAT_NUM ){
				tmp_kawa_mode =  kawa_mode[tmp_sute_idx] - RIICHI_STAT_NUM;
				riichi_flg = true;
			}else{
				tmp_kawa_mode =  kawa_mode[tmp_sute_idx];
				riichi_flg = false;
			}

			// 捨牌表示
			if(riichi_flg == true){
				// 捨牌表示 - リーチ牌
				DispLHai( tmp_x, tmp_y+7, kawa_tbl[tmp_sute_idx], kawa_tbl_aka[tmp_sute_idx], false, tmp_kawa_mode, 0);
				tmp_x = tmp_x + LHAI_XSIZE;
			}else{
				// 捨牌表示 - 通常
				DispHai( tmp_x, tmp_y,    kawa_tbl[tmp_sute_idx], kawa_tbl_aka[tmp_sute_idx], false, tmp_kawa_mode, 0);
				tmp_x = tmp_x + HAI_XSIZE;
			}

		}
	}



}

/* ---------------------------------------------------------------------------------------------- */
// アクション河情報・LEFTプレーヤ表示
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispActKawaParts_left(int x, int y, int kawa_tbl_count, int kawa_tbl[], bool kawa_tbl_aka[], int kawa_mode[]){

	// ----------------------------------------
	// 変数初期化
	// ----------------------------------------
	int  tmp_x;
	int  tmp_y;
	int  line_sutehai_count = 0;
	int  tmp_sute_idx = 0;
	int  tmp_kawa_mode = 0;
	bool riichi_flg = false;

	// ----------------------------------------
	// 捨牌表示(1段目)
	// ----------------------------------------
	if( kawa_tbl_count > 0){

		// 変数定義
		tmp_x = x;
		tmp_y = y;

		// 牌枚数
		if(kawa_tbl_count > LINE_SUTEHAI_COUNT_MAX){
			line_sutehai_count = LINE_SUTEHAI_COUNT_MAX;
		}else{
			line_sutehai_count = kawa_tbl_count;
		}

		// 捨牌表示(1段目)
		for(int tmp_i = 0; tmp_i < line_sutehai_count; tmp_i++){

			// 捨牌INDEXの定義
			tmp_sute_idx = tmp_i;

			// 牌モード確認
			if( kawa_mode[tmp_sute_idx] >= RIICHI_STAT_NUM ){
				tmp_kawa_mode =  kawa_mode[tmp_sute_idx] - RIICHI_STAT_NUM;
				riichi_flg = true;
			}else{
				tmp_kawa_mode =  kawa_mode[tmp_sute_idx];
				riichi_flg = false;
			}

			// 捨牌表示
			if(riichi_flg == true){
				// 捨牌表示 - リーチ牌
				DispHai( tmp_x+7, tmp_y, kawa_tbl[tmp_sute_idx], kawa_tbl_aka[tmp_sute_idx], false, tmp_kawa_mode, 0);
				tmp_y = tmp_y + HAI_YSIZE;
			}else{
				// 捨牌表示 - 通常牌
				DispLHai(tmp_x,   tmp_y, kawa_tbl[tmp_sute_idx], kawa_tbl_aka[tmp_sute_idx], true,  tmp_kawa_mode, 0);
				tmp_y = tmp_y + LHAI_YSIZE;
			}
		}
	}

	// ----------------------------------------
	// 捨牌表示(2段目)
	// ----------------------------------------
	if( kawa_tbl_count > LINE_SUTEHAI_COUNT_MAX){

		// 変数定義
		tmp_x = x-LHAI_XSIZE*1;
		tmp_y = y;

		// 牌枚数
		if(kawa_tbl_count > LINE_SUTEHAI_COUNT_MAX*2){
			line_sutehai_count = LINE_SUTEHAI_COUNT_MAX;
		}else{
			line_sutehai_count = kawa_tbl_count - LINE_SUTEHAI_COUNT_MAX;
		}

		// 捨牌表示(1段目)
		for(int tmp_i = 0; tmp_i < line_sutehai_count; tmp_i++){

			// 捨牌INDEXの定義
			tmp_sute_idx = tmp_i + LINE_SUTEHAI_COUNT_MAX;

			// 牌モード確認
			if( kawa_mode[tmp_sute_idx] >= RIICHI_STAT_NUM ){
				tmp_kawa_mode =  kawa_mode[tmp_sute_idx] - RIICHI_STAT_NUM;
				riichi_flg = true;
			}else{
				tmp_kawa_mode =  kawa_mode[tmp_sute_idx];
				riichi_flg = false;
			}

			// 捨牌表示
			if(riichi_flg == true){
				// 捨牌表示 - リーチ牌
				DispHai( tmp_x+7, tmp_y, kawa_tbl[tmp_sute_idx], kawa_tbl_aka[tmp_sute_idx], false, tmp_kawa_mode, 0);
				tmp_y = tmp_y + HAI_YSIZE;
			}else{
				// 捨牌表示 - 通常牌
				DispLHai(tmp_x,   tmp_y, kawa_tbl[tmp_sute_idx], kawa_tbl_aka[tmp_sute_idx], true,  tmp_kawa_mode, 0);
				tmp_y = tmp_y + LHAI_YSIZE;
			}
		}

	}

	// ----------------------------------------
	// 捨牌表示(3段目)
	// ----------------------------------------
	if( kawa_tbl_count > LINE_SUTEHAI_COUNT_MAX*2){

		// 変数定義
		tmp_x = x-LHAI_XSIZE*2;
		tmp_y = y;

		// 牌枚数
		if(kawa_tbl_count > LINE_SUTEHAI_COUNT_MAX*3){
			line_sutehai_count = LINE_SUTEHAI_COUNT_MAX;
		}else{
			line_sutehai_count = kawa_tbl_count - LINE_SUTEHAI_COUNT_MAX*2;
		}

		// 捨牌表示(1段目)
		for(int tmp_i = 0; tmp_i < line_sutehai_count; tmp_i++){

			// 捨牌INDEXの定義
			tmp_sute_idx = tmp_i + LINE_SUTEHAI_COUNT_MAX*2;

			// 牌モード確認
			if( kawa_mode[tmp_sute_idx] >= RIICHI_STAT_NUM ){
				tmp_kawa_mode =  kawa_mode[tmp_sute_idx] - RIICHI_STAT_NUM;
				riichi_flg = true;
			}else{
				tmp_kawa_mode =  kawa_mode[tmp_sute_idx];
				riichi_flg = false;
			}

			// 捨牌表示
			if(riichi_flg == true){
				// 捨牌表示 - リーチ牌
				DispHai( tmp_x+7, tmp_y, kawa_tbl[tmp_sute_idx], kawa_tbl_aka[tmp_sute_idx], false, tmp_kawa_mode, 0);
				tmp_y = tmp_y + HAI_YSIZE;
			}else{
				// 捨牌表示 - 通常牌
				DispLHai(tmp_x,   tmp_y, kawa_tbl[tmp_sute_idx], kawa_tbl_aka[tmp_sute_idx], true,  tmp_kawa_mode, 0);
				tmp_y = tmp_y + LHAI_YSIZE;
			}
		}

	}

	// ----------------------------------------
	// 捨牌表示(4段目)
	// ----------------------------------------
	if( kawa_tbl_count > LINE_SUTEHAI_COUNT_MAX*3){

		// 変数定義
		tmp_x = x-LHAI_XSIZE*3;
		tmp_y = y;

		// 牌枚数
		if(kawa_tbl_count > LINE_SUTEHAI_COUNT_MAX*4){
			line_sutehai_count = LINE_SUTEHAI_COUNT_MAX;
		}else{
			line_sutehai_count = kawa_tbl_count - LINE_SUTEHAI_COUNT_MAX*3;
		}

		// 捨牌表示(1段目)
		for(int tmp_i = 0; tmp_i < line_sutehai_count; tmp_i++){

			// 捨牌INDEXの定義
			tmp_sute_idx = tmp_i + LINE_SUTEHAI_COUNT_MAX*3;

			// 牌モード確認
			if( kawa_mode[tmp_sute_idx] >= RIICHI_STAT_NUM ){
				tmp_kawa_mode =  kawa_mode[tmp_sute_idx] - RIICHI_STAT_NUM;
				riichi_flg = true;
			}else{
				tmp_kawa_mode =  kawa_mode[tmp_sute_idx];
				riichi_flg = false;
			}

			// 捨牌表示
			if(riichi_flg == true){
				// 捨牌表示 - リーチ牌
				DispHai( tmp_x+7, tmp_y, kawa_tbl[tmp_sute_idx], kawa_tbl_aka[tmp_sute_idx], false, tmp_kawa_mode, 0);
				tmp_y = tmp_y + HAI_YSIZE;
			}else{
				// 捨牌表示 - 通常牌
				DispLHai(tmp_x,   tmp_y, kawa_tbl[tmp_sute_idx], kawa_tbl_aka[tmp_sute_idx], true,  tmp_kawa_mode, 0);
				tmp_y = tmp_y + LHAI_YSIZE;
			}
		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// アクション河情報・RIGHTプレーヤ表示
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispActKawaParts_right(int x, int y, int kawa_tbl_count, int kawa_tbl[], bool kawa_tbl_aka[], int kawa_mode[]){

	// ----------------------------------------
	// 変数初期化
	// ----------------------------------------
	int  tmp_x;
	int  tmp_y;
	int  line_sutehai_count = 0;
	int  tmp_sute_idx = 0;
	int  tmp_kawa_mode = 0;
	bool riichi_flg = false;
	bool disp_riichi_flg = false;

	// ----------------------------------------
	// 捨牌表示(1段目)
	// ----------------------------------------
	if( kawa_tbl_count > 0){

		// 行の牌枚数
		if(kawa_tbl_count > LINE_SUTEHAI_COUNT_MAX){
			line_sutehai_count = LINE_SUTEHAI_COUNT_MAX;
		}else{
			line_sutehai_count = kawa_tbl_count;
		}

		// 行リーチ確認
		disp_riichi_flg = false;
		for(int tmp_i = 0; tmp_i < line_sutehai_count; tmp_i++){
			if( kawa_mode[tmp_i] >= RIICHI_STAT_NUM ){
				disp_riichi_flg = true;
				break;
			}
		}

		// 変数定義
		tmp_x = x;
		tmp_y = y + LHAI_YSIZE*(LINE_SUTEHAI_COUNT_MAX-line_sutehai_count);  // 空白分だけ下げる

		// リーチ位置の修正
		if( disp_riichi_flg == true ){
			tmp_y=tmp_y-8;
		}

		// 捨牌表示(Rightプレーヤ)
		for(int tmp_i = 0; tmp_i < line_sutehai_count; tmp_i++){

			// 捨牌INDEXの定義
			tmp_sute_idx = 0 + line_sutehai_count - tmp_i - 1;

			// 牌モード確認
			if( kawa_mode[tmp_sute_idx] >= RIICHI_STAT_NUM ){
				tmp_kawa_mode =  kawa_mode[tmp_sute_idx] - RIICHI_STAT_NUM;
				riichi_flg = true;
			}else{
				tmp_kawa_mode =  kawa_mode[tmp_sute_idx];
				riichi_flg = false;
			}

			// 捨牌表示
			if(riichi_flg == true){
				// 捨牌表示 - リーチ牌
				DispHai( tmp_x, tmp_y, kawa_tbl[tmp_sute_idx], kawa_tbl_aka[tmp_sute_idx], true,  tmp_kawa_mode, 0);
				tmp_y = tmp_y + HAI_YSIZE;
			}else{
				// 捨牌表示 - 通常牌
				DispLHai( tmp_x,  tmp_y, kawa_tbl[tmp_sute_idx], kawa_tbl_aka[tmp_sute_idx], false, tmp_kawa_mode, 0);    // Right1段目
				tmp_y = tmp_y + LHAI_YSIZE;
			}

		}

	}

	// ----------------------------------------
	// 捨牌表示(2段目)
	// ----------------------------------------
	if( kawa_tbl_count > 6){

		// 行の牌枚数
		if(kawa_tbl_count > 12){
			line_sutehai_count = 6;
		}else{
			line_sutehai_count = kawa_tbl_count - 6;
		}

		// 行リーチ確認
		disp_riichi_flg = false;
		for(int tmp_i = 0; tmp_i < line_sutehai_count; tmp_i++){
			if( kawa_mode[tmp_i+6] >= RIICHI_STAT_NUM ){
				disp_riichi_flg = true;
				break;
			}
		}

		// 変数定義
		tmp_x = x + LHAI_XSIZE*1;
		tmp_y = y + LHAI_YSIZE*(LINE_SUTEHAI_COUNT_MAX-line_sutehai_count);  // 空白分だけ下げる

		// リーチ位置の修正
		if( disp_riichi_flg == true ){
			tmp_y=tmp_y-8;
		}

		// 捨牌表示(Rightプレーヤ)
		for(int tmp_i = 0; tmp_i < line_sutehai_count; tmp_i++){

			// 捨牌INDEXの定義
			tmp_sute_idx = LINE_SUTEHAI_COUNT_MAX + line_sutehai_count - tmp_i - 1;

			// 牌モード確認
			if( kawa_mode[tmp_sute_idx] >= RIICHI_STAT_NUM ){
				tmp_kawa_mode =  kawa_mode[tmp_sute_idx] - RIICHI_STAT_NUM;
				riichi_flg = true;
			}else{
				tmp_kawa_mode =  kawa_mode[tmp_sute_idx];
				riichi_flg = false;
			}

			// 捨牌表示
			if(riichi_flg == true){
				// 捨牌表示 - リーチ牌
				DispHai( tmp_x, tmp_y, kawa_tbl[tmp_sute_idx], kawa_tbl_aka[tmp_sute_idx], true,  tmp_kawa_mode, 0);
				tmp_y = tmp_y + HAI_YSIZE;
			}else{
				// 捨牌表示 - 通常牌
				DispLHai( tmp_x,  tmp_y, kawa_tbl[tmp_sute_idx], kawa_tbl_aka[tmp_sute_idx], false, tmp_kawa_mode, 0);    // Right2段目
				tmp_y = tmp_y + LHAI_YSIZE;
			}

		}


	}

	// ----------------------------------------
	// 捨牌表示(3段目)
	// ----------------------------------------
	if( kawa_tbl_count > 12){

		// 行の牌枚数
		if(kawa_tbl_count > 18){
			line_sutehai_count = 6;
		}else{
			line_sutehai_count = kawa_tbl_count - 12;
		}

		// 行リーチ確認
		disp_riichi_flg = false;
		for(int tmp_i = 0; tmp_i < line_sutehai_count; tmp_i++){
			if( kawa_mode[tmp_i+12] >= RIICHI_STAT_NUM ){
				disp_riichi_flg = true;
				break;
			}
		}

		// 変数定義
		tmp_x = x + LHAI_XSIZE*2;
		tmp_y = y + LHAI_YSIZE*(LINE_SUTEHAI_COUNT_MAX-line_sutehai_count);  // 空白分だけ下げる

		// リーチ位置の修正
		if( disp_riichi_flg == true ){
			tmp_y=tmp_y-8;
		}

		// 捨牌表示(Rightプレーヤ)
		for(int tmp_i = 0; tmp_i < line_sutehai_count; tmp_i++){

			// 捨牌INDEXの定義
			tmp_sute_idx = LINE_SUTEHAI_COUNT_MAX*2 + line_sutehai_count - tmp_i - 1;

			// 牌モード確認
			if( kawa_mode[tmp_sute_idx] >= RIICHI_STAT_NUM ){
				tmp_kawa_mode =  kawa_mode[tmp_sute_idx] - RIICHI_STAT_NUM;
				riichi_flg = true;
			}else{
				tmp_kawa_mode =  kawa_mode[tmp_sute_idx];
				riichi_flg = false;
			}

			// 捨牌表示
			if(riichi_flg == true){
				// 捨牌表示 - リーチ牌
				DispHai( tmp_x, tmp_y, kawa_tbl[tmp_sute_idx], kawa_tbl_aka[tmp_sute_idx], true,  tmp_kawa_mode, 0);
				tmp_y = tmp_y + HAI_YSIZE;
			}else{
				// 捨牌表示 - 通常牌
				DispLHai( tmp_x,  tmp_y, kawa_tbl[tmp_sute_idx], kawa_tbl_aka[tmp_sute_idx], false, tmp_kawa_mode, 0);    // Right2段目
				tmp_y = tmp_y + LHAI_YSIZE;
			}

		}

	}

	// ----------------------------------------
	// 捨牌表示(4段目)
	// ----------------------------------------
	if( kawa_tbl_count > 18){

		// 行の牌枚数
		line_sutehai_count = kawa_tbl_count - 18;

		// 行リーチ確認
		disp_riichi_flg = false;
		for(int tmp_i = 0; tmp_i < line_sutehai_count; tmp_i++){
			if( kawa_mode[tmp_i+18] >= RIICHI_STAT_NUM ){
				disp_riichi_flg = true;
				break;
			}
		}

		// 変数定義
		tmp_x = x + LHAI_XSIZE*3;
		tmp_y = y + LHAI_YSIZE*(LINE_SUTEHAI_COUNT_MAX-line_sutehai_count);  // 空白分だけ下げる

		// リーチ位置の修正
		if( disp_riichi_flg == true ){
			tmp_y=tmp_y-8;
		}

		// 捨牌表示(Rightプレーヤ)
		for(int tmp_i = 0; tmp_i < line_sutehai_count; tmp_i++){

			// 捨牌INDEXの定義
			tmp_sute_idx = LINE_SUTEHAI_COUNT_MAX*3 + line_sutehai_count - tmp_i - 1;

			// 牌モード確認
			if( kawa_mode[tmp_sute_idx] >= RIICHI_STAT_NUM ){
				tmp_kawa_mode =  kawa_mode[tmp_sute_idx] - RIICHI_STAT_NUM;
				riichi_flg = true;
			}else{
				tmp_kawa_mode =  kawa_mode[tmp_sute_idx];
				riichi_flg = false;
			}

			// 捨牌表示
			if(riichi_flg == true){
				// 捨牌表示 - リーチ牌
				DispHai( tmp_x, tmp_y, kawa_tbl[tmp_sute_idx], kawa_tbl_aka[tmp_sute_idx], true,  tmp_kawa_mode, 0);
				tmp_y = tmp_y + HAI_YSIZE;
			}else{
				// 捨牌表示 - 通常牌
				DispLHai( tmp_x,  tmp_y, kawa_tbl[tmp_sute_idx], kawa_tbl_aka[tmp_sute_idx], false, tmp_kawa_mode, 0);    // Right2段目
				tmp_y = tmp_y + LHAI_YSIZE;
			}

		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 晒し面子のパーツ表示：UPプレーヤ表示
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispActSarashiParts_up(int x, int y, LBMen naki_stat, int hai_index, int aka_count){

	// ----------------------------------------
	// 変数の初期化
	// ----------------------------------------
	int tmp_aka_count = aka_count;

	// ----------------------------------------
	// ポン牌の表示
	// ----------------------------------------
	if( naki_stat == MINKO || naki_stat == ANKO ){

		// 晒し牌の表示
		for(int tmp_i = 0; tmp_i < 3; tmp_i++){
 			if( ( hai_index == 5 || hai_index == 15 || hai_index == 25) && tmp_aka_count > 0 ){
 				DispHai( x-HAI_XSIZE*tmp_i, y, hai_index, true, true,  0, 0);
				tmp_aka_count--;
			}else{
				DispHai( x-HAI_XSIZE*tmp_i, y, hai_index, false, true, 0, 0);
			}
		}

	// ----------------------------------------
	// チー牌の表示
	// ----------------------------------------
	}else if(naki_stat == MINSHUN || naki_stat == SHUNTSU ){

		// 晒し牌の表示(1枚目)
 		if( ( hai_index == 5 || hai_index == 15 || hai_index == 25) && tmp_aka_count > 0 ){
			DispHai( x-HAI_XSIZE*0, y, hai_index, true, true, 0, 0);
			tmp_aka_count--;
		}else{
			DispHai( x-HAI_XSIZE*0, y, hai_index, false, true, 0, 0);
		}

		// 晒し牌の表示(2枚目)
 		if( ( hai_index+1 == 5 || hai_index+1 == 15 || hai_index+1 == 25) && tmp_aka_count > 0 ){
			DispHai( x-HAI_XSIZE  , y, hai_index+1, true, true, 0, 0);
			tmp_aka_count--;
		}else{
			DispHai( x-HAI_XSIZE  , y, hai_index+1, false, true, 0, 0);
		}

		// 晒し牌の表示(3枚目)
 		if( ( hai_index+2 == 5 || hai_index+2 == 15 || hai_index+2 == 25) && tmp_aka_count > 0 ){
			DispHai( x-HAI_XSIZE*2, y, hai_index+2, true, true, 0, 0);
			tmp_aka_count--;
		}else{
			DispHai( x-HAI_XSIZE*2, y, hai_index+2, false, true, 0, 0);
		}

	// ----------------------------------------
	// 暗槓牌の表示
	// ----------------------------------------
	}else if(naki_stat == ANKAN){

		// 晒し牌の表示(オープン1枚目)
		if( tmp_aka_count > 0 ){
			DispHai( x-HAI_XSIZE  , y, hai_index, true, true, 0, 0);
		}else{
			DispHai( x-HAI_XSIZE  , y, hai_index, false, true, 0, 0);
		}

		// 晒し牌の表示(オープン2枚目)
		if( tmp_aka_count > 1 ){
			DispHai( x-HAI_XSIZE*2, y, hai_index, true, true, 0, 0);
		}else{
			DispHai( x-HAI_XSIZE*2, y, hai_index, false, true, 0, 0);
		}

		// 裏向き牌
		DispHai( x,             y, 0, false, false, 0, 0);
		DispHai( x-HAI_XSIZE*3, y, 0, false, false, 0, 0);

	// ----------------------------------------
	// 明槓牌の表示
	// ----------------------------------------
	}else if(naki_stat == MINKAN){

		// 晒し牌の表示(オープン1枚目)
		if( tmp_aka_count > 0 ){
			DispHai( x            , y, hai_index, true, true, 0, 0);
		}else{
			DispHai( x            , y, hai_index, false, true, 0, 0);
		}

		// 晒し牌の表示(オープン2枚目)
		if( tmp_aka_count > 1 ){
			DispHai( x-HAI_XSIZE*1, y, hai_index, true, true, 0, 0);
		}else{
			DispHai( x-HAI_XSIZE*1, y, hai_index, false, true, 0, 0);
		}

		// 晒し牌の表示(オープン3枚目)
		if( tmp_aka_count > 2 ){
			DispHai( x-HAI_XSIZE*2, y, hai_index, true, true, 0, 0);
		}else{
			DispHai( x-HAI_XSIZE*2, y, hai_index, false, true, 0, 0);
		}

		// 晒し牌の表示(オープン4枚目)
		if( tmp_aka_count > 3 ){
			DispHai( x-HAI_XSIZE*3, y, hai_index, true, true, 0, 0);
		}else{
			DispHai( x-HAI_XSIZE*3, y, hai_index, false, true, 0, 0);
		}

	// ----------------------------------------
	// 加槓牌の表示
	// ----------------------------------------
	}else if(naki_stat == KAKAN){

		// 晒し牌の表示(オープン4枚目)
		if( tmp_aka_count > 0 ){
			DispHai( x-HAI_XSIZE*3, y, hai_index, true, true, 0, 0);
		}else{
			DispHai( x-HAI_XSIZE*3, y, hai_index, false, true, 0, 0);
		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 晒し面子のパーツ表示：LEFTプレーヤ表示
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispActSarashiParts_left(int x, int y, LBMen naki_stat, int hai_index, int aka_count){

	// ----------------------------------------
	// 変数の初期化
	// ----------------------------------------
	int tmp_aka_count = aka_count;

	// ----------------------------------------
	// ポン牌の表示
	// ----------------------------------------
	if( naki_stat == MINKO || naki_stat == ANKO ){

		// 晒し牌の表示
		for(int tmp_i = 0; tmp_i < 3; tmp_i++){
 			if( ( hai_index == 5 || hai_index == 15 || hai_index == 25) && tmp_aka_count > 0 ){
 				DispLHai( x, y+LHAI_YSIZE*tmp_i, hai_index, true, true,  0, 0);
				tmp_aka_count--;
			}else{
				DispLHai( x, y+LHAI_YSIZE*tmp_i, hai_index, false, true, 0, 0);
			}
		}

	// ----------------------------------------
	// チー牌の表示
	// ----------------------------------------
	}else if(naki_stat == MINSHUN || naki_stat == SHUNTSU ){

		// 晒し牌の表示(1枚目)
 		if( ( hai_index == 5 || hai_index == 15 || hai_index == 25) && tmp_aka_count > 0 ){
			DispLHai( x, y+LHAI_YSIZE*0, hai_index, true, true, 0, 0);
			tmp_aka_count--;
		}else{
			DispLHai( x, y+LHAI_YSIZE*0, hai_index, false, true, 0, 0);
		}

		// 晒し牌の表示(2枚目)
 		if( ( hai_index+1 == 5 || hai_index+1 == 15 || hai_index+1 == 25) && tmp_aka_count > 0 ){
			DispLHai( x, y+LHAI_YSIZE*1, hai_index+1, true, true, 0, 0);
			tmp_aka_count--;
		}else{
			DispLHai( x, y+LHAI_YSIZE*1, hai_index+1, false, true, 0, 0);
		}

		// 晒し牌の表示(3枚目)
 		if( ( hai_index+2 == 5 || hai_index+2 == 15 || hai_index+2 == 25) && tmp_aka_count > 0 ){
			DispLHai( x, y+LHAI_YSIZE*2, hai_index+2, true, true, 0, 0);
			tmp_aka_count--;
		}else{
			DispLHai( x, y+LHAI_YSIZE*2, hai_index+2, false, true, 0, 0);
		}

	// ----------------------------------------
	// 暗槓牌の表示
	// ----------------------------------------
	}else if(naki_stat == ANKAN){

		// 裏向き牌
		DispLHai( x, y+LHAI_YSIZE*0, 0, false, false, 0, 0);

		// 晒し牌の表示(オープン1枚目)
		if( tmp_aka_count > 0 ){
			DispLHai( x, y+LHAI_YSIZE*1, hai_index, true, true, 0, 0);
		}else{
			DispLHai( x, y+LHAI_YSIZE*1, hai_index, false, true, 0, 0);
		}

		// 晒し牌の表示(オープン2枚目)
		if( tmp_aka_count > 1 ){
			DispLHai( x, y+LHAI_YSIZE*2, hai_index, true, true, 0, 0);
		}else{
			DispLHai( x, y+LHAI_YSIZE*2, hai_index, false, true, 0, 0);
		}

		// 裏向き牌
		DispLHai( x, y+LHAI_YSIZE*3, 0, false, false, 0, 0);

	// ----------------------------------------
	// 明槓牌の表示
	// ----------------------------------------
	}else if(naki_stat == MINKAN){

		// 晒し牌の表示(オープン1枚目)
		if( tmp_aka_count > 0 ){
			DispLHai( x, y+LHAI_YSIZE*0, hai_index, true, true, 0, 0);
		}else{
			DispLHai( x, y+LHAI_YSIZE*0, hai_index, false, true, 0, 0);
		}

		// 晒し牌の表示(オープン2枚目)
		if( tmp_aka_count > 1 ){
			DispLHai( x, y+LHAI_YSIZE*1, hai_index, true, true, 0, 0);
		}else{
			DispLHai( x, y+LHAI_YSIZE*1, hai_index, false, true, 0, 0);
		}

		// 晒し牌の表示(オープン3枚目)
		if( tmp_aka_count > 2 ){
			DispLHai( x, y+LHAI_YSIZE*2, hai_index, true, true, 0, 0);
		}else{
			DispLHai( x, y+LHAI_YSIZE*2, hai_index, false, true, 0, 0);
		}

		// 晒し牌の表示(オープン4枚目)
		if( tmp_aka_count > 3 ){
			DispLHai( x, y+LHAI_YSIZE*3, hai_index, true, true, 0, 0);
		}else{
			DispLHai( x, y+LHAI_YSIZE*3, hai_index, false, true, 0, 0);
		}

	// ----------------------------------------
	// 加槓牌の表示
	// ----------------------------------------
	}else if(naki_stat == KAKAN){

		// 晒し牌の表示(オープン4枚目)
		if( tmp_aka_count > 0 ){
			DispLHai( x, y+LHAI_YSIZE*3, hai_index, true, true, 0, 0);
		}else{
			DispLHai( x, y+LHAI_YSIZE*3, hai_index, false, true, 0, 0);
		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 晒し面子のパーツ表示：RIGHTプレーヤ表示
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispActSarashiParts_right(int x, int y, LBMen naki_stat, int hai_index, int aka_count){

	// ----------------------------------------
	// 変数の初期化
	// ----------------------------------------
	int tmp_aka_count = aka_count;

	// ----------------------------------------
	// ポン牌の表示
	// ----------------------------------------
	if( naki_stat == MINKO || naki_stat == ANKO ){

		// 晒し牌の表示
		for(int tmp_i = 0; tmp_i < 3; tmp_i++){
 			if( ( hai_index == 5 || hai_index == 15 || hai_index == 25) && tmp_aka_count > 0 ){
 				DispLHai( x, y+LHAI_YSIZE*tmp_i, hai_index, true,  false, 0, 0);
				tmp_aka_count--;
			}else{
				DispLHai( x, y+LHAI_YSIZE*tmp_i, hai_index, false, false, 0, 0);
			}
		}

	// ----------------------------------------
	// チー牌の表示
	// ----------------------------------------
	}else if(naki_stat == MINSHUN || naki_stat == SHUNTSU ){

		// 晒し牌の表示(1枚目)
 		if( ( hai_index+2 == 5 || hai_index+2 == 15 || hai_index+2 == 25) && tmp_aka_count > 0 ){
 				DispLHai( x, y+LHAI_YSIZE*0, hai_index+2, true,  false, 0, 0);
				tmp_aka_count--;
		}else{
				DispLHai( x, y+LHAI_YSIZE*0, hai_index+2, false, false, 0, 0);
		}

		// 晒し牌の表示(2枚目)
 		if( ( hai_index+1 == 5 || hai_index+1 == 15 || hai_index+1 == 25) && tmp_aka_count > 0 ){
 				DispLHai( x, y+LHAI_YSIZE*1, hai_index+1, true,  false, 0, 0);
				tmp_aka_count--;
		}else{
				DispLHai( x, y+LHAI_YSIZE*1, hai_index+1, false, false, 0, 0);
		}

		// 晒し牌の表示(3枚目)
 		if( ( hai_index   == 5 || hai_index   == 15 || hai_index   == 25) && tmp_aka_count > 0 ){
 				DispLHai( x, y+LHAI_YSIZE*2, hai_index  , true,  false, 0, 0);
				tmp_aka_count--;
		}else{
				DispLHai( x, y+LHAI_YSIZE*2, hai_index  , false, false, 0, 0);
		}

	// ----------------------------------------
	// 暗槓牌の表示
	// ----------------------------------------
	}else if(naki_stat == ANKAN){

		// 裏向き牌
		DispLHai( x, y,                 0,          false, false, 0, 0);

		// 晒し牌の表示(オープン1枚目)
		if( tmp_aka_count > 0 ){
			DispLHai( x, y+LHAI_YSIZE  , hai_index, true,  false, 0, 0);
		}else{
			DispLHai( x, y+LHAI_YSIZE  , hai_index, false, false, 0, 0);
		}

		// 晒し牌の表示(オープン2枚目)
		if( tmp_aka_count > 1 ){
			DispLHai( x, y+LHAI_YSIZE*2, hai_index, true,  false, 0, 0);
		}else{
			DispLHai( x, y+LHAI_YSIZE*2, hai_index, false, false, 0, 0);
		}

		// 裏向き牌
			DispLHai( x, y+LHAI_YSIZE*3, 0,         false, false, 0, 0);

	// ----------------------------------------
	// 明槓牌の表示
	// ----------------------------------------
	}else if(naki_stat == MINKAN){

		// 晒し牌の表示(オープン1枚目)
		if( tmp_aka_count > 0 ){
			DispLHai( x, y  , hai_index, true,  false, 0, 0);
		}else{
			DispLHai( x, y  , hai_index, false, false, 0, 0);
		}

		// 晒し牌の表示(オープン2枚目)
		if( tmp_aka_count > 1 ){
			DispLHai( x, y+LHAI_YSIZE*1, hai_index, true,  false, 0, 0);
		}else{
			DispLHai( x, y+LHAI_YSIZE*1, hai_index, false, false, 0, 0);
		}

		// 晒し牌の表示(オープン3枚目)
		if( tmp_aka_count > 2 ){
			DispLHai( x, y+LHAI_YSIZE*2 , hai_index, true,  false, 0, 0);
		}else{
			DispLHai( x, y+LHAI_YSIZE*2 , hai_index, false, false, 0, 0);
		}

		// 晒し牌の表示(オープン4枚目)
		if( tmp_aka_count > 3 ){
			DispLHai( x, y+LHAI_YSIZE*3, hai_index, true,  false, 0, 0);
		}else{
			DispLHai( x, y+LHAI_YSIZE*3, hai_index, false, false, 0, 0);
		}

	// ----------------------------------------
	// 加槓牌の表示
	// ----------------------------------------
	}else if(naki_stat == KAKAN){

		// 晒し牌の表示(オープン4枚目)
		if( tmp_aka_count > 0 ){
			DispLHai( x, y+LHAI_YSIZE*3, hai_index, true,  false, 0, 0);
		}else{
			DispLHai( x, y+LHAI_YSIZE*3, hai_index, false, false, 0, 0);
		}

	}
}

/* ---------------------------------------------------------------------------------------------- */
// 席情報の表示：UPプレーヤ表示
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispName_up(int x, int y, char *str){

	// 席情報の表示：UPプレーヤ表示
	DrawRotaString( x, y, 1.0, 1.0, 0, 0, PI, GetColor( 255, 255, 255 ), 0, FALSE, str);

}

/* ---------------------------------------------------------------------------------------------- */
// 席情報の表示：LEFTプレーヤ表示
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispName_left(int x, int y, char *str){

	// 席情報の表示：LEFTプレーヤ表示
	DrawRotaString( x, y, 1.0, 1.0, 0, 0, PI / 2.0, GetColor( 255, 255, 255 ), 0, FALSE, str);

}

/* ---------------------------------------------------------------------------------------------- */
// 席情報の表示：RIGHTプレーヤ表示
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispName_right(int x, int y, char *str){

	// 席情報の表示：RIGHTプレーヤ表示
	DrawRotaString( x, y, 1.0, 1.0, 0, 0, PI*3.0 / 2.0, GetColor( 255, 255, 255 ), 0, FALSE, str);

}

/* ---------------------------------------------------------------------------------------------- */
// アクションプレート表示：UPプレーヤ表示
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispActplt_up(int x, int y, char *str){

	// アクションプレート_UP
	DrawBox( x + 4 - 56, 
	         y + 4 - 23,
	         x + 4 ,
	         y + 4 ,
	         GetColor( 128, 0, 0 ), TRUE ) ;

	// 文字表示_UP
	DrawRotaString( x, y,
	                1.0, 1.0, 0, 0, PI, GetColor( 255, 255, 255 ), 0, FALSE, str);

}

/* ---------------------------------------------------------------------------------------------- */
// アクションプレート表示：DOWNプレーヤ表示
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispActplt_down(int x, int y, char *str){

	// アクションプレート_DOWN
	DrawBox( x - 4, 
	         y - 4,
	         x - 4 + 56,
	         y - 4 + 23,
	         GetColor( 128, 0, 0 ), TRUE ) ;

	// 文字表示_DOWN
	DispString( x, y, str);

}

/* ---------------------------------------------------------------------------------------------- */
// アクションプレート表示：LEFTプレーヤ表示
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispActplt_left(int x, int y, char *str){

	// アクションプレート_LEFT
	DrawBox( x + 4 - 23, 
	         y - 4 ,
	         x + 4 ,
	         y - 4 + 56,
	         GetColor( 128, 0, 0 ), TRUE ) ;

	// 文字表示_LEFT
	DrawRotaString( x, y,
	                1.0, 1.0, 0, 0, PI / 2.0, GetColor( 255, 255, 255 ), 0, FALSE, str);

}

/* ---------------------------------------------------------------------------------------------- */
// アクションプレート表示：RIGHTプレーヤ表示
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispActplt_right(int x, int y, char *str){

	// アクションプレート_RIGHT
	DrawBox( x - 4, 
	         y + 4 - 56,
	         x - 4 + 23,
	         y + 4 ,
	         GetColor( 128, 0, 0 ), TRUE ) ;

	// 文字表示_RIGHT
	DrawRotaString( x, y,
	                1.0, 1.0, 0, 0, PI * 3.0 / 2.0, GetColor( 255, 255, 255 ), 0, FALSE, str);

}

/* ---------------------------------------------------------------------------------------------- */
// ソース終了
/* ---------------------------------------------------------------------------------------------- */
