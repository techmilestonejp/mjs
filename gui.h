/* ---------------------------------------------------------------------------------------------- 
 * 
 * �v���O�����T�v �F �����疃��(Ver0.1.2�F�J����)
 * �o�[�W����     �F 0.1.2.0.219(MJAI���O�\���F���h�����ʕ\��)
 * �v���O������   �F mjs.exe
 * �t�@�C����     �F gui.h
 * �N���X��       �F MJSGui
 * �����T�v       �F GUI����N���X
 * Ver0.1.0�쐬�� �F 2022/05/03 18:50:06
 * �ŏI�X�V��     �F 2024/10/30 09:26:27
 * 
 * Copyright (c) 2010-2024 Techmilestone, All rights reserved.
 * 
 * ---------------------------------------------------------------------------------------------- */

#include "stdafx.h"
#include "DxLib.h"
#include "tkinfo.h"

#ifndef MJSMOUSE_H_INCLUDED
#define MJSMOUSE_H_INCLUDED

/* ---------------------------------------------------------------------------------------------- */
// �Œ�l(�摜�֘A)
/* ---------------------------------------------------------------------------------------------- */

// �\���`��
#define DISP_TEHAI_MODE_DEF             1    // �f�t�H���g�̎�v�\�����[�h(0:���C�i�[�\���A1:�X�N�G�A�\���A2:�e�X�g�\��)
#define DISP_SQUARE_NAKI_MENTSU_DEF     0    // �͂݃��[�h�ł̖��ʎq�\���`��(0:���C�i�[�\���A1:�c�\��)
#define DISP_DEBUG_INFO                 0    // �f�o�O���̕\��(0:��\��)

// �t���[���J�E���g
#define AUTO_FRAME_COUNT_PLAYING       20    // �v���C���[�h�̃t���[���J�E���g��
#define AUTO_FRAME_COUNT_RUNNING        1    // ���؃��[�h�̃t���[���J�E���g��
#define AUTO_FRAME_COUNT_CLIENT         5    // �N���C�A���g���[�h�̃t���[���J�E���g��
#define AUTO_FRAME_COUNT_CLIENT_SND     5    // ���M���E�G�C�g�p�̃t���[���J�E���g��
#define AUTO_FRAME_COUNT_AUTO_TSUMO    20    // ���[�`���̃I�[�g���̂̃t���[���J�E���g��
#define AUTO_FRAME_COUNT_RESULT       150    // ���ʕ\�����̃E�F�C�g�p�t���[���J�E���g��

/* ---------------------------------------------------------------------------------------------- */
// �Œ�l(���O�ݒ�)
/* ---------------------------------------------------------------------------------------------- */

// �r���[�A�[���[�h
#define MJSCORE_LOG_OUTPUT_MODE         0    // ���O�o�̓��[�h

// ���O�t���p�X���̍ő�T�C�Y
#define FULLPATH_LOGNAME_SIZE         256    // �t�@�C�����ő�T�C�Y

/* ---------------------------------------------------------------------------------------------- */
// �Œ�l(GUI�N���X��`�p)
/* ---------------------------------------------------------------------------------------------- */

#define PLT_COUNT_MAX    10   // �v���[�g����
#define PLTLINE_COUNT     6   // �v���[�g���C���̐�
#define PLTSTATNUM_NEXT   6   // �u���ցv�v���[�g�̈ʒu�ԍ�

/* ---------------------------------------------------------------------------------------------- */
// �Œ�l(��p�[�c�T�C�Y)
/* ---------------------------------------------------------------------------------------------- */

// �v�T�C�Y
#define HAI_XSIZE        24
#define HAI_YSIZE        32

// ���v�T�C�Y
#define LHAI_XSIZE       32
#define LHAI_YSIZE       24

// �v���[�g�T�C�Y
#define PLT_ICON_XSIZE   80
#define PLT_ICON_YSIZE   30

// �{�^���T�C�Y
#define BUT_ICON_XSIZE   32
#define BUT_ICON_YSIZE   32

/* ---------------------------------------------------------------------------------------------- */
// �Œ�l(�摜�ʒu)
/* ---------------------------------------------------------------------------------------------- */

// �I�[�v�j���O�\���ʒu
#define OPENING_BUT01_X_START     160   // �Z���N�g�{�^����X���J�n�ʒu
#define OPENING_BUT01_Y_START     240   // �Z���N�g�{�^����Y���J�n�ʒu
#define OPENING_BUT01_Y_RANGE      40   // �Z���N�g�{�^����Y����

// �ݒ胂�[�h�̕\���ʒu
#define SETTING_X_START            80   // �ݒ胂�[�h��X���J�n�ʒu
#define SETTING_Y_START           160   // �ݒ胂�[�h��Y���J�n�ʒu
#define SETTING_Y_RANGE            64   // �ݒ胂�[�h��Y����
#define SETTING_ENDBUT_Y_START    600   // �I���{�^����Y����

// ��Q�[�����[�h�̕\���ʒu(�S��)
#define STRING_YSIZE               16   // �����T�C�Y
#define SPACE_XSIZE                 4   // X���̌��ԃT�C�Y
#define SPACE_YSIZE                 4   // Y���̌��ԃT�C�Y

// ���ʃp�[�c�̕\���ʒu
#define GAMESTAT_X_STAT           770   // �Q�[���X�e�[�^�X��X�ʒu
#define GAMESTAT_Y_STAT            50   // �Q�[���X�e�[�^�X��Y�ʒu

// ��Q�[�����[�h�̕\���ʒu(�v���[���[���)
#define PLY_YSTART                 90   // �v���[���[����Y�J�n�ʒu
#define PLY_YSIZE                  90   // �v���[���[���Ƃ�Y�T�C�Y�̃����W

// ��Q�[�����[�h�̕\���ʒu(�v�\��)
#define DORA_XSIZE                450   // �h���v�̈ʒu
#define URADORA_XSIZE_RANGE       125   // ���h���v�̍����ʒu

// ��Q�[�����[�h�̕\���ʒu(��v�֘A)
#define NAKI_X_START              600   // ���v��X���J�n�ʒu
#define NAKI_MENTSU_XSIZE         150   // ���ʎq�̕��T�C�Y

// ��Q�[�����[�h�̕\���ʒu(��v�֘A�E�͂݃��[�h)
#define LINE_SUTEHAI_COUNT_MAX      6   // 1�s������̎̔v��

#define TAKU_PLT_X_SIZE           696   // ��v���[�g_X�T�C�Y
#define TAKU_PLT_Y_SIZE           696   // ��v���[�g_Y�T�C�Y
#define TAKU_PLT_X_STAT            64   // ��v���[�g_X�J�n�ʒu
#define TAKU_PLT_Y_STAT            64   // ��v���[�g_Y�J�n�ʒu

#define SUTEHAI_CENTERPLT_RANGE     8   // �̔v�����W
#define SUTEHAI_TEHAI_RANGE        64   // ��v�����W
#define NAME_TEHAI_RANGE            8   // ���O�����W
#define NAKI_RANGE                384   // ���v�����W
#define NAKI_MENTSU_RANGE         104   // ���v���Ƃ̃����W

// ��Q�[�����[�h�̕\���ʒu(�v���[�g�֘A)
#define PLT_Y_STAT                700   // �v���[�g��Y�ʒu
#define PLT_NAKIARI_X_STAT        550   // �v���[�g���L����X�ʒu

// ��Q�[�����[�h�̕\���ʒu(���b�Z�[�W�֘A)
#define PLY_MES_X_STAT            720   // ���b�Z�[�W��X�ʒu
#define PLY_MES_Y_STAT            688   // ���b�Z�[�W��Y�ʒu

// ��Q�[�����[�h�̕\���ʒu(�r���[�A�{�^��)
#define ACTID_Y_STAT              504   // �{�^����Y�ʒu(�r���[�A�@�\�{�^��)
#define KYOID_X_STAT              720   // �{�^��02��X�ʒu(�r���[�A���[�h�F��ID�ύX)
#define ACTID_X_STAT              800   // �{�^��03��X�ʒu(�r���[�A���[�h�FActID�ύX)

#define BAGIME_Y_STAT             544   // �{�^����Y�ʒu(�r���[�A�@�\�{�^��)
#define BAGIME_X_STAT             720   // �{�^��01��X�ʒu(�ꌈ�ߕ\��)
#define TKEND_X_STAT              760   // �{�^��04��X�ʒu(�ǌ��ʕ\��)

#define VIEWER_SEKI_Y_STAT        584   // �r���[�A���[�h�F�ȕύX_Y�ʒu
#define VIEWER_SEKI_X_STAT        720   // �r���[�A���[�h�F�ȕύX_X�ʒu

// ��Q�[�����[�h�̕\���ʒu(��񑀍�{�^��)
#define BUT02_Y_STAT              640   // �{�^����Y�ʒu(����{�^��)
#define THINFO_BUT_X_STAT         720   // ��v�ڍ׏��{�^����X�ʒu
#define TKINFO_BUT_X_STAT         760   // TK�N���X���{�^����X�ʒu(�f�o�O�p)
#define PLYINFO_BUT_X_STAT        800   // PLY���{�^����X�ʒu
#define QUIT_BUT_X_STAT           840   // �I���{�^����X�ʒu

// ��Q�[�����[�h�̕\���ʒu(���\��)
#define DEBUG_INFO_Y_STAT         550   // �f�o�O����Y�ʒu
#define GUI_INFO_Y_STAT           715   // GUI����Y�ʒu
#define TKINFO_X1                 145   // ����_1��X�ʒu
#define TKINFO_X2                 275   // ����_2��X�ʒu

// ��Q�[�����[�h�̕\���ʒu(�ꌈ��)
#define BAGIME_X_START             50   // �ꌈ��_X�J�n�ʒu
#define BAGIME_Y_START            150   // �ꌈ��_Y�J�n�ʒu

// ��Q�[�����[�h�̕\���ʒu(�a������)
#define AGARI_INFO_X1             250         // �a�����_1��X�ʒu
#define AGARI_INFO_X1_1           350         // �a�����_1(�T�u1)��X�ʒu
#define AGARI_INFO_X1_2           390         // �a�����_1(�T�u2)��X�ʒu
#define AGARI_INFO_X2             450         // �a�����_2��X�ʒu
#define AGARI_INFO_X3             620         // �a�����_3��X�ʒu
#define AGARI_INFO_X4             670         // �a�����_4��X�ʒu

// ��Q�[�����[�h�̕\���ʒu(�쌋��)
#define GAMERESULT_X_START         50   // �쌋��_X�J�n�ʒu
#define GAMERESULT_Y_START        150   // �쌋��_Y�J�n�ʒu

/* ---------------------------------------------------------------------------------------------- */
// ���x��(�e���[�h)
/* ---------------------------------------------------------------------------------------------- */

// GUI���C���X�e�[�^�X
typedef enum {

	GUI_NO_MAIN_STAT = 0,     // �������Ă��Ȃ�

	GUI_OPENING_INIT,         // �^�C�g�����
	GUI_OPENING,
	GUI_OPENING_POST,

	GUI_PLAYING_INIT,         // ��Q�[���v���C���[�h
	GUI_PLAYING,
	GUI_PLAYING_POST,

	GUI_VIEWING_INIT,         // �r���[�A�[���[�h
	GUI_VIEWING,
	GUI_VIEWING_POST,

	GUI_RUNNING_INIT,         // ���؃��[�h
	GUI_RUNNING,
	GUI_RUNNING_POST,

	GUI_CLIENT_INIT,          // MJAI�N���C�A���g���[�h
	GUI_CLIENT,
	GUI_CLIENT_POST,

	GUI_MJAISERVER_INIT,      // MJAI�T�[�o���[�h
	GUI_MJAISERVER,
	GUI_MJAISERVER_POST,

	GUI_SETTING_INIT,         // �ݒ���
	GUI_SETTING,
	GUI_SETTING_POST,

	GUI_DEMO_INIT,            // �f�����
	GUI_DEMO,
	GUI_DEMO_POST,

} LBGuiGmSt;

// GUI��Q�[���\�����[�h
typedef enum {

	COMMON_NO_MODE = 0,                 // 00:��ԂȂ�
	COMMON_BAGIME_MODE,                 // 01:��Q�[���J�n(�ꌈ�ߕ\��)
	COMMON_PLAY_MODE,                   // 02:�ʏ��v�\��
	COMMON_KYOKURESULT_MODE,            // 03:�ǌ��ʕ\��
	COMMON_TAKURESULT_MODE,             // 04:��Q�[�����ʕ\��(�쌋�ʕ\��)
	COMMON_TEHAI_DETAIL_MODE,           // 05:��v�ڍ׃��[�h
	COMMON_TKINFO_MODE,                 // 06:TK�N���X���\�����[�h
	GAME_PLY_INFO_MODE,                 // 07:�v���[�����W���[��(ply�N���X)�\��
	COMMON_END_CHECK_MODE,              // 08:�I���m�F���[�h
	COMMON_END_MODE,                    // 09:�I�����[�h
	SETTING_DETAIL_MODE,                // 10:�ݒ���\��

} LBGuiTakuMode;

// GUI��v���[�h
typedef enum {

	TEHAI_NO_MODE = 0,                  // 00:��ԂȂ�
	TEHAI_NORMAL,                       // 01:�ʏ���
	TEHAI_RIICHI_SUTEHAI,               // 03:���[�`���̎̔v�I��
	TEHAI_RIICHI_YUKO,                  // 04:���[�`�L�����
	TEHAI_ANKAN_KAKAN_SELECT,           // 05:�ÞȁE���ȑI��(�ÞȁE���Ȃ͓���)
	TEHAI_CHI_SELECT,                   // 06:�`�[�I��
	TEHAI_KUIKAE_NAKISUTE,              // 07:�򂢊�����Ԃ̖��̔v

} LBGuiTehaiMode;

// GUI_MJAI�N���C�A���g���[�h
typedef enum {

	GUI_MJAI_CLIENT_NO_MODE = 0,        // 00:��ԂȂ�
	GUI_MJAI_NOTCONNECT,                // 01:�ڑ��O�҂�
	GUI_MJAI_CONNECT_ACTION,            // 02:�ڑ�����
	GUI_MJAI_CHECK_DISCONNECT,          // 03:�ؒf�m�F
	GUI_MJAI_DISCONNECT,                // 04:�ؒf����
	GUI_MJAI_ERR_CONNECT,               // 05:Socket�ڑ����G���[
	GUI_MJAI_WAIT_HELO_RESMES,          // 06:HELLO���N�G�X�g�҂�
	GUI_MJAI_WAIT_TAKU_START_RESMES,    // 07:��J�n�҂�
	GUI_MJAI_BAGIME,                    // 08:�ꌈ��
	GUI_MJAI_WAIT_KYOKU_START_RESMES,   // 09:�ǊJ�n�҂�
	GUI_MJAI_HAIPAI,                    // 10:�z�v�\��
	GUI_MJAI_WAIT_TAKU_RESMES,          // 11:�샂�[�h�F��M���b�Z�[�W�҂�
	GUI_MJAI_WAIT_TAKU_PLYACT,          // 12:�샂�[�h�F�v���[���[�A�N�V�����҂�
	GUI_MJAI_WAIT_SED_MES,              // 13:�샂�[�h�F���b�Z�[�W���M�̏����҂�����
	GUI_MJAI_ERR_RES_MES,               // 14:�샂�[�h�F�G���[���b�Z�[�W��M�����
	GUI_MJAI_KYOKUEND,                  // 15:�ǌ��ʁF�ǏI������
	GUI_MJAI_KYOKUEND_SED_MES,          // 16:�ǌ��ʁF�ǏI�����̊m�F���b�Z�[�W���M�̑҂�����
	GUI_MJAI_TAKURESULT,                // 17:�쌋�ʁF�쌋�ʏ���
	GUI_MJAI_END_MODE,                  // 18:�I�����[�h

} LBGuiMjaiClientMode;

// GUI�ݒ胂�[�h
typedef enum {

	SETTING_NO_MODE = 0,                // 00:��ԂȂ�
	SETTING_INFO_MODE,                  // 01:�p�����[�^�ꗗ
	SETTING_FILENAME_MJAI_MODE,         // 02:�t�@�C�����擾(MJAI)
	SETTING_FILENAME_MJSCORE_MODE,      // 03:�t�@�C�����擾(mjscore)

} LBGuiSettingMode;

// �Ǎ��ݔv�����O���
typedef enum {

	GUI_LOG_NOTYPE  = 0,                // 00:��ԂȂ�
	GUI_LOG_MJAILOG,                    // 01:MJAI���O
	GUI_LOG_MJSCORE,                    // 02:���������O

} LBGuiLogType;

/* ---------------------------------------------------------------------------------------------- */
// ���x��(GUI����)
/* ---------------------------------------------------------------------------------------------- */

// �v���[�g���x��
typedef enum {

	// �ʏ�\��
	PLT_RIICHI = 0,      // 00:�v���[�g�E���[�`
	PLT_PON,             // 01:�v���[�g�E�|��
	PLT_KAN,             // 02:�v���[�g�E�J��
	PLT_CHI,             // 03:�v���[�g�E�`�[
	PLT_AGARI,           // 04:�v���[�g�E�a��
	PLT_NEXT,            // 05:�v���[�g�E����

	// �L/��
	PLT_NAKIARI,         // 06:�v���[�g�E�L
	PLT_NAKINASHI,       // 07:�v���[�g�E��

	// YES/NO����
	PLT_YES,             // 08:�v���[�g�E�͂�
	PLT_NO,              // 09:�v���[�g�E������

} LBPlt;

/* ---------------------------------------------------------------------------------------------- */
// �N���X��`
/* ---------------------------------------------------------------------------------------------- */
class MJSGui
{

	/* ----------------------------- */
	// ���J�֐���`
	/* ----------------------------- */
	public:

	// -----------------------------
	// �}�E�X�p
	// -----------------------------
	int msx;                                 // �}�E�X��X���W
	int msy;                                 // �}�E�X��Y���W
	int wheelrotvol;                         // �z�C�[���̉�]��
	unsigned int Button[8];                  // �{�^���̉��������

	// -----------------------------
	// �}�E�X�����֘A�̃t���O
	// -----------------------------
	int mouse_push_flg;                      // bool�^�ɕύX�\��
	// bool mouse_push_flg  
	bool act_push_flg;                       // �L���ӏ������������ꍇ�̃}�E�X�����t���O                         
	bool but_push_flg;                       // �{�^�������t���O

	// -----------------------------
	// �t���[���J�E���g
	// -----------------------------
	int frame_count;                         // �t���[���J�E���g
	int total_frame_count;                   // ���v�t���[���J�E���g

	// -----------------------------
	// ��v�\�����[�h
	// -----------------------------

	// ��v�\�����[�h
	int disp_tehai_mode;                     // �f�t�H���g�̎�v�\�����[�h(0:���C�i�[�\���A1:�X�N�G�A�\���A2:�e�X�g�\��)
	int disp_square_naki_mentsu;             // �f�t�H���g�̖��ʎq�̕\�����[�h

	// ���C���E�X�N�G�A����
	int tehai_x;                             // ��v��X���W
	int tehai_y;                             // ��v��Y���W

	// �X�N�G�A�p�̔v�ʒu
	int sutehai_up_x;
	int sutehai_up_y;
	int sutehai_down_x;
	int sutehai_down_y;
	int sutehai_left_x;
	int sutehai_left_y;
	int sutehai_right_x;
	int sutehai_right_y;

	// �X�N�G�A�p��v�ʒu
	int tehai_up_x;
	int tehai_up_y;
	int tehai_left_x;
	int tehai_left_y;
	int tehai_right_x;
	int tehai_right_y;

	// �v_����
	int nakihai_line_up_x;
	int nakihai_line_up_y;
	int nakihai_line_down_x;
	int nakihai_line_down_y;
	int nakihai_line_left_x;
	int nakihai_line_left_y;
	int nakihai_line_right_x;
	int nakihai_line_right_y;

	// �v_�c��
	int nakihai_up_x;
	int nakihai_up_y;
	int nakihai_down_x;
	int nakihai_down_y;
	int nakihai_left_x;
	int nakihai_left_y;
	int nakihai_right_x;
	int nakihai_right_y;

	// -----------------------------
	// �v���[�g
	// -----------------------------
	bool plt_mode[PLT_COUNT_MAX];                 // �v���[�g�\���L��
	char plt_name[PLT_COUNT_MAX][20];             // �v���[�g�\����
	bool plt_nakiari_flg;                         // �L/���t���O

	// -----------------------------
	// �\�����[�h���Ƃ�GUI���(���C������)
	// -----------------------------

	// GUI���C���X�e�[�^�X
	LBGuiGmSt gui_main_stat;                      // ���C���X�e�[�^�X�̒l
	LBGuiGmSt gui_next_stat;                      // �uPOST�����v��Ƀ��C���X�e�[�^�X�̒l

	// -----------------------------
	// �\�����[�h���Ƃ�GUI���(��Q�[�����[�h)
	// -----------------------------

	// GUI���[�h(��\��)
	LBGuiTakuMode  gui_taku_mode;                 // ��\�����[�h
	LBGuiTehaiMode gui_ply_tehai_mode;            // ��v�\�����[�h(��v�E�����)

	// �샍�O�o��
	bool tklog_output_flg;                        // �샍�O�̏o�͗L��
	char tklog_name[FULLPATH_LOGNAME_SIZE];       // �샍�O�E�t�@�C����(�t���p�X)

	// -----------------------------
	// ����ʗp
	// -----------------------------

	// �����(�ÞȊ֘A)
	int naki_ankan_hai_count;                     // �ÞȔv����
	int naki_ankan_hai[4];                        // �ÞȂ̔v�ԍ�

	// �����(���Ȋ֘A)
	int naki_kakan_hai_count;                     // ���Ȕv����
	int naki_kakan_hai[4];                        // ���Ȃ̔v�ԍ�

	// �����(�`�[�֘A)
	int  chihai_count;                            // �`�[�v����
	bool chihai_mode[CHI_KOHO_COUNT_MAX];         // �`�[�v�̗L����
	int  chi_idx_hai[CHI_KOHO_COUNT_MAX];         // �`�[�v�擪�̔v�ԍ�
	int  chi_aka_count[CHI_KOHO_COUNT_MAX];       // �`�[�̐Ԕv����
	int  chi_hai_num1[CHI_KOHO_COUNT_MAX];        // �`�[���s����v1���ڂ̔v�ԍ�
	int  chi_hai_num2[CHI_KOHO_COUNT_MAX];        // �`�[���s����v2���ڂ̔v�ԍ�

	// �̔v�s�e�[�u��
	int  cannot_sutehai_count;                    // �̔v�s�v�̖���
	int  cannot_sutehai[14];                      // �̔v�s�e�[�u��

	// -----------------------------
	// �\�����[�h���Ƃ�GUI���(�N���C�A���g���[�h)
	// -----------------------------

	// �N���C�A���g�̃X�e�[�^�X
	LBGuiMjaiClientMode cli_mode;

	// -----------------------------
	// �N���C�A���g���[�h�F�\�P�b�g�����p
	// -----------------------------

	// IP�A�h���X
	int ip_seg1;                   // IP�A�h���X�E�Z�O�����g1
	int ip_seg2;                   // IP�A�h���X�E�Z�O�����g2
	int ip_seg3;                   // IP�A�h���X�E�Z�O�����g3
	int ip_seg4;                   // IP�A�h���X�E�Z�O�����g4

	// Socket���b�Z�[�W
	char res_mes[1024];            // ��M���b�Z�[�W
	char snd_mes[1024];            // ���M���b�Z�[�W
	char stat_mes[256];            // �X�e�[�^�X���b�Z�[�W

	// Socket����
	int send_wait_frame_count;     // ���b�Z�[�W�����҂����̃t���[����
	int send_mes_bytes;            // ���M�o�b�t�@�̃T�C�Y

	// MJAI���b�Z�[�W��͗p�o�b�t�@
	int  wk_str_count;             // ��Ɨp�����z��̑���
	char wk_str[128][64];          // ��Ɨp�����z��

	// �N���C�A���g���O(Socket�f�o�O���O)
	bool clientlog_output_flg;                    // �N���C�A���g���O�E�o�͗L��
	char clientlog_name[FULLPATH_LOGNAME_SIZE];   // �N���C�A���g���O�E�t�@�C����(�t���p�X)
	char clientlog_buf[1024];                     // �N���C�A���g���O�E�o�b�t�@

	// -----------------------------
	// �\�����[�h���Ƃ�GUI���(�r���[�A�[���[�h)
	// -----------------------------

	// �v�����O���
	LBGuiLogType gui_logtype;                     // ���O���

	// �v�����O�t�@�C����
	char log_name_mjai[FULLPATH_LOGNAME_SIZE];    // MJAI�v�����O��(�t���p�X)
	char log_name_mjsocre[FULLPATH_LOGNAME_SIZE]; // �������v�����O��(�t���p�X)

	// �r���[�A�[���[�h�̋�ID�E�ǃA�N�V����ID
	int gui_kyoku_index;                          // GUI�ǔԍ�
	int gui_actid;                                // GUI�A�N�V�����ԍ�

	// �r���[�A�[���[�h�̉��i��v�\���v���[��ID
	int disp_down_tehai_pnum;                     // DOWN�\���v���[��ID

	// -----------------------------
	// �\�����[�h���Ƃ�GUI���(�ݒ胂�[�h)
	// -----------------------------

	// �ݒ��ʂ�GUI���[�h
	LBGuiSettingMode set_mode;

	// -----------------------------
	// �R���X�g���N�^
	// -----------------------------

	//�R���X�g���N�^
    MJSGui(){};

	//�f�X�g���N�^
    ~MJSGui(){};

	// -----------------------------
	// �֐���`
	// -----------------------------

	// GUI�N���X����������
	void GuiInit();
	void GuiPost();

	// �}�E�X���
	void MouseStat();

	// -----------------------------
	// �I�[�v�j���O
	// -----------------------------
	void chk_opening(MJSTkinfo *tk);

	// -----------------------------
	// ���ʊ֐�
	// -----------------------------
	void auto_frame_click(int tmp_coint_max);                         // �t���[�������J�E���g
	void auto_frame_click_riichi(MJSTkinfo *tk, int tmp_coint_max);   // �t���[�������J�E���g(���[�`�p)
	void chk_but(MJSTkinfo *tk);                                      // �I���{�^���̊m�F
	void set_plt_next();                                              // ���փ{�^���m�F
	void set_plt_naki_arinashi();                                     // �u�L/���v�v���[�g�̕\���ύX
	void set_plt_false();                                             // �v���[�g�\���̖�����

	// -----------------------------
	// ���ʊ֐��E��v����
	// -----------------------------

	// �쏈���E���̎�
	// void set_gui_ply_tsumo_act(MJSTkinfo *tk);                       // 1.GUI����ʏ폈���i���C���j
	// void set_hum_ply_tsumo_act(MJSTkinfo *tk);                       // 1-1.GUI����ʏ폈���E�v���[���[�ʏ�A�N�V������`(mode:TEHAI_NORMAL)
	// void set_hum_riichisute_act(MJSTkinfo *tk);                      // 1-2.GUI����ʏ폈���E���[�`�錾��̎̔v�I��(mode:TEHAI_RIICHI_SUTEHAI)
	// void set_hum_riichiyuko_act(MJSTkinfo *tk);                      // 1-3.GUI����ʏ폈���E���[�`�L����̃A�N�V����(���̐؂�A���̘a���A�Þ�)(mode:TEHAI_RIICHI_YUKO)
	// void set_hum_ankankakan_act(MJSTkinfo *tk);                      // 1-4.GUI����ʏ폈���E�v���[���[�ÞȃA�N�V������`(mode:TEHAI_ANKAN_KAKAN_SELECT)

	// �쏈���E���A�N�V�����ݒ�
	// void set_gui_ply_naki_act(MJSTkinfo *tk);                        // 2.GUI����ʏ폈���E�v���[���[�ʖ��m�F(���C��)
	// void set_hum_ply_naki_act(MJSTkinfo *tk);                        // 2-1.GUI����ʏ폈���E�v���[���[�ʖ��A�N�V������`(mode:TEHAI_NORMAL || mode:TEHAI_RIICHI_YUKO)
	// void set_hum_ply_chi1_act(MJSTkinfo *tk);                        // 2-2.GUI����ʏ폈���E�v���[���[�`�[�v�A�N�V������`(mode:TEHAI_CHI_SELECT)
	// void set_hum_ply_chi2_act(MJSTkinfo *tk);                        // 2-3.GUI����ʏ폈���E�v���[���[�`�[�v�A�N�V������`(mode:TEHAI_CHI_SELECT)

	// �쏈���E���̔v
	// void set_gui_ply_nakisute_act(MJSTkinfo *tk);                    // 3.GUI����ʏ폈���E�v���[���[����̎̔v����

	// -----------------------------
	// �v���C���[�h�E�쏈��
	// -----------------------------

	// GUI�N���X�쏉����
	void guiTakuInit();
	void guiTakuPost();

	// �쏈���E���C������
	void guiTaku(MJSTkinfo *tk);                       // ��Q�[�����[�h��GUI����(���C��)
	void guiTakuChkPreClick(MJSTkinfo *tk);            // �샂�[�h���Ƃ̃N���b�N�O����(���C��)
	void guiTakuActClick(MJSTkinfo *tk);               // �샂�[�h���Ƃ̃N���b�N�㏈��(���C��)

	// �쏈���E�N���b�N�O�̊m�F����
	void guiChkPlyTsumoStat(MJSTkinfo *tk);            // �v���[���[�̎��̏�Ԋm�F
	void guiChkPlyNakiStat(MJSTkinfo *tk);             // �v���[���[�̖���Ԋm�F
	void guiChkPlyRonStat(MJSTkinfo *tk);              // �v���[���[�̃�����Ԋm�F

	// �쏈���E���̎�
	void guiSetPlyNormalActMain(MJSTkinfo *tk);        // 1.GUI����ʏ폈���i���C���j
	void guiSetPlyNormalAct(MJSTkinfo *tk);            // 1-1.GUI����ʏ폈���E�v���[���[�ʏ�A�N�V������`(mode:TEHAI_NORMAL)
	void guiSetPlyRiichiSutehaiAct(MJSTkinfo *tk);     // 1-2.GUI����ʏ폈���E���[�`�錾��̎̔v�I��(mode:TEHAI_RIICHI_SUTEHAI)
	void guiSetPlyRiichiYukoAct(MJSTkinfo *tk);        // 1-3.GUI����ʏ폈���E���[�`�L����̃A�N�V����(���̐؂�A���̘a���A�Þ�)(mode:TEHAI_RIICHI_YUKO)
	void guiSetPlyAnkanKakanAct(MJSTkinfo *tk);        // 1-4.GUI����ʏ폈���E�v���[���[�ÞȃA�N�V������`(mode:TEHAI_ANKAN_KAKAN_SELECT)

	// �쏈���E���A�N�V��������
	void guiSetPlyNakiActMain(MJSTkinfo *tk);          // 2.GUI����ʏ폈���E�v���[���[�ʖ��m�F(���C��)
	void guiSetPlyNakiAct(MJSTkinfo *tk);              // 2-1.GUI����ʏ폈���E�v���[���[�ʖ��A�N�V������`(mode:TEHAI_NORMAL || mode:TEHAI_RIICHI_YUKO)
	void guiSetPlyChiPaiAct(MJSTkinfo *tk);            // 2-2.GUI����ʏ폈���E�v���[���[�`�[�v�A�N�V������`(mode:TEHAI_CHI_SELECT)
	void guiSetPlyChiPaiAct2(MJSTkinfo *tk);           // 2-3.GUI����ʏ폈���E�v���[���[�`�[�v�A�N�V������`(mode:TEHAI_CHI_SELECT)

	// �쏈���E���̔v
	void guiSetPlyNakiSuteAct(MJSTkinfo *tk);          // 3.GUI����ʏ폈���E�v���[���[����̎̔v����

	// �쏈���E���̑�
	void guiPlyDetailInfo(MJSTkinfo *tk);              // GUI����ʏ폈���Eply���\��
	void guiKyokuEnd(MJSTkinfo *tk);                   // GUI����ʏ폈���E�ǏI������
	void guiTakuEnd(MJSTkinfo *tk);                    // GUI����ʏ폈���E��I������

	// -----------------------------
	// �N���C�A���g���[�h�E�쏈��
	// -----------------------------

	// �N���C�A���g���[�h�E������
	void guiClientInit(MJSTkinfo *tk); 

	// �N���C�A���g���[�h�E���C������
	void guiClientMain(MJSTkinfo *tk); 

	// �N���C�A���g���[�h�E���̎�
	void guiClientSetPlyNormalActMain(MJSTkinfo *tk);       // �N���C�A���g���[�h�E�N���b�N�㏈��_�ʏ��ʁE���C������
	void guiClientSetPlyNormalAct(MJSTkinfo *tk);           // �N���C�A���g���[�h�E�N���b�N�㏈��_�ʏ��ʁE�v���[���[�ʏ�A�N�V������`(mode:TEHAI_NORMAL)
	void guiClientSetPlyRiichiSutehaiAct(MJSTkinfo *tk);    // �N���C�A���g���[�h�E�N���b�N�㏈��_�ʏ��ʁE���[�`�錾��̎̔v�I��(mode:TEHAI_RIICHI_SUTEHAI)
	void guiClientSetPlyRiichiYukoAct(MJSTkinfo *tk);       // �N���C�A���g���[�h�E�N���b�N�㏈��_�ʏ��ʁE���[�`�L����̃A�N�V����(���̐؂�A���̘a���A�Þ�)(mode:TEHAI_RIICHI_YUKO)
	void guiClientSetPlyAnkanKakanAct(MJSTkinfo *tk);       // �N���C�A���g���[�h�E�N���b�N�㏈��_�ʏ��ʁE�v���[���[�ÞȃA�N�V������`(mode:TEHAI_ANKAN_KAKAN_SELECT)

	// �N���C�A���g���[�h�E���A�N�V��������
	void guiClientSetPlyNakiActMain(MJSTkinfo *tk);         // �N���C�A���g���[�h�E���A�N�V�����E���C������
	void guiClientSetPlyNakiAct(MJSTkinfo *tk);             // �N���C�A���g���[�h�E���A�N�V�����E�T�u����
	void guiSetPlyChiHaiAct(MJSTkinfo *tk);                 // �N���C�A���g���[�h�E�`�[��1���ڂ̔v�I���A�N�V����(mode=11)
	void guiSetPlyChiHaiAct2(MJSTkinfo *tk);                // �N���C�A���g���[�h�E�`�[��2���ڂ̔v�I���A�N�V����(mode=12)

	// �N���C�A���g���[�h�E���̔v
	void guiClienSetPlyNakiSuteAct(MJSTkinfo *tk);          // �N���C�A���g���[�h�E���̔v

	// -----------------------------
	// �쏈��(�r���[�A�[���[�h)
	// -----------------------------
	// �r���[�A�[�E������
	void guiViewerInitTaku(MJSTkinfo *tk);                  // �r���[�A���[�h�̏�����

	// �r���[�A�[�E���C��
	void guiViewerTaku(MJSTkinfo *tk);                      // ���C������
	void count_plyact(MJSTkinfo *tk);                       // ACTID�̃J�E���g�A�b�v����

	// -----------------------------
	// �쏈��(���؃��[�h)
	// -----------------------------
	void guiRunningInit();                                  // ����������
	void guiRunningMain(MJSTkinfo *tk);                     // ���C������

	// -----------------------------
	// �쏈��(�ݒ胂�[�h)
	// -----------------------------
	void guiSettingInit();                                  // ����������
	void guiSetting();                                      // ���C������

};

#endif /* MJSMOUSE_H_INCLUDED */

/* ---------------------------------------------------------------------------------------------- */
// �\�[�X�I��
/* ---------------------------------------------------------------------------------------------- */
