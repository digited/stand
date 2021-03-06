/*
 *
 *    MazeProject.h
 *                                    (c) HAL@shurabaP
 *                                        2013/08/24
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef MAZEPROJECT_H
#define MAZEPROJECT_H

#include <QFileInfo>
#include "ContourModel.h"
#include "TimeMapModel.h"

/**
 * @brief Represents a project of SingMaze.
 */
class MazeProject
{
public:
    MazeProject();
    ~MazeProject();

    QFileInfo wave1Path;
    QFileInfo wave2Path;
    ContourModel morphRatioContour;
    TimeMapModel timeMap;

    bool read(const QString &path);
    bool write(const QString &path) const;

private:
};

#endif // MAZEPROJECT_H
