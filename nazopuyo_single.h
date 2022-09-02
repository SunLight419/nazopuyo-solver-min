#pragma once
#include "FIELD_ARRAY.h"
#include "CHAIN.h"
#include <vector>
// �Ȃ��Ղ�������N���X(�V���O���X���b�h)
// �}���`�X���b�h�̓R�[�h�������Ⴒ���Ⴕ�Ă̂łƂ肠����
// pthread��p���Ă�����std::thread�ŗǂ�?
class nazopuyo_single : public CHAIN
{
public:
	int nextPuyoNum; // �l�N�X�g�Ղ�̐� �T��U�肮�炢���甚������
	int goalChainNum; // �ڕW�A����
	std::array<char, 20> nextPuyos; // �Ƃ肠����10�蕪�m��

	long long visitedNodes = 0; // �T������(n�肷�ׂĒu����)�ǖʂ̐�
	long long totalNodes = 1;
	bool isAnswerFound = false; // ���������������ǂ���

	//std::array<char, FIELD_WIDTH* FIELD_HEIGHT> ansField; // �����p�̃t�B�[���h

	void set_totalNodes();

	// field ���R�s�[����֐�
	// �X�}�[�g�ɂ�����@�킩���
	void copy_field(std::array<char, FIELD_WIDTH* FIELD_HEIGHT>& from, std::array<char, FIELD_WIDTH* FIELD_HEIGHT>& to);
	
	void show_nextPuyos();

	void set_nextPuyo();
	void set_goalChainNum();
	void solve_nazopuyo(); // ��{�I�ɂ͂�����Ăяo���ΑS������Ă����

	std::vector<std::pair<int, int>> parPos = {
		{0, 0}, {0, 0}, {0, 1}, {0, 0},
	};

	std::vector<std::pair<int, int>> childPos = {
		{0, 1}, {-1, 0}, {0, 0}, {1, 0},
	};

	// ��Ղ��[���D��T���ŉ���
	// idx: ����ڂ̑g�݂Ղ悩
	void nazoDFS(int idx);
};

