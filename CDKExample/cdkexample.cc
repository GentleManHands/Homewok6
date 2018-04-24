/*
 * Usage of CDK Matrix
 *
 * File:   example1.cc
 * Author: Stephen Perkins
 * Email:  stephen.perkins@utdallas.edu
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdint.h>
#include "cdk.h"


#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 20
#define MATRIX_NAME_STRING "Binary File Contents"

using namespace std;

class BinaryFileHeader
{
public:
  uint32_t magicNumber;
  uint32_t versionNumber;
  uint64_t numRecords;

  uint8_t strLength;
  char stringBuffer[25];
  uint8_t strLength2;
  char stringBuffer2[25];
  uint8_t strLength3;
  char stringBuffer3[25];
  uint8_t strLength4;
  char stringBuffer4[25];
  
};

int main()
{

  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  // Remember that matrix starts out at 1,1.
  // Since arrays start out at 0, the first entries
  // below ("R0", and "C0") are just placeholders
  // 
  // Finally... make sure your arrays have enough entries given the
  // values you choose to set for MATRIX_WIDTH and MATRIX_HEIGHT
  // above.

  const char 		*rowTitles[] = {"R0", "a ", "b ", "c", "d", "e"};
  const char 		*columnTitles[] = {"C0", "a", "b", "c"};
  int		boxWidths[] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[] = {vMIXED, vMIXED, vMIXED, vMIXED, vMIXED};

  /*
   * Initialize the Cdk screen.
   *
   * Make sure the putty terminal is large enough
   */
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
  */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH,
			  MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths,
				     boxTypes, 1, 0, ' ', ROW, true, true, false);

  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  BinaryFileHeader *myHeader = new BinaryFileHeader();

  ifstream binInfile ("cs3377.bin", ios::in | ios::binary);

  binInfile.read((char *) myHeader, sizeof(BinaryFileHeader));

  drawCDKMatrix(myMatrix, true);
  cout << "Magic: 0x" << hex << uppercase << myHeader->magicNumber << endl;
  moveToCDKMatrixCell(myMatrix, 1, 2);
  drawCDKMatrix(myMatrix, true);
  cout << "Version: " << myHeader->versionNumber << endl;
  moveToCDKMatrixCell(myMatrix, 1, 3);
  drawCDKMatrix(myMatrix, true);
  cout << "NumRecords: " << myHeader->numRecords << endl;
  moveToCDKMatrixCell(myMatrix, 2, 1);
  drawCDKMatrix(myMatrix, true);
  cout << "strlen: " << myHeader->strLength << endl;
  moveToCDKMatrixCell(myMatrix, 2, 2);
  drawCDKMatrix(myMatrix, true);
  cout << myHeader->stringBuffer << endl;
  jumpToCell(myMatrix, 4, 1);
  drawCDKMatrix(myMatrix, true);
  cout << "strlen: " << myHeader->strLength2 << endl;
  jumpToCell(myMatrix, 4, 2);
  drawCDKMatrix(myMatrix, true);
  cout << myHeader->stringBuffer2 << endl;
  
  /*jumpToCell(myMatrix, 4, 1);
  drawCDKMatrix(myMatrix, true);
  cout << "strlen: " << myHeader->strLength3 << endl;
  moveToCDKMatrixCell(myMatrix, 4, 2);
  drawCDKMatrix(myMatrix, true);
  cout << myHeader->stringBuffer3 << endl;
  drawCDKMatrix(myMatrix, true);
  jumpToCell(myMatrix, 5, 1);
  drawCDKMatrix(myMatrix, true);
  cout << "strlen: " << myHeader->strLength4 << endl;
  moveToCDKMatrixCell(myMatrix, 5, 2);
  drawCDKMatrix(myMatrix, true);
  cout << myHeader->stringBuffer4 << endl;
  drawCDKMatrix(myMatrix, true);*/

  /* So we can see results, pause until a key is pressed. */
  unsigned char x;
  cin >> x;
  binInfile.close();

  // Cleanup screen
  endCDK();
}
