#include <iostream>
#include <bitset>
#include <iomanip>
#include <string>

using namespace std;
// This program demonstrates how a 1-Bit ALU functions when recieving different opcodes
// This ALU specifically is able to do AND, OR, ADD, and SUB
// In the for loop demonstrated, given an int, using shift, we are able to get said bit value
// By doing so, we are able to get the bit value with logical AND 1 to compare bit position and
// either get 0 or 1. Allowing us to get every result for the 3 bits of a,b,CIN and applying the ALU function
// Applying Binv to 0 for every loop since it is not being used, and having the result be the output of ALU function



/*
	BOOTHS ALG
	----------
	MQ0		MQ-1

	0		0	AC
	1		1	AC
	0		1	AC <- AC + MD	// 16-bit addition
	1		0	AC <- AC - MD	// 16-bit subtraction


	2. AC | MQ | MD >> 1 (Arithmatic)

	3. Counter--;

	input - MD->16 bits / MQ->16 bits / AC->16 bits


	ex
	ALU 16()
	{
	// Runs for 16 times (16-bits)
		ALU1() // MQ[15]  MD[15]
		ALU1() // MQ[14]  MD[14]


		returns MQ, MD
	}

	// ALU0 cout is ALU1's CIN

	BOOTHS ALG()
	{
	// Runs for 16 time
	// vvvvvvv

		if(mq0 = 0 && mq-1 = 1)
		{
		ALU16(add);
		}
		if(MQ0 = 1 & MQ-1 = 0)
		{
		ALU16(sub);
		}

		Right shift(MD, MQ, AC)
	// ^^^^^^^^^
		Binary counter;		// Each step counter displayed // Displays MD	AC	MQ	MQ-1
		return product;


	}



*/

int AND_gate(int a, int b);
int OR_gate(int a, int b);

int full_adder(int a, int b, int cin, int& cout);
int mux_2x1(int x1, int x2, int op);
int mux_4x1(int x1, int x2, int x3, int x4, string op);
int ALU_1bit(int a, int b, int B_inv, int cin, string op, int& cout);


void ALU_results(string inp);	// Displays various outcomes for our 1-bit ALU

int* ALU_16bit(int a[], int b[], int B_inv, string op);	// 16 - bit ALU using 1 - bit ALU component 16 times

int* boothAlg(int MD[], int MQ[]);	// Booth alg implemented

void stringToArr(string valInp, int arrInp[]);	// converts users string input into an array

void display(int* product);		// Displays arrays
void rightShift(int* arrInp);	// Shifts array


const int bitSize16 = 16;
int main()
{
	string valA, valB;
	int userMD[bitSize16];
	int userMQ[bitSize16];

	/**/
	cout << "These are 16-bit values" << endl;
	cout << "***********************" << endl;


	cout << "Enter MD: ";
	getline(cin, valA);
	stringToArr(valA, userMD);

	//cin >> skipws >> setw(bitSize) >> valA;


	cout << "Enter MQ: ";
	getline(cin, valB);
	stringToArr(valB, userMQ);



	/*
	for (int i = 0; i < bitSize; i++)
	{

		cout << "i: " << i << endl;
		cout << "A: " << aBit[i] << endl;
		cout << "B: " << bBit[i] << endl;

	}
	/*
	
	// prints the result array
	for (int i = 0; i < bitSize; i++)
	{
		if (i % 4 == 0 && i != 0)
			cout << " ";


		cout << res[i];

	}
	/**/


	//cout << ALU_16bit(aBit, bBit, 0, "00") << endl;
	
	/*
	int* arrPtr;
	arrPtr = ALU_16bit(userMD, userMQ, 0, "00");

	// prints the result array
	for (int i = 0; i < bitSize16; i++)
	{
		if (i % 4 == 0 && i != 0)
			cout << " ";


		cout << arrPtr[i];
	}

	cout << "\n";

	rightShift(arrPtr);

	display(arrPtr);
	/**/

	
	int* product = boothAlg(userMD, userMQ);

	cout << "\nProduct: ";

	for (int i = 0; i < bitSize16 + bitSize16; i++)		// Outputs our 32-bit result
	{
		if (i % 4 == 0 && i != 0)
			cout << " ";


		cout << product[i];
	}
	/**/

	/*
	ALU_results("AND");
	ALU_results("OR");
	ALU_results("ADD");
	ALU_results("SUB");
	/**/



	return 0;
}

void display(int* product)
{

	for (int i = 0; i < bitSize16; i++)
	{
		if (i % 16 == 0 && i != 0)
			cout << " ";


		cout << product[i];
	}
}


void rightShift(int arrInp[])// Shifts array
{

	//for (int i = bitSize - 1; i >= 0; i--) // decreement from MQ MD

	
	//int temp = arrInp[0];	// MSB, signed bit

	for (int i = bitSize16 - 1; i >= 0; i--)
	{
		arrInp[i] = arrInp[i - 1];

	}
	//arrInp[0] = temp;
}

void stringToArr(string valInp, int arrInp[])
{
	int arrCtr = 0;
	char c;
	for (int i = 0; i < valInp.length(); i++) // keeps it under 16 chars, telling user to input 16
	{
		c = valInp.at(i);
		//cout << "VAL[i]: " << valInp.at(i) << endl;
		if (c != ' ')
		{
			arrInp[arrCtr] = atoi(&c);
			arrCtr++;
		}
	}


}



// Takes in string input to chose from different outputs
void ALU_results(string inp)
{
	if (inp == "AND")
	{
		cout << "------------------------------------------------------------------------------" << endl;
		cout << "\t\t\tAND results" << endl;
		cout << "\ta\tb\tcin\tBinv\top\tresult\tcout" << endl;
		cout << "------------------------------------------------------------------------------" << endl;
		for (int i = 0; i < 8; i++)
		{
			int a = (i >> 2) & 1;	// gets the left-most bit, since in code a = 
			int b = (i >> 1) & 1;	// gets the 2nd bit
			int cinINP = (i >> 0) & 1; // gets the right-most bit
			int B_inv = 0;
			string opCode = "00"; // SUB due to Binv = 1;

			int coutINP = 0;
			int res = ALU_1bit(a, b, B_inv, cinINP, opCode, coutINP); //Result from inputs

			cout << "\t" << a << "\t" << b << "\t" << cinINP << "\t" << B_inv << "\t" << opCode << "\t" << res << "\t" << coutINP << endl;
		}
	}
	else if (inp == "OR")
	{
		cout << "------------------------------------------------------------------------------" << endl;
		cout << "\t\t\tOR results" << endl;
		cout << "\ta\tb\tcin\tBinv\top\tresult\tcout" << endl;
		cout << "------------------------------------------------------------------------------" << endl;
		for (int i = 0; i < 8; i++)
		{
			int a = (i >> 2) & 1;	// gets the left-most bit, since in code a = 
			int b = (i >> 1) & 1;	// gets the 2nd bit
			int cinINP = (i >> 0) & 1; // gets the right-most bit
			int Binv = 0;
			string opCode = "01"; // OR
			int coutINP = 0;

			int res = ALU_1bit(a, b, Binv, cinINP, opCode, coutINP); //Result from inputs

			cout << "\t" << a << "\t" << b << "\t" << cinINP << "\t" << Binv << "\t" << opCode << "\t" << res << "\t" << coutINP << endl;
		}
	}
	else if (inp == "ADD")
	{
		cout << "------------------------------------------------------------------------------" << endl;
		cout << "\t\t\tADD results" << endl;
		cout << "\ta\tb\tcin\tBinv\top\tresult\tcout" << endl;
		cout << "------------------------------------------------------------------------------" << endl;
		for (int i = 0; i < 8; i++)
		{
			int a = (i >> 2) & 1;	// gets the left-most bit, since in code a = 
			int b = (i >> 1) & 1;	// gets the 2nd bit
			int cinINP = (i >> 0) & 1; // gets the right-most bit
			int Binv = 0;
			string opCode = "10"; // ADD
			int coutINP = 0;

			int res = ALU_1bit(a, b, Binv, cinINP, opCode, coutINP); //Result from inputs

			cout << "\t" << a << "\t" << b << "\t" << cinINP << "\t" << Binv << "\t" << opCode << "\t" << res << "\t" << coutINP << endl;
		}
	}
	else if (inp == "SUB")
	{
		cout << "------------------------------------------------------------------------------" << endl;
		cout << "\t\t\tSUB results" << endl;
		cout << "\ta\tb\tcin\tBinv\top\tresult\tcout" << endl;
		cout << "------------------------------------------------------------------------------" << endl;
		for (int i = 0; i < 8; i++)
		{
			int a = (i >> 2) & 1;	// gets the left-most bit, since in code a = 
			int b = (i >> 1) & 1;	// gets the 2nd bit
			int cinINP = (i >> 0) & 1; // gets the right-most bit
			int Binv = 1; // SUB
			string opCode = "10"; // SUB
			int coutINP = 0; // default val

			int res = ALU_1bit(a, b, Binv, cinINP, opCode, coutINP); //Result from inputs

			cout << "\t" << a << "\t" << b << "\t" << cinINP << "\t" << Binv << "\t" << opCode << "\t" << res << "\t" << coutINP << endl;
		}
	}


}



int AND_gate(int a, int b)
{

	return (a & b);
}


int OR_gate(int a, int b)
{

	return (a | b);
}

int full_adder(int a, int b, int cin, int& cout)
{
;
	cout = (a & b) | (cin & (a ^ b));


	return (a ^ b ^ cin);
}

int mux_2x1(int x1, int x2, int op)
{// If sel == 0, return x1, if sel != 0 return x2
	if (op == 0)
		return x1;
	else if (op == 1)
		return x2;
	else
	return -9999; 
}

int mux_4x1(int x1, int x2, int x3, int x4, string op)
{

	if (op == "00")
		return x1;
	else if (op == "01")
		return x2;
	else if (op == "10") 
		return x3;
	else if (op == "11") 
		return x4;

	else return -9999; //error
}

int ALU_1bit(int a, int b, int B_inv, int cin, string op, int& cout)
{

	if (B_inv == 1)
	{
		if (b == 0)
			b = 1;
		else
			b = 0;
	}

	int and_out = AND_gate(a, b);
	int or_out = OR_gate(a, b);
	int adder_out = full_adder(a, b, cin, cout);

	


	return (mux_4x1(and_out, or_out, adder_out, 0, op));

}

// MQ-1 = LSB_MQ


int* ALU_16bit(int a[], int b[], int B_inv, string op) // Op code for and, or, add, sub
{
	int cout = B_inv;
	//res[bitSize - 1] = ALU_1bit(a[bitSize - 1], b[bitSize - 1], B_inv, B_inv, op, cout);
	int tempCout = cout;
	static int res[bitSize16];

	for (int i = bitSize16 - 1; i >= 0; i--) // decreement from MQ MD
	{
		res[i] = ALU_1bit(a[i], b[i], B_inv, tempCout, op, cout);
		tempCout = cout;


		// Here I would need to initiate the ALU0
		// To do so, some input would change B_inv		// example if we want to sub the two values, we set B_inv to 1

		// and op code to 10 to use adder
		// AND would be 00 with no cin, b-inv, or cout
		// to implement ADD/SUB, the carry in could be changed to whatever given data has and 
		// ALU0 carrout becomes ALU1's carry-in to use for next instruction
		// What stays constant between ALU calls is only the op code
		// could be a switch statement with enums to have AND/OR/ADD/SUB
		// We could iterate through integers and perform given tasks



		// Given input of 16-bits, we constantly doing actions
		//cout = 0;
		// a is bit from top part, b is bit from bottom
	//	ALU_1bit(LSB_MQ, LSB_MD, B_inv, cin, op, &cout);
	//	cout = cin;
		

		//int cin = cout;

	}
	return res;

	/*
	std::cout << "\n";
	for (int i = 0; i < bitSize; i++)
	{
		std::cout << "i: " << i << "\n" << "VAL: " << res[i] << endl;
	}
	/**/

	
}

int* boothAlg(int MD[], int MQ[])
{
	int MQ_1 = 0;	// initially set to 0

	// Initialize values

	int zeroArr[bitSize16] = { 0 };
	int cycleCounter = { 1 };

	int AC[bitSize16] = { 0 };
	int* ACptr = AC;
	
	

	// Inital step

	cout << "Initial Setup" << endl;
	cout << "**************" << endl;
	cout << "MD\t\t\tAC\t\t\tMQ\t\t\t\t\tMQ-1" << endl;
	cout << "************************************************************************************" << endl;



	display(MD);
	cout << "\t";
	display(AC);
	cout << "\t";
	display(MQ);
	cout << "\t";
	cout << MQ_1;
	cout << endl;

	for (int i = bitSize16 - 1; i >= 0; i--) // decreement from MQ MD
	{


		if (MQ[bitSize16 - 1] == 0 && MQ_1 == 0)	// AC = AC + 0
		{
			ACptr = ALU_16bit(AC, zeroArr, 0, "10");
			for (int i = 0; i < bitSize16; i++)
			{
				AC[i] = ACptr[i];
				//cout << AC[i];
			}
		}
		if (MQ[bitSize16 - 1] == 0 && MQ_1 == 1)	// AC = AC + MD
		{
			ACptr = ALU_16bit(AC, MD, 0, "10");
			for (int i = 0; i < bitSize16; i++)
			{
				AC[i] = ACptr[i];
				//out << AC[i];
			}
		}
		if (MQ[bitSize16 - 1] == 1 && MQ_1 == 0)	// AC = AC - MD
		{
			ACptr = ALU_16bit(AC, MD, 1, "10");
			for (int i = 0; i < bitSize16; i++)
			{
				AC[i] = ACptr[i];
				//cout << AC[i];
			}
		}
		if (MQ[bitSize16 - 1] == 1 && MQ_1 == 1)	// AC = AC + 0
		{
			ACptr = ALU_16bit(AC, zeroArr, 0, "10");
			for (int i = 0; i < bitSize16; i++)
			{
				AC[i] = ACptr[i];
				//cout << AC[i];
			}
		}

		cout << '\n';

		display(MD);
		cout << "\t";
		display(AC);
		cout << "\t";
		display(MQ);
		cout << "\t";
		cout << MQ_1;
		cout << endl;


		int msbAC = AC[0];
		int lsbAC = AC[bitSize16 - 1];
		rightShift(AC);
		AC[0] = msbAC;

		int lsbMQ = MQ[bitSize16 - 1];
		MQ_1 = lsbMQ;

		rightShift(MQ);
		MQ[0] = lsbAC;


		display(MD);
		cout << "\t";
		display(AC);
		cout << "\t";
		display(MQ);
		cout << "\t";
		cout << MQ_1;
		cout << endl;

	}

	static int product[bitSize16 + bitSize16];

	for (int i = 0; i < bitSize16; i++)
	{
		product[i] = AC[i];
	}
	for (int j = 0; j < bitSize16; j++)
	{
		product[bitSize16 + j] = MQ[j];

	}
	// returns product; // AC / MQ

	return product; // temp
}


////// AND results
////cout << "------------------------------------------------------------------------------" << endl;
////cout << "\t\t AND results \t\t" << endl;
////cout << "\ta\tb\tcin\tBinv\top\tresult\tcout" << endl;
////cout << "------------------------------------------------------------------------------" << endl;
////for (int i = 0; i < 8; i++)
////{
////	int a = (i >> 2) & 1;	// gets the left-most bit
////	int b = (i >> 1) & 1;	// gets the 2nd bit
////	int cinINP = (i >> 0) & 1; // gets the right-most bit
////	int Binv = 0;
////	string opCode = "00"; // AND
////
////	int res = ALU_1bit(a, b, Binv, cinINP, opCode, coutINP); //Result from inputs
////
////	cout << "\t" << a << "\t" << b << "\t" << cinINP << "\t" << Binv << "\t" << opCode << "\t" << res << "\t" << coutINP << endl;
////}
////
////
////
////
////cout << "------------------------------------------------------------------------------" << endl;
////cout << "\t\t OR results \t\t" << endl;
////cout << "\ta\tb\tcin\tBinv\top\tresult\tcout" << endl;
////cout << "------------------------------------------------------------------------------" << endl;
////for (int i = 0; i < 8; i++)
////{
////	int a = (i >> 2) & 1;	// gets the left-most bit, since in code a = 
////	int b = (i >> 1) & 1;	// gets the 2nd bit
////	int cinINP = (i >> 0) & 1; // gets the right-most bit
////	int Binv = 0;
////	string opCode = "01"; // OR
////
////	int res = ALU_1bit(a, b, Binv, cinINP, opCode, coutINP); //Result from inputs
////
////	cout << "\t" << a << "\t" << b << "\t" << cinINP << "\t" << Binv << "\t" << opCode << "\t" << res << "\t" << coutINP << endl;
////}
////
////
////
////
////cout << "------------------------------------------------------------------------------" << endl;
////cout << "\t\t ADD results \t\t" << endl;
////cout << "\ta\tb\tcin\tBinv\top\tresult\tcout" << endl;
////cout << "------------------------------------------------------------------------------" << endl;
////for (int i = 0; i < 8; i++)
////{
////	int a = (i >> 2) & 1;	// gets the left-most bit, since in code a = 
////	int b = (i >> 1) & 1;	// gets the 2nd bit
////	int cinINP = (i >> 0) & 1; // gets the right-most bit
////	int Binv = 0;
////	string opCode = "10"; // ADD
////
////	int res = ALU_1bit(a, b, Binv, cinINP, opCode, coutINP); //Result from inputs
////
////	cout << "\t" << a << "\t" << b << "\t" << cinINP << "\t" << Binv << "\t" << opCode << "\t" << res << "\t" << coutINP << endl;
////}
////
////
////
////
////cout << "------------------------------------------------------------------------------" << endl;
////cout << "\t\t SUB results \t\t" << endl;
////cout << "\ta\tb\tcin\tBinv\top\tresult\tcout" << endl;
////cout << "------------------------------------------------------------------------------" << endl;
////for (int i = 0; i < 8; i++)
////{
////	int a = (i >> 2) & 1;	// gets the left-most bit, since in code a = 
////	int b = (i >> 1) & 1;	// gets the 2nd bit
////	int cinINP = (i >> 0) & 1; // gets the right-most bit
////	int Binv = 1;
////	string opCode = "10"; // SUB due to Binv = 1;
////
////	int res = ALU_1bit(a, b, Binv, cinINP, opCode, coutINP); //Result from inputs
////
////	cout << "\t" << a << "\t" << b << "\t" << cinINP << "\t" << Binv << "\t" << opCode << "\t" << res << "\t" << coutINP << endl;
////}
////
