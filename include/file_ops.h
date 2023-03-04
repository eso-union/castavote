/***********************************************************************
 *                            T R O K A M
 *                       Internet Search Engine
 *
 * Copyright (C) 2022, Nicolas Slusarenko
 *                     nicolas.slusarenko@EsoUnion.com
 *
 * This file is part of EsoUnion.
 *
 * EsoUnion is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * EsoUnion is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with EsoUnion. If not, see <http://www.gnu.org/licenses/>.
 **********************************************************************/

#pragma once

/// C++
#include <string>
#include <vector>

/**
 * File Operations.
 */
namespace EsoUnion
{
    class FileOps
    {
        public:

            static std::string read(
                const std::string &filename);

            static std::string readLines(
                const size_t SIZE_LIMIT,
                const std::string &filename);

            /**
             * Put every line of file in content.
             * It skips blank lines and commented lines.
             * Commented lines start with '#'.
             */
            static void readNoComment(
                const std::string &filename,
                std::vector<std::string> &content);

            static void save(
                const std::string &filename,
                const std::string &content);

            static void rmDir(
                const std::string &dirname);

            static void cleanDir(
                const std::string &dirname);

            static std::string generateDirName(
                const std::string &stem,
                const int &index,
                const int &serial);

            static std::string generateDirLabel(
                const std::string &stem,
                const int &index,
                const int &serial);
    };
}
