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

// C++
#include <cctype>
#include <chrono>

// Boost
#include <boost/algorithm/string.hpp>

// Wt
#include <Wt/WAbstractItemModel.h>
#include <Wt/WAnchor.h>
#include <Wt/WApplication.h>
#include <Wt/WButtonGroup.h>
#include <Wt/WCheckBox.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WEnvironment.h>
#include <Wt/WPopupMenu.h>
#include <Wt/WPushButton.h>
#include <Wt/WLabel.h>
#include <Wt/WLink.h>
#include <Wt/WLineEdit.h>
#include <Wt/WRadioButton.h>
#include <Wt/WString.h>
#include <Wt/WStringListModel.h>
#include <Wt/WTable.h>
#include <Wt/WTabWidget.h>
#include <Wt/WTemplate.h>
#include <Wt/WText.h>
#include <Wt/Utils.h>

// EsoUnion
#include "file_ops.h"
#include "plain_text_processor.h"
#include "master_page.h"
#include "shared_resources.h"

EsoUnion::MasterPage::MasterPage(
    boost::shared_ptr<EsoUnion::SharedResources> &sr,
    Wt::WApplication* app):
        Wt::WContainerWidget(),
        application(app),
        shared_resources(sr)
{
    /*
    addStyleClass("d-flex");
    addStyleClass("h-100");
    addStyleClass("text-bg-primary");
    */

    container = addWidget(std::make_unique<Wt::WContainerWidget>());
    container->addStyleClass("cover-container");
    container->addStyleClass("d-flex");
    container->addStyleClass("w-100");
    container->addStyleClass("h-100");
    container->addStyleClass("p-3");
    container->addStyleClass("mx-auto");
    container->addStyleClass("flex-column");

    Select();
}

void EsoUnion::MasterPage::Select()
{
    switch(state)
    {
        case(INITIALISE):
        {
            Initialise();
            break;
        }
        case(VALIDATE_VOTER_LIST):
        {
            ValidateVoterList();
        } break;
        case(START_VOTING):
        {
            StartVoting();
        } break;
        case(WAITING):
        {
            Waiting();
        } break;
        case(GET_RESULTS):
        {
            GettingResults();
        } break;
        case(CLOSED):
        {
            Closed();
        } break;
    }
}

void EsoUnion::MasterPage::Initialise()
{
    auto main_area = std::make_unique<Wt::WContainerWidget>();

    main_area->addWidget(
        std::make_unique<Wt::WTemplate>(
            Wt::WString::tr("search-page-header")));

    auto okPtr = std::make_unique<Wt::WPushButton>("Activar inspectores y testigos");
    auto ok = okPtr.get();

    ok->clicked().connect(ok, &Wt::WPushButton::disable);
    ok->clicked().connect([=] {
        // ok->setText("Activados");
        state = VALIDATE_VOTER_LIST;
        container->clear();
        Select();
    });

    main_area->addWidget(std::move(okPtr));
    container->addWidget(std::move(main_area));
}

void EsoUnion::MasterPage::ValidateVoterList()
{
    auto main_area = std::make_unique<Wt::WContainerWidget>();

    main_area->addWidget(
        std::make_unique<Wt::WTemplate>(
            Wt::WString::tr("search-page-header")));

    auto okPtr = std::make_unique<Wt::WPushButton>("Validar nomina");
    auto ok = okPtr.get();

    ok->clicked().connect(ok, &Wt::WPushButton::disable);
    ok->clicked().connect([=] {
        // ok->setText("Nomina validada");
        state = START_VOTING;
        container->clear();
        Select();
    });

    main_area->addWidget(std::move(okPtr));
    container->addWidget(std::move(main_area));
}

void EsoUnion::MasterPage::StartVoting()
{
    auto main_area = std::make_unique<Wt::WContainerWidget>();

    main_area->addWidget(
        std::make_unique<Wt::WTemplate>(
            Wt::WString::tr("search-page-header")));

    auto okPtr = std::make_unique<Wt::WPushButton>("Iniciar votacion");
    auto ok = okPtr.get();

    ok->clicked().connect(ok, &Wt::WPushButton::disable);
    ok->clicked().connect([=] {
        state = WAITING;
        container->clear();
        Select();
    });

    main_area->addWidget(std::move(okPtr));
    container->addWidget(std::move(main_area));
}

void EsoUnion::MasterPage::Waiting()
{
    auto main_area = std::make_unique<Wt::WContainerWidget>();

    main_area->addWidget(
        std::make_unique<Wt::WTemplate>(
            Wt::WString::tr("search-page-header")));

    auto okPtr = std::make_unique<Wt::WPushButton>("Terminar espera");
    auto ok = okPtr.get();

    ok->clicked().connect(ok, &Wt::WPushButton::disable);
    ok->clicked().connect([=] {
        state = GET_RESULTS;
        container->clear();
        Select();
    });

    main_area->addWidget(std::move(okPtr));
    container->addWidget(std::move(main_area));
}

void EsoUnion::MasterPage::GettingResults()
{
    auto main_area = std::make_unique<Wt::WContainerWidget>();

    main_area->addWidget(
        std::make_unique<Wt::WTemplate>(
            Wt::WString::tr("search-page-header")));

    auto okPtr = std::make_unique<Wt::WPushButton>("Termnar votacion y obtener resultados");
    auto ok = okPtr.get();

    ok->clicked().connect(ok, &Wt::WPushButton::disable);
    ok->clicked().connect([=] {
        state = CLOSED;
        container->clear();
        Select();
    });

    main_area->addWidget(std::move(okPtr));
    container->addWidget(std::move(main_area));
}

void EsoUnion::MasterPage::Closed()
{
    auto main_area = std::make_unique<Wt::WContainerWidget>();

    main_area->addWidget(
        std::make_unique<Wt::WTemplate>(
            Wt::WString::tr("search-page-header")));


    container->addWidget(std::move(main_area));
}
