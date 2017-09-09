/*	Program to reduce Boolean Expression with Min and Max terms using Tabulation method
	(Currently Valid for 4 variables, i.e., 16 Min or Max terms)
	
	NOTE : Program is in Beta Version and can only work upto Quads
	
	IDE Used  : Visual Studio Community 2017
	Compiler  : Microsoft Visual C++ Compiler (MSVC)
	Developer : Shashank Singh
*/
#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;
char binary_matrix[17][8] =
{
    /* {0000 0} The last zero gives info on the number of ones (for SOP), (4-last zero) for POS */
    {'0','0','0','0', '0','U','u','\0'},	// 0
    {'0','0','0','1', '1','U','u','\0'},	// 1
    {'0','0','1','0', '1','U','u','\0'},	// 2
    {'0','0','1','1', '2','U','u','\0'},	// 3
    {'0','1','0','0', '1','U','u','\0'},	// 4
    {'0','1','0','1', '2','U','u','\0'},	// 5
    {'0','1','1','0', '2','U','u','\0'},	// 6
    {'0','1','1','1', '3','U','u','\0'},	// 7
    {'1','0','0','0', '1','U','u','\0'},	// 8
    {'1','0','0','1', '2','U','u','\0'},	// 9
    {'1','0','1','0', '2','U','u','\0'},	// 10
    {'1','0','1','1', '3','U','u','\0'},	// 11
    {'1','1','0','0', '2','U','u','\0'},	// 12
    {'1','1','0','1', '3','U','u','\0'},	// 13
    {'1','1','1','0', '3','U','u','\0'},	// 14
    {'1','1','1','1', '4','U','u','\0'}	    // 15
};
void SOP();
//void POS();
int main()
{
	system("cls");

	int choice;

	cout << "\n BOOLEAN CIRCUIT REDUCTION : TABULATION METHOD" << endl;

	cout << "\n What is the type of your expression?" << endl;
	cout << "\n 1. Canonical SOP" << endl;
	cout << " 2. Canonical POS" << endl;
	getexptype:
	cout << "\n Enter your choice (1-2): "; cin >> choice;

	switch(choice)
	{
		case 1 :	SOP();	break;

		//case 2 :	POS();	break;

		default :	cout << "\n Wrong choice !!!" << endl;
					goto getexptype;
	}

	cout << "\n Operation Completed\n" << endl;
	system("pause");
	return 0;
}
void SOP()
{
	int i, j, l, x, varcount, mintcount, minterms[16], gpCount = 0, gpe[16], pCount = 0, qCount = 0, pe[10], qe[5], k = 0, nomatch;
	char vars[4], groups[16][16][5], pairs[10][16][5], quad[5][16][5];
	bool nopairingp;

	cout << "\n Enter the number of variables(max 4): ";
	cin >> varcount;

	cout << "\n Enter your variables: ";
	for(i=0; i<varcount; ++i)
		cin >> vars[i];

	cout << "\n Enter the number of MinTerms : ";
	cin >> mintcount;

	cout << "\n Enter all MinTerms separated by space : ";
	for(i=0; i<mintcount; ++i)
		cin >> minterms[i];

	/* Comparing MinTerm bits to create groups	*/
	for(i=0; i<mintcount; ++i)
	{
	    k = 0;
	    if(binary_matrix[minterms[i]][6] == 'u')
	    {
	        strncpy_s(groups[gpCount][k], binary_matrix[minterms[i]], 4);
	        groups[gpCount][k][4] = '\0';
	        ++k;
            for(j=0; j<mintcount; ++j)
            {
                if((j != i) && (binary_matrix[minterms[i]][6]) == 'u')
                {
                    //check if they have same number of zeros
                    if(binary_matrix[minterms[i]][4] == binary_matrix[minterms[j]][4])
                    {
                        strncpy_s(groups[gpCount][k], binary_matrix[minterms[j]], 4);
                        groups[gpCount][k][4] = '\0';
                        ++k;
                        binary_matrix[minterms[j]][6] = 'g';
                    }
                }
            }
            gpe[gpCount] = k;
            ++gpCount;
            binary_matrix[minterms[i]][6] = 'g';
        }
	}

	cout << "\n There are " << gpCount << " groups " << endl;

    for(i=0; i<gpCount; ++i)
    {
        cout << "\n Group " << i+1 << "\n" << endl;
        for(j=0; j<gpe[i]; ++j)
        {
            cout << " ";
            for(k=0; groups[i][j][k] != '\0'; ++k)
                cout << groups[i][j][k];
            cout << endl;
        }
    }

    /*  Comparing Groups to create Paris */
    for(i=0; i<gpCount-1; ++i)
    {
        nopairingp = true;
        x = 0;
        for(j=0; j<gpe[i]; ++j)
        {
            l = 0;
            while(l < gpe[i+1])
            {
                nomatch = 0;

                for(k=0; k<4; ++k)
                    if(groups[i][j][k] != groups[i+1][l][k])
                        ++nomatch;

                if(nomatch == 1)
                {
                        nopairingp = false;
                        strcpy_s(pairs[pCount][x], groups[i][j]);

                        for(k=0; k<4; ++k)
                            if(groups[i][j][k] != groups[i+1][l][k])
                                pairs[pCount][x][k] = '_';

                        ++x;
                        pe[pCount] = x;
                }
                ++l;
            }
        }
        if(nopairingp == false)
            ++pCount;
    }//pairs completed

    cout << "\n There are " << pCount << " pairs " << endl;

    for(i=0; i<pCount; ++i)
    {
        cout << "\n Pair " << i+1 << "\n" << endl;
        for(j=0; j<pe[i]; ++j)
        {
            cout << " ";
            for(k=0; pairs[i][j][k] != '\0'; ++k)
                cout << pairs[i][j][k];
            cout << endl;
        }
    }

    /*  Comparing pAIRs to create Quads */
    for(i=0; i<pCount-1; ++i)
    {
        nopairingp = true;
        x = 0;
        for(j=0; j<pe[i]; ++j)
        {
            l = 0;
            while(l < pe[i+1])
            {
                nomatch = 0;

                for(k=0; k<4; ++k)
                    if(pairs[i][j][k] != pairs[i+1][l][k])
                        ++nomatch;

                if(nomatch == 1)
                {
                        nopairingp = false;
                        strcpy_s(quad[qCount][x], pairs[i][j]);

                        for(k=0; k<4; ++k)
                            if(pairs[i][j][k] != pairs[i+1][l][k])
                                quad[qCount][x][k] = '_';

                        ++x;
                        qe[qCount] = x;
                }
                ++l;
            }
        }
        if(nopairingp == false)
            ++qCount;
    }//pairs completed

    cout << "\n There are " << qCount << " quads " << endl;

    for(i=0; i<qCount; ++i)
    {
        cout << "\n Quad " << i+1 << "\n" << endl;
        for(j=0; j<qe[i]; ++j)
        {
            cout << " ";
            for(k=0; quad[i][j][k] != '\0'; ++k)
                cout << quad[i][j][k];
            cout << endl;
        }
    }

    //Currently this functions does not supports octets

    //Print the reduced boolean expression
}
