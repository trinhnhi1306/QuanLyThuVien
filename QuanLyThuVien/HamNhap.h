#pragma once
#include <iostream>
#include <string>
#include <conio.h>
#include <iomanip>
#include "mylib.h"
#include "HangSo.h"
using namespace std;

//=====Khai báo các thuật toán=====
void chuan_hoa_chu(string& a);
bool Kiem_Tra_Du_Lieu(char c);
bool Kiem_Tra_Ki_Tu_So(char c);
int Kiem_tra_phim(char c);
int nhap_ki_tu(string& str, int flag, int viTri);
void xoaBangNhap();
void xoaThongBao();
void inThongBao(string str);

// hàm chuẩn hóa chữ ( xóa khoảng trắng đầu, cuối, khoảng trắng dư ở giữa, biến đổi các chữ trong chuỗi thành in hoa hết) 
void chuan_hoa_chu(string& a)
{
	//vòng lặp kiểm tra xem kí tự đầu tiên có phải là khoảng trắng hay là không 
	while (a[0] == ' ')
	{
		// nếu có thì xóa khoảng trắng ở vị trí đầu tiên
		a.erase(a.begin() + 0);
	}
	//vòng lặp kiểm tra xem kí tự cuối có phải là khoảng trắng hay là không 
	while (a[a.length() - 1] == ' ')
	{
		// nếu có thì xóa khoảng trắng ở vị trí cuối
		a.erase(a.begin() + a.length() - 1);
	}
	// kt giua 
	for (int i = 0; i < a.length(); i++)
	{
		//kiểm tra nếu có 2 khoảng trắng liên tục thì xóa 1 cái đi
		if (a[i] == ' ' && a[i + 1] == ' ')
		{
			// xóa và trừ độ dài đi 1
			a.erase(a.begin() + i + 1);
			i--;
		}
	}

	// ------------------------------------ bien doi chu hoa  ----------------------
	// hàm này thực chất là hàm biến đổi chữ cái đầu của mỗi từ thành chữ hoa thôi nhưng mà mình cho tất cả thành chữ hoa luôn :v
	if (a[0] >= 97 && a[0] <= 122)
	{
		a[0] -= 32;
	}
	for (int i = 1; i < a.length(); i++)
	{
		if (a[i] == ' ')
		{
			i++;
			if (a[i] >= 97 && a[i] <= 122)
			{
				a[i] -= 32;
			}
		}
		else if (a[i] >= 97 && a[i] <= 122)
		{
			a[i] -= 32;
		}

	}
}

// hàm kiểm tra dữ liệu của chuỗi nhập vào phải là các kí tự số hoặc kí tự chữ cái đsung true <> false
bool Kiem_Tra_Du_Lieu(char c)
{
	if ((c >= 48 && c <= 57) || c == 8) // nếu là số thì rt true <> false;
	{
		return true;
	}
	return false;
}
bool Kiem_Tra_Ki_Tu_So(char c)
{
	if (c >= '0' && c <= '9')
		return true;
	return false;
}
// ki tu so rt 2 <> ky tu dac biet rt 1 <> 0
int Kiem_tra_phim(char c)
{
	// 9 : tab, 16: shifl, ôi nhác quá đi nt với cr thoi
	int arr[31] = { 9,16,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,58,59,60,61,62,63,64,91,93,92,94,95,96,126 };
	if (Kiem_Tra_Ki_Tu_So(c) == true) // so
		return 2;
	for (int i = 0; i < 31; i++)
		if (c == arr[i])
			return 1;

	return 0;
}
// truyền một chuỗi và cờ để nhập - flag = 0 chỉ có kí tự, flag = 1 kí tự và số, flag = 2 nhập kí tự số
int nhap_ki_tu(string& str, int flag, int viTri)
{
	// nếu nhập kí tự enter thì chuỗi hiểu đó là kí tự kết thúc chuỗi <=> length = 0, ko tính là 1 kí tự
	bool KT = false; // điều kiện để chạy vòng lặp
	int length = str.length(); // biến cho con trỏ dịch đến cuối
	gotoxy(X_Add + 12, viTri * 2 + Y_Add);
	cout << str;
	char c;
	do
	{

		c = _getch(); // nhận 1 kí tự ở bàn phím và gán cho c
		while (int(c) != 13) // vòng lặp nếu chạy cho đến khi nhấn phím enter ( dùng int tại vì so sánh trong while ko so sách char với số được)
		{

			if (c == 0 || c == -32) // 0 là null và -32 là một số trường hợp đặt biệt sẽ xuất hiện kí tự -32 ví dụ như các phím di chuyển lên xuống <^>
			{
				break;
			}
			if (c == 27) // nhấn nút esc thì thoát
			{
				return -1;
			}
			int k = Kiem_tra_phim(c); // kiểm tra kí tự có phải là kí tự chức năng hay là kí tự số, 1 : chức năng, 2 : số 
			if (k == 1) // phím chức năng
			{
				break;
			}
			if (flag == 2)
			{
				if (Kiem_Tra_Du_Lieu(c) == false) // nếu nhập kí tự là chữ
				{
					break;
				}
			}
			if (k == 2 && flag == 0) // nếu nhập kí tự là số
			{
				break;
			}



			if (int(c) == 8) // nếu ấn phím Backspace thì xóa 1 kí tự ở cuối
			{

				if (length > 0) // nếu như độ dài biến con trỏ dịch bằng 0 thì ko cho xóa tiếp
				{
					cout << "\b \b"; // khi bấm phím Backspace thì sẽ xóa từng kí tự của chuỗi kí tự hiện tại
					length--;
				}
				if (str.length() != 0) // xóa kí tự cuối trong chuỗi string 
				{
					str.erase(str.begin() + (str.length() - 1));
				}
			}
			else
			{
				// bỏ kí tự vừa nhập vào cuối
				str.push_back(c);

				// xóa 1 khoảng trắng nếu có 2 khoảng trắng liên tiếp
				if (str.length() > 1) {
					if (str[str.length() - 1] == ' ' && str[str.length() - 2] == ' ')
					{

						// xóa và trừ độ dài đi 1
						str.erase(str.begin() + (str.length() - 1));
						// đè kí hiệu khoảng trắng lên màn hình
						cout << "\b \b";
						length--;
					}
				}

				// in hoa nếu là chữ
				if (c >= 97 && c <= 122) {
					c = c - 32;
					cout << c;
				}
				else cout << c;
				length++;


			}
			break;
		}
		// sau khi nhấn enter thì xem phải chuỗi rỗng hay ko, nếu có thì thông báo lỗi
		if (c == 13)
		{
			int dem = 1;
			int dem1 = 0;
			for (int i = 0; i < length; i++)
			{
				if ((int)str[i] == 32)
					dem++;
				else
					dem1++;
			}
			if (length == 0 || (dem >= 2 && dem1 == 0))
			{
				cout << "KHONG DUOC DE TRONG";
				KT = false;
			}
			else
				KT = true;

		}
	} while (KT == false);
	cout << endl;
	// hàm này chỉ để xóa khoảng trắng đâu và cuối, in hoa 
	chuan_hoa_chu(str);
}
void xoaBangNhap()
{
	system("color 0B");
	for (int i = 0; i < 20; i++)
	{
		gotoxy(X_Add - 2, Y_Add - 1 + i);
		printf("%-60s", " ");
	}
	//ShowCur(false);
}
void xoaThongBao()
{
	gotoxy(X_Notification, Y_Notification + 1);
	cout << setw(60) << setfill(' ') << " ";
}

void inThongBao(string str)
{
	gotoxy(X_Notification, Y_Notification + 1);
	cout << str;
}