/* ---------------------------------------------------------------------------------------------- 
 * 
 * �v���O�����T�v �F �����疃��(Ver0.1.2�F�J����)
 * �o�[�W����     �F 0.1.2.1.224(���F�v�E���F�v�̕\������)
 * �v���O������   �F mjs.exe
 * �t�@�C����     �F dispparts.cpp
 * �N���X��       �F MJSDisplayParts
 * �����T�v       �F �p�[�c�`�ʃN���X
 * ����쐬��     �F 2023/05/20 10:59:12
 * Ver0.1.2�쐬�� �F 2023/05/20 10:59:12
 * Ver0.1.3.0pre  �F 2024/03/19 23:55:27
 * Ver0.1.3.1pre  �F 2024/04/05 19:50:22
 * �ŏI�X�V��     �F 2024/11/02 15:07:30
 * 
 * Copyright (c) 2010-2024 TechMileStoraJP, All rights reserved.
 * 
 * ---------------------------------------------------------------------------------------------- */

#include "dispparts.h"

/* ---------------------------------------------------------------------------------------------- */
// ��ʏ���������
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispPartsInit(){

	// ----------------------------------------
	// ���O����
	// ----------------------------------------

	// �v�ԍ����u��
	int tmpPaiImgNum[] = {

		37,
		 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
		10,11,12,13,14,15,16,17,18,19,
		20,21,22,23,24,25,26,27,28,29,
		30,31,32,33,34,35,36,37,37,37,

	};

	// �v�ԍ��i�[
	for(int i = 0; i < PAI_MAX; i++){
		// �v�ԍ����i�[
		PaiImgNum[i] = tmpPaiImgNum[i];
	}

	// -----------------------------
	// �v���[�g������`
	// -----------------------------

	wsprintf(plt_name[PLT_RIICHI]   , "���[�`");
	wsprintf(plt_name[PLT_PON]      , "�|�@��");
	wsprintf(plt_name[PLT_KAN]      , "�J�@��");
	wsprintf(plt_name[PLT_CHI]      , "�`�@�[");
	wsprintf(plt_name[PLT_AGARI]    , "�a�@��");
	wsprintf(plt_name[PLT_NEXT]     , "���@��");


	wsprintf(plt_name[PLT_NAKIARI]  , "�@�L");
	wsprintf(plt_name[PLT_NAKINASHI], "�@��");

	wsprintf(plt_name[PLT_YES]      , "�́@��");
	wsprintf(plt_name[PLT_YES]      , "������");

	// ----------------------------------------
	// ���b�Z�[�W������\��
	// ----------------------------------------

	// �ǖ�
	wsprintf(kyokutbl[0],"�����");
	wsprintf(kyokutbl[1],"�����");
	wsprintf(kyokutbl[2],"���O��");
	wsprintf(kyokutbl[3],"���l��");
	wsprintf(kyokutbl[4],"����");
	wsprintf(kyokutbl[5],"����");
	wsprintf(kyokutbl[6],"��O��");
	wsprintf(kyokutbl[7],"��l��");

	// �����擾
	SetYakuName();

	// ----------------------------------------
	// �ϐ�������
	// ----------------------------------------

	desp_tehai_mode = 0; // (0:���C�i�[�\���A1:�X�N�G�A�\���A2:������\��)

}

/* ---------------------------------------------------------------------------------------------- */
// ��ʏ���������
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispPartsPost(){

}

/* ---------------------------------------------------------------------------------------------- */
// ���ʊ֐� - �𖼐ݒ�
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::SetYakuName(){

	// �𖼒�`�E�ʏ��
	wsprintf(yakuname[NOYAKU],          "���Ȃ��@�@�@");
	wsprintf(yakuname[RIICH],           "���[�`�@�@�@");
	wsprintf(yakuname[WRIICH],          "�_�u�����[�`");
	wsprintf(yakuname[IPPATSU],         "�ꔭ�@�@�@�@");
	wsprintf(yakuname[CHINISO],         "����F�@�@�@");
	wsprintf(yakuname[HONISO],          "����F�@�@�@");
	wsprintf(yakuname[JUNCHAN],         "���S�с@�@�@");
	wsprintf(yakuname[RYANPEKO],        "��u���@�@�@");
	wsprintf(yakuname[HONROTO],         "���V���@�@�@");
	wsprintf(yakuname[SHOSANGEN],       "���O���@�@�@");
	wsprintf(yakuname[ITSU],            "��C�ʊс@�@");
	wsprintf(yakuname[SANDOKOU],        "�O�F�����@�@");
	wsprintf(yakuname[SANDOJUN],        "�O�F�����@�@");
	wsprintf(yakuname[SANKANTSU],       "�O�Ȏq�@�@�@");
	wsprintf(yakuname[SANANKO],         "�O�Í��@�@�@");
	wsprintf(yakuname[TOITOI],          "�΁X�a�@�@�@");
	wsprintf(yakuname[CHANTA],          "���S�с@�@�@");
	wsprintf(yakuname[CHITOI],          "���Ύq�@�@�@");
	wsprintf(yakuname[PINFU],           "���a�@�@�@�@");
	wsprintf(yakuname[TANYAO],          "�f����@�@�@");
	wsprintf(yakuname[IPEKO],           "��u���@�@�@");
	wsprintf(yakuname[BAKAZE],          "�ꕗ�v�@�@�@");
	wsprintf(yakuname[ZIKAZE],          "�����v�@�@�@");
	wsprintf(yakuname[YAKUHAI],         "�O���v�@�@�@");
	wsprintf(yakuname[YAKUHAIHAKU],     "�O���v���@�@");
	wsprintf(yakuname[YAKUHAIHATSU],    "�O���v���@�@");
	wsprintf(yakuname[YAKUHAICHUN],     "�O���v���@�@");
	wsprintf(yakuname[HAITEI],          "�C��̌��@�@");
	wsprintf(yakuname[HOUTEI],          "�͒ꝝ���@�@");
	wsprintf(yakuname[RINSHAN],         "���J�ԁ@�@");
	wsprintf(yakuname[CHANKAN],         "���ȁ@�@�@�@");
	wsprintf(yakuname[TSUMO],           "��O�����̘a");
	wsprintf(yakuname[DORA],            "�\�h���@�@�@");
	wsprintf(yakuname[URADORA],         "���h���@�@�@");
	wsprintf(yakuname[AKAHAI],          "�Ԕv�@�@�@�@");
	wsprintf(yakuname[RENHO],           "�l�a(����)�@");
	wsprintf(yakuname[NAGASHIMAN],      "�������с@�@");
	wsprintf(yakuname[UNKNOWN_YAKU],    "���s���@�@");

	// �𖼒�`�E��
	wsprintf(yakumanname[NOYAKUMAN],    "���Ȃ��@�@�@");
	wsprintf(yakumanname[TENHO],        "�V�a�@�@�@�@");
	wsprintf(yakumanname[CHIHO],        "�n�a�@�@�@�@");
	wsprintf(yakumanname[CHUREN9MEN],   "��A��ʑҁ@");
	wsprintf(yakumanname[CHUREN],       "��A�󓕁@�@");
	wsprintf(yakumanname[KOKUSHI13MEN], "���m�\�O�ʑ�");
	wsprintf(yakumanname[KOKUSHI],      "���m���o�@�@");
	wsprintf(yakumanname[DAISANGEN],    "��O���@�@�@");
	wsprintf(yakumanname[DAISUSHI],     "��l��a�@�@");
	wsprintf(yakumanname[SHOSUSHI],     "���l��a�@�@");
	wsprintf(yakumanname[TSUISO],       "����F�@�@�@");
	wsprintf(yakumanname[CHINROTO],     "���V���@�@�@");
	wsprintf(yakumanname[RYUISO],       "�Έ�F�@�@�@");
	wsprintf(yakumanname[SUKANTSU],     "�l�Ȏq�@�@�@");
	wsprintf(yakumanname[SUANKOTANKI],  "�l�Í��P�R�@");
	wsprintf(yakumanname[SUANKO],       "�l�Í��@�@�@");
	wsprintf(yakumanname[RENHOYAKUMAN], "�l�a�@�@�@�@");

	// ���ǎ�ʖ���`
	wsprintf(ryukyokuname[NORKK],         "���ǐݒ�Ȃ��@�@");
	wsprintf(ryukyokuname[HOWANPAI],      "���ǁF�r�v�@�@�@");
	wsprintf(ryukyokuname[SUFURENDA],     "���ǁF�l���A�Ł@");
	wsprintf(ryukyokuname[RIICHI4PLY],    "���ǁF�l�l���[�`");
	wsprintf(ryukyokuname[RON3PLY],       "���ǁF�O�l�����@");
	wsprintf(ryukyokuname[TEHAI9HAI],     "���ǁF����v�@");
	wsprintf(ryukyokuname[NAGASHIMANGAN], "���ǁF�������с@");
	wsprintf(ryukyokuname[UNKNOWNRKK],    "���ǁF���̑�����");

}

/* ---------------------------------------------------------------------------------------------- */
// ��ʏ���������
/* ---------------------------------------------------------------------------------------------- */
int MJSDisplayParts::DispPartsFrameInit(){

	// Log.txt�̏o�͗}�~
	SetOutApplicationLogValidFlag(FALSE);

	// �E�C���h�E���[�h�ɂ���
	// DxLib_Init���O�ɍs��
    if( ChangeWindowMode(TRUE) != DX_CHANGESCREEN_OK ) {

		// �ُ�I��
		return -1;

	}

	// �E�B���h�E�T�C�Y�ύX
	SetGraphMode( 1024 , 768 , 32 );
	SetWindowSize( 1024 , 768 );

	// �E�C���h�E���A�N�e�B�u�ł͂Ȃ���Ԃł������𑱍s����
 	SetAlwaysRunFlag(TRUE);

	// 2�ȏ㓯���ɋN���ł��邩�ǂ�����ݒ肷��B
 	SetDoubleStartValidFlag(TRUE);

	// �}�E�X�\���I��
    SetMouseDispFlag(TRUE);

	// ����I��
	return 0;

}

/* ---------------------------------------------------------------------------------------------- */
// DXLib������
/* ---------------------------------------------------------------------------------------------- */
int MJSDisplayParts::DispPartsLibInit(){

	// DX���C�u����������
	if (DxLib_Init() != 0){

		// �ُ�I��
		return -1;

	}

	// �`���𗠉�ʂɐݒ�
	SetDrawScreen(DX_SCREEN_BACK); 

	// �摜�ǂݍ���
	DispPartsReadPic();

	// ����I��
	return 0;
}

/* ---------------------------------------------------------------------------------------------- */
// �摜�ǂݍ���
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispPartsReadPic(){

	// ----------------------------------------
	// �摜�ǂݍ���
	// ----------------------------------------

	// �w�i�摜
	backpic = LoadGraph("bmp\\back.bmp");                   // �w�i
	title   = LoadGraph("bmp\\title.bmp");                  // �^�C�g��
	banner  = LoadGraph("bmp\\banner.bmp");                 // �o�i�[
	pltimg  = LoadGraph("bmp\\plt.bmp");                    // �v���[�g
	center_pltimg = LoadGraph("bmp\\center_plt.png");       // ��Z���^�[�v���[�g

	// �{�^���摜
	but02      = LoadGraph( "bmp\\but02.bmp");              // �{�^��02
	but03      = LoadGraph( "bmp\\but03.bmp");              // �{�^��03
	but_red    = LoadGraph( "bmp\\but_red.bmp");            // �ԐF�{�^��
	but_green  = LoadGraph( "bmp\\but_green.bmp");          // �ΐF�{�^��
	but_blue   = LoadGraph( "bmp\\but_bule.bmp");           // �F�{�^��
	but_yellow = LoadGraph( "bmp\\but_yellow.bmp");         // ���F�{�^��

	// �w�i�F
 	gray    = LoadGraph( "bmp\\gray.bmp" );                 // �D�w�i�p
 	lgray   = LoadGraph( "bmp\\lgray.bmp");                 // �D�w�i�p_���v
 	blue    = LoadGraph( "bmp\\blue.bmp" );                 // �w�i�p
 	lblue   = LoadGraph( "bmp\\lblue.bmp");                 // �w�i�p_���v
 	pink    = LoadGraph( "bmp\\pink.bmp" );                 // ���w�i�p
 	lpink   = LoadGraph( "bmp\\lpink.bmp");                 // ���w�i�p_���v
 	yellow  = LoadGraph( "bmp\\yellow.bmp" );               // ���w�i�p
 	lyellow = LoadGraph( "bmp\\lyellow.bmp");               // ���w�i�p_���v


	// �摜�𕪊����āA�z��ɕۑ�
	LoadDivGraph( "bmp\\pai.bmp",      40, 10, 4,  HAI_XSIZE,  HAI_YSIZE, Pai    );  
	LoadDivGraph( "bmp\\paibase.bmp",   6,  2, 3,         24,         36, PaiBase);  
 
	// �摜�̕����i�[�E���v
	LoadDivGraph( "bmp\\lpai.bmp",      40, 10, 4,         32,         24, LPai    ); 
	LoadDivGraph( "bmp\\lpaibase.bmp",   6,  2, 3,         32,         29, LPaiBase); 

}

/* ---------------------------------------------------------------------------------------------- */
// DXLib�I������
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispPartsLibPost(){

	// DX���C�u�����g�p�̏I������
	DxLib_End();

}

/* ---------------------------------------------------------------------------------------------- */
// �����`�揈��
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispPartsClearDraw(){

	// ��ʂ�����
	ClearDrawScreen();

	// �w�i�\��
	DrawGraph( 0, 0, backpic, TRUE );

}

/* ---------------------------------------------------------------------------------------------- */
// �t���b�v����
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispPartsFlip(){

	// ����ʂ�\��ʂɔ��f
	ScreenFlip();

}

/* ---------------------------------------------------------------------------------------------- */
// ���ʊ֐� - �����o��
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispString(int x, int y, char *str){

	// �����o��
	DrawFormatString( x, y, GetColor(255,255,255), str);

}

/* ---------------------------------------------------------------------------------------------- */
// �p�[�c�\��/�I�[�v�j���O�^�C�g��
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispOpeningTitle(int ver1, int ver2, int ver3, int ver4, int ver5){

	// �^�C�g���摜
	DrawGraph( 350, 100, title, TRUE );

	// �^�C�g���p�̃o�[�W�����\��
	DrawFormatString(800, 300, GetColor(255,255,255), "Ver. %d.%d.%d.%d.%d", ver1, ver2, ver3, ver4, ver5);

	// �t�b�^�[
	DrawFormatString( 425, 720, GetColor(255,255,255), "Copyright (c) 2010-2024 TechMilestone All Rights Reserved.");

}

/* ---------------------------------------------------------------------------------------------- */
// �p�[�c�\��/�o�i�[�\��
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispBunner(int ver1, int ver2, int ver3, int ver4, int ver5){

	// �o�i�[�\��
	DrawGraph( 884, 0, banner, TRUE ) ;

	// �o�[�W�������\��
	wsprintf(tmp_disp_msg, "Ver %d.%d.%d.%d.%d", ver1, ver2, ver3, ver4, ver5);
	DispString( 870, 45, tmp_disp_msg );
}

/* ---------------------------------------------------------------------------------------------- */
// �p�[�c�\��/�Z���^�[�v���[�g�\��
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispCenterPlt(int x, int y){

	// �Z���^�[�v���[�g�\��
	DrawGraph( x, y, center_pltimg, TRUE ) ;

}

/* ---------------------------------------------------------------------------------------------- */
// �p�[�c�\�� - �}�E�X�|�C���g
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispMousepoint(int x, int y, int msx,int msy, int b0, int b1){

	// �}�E�X�|�C���g�\��
	wsprintf(tmp_disp_msg, "X=%4d Y=%3d B[0]=%d B[1]=%d", msx, msy, b0, b1);
	DispString( x, y, tmp_disp_msg );

}

/* ---------------------------------------------------------------------------------------------- */
// �p�[�c�\�� - FPS�t���[��
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispFps(int x, int y, float mFps, int total_frame_count, int frame_count){

	// FPS�t���[���\��
	DrawFormatString(x, y, GetColor(255,255,255), "TotalFrCnt:%6d FrCnt:%4d FPS�F%03.1f", total_frame_count, frame_count, mFps);

}

/* ---------------------------------------------------------------------------------------------- */
// �p�[�c�\���E�v���[�g�\��
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispPltline(int x, int y, int plt_range, bool plt_mode[]){

	// �v���[�g�\��
	for(int tmp_i = 0; tmp_i < PLTLINE_COUNT ; tmp_i++ ) {
	    if( plt_mode[tmp_i] == true ) {
			// �v���[�g�\��
			DrawGraph       ( x+plt_range*tmp_i,    y,   pltimg, TRUE );
			// �����\��
			DrawFormatString( x+plt_range*tmp_i+16, y+7, GetColor(255,255,255), plt_name[tmp_i]);
		}
	}

}

/* ---------------------------------------------------------------------------------------------- */
// �p�[�c�\���E������Ȃ��v���[�g
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispPltNakiAriNashi(int x, int y, bool plt_naki_stat){

	// �v���[�g�\��
	DrawGraph( x, y, pltimg, TRUE );

	// �����\��
	if( plt_naki_stat == true ) {
		DrawFormatString( x+16, y+7, GetColor(255,255,255), plt_name[PLT_NAKIARI]);
	}else{
		DrawFormatString( x+16, y+7, GetColor(255,255,255), plt_name[PLT_NAKINASHI]);
	}

}

/* ---------------------------------------------------------------------------------------------- */
// �{�^���\��
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispButton(int x, int y, LBPartsButColor but_color){

	// �{�^���\��
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
// ��񑀍�{�^��
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispInfoButton(int thinfo_x, int tkinfo_x, int plyinfo_x, int quit_x, int y){

	// ��񑀍�{�^���\��
	DrawGraph( thinfo_x,  y, but_blue,   TRUE );
	DrawGraph( tkinfo_x,  y, but_blue,   TRUE );
	DrawGraph( plyinfo_x, y, but_yellow, TRUE );
	DrawGraph( quit_x,    y, but_red,    TRUE );

}

/* ---------------------------------------------------------------------------------------------- */
// Actid�{�^��
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispActidButton(int kyoid_x, int actid_x, int y){

	// �r���[�A�[���[�h�p��ID�AACTID�{�^��
	DrawGraph( kyoid_x, y, but02, TRUE );         // ��INDEX�ύX
	DrawGraph( actid_x, y, but03, TRUE );         // ActID�ύX

}

/* ---------------------------------------------------------------------------------------------- */
// �ꌈ�߁E�쌋�ʃ{�^��
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispBagimeButton(int bagime_x, int tkend_x, int y){

	// �r���[�A�[���[�h�p�ꌈ�߁E�쌋�ʃ{�^��
	DrawGraph( bagime_x, y, but_green, TRUE );    // �ꌈ�ߕ\��
	DrawGraph( tkend_x,  y, but_green, TRUE );    // �쌋�ʕ\��

}

/* ---------------------------------------------------------------------------------------------- */
// �ȕύX�{�^��
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispSekiButton(int x, int y){

	// �r���[�A�[���[�h�p�ȕύX�{�^��
	DrawGraph( x, y, but02, TRUE );

}

/* ---------------------------------------------------------------------------------------------- */
// ���C���{�^���\��(�r���[�A�[���[�h)
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispViewerModeButton(){

}

/* ---------------------------------------------------------------------------------------------- */
// �h���\��
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispDora(int x, int y, int doracount, int dora[], bool dora_aka[], int dora_actid[], int tmp_act_id){

	// �h���v�\��
	for(int tmp_i = 0; tmp_i < doracount ; tmp_i++ ) {
		// �h���v�\������A�N�V�����ԍ��m�F
		if(dora_actid[tmp_i] <= tmp_act_id){
			DispHai( x+24*tmp_i, y, dora[tmp_i], dora_aka[tmp_i], false, 0, 0);
		}else{
			DispHai( x+24*tmp_i, y, 0, false, false, 0, 0);
		}
	}

	// �������v
	for(int tmp_i = 0; tmp_i < 5-doracount ; tmp_i++ ) {
			DispHai( x+24*(doracount+tmp_i), y, 0, false, false, 0, 0);
	}

}

/* ---------------------------------------------------------------------------------------------- */
// �p�[�c�\���E�v�\��
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispHai(int x, int y, int hai, bool aka, bool hai_turn, int haimode, int haicolor){

	// �f�o�b�O�p
	if ( hai < 0 || hai > PAI_MAX){
		hai=0;
	}

	// �Ԕv�̏ꍇ
	      if( hai == MAN5NUM && aka == true ){
		hai=10;
	}else if( hai == PIN5NUM && aka == true ){
		hai=20;
	}else if( hai == SOU5NUM && aka == true ){
		hai=30;
	}

	// �v�\�����C��
	if ( hai == 0 ){
			DrawGraph( x, y, PaiBase[haicolor*2+1], TRUE ) ;                         // ���ʕ\��
	}else{

		// ----------------------------------------
		// �ʏ�\��
		// ----------------------------------------
		if ( haimode == DISP_HAI_COLOR_NUM_NOCOLOR ){

		 	// �v�g�\��
			DrawGraph( x, y, PaiBase[haicolor*2], TRUE ) ;
			// �v�ʕ\��
			if (hai_turn == true){
				DrawRotaGraph( x+12, y+16, 1.0f, PI, Pai[PaiImgNum[hai]], TRUE );     // �v�̏㉺���]
			}else{
				DrawGraph( x, y, Pai[PaiImgNum[hai]] , TRUE ) ;                       // �v�ʕ\��
			}

		// ----------------------------------------
		// �u�����h���[�h - �D�F
		// ----------------------------------------
		}else if( haimode == DISP_HAI_COLOR_NUM_GRAY ){

			// �F�x�[�X�\��
			DrawGraph( x, y, gray, TRUE ) ;
			// �u�����h�\���J�n
			SetDrawBlendMode( DX_BLENDMODE_ADD , 64 ) ;
		    // �v�g�\��
			DrawGraph( x, y, PaiBase[haicolor*2], TRUE );
			// �v�ʕ\��
			if (hai_turn == true){
				DrawRotaGraph( x+12, y+16, 1.0f, PI, Pai[PaiImgNum[hai]], TRUE );    // �v�̏㉺���]
			}else{
				DrawGraph( x, y, Pai[PaiImgNum[hai]] , TRUE );                       // �v�ʕ\��
			}
		    // �u�����h�\������
			SetDrawBlendMode( DX_BLENDMODE_NOBLEND , 0 );

		// ----------------------------------------
		// �u�����h���[�h - �D�F(�Z����)
		// ----------------------------------------
		}else if( haimode == DISP_HAI_COLOR_NUM_DEEP_GRAY ){

			// �F�x�[�X�\��
			DrawGraph( x, y, gray, TRUE ) ;
			// �u�����h�\���J�n
			SetDrawBlendMode( DX_BLENDMODE_ADD , 48 ) ;
			// �v�g�\��
			DrawGraph( x, y, PaiBase[haicolor*2], TRUE ) ;
			// �v�\��
			if (hai_turn == true){
				DrawRotaGraph( x+12, y+16, 1.0f, PI, Pai[PaiImgNum[hai]], TRUE );     // �v�̏㉺���]
			}else{
				DrawGraph( x, y, Pai[PaiImgNum[hai]] , TRUE ) ;
			}
			// �u�����h�\������
			SetDrawBlendMode( DX_BLENDMODE_NOBLEND , 0 ) ;

		// ----------------------------------------
		// �u�����h���[�h - ��
		// ----------------------------------------
		}else if( haimode == DISP_HAI_COLOR_NUM_BLUE ){

			// �F�x�[�X�\��
			DrawGraph( x, y, blue, TRUE ) ;
			// �u�����h�\���J�n
			SetDrawBlendMode( DX_BLENDMODE_ADD , 64 ) ;
			// �v�g�\��
			DrawGraph( x, y, PaiBase[haicolor*2], TRUE ) ;
			// �v�\��
			if (hai_turn == true){
				DrawRotaGraph( x+12, y+16, 1.0f, PI, Pai[PaiImgNum[hai]], TRUE );     // �v�̏㉺���]
			}else{
				DrawGraph( x, y, Pai[PaiImgNum[hai]] , TRUE ) ;
			}
			// �u�����h�\������
			SetDrawBlendMode( DX_BLENDMODE_NOBLEND , 0 ) ;

		// ----------------------------------------
		// �u�����h���[�h - ��(�Z����)
		// ----------------------------------------
		}else if( haimode == DISP_HAI_COLOR_NUM_DEEP_BLUE ){

			// �F�x�[�X�\��
			DrawGraph( x, y, blue, TRUE ) ;
			// �u�����h�\���J�n
			SetDrawBlendMode( DX_BLENDMODE_ADD , 48 ) ;
			// �v�g�\��
			DrawGraph( x, y, PaiBase[haicolor*2], TRUE ) ;
			// �v�\��
			if (hai_turn == true){
				DrawRotaGraph( x+12, y+16, 1.0f, PI, Pai[PaiImgNum[hai]], TRUE );     // �v�̏㉺���]
			}else{
				DrawGraph( x, y, Pai[PaiImgNum[hai]] , TRUE ) ;
			}
			// �u�����h�\������
			SetDrawBlendMode( DX_BLENDMODE_NOBLEND , 0 ) ;

		// ----------------------------------------
		// �u�����h���[�h - ��
		// ----------------------------------------
		}else if( haimode == DISP_HAI_COLOR_NUM_PINK ){

			// �v�g�\��
			DrawGraph( x, y, PaiBase[haicolor*2], TRUE ) ;
			// �F�x�[�X�\��
			DrawGraph( x, y, pink, TRUE ) ;
			// �u�����h�\���J�n
			SetDrawBlendMode( DX_BLENDMODE_ADD , 64 ) ;
			// �v�\��
			if (hai_turn == true){
				DrawRotaGraph( x+12, y+16, 1.0f, PI, Pai[PaiImgNum[hai]], TRUE );     // �v�̏㉺���]
			}else{
				DrawGraph( x, y, Pai[PaiImgNum[hai]] , TRUE ) ;
			}
			// �u�����h�\������
			SetDrawBlendMode( DX_BLENDMODE_NOBLEND , 0 ) ;

		// ----------------------------------------
		// �u�����h���[�h - ��
		// ----------------------------------------
		}else if( haimode == DISP_HAI_COLOR_NUM_YELLOW ){

			// �v�g�\��
			DrawGraph( x, y, PaiBase[haicolor*2], TRUE ) ;
			// �F�x�[�X�\��
			DrawGraph( x, y, yellow, TRUE ) ;
			// �u�����h�\���J�n
			SetDrawBlendMode( DX_BLENDMODE_ADD , 64 ) ;
			// �v�\��
			if (hai_turn == true){
				DrawRotaGraph( x+12, y+16, 1.0f, PI, Pai[PaiImgNum[hai]], TRUE );     // �v�̏㉺���]
			}else{
				DrawGraph( x, y, Pai[PaiImgNum[hai]] , TRUE ) ;
			}
			// �u�����h�\������
			SetDrawBlendMode( DX_BLENDMODE_NOBLEND , 0 ) ;

		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// �p�[�c�\���E���v�\��
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispLHai(int x, int y, int hai, bool aka, bool hai_turn, int haimode, int haicolor){

	// �f�o�b�O�p
	if ( hai < 0 || hai > PAI_MAX){
		hai=0;
	}

	// �Ԕv�̏ꍇ
	      if( hai == MAN5NUM && aka == true ){
		hai=10;
	}else if( hai == PIN5NUM && aka == true ){
		hai=20;
	}else if( hai == SOU5NUM && aka == true ){
		hai=30;
	}

	// �v�\�����C��
	if ( hai == 0 ){

		// ���ʕ\��
		DrawGraph( x, y, LPaiBase[haicolor*2+1], TRUE ) ;

	}else{

		// ----------------------------------------
		// �ʏ�\��
		// ----------------------------------------
		if ( haimode == DISP_HAI_COLOR_NUM_NOCOLOR ){
		 	// �v�g�\��
			DrawGraph( x, y, LPaiBase[haicolor*2], TRUE ) ;
			// �v�ʕ\��
			if (hai_turn == true){
				DrawRotaGraph( x+16, y+12, 1.0f, PI, LPai[PaiImgNum[hai]], TRUE );     // �v�̏㉺���]
			}else{
				DrawGraph( x, y, LPai[PaiImgNum[hai]] , TRUE ) ;
			}

		// ----------------------------------------
		// �u�����h���[�h - �D�F
		// ----------------------------------------
		}else if( haimode == DISP_HAI_COLOR_NUM_GRAY ){

			// �F�x�[�X�\��
			DrawGraph( x, y, lgray, TRUE ) ;
			// �u�����h�\���J�n
			SetDrawBlendMode( DX_BLENDMODE_ADD , 64 ) ;
		 	// �v�g�\��
			DrawGraph( x, y, LPaiBase[haicolor*2], TRUE ) ;
			// �v�ʕ\��
			if (hai_turn == true){
				DrawRotaGraph( x+16, y+12, 1.0f, PI, LPai[PaiImgNum[hai]], TRUE );     // �v�̏㉺���]
			}else{
				DrawGraph( x, y, LPai[PaiImgNum[hai]] , TRUE ) ;
			}
			// �u�����h�\������
			SetDrawBlendMode( DX_BLENDMODE_NOBLEND , 0 ) ;

		// ----------------------------------------
		// �u�����h���[�h - �D�F(�Z����)
		// ----------------------------------------
		}else if( haimode == DISP_HAI_COLOR_NUM_DEEP_GRAY ){

			// �F�x�[�X�\��
			DrawGraph( x, y, lgray, TRUE ) ;
			// �u�����h�\���J�n
			SetDrawBlendMode( DX_BLENDMODE_ADD , 48 ) ;
		 	// �v�g�\��
			DrawGraph( x, y, LPaiBase[haicolor*2], TRUE ) ;
			// �v�ʕ\��
			if (hai_turn == true){
				DrawRotaGraph( x+16, y+12, 1.0f, PI, LPai[PaiImgNum[hai]], TRUE );     // �v�̏㉺���]
			}else{
				DrawGraph( x, y, LPai[PaiImgNum[hai]] , TRUE ) ;
			}
			// �u�����h�\������
			SetDrawBlendMode( DX_BLENDMODE_NOBLEND , 0 ) ;

		// ----------------------------------------
		// �u�����h���[�h - ��
		// ----------------------------------------
		}else if( haimode == DISP_HAI_COLOR_NUM_BLUE ){

			// �F�x�[�X�\��
			DrawGraph( x, y, lblue, TRUE ) ;
			// �u�����h�\���J�n
			SetDrawBlendMode( DX_BLENDMODE_ADD , 64 ) ;
		 	// �v�g�\��
			DrawGraph( x, y, LPaiBase[haicolor*2], TRUE ) ;
			// �v�ʕ\��
			if (hai_turn == true){
				DrawRotaGraph( x+16, y+12, 1.0f, PI, LPai[PaiImgNum[hai]], TRUE );     // �v�̏㉺���]
			}else{
				DrawGraph( x, y, LPai[PaiImgNum[hai]] , TRUE ) ;
			}
			// �u�����h�\������
			SetDrawBlendMode( DX_BLENDMODE_NOBLEND , 0 ) ;

		// ----------------------------------------
		// �u�����h���[�h - ��(�Z����)
		// ----------------------------------------
		}else if( haimode == DISP_HAI_COLOR_NUM_DEEP_BLUE ){

			// �v�\��
			DrawGraph( x, y, lblue, TRUE ) ;
			// �u�����h�\���J�n
			SetDrawBlendMode( DX_BLENDMODE_ADD , 48 ) ;
		 	// �v�g�\��
			DrawGraph( x, y, LPaiBase[haicolor*2], TRUE ) ;
			// �v�ʕ\��
			if (hai_turn == true){
				DrawRotaGraph( x+16, y+12, 1.0f, PI, LPai[PaiImgNum[hai]], TRUE );     // �v�̏㉺���]
			}else{
				DrawGraph( x, y, LPai[PaiImgNum[hai]] , TRUE ) ;
			}
			// �u�����h�\������
			SetDrawBlendMode( DX_BLENDMODE_NOBLEND , 0 ) ;

		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// ��v�p�[�c�̕\��(�ʏ��)
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispActTehaiParts(int x, int y,int tehai_tbl_count, int tehai_tbl[], bool tehai_tbl_aka[], int tsumo_hai, bool tsumo_aka, int sute_hai_num, int color_hai, int color_hai2, bool color_ankan){

	int tmp_hai_x;         // ��vX�ʒu

	// ----------------------------------------
	// ��v�\��
	// ----------------------------------------
	for(int tmp_i = 0; tmp_i < tehai_tbl_count; tmp_i++){

		// X�ʒu
		tmp_hai_x = x + tmp_i*HAI_XSIZE;

		// ----------------------------------------
		// ��v�\��(�ʏ탂�[�h)
		// ----------------------------------------
		if( tmp_i != sute_hai_num){

			// ���F�v�ł���Ȃ�
			if( tmp_i == color_hai || tmp_i == color_hai2){

				// �Ԕv�ł���Ȃ�
				if( tehai_tbl_aka[tmp_i] == true){
					// �F�E�Ԕv�\��
					DispHai( tmp_hai_x, y, tehai_tbl[tmp_i], true, false, DISP_HAI_COLOR_NUM_BLUE, 0);
				}else{
					// �F�E�ʏ�\��
					DispHai( tmp_hai_x, y, tehai_tbl[tmp_i], false, false, DISP_HAI_COLOR_NUM_BLUE, 0);
				}

			// ���F�̕\��
			}else{

				// �Ԕv�ł���Ȃ�
				if( tehai_tbl_aka[tmp_i] == true){
					// ���F�E�Ԕv�\��
					DispHai( tmp_hai_x, y, tehai_tbl[tmp_i], true, false, 0, 0);
				}else{
					// ���F�E�ʏ�\��
					DispHai( tmp_hai_x, y, tehai_tbl[tmp_i], false, false, 0, 0);
				}
			}

		}

	}

	// ----------------------------------------
	// �c���v�\��
	// ----------------------------------------

	// ���̔v�\���Ȃ�
	if (tsumo_hai > 0 && tsumo_hai < 38){

		// ���F�v�ł���Ȃ�
		if( tehai_tbl_count == color_hai){
			DispHai( x+HAI_XSIZE*tehai_tbl_count+SPACE_XSIZE, y, tsumo_hai, tsumo_aka, false, DISP_HAI_COLOR_NUM_BLUE, 0);
		}else{
			DispHai( x+HAI_XSIZE*tehai_tbl_count+SPACE_XSIZE, y, tsumo_hai, tsumo_aka, false, 0, 0);
		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// ��v�p�[�c(�l�v���[���[�̔v�֎~�\��)
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispActHumCanSuteParts(int x, int y, int  tehai_tbl_count, int tehai_tbl[], bool tehai_tbl_aka[], bool tehai_can_sute_tbl[], int tsumo_hai, bool tsumo_aka, bool tsumo_can_sute, int color_hai){

	int tmp_hai_x;         // ��vX�ʒu

	// ----------------------------------------
	// ��v�\��
	// ----------------------------------------
	for(int tmp_i = 0; tmp_i < tehai_tbl_count; tmp_i++){

		// X�ʒu
		tmp_hai_x = x+tmp_i*HAI_XSIZE;

		// ----------------------------------------
		// ��v�\��(�ʏ탂�[�h)
		// ----------------------------------------
		// tehai_can_sute_tbl��true�Ȃ�̔v�\(���F)
		if( tehai_can_sute_tbl[tmp_i] == true){

			// ���F�v�ł���Ȃ�
			if( tmp_i == color_hai){

				// �Ԕv�ł���Ȃ�
				if( tehai_tbl_aka[tmp_i] == true){
					// �F�E�Ԕv�\��
					DispHai( tmp_hai_x, y, tehai_tbl[tmp_i], true, false, DISP_HAI_COLOR_NUM_BLUE, 0);
				}else{
					// �F�E�ʏ�\��
					DispHai( tmp_hai_x, y, tehai_tbl[tmp_i], false, false, DISP_HAI_COLOR_NUM_BLUE, 0);
				}

			// �ʏ�v�̕\��
			}else{

				// �Ԕv�ł���Ȃ�
				if( tehai_tbl_aka[tmp_i] == true){
					// ���F�E�Ԕv�\��
					DispHai( tmp_hai_x, y, tehai_tbl[tmp_i], true, false, 0, 0);
				}else{
					// ���F�E�ʏ�\��
					DispHai( tmp_hai_x, y, tehai_tbl[tmp_i], false, false, 0, 0);
				}
			}

		// tehai_can_sute_tbl��true�ȊO�Ȃ�̔v�s��(�D�F)
		}else{
				if( tehai_tbl_aka[tmp_i] == true){
					// ���F�E�Ԕv�\��
					DispHai( tmp_hai_x, y, tehai_tbl[tmp_i], true, false, DISP_HAI_COLOR_NUM_GRAY, 0);
				}else{
					// ���F�E�ʏ�\��
					DispHai( tmp_hai_x, y, tehai_tbl[tmp_i], false, false, DISP_HAI_COLOR_NUM_GRAY, 0);
				}

		 }

	}

	// ----------------------------------------
	// �c���v�\��
	// ----------------------------------------

	// ���̔v�\���Ȃ�
	if (tsumo_hai > 0 && tsumo_hai < 38){
		// tsumo_can_sute��true�Ȃ�̔v�\(���F)
		if( tsumo_can_sute == true ){

			// ���F�v�ł���Ȃ�
			if( tehai_tbl_count == color_hai){
				DispHai( x+HAI_XSIZE*tehai_tbl_count+SPACE_XSIZE, y, tsumo_hai, tsumo_aka, false, DISP_HAI_COLOR_NUM_BLUE, 0);
			}else{
				DispHai( x+HAI_XSIZE*tehai_tbl_count+SPACE_XSIZE, y, tsumo_hai, tsumo_aka, false, 0, 0);
			}

		// tsumo_can_sute��true�ȊO�Ȃ�̔v�s��(�D�F)
		}else{
				DispHai( x+HAI_XSIZE*tehai_tbl_count+SPACE_XSIZE, y, tsumo_hai, tsumo_aka, false, DISP_HAI_COLOR_NUM_GRAY, 0);
		}
	}
}

/* ---------------------------------------------------------------------------------------------- */
// ��v�p�[�c�̕\��(�J���v�I��)
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispActHumKanSelectTehaiParts(int x, int y, int  tehai_tbl_count, int  tehai_tbl[], bool tehai_tbl_aka[], int tsumo_hai, bool tsumo_aka, int ankan_hai1, int ankan_hai2, int ankan_hai3, int kakan_hai1, int kakan_hai2, int kakan_hai3, int color_hai){

	int tmp_hai_x;            // ��vX�ʒu

	// ----------------------------------------
	// ��v�\��
	// ----------------------------------------
	for(int tmp_i = 0; tmp_i < tehai_tbl_count; tmp_i++){

		// X�ʒu
		tmp_hai_x = SPACE_XSIZE+tmp_i*HAI_XSIZE;

		// ----------------------------------------
		// ��v�\��(�ʏ탂�[�h)
		// ----------------------------------------
		// �J�����v�Ȃ璅�F
		if( tehai_tbl[tmp_i] == ankan_hai1 || tehai_tbl[tmp_i] == ankan_hai2 || tehai_tbl[tmp_i] == ankan_hai3 ||
		    tehai_tbl[tmp_i] == kakan_hai1 || tehai_tbl[tmp_i] == kakan_hai2 || tehai_tbl[tmp_i] == kakan_hai3 ){
			// �}�E�X�ʒu�Œ��L�����m�F
			if( tmp_i == color_hai){
				DispHai( tmp_hai_x, y, tehai_tbl[tmp_i], tehai_tbl_aka[tmp_i], false, DISP_HAI_COLOR_NUM_BLUE, 0);
			// �ʏ�v�̕\��
			}else{
				DispHai( tmp_hai_x, y, tehai_tbl[tmp_i], tehai_tbl_aka[tmp_i], false, 0, 0);
			}
		// �J�����v�łȂ��Ȃ��ɊD�F
		}else{
				DispHai( tmp_hai_x, y, tehai_tbl[tmp_i], tehai_tbl_aka[tmp_i], false, DISP_HAI_COLOR_NUM_GRAY, 0);
		}

	}

	// ----------------------------------------
	// �c���v�\��
	// ----------------------------------------

	// �J�����v�Ȃ璅�F
	if( tsumo_hai == ankan_hai1 || tsumo_hai == ankan_hai2 || tsumo_hai == ankan_hai3 ||
	    tsumo_hai == kakan_hai1 || tsumo_hai == kakan_hai2 || tsumo_hai == kakan_hai3 ){
		// ���F�v�ł���Ȃ�
		if( tehai_tbl_count == color_hai){
			DispHai( x+HAI_XSIZE*tehai_tbl_count+SPACE_XSIZE, y, tsumo_hai, tsumo_aka, false, DISP_HAI_COLOR_NUM_BLUE, 0);
		}else{
			DispHai( x+HAI_XSIZE*tehai_tbl_count+SPACE_XSIZE, y, tsumo_hai, tsumo_aka, false, 0, 0);
		}
	// �e���p�C�łȂ��Ȃ��ɊD�F
	}else{
			DispHai( x+HAI_XSIZE*tehai_tbl_count+SPACE_XSIZE, y, tsumo_hai, tsumo_aka, false, DISP_HAI_COLOR_NUM_GRAY, 0);
	}

}

/* ---------------------------------------------------------------------------------------------- */
// ��������v�\��
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DisplayUnkownTehai(int x, int y, int tehai_tbl_count, bool tsumo_flg, int sute_hai_num){

	// �ϐ���`
	int tmp_hai_x;

	// ----------------------------------------
	// ��v�\��
	// ----------------------------------------
	for(int tmp_i = 0; tmp_i < tehai_tbl_count; tmp_i++){

		// X�ʒu
		tmp_hai_x = SPACE_XSIZE+tmp_i*HAI_XSIZE;

		// �^���̔v�\��
		// if(sute_flg == false || tmp_i != 5){
		if( tmp_i != sute_hai_num ){
			DispHai( tmp_hai_x, y, 0, false, false, 0, 0);
		}

	}

	// ----------------------------------------
	// ���̔v�\��
	// ----------------------------------------
	if(tsumo_flg == true){
		tmp_hai_x = SPACE_XSIZE+tehai_tbl_count*HAI_XSIZE + SPACE_XSIZE;
		DispHai( tmp_hai_x, y, 0, false, false, 0, 0);
	}


}

/* ---------------------------------------------------------------------------------------------- */
// �N���ʎq�̃p�[�c�\��
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispActSarashiParts(int x, int y, LBMen naki_stat, int hai_index, int aka_count){

	// �ϐ��̏�����
	int tmp_aka_count = aka_count;

	// ----------------------------------------
	// (�f�o�O�p)�Ԕv����
	// ----------------------------------------
/*
	// ���Ȋm�F
 	if( naki_stat != KAKAN){

			// (�f�o�O�p)���ʎq�̐Ԕv�����\��
			DrawFormatString( x+HAI_XSIZE*4+2, y   , GetColor(255,255,255), "��%d��", aka_count);

	}else{

		// (�f�o�O�p)���ȁE�Ԕv�m�F
		if (aka_count>0){
			DrawFormatString( x+HAI_XSIZE*4+2, y+17, GetColor(255,255,255), "��+1��");
		}else{
			DrawFormatString( x+HAI_XSIZE*4+2, y+17, GetColor(255,255,255), "��+0��");
		}

	}
*/
	// ----------------------------------------
	// �|���v�̕\��
	// ----------------------------------------
	if( naki_stat == MINKO || naki_stat == ANKO ){

		// �N���v�̕\��
		for(int tmp_i = 0; tmp_i < 3; tmp_i++){
 			if( ( hai_index == 5 || hai_index == 15 || hai_index == 25) && tmp_aka_count > 0 ){
 				DispHai( x+HAI_XSIZE*tmp_i, y, hai_index, true, false,  0, 0);
				tmp_aka_count--;
			}else{
				DispHai( x+HAI_XSIZE*tmp_i, y, hai_index, false, false, 0, 0);
			}
		}

	// ----------------------------------------
	// �`�[�v�̕\��
	// ----------------------------------------
	}else if(naki_stat == MINSHUN || naki_stat == SHUNTSU ){

		// �N���v�̕\��(1����)
 		if( ( hai_index == 5 || hai_index == 15 || hai_index == 25) && tmp_aka_count > 0 ){
			DispHai( x            , y, hai_index  , true, false, 0, 0);
			tmp_aka_count--;
		}else{
			DispHai( x            , y, hai_index  , false, false, 0, 0);
		}

		// �N���v�̕\��(2����)
 		if( ( hai_index+1 == 5 || hai_index+1 == 15 || hai_index+1 == 25) && tmp_aka_count > 0 ){
			DispHai( x+HAI_XSIZE  , y, hai_index+1, true, false, 0, 0);
			tmp_aka_count--;
		}else{
			DispHai( x+HAI_XSIZE  , y, hai_index+1, false, false, 0, 0);
		}

		// �N���v�̕\��(3����)
 		if( ( hai_index+2 == 5 || hai_index+2 == 15 || hai_index+2 == 25) && tmp_aka_count > 0 ){
			DispHai( x+HAI_XSIZE*2, y, hai_index+2, true, false, 0, 0);
			tmp_aka_count--;
		}else{
			DispHai( x+HAI_XSIZE*2, y, hai_index+2, false, false, 0, 0);
		}

	// ----------------------------------------
	// �ÞȔv�̕\��
	// ----------------------------------------
	}else if(naki_stat == ANKAN){

		// �N���v�̕\��(�I�[�v��1����)
		if( tmp_aka_count > 0 ){
			DispHai( x+HAI_XSIZE  , y, hai_index, true, false, 0, 0);
		}else{
			DispHai( x+HAI_XSIZE  , y, hai_index, false, false, 0, 0);
		}

		// �N���v�̕\��(�I�[�v��2����)
		if( tmp_aka_count > 1 ){
			DispHai( x+HAI_XSIZE*2, y, hai_index, true, false, 0, 0);
		}else{
			DispHai( x+HAI_XSIZE*2, y, hai_index, false, false, 0, 0);
		}

		// �������v
		DispHai( x,             y, 0, false, false, 0, 0);
		DispHai( x+HAI_XSIZE*3, y, 0, false, false, 0, 0);

	// ----------------------------------------
	// ���Ȕv�̕\��
	// ----------------------------------------
	}else if(naki_stat == MINKAN){

		// �N���v�̕\��(�I�[�v��1����)
		if( tmp_aka_count > 0 ){
			DispHai( x            , y, hai_index, true, false, 0, 0);
		}else{
			DispHai( x            , y, hai_index, false, false, 0, 0);
		}

		// �N���v�̕\��(�I�[�v��2����)
		if( tmp_aka_count > 1 ){
			DispHai( x+HAI_XSIZE*1, y, hai_index, true, false, 0, 0);
		}else{
			DispHai( x+HAI_XSIZE*1, y, hai_index, false, false, 0, 0);
		}

		// �N���v�̕\��(�I�[�v��3����)
		if( tmp_aka_count > 2 ){
			DispHai( x+HAI_XSIZE*2, y, hai_index, true, false, 0, 0);
		}else{
			DispHai( x+HAI_XSIZE*2, y, hai_index, false, false, 0, 0);
		}

		// �N���v�̕\��(�I�[�v��4����)
		if( tmp_aka_count > 3 ){
			DispHai( x+HAI_XSIZE*3, y, hai_index, true, false, 0, 0);
		}else{
			DispHai( x+HAI_XSIZE*3, y, hai_index, false, false, 0, 0);
		}

	// ----------------------------------------
	// ���Ȕv�̕\��
	// ----------------------------------------
	}else if(naki_stat == KAKAN){
		if( tmp_aka_count > 0 ){
			DispHai( x+HAI_XSIZE*3, y, hai_index, true, false, 0, 0);
		}else{
			DispHai( x+HAI_XSIZE*3, y, hai_index, false, false, 0, 0);
		}

	// ----------------------------------------
	// ���E�Ύq�̕\��
	// ----------------------------------------
	}else if( naki_stat == ATAMA || naki_stat == TOITSU ){

		// �N���v�̕\��
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
// �N���ʎq�̃p�[�c�\���F�S���ʎq�\��
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispAllSarashiParts(int x, int y, int naki_count, LBMen naki_stat[], int naki_hai[], int naki_idx[], int naki_aka[]){

	// �ϐ���`
	int tmp_xstat_count = 0;

	// ���炵�\��
	for(int tmp_i = 0; tmp_i < naki_count; tmp_i++){

		// ----------------------------------------
		// �|���v�̕\���E���Ȕv�̕\���E�ÞȔv�̕\��
		// ----------------------------------------
		if( naki_stat[tmp_i] == MINKO  || 
		    naki_stat[tmp_i] == MINKAN || 
		    naki_stat[tmp_i] == ANKAN  ){

			// ���\��
			DispActSarashiParts( x - tmp_xstat_count*NAKI_MENTSU_RANGE, y,  naki_stat[tmp_i], naki_hai[tmp_i], naki_aka[tmp_i]);

			// ���ʎq�̕\���ʒu�ړ�
			tmp_xstat_count++;

		// ----------------------------------------
		// �`�[�v�v�̕\��
		// ----------------------------------------
		}else if(naki_stat[tmp_i] == MINSHUN){

			// ���\��
			DispActSarashiParts( x - tmp_xstat_count*NAKI_MENTSU_RANGE, y,  naki_stat[tmp_i], naki_idx[tmp_i], naki_aka[tmp_i]);

			// ���ʎq�̕\���ʒu�ړ�
			tmp_xstat_count++;


		// ----------------------------------------
		// ���Ȕv�̕\��
		// ----------------------------------------
		}else if(naki_stat[tmp_i] == KAKAN){

			// ���Ȃ̎N���v�ԍ��̊m�F
			for(int tmp_j = 0; tmp_j < naki_count; tmp_j++){
				// �����N���ʎq�Ɠ����Ȃ��
				if (naki_hai[tmp_j] == naki_hai[tmp_i]){
					// ���ȕ\��
					DispActSarashiParts(x - tmp_j*NAKI_MENTSU_RANGE, y,  KAKAN, naki_hai[tmp_j], naki_hai[tmp_i]);
					// ���Ȃ�����̂ŁA�����Ŕ�����B(�����Ȃ��Ɖ��Ȃŏd�������ɂȂ��Ă��܂�)
					break;
				}
			}

		// ----------------------------------------
		// ���̑��̕\��
		// ----------------------------------------
		}else{
			// ���̑�����
			DrawFormatString(x, y,  GetColor(255,255,255), "���̑�");
		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// �v��p�[�c/�͏��F���C�i�[�\��
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispActKawaParts_liner(int x, int y, int kawa_tbl_count, int kawa_tbl[], bool kawa_tbl_aka[], int kawa_mode[]){

	// �v��X�ʒu�\���p
	int sute_xstat = 0;

	// �̔v�\��(���C�i�[�\��)
	for(int tmp_i = 0; tmp_i < kawa_tbl_count; tmp_i++){

		// ���[�`�����̏ꍇ
		if( kawa_mode[tmp_i] >= RIICHI_STAT_NUM ){

			// �̔v�\�� - ���[�`�v
			DispLHai( SPACE_XSIZE + sute_xstat, y+7, kawa_tbl[tmp_i], kawa_tbl_aka[tmp_i], false, kawa_mode[tmp_i]-RIICHI_STAT_NUM, 0);

			// �̔v�̈ʒu�ύX
			sute_xstat = sute_xstat + LHAI_XSIZE;

		// �ʏ�̏ꍇ
		}else{

			// �̔v�\��
			DispHai( SPACE_XSIZE + sute_xstat, y, kawa_tbl[tmp_i], kawa_tbl_aka[tmp_i], false,  kawa_mode[tmp_i], 0);

			// �̔v�̈ʒu�ύX
			sute_xstat = sute_xstat + HAI_XSIZE;

		 }

	}

}

/* ---------------------------------------------------------------------------------------------- */
// �A�N�V������v�EUP�v���[���\��
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispActTehaiParts_up(int x,int y,int tehai_tbl_count, int tehai_tbl[], bool tehai_tbl_aka[], int tsumo_hai, bool tsumo_aka, int sute_hai_num){

	// ��v�\��(UP�v���[��)
	for(int tmp_i = 0; tmp_i < tehai_tbl_count; tmp_i++){
		// �̔v�łȂ��Ȃ�
		if( sute_hai_num != (tehai_tbl_count-tmp_i-1) ){
			DispHai( x + (13-tehai_tbl_count) * HAI_XSIZE + tmp_i * HAI_XSIZE, 
			         y, 
			         tehai_tbl[tehai_tbl_count-tmp_i-1], tehai_tbl_aka[tehai_tbl_count-tmp_i-1], true, 0, 0);
		}
	}

		// ���̔v�\��(UP�v���[��)
		if ( tsumo_hai > 0 && tsumo_hai < PAI_MAX){
			DispHai( x + (13-tehai_tbl_count) * HAI_XSIZE - HAI_XSIZE - SPACE_XSIZE, 
			         y, 
			         tsumo_hai, tsumo_aka, true, 0, 0);
		}
}

/* ---------------------------------------------------------------------------------------------- */
// �A�N�V������v�ELeft�v���[���\��
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispActTehaiParts_left(int x,int y,int tehai_tbl_count, int tehai_tbl[], bool tehai_tbl_aka[], int tsumo_hai, bool tsumo_aka, int sute_hai_num){

	// ��v�\��(Left�v���[��)
	for(int tmp_i = 0; tmp_i < tehai_tbl_count; tmp_i++){
		// �̔v�łȂ��Ȃ�
		if(tmp_i != sute_hai_num){
			DispLHai( x, y + tmp_i * LHAI_YSIZE, tehai_tbl[tmp_i], tehai_tbl_aka[tmp_i], true, 0, 0);         // ����v
		}
	}

		// ���̔v�\��(Left�v���[��)
		if ( tsumo_hai > 0 && tsumo_hai < PAI_MAX){
			DispLHai( x, y + tehai_tbl_count * LHAI_YSIZE + 10, tsumo_hai, tsumo_aka, true, 0, 0);            // ������(13*23=299)
		}
}

/* ---------------------------------------------------------------------------------------------- */
// �A�N�V������v�ERight�v���[���\��
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispActTehaiParts_right(int x,int y,int tehai_tbl_count, int tehai_tbl[], bool tehai_tbl_aka[], int tsumo_hai, bool tsumo_aka, int sute_hai_num){

	// ��v�\��(Right�v���[��)
	for(int tmp_i = 0; tmp_i < tehai_tbl_count; tmp_i++){
		// �̔v�łȂ��Ȃ�
		if( sute_hai_num != (tehai_tbl_count-tmp_i-1) ){
			DispLHai( x, 
			          y + 35 + (13-tehai_tbl_count)*LHAI_YSIZE + tmp_i*LHAI_YSIZE, 
			          tehai_tbl[tehai_tbl_count-tmp_i-1], tehai_tbl_aka[tehai_tbl_count-tmp_i-1], false, 0, 0);
		}
	}

		// ���̔v�\��(Right�v���[��)
		if ( tsumo_hai > 0 && tsumo_hai < PAI_MAX){
			DispLHai( x, 
			          y + (13-tehai_tbl_count)*LHAI_YSIZE, 
		              tsumo_hai, tsumo_aka, false, 0, 0);
		}

}

/* ---------------------------------------------------------------------------------------------- */
// �A�N�V�����͏��EUP�v���[���\��
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispActKawaParts_up(int x, int y, int kawa_tbl_count, int kawa_tbl[], bool kawa_tbl_aka[], int kawa_mode[]){

	// ----------------------------------------
	// �ϐ�������
	// ----------------------------------------
	int  tmp_x;
	int  tmp_y;
	int  line_sutehai_count = 0;
	int  tmp_sute_idx   = 0;
	int  tmp_kawa_mode  = 0;
	bool riichi_flg = false;

	// ----------------------------------------
	// �̔v�\��(1�i��)
	// ----------------------------------------
	if( kawa_tbl_count > LINE_SUTEHAI_COUNT_MAX*3){

		// �ϐ���`
		tmp_x = x+HAI_XSIZE*5;
		tmp_y = y;

		// �v����
		line_sutehai_count = kawa_tbl_count - LINE_SUTEHAI_COUNT_MAX*3;

		// �̔v�\��(1�i��)
		for(int tmp_i = 0; tmp_i < line_sutehai_count; tmp_i++){

			// �̔vINDEX�̒�`
			tmp_sute_idx = tmp_i + LINE_SUTEHAI_COUNT_MAX*3;

			// �v���[�h�m�F
			if( kawa_mode[tmp_sute_idx] >= RIICHI_STAT_NUM ){
				tmp_kawa_mode =  kawa_mode[tmp_sute_idx] - RIICHI_STAT_NUM;
				riichi_flg = true;
			}else{
				tmp_kawa_mode =  kawa_mode[tmp_sute_idx];
				riichi_flg = false;
			}

			// �̔v�\��
			if(riichi_flg == true){
				// �̔v�\�� - ���[�`�v
				DispLHai( tmp_x-8,tmp_y+7, kawa_tbl[tmp_sute_idx], kawa_tbl_aka[tmp_sute_idx], true, tmp_kawa_mode, 0);
				tmp_x = tmp_x - LHAI_XSIZE;
			}else{
				// �̔v�\�� - �ʏ�
				DispHai( tmp_x, tmp_y,   kawa_tbl[tmp_sute_idx], kawa_tbl_aka[tmp_sute_idx], true, tmp_kawa_mode, 0);
				tmp_x = tmp_x - HAI_XSIZE;
			}

		}

	}

	// ----------------------------------------
	// �̔v�\��(2�i��)
	// ----------------------------------------
	if( kawa_tbl_count > LINE_SUTEHAI_COUNT_MAX*2){

		// �ϐ���`
		tmp_x = x+HAI_XSIZE*5;
		tmp_y = y+HAI_YSIZE*1;

		// �v����
		if(kawa_tbl_count > LINE_SUTEHAI_COUNT_MAX*3){
			line_sutehai_count = LINE_SUTEHAI_COUNT_MAX;
		}else{
			line_sutehai_count = kawa_tbl_count - LINE_SUTEHAI_COUNT_MAX*2;
		}

		// �̔v�\��(1�i��)
		for(int tmp_i = 0; tmp_i < line_sutehai_count; tmp_i++){

			// �̔vINDEX�̒�`
			tmp_sute_idx = tmp_i + LINE_SUTEHAI_COUNT_MAX*2;

			// �v���[�h�m�F
			if( kawa_mode[tmp_sute_idx] >= RIICHI_STAT_NUM ){
				tmp_kawa_mode =  kawa_mode[tmp_sute_idx] - RIICHI_STAT_NUM;
				riichi_flg = true;
			}else{
				tmp_kawa_mode =  kawa_mode[tmp_sute_idx];
				riichi_flg = false;
			}

			// �̔v�\��
			if(riichi_flg == true){
				// �̔v�\�� - ���[�`�v
				DispLHai( tmp_x-8,tmp_y+7, kawa_tbl[tmp_sute_idx], kawa_tbl_aka[tmp_sute_idx], true, tmp_kawa_mode, 0);
				tmp_x = tmp_x - LHAI_XSIZE;
			}else{
				// �̔v�\�� - �ʏ�
				DispHai( tmp_x, tmp_y,   kawa_tbl[tmp_sute_idx], kawa_tbl_aka[tmp_sute_idx], true, tmp_kawa_mode, 0);
				tmp_x = tmp_x - HAI_XSIZE;
			}

		}

	}

	// ----------------------------------------
	// �̔v�\��(3�i��)
	// ----------------------------------------
	if( kawa_tbl_count > LINE_SUTEHAI_COUNT_MAX){

		// �ϐ���`
		tmp_x = x+HAI_XSIZE*5;
		tmp_y = y+HAI_YSIZE*2;

		// �v����
		if(kawa_tbl_count > LINE_SUTEHAI_COUNT_MAX*2){
			line_sutehai_count = LINE_SUTEHAI_COUNT_MAX;
		}else{
			line_sutehai_count = kawa_tbl_count - LINE_SUTEHAI_COUNT_MAX;
		}

		// �̔v�\��(1�i��)
		for(int tmp_i = 0; tmp_i < line_sutehai_count; tmp_i++){

			// �̔vINDEX�̒�`
			tmp_sute_idx = tmp_i + LINE_SUTEHAI_COUNT_MAX;

			// �v���[�h�m�F
			if( kawa_mode[tmp_sute_idx] >= RIICHI_STAT_NUM ){
				tmp_kawa_mode =  kawa_mode[tmp_sute_idx] - RIICHI_STAT_NUM;
				riichi_flg = true;
			}else{
				tmp_kawa_mode =  kawa_mode[tmp_sute_idx];
				riichi_flg = false;
			}

			// �̔v�\��
			if(riichi_flg == true){
				// �̔v�\�� - ���[�`�v
				DispLHai( tmp_x-8,tmp_y+7, kawa_tbl[tmp_sute_idx], kawa_tbl_aka[tmp_sute_idx], true, tmp_kawa_mode, 0);
				tmp_x = tmp_x - LHAI_XSIZE;
			}else{
				// �̔v�\�� - �ʏ�
				DispHai( tmp_x, tmp_y,   kawa_tbl[tmp_sute_idx], kawa_tbl_aka[tmp_sute_idx], true, tmp_kawa_mode, 0);
				tmp_x = tmp_x - HAI_XSIZE;
			}

		}

	}

	// ----------------------------------------
	// �̔v�\��(4�i��)
	// ----------------------------------------
	if( kawa_tbl_count > 0){

		// �ϐ���`
		tmp_x = x+HAI_XSIZE*5;
		tmp_y = y+HAI_YSIZE*3;

		// �v����
		if(kawa_tbl_count > LINE_SUTEHAI_COUNT_MAX){
			line_sutehai_count = LINE_SUTEHAI_COUNT_MAX;
		}else{
			line_sutehai_count = kawa_tbl_count;
		}

		// �̔v�\��(1�i��)
		for(int tmp_i = 0; tmp_i < line_sutehai_count; tmp_i++){

			// �̔vINDEX�̒�`
			tmp_sute_idx = tmp_i;

			// �v���[�h�m�F
			if( kawa_mode[tmp_sute_idx] >= RIICHI_STAT_NUM ){
				tmp_kawa_mode =  kawa_mode[tmp_sute_idx] - RIICHI_STAT_NUM;
				riichi_flg = true;
			}else{
				tmp_kawa_mode =  kawa_mode[tmp_sute_idx];
				riichi_flg = false;
			}

			// �̔v�\��
			if(riichi_flg == true){
				// �̔v�\�� - ���[�`�v
				DispLHai( tmp_x-8,tmp_y+7, kawa_tbl[tmp_sute_idx], kawa_tbl_aka[tmp_sute_idx], true, tmp_kawa_mode, 0);
				tmp_x = tmp_x - LHAI_XSIZE;
			}else{
				// �̔v�\�� - �ʏ�
				DispHai( tmp_x, tmp_y,   kawa_tbl[tmp_sute_idx], kawa_tbl_aka[tmp_sute_idx], true, tmp_kawa_mode, 0);
				tmp_x = tmp_x - HAI_XSIZE;
			}

		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// �A�N�V�����͏��EDOWN�v���[���\��
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispActKawaParts_down(int x, int y, int kawa_tbl_count, int kawa_tbl[], bool kawa_tbl_aka[], int kawa_mode[]){

	// �\����1�i�ځ�4�i�ڂ̏����͌���ƂȂ�A�ʂ�1�i�ځ�4�i�ڂ���\������

	// ----------------------------------------
	// �ϐ�������
	// ----------------------------------------
	int  tmp_x;
	int  tmp_y;
	int  line_sutehai_count = 0;
	int  tmp_sute_idx = 0;
	int  tmp_kawa_mode = 0;
	bool riichi_flg = false;

	// ----------------------------------------
	// �̔v�\��(1�i��)
	// ----------------------------------------
	if( kawa_tbl_count > 0){

		// �ϐ���`
		tmp_x = x;
		tmp_y = y;

		// �v����
		if(kawa_tbl_count > LINE_SUTEHAI_COUNT_MAX){
			line_sutehai_count = LINE_SUTEHAI_COUNT_MAX;
		}else{
			line_sutehai_count = kawa_tbl_count;
		}

		// �̔v�\��(1�i��)
		for(int tmp_i = 0; tmp_i < line_sutehai_count; tmp_i++){

			// �̔vINDEX�̒�`
			tmp_sute_idx = tmp_i;

			// �v���[�h�m�F
			if( kawa_mode[tmp_sute_idx] >= RIICHI_STAT_NUM ){
				tmp_kawa_mode =  kawa_mode[tmp_sute_idx] - RIICHI_STAT_NUM;
				riichi_flg = true;
			}else{
				tmp_kawa_mode =  kawa_mode[tmp_sute_idx];
				riichi_flg = false;
			}

			// �̔v�\��
			if(riichi_flg == true){
				// �̔v�\�� - ���[�`�v
				DispLHai( tmp_x,tmp_y+7, kawa_tbl[tmp_sute_idx], kawa_tbl_aka[tmp_sute_idx], false, tmp_kawa_mode, 0);
				tmp_x = tmp_x + LHAI_XSIZE;
			}else{
				// �̔v�\�� - �ʏ�
				DispHai( tmp_x, tmp_y  , kawa_tbl[tmp_sute_idx], kawa_tbl_aka[tmp_sute_idx], false, tmp_kawa_mode, 0);
				tmp_x = tmp_x + HAI_XSIZE;
			}

		}
	}

	// ----------------------------------------
	// �̔v�\��(2�i��)
	// ----------------------------------------
	if(kawa_tbl_count > LINE_SUTEHAI_COUNT_MAX){

		// �ϐ���`
		tmp_x = x;
		tmp_y = y+HAI_YSIZE*1;

		// �v����
		if(kawa_tbl_count > LINE_SUTEHAI_COUNT_MAX*2){
			line_sutehai_count = LINE_SUTEHAI_COUNT_MAX;
		}else{
			line_sutehai_count = kawa_tbl_count - LINE_SUTEHAI_COUNT_MAX;
		}

		// �̔v�\��(2�i��)
		for(int tmp_i = 0; tmp_i < line_sutehai_count; tmp_i++){

			// �̔vINDEX�̒�`
			tmp_sute_idx = tmp_i + LINE_SUTEHAI_COUNT_MAX;

			// �v���[�h�m�F
			if( kawa_mode[tmp_sute_idx] >= RIICHI_STAT_NUM ){
				tmp_kawa_mode =  kawa_mode[tmp_sute_idx] - RIICHI_STAT_NUM;
				riichi_flg = true;
			}else{
				tmp_kawa_mode =  kawa_mode[tmp_sute_idx];
				riichi_flg = false;
			}

			// �̔v�\��
			if(riichi_flg == true){
				// �̔v�\�� - ���[�`�v
				DispLHai(tmp_x, tmp_y+7, kawa_tbl[tmp_sute_idx], kawa_tbl_aka[tmp_sute_idx], false, tmp_kawa_mode, 0);
				tmp_x = tmp_x + LHAI_XSIZE;
			}else{
				// �̔v�\�� - �ʏ�
				DispHai( tmp_x, tmp_y,   kawa_tbl[tmp_sute_idx], kawa_tbl_aka[tmp_sute_idx], false, tmp_kawa_mode, 0);
				tmp_x = tmp_x + HAI_XSIZE;
			}

		}
	}

	// ----------------------------------------
	// �̔v�\��(3�i��)
	// ----------------------------------------
	if(kawa_tbl_count > LINE_SUTEHAI_COUNT_MAX*2){

		// �ϐ���`
		tmp_x = x;
		tmp_y = y+HAI_YSIZE*2;

		// �v����
		if(kawa_tbl_count > LINE_SUTEHAI_COUNT_MAX*3){
			line_sutehai_count = LINE_SUTEHAI_COUNT_MAX;
		}else{
			line_sutehai_count = kawa_tbl_count - LINE_SUTEHAI_COUNT_MAX*2;
		}

		// �̔v�\��(3�i��)
		for(int tmp_i = 0; tmp_i < line_sutehai_count; tmp_i++){

			// �̔vINDEX�̒�`
			tmp_sute_idx = tmp_i + LINE_SUTEHAI_COUNT_MAX*2;

			// �v���[�h�m�F
			if( kawa_mode[tmp_sute_idx] >= RIICHI_STAT_NUM ){
				tmp_kawa_mode =  kawa_mode[tmp_sute_idx] - RIICHI_STAT_NUM;
				riichi_flg = true;
			}else{
				tmp_kawa_mode =  kawa_mode[tmp_sute_idx];
				riichi_flg = false;
			}

			// �̔v�\��
			if(riichi_flg == true){
				// �̔v�\�� - ���[�`�v
				DispLHai( tmp_x, tmp_y+7, kawa_tbl[tmp_sute_idx], kawa_tbl_aka[tmp_sute_idx], false, tmp_kawa_mode, 0);
				tmp_x = tmp_x + LHAI_XSIZE;
			}else{
				// �̔v�\�� - �ʏ�
				DispHai( tmp_x, tmp_y,    kawa_tbl[tmp_sute_idx], kawa_tbl_aka[tmp_sute_idx], false, tmp_kawa_mode, 0);
				tmp_x = tmp_x + HAI_XSIZE;
			}

		}
	}

	// ----------------------------------------
	// �̔v�\��(4�i��)
	// ----------------------------------------
	if(kawa_tbl_count > LINE_SUTEHAI_COUNT_MAX*3){

		// �ϐ���`
		tmp_x = x;
		tmp_y = y+HAI_YSIZE*3;

		// �v����
		if(kawa_tbl_count > LINE_SUTEHAI_COUNT_MAX*4){
			line_sutehai_count = LINE_SUTEHAI_COUNT_MAX;
		}else{
			line_sutehai_count = kawa_tbl_count - LINE_SUTEHAI_COUNT_MAX*3;
		}

		// �̔v�\��(3�i��)
		for(int tmp_i = 0; tmp_i < line_sutehai_count; tmp_i++){

			// �̔vINDEX�̒�`
			tmp_sute_idx = tmp_i + LINE_SUTEHAI_COUNT_MAX*3;

			// �v���[�h�m�F
			if( kawa_mode[tmp_sute_idx] >= RIICHI_STAT_NUM ){
				tmp_kawa_mode =  kawa_mode[tmp_sute_idx] - RIICHI_STAT_NUM;
				riichi_flg = true;
			}else{
				tmp_kawa_mode =  kawa_mode[tmp_sute_idx];
				riichi_flg = false;
			}

			// �̔v�\��
			if(riichi_flg == true){
				// �̔v�\�� - ���[�`�v
				DispLHai( tmp_x, tmp_y+7, kawa_tbl[tmp_sute_idx], kawa_tbl_aka[tmp_sute_idx], false, tmp_kawa_mode, 0);
				tmp_x = tmp_x + LHAI_XSIZE;
			}else{
				// �̔v�\�� - �ʏ�
				DispHai( tmp_x, tmp_y,    kawa_tbl[tmp_sute_idx], kawa_tbl_aka[tmp_sute_idx], false, tmp_kawa_mode, 0);
				tmp_x = tmp_x + HAI_XSIZE;
			}

		}
	}



}

/* ---------------------------------------------------------------------------------------------- */
// �A�N�V�����͏��ELEFT�v���[���\��
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispActKawaParts_left(int x, int y, int kawa_tbl_count, int kawa_tbl[], bool kawa_tbl_aka[], int kawa_mode[]){

	// ----------------------------------------
	// �ϐ�������
	// ----------------------------------------
	int  tmp_x;
	int  tmp_y;
	int  line_sutehai_count = 0;
	int  tmp_sute_idx = 0;
	int  tmp_kawa_mode = 0;
	bool riichi_flg = false;

	// ----------------------------------------
	// �̔v�\��(1�i��)
	// ----------------------------------------
	if( kawa_tbl_count > 0){

		// �ϐ���`
		tmp_x = x;
		tmp_y = y;

		// �v����
		if(kawa_tbl_count > LINE_SUTEHAI_COUNT_MAX){
			line_sutehai_count = LINE_SUTEHAI_COUNT_MAX;
		}else{
			line_sutehai_count = kawa_tbl_count;
		}

		// �̔v�\��(1�i��)
		for(int tmp_i = 0; tmp_i < line_sutehai_count; tmp_i++){

			// �̔vINDEX�̒�`
			tmp_sute_idx = tmp_i;

			// �v���[�h�m�F
			if( kawa_mode[tmp_sute_idx] >= RIICHI_STAT_NUM ){
				tmp_kawa_mode =  kawa_mode[tmp_sute_idx] - RIICHI_STAT_NUM;
				riichi_flg = true;
			}else{
				tmp_kawa_mode =  kawa_mode[tmp_sute_idx];
				riichi_flg = false;
			}

			// �̔v�\��
			if(riichi_flg == true){
				// �̔v�\�� - ���[�`�v
				DispHai( tmp_x+7, tmp_y, kawa_tbl[tmp_sute_idx], kawa_tbl_aka[tmp_sute_idx], false, tmp_kawa_mode, 0);
				tmp_y = tmp_y + HAI_YSIZE;
			}else{
				// �̔v�\�� - �ʏ�v
				DispLHai(tmp_x,   tmp_y, kawa_tbl[tmp_sute_idx], kawa_tbl_aka[tmp_sute_idx], true,  tmp_kawa_mode, 0);
				tmp_y = tmp_y + LHAI_YSIZE;
			}
		}
	}

	// ----------------------------------------
	// �̔v�\��(2�i��)
	// ----------------------------------------
	if( kawa_tbl_count > LINE_SUTEHAI_COUNT_MAX){

		// �ϐ���`
		tmp_x = x-LHAI_XSIZE*1;
		tmp_y = y;

		// �v����
		if(kawa_tbl_count > LINE_SUTEHAI_COUNT_MAX*2){
			line_sutehai_count = LINE_SUTEHAI_COUNT_MAX;
		}else{
			line_sutehai_count = kawa_tbl_count - LINE_SUTEHAI_COUNT_MAX;
		}

		// �̔v�\��(1�i��)
		for(int tmp_i = 0; tmp_i < line_sutehai_count; tmp_i++){

			// �̔vINDEX�̒�`
			tmp_sute_idx = tmp_i + LINE_SUTEHAI_COUNT_MAX;

			// �v���[�h�m�F
			if( kawa_mode[tmp_sute_idx] >= RIICHI_STAT_NUM ){
				tmp_kawa_mode =  kawa_mode[tmp_sute_idx] - RIICHI_STAT_NUM;
				riichi_flg = true;
			}else{
				tmp_kawa_mode =  kawa_mode[tmp_sute_idx];
				riichi_flg = false;
			}

			// �̔v�\��
			if(riichi_flg == true){
				// �̔v�\�� - ���[�`�v
				DispHai( tmp_x+7, tmp_y, kawa_tbl[tmp_sute_idx], kawa_tbl_aka[tmp_sute_idx], false, tmp_kawa_mode, 0);
				tmp_y = tmp_y + HAI_YSIZE;
			}else{
				// �̔v�\�� - �ʏ�v
				DispLHai(tmp_x,   tmp_y, kawa_tbl[tmp_sute_idx], kawa_tbl_aka[tmp_sute_idx], true,  tmp_kawa_mode, 0);
				tmp_y = tmp_y + LHAI_YSIZE;
			}
		}

	}

	// ----------------------------------------
	// �̔v�\��(3�i��)
	// ----------------------------------------
	if( kawa_tbl_count > LINE_SUTEHAI_COUNT_MAX*2){

		// �ϐ���`
		tmp_x = x-LHAI_XSIZE*2;
		tmp_y = y;

		// �v����
		if(kawa_tbl_count > LINE_SUTEHAI_COUNT_MAX*3){
			line_sutehai_count = LINE_SUTEHAI_COUNT_MAX;
		}else{
			line_sutehai_count = kawa_tbl_count - LINE_SUTEHAI_COUNT_MAX*2;
		}

		// �̔v�\��(1�i��)
		for(int tmp_i = 0; tmp_i < line_sutehai_count; tmp_i++){

			// �̔vINDEX�̒�`
			tmp_sute_idx = tmp_i + LINE_SUTEHAI_COUNT_MAX*2;

			// �v���[�h�m�F
			if( kawa_mode[tmp_sute_idx] >= RIICHI_STAT_NUM ){
				tmp_kawa_mode =  kawa_mode[tmp_sute_idx] - RIICHI_STAT_NUM;
				riichi_flg = true;
			}else{
				tmp_kawa_mode =  kawa_mode[tmp_sute_idx];
				riichi_flg = false;
			}

			// �̔v�\��
			if(riichi_flg == true){
				// �̔v�\�� - ���[�`�v
				DispHai( tmp_x+7, tmp_y, kawa_tbl[tmp_sute_idx], kawa_tbl_aka[tmp_sute_idx], false, tmp_kawa_mode, 0);
				tmp_y = tmp_y + HAI_YSIZE;
			}else{
				// �̔v�\�� - �ʏ�v
				DispLHai(tmp_x,   tmp_y, kawa_tbl[tmp_sute_idx], kawa_tbl_aka[tmp_sute_idx], true,  tmp_kawa_mode, 0);
				tmp_y = tmp_y + LHAI_YSIZE;
			}
		}

	}

	// ----------------------------------------
	// �̔v�\��(4�i��)
	// ----------------------------------------
	if( kawa_tbl_count > LINE_SUTEHAI_COUNT_MAX*3){

		// �ϐ���`
		tmp_x = x-LHAI_XSIZE*3;
		tmp_y = y;

		// �v����
		if(kawa_tbl_count > LINE_SUTEHAI_COUNT_MAX*4){
			line_sutehai_count = LINE_SUTEHAI_COUNT_MAX;
		}else{
			line_sutehai_count = kawa_tbl_count - LINE_SUTEHAI_COUNT_MAX*3;
		}

		// �̔v�\��(1�i��)
		for(int tmp_i = 0; tmp_i < line_sutehai_count; tmp_i++){

			// �̔vINDEX�̒�`
			tmp_sute_idx = tmp_i + LINE_SUTEHAI_COUNT_MAX*3;

			// �v���[�h�m�F
			if( kawa_mode[tmp_sute_idx] >= RIICHI_STAT_NUM ){
				tmp_kawa_mode =  kawa_mode[tmp_sute_idx] - RIICHI_STAT_NUM;
				riichi_flg = true;
			}else{
				tmp_kawa_mode =  kawa_mode[tmp_sute_idx];
				riichi_flg = false;
			}

			// �̔v�\��
			if(riichi_flg == true){
				// �̔v�\�� - ���[�`�v
				DispHai( tmp_x+7, tmp_y, kawa_tbl[tmp_sute_idx], kawa_tbl_aka[tmp_sute_idx], false, tmp_kawa_mode, 0);
				tmp_y = tmp_y + HAI_YSIZE;
			}else{
				// �̔v�\�� - �ʏ�v
				DispLHai(tmp_x,   tmp_y, kawa_tbl[tmp_sute_idx], kawa_tbl_aka[tmp_sute_idx], true,  tmp_kawa_mode, 0);
				tmp_y = tmp_y + LHAI_YSIZE;
			}
		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// �A�N�V�����͏��ERIGHT�v���[���\��
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispActKawaParts_right(int x, int y, int kawa_tbl_count, int kawa_tbl[], bool kawa_tbl_aka[], int kawa_mode[]){

	// ----------------------------------------
	// �ϐ�������
	// ----------------------------------------
	int  tmp_x;
	int  tmp_y;
	int  line_sutehai_count = 0;
	int  tmp_sute_idx = 0;
	int  tmp_kawa_mode = 0;
	bool riichi_flg = false;
	bool disp_riichi_flg = false;

	// ----------------------------------------
	// �̔v�\��(1�i��)
	// ----------------------------------------
	if( kawa_tbl_count > 0){

		// �s�̔v����
		if(kawa_tbl_count > LINE_SUTEHAI_COUNT_MAX){
			line_sutehai_count = LINE_SUTEHAI_COUNT_MAX;
		}else{
			line_sutehai_count = kawa_tbl_count;
		}

		// �s���[�`�m�F
		disp_riichi_flg = false;
		for(int tmp_i = 0; tmp_i < line_sutehai_count; tmp_i++){
			if( kawa_mode[tmp_i] >= RIICHI_STAT_NUM ){
				disp_riichi_flg = true;
				break;
			}
		}

		// �ϐ���`
		tmp_x = x;
		tmp_y = y + LHAI_YSIZE*(LINE_SUTEHAI_COUNT_MAX-line_sutehai_count);  // �󔒕�����������

		// ���[�`�ʒu�̏C��
		if( disp_riichi_flg == true ){
			tmp_y=tmp_y-8;
		}

		// �̔v�\��(Right�v���[��)
		for(int tmp_i = 0; tmp_i < line_sutehai_count; tmp_i++){

			// �̔vINDEX�̒�`
			tmp_sute_idx = 0 + line_sutehai_count - tmp_i - 1;

			// �v���[�h�m�F
			if( kawa_mode[tmp_sute_idx] >= RIICHI_STAT_NUM ){
				tmp_kawa_mode =  kawa_mode[tmp_sute_idx] - RIICHI_STAT_NUM;
				riichi_flg = true;
			}else{
				tmp_kawa_mode =  kawa_mode[tmp_sute_idx];
				riichi_flg = false;
			}

			// �̔v�\��
			if(riichi_flg == true){
				// �̔v�\�� - ���[�`�v
				DispHai( tmp_x, tmp_y, kawa_tbl[tmp_sute_idx], kawa_tbl_aka[tmp_sute_idx], true,  tmp_kawa_mode, 0);
				tmp_y = tmp_y + HAI_YSIZE;
			}else{
				// �̔v�\�� - �ʏ�v
				DispLHai( tmp_x,  tmp_y, kawa_tbl[tmp_sute_idx], kawa_tbl_aka[tmp_sute_idx], false, tmp_kawa_mode, 0);    // Right1�i��
				tmp_y = tmp_y + LHAI_YSIZE;
			}

		}

	}

	// ----------------------------------------
	// �̔v�\��(2�i��)
	// ----------------------------------------
	if( kawa_tbl_count > 6){

		// �s�̔v����
		if(kawa_tbl_count > 12){
			line_sutehai_count = 6;
		}else{
			line_sutehai_count = kawa_tbl_count - 6;
		}

		// �s���[�`�m�F
		disp_riichi_flg = false;
		for(int tmp_i = 0; tmp_i < line_sutehai_count; tmp_i++){
			if( kawa_mode[tmp_i+6] >= RIICHI_STAT_NUM ){
				disp_riichi_flg = true;
				break;
			}
		}

		// �ϐ���`
		tmp_x = x + LHAI_XSIZE*1;
		tmp_y = y + LHAI_YSIZE*(LINE_SUTEHAI_COUNT_MAX-line_sutehai_count);  // �󔒕�����������

		// ���[�`�ʒu�̏C��
		if( disp_riichi_flg == true ){
			tmp_y=tmp_y-8;
		}

		// �̔v�\��(Right�v���[��)
		for(int tmp_i = 0; tmp_i < line_sutehai_count; tmp_i++){

			// �̔vINDEX�̒�`
			tmp_sute_idx = LINE_SUTEHAI_COUNT_MAX + line_sutehai_count - tmp_i - 1;

			// �v���[�h�m�F
			if( kawa_mode[tmp_sute_idx] >= RIICHI_STAT_NUM ){
				tmp_kawa_mode =  kawa_mode[tmp_sute_idx] - RIICHI_STAT_NUM;
				riichi_flg = true;
			}else{
				tmp_kawa_mode =  kawa_mode[tmp_sute_idx];
				riichi_flg = false;
			}

			// �̔v�\��
			if(riichi_flg == true){
				// �̔v�\�� - ���[�`�v
				DispHai( tmp_x, tmp_y, kawa_tbl[tmp_sute_idx], kawa_tbl_aka[tmp_sute_idx], true,  tmp_kawa_mode, 0);
				tmp_y = tmp_y + HAI_YSIZE;
			}else{
				// �̔v�\�� - �ʏ�v
				DispLHai( tmp_x,  tmp_y, kawa_tbl[tmp_sute_idx], kawa_tbl_aka[tmp_sute_idx], false, tmp_kawa_mode, 0);    // Right2�i��
				tmp_y = tmp_y + LHAI_YSIZE;
			}

		}


	}

	// ----------------------------------------
	// �̔v�\��(3�i��)
	// ----------------------------------------
	if( kawa_tbl_count > 12){

		// �s�̔v����
		if(kawa_tbl_count > 18){
			line_sutehai_count = 6;
		}else{
			line_sutehai_count = kawa_tbl_count - 12;
		}

		// �s���[�`�m�F
		disp_riichi_flg = false;
		for(int tmp_i = 0; tmp_i < line_sutehai_count; tmp_i++){
			if( kawa_mode[tmp_i+12] >= RIICHI_STAT_NUM ){
				disp_riichi_flg = true;
				break;
			}
		}

		// �ϐ���`
		tmp_x = x + LHAI_XSIZE*2;
		tmp_y = y + LHAI_YSIZE*(LINE_SUTEHAI_COUNT_MAX-line_sutehai_count);  // �󔒕�����������

		// ���[�`�ʒu�̏C��
		if( disp_riichi_flg == true ){
			tmp_y=tmp_y-8;
		}

		// �̔v�\��(Right�v���[��)
		for(int tmp_i = 0; tmp_i < line_sutehai_count; tmp_i++){

			// �̔vINDEX�̒�`
			tmp_sute_idx = LINE_SUTEHAI_COUNT_MAX*2 + line_sutehai_count - tmp_i - 1;

			// �v���[�h�m�F
			if( kawa_mode[tmp_sute_idx] >= RIICHI_STAT_NUM ){
				tmp_kawa_mode =  kawa_mode[tmp_sute_idx] - RIICHI_STAT_NUM;
				riichi_flg = true;
			}else{
				tmp_kawa_mode =  kawa_mode[tmp_sute_idx];
				riichi_flg = false;
			}

			// �̔v�\��
			if(riichi_flg == true){
				// �̔v�\�� - ���[�`�v
				DispHai( tmp_x, tmp_y, kawa_tbl[tmp_sute_idx], kawa_tbl_aka[tmp_sute_idx], true,  tmp_kawa_mode, 0);
				tmp_y = tmp_y + HAI_YSIZE;
			}else{
				// �̔v�\�� - �ʏ�v
				DispLHai( tmp_x,  tmp_y, kawa_tbl[tmp_sute_idx], kawa_tbl_aka[tmp_sute_idx], false, tmp_kawa_mode, 0);    // Right2�i��
				tmp_y = tmp_y + LHAI_YSIZE;
			}

		}

	}

	// ----------------------------------------
	// �̔v�\��(4�i��)
	// ----------------------------------------
	if( kawa_tbl_count > 18){

		// �s�̔v����
		line_sutehai_count = kawa_tbl_count - 18;

		// �s���[�`�m�F
		disp_riichi_flg = false;
		for(int tmp_i = 0; tmp_i < line_sutehai_count; tmp_i++){
			if( kawa_mode[tmp_i+18] >= RIICHI_STAT_NUM ){
				disp_riichi_flg = true;
				break;
			}
		}

		// �ϐ���`
		tmp_x = x + LHAI_XSIZE*3;
		tmp_y = y + LHAI_YSIZE*(LINE_SUTEHAI_COUNT_MAX-line_sutehai_count);  // �󔒕�����������

		// ���[�`�ʒu�̏C��
		if( disp_riichi_flg == true ){
			tmp_y=tmp_y-8;
		}

		// �̔v�\��(Right�v���[��)
		for(int tmp_i = 0; tmp_i < line_sutehai_count; tmp_i++){

			// �̔vINDEX�̒�`
			tmp_sute_idx = LINE_SUTEHAI_COUNT_MAX*3 + line_sutehai_count - tmp_i - 1;

			// �v���[�h�m�F
			if( kawa_mode[tmp_sute_idx] >= RIICHI_STAT_NUM ){
				tmp_kawa_mode =  kawa_mode[tmp_sute_idx] - RIICHI_STAT_NUM;
				riichi_flg = true;
			}else{
				tmp_kawa_mode =  kawa_mode[tmp_sute_idx];
				riichi_flg = false;
			}

			// �̔v�\��
			if(riichi_flg == true){
				// �̔v�\�� - ���[�`�v
				DispHai( tmp_x, tmp_y, kawa_tbl[tmp_sute_idx], kawa_tbl_aka[tmp_sute_idx], true,  tmp_kawa_mode, 0);
				tmp_y = tmp_y + HAI_YSIZE;
			}else{
				// �̔v�\�� - �ʏ�v
				DispLHai( tmp_x,  tmp_y, kawa_tbl[tmp_sute_idx], kawa_tbl_aka[tmp_sute_idx], false, tmp_kawa_mode, 0);    // Right2�i��
				tmp_y = tmp_y + LHAI_YSIZE;
			}

		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// �N���ʎq�̃p�[�c�\���FUP�v���[���\��
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispActSarashiParts_up(int x, int y, LBMen naki_stat, int hai_index, int aka_count){

	// ----------------------------------------
	// �ϐ��̏�����
	// ----------------------------------------
	int tmp_aka_count = aka_count;

	// ----------------------------------------
	// �|���v�̕\��
	// ----------------------------------------
	if( naki_stat == MINKO || naki_stat == ANKO ){

		// �N���v�̕\��
		for(int tmp_i = 0; tmp_i < 3; tmp_i++){
 			if( ( hai_index == 5 || hai_index == 15 || hai_index == 25) && tmp_aka_count > 0 ){
 				DispHai( x-HAI_XSIZE*tmp_i, y, hai_index, true, true,  0, 0);
				tmp_aka_count--;
			}else{
				DispHai( x-HAI_XSIZE*tmp_i, y, hai_index, false, true, 0, 0);
			}
		}

	// ----------------------------------------
	// �`�[�v�̕\��
	// ----------------------------------------
	}else if(naki_stat == MINSHUN || naki_stat == SHUNTSU ){

		// �N���v�̕\��(1����)
 		if( ( hai_index == 5 || hai_index == 15 || hai_index == 25) && tmp_aka_count > 0 ){
			DispHai( x-HAI_XSIZE*0, y, hai_index, true, true, 0, 0);
			tmp_aka_count--;
		}else{
			DispHai( x-HAI_XSIZE*0, y, hai_index, false, true, 0, 0);
		}

		// �N���v�̕\��(2����)
 		if( ( hai_index+1 == 5 || hai_index+1 == 15 || hai_index+1 == 25) && tmp_aka_count > 0 ){
			DispHai( x-HAI_XSIZE  , y, hai_index+1, true, true, 0, 0);
			tmp_aka_count--;
		}else{
			DispHai( x-HAI_XSIZE  , y, hai_index+1, false, true, 0, 0);
		}

		// �N���v�̕\��(3����)
 		if( ( hai_index+2 == 5 || hai_index+2 == 15 || hai_index+2 == 25) && tmp_aka_count > 0 ){
			DispHai( x-HAI_XSIZE*2, y, hai_index+2, true, true, 0, 0);
			tmp_aka_count--;
		}else{
			DispHai( x-HAI_XSIZE*2, y, hai_index+2, false, true, 0, 0);
		}

	// ----------------------------------------
	// �ÞȔv�̕\��
	// ----------------------------------------
	}else if(naki_stat == ANKAN){

		// �N���v�̕\��(�I�[�v��1����)
		if( tmp_aka_count > 0 ){
			DispHai( x-HAI_XSIZE  , y, hai_index, true, true, 0, 0);
		}else{
			DispHai( x-HAI_XSIZE  , y, hai_index, false, true, 0, 0);
		}

		// �N���v�̕\��(�I�[�v��2����)
		if( tmp_aka_count > 1 ){
			DispHai( x-HAI_XSIZE*2, y, hai_index, true, true, 0, 0);
		}else{
			DispHai( x-HAI_XSIZE*2, y, hai_index, false, true, 0, 0);
		}

		// �������v
		DispHai( x,             y, 0, false, false, 0, 0);
		DispHai( x-HAI_XSIZE*3, y, 0, false, false, 0, 0);

	// ----------------------------------------
	// ���Ȕv�̕\��
	// ----------------------------------------
	}else if(naki_stat == MINKAN){

		// �N���v�̕\��(�I�[�v��1����)
		if( tmp_aka_count > 0 ){
			DispHai( x            , y, hai_index, true, true, 0, 0);
		}else{
			DispHai( x            , y, hai_index, false, true, 0, 0);
		}

		// �N���v�̕\��(�I�[�v��2����)
		if( tmp_aka_count > 1 ){
			DispHai( x-HAI_XSIZE*1, y, hai_index, true, true, 0, 0);
		}else{
			DispHai( x-HAI_XSIZE*1, y, hai_index, false, true, 0, 0);
		}

		// �N���v�̕\��(�I�[�v��3����)
		if( tmp_aka_count > 2 ){
			DispHai( x-HAI_XSIZE*2, y, hai_index, true, true, 0, 0);
		}else{
			DispHai( x-HAI_XSIZE*2, y, hai_index, false, true, 0, 0);
		}

		// �N���v�̕\��(�I�[�v��4����)
		if( tmp_aka_count > 3 ){
			DispHai( x-HAI_XSIZE*3, y, hai_index, true, true, 0, 0);
		}else{
			DispHai( x-HAI_XSIZE*3, y, hai_index, false, true, 0, 0);
		}

	// ----------------------------------------
	// ���Ȕv�̕\��
	// ----------------------------------------
	}else if(naki_stat == KAKAN){

		// �N���v�̕\��(�I�[�v��4����)
		if( tmp_aka_count > 0 ){
			DispHai( x-HAI_XSIZE*3, y, hai_index, true, true, 0, 0);
		}else{
			DispHai( x-HAI_XSIZE*3, y, hai_index, false, true, 0, 0);
		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// �N���ʎq�̃p�[�c�\���FLEFT�v���[���\��
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispActSarashiParts_left(int x, int y, LBMen naki_stat, int hai_index, int aka_count){

	// ----------------------------------------
	// �ϐ��̏�����
	// ----------------------------------------
	int tmp_aka_count = aka_count;

	// ----------------------------------------
	// �|���v�̕\��
	// ----------------------------------------
	if( naki_stat == MINKO || naki_stat == ANKO ){

		// �N���v�̕\��
		for(int tmp_i = 0; tmp_i < 3; tmp_i++){
 			if( ( hai_index == 5 || hai_index == 15 || hai_index == 25) && tmp_aka_count > 0 ){
 				DispLHai( x, y+LHAI_YSIZE*tmp_i, hai_index, true, true,  0, 0);
				tmp_aka_count--;
			}else{
				DispLHai( x, y+LHAI_YSIZE*tmp_i, hai_index, false, true, 0, 0);
			}
		}

	// ----------------------------------------
	// �`�[�v�̕\��
	// ----------------------------------------
	}else if(naki_stat == MINSHUN || naki_stat == SHUNTSU ){

		// �N���v�̕\��(1����)
 		if( ( hai_index == 5 || hai_index == 15 || hai_index == 25) && tmp_aka_count > 0 ){
			DispLHai( x, y+LHAI_YSIZE*0, hai_index, true, true, 0, 0);
			tmp_aka_count--;
		}else{
			DispLHai( x, y+LHAI_YSIZE*0, hai_index, false, true, 0, 0);
		}

		// �N���v�̕\��(2����)
 		if( ( hai_index+1 == 5 || hai_index+1 == 15 || hai_index+1 == 25) && tmp_aka_count > 0 ){
			DispLHai( x, y+LHAI_YSIZE*1, hai_index+1, true, true, 0, 0);
			tmp_aka_count--;
		}else{
			DispLHai( x, y+LHAI_YSIZE*1, hai_index+1, false, true, 0, 0);
		}

		// �N���v�̕\��(3����)
 		if( ( hai_index+2 == 5 || hai_index+2 == 15 || hai_index+2 == 25) && tmp_aka_count > 0 ){
			DispLHai( x, y+LHAI_YSIZE*2, hai_index+2, true, true, 0, 0);
			tmp_aka_count--;
		}else{
			DispLHai( x, y+LHAI_YSIZE*2, hai_index+2, false, true, 0, 0);
		}

	// ----------------------------------------
	// �ÞȔv�̕\��
	// ----------------------------------------
	}else if(naki_stat == ANKAN){

		// �������v
		DispLHai( x, y+LHAI_YSIZE*0, 0, false, false, 0, 0);

		// �N���v�̕\��(�I�[�v��1����)
		if( tmp_aka_count > 0 ){
			DispLHai( x, y+LHAI_YSIZE*1, hai_index, true, true, 0, 0);
		}else{
			DispLHai( x, y+LHAI_YSIZE*1, hai_index, false, true, 0, 0);
		}

		// �N���v�̕\��(�I�[�v��2����)
		if( tmp_aka_count > 1 ){
			DispLHai( x, y+LHAI_YSIZE*2, hai_index, true, true, 0, 0);
		}else{
			DispLHai( x, y+LHAI_YSIZE*2, hai_index, false, true, 0, 0);
		}

		// �������v
		DispLHai( x, y+LHAI_YSIZE*3, 0, false, false, 0, 0);

	// ----------------------------------------
	// ���Ȕv�̕\��
	// ----------------------------------------
	}else if(naki_stat == MINKAN){

		// �N���v�̕\��(�I�[�v��1����)
		if( tmp_aka_count > 0 ){
			DispLHai( x, y+LHAI_YSIZE*0, hai_index, true, true, 0, 0);
		}else{
			DispLHai( x, y+LHAI_YSIZE*0, hai_index, false, true, 0, 0);
		}

		// �N���v�̕\��(�I�[�v��2����)
		if( tmp_aka_count > 1 ){
			DispLHai( x, y+LHAI_YSIZE*1, hai_index, true, true, 0, 0);
		}else{
			DispLHai( x, y+LHAI_YSIZE*1, hai_index, false, true, 0, 0);
		}

		// �N���v�̕\��(�I�[�v��3����)
		if( tmp_aka_count > 2 ){
			DispLHai( x, y+LHAI_YSIZE*2, hai_index, true, true, 0, 0);
		}else{
			DispLHai( x, y+LHAI_YSIZE*2, hai_index, false, true, 0, 0);
		}

		// �N���v�̕\��(�I�[�v��4����)
		if( tmp_aka_count > 3 ){
			DispLHai( x, y+LHAI_YSIZE*3, hai_index, true, true, 0, 0);
		}else{
			DispLHai( x, y+LHAI_YSIZE*3, hai_index, false, true, 0, 0);
		}

	// ----------------------------------------
	// ���Ȕv�̕\��
	// ----------------------------------------
	}else if(naki_stat == KAKAN){

		// �N���v�̕\��(�I�[�v��4����)
		if( tmp_aka_count > 0 ){
			DispLHai( x, y+LHAI_YSIZE*3, hai_index, true, true, 0, 0);
		}else{
			DispLHai( x, y+LHAI_YSIZE*3, hai_index, false, true, 0, 0);
		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// �N���ʎq�̃p�[�c�\���FRIGHT�v���[���\��
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispActSarashiParts_right(int x, int y, LBMen naki_stat, int hai_index, int aka_count){

	// ----------------------------------------
	// �ϐ��̏�����
	// ----------------------------------------
	int tmp_aka_count = aka_count;

	// ----------------------------------------
	// �|���v�̕\��
	// ----------------------------------------
	if( naki_stat == MINKO || naki_stat == ANKO ){

		// �N���v�̕\��
		for(int tmp_i = 0; tmp_i < 3; tmp_i++){
 			if( ( hai_index == 5 || hai_index == 15 || hai_index == 25) && tmp_aka_count > 0 ){
 				DispLHai( x, y+LHAI_YSIZE*tmp_i, hai_index, true,  false, 0, 0);
				tmp_aka_count--;
			}else{
				DispLHai( x, y+LHAI_YSIZE*tmp_i, hai_index, false, false, 0, 0);
			}
		}

	// ----------------------------------------
	// �`�[�v�̕\��
	// ----------------------------------------
	}else if(naki_stat == MINSHUN || naki_stat == SHUNTSU ){

		// �N���v�̕\��(1����)
 		if( ( hai_index+2 == 5 || hai_index+2 == 15 || hai_index+2 == 25) && tmp_aka_count > 0 ){
 				DispLHai( x, y+LHAI_YSIZE*0, hai_index+2, true,  false, 0, 0);
				tmp_aka_count--;
		}else{
				DispLHai( x, y+LHAI_YSIZE*0, hai_index+2, false, false, 0, 0);
		}

		// �N���v�̕\��(2����)
 		if( ( hai_index+1 == 5 || hai_index+1 == 15 || hai_index+1 == 25) && tmp_aka_count > 0 ){
 				DispLHai( x, y+LHAI_YSIZE*1, hai_index+1, true,  false, 0, 0);
				tmp_aka_count--;
		}else{
				DispLHai( x, y+LHAI_YSIZE*1, hai_index+1, false, false, 0, 0);
		}

		// �N���v�̕\��(3����)
 		if( ( hai_index   == 5 || hai_index   == 15 || hai_index   == 25) && tmp_aka_count > 0 ){
 				DispLHai( x, y+LHAI_YSIZE*2, hai_index  , true,  false, 0, 0);
				tmp_aka_count--;
		}else{
				DispLHai( x, y+LHAI_YSIZE*2, hai_index  , false, false, 0, 0);
		}

	// ----------------------------------------
	// �ÞȔv�̕\��
	// ----------------------------------------
	}else if(naki_stat == ANKAN){

		// �������v
		DispLHai( x, y,                 0,          false, false, 0, 0);

		// �N���v�̕\��(�I�[�v��1����)
		if( tmp_aka_count > 0 ){
			DispLHai( x, y+LHAI_YSIZE  , hai_index, true,  false, 0, 0);
		}else{
			DispLHai( x, y+LHAI_YSIZE  , hai_index, false, false, 0, 0);
		}

		// �N���v�̕\��(�I�[�v��2����)
		if( tmp_aka_count > 1 ){
			DispLHai( x, y+LHAI_YSIZE*2, hai_index, true,  false, 0, 0);
		}else{
			DispLHai( x, y+LHAI_YSIZE*2, hai_index, false, false, 0, 0);
		}

		// �������v
			DispLHai( x, y+LHAI_YSIZE*3, 0,         false, false, 0, 0);

	// ----------------------------------------
	// ���Ȕv�̕\��
	// ----------------------------------------
	}else if(naki_stat == MINKAN){

		// �N���v�̕\��(�I�[�v��1����)
		if( tmp_aka_count > 0 ){
			DispLHai( x, y  , hai_index, true,  false, 0, 0);
		}else{
			DispLHai( x, y  , hai_index, false, false, 0, 0);
		}

		// �N���v�̕\��(�I�[�v��2����)
		if( tmp_aka_count > 1 ){
			DispLHai( x, y+LHAI_YSIZE*1, hai_index, true,  false, 0, 0);
		}else{
			DispLHai( x, y+LHAI_YSIZE*1, hai_index, false, false, 0, 0);
		}

		// �N���v�̕\��(�I�[�v��3����)
		if( tmp_aka_count > 2 ){
			DispLHai( x, y+LHAI_YSIZE*2 , hai_index, true,  false, 0, 0);
		}else{
			DispLHai( x, y+LHAI_YSIZE*2 , hai_index, false, false, 0, 0);
		}

		// �N���v�̕\��(�I�[�v��4����)
		if( tmp_aka_count > 3 ){
			DispLHai( x, y+LHAI_YSIZE*3, hai_index, true,  false, 0, 0);
		}else{
			DispLHai( x, y+LHAI_YSIZE*3, hai_index, false, false, 0, 0);
		}

	// ----------------------------------------
	// ���Ȕv�̕\��
	// ----------------------------------------
	}else if(naki_stat == KAKAN){

		// �N���v�̕\��(�I�[�v��4����)
		if( tmp_aka_count > 0 ){
			DispLHai( x, y+LHAI_YSIZE*3, hai_index, true,  false, 0, 0);
		}else{
			DispLHai( x, y+LHAI_YSIZE*3, hai_index, false, false, 0, 0);
		}

	}
}

/* ---------------------------------------------------------------------------------------------- */
// �ȏ��̕\���FUP�v���[���\��
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispName_up(int x, int y, char *str){

	// �ȏ��̕\���FUP�v���[���\��
	DrawRotaString( x, y, 1.0, 1.0, 0, 0, PI, GetColor( 255, 255, 255 ), 0, FALSE, str);

}

/* ---------------------------------------------------------------------------------------------- */
// �ȏ��̕\���FLEFT�v���[���\��
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispName_left(int x, int y, char *str){

	// �ȏ��̕\���FLEFT�v���[���\��
	DrawRotaString( x, y, 1.0, 1.0, 0, 0, PI / 2.0, GetColor( 255, 255, 255 ), 0, FALSE, str);

}

/* ---------------------------------------------------------------------------------------------- */
// �ȏ��̕\���FRIGHT�v���[���\��
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispName_right(int x, int y, char *str){

	// �ȏ��̕\���FRIGHT�v���[���\��
	DrawRotaString( x, y, 1.0, 1.0, 0, 0, PI*3.0 / 2.0, GetColor( 255, 255, 255 ), 0, FALSE, str);

}

/* ---------------------------------------------------------------------------------------------- */
// �A�N�V�����v���[�g�\���FUP�v���[���\��
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispActplt_up(int x, int y, char *str){

	// �A�N�V�����v���[�g_UP
	DrawBox( x + 4 - 56, 
	         y + 4 - 23,
	         x + 4 ,
	         y + 4 ,
	         GetColor( 128, 0, 0 ), TRUE ) ;

	// �����\��_UP
	DrawRotaString( x, y,
	                1.0, 1.0, 0, 0, PI, GetColor( 255, 255, 255 ), 0, FALSE, str);

}

/* ---------------------------------------------------------------------------------------------- */
// �A�N�V�����v���[�g�\���FDOWN�v���[���\��
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispActplt_down(int x, int y, char *str){

	// �A�N�V�����v���[�g_DOWN
	DrawBox( x - 4, 
	         y - 4,
	         x - 4 + 56,
	         y - 4 + 23,
	         GetColor( 128, 0, 0 ), TRUE ) ;

	// �����\��_DOWN
	DispString( x, y, str);

}

/* ---------------------------------------------------------------------------------------------- */
// �A�N�V�����v���[�g�\���FLEFT�v���[���\��
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispActplt_left(int x, int y, char *str){

	// �A�N�V�����v���[�g_LEFT
	DrawBox( x + 4 - 23, 
	         y - 4 ,
	         x + 4 ,
	         y - 4 + 56,
	         GetColor( 128, 0, 0 ), TRUE ) ;

	// �����\��_LEFT
	DrawRotaString( x, y,
	                1.0, 1.0, 0, 0, PI / 2.0, GetColor( 255, 255, 255 ), 0, FALSE, str);

}

/* ---------------------------------------------------------------------------------------------- */
// �A�N�V�����v���[�g�\���FRIGHT�v���[���\��
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplayParts::DispActplt_right(int x, int y, char *str){

	// �A�N�V�����v���[�g_RIGHT
	DrawBox( x - 4, 
	         y + 4 - 56,
	         x - 4 + 23,
	         y + 4 ,
	         GetColor( 128, 0, 0 ), TRUE ) ;

	// �����\��_RIGHT
	DrawRotaString( x, y,
	                1.0, 1.0, 0, 0, PI * 3.0 / 2.0, GetColor( 255, 255, 255 ), 0, FALSE, str);

}

/* ---------------------------------------------------------------------------------------------- */
// �\�[�X�I��
/* ---------------------------------------------------------------------------------------------- */
