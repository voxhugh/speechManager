#pragma once
#include <iostream>
using namespace std;
#include <vector>
#include <map>
#include "Speaker.h"
#include <string>
#include <algorithm>
#include <map>
#include <functional>
#include <deque>
#include <numeric>
#include <fstream>
#include <ctime>

class SpeechManager
{


public:

			/*�ӿ�*/


	//����
	SpeechManager();

	//չʾ�˵�
	void showMenu();

	//�˳�ϵͳ
	void exitSystem();

	//���Գ�ʼ��
	void init();

	//ѡ�ִ���
	void createSpeaker();

	//��ʼ����
	void startContest();

	//��ǩ
	void draw();

	//����
	void speechContest();

	//��ʾ�������
	void showScore();

	//�����¼
	void saveRecord();

	//��ȡ��¼
	void loadRecord();

	//��ʾ�����¼
	void showRecord();

	//��ռ�¼
	void clearRecord();

	//����
	~SpeechManager();

			/*����*/


	//��һ��ѡ�ֱ��
	vector<int> v1;

	//�ڶ���ѡ�ֱ��
	vector<int> v2;

	//��ʤѡ�ֱ��
	vector<int> vVictory;

	//<���,ѡ��>
	map<int, Speaker> m_Speaker;

	// ��ǰ��������
	int m_Index;

	//�ļ��Ƿ�Ϊ�ձ�־
	bool fileIsEmpty;

	//�����¼
	map<int, vector<string>> m_Record;
};