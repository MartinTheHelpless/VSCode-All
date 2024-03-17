#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <stdexcept>

class IndexException : public std::exception
{
private:
    std::string exception;

public:
    IndexException(const char *msg) : exception(msg) {}
};

class Value
{
public:
    virtual ~Value() {}

    virtual Value *clone() = 0;

    virtual void accept(class Visitor &visitor) = 0;

    virtual Value *operator[](int n) const { throw IndexException("no integerino"); }
    virtual Value *operator[](std::string key) const { throw IndexException("no stringerino"); }
};

class Integer : public Value
{
private:
    int val;

public:
    Integer(int n);

    int get_value() const;

    virtual Integer *clone() override;

    virtual void accept(class Visitor &visitor) override;
};

class Array : public Value
{
private:
    std::vector<Value *> elements;

public:
    Array(const std::vector<Value *> &elems);

    ~Array();

    size_t size() const;

    void append(Value *elem);

    void remove(int n);

    Value *operator[](int n) const override;

    Array *clone() const;

    void accept(Visitor &visitor) override;
};

class Object : public Value
{
private:
    std::unordered_map<std::string, Value *> elements;

public:
    Object(const std::unordered_map<std::string, Value *> &elems);

    Object() {}

    ~Object();

    std::vector<std::string> keys() const;

    void insert(const std::string &key, Value *elem);

    void remove(const std::string &key);

    Value *operator[](std::string key) const override;

    size_t size() const;

    Object *clone() const;

    void accept(Visitor &visitor) override;
};

class Null : public Value
{
public:
    Null();

    Null *clone() const;

    virtual void accept(Visitor &visitor) override;
};

class Visitor
{
public:
    virtual ~Visitor() {}
    virtual void visit(Integer &integer) = 0;
    virtual void visit(Array &array) = 0;
    virtual void visit(Object &object) = 0;
    virtual void visit(Null &null) = 0;
};