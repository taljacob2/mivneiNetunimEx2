
#ifndef NEWMAKER_H
#define NEWMAKER_H

class NewMaker {
  public:
    static bool createdOnHeapStatic;
};

bool NewMaker::createdOnHeapStatic = false;

#endif // NEWMAKER_H
