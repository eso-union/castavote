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
#include <Wt/WApplication.h>
#include <Wt/WBootstrapTheme.h>
#include <Wt/WEnvironment.h>
#include <Wt/WHBoxLayout.h>
#include <Wt/WBootstrap5Theme.h>
#include <Wt/WCssTheme.h>
#include <Wt/WLink.h>

// Json
#include <nlohmann/json.hpp>

// EsoUnion
#include "app_generator.h"
#include "common.h"
#include "master_page.h"

EsoUnion::AppGenerator::AppGenerator(nlohmann::json &opt)
    :commonResources(new EsoUnion::SharedResources(opt))
{}

std::unique_ptr<Wt::WApplication>
    EsoUnion::AppGenerator::createApplication(
        const Wt::WEnvironment& env)
{
    /**
     * Instantiate the application object.
     **/
    auto app = std::make_unique<Wt::WApplication>(env);

    /**
     * Verifying approot directory.
     **/
    if (app->appRoot().empty())
    {
        Wt::log("error") << WARNING_APPROOT_EMPTY;
    }

    /**
     * Using Bootstrap CSS version 5.
     **/
    auto bootstrapTheme = std::make_shared<Wt::WBootstrap5Theme>();
    app->setTheme(bootstrapTheme);

    /**
     * Additional stylesheet.
     **/
    app->useStyleSheet("/style/paranal_common.css");
    app->useStyleSheet("/style/paranal_light.css");

    /**
     * Load text bundles.
     **/
    app->messageResourceBundle().use(app->appRoot() + "text");
    app->root()->addWidget(
        std::make_unique<EsoUnion::MasterPage>(
            commonResources, app.get()));

    /**
     * Set web site title.
     **/
    app->setTitle("Sindicato Paranal");

    return app;
}
