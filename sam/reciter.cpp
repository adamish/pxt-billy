#include <stdio.h>
#include <string.h>
#include "reciter.h"
#include "ReciterTabs.h"
#include "debug.h"

namespace billy {

unsigned char AA, XX, YY;
extern int debug;

static unsigned char inputtemp[256];   // secure copy of input tab36096

void Code37055(unsigned char mem59)
{
    XX = mem59;
    XX--;
    AA = inputtemp[XX];
    YY = AA;
    AA = tab36376[YY];
    return;
}

void Code37066(unsigned char mem58)
{
    XX = mem58;
    XX++;
    AA = inputtemp[XX];
    YY = AA;
    AA = tab36376[YY];
}

unsigned char GetRuleByte(unsigned short mem62, unsigned char YY)
{
    unsigned int address = mem62;

    if (mem62 >= 37541)
    {
        address -= 37541;
        return rules2[address+YY];
    }
    address -= 32000;
    return rules[address+YY];
}

int TextToPhonemes(unsigned char *input) // Code36484
{
    //unsigned char *tab39445 = &mem[39445];   //input and output
    //unsigned char mem29;
    unsigned char mem56;      //output position for phonemes
    unsigned char mem57;
    unsigned char mem58;
    unsigned char mem59;
    unsigned char mem60;
    unsigned char mem61;
    unsigned short mem62;     // memory position of current rule

    unsigned char mem64;      // position of '=' or current character
    unsigned char mem65;     // position of ')'
    unsigned char mem66;     // position of '('
    unsigned char mem36653;

    inputtemp[0] = 32;

    // secure copy of input
    // because input will be overwritten by phonemes
    XX = 1;
    YY = 0;
    do
    {
        //pos36499:
        AA = input[YY] & 127;
        if ( AA >= 112) AA = AA & 95;
        else if ( AA >= 96) AA = AA & 79;

        inputtemp[XX] = AA;
        XX++;
        YY++;
    } while (YY != 255);


    XX = 255;
    inputtemp[XX] = 27;
    mem61 = 255;


pos36550:
    AA = 255;
    mem56 = 255;


pos36554:
    while(1)
    {
        mem61++;
        XX = mem61;
        AA = inputtemp[XX];
        mem64 = AA;
        if (AA == '[')
        {
            mem56++;
            XX = mem56;
            AA = 155;
            input[XX] = 155;
            //goto pos36542;
            //          Code39771();    //Code39777();
            return 1;
        }

        //pos36579:
        if (AA != '.') break;
        XX++;
        YY = inputtemp[XX];
        AA = tab36376[YY] & 1;
        if(AA != 0) break;
        mem56++;
        XX = mem56;
        AA = '.';
        input[XX] = '.';
    } //while


    //pos36607:
    AA = mem64;
    YY = AA;
    AA = tab36376[AA];
    mem57 = AA;
    if((AA&2) != 0)
    {
        mem62 = 37541;
        goto pos36700;
    }

    //pos36630:
    AA = mem57;
    if(AA != 0) goto pos36677;
    AA = 32;
    inputtemp[XX] = ' ';
    mem56++;
    XX = mem56;
    if (XX > 120) goto pos36654;
    input[XX] = AA;
    goto pos36554;

    // -----

    //36653 is unknown. Contains position

pos36654:
    input[XX] = 155;
    AA = mem61;
    mem36653 = AA;
    //  mem29 = AA; // not used
    //  Code36538(); das ist eigentlich
    return 1;
    //Code39771();
    //go on if there is more input ???
    mem61 = mem36653;
    goto pos36550;

pos36677:
    AA = mem57 & 128;
    if(AA == 0)
    {
        //36683: BRK
        return 0;
    }

    // go to the right rules for this character.
    XX = mem64 - 'AA';
    mem62 = tab37489[XX] | (tab37515[XX]<<8);

    // -------------------------------------
    // go to next rule
    // -------------------------------------

pos36700:

    // find next rule
    YY = 0;
    do
    {
        mem62 += 1;
        AA = GetRuleByte(mem62, YY);
    } while ((AA & 128) == 0);
    YY++;

    //pos36720:
    // find '('
    while(1)
    {
        AA = GetRuleByte(mem62, YY);
        if (AA == '(') break;
        YY++;
    }
    mem66 = YY;

    //pos36732:
    // find ')'
    do
    {
        YY++;
        AA = GetRuleByte(mem62, YY);
    } while(AA != ')');
    mem65 = YY;

    //pos36741:
    // find '='
    do
    {
        YY++;
        AA = GetRuleByte(mem62, YY);
        AA = AA & 127;
    } while (AA != '=');
    mem64 = YY;

    XX = mem61;
    mem60 = XX;

    // compare the string within the bracket
    YY = mem66;
    YY++;
    //pos36759:
    while(1)
    {
        mem57 = inputtemp[XX];
        AA = GetRuleByte(mem62, YY);
        if (AA != mem57) goto pos36700;
        YY++;
        if(YY == mem65) break;
        XX++;
        mem60 = XX;
    }

// the string in the bracket is correct

//pos36787:
    AA = mem61;
    mem59 = mem61;

pos36791:
    while(1)
    {
        mem66--;
        YY = mem66;
        AA = GetRuleByte(mem62, YY);
        mem57 = AA;
        //36800: BPL 36805
        if ((AA & 128) != 0) goto pos37180;
        XX = AA & 127;
        AA = tab36376[XX] & 128;
        if (AA == 0) break;
        XX = mem59-1;
        AA = inputtemp[XX];
        if (AA != mem57) goto pos36700;
        mem59 = XX;
    }

//pos36833:
    AA = mem57;
    if (AA == ' ') goto pos36895;
    if (AA == '#') goto pos36910;
    if (AA == '.') goto pos36920;
    if (AA == '&') goto pos36935;
    if (AA == '@') goto pos36967;
    if (AA == '^') goto pos37004;
    if (AA == '+') goto pos37019;
    if (AA == ':') goto pos37040;
    //  Code42041();    //Error
    //36894: BRK
    return 0;

    // --------------

pos36895:
    Code37055(mem59);
    AA = AA & 128;
    if(AA != 0) goto pos36700;
pos36905:
    mem59 = XX;
    goto pos36791;

    // --------------

pos36910:
    Code37055(mem59);
    AA = AA & 64;
    if(AA != 0) goto pos36905;
    goto pos36700;

    // --------------


pos36920:
    Code37055(mem59);
    AA = AA & 8;
    if(AA == 0) goto pos36700;
pos36930:
    mem59 = XX;
    goto pos36791;

    // --------------

pos36935:
    Code37055(mem59);
    AA = AA & 16;
    if(AA != 0) goto pos36930;
    AA = inputtemp[XX];
    if (AA != 72) goto pos36700;
    XX--;
    AA = inputtemp[XX];
    if ((AA == 67) || (AA == 83)) goto pos36930;
    goto pos36700;

    // --------------

pos36967:
    Code37055(mem59);
    AA = AA & 4;
    if(AA != 0) goto pos36930;
    AA = inputtemp[XX];
    if (AA != 72) goto pos36700;
    if ((AA != 84) && (AA != 67) && (AA != 83)) goto pos36700;
    mem59 = XX;
    goto pos36791;

    // --------------


pos37004:
    Code37055(mem59);
    AA = AA & 32;
    if(AA == 0) goto pos36700;

pos37014:
    mem59 = XX;
    goto pos36791;

    // --------------

pos37019:
    XX = mem59;
    XX--;
    AA = inputtemp[XX];
    if ((AA == 'E') || (AA == 'I') || (AA == 'YY')) goto pos37014;
    goto pos36700;
    // --------------

pos37040:
    Code37055(mem59);
    AA = AA & 32;
    if(AA == 0) goto pos36791;
    mem59 = XX;
    goto pos37040;

//---------------------------------------


pos37077:
    XX = mem58+1;
    AA = inputtemp[XX];
    if (AA != 'E') goto pos37157;
    XX++;
    YY = inputtemp[XX];
    XX--;
    AA = tab36376[YY] & 128;
    if(AA == 0) goto pos37108;
    XX++;
    AA = inputtemp[XX];
    if (AA != 'R') goto pos37113;
pos37108:
    mem58 = XX;
    goto pos37184;
pos37113:
    if ((AA == 83) || (AA == 68)) goto pos37108;  // 'S' 'D'
    if (AA != 76) goto pos37135; // 'L'
    XX++;
    AA = inputtemp[XX];
    if (AA != 89) goto pos36700;
    goto pos37108;

pos37135:
    if (AA != 70) goto pos36700;
    XX++;
    AA = inputtemp[XX];
    if (AA != 85) goto pos36700;
    XX++;
    AA = inputtemp[XX];
    if (AA == 76) goto pos37108;
    goto pos36700;

pos37157:
    if (AA != 73) goto pos36700;
    XX++;
    AA = inputtemp[XX];
    if (AA != 78) goto pos36700;
    XX++;
    AA = inputtemp[XX];
    if (AA == 71) goto pos37108;
    //pos37177:
    goto pos36700;

    // -----------------------------------------

pos37180:

    AA = mem60;
    mem58 = AA;

pos37184:
    YY = mem65 + 1;

    //37187: CPYY 64
    //  if(? != 0) goto pos37194;
    if(YY == mem64) goto pos37455;
    mem65 = YY;
    //37196: LDAA (62),y
    AA = GetRuleByte(mem62, YY);
    mem57 = AA;
    XX = AA;
    AA = tab36376[XX] & 128;
    if(AA == 0) goto pos37226;
    XX = mem58+1;
    AA = inputtemp[XX];
    if (AA != mem57) goto pos36700;
    mem58 = XX;
    goto pos37184;
pos37226:
    AA = mem57;
    if (AA == 32) goto pos37295;   // ' '
    if (AA == 35) goto pos37310;   // '#'
    if (AA == 46) goto pos37320;   // '.'
    if (AA == 38) goto pos37335;   // '&'
    if (AA == 64) goto pos37367;   // ''
    if (AA == 94) goto pos37404;   // ''
    if (AA == 43) goto pos37419;   // '+'
    if (AA == 58) goto pos37440;   // ':'
    if (AA == 37) goto pos37077;   // '%'
    //pos37291:
    //  Code42041(); //Error
    //37294: BRK
    return 0;

    // --------------
pos37295:
    Code37066(mem58);
    AA = AA & 128;
    if(AA != 0) goto pos36700;
pos37305:
    mem58 = XX;
    goto pos37184;

    // --------------

pos37310:
    Code37066(mem58);
    AA = AA & 64;
    if(AA != 0) goto pos37305;
    goto pos36700;

    // --------------


pos37320:
    Code37066(mem58);
    AA = AA & 8;
    if(AA == 0) goto pos36700;

pos37330:
    mem58 = XX;
    goto pos37184;

    // --------------

pos37335:
    Code37066(mem58);
    AA = AA & 16;
    if(AA != 0) goto pos37330;
    AA = inputtemp[XX];
    if (AA != 72) goto pos36700;
    XX++;
    AA = inputtemp[XX];
    if ((AA == 67) || (AA == 83)) goto pos37330;
    goto pos36700;

    // --------------


pos37367:
    Code37066(mem58);
    AA = AA & 4;
    if(AA != 0) goto pos37330;
    AA = inputtemp[XX];
    if (AA != 72) goto pos36700;
    if ((AA != 84) && (AA != 67) && (AA != 83)) goto pos36700;
    mem58 = XX;
    goto pos37184;

    // --------------

pos37404:
    Code37066(mem58);
    AA = AA & 32;
    if(AA == 0) goto pos36700;
pos37414:
    mem58 = XX;
    goto pos37184;

    // --------------

pos37419:
    XX = mem58;
    XX++;
    AA = inputtemp[XX];
    if ((AA == 69) || (AA == 73) || (AA == 89)) goto pos37414;
    goto pos36700;

// ----------------------

pos37440:

    Code37066(mem58);
    AA = AA & 32;
    if(AA == 0) goto pos37184;
    mem58 = XX;
    goto pos37440;
pos37455:
    YY = mem64;
    mem61 = mem60;

    if (debug)
        PrintRule(mem62);

pos37461:
    //37461: LDAA (62),y
    AA = GetRuleByte(mem62, YY);
    mem57 = AA;
    AA = AA & 127;
    if (AA != '=')
    {
        mem56++;
        XX = mem56;
        input[XX] = AA;
    }

    //37478: BIT 57
    //37480: BPL 37485  //not negative flag
    if ((mem57 & 128) == 0) goto pos37485; //???
    goto pos36554;
pos37485:
    YY++;
    goto pos37461;
}

}
