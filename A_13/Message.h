#include <string>
#include <set>

using namespace std;

class Folder;
class Message {
    friend class Folder;
public:
    explicit Message(const string &str = ""):contents(str) {}
    Message(const Message &m);
    Message& operator= (const Message&);
    ~Message();

    void save(Folder&);  // 目录中添加该Message
    void remove(Folder&);  // 目录中删除该Message
private:
    string contents;  // 信息
    set<Folder*> folders;  // 目录

    void add_to_Folders(const Message&);
    void remove_to_Folders();
};

void Message::save(Folder &f) {
    folders.insert(&f);
    //f.add_Msg(this);
}

void Message::remove(Folder &f) {
    folders.erase(&f);
    //f.rem_Msg(this);
}

void Message::add_to_Folders(const Message &m) {
    for (auto f: m.folders) {
        //f->add_Msg(this);
    }
}

void Message::remove_to_Folders() {
    for (auto f: folders) {
        //f->rem_Msg(this);
    }
}

Message::Message(const Message &m) : contents(m.contents), folders(m.folders) {
    add_to_Folders(m);
}

Message& Message::operator=(const Message &m) {
    remove_to_Folders();
    contents = m.contents;
    folders = m.folders;
    add_to_Folders(m);
    return *this;
}

Message::~Message() {
    remove_to_Folders();
}

