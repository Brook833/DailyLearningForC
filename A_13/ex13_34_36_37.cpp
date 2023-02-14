#include "ex13_34_36_37.h"

void Message::add_to_Folders(const Message& m)
{
    for (auto f : m.folders) f->addMsg(this);
}

void Message::remove_from_Folders() {
    for (auto f : folders) {
        f->remMsg(this);
    }
}

void Message::save(Folder& f)
{
    addFldr(&f);
    f.addMsg(this);
}

void Message::remove(Folder& f)
{
    remFldr(&f);
    f.remMsg(this);
}

Message::Message(const Message& m) : contents(m.contents), folders(m.folders)
{
    add_to_Folders(m);
}

Message& Message::operator=(const Message& rhs)
{
    remove_from_Folders();
    contents = rhs.contents;
    folders = rhs.folders;
    add_to_Folders(rhs);
    return *this;
}

Message::~Message()
{
    remove_from_Folders();
}

void swap(Message& lhs, Message& rhs)
{
    using std::swap;
    lhs.remove_from_Folders();
    rhs.remove_from_Folders();

    swap(lhs.folders, rhs.folders);
    swap(lhs.contents, rhs.contents);

    lhs.add_to_Folders(lhs);
    rhs.add_to_Folders(rhs);
}

void Folder::add_to_Messages(const Folder &f) {
    for (auto m : f.msgs) {
        m->addFldr(this);
    }
}

void Folder::rem_from_Messages() {
    for (auto m : msgs) {
        m->remFldr(this);
    }
}

Folder::Folder(const Folder &f) : msgs(f.msgs) {
    add_to_Messages(f);
}

Folder& Folder::operator= (const Folder &f) {
    rem_from_Messages();
    msgs = f.msgs;
    add_to_Messages(f);
    return *this;
}

Folder::~Folder() {
    rem_from_Messages();
}

void swap(Folder &lhs, Folder &rhs) {
    using std::swap;
    lhs.rem_from_Messages();
    rhs.rem_from_Messages();
    swap(lhs.msgs, rhs.msgs);
    lhs.add_to_Messages(lhs);
    lhs.add_to_Messages(rhs);
}