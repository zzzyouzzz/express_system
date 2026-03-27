#include "express.h"
using namespace std;
class Admin : public IAccountQuery {
    private:
        int adminId;
        Account accounts;
    public:
        Admin(int adminId, Account accounts) :adminId(adminId), accounts(accounts) {}
};