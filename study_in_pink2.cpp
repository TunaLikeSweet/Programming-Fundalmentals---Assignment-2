#include "study_in_pink2.h"

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

int sumDigits(int &num)
{
    while (num >= 10)
    {
        int sum = 0;
        while (num > 0)
        {
            sum += num % 10;
            num /= 10;
        }
        num = sum;
    }
    return num;
}

MapElement::MapElement(ElementType in_type) : type(in_type) {}
ElementType MapElement::getType() const { return type; }
MapElement::~MapElement() = default;

Path::Path() : MapElement(PATH) {}
Wall::Wall() : MapElement(WALL) {}
FakeWall::FakeWall(int req_exp) : MapElement(FAKE_WALL), req_exp(req_exp) {}
int FakeWall::getReqExp() const { return req_exp; }

Map::Map(int num_rows, int num_cols, int num_walls, Position *array_walls, int num_fake_walls, Position *array_fake_walls) : num_rows(num_rows), num_cols(num_cols)
{
    map = new MapElement **[num_rows];
    for (int i = 0; i < num_rows; i++)
    {
        map[i] = new MapElement *[num_cols];
        for (int j = 0; j < num_cols; j++)
            map[i][j] = new Path();
    }
    for (int i = 0; i < num_walls; i++)
    {
        int r = array_walls[i].getRow();
        int c = array_walls[i].getCol();
        delete map[r][c];
        map[r][c] = new Wall();
    }
    for (int i = 0; i < num_fake_walls; i++)
    {
        int r = array_fake_walls[i].getRow();
        int c = array_fake_walls[i].getCol();
        delete map[r][c];
        map[r][c] = new FakeWall(ceilf((r * 257 + c * 139 + 89) % 900 + 1));
    }
}

bool Map::isValid(const Position &pos, MovingObject *mv_obj) const
{
    if (pos.getRow() < 0 || pos.getCol() < 0 || pos.getRow() >= num_rows || pos.getCol() >= num_cols)
        return false;
    ElementType type = map[pos.getRow()][pos.getCol()]->getType();
    if (type == WALL)
        return false;
    else if (type == FAKE_WALL) // Mình sẽ không xét ở đây
    {
        // if (mv_obj->getName() == "Watson")
        // {
        //     if (character->getEXP() > map[pos.getRow()][pos.getCol()]->getReqExp())
        //         return true;
        //     else
        //         return false;
        // }
        return true;
    }
    else if (type == PATH)
        return true;
    else
        return false;
}

bool Map::isFakeWall(const Position &pos) const
{
    return map[pos.getRow()][pos.getCol()]->getType() == FAKE_WALL;
}

bool Map::isWall(const Position &pos) const
{
    return map[pos.getRow()][pos.getCol()]->getType() == WALL;
}

Map::~Map()
{
    for (int i = 0; i < num_rows; i++)
    {
        for (int j = 0; j < num_cols; j++)
            delete map[i][j];
        delete[] map[i];
    }
    delete[] map;
}

Position::Position(int r, int c) : r(r), c(c) {}
int Position::getCol() const { return c; }
int Position::getRow() const { return r; }
void Position::setCol(int col) { this->c = col; }
void Position::setRow(int row) { this->r = row; }

Position::Position(const string &str_pos)
{
    size_t pos = str_pos.find(',');
    r = stoi(str_pos.substr(1, pos - 1));
    c = stoi(str_pos.substr(pos + 1, str_pos.length() - pos - 2));
}

string Position::str() const { return "(" + to_string(r) + "," + to_string(c) + ")"; }

bool Position::isEqual(int in_r, int in_c) const { return r == in_r && c == in_c; }
bool Position::isEqual(const Position &pos) const { return r == pos.r && c == pos.c; }

const Position Position::npos = Position(-1, -1);

MovingObject::MovingObject(int index, const Position pos, Map *map, const string &name) : index(index), pos(pos), map(map), name(name) {}
Character::Character(int index, const Position pos, Map *map, const string &name) : MovingObject(index, pos, map, name) {}
Character::Character(int index, const string &moving_rule, const Position pos, Map *map, int init_hp, int init_exp, const string &name) : MovingObject(index, pos, map, name), moving_rule(moving_rule), hp(init_hp), exp(init_exp) {}
Position Character::getPrevPosition() const { return prev; }

void Character::move()
{
    Position next_pos = this->getNextPosition();
    prev = this->pos;
    if (!next_pos.isEqual(Position::npos) && !map->isWall(next_pos))
        pos = next_pos;
    else
        return;
}

Sherlock::Sherlock(int index, const string &moving_rule, const Position &init_pos, Map *map, int init_hp, int init_exp)
    : Character(index, moving_rule, init_pos, map, init_hp, init_exp, "Sherlock"), hp(init_hp), exp(init_exp), moving_rule(moving_rule) { sherlockBag = new SherlockBag(this); }

Position Sherlock::getNextPosition()
{
    if (hp == 0 || exp == 0)
        return Position::npos;
    char move;
    Position next_pos = pos;
    if (!moving_rule.empty())
    {
        move = moving_rule[steps % moving_rule.length()];
        // Xác định bước tiếp theo di chuyển.
        switch (move)
        {
        case 'U':
            next_pos.setRow(next_pos.getRow() - 1); // Di chuyển lên trên.
            break;
        case 'D':
            next_pos.setRow(next_pos.getRow() + 1); // Di chuyển xuống dưới.
            break;
        case 'L':
            next_pos.setCol(next_pos.getCol() - 1); // Di chuyển sang trái.
            break;
        case 'R':
            next_pos.setCol(next_pos.getCol() + 1); // Di chuyển sang phải.
            break;
        }
        steps = (++steps) % moving_rule.length(); // Cập nhật bước di chuyển.
    }
    else
        return Position::npos;
    if (map->isValid(next_pos, this))
        return Position(next_pos);
    else
        return Position::npos;
}

Position Sherlock::setPositionTo(const Position &newPos)
{
    this->pos = newPos;
    return pos;
}

string Sherlock::str() const
{
    stringstream SherlockStr;
    SherlockStr << "Sherlock[index=" << index << ";pos=" << pos.str() << ";moving_rule=" << moving_rule << "]";
    return SherlockStr.str();
}

Watson::Watson(int index, const string &moving_rule, const Position &init_pos, Map *map, int init_hp, int init_exp)
    : Character(index, moving_rule, init_pos, map, init_hp, init_exp, "Watson"), hp(init_hp), exp(init_exp), moving_rule(moving_rule) { watsonBag = new WatsonBag(this); }

Position Watson::getNextPosition()
{
    if (hp == 0 || exp == 0)
        return Position::npos;
    char move = moving_rule[steps % moving_rule.length()];
    // Xác định bước tiếp theo di chuyển.
    Position next_pos = pos;
    switch (move)
    {
    case 'U':
        next_pos.setRow(next_pos.getRow() - 1); // Di chuyển lên trên.
        break;
    case 'D':
        next_pos.setRow(next_pos.getRow() + 1); // Di chuyển xuống dưới.
        break;
    case 'L':
        next_pos.setCol(next_pos.getCol() - 1); // Di chuyển sang trái.
        break;
    case 'R':
        next_pos.setCol(next_pos.getCol() + 1); // Di chuyển sang phải.
        break;
    }
    steps = (++steps) % moving_rule.length();

    if (map->isValid(next_pos, this))
    {
        if (map->isWall(next_pos))
            // Nếu là Wall, trả về Position::npos
            return Position::npos;
        else if (map->isFakeWall(next_pos) && exp <= map->map[next_pos.getRow()][next_pos.getCol()]->getReqExp())
            // Nếu không đủ EXP để đi qua Fake Wall, trả về Position::npos
            return Position::npos;
        return Position(next_pos);
    }
    else
        return Position::npos;
}

string Watson::str() const
{
    stringstream WatsonStr;
    WatsonStr << "Watson[index=" << index << ";pos=" << pos.str() << ";moving_rule=" << moving_rule << "]";
    return WatsonStr.str();
}

Criminal::Criminal(int index, const Position &init_pos, Map *map, Sherlock *sherlock, Watson *watson)
    : Character(index, init_pos, map, "Criminal"), sherlock(sherlock), watson(watson) {}

Position Criminal::getNextPosition()
{
    Position next_pos = this->getCurrentPosition();
    int maxDistance = -1;
    // Directions: 'U', 'L', 'D', 'R', move to Up, Left, Down, Right base on clock-wise.
    int directions[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
    for (int i = 0; i < 4; i++)
    {
        Position newPos(this->getCurrentPosition().getRow() + directions[i][0], this->getCurrentPosition().getCol() + directions[i][1]);
        if (!this->map->isValid(newPos, this))
            continue;

        int SherlockDist = abs(newPos.getRow() - sherlock->getCurrentPosition().getRow()) + abs(newPos.getCol() - sherlock->getCurrentPosition().getCol());
        int WatsonDist = abs(newPos.getRow() - watson->getCurrentPosition().getRow()) + abs(newPos.getCol() - watson->getCurrentPosition().getCol());
        int CriminalDist = SherlockDist + WatsonDist;
        if (CriminalDist > maxDistance)
        {
            maxDistance = CriminalDist;
            next_pos = newPos;
        }
    }
    steps++;
    return next_pos;
}

int Criminal::distanceToSherlock() const
{
    return abs(pos.getRow() - sherlock->getCurrentPosition().getRow()) + abs(pos.getCol() - sherlock->getCurrentPosition().getCol());
}

int Criminal::distanceToWatson() const
{
    return abs(pos.getRow() - watson->getCurrentPosition().getRow()) + abs(pos.getCol() - watson->getCurrentPosition().getCol());
}

string Criminal::str() const
{
    stringstream CriminalStr;
    CriminalStr << "Criminal[index=" << index << ";pos=" << pos.str() << "]";
    return CriminalStr.str();
}

ArrayMovingObject::ArrayMovingObject(int capacity) : capacity(capacity), count(0)
{
    arr_mv_objs = new MovingObject *[capacity];
}

bool ArrayMovingObject::isFull() const { return count == capacity; }

bool ArrayMovingObject::add(MovingObject *mv_obj)
{
    if (isFull() || mv_obj == nullptr)
        return false;
    else
        arr_mv_objs[count++] = mv_obj;
    return true;
}
int ArrayMovingObject::size() const { return count; }

MovingObject *ArrayMovingObject::get(int index) const
{
    if (index < 0 || index >= count)
        return nullptr;
    return arr_mv_objs[index];
}

string ArrayMovingObject::str() const
{
    stringstream ArrayMovingObjectStr;
    ArrayMovingObjectStr << "ArrayMovingObject[count=" << count << ";capacity=" << capacity << ";";
    for (int i = 0; i < count; i++)
        ArrayMovingObjectStr << arr_mv_objs[i]->str() << ";";
    string convert = string(ArrayMovingObjectStr.str());
    if (!convert.empty())
        convert.pop_back();
    ArrayMovingObjectStr.str("");
    ArrayMovingObjectStr.clear();
    ArrayMovingObjectStr << convert;
    ArrayMovingObjectStr << "]";
    return ArrayMovingObjectStr.str();
}

ArrayMovingObject::~ArrayMovingObject() = default;
//{
// for (int i = 0; i < count; i++)
//     delete arr_mv_objs[i];
// delete[] arr_mv_objs;
//}

Configuration::Configuration(const string &filepath) : map_num_rows(map_num_rows), map_num_cols(map_num_cols), max_num_moving_objects(max_num_moving_objects), num_walls(num_walls), num_fake_walls(num_fake_walls), sherlock_moving_rule(""), sherlock_init_hp(sherlock_init_hp), sherlock_init_exp(sherlock_init_exp), watson_moving_rule(""), watson_init_hp(watson_init_hp), watson_init_exp(watson_init_exp), num_steps(num_steps)
{
    ifstream file(filepath);
    if (!file.is_open())
    {
        cerr << "Cannot open file!\n"; // If error, solution is using the full path of file (ex: "C:\\Users\\Admin\\Desktop\\study_in_pink2\\testcase\\testcase1.txt")
        return;
    }
    else
    {
        string line;
        while (getline(file, line))
        {
            istringstream iss(line);
            string key;
            getline(iss, key, '='); // Read a string until a '=' character is found
            if (key == "MAP_NUM_ROWS")
                iss >> map_num_rows;
            else if (key == "MAP_NUM_COLS")
                iss >> map_num_cols;
            else if (key == "MAX_NUM_MOVING_OBJECTS")
                iss >> max_num_moving_objects;
            else if (key == "ARRAY_WALLS")
            {
                string pos_walls;
                string list_walls;
                iss >> pos_walls;
                pos_walls = pos_walls.substr(1, pos_walls.length() - 2);
                num_walls = 0;
                for (char c : pos_walls)
                    if (c == '(')
                        num_walls++;
                arr_walls = new Position[num_walls];
                for (char c : pos_walls)
                    if (c != ';')
                        list_walls += c;
                string coordinate;
                int j = 0;
                for (int i = 0; i < list_walls.length(); i++)
                {
                    if (list_walls[i] == '(')
                        continue;
                    else if (list_walls[i] == ')')
                    {
                        string x, y;
                        int k = 0;
                        while (coordinate[k] != ',')
                        {
                            x += coordinate[k];
                            k++;
                        }
                        k++; // Bỏ qua dấu phẩy
                        while (k < coordinate.length())
                        {
                            y += coordinate[k];
                            k++;
                        }
                        arr_walls[j] = Position(stoi(x), stoi(y));
                        j++;
                        coordinate = "";
                    }
                    else
                        coordinate += list_walls[i];
                }
            }
            else if (key == "ARRAY_FAKE_WALLS")
            {
                string pos_fake_walls;
                string list_fake_walls;
                iss >> pos_fake_walls;
                pos_fake_walls = pos_fake_walls.substr(1, pos_fake_walls.length() - 2);
                num_fake_walls = 0;
                for (char c : pos_fake_walls)
                    if (c == '(')
                        num_fake_walls++;
                arr_fake_walls = new Position[num_fake_walls];
                for (char c : pos_fake_walls)
                    if (c != ';')
                        list_fake_walls += c;
                string coordinate;
                int j = 0;
                for (int i = 0; i < list_fake_walls.length(); i++)
                {
                    if (list_fake_walls[i] == '(')
                        continue;
                    else if (list_fake_walls[i] == ')')
                    {
                        string x, y;
                        int k = 0;
                        while (coordinate[k] != ',')
                        {
                            x += coordinate[k];
                            k++;
                        }
                        k++;
                        while (k < coordinate.length())
                        {
                            y += coordinate[k];
                            k++;
                        }
                        arr_fake_walls[j] = Position(stoi(x), stoi(y));
                        j++;
                        coordinate = "";
                    }
                    else
                        coordinate += list_fake_walls[i];
                }
            }
            else if (key == "SHERLOCK_MOVING_RULE")
                iss >> sherlock_moving_rule;
            else if (key == "SHERLOCK_INIT_POS")
            {
                string pos;
                iss >> pos;
                sherlock_init_pos = Position(pos);
            }
            else if (key == "SHERLOCK_INIT_HP")
                iss >> sherlock_init_hp;
            else if (key == "SHERLOCK_INIT_EXP")
                iss >> sherlock_init_exp;
            else if (key == "WATSON_MOVING_RULE")
                iss >> watson_moving_rule;
            else if (key == "WATSON_INIT_POS")
            {
                string pos;
                iss >> pos;
                watson_init_pos = Position(pos);
            }
            else if (key == "WATSON_INIT_HP")
                iss >> watson_init_hp;
            else if (key == "WATSON_INIT_EXP")
                iss >> watson_init_exp;
            else if (key == "CRIMINAL_INIT_POS")
            {
                string pos;
                iss >> pos;
                criminal_init_pos = Position(pos);
            }
            else if (key == "NUM_STEPS")
                iss >> num_steps;
        }
    }
    file.close();
}

string Configuration::str() const
{
    stringstream ConfigurationStr;
    stringstream ss1;
    stringstream ss2;
    ConfigurationStr << "Configuration[\n"
                     << "MAP_NUM_ROWS=" << map_num_rows << '\n'
                     << "MAP_NUM_COLS=" << map_num_cols << '\n'
                     << "MAX_NUM_MOVING_OBJECTS=" << max_num_moving_objects << '\n'
                     << "NUM_WALLS=" << num_walls << '\n'
                     << "ARRAY_WALLS=[";
    for (int i = 0; i < num_walls; i++)
        ss1 << arr_walls[i].str() << ";";
    string convert1 = string(ss1.str());
    if (!convert1.empty())
        convert1.pop_back();
    ConfigurationStr << convert1 << "]";
    ConfigurationStr << '\n'
                     << "NUM_FAKE_WALLS=" << num_fake_walls << '\n'
                     << "ARRAY_FAKE_WALLS=[";
    for (int i = 0; i < num_fake_walls; i++)
        ss2 << arr_fake_walls[i].str() << ";";
    string convert2 = string(ss2.str());
    if (!convert2.empty())
        convert2.pop_back();
    ConfigurationStr << convert2 << "]";
    ConfigurationStr << '\n'
                     << "SHERLOCK_MOVING_RULE=" << sherlock_moving_rule << '\n'
                     << "SHERLOCK_INIT_POS=" << sherlock_init_pos.str() << '\n'
                     << "SHERLOCK_INIT_HP=" << sherlock_init_hp << '\n'
                     << "SHERLOCK_INIT_EXP=" << sherlock_init_exp << '\n'
                     << "WATSON_MOVING_RULE=" << watson_moving_rule << '\n'
                     << "WATSON_INIT_POS=" << watson_init_pos.str() << '\n'
                     << "WATSON_INIT_HP=" << watson_init_hp << '\n'
                     << "WATSON_INIT_EXP=" << watson_init_exp << '\n'
                     << "CRIMINAL_INIT_POS=" << criminal_init_pos.str() << '\n'
                     << "NUM_STEPS=" << num_steps << '\n'
                     << "]";
    return ConfigurationStr.str();
}

Configuration::~Configuration()
{
    delete[] arr_walls;
    delete[] arr_fake_walls;
}

Robot::Robot(int index, const Position &pos, Map *map, RobotType robot_type, const string &name)
    : MovingObject(index, pos, map, name), robot_type(robot_type), item(nullptr) { Robot::createItem(); }

void Robot::createItem()
{
    pos = this->getCurrentPosition();
    int i = pos.getRow();
    int j = pos.getCol();
    int p = i * j;
    int s = sumDigits(p);
    //
    if (this->item != nullptr)
    {
        delete this->item;
        this->item = nullptr;
    }
    if (s >= 0 && s <= 1)
        this->item = new MagicBook();
    if (s >= 2 && s <= 3)
        this->item = new EnergyDrink();
    if (s >= 4 && s <= 5)
        this->item = new FirstAid();
    if (s >= 6 && s <= 7)
        this->item = new ExcemptionCard();
    if (s >= 8 && s <= 9)
    {
        string challenge;
        int t = (11 * i + j) % 4;
        switch (t)
        {
        case 0:
            challenge = "RobotS";
            break;
        case 1:
            challenge = "RobotC";
            break;
        case 2:
            challenge = "RobotSW";
            break;
        case 3:
            challenge = "all";
            break;
        }
        this->item = new PassingCard(challenge);
    }
}

Robot::~Robot() = default;

Position RobotC::getNextPosition()
{
    return criminal->getPrevPosition();
}

void RobotC::move()
{
    Position next_pos = getNextPosition();
    if (!next_pos.isEqual(Position::npos))
    {
        if (map->isWall(next_pos))
            return;
        else
            pos = next_pos;
    }
}

int RobotC::toSherlock() const
{
    return abs(pos.getRow() - sherlock->getCurrentPosition().getRow()) + abs(pos.getCol() - sherlock->getCurrentPosition().getCol());
}

int RobotC::toWatson() const
{
    return abs(pos.getRow() - watson->getCurrentPosition().getRow()) + abs(pos.getCol() - watson->getCurrentPosition().getCol());
}

int RobotC::getDistance() const
{
    return toSherlock() + toWatson();
}

string RobotC::str() const
{
    stringstream ss;
    ss << "Robot[pos=" << this->pos.str() << ";type=" << "C" << ";dist=]";
    return ss.str();
}

Position RobotS::getNextPosition()
{
    Position currentPos = this->getCurrentPosition();
    Position sherlockPos = this->sherlock->getCurrentPosition();

    Position directions[4] = {
        Position(currentPos.getRow() - 1, currentPos.getCol()),  // Up
        Position(currentPos.getRow(), currentPos.getCol() + 1),  // Right
        Position(currentPos.getRow() + 1, currentPos.getCol()),  // Down
        Position(currentPos.getRow(), currentPos.getCol() - 1)}; // Left

    int minDistance = INT_MAX;
    Position nextPos = Position::npos;
    for (const auto &i : directions)
    {
        if (!this->map->isValid(i, this))
        {
            continue;
        }

        int distance = abs(i.getRow() - sherlockPos.getRow()) + abs(i.getCol() - sherlockPos.getCol());
        if (distance < minDistance)
        {
            minDistance = distance;
            nextPos = i;
        }
    }
    return nextPos;
}
void RobotS::move()
{
    Position nextPos = getNextPosition();
    if (!nextPos.isEqual(Position::npos))
    {
        if (map->isWall(nextPos))
            return;
        else
            this->pos = nextPos;
    }
}

int RobotS::getDistance() const
{
    return abs(this->pos.getRow() - this->sherlock->getCurrentPosition().getRow()) + abs(this->pos.getCol() - this->sherlock->getCurrentPosition().getCol());
}

string RobotS::str() const
{
    stringstream ss;
    ss << "Robot[pos=" << this->pos.str() << ";type=" << "S" << ";dist=" << getDistance() << "]";
    return ss.str();
}

Position RobotW::getNextPosition()
{
    Position currentPos = this->getCurrentPosition();
    Position watsonPos = this->watson->getCurrentPosition();

    Position directions[4] = {
        Position(currentPos.getRow() - 1, currentPos.getCol()),  // Up
        Position(currentPos.getRow(), currentPos.getCol() + 1),  // Right
        Position(currentPos.getRow() + 1, currentPos.getCol()),  // Down
        Position(currentPos.getRow(), currentPos.getCol() - 1)}; // Left

    int minDistance = INT_MAX;
    Position nextPos = Position::npos;
    for (const auto &i : directions)
    {
        if (!this->map->isValid(i, this))
            continue;

        int distance = abs(i.getRow() - watsonPos.getRow()) + abs(i.getCol() - watsonPos.getCol());
        if (distance < minDistance)
        {
            minDistance = distance;
            nextPos = i;
        }
    }
    return nextPos;
}

void RobotW::move()
{
    Position nextPos = getNextPosition();
    if (!nextPos.isEqual(Position::npos) && map->isValid(nextPos, this))
        this->pos = nextPos;
}

int RobotW::getDistance() const
{
    return abs(this->pos.getRow() - this->watson->getCurrentPosition().getRow()) + abs(this->pos.getCol() - this->watson->getCurrentPosition().getCol());
}

string RobotW::str() const
{
    stringstream ss;
    ss << "Robot[pos=" << this->pos.str() << ";type=" << "W" << ";dist=" << getDistance() << "]";
    return ss.str();
}

Position RobotSW::getNextPosition()
{
    int minDistance = INT_MAX;
    Position nextPos = Position::npos;
    int directions[8][2] = {{-2, 0}, {-1, 1}, {0, 2}, {1, 1}, {2, 0}, {1, -1}, {0, -2}, {-1, -1}}; // 8 directions base on clock-wise
    for (int i = 0; i < 8; i++)
    {
        Position newPos = Position(this->pos.getRow() + directions[i][0], this->pos.getCol() + directions[i][1]);
        if (!this->map->isValid(newPos, this))
            continue;
        int distance = (abs(newPos.getRow() - this->sherlock->getCurrentPosition().getRow()) + abs(newPos.getCol() - this->sherlock->getCurrentPosition().getCol())) + (abs(newPos.getRow() - this->watson->getCurrentPosition().getRow()) + abs(newPos.getCol() - this->watson->getCurrentPosition().getCol()));
        if (distance < minDistance)
        {
            minDistance = distance;
            nextPos = newPos;
        }
    }
    return nextPos;
}

void RobotSW::move()
{
    Position nextPos = this->getNextPosition();
    if (!nextPos.isEqual(Position::npos))
    {
        if (map->isWall(nextPos))
            return;
        else
            this->pos = nextPos;
    }
}

int RobotSW::getDistance() const
{
    return abs(this->pos.getRow() - this->sherlock->getCurrentPosition().getRow()) + abs(this->pos.getCol() - this->sherlock->getCurrentPosition().getCol()) + abs(this->pos.getRow() - this->watson->getCurrentPosition().getRow()) + abs(this->pos.getCol() - this->watson->getCurrentPosition().getCol());
}

string RobotSW::str() const
{
    stringstream ss;
    ss << "Robot[pos=" << this->pos.str() << ";type=" << "SW" << ";dist=" << getDistance() << "]";
    return ss.str();
}

// Item: MagicBook, EnergyDrink, FirstAid, ExcemptionCard, PassingCard
bool MagicBook::canUse(Character *obj, Robot *robot)
{
    return ((obj->getName() == "Sherlock" || obj->getName() == "Watson") && obj->getEXP() <= 350);
}

void MagicBook::use(Character *obj, Robot *robot)
{
    obj->setEXP(ceilf(obj->getEXP() * 1.25));
}

bool EnergyDrink::canUse(Character *obj, Robot *robot)
{
    return ((obj->getName() == "Sherlock" || obj->getName() == "Watson") && obj->getHP() <= 100);
}

void EnergyDrink::use(Character *obj, Robot *robot)
{
    obj->setHP(ceilf(obj->getHP() * 1.2));
}

bool FirstAid::canUse(Character *obj, Robot *robot)
{
    return ((obj->getName() == "Sherlock" || obj->getName() == "Watson") && (obj->getHP() <= 100 || obj->getEXP() <= 350));
}

void FirstAid::use(Character *obj, Robot *robot)
{
    obj->setHP(ceilf(obj->getHP() * 1.5));
}

bool ExcemptionCard::canUse(Character *obj, Robot *robot)
{
    return (obj->getName() == "Sherlock" && obj->getHP() % 2);
}

void ExcemptionCard::use(Character *obj, Robot *robot)
{
    obj->setHP(obj->getHP());
    obj->setEXP(obj->getEXP());
}

bool PassingCard::canUse(Character *obj, Robot *robot)
{
    return (obj->getName() == "Watson" && !obj->getHP() % 2);
}

void PassingCard::use(Character *obj, Robot *robot)
{
    if (challenge == "all" || challenge == robot->getName())
        return;
    else
        obj->setEXP(obj->getEXP() - 50);
}

void BaseBag::SwapItem(BaseBag &otherCharacter, ItemType itemType)
{
    BaseItem *item = get(itemType);
    while (item != nullptr)
    {
        otherCharacter.insert(item);
        item = get(itemType);
    }
}

bool SherlockBag::insert(BaseItem *item)
{
    if (size >= capacity)
        return false; // Bag is full
    Node *newNode = new Node(item);
    newNode->next = head;
    head = newNode;
    size++;
    return true;
}

bool WatsonBag::insert(BaseItem *item)
{
    if (size >= capacity)
        return false; // Bag is full
    Node *newNode = new Node(item);
    newNode->next = head;
    head = newNode;
    size++;
    return true;
}

BaseItem *BaseBag::get()
{
    if (head == nullptr)
        return nullptr;
    Node *prev = nullptr;
    Node *current = head;
    while (current != nullptr && obj != nullptr)
    {
        if (current->item == nullptr ||
            !current->item->canUse(obj, robot) ||
            dynamic_cast<ExcemptionCard *>(current->item) != nullptr || // Chặn ExcemptionCard
            dynamic_cast<PassingCard *>(current->item) != nullptr)      // Chặn PassingCard
        {
            prev = current;
            current = (current->next != nullptr) ? current->next : nullptr;
        }
        else
            break;
    }
    if (current == nullptr)
        return nullptr;
    BaseItem *item = current->item;
    if (prev != nullptr)
        prev->next = current->next;
    else
        head = head->next;
    delete current;
    size--;
    return item;
}

BaseItem *BaseBag::get(ItemType itemType)
{
    Node *temp = head;
    Node *prev = nullptr;
    while (temp != nullptr)
    {
        if (temp->item->getItemType() == itemType)
        {
            if (prev != nullptr)
            {
                prev->next = temp->next;
                temp->next = head;
                head = temp;
            }
            BaseItem *item = head->item;
            head = head->next;
            delete temp;
            size--;
            return item;
        }
        prev = temp;
        temp = temp->next;
    }
    return nullptr;
}

string BaseItem::getType() const
{
    switch (item_type)
    {
    case MAGIC_BOOK:
        return "MagicBook";
    case ENERGY_DRINK:
        return "EnergyDrink";
    case FIRST_AID:
        return "FirstAid";
    case EXCEMPTION_CARD:
        return "ExcemptionCard";
    case PASSING_CARD:
        return "PassingCard";
    default:
        return "";
    }
}

string BaseBag::str() const
{
    std::string result = "Bag[count=" + std::to_string(size) + ";";
    Node *current = head;
    while (current != nullptr)
    {
        result += current->item->getType() + ",";
        current = current->next;
    }
    if (size > 0)
    {
        result.pop_back();
    }
    result += "]";
    return result;
}

StudyPinkProgram::StudyPinkProgram(const string &filepath)
{
    this->config = new Configuration(filepath);
    map = new Map(config->map_num_rows, config->map_num_cols, config->num_walls, config->arr_walls, config->num_fake_walls, config->arr_fake_walls);
    sherlock = new Sherlock(1, config->sherlock_moving_rule, config->sherlock_init_pos, map, config->sherlock_init_hp, config->sherlock_init_exp);
    watson = new Watson(2, config->watson_moving_rule, config->watson_init_pos, map, config->watson_init_hp, config->watson_init_exp);
    criminal = new Criminal(0, config->criminal_init_pos, map, sherlock, watson);
    num_steps = config->num_steps;
    arr_mv_objs = new ArrayMovingObject(config->max_num_moving_objects);
    arr_mv_objs->add(criminal);
    arr_mv_objs->add(sherlock);
    arr_mv_objs->add(watson);
}

bool StudyPinkProgram::isStop() const
{
    return sherlock->getHP() == 0 || watson->getHP() == 0 || criminal->getCurrentPosition().isEqual(sherlock->getCurrentPosition()) || criminal->getCurrentPosition().isEqual(watson->getCurrentPosition());
}

void StudyPinkProgram::run(bool verbose)
{
    for (int istep = 0; istep < num_steps; ++istep)
    {
        for (int i = 0; i < arr_mv_objs->size(); ++i)
        {
            arr_mv_objs->get(i)->move();
            bool isCreated = false
            if (criminal->steps != 0 && criminal->steps % 3 == 0 && !isCreated)
            {
                if (!arr_mv_objs->isFull())
                {
                    if (arr_mv_objs->size == 3)
                    {
                        robotC = new RobotC(arr_mv_objs->size(), criminal->getPrevPosition(), map, criminal);
                        arr_mv_objs->add(robotC);
                    }
                    else if (arr_mv_objs->size() != 3 && criminal->distanceToSherlock() < criminal->distanceToWatson()) // Nếu khoảng cách từ Criminal đến Sherlock nhỏ hơn khoảng cách từ Criminal đến Watson
                    {
                        robotS = new RobotS(arr_mv_objs->size(), criminal->getPrevPosition(), map, criminal, sherlock);
                        arr_mv_objs->add(robotS);
                    }
                    else if (arr_mv_objs->size() != 3 && criminal->distanceToSherlock() > criminal->distanceToWatson()) // Nếu khoảng cách từ Criminal đến Sherlock lớn hơn khoảng cách từ Criminal đến Watson
                    {
                        robotW = new RobotW(arr_mv_objs->size(), criminal->getPrevPosition(), map, criminal, watson);
                        arr_mv_objs->add(robotW);
                    }
                    else if (arr_mv_objs->size() != 3 && criminal->distanceToSherlock() == criminal->distanceToWatson()) // Nếu khoảng cách từ Criminal đến Sherlock bằng khoảng cách từ Criminal đến Watson
                    {
                        robotSW = new RobotSW(arr_mv_objs->size(), criminal->getPrevPosition(), map, criminal, sherlock, watson);
                        arr_mv_objs->add(robotSW);
                    }
                }
            }
            if (sherlock->getCurrentPosition().isEqual(watson->getCurrentPosition()))
            {
                sherlock->getBag()->SwapItem(*watson->getBag(), ItemType::PASSING_CARD);
                watson->getBag()->SwapItem(*sherlock->getBag(), ItemType::EXCEMPTION_CARD);
            }
            if (sherlock->getCurrentPosition().isEqual(criminal->getPrevPosition()))
            {
                if (sherlock->getEXP() > 500)
                    sherlock->setPositionTo(criminal->getCurrentPosition());
                else
                {
                    BaseItem *item = robotC->getItem();
                    sherlock->getBag()->insert(item);
                    BaseItem *Item = sherlock->getBag()->get();
                    if (Item != nullptr)
                        Item->use(sherlock, nullptr);
                }
            }
            if (watson->getCurrentPosition().isEqual(criminal->getPrevPosition()))
            {
                BaseItem *item = robotC->getItem();
                watson->getBag()->insert(item);
                watson->setMovingRule(""); // Watson dừng lại
                BaseItem *Item = watson->getBag()->get();
                if (Item != nullptr)
                    Item->use(watson, nullptr);
            }
            if (sherlock->getCurrentPosition().isEqual(arr_mv_objs->get(i)->getCurrentPosition()))
            {
                string robotName = arr_mv_objs->get(i)->getName();
                if (robotName == "RobotW")
                {
                    BaseItem *item = sherlock->getBag()->get();
                    item = robotW->getItem();
                    sherlock->getBag()->insert(item);
                    BaseItem *Item = sherlock->getBag()->get();
                    if (Item != nullptr)
                        Item->use(sherlock, nullptr);
                }
                if (robotName == "RobotS")
                {
                    if (sherlock->getEXP() > 400)
                    {
                        BaseItem *item = robotS->getItem();
                        if (item != nullptr)
                            sherlock->getBag()->insert(item);
                    }
                    else
                    {
                        BaseItem *item = sherlock->getBag()->get(EXCEMPTION_CARD);
                        if (item != nullptr)
                            item->use(sherlock, robotS);
                        else
                        {
                            sherlock->setEXP(ceilf(sherlock->getEXP() * 0.85));
                            sherlock->setHP(ceilf(sherlock->getHP() * 0.85));
                        }
                    }
                    BaseItem *Item = sherlock->getBag()->get();
                    if (Item != nullptr)
                        Item->use(sherlock, nullptr);
                }
                if (robotName == "RobotSW")
                {
                    if (sherlock->getHP() > 335 && sherlock->getEXP() > 300)
                    {
                        BaseItem *item = robotSW->getItem();
                        sherlock->getBag()->insert(item);
                    }
                    else
                    {
                        BaseItem *item = sherlock->getBag()->get(EXCEMPTION_CARD);
                        if (item != nullptr)
                            item->use(sherlock, robotSW);
                        else
                        {
                            sherlock->setEXP(ceilf(sherlock->getEXP() * 0.85));
                            sherlock->setHP(ceilf(sherlock->getHP() * 0.85));
                        }
                    }
                    BaseItem *Item = sherlock->getBag()->get();
                    if (Item != nullptr)
                        Item->use(sherlock, nullptr);
                }
            }
            if (watson->getCurrentPosition().isEqual(arr_mv_objs->get(i)->getCurrentPosition()))
            {
                string robotName = arr_mv_objs->get(i)->getName();
                if (robotName == "RobotW")
                {
                    if (watson->getEXP() > 350)
                    {
                        BaseItem *item = robotW->getItem();
                        watson->getBag()->insert(item);
                    }
                    else
                    {
                        BaseItem *item = watson->getBag()->get(PASSING_CARD);
                        if (item != nullptr && item->canUse(watson, robotW))
                            item->use(watson, robotW);
                        else
                            watson->setHP(ceilf(watson->getHP() * 0.95));
                    }
                    BaseItem *Item = watson->getBag()->get();
                    if (Item != nullptr)
                        Item->use(watson, nullptr);
                }
                if (robotName == "RobotS")
                {
                } // Do nothing?
                if (robotName == "RobotSW")
                {
                    if (watson->getHP() > 165 && watson->getEXP() > 600)
                    {
                        BaseItem *item = robotSW->getItem();
                        watson->getBag()->insert(item);
                    }
                    else
                    {
                        BaseItem *item = watson->getBag()->get(PASSING_CARD);
                        if (item->canUse(watson, robotSW))
                            item->use(watson, robotSW);
                        else
                        {
                            watson->setEXP(ceilf(watson->getEXP() * 0.85));
                            watson->setHP(ceilf(watson->getHP() * 0.85));
                        }
                    }
                    BaseItem *Item = watson->getBag()->get();
                    if (Item != nullptr)
                        Item->use(watson, nullptr);
                }
            }
            if (isStop())
            {
                printStep(istep);
                break;
            }
            if (verbose)
                printStep(istep);
        }
    }
    StudyPinkProgram::printResult();
}

StudyPinkProgram::~StudyPinkProgram()
{
    delete map;
    delete criminal;
    delete sherlock;
    delete watson;
    delete robotC;
    delete robotS;
    delete robotW;
    delete robotSW;
    delete arr_mv_objs;
    delete config;
};
////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////
