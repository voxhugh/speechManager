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

			/*接口*/


	//构造
	SpeechManager();

	//展示菜单
	void showMenu();

	//退出系统
	void exitSystem();

	//属性初始化
	void init();

	//选手创建
	void createSpeaker();

	//开始比赛
	void startContest();

	//抽签
	void draw();

	//比赛
	void speechContest();

	//显示比赛结果
	void showScore();

	//保存记录
	void saveRecord();

	//读取记录
	void loadRecord();

	//显示往届记录
	void showRecord();

	//清空记录
	void clearRecord();

	//析构
	~SpeechManager();

			/*属性*/


	//第一轮选手编号
	vector<int> v1;

	//第二轮选手编号
	vector<int> v2;

	//获胜选手编号
	vector<int> vVictory;

	//<编号,选手>
	map<int, Speaker> m_Speaker;

	// 当前比赛轮数
	int m_Index;

	//文件是否为空标志
	bool fileIsEmpty;

	//往届记录
	map<int, vector<string>> m_Record;
};