/*
 * Usage of CDK Matrix
 *
 * File:   example1.cc
 * Author: Stephen Perkins
 * Email:  stephen.perkins@utdallas.edu
 */

#include <iostream>
#include <string>
#include "cdk.h"
#include "BinaryFileModel.h"

#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 20 //15
#define MATRIX_NAME_STRING "Test Matrix"


void test();

using namespace std;


int main()
{
  //  test();

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
   * Dipslay a message
   */
  setCDKMatrixCell(myMatrix, 1, 1, dispFile.header.getMagicNumTitle().c_str());
  setCDKMatrixCell(myMatrix, 1, 2, dispFile.header.getVersionNumTitle().c_str());
  setCDKMatrixCell(myMatrix, 1, 3, dispFile.header.getNumRecordsTitle().c_str());

  int i = 2;
  for(list<BinaryFileRecord>::iterator it = dispFile.records.begin(); it != dispFile.records.end(); it++) {
    BinaryFileRecord rec = (BinaryFileRecord)*it;
    setCDKMatrixCell(myMatrix, i, 1, rec.getStrLengthTitle().c_str());
    setCDKMatrixCell(myMatrix, i, 2, rec.stringBuffer);
    i++;
  }
  
  // setCDKMatrixCell(myMatrix, 2, 2, "Test Message");
  drawCDKMatrix(myMatrix, true);    /* required  */

  /* So we can see results, pause until a key is pressed. */
  unsigned char x;
  cin >> x;

  // Cleanup screen
  endCDK();
}
/*
void test() {
  BinaryFile dispFile;
  dispFile.readFile("cs3377.bin");
  cout << "Back from read file." << endl;
  cout << "Magic Number : " <<  hex << dispFile.header.magicNumber << endl;
  unsigned char x;
  cin >> x;

}

*/
