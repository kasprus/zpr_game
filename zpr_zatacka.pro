TEMPLATE = subdirs

SUBDIRS += \
    app_clients \
    app_server \
    GamePlay \
    GamePlayTest \
    Communication \
    CommunicationTest

Communication.depends += GamePlay

app_clients.depends += Communication
app_clients.depends += GamePlay

app_server.depends += Communication
app_server.depends += GamePlay


GamePlayTest.depends += GamePlay

CommunicationTest.depends += Communication \
    GamePlay
