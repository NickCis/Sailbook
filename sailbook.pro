# NOTICE:
#
# Application name defined in TARGET has a corresponding QML filename.
# If name defined in TARGET is changed, the following needs to be done
# to match new name:
#   - corresponding QML filename must be changed
#   - desktop icon filename must be changed
#   - desktop filename must be changed
#   - icon definition filename in desktop file must be changed
#   - translation filenames have to be changed

# The name of your application
TARGET = sailbook

CONFIG += sailfishapp

SOURCES += \
    src/request.cpp \
    src/configurator.cpp \
    #src/loginmanager_old.cpp \
    src/loginmanager.cpp \
    src/sailbook.cpp

OTHER_FILES += qml/sailbook.qml \
    qml/cover/CoverPage.qml \
    translations/*.ts \
    qml/pages/NewsFeed.qml \
    qml/components/Request.qml \
    qml/pages/TokenGetter.qml \
    qml/pages/MainMenu.qml \
    qml/js/request.js \
    qml/components/FeedList.qml \
    qml/pages/GenericElement.qml \
    sailbook.desktop \
    rpm/sailbook.yaml \
    rpm/sailbook.spec \
    rpm/sailbook.changes.in

# to disable building translations every time, comment out the
# following CONFIG line
CONFIG += sailfishapp_i18n
TRANSLATIONS += translations/sailbook-de.ts

HEADERS += \
    src/request.h \
    src/configurator.h \
    #src/loginmanager_old.h \
    src/loginmanager.h

