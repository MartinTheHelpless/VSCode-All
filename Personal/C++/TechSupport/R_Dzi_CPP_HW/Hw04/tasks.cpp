#include "tasks.h"

void Value::accept(Visitor &visitor) const { visitor.visit(this); }
void Value::accept(MutatingVisitor &visitor) { visitor.visit(this); }

Value *Value::operator[](int n) const
{
    throw IndexException("no integerino");
}

Value *Value::operator[](std::string key) const
{
    throw IndexException("no stringerino");
}

Integer::Integer(int n) : val(n) {}

int Integer::get_value() const
{
    return val;
}

Integer *Integer::clone() const
{
    return new Integer(val);
}

Array::Array(const std::initializer_list<Value *> &elems) : elements(elems) {}

Array::Array(const std::vector<Value *> &elems) : elements(elems) {}

Array::~Array()
{
    for (auto &elem : elements)
        delete elem;
}

size_t Array::size() const
{
    return elements.size();
}

void Array::append(Value *elem)
{
    elements.push_back(elem);
}

void Array::remove(int n)
{
    if (n >= 0 && n < elements.size())
    {
        delete elements[n];
        elements.erase(elements.begin() + n);
    }
}

Value *Array::operator[](int n) const
{
    if (n >= 0 && n < elements.size())
        return elements[n];
    else
        return nullptr;
}

Array *Array::clone() const
{
    {
        std::vector<Value *> clone;
        for (const auto &e : elements)
        {
            clone.push_back(e->clone());
        }
        return new Array(elements);
    }
}

Object::Object(const std::unordered_map<std::string, Value *> &elems) : elements(elems) {}

Object::~Object()
{
    for (auto &pair : elements)
        delete pair.second;
}

std::vector<std::string> Object::keys() const
{
    std::vector<std::string> result;
    for (const auto &e : elements)
    {
        result.push_back(e.first);
    }
    std::sort(result.begin(), result.end());
    return result;
}

void Object::insert(const std::string &key, Value *elem)
{
    elements[key] = elem->clone();
}

void Object::remove(const std::string &key)
{
    auto it = elements.find(key);
    if (it != elements.end())
    {
        delete it->second;
        elements.erase(it);
    }
}

Value *Object::operator[](std::string key) const
{
    auto it = elements.find(key);
    if (it != elements.end())
        return it->second;
    else
        throw IndexException("Key not found");
}

size_t Object::size() const
{
    return elements.size();
}

Object *Object::clone() const
{
    std::unordered_map<std::string, Value *> cloned_pairs;
    for (const auto &pair : elements)
        cloned_pairs[pair.first] = pair.second->clone();
    return new Object(cloned_pairs);
}

Null::Null() {}

Null *Null::clone() const
{
    return new Null();
}
