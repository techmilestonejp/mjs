/* ---------------------------------------------------------------------------------------------- 
 * 
 * �v���O�����T�v �F �����疃��(Ver0.1.2.1�F�J����)
 * �o�[�W����     �F 0.1.2.1.233(�a���֐��̌y���ȏC��)
 * �v���O������   �F mjs.exe
 * �t�@�C����     �F score.cpp
 * �N���X��       �F MJSScore�N���X
 * �����T�v       �F ���_�v�Z�N���X
 * Ver0.1.2�쐬�� �F 2023/11/04 09:10:01
 * �ŏI�X�V��     �F 2025/01/04 11:21:26
 * 
 * Copyright (c) 2010-2025 Techmilestone, All rights reserved.
 * 
 * ---------------------------------------------------------------------------------------------- */

#include "score.h"

/* ---------------------------------------------------------------------------------------------- */
// ���_�v�Z�N���X�̏�����
/* ---------------------------------------------------------------------------------------------- */
void MJSScore::ScoreInit(){

}

/* ---------------------------------------------------------------------------------------------- */
// ���_�v�Z�N���X�̏I������
/* ---------------------------------------------------------------------------------------------- */
void MJSScore::ScorePost(){

}

/* ---------------------------------------------------------------------------------------------- */
// ������`
/* ---------------------------------------------------------------------------------------------- */
void MJSScore::SetYakuInfo(){

	// �|����`�E�ʏ��
	yakuhan[NOYAKU]     = 0;
	yakuhan[RIICH]      = 1;
	yakuhan[WRIICH]     = 2;
	yakuhan[IPPATSU]    = 1;
	yakuhan[CHINISO]    = 6;
	yakuhan[HONISO]     = 3;
	yakuhan[JUNCHAN]    = 3;
	yakuhan[RYANPEKO]   = 3;
	yakuhan[HONROTO]    = 2;
	yakuhan[SHOSANGEN]  = 2;
	yakuhan[ITSU]       = 2;
	yakuhan[SANDOKOU]   = 2;
	yakuhan[SANDOJUN]   = 2;
	yakuhan[SANKANTSU]  = 2;
	yakuhan[SANANKO]    = 2;
	yakuhan[TOITOI]     = 2;
	yakuhan[CHANTA]     = 2;
	yakuhan[CHITOI]     = 2;
	yakuhan[PINFU]      = 1;
	yakuhan[TANYAO]     = 1;
	yakuhan[IPEKO]      = 1;
	yakuhan[BAKAZE]     = 1;
	yakuhan[ZIKAZE]     = 1;
	yakuhan[YAKUHAIHAKU]  = 1;
	yakuhan[YAKUHAIHATSU] = 1;
	yakuhan[YAKUHAICHUN]  = 1;
	yakuhan[HAITEI]     = 1;
	yakuhan[HOUTEI]     = 1;
	yakuhan[RINSHAN]    = 1;
	yakuhan[CHANKAN]    = 1;
	yakuhan[TSUMO]      = 1;
	yakuhan[DORA]       = 0;
	yakuhan[URADORA]    = 0;
	yakuhan[AKAHAI]     = 0;
	yakuhan[RENHO]      = 5;
	yakuhan[NAGASHIMAN] = 5;

	// �|����`�E�ʏ���F������
	nakihan[NOYAKU]     = 0;
	nakihan[RIICH]      = 0;
	nakihan[WRIICH]     = 0;
	nakihan[IPPATSU]    = 0;
	nakihan[CHINISO]    = 5;
	nakihan[HONISO]     = 2;
	nakihan[JUNCHAN]    = 2;
	nakihan[RYANPEKO]   = 0;
	nakihan[HONROTO]    = 2;
	nakihan[SHOSANGEN]  = 2;
	nakihan[ITSU]       = 1;
	nakihan[SANDOKOU]   = 2;
	nakihan[SANDOJUN]   = 1;
	nakihan[SANKANTSU]  = 2;
	nakihan[SANANKO]    = 2;
	nakihan[TOITOI]     = 2;
	nakihan[CHANTA]     = 1;
	nakihan[CHITOI]     = 0;
	nakihan[PINFU]      = 0;
	nakihan[TANYAO]     = 1;
	nakihan[IPEKO]      = 0;
	nakihan[BAKAZE]     = 1;
	nakihan[ZIKAZE]     = 1;
	nakihan[YAKUHAIHAKU]  = 1;
	nakihan[YAKUHAIHATSU] = 1;
	nakihan[YAKUHAICHUN]  = 1;
	nakihan[HAITEI]     = 1;
	nakihan[HOUTEI]     = 1;
	nakihan[RINSHAN]    = 1;
	nakihan[CHANKAN]    = 1;
	nakihan[TSUMO]      = 0;
	nakihan[DORA]       = 0;
	nakihan[URADORA]    = 0;
	nakihan[AKAHAI]     = 0;
	nakihan[RENHO]      = 0;
	nakihan[NAGASHIMAN] = 5;

	// ��
	yakuman_bai[NOYAKUMAN]    = 0;
	yakuman_bai[TENHO]        = 1;
	yakuman_bai[CHIHO]        = 1;
	yakuman_bai[CHUREN9MEN]   = 1;
	yakuman_bai[CHUREN]       = 1;
	yakuman_bai[KOKUSHI13MEN] = 1;
	yakuman_bai[KOKUSHI]      = 1;
	yakuman_bai[DAISANGEN]    = 1;
	yakuman_bai[DAISUSHI]     = 1;
	yakuman_bai[SHOSUSHI]     = 1;
	yakuman_bai[TSUISO]       = 1;
	yakuman_bai[CHINROTO]     = 1;
	yakuman_bai[RYUISO]       = 1;
	yakuman_bai[SUKANTSU]     = 1;
	yakuman_bai[SUANKOTANKI]  = 1;
	yakuman_bai[SUANKO]       = 1;
	yakuman_bai[RENHOYAKUMAN] = 1;
}

/* ---------------------------------------------------------------------------------------------- */
// ��b���_�e�[�u���̐ݒ�
/* ---------------------------------------------------------------------------------------------- */
void MJSScore::SetBaseScoreTable(){

	// ���_���
	// https://mj-dragon.com/calc/index-score.html
	// http://yahoo-mbga.jp/page/stdgame/300001/majan_09.html

	// -----------------------------
	// �e����
	// -----------------------------

	// �e�����E��|
	score_ron_oya[0][0] = 0;    // 20��
	score_ron_oya[0][1] = 1500; // 30��
	score_ron_oya[0][2] = 2000; // 40��
	score_ron_oya[0][3] = 2400; // 50��
	score_ron_oya[0][4] = 2900; // 60��
	score_ron_oya[0][5] = 3400; // 70��
	score_ron_oya[0][6] = 3900; // 80��
	score_ron_oya[0][7] = 4400; // 90��
	score_ron_oya[0][8] = 4800; // 100��
	score_ron_oya[0][9] = 5300; // 110��

	// �e�����E��|
	score_ron_oya[1][0] = 2100;  // 20��
	score_ron_oya[1][1] = 2900;  // 30��
	score_ron_oya[1][2] = 3900;  // 40��
	score_ron_oya[1][3] = 4800;  // 50��
	score_ron_oya[1][4] = 5800;  // 60��
	score_ron_oya[1][5] = 6800;  // 70��
	score_ron_oya[1][6] = 7700;  // 80��
	score_ron_oya[1][7] = 8700;  // 90��
	score_ron_oya[1][8] = 9600;  // 100��
	score_ron_oya[1][9] = 10600; // 110��

	// �e�����E�O�|
	score_ron_oya[2][0] = 3900;  // 20��
	score_ron_oya[2][1] = 5800;  // 30��
	score_ron_oya[2][2] = 7700;  // 40��
	score_ron_oya[2][3] = 9600;  // 50��
	score_ron_oya[2][4] = 11600; // 60��
	score_ron_oya[2][5] = 12000; // 70��
	score_ron_oya[2][6] = 12000; // 80��
	score_ron_oya[2][7] = 12000; // 90��
	score_ron_oya[2][8] = 12000; // 100��
	score_ron_oya[2][9] = 12000; // 110��

	// �e�����E�l�|
	score_ron_oya[3][0] =  5800; // 20��
	score_ron_oya[3][1] = 11600; // 30��
	score_ron_oya[3][2] = 12000; // 40��
	score_ron_oya[3][3] = 12000; // 50��
	score_ron_oya[3][4] = 12000; // 60��
	score_ron_oya[3][5] = 12000; // 70��
	score_ron_oya[3][6] = 12000; // 80��
	score_ron_oya[3][7] = 12000; // 90��
	score_ron_oya[3][8] = 12000; // 100��
	score_ron_oya[3][9] = 12000; // 110��

	// �e�����E���Ύq
	score_chitoi_ron_oya[0] = 1200;  // ��|25��
	score_chitoi_ron_oya[1] = 2400;  // ��|25��
	score_chitoi_ron_oya[2] = 4800;  // �O�|25��
	score_chitoi_ron_oya[3] = 9600;  // �l�|25��

	// �e�����E���шȏ�
	score_mangan_ron_oya[0] = 12000; // ����
	score_mangan_ron_oya[1] = 18000; // ����
	score_mangan_ron_oya[2] = 24000; // �{��
	score_mangan_ron_oya[3] = 36000; // �O�{��
	score_mangan_ron_oya[4] = 48000; // ������

	// �e�����E��
	score_yakuman_ron_oya = 48000;

	// -----------------------------
	// �q����
	// -----------------------------

	// �q�����E��|
	score_ron_ko[0][0] = 0;    // 20��
	score_ron_ko[0][1] = 1000; // 30��
	score_ron_ko[0][2] = 1300; // 40��
	score_ron_ko[0][3] = 1600; // 50��
	score_ron_ko[0][4] = 2000; // 60��
	score_ron_ko[0][5] = 2300; // 70��
	score_ron_ko[0][6] = 2600; // 80��
	score_ron_ko[0][7] = 2900; // 90��
	score_ron_ko[0][8] = 3200; // 100��
	score_ron_ko[0][9] = 3600; // 110��

	// �q�����E��|
	score_ron_ko[1][0] = 1300; // 20��
	score_ron_ko[1][1] = 2000; // 30��
	score_ron_ko[1][2] = 2600; // 40��
	score_ron_ko[1][3] = 3200; // 50��
	score_ron_ko[1][4] = 3900; // 60��
	score_ron_ko[1][5] = 4500; // 70��
	score_ron_ko[1][6] = 5200; // 80��
	score_ron_ko[1][7] = 5800; // 90��
	score_ron_ko[1][8] = 6400; // 100��
	score_ron_ko[1][9] = 7100; // 110��

	// �q�����E�O�|
	score_ron_ko[2][0] = 2600; // 20��
	score_ron_ko[2][1] = 3900; // 30��
	score_ron_ko[2][2] = 5200; // 40��
	score_ron_ko[2][3] = 6400; // 50��
	score_ron_ko[2][4] = 7700; // 60��
	score_ron_ko[2][5] = 8000; // 70��
	score_ron_ko[2][6] = 8000; // 80��
	score_ron_ko[2][7] = 8000; // 90��
	score_ron_ko[2][8] = 8000; // 100��
	score_ron_ko[2][9] = 8000; // 110��

	// �q�����E�l�|
	score_ron_ko[3][0] = 5200; // 20��
	score_ron_ko[3][1] = 7700; // 30��
	score_ron_ko[3][2] = 8000; // 40��
	score_ron_ko[3][3] = 8000; // 50��
	score_ron_ko[3][4] = 8000; // 60��
	score_ron_ko[3][5] = 8000; // 70��
	score_ron_ko[3][6] = 8000; // 80��
	score_ron_ko[3][7] = 8000; // 90��
	score_ron_ko[3][8] = 8000; // 100��
	score_ron_ko[3][9] = 8000; // 110��

	// �q�����E���Ύq
	score_chitoi_ron_oya[0] =  800;  // ��|25��
	score_chitoi_ron_oya[1] = 1600;  // ��|25��
	score_chitoi_ron_oya[2] = 3200;  // �O�|25��
	score_chitoi_ron_oya[3] = 6400;  // �l�|25��

	// �q�����E���шȏ�
	score_mangan_ron_ko[0] =  8000; // ����
	score_mangan_ron_ko[1] = 12000; // ����
	score_mangan_ron_ko[2] = 16000; // �{��
	score_mangan_ron_ko[3] = 24000; // �O�{��
	score_mangan_ron_ko[4] = 32000; // ������

	// �q�����E��
	score_yakuman_ron_ko = 32000;

	// -----------------------------
	// ���̘a���E�e�x����
	// -----------------------------

	// ���̘a���e�x�����E��|
	score_tsumo_oya[0][0] =    0; // 20��
	score_tsumo_oya[0][1] =  500; // 30��
	score_tsumo_oya[0][2] =  700; // 40��
	score_tsumo_oya[0][3] =  800; // 50��
	score_tsumo_oya[0][4] = 1000; // 60��
	score_tsumo_oya[0][5] = 1200; // 70��
	score_tsumo_oya[0][6] = 1300; // 80��
	score_tsumo_oya[0][7] = 1500; // 90��
	score_tsumo_oya[0][8] = 1600; // 100��
	score_tsumo_oya[0][9] = 1800; // 110��

	// ���̘a���e�x�����E��|
	score_tsumo_oya[1][0] =  700; // 20��
	score_tsumo_oya[1][1] = 1000; // 30��
	score_tsumo_oya[1][2] = 1300; // 40��
	score_tsumo_oya[1][3] = 1600; // 50��
	score_tsumo_oya[1][4] = 2000; // 60��
	score_tsumo_oya[1][5] = 2300; // 70��
	score_tsumo_oya[1][6] = 2600; // 80��
	score_tsumo_oya[1][7] = 2900; // 90��
	score_tsumo_oya[1][8] = 3200; // 100��
	score_tsumo_oya[1][9] = 3600; // 110��

	// ���̘a���e�x�����E�O�|
	score_tsumo_oya[2][0] = 1300; // 20��
	score_tsumo_oya[2][1] = 2000; // 30��
	score_tsumo_oya[2][2] = 2600; // 40��
	score_tsumo_oya[2][3] = 3200; // 50��
	score_tsumo_oya[2][4] = 3900; // 60��
	score_tsumo_oya[2][5] = 4000; // 70��
	score_tsumo_oya[2][6] = 4000; // 80��
	score_tsumo_oya[2][7] = 4000; // 90��
	score_tsumo_oya[2][8] = 4000; // 100��
	score_tsumo_oya[2][9] = 4000; // 110��

	// ���̘a���e�x�����E�l�|
	score_tsumo_oya[3][0] = 2600; // 20��
	score_tsumo_oya[3][1] = 3900; // 30��
	score_tsumo_oya[3][2] = 4000; // 40��
	score_tsumo_oya[3][3] = 4000; // 50��
	score_tsumo_oya[3][4] = 4000; // 60��
	score_tsumo_oya[3][5] = 4000; // 70��
	score_tsumo_oya[3][6] = 4000; // 80��
	score_tsumo_oya[3][7] = 4000; // 90��
	score_tsumo_oya[3][8] = 4000; // 100��
	score_tsumo_oya[3][9] = 4000; // 110��

	// ���̘a���e�x�����E���Ύq
	score_chitoi_tsumo_oya[0] =  400;
	score_chitoi_tsumo_oya[1] =  800;
	score_chitoi_tsumo_oya[2] = 1600;
	score_chitoi_tsumo_oya[3] = 3200;

	// ���̘a���e�x�����E���шȏ�
	score_mangan_tsumo_oya[0] =  4000;
	score_mangan_tsumo_oya[1] =  6000;
	score_mangan_tsumo_oya[2] =  8000;
	score_mangan_tsumo_oya[3] = 12000;
	score_mangan_tsumo_oya[4] = 16000;

	// ���̘a���e�x�����E��
	score_yakuman_tsumo_oya = 16000;

	// -----------------------------
	// ���̘a���E�q�x����
	// -----------------------------

	// ���̘a���q�x�����E��|
	score_tsumo_ko[0][0] = 0;    // 20��
	score_tsumo_ko[0][1] = 300;  // 30��
	score_tsumo_ko[0][2] = 400;  // 40��
	score_tsumo_ko[0][3] = 400;  // 50��
	score_tsumo_ko[0][4] = 500;  // 60��
	score_tsumo_ko[0][5] = 600;  // 70��
	score_tsumo_ko[0][6] = 700;  // 80��
	score_tsumo_ko[0][7] = 800;  // 90��
	score_tsumo_ko[0][8] = 800;  // 100��
	score_tsumo_ko[0][9] = 900;  // 110��

	// ���̘a���q�x�����E��|
	score_tsumo_ko[1][0] =  400;  // 20��
	score_tsumo_ko[1][1] =  500;  // 30��
	score_tsumo_ko[1][2] =  700;  // 40��
	score_tsumo_ko[1][3] =  800;  // 50��
	score_tsumo_ko[1][4] = 1000;  // 60��
	score_tsumo_ko[1][5] = 1200;  // 70��
	score_tsumo_ko[1][6] = 1300;  // 80��
	score_tsumo_ko[1][7] = 1500;  // 90��
	score_tsumo_ko[1][8] = 1600;  // 100��
	score_tsumo_ko[1][9] = 1800;  // 110��

	// ���̘a���q�x�����E�O�|
	score_tsumo_ko[2][0] =  700; // 20��
	score_tsumo_ko[2][1] = 1000; // 30��
	score_tsumo_ko[2][2] = 1300; // 40��
	score_tsumo_ko[2][3] = 1600; // 50��
	score_tsumo_ko[2][4] = 2000; // 60��
	score_tsumo_ko[2][5] = 2000; // 70��
	score_tsumo_ko[2][6] = 2000; // 80��
	score_tsumo_ko[2][7] = 2000; // 90��
	score_tsumo_ko[2][8] = 2000; // 100��
	score_tsumo_ko[2][9] = 2000; // 110��

	// ���̘a���q�x�����E�l�|
	score_tsumo_ko[3][0] = 1300; // 20��
	score_tsumo_ko[3][1] = 2000; // 30��
	score_tsumo_ko[3][2] = 2000; // 40��
	score_tsumo_ko[3][3] = 2000; // 50��
	score_tsumo_ko[3][4] = 2000; // 60��
	score_tsumo_ko[3][5] = 2000; // 70��
	score_tsumo_ko[3][6] = 2000; // 80��
	score_tsumo_ko[3][7] = 2000; // 90��
	score_tsumo_ko[3][8] = 2000; // 100��
	score_tsumo_ko[3][9] = 2000; // 110��

	// ���̘a���q�x�����E���Ύq
	score_chitoi_tsumo_ko[0] =  200;
	score_chitoi_tsumo_ko[1] =  400;
	score_chitoi_tsumo_ko[2] =  800;
	score_chitoi_tsumo_ko[3] = 1600;

	// ���̘a���q�x�����E���шȏ�
	score_mangan_tsumo_ko[0] = 2000;
	score_mangan_tsumo_ko[1] = 3000;
	score_mangan_tsumo_ko[2] = 4000;
	score_mangan_tsumo_ko[3] = 6000;
	score_mangan_tsumo_ko[4] = 8000;

	// ���̘a���q�x�����E��
	score_yakuman_tsumo_ko   = 8000;

}

/* ---------------------------------------------------------------------------------------------- */
// ���C�������F�a�����_�ݒ�
/* ---------------------------------------------------------------------------------------------- */
void MJSScore::SetAgari(
	MJSYakuinfo *yk,          // �a�������\����
	int  kyoku,               // �ǔԍ�
	int  ie[],                // �v���[���̉Ə��
	int  dora_count,          // �\�h���v����
	int  dora[],              // �\�h���v���
	int  uradora_count,       // ���h���v����
	int  uradora[],           // ���h���v���
	LBAgariTehai  agari_stat, // �a���`��
	int  agari_ply_num,       // �a���v���[��
	int  furikomi_ply_num,    // �U���v���[��
	bool tsumoagari_flg,      // ���̘a���̗L��
	int  agari_hai,           // �a���v
	bool agari_aka,           // �a���v�̐Ԕv�L��
	int  tehai_hist[],        // �a�����̎�v�q�X�g�O����
	int  aka_count[],         // ��v�̐Ԕv����
	int  atama_hai,           // ���v
	int  men_count,           // �ʎq��
	LBMen men_stat[],         // �ʎq���
	int  men_hai[],           // �ʎq�v
	int  men_idx[],           // �ʎqINDEX
	int  nakimen_count,       // ���ʎq��
	LBMen nakimen_stat[],     // ���ʎq���
	int  nakimen_hai[],       // ���ʎq�v
	int  nakimen_idx[],       // ���ʎqINDEX
	int  nakimen_aka[],       // ���ʎq�Ԕv����
	bool tmp_riichi_flg,      // ���[�`�t���O
	bool tmp_riichi_ippatsu_flg,  // ���[�`�ꔭ�t���O
	bool tmp_double_riichi_flg    // �_�u�����[�`�t���O
	){

	// -----------------------------
	// ���O��`
	// -----------------------------
	SetYakuInfo();
	SetBaseScoreTable();

	// -----------------------------
	// ���C������
	// -----------------------------

	// 01:����������
	Chk_initAgariScore(yk);

	// -----------------------------
	// score�\���̂ɘa�����ݒ�
	// -----------------------------
	yk->agari_stat        = agari_stat;           // �a���`��
	yk->agari_ply_num     = agari_ply_num;        // �a���v���[��
	yk->furikomi_ply_num  = furikomi_ply_num;     // �U���v���[��
	yk->tsumo_agari_flg   = tsumoagari_flg;       // ���̘a��
	yk->agari_hai         = agari_hai;            // �a���v
	yk->agari_aka         = agari_aka;            // �a���v��

	// -----------------------------
	// �Ǐ��̐ݒ�
	// -----------------------------

	// ���ǃt���O
	yk->ryukyoku_flg = false;

	// �e�t���O�̐ݒ�
	if( ie[agari_ply_num] == 0 ){
		yk->agari_ply_oya_flg = true;
	}else{
		yk->agari_ply_oya_flg = false;
	}

	// �ʑO�t���O�̐ݒ�
	if(nakimen_count == 0){
		yk->menzen_flg = true;
	}else{
		yk->menzen_flg = false;
	}

	// �ꕗ�����̐ݒ�
	yk->agari_ply_bakaze = 31+(kyoku/4);
	yk->agari_ply_zikaze = 31+ie[agari_ply_num];

	// -----------------------------
	// �Ԕv�ݒ�
	// -----------------------------

	// ��Ɨp�ϐ��̐ݒ�
	yk->agari_aka_count[0] = aka_count[0];
	yk->agari_aka_count[1] = aka_count[1];
	yk->agari_aka_count[2] = aka_count[2];

	// �a���v�̉��Z
	if(agari_aka == true){
		yk->agari_aka_count[(agari_hai-5)/10]++;
	}

	// 02:���O�a�����̐ݒ�
	Chk_preAgariScore(yk,
	atama_hai,
	men_count,
	men_stat,
	men_hai,
	men_idx,
	nakimen_count,
	nakimen_stat,
	nakimen_hai,
	nakimen_idx,
	nakimen_aka,
	tmp_riichi_flg,
	tmp_riichi_ippatsu_flg,
	tmp_double_riichi_flg);

	// 03:��v�e�[�u���ݒ�
	Set_AgariTehaiTbl(yk, tehai_hist);

	// �a���`�����Ƃ̕��v�Z
	if(yk->agari_stat == AGARI_NORMAL){
		// �ʏ�`��
		Chk_mentsu(yk, dora_count, dora, uradora);     // 04:�ʎq�m�F
		Chk_tehai_count(yk);                           // 05:��v�����m�F
		Chk_fu(yk);                                    // 06:���v�Z
	}else if(yk->agari_stat == AGARI_CHITOI){
		// ���Ύq�`��
		Chk_chitoi_mentsu(yk);                         // 04:�ʎq�m�F(���Ύq�`��)
	}else if(yk->agari_stat == AGARI_KOKUSHI){
		Chk_kokushi_mentsu(yk);
	}

	// 07:���m�F
	Chk_yaku(yk, tehai_hist);

	// 08:���_�v�Z
	Chk_score(yk);

}

/* ---------------------------------------------------------------------------------------------- */
// 01:����������
/* ---------------------------------------------------------------------------------------------- */
void MJSScore::Chk_initAgariScore(MJSYakuinfo *yk){

	// �a���v�ʎq
	yk->agari_men_num_agari_hai = 999;

	// �h��
	yk->agari_dora_count = 0; 
	yk->agari_uradora_count = 0;

	// �Ԕv
	yk->agari_aka_count[0] = 0;
	yk->agari_aka_count[1] = 0;
	yk->agari_aka_count[2] = 0;

	// �ʎq��
	yk->mentsu_count_shuntsu = 0;
	yk->mentsu_count_minshun = 0;
	yk->mentsu_count_anko    = 0;
	yk->mentsu_count_minko   = 0;
	yk->mentsu_count_ankan   = 0;
	yk->mentsu_count_minkan  = 0;

	yk->mentsu_count_19zi = 0;
	yk->mentsu_count_chunchan = 0;
	yk->mentsu_count_manzu = 0;
	yk->mentsu_count_pinzu = 0;
	yk->mentsu_count_souzu = 0;
	yk->mentsu_count_zihai = 0;
	yk->mentsu_count_green = 0;

	// ���̐ݒ�
	yk->basefu = 20;
	yk->agari_men_Fu[0]=0;
	yk->agari_men_Fu[1]=0;
	yk->agari_men_Fu[2]=0;
	yk->agari_men_Fu[3]=0;
	yk->atamaFu=0;
	yk->menzenFu=0;
	yk->machiFu=0;
	yk->tsumoFu=0;

	// ���̍��v
	yk->totalFu = yk->basefu;
	yk->scoreFu = yk->totalFu;

}

/* ---------------------------------------------------------------------------------------------- */
// 02:���O�a�����̐ݒ�
/* ---------------------------------------------------------------------------------------------- */
void MJSScore::Chk_preAgariScore(
	MJSYakuinfo *yk,
	int  atama_hai,           // ���v
	int  men_count,           // �ʎq��
	LBMen men_stat[],         // �ʎq���
	int  men_hai[],           // �ʎq�v
	int  men_idx[],           // �ʎqINDEX
	int  nakimen_count,       // ���ʎq��
	LBMen nakimen_stat[],     // ���ʎq���
	int  nakimen_hai[],       // ���ʎq�v
	int  nakimen_idx[],       // ���ʎqINDEX
	int  nakimen_aka[],       // ���ʎq�Ԕv����
	bool tmp_riichi_flg,      // ���[�`�t���O
	bool tmp_riichi_ippatsu_flg,        // ���[�`�ꔭ�t���O
	bool tmp_double_riichi_flg          // �_�u�����[�`�t���O
	){

	// -----------------------------
	// ��Ɨp�ϐ��̒�`
	// -----------------------------
	// �Ԕv
	int tmp_aka_man;
	int tmp_aka_pin;
	int tmp_aka_sou;

	// -----------------------------
	// �a���v���[���[�̘a�����̉񐔁E���[�`��Ԋm�F(������)
	// -----------------------------

	yk->riichi_flg          = tmp_riichi_flg;
	yk->riichi_ippatsu_flg  = tmp_riichi_ippatsu_flg;
	yk->double_riichi_flg   = tmp_double_riichi_flg;
	yk->agari_ply_tsumo_count  = 0;
	yk->agari_ply_riichi_count = 0;

	// -----------------------------
	// �Ԕv������
	// -----------------------------

	// ��Ɨp�ϐ��̐ݒ�
	tmp_aka_man = yk->agari_aka_count[0];
	tmp_aka_pin = yk->agari_aka_count[1];
	tmp_aka_sou = yk->agari_aka_count[2];

	// -----------------------------
	// �������̐ݒ�
	// -----------------------------

	// �����ݒ�
	yk->agari_ata_hai = atama_hai;

	// �a���v�̖ʎq�ԍ��ݒ�
	if (yk->agari_ata_hai == yk->agari_hai){

		// �ʎq�ԍ��͉��u���́u999�v�Ƃ���
		yk->agari_men_num_agari_hai = 999;

	}

	// �Ԕv�ݒ�
	yk->agari_ata_aka = 0;

	if(yk->agari_ata_hai == 5){
		if(tmp_aka_man>2){
			yk->agari_ata_aka=2;
			tmp_aka_man=tmp_aka_man-2;
		}else{
			yk->agari_ata_aka=tmp_aka_man;
			tmp_aka_man=0;
		}
	}

	if(yk->agari_ata_hai == 15){
		if(tmp_aka_pin>2){
			yk->agari_ata_aka=2;
			tmp_aka_pin=tmp_aka_pin-2;
		}else{
			yk->agari_ata_aka=tmp_aka_pin;
			tmp_aka_pin=0;
		}
	}

	if(yk->agari_ata_hai == 25){
		if(tmp_aka_sou>2){
			yk->agari_ata_aka=tmp_aka_sou=2;
			tmp_aka_sou=tmp_aka_sou-2;
		}else{
			yk->agari_ata_aka=tmp_aka_sou;
			tmp_aka_sou=0;
		}
	}

	// -----------------------------
	// ��v�ʎq�̐ݒ�
	// -----------------------------

	// �ʎq���ݒ�
	yk->agari_men_count = men_count;

	// �����c���̊i�[
	for(int tmp_i = 0; tmp_i < yk->agari_men_count; tmp_i++){

		// -----------------------------
		// �����c���̊i�[
		// -----------------------------

		yk->agari_men_stat[tmp_i]      = men_stat[tmp_i];  
		yk->agari_men_hai[tmp_i]       = men_hai[tmp_i];   
		yk->agari_men_aka_count[tmp_i] = 0;                      // �Ԕv�̏�����

		// -----------------------------
		// �Í�����
		// -----------------------------
		if ( yk->agari_men_stat[tmp_i] == ANKO){

			// �ݎq����
			if(yk->agari_men_hai[tmp_i] == 5){
				if(tmp_aka_man>3){
					yk->agari_men_aka_count[tmp_i]=3;
					tmp_aka_man=tmp_aka_man-3;
				}else{
					yk->agari_men_aka_count[tmp_i]=tmp_aka_man;
					tmp_aka_man=0;
				}
			}

			// ���q����
			if(yk->agari_men_hai[tmp_i] == 15){
				if(tmp_aka_pin>2){
					yk->agari_men_aka_count[tmp_i]=3;
					tmp_aka_pin=tmp_aka_pin-3;
				}else{
					yk->agari_men_aka_count[tmp_i]=tmp_aka_pin;
					tmp_aka_pin=0;
				}
			}

			// ���q����
			if(yk->agari_men_hai[tmp_i] == 25){
				if(tmp_aka_sou>2){
					yk->agari_men_aka_count[tmp_i]=3;
					tmp_aka_sou=tmp_aka_sou-3;
				}else{
					yk->agari_men_aka_count[tmp_i]=tmp_aka_sou;
					tmp_aka_sou=0;
				}
			}

			// �a���v�̖ʎq�ԍ��ݒ� - �Í��̏ꍇ
			if ( yk->agari_men_hai[tmp_i] == yk->agari_hai){

				// �ʎq�ԍ��̐ݒ�
				yk->agari_men_num_agari_hai = tmp_i;

				// �����a���̖ʎq�ԍ��͖������c�ɕύX����
				if(yk->tsumo_agari_flg == false){
					yk->agari_men_stat[tmp_i] = MINKO;
				}

			}
		}

		// -----------------------------
		// ���q����
		// -----------------------------
		if ( yk->agari_men_stat[tmp_i] == SHUNTSU){

			// �ݎq����
			if(yk->agari_men_hai[tmp_i] == 3 || 
			   yk->agari_men_hai[tmp_i] == 4 ||
			   yk->agari_men_hai[tmp_i] == 5){

				// �Ԕv������Ȃ�
				if(tmp_aka_man>0){
					yk->agari_men_aka_count[tmp_i]++;
					tmp_aka_man--;
				}
			}

			// ���q����
			if(yk->agari_men_hai[tmp_i] == 13 || 
			   yk->agari_men_hai[tmp_i] == 14 ||
			   yk->agari_men_hai[tmp_i] == 15){

				// �Ԕv������Ȃ�
				if(tmp_aka_pin>0){
					yk->agari_men_aka_count[tmp_i]++;
					tmp_aka_pin--;
				}
			}

			// ���q����
			if(yk->agari_men_hai[tmp_i] == 23 || 
			   yk->agari_men_hai[tmp_i] == 24 ||
			   yk->agari_men_hai[tmp_i] == 25){

				// �Ԕv������Ȃ�
				if(tmp_aka_sou>0){
					yk->agari_men_aka_count[tmp_i]++;
					tmp_aka_sou--;
				}
			}

			// �a���v�̖ʎq�ԍ��ݒ� - ���q�̏ꍇ
			if ( yk->agari_men_hai[tmp_i]   == yk->agari_hai || 
			     yk->agari_men_hai[tmp_i]+1 == yk->agari_hai || 
			     yk->agari_men_hai[tmp_i]+2 == yk->agari_hai ){

				// �ʎq�ԍ��̐ݒ�
				yk->agari_men_num_agari_hai = tmp_i;

				// �����a���̖ʎq�ԍ��͖������c�ɕύX����
				if(yk->tsumo_agari_flg == false){
					yk->agari_men_stat[tmp_i] = MINSHUN;
				}
			}

		}

	}

	// -----------------------------
	// �N���ʎq(���ʎq)�̐ݒ�
	// -----------------------------

	// �N���ʎq�̒ǉ�
	for(int tmp_i = 0; tmp_i < nakimen_count; tmp_i++){

		// ���Ȋm�F
		if( nakimen_stat[tmp_i] == KAKAN){

			// ���Ȗʎq�ݒ�
			for(int tmp_j = 0; tmp_j < nakimen_count; tmp_j++){

				// ���Ȃ����Í��ł����
				if(yk->agari_men_hai[tmp_j] == nakimen_hai[tmp_i]){

					// �����c���̊i�[(����)
					yk->agari_men_stat[tmp_j] = MINKAN;

					// �Ԕv+1���Z
					if( nakimen_aka[tmp_j] > 0){
						yk->agari_men_aka_count[tmp_j]++;
					}

				}
			}

		// ���ȈȊO
		}else{

			// �����c���̊i�[
			yk->agari_men_stat[yk->agari_men_count]       = nakimen_stat[tmp_i];
			yk->agari_men_hai[yk->agari_men_count]        = nakimen_idx[tmp_i];
			yk->agari_men_aka_count[yk->agari_men_count]  = nakimen_aka[tmp_i];
			yk->agari_men_count++;

		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 03:�a����v�e�[�u���̐ݒ�
/* ---------------------------------------------------------------------------------------------- */
void MJSScore::Set_AgariTehaiTbl(MJSYakuinfo *yk, int tehai_hist[]){

	// �Ԕv���̉��ݒ�
	int tmp_aka_man;
	int tmp_aka_pin;
	int tmp_aka_sou;

	tmp_aka_man = yk->agari_aka_count[0];
	tmp_aka_pin = yk->agari_aka_count[1];
	tmp_aka_sou = yk->agari_aka_count[2];

	// ----------------------------------------
	// �e�[�u�����̊i�[
	// ----------------------------------------

	// ��v���̏�����
	yk->agari_tehaicount = 0;

	// ��v�e�[�u���̐ݒ�
	for(int tmp_i = 1; tmp_i < PAI_MAX; tmp_i++){

		// ��v�̐������J��Ԃ�
		for(int tmp_j = 0; tmp_j < tehai_hist[tmp_i]; tmp_j++){

			// ��v�e�[�u���ݒ�
			yk->agari_tehaitbl[yk->agari_tehaicount] = tmp_i;

			// �Ԕv�e�[�u���ݒ�
			if(tmp_i == 5 && tmp_aka_man > 0){
				yk->agari_tehai_tbl_aka[yk->agari_tehaicount] = true;
				tmp_aka_man--;
			}else if(tmp_i == 15 && tmp_aka_pin > 0){
				yk->agari_tehai_tbl_aka[yk->agari_tehaicount] = true;
				tmp_aka_pin--;
			}else if(tmp_i == 25 && tmp_aka_sou > 0){
				yk->agari_tehai_tbl_aka[yk->agari_tehaicount] = true;
				tmp_aka_sou--;
			}else{
				yk->agari_tehai_tbl_aka[yk->agari_tehaicount] = false;
			}

			// ��v����+1
			yk->agari_tehaicount++;

		}
	}

}

/* ---------------------------------------------------------------------------------------------- */
// 04:�ʎq�m�F
/* ---------------------------------------------------------------------------------------------- */
void MJSScore::Chk_mentsu(MJSYakuinfo *yk, int dora_count, int dora[], int uradora[]){

	// -----------------------------
	// �ϐ���`
	// -----------------------------

	// �Ԕv��Ɨp
	int tmp_aka_man;
	int tmp_aka_pin;
	int tmp_aka_sou;

	yk->agari_aka_count[0] = 0;
	yk->agari_aka_count[1] = 0;
	yk->agari_aka_count[2] = 0;

	// -----------------------------
	// �Ԕv������
	// -----------------------------

	tmp_aka_man = 0;
	tmp_aka_pin = 0;
	tmp_aka_sou = 0;

	// -----------------------------
	// �҂��`���̊m�F
	// -----------------------------

	// �P�R�҂��m�F
	if( yk->agari_men_num_agari_hai == 999){
		yk->agari_machi_stat = TANKI;

	// ���q�֘A�̑҂�
	}else if( yk->agari_men_stat[yk->agari_men_num_agari_hai] == SHUNTSU ||
              yk->agari_men_stat[yk->agari_men_num_agari_hai] == MINSHUN ){

		// �a���v���ʎqINDEX�Ɠ����Ȃ�
		if( yk->agari_men_hai[yk->agari_men_num_agari_hai] == yk->agari_hai ){

			// �y���`�����𒲂ׂ�
			if( yk->agari_hai ==  7 || 
			    yk->agari_hai == 17 || 
			    yk->agari_hai == 27 ){
				yk->agari_machi_stat = PENCHAN ; 
			}else{
				yk->agari_machi_stat = RYANMEN;
			}

		}

		// �a���v���ʎqINDEX+1�Ȃ�
		if( yk->agari_men_hai[yk->agari_men_num_agari_hai] + 1 == yk->agari_hai ){
			yk->agari_machi_stat = KANCHAN;
		}

		// �a���v���ʎqINDEX+2�Ȃ�
		if( yk->agari_men_hai[yk->agari_men_num_agari_hai] + 2 == yk->agari_hai ){

			// �y���`�����𒲂ׂ�
			if( yk->agari_hai ==  3 || 
			    yk->agari_hai == 13 || 
			    yk->agari_hai == 23 ){
				yk->agari_machi_stat = PENCHAN ; 
			}else{
				yk->agari_machi_stat = RYANMEN;
			}

		}

	// �V�����|���҂��m�F
	}else if( yk->agari_men_stat[yk->agari_men_num_agari_hai] == ANKO  ||
              yk->agari_men_stat[yk->agari_men_num_agari_hai] == MINKO ){
				yk->agari_machi_stat = TOITSU;

	// ���̑�
	}else{
		yk->agari_machi_stat = NOMENTSU;
	}

	// -----------------------------
	// �h���J�E���g
	// -----------------------------

	// �h���J�E���g
	Chk_tehai_dora_count(yk, dora_count, dora, uradora);

	// -----------------------------
	// �Ԕv�J�E���g
	// -----------------------------

	yk->agari_aka_count[0] = 0;
	yk->agari_aka_count[1] = 0;
	yk->agari_aka_count[2] = 0;

	// ���ԃJ�E���g
	if(yk->agari_ata_hai == MAN5NUM){
		yk->agari_aka_count[0]=yk->agari_ata_aka;
	}else if(yk->agari_ata_hai == PIN5NUM){
		yk->agari_aka_count[1]=yk->agari_ata_aka;
	}else if(yk->agari_ata_hai == SOU5NUM){
		yk->agari_aka_count[2]=yk->agari_ata_aka;
	}

	// �ʎq�ԃJ�E���g
	for(int tmp_i = 0; tmp_i < 4; tmp_i++){

		// �ʎq�ԃJ�E���g - �ݎq
		if( yk->agari_men_hai[tmp_i] == MAN3NUM || 
		    yk->agari_men_hai[tmp_i] == MAN4NUM ||
		    yk->agari_men_hai[tmp_i] == MAN5NUM ){

			// �Ԕv���Z
			yk->agari_aka_count[0] = yk->agari_aka_count[0] + yk->agari_men_aka_count[tmp_i];

		// �ʎq�ԃJ�E���g - ���q
		}else if(yk->agari_men_hai[tmp_i] == PIN3NUM ||
		         yk->agari_men_hai[tmp_i] == PIN4NUM ||
		         yk->agari_men_hai[tmp_i] == PIN5NUM ){

			// �Ԕv���Z
			yk->agari_aka_count[1] = yk->agari_aka_count[1] + yk->agari_men_aka_count[tmp_i];

		// �ʎq�ԃJ�E���g - ���q
		}else if(yk->agari_men_hai[tmp_i] == SOU3NUM ||
		         yk->agari_men_hai[tmp_i] == SOU4NUM ||
		         yk->agari_men_hai[tmp_i] == SOU5NUM ){

			// �Ԕv���Z
			yk->agari_aka_count[2] = yk->agari_aka_count[2] + yk->agari_men_aka_count[tmp_i];

		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 04-01:���O�a�����̐ݒ�(���Ύq)
/* ---------------------------------------------------------------------------------------------- */
void MJSScore::Chk_chitoi_mentsu(MJSYakuinfo *yk){
/*
	// -----------------------------
	// �ϐ���`
	// -----------------------------

	// �Ԕv��Ɨp
	int tmp_aka_man;
	int tmp_aka_pin;
	int tmp_aka_sou;

	yk->mentsu_count_19zi=0;                   // ��㎚�̖ʎq��
	yk->mentsu_count_chunchan=0;               // �����v�̖ʎq��

	yk->mentsu_count_manzu=0;                  // �ݎq��
	yk->mentsu_count_pinzu=0;                  // ���q��
	yk->mentsu_count_souzu=0;                  // ���q��
	yk->mentsu_count_zihai=0;                  // ���v�̐�

	// -----------------------------
	// �҂��`��
	// -----------------------------
	yk->agari_machi_stat = TANKI;

	// -----------------------------
	// ���̐ݒ�
	// -----------------------------
	yk->basefu = 25;
	yk->agari_men_Fu[0]=0;
	yk->agari_men_Fu[1]=0;
	yk->agari_men_Fu[2]=0;
	yk->agari_men_Fu[3]=0;
	yk->atamaFu=0;
	yk->menzenFu=0;
	yk->machiFu=0;
	yk->tsumoFu=0;

	// ���̍��v
	yk->totalFu = yk->basefu;
	yk->scoreFu = yk->totalFu;

	// -----------------------------
	// �Ԕv������
	// -----------------------------

	// ��Ɨp�ϐ��̐ݒ�
	tmp_aka_man = tk->ply_act_aka_count[yk->agari_ply_num][0];
	tmp_aka_pin = tk->ply_act_aka_count[yk->agari_ply_num][1];
	tmp_aka_sou = tk->ply_act_aka_count[yk->agari_ply_num][2];

	// -----------------------------
	// �ʎq�m�F
	// -----------------------------
	int tmp_men_count=0;
	for(int tmp_hai=1; tmp_hai<PAI_MAX; tmp_hai++){
		// �a���ʎq�ԍ��ݒ�
		if(yk->agari_hai == tmp_hai){
			yk->agari_men_num_agari_hai = tmp_men_count;
		}

		// �������m�F
		if(tk->ply_act_tehai[yk->agari_ply_num][tmp_hai] > 1 ||
		   yk->agari_hai == tmp_hai){
			// �ʎq�ݒ�
			yk->agari_chitoi_men_hai[tmp_men_count] = tmp_hai;
			yk->agari_chitoi_men_aka_count[tmp_men_count] = 0;
			tmp_men_count++;
		}

	}

	// -----------------------------
	// �e��v�̖����m�F
	// -----------------------------
	for(int tmp_i=0; tmp_i<7; tmp_i++){

		// -----------------------------
		// ��㎚�m�F
		// -----------------------------
		if (yk->agari_chitoi_men_hai[tmp_i] ==  9 ||
		    yk->agari_chitoi_men_hai[tmp_i] == 11 ||
	        yk->agari_chitoi_men_hai[tmp_i] == 19 ||
		    yk->agari_chitoi_men_hai[tmp_i] == 21 ||
		    yk->agari_chitoi_men_hai[tmp_i] == 29 ||
		    yk->agari_chitoi_men_hai[tmp_i] == 31 ||
		    yk->agari_chitoi_men_hai[tmp_i] == 32 ||
		    yk->agari_chitoi_men_hai[tmp_i] == 33 ||
	        yk->agari_chitoi_men_hai[tmp_i] == 34 ||
	        yk->agari_chitoi_men_hai[tmp_i] == 35 ||
		    yk->agari_chitoi_men_hai[tmp_i] == 36 ||
		    yk->agari_chitoi_men_hai[tmp_i] == 37 ){

			// �ʎq���̉��Z
			yk->mentsu_count_19zi++;

		}else{

			// �ʎq���̉��Z
			yk->mentsu_count_chunchan++;

		}

		// -----------------------------
		// �F����
		// -----------------------------
		if (yk->agari_chitoi_men_hai[tmp_i] >  0 &&
		    yk->agari_chitoi_men_hai[tmp_i] < 10 ){

			// �ʎq���̉��Z
			yk->mentsu_count_manzu++;

		}else if ( yk->agari_chitoi_men_hai[tmp_i] > 10 &&
		           yk->agari_chitoi_men_hai[tmp_i] < 20 ){

			// �ʎq���̉��Z
			yk->mentsu_count_pinzu++;

		}else if ( yk->agari_chitoi_men_hai[tmp_i] > 20 &&
		           yk->agari_chitoi_men_hai[tmp_i] < 30 ){

			// �ʎq���̉��Z
			yk->mentsu_count_souzu++;

		}else if ( yk->agari_chitoi_men_hai[tmp_i] > 30 &&
		           yk->agari_chitoi_men_hai[tmp_i] < 38 ){

			// �ʎq���̉��Z
			yk->mentsu_count_zihai++;

		}

	}
*/
}

/* ---------------------------------------------------------------------------------------------- */
// 04-02:���O�a�����̐ݒ�(���m)
/* ---------------------------------------------------------------------------------------------- */
void MJSScore::Chk_kokushi_mentsu(MJSYakuinfo *yk){

	// �҂��`��
	yk->agari_machi_stat = TANKI;

	// ���̐ݒ�
	yk->basefu = 20;
	yk->agari_men_Fu[0]=0;
	yk->agari_men_Fu[1]=0;
	yk->agari_men_Fu[2]=0;
	yk->agari_men_Fu[3]=0;
	yk->atamaFu=0;
	yk->menzenFu=0;
	yk->machiFu=0;
	yk->tsumoFu=0;

	// ���̍��v
	yk->totalFu = yk->basefu;
	yk->scoreFu = yk->totalFu;
}

/* ---------------------------------------------------------------------------------------------- */
// 05:��v�����m�F
/* ---------------------------------------------------------------------------------------------- */
void MJSScore::Chk_tehai_count(MJSYakuinfo *yk){

	// -----------------------------
	// �e��v�̖����m�F
	// -----------------------------

	// �ϐ�������
	yk->mentsu_count_shuntsu = 0;
	yk->mentsu_count_minshun = 0;
	yk->mentsu_count_anko    = 0;
	yk->mentsu_count_minko   = 0;
	yk->mentsu_count_ankan   = 0;
	yk->mentsu_count_minkan  = 0;

	yk->mentsu_count_19zi     = 0;             // ��㎚�̐�
	yk->mentsu_count_chunchan = 0;             // �����v�̖ʎq��

	yk->mentsu_count_manzu    = 0;             // �ݎq��
	yk->mentsu_count_pinzu    = 0;             // ���q��
	yk->mentsu_count_souzu    = 0;             // ���q��
	yk->mentsu_count_zihai    = 0;             // ���v�̐�
	yk->mentsu_count_green    = 0;             // �Δv�̐�

	// �q�X�g�O�����̏�����
	for(int tmp_i = 0; tmp_i < PAI_MAX; tmp_i++){
		yk->anko_hist[tmp_i]    = 0;
		yk->shuntsu_hist[tmp_i] = 0;
	}

	// -----------------------------
	// �����m�F����
	// -----------------------------

		// -----------------------------
		// �����m�F����
		// -----------------------------

		// ��v�m�F
		if (yk->agari_ata_hai == yk->agari_ply_bakaze ||
		    yk->agari_ata_hai == yk->agari_ply_zikaze ||
		    yk->agari_ata_hai == 35 ||
	        yk->agari_ata_hai == 36 ||
		    yk->agari_ata_hai == 37 ){

			// ��v�ݒ�
			yk->agari_ata_19zi = 2; 

			// �ʎq���̉��Z
			yk->mentsu_count_19zi++;

		// ��㎚�v�m�F
		}else if (yk->agari_ata_hai == 1 ||
		    yk->agari_ata_hai ==  9 ||
		    yk->agari_ata_hai == 11 ||
	        yk->agari_ata_hai == 19 ||
		    yk->agari_ata_hai == 21 ||
	        yk->agari_ata_hai == 29 ||
		    yk->agari_ata_hai == 31 ||
	        yk->agari_ata_hai == 32 ||
	        yk->agari_ata_hai == 33 ||
		    yk->agari_ata_hai == 34 ){

			// ��㎚�v�ݒ�
			yk->agari_ata_19zi = 1;

			// �ʎq���̉��Z
			yk->mentsu_count_19zi++;

		// �����v�m�F
		}else{

			// �����v�ݒ�
			yk->agari_ata_19zi = 0;

			// �ʎq���̉��Z
			yk->mentsu_count_chunchan++;

		}

		// -----------------------------
		// �ݎq�E���q�E���q�E���v�̖����m�F(����)
		// -----------------------------

		// �ݎq���Z
		if (yk->agari_ata_hai >  0 &&
		    yk->agari_ata_hai < 10 ){

			// �ݎq���Z
			yk->mentsu_count_manzu++;

		// ���q���Z
		}else if (yk->agari_ata_hai > 10 &&
		          yk->agari_ata_hai < 20 ){

			// ���q���Z
			yk->mentsu_count_pinzu++;

		// ���q���Z
		}else if (yk->agari_ata_hai > 20 &&
		          yk->agari_ata_hai < 30 ){

			// ���q���Z
			yk->mentsu_count_souzu++;

		// ���v���Z
		}else if (yk->agari_ata_hai > 30 &&
		          yk->agari_ata_hai < 38 ){

			// ���v���Z
			yk->mentsu_count_zihai++;

		}

	// -----------------------------
	// �Δv�̖����m�F(����)
	// -----------------------------





	// -----------------------------
	// �ʎq�m�F����
	// -----------------------------

	for(int tmp_i = 0; tmp_i < 4; tmp_i++){

		// -----------------------------
		// ��㎚�m�F(�����c)
		// -----------------------------

		if (yk->agari_men_hai[tmp_i] == yk->agari_ply_bakaze ||
		    yk->agari_men_hai[tmp_i] == yk->agari_ply_zikaze ||
		    yk->agari_men_hai[tmp_i] == 35 ||
	        yk->agari_men_hai[tmp_i] == 36 ||
		    yk->agari_men_hai[tmp_i] == 37 ){

			// ��v�ݒ�
			yk->agari_men_19zi[tmp_i] = 2; 

			// �ʎq���̉��Z
			yk->mentsu_count_19zi++;

		}else if (yk->agari_men_hai[tmp_i] == 1 ||
		    yk->agari_men_hai[tmp_i] ==  9 ||
		    yk->agari_men_hai[tmp_i] == 11 ||
	        yk->agari_men_hai[tmp_i] == 19 ||
		    yk->agari_men_hai[tmp_i] == 21 ||
		    yk->agari_men_hai[tmp_i] == 29 ||
		    yk->agari_men_hai[tmp_i] == 31 ||
		    yk->agari_men_hai[tmp_i] == 32 ||
		    yk->agari_men_hai[tmp_i] == 33 ||
		    yk->agari_men_hai[tmp_i] == 34 ){

			// ��㎚�ݒ�
			yk->agari_men_19zi[tmp_i] = 1; 

			// �ʎq���̉��Z
			yk->mentsu_count_19zi++;

		// 789�̃y���`�����̏ꍇ
		}else if((yk->agari_men_stat[tmp_i] == SHUNTSU || yk->agari_men_stat[tmp_i] == MINSHUN) && 
                 (yk->agari_men_hai[tmp_i] == 7  || 
		          yk->agari_men_hai[tmp_i] == 17 || 
		          yk->agari_men_hai[tmp_i] == 27 )){

			// ��㎚�ݒ�
			yk->agari_men_19zi[tmp_i] = 1; 

			// �ʎq���̉��Z
			yk->mentsu_count_19zi++;


		}else{

			// �����v�ݒ�
			yk->agari_men_19zi[tmp_i] = 0;

			// �ʎq���̉��Z
			yk->mentsu_count_chunchan++;

		}

		// -----------------------------
		// �ݎq�E���q�E���q�E���v�̖����m�F(�ʎq)
		// -----------------------------

		// �ݎq���Z
		if (yk->agari_men_hai[tmp_i] >  0 &&
		    yk->agari_men_hai[tmp_i] < 10 ){

			// �ݎq���Z
			yk->mentsu_count_manzu++;

		// ���q���Z
		}else if (yk->agari_men_hai[tmp_i] > 10 &&
		          yk->agari_men_hai[tmp_i] < 20 ){

			// ���q���Z
			yk->mentsu_count_pinzu++;

		// ���q���Z
		}else if (yk->agari_men_hai[tmp_i] > 20 &&
		          yk->agari_men_hai[tmp_i] < 30 ){

			// ���q���Z
			yk->mentsu_count_souzu++;

		// ���v���Z
		}else if (yk->agari_men_hai[tmp_i] > 30 &&
		          yk->agari_men_hai[tmp_i] < 38 ){

			// ���v���Z
			yk->mentsu_count_zihai++;

		}

		// -----------------------------
		// �Δv�̖����m�F
		// -----------------------------




		// -----------------------------
		// ���q�E�Í��̃q�X�g�O�����ݒ�
		// -----------------------------

		if( yk->agari_men_stat[tmp_i] == SHUNTSU ){

			// �ʎq��ʂ̉��Z
			yk->mentsu_count_shuntsu++;

			// �q�X�g�O�������Z
			yk->shuntsu_hist[yk->agari_men_hai[tmp_i]]++;

		}else if(yk->agari_men_stat[tmp_i] == MINSHUN ){

			// �ʎq��ʂ̉��Z
			yk->mentsu_count_minshun++;

			// �q�X�g�O�������Z
			yk->shuntsu_hist[yk->agari_men_hai[tmp_i]]++;

		}else if(yk->agari_men_stat[tmp_i] == ANKO){

			// �ʎq��ʂ̉��Z
			yk->mentsu_count_anko++;

			// �q�X�g�O�������Z
			yk->anko_hist[yk->agari_men_hai[tmp_i]]++;

		}else if(yk->agari_men_stat[tmp_i] == MINKO){

			// �ʎq��ʂ̉��Z
			yk->mentsu_count_minko++;

			// �q�X�g�O�������Z
			yk->anko_hist[yk->agari_men_hai[tmp_i]]++;

		}else if(yk->agari_men_stat[tmp_i] == ANKAN){

			// �ʎq��ʂ̉��Z
			yk->mentsu_count_ankan++;

			// �q�X�g�O�������Z
			yk->anko_hist[yk->agari_men_hai[tmp_i]]++;

		}else if(yk->agari_men_stat[tmp_i] == MINKAN){

			// �ʎq��ʂ̉��Z
			yk->mentsu_count_minkan++;

			// �q�X�g�O�������Z
			yk->anko_hist[yk->agari_men_hai[tmp_i]]++;

		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 06:���v�Z
/* ---------------------------------------------------------------------------------------------- */
void MJSScore::Chk_fu(MJSYakuinfo *yk){

	// ���v�Z
	// https://kinmaweb.jp/mahjong-rule/fukeisan

	// -----------------------------
	// �����̕��v�Z
	// -----------------------------

	// �����̕�
	if (yk->agari_ata_19zi == 2){

		// �����̕�
		yk->atamaFu = 2;

	}else{

		// �����̕�
		yk->atamaFu = 0;

	}

	// -----------------------------
	// �ʎq�̕��v�Z
	// -----------------------------

	// for(int tmp_i = 0; tmp_i < tk->mentu_count; tmp_i++){
	for(int tmp_i = 0; tmp_i < 4; tmp_i++){

		if(yk->agari_men_stat[tmp_i] == ANKO){

			if (yk->agari_men_19zi[tmp_i] == 1 || 
			    yk->agari_men_19zi[tmp_i] == 2 ){

				yk->agari_men_Fu[tmp_i] = 8;

			}else{

				yk->agari_men_Fu[tmp_i] = 4;

			}

		}else if (yk->agari_men_stat[tmp_i] == MINKO){

			if (yk->agari_men_19zi[tmp_i] == 1 || 
			    yk->agari_men_19zi[tmp_i] == 2 ){

				yk->agari_men_Fu[tmp_i] = 4;

			}else{

				yk->agari_men_Fu[tmp_i] = 2;

			}

		}else if (yk->agari_men_stat[tmp_i] == ANKAN){

			if (yk->agari_men_19zi[tmp_i] == 1 || 
			    yk->agari_men_19zi[tmp_i] == 2 ){

				yk->agari_men_Fu[tmp_i] = 32;

			}else{

				yk->agari_men_Fu[tmp_i] = 16;

			}

		}else if (yk->agari_men_stat[tmp_i] == MINKAN){

			if (yk->agari_men_19zi[tmp_i] == 1 || 
			    yk->agari_men_19zi[tmp_i] == 2 ){

				yk->agari_men_Fu[tmp_i] = 16;

			}else{

				yk->agari_men_Fu[tmp_i] = 8;

			}

		}else if ( yk->agari_men_stat[tmp_i] == SHUNTSU || 
                   yk->agari_men_stat[tmp_i] == MINSHUN ){

				yk->agari_men_Fu[tmp_i] = 0;

		}else{

				// �f�o�O�p
				yk->agari_men_Fu[tmp_i] = 99;

		}

	}

	// -----------------------------
	// �ʑO��
	// -----------------------------

	if(yk->menzen_flg      == true  && 
       yk->tsumo_agari_flg == false ){
		yk->menzenFu=10;
	}else{
		yk->menzenFu=0;
	}

	// -----------------------------
	// �҂����v�Z
	// -----------------------------
	if( yk->agari_machi_stat == TANKI || 
	    yk->agari_machi_stat == PENCHAN || 
	    yk->agari_machi_stat == KANCHAN ){

		yk->machiFu=2;

	}else{
		yk->machiFu=0;
	}

	// -----------------------------
	// ���̕�
	// -----------------------------

	if(yk->tsumo_agari_flg == true){
		yk->tsumoFu=2;
	}else{
		yk->tsumoFu=0;
	}

}

/* ---------------------------------------------------------------------------------------------- */
// 07:���m�F
/* ---------------------------------------------------------------------------------------------- */
void MJSScore::Chk_yaku(MJSYakuinfo *yk, int  tehai_hist[]){

	// -----------------------------
	// ������
	// -----------------------------
	yk->yakucount     = 0;
	yk->yakuman_count = 0;
	yk->agari_ply_han = 0;
	yk->agari_ply_mangan_count = 0;
	yk->yakuman_agari_ply_bai=0;

	// -----------------------------
	// �t���O������
	// -----------------------------

	// ��
	for(int tmp_i = 0; tmp_i < YAKUMAN_SHUBETSU_MAX; tmp_i++){
		yk->yakuman_flg[tmp_i] = false;
	}

	// �ʏ��
	for(int tmp_i = 0; tmp_i < YAKU_SHUBETSU_MAX; tmp_i++){
		yk->yaku_flg[tmp_i] = false;
	}

	// -----------------------------
	// ���m�F
	// -----------------------------

	ChkYakuRiich(yk);             // ���[�`
	ChkYakuChitoiIpeko(yk);       // ���Ύq�A��u���A��u�� 
	ChkYakuChinItsu_HonItsu(yk);  // ��F
	ChkYakuAnko(yk);              // �Í�
	ChkYakuChanta(yk);            // �`�����^
	ChkYakuSanshoku(yk);          // �O�F
	ChkYakuItsu(yk);              // ���
	ChkYakuPinfu(yk);             // ���a
	ChkYakuTanyao(yk);            // �^�����I
	ChkYakuYakuhai(yk);           // ��v
	ChkYakuDaisangen(yk);         // ��O���E���O��
	ChkYakuDaisushi(yk);          // ��l��a�E���l��a
	ChkYakuKokushi(yk);           // ���m���o
	ChkYakuChuren(yk,tehai_hist); // ��A��
	ChkYakuTenho(yk);             // �V�a
	ChkYakuEtc(yk);               // ���̑�

	// -----------------------------
	// ���e�[�u���ݒ�
	// -----------------------------

		// �𖞊m�F
		for(int tmp_i = 0; tmp_i < YAKUMAN_SHUBETSU_MAX; tmp_i++){

			// ��ݒ�L��
			if(yk->yakuman_flg[tmp_i] == true){

				// ���e�[�u���ݒ�
				yk->yakuman_count++;

				// �𖞔{�̐ݒ�
				yk->yakuman_bai[tmp_i] = yakuman_bai[tmp_i];

				// �𖞍��v�{���J�E���g
				yk->yakuman_agari_ply_bai = yk->yakuman_agari_ply_bai + yakuman_bai[tmp_i];

			}

		}

	// �ʏ��
	if( yk->yakuman_count == 0 ){

		// �ʏ���m�F
		for(int tmp_i = 0; tmp_i < YAKU_SHUBETSU_MAX; tmp_i++){

			// ��ݒ�L��
			if(yk->yaku_flg[tmp_i] == true){

				// ���e�[�u���ݒ�
				yk->yakucount++;

				// �|���ݒ�
				if(yk->menzen_flg == true){
					// �|���ݒ�(���Ȃ�)
					yk->yaku_han[tmp_i] = yakuhan[tmp_i];
				}else{
					// �|���ݒ�(���Ȃ�)
					yk->yaku_han[tmp_i] = nakihan[tmp_i];
				}

				// ���v�|���̃J�E���g
				yk->agari_ply_han = yk->agari_ply_han + yk->yaku_han[tmp_i];

			}
		}

		// ���шȏ�m�F
		if (yk->agari_ply_han == 5){
			// ����
			yk->agari_ply_mangan_count = 1;
		}else if(yk->agari_ply_han >=6 && yk->agari_ply_han <= 7){
			// ����
			yk->agari_ply_mangan_count = 2;
		}else if(yk->agari_ply_han >=8 && yk->agari_ply_han <= 10){
			// �{��
			yk->agari_ply_mangan_count = 3;
		}else if(yk->agari_ply_han >=11 && yk->agari_ply_han <= 12){
			// �O�{��
			yk->agari_ply_mangan_count = 4;
		}else if(yk->agari_ply_han >=13){
			// ������
			yk->agari_ply_mangan_count = 5;
		}

	}

	// -----------------------------
	// ���̍��v(�s���d���L���m�F��Ɏ��s)
	// -----------------------------

	yk->basefu = 20;

	// ���̍��v
	yk->totalFu = yk->basefu + 
	yk->agari_men_Fu[0] +
	yk->agari_men_Fu[1] +
	yk->agari_men_Fu[2] +
	yk->agari_men_Fu[3] +
	yk->atamaFu +
	yk->menzenFu +
	yk->machiFu +
	yk->tsumoFu;

	// -----------------------------
	// ���̐؂�グ
	// -----------------------------

	if(yk->totalFu % 10 == 0){
		yk->scoreFu = yk->totalFu;
	}else{
		yk->scoreFu = yk->totalFu+10-(yk->totalFu % 10);
	}

}

/* ---------------------------------------------------------------------------------------------- */
// 08:���_�v�Z
/* ---------------------------------------------------------------------------------------------- */
void MJSScore::Chk_score(MJSYakuinfo *yk){

	// -----------------------------
	// ���_ - �a�����_
	// -----------------------------

	// ���̘a���ł��邩�ǂ���
	if (yk->tsumo_agari_flg == true){

		// -----------------------------
		// �c���a���E�e
		// -----------------------------
		if (yk->agari_ply_oya_flg == true){

			// �𖞂̏ꍇ
			if( yk->yakuman_count > 0 ){

					// ���_�ݒ�
					yk->agari_ply_ron       = 0;
					yk->agari_ply_tsumo_oya = 16000*yk->yakuman_agari_ply_bai;
					yk->agari_ply_tsumo_ko  = 0;

			// �ʏ���̏ꍇ
			}else{

				// ���шȏ�
				if(yk->agari_ply_mangan_count > 0){

					// ���_�ݒ�
					yk->agari_ply_ron       = 0;
					yk->agari_ply_tsumo_oya = score_mangan_tsumo_oya[yk->agari_ply_mangan_count-1];
					yk->agari_ply_tsumo_ko  = 0;

				// ���і���
				}else{
					// �`���m�F
					if(yk->agari_stat == AGARI_CHITOI){
						// ���_�ݒ�(���Ύq)
						yk->agari_ply_ron       = 0;
						yk->agari_ply_tsumo_oya = score_chitoi_tsumo_oya[yk->agari_ply_han-1];
						yk->agari_ply_tsumo_ko  = 0;
					}else{
						// ���_�ݒ�(�ʏ�)
						yk->agari_ply_ron       = 0;
						yk->agari_ply_tsumo_oya = score_tsumo_oya[yk->agari_ply_han-1][(yk->scoreFu-20)/10];
						yk->agari_ply_tsumo_ko  = 0;
					}
				}
			}

		// -----------------------------
		// �c���a���E�q
		// -----------------------------
		}else{

			// �𖞂̏ꍇ
			if( yk->yakuman_count > 0 ){

					// ���_�ݒ�
					yk->agari_ply_ron       = 0;
					yk->agari_ply_tsumo_oya = 16000*yk->yakuman_agari_ply_bai;
					yk->agari_ply_tsumo_ko  = 8000*yk->yakuman_agari_ply_bai;

			// �ʏ���̏ꍇ
			}else{

				// ���шȏ�
				if(yk->agari_ply_mangan_count > 0){

					// ���_�ݒ�
					yk->agari_ply_ron       = 0;
					yk->agari_ply_tsumo_oya = score_mangan_tsumo_oya[yk->agari_ply_mangan_count-1];
					yk->agari_ply_tsumo_ko  = score_mangan_tsumo_ko[yk->agari_ply_mangan_count-1];

				// ���і���
				}else{
					// �`���m�F
					if(yk->agari_stat == AGARI_CHITOI){
						// ���_�ݒ�(���Ύq)
						yk->agari_ply_ron       = 0;
						yk->agari_ply_tsumo_oya = score_chitoi_tsumo_oya[yk->agari_ply_han-1];
						yk->agari_ply_tsumo_ko  = score_chitoi_tsumo_ko[yk->agari_ply_han-1];
					}else{
						// ���_�ݒ�(�ʏ�)
						yk->agari_ply_ron       = 0;
						yk->agari_ply_tsumo_oya = score_tsumo_oya[yk->agari_ply_han-1][(yk->scoreFu-20)/10];
						yk->agari_ply_tsumo_ko  = score_tsumo_ko[yk->agari_ply_han-1][(yk->scoreFu-20)/10];
					}
				}
			}
		}

	}else{

		// -----------------------------
		// �����a���E�e
		// -----------------------------
		if (yk->agari_ply_oya_flg == true){

			// �𖞂̏ꍇ
			if( yk->yakuman_count > 0 ){

					// ���_�ݒ�
					yk->agari_ply_ron       = 48000*yk->yakuman_agari_ply_bai;
					yk->agari_ply_tsumo_oya = 0;
					yk->agari_ply_tsumo_ko  = 0;

			// �ʏ���̏ꍇ
			}else{

				// ���шȏ�
				if(yk->agari_ply_mangan_count > 0){

					// ���_�ݒ�
					yk->agari_ply_ron       = score_mangan_ron_oya[yk->agari_ply_mangan_count-1];
					yk->agari_ply_tsumo_oya = 0;
					yk->agari_ply_tsumo_ko  = 0;

				// ���і���
				}else{
					// �`���m�F
					if(yk->agari_stat == AGARI_CHITOI){
						// ���_�ݒ�(���Ύq)
						yk->agari_ply_ron       = score_chitoi_ron_oya[yk->agari_ply_han-1];
						yk->agari_ply_tsumo_oya = 0;
						yk->agari_ply_tsumo_ko  = 0;
					}else{
						// ���_�ݒ�(�ʏ�)
						yk->agari_ply_ron       = score_ron_oya[yk->agari_ply_han-1][(yk->scoreFu-20)/10];
						yk->agari_ply_tsumo_oya = 0;
						yk->agari_ply_tsumo_ko  = 0;
					}
				}
			}

		// -----------------------------
		// �����a���E�q
		// -----------------------------
		}else{

			// �𖞂̏ꍇ
			if( yk->yakuman_count > 0 ){

					// ���_�ݒ�
					yk->agari_ply_ron       = 32000*yk->yakuman_agari_ply_bai;
					yk->agari_ply_tsumo_oya = 0;
					yk->agari_ply_tsumo_ko  = 0;

			// �ʏ���̏ꍇ
			}else{

				// ���шȏ�
				if(yk->agari_ply_mangan_count > 0){

					// ���_�ݒ�(����)
					yk->agari_ply_ron       = score_mangan_ron_ko[yk->agari_ply_mangan_count-1];
					yk->agari_ply_tsumo_oya = 0;
					yk->agari_ply_tsumo_ko  = 0;

				// ���і���
				}else{
					// �`���m�F
					if(yk->agari_stat == AGARI_CHITOI){
						// ���_�ݒ�(���Ύq)
						yk->agari_ply_ron       = score_chitoi_tsumo_ko[yk->agari_ply_han-1];
						yk->agari_ply_tsumo_oya = 0;
						yk->agari_ply_tsumo_ko  = 0;
					}else{
						// ���_�ݒ�(�ʏ�)
						yk->agari_ply_ron       = score_ron_ko[yk->agari_ply_han-1][(yk->scoreFu-20)/10];
						yk->agari_ply_tsumo_oya = 0;
						yk->agari_ply_tsumo_ko  = 0;
					}
				}
			}

		}

	}

	// -----------------------------
	// ���_ - �v���[���[���Ƃ̐��Z
	// -----------------------------

	// ������
	yk->kyoku_score[0] = 0;
	yk->kyoku_score[1] = 0;
	yk->kyoku_score[2] = 0;
	yk->kyoku_score[3] = 0;

	// ���̃����m�F
	if (yk->tsumo_agari_flg == true){

		if (yk->agari_ply_oya_flg == true){

			// �c���a���E�e
			for(int tmp_i = 0; tmp_i < 4; tmp_i++){
				if(tmp_i == yk->agari_ply_num){
					yk->kyoku_score[tmp_i] = yk->agari_ply_tsumo_oya*3;
				}else{
					yk->kyoku_score[tmp_i] = yk->agari_ply_tsumo_oya*(-1);
				}
			}

		}else{

			// �c���a���E�q
			for(int tmp_i = 0; tmp_i < 4; tmp_i++){
				if(tmp_i == yk->agari_ply_num){
					yk->kyoku_score[tmp_i] = yk->agari_ply_tsumo_oya+yk->agari_ply_tsumo_ko*2;
				}else{
					if(yk->ie[tmp_i]==0){
						yk->kyoku_score[tmp_i] = yk->agari_ply_tsumo_oya*(-1);
					}else{
						yk->kyoku_score[tmp_i] = yk->agari_ply_tsumo_ko*(-1);
					}
				}
			}

		}

	}else{

			// �����a��
			yk->kyoku_score[yk->agari_ply_num] = yk->agari_ply_ron;
			yk->kyoku_score[yk->furikomi_ply_num]  = yk->agari_ply_ron*(-1);

	}

}

/* ---------------------------------------------------------------------------------------------- */
// �h�������̊m�F
/* ---------------------------------------------------------------------------------------------- */
void MJSScore::Chk_tehai_dora_count(MJSYakuinfo *yk, int dora_count, int dora[], int ura_dora[]){

	// ������
	yk->agari_dora_count = 0; 
	yk->agari_uradora_count = 0;

	// �h���J�E���g
	for(int tmp_dora_i = 0; tmp_dora_i < dora_count; tmp_dora_i++){

		// �\�h���J�E���g
		sub_tehai_dora_count(yk, Get_dora_hai(dora[tmp_dora_i]), true);

		// ���[�`�Ȃ�΁A���h���J�E���g
		if(yk->riichi_flg == true){
			sub_tehai_dora_count(yk, Get_dora_hai(ura_dora[tmp_dora_i]), false);
		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// �h�������̊m�F
/* ---------------------------------------------------------------------------------------------- */
void MJSScore::sub_tehai_dora_count(MJSYakuinfo *yk, int dora_hai, bool omote_dora_type){

	// ���h���J�E���g
	if(yk->agari_ata_hai == dora_hai){
		if(omote_dora_type == true){
			yk->agari_dora_count=yk->agari_dora_count+2;
		}else{
			yk->agari_uradora_count=yk->agari_uradora_count+2;
		}
	}

	// �ʎq�h���J�E���g
	for(int tmp_i = 0; tmp_i < 4; tmp_i++){

		// �A���R�̏ꍇ
		if ( yk->agari_men_stat[tmp_i] == ANKO    || yk->agari_men_stat[tmp_i] == MINKO  ){

			// �h���J�E���g
			if(yk->agari_men_hai[tmp_i] == dora_hai){
				if(omote_dora_type == true){
					yk->agari_dora_count=yk->agari_dora_count+3;
				}else{
					yk->agari_uradora_count=yk->agari_uradora_count+3;
				}
			}

		// �J���c�̏ꍇ
		}else if ( yk->agari_men_stat[tmp_i] == ANKAN   || yk->agari_men_stat[tmp_i] == MINKAN ){

			// �h���J�E���g
			if(yk->agari_men_hai[tmp_i] == dora_hai){
				if(omote_dora_type == true){
					yk->agari_dora_count=yk->agari_dora_count+4;
				}else{
					yk->agari_uradora_count=yk->agari_uradora_count+4;
				}
			}

		// ���q�̏ꍇ
		}else if ( yk->agari_men_stat[tmp_i] == SHUNTSU || yk->agari_men_stat[tmp_i] == MINSHUN){

			// �h���J�E���g
			if( yk->agari_men_hai[tmp_i]     == dora_hai ||
			    yk->agari_men_hai[tmp_i] + 1 == dora_hai ||
			    yk->agari_men_hai[tmp_i] + 2 == dora_hai ){
				if(omote_dora_type == true){
					yk->agari_dora_count=yk->agari_dora_count+1;
				}else{
					yk->agari_uradora_count=yk->agari_uradora_count+1;
				};
			}

		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// �h���\���v���h���v�̕ϊ�
/* ---------------------------------------------------------------------------------------------- */
int MJSScore::Get_dora_hai(int dora_hai){

	// �h���\���v���h���v�̕ϊ�
	if(dora_hai == 9){
		return 1;
	}else if(dora_hai == 19){
		return 11;
	}else if(dora_hai == 29){
		return 21;
	}else if(dora_hai == 34){
		return 31;
	}else if(dora_hai == 37){
		return 35;
	// �f�o�O�p
	}else if(dora_hai < 1 || dora_hai > 37){
		return 0;
	}else{
		return dora_hai+1;
	}

}

/* ---------------------------------------------------------------------------------------------- */
// ���[�`�n
/* ---------------------------------------------------------------------------------------------- */
void MJSScore::ChkYakuRiich(MJSYakuinfo *yk){

	// -----------------------------------------------------------------------
	// 01: ���[�`
	// -----------------------------------------------------------------------

	if (yk->riichi_flg == true){
		// ��flg�L����
		yk->yaku_flg[RIICH] = true;
	}

	// -----------------------------------------------------------------------
	// 02: �_�u�����[�`
	// -----------------------------------------------------------------------

	if (yk->double_riichi_flg == true){
		// ��flg�L����
		yk->yaku_flg[RIICH]  = false;
		yk->yaku_flg[WRIICH] = true;
	}

	// -----------------------------------------------------------------------
	// 03: �ꔭ
	// -----------------------------------------------------------------------

	if (yk->riichi_ippatsu_flg == true){
		// ��flg�L����
		yk->yaku_flg[IPPATSU] = true;
	}

}

/* ---------------------------------------------------------------------------------------------- */
// ���Ύq�A��u���A��u�� 
/* ---------------------------------------------------------------------------------------------- */
void MJSScore::ChkYakuChitoiIpeko(MJSYakuinfo *yk){

	/* ----------------------------------------------------------------------- */
	// ��u���E��u��
	/* ----------------------------------------------------------------------- */
	for(int tmp_i = 1; tmp_i < 28; tmp_i++){

		// ��u���L����
		if ( yk->shuntsu_hist[tmp_i] > 1 && 
		     yk->menzen_flg == true &&
			 yk->yaku_flg[IPEKO] == true){

			// ��u���L����
			yk->yaku_flg[IPEKO] = false;
			yk->yaku_flg[RYANPEKO] = true;
			break;

		// ��u���̗L�����m�F
		}else if ( yk->shuntsu_hist[tmp_i] > 1 && yk->menzen_flg == true ){
			// ��flg�L����
			yk->yaku_flg[IPEKO] = true;

		// ���Ύq�̗L�����m�F
		}else if(yk->agari_stat == AGARI_CHITOI){

			// ��flg�L����
			yk->yaku_flg[CHITOI] = true;

		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// ����n
/* ---------------------------------------------------------------------------------------------- */
void MJSScore::ChkYakuChinItsu_HonItsu(MJSYakuinfo *yk){

	// �ʏ�`��
	if(yk->agari_stat == AGARI_NORMAL){

		// -----------------------------------------------------------------------
		// 04: ����F
		// -----------------------------------------------------------------------
		if ( yk->mentsu_count_manzu == 5 ||
		     yk->mentsu_count_pinzu == 5 ||
		     yk->mentsu_count_souzu == 5 ){

			// ��flg�L����
			yk->yaku_flg[CHINISO]=true;

		// -----------------------------------------------------------------------
		// 10: ����F
		// -----------------------------------------------------------------------
		}else if( yk->mentsu_count_zihai == 5){

			// ��flg�L����
			yk->yakuman_flg[TSUISO]=true;

		// -----------------------------------------------------------------------
		// 04: ����F
		// -----------------------------------------------------------------------
		}else if( yk->mentsu_count_manzu + yk->mentsu_count_zihai == 5 ||
		          yk->mentsu_count_pinzu + yk->mentsu_count_zihai == 5 ||
		          yk->mentsu_count_souzu + yk->mentsu_count_zihai == 5 ){

			// ��flg�L����
			yk->yaku_flg[HONISO]=true;

		// -----------------------------------------------------------------------
		// 12: �Έ�F
		// -----------------------------------------------------------------------

		}

	// ���Ύq�`��
	}else if(yk->agari_stat == AGARI_CHITOI){

		// -----------------------------------------------------------------------
		// 04: ����F
		// -----------------------------------------------------------------------
		if ( yk->mentsu_count_manzu == 7 ||
		     yk->mentsu_count_pinzu == 7 ||
		     yk->mentsu_count_souzu == 7 ){

			// ��flg�L����
			yk->yaku_flg[CHINISO]=true;

		// -----------------------------------------------------------------------
		// 10: ����F
		// -----------------------------------------------------------------------
		}else if( yk->mentsu_count_zihai == 7){

			// ��flg�L����
			yk->yakuman_flg[TSUISO]=true;

		// -----------------------------------------------------------------------
		// 04: ����F
		// -----------------------------------------------------------------------
		}else if( yk->mentsu_count_manzu + yk->mentsu_count_zihai == 7 ||
		          yk->mentsu_count_pinzu + yk->mentsu_count_zihai == 7 ||
		          yk->mentsu_count_souzu + yk->mentsu_count_zihai == 7 ){

			// ��flg�L����
			yk->yaku_flg[HONISO]=true;
		}
	}


}

/* ---------------------------------------------------------------------------------------------- */
// �Í��n
/* ---------------------------------------------------------------------------------------------- */
void MJSScore::ChkYakuAnko(MJSYakuinfo *yk){

	// -----------------------------------------------------------------------
	// ��14: �l�Ȏq
	// -----------------------------------------------------------------------
	if ( yk->mentsu_count_ankan  +
	     yk->mentsu_count_minkan == 4 ){

		// ��flg�L����
		yk->yakuman_flg[SUKANTSU] = true;

	}

	// -----------------------------------------------------------------------
	// 13: �O�Ȏq
	// -----------------------------------------------------------------------
	if ( yk->mentsu_count_ankan  +
	     yk->mentsu_count_minkan == 3 ){

		// ��flg�L����
		yk->yaku_flg[SANKANTSU] = true;

	}

	// -----------------------------------------------------------------------
	// ��15: �l�Í�
	// -----------------------------------------------------------------------
	if ( yk->mentsu_count_anko  +
	     yk->mentsu_count_ankan == 4 ){

		// ��flg�L����
		yk->yakuman_flg[SUANKO]=true;

	}

	// -----------------------------------------------------------------------
	// 14: �O�Í�
	// -----------------------------------------------------------------------
	if ( yk->mentsu_count_anko  +
	     yk->mentsu_count_ankan == 3 ){

		// ��flg�L����
		yk->yaku_flg[SANANKO] = true;

	}

	// -----------------------------------------------------------------------
	// 15: �΁X�a
	// -----------------------------------------------------------------------
	if ( yk->mentsu_count_anko  +
	     yk->mentsu_count_minko +
	     yk->mentsu_count_ankan +
	     yk->mentsu_count_minkan == 4 ){

		// ��flg�L����
		yk->yaku_flg[TOITOI] = true;

	}

}

/* ---------------------------------------------------------------------------------------------- */
// ���S��
/* ---------------------------------------------------------------------------------------------- */
void MJSScore::ChkYakuChanta(MJSYakuinfo *yk){


	// �ʏ�`��
	if(yk->agari_stat == AGARI_NORMAL){

		/* ----------------------------------------------------------------------- */
		// �`�����^�n(�ʏ��)
		/* ----------------------------------------------------------------------- */
		if (yk->mentsu_count_19zi == 5){
			// �S�ăA���R�̏ꍇ
			if ( yk->mentsu_count_anko  +
			     yk->mentsu_count_minko +
			     yk->mentsu_count_ankan +
			     yk->mentsu_count_minkan == 4 ){
				// ���v���m�F
				if(yk->mentsu_count_zihai == 0){
					// ��flg�L����
					yk->yaku_flg[JUNCHAN] = true;
				}else{
					// ��flg�L����
					yk->yaku_flg[CHANTA] = true;
				}
			// ���q������ꍇ
			}else{
				// ���v���m�F
				if(yk->mentsu_count_zihai == 0){
					// ��flg�L����
					yk->yakuman_flg[CHINROTO]=true;
				}else{
					// ��flg�L����
					yk->yaku_flg[HONROTO] = true;
				}
			}
		}

	// ���Ύq�`��
	}else if(yk->agari_stat == AGARI_CHITOI){

		/* ----------------------------------------------------------------------- */
		// �`�����^�n(���Ύq)
		/* ----------------------------------------------------------------------- */
		if (yk->mentsu_count_19zi == 7){
			// ��flg�L����
			yk->yaku_flg[HONROTO] = true;
		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// �O�F�n
/* ---------------------------------------------------------------------------------------------- */
void MJSScore::ChkYakuSanshoku(MJSYakuinfo *yk){

	// -----------------------------------------------------------------------
	// 11: �O�F����
	// 12: �O�F����
	// -----------------------------------------------------------------------
	for(int i = 0; i < 9; i++){

		// �O�F�����m�F
		if ( yk->shuntsu_hist[1+i]  > 0 &&
		     yk->shuntsu_hist[11+i] > 0 &&
		     yk->shuntsu_hist[21+i] > 0 ){

			// ��flg�L����
			yk->yaku_flg[SANDOJUN] = true;

		}

		// �O�F�����m�F
		if ( yk->anko_hist[1+i]  > 0 &&
		     yk->anko_hist[11+i] > 0 &&
		     yk->anko_hist[21+i] > 0 ){

			// ��flg�L����
			yk->yaku_flg[SANDOKOU] = true;

		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// ��ʌn
/* ---------------------------------------------------------------------------------------------- */
void MJSScore::ChkYakuItsu(MJSYakuinfo *yk){

	// -----------------------------------------------------------------------
	// 10: ��C�ʊ�
	// -----------------------------------------------------------------------
	for(int i = 0; i < 3; i++){
		if ( yk->shuntsu_hist[1+10*i] > 0 &&
		     yk->shuntsu_hist[4+10*i] > 0 &&
		     yk->shuntsu_hist[7+10*i] > 0 ){

			// ��flg�L����
			yk->yaku_flg[ITSU] = true;

		}
	}

}

/* ---------------------------------------------------------------------------------------------- */
// ���a�n
/* ---------------------------------------------------------------------------------------------- */
void MJSScore::ChkYakuPinfu(MJSYakuinfo *yk){

	// -----------------------------------------------------------------------
	// 10: ���a
	// -----------------------------------------------------------------------

	// ���m�F
	if(yk->menzen_flg == false ){
		return ;
	}

	// ���q���̊m�F
	if( (yk->mentsu_count_shuntsu != 4 ) && 
	    (yk->mentsu_count_shuntsu != 3 || yk->mentsu_count_minshun != 1 )
	){
		return ;
	}

	// �����̖�v�m�F��agari_ata_19zi=2�̏ꍇ�͕��a�ɂȂ�Ȃ�
	if( yk->agari_ata_19zi == 2){
		return ;
	}

	// ���ʂ̊m�F
	if(yk->agari_machi_stat != RYANMEN ){
		return ;
	}

	// ��flg�L����
	yk->yaku_flg[PINFU] = true;

	// ���a�̎��̕���0��
	yk->tsumoFu=0;

}

/* ---------------------------------------------------------------------------------------------- */
// �^�����I�n
/* ---------------------------------------------------------------------------------------------- */
void MJSScore::ChkYakuTanyao(MJSYakuinfo *yk){

	/* ----------------------------------------------------------------------- */
	// 10: �^�����I
	/* ----------------------------------------------------------------------- */
	if (yk->mentsu_count_chunchan == 5){

		// ��flg�L����
		yk->yaku_flg[TANYAO] = true;

	}
}


/* ---------------------------------------------------------------------------------------------- */
// ��v�n
/* ---------------------------------------------------------------------------------------------- */
void MJSScore::ChkYakuYakuhai(MJSYakuinfo *yk){

	// -----------------------------------------------------------------------
	// 21: �ꕗ�v
	// -----------------------------------------------------------------------
	if ( yk->anko_hist[yk->agari_ply_bakaze] > 0 ){

		// ��flg�L����
		yk->yaku_flg[BAKAZE] = true;

	}

	/* ----------------------------------------------------------------------- */
	// 22: �����v
	/* ----------------------------------------------------------------------- */
	if ( yk->anko_hist[yk->agari_ply_zikaze] > 0 ){

		// ��flg�L����
		yk->yaku_flg[ZIKAZE] = true;

	}

	// -----------------------------------------------------------------------
	// 23: �O���v��
	// -----------------------------------------------------------------------
	if ( yk->anko_hist[HAKUNUM] > 0 ){

		// ��flg�L����
		yk->yaku_flg[YAKUHAIHAKU] = true;

	}

	// -----------------------------------------------------------------------
	// 24: �O���v��
	// -----------------------------------------------------------------------
	if ( yk->anko_hist[HATSUNUM] > 0 ){

		// ��flg�L����
		yk->yaku_flg[YAKUHAIHATSU] = true;

	}

	// -----------------------------------------------------------------------
	// 25: �O���v��
	// -----------------------------------------------------------------------
	if ( yk->anko_hist[CHUNNUM] > 0){

		// ��flg�L����
		yk->yaku_flg[YAKUHAICHUN] = true;

	}

}

/* ---------------------------------------------------------------------------------------------- */
// ��O���E���O��
/* ---------------------------------------------------------------------------------------------- */
void MJSScore::ChkYakuDaisangen(MJSYakuinfo *yk){

	/* ----------------------------------------------------------------------- */
	// ���O���E��(HAKUNUM)�A�^�}
	/* ----------------------------------------------------------------------- */
	if (( yk->agari_ata_hai == HAKUNUM ) &&
		( yk->anko_hist[HATSUNUM] > 0 ) &&
		( yk->anko_hist[CHUNNUM]  > 0 ) ){

		// ��flg�L����
		yk->yaku_flg[SHOSANGEN]=true;
	}

	/* ----------------------------------------------------------------------- */
	// ���O���E��(HAKUNUM)�A�^�}
	/* ----------------------------------------------------------------------- */
	if (( yk->agari_ata_hai == HATSUNUM ) &&
		( yk->anko_hist[HAKUNUM] > 0 ) &&
		( yk->anko_hist[CHUNNUM]  > 0 ) ){

		// ��flg�L����
		yk->yaku_flg[SHOSANGEN]=true;
	}

	/* ----------------------------------------------------------------------- */
	// ���O���E��(HAKUNUM)�A�^�}
	/* ----------------------------------------------------------------------- */
	if (( yk->agari_ata_hai == CHUNNUM ) &&
		( yk->anko_hist[HAKUNUM]   > 0 ) &&
		( yk->anko_hist[HATSUNUM]  > 0 ) ){

		// ��flg�L����
		yk->yaku_flg[SHOSANGEN]=true;
	}

	/* ----------------------------------------------------------------------- */
	// ��O��
	/* ----------------------------------------------------------------------- */
	if (( yk->anko_hist[HAKUNUM]  > 0 ) &&
		( yk->anko_hist[HATSUNUM] > 0 ) &&
		( yk->anko_hist[CHUNNUM]  > 0 ) ){

		// ��flg�L����
		yk->yakuman_flg[DAISANGEN]=true;

	}

}

/* ---------------------------------------------------------------------------------------------- */
// ��l��a�E���l��a
/* ---------------------------------------------------------------------------------------------- */
void MJSScore::ChkYakuDaisushi(MJSYakuinfo *yk){

	/* ----------------------------------------------------------------------- */
	// ���l��a�E���A�^�}
	/* ----------------------------------------------------------------------- */

	if (( yk->agari_ata_hai == TONNUM ) &&
		( yk->anko_hist[NANNUM] > 0 ) &&
		( yk->anko_hist[SHANUM] > 0 ) &&
		( yk->anko_hist[PEINUM] > 0 ) ){

		// ��flg�L����
		yk->yakuman_flg[SHOSUSHI]=true;

	}

	/* ----------------------------------------------------------------------- */
	// ���l��a�E��A�^�}
	/* ----------------------------------------------------------------------- */

	if (( yk->agari_ata_hai == NANNUM ) &&
		( yk->anko_hist[TONNUM] > 0 ) &&
		( yk->anko_hist[SHANUM] > 0 ) &&
		( yk->anko_hist[PEINUM] > 0 ) ){

		// ��flg�L����
		yk->yakuman_flg[SHOSUSHI]=true;

	}

	/* ----------------------------------------------------------------------- */
	// ���l��a�E���A�^�}
	/* ----------------------------------------------------------------------- */

	if (( yk->agari_ata_hai == SHANUM ) &&
		( yk->anko_hist[TONNUM] > 0 ) &&
		( yk->anko_hist[NANNUM] > 0 ) &&
		( yk->anko_hist[PEINUM] > 0 ) ){

		// ��flg�L����
		yk->yakuman_flg[SHOSUSHI]=true;

	}

	/* ----------------------------------------------------------------------- */
	// ���l��a�E�k�A�^�}
	/* ----------------------------------------------------------------------- */

	if (( yk->agari_ata_hai == PEINUM ) &&
		( yk->anko_hist[TONNUM] > 0 ) &&
		( yk->anko_hist[NANNUM] > 0 ) &&
		( yk->anko_hist[SHANUM] > 0 ) ){

		// ��flg�L����
		yk->yakuman_flg[SHOSUSHI]=true;

	}

	// -----------------------------------------------------------------------
	// ��07: ��l��a
	// -----------------------------------------------------------------------

	if (( yk->anko_hist[TONNUM] > 0 ) &&
		( yk->anko_hist[NANNUM] > 0 ) &&
		( yk->anko_hist[SHANUM] > 0 ) &&
		( yk->anko_hist[PEINUM] > 0 ) ){

		// ��flg�L����
		yk->yakuman_flg[DAISUSHI]=true;

	}

}

/* ---------------------------------------------------------------------------------------------- */
// ���m���o
/* ---------------------------------------------------------------------------------------------- */
void MJSScore::ChkYakuKokushi(MJSYakuinfo *yk){
/*
	// ��z�`�������m�ł���̂��H
	if(yk->agari_stat == AGARI_KOKUSHI){
		// 13�ʊm�F
		if ( yk->ply_act_tehai[yk->agari_hai] > 0){
			// ��flg�L����
			yk->yakuman_flg[KOKUSHI13MEN] = true;
		}else{
			// ��flg�L����
			yk->yakuman_flg[KOKUSHI] = true;
		}
	}
*/
}

/* ---------------------------------------------------------------------------------------------- */
// ��A��
/* ---------------------------------------------------------------------------------------------- */
void MJSScore::ChkYakuChuren(MJSYakuinfo *yk, int tehai_hist[]){

	// �ϐ��ݒ�
	bool agari_flg;

	/* ----------------------------------------------------------------------- */
	// ��03: ��A�󓕁E�ݎq
	/* ----------------------------------------------------------------------- */

	// �a���t���O������
	agari_flg = true;

	// �����Ɩʎq4�������ׂē���̍��q�ł��邱��
	if ( yk->mentsu_count_manzu != 5){
		agari_flg = false ;
	}

	// ��v�Ƌ�v��3���ȏ゠�邱��
    if ( (tehai_hist[MAN1NUM] < 3) || 
	     (tehai_hist[MAN9NUM] < 3) ){
		agari_flg = false ;
	}

	// ��v�����v�܂őS�đ����Ă��邱��
	for (int tmp_i = 1; tmp_i < 10; tmp_i++) {
        if (tehai_hist[tmp_i] == 0){
			agari_flg = false ;
		}
    }

	// �a���m�F
	if (agari_flg == true){

		// ��flg�L����
		yk->yakuman_flg[CHUREN]=true;

	}

	/* ----------------------------------------------------------------------- */
	// ��03: ��A�󓕁E���q
	/* ----------------------------------------------------------------------- */

	// �a���t���O������
	agari_flg = true;

	// �����Ɩʎq4�������ׂē���̍��q�ł��邱��
	if ( yk->mentsu_count_pinzu != 5){
		agari_flg = false ;
	}

	// ��v�Ƌ�v��3���ȏ゠�邱��
    if ( (tehai_hist[PIN1NUM] < 3) || 
	     (tehai_hist[PIN9NUM] < 3) ){
		agari_flg = false ;
	}

	// ��v�����v�܂őS�đ����Ă��邱��
	for (int tmp_i = 11; tmp_i < 20; tmp_i++) {
        if (tehai_hist[tmp_i] == 0){
			agari_flg = false ;
		}
    }

	// �a���m�F
	if (agari_flg == true){

		// ��flg�L����
		yk->yakuman_flg[CHUREN]=true;

	}

	/* ----------------------------------------------------------------------- */
	// ��03: ��A�󓕁E���q
	/* ----------------------------------------------------------------------- */

	// �a���t���O������
	agari_flg = true;

	// �����Ɩʎq4�������ׂē���̍��q�ł��邱��
	if ( yk->mentsu_count_souzu != 5){
		agari_flg = false ;
	}

	// ��v�Ƌ�v��3���ȏ゠�邱��
    if ( (tehai_hist[SOU1NUM] < 3) || 
	     (tehai_hist[SOU9NUM] < 3) ){

		// �a���t���O������
		agari_flg = false ;
	}

	// ��v�����v�܂őS�đ����Ă��邱��
	for (int tmp_i = 21; tmp_i < 30; tmp_i++) {
        if (tehai_hist[tmp_i] == 0){
			agari_flg = false ;
		}
    }

	// �a���m�F
	if (agari_flg == true){

		// ��flg�L����
		yk->yakuman_flg[CHUREN]=true;

	}

}

/* ---------------------------------------------------------------------------------------------- */
// �V�a
/* ---------------------------------------------------------------------------------------------- */
void MJSScore::ChkYakuTenho(MJSYakuinfo *yk){

	// -----------------------------------------------------------------------
	// ��01: �V�a
	// -----------------------------------------------------------------------
	if(yk->agari_ply_tsumo_count == 1 && yk->tsumo_agari_flg == true){

		// ��flg�L����
		// yk->yakuman_flg[TENHO]=true;

	}

	// -----------------------------------------------------------------------
	// ��02: �n�a
	// -----------------------------------------------------------------------
	if(yk->agari_ply_tsumo_count == 0 && yk->tsumo_agari_flg == false){

		// ��flg�L����
		// yk->yakuman_flg[CHIHO]=true;

	}

}

/* ---------------------------------------------------------------------------------------------- */
// ���̑�����
/* ---------------------------------------------------------------------------------------------- */
void MJSScore::ChkYakuEtc(MJSYakuinfo *yk){

	// -----------------------------------------------------------------------
	// 29: ��O�����̘a
	// -----------------------------------------------------------------------

	if(yk->tsumo_agari_flg == true && 
	   yk->menzen_flg      == true ){

		// ��flg�L����
		yk->yaku_flg[TSUMO] = true;

	}

	// -----------------------------
	// 31: �h��
	// -----------------------------
	if( yk->agari_dora_count > 0 ){

		// ��flg�L����
		yk->yaku_flg[DORA] = true;

		// �|���ݒ�
		yakuhan[DORA] = yk->agari_dora_count;
		nakihan[DORA] = yakuhan[DORA];

	}

	// -----------------------------
	// 32: ���h��
	// -----------------------------
	if( yk->agari_uradora_count > 0 ){

		// ��flg�L����
		yk->yaku_flg[URADORA] = true;

		// �|���ݒ�
		yakuhan[URADORA] = yk->agari_uradora_count;
		nakihan[URADORA] = yakuhan[URADORA];

	}

	// -----------------------------
	// 33: �Ԕv
	// -----------------------------
	if(yk->agari_aka_count[0] > 0 ||
	   yk->agari_aka_count[1] > 0 ||
	   yk->agari_aka_count[2] > 0 ){

		// ��flg�L����
		yk->yaku_flg[AKAHAI] = true;

		// �|���ݒ�
		yakuhan[AKAHAI] = yk->agari_aka_count[0] + 
		                  yk->agari_aka_count[1] +
		                  yk->agari_aka_count[2] ;
		nakihan[AKAHAI] = yakuhan[AKAHAI];

	}

}

/* ---------------------------------------------------------------------------------------------- */
// �r�v�����_�ݒ�
/* ---------------------------------------------------------------------------------------------- */
void MJSScore::SetHowanpaiScore(MJSYakuinfo *yk){

	// -----------------------------------------------------------
	// �X�e�[�^�X��`
	// -----------------------------------------------------------
	yk->ryukyoku_stat = HOWANPAI;

	// -----------------------------------------------------------
	// ���_�ݒ�
	// -----------------------------------------------------------
	for(int tmp_num = 0; tmp_num< PLAYER_MAX; tmp_num++){
		if(yk->ply_tempai_count == 0 || yk->ply_tempai_count == 4){
			yk->kyoku_score[tmp_num] = 0;
		}else if(yk->ply_tempai_count == 1 && yk->ply_tempai_flg[tmp_num] == true){
			yk->kyoku_score[tmp_num] = 3000;
		}else if(yk->ply_tempai_count == 1 && yk->ply_tempai_flg[tmp_num] == false){
			yk->kyoku_score[tmp_num] = -1000;
		}else if(yk->ply_tempai_count == 2 && yk->ply_tempai_flg[tmp_num] == true){
			yk->kyoku_score[tmp_num] = 1500;
		}else if(yk->ply_tempai_count == 2 && yk->ply_tempai_flg[tmp_num] == false){
			yk->kyoku_score[tmp_num] = -1500;
		}else if(yk->ply_tempai_count == 3 && yk->ply_tempai_flg[tmp_num] == true){
			yk->kyoku_score[tmp_num] = 1000;
		}else if(yk->ply_tempai_count == 3 && yk->ply_tempai_flg[tmp_num] == false){
			yk->kyoku_score[tmp_num] = -3000;
		}
	}

}

/* ---------------------------------------------------------------------------------------------- */
// �\�[�X�I��
/* ---------------------------------------------------------------------------------------------- */
