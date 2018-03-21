//work with string
void replace(char *s, char a, char b);

int strEnd(char *string, char *end);

int strIn(char *string, char *find);

void moveCharLeft(char *string);

void moveCharRight(char *string);

void trimLeft(char *string);

void trimMiddle(char *string);

void trimRight(char *string);

char codeLetter(char a, int n);

char *code(char *string, int n);

void capitalLetterOff(char *a);

void capitalLetterOn(char *a);

void capitalOn(char *buffer);

void capitalOff(char *buffer);

//work with number
int checkPrime(int number);

int checkPerfectNumber(int n);

int getRandomNumber(int min, int max); //srand(time(NULL)) in main once time

void convertHexa(int *number, int num);

int decimalToBinary(int number, int *binary);

int decimalToHexa(int number, int *hexa);

int decimalToOctal(int number, int *octal);

void printHexa(int *hexa, int num);
