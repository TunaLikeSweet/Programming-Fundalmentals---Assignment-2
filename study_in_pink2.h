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
class WatsonBag;
class SherlockBag;
class Character;
class Sherlock;
class Watson;
class Criminal;
class RobotS;
class RobotW;
class RobotSW;
class RobotC;

class ArrayMovingObject;
class StudyPinkProgram;
class BaseItem;
class BaseBag;

class TestStudyInPink;
int sumDigits(int &s);
enum ItemType { MAGIC_BOOK, ENERGY_DRINK, FIRST_AID, EXCEMPTION_CARD, PASSING_CARD};
enum ElementType { PATH, WALL, FAKE_WALL };
enum RobotType { C = 0, S, W, SW };

class MapElement
{
    friend class TestStudyInPink;

protected:
    ElementType type;

public:
    explicit MapElement(ElementType in_type);
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
    explicit FakeWall(int in_req_exp);
    int getReqExp() const final;
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

    explicit Position(int r = 0, int c = 0);

    explicit Position(const string &str_pos);

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
    string name;

public:
    MovingObject(int index, const Position pos, Map *map, const string &name = "");
    MovingObject() {}
    Position getCurrentPosition() const { return pos;};
    virtual Position getNextPosition() = 0;
    virtual void move() = 0;
    string getName() const { return this->name; }
    virtual string str() const = 0;
    virtual ~MovingObject() {};
};

class Character : public MovingObject
{
    friend class TestStudyInPink;

protected:
    string moving_rule;
    int hp;
    int exp;
    Position prev = Position(-1, -1);

public:
    Character(int index, const Position pos, Map *map, const string &name = "");
    Character(int index, const string& moving_rule, const Position pos, Map * map, int init_hp, int init_exp, const string & name="");
    Character() {}
    virtual Position getNextPosition() = 0;
    Position getPrevPosition() const;
    int getEXP() const { return exp; }
    int getHP() const { return hp; }
    void setHP(int init_hp) { hp = min(500, max(0, init_hp)); }
    void setEXP(int init_exp) { exp = min(900, max(0, init_exp)); }
    void move() override;
};

class Sherlock : public Character
{
    friend class TestStudyInPink;

private:
    // TODO
    string moving_rule;
    int hp;
    int exp;
    int steps = 0; // number of steps that Sherlock has moved
    SherlockBag *sherlockBag;

public:
    Sherlock(int index, const string &moving_rule, const Position &init_pos, Map *map, int init_hp, int init_exp);
    Sherlock() {}
    Position getNextPosition() override;
    Position setPositionTo(const Position &newPos);
    SherlockBag *getBag() { return sherlockBag; }
    // void move() override;
    string str() const override;
    // ...
    ~Sherlock() {}
};

class Watson /* TODO */ : public Character
{
    friend class TestStudyInPink;

private:
    // TODO
    string moving_rule;
    int hp;
    int exp;
    int steps = 0; // number of steps that Watson has moved
    WatsonBag *watsonBag;

public:
    Watson(int index, const string &moving_rule, const Position &init_pos, Map *map, int init_hp, int init_exp);
    Watson() {}
    Position getNextPosition() override;
    WatsonBag *getBag() { return watsonBag; }
    // void move() override;
    string str() const override;
    // ...
    ~Watson() {}
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

// Robot, BaseItem, BaseBag,...
class Robot : public MovingObject
{
    friend class TestStudyInPink;

protected:
    RobotType robot_type;
    BaseItem *item;

public:
    Robot(int index, const Position &pos, Map *map, RobotType robot_type, const string &robotName);
    Robot() {}
    void createItem();
    virtual void move() = 0;
    BaseItem *getItem() const { return item; }
    SherlockBag *sherlockBag;
    WatsonBag *watsonBag;
    virtual int getDistance() const = 0;
    virtual string str() const = 0;
    virtual ~Robot();
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
    RobotC() {}
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
    RobotS() {}
    Position getNextPosition() override;
    void move() override;
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
    RobotW() {}
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
    RobotSW(int index, const Position &pos, Map *map, Criminal *criminal, Sherlock *sherlock, Watson *watson) : Robot(index, pos, map, SW, "RobotSW"), criminal(criminal), sherlock(sherlock), watson(watson) {}
    RobotSW() {}
    Position getNextPosition() override;
    void move() override;
    int getDistance() const override;
    string str() const override;
};
// Item
class BaseItem
{
    friend class TestStudyInPink;

protected:
    ItemType item_type;
    Character *obj;
    Robot *robot;

public:
    BaseItem(ItemType item_type) : item_type(item_type) {}
    BaseItem() {}
    virtual bool canUse(Character *obj, Robot *robot) = 0;
    string getType() const;
    ItemType getItemType() const { return item_type; }
    virtual void use(Character *obj, Robot *robot) = 0;
    virtual ~BaseItem() = default;
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
public:
    string challenge;

public:
    PassingCard(const string &challenge) : BaseItem(PASSING_CARD), challenge(challenge) {}
    bool canUse(Character *obj, Robot *robot) override;
    void use(Character *obj, Robot *robot) override;
};

class BaseBag
{
    friend class TestStudyInPink;

protected:
    class Node
    {
    public:
        BaseItem *item;
        Node *next;
        Node(BaseItem *item, Node *next = nullptr) : item(item), next(next) {}
    };
    int size;
    int capacity;
    Node *head;
    Character *obj;
    Robot *robot;

public:
    BaseBag(Character *obj, int capacity) : size(0), capacity(capacity), head(nullptr), obj(obj) {}
    virtual bool insert(BaseItem *item) = 0;
    virtual BaseItem *get();
    virtual BaseItem *get(ItemType itemType);
    void SwapItem(BaseBag &otherCharacter, ItemType itemType);
    string str() const;
    virtual ~BaseBag() {}
};

class SherlockBag : public BaseBag
{
    friend class TestStudyInPink;

private:
    Sherlock *sherlock;

public:
    SherlockBag(Sherlock *Char) : BaseBag(Char, 13), sherlock(Char) {}
    bool insert(BaseItem *item) override;
    ~SherlockBag() = default;
};

class WatsonBag : public BaseBag
{
private:
    Watson *watson;
    friend class TestStudyInPink;

public:
    WatsonBag(Watson *Char) : BaseBag(Char, 15), watson(Char) {}
    bool insert(BaseItem *item) override;
    ~WatsonBag() = default;
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

