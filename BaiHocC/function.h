//Ham dung chung
void refresh();
void showCategory();
void showProducts();

//Ham danh cho danh muc
int findByID(char s[]);

//Ham danh cho quan ly
void read_binary_file_category();
void managerMenuC(); // Hien thi menu quan ly danh muc
void managerMenuP(); // Menu san pham
void addCategory(); // Them danh muc
int checkInputCategory(const char input[]);
int checkEmpty(char s[],int size); // Kiem tra du lieu nhap vao co trong hay ko
void write_binary_file_category(); // ghi file danh muc
void fixCategory(); // Sua danh muc
void deleteCategory(); // Xoa danh muc
void toLowerCase(char str[]);//Chuyen doi chu cai
void findCategory(); // Tim kiem danh muc
void sortMenuCategory(); // Menu sap xep danh muc
void sortCategory(int choice); // Sap xep

//Ham danh cho san pham
void addProduct(); // Them san pham
void read_binary_file_product();
int categoryIdCheck(); // Kiem tra ID danh muc thong qua san pham
void write_binary_file_product();
void fixProduct();// Sua thong tin san pham
int findByID2(const char s[]); // Tim kiem san pham thong qua ID san pham
void deleteProduct1(); // Xoa san pham
void deleteProduct2(char cateogoryID[]); // xoa san pham sau khi xoa danh muc
void findProduct(); // Tim kiem san pham thong qua ten
void sortByPrice();
void sortMenuProduct();
void filterProductsByCategoryID(); // loc san pham thong qua danh muc
void findByID3(const char s[]);
void filterMenu();
int findByPrice(int start,int end);
void filterProductsByPrice();// loc san pham thong qua gia tien

//Admin
void read_binary_file_account();
void adminLogin();
int checkAccount(char user[],char pass[]);
