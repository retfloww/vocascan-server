#ifndef NEWVOCABHANDLER_H
#define NEWVOCABHANDLER_H

#include "database.hpp"
#include <vector>

class NewVocabHandler
{

public:
    NewVocabHandler(const Database &db);

private:
    Database database;
};

#endif //NEWVOCABHANDLER_H
