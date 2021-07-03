#pragma once
#include "HamNhap.h"
#include "HangSo.h"
#include "HienThi.h"
#include "DanhMucSach.h"
#include "mylib.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <string.h>
using namespace std;
#define MAX 300 //số lượng đầu sách tối đa

// thong tin vi tri hien tai
int trangDSHienTai = 1;
int soLuongTrangDS = 0;
int xKeyDisplay[7] = { 1, 20, 55, 70, 90, 110, 130 };// toa do X cac diem nut
string thongTinDS[6] = { "ISBN", "Ten sach", "So trang", "Tac gia", "Nam xuat ban", "The loai" };
string thongTinDMS[4] = { "ISBN", "So luong sach can them", "Ma sach", "Vi tri"};

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

//Khai bao de sap xep giu nguyen index
struct indexTheLoai
{
	int chiso;
	string theloai;
	string tensach;
};

struct listTheLoai {
	int n;
	indexTheLoai* nodes;
};

//=====Khai bao cac thuat toan=====
void khoiTaoDS(LIST_DS& l);
int themMotDS(LIST_DS& l, dausach s);
void nhapDS(LIST_DS& l);
int timKiemDauSachTheoMa(LIST_DS l, string maDauSach);
void xoaNoiDungCu(int nContent, int locate);
void inMotDS(dausach* s, int position);
void veBang(string content[], int nContent);
void xoaNoiDungBiDu(int count, int nContent);
void inMotTrangDS(LIST_DS l, int StartIndex);
void chuyenTrangDS(LIST_DS l);
void docFileDS(LIST_DS& l);
void ghiFileDS(LIST_DS l);
void menuDauSach(LIST_DS& l);
int demSoLuongSach(dausach x);
int menu_xoa(int x, int y);
void sapXepGiuNguyenIndex(LIST_DS& l, listTheLoai& listIndex);
string tachMaSach(string masach);
PTR_DMS timKiemDanhMucSach(LIST_DS l, string masach);

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
void NormalLine()
{
	SetColor(11);// aqua
	SetBGColor(0);// black
}
// dong dang chon
void HighlightLine()
{
	SetColor(0);// black
	SetBGColor(11);// aqua     
}
int menu_xoa(int x, int y)
{
	// return 0 la yes - dong y, return 1 la no - tu choi
	ShowCur(false);
	NormalLine();

	gotoxy(x, y);
	cout << "Ban co chac chan muon xoa khong?";

	char Option[2][10] = { "Co   ",
						   "Khong" };
	for (int i = 0; i < 2; i++)
	{
		gotoxy(x, y + i * 2 + 2);
		cout << Option[i];
	}
	int pointer = 0;

	gotoxy(x, y + pointer * 2 + 2);
	HighlightLine();
	cout << Option[pointer];
	char signal;

	while (true)
	{
		signal = _getch();
		if (signal == 224)
			signal = _getch();
		switch (signal)
		{
		case KEY_UP:
			if (pointer > 0)
			{
				NormalLine();
				gotoxy(x, y + pointer * 2 + 2);
				cout << Option[pointer];
				pointer--;
				HighlightLine();
				gotoxy(x, y + pointer * 2 + 2);
				cout << Option[pointer];
			}
			break;
		case KEY_DOWN:
			if (pointer < 1)
			{
				NormalLine();
				gotoxy(x, y + pointer * 2 + 2);
				cout << Option[pointer];
				pointer++;
				HighlightLine();
				gotoxy(x, y + pointer * 2 + 2);
				cout << Option[pointer];
			}
			break;
		case ENTER:
			NormalLine();
			for (int i = 0; i < 3; i++)
			{
				gotoxy(x, y + i * 2);
				cout << setw(50) << setfill(' ') << "";
			}
			return pointer;
		}
	}// while(true)
}

void xoaDSTheoMa(LIST_DS& l, string ma) {
	int i = timKiemDauSachTheoMa(l, ma);
	if (i == -1) return;
	else
	{
		delete  l.ds[i];
		for (int j = i + 1; j < l.n; j++)
			l.ds[j - 1] = l.ds[j];

		l.n--;
	}
}

void xoaThongTinBangNhap()
{
	gotoxy(X_Add + 12, 1 * 2 + Y_Add);
	cout << setw(30) << setfill(' ') << "";
	gotoxy(X_Add + 12, 2 * 2 + Y_Add);
	cout << setw(30) << setfill(' ') << "";
	gotoxy(X_Add + 12, 3 * 2 + Y_Add);
	cout << setw(30) << setfill(' ') << "";
	gotoxy(X_Add + 12, 4 * 2 + Y_Add);
	cout << setw(30) << setfill(' ') << "";
	gotoxy(X_Add + 12, 5 * 2 + Y_Add);
	cout << setw(30) << setfill(' ') << "";
}

//Nhập thông tin đầu sách, flag = 0 : thêm mới, flag = 1 : xóa, flag = 2: chỉnh sửa
void nhapDS(LIST_DS& l, int flag)
{
	dausach s;	
	string soTrang;
	string namxb;
	int viTri = 0;// so thu tu bat dau nhap
	int kt;
	int khoangCach = 12;
	ShowCur(true);
	while (true)
	{
		switch (viTri)
		{
			case 0:
			{
				xoaThongTinBangNhap();
				kt = nhap_ki_tu(s.ISBN, 2, viTri, khoangCach);
				if (kt == -1)
				{
					xoaBangNhap();
					xoaThongBao();
					return;
				}
				if (flag == 0) //trường hợp nhập mới
				{
					xoaThongBao();
					if (timKiemDauSachTheoMa(l, s.ISBN) != -1)
					{						
						inThongBao("Ma ISBN bi trung!");
						break;
					}
					viTri++;
					break;
				}
				if (flag == 1)
				{
					int stt = timKiemDauSachTheoMa(l, s.ISBN);
					xoaThongBao();
					if (stt == -1)
					{						
						inThongBao("Dau sach khong ton tai!");
						break;
					}									
					gotoxy(X_Add + 12, 1 * 2 + Y_Add);
					cout << l.ds[stt]->tensach;
					gotoxy(X_Add + 12, 2 * 2 + Y_Add);
					cout << l.ds[stt]->sotrang;
					gotoxy(X_Add + 12, 3 * 2 + Y_Add);
					cout << l.ds[stt]->tacgia;
					gotoxy(X_Add + 12, 4 * 2 + Y_Add);
					cout << l.ds[stt]->namxuatban;
					gotoxy(X_Add + 12, 5 * 2 + Y_Add);
					cout << l.ds[stt]->theloai;
					if (demSoLuongSach(*l.ds[stt]) == 0)
					{
						int luaChon = menu_xoa(X_Notification, Y_Notification + 1);
						if (luaChon == 0) // Có
						{
							xoaDSTheoMa(l, s.ISBN);
							ghiFileDS(l);
							xoaBangNhap();
							soLuongTrangDS = (int)ceil((double)l.n / NumberPerPage);
							inMotTrangDS(l, (trangDSHienTai - 1) * NumberPerPage);
							inThongBao("Xoa thanh cong!");
							return;
						}
						else
						{
							ShowCur(true);
							break;
						}
					}
					else
					{
						xoaThongBao();
						inThongBao("Dau sach nay dang co sach, khong the xoa!");
						ShowCur(true);
						break;
					}
				}
			}
			case 1:
			{
				kt = nhap_ki_tu(s.tensach, 1, viTri, khoangCach);
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
				kt = nhap_ki_tu(soTrang, 2, viTri, khoangCach);
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
				kt = nhap_ki_tu(s.tacgia, 0, viTri, khoangCach);
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
				kt = nhap_ki_tu(namxb, 2, viTri, khoangCach);
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
				kt = nhap_ki_tu(s.theloai, 0, viTri, khoangCach);
				if (kt == -1)
				{
					xoaBangNhap();
					xoaThongBao();
					return;
				}
				s.soluotmuon = 0;
				themMotDS(l, s);
				ghiFileDS(l);
				xoaThongBao();
				inThongBao("Them dau sach thanh cong");
				xoaBangNhap();
				soLuongTrangDS = (int)ceil((double)l.n / NumberPerPage);
				inMotTrangDS(l, (trangDSHienTai - 1)* NumberPerPage);
				return;
			}
		}
	}
}

//Nhập thông tin sách
void nhapDMS(LIST_DS& l)
{	
	int i; //vị trí đầu sách trong mảng
	int n = 0; //số lượng sách cần thêm mà người dùng nhập vào	
	string chuoinhap; //chuỗi người dùng nhập vào
	int viTri = 0;// so thu tu bat dau nhap	
	int kt;
	int khoangCach = 20;
	ShowCur(true);
	while (true)
	{
		switch (viTri)
		{
			case 0:
			{
				xoaThongTinBangNhap();
				kt = nhap_ki_tu(chuoinhap, 2, viTri, khoangCach);
				if (kt == -1)
				{
					xoaBangNhap();
					xoaThongBao();
					return;
				}
				i = timKiemDauSachTheoMa(l, chuoinhap);
				if (i == -1)
				{
					xoaThongBao();
					inThongBao("Dau sach nay khong ton tai!");
					break;
				}					
				xoaThongBao();
				viTri++;
				chuoinhap = "";
				break;
			}
			case 1:
			{
				kt = nhap_ki_tu(chuoinhap, 2, viTri, khoangCach); //chỉ nhập số
				if (kt == -1)
				{
					xoaBangNhap();
					xoaThongBao();
					return;
				}
				n = atoi(chuoinhap.c_str());
				viTri++;
				break;
			}
			case 2:
			{
				danhmucsach x;
				int stt = 0; //stt mã sách
				if (l.ds[i]->dms != NULL)
				{
					PTR_DMS q = l.ds[i]->dms;
					while (q->next != NULL)
					{
						q = q->next;
					}
					x.vitri = q->data.vitri; // lấy vị trí cuối cùng của sách đã tồn tại
					int pos = q->data.masach.find("-"); // lấy vị trí của kí tự - trong chuỗi
					string str = q->data.masach.substr(pos + 1); //  lấy chuỗi con của q->data.masach bắt đầu sau kí tự '-'
					stt = atoi(str.c_str()); //chuyển chuỗi sang số
				}
				for (int j = 0; j < n; j++)
				{
					x.masach = l.ds[i]->ISBN + "-" + to_string(stt + j + 1);
					gotoxy(X_Add + khoangCach, viTri * 2 + Y_Add);
					cout << x.masach;
					kt = nhap_ki_tu(x.vitri, 1, viTri + 1, khoangCach); //chỉ nhập kí tự và số
					if (kt == -1) // ESC
					{
						xoaBangNhap();
						xoaThongBao();
						return;
					}
					x.trangthai = 0; // mặc định sách có thể mượn được
					themLastDMS(l.ds[i]->dms, taoNodeDMS(x));
				}
				ghiFileDS(l);
				xoaThongBao();
				inThongBao("Them sach thanh cong!");
				xoaBangNhap();
				return;
			}			
		}
	}
}

//Tìm kiếm đầu sách theo mã đầu sách nếu có trả về vị trí, nếu không trả về -1
int timKiemDauSachTheoMa(LIST_DS l, string maDauSach)
{ 
	for (int i = 0; i < l.n; i++)
	{
		if (maDauSach.compare(l.ds[i]->ISBN) == 0)
			return i;
	}
	return -1;
}

//Xóa nội dung trang trước
void xoaNoiDungCu(int nContent, int locate)
{
	for (int i = 0; i < nContent; i++)
	{
		gotoxy(xKeyDisplay[i] + 3, Y_Display + 3 + locate * 3);
		cout << setw(xKeyDisplay[i + 1] - xKeyDisplay[i] - 3) << setfill(' ') << "";
	}
}

void swap(indexTheLoai& x, indexTheLoai& y)
{
	indexTheLoai temp = x;
	x = y;
	y = temp;
}

//sắp xếp đầu sách giữ nguyên index
void sapXepGiuNguyenIndex(LIST_DS& l, listTheLoai& listIndex)
{
	listIndex.nodes = new indexTheLoai[l.n];
	listIndex.n = l.n;
	for (int i = 0; i < l.n; i++)
	{
		listIndex.nodes[i].chiso = i;
		listIndex.nodes[i].theloai = l.ds[i]->theloai;
		listIndex.nodes[i].tensach = l.ds[i]->tensach;
	}
	for (int i = 0; i < l.n - 1; i++)
		for (int j = i + 1; j < l.n; j++)
			if (listIndex.nodes[j].theloai.compare(listIndex.nodes[i].theloai) < 0)
				swap(listIndex.nodes[j], listIndex.nodes[i]);
			else if (listIndex.nodes[j].theloai.compare(listIndex.nodes[i].theloai) == 0)
				if (listIndex.nodes[j].tensach.compare(listIndex.nodes[i].tensach) < 0)
					swap(listIndex.nodes[j], listIndex.nodes[i]);
}

//in đầu sách
void inMotDS(dausach* s, int position)
{
	xoaNoiDungCu(sizeof(thongTinDS) / sizeof(string), position);// xoa dong noi dung cu truoc do
	gotoxy(xKeyDisplay[0] + 3, Y_Display + 3 + position * 3); cout << s->ISBN;
	gotoxy(xKeyDisplay[1] + 3, Y_Display + 3 + position * 3); cout << s->tensach;
	gotoxy(xKeyDisplay[2] + 3, Y_Display + 3 + position * 3); cout << s->sotrang;
	gotoxy(xKeyDisplay[3] + 3, Y_Display + 3 + position * 3); cout << s->tacgia;
	gotoxy(xKeyDisplay[4] + 3, Y_Display + 3 + position * 3); cout << s->namxuatban;
	gotoxy(xKeyDisplay[5] + 3, Y_Display + 3 + position * 3); cout << s->theloai;
}

void veBang(string content[], int nContent)// ve bang 
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

	//ve cac duong thang de phan chia cac cot
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
	cout << " Page Up: Len || Page Down: Xuong ";
	gotoxy(X_Tutorial, Y_Tutorial + 3);
	cout << " Insert: Them dau sach || Del: Xoa ";
	gotoxy(X_Tutorial, Y_Tutorial + 4);
	cout << " Home: Them sach || ESC: Thoat";
	gotoxy(X_Notification, Y_Notification);
	cout << " Thong Bao ";
}

//Xóa nội dung bị dư trong bảng cuối cùng, nContent - so luong cột có trong bang do
void xoaNoiDungBiDu(int count, int nContent)
{
	if (count < NumberPerPage)
	{
		for (int i = count; i < NumberPerPage; i++)
		{
			for (int y = 0; y < nContent; y++)
			{
				gotoxy(xKeyDisplay[y] + 3, Y_Display + 3 + i * 3);
				cout << setw(xKeyDisplay[y + 1] - xKeyDisplay[y] - 3) << setfill(' ') << "";
			}
		}
	}
}

void inMotTrangDS (LIST_DS l, int StartIndex)
{
	int cs;
	listTheLoai listTL;
	sapXepGiuNguyenIndex(l, listTL);
	gotoxy(1, 2);
	cout << " So luong dau sach : " << l.n;
	int i;
	for (i = 0; i + StartIndex < l.n && i < NumberPerPage; i++)
	{
		cs = listTL.nodes[i + StartIndex].chiso;
		inMotDS(l.ds[cs], i);
	}
	xoaNoiDungBiDu(i, 6); //hàm này để xóa những nội dung cũ ở trang trước trang cuối cùng, nếu trang cuối cùng không đầy
	gotoxy(X_Page, Y_Page);
	cout << setw(20) << setfill(' ') << "";
	gotoxy(X_Page, Y_Page);
	cout << " Trang " << trangDSHienTai << "/" << soLuongTrangDS;
	delete[] listTL.nodes;
}

// đếm số lượng sách có thuộc 1 đầu sách
int demSoLuongSach(dausach x)
{
	int n = 0;
	for (PTR_DMS p = x.dms; p != NULL; p = p->next)
		n++;
	return n;
}

void ghiFileDS(LIST_DS l)
{
	ofstream f("DAUSACH.txt");
	f << l.n << endl;
	for (int i = 0; i < l.n; i++)
	{
		f << l.ds[i]->ISBN << ',';
		f << l.ds[i]->tensach << ',';
		f << l.ds[i]->sotrang << ',';
		f << l.ds[i]->tacgia << ',';
		f << l.ds[i]->namxuatban << ',';
		f << l.ds[i]->theloai << ',';
		f << l.ds[i]->soluotmuon << endl;
		f << demSoLuongSach(*l.ds[i]) << endl;
		for (PTR_DMS p = l.ds[i]->dms; p != NULL; p = p->next)
		{
			f << p->data.masach << ',';
			f << p->data.trangthai << ',';
			f << p->data.vitri << endl;
		}
	}
	f.close();
}

void docFileDS(LIST_DS& l)
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
		int vitri = timKiemDauSachTheoMa(l, data.ISBN);
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
//Tách mã sách để lấy mã ISBN
string tachMaSach(string masach)
{
	string temp;
	int n = masach.length();
	int dem = 0;
	for (int i = 0; i < n; i++)
	{
		if (masach[i] == '-')
			dem = i;
	}
	temp = masach.substr(0, dem);

	return temp;
}

node_DMS* timKiemDanhMucSach(LIST_DS l, string masach)
{
	string isbn = tachMaSach(masach);
	int i = timKiemDauSachTheoMa(l, isbn);
	if (i != -1)
		for (node_DMS* p = l.ds[i]->dms; p != NULL; p = p->next)
		{
			if (p->data.masach.compare(masach) == 0)
				return p;
		}
	return NULL;
}

void menuDauSach(LIST_DS& l)
{
	ShowCur(false);
	system("cls");
	trangDSHienTai = 1;
	// ceil lam tron len
	soLuongTrangDS = (int)ceil((double)l.n / NumberPerPage);
	inMotTrangDS(l, 0);
	veBang(thongTinDS, sizeof(thongTinDS) / sizeof(string));

	gotoxy(X_TitlePage, Y_TitlePage);
	cout << "Quan li dau sach";

	int signal;
	while (true)
	{
		while (_kbhit())
		{
			xoaThongBao();
			signal = _getch();
			if (signal == ESC)
				return;
			if (signal == 224)
			{
				signal = _getch();
				if (signal == PAGE_UP)
				{
					if (trangDSHienTai > 1)
						trangDSHienTai--;
					else trangDSHienTai = soLuongTrangDS;
					inMotTrangDS(l, (trangDSHienTai - 1) * NumberPerPage);
				}
				else if (signal == PAGE_DOWN)
				{
					if (trangDSHienTai < soLuongTrangDS)
						trangDSHienTai++;
					else trangDSHienTai = 1;
					inMotTrangDS(l, (trangDSHienTai - 1) * NumberPerPage);
				}
				// them moi
				else if (signal == INSERT) //Thêm đầu sách
				{
					if (l.n == MAX)
					{
						inThongBao("Danh sach day, khong the them");
						break;
					}
					taoBangNhap("Nhap thong tin dau sach", thongTinDS, 0, 6, 50);
					nhapDS(l, 0);					
					ShowCur(false);
				}// endif signal == INSERT

				// xoa di
				else if (signal == DEL) //Xóa đầu sách
				{
					if (l.n == 0)
					{
						inThongBao("Danh sach rong");
						return;
					}
					taoBangNhap("Nhap thong tin dau sach", thongTinDS, 0, 6, 50);
					nhapDS(l, 1);
					ShowCur(false);
				}//else if( signal == DEL)
				// HOME == chinh sua
				else if (signal == HOME) //Thêm sách
				{
					taoBangNhap("Nhap thong tin sach", thongTinDMS, 0, 4, 50);
					nhapDMS(l);
					ShowCur(false);
				}// signal == HOME
			}
		}//while( _kbhit)
	}// while(true)
}
