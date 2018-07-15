#include "Chat.h"
#include <sstream>
using namespace std;
Chat::Chat(){}
Chat::~Chat(){}
void Chat::Open() {
	rc = sqlite3_open("chat.db", &db);
	if (rc) {
		cout << "- Can't open database" << sqlite3_errmsg(db) << endl;
		exit(0);
	}else {}
}
int Chat::Select_login(sqlite3 *db, char *us, char *pa) {
	int id = 0;
	szSQL = "SELECT * FROM  user WHERE username = ? and password = ? ";
	rc = sqlite3_prepare(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		// bind the value
		sqlite3_bind_text(stmt, 1, us, strlen(us), 0);
		sqlite3_bind_text(stmt, 2, pa, strlen(pa), 0);
		// commit
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			stringstream str;
			str << sqlite3_column_text(stmt, 0);
			str >> id;
		}
		sqlite3_finalize(stmt);
	}
	else {
		cout << "+================+ SQL error: +================+" << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
	return id;
}
void Chat::Insert_Acc(sqlite3 *db, char *user, char *pass,char *ge, char *bir, char *na,char *add) {
	szSQL = "insert into user (username, password,gender,birth,name,address) values (?,?,?,?,?,?)";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		sqlite3_bind_text(stmt, 1, user, strlen(user), 0);
		sqlite3_bind_text(stmt, 2, pass, strlen(pass), 0);
		sqlite3_bind_text(stmt, 3, ge, strlen(ge), 0);
		sqlite3_bind_text(stmt, 4, bir, strlen(bir), 0);
		sqlite3_bind_text(stmt, 5, na, strlen(na), 0);
		sqlite3_bind_text(stmt, 6, add, strlen(add), 0);
		sqlite3_step(stmt);
		sqlite3_finalize(stmt);
	}
	else {
		cout << "+================+ SQL error: +================+" << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
}
void Chat::SelectMess(sqlite3 *db, int zID) {
	if (!db)return;
	szSQL = "select messenger.contend from messenger,user where user.id=messenger.idsen and user.id=?";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		sqlite3_bind_int(stmt, 1, zID);
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			answer.push_back(string((const char *)sqlite3_column_text(stmt, 0)));
		}
		sqlite3_finalize(stmt);
		cout << "+================+ Danh sach tin nhan +================+\n\n";
		for (list<std::string>::const_iterator it = answer.begin(); it != answer.end(); it++)
			cout << *it << endl;
	}
	else {
		cout << "+================+ SQL error: +================+" << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
}
int Chat::Seach_fr(char *frien) {
	int id2 = -1;
	szSQL = "SELECT id FROM user WHERE username = ?";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		sqlite3_bind_text(stmt, 1, frien, strlen(frien), 0);
		if (sqlite3_step(stmt) == SQLITE_ROW) {
			stringstream str;
			str << sqlite3_column_text(stmt, 0);
			str >> id2;
		}
		sqlite3_finalize(stmt);
	}
	else {
		cout << "+================+ SQL error: +================+" << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
	return id2;
}
void Chat::ShowMessDetail(sqlite3 *db, int id1, int id2) {
	if (!db)return;
	cout << " +\n================+ Mess Detail +================+\n";
	szSQL = "SELECT * FROM messenger,user WHERE(idsen = ? OR idsen = ?) AND(idrec = ? OR idrec = ?) and user.id = messenger.idsen";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	// cout << id1 << id2;
	if (rc == SQLITE_OK) {
		// bind the value
		sqlite3_bind_int(stmt, 1, id1);
		sqlite3_bind_int(stmt, 2, id2);
		sqlite3_bind_int(stmt, 3, id1);
		sqlite3_bind_int(stmt, 4, id2);
		// commit
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			cout << string((const char *)sqlite3_column_text(stmt, 5)) << ": " << endl;
			cout << "	"<< string((const char *)sqlite3_column_text(stmt, 2)) << " - ";
			cout << string((const char *)sqlite3_column_text(stmt, 3)) << endl;

		}
		sqlite3_finalize(stmt);
	}
	else {
		cout << "+================+ SQL error: +================+" << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
}
void Chat::UpdateFriend(sqlite3 *db, char *gender,char *name, char *address,int id) {
	if (!db)return;
	szSQL = "INSERT INTO user1 (gender1,name1,address1,id1) VALUES (?,?,?,?)";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		int isblock = 0;
		sqlite3_bind_text(stmt, 1, gender, strlen(gender), 0);
		sqlite3_bind_text(stmt, 2, name, strlen(name), 0);
		sqlite3_bind_text(stmt, 2, address, strlen(address), 0);
		sqlite3_bind_int(stmt, 1, id);

		sqlite3_step(stmt);
		sqlite3_finalize(stmt);
	}
	else {
		cout << "+================+ SQL error: +================+" << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
}
bool Chat::CheckFriend(sqlite3 *db, int id1, int id2) {
	int isFriend = 0;
	szSQL = "SELECT * FROM friend WHERE ( id1 = ? AND id2 = ?) OR ( id1 = ? AND id2 = ?)";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		// bind the value
		sqlite3_bind_int(stmt, 1, id1);
		sqlite3_bind_int(stmt, 2, id2);
		sqlite3_bind_int(stmt, 3, id2);
		sqlite3_bind_int(stmt, 4, id1);
		// commit
		if (sqlite3_step(stmt) == SQLITE_ROW) {
			stringstream str;
			str << sqlite3_column_text(stmt, 0);
			str >> isFriend;
			if (isFriend != 0) isFriend = 1;
			else isFriend = 0;
			sqlite3_finalize(stmt);
		}
	}
	else {
		cout << "+================+ SQL error: +================+" << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
	return isFriend;
}
bool Chat::CheckBlock(sqlite3 *db, int id1, int id2) {
	int isblock = 0;
	if (!db)return 0;
	szSQL = "SELECT isblock FROM friend WHERE (id1 = ? AND id2 = ?)";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		// bind the value
		sqlite3_bind_int(stmt, 1, id2);
		sqlite3_bind_int(stmt, 2, id1);
		// commit
		if (sqlite3_step(stmt) == SQLITE_ROW) {
			stringstream str;
			str << sqlite3_column_text(stmt, 0);
			str >> isblock;
		}
		sqlite3_finalize(stmt);
	}
	else {
		cout << "+================+ SQL error: +================+" << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
	return isblock;
}
void Chat::WriteToFriend(sqlite3 *db, int id1, int id2) {
	if (!db)return;
	szSQL = "INSERT INTO friend VALUES (?,?,?),(?,?,?)";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		
		int isblock = 0;
		sqlite3_bind_int(stmt, 1, id1);
		sqlite3_bind_int(stmt, 2, id2);
		sqlite3_bind_int(stmt, 3, isblock);
		sqlite3_bind_int(stmt, 4, id2);
		sqlite3_bind_int(stmt, 5, id1);
		sqlite3_bind_int(stmt, 6, isblock);
	
		sqlite3_step(stmt);
		sqlite3_finalize(stmt);
	}
	else {
		cout << "+================+ SQL error: +================+" << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
}
void Chat::ShowFriend(sqlite3 *db, int id1) {
	cout << " +================+ List Friends +================+ \n";
	if (!db)return;
	szSQL = "SELECT DISTINCT user.username FROM (SELECT * FROM friend where (id1 = ?) AND isblock = 0) as A LEFT JOIN user ON (A.id2 = user.id)";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {

		sqlite3_bind_int(stmt, 1, id1);
		
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			cout << string((const char *)sqlite3_column_text(stmt, 0)) << endl;
		}
		sqlite3_finalize(stmt);
	}
	else {
		cout << "+================+ SQL error: +================+" << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
}
void Chat::ShowSendMess(sqlite3 *db, int id1) {
	cout << " +================+ Tin Nhan Da Gui +================+ \n";
	if (!db)return;
	szSQL = "SELECT contend FROM messenger where idsen=?";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {

		sqlite3_bind_int(stmt, 1, id1);

		while (sqlite3_step(stmt) == SQLITE_ROW) {
			cout << string((const char *)sqlite3_column_text(stmt, 0)) << endl;
		}
		sqlite3_finalize(stmt);
	}
	else {
		cout << "+================+ SQL error: +================+" << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
}
void Chat::ShowRecMess(sqlite3 *db, int id1) {
	cout << " +================+ Tin Nhan Da Nhan +================+ \n";
	if (!db)return;
	szSQL = "SELECT contend FROM messenger where idrec=?";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {

		sqlite3_bind_int(stmt, 1, id1);

		while (sqlite3_step(stmt) == SQLITE_ROW) {
			cout << string((const char *)sqlite3_column_text(stmt, 0)) << endl;
		}
		sqlite3_finalize(stmt);
	}
	else {
		cout << "+================+ SQL error: +================+" << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
}
void Chat::Group(sqlite3 *db, int id, char *name, char* address) {
	cout << "\n\n+================+ Ban be cung thanh pho +================+ \n";
	if (!db)return;
	szSQL = "SELECT DISTINCT user.address FROM (SELECT * FROM friend where (id1 = ?) AND isblock = 0) as A LEFT JOIN user ON (A.id2 = user.id)";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {

		sqlite3_bind_int(stmt, 1, id);
		/*sqlite3_bind_text(stmt, 5, name, strlen(name), 0);
		sqlite3_bind_text(stmt, 6, address, strlen(address), 0);*/
		


		while (sqlite3_step(stmt) == SQLITE_ROW) {
			cout << string((const char *)sqlite3_column_text(stmt, 0)) << endl;
		}
		sqlite3_finalize(stmt);
	}
	else {
		cout << "+================+ SQL error: +================+" << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
}
void Chat::ShowFriendDetail(sqlite3 *db,int id2) {
	cout << "\n+================+ Friend Detail +================+\n\n";
	if (!db)return;
	szSQL = "SELECT *FROM user Where id = ?";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		// bind the value
		sqlite3_bind_int(stmt, 1, id2);
		// commit
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			//cout << string((const char *)sqlite3_column_text(stmt, 0)) << endl; // not show id
			cout << string((const char *)sqlite3_column_text(stmt, 1)) << endl;
			//cout << string((const char *)sqlite3_column_text(stmt, 2)) << endl; // not show password
			cout << string((const char *)sqlite3_column_text(stmt, 3)) << endl;
			cout << string((const char *)sqlite3_column_text(stmt, 4)) << endl;
			cout << string((const char *)sqlite3_column_text(stmt, 5)) << endl;
			cout << string((const char *)sqlite3_column_text(stmt, 6)) << endl;
		}
		sqlite3_finalize(stmt);
		cout << "+================================================+\n";
	}
	else {
		cout << "+================+SQL error: +================+" << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
}
void Chat::BlockFriend(sqlite3 *db, int id1, int id2) {
	if (!db)return;
	szSQL = "UPDATE friend SET isblock = 1 WHERE id1 = ? AND id2 = ?";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		// bind the value
		sqlite3_bind_int(stmt, 1, id1);
		sqlite3_bind_int(stmt, 2, id2);
		// commit
		sqlite3_step(stmt);
		sqlite3_finalize(stmt);
	}
	else {
		cout << "+================+ SQL error: +================+" << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
}
void Chat::WriteToMess(sqlite3 *db, int id1, int id2, char *mes, char *time,int tt) {
	szSQL = "INSERT INTO messenger VALUES (?,?,?,?,?)";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		// bind the value
		sqlite3_bind_int(stmt, 1, id1);
		sqlite3_bind_int(stmt, 2, id2);
		sqlite3_bind_text(stmt, 3, mes, strlen(mes), 0);
		sqlite3_bind_text(stmt, 4, time, strlen(time), 0);
		sqlite3_bind_int(stmt, 5, tt);
		// commit
		sqlite3_step(stmt);
		sqlite3_finalize(stmt);
	}
	else {
		cout << "+================+ SQL error: +================+" << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}

}
void Chat::update_tt(sqlite3 *db, int id1, int id2) {
	if (!db)return;
	szSQL = "UPDATE messenger SET trangthai = 0 WHERE idsen = ? AND idrec = ?";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		// bind the value
		sqlite3_bind_int(stmt, 1, id1);
		sqlite3_bind_int(stmt, 2, id2);
		// commit
		sqlite3_step(stmt);
		sqlite3_finalize(stmt);
	}
	else {
		cout << "+================+ SQL error: +================+" << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
}
