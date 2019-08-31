#include "Globals.h"

int main(int argc, char** argv)
{
	AccountDB<UserAccount> db;
	db.createAccount("ass");

	ATM atm(&db);
	atm.access("ass", 000)->deposit(100.f)
		.takeOut(50.f)
		.deposit(25.f)
		.setPin(100);

	atm.access("ass", 100)->showLogs();

	return 0;
}