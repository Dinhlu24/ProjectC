#define MAX 100

typedef struct{
	int month,day,year;
}Date;

typedef struct{
    char CategoryId[10];
    char CategoryName[20];
}Category;

int csize=0; // category size, Dem tu 0 -> 99 (Co' 100 phan tu), vua la size vua la vi tri
Category category[MAX];

typedef struct{
	char productID[10];
	char categoryID[10];
	char productName[20];
	int quantity;
	int price;
}Product;

int psize=0,maxProductPrice=-1e9; // product size,san pham co gia tien cao nhat (dung trong loc san pham)
Product products[MAX];

typedef struct{
	char username[20];
	char password[20];
}Account;

int asize = 0; // account size
Account account[MAX];

typedef struct{
	char orderID[10];
	char customerID[20];
	Date date;
	Product product;
}Order;
