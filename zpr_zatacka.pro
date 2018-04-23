TEMPLATE = subdirs

SUBDIRS += \
    app_clients \
    app_server \
    GamePlay \
    GamePlayTest \
    Communication \
    CommunicationTest

app_clients.depends += Communication
app_clients.depends += GamePlay

app_server.depends += Communication
app_server.depends += GamePlay
