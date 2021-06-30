#pragma once
#include "HamNhap.h"
#include "HangSo.h"
#include "HienThi.h"
#include "DanhMucSach.h"
#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;
#define MAX 300 //số lượng đầu sách tối đa

// thong tin vi tri hien tai
int trangDSHienTai = 1;
int soLuongTrangDS = 0;
int xKeyDisplay[7] = { 1,20,60,70,90,110, 130 };// toa do X cac diem nut
string thongTinDS[6] = { "ISBN", "Ten sach", "So trang", "Tac gia", "Nam xuat ban", "The loai" };

//=====ĐẦU SÁCH=====
struct dausach
{
	string ISBN; // mã sách theo chuẩn quốc tế
	string tensach;
	int sotrang;
	string tacgia;
	int namxuatban;
	string theloai;
	int soluotmuon; // biến lưu trữ số lần mượn sách của độc giả dùng để thống kê sách mượn nhiều nhất
	PTR_DMS dms; // con trỏ trỏ đến các sách thuộc đầu sách tương ứng
};

struct list_dausach
{
	int n;
	dausach* ds[MAX];
};
typedef struct list_dausach LIST_DS;

//=====Khai bao cac thuat toan=====
void khoiTaoDS(LIST_DS& l);
int themMotDS(LIST_DS& l, dausach s);
void nhapDS(LIST_DS& l);
int timKiemDSTheoMa(LIST_DS l, string ma);
void RemoveOldData(int nContent, int locate);
void inMotDS(dausach* s, int position);
void hienThi(string content[], int nContent);
void xoaNoiDungBiDu(int count, int nContent);
void inMotTrangDS(LIST_DS l, int StartIndex);
void chuyenTrangDS(LIST_DS l);
void loadFileDS(LIST_DS& l);
void menuDauSach(LIST_DS& l);

//=====CÁC THUẬT TOÁN=====

//Khởi tạo danh sách đầu sách
void khoiTaoDS(LIST_DS& l)
{
	l.n = 0;
}
//Thêm một đầu sách
int themMotDS(LIST_DS& l, dausach s)
{
	// nếu còn thêm được
	if (l.n < MAX)
	{
		l.ds[l.n] = new dausach;
		*l.ds[l.n] = s;
		khoiTaoDMS(l.ds[l.n]->dms);
		l.n++;
		return 1;
	}
	else return 0;
}
//Nhập đầu sách
void nhapDS(LIST_DS& l)
{
	dausach s;
	int viTri = 0;// so thu tu bat dau nhap
	int target = -1;
	string soTrang;
	string namxb;
	int kt;
	ShowCur(true);
	while (true)
	{
		switch (viTri)
		{
			case 0:
			{
				kt = nhap_ki_tu(s.ISBN, 2, viTri);
				if (kt == -1)
				{
					xoaBangNhap();
					xoaThongBao();
					return;
				}
				if (timKiemDSTheoMa(l, s.ISBN) != -1)
				{
					gotoxy(X_Add + 12, viTri * 2 + Y_Add);
					cout << setw(30) << setfill(' ') << " ";
					xoaThongBao();
					inThongBao("Ma ISBN bi trung!");
					break;
				}
				xoaThongBao();
				viTri++;
				break;
			}
			case 1:
			{
				kt = nhap_ki_tu(s.tensach, 1, viTri);
				if (kt == -1)
				{
					xoaBangNhap();
					xoaThongBao();
					return;
				}
				viTri++;
				break;
			}
			case 2:
			{
				kt = nhap_ki_tu(soTrang, 2, viTri);
				if (kt == -1)
				{
					xoaBangNhap();
					xoaThongBao();
					return;
				}
				viTri++;
				s.sotrang = atoi(soTrang.c_str());
				break;
			}
			case 3:
			{
				kt = nhap_ki_tu(s.tacgia, 0, viTri);
				if (kt == -1)
				{
					xoaBangNhap();
					xoaThongBao();
					return;
				}
				viTri++;
				break;
			}
			case 4:
			{
				kt = nhap_ki_tu(namxb, 2, viTri);
				if (kt == -1)
				{
					xoaBangNhap();
					xoaThongBao();
					return;
				}
				s.namxuatban = atoi(namxb.c_str());
				viTri++;
				break;
			}
			case 5:
			{
				kt = nhap_ki_tu(s.theloai, 0, viTri);
				if (kt == -1)
				{
					xoaBangNhap();
					xoaThongBao();
					return;
				}
				s.soluotmuon = 0;
				themMotDS(l, s);
				xoaThongBao();
				gotoxy(X_Notification, Y_Notification + 1);
				cout << "Them thanh cong ";
				xoaBangNhap();
				soLuongTrangDS = (int)ceil((double)l.n / NumberPerPage);
				trangDSHienTai = soLuongTrangDS;
				chuyenTrangDS(l);
				return;
			}
		}
	}
}

//Tìm kiếm đầu sách theo mã đầu sách nếu có trả về vị trí, nếu không trả về -1
int timKiemDSTheoMa(LIST_DS l, string ma)
{ 
	for (int i = 0; i < l.n; i++)
	{
		if (ma.compare(l.ds[i]->ISBN) == 0)
			return i;
	}
	return -1;
}
void RemoveOldData(int nContent, int locate)
{
	for (int i = 0; i < nContent; i++)
	{
		gotoxy(xKeyDisplay[i] + 3, Y_Display + 3 + locate * 3);
		cout << setw(xKeyDisplay[i + 1] - xKeyDisplay[i]) << setfill(' ') << " ";
	}
}

//in đầu sách
void inMotDS(dausach* s, int position)
{
	RemoveOldData( sizeof(thongTinDS) / sizeof(string),position);// xoa du lieu cu di
	gotoxy(xKeyDisplay[0] + 3, Y_Display + 3 + position * 3); cout << s->ISBN;
	gotoxy(xKeyDisplay[1] + 3, Y_Display + 3 + position * 3); cout << s->tensach;
	gotoxy(xKeyDisplay[2] + 3, Y_Display + 3 + position * 3); cout << s->sotrang;
	gotoxy(xKeyDisplay[3] + 3, Y_Display + 3 + position * 3); cout << s->tacgia;
	gotoxy(xKeyDisplay[4] + 3, Y_Display + 3 + position * 3); cout << s->namxuatban;
	gotoxy(xKeyDisplay[5] + 3, Y_Display + 3 + position * 3); cout << s->theloai;
}

void hienThi(string content[], int nContent)// ve bang 
{
	system("color 0B");
	SetColor(11);
	SetBGColor(0);
	//show key - the hien ra noi dung cua cac cot
	for (int i = 0; i < nContent; i++)
	{// Y_Display 3
		gotoxy(xKeyDisplay[i] + 3, Y_Display + 1);
		cout << content[i];
	}

	//ve cac duong thang de phan chia cac cot - kich thuoc toi da la 24 ve chieu dai
	for (int j = Y_Display; j <= Y_Display + 20; j++)
	{
		for (int i = 0; i < nContent + 1; i++)
		{
			gotoxy(xKeyDisplay[i], j);
			cout << char(176);
		}
	}
	//ve thanh ngang ben tren va duoi
	for (int i = xKeyDisplay[0]; i <= xKeyDisplay[nContent]; i++)
	{
		//ve thanh ngang ben tren so 1
		gotoxy(i, Y_Display);
		cout << char(176);

		// ve thanh ngang ben tren so 2
		gotoxy(i, Y_Display + 2);
		cout << char(176);

		//ve thanh ngang ben duoi
		gotoxy(i, Y_Display + 21);
		cout << char(176);
	}

	cout << endl;
	gotoxy(X_Tutorial, Y_Tutorial);
	cout << " Huong dan ";
	gotoxy(X_Tutorial, Y_Tutorial + 2);
	cout << " Page Up:Len || Page Down:Xuong ";
	gotoxy(X_Tutorial, Y_Tutorial + 3);
	cout << " Insert:Them || Del:Xoa ";
	gotoxy(X_Tutorial, Y_Tutorial + 4);
	cout << " Home:Chinh Sua || ESC : thoat";
	gotoxy(X_Notification, Y_Notification);
	cout << " Thong Bao ";
}

// nContent - so luong thanh phan co trong bang do
void xoaNoiDungBiDu(int count, int nContent)
{
	if (count < NumberPerPage)
	{
		for (int i = count; i < NumberPerPage; i++)
		{
			for (int y = 0; y < nContent; y++)
			{
				gotoxy(xKeyDisplay[y] + 3, Y_Display + 3 + i * 3);
				printf("%-30s", " ");
			}
		}
	}
}

void inMotTrangDS (LIST_DS l, int StartIndex)
{
	gotoxy(1, 2);
	cout << " So luong dau sach : " << l.n;
	int i;
	for (i = 0; i + StartIndex < l.n && i < NumberPerPage; i++)
	{
		inMotDS(l.ds[i + StartIndex], i);
	}
	xoaNoiDungBiDu(i, 6);
	gotoxy(X_Page, Y_Page);
	cout << " Trang " << trangDSHienTai << "/" << soLuongTrangDS;
}

void chuyenTrangDS(LIST_DS l)
{
	gotoxy(X_TitlePage, Y_TitlePage);
	cout << " Quan li dau sach ";
	inMotTrangDS(l, (trangDSHienTai - 1) * NumberPerPage);
	hienThi(thongTinDS, sizeof(thongTinDS) / sizeof(string));
}

void loadFileDS(LIST_DS& l)
{
	dausach data;
	danhmucsach x;
	ifstream file("DAUSACH.txt");
	int sl_dausach;
	int sl_dms;	
	file >> sl_dausach;
	file.ignore();
	for (int i = 0; i < sl_dausach; i++)
	{
		getline(file, data.ISBN, ',');
		getline(file, data.tensach, ',');
		file >> data.sotrang;
		file.ignore();
		getline(file, data.tacgia, ',');
		file >> data.namxuatban;
		file.ignore();
		getline(file, data.theloai, ',');
		file >> data.soluotmuon;
		file.ignore();
		file >> sl_dms;
		file.ignore();
		themMotDS(l, data);
		int vitri = timKiemDSTheoMa(l, data.ISBN);
		for (int i = 0; i < sl_dms; i++)
		{
			getline(file, x.masach, ',');
			file >> x.trangthai;
			file.ignore();
			getline(file, x.vitri);
			themLastDMS(l.ds[vitri]->dms, taoNodeDMS(x));
		}
	}
	file.close();
}

void menuDauSach(LIST_DS& l)
{
	ShowCur(false);
	system("cls");
	trangDSHienTai = 1;
	// ceil lam tron len
	soLuongTrangDS = (int)ceil((double)l.n / NumberPerPage);
	
	inMotTrangDS(l, 0);
	hienThi(thongTinDS, sizeof(thongTinDS) / sizeof(string));

	gotoxy(X_TitlePage, Y_TitlePage);
	cout << "Quan li dau sach";

	int signal;
	while (true)
	{
		while (_kbhit())
		{
			signal = _getch();
			if (signal == ESC)
				return;
			if (signal == 224)
			{
				signal = _getch();
				if (signal == PAGE_UP && trangDSHienTai > 1)
				{
					trangDSHienTai--;
					chuyenTrangDS(l);					
				}
				else if (signal == PAGE_DOWN && trangDSHienTai < soLuongTrangDS)
				{
					trangDSHienTai++;
					chuyenTrangDS(l);
				}
				// them moi
				else if (signal == INSERT)
				{
					if (l.n == MAX)
					{
						gotoxy(X_Notification, Y_Notification + 1); cout << "Danh sach day, khong the them";
						return;
					}
					CreateForm(thongTinDS, 0, 6, 50);
					nhapDS(l);					
					ShowCur(false);
				}// endif signal == INSERT

				// xoa di
				else if (signal == DEL)
				{/*
					if (LA.SoLuong == 0)
					{
						gotoxy(X_Notification, Y_Notification + 1); cout << "Danh sach rong,khong the xoa";
						return;
					}
					CreateForm(ContentAirplane, 0, 1, 27);
					InputAirplane(LA, false, true);
					TotalAirplanePage = (int)ceil((double)LA.SoLuong / NumberPerPage);
					ShowListAirplaneOnePage(LA, (CurAirplanePage - 1) * NumberPerPage);
				*/
				}//else if( signal == DEL)
				// HOME == chinh sua
				else if (signal == HOME)
				{/*
					CreateForm(ContentAirplane, 0, 3, 27);
					InputAirplane(LA, true, false);
					TotalAirplanePage = (int)ceil((double)LA.SoLuong / NumberPerPage);
					ShowListAirplaneOnePage(LA, (CurAirplanePage - 1) * NumberPerPage);
				*/
				}// signal == HOME
			}
		}//while( _kbhit)
	}// while(true)
}
