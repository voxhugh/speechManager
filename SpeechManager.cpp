#include "SpeechManager.h"


//构造
SpeechManager::SpeechManager()
{
	//初始化属性
	this->init();

	//创建12名选手
	this->createSpeaker();

	//从磁盘读取数据
	this->loadRecord();

}
//展示菜单
void SpeechManager::showMenu()
{

	cout << "****************************************************" << endl;
	cout << "****************** 欢迎参加演讲比赛 ****************" << endl;
	cout << "****************** 1.开始演讲比赛 ******************" << endl;
	cout << "****************** 2.查看往届记录 ******************" << endl;
	cout << "****************** 3.清空比赛记录 ******************" << endl;
	cout << "****************** 0.退出比赛程序 ******************" << endl;
	cout << "****************************************************" << endl;
	cout << endl;

}

//退出系统
void SpeechManager::exitSystem()
{
	cout << "欢迎下次使用！" << endl;
	system("pause");
	exit(0);

}

//属性初始化
void SpeechManager::init()
{
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();
	this->m_Index = 1;
	this->m_Record.clear();

}

//选手创建
void SpeechManager::createSpeaker()
{
	string nameSeed = "ABCDEFGHIJKL";
	
	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name = "选手";
		name += nameSeed[i];
		
		Speaker sp;
		for (int i = 0; i < 2; i++)
		{
			sp.m_Score[i] = 0;
		}
		sp.m_Name = name;
		//存入第一轮容器
		this->v1.push_back(10001+i);
		//存入<int,Speaker>
		this->m_Speaker.insert(make_pair(10001 + i, sp));
	}

}

//开始比赛
void SpeechManager::startContest()
{
	//第一轮抽签
	this->draw();
	//初赛
	this->speechContest();
	//显示结果
	this->showScore();
	
	this->m_Index++;

	//第二轮抽签
	this->draw();
	//决赛
	this->speechContest();
	//显示结果
	this->showScore();

	//保存记录
	this->saveRecord();

	cout << "本届比赛完毕！" << endl;

	system("pause");
	system("cls");

	//更新状态
	this->init();
	this->createSpeaker();
	this->loadRecord();
}

//抽签
void SpeechManager::draw()
{

	cout << "第 <<" << this->m_Index << ">> 轮比赛选手正在抽签..." << endl;
	cout << "----------------------------" << endl;
	cout << "抽签后演讲顺序如下：" << endl;
	if (this->m_Index == 1)
	{
		//洗牌
		random_shuffle(this->v1.begin(), this->v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
		}
	}
	else
	{
		random_shuffle(this->v2.begin(), this->v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
		{
			cout << *it << " ";
		}
	}
	cout << endl;
	cout << "----------------------------" << endl;
	system("pause");

}


//比赛
void SpeechManager::speechContest()
{
	cout << "----------------第 " << this->m_Index << " 轮正式比赛开始-----------------" << endl;
	vector<int> src;
	if (this->m_Index == 1)
	{
		src = this->v1;
	}
	else
	{
		src = this->v2;
	}
	//每六人一组
	multimap<double, int,greater<double>>groupMod6;
	//记录当前遍历的人数
	int indexSpeaker = 0;

	for (vector<int>::iterator it = src.begin(); it != src.end(); it++)
	{

		indexSpeaker++;
		//记录评委打分
		deque<double> sc;
		//循环打分10次
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600)/10.f;
			sc.push_back(score);
		}

		//降序排列
		sort(sc.begin(), sc.end(), greater<double>());

		//去头去尾
		sc.pop_front();
		sc.pop_back();

		//求平均分

		double sum =accumulate(sc.begin(), sc.end(),0.0f);
		double avg = sum / (double)sc.size();
		//通过索引将平均分存入维护的<int,Speaker>中
		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;

		//分组处理
		groupMod6.insert(make_pair(avg, *it));


		//满6人公布小组内名次
		if (indexSpeaker % 6 == 0)
		{
			//降序遍历小组容器，打印比赛名次

			cout << "第" << indexSpeaker/6 << "小组比赛名次：" << endl;
			for (multimap<double, int,greater<double>>::iterator mit = groupMod6.begin(); mit != groupMod6.end(); mit++)
			{
				cout << "编号：" << mit->second << "\t姓名：" << this->m_Speaker[mit->second].m_Name << "\t成绩：" <<
					mit->first << endl;
			}
			cout << endl;
			//再次遍历前三名
			int bfThree = 0;
			for (multimap<double, int, greater<double>>::iterator mit = groupMod6.begin(); mit != groupMod6.end() && bfThree<3; mit++, bfThree++)
			{
				if (this->m_Index == 1)
				{
					this->v2.push_back(mit->second);
				}
				else
				{

					this->vVictory.push_back(mit->second);
				}
			}
			//清空小组容器
			groupMod6.clear();
		}

	}
	cout << "----------------第 " << this->m_Index << " 轮比赛完毕！-----------------" << endl;
	system("pause");

}

//显示比赛结果
void SpeechManager:: showScore()
{
	cout << "----------------第" << this->m_Index << "轮晋级选手如下：----------------" << endl;
	vector<int> v;
	if (this->m_Index == 1)
	{
		v = this->v2;
	}
	else
	{
		v = this->vVictory;
	}

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "选手编号：" << *it << "\t姓名：" << this->m_Speaker[*it].m_Name << "\t得分：" << this->m_Speaker[*it].m_Score[this->m_Index - 1] << endl;

	}
	system("pause");
	system("cls");
	this->showMenu();
}

//保存记录
void SpeechManager::saveRecord()
{
	ofstream ofs;
	ofs.open("./speech.csv", ios::out | ios::app);

	for (vector<int>::iterator it = this->vVictory.begin(); it != this->vVictory.end(); it++)
	{
		ofs << *it << "," << this->m_Speaker[*it].m_Score[this->m_Index - 1] << ",";
	}
	ofs << endl;			//一届一行记录，bug:错敲成cout会导致每届记录都在同一行
	ofs.close();
	cout << "记录已保存！" << endl;
	this->fileIsEmpty = false;

}

//读取记录
void SpeechManager::loadRecord()
{
	ifstream ifs("./speech.csv",ios::in);

	//文件不存在
	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
		//cout << "文件不存在" << endl;
		ifs.close();
		return;
	}

	//文件为空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		this->fileIsEmpty = true;
		//cout << "记录为空" << endl;
		ifs.close();
		return;
	}

	//文件存在且记录不为空
	this->fileIsEmpty = false;

	//读回第一个字符
	ifs.putback(ch);

	int index = 0;		//届数
	string rowData;		//一行数据
	while (ifs >> rowData)			//行行读取
	{
		int pos = -1;				//记录逗号位置
		int start =0;				//子串起始位置
		vector<string> v6;		//记录一行六个数据

		while (true)
		{
			pos = rowData.find(",",start);		//bug:这里一开始漏了第二个参数，导致每次默认从0索引，陷入 取子串—赋值 死循环
			if (pos == -1)
			{
				//cout << "未找到" << endl;
				break;
			}
			string temp = rowData.substr(start, pos - start);
			v6.push_back(temp);
			start = pos + 1;
		}
		this->m_Record.insert(make_pair(index, v6));
		index++;

	}
	ifs.close();		//bug:错放到循环体内会导致只能读一行
}

//显示往届记录
void SpeechManager::showRecord()
{
	if (this->fileIsEmpty)
	{
		cout << "文件不存在，或记录为空！" << endl;
		system("pause");
		system("cls");
		return;
	}

	for (int i = 0; i < this->m_Record.size(); i++)
	{
		cout << "<第" << i + 1 << "届>" << endl;
		cout << "冠军编号：" << this->m_Record[i][0] << " 得分：" << this->m_Record[i][1] << "\t"
			<< "亚军编号：" << this->m_Record[i][2] << " 得分：" << this->m_Record[i][3] << "\t"
		 << "季军编号：" << this->m_Record[i][4] << " 得分：" << this->m_Record[i][5] << endl;
	}
	system("pause");
	system("cls");
}

//清空记录
void SpeechManager:: clearRecord()
{
	cout << "确定清空？" << endl;
	int select = 2;
	cout << "1、确定" << endl;
	cout << "2、返回" << endl;
	cin >> select;
	if (select == 1)
	{
		ofstream ofs("./speech.csv", ios::trunc);

		//更新状态
		this->fileIsEmpty = true;
		this->init();
		this->createSpeaker();
		this->loadRecord();

		cout << "记录已清空！" << endl;
		ofs.close();

	}
	system("pause");
	system("cls");
}
//析构
SpeechManager::~SpeechManager()
{


}