/*
 * gnote
 *
 * Copyright (C) 2013 Aurimas Cernius
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "iactionmanager.hpp"

namespace gnote {

const int IActionManager::APP_ACTION_NEW = 1;
const int IActionManager::APP_ACTION_MANAGE = 2;
const int IActionManager::APP_ACTION_HELP = 3;
const int IActionManager::APP_ACTION_LAST = 4;

IActionManager::~IActionManager()
{}

}

