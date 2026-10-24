#pragma once

#include <QtWidgets>
#include <sane/sane.h>

class AuthModal : public QDialog
{
    Q_OBJECT

public:
    AuthModal(const QString &resource);

    static void saneCallback(
      SANE_String_Const resource,
      SANE_Char         username[SANE_MAX_USERNAME_LEN],
      SANE_Char         password[SANE_MAX_PASSWORD_LEN]);
};