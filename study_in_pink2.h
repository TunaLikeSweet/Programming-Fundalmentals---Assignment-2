/*
 * Ho Chi Minh City University of Technology
 * Faculty of Computer Science and Engineering
 * Initial code for Assignment 1
 * Programming Fundamentals Spring 2023
 * Author: Vu Van Tien
 * Date: 02.02.2023
 */

// The library here is concretely set, students are not allowed to include any other libraries.
#ifndef _H_STUDY_IN_PINK_2_H_
#define _H_STUDY_IN_PINK_2_H_

#include "main.h"

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

// Forward declaration
class MovingObject;
class Position;
class Configuration;
class Map;
class Character;
class Criminal;
class RobotS;
class RobotW;
class RobotSW;
class RobotC;

class ArrayMovingObject;
class StudyPinkProgram;
class BaseItem;
class BaseBag;
class SherlockBag;
class WatsonBag;

class TestStudyInPink;

enum ItemType { MAGIC_BOOK, ENERGY_DRINK, FIRST_AID, EXCEMPTION_CARD, PASSING_CARD };
enum ElementType{ PATH, WALL, FAKE_WALL };
enum RobotType { C = 0, S, W, SW };

class MapElement
{
    friend class TestStudyInPink;

protected:
    ElementType type;

public:
    MapElement(ElementType in_type);
    virtual ElementType getType() const;
    virtual int getReqExp() const { return 0; }
    virtual ~MapElement();
};

class Path : public MapElement
{
    friend class TestStudyInPink;
public:
    Path();
};

class Wall : public MapElement
{   
    friend class TestStudyInPink;
public:
    Wall();
};

class FakeWall : public MapElement
{
    friend class TestStudyInPink;
private:
    int req_exp;

public:
    FakeWall(int in_req_exp);
    int getReqExp() const;
};

class Map
{
    friend class TestStudyInPink;
    friend class Watson;
private:
    int num_rows, num_cols;
    MapElement ***map;

public:
    Map(int num_rows, int num_cols, int num_walls, Position *array_walls, int num_fake_walls, Position *array_fake_walls);
    bool isValid(const Position &pos, MovingObject *mv_obj) const;
    bool isFakeWall(const Position &pos) const;
    bool isWall(const Position &pos) const;
    ~Map();
};

class Position
{
    friend class TestStudyInPink;
private:
    int r, c;

public:
    static const Position npos;

    Position(int r = 0, int c = 0);

    Position(const string &str_pos);

    int getRow() const;
    int getCol() const;
    void setRow(int r);
    void setCol(int c);

    string str() const;

    bool isEqual(int in_r, int in_c) const;
    bool isEqual(const Position &pos) const;
};

class MovingObject
{
    friend class TestStudyInPink;

protected:
    int index;
    Position pos;
    Map *map;
    const string &name;

public:
    MovingObject(int index, const Position pos, Map *map, const string &name = " ");
    Position getCurrentPosition() const;
    virtual Position getNextPosition() = 0;
    virtual void move() = 0;
    string getName() { return this->name; } // Thật sự có vấn đề về alloc với method này?
    virtual string str() const = 0;
    virtual ~MovingObject();
};

class Character : public MovingObject
{
    friend class TestStudyInPink;

protected:
    string moving_rule;
    int init_hp;
    int init_exp;
    Position prev;

public:
    Character(int index, const Position pos, Map *map, const string &name = "");
    virtual Position getNextPosition() = 0;
    Position getPrevPosition() const;
    virtual int getEXP() const = 0;
    virtual int getHP() const = 0;
    void move() override;
    virtual void setHP(int init_hp) = 0;
    virtual void setEXP(int init_exp) = 0; 
};

class Sherlock : public Character
{
    friend class TestStudyInPink;

private:
    // TODO
    string moving_rule;
    int init_hp;
    int init_exp;
    int steps = 0; // number of steps that Sherlock has moved
    SherlockBag *sherlockBag;

public:
    Sherlock(int index, const string &moving_rule, const Position &init_pos, Map *map, int init_hp, int init_exp);
    Position getNextPosition() override;
    int getEXP() const override { return init_exp; }
    int getHP() const override { return init_hp; }
    void setHP(int hp) override { this->init_hp = hp; }
    void setEXP(int exp) override { this->init_exp = exp;}
    Position setPosition(Position newpos) { return pos = newpos;}
    SherlockBag *getBag() const { return sherlockBag; }
//    string getName() const override { return "Sherlock"; }
    // void move() override;
    string str() const override;
    // ...
};

class Watson /* TODO */ : public Character
{
    friend class TestStudyInPink;
    
private:
    // TODO
    string moving_rule;
    int init_hp;
    int init_exp;
    int steps = 0; // number of steps that Watson has moved
    WatsonBag *watsonBag;

public:
    Watson(int index, const string &moving_rule, const Position &init_pos, Map *map, int init_hp, int init_exp);
    Position getNextPosition() override;
    // void move() override;
    int getEXP() const override { return init_exp; }
    int getHP() const override { return init_hp; }
    void setHP(int init_hp) override { this->init_hp = init_hp; }
    void setEXP(int init_exp) override { this->init_exp = init_exp;}
    WatsonBag *getBag() const { return watsonBag; }
//    string getName() const override { return "Watson"; }
    string str() const override;
    // ...
};

class Criminal : public Character
{
    friend class TestStudyInPink;

private:
    // TODO
    Sherlock *sherlock;
    Watson *watson;

public:
    int steps = 0; // number of steps that the criminal has moved
    Criminal(int index, const Position &init_pos, Map *map, Sherlock *sherlock, Watson *watson);
    Position getNextPosition() override;
    // void move() override;
//    string getName() const override { return "Criminal"; }
    int getEXP() const override { return 0; }
    int getHP() const override { return 0; }
    void setHP(int init_hp) override {}
    void setEXP(int init_exp) override {}
    int distanceToSherlock() const;
    int distanceToWatson() const;
    string str() const override;
    // ...
};

class ArrayMovingObject
{
    friend class TestStudyInPink;

private:
    // TODO
    MovingObject **arr_mv_objs;
    int count;
    int capacity;

public:
    ArrayMovingObject(int capacity);
    bool isFull() const;
    bool add(MovingObject *mv_obj);
    MovingObject *get(int index) const;
    int size() const; // return current number of elements in the array
    string str() const;
    ~ArrayMovingObject();
};

class Configuration
{
    friend class TestStudyInPink;
public:
    // TODO
    int map_num_rows, map_num_cols;
    int max_num_moving_objects;
    int num_walls;
    Position *arr_walls;
    int num_fake_walls;
    Position *arr_fake_walls;
    string sherlock_moving_rule;
    Position sherlock_init_pos;
    int sherlock_init_hp;
    int sherlock_init_exp;
    string watson_moving_rule;
    Position watson_init_pos;
    int watson_init_hp;
    int watson_init_exp;
    Position criminal_init_pos;
    int num_steps;

public:
    Configuration(const string &filepath);
    string str() const;
    ~Configuration();
};

//Robot, BaseItem, BaseBag,...

class Robot : public MovingObject
{
    friend class TestStudyInPink;
protected:
    RobotType robot_type;
    BaseItem *item;
    string challenge;

public:
    Robot(int index, const Position &pos, Map *map, RobotType robot_type, const string &name = "");
    virtual void move() = 0;
    BaseItem *getItem() const { return item; }
    virtual int getDistance() const = 0;
    virtual string str() const = 0;
    string getChallenge() const { return challenge; }
};

// Class RobotC
class RobotC : public Robot
{
    friend class TestStudyInPink;
private:
    Criminal *criminal;
    Sherlock *sherlock;
    Watson *watson;

public:
    RobotC(int index, const Position &pos, Map *map, Criminal *criminal) : Robot(index, pos, map, C, "RobotC"), criminal(criminal) {}
    Position getNextPosition() override;
    void move() override;
    int toSherlock() const;
    int toWatson() const;
    int getDistance() const override;
    string str() const override;
};

// Class RobotS
class RobotS : public Robot
{
    friend class TestStudyInPink;
private:
    Criminal *criminal;
    Sherlock *sherlock;

public:
    RobotS(int index, const Position &pos, Map *map, Criminal *criminal, Sherlock *sherlock) : Robot(index, pos, map, S, "RobotS"), criminal(criminal), sherlock(sherlock) {}
    Position getNextPosition() override;
    void move() override;
    string getRobotName() const { return "RobotS"; }
    int getDistance() const override;
    string str() const override;
};

// Class RobotW
class RobotW : public Robot
{
    friend class TestStudyInPink;
private:
    Criminal *criminal;
    Watson *watson;

public:
    RobotW(int index, const Position &pos, Map *map, Criminal *criminal, Watson *watson) : Robot(index, pos, map, W, "RobotW"), criminal(criminal), watson(watson) {}
    Position getNextPosition() override;
    void move() override;
    int getDistance() const override;
    string str() const override;
};

// Class RobotSW
class RobotSW : public Robot
{
    friend class TestStudyInPink;
private:
    Criminal *criminal;
    Sherlock *sherlock;
    Watson *watson;

public:
    RobotSW(int index, const Position &pos, Map *map, Criminal *criminal, Sherlock *sherlock, Watson *watson) : Robot(index, pos, map, SW, "RobotSW"), criminal(criminal), watson(watson), sherlock(sherlock) {}
    void move() override;
    int getDistance() const override;
    Position getNextPosition() override;
    string str() const override;
};
// Item
class BaseItem
{
    friend class TestStudyInPink;
protected:
    ItemType item_type;

public:
    BaseItem(ItemType item_type) : item_type(item_type) {}
    virtual bool canUse(Character *obj, Robot *robot) = 0;
    string getType() const;
    ItemType getItemType() const { return item_type; }
    virtual void use(Character *obj, Robot *robot) = 0;
    virtual ~BaseItem() {}
};

class MagicBook : public BaseItem
{
    friend class TestStudyInPink;
public:
    MagicBook() : BaseItem(MAGIC_BOOK){};
    bool canUse(Character *obj, Robot *robot) override;
    void use(Character *obj, Robot *robot) override;
};

class EnergyDrink : public BaseItem
{
    friend class TestStudyInPink;
public:
    EnergyDrink() : BaseItem(ENERGY_DRINK){};
    bool canUse(Character *obj, Robot *robot) override;
    void use(Character *obj, Robot *robot) override;
};
class FirstAid : public BaseItem
{
    friend class TestStudyInPink;
public:
    FirstAid() : BaseItem(FIRST_AID){};
    bool canUse(Character *obj, Robot *robot) override;
    void use(Character *obj, Robot *robot) override;
};
class ExcemptionCard : public BaseItem
{
    friend class TestStudyInPink;
public:
    ExcemptionCard() : BaseItem(EXCEMPTION_CARD){};
    bool canUse(Character *obj, Robot *robot) override;
    void use(Character *obj, Robot *robot) override;
};

class PassingCard : public BaseItem
{
    friend class TestStudyInPink;
private:
    string challenge;

public:
    PassingCard(const string &challenge) : BaseItem(PASSING_CARD) {}
   bool canUse(Character *obj, Robot *robot) override;
   void use(Character *obj, Robot *robot) override;
};

class BaseBag
{
    friend class TestStudyInPink;
protected:
    struct Node
    {
        BaseItem *item;
        Node *next;
    };
    Node *head = nullptr;
    int count = 0;

public:
    BaseBag(Character *obj) : head(nullptr), count(0) {};
    virtual bool insert(BaseItem *item) = 0;
    virtual BaseItem *get() = 0;
    virtual BaseItem *get(ItemType itemType) = 0;

    void SwapItem(BaseBag &otherCharacter, ItemType itemType);
    string str() const;
    ~BaseBag() {}
};

class SherlockBag : public BaseBag
{
    friend class TestStudyInPink;
private:
    Character *obj;
    Robot *robot;
public:
    SherlockBag(Sherlock* sherlock) : BaseBag(sherlock) {};
    bool insert(BaseItem *item) override;
    BaseItem *get() override;
    BaseItem *get(ItemType itemType) override;
};

class WatsonBag : public BaseBag
{
    friend class TestStudyInPink;
private:
    Character *obj;
    Robot *robot;
public:
    WatsonBag(Watson *watson) : BaseBag(watson) {};
    bool insert(BaseItem *item) override;
    BaseItem *get() override;
    BaseItem *get(ItemType itemType) override;
};

class StudyPinkProgram
{
    friend class Configuration;
    friend class TestStudyInPink;
private:
    // Sample attributes
    Configuration *config;

    Sherlock *sherlock;
    Watson *watson;
    SherlockBag *sherlockBag;
    WatsonBag *watsonBag;
    Criminal *criminal;

    Map *map;
     ArrayMovingObject *arr_mv_objs;
    int num_steps;

    RobotC *robotC;
    RobotS *robotS;
    RobotW *robotW;
    RobotSW *robotSW;

    public:
        StudyPinkProgram(const string &config_file_path);

    bool isStop() const;

    void printResult() const
    {
        if (sherlock->getCurrentPosition().isEqual(criminal->getCurrentPosition()))
        {
            cout << "Sherlock caught the criminal" << endl;
        }
        else if (watson->getCurrentPosition().isEqual(criminal->getCurrentPosition()))
        {
            cout << "Watson caught the criminal" << endl;
        }
        else
        {
            cout << "The criminal escaped" << endl;
        }
    }

    void printStep(int si) const
    {
        cout << "Step: " << setw(4) << setfill('0') << si
             << "--"
             << sherlock->str() << "--|--" << watson->str() << "--|--" << criminal->str() << endl;
    }

    void run(bool verbose);

    ~StudyPinkProgram();
};


////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////
#endif /* _H_STUDY_IN_PINK_2_H_ */