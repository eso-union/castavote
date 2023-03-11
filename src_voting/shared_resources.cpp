/***********************************************************************
 * Copyright (C) Nicolas Slusarenko
 *               nicolas.slusarenko@sindicatoparanal.cl
 *
 * This file is part of Cast-a-vote.
 *
 * Cast-a-vote is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Cast-a-vote is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Cast-a-vote. If not, see <http://www.gnu.org/licenses/>.
 **********************************************************************/

// Wt
#include <Wt/WLogger.h>

// Fmt
#include <fmt/format.h>

// EsoUnion
#include "common.h"
#include "file_ops.h"
#include "shared_resources.h"

EsoUnion::SharedResources::SharedResources(
    nlohmann::json &value):
        settings(value)
{
    // transfers.reset(new EsoUnion::Transfers(settings));
}

EsoUnion::SharedResources::~SharedResources()
{}
