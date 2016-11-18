#include <iostream>
#include <fstream>

using namespace std;

void loadKeyArrFromFile (char keyArr[13][13], char* fileName)
{
    ifstream input;
    input.open(fileName);

    for (int r = 0; r < 13; r++)
    {
        for (int c = 0; c < 13; c++)
        {
            char in;
            input.get(in); // get next character
            keyArr[r][c] = in;
        }
        input.get(); // skip \n character
    }

    input.close();
}

void printKeyArray (char keyArr[13][13])
{
    // print header
    for (int i = 0; i < 13; i++)
        cout << char ('a' + i);
    cout << endl;

    for (int r = 0; r < 13; r++)
    {
        cout << char ('A' + r);
        for (int c = 0; c < 13; c++)
        {
            cout << keyArr[r][c];
        }
        cout << char ('n' + r);
        cout << endl;
    }

    // print footer
    for (int i = 0; i < 13; i++)
        cout << char ('N' + i);
    cout << endl;
}

/**
  * Makes a step at a given direction
  *
  * Alters r or c according to the direction we are heading
  *
  * @param direction is either n, e, s or w
  * @param r row index
  * @param c column index
*/
void doStep (char direction, int *r, int *c)
{
    if (direction == 'n') // if you're going north, decrement row index
        *r = *r-1;
    else if (direction == 'e')
        *c = *c+1;
    else if (direction == 's')
        *r = *r+1;
    else if (direction == 'w')
        *c = *c-1;
}

/**
  * Encrypts a letter with a given key
  *
  * @param keyArr key stored as an array
  * @param toEncrypt the letter (character) to be encrypted
  *
  * @return encrypted letter or \0 if unsupported character
 */
char encryptLetter (char keyArr[13][13], char toEncrypt)
{
    /*  a -> m
       A      n
       |      |
       v      v
       M      z
        N -> Z  */

    int r, c; // row index and column index
    char direction; // the current direction we are heading (north,east...)


    if (toEncrypt >= 'a' and toEncrypt <= 'm') // we start somewhere at the top of the table
    {
        r = 0; // as we start at the top, the row index is clearly 0
        c = toEncrypt - 'a'; // store the column we are in
        direction = 's'; // and we are heading south (we will go downwards)
    }
    else if (toEncrypt >= 'n' and toEncrypt <= 'z') // we start somewhere at the rightmost column
    {
        c = 12;
        r = toEncrypt - 'n';
        direction = 'w';
    }
    else if (toEncrypt >= 'A' and toEncrypt <= 'M')
    {
        c = 0;
        r = toEncrypt - 'A';
        direction = 'e';
    }
    else if (toEncrypt >= 'N' and toEncrypt <= 'Z')
    {
        r = 12;
        c = toEncrypt - 'N';
        direction = 'n';
    }
    else
    {
        cout << "UNSUPPORTED CHARACTER" << endl;
        return '\0';
    }

    /* Do steps as long as you don't hit the "walls"
     * by walls meaning top/bottommost row and left/rigthmost column
     *
     * On each iteration of the while loop we check the following:
     * 1) is at our postion in keyArr a "mirror"? if yes, change direction accordingly
     * 2) do the step by calling doStep() method
     * 3) check if we've hit a wall if yes the letter is finally encrypted and return it
    */
    while (true)
    {
    // 1)
        if (keyArr[r][c] == '\\')
        {
            if (direction == 'n')
                direction = 'w';
            else if (direction == 'e')
                direction = 's';
            else if (direction == 's')
                direction = 'e';
            else if (direction == 'w')
                direction = 'n';
        }
        else if (keyArr[r][c] == '/')
        {
            if (direction == 'n')
                direction = 'e';
            else if (direction == 'e')
                direction = 'n';
            else if (direction == 's')
                direction = 'w';
            else if (direction == 'w')
                direction = 's';
        }
    // 2)
        doStep(direction, &r, &c);

    // 3)
        if (r < 0) // in this case we've clearly hit the topmost row (encrypted letter a->m according to the column)
            return c+'a';
        if (r > 12)
            return c+'N';
        if (c < 0)
            return r+'A';
        if (c > 12)
            return r+'n';
    }

}


int main()
{
    char keyArr[13][13];
    loadKeyArrFromFile(keyArr, "key.txt"); // check key.txt to see what the file is like
    printKeyArray(keyArr); // optional of course

    while (true)
    {
        char in;
        cin >> in; // get a character from the user to be encrypted

        cout << encryptLetter(keyArr, in) << endl; // encrypt it
    }

    return 0;
}
