//Implement lexical analyser using C for recognizing the following tokens:
//• 24 keywords (given in the following program)
//• Identifiers with the regular expression : letter(letter | digit)*
//• Integers with the regular expression: digit+
//• Relational operators: <, >, <=, >=, ==, !=
//• Ignores everything between multi line comments (/* .... */)
//• Storing identifiers in symbol table.


#include <stdio.h>
#include <ctype.h>
#include <string.h>

char keyword[30][30] = {"int", "while", "break", "for", "do", "if", "float", "char", "switch", "double", "short", "long", "unsigned", "sizeof", "else", "register", "extern", "static", "auto", "case", "break", "volatile", "enum", "typedef"};
char id[20], num[10];
char symbol_table[100][20];  // Declare symbol table as a doubly dimensional array of characters.
int symbol_count = 0;        // Counter for symbol table entries.

int check_keyword(char s[])
{
    int i;
    for (i = 0; i < 24; i++)
        if (strcmp(s, keyword[i]) == 0)
            return 1;
    return 0;
}

// Function to store an identifier in the symbol table.
void store_symbol(char id[])
{
    // Check whether the id is already available in the symbol table, if available, ignore.
    for (int i = 0; i < symbol_count; i++)
    {
        if (strcmp(symbol_table[i], id) == 0)
        {
            return; // Identifier is already in the symbol table.
        }
    }

    // If not found, add it to the symbol table.
    strcpy(symbol_table[symbol_count], id);
    symbol_count++;
}

int main()
{
    FILE *fp1, *fp2;
    char c;
    int state = 0;
    int i = 0, j = 0;
    fp1 = fopen("x.txt", "r"); // Input file containing source code.
    fp2 = fopen("y.txt", "w"); // Output file name

    while ((c = fgetc(fp1)) != EOF)
    {
        switch (state)
        {
        case 0:
            if (isalpha(c))
            {
                state = 1;
                id[i++] = c;
            }
            else if (isdigit(c))
            {
                state = 3;
                num[j++] = c;
            }
            else if (c == '<' || c == '>')
                state = 5;
            else if (c == '=' || c == '!')
                state = 8;
            else if (c == '/')
                state = 10;
            else if (c == ' ' || c == '\t' || c == '\n')
                state = 0;
            else
                fprintf(fp2, "\n%c", c);
            break;

        case 1:
            if (isalnum(c))
            {
                state = 1;
                id[i++] = c;
            }
            else
            {
                id[i] = '\0';
                if (check_keyword(id))
                    fprintf(fp2, "\n %s : keyword ", id);
                else
                {
                    fprintf(fp2, "\n %s : identifier", id);
                    // Call the function to store the identifier in the symbol table.
                    store_symbol(id);
                }
                state = 0;
                i = 0;
                ungetc(c, fp1);
            }
            break;

        case 3:
            if (isdigit(c))
            {
                num[j++] = c;
                state = 3;
            }
            else
            {
                num[j] = '\0';
                fprintf(fp2, "\n%s: number", num);
                state = 0;
                j = 0;
                ungetc(c, fp1);
            }
            break;

        case 5:
            if (c == '=')
            {
                fprintf(fp2, "\n relational operator: ");
                fprintf(fp2, "<=");
                state = 0;
            }
            else
            {
                fprintf(fp2, "\n relational operator: ");
                fprintf(fp2, "<");
                state = 0;
                ungetc(c, fp1);
            }
            break;

        case 8:
            if (c == '=')
            {
                fprintf(fp2, "\n relational operator: ");
                fprintf(fp2, "==");
                state = 0;
            }
            else
            {
                fprintf(fp2, "\n relational operator: ");
                fprintf(fp2, "!=");
                state = 0;
                ungetc(c, fp1);
            }
            break;

        case 10:
            if (c == '*')
                state = 11;
            else
                fprintf(fp2, "\n invalid lexeme");
            break;

        case 11:
            if (c == '*')
                state = 12;
            else
                state = 11;
            break;

        case 12:
            if (c == '*')
                state = 12;
            else if (c == '/')
                state = 0;
            else
                state = 11;
            break;
        } // End of switch
    }     // End of while

    if (state == 11)
        fprintf(fp2, "comment did not close");

    // Print the contents of the symbol table.
    fprintf(fp2, "\n\nSymbol Table:\n");
    for (int k = 0; k < symbol_count; k++)
    {
        fprintf(fp2, "%s\n", symbol_table[k]);
    }

    fclose(fp1);
    fclose(fp2);
    return 0;
}

