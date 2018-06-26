#ifndef OBJ_READER_H
#define OBJ_READER_H


#include "types.h"
#include "control.h"
#include <string>
#include <fstream>

class ObjReader {
public:
	ObjReader() {};
	~ObjReader();
    void read(std::string filename, Control& control);

private:
    std::fstream m_fs;
};


#endif

