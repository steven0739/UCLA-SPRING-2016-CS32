//
//  list.cpp
//  HOMEWORK 4.3
//
//  Created by 杨博超 on 16/5/23.
//  Copyright © 2016年 杨博超. All rights reserved.
//
//
//#include <iostream>
//#include <string>
//#include <vector>
//
//using namespace std;
//
//class File
//{
//public:
//    File(string nm) : m_name(nm) {}
//    virtual ~File() {};
//    string name() const { return m_name; }
//    virtual bool add(File* f) = 0;
//    virtual const vector<File*>* files() const = 0;
//private:
//    string m_name;
//};
//
//class PlainFile : public File
//{
//public:
//    PlainFile(string nm) : File(nm) {}
//    virtual bool add(File* f) { return false; }
//    virtual const vector<File*>* files() const { return NULL; }
//};
//
//class Directory : public File
//{
//public:
//    Directory(string nm) : File(nm) {}
//    virtual ~Directory();
//    virtual bool add(File* f) { m_files.push_back(f); return true; }
//    virtual const vector<File*>* files() const { return &m_files; }
//private:
//    vector<File*> m_files;
//};
//
//Directory::~Directory()
//{
//    for (int k = 0; k < m_files.size(); k++)
//        delete m_files[k];
//}

void listAll(string path, const File* f)  // two-parameter overload
{
    path = path + "/" + f->name();
    cout << path << endl;
    
    if (f->files() != NULL) // not plain
        // if it is a directory, iterate the loop
    {
        const vector<File*>& files = *f->files();
        for (size_t k = 0; k < files.size(); k++)
            listAll(path, files[k]);
    }
}

//void listAll(const File* f)  // one-parameter overload
//{
//    listAll("", f);
//}
//
//int main()
//{
//    Directory* d1 = new Directory("Fun");
//    d1->add(new PlainFile("party.jpg"));
//    d1->add(new PlainFile("beach.jpg"));
//    d1->add(new PlainFile("skitrip.jpg"));
//    Directory* d2 = new Directory("Work");
//    d2->add(new PlainFile("seaslab.jpg"));
//    Directory* d3 = new Directory("My Pictures");
//    d3->add(d1);
//    d3->add(new PlainFile("me.jpg"));
//    d3->add(new Directory("Miscellaneous"));
//    d3->add(d2);
//    listAll(d3);
//    delete d3;
//}