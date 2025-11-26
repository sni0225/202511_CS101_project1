#include <iostream>
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	
	int number1 = 13;
	double number2 = 14.1;
	char letter = 'a';
	
	//pointer declaration
	int* int_ptr = &number1;	//address operator: &<variable name> 
	double* dbl_ptr = &number2;	//type of ptr must match type of variable
	char* chr_ptr = &letter;
	int* null_pointer = nullptr; //can initialize to nullptr
	
	//usually 8 bytes(system dependent)
	cout << "Size of int_ptr: " << sizeof(int_ptr) << endl;
	cout << "Size of dbl_ptr: " << sizeof(dbl_ptr) << endl;
	cout << "Size of chr_ptr: " << sizeof(chr_ptr) << endl;
	
	cout << "Size of int: " << sizeof(number1) << endl;		//int: 4 bytes
	cout << "Size of dbl: " << sizeof(number2) << endl;		//double: 8 bytes
	cout << "Size of chr: " << sizeof(letter) << endl;		//char: 1 or 2 bytes
	
	//printing pointers
	cout << "Address of number1: " << &number1 << endl;
	cout << "Address of number1: " << int_ptr << endl;
	
	cout << "Address of number2: " << &number2 << endl;
	cout << "Address of number2: " << dbl_ptr << endl;
	
	//printing pointer address
	cout << "Address of int_ptr: " << &int_ptr << endl;
	cout << "Address of dbl_ptr: " << &dbl_ptr << endl;
	
	cout << "Number1: " << number1 << endl;
	cout << "Number2: " << number2 << endl;
	//derefrencing: access the content held in the address
	//not to be confused with * in ptr declaration
	cout << "Number1: " << *int_ptr << endl;
	cout << "Number2: " << *dbl_ptr << endl;
	
	return 0;
}
