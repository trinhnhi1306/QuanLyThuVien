#pragma once
#include <string>
#include "DanhMucSach.h"
using namespace std;
#define MAX 300 //số lượng đầu sách tối đa

//=====ĐẦU SÁCH=====
struct dausach
{
	string ISBN; // mã sách theo chuẩn quốc tế
	string tensach;
	int sotrang;
	string tacgia;
	int namxuatban;
	string theloai;
	int soluongmuon; // biến lưu trữ số lần mượn sách của độc giả dùng để thống kê sách mượn nhiều nhất
	PTR_DMS dms; // con trỏ trỏ đến các sách thuộc đầu sách tương ứng
};

struct list_dausach
{
	int n;
	dausach* ds[MAX];
};
typedef struct list_dausach LIST_DS;