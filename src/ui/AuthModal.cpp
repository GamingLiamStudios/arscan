#include "AuthModal.hpp"

#include <cstring>

void AuthModal::saneCallback(SANE_String_Const resource, SANE_Char *username, SANE_Char *password)
{
    // resource is the name of whatever needing authorization
    // username and password are write-only, and are the resultant username and password our GUI
    // supplies

    std::memset(username, 0, SANE_MAX_USERNAME_LEN);
    std::memset(password, 0, SANE_MAX_PASSWORD_LEN);

    QString   qResource(resource);
    AuthModal modal((qResource));
    modal.show();

    modal.exec();    // Block UI until resolved
}

AuthModal::AuthModal(const QString &resource)
{
    // TODO: Create Auth Modal UI

    // Set title to resource
    setWindowTitle(resource);
}