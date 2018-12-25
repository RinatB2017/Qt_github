/*
 * LCD Image Converter. Converts images and fonts for embedded applications.
 * Copyright (C) 2012 riuson
 * mailto: riuson@gmail.com
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
 * along with this program.  If not, see <http://www.gnu.org/licenses/
 */

#include "externaltooloptions.h"

#include <appsettings.h>

const QString ExternalToolOptions::imageEditor()
{
  AppSettings appsett;
  QSettings &sett = appsett.get();
  sett.beginGroup("external-tools");
  QString result = sett.value("imageEditor", QVariant("gimp")).toString();
  sett.endGroup();

  return result;
}

void ExternalToolOptions::setImageEditor(const QString &value)
{
  AppSettings appsett;
  QSettings &sett = appsett.get();
  sett.beginGroup("external-tools");
  sett.setValue("imageEditor", QVariant(value));
  sett.endGroup();
}

