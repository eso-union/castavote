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
#include "voting_page.h"
#include "shared_resources.h"

EsoUnion::VotingPage::VotingPage(
    boost::shared_ptr<EsoUnion::SharedResources> &sr,
    Wt::WApplication* app):
        Wt::WContainerWidget(),
        application(app),
        shared_resources(sr)
{
    addStyleClass("d-flex");
    addStyleClass("h-100");
    addStyleClass("text-bg-primary");

    container = addWidget(std::make_unique<Wt::WContainerWidget>());
    container->addStyleClass("cover-container");
    container->addStyleClass("d-flex");
    container->addStyleClass("w-100");
    container->addStyleClass("h-100");
    container->addStyleClass("p-3");
    container->addStyleClass("mx-auto");
    container->addStyleClass("flex-column");

    container->addWidget(
        std::make_unique<Wt::WTemplate>(
            Wt::WString::tr("search-page-header")));

    auto result =  std::make_unique<Wt::WTemplate>(Wt::WString::tr("code_input"));

    auto name = result->bindWidget("name", std::make_unique<Wt::WLineEdit>());
    name->setPlaceholderText("codigo");

    auto button = result->bindWidget("button", std::make_unique<Wt::WPushButton>("Validar"));

    auto out = result->bindWidget("out", std::make_unique<Wt::WText>());

    button->clicked().connect([=] {
        out->setText("Hello, " + name->text() + "! I just want to help you... You"
                    + " could complete this simple form by adding validation.");
        AddChoices();
    });

    container->addWidget(std::move(result));
}

void EsoUnion::VotingPage::AddChoices()
{
    auto choices = std::make_unique<Wt::WContainerWidget>();
    Wt::WCheckBox *cb;

    cb = choices->addNew<Wt::WCheckBox>("Candidato A");
    cb->setInline(false);

    cb = choices->addNew<Wt::WCheckBox>("Candidato B");
    cb->setInline(false);

    cb = choices->addNew<Wt::WCheckBox>("Candidato C");
    cb->setInline(false);

    container->addWidget(std::move(choices));
}
