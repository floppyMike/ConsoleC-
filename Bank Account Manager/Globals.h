#pragma once

#include "Account.h"
#include "AccountDB.h"
#include "AccountMoney.h"
#include "AccountLogger.h"
#include "AccountSecurity.h"
#include "ATM.h"

using UserAccount = Account<AccountMoney, AccountLogger, AccountSecurity>;