#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <String>
#include <cstring>

using namespace std;

char hex2byte(char* hs)
{
    char b = 0;
    char nibbles[2];
    int i;

    for (i = 0; i < 2; i++) {
        if ((hs[i] >= '0') && (hs[i] <= '9'))
            nibbles[i] = hs[i] - '0';
        else if ((hs[i] >= 'A') && (hs[i] <= 'F'))
            nibbles[i] = (hs[i] - 'A') + 10;
        else if ((hs[i] >= 'a') && (hs[i] <= 'f'))
            nibbles[i] = (hs[i] - 'a') + 10;
        else
            return 0;
    }

    b = (nibbles[0] << 4) | nibbles[1];
    return b;
}

int main(int argc, char* argv[]) {
    printf("We have %d arguments:\n", argc);
    for (int i = 0; i < argc; ++i) {
        printf("[%d] %s\n", i, argv[i]);
    }

    for (size_t k = 1; k < argc; k++)
    {
        fstream tb_file(argv[k], ios::in);
        if (!tb_file.is_open()) {
            printf("Failed to open file.\n");
            system("pause");
            return 0;
        }

        string outFileName = argv[k];
        outFileName.insert(outFileName.length() - 4, "_int");
        fstream tb_outFile(outFileName, ios::out);
        cout << outFileName << ".....";

        vector<string> lines;
        string line;

        while (getline(tb_file, line)) {
            lines.push_back(line);
        }

        for (size_t i = 0; i < lines.size(); i++)
        {
            if (lines[i] != "")
                if (lines[i].length() != 78) {
                    tb_file.close();
                    tb_outFile.close();
                    printf("Error length Data [%d]\n", (int)i);
                    system("pause");
                    return 0;
                }
                else
            {
                char f_d[79];
                uint8_t dest_val[26];
                float d[6];
                strcpy(f_d, lines[i].c_str());
                for (size_t j = 0; j < 26; j++) dest_val[j] = hex2byte(&f_d[j * 3]);
                for (size_t j = 0; j < 6; j++)  d[j] = *(float*)&dest_val[j * 4];
                for (size_t j = 0; j < 6; j++) tb_outFile << d[j] << " ";
                tb_outFile << endl;
            }
        }
        tb_file.close();
        tb_outFile.close();
        printf("done\n");
    }
    return 0;
}
