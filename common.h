/* ---------------------------------------------------------------------------------------------- 
 * 
 * プログラム概要 ： さくら麻雀(Ver0.1.2.1：開発版)
 * バージョン     ： 0.1.2.1.234(表示牌(open_haiparts)一覧表示)
 * プログラム名   ： mjs.exe
 * ファイル名     ： common.h
 * クラス名       ： 共通ヘッダー
 * 処理概要       ： 共通ヘッダー
 * Ver0.1.2作成日 ： 2023/11/04 09:10:01
 * 最終更新日     ： 2025/02/01 09:57:37
 * 
 * Copyright (c) 2010-2025 TechMileStoraJP, All rights reserved.
 * 
 * ---------------------------------------------------------------------------------------------- */

#pragma once

#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

/* ---------------------------------------------------------------------------------------------- */
// 固定値
/* ---------------------------------------------------------------------------------------------- */

// バージョン情報
#define VER1                      0     // 1桁目のバージョン(公開向け)
#define VER2                      1     // 2桁目のバージョン(ソース全体の改変があった場合(一から作り直した場合)、互換性なし)
#define VER3                      2     // 3桁目のバージョン(新機能の追加した場合、又は既存ソースからフォークした場合、互換性あり)
#define VER4                      1     // 4桁目のバージョン(雑多な細かい更新があった場合、互換性あり)
#define VER5                    234     // 5桁目のバージョン(内部管理用、公開時は常に0とする、互換性あり)

// バージョン情報(MJSlog)

#define MJSLOG_VER1               0     // 1桁目のバージョン(公開向け)
#define MJSLOG_VER2               0     // 2桁目のバージョン(ログ出力の形式を全体的に見直した場合、互換性なし)
#define MJSLOG_VER3               1     // 3桁目のバージョン(ログ出力の形式を若干見直した場合、互換性あり)
#define MJSLOG_VER4               3     // 4桁目のバージョン(形式を変更しない細かな更新があった場合、互換性あり)

// プレーヤー情報
#define PLAYER_MAX                4     // プレーヤ数
#define HUM_PLY_SEKI_NUM          3     // Humプレーヤーの席番号

// 牌情報
#define PAI_COUNT_MAX           136     // 牌数
#define HAI_POINT_START          66     // 局開始時点の牌ポインタ番号
#define RINSHAN_POINT_START      10     // 局開始時点の牌ポインタ番号
#define PAI_MAX                  38     // 牌の種類数
#define COLOR_MAX_COUNT           4     // 萬子・筒子・索子・字牌の種別数
#define AKA_TYPE_MAX_COUNT        3     // 赤牌(萬子・筒子・索子)の種別数
#define DORA_MAX                  5     // ドラ最大数
#define TEHAI_MAX                13     // 手牌最大数(自摸牌含まず)
#define TSUMOARI_TEHAI_MAX       14     // 手牌最大数(自摸牌含む)
#define MEN_MAX                   8     // 面子数
#define CHITOI_MEN_MAX            7     // 七対子形式の面子数
#define NORMAL_MACHI_MAX_COUNT   10     // 通常役の待牌数
#define KAWA_HAI_MAX             25     // 捨牌数(河牌の最大数)
#define SUTEHAI_MAX_COUNT        14     // 捨牌候補の最大数
#define NAKI_KOHO_MAX_COUNT      20     // 鳴き候補の最大数
#define CHI_KOHO_COUNT_MAX        6     // チー候補の最大数

// 局情報
#define KYOKU_MAX                64     // 半荘での最大局数
#define ACTID_MAX               200     // ACT_ID最大
#define INITSCORE             25000     // 初期得点
// #define INITSCORE          27000     // 初期得点

// 役情報
#define YAKU_SHUBETSU_MAX        40     // 通常役の最大数
#define YAKUMAN_SHUBETSU_MAX     20     // 役満の最大数
#define RYUKYOKU_SHUBETSU_MAX    10     // 流局種別の最大数
#define NORMALYAKU_MAX           12     // 通常役の最大数

// 内部処理
#define EXCEPT_VALUE            999     // 作業用の例外値

// モード定義
#define SEED_NUM           26234098     // 乱数シード番号

/* ---------------------------------------------------------------------------------------------- */
// 固定値(捨牌の状態)
/* ---------------------------------------------------------------------------------------------- */

#define HAI_COLOR_NUM_NOCOLOR     0     // 「無色」の番号：通常牌の表示
#define HAI_COLOR_NUM_GRAY        1     // 「灰色」の番号：鳴かれた場合
#define HAI_COLOR_NUM_BLUE        2     // 「青色」の番号：鳴き実行確認・和了牌表示
#define HAI_COLOR_NUM_YELLOW      3     // 「黄色」の番号：ドラ牌である場合
#define HAI_COLOR_NUM_GREEN       4     // 「緑色」の番号：強調表示
#define RIICHI_STAT_NUM           5     // リーチ状態

/* ---------------------------------------------------------------------------------------------- 
 * 固定値(牌番号)
 * ---------------------------------------------------------------------------------------------- */

#define HAIZERONUM    0   //  牌番号0

#define MAN1NUM       1   // 「萬子1」牌番号
#define MAN2NUM       2   // 「萬子2」牌番号
#define MAN3NUM       3   // 「萬子3」牌番号
#define MAN4NUM       4   // 「萬子4」牌番号
#define MAN5NUM       5   // 「萬子5」牌番号
#define MAN6NUM       6   // 「萬子6」牌番号
#define MAN7NUM       7   // 「萬子7」牌番号
#define MAN8NUM       8   // 「萬子8」牌番号
#define MAN9NUM       9   // 「萬子9」牌番号

#define PIN1NUM      11   // 「筒子1」牌番号
#define PIN2NUM      12   // 「筒子2」牌番号
#define PIN3NUM      13   // 「筒子3」牌番号
#define PIN4NUM      14   // 「筒子4」牌番号
#define PIN5NUM      15   // 「筒子5」牌番号
#define PIN6NUM      16   // 「筒子6」牌番号
#define PIN7NUM      17   // 「筒子7」牌番号
#define PIN8NUM      18   // 「筒子8」牌番号
#define PIN9NUM      19   // 「筒子9」牌番号

#define SOU1NUM      21   // 「索子1」牌番号
#define SOU2NUM      22   // 「索子2」牌番号
#define SOU3NUM      23   // 「索子3」牌番号
#define SOU4NUM      24   // 「索子4」牌番号
#define SOU5NUM      25   // 「索子5」牌番号
#define SOU6NUM      26   // 「索子6」牌番号
#define SOU7NUM      27   // 「索子7」牌番号
#define SOU8NUM      28   // 「索子8」牌番号
#define SOU9NUM      29   // 「索子9」牌番号

#define TONNUM       31   // 「東」牌番号
#define NANNUM       32   // 「南」牌番号
#define SHANUM       33   // 「西」牌番号
#define PEINUM       34   // 「北」牌番号

#define HAKUNUM      35   // 「白」牌番号
#define HATSUNUM     36   // 「発」牌番号
#define CHUNNUM      37   // 「中」牌番号

#define UNKNOWNNUM   38   // 「？」牌番号

/* ---------------------------------------------------------------------------------------------- */
// ラベル(卓状態)
/* ---------------------------------------------------------------------------------------------- */

// 卓ゲーム種別
typedef enum {

	NO_TKGAME_TYPE = 0,       // 00: 卓ゲーム種別なし
	TKGAME_HANCHAN,           // 01: 半荘戦プレイ
	TKGAME_TONPU,             // 02: 東風戦プレイ
	TKGAME_1KYOKU,            // 03: 一局戦プレイ
	TKGAME_MAXID_TEST,        // 04: 局ID最大プレイ
	TKGAME_MJAI,              // 05: MJAIクライアントモード
	TKGAME_VIEWER,            // 06: ビューアモード(東風戦)
	TKGAME_VIEWER_HANCHAN,    // 07: ビューアモード(半荘戦)

} LBTkGmTYPE;

// 卓状態ラベル
typedef enum {

	PLYNOACT = 0,             // 00: 卓状態の定義なし
	TAKUSTART,                // 01: 卓開始
	BAGIME,                   // 02: 場決め
	KYOKUSTART,               // 03: 局開始
	HAIPAI,                   // 04: 配牌
	PLYACTTSUMOWAIT,          // 05: 自摸牌待ち(他プレーヤの鳴き待ち)
	PLYACTTSUMO,              // 06: 自摸牌受取
	PLYRINSHAN,               // 07: 嶺上牌受取
	PLYACTSUTEWAIT,           // 08: 自摸後の捨牌待ち
	PLYACTNAKISUTEWAIT,       // 09: 鳴後の捨牌待ち
	PLYACTSUTE,               // 10: 捨牌
	PLYACTTSUMOGIRI,          // 11: 自摸切り
	PLYACTNAKISUTE,           // 12: 鳴き捨牌
	PLYACTRIICH,              // 13: リーチ宣言
	PLYRIICHACCEPTED,         // 14: リーチ宣言受け入れ
	PLYTSUMOAGARI,            // 15: 自摸和了
	PLYACTANKAN,              // 16: 暗槓
	PLYACTKAKAN,              // 17: 加槓
	PLYACTNAKIWAIT,           // 18: 鳴き待ち
	PLYACTRON,                // 19: ロン和了
	PLYACTPON,                // 20: ポン
	PLYACTCHI,                // 21: チー
	PLYACTMINKAN,             // 22: 明槓
	PLYACTCHANKAN,            // 23: 槍槓ロン
	TSUMOKANDORAOPEN,         // 24: 自摸時カンドラ表示(暗槓時)
	SUTEKANDORAOPEN,          // 25: 捨牌時カンドラ表示(明槓加槓時)
	RYUKYOKU,                 // 26: 流局
	KYOKURESULT,              // 27: 局結果表示
	KYOKUEND,                 // 28: 局終了
	TAKURESULT,               // 29: 卓結果表示
	TAKUEND,                  // 30: 卓終了
	TAKUERR,                  // 31: 卓エラー状態

} LBTkSt;

// 局終了(流局)ラベル
typedef enum {

	NORKK,                    // 00: 流局設定なし
	HOWANPAI,                 // 01: 荒牌
	SUFURENDA,                // 03: 四風連打
	RIICHI4PLY,               // 03: 四人リーチ
	RON3PLY,                  // 04: 三人ロン
	TEHAI9HAI,                // 05: 九種九牌
	NAGASHIMANGAN,            // 06: 流し満貫
	UNKNOWNRKK,               // 07: その他流局
	AGARIEND,                 // 08: 和了で局が終了

} LBRKStat;

// プレーヤ動作ラベル
typedef enum {

	NOACT = 0,                // 00: アクションなし
	ACTHAIPAI,                // 01: 配牌時
	ACTTSUMO,                 // 02: 自摸牌受取
	ACTRINSHAN,               // 03: 嶺上牌受取
	ACTSUTEWAIT,              // 04: 捨牌待ち
	ACTSUTE,                  // 05: 捨牌
	ACNAKITSUTEWAIT,          // 06: 鳴き捨牌待ち
	ACTNAKISUTE,              // 07: 鳴き捨牌
	ACTTSUMOGIRI,             // 08: 自摸切り
	ACTRIICH,                 // 09: リーチ宣言
	ACTTSUMOAGARI,            // 10: 自摸和了宣言
	ACTNAKIWAIT,              // 11: 鳴き待ち
	ACTNONAKI,                // 12: 鳴きをしない
	ACTRON,                   // 13: ロン和了宣言
	ACTPON,                   // 14: ポン鳴き宣言
	ACTCHI,                   // 15: チー鳴き宣言
	ACTMINKAN,                // 16: 明槓鳴き宣言
	ACTANKAN,                 // 17: 暗槓鳴き宣言
	ACTKAKAN,                 // 18: 加槓鳴き宣言
	ACTCHANKAN,               // 19: 槍槓和了宣言
	ACTTEHAI9HAI,             // 20: 九種九牌宣言

} LBPAct;

// 面子・搭子ラベル
typedef enum {

	// 面子ラベル
	NOMENTSU = 0, // 無し
	SHUNTSU,      // 暗順
	MINSHUN,      // 明順
	ANKO,         // 暗刻
	MINKO,        // 明刻
	ANKAN,        // 暗槓
	MINKAN,       // 明槓
	KAKAN,        // 加槓
	ATAMA,        // 雀頭

	// 塔子ラベル
	RYANMEN,      // 両面
	KANCHAN,      // 嵌張
	PENCHAN,      // 辺張
	TOITSU,       // 対子
	TANKI,        // 単騎

	// 孤立牌(浮き牌)ラベル
	UKIHAI,       // 孤立牌(浮き牌)

} LBMen;

/* ---------------------------------------------------------------------------------------------- */
// ラベル(手牌役)
/* ---------------------------------------------------------------------------------------------- */

// 和了形式
typedef enum {

	NOAGARI_TEHAI = 0,   // 00:和了形式なし
	AGARI_NORMAL,        // 01:通常形式
	AGARI_CHITOI,        // 02:七対形式
	AGARI_KOKUSHI,       // 03:国士形式

} LBAgariTehai;

// チョンボ状態ラベル
typedef enum {

	NOCHBSTAT = 0,       // 00:形式不明
	AGARI_POSSIBLE,      // 01:和了可能
	NOAGARI_CHONBO,      // 02:和了形式でない
	YAKUNASHI,           // 03:役がない
	FURITEN,             // 04:捨牌済の振聴ロン
	DOJUN_FURITEN,       // 05:同順の見逃し振聴ロン
	REACH_FURITEN,       // 06:リーチ後の見逃し振聴ロン
	REACH_NOTEMPAI,      // 07:リーチ時点で聴牌していない

} LBCbSt;

// ノーマル役ラベル
typedef enum {

	// 役なし(デバグ用)
	NOYAKU = 0,          // 00: 役なし

	// リーチ系
	RIICH,               // 01: リーチ
	WRIICH,              // 02: ダブルリーチ
	IPPATSU,             // 03: 一発

	// 六飜
	CHINISO,             // 04: 清一色

	// 三飜
	HONISO,              // 05: 混一色
	JUNCHAN,             // 06: 純全帯
	RYANPEKO,            // 07: 二盃口

	// 二飜
	HONROTO,             // 08: 混老頭
	SHOSANGEN,           // 09: 小三元
	ITSU,                // 10: 一気通貫
	SANDOKOU,            // 11: 三色同刻
	SANDOJUN,            // 12: 三色同順
	SANKANTSU,           // 13: 三槓子
	SANANKO,             // 14: 三暗刻
	TOITOI,              // 15: 対々和
	CHANTA,              // 16: 混全帯
	CHITOI,              // 17: 七対子

	// 一飜
	PINFU,               // 18: 平和
	TANYAO,              // 19: 断公九
	IPEKO,               // 20: 一盃口
	BAKAZE,              // 21: 場風牌
	ZIKAZE,              // 22: 自風牌
	YAKUHAI,             // 23: 三元牌(色指定なしの場合)
	YAKUHAIHAKU,         // 24: 三元牌白
	YAKUHAIHATSU,        // 25: 三元牌発
	YAKUHAICHUN,         // 26: 三元牌中
	HAITEI,              // 27: 海底摸月
	HOUTEI,              // 28: 河底撈魚
	RINSHAN,             // 29: 嶺上開花
	CHANKAN,             // 30: 槍槓
	TSUMO,               // 31: 門前清自摸和

	// ドラ・赤牌
	DORA,                // 32: ドラ(表ドラ)
	URADORA,             // 33: 裏ドラ
	AKAHAI,              // 34: 赤牌

	// 特殊役
	RENHO,               // 35: 人和(満貫)
	NAGASHIMAN,          // 36: 流し満貫

	// 不明役
	UNKNOWN_YAKU,        // 37: 不明の役

	// 予約用
	YAKU_RESERVE1,       // 38: 予約領域1
	YAKU_RESERVE2,       // 39: 予約領域2

} LBYaku;

// 役満ラベル
typedef enum {

	// 役なし(デバグ用)
	NOYAKUMAN = 0,       // 役満00: 役なし
	TENHO,               // 役満01: 天和
	CHIHO,               // 役満02: 地和
	CHUREN9MEN,          // 役満03: 九連九面待ち
	CHUREN,              // 役満04: 九連宝燈
	KOKUSHI13MEN,        // 役満05: 国士13面
	KOKUSHI,             // 役満06: 国士無双
	DAISANGEN,           // 役満07: 大三元
	DAISUSHI,            // 役満08: 大四喜和
	SHOSUSHI,            // 役満09: 小四喜和
	TSUISO,              // 役満10: 字一色
	CHINROTO,            // 役満11: 清老頭
	RYUISO,              // 役満12: 緑一色
	SUKANTSU,            // 役満13: 四槓子
	SUANKOTANKI,         // 役満14: 四暗刻単騎
	SUANKO,              // 役満15: 四暗刻
	RENHOYAKUMAN,        // 役満16: 人和(役満)

	// 不明役
	UNKNOWN_YAKUMAN,     // 役満17: 不明の役満

	// 予約用
	YAKUMAN_RESERVE1,    // 役満18: 予約領域2
	YAKUMAN_RESERVE2,    // 役満19: 予約領域3

} LBYkmn;

#endif /* COMMON_H_INCLUDED */

/* ---------------------------------------------------------------------------------------------- */
// ソース終了
/* ---------------------------------------------------------------------------------------------- */
