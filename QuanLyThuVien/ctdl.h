#pragma once
#include <string>
using namespace std;
#define MAX 1000 //số lượng đầu sách tối đa

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

//=====NGÀY THÁNG NĂM=====
struct Date
{
	int ngay;
	int thang;
	int nam;
};

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