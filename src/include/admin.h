#include "express.h"
using namespace std;
class Admin : public IPacketQuery {
    private:
        int adminId;
        Account account;
    public:
        Admin(int adminId, Account account) :adminId(adminId), account(account) {}
        ~Admin() {}
        void query_packet(int type,string value) override;
        void query_user();
        string name();
};
void adminloop(Admin admin);