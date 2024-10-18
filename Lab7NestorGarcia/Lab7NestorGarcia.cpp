#include <iostream>
#include <bitset>
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
int mux_2x1(int x1, int x2, int sel);
int mux_4x1(int x1, int x2, int x3, int x4, string sel);
int ALU_1bit(int a, int b, int B_inv, int cin, string op, int& cout);


void ALU_results(string inp);

int ALU_16bit(int inpMQ, int inpMD, int B_inv, int cin, string op, int& cout);

int main()
{

	ALU_results("AND");
	ALU_results("OR");
	ALU_results("ADD");
	ALU_results("SUB");




	return 0;
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

	int sum = (a ^ b ^ cin);
	cout = (a & b) | (cin & (a ^ b));


	return sum;
}

int mux_2x1(int x1, int x2, int sel)
{

	return ((sel == 0) ? x1 : x2); // If sel == 0, return x1, if sel != 0 return x2
}

int mux_4x1(int x1, int x2, int x3, int x4, string sel)
{
	switch (atoi(sel.c_str()))
	{
	case 00:
		return x1;
		break;

	case 01:
		return x2;
		break;

	case 10:
		return x3;
		break;

	case 11:
		return x4;
		break;



	}

}

int ALU_1bit(int a, int b, int B_inv, int cin, string op, int& cout)
{
	switch (atoi(op.c_str()))
	{
	case 00: // AND
		//cout = cin; //Assignment shows both no cout and there being a cout in AND case
		return (a & b);
		break;

	case 01: // OR
		//cout = cin; 
		return (a | b);
		break;

	case 10: // ADD

		// if B_inv = 0 and b = 1, b = 1 or if b = 0, b = 0; 
		// if B_inv = 1 and b = 1, b = 0, or if b = 0, b = 1
		b = (B_inv ^ b);

		cout = (a & b) | (cin & (a ^ b));
		return (a ^ b ^ cin);
		break;


	}

}

// MQ-1 = LSB_MQ

int ALU_16bit(int inpMQ, int inpMD, int B_inv16, int cin16, string op16, int& cout) // Op code for and, or, add, sub
{
	int binMQ = inpMQ;
	int binMD = inpMD;


	for (int i = 16; i > 0; i--) // decreement from MQ MD
	{
		int LSB_MQ = binMQ % 10; // bit0, least significant bits for MQ and MD
		int LSB_MD = binMD % 10;

		// Here I would need to initiate the ALU0
		// To do so, some input would change B_inv
		// example if we want to sub the two values, we set B_inv to 1
		// and op code to 10 to use adder
		// AND would be 00 with no cin, b-inv, or cout
		// to implement ADD/SUB, the carry in could be changed to whatever given data has and 
		// ALU0 carrout becomes ALU1's carry-in to use for next instruction
		// What stays constant between ALU calls is only the op code
		// could be a switch statement with enums to have AND/OR/ADD/SUB
		// We could iterate through integers and perform given tasks



		// Given input of 16-bits, we constantly doing actions
		cout = 0;
		// a is bit from top part, b is bit from bottom
		ALU_1bit(LSB_MQ, LSB_MD, B_inv, cin, op, &cout);
		cout = cin;
		
		binMQ = binMQ >> 1; // Shifts the integer to next bit
		binMD = binMD >> 1;

		//int cin = cout;


	}


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
