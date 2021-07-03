#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <pthread.h>
#include <sys/wait.h>
#include <algorithm>
using namespace std;


string readFile(string filename)        //Will read the file and store it into string
{
    string read;
    char c;

    fstream obj (filename + ".txt", ios::in);       //Opening file

    if (obj)
    {
        c = obj.get();
        while (!obj.eof())
        {
           if (isupper(c))
            c = tolower(c);

           read += c; 
           c = obj.get();
        }
        obj.close();
    }
    else
    {
        cout<<"File not opened!"<<endl;
    }

    return read;

}

void* countLetter(void* arg) 
{
    string read = readFile("test");
    int n = *((int *)arg); 
    char letter = (char)n;

    int count=0;
    for (int i=0; i< read.length(); i++)
    {
        if (read[i] == letter)
        {
            count++;
        }
    }

    memcpy(arg, &count, sizeof(int));

    return NULL;
}

int main()
{
    char letter = 'a';
    int sum = 0;

    for (letter = 'a'; letter <= 'z'; letter++)
    {
        int temp = (int)letter;

        pthread_t tid;
        pthread_create(&tid, NULL, countLetter, (void*) &temp);

        pthread_join(tid, NULL);

        cout << letter << " = " << temp << endl;
        sum += temp;
    }

    cout << "The total number of characters in file = " << sum << endl;

    pthread_exit(NULL);
}