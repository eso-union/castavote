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

// C++
#include <iostream>
#include <string>
#include <vector>

// Boost
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>

// EsoUnion
#include "common.h"

namespace EsoUnion
{
    class PlainTextProcessor
    {
        public:

            static std::string getUrlPrefix(
                const std::string &url);

            static void extractUrl(
                const int &max_url_extracted,
                const web_doc *doc,
                std::vector<std::string> &internal,
                std::vector<std::string> &external);

            static std::string formatUrl(
                const std::string &url_prefix,
                std::string &url);

            /**
             * Suitable only for small strings, since this
             * method makes a copy of the incomming text.
             */
            static std::vector<std::string> tokenize(
                std::string text,
                const char &delimiter = ' ');

            static std::string snippet(
                const std::string &block_text,
                const std::string &search_text,
                const size_t &snippet_length);

            static size_t caseInsensitiveFind(
                const std::string &text_block,
                std::string text_piece);

            static float howMuchOf(
                std::string text_block,
                std::string text_piece);
    };
}
