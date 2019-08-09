// This file is generated by kconfig_compiler_kf5 from kmines.kcfg.
// All changes you do to this file will be lost.

#include "settings.h"

#include <qglobal.h>
#include <QtCore/QFile>

class SettingsHelper
{
  public:
    SettingsHelper() : q(nullptr) {}
    ~SettingsHelper() { delete q; }
    Settings *q;
};
Q_GLOBAL_STATIC(SettingsHelper, s_globalSettings)
Settings *Settings::self()
{
  if (!s_globalSettings()->q) {
    new Settings;
    s_globalSettings()->q->read();
  }

  return s_globalSettings()->q;
}

Settings::Settings(  )
  : KConfigSkeleton( QStringLiteral( "kminesrc" ) )
{
  Q_ASSERT(!s_globalSettings()->q);
  s_globalSettings()->q = this;
  setCurrentGroup( QStringLiteral( "General" ) );

  KConfigSkeleton::ItemBool  *itemUseQuestionMarks;
  itemUseQuestionMarks = new KConfigSkeleton::ItemBool( currentGroup(), QStringLiteral( "question mark" ), mUseQuestionMarks, true );
  addItem( itemUseQuestionMarks, QStringLiteral( "UseQuestionMarks" ) );

  setCurrentGroup( QStringLiteral( "Options" ) );

  KConfigSkeleton::ItemInt  *itemCustomWidth;
  itemCustomWidth = new KConfigSkeleton::ItemInt( currentGroup(), QStringLiteral( "custom width" ), mCustomWidth, 10 );
  itemCustomWidth->setMinValue(5);
  itemCustomWidth->setMaxValue(50);
  addItem( itemCustomWidth, QStringLiteral( "CustomWidth" ) );
  KConfigSkeleton::ItemInt  *itemCustomHeight;
  itemCustomHeight = new KConfigSkeleton::ItemInt( currentGroup(), QStringLiteral( "custom height" ), mCustomHeight, 10 );
  itemCustomHeight->setMinValue(5);
  itemCustomHeight->setMaxValue(50);
  addItem( itemCustomHeight, QStringLiteral( "CustomHeight" ) );
  KConfigSkeleton::ItemInt  *itemCustomMines;
  itemCustomMines = new KConfigSkeleton::ItemInt( currentGroup(), QStringLiteral( "custom mines" ), mCustomMines, 20 );
  itemCustomMines->setMinValue(1);
  addItem( itemCustomMines, QStringLiteral( "CustomMines" ) );
}

Settings::~Settings()
{
  s_globalSettings()->q = nullptr;
}
