#pragma once
#include <array>
#include <string>

// �t�B�[���h�̏󋵂�\��
// vector �^�Ŏ������Ă����̂� array �^�Ŏ������Ă݂�
// 78�ʂ肵���Ȃ��̂� i*FIELD_WIDTH+j �Ƃ�������z������O�ɍ쐬����������������
class FIELD_ARRAY
{
public:
	std::array<char, FIELD_WIDTH * FIELD_HEIGHT> field;
	// char �^1�����z��
	// ���ォ�牺�Ɍ������� 0, 1, 2, ..., 77( = 13 * 6 - 1)
	// �Ƃ��������s�����ǂ����A�E�ɑ�������悤�ɂȂ�����Ȃ��ĂȂ������肵�Ă�̂ŗv�C��
	FIELD_ARRAY();									// �R���X�g���N�^
	char at(int x, int y);							// �Ղ�̐F��Ԃ�
	void showColor(char c);							// �F�t���Ń^�[�~�i���Ƀt�B�[���h�̏󋵂�`�悷�邽�߂̉�����
	void show();
	void show(bool isFlush);						// �F�t���Ń^�[�~�i���Ƀt�B�[���h�̏󋵂�`�悷��
	void show_with_cursol(int x, int y);			// x, y �ɃJ�[�\����\������ver
	void set_puyo(int x, int y, char puyoColor);	// x, y �ɂՂ���Z�b�g����
	void set_template(std::string key);				// �����̃e���v���[�g�t�B�[���h���Z�b�g����(Kenny��19�A���Ȃ�)
	void pop_top(int x);							// �� x �̍ŏ�ʂՂ�����


};

