#pragma once
#include <string>
#include "Date.h"
using namespace std;

//=====MƯỢN TRẢ=====
struct muontra
{
	string masach;
	Date ngaymuon;
	Date ngaytra;
	int trangthai; // =0 đang mượn, =1 đã trả, =2 làm mất sách
};
struct node_muontra
{
	muontra data;
	node_muontra* next;
};
typedef struct node_muontra* PTR_MT;