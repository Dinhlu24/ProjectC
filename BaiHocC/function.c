#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
const int MAX = 100;
#include "datatype.h"

void refresh(){
	system("pause");
    system("cls");
}

void write_binary_file_category(){
	FILE *f = fopen("category.bin","wb");
	int i=0;
	for(;i<csize;i++)
		fwrite(&category[i],sizeof(category[i]),1,f);
	fclose(f);
}

int findByID(char s[]){
	int i=0;
	for(;i<csize;i++)
		if(!strcmp(s,category[i].CategoryId))
			return i;
	return -1;
}

void showCategory(){
	printf("\t\t%60s\n","___________________________________________________________");
	printf("\t\t/%18s  |  %-36s\\\n","Category ID","Category Name");
	printf("\t\t%60s\n","+-----------------------------------------------------------+");
	if(!csize){
		printf("\t\t|%42s%18s\n","~~~~~~~~~~EMPTY~~~~~~~~~~","|");
		printf("\t\t%60s\n","*-----------------------------------------------------------*");
	}
	else{
		int i=0;
		for(;i<csize;i++){
			printf("\t\t|%-4d|%-15s%-11s%28s|\n",i+1,category[i].CategoryId,"|",category[i].CategoryName);
			if(i != csize-1)
				printf("\t\t%60s\n","|-----------------------------------------------------------|");
			else
				printf("\t\t%60s\n","*-----------------------------------------------------------*");
		}
	}
}

void showProducts(){
	printf("\n\n\t ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	printf("\t*|%16s%4s|%16s%4s|%27s%13s|%15s%5s|%14s%6s|*\n","<Product ID>","","<Category ID>","","<Product Name>","","<Quantity>","","<Price>","");
	printf("\t |____________________|____________________|________________________________________|____________________|____________________|\n");
	if(!psize){
		printf("\t |%24s%20s%40s%20s%20s|\n","","","","","");
		printf("\t |%24s%20s%40s%20s%20s|\n","","","","","");
		printf("\t |%74s%50s|\n","~~~~~~~~~~EMPTY~~~~~~~~~~","");
		printf("\t |%24s%20s%40s%20s%20s|\n","","","","","");
		printf("\t |____________________________________________________________________________________________________________________________|\n");
	}
	else{
		int i=0;
		for(;i<psize;i++){
			printf("\t |%20s|%20s|%40s|%20s|%20s|\n","","","","","");
			printf("\t |     %-10s     |     %-10s     |          %-20s          |         %-10d |         %-10d |\n",products[i].productID,products[i].categoryID,products[i].productName,products[i].quantity,products[i].price);
			printf("\t |____________________|____________________|________________________________________|____________________|____________________|\n");
		}
	}
}

void read_binary_file_category(){
	FILE *f = fopen("category.bin","rb");
	if(f != NULL)
		while(fread(&category[csize],sizeof(Category),1,f) != 0)
			csize++;
	fclose(f);
}

void managerMenuC(){ // category menu
    int choice;
    while(1){
    	refresh();
    	system("color A");
        showCategory();
        printf("\n\n\t-=-=-=-Store Management Using C-=-=-=-\n");
        printf("\n\t%31s\n","+Store Admin Menu (Category)+");
        printf("\t%30s\n","*===============================*");
        printf("\t%19s\n","[1] Add Category.");
        printf("\t%27s\n","[2] Fix Category (By ID).");
        printf("\t%30s\n","[3] Delete Category (By ID).");
        printf("\t%30s\n","[4] Find Category (By Name).");
        printf("\t%16s\n","[5] Sort Menu.");
        printf("\t%19s\n","[6] Product List.");
        printf("\t%11s\n","[0] Exit.");
        printf("\t%30s\n","*===============================*");
        printf("\t%17s","Your Choice: ");
        scanf("%d",&choice);
        while(getchar() != '\n');
        switch(choice){
            case 1:// Add category
            	addCategory();
                break;
            case 2:// Fix
            	fixCategory();
                break;
            case 3:// Delete
            	deleteCategory();
            	break;
            case 4: // Find
            	findCategory();
            	break;
            case 5: // Sort
            	sortMenuCategory();
            	break;
            case 6: // Products menu
            	managerMenuP();
            	break;
            case 0:// Exit
                return;
        }
    }
}

void sortMenuCategory(){
	int choice;
    while(1){
    	refresh();
        showCategory();
        printf("\n\n\t-=-=-=-Store Management Using C-=-=-=-\n");
        printf("\n\t%23s\n","+Sort Menu+");
        printf("\t%30s\n","*===============================*");
        printf("\t%14s\n","[1] Sort Up.");
        printf("\t%16s\n","[2] Sort Down.");
        printf("\t%11s\n","[0] Exit.");
        printf("\t%30s\n","*===============================*");
        printf("\t%17s","Your Choice: ");
        scanf("%d",&choice);
        while(getchar() != '\n');
        switch(choice){
        	case 1: // Sort Up
        		sortCategory(choice);
        		break;
        	case 2: // Sort Down
        		sortCategory(choice);
        		break;
        	case 0: // Exit
        		return;
		}
    }
}

int checkInputCategory(char input[]){
	if(!csize)
		return;
	int i=0;
	for(;i<csize;i++)
		if(!strcmp(input,category[i].CategoryId) || !strcmp(input,category[i].CategoryName))
			return 1;
	return 0;
}

void addCategory(){
	refresh();
	printf("Enter 'exit' to return!!!\n\n");
	char s[30],tmp[30];
	
	if(csize > MAX-1){
			printf("Your category list is full please return!\n\n");
			return;
	}
	
	while(csize < MAX){
		int empty = 0,size,inputCheck;
		
		do{
			printf("-> Category ID (%d): ",csize+1);
			fgets(s,30,stdin);
			s[strlen(s)-1] = '\0';
			
			size = strlen(s);
			empty = checkEmpty(s,size);
			inputCheck = checkInputCategory(s);
			
			if(strlen(s) > 10)
				printf("Your ID is too long please try again !!!\n\n");
			else if(!empty)
				printf("Invalid Data\n\n");
			else if(inputCheck)
				printf("Please enter different input\n\n");
		}while(strlen(s) > 10 || !empty || inputCheck);
		
		if(strcmp(s,"exit") == 0){
			printf("\t...Return...\n");
			write_binary_file_category();
			return;
		}
		
		strcpy(tmp,s);
		
		do{
			printf("-> Category Name (%d): ",csize+1);
			fgets(s,30,stdin);
			s[strlen(s)-1] = '\0';
			
			size = strlen(s);
			empty = checkEmpty(s,size);
			inputCheck = checkInputCategory(s);
			
			if(strlen(s) > 20)
				printf("Your Name is too long please try again !!!\n\n");
			else if(inputCheck)
				printf("Please enter different input\n\n");
			else if(!empty)
				printf("Invalid Data\n\n");
		}while(strlen(s) > 20 || !empty || inputCheck);
		
		if(strcmp(s,"exit") == 0){
			printf("\t...Return...\n");
			write_binary_file_category();
			return;
		}
		
		strcpy(category[csize].CategoryId,tmp);
		strcpy(category[csize].CategoryName,s);
		printf("Add Success!!!\n");
		csize++;
		if(csize > MAX-1){
			printf("Your category list is full please return!\n\n");
			return;
		}
	}
}

int checkEmpty(char s[],int size){ // ben trai la ki tu va do dai chuoi
	int i=0,count=0;//Tao bien count de dem so ki tu
	for(;i<size;i++)
		if(isalpha(s[i]))
			count++;
	return (count > 0);
}

void fixCategory(){
	if(!csize){
		printf("\t\tYour list is empty !\n\n");
		return;
	}
	char s[10];
	printf("\n\t-> Fix category ID: ");
	fgets(s,10,stdin);
	s[strlen(s)-1] = '\0';
	
	int check=findByID(s);
	if(check != -1){
		refresh();
		printf("\n\tFounded !!!\n");
		printf("\tOld %s category NAME: %s\n\n",category[check].CategoryId,category[check].CategoryName);
		printf("\t-> NEW NAME: ");
		fgets(category[check].CategoryName,20,stdin);
		category[check].CategoryName[strlen(category[check].CategoryName) - 1] = '\0';
		printf("\tFix Successful !\n\n");
		write_binary_file_category();
		return;
	}
	printf("\tInvalid ID!\n\n");
}

void deleteCategory(){
	if(!csize){
		printf("Your list is empty !\n\n");
		return;
	}
	char s[10];
	printf("-> Delete category ID: ");
	fgets(s,10,stdin);
	s[strlen(s)-1] = '\0';
	
	int i=findByID(s);
	if(i != -1){
		printf("Founded !!!\n");
		printf("This is your category information:\n");
		printf("ID: %s\nName: %s\n\n",category[i].CategoryId,category[i].CategoryName);
		printf("Are you sure you want to delete this category (yes/no): ");
		fgets(s,10,stdin);
		s[strlen(s)-1] = '\0';
		if(!strcmp(s,"no")){
			printf("\t\t...Return...\n\n");
			return;
		}
		else if(!strcmp(s,"yes")){
			deleteProduct2(category[i].CategoryId);
			for(;i<csize-1;i++)
				category[i] = category[i+1];
			csize--;
			printf("Delete Successful !\n\n");
			write_binary_file_category();
			return;
		}
	}
	printf("Invail ID!\n\n");
}

void deleteProduct2(char categoryID[]){
	if(psize){
		int i=0,j=0;
		for(;i<psize;i++){
			if(strcmp(products[i].categoryID,categoryID) != 0){
				products[j++] = products[i];
			}
		}
		psize=j;
		write_binary_file_product();
	}
}

void toLowerCase(char str[]) { // Chuyen doi chu cai hoa ve thuong de so sanh
	int i=0;
    for (;str[i] != '\0'; i++) {
        str[i] = tolower(str[i]);
    }
}

void findCategory(){
	refresh();
	if(!csize){
		printf("Your list is empty !\n\n");
		return;
	}
	char s[10];

	printf("-> Enter name the category you want to find: ");
	fgets(s,10,stdin);
	s[strlen(s)-1] = '\0';
	toLowerCase(s);
	int found = 0,i=0;
	
	
	printf("\t\t%60s\n","___________________________________________________________");
	printf("\t\t/%18s  |  %-36s\\\n","Category ID","Category Name");
	printf("\t\t%60s\n","+-----------------------------------------------------------+");
	
	for(;i<csize;i++){
		char tmp[20];
		strcpy(tmp,category[i].CategoryName);
		toLowerCase(tmp);
		if(strstr(tmp,s) != NULL){
			printf("\t\t|%-4d|%-15s%-11s%28s|\n",i+1,category[i].CategoryId,"|",category[i].CategoryName);
			printf("\t\t%60s\n","*-----------------------------------------------------------*");
			found = 1;
		}
	}
	
	if(i == csize - 1 && found == 1)	return;
	
	if(!found)
		printf("INVALID NAME\n\n");
}

void sortCategory(int choice){
	if(csize == 1){
		printf("Your list just have 1 category cannot sort !\n\n");
		return;
	}
	
	int i=1;
	for(;i<csize;i++){
		Category x = category[i];
		int j = i-1;
		
		if(choice == 1){
			while(j >= 0 && strcmp(x.CategoryName,category[j].CategoryName) < 0){
				category[j+1] = category[j];
				--j;
			}
		}
		else{
			while(j >= 0 && strcmp(x.CategoryName,category[j].CategoryName) > 0){
				category[j+1] = category[j];
				--j;
			}
		}
		category[j+1] = x;
	}
	printf("\nSort Success !!!\n\n");
	write_binary_file_category();
}

//----------------------------------Products----------------------------------------------//

void write_binary_file_product(){
	FILE *f = fopen("product.bin","wb");
	int i=0;
	for(;i<psize;i++)
		fwrite(&products[i],sizeof(products[i]),1,f);
	fclose(f);
}

void read_binary_file_product(){
	FILE *f = fopen("product.bin","rb");
	if(f != NULL)
		while(fread(&products[psize],sizeof(products[psize]),1,f) != 0){
			if(maxProductPrice < products[psize].price)
				maxProductPrice = products[psize].price;
			psize++;
		}
	fclose(f);
}

void managerMenuP(){ // Products menu
    int choice;
    while(1){
    	refresh();
        showProducts();
        if(!csize){
        	printf("\n\n\tYour Category List is empty please add !\n");
        	return;
		}
		else{
			printf("\n\n\t-=-=-=-Store Management Using C-=-=-=-\n");
	        printf("\n\t%30s\n","+Store Admin Menu (Product)+");
	        printf("\t%30s\n","*==============================*");
	        printf("\t%18s\n","[1] Add Product.");
	        printf("\t%26s\n","[2] Fix Product (By ID).");
	        printf("\t%29s\n","[3] Delete Product (By ID).");
	        printf("\t%29s\n","[4] Find Product (By Name).");
	        printf("\t%27s\n","[5] Sort Menu (By Price).");
	        printf("\t%18s\n","[6] Filter Menu.");
	        printf("\t%11s\n","[0] Exit.");
	        printf("\t%30s\n","*==============================*");
	        printf("\t%17s","Your Choice: ");
	        scanf("%d",&choice);
	        while(getchar() != '\n');
		}
        switch(choice){
        	case 1: // Add products
        		addProduct();
        		break;
        	case 2: // Fix product
        		fixProduct();
        		break;
        	case 3:// Delete product
        		deleteProduct1();
        		break;
        	case 4:// Find product
        		findProduct();
        		break;
        	case 5:// Sort product menu
        		sortMenuProduct();
        		break;
        	case 6:
        		filterMenu();
        		break;
        	case 0:
        		return;
		}
    }
}

void addProduct(){
	printf("Enter 'exit' to return!!!\n\n");
	Product x;
	
	if(psize > MAX-1){
		printf("Your product list is full please return!\n\n");
		return;
	}
	
	while(psize < MAX){
		int checkID=0,empty=0,size;
		
		do{
			printf("-> Product ID (%d): ",psize+1);
			fgets(x.productID,20,stdin);
			x.productID[strlen(x.productID)-1] = '\0';
			
			checkID = categoryIdCheck(x.productID);
			size = strlen(x.productID);
			empty = checkEmpty(x.productID,size);
			
			if(strlen(x.productID) > 10)
				printf("Your Product ID is too long please try again !!\n\n");
			else if(checkID)
				printf("Please try another ID, your ID is same as Category ID !!!\n\n");
			else if(!empty)
				printf("Invalid Data\n\n");
			else if(!strcmp(x.productID,"exit")){
				write_binary_file_product();
				return;
			}
		}while(strlen(x.productID) > 10 || checkID || !empty);
		
		do{
			printf("-> Category ID (%d): ",psize+1);
			fgets(x.categoryID,10,stdin);
			x.categoryID[strlen(x.categoryID)-1] = '\0';
			
			checkID = categoryIdCheck(x.categoryID);
			
			if(checkID)
				break;
			else if(!strcmp(x.categoryID,"exit")){
				write_binary_file_product();
				return;
			}
			else
				printf("Invail Category ID please try again !!\n\n");
		}while(1);
		
		do{
			printf("-> Product Name (%d): ",psize+1);
			fgets(x.productName,20,stdin);
			x.productName[strlen(x.productName)-1] = '\0';
			
			checkID = categoryIdCheck(x.productName);
			size = strlen(x.productID);
			empty = checkEmpty(x.productID,size);
			
			if(strlen(x.productName) > 20)
				printf("Your Product ID is too long please try again !!\n\n");
			else if(!strcmp(x.productName,x.productID))
				printf("Your Name is same as Product ID please ENTER new name !!\n\n");
		 	else if(checkID)
				printf("Your Name is same as Category ID please ENTER new name !!\n\n");
			else if(!empty)
				printf("Invalid Data\n\n");
			else if(!strcmp(x.productName,"exit")){
				write_binary_file_product();
				return;
			}
		}while(strlen(x.productID) > 20 || !strcmp(x.productName,x.productID) || checkID || !empty);
		
		printf("-> Product Quantity (%d): ",psize+1);
		while(scanf("%d",&x.quantity) != 1 || x.quantity < 0){
			printf("Invalid Data\n\n");
			printf("-> Product Quantity (%d): ",psize+1);
			while(getchar() != '\n');
		}
		while(getchar() != '\n');
		
		printf("-> Product Price (%d): ",psize+1);
		while(scanf("%d",&x.price) != 1 || x.price < 0){
			printf("Invalid Data\n\n");
			printf("-> Product Price (%d): ",psize+1);
			while(getchar() != '\n');
		}
		while(getchar() != '\n');
		
		if(maxProductPrice < x.price)
			maxProductPrice = x.price;
		
		printf("Add Success !!!\n\n");
		products[psize++] = x;
	}
}

int categoryIdCheck(char s[]){
	int i=0;
	for(;i<csize;i++)
		if(!strcmp(s,category[i].CategoryId))
			return 1;
	return 0;
}

void fixProduct(){
	if(!psize){
		printf("\t\tYour list is empty !\n\n");
		return;
	}
	char str[10];
	printf("\n-> Fix Product ID: ");
	fgets(str,10,stdin);
	str[strlen(str)-1] = '\0';
	
	int check = findByID2(str);
	if(check != -1){
		refresh();
		printf("\n\tFounded !!!\n");
		printf("\tThis is your old Product ID %s information\n\n",products[check].productID);
		printf("\t%52s\n","+------------------------*-------------------------+");
		printf("\t-> CategoryID: %s\n",products[check].categoryID);
		printf("\t-> Product Name: %s\n",products[check].productName);
		printf("\t-> Quantity: %d\n",products[check].quantity);
		printf("\t-> Price: %d\n",products[check].price);
		printf("\t%52s\n","+--------------------------------------------------+");
		
		do{
			printf("\t+> New CategoryID: ");
			fgets(products[check].categoryID,10,stdin);
			products[check].categoryID[strlen(products[check].categoryID)-1] = '\0';
			check = categoryIdCheck(products[check].categoryID);
			if(!check)
				printf("\n\tYour new Category Id is invalid in Category ID List please try again !!\n\n");
		}while(!check);
		
		do{
			printf("\t+> New Product Name: ");
			fgets(products[check].productName,20,stdin);
			products[check].productName[strlen(products[check].productName)-1] = '\0';
			check = checkEmpty(products[check].productName,strlen(products[check].productName));
			if(!check)
				printf("\tYour Data empty please try again !!\n");
		}while(!check);
		
		printf("\t+> Product Quantity: ");
		while(scanf("%d",&products[check].quantity) != 1 || products[check].quantity < 0){
			printf("\tInvalid Data\n\n");
			printf("\t+> Product Quantity: ");
			while(getchar() != '\n');
		}
		while(getchar() != '\n');
		
		printf("\t+> New Product Price: ");
		while(scanf("%d",&products[check].price) != 1 || products[check].price < 0){
			printf("\tInvalid Data\n\n");
			printf("\t+> Product Price: ");
			while(getchar() != '\n');
		}
		while(getchar() != '\n');
		
		printf("\n\tFix Success !!!\n");
		printf("\t%52s\n","+--------------------------------------------------+");
		write_binary_file_product();
		return;
	}
	printf("\tInvail ID!\n\n");
}

int findByID2(const char str[]){
	int i=0;
	for(;i<psize;i++)
		if(!strcmp(str,products[i].productID))
			return i;
	return -1;
}

void deleteProduct1(){
	if(!psize){
		printf("Your list is empty !\n\n");
		return;
	}
	char s[10];
	printf("-> Delete product ID: ");
	fgets(s,10,stdin);
	s[strlen(s)-1] = '\0';
	
	int i=findByID2(s);
	if(i != -1){
		printf("Founded !!!\n");
		printf("This is your product information:\n");
		printf("Product ID: %s\n",products[i].productID);
		printf("Category ID: %s\n",products[i].categoryID);
		printf("Product Name: %s\n",products[i].productName);
		printf("Quantity: %d\n",products[i].quantity);
		printf("Price: %d\n\n",products[i].price);
		printf("Are you sure you want to delete this product (yes/no): ");
		fgets(s,10,stdin);
		s[strlen(s)-1] = '\0';
		if(!strcmp(s,"no")){
			printf("\t\t...Return...\n\n");
			return;
		}
		else if(!strcmp(s,"yes")){
			for(;i<psize-1;i++)
				products[i] = products[i+1];
			psize--;
			printf("Delete Successful !\n\n");
			write_binary_file_product();
			return;
		}
		printf("Invail ID!\n\n");
	}
}

void findProduct(){
	refresh();
	if(!psize){
		printf("Your list is empty !\n\n");
		return;
	}
	char s[10];

	printf("-> Enter name the product you want to find: ");
	fgets(s,10,stdin);
	s[strlen(s)-1] = '\0';
	toLowerCase(s);
	int found = 0,i=0;
	
	printf("\t\t%115s\n","_________________________________________________________________________________________________________________");
	printf("\t\t/%20s|%20s|%30s|%20s|%20s\\\n","Product ID","Category ID","Product Name","Quantity","Price");
	printf("\t\t%60s\n","+------------------------------------------------------------------------------------------------------------------+");
	
	for(;i<psize;i++){
		char tmp[20];
		strcpy(tmp,products[i].productName);
		toLowerCase(tmp);
		if(strstr(tmp,s) != NULL){
			printf("\t\t|%20s|%20s|%30s|%20d|%20d|\n",products[i].productID,products[i].categoryID,products[i].productName,products[i].quantity,products[i].price);
			printf("\t\t%60s\n","*------------------------------------------------------------------------------------------------------------------*");
			found = 1;
		}
	}
	
	if(i == psize - 1 && found == 1)	return;
	
	if(!found)
		printf("INVALID NAME\n\n");
}

void sortMenuProduct(){
	int choice;
    while(1){
    	refresh();
        showProducts();
        printf("\n\n\t-=-=-=-Store Management Using C-=-=-=-\n");
        printf("\n\t%23s\n","+Sort Menu+");
        printf("\t%30s\n","*===============================*");
        printf("\t%14s\n","[1] Sort Up.");
        printf("\t%16s\n","[2] Sort Down.");
        printf("\t%11s\n","[0] Exit.");
        printf("\t%30s\n","*===============================*");
        printf("\t%17s","Your Choice: ");
        scanf("%d",&choice);
        while(getchar() != '\n');
        switch(choice){
        	case 1: // Sort Up
        		sortByPrice(choice);
        		break;
        	case 2: // Sort Down
        		sortByPrice(choice);
        		break;
        	case 0: // Exit
        		return;
		}
    }
}

void sortByPrice(int choice){
	if(psize == 1){
		printf("Your list just have 1 product cannot sort !\n\n");
		return;
	}
	
	int i=1;
	for(;i<psize;i++){
		Product x = products[i];
		int j = i-1;
		
		if(choice == 1){
			while(j >= 0 && products[j].price > x.price){
				products[j+1] = products[j];
				--j;
			}
		}
		else{
			while(j >= 0 && products[j].price < x.price){
				products[j+1] = products[j];
				--j;
			}
		}
		products[j+1] = x;
	}
	printf("\nSort Success !!!\n\n");
	write_binary_file_product();
}

void filterMenu(){
	if(!psize){
		printf("Your Products List is empty please add Product before Filter !!!\n\n");
		return;
	}
	int choice;
    while(1){
    	refresh();
        showProducts();
        printf("\n\n\t-=-=-=-Store Management Using C-=-=-=-\n");
        printf("\n\t%23s\n","+Sort Menu+");
        printf("\t%30s\n","*===============================*");
        printf("\t%25s\n","[1] Filter By Category.");
        printf("\t%22s\n","[2] Filter By Price.");
        printf("\t%11s\n","[0] Exit.");
        printf("\t%30s\n","*===============================*");
        printf("\t%17s","Your Choice: ");
        scanf("%d",&choice);
        while(getchar() != '\n');
        switch(choice){
        	case 1:// Tim kiem theo danh muc
        		filterProductsByCategoryID();
        		break;
        	case 2:// Tim kiem theo gia tien
        		filterProductsByPrice();
        		break;
        	case 0:
        		return;
		}
    }
}

int findByID3(const char s[]){
	int i=0;
	for(;i<psize;i++)
		if(!strcmp(s,products[i].categoryID))
			return 1;
	return 0;
}

void filterProductsByCategoryID(){
	refresh();
	showProducts();
	char id[10];
	printf("\t->Enter Category ID: ");	
	fgets(id,10,stdin);
	id[strlen(id)-1] = '\0';
	int check = findByID3(id);
	refresh();
	printf("\n\n\t\t\t\tCATEGORY ID %s IN PRODUCTS LIST\n",id);
	printf("\t\t%115s\n","_________________________________________________________________________________________________________________");
	printf("\t\t/%20s|%20s|%30s|%20s|%20s\\\n","Product ID","Category ID","Product Name","Quantity","Price");
	printf("\t\t%60s\n","+------------------------------------------------------------------------------------------------------------------+");
	if(check){
		int i=0;
		for(;i<psize;i++){
			if(!strcmp(products[i].categoryID,id)){
				printf("\t\t|%20s|%20s|%30s|%20d|%20d|\n",products[i].productID,products[i].categoryID,products[i].productName,products[i].quantity,products[i].price);
				printf("\t\t%60s\n","+------------------------------------------------------------------------------------------------------------------+");
			}
		}
		return;
	}
	printf("\t\t%85s\n","~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~EMPTY~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	printf("\t\t%60s\n","*------------------------------------------------------------------------------------------------------------------*");
}

int findByPrice(int start,int end){
	int i=0;
	for(;i<psize;i++){
		if(products[i].price >= start && products[i].price <= end)
			return 1;
	}
	return 0;
}

void filterProductsByPrice(){
	refresh();
	showProducts();
	int minPrice,maxPrice;
	
	do{
		printf("\t->Please enter the starting price(1 -> %d): ",maxProductPrice+1);
		scanf("%d",&minPrice);
		while(getchar() != '\n');
	
		printf("\t->Please enter the ending price(1 -> %d): ",maxProductPrice+1);
		scanf("%d",&maxPrice);
		while(getchar() != '\n');
		
		if(minPrice < 0 || maxPrice < 0)
			printf("\n\tInvalid price range: Prices cannot be negative. Please try again.\n");
		else if (minPrice > maxPrice)
			printf("\n\tInvalid price range: The starting price cannot be greater than the ending price. Please try again.\n");
		else if (maxPrice > maxProductPrice+1)
			printf("\n\tInvalid price range: The ending price is too high. Please enter a value less than or equal to %d.\n",maxProductPrice+1);
		else if (minPrice < 1)
			printf("\n\tInvalid price range: The starting price is too low. Please enter a value greater than or equal to 1.\n");
		else
			break;
	}while(1);
	
	int check = findByPrice(minPrice,maxPrice);
	refresh();
	printf("\n\n\t\t\t\tPRODCUCT PRICE FROM %d TO %d IN PRODUCTS LIST\n",minPrice,maxPrice);
	printf("\t\t%115s\n","_________________________________________________________________________________________________________________");
	printf("\t\t/%20s|%20s|%30s|%20s|%20s\\\n","Product ID","Category ID","Product Name","Quantity","Price");
	printf("\t\t%60s\n","+------------------------------------------------------------------------------------------------------------------+");
	if(check){
		int i=0;
		for(;i<psize;i++){
			if(products[i].price >= minPrice && products[i].price <= maxPrice){
				printf("\t\t|%20s|%20s|%30s|%20d|%20d|\n",products[i].productID,products[i].categoryID,products[i].productName,products[i].quantity,products[i].price);
				printf("\t\t%60s\n","+------------------------------------------------------------------------------------------------------------------+");
			}
		}
		return;
	}
	printf("\t\t%85s\n","~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~EMPTY~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	printf("\t\t%60s\n","*------------------------------------------------------------------------------------------------------------------*");
}

// ADMIN \---------------------------------------------------------------------------------------------------------------------------------------------------------/

void read_binary_file_account(){
	FILE *f;
//	f = fopen("account.bin","wb");
//	strcpy(account[0].username,"abc");
//	strcpy(account[0].password,"123");
//	fwrite(&account[0],sizeof(Account),1,f);
//	fclose(f);
	f = fopen("account.bin","rb");
	if(f != NULL)
		while(fread(&account[asize],sizeof(Account),1,f) != 0)
			asize++;
	fclose(f);
}

void adminLogin(){
	char user[20],pass[20],alpha;
	int check=0,characterPos=0;
	do{
		refresh();
		system("color 9");
		printf("\t\t-+-+-+-LOGIN-+-+-+-");
		printf("\n\n\t\t-> Username: ");
		fgets(user,20,stdin);
		user[strlen(user)-1] = '\0';
		printf("\t\t-> Password: ");
		while(1){
			alpha = getch();
			if(alpha == 13)// Enter
				break;
			else if(alpha == 8){ // backspace
				if(characterPos > 0){
					pass[--characterPos] = '\0';
					printf("\b \b");
				}
			}
			else if(alpha == 32 || alpha == 9) // space or tab
				continue;
			else{
				if(characterPos < 20){
					pass[characterPos++] = alpha;
					printf("*");
				}
			}
		}
		pass[characterPos] = '\0';
		check = checkAccount(user,pass);
		printf("\n");
		if(!check)
			printf("\nWrong username or password please try again!!\n");
	}while(!check);
	printf("\nLogin Success !!!\n");
}

int checkAccount(char user[],char pass[]){
	int i=0;
	for(;i<asize;i++)
		if(!strcmp(user,account[i].username) && !strcmp(pass,account[i].password))
			return 1;
	return 0;
}
