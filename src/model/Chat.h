#pragma once
#include <iostream>
#include "sqlite3.h"
#include<stdio.h>
#include <list>
using namespace std;
class Chat
{
public:
	Chat();
	~Chat();
public:
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	const char *szSQL;
	const char *pzTest;
	sqlite3_stmt *stmt;
	list<string> answer;
public:
	void Open();
	int Select_login(sqlite3 *db, char *fn, char *ln);

	void Insert_Acc(sqlite3 *db, char *a, char *a1, char *a2, char *a3,char *a4,char *a5);

	void SelectMess(sqlite3 *db, int id);
	int Seach_fr(char *frien);
	void ShowMessDetail(sqlite3 *db, int id1, int id2);
	bool CheckFriend(sqlite3 *db, int id1, int id2);
	bool CheckBlock(sqlite3 *db, int id1, int id2);
	void WriteToFriend(sqlite3 *db, int id1, int id2);
	void ShowFriend(sqlite3 *db, int id1);
	void ShowFriendDetail(sqlite3 *db, int id2);
	void BlockFriend(sqlite3 *db, int id1, int id2);
	void UpdateFriend(sqlite3 *db, char *na, char *ge, char *add,int id);
	void WriteToMess(sqlite3 *db, int id1, int id2, char *mes, char *time,int tt);
	void update_tt(sqlite3 *db, int id1, int id2);
	void ShowSendMess(sqlite3 *db, int id);
	void ShowRecMess(sqlite3 *db, int id);
	void Group(sqlite3 *db, int id, char *name, char* address);
};

