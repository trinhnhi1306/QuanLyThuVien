#pragma once
#include <string>
#include "Date.h"
using namespace std;

//=====DANH MỤC SÁCH=====
struct danhmucsach
{
	string masach;
	int trangthai; // =0 cho mượn được, =1 đã có độc giả mượn, =2 sách đã thanh lí
	string vitri;
};

struct node_DMS
{
	danhmucsach data;
	node_DMS* next;
};
typedef node_DMS* PTR_DMS;

//=====CÁC THUẬT TOÁN=====

//Khởi tạo danh sách danh mục sách
void khoiTaoDMS(PTR_DMS& First)
{
	First = NULL;
}
// tạo 1 node mới 
node_DMS* taoNodeDMS(danhmucsach& x)
{
	node_DMS* p = new node_DMS;
	p->data = x;
	p->next = NULL;
	return p;
}
//Thêm sách vào danh mục sách để quản lí
void themLastDMS(PTR_DMS& First, node_DMS* p)
{
	if (First == NULL)
	{
		First = p;
	}
	else
	{
		PTR_DMS q = First;
		while (q->next != NULL)
		{
			q = q->next;
		}
		q->next = p;
	}
}
void inDMS(PTR_DMS First)
{
	int stt = 0;
	cout << setfill(' ');
	cout << left << setw(5) << "STT" << setw(15) << "Ma sach" << setw(30) << "Trang thai" << setw(20) << "Vi tri" << endl;
	for (PTR_DMS q = First; q != NULL; q = q->next)
	{
		cout << setw(5) << left << ++stt;
		cout << setw(15) << left << q->data.masach;
		cout << setw(30) << left << q->data.trangthai;
		cout << setw(20) << left << q->data.vitri << endl;
	}
}