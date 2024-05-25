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
BaseItem *stringtoItem(string input)
{
    if (input == "MAGIC_BOOK")
        return new MagicBook();
    else if (input == "ENERGY_DRINK")
        return new EnergyDrink();
    else if (input == "FIRST_AID")
        return new FirstAid;
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
void g_satc_02()
{ // global
    cout << "----- Sample Testcase 02 -----" << endl;
    Configuration *config = new Configuration("sa_tc_02_config");
    cout << config->str() << endl;
    delete config;
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

        delete sherlock;
        delete watson;
        delete criminal;
        delete map;
        delete robotC;
    }
    static void tc_1293()
    {
        cout << "----- Testcase 293 -----" << endl;
        int num_walls = 4;
        Position arr_walls[] = {Position(1, 2), Position(2, 3), Position(3, 4), Position(4, 5)};
        int num_fake_walls = 2;
        Position arr_fake_walls[] = {Position(2, 0), Position(4, 0)};

        Map *map = new Map(10, 10, num_walls, arr_walls, num_fake_walls, arr_fake_walls);

        Sherlock *sherlock = new Sherlock(1, "RUU", Position(1, 3), map, 150, 450);

        Watson *watson = new Watson(2, "LU", Position(2, 1), map, 274, 350);

        Criminal *criminal = new Criminal(0, Position(7, 9), map, sherlock, watson);

        RobotC *robotC = new RobotC(3, Position(9, 5), map, criminal);

        PassingCard *passingCard = static_cast<PassingCard *>(robotC->item);
        if (passingCard == NULL)
        {
            cout << "Item is not PassingCard" << endl;
        }
        else
        {
            cout << passingCard->challenge << endl;
        }

        delete map;
        delete sherlock;
        delete watson;
        delete criminal;
        delete robotC;
    }
    static void satc_05(string input_file)
    {
        int num_walls = 3;
        Position arr_walls[] = {Position(1, 2), Position(2, 3), Position(3, 4)};
        int num_fake_walls = 1;
        Position arr_fake_walls[] = {Position(2, 0)};
        Map *map = new Map(10, 10, num_walls, arr_walls, num_fake_walls, arr_fake_walls);

        ifstream infile(input_file); // Mở file

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
    static void tc_1205()
    {
        cout << "----- Testcase 205 -----" << endl;
        int num_walls = 5;
        Position arr_walls[] = {Position(1, 2), Position(2, 3), Position(3, 4), Position(3, 2), Position(4, 3)};
        int num_fake_walls = 1;
        Position arr_fake_walls[] = {Position(2, 0)};

        Map *map = new Map(10, 10, num_walls, arr_walls, num_fake_walls, arr_fake_walls);

        Sherlock *sherlock = new Sherlock(1, "RUU", Position(1, 3), map, 250, 450);
        Watson *watson = new Watson(2, "LU", Position(2, 1), map, 300, 350);
        Criminal *criminal = new Criminal(0, Position(7, 9), map, sherlock, watson);
        RobotS *robotS = new RobotS(3, Position(3, 3), map, criminal, sherlock);
        int distance_old = robotS->getDistance();

        Position new_position = robotS->getNextPosition();
        RobotS *robotS_new = new RobotS(4, new_position, map, criminal, sherlock);
        int distance_new = robotS->getDistance();

        cout << "Current: " << robotS->pos.getRow() << " " << robotS->pos.getCol() << endl;
        cout << "Next position: " << robotS_new->pos.getRow() << " " << robotS_new->pos.getCol() << endl;

        if (distance_old - distance_new >= 0)
            cout << "Can get close";
        else
            cout << "Can not get close";

        delete robotS;
        delete robotS_new;
        delete sherlock;
        delete watson;
        delete criminal;
        delete map;
    }
    static void tc_1300()
    {
        cout << "----- Testcase 300 -----" << endl;
        int num_walls = 4;
        Position arr_walls[] = {Position(1, 2), Position(2, 3), Position(3, 4), Position(4, 5)};
        int num_fake_walls = 2;
        Position arr_fake_walls[] = {Position(2, 0), Position(4, 0)};

        Map *map = new Map(10, 10, num_walls, arr_walls, num_fake_walls, arr_fake_walls);

        Sherlock *sherlock = new Sherlock(1, "RUU", Position(1, 3), map, 80, 450);

        BaseBag *sherlockBag = new SherlockBag(sherlock);

        for (int i = 0; i < 14; i++)
        {
            BaseItem *firstAid = new FirstAid();
            sherlockBag->insert(firstAid);
        }

        cout << sherlockBag->str() << endl;

        delete map;
        delete sherlock;
        delete sherlockBag;
    }

    static void tc_1279()
    {
        cout << "----- Testcase 279 -----" << endl;
        int num_walls = 4;
        Position arr_walls[] = {Position(1, 2), Position(2, 3), Position(3, 4), Position(4, 5)};
        int num_fake_walls = 2;
        Position arr_fake_walls[] = {Position(2, 0), Position(4, 0)};

        Map *map = new Map(10, 10, num_walls, arr_walls, num_fake_walls, arr_fake_walls);

        Sherlock *sherlock = new Sherlock(1, "RUU", Position(1, 3), map, 150, 450);

        Watson *watson = new Watson(2, "LU", Position(2, 1), map, 300, 350);

        Criminal *criminal = new Criminal(0, Position(7, 9), map, sherlock, watson);

        RobotC *robotC = new RobotC(3, Position(7, 9), map, criminal);

        BaseItem *excemptionCard = new ExcemptionCard();

        BaseBag *sherlockBag = new SherlockBag(sherlock);

        sherlockBag->insert(excemptionCard);

        cout << excemptionCard->canUse(sherlock, robotC);

        delete map;
        delete sherlock;
        delete watson;
        delete criminal;
        delete robotC;
        delete sherlockBag;
        delete excemptionCard;
    }
    static void tc_1280()
    {
        cout << "----- Testcase 280 -----" << endl;
        int num_walls = 4;
        Position arr_walls[] = {Position(1, 2), Position(2, 3), Position(3, 4), Position(4, 5)};
        int num_fake_walls = 2;
        Position arr_fake_walls[] = {Position(2, 0), Position(4, 0)};

        Map *map = new Map(10, 10, num_walls, arr_walls, num_fake_walls, arr_fake_walls);

        Sherlock *sherlock = new Sherlock(1, "RUU", Position(1, 3), map, 251, 450);

        Watson *watson = new Watson(2, "LU", Position(2, 1), map, 300, 350);

        Criminal *criminal = new Criminal(0, Position(7, 9), map, sherlock, watson);

        RobotC *robotC = new RobotC(3, Position(7, 9), map, criminal);

        BaseItem *excemptionCard = new ExcemptionCard();

        BaseBag *sherlockBag = new SherlockBag(sherlock);

        sherlockBag->insert(excemptionCard);

        cout << excemptionCard->canUse(sherlock, robotC);

        delete map;
        delete sherlock;
        delete watson;
        delete criminal;
        delete robotC;
        delete sherlockBag;
        delete excemptionCard;
    }
    static void tc_1329()
    {
        cout << "----- Testcase 329 -----" << endl;
        int num_walls = 4;
        Position arr_walls[] = {Position(1, 2), Position(2, 3), Position(3, 4), Position(4, 5)};
        int num_fake_walls = 2;
        Position arr_fake_walls[] = {Position(2, 0), Position(4, 0)};

        Map *map = new Map(10, 10, num_walls, arr_walls, num_fake_walls, arr_fake_walls);

        Watson *watson = new Watson(1, "RUU", Position(1, 3), map, 70, 450);

        BaseItem *excemptionCard1 = new ExcemptionCard();
        BaseItem *excemptionCard2 = new ExcemptionCard();

        BaseBag *watsonBag = new WatsonBag(watson);

        watsonBag->insert(excemptionCard1);
        watsonBag->insert(excemptionCard2);

        watsonBag->get();

        cout << watsonBag->str() << endl;

        delete map;
        delete watson;
        delete excemptionCard1;
        delete excemptionCard2;
        delete watsonBag;
    }
    static void tc_1318()
    {
        cout << "----- Testcase 318 -----" << endl;
        int num_walls = 4;
        Position arr_walls[] = {Position(1, 2), Position(2, 3), Position(3, 4), Position(4, 5)};
        int num_fake_walls = 2;
        Position arr_fake_walls[] = {Position(2, 0), Position(4, 0)};

        Map *map = new Map(10, 10, num_walls, arr_walls, num_fake_walls, arr_fake_walls);

        Sherlock *sherlock = new Sherlock(1, "RUU", Position(1, 3), map, 80, 450);

        BaseItem *firstAid1 = new FirstAid();
        BaseItem *firstAid2 = new FirstAid();
        BaseItem *magicBook = new MagicBook();

        BaseBag *sherlockBag = new SherlockBag(sherlock);

        sherlockBag->insert(firstAid1);
        sherlockBag->insert(firstAid2);
        sherlockBag->insert(magicBook);
        cout << sherlockBag->str() << endl;
        sherlockBag->get();

        cout << sherlockBag->str() << endl;

        delete map;
        delete sherlock;
        delete firstAid1;
        delete firstAid2;
        delete magicBook;
        delete sherlockBag;
    }
    static void tc_1316()
    {
        cout << "----- Testcase 316 -----" << endl;
        int num_walls = 4;
        Position arr_walls[] = {Position(1, 2), Position(2, 3), Position(3, 4), Position(4, 5)};
        int num_fake_walls = 2;
        Position arr_fake_walls[] = {Position(2, 0), Position(4, 0)};

        Map *map = new Map(10, 10, num_walls, arr_walls, num_fake_walls, arr_fake_walls);

        Sherlock *sherlock = new Sherlock(1, "RUU", Position(1, 3), map, 150, 450);

        BaseItem *passingCard1 = new PassingCard("RobotS");
        BaseItem *passingCard2 = new PassingCard("RobotC");

        BaseBag *sherlockBag = new SherlockBag(sherlock);

        BaseItem *magicBook = new MagicBook();

        sherlockBag->insert(magicBook);
        sherlockBag->insert(passingCard1);
        sherlockBag->insert(passingCard2);

        sherlockBag->get();

        cout << sherlockBag->str() << endl;

        delete map;
        delete sherlock;
        delete magicBook;
        delete passingCard1;
        delete passingCard2;
        delete sherlockBag;
    }
    static void tc_1303()
    {
        cout << "----- Testcase 303 -----" << endl;
        int num_walls = 4;
        Position arr_walls[] = {Position(1, 2), Position(2, 3), Position(3, 4), Position(4, 5)};
        int num_fake_walls = 2;
        Position arr_fake_walls[] = {Position(2, 0), Position(4, 0)};

        Map *map = new Map(10, 10, num_walls, arr_walls, num_fake_walls, arr_fake_walls);

        Sherlock *sherlock = new Sherlock(1, "RUU", Position(1, 3), map, 150, 450);

        BaseItem *passingCard1 = new PassingCard("RobotSW");
        BaseItem *passingCard2 = new PassingCard("all");

        BaseBag *sherlockBag = new SherlockBag(sherlock);

        sherlockBag->insert(passingCard1);
        sherlockBag->insert(passingCard2);

        sherlockBag->get();

        cout << sherlockBag->str() << endl; // str

        delete map;
        delete sherlock;
        delete passingCard1;
        delete passingCard2;
        delete sherlockBag;
    }
    static void tc_1270()
    {
        cout << "----- Testcase 270 -----" << endl;
        int num_walls = 4;
        Position arr_walls[] = {Position(1, 2), Position(2, 3), Position(3, 4), Position(4, 5)};
        int num_fake_walls = 2;
        Position arr_fake_walls[] = {Position(2, 0), Position(4, 0)};

        Map *map = new Map(10, 10, num_walls, arr_walls, num_fake_walls, arr_fake_walls);

        Sherlock *sherlock = new Sherlock(1, "RUU", Position(1, 3), map, 250, 450);

        Watson *watson = new Watson(2, "LU", Position(2, 1), map, 300, 350);

        Criminal *criminal = new Criminal(0, Position(7, 9), map, sherlock, watson);

        BaseItem *firstAid = new FirstAid();

        cout << firstAid->canUse(criminal, NULL) << endl;

        delete map;
        delete sherlock;
        delete watson;
        delete criminal;
        delete firstAid;
    }
    static void tc_1317()
    {
        cout << "----- Testcase 317 -----" << endl;
        int num_walls = 4;
        Position arr_walls[] = {Position(1, 2), Position(2, 3), Position(3, 4), Position(4, 5)};
        int num_fake_walls = 2;
        Position arr_fake_walls[] = {Position(2, 0), Position(4, 0)};

        Map *map = new Map(10, 10, num_walls, arr_walls, num_fake_walls, arr_fake_walls);

        Sherlock *sherlock = new Sherlock(1, "RUU", Position(1, 3), map, 120, 300);

        BaseItem *passingCard = new PassingCard("RobotW");
        BaseItem *firstAid = new FirstAid();
        BaseItem *magicBook = new MagicBook();

        BaseBag *sherlockBag = new SherlockBag(sherlock);

        sherlockBag->insert(passingCard);
        sherlockBag->insert(firstAid);
        sherlockBag->insert(magicBook);

        sherlockBag->get();

        cout << sherlockBag->str() << endl;

        delete map;
        delete sherlock;
        delete magicBook;
        delete passingCard;
        delete firstAid;
        delete sherlockBag;
    }
};
int main(int argc, const char *argv[])
{
    // TestStudyInPink::satc_01();
    // TestStudyInPink::satc_02();
    // TestStudyInPink::satc_03();
    // TestStudyInPink::tc_1293();
    // TestStudyInPink::tc_1205();
    // TestStudyInPink::satc_05(R"(C:\Users\Nem\VNU-HCMUT\Programming Fundalmentals - Assignment 2\sa_tc_05_config)");
    // TestStudyInPink::tc_1300();
    // TestStudyInPink::tc_1279();
    // TestStudyInPink::tc_1280();
    // TestStudyInPink::tc_1329();
    // TestStudyInPink::tc_1318();
    // TestStudyInPink::tc_1316();
    // TestStudyInPink::tc_1303();
    TestStudyInPink::tc_1270();
    TestStudyInPink::tc_1317();
    return 0;
}
