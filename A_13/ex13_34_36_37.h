#ifndef EX13_34_36_37_H_
#define EX13_34_36_37_H_

#include <iostream>
#include <string>
#include <set>

using namespace std;

class Folder;

class Message
{
    friend void swap(Message&, Message&);
    friend void swap(Folder&, Folder&);
    friend class Folder;
private:
    string contents;
    set<Folder*> folders;

    void add_to_Folders(const Message &);
    void remove_from_Folders();

    void addFldr(Folder *f) { folders.insert(f); }
    void remFldr(Folder *f) { folders.erase(f); }

public:
    explicit Message(const string &str = "") : contents(str) {}
    Message(const Message&);
    Message& operator= (const Message&);
    ~Message();

    void save(Folder&);
    void remove(Folder&);

    void print_debug() {
        cout << contents << endl;
    }
};

void swap(Message&, Message&);

class Folder
{
    friend void swap(Message&, Message&);
    friend void swap(Folder&, Folder&);
    friend class Message;
private:
    set<Message*> msgs;

    void add_to_Messages(const Folder &);
    void rem_from_Messages();

    void addMsg(Message *m) { msgs.insert(m); }
    void remMsg(Message *m) { msgs.erase(m); }
    
public:
    Folder() = default;
    Folder(const Folder&);
    Folder& operator= (const Folder&);
    ~Folder();

    void print_debug() {
    for (auto m : msgs) std::cout << m->contents << " ";
    std::cout << std::endl;
    }
};

void swap(Folder&, Folder&);

#endif  // EX13_34_36_37_H_
