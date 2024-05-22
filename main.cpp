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
#include <vector>
#include "extra_tc.h"
#include <filesystem>
using namespace std;

// int main()
// {
//     TestStudyInPink::tc_1001();
//     TestStudyInPink::tc_1004();
//     TestStudyInPink::tc_1009();
//     TestStudyInPink::tc_1014();
//     TestStudyInPink::tc_1015();
//     TestStudyInPink::tc_1016();
//     TestStudyInPink::tc_1017();
//     TestStudyInPink::tc_1057();
//     TestStudyInPink::tc_1062();
//     TestStudyInPink::tc_1063();
//     TestStudyInPink::tc_1066();
//     TestStudyInPink::tc_1067();
//     TestStudyInPink::tc_1070();
//     TestStudyInPink::tc_1094();
//     TestStudyInPink::tc_1099();
//     TestStudyInPink::tc_1109();
//     TestStudyInPink::tc_1114();
//     TestStudyInPink::tc_1120();
//     TestStudyInPink::tc_1132();
//     TestStudyInPink::tc_1138();
//     TestStudyInPink::tc_1143();
//     TestStudyInPink::tc_1153();
//     TestStudyInPink::tc_1159();
//     TestStudyInPink::tc_1167();
//     TestStudyInPink::tc_1181();
//     TestStudyInPink::tc_1185();
//     TestStudyInPink::tc_1199();
//     TestStudyInPink::tc_1211();
//     TestStudyInPink::tc_1223();
//     TestStudyInPink::tc_1235();
//     TestStudyInPink::tc_1247();
//     TestStudyInPink::tc_1297();
//     TestStudyInPink::tc_1323();
//     TestStudyInPink::tc_1004();
//     TestStudyInPink::tc_1009();
//     TestStudyInPink::tc_1014();
//     TestStudyInPink::tc_1015();
//     TestStudyInPink::tc_1016();
//     TestStudyInPink::tc_1017();
//     TestStudyInPink::tc_1043();
//     TestStudyInPink::tc_1057();
//     TestStudyInPink::tc_1062();
//     TestStudyInPink::tc_1063();
//     TestStudyInPink::tc_1066();
//     TestStudyInPink::tc_1067();
//     TestStudyInPink::tc_1070();
//     TestStudyInPink::tc_1094();
//     TestStudyInPink::tc_1114();
//     TestStudyInPink::tc_1120();
//     TestStudyInPink::tc_1132();
//     TestStudyInPink::tc_1138();
//     TestStudyInPink::tc_1143();
//     TestStudyInPink::tc_1153();
//     TestStudyInPink::tc_1159();
//     TestStudyInPink::tc_1167();
//     TestStudyInPink::tc_1171();
//     TestStudyInPink::tc_1181();
//     TestStudyInPink::tc_1185();
//     TestStudyInPink::tc_1199();
//     TestStudyInPink::tc_1211();
//     TestStudyInPink::tc_1223();
//     TestStudyInPink::tc_1235();
//     TestStudyInPink::tc_1247();
//     TestStudyInPink::tc_1278();
//     TestStudyInPink::tc_1297();
//     TestStudyInPink::tc_1323();
//     TestStudyInPink::tc_1286();
//     TestStudyInPink::tc_1194();
//     TestStudyInPink::tc_1253();
//     TestStudyInPink::tc_1354();
// }
// void g_satc_02()
// { // global
//     cout << "----- Sample Testcase 02 -----" << endl;
//     Configuration *config = new Configuration("C:\\Users\\Nem\\VNU-HCMUT\\intial\\sa_tc_02_config");
//     cout << config->str() << endl;
//     delete config;
// }

// BaseItem *stringtoItem(const string &input)
// {
//     if (input == "MAGIC_BOOK")
//         return new MagicBook();
//     else if (input == "ENERGY_DRINK")
//         return new EnergyDrink();
//     else if (input == "FIRST_AID")
//         return new FirstAid();
//     else if (input == "EXCEMPTION_CARD")
//         return new ExcemptionCard();
//     else
//         return new PassingCard("all");
// }

// // Ham stringToItemType chuyen string thanh ItemType
// ItemType stringtoItemType(const string &input)
// {
//     if (input == "MAGIC_BOOK")
//         return MAGIC_BOOK;
//     else if (input == "ENERGY_DRINK")
//         return ENERGY_DRINK;
//     else if (input == "FIRST_AID")
//         return FIRST_AID;
//     else if (input == "EXCEMPTION_CARD")
//         return EXCEMPTION_CARD;
//     else
//         return PASSING_CARD;
// }

// class TestStudyInPink
// {
// public:
//     TestStudyInPink() = default;

//     static void satc_01()
//     {
//         cout << "----- Sample Testcase 01 -----" << endl;
//         int num_walls = 3;
//         Position arr_walls[] = {Position(1, 2), Position(2, 3), Position(3, 4)};
//         int num_fake_walls = 1;
//         Position arr_fake_walls[] = {Position(2, 0)};

//         Map *map = new Map(10, 10, num_walls, arr_walls, num_fake_walls, arr_fake_walls);

//         Sherlock *sherlock = new Sherlock(1, "RUU", Position(1, 3), map, 250, 450);
//         cout << sherlock->str() << endl;

//         Watson *watson = new Watson(2, "LU", Position(2, 1), map, 300, 350);
//         cout << watson->str() << endl;

//         Criminal *criminal = new Criminal(0, Position(7, 9), map, sherlock, watson);
//         cout << criminal->str() << endl;

//         cout << "* Sherlock makes a move" << endl;
//         sherlock->move();
//         cout << sherlock->str() << endl;

//         cout << "* Watson makes a move" << endl;
//         watson->move();
//         cout << watson->str() << endl;

//         cout << "* Criminal makes a move" << endl;
//         criminal->move();
//         cout << criminal->str() << endl;

//         ArrayMovingObject *arr_mv_objs = new ArrayMovingObject(10);
//         arr_mv_objs->add(criminal);
//         arr_mv_objs->add(sherlock);
//         arr_mv_objs->add(watson);
//         cout << arr_mv_objs->str() << endl;

//         delete arr_mv_objs;
//         delete sherlock;
//         delete watson;
//         delete criminal;
//         delete map;
//     }

//     static void satc_02()
//     {
//         g_satc_02();
//     }

//     static void satc_03()
//     {
//         // Sample test for RobotC
//         cout << "----- Sample Testcase 03 -----" << endl;
//         int num_walls = 3;
//         Position arr_walls[] = {Position(1, 2), Position(2, 3), Position(3, 4)};
//         int num_fake_walls = 1;
//         Position arr_fake_walls[] = {Position(2, 0)};

//         Map *map = new Map(10, 10, num_walls, arr_walls, num_fake_walls, arr_fake_walls);

//         Sherlock *sherlock = new Sherlock(1, "RUU", Position(1, 3), map, 250, 450);
//         Watson *watson = new Watson(2, "LU", Position(2, 1), map, 300, 350);
//         Criminal *criminal = new Criminal(0, Position(7, 9), map, sherlock, watson);
//         criminal->move();

//         RobotC *robotC = new RobotC(3, Position(7, 9), map, criminal);
//         cout << "Current position of Criminal: " << criminal->str() << endl;
//         cout << "Criminal makes a move" << endl;
//         criminal->move();
//         cout << "New position of Criminal: " << criminal->str() << endl;

//         cout << "Current position of robotC: " << robotC->str() << endl;
//         cout << "RobotC makes a move" << endl;
//         robotC->move();
//         cout << "New position of robotC: " << robotC->str() << endl;

//         RobotW *robotW = new RobotW(4, Position(4, 9), map, criminal, watson);
//         cout << "RobotW makes a move" << endl;
//         robotW->move();
//         cout << "New position of robotW: " << robotW->str() << endl;

//         RobotS *robotS = new RobotS(5, Position(5, 9), map, criminal, sherlock);
//         cout << "RobotS makes a move" << endl;
//         robotS->move();
//         cout << "New position of robotS: " << robotS->str() << endl;

//         RobotSW *robotSW = new RobotSW(6, Position(6, 9), map, criminal, sherlock, watson);
//         cout << "RobotSW makes a move" << endl;
//         robotSW->move();
//         cout << "New position of robotSW: " << robotSW->str() << endl;

//         delete sherlock;
//         delete watson;
//         delete criminal;
//         delete map;
//         delete robotC;
//         delete robotW;
//         delete robotS;
//         delete robotSW;
//     }
//     static void satc_04()
//     {
//         auto *program = new StudyPinkProgram("C:\\Users\\Nem\\VNU-HCMUT\\intial\\sa_tc_02_config");
//         program->run(true);
//         delete program;
//     }

//     static void satc_05(string input_file)
//     {
//         int num_walls = 3;
//         Position arr_walls[] = {Position(1, 2), Position(2, 3), Position(3, 4)};
//         int num_fake_walls = 1;
//         Position arr_fake_walls[] = {Position(2, 0)};
//         Map *map = new Map(10, 10, num_walls, arr_walls, num_fake_walls, arr_fake_walls);

//         ifstream infile(input_file); // Mở file

//         int hp_sher;
//         int hp_wat;
//         int exp_sher;
//         int exp_wat;
//         vector<BaseItem *> items;

//         infile >> hp_sher;
//         infile >> hp_wat;
//         infile >> exp_sher;
//         infile >> exp_wat;

//         Sherlock *sherlock = new Sherlock(0, "RL", Position(1, 3), map, hp_sher, exp_sher);
//         cout << sherlock->str() << " HP: " << hp_sher << " EXP: " << exp_sher << endl;
//         Watson *watson = new Watson(1, "UD", Position(2, 1), map, hp_wat, exp_wat);
//         cout << watson->str() << " HP: " << hp_wat << " EXP: " << exp_wat << endl;

//         BaseBag *sher_bag = new SherlockBag(sherlock);
//         cout << sher_bag->str() << endl;
//         BaseBag *wat_bag = new WatsonBag(watson);
//         cout << wat_bag->str() << endl;
//         int numline = 3;
//         string line;

//         while (getline(infile, line))
//         {
//             numline++;
//             istringstream iss(line);
//             string command;
//             iss >> command;

//             if (command == "INSERT")
//             {
//                 string input;
//                 iss >> input;
//                 cout << "LINE " << numline << ": * Insert " << input << " into bag" << endl;
//                 BaseItem *tempitem = stringtoItem(input);
//                 items.push_back(tempitem);
//                 sher_bag->insert(tempitem);
//                 wat_bag->insert(tempitem);
//                 cout << "SherlockBag: " << sher_bag->str() << endl;
//                 cout << "WatsonBag " << wat_bag->str() << endl;
//             }
//             else if (command == "GET")
//             {
//                 string input;
//                 iss >> input;
//                 cout << "LINE " << numline << ": * Get " << input << " from bag" << endl;
//                 if (input.empty())
//                 {
//                     sher_bag->get();
//                     wat_bag->get();
//                 }
//                 else
//                 {
//                     sher_bag->get(stringtoItemType(input));
//                     wat_bag->get(stringtoItemType(input));
//                 }
//                 cout << "SherlockBag: " << sher_bag->str() << endl;
//                 cout << "WatsonBag " << wat_bag->str() << endl;
//             }
//         }
//         infile.close();
//         cout << "End." << endl;

//         delete sherlock;
//         delete watson;
//         delete sher_bag;
//         delete wat_bag;
//         delete map;
//         for (int i = 0; i < items.size(); i++)
//         {
//             if (items[i] != nullptr)
//                 delete items[i];
//         }
//     }
// };

//
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
        }

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