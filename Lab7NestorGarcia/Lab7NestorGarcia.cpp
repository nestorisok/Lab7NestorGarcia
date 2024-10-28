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

void display16B(int* product);		// Displays arrays
void rightShift(int arrInp[]);	// Shifts array


const int bitSize16 = 16;
int main()
{
	string valA, valB;
	int userMD[bitSize16];
	int userMQ[bitSize16];


	cout << "These are 16-bit values" << endl;
	cout << "***********************" << endl;


	cout << "Enter MD: ";
	getline(cin, valA);
	stringToArr(valA, userMD);


	cout << "Enter MQ: ";
	getline(cin, valB);
	stringToArr(valB, userMQ);


	int* product = boothAlg(userMD, userMQ);

	cout << "\nProduct: ";

	for (int i = 0; i < bitSize16 + bitSize16; i++)		// Outputs our 32-bit result
	{
		if (i % 16 == 0 && i != 0)
			cout << " ";


		cout << product[i];
	}


	return 0;
}

void display16B(int* product)
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

	for (int i = bitSize16 - 1; i >= 0; i--)
	{
		arrInp[i] = arrInp[i - 1];

	}

}

void stringToArr(string valInp, int arrInp[])
{
	int arrCtr = 0; // counter for array itself
	char c;

		for (int i = 0; i < valInp.length(); i++) // keeps it under 16 chars, telling user to input 16
		{
			c = valInp.at(i);
			if (c != ' ' && arrCtr != bitSize16)	// Skips white space and does not go past our array size
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
	int cout = B_inv; // Initially cout is B_inv so 
	//res[bitSize - 1] = ALU_1bit(a[bitSize - 1], b[bitSize - 1], B_inv, B_inv, op, cout);
	int tempCin = cout;	// used for first call of ALU
	static int res[bitSize16];	// local array to return

	for (int i = bitSize16 - 1; i >= 0; i--) // decreement from MQ MD
	{
		res[i] = ALU_1bit(a[i], b[i], B_inv, tempCin, op, cout);
		tempCin = cout;	// tempCin holds carryOut from previous ALU_1bit call and inputs it back as next carry-in input



	}

	return res; // returns array res
	
}

int* boothAlg(int MD[], int MQ[])
{
	int MQ_1 = 0;	// initially set to 0

	// Initialize values

	int zeroArr[bitSize16] = { 0 }; // Simply an array of zeros for AC <- AC + 0

	int AC[bitSize16] = { 0 };	// our AC array intially filled with 0's
	int* ACptr = AC;	// pointer for our array

	int counterSize = bitSize16 - 1;	// Using our bitSize for input -1 to be able to perform opperation


	cout << "\ncycle_counter\tMD\t\t\tAC\t\t\tMQ\t\t\tMQ-1" << endl;
	cout << "***************************************************************************************************" << endl;



	while (counterSize >= 0)
	{
		bitset<4> cycle_counter(counterSize);

		if (counterSize == bitSize16 - 1)	// Outputs our initial values that user has given
		{
			//cout << counterSize << " ";
			cout << cycle_counter;
			cout << "\t\t";
			display16B(MD);
			cout << "\t";
			display16B(AC);
			cout << "\t";
			display16B(MQ);
			cout << "\t";
			cout << MQ_1;
			cout << endl;
		}
			//bitset<4> cycle_counter(counterSize); // Could work if we do while loop for who thing instead of for loop


			if (MQ[bitSize16 - 1] == 0 && MQ_1 == 0)	// AC = AC + 0 // bitSize - 1 is lsb 
			{
				ACptr = ALU_16bit(AC, zeroArr, 0, "10");	// ACptr recieves array returned from ALU_16bit
				for (int i = 0; i < bitSize16; i++)			// AC[] recieves data from ACptr
				{
					AC[i] = ACptr[i];
				}
			}
			if (MQ[bitSize16 - 1] == 0 && MQ_1 == 1)	// AC = AC + MD
			{
				ACptr = ALU_16bit(AC, MD, 0, "10");
				for (int i = 0; i < bitSize16; i++)
				{
					AC[i] = ACptr[i];
				}
			}
			if (MQ[bitSize16 - 1] == 1 && MQ_1 == 0)	// AC = AC - MD
			{
				ACptr = ALU_16bit(AC, MD, 1, "10");
				for (int i = 0; i < bitSize16; i++)
				{
					AC[i] = ACptr[i];
				}
			}
			if (MQ[bitSize16 - 1] == 1 && MQ_1 == 1)	// AC = AC + 0
			{
				ACptr = ALU_16bit(AC, zeroArr, 0, "10");
				for (int i = 0; i < bitSize16; i++)
				{
					AC[i] = ACptr[i];
				}
			}

			cout << '\n';

			cout << cycle_counter;
			cout << "\t\t";
			display16B(MD);
			cout << "\t";
			display16B(AC);
			cout << "\t";
			display16B(MQ);
			cout << "\t";
			cout << MQ_1;
			cout << endl;


			int msbAC = AC[0];	// hold the signbit from AC
			int lsbAC = AC[bitSize16 - 1];	// holds lsb from AC
			rightShift(AC);		// moves values over to the right in AC
			AC[0] = msbAC;		// the new signed bit recieves the value held from MSB

			int lsbMQ = MQ[bitSize16 - 1];	// hold the last value from MQ[]
			MQ_1 = lsbMQ;					// MQ_1 recieves the lsb from MQ[]

			rightShift(MQ);					// shifts values right 1
			MQ[0] = lsbAC;					// After shifting, MQ's MSB recieves AC's LSB


			//cout << counterSize << " ";
			cout << cycle_counter;
			cout << "\t\t";
			display16B(MD);
			cout << "\t";
			display16B(AC);
			cout << "\t";
			display16B(MQ);
			cout << "\t";
			cout << MQ_1;
			cout << endl;

			counterSize--;
		
	}

	static int product[bitSize16 + bitSize16];	// Create a 32-bit array

	for (int i = 0; i < bitSize16; i++)
	{
		product[i] = AC[i];						// first 16 bits comes from AC
	}
	for (int j = 0; j < bitSize16; j++)
	{
		product[bitSize16 + j] = MQ[j];			// Second half of array is values from MQ

	}

	return product; // Returns the product array, giving results from Booth's alg
}