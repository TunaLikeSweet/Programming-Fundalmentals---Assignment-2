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
using namespace std;

void g_satc_02()
{ // global
    cout << "----- Sample Testcase 02 -----" << endl;
    Configuration *config = new Configuration("C:\\Users\\Nem\\VNU-HCMUT\\intial\\sa_tc_02_config");
    cout << config->str() << endl;
    delete config;
}

BaseItem *stringtoItem(string input)
{
    if (input == "MAGIC_BOOK")
        return new MagicBook();
    else if (input == "ENERGY_DRINK")
        return new EnergyDrink();
    else if (input == "FIRST_AID")
        return new FirstAid();
    else if (input == "EXCEMPTION_CARD")
        return new ExcemptionCard();
    else
        return new PassingCard("all");
}

// Ham stringToItemType chuyen string thanh ItemType
ItemType stringtoItemType(string input)
{
    if (input == "MAGIC_BOOK")
        return MAGIC_BOOK;
    else if (input == "ENERGY_DRINK")
        return ENERGY_DRINK;
    else if (input == "FIRST_AID")
        return FIRST_AID;
    else if (input == "EXCEMPTION_CARD")
        return EXCEMPTION_CARD;
    else
        return PASSING_CARD;
}

class TestStudyInPink
{
public:
    TestStudyInPink() = default;

    static void satc_01()
    {
        cout << "----- Sample Testcase 01 -----" << endl;
        int num_walls = 3;
        Position arr_walls[] = {Position(1, 2), Position(2, 3), Position(3, 4)};
        int num_fake_walls = 1;
        Position arr_fake_walls[] = {Position(2, 0)};

        Map *map = new Map(10, 10, num_walls, arr_walls, num_fake_walls, arr_fake_walls);

        Sherlock *sherlock = new Sherlock(1, "RUU", Position(1, 3), map, 250, 450);
        cout << sherlock->str() << endl;

        Watson *watson = new Watson(2, "LU", Position(2, 1), map, 300, 350);
        cout << watson->str() << endl;

        Criminal *criminal = new Criminal(0, Position(7, 9), map, sherlock, watson);
        cout << criminal->str() << endl;

        cout << "* Sherlock makes a move" << endl;
        sherlock->move();
        cout << sherlock->str() << endl;

        cout << "* Watson makes a move" << endl;
        watson->move();
        cout << watson->str() << endl;

        cout << "* Criminal makes a move" << endl;
        criminal->move();
        cout << criminal->str() << endl;

        ArrayMovingObject *arr_mv_objs = new ArrayMovingObject(10);
        arr_mv_objs->add(criminal);
        arr_mv_objs->add(sherlock);
        arr_mv_objs->add(watson);
        cout << arr_mv_objs->str() << endl;

        delete arr_mv_objs;
        delete sherlock;
        delete watson;
        delete criminal;
        delete map;
    }

    static void satc_02()
    {
        g_satc_02();
    }

    static void satc_03()
    {
        // Sample test for RobotC
        cout << "----- Sample Testcase 03 -----" << endl;
        int num_walls = 3;
        Position arr_walls[] = {Position(1, 2), Position(2, 3), Position(3, 4)};
        int num_fake_walls = 1;
        Position arr_fake_walls[] = {Position(2, 0)};

        Map *map = new Map(10, 10, num_walls, arr_walls, num_fake_walls, arr_fake_walls);

        Sherlock *sherlock = new Sherlock(1, "RUU", Position(1, 3), map, 250, 450);
        Watson *watson = new Watson(2, "LU", Position(2, 1), map, 300, 350);
        Criminal *criminal = new Criminal(0, Position(7, 9), map, sherlock, watson);
        criminal->move();

        RobotC *robotC = new RobotC(3, Position(7, 9), map, criminal);
        cout << "Current position of Criminal: " << criminal->str() << endl;
        cout << "Criminal makes a move" << endl;
        criminal->move();
        cout << "New position of Criminal: " << criminal->str() << endl;

        cout << "Current position of robotC: " << robotC->str() << endl;
        cout << "RobotC makes a move" << endl;
        robotC->move();
        cout << "New position of robotC: " << robotC->str() << endl;

        RobotW *robotW = new RobotW(4, Position(4, 9), map, criminal, watson);
        cout << "RobotW makes a move" << endl;
        robotW->move();
        cout << "New position of robotW: " << robotW->str() << endl;

        RobotS *robotS = new RobotS(5, Position(5, 9), map, criminal, sherlock);
        cout << "RobotS makes a move" << endl;
        robotS->move();
        cout << "New position of robotS: " << robotS->str() << endl;

        RobotSW *robotSW = new RobotSW(6, Position(6, 9), map, criminal, sherlock, watson);
        cout << "RobotSW makes a move" << endl;
        robotSW->move();
        cout << "New position of robotSW: " << robotSW->str() << endl;

        delete sherlock;
        delete watson;
        delete criminal;
        delete map;
        delete robotC;
        delete robotW;
        delete robotS;
        delete robotSW;
    }
    static void satc_04()
    {
        StudyPinkProgram *program = new StudyPinkProgram("C:\\Users\\Nem\\VNU-HCMUT\\intial\\sa_tc_02_config");
        program->run(true);
        delete program;
    }

    static void satc_05(const string &filepath)
    {
        int num_walls = 3;
        Position arr_walls[] = {Position(1, 2), Position(2, 3), Position(3, 4)};
        int num_fake_walls = 1;
        Position arr_fake_walls[] = {Position(2, 0)};
        Map *map = new Map(10, 10, num_walls, arr_walls, num_fake_walls, arr_fake_walls);

        ifstream infile(filepath); // Mở file

        int hp_sher;
        int hp_wat;
        int exp_sher;
        int exp_wat;
        vector<BaseItem *> items;

        infile >> hp_sher;
        infile >> hp_wat;
        infile >> exp_sher;
        infile >> exp_wat;

        Sherlock *sherlock = new Sherlock(0, "RL", Position(1, 3), map, hp_sher, exp_sher);
        cout << sherlock->str() << " HP: " << hp_sher << " EXP: " << exp_sher << endl;
        Watson *watson = new Watson(1, "UD", Position(2, 1), map, hp_wat, exp_wat);
        cout << watson->str() << " HP: " << hp_wat << " EXP: " << exp_wat << endl;

        BaseBag *sher_bag = new SherlockBag(sherlock);
        cout << sher_bag->str() << endl;
        BaseBag *wat_bag = new WatsonBag(watson);
        cout << wat_bag->str() << endl;
        int numline = 3;
        string line;

        while (getline(infile, line))
        {
            numline++;
            istringstream iss(line);
            string command;
            iss >> command;

            if (command == "INSERT")
            {
                string input;
                iss >> input;
                cout << "LINE " << numline << ": * Insert " << input << " into bag" << endl;
                BaseItem *tempitem = stringtoItem(input);
                items.push_back(tempitem);
                sher_bag->insert(tempitem);
                wat_bag->insert(tempitem);
                cout << "SherlockBag: " << sher_bag->str() << endl;
                cout << "WatsonBag " << wat_bag->str() << endl;
            }
            else if (command == "GET")
            {
                string input;
                iss >> input;
                cout << "LINE " << numline << ": * Get " << input << " from bag" << endl;
                if (input.empty())
                {
                    sher_bag->get();
                    wat_bag->get();
                }
                else
                {
                    sher_bag->get(stringtoItemType(input));
                    wat_bag->get(stringtoItemType(input));
                }
                cout << "SherlockBag: " << sher_bag->str() << endl;
                cout << "WatsonBag " << wat_bag->str() << endl;
            }
        }
        infile.close();
        cout << "End." << endl;

        delete sherlock;
        delete watson;
        delete sher_bag;
        delete wat_bag;
        delete map;
        for (int i = 0; i < items.size(); i++)
        {
            if (items[i] != nullptr)
                delete items[i];
        }
    }
};

int main(int argc, const char *argv[])
{
    // TestStudyInPink::satc_01();
    // TestStudyInPink::satc_02();
    // TestStudyInPink::satc_03();
    // TestStudyInPink::satc_04();
    TestStudyInPink::satc_05("C:\\Users\\Nem\\VNU-HCMUT\\intial\\sa_tc_05_config");
    return 0;
}