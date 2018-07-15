#include "Account.h"
#include "Account1.h"
#include "Chat.h"
#include<stdio.h>
#include <iostream>
#include <windows.h>
#include<conio.h>
#include <ctime>
#include <string>
using namespace std;

Account::Account(){}
Account::~Account(){}

// clrscr xóa màn hình
void clrscr1() 
{
	COORD origin = { 0, 0 };
	unsigned long len;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	unsigned long size;
	void* handle = GetStdHandle(STD_OUTPUT_HANDLE);

	GetConsoleScreenBufferInfo(handle, &csbi);
	size = csbi.dwSize.X * csbi.dwSize.Y;
	FillConsoleOutputCharacter(handle, TEXT(' '), size, origin, &len);
	FillConsoleOutputAttribute(handle, csbi.wAttributes, size, origin, &len);
	SetConsoleCursorPosition(handle, origin);
}

void Account::SignIn() {
	username = new (char);
	password = new (char);

	cout << " - Nhap username: ";
	cin >> username;
	cout << " - Nhap password: ";
	cin >> password;
	Chat conn;
	conn.Open();
	if (conn.Select_login(conn.db,username,password)>0) {
		clrscr1();
		cout << " +================+ Successfuly ! +================+\n\n";
		id = conn.Select_login(conn.db, username, password);
		check = true;
		zID = id;
	}
	else {
		clrscr1();
		cout << " +================+ Sign in fail! +================+\n\n";
		check = false;
	}
}
void Account::SingUp() {
	username = new (char);
	password = new char;
	gender = new char;
	birth = new char;
	name = new char;
	address = new char;

	cout << "- Nhap username: ";
	cin >> username;
	cout << "- Nhap password: ";
	cin >> password;
	cout << "- Nhap gender: ";
	cin >> gender;
	cout << "- Nhap birth: ";
	cin >> birth;
	cout << "- Nhap name: ";
	cin >> name;
	cout << "- Nhap address: ";
	cin.ignore();
	cin.getline(address, 100);
	Chat con;
	con.Open();
	con.Insert_Acc(con.db, username, password,gender,birth,name,address);
}

void Account::SignOut() {
	check = false;
	clrscr1();
	cout << "+================+ Ban da dang xuat. +================+\n";
}
void Account::SendMess(int id) {
	if (check) {
		int id2;
		cout << "- Nhap ten nguoi nhan: ";
		char *frien;
		frien = new char;
		cin >> frien;
		
		Chat conn;
		conn.Open();
		id2 = conn.Seach_fr(frien);
		if (id2 > 0) {
			char *mess, *dt;
			mess = new char;
			dt = new char;
			if (conn.CheckBlock(conn.db, id, id2)) {
				cout << "+================+ You is blocked by her +================+\n";
			}
			else {
				conn.update_tt(conn.db, id, id2);
				cout << "- Nhap tin nhan: \n";
				cin >> mess;
				time_t hientai = time(0);
				dt = ctime(&hientai);
				int tt = 1;
				conn.WriteToMess(conn.db, id, id2, mess, dt, tt);
				conn.ShowMessDetail(conn.db, id, id2);
			}
		}

		else cout << "+================+ Tai khoan khong ton tai +================+\n";
	}
	else {
		cout << "+================+ Ban chua dang nhap. +================+\n\n";
	}
}

void Account::ShowMess(int ID) {
	if (check) {
	Chat conn;
		conn.Open();
		conn.ShowSendMess(conn.db, id);
		conn.ShowRecMess(conn.db, id);
		
	}
	else {
		cout << "+================+ Ban chua dang nhap. +================+\n\n";
	}
}
void Account::ShowMessDetail(int id1) {
	if (check) {
		int id2;
		cout << "- Nhap ten: ";
		char *frien;
		frien = new char;
		cin >> frien;
	Chat conn;
		conn.Open();
		id2 = conn.Seach_fr(frien);
		if (id2 > 0)
			conn.ShowMessDetail(conn.db, id1, id2);

		cout << "- Chon Ctrl + R (Reply): ";
		RegisterHotKey(NULL, 1, MOD_CONTROL | MOD_NOREPEAT, 0x52);//0x52 is 'R'
		MSG msg = { 0 };
		if (GetMessage(&msg, NULL, 0, 0) != 0)
		{
			if (msg.message == WM_HOTKEY)
			{
				if (check) {
				if (id2 > 0) {
					 char *mess, *dt;
					mess = new char;
					dt = new char;
						conn.update_tt(conn.db, id, id2);
						clrscr1();
						cout << "\n- Nhap tin nhan: \n";
						cin.ignore();
						cin.getline(mess,100);
						time_t hientai = time(0);
						dt = ctime(&hientai);
						int tt = 1;
						conn.WriteToMess(conn.db, id, id2, mess, dt, tt);
						conn.ShowMessDetail(conn.db, id, id2);
				}

				else cout << "+================+ Tai khoan khong ton tai +================+\n";
				}
				else {
					cout << "+================+ Ban chua dang nhap. +================+\n\n";
				}
			}
			else
			{
				cout << "- Không Bắt Được Phím Ctrl+R !!!";
			}
		}
		else cout << "+================+ Tai khoan khong ton tai +================+\n";
	}
	else {
		cout << "+================+ Ban chua dang nhap. +================+\n\n";
	}
}
void Account::ShowFriend(int id1) {
	if (check) {
		Chat conn;
		conn.Open();
		conn.ShowFriend(conn.db, id1);

		cout << " - Chon Ctrl + C (Friend Group) City: ";
		RegisterHotKey(NULL, 1, MOD_CONTROL | MOD_NOREPEAT, 0x43);//0x43 is 'C'
		MSG msg = { 0 };
		if (GetMessage(&msg, NULL, 0, 0) != 0)
		{
			if (msg.message == WM_HOTKEY)
			{
				Chat conn;
				conn.Open();
				conn.Group(conn.db, id1,name,address );
			}
		}

	}
	else {
		cout << "+================+ Ban chua dang nhap. +================+\n\n";
	}
}

void Account::ShowFriendDetail(int id1) {
	if (check) {
		Chat conn;
		conn.Open();
		conn.ShowFriend(conn.db, id1);

		int id2;
		cout << "\n- Nhap ten ban muon xem chi tiet: ";
		char *frien;
		frien = new char;
		cin >> frien;
		id2 = conn.Seach_fr(frien);
		if (id2 > 0)
			conn.ShowFriendDetail(conn.db, id2);

		cout << "\n- An (Ctrl + R) de gui tin nhan: ";
		RegisterHotKey(NULL, 1, MOD_CONTROL | MOD_NOREPEAT, 0x52);//0x52 is 'R'
		MSG msg = { 0 };
		if (GetMessage(&msg, NULL, 0, 0) != 0)
		{
			if (msg.message == WM_HOTKEY)
			{
				if (check) {
					if (id2 > 0) {
						char *mess;
						char *dt;
						mess = new char;
						dt = new char;
						conn.update_tt(conn.db, id, id2);
						clrscr1();
						cout << "\n- Nhap tin nhan: \n";
						cin.ignore();
						cin.getline(mess, 100);
						time_t hientai = time(0);
						dt = ctime(&hientai);
						int tt = 1;
						conn.WriteToMess(conn.db, id, id2, mess, dt, tt);
						cout << "\n+================+ Gui Thanh Cong +================+\n";
					}

					else cout << "+================+ Tai khoan khong ton tai +================+\n";
				}
				else {
					cout << " +================+ Ban chua dang nhap. +================+\n\n";
				}
			}
			else
			{
				cout << "- Không Bắt Được Phím Ctrl+R";
			}
		}
		else cout << "+================+ Tai khoan khong ton tai+================+\n";

	}
	else {
		cout << "+================+ Ban chua dang nhap. +================+\n\n";
	}
}

void Account::AddFriend(int id) {
	if (check) {
		cout << "- Nhap ten nguoi ban muon them: ";
		char *newfr;
		newfr = new char;
		cin >> newfr;
		Chat conn;
		conn.Open();
		int id2 = conn.Seach_fr(newfr);
		if (id2 > 0) {
			if (!conn.CheckFriend(conn.db, id, id2)) {
				if (!conn.CheckBlock(conn.db, id, id2)) {
					conn.WriteToFriend(conn.db, id, id2);
					ShowFriend(id);
				}
				else cout << "+================+ You were blocked by her +================+\n\n\n";
			}
			else cout << "+================+ You was friend +================+\n\n\n";
		}
		else cout << "+================+ Tai khoan khong ton tai +================+\n";
	}
	else cout << "+================+ Ban chua dang nhap. +================+\n\n";
}
void Account::UpdateFriend(int id) {
	if (check) {
		cout << "\n - Nhap ten nguoi ban muon sua: ";
		char *newfr;
		newfr = new char;
		cin >> newfr;
		Chat conn;
		conn.Open();
		int id2 = conn.Seach_fr(newfr);
		if (id2 > 0) {
			if (conn.CheckFriend(conn.db, id, id2)) {
				
				gender = new (char);
				name = new char;
				address = new char;

				cout << "Nhap Name: ";
				cin >> name;
				
				cout << "Nhap Gender: ";
				cin >> gender;
				
				cout << "Nhap Address: ";
				cin >> address;

				conn.UpdateFriend(conn.db, gender, name, address, id2);

				cout << "---------- Doi thanh cong ----------\n\n\n";
			}
			else cout << "------You was friend ----------\n\n\n";
		}
		else cout << "----Tai khoan khong ton tai-----------\n";
	}
	else cout << "----------Ban chua dang nhap.--------\n\n";
}
void Account::BlockFriend(int id) {
	if (check) {
		cout << " - Chon nguoi ban muon block: ";
		char *name;
		name = new char;
		cin >> name;
		Chat conn;
		conn.Open();
		int id2 = conn.Seach_fr(name);
		if (id2 > 0) {
			conn.BlockFriend(conn.db, id, id2);
			cout << "+================+ Block Successfuly +================+\n\n";
		}
		else cout << "+================+ Tai khoan khong ton tai +================+\n";
	}
	else {
		cout << "+================+ Ban chua dang nhap. +================+\n\n";
	}
}
