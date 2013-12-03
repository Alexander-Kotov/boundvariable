#include <stdio.h>
#include <iterator>
#include <string.h>

const int   arabar[]  = {  1,   4,    5,   9,    10,  40,  50,   90,  100, 400,  500, 900,  1000 };
const char *romanar[] = { "I", "IV", "V", "IX", "X", "XL", "L", "XC", "C", "CD", "D", "CM", "M" };

char *arab2roman(unsigned short int arab)
{
    static char roman[80];
    const int m = sizeof(arabar)/sizeof(int)-1, arabmax=arabar[m];
    const char romanmax=romanar[m][0];
    int i, n;
    if(!arab) {
        *roman=0;
        return roman;
    }
    i=0;
    while(arab>arabmax) {
        roman[i++] = romanmax;
        arab      -= arabmax;
    }
    n=m;
    while(arab > 0) {
        if(arab >= arabar[n]) {
            roman[i++] = romanar[n][0];
            if(n&1)
                roman[i++] = romanar[n][1];
            arab -= arabar[n];
        } else
            n--;
    }
    roman[i]=0;
    return roman;
}

unsigned short int roman2arab(char *roman)
{
    const int m = sizeof(arabar)/sizeof(int)-1;
    unsigned short int arab;
    int len, n, i, pir;
    len=strlen(roman);

    arab=0;
    n=m;
    i=0;
    while(n >= 0 && i < len) {
        pir=n&1;
        if(roman[i] == romanar[n][0] && (!pir || roman[i+1] == romanar[n][1])) {
            arab += arabar[n];
            i    += 1+pir;
        } else
            n--;
    }
    return arab;
}

char const *RN(unsigned value)
{
    strdup(arab2roman(value));
}

int main()
{
    char const *usernameSource[] =
    {
        "ftd",
        "knr",
        //"guest",
        "gardener",
        "ohmega",
        "yang",
        "howie",
        "hmonk",
        "bbarker"
    };
    char const *wordSource[] =
    {
        "airplane",
        "alphabet",
        "aviator",
        "bidirectional",
        "changeme",
        "creosote",
        "cyclone",
        "december",
        "dolphin",
        "elephant",
        "ersatz",
        "falderal",
        "functional",
        "future",
        "guitar",
        "gymnast",
        "hello",
        "imbroglio",
        "january",
        "joshua",
        "kernel",
        "kingfish",
        "(\\b.bb)(\\v.vv)",
        "millennium",
        "monday",
        "nemesis",
        "oatmeal",
        "october",
        "paladin",
        "pass",
        "password",
        "penguin",
        "polynomial",
        "popcorn",
        "qwerty",
        "sailor",
        "swordfish",
        "symmetry",
        "system",
        "tattoo",
        "thursday",
        "tinman",
        "topography",
        "unicorn",
        "vader",
        "vampire",
        "viper",
        "warez",
        "xanadu",
        "xyzzy",
        "zephyr",
        "zeppelin",
        "zxcvbnm"
    };

    int line;
    line = 10;

    int usernameCount = std::end(usernameSource) - std::begin(usernameSource);
    int wordCount = std::end(wordSource) - std::begin(wordSource);

    printf("%s DIM user(%s) AS STRING\n", RN(line), RN(usernameCount));
    line += 10;
    for(int i = 0; i != usernameCount; ++i)
    {
        printf("%s user(%s) = \"%s\"\n", RN(line), RN(i + 1), usernameSource[i]);
        line += 10;
    }

    printf("%s DIM pass(%s) AS STRING\n", RN(line), RN(wordCount));
    line += 10;
    for(int i = 0; i != wordCount; ++i)
    {
        printf("%s pass(%s) = \"%s\"\n", RN(line), RN(i + 1), wordSource[i]);
        line += 10;
    }

    printf("%s DIM i AS INTEGER\n", RN(line));
    line += 10;
    printf("%s DIM j AS INTEGER\n", RN(line));
    line += 10;
    printf("%s DIM k AS INTEGER\n", RN(line));
    line += 10;
    printf("%s DIM m AS INTEGER\n", RN(line));
    line += 10;

    printf("%s i = %s\n", RN(line), RN(1));
    line += 10;
    char const *L1 = RN(line);
    printf("%s j = %s\n", RN(line), RN(1));
    line += 10;
    char const *L4 = RN(line);
    printf("%s IF CHECKPASS(user(i), pass(j)) THEN GOTO %s\n", RN(line), RN(2000));
    line += 10;
    printf("%s k = %s\n", RN(line), RN(1));
    line += 10;
    char const *L3 = RN(line);
    printf("%s m = %s\n", RN(line), RN(1));
    line += 10;
    char const *L2 = RN(line);
    printf("%s IF CHECKPASS(user(i), pass(j) + CHR(%s + k - %s) + CHR(%s + m - %s)) THEN GOTO %s\n", RN(line), RN(48), RN(1), RN(48), RN(1), RN(2200));
    line += 10;
    printf("%s m = m + %s\n", RN(line), RN(1));
    line += 10;
    printf("%s IF m <= %s THEN GOTO %s\n", RN(line), RN(10), L2);
    line += 10;
    printf("%s k = k + %s\n", RN(line), RN(1));
    line += 10;
    printf("%s IF k <= %s THEN GOTO %s\n", RN(line), RN(10), L3);
    line += 10;
    printf("%s j = j + %s\n", RN(line), RN(1));
    line += 10;
    printf("%s IF j <= %s THEN GOTO %s\n", RN(line), RN(wordCount), L4);
    line += 10;
    char const *L6 = RN(line);
    printf("%s i = i + %s\n", RN(line), RN(1));
    line += 10;
    printf("%s IF i <= %s THEN GOTO %s\n", RN(line), RN(usernameCount), L1);
    line += 10;

    printf("%s END\n", RN(line));

    line = 2000;
    printf("%s PRINT user(i) + \" \" + pass(j)\n", RN(line));
    line += 10;
    printf("%s PRINT CHR(%s)\n", RN(line), RN(10));
    line += 10;
    printf("%s GOTO %s\n", RN(line), L6);

    line = 2200;
    printf("%s PRINT user(i) + \" \" + pass(j) + CHR(%s + k - %s) + CHR(%s + m - %s)\n", RN(line), RN(48), RN(1), RN(48), RN(1));
    line += 10;
    printf("%s PRINT CHR(%s)\n", RN(line), RN(10));
    line += 10;
    printf("%s GOTO %s\n", RN(line), L6);

    return 0;
}
