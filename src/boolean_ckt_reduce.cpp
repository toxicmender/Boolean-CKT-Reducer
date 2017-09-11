/*	Program to reduce Boolean Expression with Min and Max terms using Tabulation method
	(Currently Valid for 4 variables, i.e., 16 Min or Max terms)
	
	NOTE : Program is in "Beta" Version and can only work upto Quads
	
	IDE Used  : Visual Studio Community 2017
	Compiler  : Microsoft Visual C++ Compiler (MSVC)
	Developer : Shashank Singh (https://github.com/shashank9830)
*/
#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;
char binary_matrix[17][8] =
{
    /* {0000 0 U u} 
		
		First four values are binary representation of Decimal numbers 0-15
		The fifth value gives info on the number of ones (for SOP), (4-no of ones) for POS 
		u states that no group is formed from this value - it is changed to g
		U states that no pair is formed from this value - it is changed to G
	*/
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
//POS() function is commented out because the code currently doesn't supports POS expressions
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
//Function to reduce Sum-of-Product(SOP) expression
void SOP()
{
	int i, j, l, x, varcount, mintcount, minterms[16], gpCount = 0, gpe[16], pCount = 0, qCount = 0, pe[10], qe[5], k = 0, nomatch;
	char vars[4], groups[16][16][5], pairs[10][16][5], quad[5][16][5];
	bool nopairingp;

	//Take the number of literals present in the expression
	cout << "\n Enter the number of variables(max 4): ";
	cin >> varcount;

	//Enter the literals
	cout << "\n Enter your variables: ";
	for(i=0; i<varcount; ++i)
		cin >> vars[i];
	/* it should be noted that these literals are currently not used anywhere as there is no print function*/


	//Get the number of minterm values from the user
	cout << "\n Enter the number of MinTerms : ";
	cin >> mintcount;

	//Get all the minterm values
	cout << "\n Enter all MinTerms separated by space : ";
	for(i=0; i<mintcount; ++i)
		cin >> minterms[i];

	/*	Comparing MinTerm bits to create groups

		The minterm values are grouped together according to the global binary matrix
		They are checked if they are ungrouped(u flag)
		If they are not grouped a new group is created for them. And all grouped minterms flags are changed to 'g'
	
	*/
	for(i=0; i<mintcount; ++i)
	{
	    k = 0;
		//check if the minterm is ungrouped
	    if(binary_matrix[minterms[i]][6] == 'u')
	    {	
			//create a new group for that minterm
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
						//add other minterms with same no of zeros to that group
                        strncpy_s(groups[gpCount][k], binary_matrix[minterms[j]], 4);
                        groups[gpCount][k][4] = '\0';
                        ++k;
						//change the minterm status to grouped
                        binary_matrix[minterms[j]][6] = 'g';
                    }
                }
            }
			//gpe[] is an array that holds the number of minterm values present in each group
            gpe[gpCount] = k;
            //increase the group count
			++gpCount;
			//change the minterm status to grouped
            binary_matrix[minterms[i]][6] = 'g';
        }
	}

	//Printing the newly generated groups
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

    /*  Comparing Groups to create Pairs 

		The groups[][][] array is used to compare and form pairs if the binary values of the terms being
		compared differes only by one bit.
	*/
    for(i=0; i<gpCount-1; ++i)
    {	
		//it is assumed that there are no pairs in the beginning
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

				//condition to check if values differ by just one bit
                if(nomatch == 1)
                {	
						//pair exists
                        nopairingp = false;
                        strcpy_s(pairs[pCount][x], groups[i][j]);

						//put '-' in the place of bits that differ
                        for(k=0; k<4; ++k)
                            if(groups[i][j][k] != groups[i+1][l][k])
                                pairs[pCount][x][k] = '_';

                        ++x;

						//pe[] holds the number of values present in each pair
                        pe[pCount] = x;
                }
                ++l;
            }
        }
        if(nopairingp == false)
            ++pCount;	//increase pair count
    }//pairs generated

	//Printing the newly generated pairs
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

    /*  Comparing Pairs to generate Quads
		
		The pairs[][][] array is used to compare and form quads if the binary values of the terms being
		compared differes only by one bit.
	*/
    for(i=0; i<pCount-1; ++i)
    {	
		//it is assumed that no quad exists in the beginning
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

				//condition to check if values differ by just one bit
                if(nomatch == 1)
                {	
						//quads exists
                        nopairingp = false;
                        strcpy_s(quad[qCount][x], pairs[i][j]);

						//put '-' in the place of bits that differ
                        for(k=0; k<4; ++k)
                            if(pairs[i][j][k] != pairs[i+1][l][k])
                                quad[qCount][x][k] = '_';

                        ++x;

						//qe[] holds the number of values in each quad
                        qe[qCount] = x;
                }
                ++l;
            }
        }
        if(nopairingp == false)
            ++qCount;	//Quad count is increased
    }//quads generated

	//Printing the newly generated quads
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

    //Function to find octets goes here

    //Function to print the reduced expression goes here

	/*	NOTE:
		Contributors must try to find a way to change the pair, quad, octet... generation using a recursive function
	*/
}
