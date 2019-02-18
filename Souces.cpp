#include "DxLib.h"
#define HIT 200

int SARA1, SARA2, SARA3;
int black = GetColor(255, 255, 0);
int red = GetColor(255, 0, 0);
int HitX[HIT], HitY[HIT], HitFlag[HIT], HitTime[HIT];
int mouseFlag = 0;
int i;
int life = 5;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	//windowӰ�ށ@�������@�E�B���h�E�e�L�X�g
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); SetMainWindowText("���SARA�E���}��"); 
	SetGraphMode(432, 720, 32);
	
	//�摜�ǂݍ���
	SARA1 = LoadGraph("img_SARA.png");
	SARA2 = LoadGraph("img_SARA02.png");
	SARA3 = LoadGraph("img_SARA03.png");


	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {

		//�摜�o�͂Ƒ̗͂̏o��
		DrawGraph(0, 0, SARA1, TRUE);
		DrawFormatString(0, 0, black, "SARA�̗̑�%d", life);

		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
			if (mouseFlag == 0) {
				// �}�E�X�̃N���b�N���������ꏊ�œ��������Ƃ݂Ȃ�
				int mx = 0, my = 0;
				GetMousePoint(&mx, &my);
				for (i = 0; i < HIT; i++) {
					if (HitFlag[i] == 0) {
						HitX[i] = mx;
						HitY[i] = my;
						HitFlag[i] = 1;
						HitTime[i] = GetNowCount();
						break;
					}
				}
			}
			mouseFlag = 1;
		}
		else mouseFlag = 0;

		// �q�b�g�G�t�F�N�g��`�悷��
		for (i = 0; i < HIT; i++) {

			if (HitFlag[i] == 1) {
				DrawGraph(0, 0, SARA2, TRUE);
				// DrawRectGraph(HitX[i], HitY[i] - 10, 224, 32, 32, 32, hitgraph, TRUE, FALSE);
				DrawString(HitX[i], HitY[i], "�U", GetColor(255, 0, 0));

				if (GetNowCount() - HitTime[i] > 2000) {
					HitFlag[i] = 0; // 2�b�o���Ă��������
					life = life - 1;
				}
			}

		}
		if (life == 0) {
			break;
		}

		
	}
	DrawGraph(0, 0, SARA3, TRUE);
	DrawFormatString(0, 0, red, "SARA�����ɂ܂����B");
	DrawFormatString(0, 20, red, "�ǂꂩ�̃L�[����͂���ƏI�����܂��B");

	WaitKey();
	DxLib_End();
	return 0;
}