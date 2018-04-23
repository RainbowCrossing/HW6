/*
 * Usage of CDK Matrix
 *
 * CDKEXAMPLE provided by Dr. Perkins
 * Tyler Waller tmw160530@utdallas.edu
 * 3377.501
 */

#include <iostream>
#include <string>
#include "cdk.h"
#include "BinaryFileModel.h"
// Includes header file.

// Created assignment parameters of the table.
#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 20 //15
#define MATRIX_NAME_STRING "Test Matrix"

using namespace std;

int main()
{
  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  // Remember that matrix starts out at 1,1.
  // Since arrays start out at 0, the first entries
  // below ("", and "") are just placeholders
  // 
  // Finally... make sure your arrays have enough entries given the
  // values you choose to set for MATRIX_WIDTH and MATRIX_HEIGHT
  // above.

  const char 		*rowTitles[] = {"", "A", "B", "C", "D", "E", "F"};
  const char 		*columnTitles[] = {"", "A", "B", "C", "D", "E", "F"};
  int		boxWidths[] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[] = {vMIXED, vMIXED, vMIXED, vMIXED,  vMIXED,  vMIXED};

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
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  /* Display the Matrix */
  drawCDKMatrix(myMatrix, true);
  
  BinaryFile dispFile;
  dispFile.readFile("cs3377.bin");
  /*
   * Setting our information gathered from the bin file in to place 
   * correctly in the rows and columns.
   */
  setCDKMatrixCell(myMatrix, 1, 1, dispFile.header.getMagicNumTitle().c_str());
  setCDKMatrixCell(myMatrix, 1, 2, dispFile.header.getVersionNumTitle().c_str());
  setCDKMatrixCell(myMatrix, 1, 3, dispFile.header.getNumRecordsTitle().c_str());
  // Starting on the second row and advancing down from there.
  int i = 2;
  // Loop to place the strlength and stringBuffer in to place.
  for(list<BinaryFileRecord>::iterator it = dispFile.records.begin(); it != dispFile.records.end(); it++) {
    BinaryFileRecord rec = (BinaryFileRecord)*it;
    setCDKMatrixCell(myMatrix, i, 1, rec.getStrLengthTitle().c_str());
    setCDKMatrixCell(myMatrix, i, 2, rec.stringBuffer);
    i++;
  }
  drawCDKMatrix(myMatrix, true);    /* required  */

  /* So we can see results, pause until a key is pressed. */
  unsigned char x;
  cin >> x;

  // Cleanup screen
  endCDK();
}
