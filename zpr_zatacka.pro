TEMPLATE = subdirs

SUBDIRS += \
    app_clients \
    app_server \
    GamePlay \
    GamePlayTest \
    Communication \
    CommunicationTest

app_clients.subdir = app_clients
app_server.subdir = app_server
GamePlay.subdir = GamePlay
GamePlayTest.subdir = GamePlayTest
Communication.subdir = Communication
CommuniactionTest.subdir = CommunicationTest

Communication.depends += GamePlay

app_clients.depends += GamePlay Communication

app_server.depends += GamePlay Communication

GamePlayTest.depends += GamePlay

CommunicationTest.depends += GamePlay Communication
