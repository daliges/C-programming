// Course: Advanced C programming
// exercise 2, question 4
// file name: ex2_q3.c

// --------------------------- //
//
//	Assigned by:
//		Idan Rodrigez #211360755
//		Daniel Grubnyk #318816659
//
// --------------------------- //

// --------------------------------------- //
// Include and definition package section:
// --------------------------------------- //
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define scanf_s scanf
#define PATH1 "c:\\temp\\file1.txt"
#define PATH2 "c:\\temp\\file2.txt"
#define PATH3 "c:\\temp\\file3.txt"

// --------------------------------------- //
// Functions declration section:
// --------------------------------------- //

int memoryReport(char* filename);
int stringToNumPush(char* s, int* i);
int MatByteCalc(int* first, int* second);
// --------------------------------------- //
// Main section:
// --------------------------------------- //
int main()
{
	int total1, total2, total3;

	// Start Program:
	printf("Start Program\n");

	// call functions:
	total1 = memoryReport(PATH1);
	total2 = memoryReport(PATH2);
	total3 = memoryReport(PATH3);

	// write output:
	printf("Output:\n");
	printf("First file required %d bytes\n", total1);
	printf("Second file required %d bytes\n", total2);
	printf("Third file required %d bytes\n", total3);

	return 0;
}
// --------------------------- //


/// <summary>
/// The function receives a pointer to a string, representing a path to a file.
/// The function output all varibles declerations and their size in byte.
/// </summary>
/// <param>char *filename - valid path to a file</param>
/// <returns>total bytes required</returns>
///
int stringToNumPush(char* s, int* i)
{
	int  c = 0;
	while (s[*i] && s[*i] <= '9' && s[*i] >= '0')
	{
		c *= 10;
		c += s[(*i)++] - '0';
	}
	return c;
}


int MatByteCalc(int* first, int* second)
{
	int  c = 0;
	c = (*first) * (*second);
	return c;
}

int memoryReport(char* filename)
{
	FILE* f = fopen(filename, "r");
	if (f == NULL)
	{
		printf("Could not open file\n");
		return 0;
	}
	char s[200] = { 0 };
	char* string = fgets(s, sizeof(s), f);
	int i, size = strlen(s), v_size = 0, c, c2, total_sum = 0, ptr_size = 4;
	int token_ptr;
	char variable[3] = "";

	do
	{
		size = strlen(s);
		for (i = 0; i < size - 1; i++)
		{
			if ((i > 0) && (string[i - 1] == '*'))
			{
				break;
			}
			while ((string[i] == '\t') || (string[i] == ' '))
				++i;
			if (string[i] != ' ' && string[i] != '*')
			{
				variable[0] = string[i];
				if (variable[0] != 'l' && variable[0] != 'u')
				{
					variable[1] = '\0';
					for (; (string[i] != ' ') && (string[i] != '*'); i++); { // // // // //
						break;
					}
				}
				else
				{
					switch (variable[0])
					{
					case 'l':

						for (i = i + 5; i < size - 1; i++)
						{
							v_size = 8;
							while ((string[i] == '\t') || (string[i] == ' '))
								++i;
							if (string[i] == '*') {
								v_size = 4;
								variable[1] = '/0';
								variable[0] = '*';
								i++;
								break;
							}
							if (string[i] != ' ')
							{
								while ((string[i] == '\t') || (string[i] == ' '))
									++i;
								if (string[i] == 'l')
									if (string[i + 1] && string[i + 1] == 'o'
										&& string[i + 2] && string[i + 2] == 'n'
										&& string[i + 3] && string[i + 3] == 'g'
										/* && string[i + 4] && string[i + 4] == ' '*/)
									{
										variable[1] = 'l', variable[2] = '\0';
										i += 4;
									}
									else
										variable[1] = '/0';
								break;
							}
							else
							{
								break;
							}
							break;
						}
						break;
					case 'u':
						for (i = i + 8; i < size - 1; i++)
						{
							if (string[i] != ' ')
							{
								if (string[i] == 'i') {
									if (string[i + 1] && string[i + 1] == 'n'
										&& string[i + 2] && string[i + 2] == 't'
										/* && string[i + 3] && string[i + 3] == ' '*/)
									{
										i += 3;
										variable[1] = '/0';
									}
									else
										variable[1] = '/0';
								}
								else {
									i = i - 8;
								}
								break;
							}
						}
						break;
					}
				}
			}
			break;
		}

		switch (variable[0])
		{
		case 'c':
			v_size = sizeof(char);
			break;
		case 's':
			v_size = sizeof(short);
			break;
		case 'i':
			v_size = sizeof(int);
			break;
		case 'u':
			v_size = sizeof(unsigned int);
			break;
		case 'f':
			v_size = sizeof(float);
			break;
		case 'd':
			v_size = sizeof(double);
			break;
		case 'l':
			v_size = (variable[1] ? sizeof(long long) : sizeof(long));
			break;
		default:
			break;
		}
		while (i < size - 1)
		{
			if (string[i] != ' ' && string[i] != ',')
			{
				//when the string is *
				if (string[i] == '*')
				{
					for (i += 1; i < size; i++)
					{
						if (string[i] != ' ')
						{
							while (string[i] != ' ' && string[i] != ';' && string[i] != ',') {
								if (string[i] == '[') {
									break;
								}
								printf("%c", string[i++]);
							}
							while ((string[i] == '\t') || (string[i] == ' '))
								++i;
							if (string[i] == '[') {
								while ((string[i] == '\t') || (string[i] == ' '))
									++i;
								v_size = 4; //
								break;
							}
							printf(" requires %d\n", ptr_size);
							total_sum += ptr_size;
							break;
						}
					}

				}
				else
				{
					if (string[i] == ';')
						break;
					while (string[i] != ';' && string[i] != ' ' && string[i] != ',' && string[i] != '[') {
						while ((string[i] == '\t') || (string[i] == ' '))
							++i;
						printf("%c", string[i++]);

					}
					while ((string[i] == '\t') || (string[i] == ' '))
						++i;
					printf(" requires ");
					if (string[i] == '[')
					{
						i++;
						while ((string[i] == '\t') || (string[i] == ' '))
							++i;
						while ((string[i] == '\t') || (string[i] == ' '))
							++i;
						c = stringToNumPush(string, &(i));
						i++;
						while ((string[i] == '\t') || (string[i] == ' '))
							++i;
						if (string[i] == '[') {
							i++;
							c2 = stringToNumPush(string, &(i));
							printf("%d bytes\n", MatByteCalc(&c, &c2) * v_size);
							total_sum += MatByteCalc(&c, &c2) * v_size;
						}
						else
						{
							printf("%d bytes\n", c * v_size);
							total_sum += c * v_size;
						}

					}
					else {
						printf("%d bytes\n", v_size);
						total_sum += v_size;
					}
					i++;
				}
			}
			else
				i++;
		}
	} while (string = fgets(s, sizeof(s), f));
	fclose(f);
	return total_sum;
}