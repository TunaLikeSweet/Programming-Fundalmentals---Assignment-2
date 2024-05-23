/*
 * Ho Chi Minh City University of Technology
 * Faculty of Computer Science and Engineering
 * Initial code for Assignment 1
 * Programming Fundamentals Spring 2023
 * Author: Vu Van Tien
 * Date: 01.03.2023
 */

// The library here is concretely set, students are not allowed to include any other libraries.

#include "study_in_pink2.h"
#include "extra_tc.h"
#include "main.h"
#include <filesystem>
#include <vector>
using namespace std;

// Global:

int main()
{
    // List of test cases
    vector<pair<void (*)(), string>> testCases = {
        {TestStudyInPink::tc_1001, "tc_1001.out"},
        {TestStudyInPink::tc_1004, "tc_1004.out"},
        {TestStudyInPink::tc_1009, "tc_1009.out"},
        {TestStudyInPink::tc_1014, "tc_1014.out"},
        {TestStudyInPink::tc_1015, "tc_1015.out"},
        {TestStudyInPink::tc_1016, "tc_1016.out"},
        {TestStudyInPink::tc_1017, "tc_1017.out"},
        {TestStudyInPink::tc_1043, "tc_1043.out"},
        {TestStudyInPink::tc_1057, "tc_1057.out"},
        {TestStudyInPink::tc_1062, "tc_1062.out"},
        {TestStudyInPink::tc_1063, "tc_1063.out"},
        {TestStudyInPink::tc_1066, "tc_1066.out"},
        {TestStudyInPink::tc_1067, "tc_1067.out"},
        {TestStudyInPink::tc_1070, "tc_1070.out"},
        {TestStudyInPink::tc_1094, "tc_1094.out"},
        {TestStudyInPink::tc_1099, "tc_1099.out"},
        {TestStudyInPink::tc_1109, "tc_1109.out"},
        {TestStudyInPink::tc_1114, "tc_1114.out"},
        {TestStudyInPink::tc_1120, "tc_1120.out"},
        {TestStudyInPink::tc_1132, "tc_1132.out"},
        {TestStudyInPink::tc_1138, "tc_1138.out"},
        {TestStudyInPink::tc_1143, "tc_1143.out"},
        {TestStudyInPink::tc_1153, "tc_1153.out"},
        {TestStudyInPink::tc_1159, "tc_1159.out"},
        {TestStudyInPink::tc_1167, "tc_1167.out"},
        {TestStudyInPink::tc_1171, "tc_1171.out"},
        {TestStudyInPink::tc_1181, "tc_1181.out"},
        {TestStudyInPink::tc_1185, "tc_1185.out"},
        {TestStudyInPink::tc_1194, "tc_1194.out"},
        {TestStudyInPink::tc_1199, "tc_1199.out"},
        {TestStudyInPink::tc_1211, "tc_1211.out"},
        {TestStudyInPink::tc_1223, "tc_1223.out"},
        {TestStudyInPink::tc_1235, "tc_1235.out"},
        {TestStudyInPink::tc_1247, "tc_1247.out"},
        {TestStudyInPink::tc_1253, "tc_1253.out"},
        {TestStudyInPink::tc_1278, "tc_1278.out"},
        {TestStudyInPink::tc_1286, "tc_1286.out"},
        {TestStudyInPink::tc_1297, "tc_1297.out"},
        {TestStudyInPink::tc_1323, "tc_1323.out"},
        {TestStudyInPink::tc_1354, "tc_1354.out"},

    };

    for (const auto &testCase : testCases)
    {
        // Redirect cout to a file
        streambuf *coutbuf = cout.rdbuf();
        ofstream out(R"(C:\Users\\Nem\VNU-HCMUT\intial\Result\)" + testCase.second);
        if (!out)
        {
            cerr << "Failed to open output file for " << testCase.second << "\n";
            continue;
        }
        cout.rdbuf(out.rdbuf());

        try
        {
            // Run the test case
            testCase.first();

            // Flush the output stream
            cout.flush();
        }
        catch (const std::exception &e)
        {
            // Print the exception message to the original cout
            std::cout.rdbuf(coutbuf);
            std::cout << "Exception in " << testCase.second << ": " << e.what() << "\n";
            out.close();
            continue;
        }
        out.close();
        if (out.fail())
        {
            cerr << "Failed to write to output file for " << testCase.second << "\n";
            continue;
        }
        else
            // Reset cout
            cout.rdbuf(coutbuf);
    }

    // Compare the output files
    for (const auto &entry : filesystem::directory_iterator("Result"))
    {
        ifstream resultFile(entry.path());
        ifstream expectedFile("C:\\Users\\Nem\\VNU-HCMUT\\intial\\output\\" + entry.path().filename().string());

        if (!expectedFile)
        {
            cout << "No expected output for " << entry.path().filename() << "\n";
            continue;
        }

        string result((istreambuf_iterator<char>(resultFile)), istreambuf_iterator<char>());
        string expected((istreambuf_iterator<char>(expectedFile)), istreambuf_iterator<char>());

        if (result != expected)
        {
            cout << "Mismatch in " << entry.path().filename() << "\n";
        }
        else if (result.empty())
        {
            cout << "Empty output for " << entry.path().filename() << "\n";
        }
        else
        {
            cout << "Match in " << entry.path().filename() << "\n";
        }
    }
    return 0;
}
