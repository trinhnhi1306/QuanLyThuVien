#pragma once
#include <string>
#include "MuonTra.h"
using namespace std;

//=====ĐỘC GIẢ=====
struct docgia
{
	int mathe;
	string ho;
	string ten;
	string phai;
	int trangthaithe; // =0 khoa, =1 hoat dong
	PTR_MT mt; // con trỏ sẽ trỏ đến danh sách các cuốn đã và đang mượn
};

struct node_docgia
{
	docgia data;
	node_docgia* left;
	node_docgia* right;
};
typedef struct node_docgia* TREE_DG;

//=====QUÁ HẠN=====
struct quahan
{
	int ma_doc_gia;
	string ma_sach;
	int so_ngay_quahan;
};