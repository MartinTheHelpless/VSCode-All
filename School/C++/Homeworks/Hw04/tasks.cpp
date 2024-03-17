#include "tasks.h"

// --------------------------------- Value Class Implemented in .h ---------------------------------------

void Value::accept(Visitor &visitor) const { visitor.visit(this); }

void Value::accept(MutatingVisitor &visitor) { visitor.visit(this); }

Value *Value::operator[](uint32_t index) const
{
    try
    {

        if (this->GetClassID() == 4 || this->GetClassID() == 1)
            throw IndexException();
        else if (index < m_Values.size())
            return m_Values[index];
        else
            return nullptr;
    }
    catch (const std::exception &e)
    {
        throw IndexException();
    }
}

Value *Value::operator[](std::string index) const
{
    try
    {
        if (this->GetClassID() == 4 || this->GetClassID() == 1)
            throw IndexException();
        else if (m_MapValues.find(index) != m_MapValues.end())
            return m_MapValues.at(index);
        else
            return nullptr;
    }
    catch (const std::exception &e)
    {
        throw IndexException();
    }
}

// ----------------------------------------- Integer Class -----------------------------------------------

Integer::Integer(uint32_t value)
{
    m_Value = value;
    m_ClassID = 1;
}

Integer *Integer::clone() const
{
    return new Integer{m_Value};
}

uint32_t Integer::get_value() const
{
    return m_Value;
}

// ----------------------------------------- Object Class ------------------------------------------------

Object::Object(std::initializer_list<std::pair<std::string, Value *>> values)
{
    m_ClassID = 3;

    for (auto value : values)
        m_MapValues.insert(value), m_Keys.push_back(value.first);
}

Object::Object(std::vector<std::pair<std::string, Value *>> &values)
{
    m_ClassID = 3;

    for (auto value : values)
        m_MapValues.insert(value), m_Keys.push_back(value.first);
}

Object::~Object()
{
    for (auto &pair : m_MapValues)
        delete pair.second;
}

void Object::insert(const char *key, Value *value)
{
    std::string str(key);

    if (m_MapValues.find((str)) != m_MapValues.end())
        remove(key);

    m_MapValues.insert({(str), value}), m_Keys.push_back((str));

    std::sort(m_Keys.begin(), m_Keys.end());
}

void Object::insert(std::string key, Value *value)
{
    if (m_MapValues.find(key) != m_MapValues.end())
        remove(key);

    m_MapValues.insert({key, value}), m_Keys.push_back(key);

    std::sort(m_Keys.begin(), m_Keys.end());
}

void Object::remove(std::string key)
{
    if (m_MapValues.find(key) != m_MapValues.end())
    {
        delete m_MapValues.at(key);
        m_MapValues.erase(key);

        for (size_t i = 0; i < m_Keys.size(); i++)
            if (m_Keys[i] == key)
            {
                m_Keys.erase(m_Keys.begin() + i);
                break;
            }
    }
}

void Object::remove(const char *key)
{
    std::string str(key);

    if (m_MapValues.find(str) != m_MapValues.end())
    {
        delete m_MapValues.at(key);
        m_MapValues.erase(str);

        for (size_t i = 0; i < m_Keys.size(); i++)
            if (m_Keys[i] == str)
            {
                m_Keys.erase(m_Keys.begin() + i);
                break;
            }
    }
}

std::vector<std::string> Object::keys() const
{
    return m_Keys;
}

Object *Object::clone() const
{

    std::vector<std::pair<std::string, Value *>> initList;

    for (const auto &key : m_Keys)
    {
        auto it = m_MapValues.find(key);
        if (it != m_MapValues.end())
        {
            Value *newValue = it->second->clone();
            initList.push_back({key, newValue});
        }
    }

    return new Object(initList);
}

// ----------------------------------------- Array Class ------------------------------------------------

Array::Array(std::initializer_list<Value *> values)
{
    m_ClassID = 2;

    for (auto value : values)
        m_Values.push_back(value);
}

Array::Array(std::vector<Value *> values)
{
    m_ClassID = 2;

    for (auto value : values)
        m_Values.push_back(value);
}

Array::~Array()
{
    for (Value *val : m_Values)
        delete val;
}

Array *Array::clone() const
{
    std::vector<Value *> copiedValues;

    for (const auto &value : m_Values)
    {
        Value *newValue = value->clone(); // Assuming Value class has a clone method
        copiedValues.push_back(newValue);
    }

    return new Array(copiedValues);
}
