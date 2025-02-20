#define _CRT_SECURE_NO_WARNINGS
#include"speechManager.h"

void speakerManager::initSpeech() {
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->map_Person.clear();
	this->index = 1;
}

speakerManager::speakerManager() {
	this->initSpeech();
	this->createSpeaker();
}

speakerManager::~speakerManager() {

}

void speakerManager::showMenu() {
	cout << "---------- 1.开始演讲比赛 -----------" << endl;
	cout << "---------- 2.查看往届记录 -----------" << endl;
	cout << "---------- 3.清空比赛记录 -----------" << endl;
	cout << "---------- 0.退出比赛程序 -----------" << endl;
	cout << endl;

}

void speakerManager::exitSystem() {
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}

void speakerManager::createSpeaker() {
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++) {
		string name = "选手";
		name += nameSeed[i];
		Person p;
		p.name = name;
		for (int j = 0; j < 2; j++) {
			p.score[j] = 0;
		}
		this->v1.push_back(i + 10001);
		this->map_Person.insert(make_pair(i + 10001, p));
	}
}

void speakerManager::shuffle() {
	cout << "第" << this->index << "次抽签开始" << endl;
	cout << "抽签后演讲顺序如下 : " << endl;
	if (this->index == 1) {
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++) {
			cout << *it << " ";
		}
		cout << endl;
	}
	else {
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++) {
			cout << *it << " ";
		}
		cout << endl;
	}
	cout << "---------------------" << endl;
	system("pause");
	cout << endl;
}


void speakerManager::speechContest() {
	cout << "-------- 第" << this->index << " 轮比赛正式开始 ------------" << endl;
	int num = 0;
	vector<int> src;
	multimap<double, int, greater<double>> temp;
	if (this->index == 1)
		src = v1;
	else
		src = v2;
	for (vector<int>::iterator it = src.begin(); it != src.end(); it++) {
		num++;
		deque<double> d;
		for (int i = 0; i < 10; i++) {
			double score = (rand() % 401 + 600) / 10.f;
			d.push_back(score);
		}
		sort(d.begin(), d.end(), greater<double>());
		d.pop_back();
		d.pop_front();
		double sum = accumulate(d.begin(), d.end(), 0.0f);
		double avg = sum / (double)d.size();
		this->map_Person[*it].score[this->index - 1] = avg;
		temp.insert(make_pair(avg, *it));

		if (num % 6 == 0) {
			cout << "第" << num / 6 << "小组比赛名次：" << endl;
			for (multimap<double, int, greater<double>>::iterator itt = temp.begin(); itt != temp.end(); itt++) {
				cout << "编号: " << itt->second << "姓名: " << this->map_Person[itt->second].name << "成绩: " << this->map_Person[itt->second].score[this->index - 1] << endl;
			}

			int count = 0;
			for (multimap<double, int, greater<double>>::iterator itt = temp.begin(); itt != temp.end() && count < 3; itt++,count++) {
				if (this->index == 1) {
					v2.push_back(itt->second);
				}
				else {
					vVictory.push_back(itt->second);
				}
			}
			temp.clear();
			cout << endl;
		}
		
	}
	cout << "------------- 第" << this->index << "轮比赛完毕  ------------- " << endl;
	system("pause");
}

void speakerManager::showScore() {
	vector<int> v;
	if (this->index == 1)
		v = v2;
	else
		v = vVictory;
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
		cout << "编号: " << *it << "姓名: " << this->map_Person[*it].name << "成绩: " << this->map_Person[*it].score[this->index - 1] << endl;
	}
	cout << endl;

	system("pause");
	system("cls");
	//this->showMenu();
}


void speakerManager::startSpeech() {
	this->shuffle();
	this->speechContest();
	this->showScore();

	this->index++;

	this->shuffle();
	this->speechContest();
	this->showScore();


	cout << "本届比赛完毕！" << endl;
	system("pause");
	system("cls");
}
