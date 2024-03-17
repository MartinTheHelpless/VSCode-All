#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>
#include <algorithm>
#include <stdexcept>

class Visitor;
class MutatingVisitor;

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

    virtual Value *clone() const = 0;

    virtual void accept(Visitor &visitor) const;
    virtual void accept(MutatingVisitor &visitor);

    virtual Value *operator[](int n) const;
    virtual Value *operator[](std::string key) const;
};

class Integer : public Value
{
private:
    int val;

public:
    Integer(int n);

    int get_value() const;

    virtual Integer *clone() const override;
};

class Array : public Value
{
private:
    std::vector<Value *> elements;

public:
    Array(const std::initializer_list<Value *> &elems);
    Array(const std::vector<Value *> &elems);

    ~Array();

    size_t size() const;

    void append(Value *elem);

    void remove(int n);

    Value *operator[](int n) const override;

    virtual Array *clone() const override;
};

class Object : public Value
{
private:
    std::unordered_map<std::string, Value *> elements;

public:
    Object(const std::unordered_map<std::string, Value *> &elems);

    Object() = default;

    ~Object();

    std::vector<std::string> keys() const;

    void insert(const std::string &key, Value *elem);

    void remove(const std::string &key);

    Value *operator[](std::string key) const override;

    size_t size() const;

    Object *clone() const;
};

class Null : public Value
{
public:
    Null();

    Null *clone() const;
};

class Visitor
{
public:
    virtual ~Visitor() {}
    virtual void visit(const Null *null) = 0;
    virtual void visit(const Array *array) = 0;
    virtual void visit(const Value *value) = 0;
    virtual void visit(const Object *object) = 0;
    virtual void visit(const Integer *integer) = 0;
};

class MutatingVisitor
{
public:
    virtual ~MutatingVisitor() {}
    virtual void visit(Null *null) = 0;
    virtual void visit(Array *array) = 0;
    virtual void visit(Value *value) = 0;
    virtual void visit(Object *object) = 0;
    virtual void visit(Integer *integer) = 0;
};

class PrintVisitor : public Visitor
{
private:
    std::stringstream &sstream;

public:
    PrintVisitor(std::stringstream &stream) : sstream(stream) {}
    ~PrintVisitor() {}

    virtual void visit(const Null *null) override {}
    virtual void visit(const Value *value) override {}
    virtual void visit(const Array *array) override {}
    virtual void visit(const Object *object) override {}
    virtual void visit(const Integer *integer) override {}
};

class RemoveNullVisitor : public MutatingVisitor
{
private:
public:
    RemoveNullVisitor() {}
    ~RemoveNullVisitor() {}
    virtual void visit(Null *null) override {}
    virtual void visit(Value *value) override {}
    virtual void visit(Array *array) override {}
    virtual void visit(Object *object) override {}
    virtual void visit(Integer *integer) override {}
};