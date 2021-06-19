#ifndef CHAPTER_H
#define CHAPTER_H

#include<QVector>

#include "problem.h"

class Chapter
{
public:
    Chapter();
    Chapter(int chapterId);

public:
    int chapterID;
    QVector<Problem> problems;
};

#endif // CHAPTER_H
