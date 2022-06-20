#include <iostream>
#include <fstream>
#include "QS.h"

using namespace std;

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK


int main(int argc, char * argv[]) {

    VS_MEM_CHECK               // enable memory leak check

    if (argc < 3)
    {
        cerr << "Please provide name of input and output files";
        return 1;
    }
    cout << "Input file: " << argv[1] << endl;
    ifstream in(argv[1]);
    if (!in)
    {
        cerr << "Unable to open " << argv[1] << " for input";
        return 1;
    }
    cout << "Output file: " << argv[2] << endl;
    ofstream out(argv[2]);
    if (!out)
    {
        in.close();
        cerr << "Unable to open " << argv[2] << " for output";
    }


    QS<int>* myArray = new QS<int>(NULL); ///new
    for (string line; getline(in, line);) {
        try {

            string commandLine;
            int itemValue, left, right, pivotIndex;
            if (line.size() == 0) continue;

            istringstream iss(line);
            iss >> commandLine;

            if (commandLine == "QuickSort") {

                iss >> itemValue;
                out << commandLine << " " << itemValue << " ";

                myArray->clear();
                delete myArray;

                myArray = new QS<int>(itemValue);

                out << "OK" << endl;

            }

            else if (commandLine == "AddToArray") {

                stringstream itemsAdded;

                out << commandLine << "  ";

                while (iss >> itemValue) {

                    itemsAdded << itemValue << ",";
                    myArray->addElement(itemValue);

                }

                string line = itemsAdded.str();

                out << line.substr(0, line.length()-1) << " OK" << endl;

            }

            else if (commandLine == "Capacity") {

                out << commandLine << " ";

                out << myArray->capacity() << endl;

            }
            else if (commandLine == "Clear") {

                out << commandLine << " ";

                myArray->clear();

                out << "OK" << endl;

            }

            else if (commandLine == "Size") {

                out << commandLine << " ";

                out << myArray->size() << endl;

            }
            else if (commandLine == "Sort") {

                iss >> left;
                iss >> right;
                out << commandLine << " " << left << "," << right << " ";
                myArray->resetStats();
                myArray->sort(left, right);
                out << "OK" << endl;
            }

            else if (commandLine == "SortAll") {

                out << commandLine << " ";

                myArray->resetStats();
                myArray->sortAll();

                out << "OK" << endl;
            }

            else if (commandLine == "MedianOfThree") {

                iss >> left;
                iss >> right;

                out << commandLine << " " << left << "," << right << " = ";

                out << myArray->medianOfThree(left, right) << endl;

            }

            else if (commandLine == "Partition") {

                iss >> left;
                iss >> right;
                iss >> pivotIndex;

                out << commandLine << " " << left << "," << right << "," << pivotIndex << " = ";

                out << myArray->partition(left, right, pivotIndex) << endl;

            }

            else if (commandLine == "PrintArray") {

                iss >> itemValue;

                out << commandLine << " " << myArray->toString();

                out  << endl;
            }

            else if (commandLine == "Stats") { ///BONUS

                out << commandLine << " ";

                out <<  myArray->comparisons() << "," << myArray->exchanges() << endl;

            }

        }
        catch (string error) {
            out << error << endl;
        }



    }

    myArray->clear();
    delete myArray;

    in.close();
    out.close();

    in.open(argv[2]);

    string line;
    if (in.is_open()) {
        while (getline(in, line)) {
            try {
                //if (line.empty()) continue;
                cout << line << endl;
            } catch (exception &e) { cout << e.what(); }
        }
    } else cout << "Unable to read from output file." << endl;
    in.close();

    return 0;

}
#endif