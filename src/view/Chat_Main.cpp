#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <windows.h> // clrscr xóa màn hình
#include "Account.h"

using namespace std;
Account us = Account();
void viewlogin();
void viewchucnang();
void login();
void chucnang();
void Mess();
void Friend();
void viewMess();\
void viewFriend();


void clrscr() // xoa man hinh
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
void login() {
	while (1) {
		viewlogin();
		char choose;
		cin >> choose;

		switch (choose) {
		case '1':
			clrscr();
			us.SignIn();
			if (us.check) {
				chucnang();
			}
			break;
		case '2':
			clrscr();
			us.SingUp();
			break;
		case '3':
			clrscr();
			cout << "+================+ An nut bat ky de thoat +================+\n";
			exit(0);
			break;
		case '4':
			clrscr();
			cout << "+================+ Fall !!! Xin moi nhap lai! +================+\n";
			break;
		}
	}
}

void chucnang() {
		while (1) {
			viewchucnang();
			char choose1;
			cin >> choose1;

			switch (choose1) {
			case '1':
				clrscr();
				Mess();
				break;
			case '2':
				clrscr();
				Friend();
				break;
			case '3':
				clrscr();
				us.SignOut();
				login();
				break;
			case '4':
				clrscr();
				cout << "+================+ Fall !!! Xin moi nhap lai! +================+\n";
				break;
			}
		}
	}
void Mess() {
	while (1) {
		viewMess();
		char choose2;
		cin >> choose2;

		switch (choose2) {
		case '1':
			clrscr();
			us.SendMess(us.id);
			break;
		case '2':
			clrscr();
			us.ShowMess(us.id);
			break;
		case '3':
			clrscr();
			us.ShowMessDetail(us.id);
			break;
		case '4':
			clrscr();
			chucnang();
			break;
		case '5':
			clrscr();
			cout << "+================+ Fall !!! Xin moi nhap lai! +================+\n";
			break;
		}
	}
}
void Friend() {
	while (1) {
		viewFriend();
		char choose3;
		cin >> choose3;

		switch (choose3) {
		case '1':
			clrscr();
			us.AddFriend(us.id);
			break;
		case '2':
			clrscr();
			us.ShowFriend(us.id);
			break;
		case '3':
			clrscr();
			us.ShowFriendDetail(us.id);
			break;
		case '4':
			clrscr();
			us.UpdateFriend(us.id);
			break;
		case '5':
			clrscr();
			us.BlockFriend(us.id);
			break;
		case '6':
			clrscr();
			chucnang();
			break;
		case '7':
			clrscr();
			cout << "+================+ Fall !!! Xin moi nhap lai! +================+\n";
			break;
		}
	}
}
void viewMess() {
	cout << "\n++++ -------- Chon chuc nang: ------- ++++\n"
		" - [1]. Gui tin nhan\n"
		" - [2]. Hien thi tin nhan\n"
		" - [3]. Hien thi chi tiet tin nhan\n"
		" - [4]. Tro ve\n";
	    "++++ -------------------------------- ++++\n";

		cout << "\n- Nhap: ";
}
void viewFriend() {
	cout << "\n++++ -------- Chon chuc nang: ------- ++++\n"
		" - [1]. Them ban be\n"
		" - [2]. Danh sach ban be\n"
		" - [3]. Hien thi ban be chi tiet\n"
		" - [4]. Sua ban be\n"
		" - [5]. Block\n"
		" - [6]. Tro ve\n"
		"++++ -------------------------------- ++++\n";

	cout << "\n- Nhap: ";
}

void viewlogin() {
	cout << "\n++++ -------- Chon chuc nang: ------- ++++\n"
		" - [1]. Dang nhap\n"
		" - [2]. Dang ky\n"
		" - [3]. Thoat\n"
		"++++ -------------------------------- ++++\n";

	cout << "\n- Nhap: ";
}
void viewchucnang() {
	cout << "\n++++ -------- Chon chuc nang: ------- ++++\n"
		" - [1]. Mess\n"
		" - [2]. Friend\n"
		" - [3]. Log Out\n"
		"++++ -------------------------------- ++++\n";

	cout << "\n- Nhap: ";
}
int main()
{
	login();
	return 0;
}

