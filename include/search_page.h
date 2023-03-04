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

#pragma once

// C++
#include <memory>
#include <string>

// Wt
#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WNavigationBar.h>
#include <Wt/WMessageBox.h>
#include <Wt/WMenu.h>
#include <Wt/WPopupMenu.h>
#include <Wt/WSelectionBox.h>
#include <Wt/WStringListModel.h>
#include <Wt/WSuggestionPopup.h>
#include <Wt/WTimer.h>

// EsoUnion
#include "preferences.h"
#include "shared_resources.h"

namespace EsoUnion
{
    class SearchPage : public Wt::WContainerWidget
    {
        public:

            SearchPage(
                boost::shared_ptr<EsoUnion::SharedResources> &sr,
                Wt::WApplication* app);

        private:

            Wt::WApplication *application;
            Wt::WContainerWidget *container = nullptr;

            boost::shared_ptr<EsoUnion::SharedResources> shared_resources;
    };
}
