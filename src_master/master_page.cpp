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
#include <Wt/WTextArea.h>
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

    // Add general password.

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
            break;
        }
        case(START_VOTING):
        {
            StartVoting();
            break;
        }
        case(WAITING):
        {
            Waiting();
            break;
        }
        case(GET_RESULTS):
        {
            GettingResults();
            break;
        }
        case(CLOSED):
        {
            Closed();
            break;
        }
    }
}

void EsoUnion::MasterPage::Initialise()
{
    auto main_area = std::make_unique<Wt::WContainerWidget>();

    main_area->addWidget(
        std::make_unique<Wt::WTemplate>(
            Wt::WString::tr("search-page-header")));

    auto person_0 = std::make_unique<Wt::WTemplate>(Wt::WString::tr("code_input"));
    auto name_0 = person_0->bindWidget("name", std::make_unique<Wt::WLineEdit>());
    name_0->setPlaceholderText("nombre");
    auto button_0 = person_0->bindWidget("button", std::make_unique<Wt::WPushButton>("Crear"));
    auto out_0 = person_0->bindWidget("out", std::make_unique<Wt::WText>());
    button_0->clicked().connect([=] {
        CreateWitness();
        out_0->setText("Created: " + name_0->text());
    });
    main_area->addWidget(std::move(person_0));

    auto person_1 = std::make_unique<Wt::WTemplate>(Wt::WString::tr("code_input"));
    auto name_1 = person_1->bindWidget("name", std::make_unique<Wt::WLineEdit>());
    name_1->setPlaceholderText("nombre");
    auto button_1 = person_1->bindWidget("button", std::make_unique<Wt::WPushButton>("Crear"));
    auto out_1 = person_1->bindWidget("out", std::make_unique<Wt::WText>());
    button_1->clicked().connect([=] {
        out_1->setText("Created: " + name_1->text());
    });
    main_area->addWidget(std::move(person_1));

    auto person_2 = std::make_unique<Wt::WTemplate>(Wt::WString::tr("code_input"));
    auto name_2 = person_2->bindWidget("name", std::make_unique<Wt::WLineEdit>());
    name_2->setPlaceholderText("nombre");
    auto button_2 = person_2->bindWidget("button", std::make_unique<Wt::WPushButton>("Crear"));
    auto out_2 = person_2->bindWidget("out", std::make_unique<Wt::WText>());
    button_2->clicked().connect([=] {
        out_2->setText("Created: " + name_2->text());
    });
    main_area->addWidget(std::move(person_2));

    auto person_3 = std::make_unique<Wt::WTemplate>(Wt::WString::tr("code_input"));
    auto name_3 = person_3->bindWidget("name", std::make_unique<Wt::WLineEdit>());
    name_3->setPlaceholderText("nombre");
    auto button_3 = person_3->bindWidget("button", std::make_unique<Wt::WPushButton>("Crear"));
    auto out_3 = person_3->bindWidget("out", std::make_unique<Wt::WText>());
    button_3->clicked().connect([=] {
        out_3->setText("Created: " + name_3->text());
    });
    main_area->addWidget(std::move(person_3));

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

    Wt::WTextArea *ta = main_area->addNew<Wt::WTextArea>();
    ta->setColumns(80);
    ta->setRows(20);
    ta->setText("Lista de los votantes");

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

    Wt::WTextArea *ta = main_area->addNew<Wt::WTextArea>();
    ta->setColumns(80);
    ta->setRows(20);
    ta->setText("Estado de los envios");

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

    auto time = std::make_unique<Wt::WText>("Faltan <b>23:00</b> para poder "
                    "cerrar esta votacion y obtener los resultados.");

    main_area->addWidget(std::move(time));

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

    auto okPtr = std::make_unique<Wt::WPushButton>("Terminar votacion y obtener resultados");
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

void EsoUnion::MasterPage::CreateWitness()
{
    auto witness_box = addChild(std::make_unique<Wt::WDialog>("Preferences"));

    auto witness_fields = std::make_unique<Wt::WTable>();
    witness_fields->addStyleClass("table");

    witness_fields->elementAt(0, 0)->addNew<Wt::WLabel>("hello");

    auto closeButton = std::make_unique<Wt::WPushButton>("Close");
    closeButton->addStyleClass("btn btn-primary");
    closeButton->clicked().connect([=] {
                                            // if(savePreferences())
                                            {
                                                removeChild(witness_box);
                                            }
                                       });

    // Process the dialog result.
    witness_box->finished().connect([=] {
                                            // if(savePreferences())
                                            {
                                                removeChild(witness_box);
                                            }
                                        });

    auto explanation = std::make_unique<Wt::WLabel>("Recuerde su clave, la necesitara para cerrar la votacion y obtener los resultados.");

    witness_box->contents()->addWidget(std::move(witness_fields));
    witness_box->footer()->addWidget(std::move(explanation));
    witness_box->footer()->addWidget(std::move(closeButton));
    witness_box->rejectWhenEscapePressed();
    witness_box->setModal(true);
    witness_box->show();
}
