#pragma once
#include <vector>
#include <utility>
#include <sstream>
#include <cstdint>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <initializer_list>

class Value;
class Null;
class Array;
class Object;
class Integer;

class IndexException : public std::exception
{
public:
    const char *what() const noexcept override { return "Tried to index an unindexable object!"; }
};

class Visitor
{
public:
    virtual ~Visitor() {}

    virtual void visit(const Value *value) = 0;
};

class MutatingVisitor
{
public:
    virtual ~MutatingVisitor() {}

    virtual void visit(Value *value) = 0;
};

class Value
{
private:
protected:
    uint32_t m_ClassID = 0;
    std::vector<Value *> m_Values;
    std::vector<std::string> m_Keys;
    std::unordered_map<std::string, Value *> m_MapValues;

public:
    Value() {}
    virtual ~Value() {}

    virtual Value *clone() const = 0;

    virtual uint32_t GetClassID() const { return m_ClassID; }

    virtual void accept(Visitor &visitor) const;
    virtual void accept(MutatingVisitor &visitor);

    virtual Value *operator[](uint32_t index) const;
    virtual Value *operator[](std::string index) const;
};

class Integer : public Value
{
private:
    uint32_t m_Value;

public:
    Integer(uint32_t value);
    ~Integer() {}

    virtual Integer *clone() const override;

    uint32_t get_value() const;
};

class Object : public Value
{
private:
    Object(std::vector<std::pair<std::string, Value *>> &values);

public:
    Object(std::initializer_list<std::pair<std::string, Value *>> values);
    virtual ~Object();

    void insert(const char *key, Value *value);
    void insert(std::string key, Value *value);

    void remove(std::string key);
    void remove(const char *key);

    std::vector<std::string> keys() const;
    std::unordered_map<std::string, Value *> &GetMap() { return m_MapValues; }
    const std::unordered_map<std::string, Value *> &GetMap() const { return m_MapValues; }

    uint32_t size() const { return m_Keys.size(); }

    virtual Object *clone() const override;
};

class Null : public Value
{
private:
public:
    Null() { m_ClassID = 4; }
    ~Null() {}
    virtual Value *clone() const override { return new Null(); }
};

class Array : public Value
{
private:
    Array(std::vector<Value *> values);

public:
    Array(std::initializer_list<Value *> values);
    virtual ~Array();

    uint32_t size() const { return m_Values.size(); }

    void append(Value *value) { m_Values.push_back(value); }
    void remove(uint32_t index) { m_Values.erase(m_Values.begin() + index); }

    void SetValueVector(std::vector<Value *> &values)
    {

        for (auto val : m_Values)
            delete val;

        m_Values = values;
    }

    std::vector<Value *> &GetValues() { return m_Values; }
    const std::vector<Value *> &GetValues() const { return m_Values; }

    virtual Array *clone() const override;
};

class RemoveNullVisitor : public MutatingVisitor
{
private:
public:
    RemoveNullVisitor() {}
    ~RemoveNullVisitor() {}

    virtual void visit(Value *value) override
    {
        switch (value->GetClassID())
        {
        case 2:
        {
            Array *val = static_cast<Array *>(value);

            std::vector<Value *> vals = val->GetValues();
            std::vector<Value *> newVals;

            for (size_t i = 0; i < vals.size(); i++)
                if (vals[i]->GetClassID() == 2 || vals[i]->GetClassID() == 3)
                    vals[i]->accept(*this), newVals.push_back(vals[i]);
                else if (vals[i]->GetClassID() == 1 || vals[i]->GetClassID() == 0)
                    newVals.push_back(vals[i]->clone());

            val->SetValueVector(newVals);

            break;
        }

        case 3:
        {
            Object *val = static_cast<Object *>(value);

            std::unordered_map<std::string, Value *> map = val->GetMap();

            for (std::string key : val->keys())
                if (map.at(key)->GetClassID() == 4)
                    val->remove(key);
                else if (map.at(key)->GetClassID() == 2 || map.at(key)->GetClassID() == 3)
                    map.at(key)->accept(*this);

            break;
        }

        default:
            break;
        }
    }
};

class PrintVisitor : public Visitor
{
private:
    std::stringstream &ss;

public:
    PrintVisitor(std::stringstream &stream) : ss(stream) {}
    ~PrintVisitor() {}

    virtual void visit(const Value *value) override
    {
        switch (value->GetClassID())
        {
        case 1:
        {
            ss << (*static_cast<const Integer *>(value)).get_value();

            break;
        }

        case 2:
        {
            const Array *val = static_cast<const Array *>(value);

            const std::vector<Value *> vec = (*val).GetValues();

            ss << "[";

            for (size_t i = 0; i < vec.size(); i++)
            {
                vec[i]->accept(*this);
                i < vec.size() - 1 ? ss << ", " : ss;
            }

            ss << "]";
            break;
        }

        case 3:
        {
            const Object *obj = static_cast<const Object *>(value);

            const auto map = (*obj).GetMap();
            const auto keys = (*obj).keys();

            ss << "{";

            for (size_t i = 0; i < keys.size(); i++)
            {
                ss << keys[i] << ": ";
                map.at(keys[i])->accept(*this);
                i < keys.size() - 1 ? ss << ", " : ss;
            }

            ss << "}";
            break;
        }

        case 4:
        {
            ss << "null";

            break;
        }

        default:
            break;
        }
    }
};
