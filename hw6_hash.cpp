#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

int Extraction(int val)
{
	int a, b, c, d, e, f, g, h, i, rem, index;

	a = val / 100000000;		//9th digit
	rem = val % 100000000;

	b = rem / 10000000;			//8th digit
	rem = rem % 10000000;

	c = rem / 1000000;			//7th digit
	rem = rem % 1000000;

	d = rem / 100000;			//6th digit
	rem = rem % 100000;

	e = rem / 10000;			//5th digit
	rem = rem % 10000;

	f = rem / 1000;				//4th digit
	rem = rem % 1000;

	g = rem / 100;				//3rd digit
	rem = rem % 100;

	h = rem / 10;				//2nd digit
	rem = rem % 10;

	i = rem;					//1st digit

	c = c * 1000;				//convert to thousands
	e = e * 100;				//convert to hundreds
	g = g * 10;					//convert to tens

	index = c + e + g + h;		//add to get extraction address
	return index;
}


bool QuadraticProbe(int key, int *& hash_table, int M)
{
	int pos, i;
	pos = 0;
	for (i = 1; i%M != pos; i++)	
	{
		pos = (pos + i*i) % M;		//quadratic probe for new position
		if (hash_table[pos] == 0)	//if position empty
		{
			hash_table[pos] = key;
			return true;
		}
	}
	return false;					//table full
}

int main()
{
	vector<int> vector_of_numbers;  //vector for social numbers
	int index, number;
	string file;
	ofstream out;
	ifstream in;					//opening file to read from and file to write to
	cout << "What file would you like to read?" << endl;
	cin >> file;
	out.open("hashed_socials.txt");
	in.open(file);
	char lineData[50];
	if (!in.is_open())				//checks if file is open
	{
		cout << "I cannot find the file.\n";
		return false;
	}
	int i = 0;
	while (in.peek() != EOF)			//reads in file (comma deliminated to lineData
	{									//and converts it to int, stores in vector 
		in.getline(lineData, 50, ',');
		number = atoi(lineData);
		vector_of_numbers.push_back(number);
		i++;
	}
	in.clear();
	in.close();

	//if (vector_of_numbers.size() == 0) { cout << "not working"; }  //checks that vector is set up

	int M = vector_of_numbers.size();
	int *hash_table = new int[M];

	for (int i = 0; i<M; i++)    //initialize hash table to 0s
		hash_table[i] = 0;

	for (int i = 0; i<M; i++)    //hash vector_of_numbers into hash_table
	{
		index = Extraction(vector_of_numbers[i]);
		if (hash_table[index] == 0)
			hash_table[index] = vector_of_numbers[i];
		else                                         //else quadratic probe to find new home
		{											 //for pour misplaced number :(
			QuadraticProbe(vector_of_numbers[i], hash_table, M);
		}
	}

/*	for (int i = 0; i < 12; i++)
	{
		cout << hash_table[i] << endl;  //checks that hash table is set up
	} */

	for (int i = 0; i < M; i++)  //write out hash table to hashed_socials.txt
	{
		out << hash_table[i];
		if (i < M - 1)
			out << ",";
	}
	cout << "Hashed socials stored in hashed_socials.txt" << endl;
	out.clear();
	out.close();
	return 1;
}

