/* ---------------------------------------------------------------------------------------------- 
 * 
 * �v���O�����T�v �F �����疃��(Ver0.1.2.1�F�J����)
 * �o�[�W����     �F 0.1.2.1.234(�\���v(open_haiparts)�ꗗ�\��)
 * �v���O������   �F mjs.exe
 * �t�@�C����     �F common.h
 * �N���X��       �F ���ʃw�b�_�[
 * �����T�v       �F ���ʃw�b�_�[
 * Ver0.1.2�쐬�� �F 2023/11/04 09:10:01
 * �ŏI�X�V��     �F 2025/02/01 09:57:37
 * 
 * Copyright (c) 2010-2025 TechMileStoraJP, All rights reserved.
 * 
 * ---------------------------------------------------------------------------------------------- */

#pragma once

#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

/* ---------------------------------------------------------------------------------------------- */
// �Œ�l
/* ---------------------------------------------------------------------------------------------- */

// �o�[�W�������
#define VER1                      0     // 1���ڂ̃o�[�W����(���J����)
#define VER2                      1     // 2���ڂ̃o�[�W����(�\�[�X�S�̂̉��ς��������ꍇ(�ꂩ���蒼�����ꍇ)�A�݊����Ȃ�)
#define VER3                      2     // 3���ڂ̃o�[�W����(�V�@�\�̒ǉ������ꍇ�A���͊����\�[�X����t�H�[�N�����ꍇ�A�݊�������)
#define VER4                      1     // 4���ڂ̃o�[�W����(�G���ȍׂ����X�V���������ꍇ�A�݊�������)
#define VER5                    234     // 5���ڂ̃o�[�W����(�����Ǘ��p�A���J���͏��0�Ƃ���A�݊�������)

// �o�[�W�������(MJSlog)

#define MJSLOG_VER1               0     // 1���ڂ̃o�[�W����(���J����)
#define MJSLOG_VER2               0     // 2���ڂ̃o�[�W����(���O�o�͂̌`����S�̓I�Ɍ��������ꍇ�A�݊����Ȃ�)
#define MJSLOG_VER3               1     // 3���ڂ̃o�[�W����(���O�o�͂̌`�����኱���������ꍇ�A�݊�������)
#define MJSLOG_VER4               3     // 4���ڂ̃o�[�W����(�`����ύX���Ȃ��ׂ��ȍX�V���������ꍇ�A�݊�������)

// �v���[���[���
#define PLAYER_MAX                4     // �v���[����
#define HUM_PLY_SEKI_NUM          3     // Hum�v���[���[�̐Ȕԍ�

// �v���
#define PAI_COUNT_MAX           136     // �v��
#define HAI_POINT_START          66     // �ǊJ�n���_�̔v�|�C���^�ԍ�
#define RINSHAN_POINT_START      10     // �ǊJ�n���_�̔v�|�C���^�ԍ�
#define PAI_MAX                  38     // �v�̎�ސ�
#define COLOR_MAX_COUNT           4     // �ݎq�E���q�E���q�E���v�̎�ʐ�
#define AKA_TYPE_MAX_COUNT        3     // �Ԕv(�ݎq�E���q�E���q)�̎�ʐ�
#define DORA_MAX                  5     // �h���ő吔
#define TEHAI_MAX                13     // ��v�ő吔(���̔v�܂܂�)
#define TSUMOARI_TEHAI_MAX       14     // ��v�ő吔(���̔v�܂�)
#define MEN_MAX                   8     // �ʎq��
#define CHITOI_MEN_MAX            7     // ���Ύq�`���̖ʎq��
#define NORMAL_MACHI_MAX_COUNT   10     // �ʏ���̑Ҕv��
#define KAWA_HAI_MAX             25     // �̔v��(�͔v�̍ő吔)
#define SUTEHAI_MAX_COUNT        14     // �̔v���̍ő吔
#define NAKI_KOHO_MAX_COUNT      20     // �����̍ő吔
#define CHI_KOHO_COUNT_MAX        6     // �`�[���̍ő吔

// �Ǐ��
#define KYOKU_MAX                64     // �����ł̍ő�ǐ�
#define ACTID_MAX               200     // ACT_ID�ő�
#define INITSCORE             25000     // �������_
// #define INITSCORE          27000     // �������_

// �����
#define YAKU_SHUBETSU_MAX        40     // �ʏ���̍ő吔
#define YAKUMAN_SHUBETSU_MAX     20     // �𖞂̍ő吔
#define RYUKYOKU_SHUBETSU_MAX    10     // ���ǎ�ʂ̍ő吔
#define NORMALYAKU_MAX           12     // �ʏ���̍ő吔

// ��������
#define EXCEPT_VALUE            999     // ��Ɨp�̗�O�l

// ���[�h��`
#define SEED_NUM           26234098     // �����V�[�h�ԍ�

/* ---------------------------------------------------------------------------------------------- */
// �Œ�l(�̔v�̏��)
/* ---------------------------------------------------------------------------------------------- */

#define HAI_COLOR_NUM_NOCOLOR     0     // �u���F�v�̔ԍ��F�ʏ�v�̕\��
#define HAI_COLOR_NUM_GRAY        1     // �u�D�F�v�̔ԍ��F���ꂽ�ꍇ
#define HAI_COLOR_NUM_BLUE        2     // �u�F�v�̔ԍ��F�����s�m�F�E�a���v�\��
#define HAI_COLOR_NUM_YELLOW      3     // �u���F�v�̔ԍ��F�h���v�ł���ꍇ
#define HAI_COLOR_NUM_GREEN       4     // �u�ΐF�v�̔ԍ��F�����\��
#define RIICHI_STAT_NUM           5     // ���[�`���

/* ---------------------------------------------------------------------------------------------- 
 * �Œ�l(�v�ԍ�)
 * ---------------------------------------------------------------------------------------------- */

#define HAIZERONUM    0   //  �v�ԍ�0

#define MAN1NUM       1   // �u�ݎq1�v�v�ԍ�
#define MAN2NUM       2   // �u�ݎq2�v�v�ԍ�
#define MAN3NUM       3   // �u�ݎq3�v�v�ԍ�
#define MAN4NUM       4   // �u�ݎq4�v�v�ԍ�
#define MAN5NUM       5   // �u�ݎq5�v�v�ԍ�
#define MAN6NUM       6   // �u�ݎq6�v�v�ԍ�
#define MAN7NUM       7   // �u�ݎq7�v�v�ԍ�
#define MAN8NUM       8   // �u�ݎq8�v�v�ԍ�
#define MAN9NUM       9   // �u�ݎq9�v�v�ԍ�

#define PIN1NUM      11   // �u���q1�v�v�ԍ�
#define PIN2NUM      12   // �u���q2�v�v�ԍ�
#define PIN3NUM      13   // �u���q3�v�v�ԍ�
#define PIN4NUM      14   // �u���q4�v�v�ԍ�
#define PIN5NUM      15   // �u���q5�v�v�ԍ�
#define PIN6NUM      16   // �u���q6�v�v�ԍ�
#define PIN7NUM      17   // �u���q7�v�v�ԍ�
#define PIN8NUM      18   // �u���q8�v�v�ԍ�
#define PIN9NUM      19   // �u���q9�v�v�ԍ�

#define SOU1NUM      21   // �u���q1�v�v�ԍ�
#define SOU2NUM      22   // �u���q2�v�v�ԍ�
#define SOU3NUM      23   // �u���q3�v�v�ԍ�
#define SOU4NUM      24   // �u���q4�v�v�ԍ�
#define SOU5NUM      25   // �u���q5�v�v�ԍ�
#define SOU6NUM      26   // �u���q6�v�v�ԍ�
#define SOU7NUM      27   // �u���q7�v�v�ԍ�
#define SOU8NUM      28   // �u���q8�v�v�ԍ�
#define SOU9NUM      29   // �u���q9�v�v�ԍ�

#define TONNUM       31   // �u���v�v�ԍ�
#define NANNUM       32   // �u��v�v�ԍ�
#define SHANUM       33   // �u���v�v�ԍ�
#define PEINUM       34   // �u�k�v�v�ԍ�

#define HAKUNUM      35   // �u���v�v�ԍ�
#define HATSUNUM     36   // �u���v�v�ԍ�
#define CHUNNUM      37   // �u���v�v�ԍ�

#define UNKNOWNNUM   38   // �u�H�v�v�ԍ�

/* ---------------------------------------------------------------------------------------------- */
// ���x��(����)
/* ---------------------------------------------------------------------------------------------- */

// ��Q�[�����
typedef enum {

	NO_TKGAME_TYPE = 0,       // 00: ��Q�[����ʂȂ�
	TKGAME_HANCHAN,           // 01: ������v���C
	TKGAME_TONPU,             // 02: ������v���C
	TKGAME_1KYOKU,            // 03: ��ǐ�v���C
	TKGAME_MAXID_TEST,        // 04: ��ID�ő�v���C
	TKGAME_MJAI,              // 05: MJAI�N���C�A���g���[�h
	TKGAME_VIEWER,            // 06: �r���[�A���[�h(������)
	TKGAME_VIEWER_HANCHAN,    // 07: �r���[�A���[�h(������)

} LBTkGmTYPE;

// ���ԃ��x��
typedef enum {

	PLYNOACT = 0,             // 00: ���Ԃ̒�`�Ȃ�
	TAKUSTART,                // 01: ��J�n
	BAGIME,                   // 02: �ꌈ��
	KYOKUSTART,               // 03: �ǊJ�n
	HAIPAI,                   // 04: �z�v
	PLYACTTSUMOWAIT,          // 05: ���̔v�҂�(���v���[���̖��҂�)
	PLYACTTSUMO,              // 06: ���̔v���
	PLYRINSHAN,               // 07: ���v���
	PLYACTSUTEWAIT,           // 08: ���̌�̎̔v�҂�
	PLYACTNAKISUTEWAIT,       // 09: ��̎̔v�҂�
	PLYACTSUTE,               // 10: �̔v
	PLYACTTSUMOGIRI,          // 11: ���̐؂�
	PLYACTNAKISUTE,           // 12: ���̔v
	PLYACTRIICH,              // 13: ���[�`�錾
	PLYRIICHACCEPTED,         // 14: ���[�`�錾�󂯓���
	PLYTSUMOAGARI,            // 15: ���̘a��
	PLYACTANKAN,              // 16: �Þ�
	PLYACTKAKAN,              // 17: ����
	PLYACTNAKIWAIT,           // 18: ���҂�
	PLYACTRON,                // 19: �����a��
	PLYACTPON,                // 20: �|��
	PLYACTCHI,                // 21: �`�[
	PLYACTMINKAN,             // 22: ����
	PLYACTCHANKAN,            // 23: ���ȃ���
	TSUMOKANDORAOPEN,         // 24: ���̎��J���h���\��(�ÞȎ�)
	SUTEKANDORAOPEN,          // 25: �̔v���J���h���\��(���ȉ��Ȏ�)
	RYUKYOKU,                 // 26: ����
	KYOKURESULT,              // 27: �ǌ��ʕ\��
	KYOKUEND,                 // 28: �ǏI��
	TAKURESULT,               // 29: �쌋�ʕ\��
	TAKUEND,                  // 30: ��I��
	TAKUERR,                  // 31: ��G���[���

} LBTkSt;

// �ǏI��(����)���x��
typedef enum {

	NORKK,                    // 00: ���ǐݒ�Ȃ�
	HOWANPAI,                 // 01: �r�v
	SUFURENDA,                // 03: �l���A��
	RIICHI4PLY,               // 03: �l�l���[�`
	RON3PLY,                  // 04: �O�l����
	TEHAI9HAI,                // 05: ����v
	NAGASHIMANGAN,            // 06: ��������
	UNKNOWNRKK,               // 07: ���̑�����
	AGARIEND,                 // 08: �a���ŋǂ��I��

} LBRKStat;

// �v���[�����색�x��
typedef enum {

	NOACT = 0,                // 00: �A�N�V�����Ȃ�
	ACTHAIPAI,                // 01: �z�v��
	ACTTSUMO,                 // 02: ���̔v���
	ACTRINSHAN,               // 03: ���v���
	ACTSUTEWAIT,              // 04: �̔v�҂�
	ACTSUTE,                  // 05: �̔v
	ACNAKITSUTEWAIT,          // 06: ���̔v�҂�
	ACTNAKISUTE,              // 07: ���̔v
	ACTTSUMOGIRI,             // 08: ���̐؂�
	ACTRIICH,                 // 09: ���[�`�錾
	ACTTSUMOAGARI,            // 10: ���̘a���錾
	ACTNAKIWAIT,              // 11: ���҂�
	ACTNONAKI,                // 12: �������Ȃ�
	ACTRON,                   // 13: �����a���錾
	ACTPON,                   // 14: �|�����錾
	ACTCHI,                   // 15: �`�[���錾
	ACTMINKAN,                // 16: ���Ȗ��錾
	ACTANKAN,                 // 17: �ÞȖ��錾
	ACTKAKAN,                 // 18: ���Ȗ��錾
	ACTCHANKAN,               // 19: ���Șa���錾
	ACTTEHAI9HAI,             // 20: ����v�錾

} LBPAct;

// �ʎq�E���q���x��
typedef enum {

	// �ʎq���x��
	NOMENTSU = 0, // ����
	SHUNTSU,      // �Ï�
	MINSHUN,      // ����
	ANKO,         // �Í�
	MINKO,        // ����
	ANKAN,        // �Þ�
	MINKAN,       // ����
	KAKAN,        // ����
	ATAMA,        // ����

	// ���q���x��
	RYANMEN,      // ����
	KANCHAN,      // �ƒ�
	PENCHAN,      // �Ӓ�
	TOITSU,       // �Ύq
	TANKI,        // �P�R

	// �Ǘ��v(�����v)���x��
	UKIHAI,       // �Ǘ��v(�����v)

} LBMen;

/* ---------------------------------------------------------------------------------------------- */
// ���x��(��v��)
/* ---------------------------------------------------------------------------------------------- */

// �a���`��
typedef enum {

	NOAGARI_TEHAI = 0,   // 00:�a���`���Ȃ�
	AGARI_NORMAL,        // 01:�ʏ�`��
	AGARI_CHITOI,        // 02:���Ό`��
	AGARI_KOKUSHI,       // 03:���m�`��

} LBAgariTehai;

// �`�����{��ԃ��x��
typedef enum {

	NOCHBSTAT = 0,       // 00:�`���s��
	AGARI_POSSIBLE,      // 01:�a���\
	NOAGARI_CHONBO,      // 02:�a���`���łȂ�
	YAKUNASHI,           // 03:�����Ȃ�
	FURITEN,             // 04:�̔v�ς̐U������
	DOJUN_FURITEN,       // 05:�����̌������U������
	REACH_FURITEN,       // 06:���[�`��̌������U������
	REACH_NOTEMPAI,      // 07:���[�`���_�Œ��v���Ă��Ȃ�

} LBCbSt;

// �m�[�}�������x��
typedef enum {

	// ���Ȃ�(�f�o�O�p)
	NOYAKU = 0,          // 00: ���Ȃ�

	// ���[�`�n
	RIICH,               // 01: ���[�`
	WRIICH,              // 02: �_�u�����[�`
	IPPATSU,             // 03: �ꔭ

	// �Z��
	CHINISO,             // 04: ����F

	// �O��
	HONISO,              // 05: ����F
	JUNCHAN,             // 06: ���S��
	RYANPEKO,            // 07: ��u��

	// ����
	HONROTO,             // 08: ���V��
	SHOSANGEN,           // 09: ���O��
	ITSU,                // 10: ��C�ʊ�
	SANDOKOU,            // 11: �O�F����
	SANDOJUN,            // 12: �O�F����
	SANKANTSU,           // 13: �O�Ȏq
	SANANKO,             // 14: �O�Í�
	TOITOI,              // 15: �΁X�a
	CHANTA,              // 16: ���S��
	CHITOI,              // 17: ���Ύq

	// ����
	PINFU,               // 18: ���a
	TANYAO,              // 19: �f����
	IPEKO,               // 20: ��u��
	BAKAZE,              // 21: �ꕗ�v
	ZIKAZE,              // 22: �����v
	YAKUHAI,             // 23: �O���v(�F�w��Ȃ��̏ꍇ)
	YAKUHAIHAKU,         // 24: �O���v��
	YAKUHAIHATSU,        // 25: �O���v��
	YAKUHAICHUN,         // 26: �O���v��
	HAITEI,              // 27: �C��̌�
	HOUTEI,              // 28: �͒ꝝ��
	RINSHAN,             // 29: ���J��
	CHANKAN,             // 30: ����
	TSUMO,               // 31: ��O�����̘a

	// �h���E�Ԕv
	DORA,                // 32: �h��(�\�h��)
	URADORA,             // 33: ���h��
	AKAHAI,              // 34: �Ԕv

	// �����
	RENHO,               // 35: �l�a(����)
	NAGASHIMAN,          // 36: ��������

	// �s����
	UNKNOWN_YAKU,        // 37: �s���̖�

	// �\��p
	YAKU_RESERVE1,       // 38: �\��̈�1
	YAKU_RESERVE2,       // 39: �\��̈�2

} LBYaku;

// �𖞃��x��
typedef enum {

	// ���Ȃ�(�f�o�O�p)
	NOYAKUMAN = 0,       // ��00: ���Ȃ�
	TENHO,               // ��01: �V�a
	CHIHO,               // ��02: �n�a
	CHUREN9MEN,          // ��03: ��A��ʑ҂�
	CHUREN,              // ��04: ��A��
	KOKUSHI13MEN,        // ��05: ���m13��
	KOKUSHI,             // ��06: ���m���o
	DAISANGEN,           // ��07: ��O��
	DAISUSHI,            // ��08: ��l��a
	SHOSUSHI,            // ��09: ���l��a
	TSUISO,              // ��10: ����F
	CHINROTO,            // ��11: ���V��
	RYUISO,              // ��12: �Έ�F
	SUKANTSU,            // ��13: �l�Ȏq
	SUANKOTANKI,         // ��14: �l�Í��P�R
	SUANKO,              // ��15: �l�Í�
	RENHOYAKUMAN,        // ��16: �l�a(��)

	// �s����
	UNKNOWN_YAKUMAN,     // ��17: �s���̖�

	// �\��p
	YAKUMAN_RESERVE1,    // ��18: �\��̈�2
	YAKUMAN_RESERVE2,    // ��19: �\��̈�3

} LBYkmn;

#endif /* COMMON_H_INCLUDED */

/* ---------------------------------------------------------------------------------------------- */
// �\�[�X�I��
/* ---------------------------------------------------------------------------------------------- */
